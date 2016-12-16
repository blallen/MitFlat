#ifndef MitFlat_Producers_SimpleTreeMetFiltersFiller_h
#define MitFlat_Producers_SimpleTreeMetFiltersFiller_h

#include "SimpleTreeFiller.h"

#include "DataFormats/Common/interface/TriggerResults.h"

class SimpleTreeMetFiltersFiller : public SimpleTreeFiller {
 public:
  SimpleTreeMetFiltersFiller(edm::ParameterSet const&, edm::ConsumesCollector&);
  ~SimpleTreeMetFiltersFiller() {}

  void addBranch(flatutils::BranchList& _list) override { _list.emplace_back("metFilters"); }
  void fill(simpletree::Event&, edm::Event const&, edm::EventSetup const&) override;

 private:
  edm::EDGetTokenT<edm::TriggerResults> filterResultsToken_;
  edm::EDGetTokenT<bool> hbheToken_;
  edm::EDGetTokenT<bool> hbheIsoToken_;
  edm::EDGetTokenT<bool> ecalDeadCellToken_;
  edm::EDGetTokenT<bool> badscToken_;
  edm::EDGetTokenT<bool> globalHalo16Token_;
  edm::EDGetTokenT<bool> badTrackToken_;
  edm::EDGetTokenT<bool> badMuonTrackToken_;
};

#endif
