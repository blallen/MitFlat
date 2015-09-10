#include "MitFlat/Mods/interface/MuGammaTree.h"
#include "MitAna/DataTree/interface/EventHeader.h"
#include "MitAna/DataTree/interface/MCEventInfo.h"
#include "MitAna/DataTree/interface/MetCol.h"
#include "MitAna/DataTree/interface/JetCol.h"
#include "MitAna/DataTree/interface/MuonCol.h"
#include "MitAna/DataTree/interface/PhotonCol.h"
#include "MitAna/DataTree/interface/ElectronCol.h"
#include "MitAna/DataTree/interface/PFTauCol.h"
#include "MitAna/DataTree/interface/DecayParticleCol.h"
#include "MitAna/DataTree/interface/VertexCol.h"
#include "MitAna/DataTree/interface/PFCandidateCol.h"
#include "MitAna/DataTree/interface/PileupEnergyDensityCol.h"
#include "MitAna/DataTree/interface/Names.h"
#include "MitAna/DataCont/interface/Types.h"

#include "MitPhysics/Utils/interface/PhotonTools.h"
#include "MitPhysics/Utils/interface/IsolationTools.h"

#include <iostream>
#include <cstring>
#include <cmath>

ClassImp(mithep::MuGammaTree)

void
mithep::MuGammaTree::Process()
{
  auto* eventHeader = GetEventHeader();  
  auto* energyDensity = GetObject<PileupEnergyDensityCol>(mithep::Names::gkPileupEnergyDensityBrn);

  fAllEvent.run = eventHeader->RunNum();
  fAllEvent.lumi = eventHeader->LumiSec();
  fAllEvent.event = eventHeader->EvtNum();
  fAllEvent.weight = 1.;
  fAllEvent.rho = energyDensity->At(0)->Rho(fRhoAlgo);
  
  MCEventInfo* mcEvent = 0;
  if (fIsMC) {
    mcEvent = GetObject<MCEventInfo>(mithep::Names::gkMCEvtInfoBrn);
    fAllEvent.weight = mcEvent->Weight();
  }

  fAllEventTree->Fill();

  if (fCondition && !fCondition->IsActive())
    return;

  fEvent.run = eventHeader->RunNum();
  fEvent.lumi = eventHeader->LumiSec();
  fEvent.event = eventHeader->EvtNum();
  fEvent.weight = 1.;
  fEvent.rho = energyDensity->At(0)->Rho(fRhoAlgo);

  if (fIsMC) {
    fEvent.weight = mcEvent->Weight();
    fEvent.genHt = 0.;
    fEvent.genZpt = -1.;
    for (unsigned iP = 0; iP != mcEvent->NPartons(); ++iP) {
      if (mcEvent->PartonStatus(iP) == 1)
        fEvent.genHt += mcEvent->PartonMom(iP)->Pt();
      if (mcEvent->PartonId(iP) == 23)
        fEvent.genZpt = mcEvent->PartonMom(iP)->Pt();
    }
  }

  mugamma::Met* outMets[] = {
    &fEvent.rawMet,
    &fEvent.t1Met,
    &fEvent.t1NoCHSMet,
    &fEvent.eta30Met,
    &fEvent.eta30T1Met,
    &fEvent.eta30T1NoCHSMet,
    &fEvent.nhScaledMet,
    &fEvent.chMet,
    &fEvent.nhMet,
    &fEvent.neMet,
    &fEvent.chGt30Met,
    &fEvent.nhGt30Met,
    &fEvent.neGt30Met
  };

  TString metNames[] = {
    fRawMetName,
    fT1MetName,
    fT1NoCHSMetName,
    fEta30MetName,
    fEta30T1MetName,
    fEta30T1NoCHSMetName,
    fNHScaledMetName,
    fCHMetName,
    fNHMetName,
    fNEMetName,
    fCHGt30MetName,
    fNHGt30MetName,
    fNEGt30MetName
  };

  for (unsigned iM = 0; iM != sizeof(outMets) / sizeof(mugamma::Met*); ++iM) {
    auto* mets = GetObject<mithep::MetCol>(metNames[iM]);
    if (!mets) {
      SendError(kAbortAnalysis, "Process", metNames[iM]);
      return;
    }
    auto& inMet(*mets->At(0));
    auto& outMet(*outMets[iM]);
    outMet.met = inMet.Pt();
    outMet.phi = inMet.Phi();
    outMet.sumEt = inMet.SumEt();
  }

  if (fPhotonsName.Length() != 0) {
    auto* photons = GetObject<mithep::PhotonCol>(fPhotonsName);
    auto* electrons = GetObject<mithep::ElectronCol>(fElectronsName);
    auto* conversions = GetObject<mithep::DecayParticleCol>(fConversionsName);
    auto* vertices = GetObject<mithep::VertexCol>(fVerticesName);
    auto* pfCandidates = GetObject<mithep::PFCandidateCol>(Names::gkPFCandidatesBrn);

    auto* looseMask = GetObject<mithep::NFArrBool>(fLoosePhotonName);
    auto* mediumMask = GetObject<mithep::NFArrBool>(fMediumPhotonName);
    auto* tightMask = GetObject<mithep::NFArrBool>(fTightPhotonName);

    fEvent.photons.resize(photons->GetEntries());

    unsigned nP(0);
    for (unsigned iP = 0; iP != photons->GetEntries(); ++iP) {
      auto& inPhoton(*photons->At(iP));
      if (inPhoton.Pt() < 10.)
        continue;

      auto& outPhoton(fEvent.photons[nP]);

      double chIso, nhIso, phIso;
      IsolationTools::PFPhotonIsoFootprintRemoved(&inPhoton, vertices->At(0), pfCandidates, 0.3, chIso, nhIso, phIso);
      outPhoton.pt = inPhoton.Pt();
      outPhoton.eta = inPhoton.Eta();
      outPhoton.phi = inPhoton.Phi();
      outPhoton.chIso = chIso;
      outPhoton.nhIso = nhIso;
      outPhoton.phIso = phIso;
      outPhoton.sieie = inPhoton.CoviEtaiEta5x5();
      outPhoton.hOverE = inPhoton.HadOverEm();
      outPhoton.pixelVeto = !inPhoton.HasPixelSeed();
      outPhoton.csafeVeto = !PhotonTools::PassElectronVetoConvRecovery(&inPhoton, electrons, conversions, vertices->At(0));
      outPhoton.isLoose = looseMask->At(iP);
      outPhoton.isMedium = mediumMask->At(iP);
      outPhoton.isTight = tightMask->At(iP);

      ++nP;
    }

    fEvent.photons.resize(nP);
  }

  if (fElectronsName.Length() != 0) {
    auto* electrons = GetObject<mithep::ElectronCol>(fElectronsName);
    if (!electrons) {
      SendError(kAbortAnalysis, "Process", fElectronsName);
      return;
    }

    auto* tightMask = GetObject<mithep::NFArrBool>(fTightElectronsName);

    fEvent.electrons.resize(electrons->GetEntries());
    for (unsigned iE = 0; iE != electrons->GetEntries(); ++iE) {
      auto& inElectron(*electrons->At(iE));
      auto& outElectron(fEvent.electrons[iE]);
      outElectron.pt = inElectron.Pt();
      outElectron.eta = inElectron.Eta();
      outElectron.phi = inElectron.Phi();
      outElectron.mass = inElectron.Mass();
      outElectron.tight = tightMask->At(iE);
    }
  }

  if (fMuonsName.Length() != 0) {
    auto* muons = GetObject<mithep::MuonCol>(fMuonsName);
    if (!muons) {
      SendError(kAbortAnalysis, "Process", fMuonsName);
      return;
    }

    auto* tightMask = GetObject<mithep::NFArrBool>(fTightMuonsName);

    fEvent.muons.resize(muons->GetEntries());
    for (unsigned iM = 0; iM != muons->GetEntries(); ++iM) {
      auto& inMuon(*muons->At(iM));
      auto& outMuon(fEvent.muons[iM]);
      outMuon.pt = inMuon.Pt();
      outMuon.eta = inMuon.Eta();
      outMuon.phi = inMuon.Phi();
      outMuon.mass = inMuon.Mass();
      outMuon.tight = tightMask->At(iM);
    }
  }

  if (fTausName.Length() != 0) {
    auto* taus = GetObject<mithep::PFTauCol>(fTausName);
    if (!taus) {
      SendError(kAbortAnalysis, "Process", fTausName);
      return;
    }

    fEvent.ntau = taus->GetEntries();
  }

  if (fJetsName.Length() != 0) {
    auto* jets = GetObject<mithep::JetCol>(fJetsName);
    if (!jets) {
      SendError(kAbortAnalysis, "Process", fJetsName);
      return;
    }

    fEvent.jets.resize(jets->GetEntries());
    for (unsigned iJ = 0; iJ != jets->GetEntries(); ++iJ) {
      auto& inJet(*jets->At(iJ));
      auto& outJet(fEvent.jets[iJ]);
      outJet.pt = inJet.Pt();
      outJet.eta = inJet.Eta();
      outJet.phi = inJet.Phi();
      outJet.mass = inJet.Mass();
    }
  }

  fEventTree->Fill();
}

void
mithep::MuGammaTree::SlaveBegin()
{
  fEventTree = new TTree(fEventTreeName, "Events");
  fEvent.book(*fEventTree);

  fAllEventTree = new TTree(fAllEventTreeName, "Events");
  fAllEvent.book(*fAllEventTree);

  AddOutput(fEventTree);
  AddOutput(fAllEventTree);
}
