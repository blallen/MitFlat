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
  auto& ebHits(getProduct_(_inEvent, ebHitsToken_, "ebHits"));
  auto& eeHits(getProduct_(_inEvent, eeHitsToken_, "eeHits"));

  auto findHit([&ebHits, &eeHits](DetId const& id)->EcalRecHit const* {
      EcalRecHitCollection const* hits(0);
      if (id.subdetId() == EcalBarrel)
        hits = &ebHits;
      else
        hits = &eeHits;

      auto&& hitItr(hits->find(id));
      if (hitItr == hits->end())
        return 0;

      return &*hitItr;
    });

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

      outSC.sieie = std::sqrt(localCov[0]);
      outSC.sipip = std::sqrt(localCov[2]);
      outSC.e2e9 = (lazyTools.eMax(seed) + lazyTools.e2nd(seed)) / lazyTools.e3x3(seed);

      outSC.emax = lazyTools.eMax(seed);
      outSC.e2nd = lazyTools.e2nd(seed);
      outSC.e4 = lazyTools.eTop(seed) + lazyTools.eRight(seed) + lazyTools.eBottom(seed) + lazyTools.eLeft(seed);

      auto* seedHit(findHit(seed.hitsAndFractions()[0].first));
      if (seedHit)
        outSC.time = seedHit->time();
    }

    outSC.timeSpan = 0.;    
    for (auto& hf : inSC.hitsAndFractions()) {
      auto* hit(findHit(hf.first));
      if (!hit || hit->energy() < 1.)
        continue;

      double dt(outSC.time - hit->time());
      if (std::abs(dt) > std::abs(outSC.timeSpan))
        outSC.timeSpan = dt;
    }
  }
}
