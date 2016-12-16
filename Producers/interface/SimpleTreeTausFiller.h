#ifndef MitFlat_Producers_SimpleTreeTausFiller_h
#define MitFlat_Producers_SimpleTreeTausFiller_h

#include "SimpleTreeFiller.h"

#include "DataFormats/Common/interface/View.h"
#include "DataFormats/TauReco/interface/BaseTau.h"

class SimpleTreeTausFiller : public SimpleTreeFiller {
 public:
  SimpleTreeTausFiller(edm::ParameterSet const&, edm::ConsumesCollector&);
  ~SimpleTreeTausFiller() {}

  void addBranch(flatutils::BranchList& _list) override { _list.emplace_back("taus"); }
  void fill(simpletree::Event&, edm::Event const&, edm::EventSetup const&) override;

 private:
  typedef edm::View<reco::BaseTau> TauView;

  edm::EDGetTokenT<TauView> tausToken_;
};

#endif
