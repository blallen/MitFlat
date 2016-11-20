#include "../interface/SimpleTreeSuperClustersFiller.h"

#include "RecoEcal/EgammaCoreTools/interface/EcalClusterLazyTools.h"
#include "DataFormats/EcalDetId/interface/EcalSubdetector.h"
#include "DataFormats/EgammaReco/interface/SuperCluster.h"

#include <cmath>

SimpleTreeSuperClustersFiller::SimpleTreeSuperClustersFiller(edm::ParameterSet const& _cfg, edm::ConsumesCollector& _coll) :
  SimpleTreeFiller("SuperClustersFiller")
{
  getToken_(superClustersToken_, _cfg, _coll, "superClusters");
  getToken_(ebHitsToken_, _cfg, _coll, "ebHits");
  getToken_(eeHitsToken_, _cfg, _coll, "eeHits");
}

void
SimpleTreeSuperClustersFiller::fill(simpletree::Event& _outEvent, edm::Event const& _inEvent, edm::EventSetup const& _setup)
{
  auto& inSuperClusters(getProduct_(_inEvent, superClustersToken_, "superClusters"));

  noZS::EcalClusterLazyTools lazyTools(_inEvent, _setup, ebHitsToken_, eeHitsToken_);

  auto& outSuperClusters(_outEvent.superClusters);

  for (auto& inSC : inSuperClusters) {
    auto& outSC(outSuperClusters.create_back());

    outSC.eta = inSC.eta();
    outSC.phi = inSC.phi();
    outSC.rawPt = inSC.rawEnergy() / std::cosh(outSC.eta);
    outSC.isEB = std::abs(outSC.eta) < 1.4442;

    auto&& seedRef(inSC.seed());
    if (seedRef.isNonnull()) {
      auto& seed(*seedRef);
      auto&& localCov(lazyTools.localCovariances(seed));

      //      outSC.time = timeTools.SuperClusterSeedTime(inSC);
      outSC.sieie = std::sqrt(localCov[0]);
      outSC.sipip = std::sqrt(localCov[2]);
      outSC.e2e9 = (lazyTools.eMax(seed) + lazyTools.e2nd(seed)) / lazyTools.e3x3(seed);
    }
  }
}
