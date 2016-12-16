#ifndef MitFlat_Producers_SimpleTreeVerticesFiller_h
#define MitFlat_Producers_SimpleTreeVerticesFiller_h

#include "SimpleTreeFiller.h"

#include "DataFormats/VertexReco/interface/VertexFwd.h"

class SimpleTreeVerticesFiller : public SimpleTreeFiller {
 public:
  SimpleTreeVerticesFiller(edm::ParameterSet const&, edm::ConsumesCollector&);
  ~SimpleTreeVerticesFiller() {}

  void addBranch(flatutils::BranchList& _list) override { _list.emplace_back("npv*"); }
  void fill(simpletree::Event&, edm::Event const&, edm::EventSetup const&) override;

 private:
  edm::EDGetTokenT<reco::VertexCollection> verticesToken_;
};

#endif
