#include "../interface/SimpleTreeElectronsFiller.h"

#include "FWCore/Common/interface/TriggerNames.h"
#include "RecoEcal/EgammaCoreTools/interface/EcalClusterLazyTools.h"
#include "DataFormats/EcalDetId/interface/EcalSubdetector.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectron.h"
#include "DataFormats/EgammaCandidates/interface/Photon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/Math/interface/deltaR.h"

#include <cmath>

SimpleTreeElectronsFiller::SimpleTreeElectronsFiller(edm::ParameterSet const& _cfg, edm::ConsumesCollector& _coll) :
  SimpleTreeFiller("ElectronsFiller"),
  combIsoEA_(_cfg.getUntrackedParameter<edm::FileInPath>("electronCombIsoEA").fullPath()),
  // ecalIsoEA_(_cfg.getUntrackedParameter<edm::FileInPath>("electronEcalIsoEA").fullPath()), // in ikrav/cmssw:egm_id_80X-v1
  // hcalIsoEA_(_cfg.getUntrackedParameter<edm::FileInPath>("electronHcalIsoEA").fullPath()),
  phCHIsoEA_(_cfg.getUntrackedParameter<edm::FileInPath>("photonCHIsoEA").fullPath()),
  phNHIsoEA_(_cfg.getUntrackedParameter<edm::FileInPath>("photonNHIsoEA").fullPath()),
  phPhIsoEA_(_cfg.getUntrackedParameter<edm::FileInPath>("photonPhIsoEA").fullPath()),
  useTrigger_(_cfg.getUntrackedParameter<bool>("useTrigger"))
{
  getToken_(electronsToken_, _cfg, _coll, "electrons");
  getToken_(photonsToken_, _cfg, _coll, "photons");
  getToken_(vetoIdToken_, _cfg, _coll, "electronVetoId");
  getToken_(looseIdToken_, _cfg, _coll, "electronLooseId");
  getToken_(mediumIdToken_, _cfg, _coll, "electronMediumId");
  getToken_(tightIdToken_, _cfg, _coll, "electronTightId");
  getToken_(phCHIsoToken_, _cfg, _coll, "photonCHIso");
  getToken_(phNHIsoToken_, _cfg, _coll, "photonNHIso");
  getToken_(phPhIsoToken_, _cfg, _coll, "photonPhIso");
  getToken_(rhoToken_, _cfg, _coll, "rho");
  if (useTrigger_) {
    getToken_(triggerObjectsToken_, _cfg, _coll, "triggerObjects");
    hltFilters_ = _cfg.getUntrackedParameter<VString>("electronHLTFilters");
    if (hltFilters_.size() != simpletree::nElectronHLTObjects)
      throw edm::Exception(edm::errors::Configuration, "SimpleTreeElectronsFiller")
        << "electronHLTFilters.size()";
  }
}

void
SimpleTreeElectronsFiller::fill(simpletree::Event& _outEvent, edm::Event const& _inEvent, edm::EventSetup const& _setup)
{
  auto& inElectrons(getProduct_(_inEvent, electronsToken_, "electrons"));
  auto& photons(getProduct_(_inEvent, photonsToken_, "photons"));
  auto& vetoId(getProduct_(_inEvent, vetoIdToken_, "vetoId"));
  auto& looseId(getProduct_(_inEvent, looseIdToken_, "looseId"));
  auto& mediumId(getProduct_(_inEvent, mediumIdToken_, "mediumId"));
  auto& tightId(getProduct_(_inEvent, tightIdToken_, "tightId"));
  auto& phCHIso(getProduct_(_inEvent, phCHIsoToken_, "chIso"));
  auto& phNHIso(getProduct_(_inEvent, phNHIsoToken_, "nhIso"));
  auto& phPhIso(getProduct_(_inEvent, phPhIsoToken_, "phIso"));
  double rho(getProduct_(_inEvent, rhoToken_, "rho"));

  std::vector<pat::TriggerObjectStandAlone const*> hltObjects[simpletree::nElectronHLTObjects];
  if (useTrigger_) {
    auto& triggerObjects(getProduct_(_inEvent, triggerObjectsToken_, "triggerObjects"));
    for (auto& obj : triggerObjects) {
      for (unsigned iF(0); iF != simpletree::nElectronHLTObjects; ++iF) {
        if (obj.hasFilterLabel(hltFilters_[iF]))
          hltObjects[iF].push_back(&obj);
      }
    }
  }

  auto& outElectrons(_outEvent.electrons);

  unsigned iEl(-1);
  for (auto& inElectron : inElectrons) {
    ++iEl;
    if (inElectron.pt() < 10.)
      continue;
    if (std::abs(inElectron.eta()) > 2.5)
      continue;

    auto&& inRef(inElectrons.refAt(iEl));

    auto&& scRef(inElectron.superCluster());
    auto& sc(*scRef);

    auto& outElectron(outElectrons.create_back());

    fillP4(outElectron, inElectron);

    double scEta(std::abs(sc.eta()));
    outElectron.isEB = scEta < 1.4442;

    outElectron.sieie = inElectron.full5x5_sigmaIetaIeta();
    outElectron.sipip = inElectron.full5x5_sigmaIphiIphi();
    outElectron.sieip = inElectron.full5x5_showerShape().sigmaIetaIphi;
    outElectron.hOverE = inElectron.hadronicOverEm();

    auto& pfIso(inElectron.pfIsolationVariables());
    outElectron.combRelIso = (pfIso.sumChargedHadronPt + std::max(0., pfIso.sumNeutralHadronEt + pfIso.sumPhotonEt - combIsoEA_.getEffectiveArea(scEta) * rho)) / outElectron.pt;
    // TODO
    outElectron.ecalIso = 0.;
    outElectron.hcalIso = 0.;

    unsigned iPh(0);
    for (auto& photon : photons) {
      if (photon.superCluster() == scRef) {
        auto&& photonRef(photons.refAt(iPh));
        outElectron.chIsoPh = phCHIso[photonRef] - phCHIsoEA_.getEffectiveArea(scEta) * rho;
        outElectron.nhIsoPh = phNHIso[photonRef] - phNHIsoEA_.getEffectiveArea(scEta) * rho;
        outElectron.phIsoPh = phPhIso[photonRef] - phPhIsoEA_.getEffectiveArea(scEta) * rho;
      }
    }

    outElectron.veto = vetoId[inRef];
    outElectron.loose = looseId[inRef];
    outElectron.medium = mediumId[inRef];
    outElectron.tight = tightId[inRef];

    if (useTrigger_) {
      for (unsigned iF(0); iF != simpletree::nElectronHLTObjects; ++iF) {
        for (auto* obj : hltObjects[iF]) {
          if (reco::deltaR(inElectron, *obj) < 0.3) {
            outElectron.matchHLT[iF] = true;
            break;
          }
        }
      }
    }

    outElectron.matchedGen = 0;

    if (!_inEvent.isRealData()) {
      // TODO
    }
  }
}
