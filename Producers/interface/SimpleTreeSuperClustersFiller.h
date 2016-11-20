#ifndef MitFlat_Producers_SimpleTreeSuperClustersFiller_h
#define MitFlat_Producers_SimpleTreeSuperClustersFiller_h

#include "SimpleTreeFiller.h"

#include "DataFormats/Common/interface/View.h"
#include "DataFormats/Common/interface/ValueMap.h"
#include "DataFormats/EcalRecHit/interface/EcalRecHitCollections.h"
#include "DataFormats/EgammaReco/interface/SuperClusterFwd.h"

class SimpleTreeSuperClustersFiller : public SimpleTreeFiller {
 public:
  SimpleTreeSuperClustersFiller(edm::ParameterSet const&, edm::ConsumesCollector&);
  ~SimpleTreeSuperClustersFiller() {}

  void fill(simpletree::Event&, edm::Event const&, edm::EventSetup const&) override;

 private:
  edm::EDGetTokenT<reco::SuperClusterCollection> superClustersToken_;
  edm::EDGetTokenT<EcalRecHitCollection> ebHitsToken_;
  edm::EDGetTokenT<EcalRecHitCollection> eeHitsToken_;
};

#endif
