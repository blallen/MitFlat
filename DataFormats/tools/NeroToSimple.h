#include "TreeEntries_simpletree.h"

#include "BareEvent.hpp"
#include "BareJets.hpp"
#include "BareMet.hpp"
#include "BarePhotons.hpp"
#include "BareLeptons.hpp"
#include "BareTaus.hpp"
#include "BareMonteCarlo.hpp"
#include "BareTrigger.hpp"
#include "BareVertex.hpp"

#include "TFile.h"
#include "TTree.h"
#include "TString.h"

#include <stdexcept>

class NeroToSimple {
 public:
  NeroToSimple(TTree& neroTree, simpletree::Event&);

  void setTriggerNames(TString const&);

  void translate(long iEntry = -1);

 private:
  bool triggerMatch(std::vector<int> const& inBits, unsigned objIdx, unsigned trigIdx);

  TTree& input_;
  
  BareEvent inEvent_;
  BareJets inJets_;
  BareMet inMet_;
  BarePhotons inPhotons_;
  BareLeptons inLeptons_;
  BareTaus inTaus_;
  BareMonteCarlo inMC_;
  BareTrigger inTrigger_;
  BareVertex inVertex_;
  
  unsigned triggerIndices_[simpletree::nHLTPaths];

  simpletree::Event& event_;
};

void
p4ToParticle(BareP4 const& _in, unsigned _idx, simpletree::Particle& _out)
{
  auto& inP(_in.momentum(_idx));
  _out.pt = inP.Pt();
  _out.eta = inP.Eta();
  _out.phi = inP.Phi();
}

void
p4ToParticle(BareP4 const& _in, unsigned _idx, simpletree::ParticleM& _out)
{
  p4ToParticle(_in, _idx, static_cast<simpletree::Particle&>(_out));
  _out.mass = _in.momentum(_idx).M();
}

inline
NeroToSimple::NeroToSimple(TTree& _neroTree, simpletree::Event& _outEvent) :
 input_(_neroTree),
 event_(_outEvent)             
{
  inEvent_.setBranchAddresses(&input_);
  inJets_.setBranchAddresses(&input_);
  inMet_.setBranchAddresses(&input_);
  inPhotons_.setBranchAddresses(&input_);
  inLeptons_.setBranchAddresses(&input_);
  inTaus_.setBranchAddresses(&input_);
  inMC_.setBranchAddresses(&input_);
  inTrigger_.setBranchAddresses(&input_);
  inVertex_.setBranchAddresses(&input_);

  for (unsigned& idx : triggerIndices_)
    idx = -1;
}

inline
void
NeroToSimple::setTriggerNames(TString const& _triggerNames)
{
  TString matchNames[simpletree::nHLTPaths] = {
    "Photon120",
    "Photon135_PFMET100_JetIdCleaned",
    "Photon165_HE10",
    "Photon175",
    "Ele23_WPLoose_Gsf",
    "Ele27_eta2p1_WPLoose_Gsf",
    "IsoMu20",
    "IsoTkMu20",
    "IsoMu24_eta2p1",
    "IsoMu27",
    "PFMET170_NoiseCleaned",
    "PFMETNoMu90_JetIdCleaned_PFMHTNoMu90_IDTight",
    "PFMETNoMu120_JetIdCleaned_PFMHTNoMu120_IDTight"
  };

  auto* names(_triggerNames.Tokenize(","));
  for (int iT(0); iT != names->GetEntries(); ++iT) {
    TString name(names->GetName());
    for (unsigned iM(0); iM != simpletree::nHLTPaths; ++iM) {
      if (name.Index("HLT_" + matchNames[iM]) == 0)
        triggerIndices_[iM] = iT;
    }      
  }
  delete names;
}

inline
void
NeroToSimple::translate(long _iEntry/* = -1*/)
{
  if (_iEntry >= 0)
    input_.GetEntry(_iEntry);

  event_.run = inEvent_.runNum;
  event_.lumi = inEvent_.lumiNum;
  event_.event = inEvent_.eventNum;
  event_.weight = inEvent_.isRealData ? 1. : inMC_.mcWeight;
  event_.rho = inEvent_.rho;
  event_.npv = inVertex_.npv;

  event_.jets.resize(inJets_.size());
  for (unsigned iJ(0); iJ != inJets_.size(); ++iJ)
    p4ToParticle(inJets_, iJ, event_.jets[iJ]);

  event_.photons.resize(inPhotons_.size());
  for (unsigned iP(0); iP != inPhotons_.size(); ++iP) {
    auto& photon(event_.photons[iP]);

    p4ToParticle(inPhotons_, iP, photon);

    photon.csafeVeto = (inPhotons_.selBits->at(iP) & BarePhotons::PhoElectronVeto) != 0;
    photon.pixelVeto = (inPhotons_.selBits->at(iP) & BarePhotons::PhoPixelSeedVeto) != 0;
    photon.loose = (inPhotons_.selBits->at(iP) & BarePhotons::PhoLoose) != 0;
    photon.medium = (inPhotons_.selBits->at(iP) & BarePhotons::PhoMedium) != 0;
    photon.tight = (inPhotons_.selBits->at(iP) & BarePhotons::PhoTight) != 0;

    photon.chIso = inPhotons_.chIso->at(iP);
    photon.nhIso = inPhotons_.nhIso->at(iP);
    photon.phIso = inPhotons_.phoIso->at(iP);
    photon.sieie = inPhotons_.sieie->at(iP);
    photon.hOverE = inPhotons_.hOverE->at(iP);

    photon.sipip = inPhotons_.sipip->at(iP);
    photon.sieip = inPhotons_.sieip->at(iP);
    photon.r9 = inPhotons_.r9->at(iP);
    // photon.s4 = inPhotons_.s4->at(iP);

    photon.mipEnergy = inPhotons_.mipEnergy->at(iP);
    photon.e55 = inPhotons_.e55->at(iP);

    photon.matchHLT[simpletree::fPh120] = triggerMatch(*inTrigger_.triggerPhotons, iP, simpletree::kPhoton120);
    photon.matchHLT[simpletree::fPh135] = triggerMatch(*inTrigger_.triggerPhotons, iP, simpletree::kPhoton135MET100);
    photon.matchHLT[simpletree::fPh165HE10] = triggerMatch(*inTrigger_.triggerPhotons, iP, simpletree::kPhoton165HE10);
    photon.matchHLT[simpletree::fPh175] = triggerMatch(*inTrigger_.triggerPhotons, iP, simpletree::kPhoton175);
  }

  event_.electrons.clear();
  event_.muons.clear();
  for (unsigned iL(0); iL != inLeptons_.size(); ++iL) {
    simpletree::Lepton* lepton(0);

    if (std::abs(inLeptons_.pdgId->at(iL)) == 11) {
      event_.electrons.resize(event_.electrons.size() + 1);
      auto& electron(event_.electrons.back());
      lepton = &electron;

      electron.matchHLT[simpletree::fEl23Loose] = triggerMatch(*inTrigger_.triggerLeps, iL, simpletree::kEle23Loose);
      electron.matchHLT[simpletree::fEl27Loose] = triggerMatch(*inTrigger_.triggerLeps, iL, simpletree::kEle27Loose);
    }
    else {
      event_.muons.resize(event_.muons.size() + 1);
      auto& muon(event_.muons.back());
      lepton = &muon;

      muon.matchHLT[simpletree::fMu20] = triggerMatch(*inTrigger_.triggerLeps, iL, simpletree::kMu20);
      muon.matchHLT[simpletree::fMuTrk20] = triggerMatch(*inTrigger_.triggerLeps, iL, simpletree::kTrkMu20);
      muon.matchHLT[simpletree::fMu24] = triggerMatch(*inTrigger_.triggerLeps, iL, simpletree::kMu24eta2p1);
      muon.matchHLT[simpletree::fMu27] = triggerMatch(*inTrigger_.triggerLeps, iL, simpletree::kMu27);
    }

    p4ToParticle(inLeptons_, iL, *lepton);
    lepton->positive = inLeptons_.pdgId->at(iL) < 0; // -11/-13 -> anti-particle = positive
    lepton->loose = (inLeptons_.selBits->at(iL) & BareLeptons::LepLoose) != 0;
    lepton->tight = (inLeptons_.selBits->at(iL) & BareLeptons::LepTight) != 0;
  }

  event_.taus.resize(inTaus_.size());
  for (unsigned iT(0); iT != inTaus_.size(); ++iT) {
    auto& tau(event_.taus[iT]);

    p4ToParticle(inTaus_, iT, tau);
    tau.combIso = inTaus_.iso->at(iT);
    tau.decayMode = (inTaus_.selBits->at(iT) & BareTaus::TauDecayModeFinding) != 0;
  }

  event_.rawMet.sumEt = inMet_.sumEtRaw;
  event_.t1Met.met = inMet_.momentum(0).Pt();
  event_.t1Met.phi = inMet_.momentum(0).Phi();

  for (unsigned iT(0); iT != simpletree::nHLTPaths; ++iT) {
    if (triggerIndices_[iT] >= inTrigger_.triggerNames->size())
      continue;

    event_.hlt[iT].pass = inTrigger_.triggerFired->at(triggerIndices_[iT]) != 0;
  }

  if (!inEvent_.isRealData) {
    event_.genJets.resize(inMC_.jetP4->GetEntries());
    for (int iJ(0); iJ != inMC_.jetP4->GetEntries(); ++iJ) {
      auto& inP4(*static_cast<TLorentzVector*>(inMC_.jetP4->At(iJ)));
      auto& genJet(event_.genJets[iJ]);
      genJet.pt = inP4.Pt();
      genJet.eta = inP4.Eta();
      genJet.phi = inP4.Phi();
      genJet.mass = inP4.M();
    }

    auto& inGenMet(*static_cast<TLorentzVector*>(inMet_.genP4->At(0)));
    event_.genMet.met = inGenMet.Pt();
    event_.genMet.phi = inGenMet.Phi();

    event_.reweight.resize(6 + inMC_.pdfRwgt->size());

    event_.reweight[0].scale = inMC_.r1f2;
    event_.reweight[1].scale = inMC_.r1f5;
    event_.reweight[2].scale = inMC_.r2f1;
    event_.reweight[3].scale = inMC_.r2f2;
    event_.reweight[4].scale = inMC_.r5f1;
    event_.reweight[5].scale = inMC_.r5f5;

    unsigned iW(6);
    for (float w : *inMC_.pdfRwgt)
      event_.reweight[iW++].scale = w;
  }
}

bool
NeroToSimple::triggerMatch(std::vector<int> const& _inBits, unsigned _objIdx, unsigned _trigIdx)
{
  return triggerIndices_[_trigIdx] < 32 && (_inBits.at(_objIdx) & (0x1 << triggerIndices_[_trigIdx])) != 0;
}
