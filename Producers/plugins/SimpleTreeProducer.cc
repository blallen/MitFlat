#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/Run.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "MitFlat/DataFormats/interface/TreeEntries_simpletree.h"

#include "../interface/SimpleTreeElectronsFiller.h"
#include "../interface/SimpleTreeHLTFiller.h"
#include "../interface/SimpleTreeJetsFiller.h"
#include "../interface/SimpleTreeMetFiltersFiller.h"
#include "../interface/SimpleTreeMuonsFiller.h"
#include "../interface/SimpleTreePhotonsFiller.h"
#include "../interface/SimpleTreeRhoFiller.h"
#include "../interface/SimpleTreeSuperClustersFiller.h"
#include "../interface/SimpleTreeT1MetFiller.h"
#include "../interface/SimpleTreeTausFiller.h"
#include "../interface/SimpleTreeVerticesFiller.h"

#include "TFile.h"
#include "TTree.h"

#include <vector>
#include <utility>

class SimpleTreeProducer : public edm::EDAnalyzer {
public:
  explicit SimpleTreeProducer(edm::ParameterSet const&);
  ~SimpleTreeProducer();

private:
  void analyze(edm::Event const&, edm::EventSetup const&) override;
  void beginRun(edm::Run const&, edm::EventSetup const&) override;
  void beginJob() override;
  void endJob() override;

  std::vector<SimpleTreeFiller*> fillers_;

  TFile* outputFile_{0};
  TTree* eventTree_{0};
  TTree* runTree_{0};
  simpletree::Event outEvent_;
  simpletree::Run outRun_;
};

SimpleTreeProducer::SimpleTreeProducer(edm::ParameterSet const& _cfg)
{
  auto&& coll(consumesCollector());

  fillers_.push_back(new SimpleTreeElectronsFiller(_cfg, coll));
  fillers_.push_back(new SimpleTreeHLTFiller(_cfg, coll));
  fillers_.push_back(new SimpleTreeJetsFiller(_cfg, coll));
  fillers_.push_back(new SimpleTreeMetFiltersFiller(_cfg, coll));
  fillers_.push_back(new SimpleTreeMuonsFiller(_cfg, coll));
  fillers_.push_back(new SimpleTreePhotonsFiller(_cfg, coll));
  fillers_.push_back(new SimpleTreeRhoFiller(_cfg, coll));
  fillers_.push_back(new SimpleTreeSuperClustersFiller(_cfg, coll));
  fillers_.push_back(new SimpleTreeT1MetFiller(_cfg, coll));
  fillers_.push_back(new SimpleTreeTausFiller(_cfg, coll));
  fillers_.push_back(new SimpleTreeVerticesFiller(_cfg, coll));
}

SimpleTreeProducer::~SimpleTreeProducer()
{
  for (auto* filler : fillers_)
    delete filler;
}

void
SimpleTreeProducer::analyze(edm::Event const& _event, edm::EventSetup const& _setup)
{
  outEvent_.init();

  outEvent_.run = _event.id().run();
  outEvent_.lumi = _event.luminosityBlock();
  outEvent_.event = _event.id().event();
  // TODO
  outEvent_.weight = 1.;

  for (auto* filler : fillers_)
    filler->fill(outEvent_, _event, _setup);

  eventTree_->Fill();
}

void
SimpleTreeProducer::beginRun(edm::Run const& _run, edm::EventSetup const& _setup)
{
  outRun_.init();

  outRun_.run = _run.run();

  for (auto* filler : fillers_)
    filler->fillRun(outRun_, _run, _setup);

  runTree_->Fill();
}

void 
SimpleTreeProducer::beginJob()
{
  outputFile_ = TFile::Open("simpletree.root", "recreate");
  eventTree_ = new TTree("events", "");
  runTree_ = new TTree("runs", "");
  outEvent_.book(*eventTree_);
  outRun_.book(*runTree_);

  for (auto* filler : fillers_)
    filler->addOutput(*outputFile_);
}

void 
SimpleTreeProducer::endJob()
{
  outputFile_->cd();
  outputFile_->Write();
  delete outputFile_;
}

DEFINE_FWK_MODULE(SimpleTreeProducer);
