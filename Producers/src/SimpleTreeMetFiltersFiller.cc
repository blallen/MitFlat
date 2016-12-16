#include "../interface/SimpleTreeMetFiltersFiller.h"

#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/PatCandidates/interface/MET.h"

SimpleTreeMetFiltersFiller::SimpleTreeMetFiltersFiller(edm::ParameterSet const& _cfg, edm::ConsumesCollector& _coll) :
  SimpleTreeFiller("MetFiltersFiller")
{
  getToken_(filterResultsToken_, _cfg, _coll, "metFilters", false);

  getToken_(hbheToken_, _cfg, _coll, "hbhe", false);
  getToken_(hbheIsoToken_, _cfg, _coll, "hbheIso", false);
  getToken_(ecalDeadCellToken_, _cfg, _coll, "ecalDeadCell", false);
  getToken_(badscToken_, _cfg, _coll, "badsc", false);
  getToken_(globalHalo16Token_, _cfg, _coll, "globalHalo16", false);
  getToken_(badTrackToken_, _cfg, _coll, "badTrack");
  getToken_(badMuonTrackToken_, _cfg, _coll, "badMuonTrack");
}

void
SimpleTreeMetFiltersFiller::fill(simpletree::Event& _outEvent, edm::Event const& _inEvent, edm::EventSetup const& _setup)
{
  auto& outMetFilters(_outEvent.metFilters);

  if (!filterResultsToken_.isUninitialized()) {
    auto& inFilterResults(getProduct_(_inEvent, filterResultsToken_, "metFilters"));
    auto&& filterNames(_inEvent.triggerNames(inFilterResults));
    for (unsigned iF(0); iF != filterNames.size(); ++iF) {
      auto& name(filterNames.triggerName(iF));
    
      if (name == "Flag_HBHENoiseFilter")
        outMetFilters.hbhe = !inFilterResults.accept(iF);
      else if (name == "Flag_HBHENoiseIsoFilter")
        outMetFilters.hbheIso = !inFilterResults.accept(iF);
      else if (name == "Flag_EcalDeadCellTriggerPrimitiveFilter")
        outMetFilters.ecalDeadCell = !inFilterResults.accept(iF);
      else if (name == "Flag_eeBadScFilter")
        outMetFilters.badsc = !inFilterResults.accept(iF);
      else if (name == "Flag_globalTightHalo2016Filter")
        outMetFilters.globalHalo16 = !inFilterResults.accept(iF);
    }
  }
  else {
    outMetFilters.hbhe = !getProduct_(_inEvent, hbheToken_, "hbhe");
    outMetFilters.hbheIso = !getProduct_(_inEvent, hbheIsoToken_, "hbheIso");
    outMetFilters.ecalDeadCell = !getProduct_(_inEvent, ecalDeadCellToken_, "ecalDeadCell");
    outMetFilters.badsc = !getProduct_(_inEvent, badscToken_, "badsc");
    outMetFilters.globalHalo16 = !getProduct_(_inEvent, globalHalo16Token_, "globalHalo16");
  }

  outMetFilters.badTrack = !getProduct_(_inEvent, badTrackToken_, "badTrack");
  outMetFilters.badMuonTrack = !getProduct_(_inEvent, badMuonTrackToken_, "badMuonTrack");
}
