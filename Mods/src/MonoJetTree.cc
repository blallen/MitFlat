#include "MitFlat/Mods/interface/MonoJetTree.h"
#include "MitAna/DataTree/interface/EventHeader.h"
#include "MitAna/DataTree/interface/PFMetCol.h"
#include "MitAna/DataTree/interface/PFJetCol.h"
#include "MitAna/DataTree/interface/ElectronCol.h"
#include "MitAna/DataTree/interface/MuonCol.h"
#include "MitAna/DataTree/interface/PFTauCol.h"
#include "MitAna/DataTree/interface/PhotonCol.h"
#include "MitAna/DataTree/interface/TriggerTable.h"
#include "MitAna/DataTree/interface/TriggerName.h"
#include "MitAna/DataTree/interface/TriggerMask.h"
#include "MitAna/DataTree/interface/TriggerObjectCol.h"
#include "MitAna/DataTree/interface/Names.h"

#include <iostream>
#include <cstring>

ClassImp(mithep::MonoJetTree)

void
mithep::MonoJetTree::Process()
{
  auto* eventHeader = GetEventHeader();

  fEvent.runNumber = eventHeader->RunNum();
  fEvent.lumiNumber = eventHeader->LumiSec();
  fEvent.eventNumber = eventHeader->EvtNum();

  if (fMetName.Length() != 0) {
    auto* inMet = GetObject<mithep::PFMetCol>(fMetName)->At(0);
    auto& met(fEvent.met);

    auto* inMuons = GetObject<mithep::MuonCol>(fMuonsName);

    auto nomu(inMet->Mom());
    for (unsigned iM = 0; iM != inMuons->GetEntries(); ++iM)
      nomu += inMuons->At(iM)->Mom();

    met.met = inMet->Pt();
    met.phi = inMet->Phi();
    met.metNoMu = nomu.Pt();
    met.phiNoMu = nomu.Phi();
  }

  // if (fJetsName.Length() != 0) {
  //   auto* inJets = GetObject<mithep::PFJetCol>(fJetsName);
  //   auto& jets(fEvent.jets);
  //   jets.resize(inJets->GetEntries());
  //   for (unsigned iJ = 0; iJ != inJets->GetEntries(); ++iJ) {
  //     auto& inJet(*inJets->At(iJ));
  //     auto& jet(jets.at(iJ));

  //     jet.pt = inJet.Pt();
  //     jet.eta = inJet.Eta();
  //     jet.phi = inJet.Phi();
  //     jet.btag = inJet.BJetTagsDisc(mithep::Jet::kCombinedInclusiveSecondaryVertexV2);
  //     jet.chFrac = inJet.ChargedHadronEnergy() / inJet.E();
  //     jet.nhFrac = inJet.NeutralHadronEnergy() / inJet.E();
  //     jet.neFrac = inJet.NeutralEmEnergy() / inJet.E();
  //   }
  // }

  // if (fElectronsName.Length() != 0) {
  //   auto* inElectrons = GetObject<mithep::ElectronCol>(fElectronsName);
  //   auto& electrons(fEvent.electrons);
  //   electrons.resize(inElectrons->GetEntries());
  //   for (unsigned iE = 0; iE != inElectrons->GetEntries(); ++iE) {
  //     auto& inElectron(*inElectrons->At(iE));
  //     auto& electron(electrons.at(iE));

  //     electron.pt = inElectron.Pt();
  //     electron.eta = inElectron.Eta();
  //     electron.phi = inElectron.Phi();
  //   }
  // }

  if (fMuonsName.Length() != 0) {
    auto* inMuons = GetObject<mithep::MuonCol>(fMuonsName);
    auto& muons(fEvent.muons);
    muons.resize(inMuons->GetEntries());
    for (unsigned iM = 0; iM != inMuons->GetEntries(); ++iM) {
      auto& inMuon(*inMuons->At(iM));
      auto& muon(muons.at(iM));

      muon.pt = inMuon.Pt();
      muon.eta = inMuon.Eta();
      muon.phi = inMuon.Phi();
    }
  }

  // if (fTausName.Length() != 0) {
  //   auto* inTaus = GetObject<mithep::PFTauCol>(fTausName);
  //   auto& taus(fEvent.taus);
  //   taus.resize(inTaus->GetEntries());
  //   for (unsigned iT = 0; iT != inTaus->GetEntries(); ++iT) {
  //     auto& inTau(*inTaus->At(iT));
  //     auto& tau(taus.at(iT));

  //     tau.pt = inTau.Pt();
  //     tau.eta = inTau.Eta();
  //     tau.phi = inTau.Phi();
  //   }
  // }

  if (fPhotonsName.Length() != 0) {
    auto* inPhotons = GetObject<mithep::PhotonCol>(fPhotonsName);
    auto& photons(fEvent.photons);
    photons.resize(inPhotons->GetEntries());
    for (unsigned iP = 0; iP != inPhotons->GetEntries(); ++iP) {
      auto& inPhoton(*inPhotons->At(iP));
      auto& photon(photons.at(iP));

      photon.pt = inPhoton.Pt();
      photon.eta = inPhoton.Eta();
      photon.phi = inPhoton.Phi();
    }
  }

  auto* triggerBits = GetObject<mithep::TriggerMask>(Names::gkHltBitBrn);
  fEvent.trigger.met90mht90 = triggerBits->At(trigIds[0]);
  fEvent.trigger.met120mht120 = triggerBits->At(trigIds[1]);

  auto* triggerObjects = GetObject<mithep::TriggerObjectCol>(fTriggerObjectsName);

  fEvent.eg135s.resize(0);
  fEvent.eg120s.resize(0);
  fEvent.eg165s.resize(0);

  for (unsigned iO(0); iO != triggerObjects->GetEntries(); ++iO) {
    TriggerObject const& to(*triggerObjects->At(iO));

    if (std::strcmp(to.ModuleName(), "hltEG135HEFilter") == 0) {
      fEvent.eg135s.resize(fEvent.eg135s.size + 1);
      auto& obj(fEvent.eg135s.at(fEvent.eg135s.size - 1));
      obj.pt = to.Pt();
      obj.eta = to.Eta();
      obj.phi = to.Phi();
    }

    if (std::strcmp(to.ModuleName(), "hltEG120R9Id90HE10IsoMTrackIsoFilter") == 0) {
      fEvent.eg120s.resize(fEvent.eg120s.size + 1);
      auto& obj(fEvent.eg120s.at(fEvent.eg120s.size - 1));
      obj.pt = to.Pt();
      obj.eta = to.Eta();
      obj.phi = to.Phi();
    }

    if (std::strcmp(to.ModuleName(), "hlt165HE10Filter") == 0) {
      fEvent.eg165s.resize(fEvent.eg165s.size + 1);
      auto& obj(fEvent.eg165s.at(fEvent.eg165s.size - 1));
      obj.pt = to.Pt();
      obj.eta = to.Eta();
      obj.phi = to.Phi();
    }
  }

  fTree->Fill();
}

void
mithep::MonoJetTree::SlaveBegin()
{
  fTree = new TTree(fTreeName, "Flat format event");
  fEvent.book(*fTree);

  AddOutput(fTree);
}

void
mithep::MonoJetTree::BeginRun()
{
  auto* triggerTable = GetHLTTable();

  auto* met90mht90 = triggerTable->GetWildcard("HLT_PFMETNoMu90_NoiseCleaned_PFMHTNoMu90_IDTight_v");
  auto* met120mht120 = triggerTable->GetWildcard("HLT_PFMETNoMu120_NoiseCleaned_PFMHTNoMu120_IDTight_v");
  trigIds[0] = met90mht90->Id();
  trigIds[1] = met120mht120->Id();
}
