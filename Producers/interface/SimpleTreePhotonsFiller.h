#ifndef MitFlat_Producers_SimpleTreePhotonsFiller_h
#define MitFlat_Producers_SimpleTreePhotonsFiller_h

#include "SimpleTreeFiller.h"

#include "DataFormats/Common/interface/View.h"
#include "DataFormats/Common/interface/ValueMap.h"
#include "DataFormats/EgammaCandidates/interface/PhotonFwd.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectronFwd.h"
#include "DataFormats/EcalRecHit/interface/EcalRecHitCollections.h"
#include "DataFormats/PatCandidates/interface/TriggerObjectStandAlone.h"

#include "RecoEgamma/EgammaTools/interface/EffectiveAreas.h"

class SimpleTreePhotonsFiller : public SimpleTreeFiller {
 public:
  SimpleTreePhotonsFiller(edm::ParameterSet const&, edm::ConsumesCollector&);
  ~SimpleTreePhotonsFiller() {}

  void addBranch(flatutils::BranchList& _list) override { _list.emplace_back("photons"); }
  void fill(simpletree::Event&, edm::Event const&, edm::EventSetup const&) override;

 private:
  typedef edm::View<reco::Photon> PhotonView;
  typedef edm::View<reco::GsfElectron> GsfElectronView;
  typedef edm::ValueMap<bool> BoolMap;
  typedef edm::ValueMap<float> FloatMap;

  edm::EDGetTokenT<PhotonView> photonsToken_;
  edm::EDGetTokenT<EcalRecHitCollection> ebHitsToken_;
  edm::EDGetTokenT<EcalRecHitCollection> eeHitsToken_;
  edm::EDGetTokenT<GsfElectronView> electronsToken_;
  edm::EDGetTokenT<BoolMap> looseIdToken_;
  edm::EDGetTokenT<BoolMap> mediumIdToken_;
  edm::EDGetTokenT<BoolMap> tightIdToken_;
  edm::EDGetTokenT<FloatMap> chIsoToken_;
  edm::EDGetTokenT<FloatMap> nhIsoToken_;
  edm::EDGetTokenT<FloatMap> phIsoToken_;
  edm::EDGetTokenT<FloatMap> wchIsoToken_;
  edm::EDGetTokenT<double> rhoToken_;
  edm::EDGetTokenT<pat::TriggerObjectStandAloneCollection> triggerObjectsToken_;

  EffectiveAreas chIsoEA_;
  EffectiveAreas nhIsoEA_;
  EffectiveAreas phIsoEA_;

  bool useTrigger_;
  VString l1Filters_;
  VString hltFilters_;
};

#endif
