#ifndef MitFlat_Producers_SimpleTreeRhoFiller_h
#define MitFlat_Producers_SimpleTreeRhoFiller_h

#include "SimpleTreeFiller.h"

class SimpleTreeRhoFiller : public SimpleTreeFiller {
 public:
  SimpleTreeRhoFiller(edm::ParameterSet const&, edm::ConsumesCollector&);
  ~SimpleTreeRhoFiller() {}

  void addBranch(flatutils::BranchList& _list) override { _list.emplace_back("rho"); }
  void fill(simpletree::Event&, edm::Event const&, edm::EventSetup const&) override;

 private:
  edm::EDGetTokenT<double> rhoToken_;
};

#endif
