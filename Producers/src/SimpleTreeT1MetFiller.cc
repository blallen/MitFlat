#include "../interface/SimpleTreeT1MetFiller.h"

#include "DataFormats/PatCandidates/interface/MET.h"

SimpleTreeT1MetFiller::SimpleTreeT1MetFiller(edm::ParameterSet const& _cfg, edm::ConsumesCollector& _coll) :
  SimpleTreeFiller("T1MetFiller")
{
  getToken_(metToken_, _cfg, _coll, "t1met");
}

void
SimpleTreeT1MetFiller::fill(simpletree::Event& _outEvent, edm::Event const& _inEvent, edm::EventSetup const& _setup)
{
  auto& inT1Met(getProduct_(_inEvent, metToken_, "t1met").at(0));

  auto& outT1Met(_outEvent.t1Met);

  outT1Met.met = inT1Met.pt();
  outT1Met.phi = inT1Met.phi();
  outT1Met.sumEt = inT1Met.sumEt();

  if (dynamic_cast<pat::MET const*>(&inT1Met)) {
    auto& patMet(static_cast<pat::MET const&>(inT1Met));

    outT1Met.metCorrUp = patMet.shiftedPt(pat::MET::JetEnUp);
    outT1Met.phiCorrUp = patMet.shiftedPhi(pat::MET::JetEnUp);
    outT1Met.metCorrDown = patMet.shiftedPt(pat::MET::JetEnDown);
    outT1Met.phiCorrDown = patMet.shiftedPhi(pat::MET::JetEnDown);
    // TODO
    outT1Met.metJetRes = outT1Met.met;
    outT1Met.phiJetRes = outT1Met.phi;
    outT1Met.metUnclUp = patMet.shiftedPt(pat::MET::UnclusteredEnUp);
    outT1Met.phiUnclUp = patMet.shiftedPhi(pat::MET::UnclusteredEnUp);
    outT1Met.metUnclDown = patMet.shiftedPt(pat::MET::UnclusteredEnDown);
    outT1Met.phiUnclDown = patMet.shiftedPhi(pat::MET::UnclusteredEnDown);
  }
}
