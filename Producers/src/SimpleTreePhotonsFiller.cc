#include "../interface/SimpleTreePhotonsFiller.h"

#include "FWCore/Common/interface/TriggerNames.h"
#include "RecoEcal/EgammaCoreTools/interface/EcalClusterLazyTools.h"
#include "DataFormats/EcalDetId/interface/EcalSubdetector.h"
#include "DataFormats/EgammaCandidates/interface/Photon.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectron.h"
#include "DataFormats/PatCandidates/interface/Photon.h"
#include "DataFormats/Math/interface/deltaR.h"

#include <cmath>

SimpleTreePhotonsFiller::SimpleTreePhotonsFiller(edm::ParameterSet const& _cfg, edm::ConsumesCollector& _coll) :
  SimpleTreeFiller("PhotonsFiller"),
  chIsoEA_(_cfg.getUntrackedParameter<edm::FileInPath>("photonCHIsoEA").fullPath()),
  nhIsoEA_(_cfg.getUntrackedParameter<edm::FileInPath>("photonNHIsoEA").fullPath()),
  phIsoEA_(_cfg.getUntrackedParameter<edm::FileInPath>("photonPhIsoEA").fullPath()),
  useTrigger_(_cfg.getUntrackedParameter<bool>("useTrigger"))
{
  getToken_(photonsToken_, _cfg, _coll, "photons");
  getToken_(ebHitsToken_, _cfg, _coll, "ebHits");
  getToken_(eeHitsToken_, _cfg, _coll, "eeHits");
  getToken_(electronsToken_, _cfg, _coll, "electrons");
  getToken_(looseIdToken_, _cfg, _coll, "photonLooseId");
  getToken_(mediumIdToken_, _cfg, _coll, "photonMediumId");
  getToken_(tightIdToken_, _cfg, _coll, "photonTightId");
  getToken_(chIsoToken_, _cfg, _coll, "photonCHIso");
  getToken_(nhIsoToken_, _cfg, _coll, "photonNHIso");
  getToken_(phIsoToken_, _cfg, _coll, "photonPhIso");
  getToken_(wchIsoToken_, _cfg, _coll, "photonWCHIso");
  getToken_(rhoToken_, _cfg, _coll, "rho");
  if (useTrigger_) {
    getToken_(triggerObjectsToken_, _cfg, _coll, "triggerObjects");
    l1Filters_ = _cfg.getUntrackedParameter<VString>("photonL1Filters");
    hltFilters_ = _cfg.getUntrackedParameter<VString>("photonHLTFilters");
    if (l1Filters_.size() != simpletree::nPhotonL1Objects)
      throw edm::Exception(edm::errors::Configuration, "SimpleTreePhotonsFiller")
        << "photonL1Filters.size()";
    if (hltFilters_.size() != simpletree::nPhotonHLTObjects)
      throw edm::Exception(edm::errors::Configuration, "SimpleTreePhotonsFiller")
        << "photonHLTFilters.size()";
  }
}

void
SimpleTreePhotonsFiller::fill(simpletree::Event& _outEvent, edm::Event const& _inEvent, edm::EventSetup const& _setup)
{
  auto& inPhotons(getProduct_(_inEvent, photonsToken_, "photons"));
  auto& ebHits(getProduct_(_inEvent, ebHitsToken_, "ebHits"));
  auto& eeHits(getProduct_(_inEvent, eeHitsToken_, "eeHits"));
  auto& electrons(getProduct_(_inEvent, electronsToken_, "electrons"));
  auto& looseId(getProduct_(_inEvent, looseIdToken_, "photonLooseId"));
  auto& mediumId(getProduct_(_inEvent, mediumIdToken_, "photonMediumId"));
  auto& tightId(getProduct_(_inEvent, tightIdToken_, "photonTightId"));
  auto& chIso(getProduct_(_inEvent, chIsoToken_, "chIso"));
  auto& nhIso(getProduct_(_inEvent, nhIsoToken_, "nhIso"));
  auto& phIso(getProduct_(_inEvent, phIsoToken_, "phIso"));
  auto& wchIso(getProduct_(_inEvent, wchIsoToken_, "wchIso"));
  double rho(getProduct_(_inEvent, rhoToken_, "rho"));

  noZS::EcalClusterLazyTools lazyTools(_inEvent, _setup, ebHitsToken_, eeHitsToken_);

  std::vector<pat::TriggerObjectStandAlone const*> l1Objects[simpletree::nPhotonL1Objects];
  std::vector<pat::TriggerObjectStandAlone const*> hltObjects[simpletree::nPhotonHLTObjects];
  if (useTrigger_) {
    auto& triggerObjects(getProduct_(_inEvent, triggerObjectsToken_, "triggerObjects"));
    for (auto& obj : triggerObjects) {
      for (unsigned iF(0); iF != simpletree::nPhotonL1Objects; ++iF) {
        if (obj.hasFilterLabel(l1Filters_[iF]))
          l1Objects[iF].push_back(&obj);
      }
      for (unsigned iF(0); iF != simpletree::nPhotonHLTObjects; ++iF) {
        if (obj.hasFilterLabel(hltFilters_[iF]))
          hltObjects[iF].push_back(&obj);
      }
    }
  }

  auto& outPhotons(_outEvent.photons);

  unsigned iPh(-1);
  for (auto& inPhoton : inPhotons) {
    ++iPh;
    if (inPhoton.pt() < 10.)
      continue;

    auto&& inRef(inPhotons.refAt(iPh));

    bool isPAT(dynamic_cast<pat::Photon const*>(&inPhoton));

    auto&& scRef(inPhoton.superCluster());
    auto& sc(*scRef);

    auto& outPhoton(outPhotons.create_back());

    fillP4(outPhoton, inPhoton);

    double scEta(std::abs(sc.eta()));

    outPhoton.scRawPt = sc.rawEnergy() / std::cosh(scEta);

    outPhoton.isEB = scEta < 1.4442;

    outPhoton.sieie = inPhoton.full5x5_sigmaIetaIeta();
    outPhoton.sipip = inPhoton.full5x5_showerShapeVariables().sigmaIphiIphi;
    outPhoton.sieip = inPhoton.full5x5_showerShapeVariables().sigmaIetaIphi;
    outPhoton.hOverE = inPhoton.hadTowOverEm();
    outPhoton.pixelVeto = !inPhoton.hasPixelSeed();

    outPhoton.electronVeto = true;
    // does this work with PAT electron & photons?
    for (auto& ele : electrons) {
      if (ele.superCluster() == scRef) {
        outPhoton.electronVeto = false;
        break;
      }
    }

    if (isPAT)
      outPhoton.csafeVeto = static_cast<pat::Photon const&>(inPhoton).passElectronVeto();

    outPhoton.chIso = chIso[inRef] - chIsoEA_.getEffectiveArea(scEta) * rho;
    outPhoton.nhIso = nhIso[inRef] - nhIsoEA_.getEffectiveArea(scEta) * rho;
    outPhoton.phIso = phIso[inRef] - phIsoEA_.getEffectiveArea(scEta) * rho;
    // TODO
    outPhoton.chIsoMax = 0.;
    outPhoton.ecalIso = 0.;
    outPhoton.hcalIso = 0.;
    outPhoton.chWorstIso = wchIso[inRef];
    
    outPhoton.loose = looseId[inRef];
    outPhoton.medium = mediumId[inRef];
    outPhoton.tight = tightId[inRef];
    // TODO
    outPhoton.highpt = true;

    outPhoton.mipEnergy = inPhoton.mipTotEnergy();
    outPhoton.mipChi2 = inPhoton.mipChi2();
    outPhoton.mipSlope = inPhoton.mipSlope();
    outPhoton.mipIntercept = inPhoton.mipIntercept();
    outPhoton.mipNhitCone = inPhoton.mipNhitCone();
    outPhoton.mipIsHalo = inPhoton.mipIsHalo();

    outPhoton.e15 = inPhoton.e1x5();
    outPhoton.e25 = inPhoton.e2x5();
    outPhoton.e33 = inPhoton.e3x3();
    outPhoton.e55 = inPhoton.e5x5();
    outPhoton.r9 = inPhoton.r9();

    outPhoton.scPt = sc.energy() / std::cosh(scEta);
    outPhoton.scEta = sc.eta();
    outPhoton.scPhi = sc.phi();
    outPhoton.etaWidth = sc.etaWidth();
    outPhoton.phiWidth = sc.phiWidth();
    //    outPhoton.time = timeTools.SuperClusterSeedTime(sc);

    outPhoton.timeSpan = 0.;    
    for (auto& hf : sc.hitsAndFractions()) {
      EcalRecHitCollection const* hits(0);
      if (hf.first.subdetId() == EcalBarrel)
        hits = &ebHits;
      else
        hits = &eeHits;

      auto&& hitItr(hits->find(hf.first));
      if (hitItr == hits->end())
        throw std::logic_error("Ecal rec hit not found");

      if (hitItr->energy() < 1.)
        continue;

      double dt(outPhoton.time - hitItr->time());
      if (std::abs(dt) > std::abs(outPhoton.timeSpan))
        outPhoton.timeSpan = dt;
    }

    auto&& seedRef(sc.seed());
    if (seedRef.isNonnull()) {
      auto& seed(*seedRef);
      outPhoton.e13 = lazyTools.e1x3(seed);
      outPhoton.e31 = lazyTools.e3x1(seed);
      outPhoton.e22 = lazyTools.e2x2(seed);
      outPhoton.e44 = lazyTools.e4x4(seed);
      outPhoton.emax = lazyTools.eMax(seed);
      outPhoton.e2nd = lazyTools.e2nd(seed);
      outPhoton.e4 = lazyTools.eTop(seed) + lazyTools.eRight(seed) + lazyTools.eBottom(seed) + lazyTools.eLeft(seed);
    }

    if (useTrigger_) {
      for (unsigned iF(0); iF != simpletree::nPhotonL1Objects; ++iF) {
        for (auto* obj : l1Objects[iF]) {
          if (reco::deltaR(inPhoton, *obj) < 0.3) {
            outPhoton.matchL1[iF] = true;
            break;
          }
        }
      }
      for (unsigned iF(0); iF != simpletree::nPhotonHLTObjects; ++iF) {
        for (auto* obj : hltObjects[iF]) {
          if (reco::deltaR(inPhoton, *obj) < 0.3) {
            outPhoton.matchHLT[iF] = true;
            break;
          }
        }
      }
    }

    outPhoton.genMatchDR = -1.;
    outPhoton.matchedGen = 0;
    outPhoton.genIso = 0.;

    if (!_inEvent.isRealData()) {
      // TODO
    }
  }
}
