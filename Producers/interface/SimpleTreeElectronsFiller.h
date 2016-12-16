#ifndef MitFlat_Producers_SimpleTreeElectronsFiller_h
#define MitFlat_Producers_SimpleTreeElectronsFiller_h

#include "SimpleTreeFiller.h"

#include "DataFormats/Common/interface/View.h"
#include "DataFormats/Common/interface/ValueMap.h"
#include "DataFormats/EgammaCandidates/interface/PhotonFwd.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectronFwd.h"
#include "DataFormats/PatCandidates/interface/TriggerObjectStandAlone.h"

#include "RecoEgamma/EgammaTools/interface/EffectiveAreas.h"

class SimpleTreeElectronsFiller : public SimpleTreeFiller {
 public:
  SimpleTreeElectronsFiller(edm::ParameterSet const&, edm::ConsumesCollector&);
  ~SimpleTreeElectronsFiller() {}

  void addBranch(flatutils::BranchList& _list) override { _list.emplace_back("electrons"); }
  void fill(simpletree::Event&, edm::Event const&, edm::EventSetup const&) override;

 private:
  typedef edm::View<reco::Photon> PhotonView;
  typedef edm::View<reco::GsfElectron> GsfElectronView;
  typedef edm::ValueMap<bool> BoolMap;
  typedef edm::ValueMap<float> FloatMap;

  edm::EDGetTokenT<GsfElectronView> electronsToken_;
  edm::EDGetTokenT<PhotonView> photonsToken_;
  edm::EDGetTokenT<BoolMap> vetoIdToken_;
  edm::EDGetTokenT<BoolMap> looseIdToken_;
  edm::EDGetTokenT<BoolMap> mediumIdToken_;
  edm::EDGetTokenT<BoolMap> tightIdToken_;
  edm::EDGetTokenT<FloatMap> phCHIsoToken_;
  edm::EDGetTokenT<FloatMap> phNHIsoToken_;
  edm::EDGetTokenT<FloatMap> phPhIsoToken_;
  edm::EDGetTokenT<double> rhoToken_;
  edm::EDGetTokenT<pat::TriggerObjectStandAloneCollection> triggerObjectsToken_;

  EffectiveAreas combIsoEA_;
  EffectiveAreas phCHIsoEA_;
  EffectiveAreas phNHIsoEA_;
  EffectiveAreas phPhIsoEA_;

  bool useTrigger_;
  VString hltFilters_;
};

#endif
