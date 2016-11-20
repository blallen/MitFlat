#ifndef MitFlat_Producers_SimpleTreeMetFiltersFiller_h
#define MitFlat_Producers_SimpleTreeMetFiltersFiller_h

#include "SimpleTreeFiller.h"

#include "DataFormats/Common/interface/TriggerResults.h"

class SimpleTreeMetFiltersFiller : public SimpleTreeFiller {
 public:
  SimpleTreeMetFiltersFiller(edm::ParameterSet const&, edm::ConsumesCollector&);
  ~SimpleTreeMetFiltersFiller() {}

  void fill(simpletree::Event&, edm::Event const&, edm::EventSetup const&) override;

 private:
  edm::EDGetTokenT<edm::TriggerResults> filterResultsToken_;
  edm::EDGetTokenT<bool> badTrackToken_;
  edm::EDGetTokenT<bool> badMuonTrackToken_;
};

#endif
