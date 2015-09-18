#include "MitFlat/Mods/interface/SimpleTreeMod.h"
#include "MitAna/DataTree/interface/EventHeader.h"
#include "MitAna/DataTree/interface/MCEventInfo.h"
#include "MitAna/DataTree/interface/ParticleCol.h"
#include "MitAna/DataTree/interface/MetCol.h"
#include "MitAna/DataTree/interface/JetCol.h"
#include "MitAna/DataTree/interface/PhotonCol.h"
#include "MitAna/DataTree/interface/PFTauCol.h"
#include "MitAna/DataTree/interface/DecayParticleCol.h"
#include "MitAna/DataTree/interface/VertexCol.h"
#include "MitAna/DataTree/interface/PFCandidateCol.h"
#include "MitAna/DataTree/interface/VertexCol.h"
#include "MitAna/DataTree/interface/PileupEnergyDensityCol.h"
#include "MitAna/DataTree/interface/MCParticleCol.h"
#include "MitAna/DataTree/interface/TriggerMask.h"
#include "MitAna/DataTree/interface/TriggerTable.h"
#include "MitAna/DataTree/interface/TriggerObjectCol.h"
#include "MitAna/DataTree/interface/Names.h"
#include "MitAna/DataCont/interface/Types.h"
#include "MitCommon/MathTools/interface/MathUtils.h"

#include "MitPhysics/Utils/interface/PhotonTools.h"
#include "MitPhysics/Utils/interface/IsolationTools.h"

#include "TVector3.h"

#include <iostream>
#include <cstring>
#include <cmath>

ClassImp(mithep::SimpleTreeMod)

void
mithep::SimpleTreeMod::Process()
{
  auto* eventHeader = GetEventHeader();
  auto* energyDensity = GetObject<mithep::PileupEnergyDensityCol>(mithep::Names::gkPileupEnergyDensityBrn);

  fAllEvent.run = eventHeader->RunNum();
  fAllEvent.lumi = eventHeader->LumiSec();
  fAllEvent.event = eventHeader->EvtNum();
  fAllEvent.weight = 1.;
  fAllEvent.rho = energyDensity->At(0)->Rho(fRhoAlgo);
  
  mithep::MCEventInfo* mcEvent = 0;
  if (fIsMC) {
    mcEvent = GetObject<mithep::MCEventInfo>(mithep::Names::gkMCEvtInfoBrn);
    fAllEvent.weight = mcEvent->Weight();
  }

  fAllEventTree->Fill();

  if (fCondition && !fCondition->IsActive())
    return;

  auto* vertices = GetObject<mithep::VertexCol>(fVerticesName);
  auto* pfCandidates = GetObject<mithep::PFCandidateCol>(Names::gkPFCandidatesBrn);
  auto* triggerMask = GetObject<mithep::TriggerMask>(mithep::Names::gkHltBitBrn);
  mithep::MCParticleCol* mcParticles(0);
  std::vector<MCParticle*> finalState;

  mithep::TriggerObjectCol* triggerObjects[simpletree::nHLTPaths] = {};

  fEvent.run = eventHeader->RunNum();
  fEvent.lumi = eventHeader->LumiSec();
  fEvent.event = eventHeader->EvtNum();
  fEvent.weight = 1.;
  fEvent.rho = energyDensity->At(0)->Rho(fRhoAlgo);
  fEvent.npv = vertices->GetEntries();

  for (unsigned iH(0); iH != simpletree::nHLTPaths; ++iH) {
    if (fHLTIds[iH] != -1) {
      fEvent.hlt[iH].pass = triggerMask->At(fHLTIds[iH]);
      if (fEvent.hlt[iH].pass)
        triggerObjects[iH] = GetObject<mithep::TriggerObjectCol>(fTriggerObjectsName[iH]);
    }
    else
      fEvent.hlt[iH].pass = false;
  }

  if (fIsMC) {
    mcParticles = GetObject<mithep::MCParticleCol>("MCParticles");
    for (unsigned iP(0); iP != mcParticles->GetEntries(); ++iP) {
      if (mcParticles->At(iP)->Status() == 1)
        finalState.push_back(mcParticles->At(iP));
    }

    fEvent.weight = mcEvent->Weight();
    fEvent.genHt = 0.;
    fEvent.genZpt = -1.;
    for (unsigned iP = 0; iP != mcEvent->NPartons(); ++iP) {
      int pid(mcEvent->PartonId(iP));
      if (mcEvent->PartonStatus(iP) == 1 && pid != 12 && pid != 14 && pid != 16)
        fEvent.genHt += mcEvent->PartonMom(iP)->Pt();
      if (pid == 23)
        fEvent.genZpt = mcEvent->PartonMom(iP)->Pt();
    }
  }

  simpletree::Met* outMets[] = {
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

  for (unsigned iM = 0; iM != sizeof(outMets) / sizeof(simpletree::Met*); ++iM) {
    if (metNames[iM].Length() == 0)
      continue;

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
    auto* electrons = GetObject<mithep::ElectronCol>(Names::gkElectronBrn);
    auto* conversions = GetObject<mithep::DecayParticleCol>(fConversionsName);

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
      IsolationTools::PFEGIsoFootprintRemoved(&inPhoton, vertices->At(0), pfCandidates, 0.3, chIso, nhIso, phIso);
      double scEta(inPhoton.SCluster()->AbsEta());

      outPhoton.pt = inPhoton.Pt();
      outPhoton.eta = inPhoton.Eta();
      outPhoton.phi = inPhoton.Phi();
      outPhoton.chIso = IsolationTools::PFPhotonIsolationRhoCorr(scEta, chIso, fEvent.rho, PhotonTools::kPhoEAPhys14, PhotonTools::kPhoChargedHadron03);
      outPhoton.nhIso = IsolationTools::PFPhotonIsolationRhoCorr(scEta, nhIso, fEvent.rho, PhotonTools::kPhoEAPhys14, PhotonTools::kPhoNeutralHadron03);
      outPhoton.phIso = IsolationTools::PFPhotonIsolationRhoCorr(scEta, phIso, fEvent.rho, PhotonTools::kPhoEAPhys14, PhotonTools::kPhoPhoton03);
      outPhoton.sieie = inPhoton.CoviEtaiEta5x5();
      outPhoton.hOverE = inPhoton.HadOverEm();
      outPhoton.pixelVeto = !inPhoton.HasPixelSeed();
      outPhoton.csafeVeto = !PhotonTools::PassElectronVetoConvRecovery(&inPhoton, electrons, conversions, vertices->At(0));
      outPhoton.loose = looseMask->At(iP);
      outPhoton.medium = mediumMask->At(iP);
      outPhoton.tight = tightMask->At(iP);

      auto&& caloPos(inPhoton.CaloPos());

      bool* hltMatch[] = {
        &outPhoton.matchHLT165HE10,
        &outPhoton.matchHLT175
      };
      mithep::TriggerObjectCol* objCol[] = {
        triggerObjects[simpletree::kPhoton165HE10],
        triggerObjects[simpletree::kPhoton175]
      };

      for (unsigned iT(0); iT != 2; ++iT) {
        if (!objCol[iT]) {
          *hltMatch[iT] = false;
          continue;
        }

        unsigned iO(0);
        for (; iO != objCol[iT]->GetEntries(); ++iO) {
          auto& trigObj(*objCol[iT]->At(iO));
          double dEta(caloPos.Eta() - trigObj.Eta());
          double dPhi(TVector2::Phi_mpi_pi(caloPos.Phi() - trigObj.Phi()));
          if (dEta * dEta + dPhi * dPhi < 0.0225)
            break;
        }
        *hltMatch[iT] = (iO != objCol[iT]->GetEntries());
      }

      if (fIsMC) {
        outPhoton.matchedGen = 0;

        double minDR(-1.);
        mithep::MCParticle* matched(0);

        for (auto* part : finalState) {
          TVector3 caloDir(caloPos.X(), caloPos.Y(), caloPos.Z());
          auto&& vtx(part->Mother()->DecayVertex());
          caloDir -= TVector3(vtx.X(), vtx.Y(), vtx.Z());
          double dR(caloDir.DeltaR(TVector3(part->Px(), part->Py(), part->Pz())));
          if (dR < 0.1 && (minDR < 0. || dR < minDR)) {
            outPhoton.matchedGen = part->PdgId();
            unsigned absId(std::abs(outPhoton.matchedGen));
            if (dR < 0.1 && (absId == 11 || absId == 13))
              break;

            minDR = dR;
            matched = part;
          }
        }

        if (matched) {
          unsigned motherId(std::abs(matched->DistinctMother()->PdgId()));
          outPhoton.hadDecay = (motherId == 21 || motherId > 25); // 21 probably never happens..
        }
        else
          outPhoton.hadDecay = false;
      }

      ++nP;
    }

    fEvent.photons.resize(nP);
  }

  TString* inputLeptonName[2] = {
    &fElectronsName,
    &fMuonsName
  };

  TString* tightMaskName[2] = {
    &fTightElectronsName,
    &fTightMuonsName
  };

  simpletree::LeptonCollection* outputCollection[2] = {
    &fEvent.electrons,
    &fEvent.muons
  };

  bool* hltMatch[2][2] = {
    {
      fEvent.electrons.matchHLT23Loose,
      fEvent.electrons.matchHLT27Loose
    },
    {
      fEvent.muons.matchHLT24,
      fEvent.muons.matchHLT27
    }
  };

  mithep::TriggerObjectCol* trigObjs[2][2] = {
    {
      triggerObjects[simpletree::kEle23Loose],
      triggerObjects[simpletree::kEle27Loose]
    },
    {
      triggerObjects[simpletree::kMu24],
      triggerObjects[simpletree::kMu27]
    }
  };

  for (unsigned iC(0); iC != 2; ++iC) {
    if (inputLeptonName[iC]->Length() != 0) {
      auto* leptons = GetObject<mithep::ParticleCol>(*inputLeptonName[iC]);
      if (!leptons) {
        SendError(kAbortAnalysis, "Process", *inputLeptonName[iC]);
        return;
      }

      mithep::NFArrBool* looseMask = 0;
      auto* tightMask = GetObject<mithep::NFArrBool>(*tightMaskName[iC]);
      if (iC == 0)
        looseMask = GetObject<mithep::NFArrBool>(fLooseElectronsName);

      outputCollection[iC]->resize(leptons->GetEntries());
      for (unsigned iL = 0; iL != leptons->GetEntries(); ++iL) {
        auto& inLepton(*leptons->At(iL));
        auto& outLepton((*outputCollection[iC])[iL]);
        outLepton.pt = inLepton.Pt();
        outLepton.eta = inLepton.Eta();
        outLepton.phi = inLepton.Phi();
        outLepton.mass = inLepton.Mass();
        outLepton.positive = inLepton.Charge() > 0.;
        outLepton.tight = tightMask->At(iL);

        if (iC == 0) {
          auto& inElectron(static_cast<mithep::Electron&>(inLepton));
          auto& outElectron(static_cast<simpletree::Electron&>(outLepton));

          outElectron.loose = looseMask->At(iL);
          
          double chIso, nhIso, phIso;
          IsolationTools::PFEGIsoFootprintRemoved(&inElectron, vertices->At(0), pfCandidates, 0.3, chIso, nhIso, phIso);
          double scEta(inElectron.SCluster()->AbsEta());

          outElectron.chIsoPh = IsolationTools::PFPhotonIsolationRhoCorr(scEta, chIso, fEvent.rho, PhotonTools::kPhoEAPhys14, PhotonTools::kPhoChargedHadron03);
          outElectron.nhIsoPh = IsolationTools::PFPhotonIsolationRhoCorr(scEta, nhIso, fEvent.rho, PhotonTools::kPhoEAPhys14, PhotonTools::kPhoNeutralHadron03);
          outElectron.phIsoPh = IsolationTools::PFPhotonIsolationRhoCorr(scEta, phIso, fEvent.rho, PhotonTools::kPhoEAPhys14, PhotonTools::kPhoPhoton03);

          outElectron.sieie = inElectron.CoviEtaiEta5x5();
          outElectron.hOverE = inElectron.HadOverEmTow();
        }
        else {
          outLepton.loose = true;
        }

        for (unsigned iT(0); iT != 2; ++iT) {
          if (!trigObjs[iC][iT]) {
            hltMatch[iC][iT][iL] = false;
            continue;
          }

          unsigned iO(0);
          for (; iO != trigObjs[iC][iT]->GetEntries(); ++iO) {
            if (mithep::MathUtils::DeltaR(inLepton, *trigObjs[iC][iT]->At(iO)) < 0.1)
              break;
          }
          hltMatch[iC][iT][iL] = (iO != trigObjs[iC][iT]->GetEntries());
        }

        if (fIsMC) {
          outLepton.matchedGen = 0;

          double minDR(-1.);
          mithep::MCParticle* matched(0);

          for (auto* part : finalState) {
            double dR(mithep::MathUtils::DeltaR(inLepton, *part));
            if (dR < 0.05 && (minDR < 0. || dR < minDR)) {
              outLepton.matchedGen = part->PdgId();

              minDR = dR;
              matched = part;
            }
          }

          if (matched) {
            unsigned motherId(std::abs(matched->DistinctMother()->PdgId()));
            outLepton.tauDecay = (motherId == 15);
            outLepton.hadDecay = (motherId == 21 || motherId > 25);
          }
          else {
            outLepton.tauDecay = outLepton.hadDecay = false;
          }
        }
      }
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
mithep::SimpleTreeMod::SlaveBegin()
{
  fEventTree = new TTree(fEventTreeName, "Events");
  fEvent.book(*fEventTree);

  fAllEventTree = new TTree(fAllEventTreeName, "Events");
  fAllEvent.book(*fAllEventTree);

  AddOutput(fEventTree);
  AddOutput(fAllEventTree);
}

void
mithep::SimpleTreeMod::BeginRun()
{
  auto* hltTable = GetObject<mithep::TriggerTable>(TString::Format("%sFwk", mithep::Names::gkHltTableBrn));
  mithep::TriggerName const* triggerName(0);

  for (unsigned iH(0); iH != simpletree::nHLTPaths; ++iH) {
    triggerName = hltTable->GetWildcard("HLT_" + fTriggerPathName[iH] + "_v");
    if (triggerName)
      fHLTIds[iH] = triggerName->Id();
    else
      fHLTIds[iH] = -1;
  }
}
