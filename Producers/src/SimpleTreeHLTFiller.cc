#include "../interface/SimpleTreeHLTFiller.h"

#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/PatCandidates/interface/MET.h"

SimpleTreeHLTFiller::SimpleTreeHLTFiller(edm::ParameterSet const& _cfg, edm::ConsumesCollector& _coll) :
  SimpleTreeFiller("HLTFiller")
{
  getToken_(triggerResultsToken_, _cfg, _coll, "triggerResults");
}

SimpleTreeHLTFiller::~SimpleTreeHLTFiller()
{
  delete paths_;
}

void
SimpleTreeHLTFiller::addOutput(TFile& outputFile_)
{
  outputFile_.cd();
  hltTree_ = new TTree("hlt", "HLT");
  paths_ = new std::vector<TString>;
  hltTree_->Branch("paths", "std::vector<TString>", &paths_, 32000, 0);
}

void
SimpleTreeHLTFiller::fillRun(simpletree::Run& _outRun, edm::Run const& _inRun, edm::EventSetup const& _setup)
{
  bool configChanged(false);
  if (!hltConfig_.init(_inRun, _setup, "HLT", configChanged)) {
    throw edm::Exception(edm::errors::Configuration, "SimpleTreeHLTFiller")
      << "Cannot access hlt config";
  }

  auto&& menuName(hltConfig_.tableName());
  auto menuItr(menuMap_.find(menuName));

  if (!configChanged) {
    if (menuItr != menuMap_.end() && menuItr->second == currentMenu_)
      return;
    else
      throw edm::Exception(edm::errors::Configuration, "SimpleTreeHLTFiller")
        << "HLTConfigProvider claims nothing is changed, but the menu name did.";
  }

  if (menuItr != menuMap_.end()) {
    _outRun.hltMenu = menuItr->second;
    hltTree_->GetEntry(_outRun.hltMenu);
    return;
  }

  _outRun.hltMenu = menuMap_.size();
  menuMap_.emplace(menuName, _outRun.hltMenu);

  paths_->clear();
  for (unsigned iP(0); iP != hltConfig_.size(); ++iP)
    paths_->push_back(hltConfig_.triggerName(iP));

  hltTree_->Fill();
}

void
SimpleTreeHLTFiller::fill(simpletree::Event& _outEvent, edm::Event const& _inEvent, edm::EventSetup const& _setup)
{
  auto& inTriggerResults(getProduct_(_inEvent, triggerResultsToken_, "hlt"));

  auto& outHLT(_outEvent.hltBits);

  for (unsigned iF(0); iF != inTriggerResults.size(); ++iF) {
    if (inTriggerResults.accept(iF))
      outHLT.set(iF);
  }
}
