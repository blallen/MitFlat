#ifndef MitFlat_Producers_SimpleTreeT1MetFiller_h
#define MitFlat_Producers_SimpleTreeT1MetFiller_h

#include "SimpleTreeFiller.h"

#include "DataFormats/Common/interface/View.h"
#include "DataFormats/METReco/interface/MET.h"

class SimpleTreeT1MetFiller : public SimpleTreeFiller {
 public:
  SimpleTreeT1MetFiller(edm::ParameterSet const&, edm::ConsumesCollector&);
  ~SimpleTreeT1MetFiller() {}

  void addBranch(flatutils::BranchList& _list) override { _list.emplace_back("t1Met"); }
  void fill(simpletree::Event&, edm::Event const&, edm::EventSetup const&) override;

 private:
  typedef edm::View<reco::MET> METView;

  edm::EDGetTokenT<METView> metToken_;
};

#endif
