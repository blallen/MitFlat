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
#include <limits>

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
  inEvent_.SetExtend(true);
  inJets_.SetExtend(true);
  inMet_.SetExtend(true);
  inPhotons_.SetExtend(true);
  inLeptons_.SetExtend(true);
  inTaus_.SetExtend(true);
  inMC_.SetExtend(true);
  inTrigger_.SetExtend(true);
  inVertex_.SetExtend(true);

  inPhotons_.SetMatch(true);
  
  inEvent_.setBranchAddresses(&input_);
  inJets_.setBranchAddresses(&input_);
  inMet_.setBranchAddresses(&input_);
  inPhotons_.setBranchAddresses(&input_);
  inLeptons_.setBranchAddresses(&input_);
  inTaus_.setBranchAddresses(&input_);
  inMC_.setBranchAddresses(&input_);
  inTrigger_.setBranchAddresses(&input_);
  inVertex_.setBranchAddresses(&input_);

  inEvent_.init();
  inJets_.init();
  inMet_.init();
  inPhotons_.init();
  inLeptons_.init();
  inTaus_.init();
  inMC_.init();
  inTrigger_.init();
  inVertex_.init();

}

inline
void
NeroToSimple::setTriggerNames(TString const& _triggerNames)
{
  auto* names(_triggerNames.Tokenize(","));
  // printf("Before loop: inTrigger_.size() = %u \n", inTrigger_.size());
  for (int iT(0); iT != names->GetEntries(); ++iT) {
    TString name(names->At(iT)->GetName());
    name = name.ReplaceAll("_v", "");

    simpletree::TriggerHelper::assignIndex(name, iT);
    inTrigger_.triggerNames->emplace_back(name);

  }
  // printf("After loop: inTrigger_.size() = %u \n", inTrigger_.size());
  delete names;
}

inline
void
NeroToSimple::translate(long _iEntry/* = -1*/)
{
  // printf("\n\niEntry %ld \n", _iEntry);

  if (_iEntry >= 0)
    input_.GetEntry(_iEntry);

  // printf("iEntry %ld \n", _iEntry);

  // printf("run %d \n", inEvent_.runNum);
  // printf("lumi %d \n", inEvent_.lumiNum);
  // printf("event %llu \n", inEvent_.eventNum);
  // printf("weight %f \n", inEvent_.isRealData ? 1. : inMC_.mcWeight);
  // printf("rho %f \n", inEvent_.rho);
  // printf("npv %d \n", inVertex_.npv);

  event_.run = inEvent_.runNum;
  event_.lumi = inEvent_.lumiNum;
  event_.event = inEvent_.eventNum;
  event_.weight = inEvent_.isRealData ? 1. : inMC_.mcWeight;
  event_.rho = inEvent_.rho;
  event_.npv = inVertex_.npv;
  event_.npvTrue = inMC_.puTrueInt;

  // in simpletree 1 means tagged by filter; in nero 1 means passing filter
  event_.metFilters.cschalo = (inEvent_.selBits & BareEvent::CSCTightHalo2015Filter) == 0;
  event_.metFilters.globalHalo16 = (inEvent_.selBits & BareEvent::GlobalTightHalo2016) == 0;
  event_.metFilters.hbhe = (inEvent_.selBits & BareEvent::HBHENoiseFilter) == 0;
  event_.metFilters.hbheIso = (inEvent_.selBits & BareEvent::HBHENoiseIsoFilter) == 0;
  event_.metFilters.badsc = (inEvent_.selBits & BareEvent::eeBadScFilter) == 0;
  event_.metFilters.badTrack = 0;
  event_.metFilters.badMuonTrack = 0;

  // printf("\nnjets %d \n", inJets_.size());
  // event_.jets.resize(inJets_.size());
  event_.jets.clear();
  for (unsigned iJ(0); iJ != inJets_.size(); ++iJ) {
    // printf(" adding jet %u \n", iJ);
    event_.jets.resize(event_.jets.size() + 1);
    auto& jet(event_.jets.back());
    p4ToParticle(inJets_, iJ, jet);
  }

  // printf("\nnpho %d \n", inPhotons_.size());
  // event_.photons.resize(inPhotons_.size());
  event_.photons.clear();
  for (unsigned iP(0); iP != inPhotons_.size(); ++iP) {
    // printf(" adding pho %u \n", iP);
    event_.photons.resize(event_.photons.size() + 1);
    auto& photon(event_.photons.back());
    // auto& photon(event_.photons[iP]);

    double etaSC(std::abs(inPhotons_.etaSC->at(iP)));

    p4ToParticle(inPhotons_, iP, photon);
    photon.scRawPt = (inPhotons_.rawScEnergy->at(iP) / TMath::CosH(etaSC));
    
    // printf("  pho eta %f \n", photon.eta);
    
    photon.isEB = (TMath::Abs(photon.eta) < 1.5) ? 1 : 0;

    // printf("  pho isEB %u \n", photon.isEB);

    photon.csafeVeto = (inPhotons_.selBits->at(iP) & BarePhotons::PhoElectronVeto) != 0;
    photon.pixelVeto = (inPhotons_.selBits->at(iP) & BarePhotons::PhoPixelSeedVeto) != 0;
    photon.loose = (inPhotons_.selBits->at(iP) & BarePhotons::PhoLoose) != 0;
    photon.medium = (inPhotons_.selBits->at(iP) & BarePhotons::PhoMedium) != 0;
    photon.tight = (inPhotons_.selBits->at(iP) & BarePhotons::PhoTight) != 0;
    
    // printf("  got through ID bits \n");

    // printf("  chiso %f \n", inPhotons_.chIso->at(iP));
    // printf("  nhiso %f \n", inPhotons_.nhIso->at(iP));
    // printf("  phiso %f \n", inPhotons_.phoIso->at(iP));
    // printf("  sieie %f \n", inPhotons_.sieie->at(iP));
    // printf("  hOverE %f \n", inPhotons_.hOverE->at(iP));

    // Spring15 EA
    double eaNH[] = {0.0599, 0.0819, 0.0696, 0.0360, 0.0360, 0.0462, 0.0656};
    double eaPh[] = {0.1271, 0.1101, 0.0756, 0.1175, 0.1498, 0.1857, 0.2183};
    double etaBounds[] = {1., 1.479, 2., 2.2, 2.3, 2.4, std::numeric_limits<double>::max()};
    unsigned iEtaBin(0);
    while (etaSC > etaBounds[iEtaBin])
      ++iEtaBin;

    photon.chIso = inPhotons_.chIso->at(iP);
    photon.nhIso = std::max(0., inPhotons_.nhIso->at(iP) - 0.014 * photon.pt - 0.000019 * photon.pt * photon.pt - eaNH[iEtaBin] * event_.rho);
    photon.phIso = std::max(0., inPhotons_.phoIso->at(iP) - 0.0053 * photon.pt - eaPh[iEtaBin] * event_.rho);
    photon.sieie = inPhotons_.sieie->at(iP);
    photon.hOverE = inPhotons_.hOverE->at(iP);

    // printf("  got through ID variables \n");

    photon.chWorstIso = inPhotons_.chWorstIso->at(iP);
    if (etaSC < 1.)
      photon.chWorstIso -= 0.078 * event_.rho;
    else
      photon.chWorstIso -= 0.089 * event_.rho;
    if (photon.chWorstIso < 0.)
      photon.chWorstIso = 0.;

    // printf("  sipip %f \n", inPhotons_.sipip->at(iP));
    // printf("  sieip %f \n", inPhotons_.sieip->at(iP));
    // printf("  r9 %f \n", inPhotons_.r9->at(iP));

    photon.sipip = inPhotons_.sipip->at(iP);
    photon.sieip = inPhotons_.sieip->at(iP);
    photon.r9 = inPhotons_.r9->at(iP);

    photon.emax = inPhotons_.emax->at(iP);
    photon.e2nd = inPhotons_.e2nd->at(iP);
    photon.e33 = inPhotons_.e33->at(iP);
    photon.e55 = inPhotons_.e55->at(iP);

    photon.mipEnergy = inPhotons_.mipEnergy->at(iP);
    
    photon.time = inPhotons_.time->at(iP); // fails on Zeynep's ntuples

    if (inPhotons_.match->at(iP) == 1) {
      photon.matchedGen = -22;
    }

    // printf("  got through extra variables \n");

    // photon.matchHLT[simpletree::fPh120] = triggerMatch(*inTrigger_.triggerPhotons, iP, simpletree::kPhoton120);
    // photon.matchHLT[simpletree::fPh135] = triggerMatch(*inTrigger_.triggerPhotons, iP, simpletree::kPhoton135MET100);
    // photon.matchHLT[simpletree::fPh165HE10] = triggerMatch(*inTrigger_.triggerPhotons, iP, simpletree::TriggerHelp);
    // photon.matchHLT[simpletree::fPh175] = triggerMatch(*inTrigger_.triggerPhotons, iP, simpletree::kPhoton175);

    // printf("  got through triggers \n");
  }

  // printf("\nnlep %u \n", inLeptons_.size());
  event_.electrons.clear();
  event_.muons.clear();
  for (unsigned iL(0); iL != inLeptons_.size(); ++iL) {
    // printf(" adding lepton %u \n", iL);
    simpletree::Lepton* lepton(0);

    if (std::abs(inLeptons_.pdgId->at(iL)) == 11) {
      event_.electrons.resize(event_.electrons.size() + 1);
      auto& electron(event_.electrons.back());
      lepton = &electron;

      // electron.matchHLT[simpletree::fEl23Loose] = triggerMatch(*inTrigger_.triggerLeps, iL, simpletree::kEle23Loose);
      // electron.matchHLT[simpletree::fEl27Loose] = triggerMatch(*inTrigger_.triggerLeps, iL, simpletree::kEle27Loose);

      electron.tight = (inLeptons_.selBits->at(iL) & BareLeptons::LepTight) != 0;

      double combRelIso(inLeptons_.iso->at(iL) / static_cast<TLorentzVector*>(inLeptons_.p4->At(iL))->Pt());
      electron.combRelIso = combRelIso;
    }
    else {
      event_.muons.resize(event_.muons.size() + 1);
      auto& muon(event_.muons.back());
      lepton = &muon;

      // muon.matchHLT[simpletree::fMu20] = triggerMatch(*inTrigger_.triggerLeps, iL, simpletree::kMu20);
      // muon.matchHLT[simpletree::fMuTrk20] = triggerMatch(*inTrigger_.triggerLeps, iL, simpletree::kTrkMu20);
      // muon.matchHLT[simpletree::fMu24] = triggerMatch(*inTrigger_.triggerLeps, iL, simpletree::kMu24eta2p1);
      // muon.matchHLT[simpletree::fMu27] = triggerMatch(*inTrigger_.triggerLeps, iL, simpletree::kMu27);

      double combRelIso(inLeptons_.iso->at(iL) / static_cast<TLorentzVector*>(inLeptons_.p4->At(iL))->Pt());
      // at some point POG switched to 0.15, but MitPhysics uses 0.12
      muon.tight = (inLeptons_.selBits->at(iL) & BareLeptons::LepTight) != 0 && combRelIso < 0.12;
      muon.combRelIso = combRelIso;
    }

    p4ToParticle(inLeptons_, iL, *lepton);
    lepton->positive = inLeptons_.pdgId->at(iL) < 0; // -11/-13 -> anti-particle = positive
    lepton->loose = (inLeptons_.selBits->at(iL) & BareLeptons::LepLoose) != 0;
  }

  // printf("\nntau %u \n", inTaus_.size());
  // event_.taus.resize(inTaus_.size());
  event_.taus.clear();
  for (unsigned iT(0); iT != inTaus_.size(); ++iT) {
    // printf(" adding tau %u \n", iT);
    event_.taus.resize(event_.taus.size() + 1);
    auto& tau(event_.taus.back());
    // auto& tau(event_.taus[iT]);

    p4ToParticle(inTaus_, iT, tau);
    tau.combIso = inTaus_.iso->at(iT);
    tau.decayMode = (inTaus_.selBits->at(iT) & BareTaus::TauDecayModeFinding) != 0;
  }

  // printf("\nsumEt %f \n", inMet_.sumEtRaw);
  // printf("met %f \n", inMet_.momentum(0).Pt());
  // printf("metPhi %f \n", inMet_.momentum(0).Phi());

  event_.rawMet.sumEt = inMet_.sumEtRaw;
  event_.t1Met.met = inMet_.momentum(0).Pt();
  event_.t1Met.phi = inMet_.momentum(0).Phi();

  for (unsigned iWord(0); iWord != 16; ++iWord) {
    event_.hltBits.words[iWord] = 0;
  }

  // printf("\nntrig %zu \n", inTrigger_.triggerNames->size());
  for (unsigned iT(0); iT != inTrigger_.triggerNames->size(); ++iT) {
    event_.hltBits.set(iT);
    // printf("Added trigger %u \n", iT);
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

    // event_.reweight.resize(6 + inMC_.pdfRwgt->size());

    // event_.reweight[0].scale = inMC_.r1f2;
    // event_.reweight[1].scale = inMC_.r1f5;
    // event_.reweight[2].scale = inMC_.r2f1;
    // event_.reweight[3].scale = inMC_.r2f2;
    // event_.reweight[4].scale = inMC_.r5f1;
    // event_.reweight[5].scale = inMC_.r5f5;

    // unsigned iW(6);
    // for (float w : *inMC_.pdfRwgt)
      // event_.reweight[iW++].scale = w;
  }
}


bool
NeroToSimple::triggerMatch(std::vector<int> const& _inBits, unsigned _objIdx, unsigned _trigIdx)
{
  return _trigIdx < 32 && (_inBits.at(_objIdx) & (0x1 << _trigIdx)) != 0;
}

