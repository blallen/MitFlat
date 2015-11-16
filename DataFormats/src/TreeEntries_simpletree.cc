#include "MitFlat/DataFormats/interface/TreeEntries_simpletree.h"
#include "TTree.h"
#include "TFile.h"
#include "TDirectory.h"

#include <cstring>

void
simpletree::Event::setStatus(TTree& _tree, Bool_t _status, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  flatutils::setStatus(_tree, "", "run", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, "", "lumi", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, "", "event", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, "", "weight", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, "", "rho", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, "", "npv", _status, _branches, _whitelist);

  partons.setStatus(_tree, _status, flatutils::subBranchList(_branches, "partons"), _whitelist);
  partonFinalStates.setStatus(_tree, _status, flatutils::subBranchList(_branches, "partonFinalStates"), _whitelist);
  jets.setStatus(_tree, _status, flatutils::subBranchList(_branches, "jets"), _whitelist);
  genJets.setStatus(_tree, _status, flatutils::subBranchList(_branches, "genJets"), _whitelist);
  photons.setStatus(_tree, _status, flatutils::subBranchList(_branches, "photons"), _whitelist);
  electrons.setStatus(_tree, _status, flatutils::subBranchList(_branches, "electrons"), _whitelist);
  muons.setStatus(_tree, _status, flatutils::subBranchList(_branches, "muons"), _whitelist);
  taus.setStatus(_tree, _status, flatutils::subBranchList(_branches, "taus"), _whitelist);
  rawMet.setStatus(_tree, _status, flatutils::subBranchList(_branches, "rawMet"), _whitelist);
  t1Met.setStatus(_tree, _status, flatutils::subBranchList(_branches, "t1Met"), _whitelist);
  genMet.setStatus(_tree, _status, flatutils::subBranchList(_branches, "genMet"), _whitelist);
  hlt.setStatus(_tree, _status, flatutils::subBranchList(_branches, "hlt"), _whitelist);
  reweight.setStatus(_tree, _status, flatutils::subBranchList(_branches, "reweight"), _whitelist);
}

void
simpletree::Event::setAddress(TTree& _tree, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  flatutils::setStatusAndAddress(_tree, "", "run", &run, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, "", "lumi", &lumi, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, "", "event", &event, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, "", "weight", &weight, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, "", "rho", &rho, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, "", "npv", &npv, _branches, _whitelist);

  partons.setAddress(_tree, flatutils::subBranchList(_branches, "partons"), _whitelist);
  partonFinalStates.setAddress(_tree, flatutils::subBranchList(_branches, "partonFinalStates"), _whitelist);
  jets.setAddress(_tree, flatutils::subBranchList(_branches, "jets"), _whitelist);
  genJets.setAddress(_tree, flatutils::subBranchList(_branches, "genJets"), _whitelist);
  photons.setAddress(_tree, flatutils::subBranchList(_branches, "photons"), _whitelist);
  electrons.setAddress(_tree, flatutils::subBranchList(_branches, "electrons"), _whitelist);
  muons.setAddress(_tree, flatutils::subBranchList(_branches, "muons"), _whitelist);
  taus.setAddress(_tree, flatutils::subBranchList(_branches, "taus"), _whitelist);
  rawMet.setAddress(_tree, flatutils::subBranchList(_branches, "rawMet"), _whitelist);
  t1Met.setAddress(_tree, flatutils::subBranchList(_branches, "t1Met"), _whitelist);
  genMet.setAddress(_tree, flatutils::subBranchList(_branches, "genMet"), _whitelist);
  hlt.setAddress(_tree, flatutils::subBranchList(_branches, "hlt"), _whitelist);
  reweight.setAddress(_tree, flatutils::subBranchList(_branches, "reweight"), _whitelist);
}

void
simpletree::Event::book(TTree& _tree, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  flatutils::book(_tree, "", "run", "", 'i', &run, _branches, _whitelist);
  flatutils::book(_tree, "", "lumi", "", 'i', &lumi, _branches, _whitelist);
  flatutils::book(_tree, "", "event", "", 'i', &event, _branches, _whitelist);
  flatutils::book(_tree, "", "weight", "", 'D', &weight, _branches, _whitelist);
  flatutils::book(_tree, "", "rho", "", 'D', &rho, _branches, _whitelist);
  flatutils::book(_tree, "", "npv", "", 's', &npv, _branches, _whitelist);

  partons.book(_tree, flatutils::subBranchList(_branches, "partons"), _whitelist);
  partonFinalStates.book(_tree, flatutils::subBranchList(_branches, "partonFinalStates"), _whitelist);
  jets.book(_tree, flatutils::subBranchList(_branches, "jets"), _whitelist);
  genJets.book(_tree, flatutils::subBranchList(_branches, "genJets"), _whitelist);
  photons.book(_tree, flatutils::subBranchList(_branches, "photons"), _whitelist);
  electrons.book(_tree, flatutils::subBranchList(_branches, "electrons"), _whitelist);
  muons.book(_tree, flatutils::subBranchList(_branches, "muons"), _whitelist);
  taus.book(_tree, flatutils::subBranchList(_branches, "taus"), _whitelist);
  rawMet.book(_tree, flatutils::subBranchList(_branches, "rawMet"), _whitelist);
  t1Met.book(_tree, flatutils::subBranchList(_branches, "t1Met"), _whitelist);
  genMet.book(_tree, flatutils::subBranchList(_branches, "genMet"), _whitelist);
  hlt.book(_tree, flatutils::subBranchList(_branches, "hlt"), _whitelist);
  reweight.book(_tree, flatutils::subBranchList(_branches, "reweight"), _whitelist);
}

void
simpletree::Weight::setStatus(TTree& _tree, Bool_t _status, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  flatutils::setStatus(_tree, "", "run", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, "", "lumi", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, "", "event", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, "", "weight", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, "", "rho", _status, _branches, _whitelist);

}

void
simpletree::Weight::setAddress(TTree& _tree, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  flatutils::setStatusAndAddress(_tree, "", "run", &run, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, "", "lumi", &lumi, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, "", "event", &event, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, "", "weight", &weight, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, "", "rho", &rho, _branches, _whitelist);

}

void
simpletree::Weight::book(TTree& _tree, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  flatutils::book(_tree, "", "run", "", 'i', &run, _branches, _whitelist);
  flatutils::book(_tree, "", "lumi", "", 'i', &lumi, _branches, _whitelist);
  flatutils::book(_tree, "", "event", "", 'i', &event, _branches, _whitelist);
  flatutils::book(_tree, "", "weight", "", 'D', &weight, _branches, _whitelist);
  flatutils::book(_tree, "", "rho", "", 'D', &rho, _branches, _whitelist);

}

TTree*
simpletree::makeHLTPathTree()
{
  auto* tree(new TTree("HLTPath", "HLTPath"));
  char name[1024];
  tree->Branch("name", name, "name/C");

  TString names[] = {
    "kPhoton120",
    "kPhoton135MET100",
    "kPhoton165HE10",
    "kPhoton175",
    "kEle23Loose",
    "kEle27Loose",
    "kMu24",
    "kMu27",
    "kMET170",
    "kMETNoMu90MHTNoMu90",
    "kMETNoMu120MHTNoMu120",
    "nHLTPaths"
  };

  for (auto&& n : names) {
    std::strcpy(name, n.Data());
    tree->Fill();
  }

  tree->ResetBranchAddresses();
  return tree;
}

