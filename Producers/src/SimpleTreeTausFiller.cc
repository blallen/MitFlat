#include "../interface/SimpleTreeTausFiller.h"

#include "DataFormats/PatCandidates/interface/Tau.h"

SimpleTreeTausFiller::SimpleTreeTausFiller(edm::ParameterSet const& _cfg, edm::ConsumesCollector& _coll) :
  SimpleTreeFiller("TausFiller")
{
  getToken_(tausToken_, _cfg, _coll, "taus");
}

void
SimpleTreeTausFiller::fill(simpletree::Event& _outEvent, edm::Event const& _inEvent, edm::EventSetup const& _setup)
{
  auto& inTaus(getProduct_(_inEvent, tausToken_, "taus"));

  auto& outTaus(_outEvent.taus);

  for (auto& inTau : inTaus) {
    if (inTau.pt() < 18.)
      continue;
    if (std::abs(inTau.eta()) > 2.3)
      continue;

    auto& outTau(outTaus.create_back());

    fillP4(outTau, inTau);

    if (dynamic_cast<pat::Tau const*>(&inTau)) {
      auto& patTau(static_cast<pat::Tau const&>(inTau));
      outTau.decayMode = patTau.tauID("decayModeFinding") > 0.5;
      outTau.combIso = patTau.tauID("byCombinedIsolationDeltaBetaCorrRaw3Hits");
    }
  }
}
