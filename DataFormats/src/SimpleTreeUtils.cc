#include "../interface/SimpleTreeUtils.h"

#include "TFile.h"
#include "TROOT.h"
#include "TDirectory.h"

#include <iostream>
#include <stdexcept>

simpletree::TriggerHelper::TreeInterface::TreeInterface()
{
  hltMenu_ = new std::vector<TString>;

  gROOT->mkdir("simpletreeTriggerHelper");
}

simpletree::TriggerHelper::TreeInterface::~TreeInterface()
{
  // gROOT will be closed by the time static singleton is deleted
  delete hltMenu_;
}

bool
simpletree::TriggerHelper::TreeInterface::initRun(Event const& _event)
{
  auto* eventTree(_event.getInput());
  if (!eventTree)
    return false;

  if (_event.run != run_.run || eventTree->GetTreeNumber() != currentTreeNumber_) {
    if (eventTree->GetTreeNumber() != currentTreeNumber_) {
      // moved to a new file
      currentTreeNumber_ = eventTree->GetTreeNumber();

      auto* inputFile(eventTree->GetCurrentFile());
      if (!inputFile)
        return false;

      gROOT->cd("simpletreeTriggerHelper");
      delete gDirectory->Get("runs");
      delete gDirectory->Get("hlt");

      auto* runSource(static_cast<TTree*>(inputFile->Get("runs")));
      if (!runSource) {
        std::cerr << "File " << inputFile->GetName() << " does not have a run tree" << std::endl;
        throw std::runtime_error("InputError");
      }

      auto* runTree(runSource->CloneTree());

      run_.setAddress(*runTree);

      auto* hltSource(static_cast<TTree*>(inputFile->Get("hlt")));
      if (!hltSource) {
        std::cerr << "File " << inputFile->GetName() << " does not have an hlt tree" << std::endl;
        return false;
      }

      hltTree_ = hltSource->CloneTree();
      hltTree_->SetBranchAddress("paths", &hltMenu_);

      run_.run = 0;
      hltTreeEntry_ = -1;
    }

    auto* runTree(run_.getInput());

    long iEntry(0);
    while (run_.run != _event.run && runTree->GetEntry(iEntry++) > 0)
      continue;

    if (run_.run != _event.run) {
      std::cerr << "Run tree in file " << runTree->GetCurrentFile()->GetName() << " does not have an entry Run = " << _event.run << std::endl;
      throw std::runtime_error("InputError");
    }

    if (run_.hltMenu != hltTreeEntry_) {
      hltTreeEntry_ = run_.hltMenu;
      hltTree_->GetEntry(hltTreeEntry_);

      for (auto& pathIndex : pathIndices_) {
        unsigned iP(0);
        for (auto& path : *hltMenu_) {
          if (path.BeginsWith(pathIndex.first))
            break;
          ++iP;
        }
        if (iP == hltMenu_->size()) {
          std::cerr << "Path " << pathIndex.first << " not found for Event " << _event.run << ":" << _event.lumi << ":" << _event.event << std::endl;
          throw std::runtime_error("ArgumentError");
        }

        pathIndex.second = iP;
      }
    }
  }

  return true;
}

unsigned&
simpletree::TriggerHelper::TreeInterface::index(char const* _path)
{
  return pathIndices_[TString(_path)];
}

/*static*/
simpletree::TriggerHelper::TreeInterface*
simpletree::TriggerHelper::TreeInterface::singleton()
{
  static simpletree::TriggerHelper::TreeInterface singleton;
  return &singleton;
}

simpletree::TriggerHelper::TriggerHelper(char const* _path)
{
  TString path(_path);
  path += "_v";
  index_ = &TreeInterface::singleton()->index(path);
}

bool
simpletree::TriggerHelper::pass(Event const& _event)
{
  if (TreeInterface::singleton()->initRun(_event))
    return _event.hltBits.pass(*index_);

  return false;
}
