#ifndef MitFlat_Producers_SimpleTreeHLTFiller_h
#define MitFlat_Producers_SimpleTreeHLTFiller_h

#include "SimpleTreeFiller.h"

#include "DataFormats/Common/interface/TriggerResults.h"
#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"

class SimpleTreeHLTFiller : public SimpleTreeFiller {
 public:
  SimpleTreeHLTFiller(edm::ParameterSet const&, edm::ConsumesCollector&);
  ~SimpleTreeHLTFiller();

  void addBranch(flatutils::BranchList& _list) override { _list.emplace_back("hlt"); }
  void addOutput(TFile&) override;
  void fill(simpletree::Event&, edm::Event const&, edm::EventSetup const&) override;
  void fillRun(simpletree::Run&, edm::Run const&, edm::EventSetup const&) override;

 private:
  edm::EDGetTokenT<edm::TriggerResults> triggerResultsToken_;
  HLTConfigProvider hltConfig_;
  unsigned currentMenu_{};
  std::map<std::string, unsigned> menuMap_{};

  TTree* hltTree_{0};
  std::vector<TString>* paths_{0};
};

#endif
