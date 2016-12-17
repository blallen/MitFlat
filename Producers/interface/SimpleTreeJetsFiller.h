#ifndef MitFlat_Producers_SimpleTreeJetsFiller_h
#define MitFlat_Producers_SimpleTreeJetsFiller_h

#include "SimpleTreeFiller.h"

#include "DataFormats/Common/interface/View.h"
#include "DataFormats/JetReco/interface/Jet.h"

class JetCorrectionUncertainty;

class SimpleTreeJetsFiller : public SimpleTreeFiller {
 public:
  SimpleTreeJetsFiller(edm::ParameterSet const&, edm::ConsumesCollector&);
  ~SimpleTreeJetsFiller();

  void addBranch(flatutils::BranchList& _list) override { _list.emplace_back("jets"); }
  void fill(simpletree::Event&, edm::Event const&, edm::EventSetup const&) override;

 private:
  typedef edm::View<reco::Jet> JetView;

  edm::EDGetTokenT<JetView> jetsToken_;

  JetCorrectionUncertainty* jecUncertainty_{0};
};

#endif
