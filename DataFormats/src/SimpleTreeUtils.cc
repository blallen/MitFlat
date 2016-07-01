#include "../interface/SimpleTreeUtils.h"

#include "TFile.h"

#include <iostream>
#include <stdexcept>

bool simpletree::TriggerHelper::staticAssignment_(false);
std::map<TString, unsigned> simpletree::TriggerHelper::indices_{};

void
simpletree::TriggerHelper::TreeInterface::reset()
{
  currentRun_ = 0;
  currentTreeNumber_ = -1;
  currentMenuIndex_ = 0xffffffff;

  runToMenuIndex_.clear();
  menus_.clear();
}

bool
simpletree::TriggerHelper::TreeInterface::initRun(Event const& _event)
{
  auto* eventTree(_event.getInput());
  if (!eventTree)
    return false;

  if (_event.run != currentRun_ || eventTree->GetTreeNumber() != currentTreeNumber_) {
    currentRun_ = _event.run;

    if (eventTree->GetTreeNumber() != currentTreeNumber_) {
      // moved to a new file
      currentTreeNumber_ = eventTree->GetTreeNumber();

      auto* inputFile(eventTree->GetCurrentFile());
      if (!inputFile)
        return false;

      runToMenuIndex_.clear();
      menus_.clear();

      auto* runTree(static_cast<TTree*>(inputFile->Get("runs")));
      if (!runTree) {
        std::cerr << "File " << inputFile->GetName() << " does not have a run tree" << std::endl;
        throw std::runtime_error("InputError");
      }

      auto* hltTree(static_cast<TTree*>(inputFile->Get("hlt")));
      if (!hltTree) {
        std::cerr << "File " << inputFile->GetName() << " does not have an hlt tree" << std::endl;
        return false;
      }

      auto* runTreeAddrs(runTree->CloneTree(0));
      runTreeAddrs->CopyAddresses(runTree, true); // second argument: undo = true. Probably has the same effect as runTree->ResetBranchAddresses()...

      simpletree::Run run;
      run.setAddress(*runTree);

      long iEntry(0);
      while (runTree->GetEntry(iEntry++) > 0)
        runToMenuIndex_.emplace(run.run, run.hltMenu);

      runTreeAddrs->CopyAddresses(runTree);
      delete runTreeAddrs;

      auto* hltTreeAddrs(hltTree->CloneTree(0));
      hltTreeAddrs->CopyAddresses(hltTree, true);

      auto* hltMenu(new std::vector<TString>);
      hltTree->SetBranchAddress("paths", &hltMenu);

      iEntry = 0;
      while (hltTree->GetEntry(iEntry++) > 0)
        menus_.emplace_back(*hltMenu);

      hltTreeAddrs->CopyAddresses(hltTree);
      delete hltTreeAddrs;
      delete hltMenu;

      currentMenuIndex_ = 0xffffffff;
    }

    auto idxItr(runToMenuIndex_.find(currentRun_));
    if (idxItr == runToMenuIndex_.end()) {
      std::cerr << "Run " << currentRun_ << " not found in the run tree" << std::endl;
      throw std::runtime_error("InputError");
    }

    if (idxItr->second != currentMenuIndex_) {
      currentMenuIndex_ = idxItr->second;
      auto& menu(menus_.at(currentMenuIndex_));

      for (auto& pathIndex : pathIndices_) {
        unsigned iP(0);
        for (auto& path : menu) {
          if (path.BeginsWith(pathIndex.first))
            break;
          ++iP;
        }
        if (iP == menu.size()) {
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
  if (staticAssignment_) {
    auto itr(indices_.find(_path));
    if (itr == indices_.end())
      throw std::runtime_error(TString::Format("Unknown trigger path %s", _path));

    index_ = &itr->second;
  }
  else {
    TString path(_path);
    path += "_v";
    index_ = &TreeInterface::singleton()->index(path);
  }
}

void
simpletree::TriggerHelper::assignIndex(char const* _path, unsigned _index)
{
  // Once any index is assigned by hand, we don't use input files to determine the trigger index any more.
  staticAssignment_ = true;
  
  indices_.emplace(_path, _index);
}

bool
simpletree::TriggerHelper::pass(Event const& _event)
{
  if (staticAssignment_ || TreeInterface::singleton()->initRun(_event))
    return _event.hltBits.pass(*index_);

  return false;
}
