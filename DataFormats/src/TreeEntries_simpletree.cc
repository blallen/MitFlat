#include "MitFlat/DataFormats/interface/TreeEntries_simpletree.h"
#include "TTree.h"
#include "TFile.h"
#include "TDirectory.h"

void
simpletree::Event::setStatus(TTree& _tree, Bool_t _status, flatutils::BranchList const& _branches/* = {"*"}*/)
{
  flatutils::setStatus(_tree, "", "run", _status, _branches);
  flatutils::setStatus(_tree, "", "lumi", _status, _branches);
  flatutils::setStatus(_tree, "", "event", _status, _branches);
  flatutils::setStatus(_tree, "", "weight", _status, _branches);
  flatutils::setStatus(_tree, "", "rho", _status, _branches);
  flatutils::setStatus(_tree, "", "npv", _status, _branches);
  flatutils::setStatus(_tree, "", "genHt", _status, _branches);
  flatutils::setStatus(_tree, "", "genZpt", _status, _branches);
  flatutils::setStatus(_tree, "", "ntau", _status, _branches);

  jets.setStatus(_tree, _status, flatutils::subBranchList(_branches, "jets"));
  photons.setStatus(_tree, _status, flatutils::subBranchList(_branches, "photons"));
  electrons.setStatus(_tree, _status, flatutils::subBranchList(_branches, "electrons"));
  muons.setStatus(_tree, _status, flatutils::subBranchList(_branches, "muons"));
  rawMet.setStatus(_tree, _status, flatutils::subBranchList(_branches, "rawMet"));
  t1Met.setStatus(_tree, _status, flatutils::subBranchList(_branches, "t1Met"));
  t1NoCHSMet.setStatus(_tree, _status, flatutils::subBranchList(_branches, "t1NoCHSMet"));
  eta30Met.setStatus(_tree, _status, flatutils::subBranchList(_branches, "eta30Met"));
  eta30T1Met.setStatus(_tree, _status, flatutils::subBranchList(_branches, "eta30T1Met"));
  eta30T1NoCHSMet.setStatus(_tree, _status, flatutils::subBranchList(_branches, "eta30T1NoCHSMet"));
  nhScaledMet.setStatus(_tree, _status, flatutils::subBranchList(_branches, "nhScaledMet"));
  chMet.setStatus(_tree, _status, flatutils::subBranchList(_branches, "chMet"));
  nhMet.setStatus(_tree, _status, flatutils::subBranchList(_branches, "nhMet"));
  neMet.setStatus(_tree, _status, flatutils::subBranchList(_branches, "neMet"));
  chGt30Met.setStatus(_tree, _status, flatutils::subBranchList(_branches, "chGt30Met"));
  nhGt30Met.setStatus(_tree, _status, flatutils::subBranchList(_branches, "nhGt30Met"));
  neGt30Met.setStatus(_tree, _status, flatutils::subBranchList(_branches, "neGt30Met"));
  hlt.setStatus(_tree, _status, flatutils::subBranchList(_branches, "hlt"));
}

void
simpletree::Event::setAddress(TTree& _tree, flatutils::BranchList const& _branches/* = {"*"}*/)
{
  flatutils::setStatusAndAddress(_tree, "", "run", &run, _branches);
  flatutils::setStatusAndAddress(_tree, "", "lumi", &lumi, _branches);
  flatutils::setStatusAndAddress(_tree, "", "event", &event, _branches);
  flatutils::setStatusAndAddress(_tree, "", "weight", &weight, _branches);
  flatutils::setStatusAndAddress(_tree, "", "rho", &rho, _branches);
  flatutils::setStatusAndAddress(_tree, "", "npv", &npv, _branches);
  flatutils::setStatusAndAddress(_tree, "", "genHt", &genHt, _branches);
  flatutils::setStatusAndAddress(_tree, "", "genZpt", &genZpt, _branches);
  flatutils::setStatusAndAddress(_tree, "", "ntau", &ntau, _branches);

  jets.setAddress(_tree, flatutils::subBranchList(_branches, "jets"));
  photons.setAddress(_tree, flatutils::subBranchList(_branches, "photons"));
  electrons.setAddress(_tree, flatutils::subBranchList(_branches, "electrons"));
  muons.setAddress(_tree, flatutils::subBranchList(_branches, "muons"));
  rawMet.setAddress(_tree, flatutils::subBranchList(_branches, "rawMet"));
  t1Met.setAddress(_tree, flatutils::subBranchList(_branches, "t1Met"));
  t1NoCHSMet.setAddress(_tree, flatutils::subBranchList(_branches, "t1NoCHSMet"));
  eta30Met.setAddress(_tree, flatutils::subBranchList(_branches, "eta30Met"));
  eta30T1Met.setAddress(_tree, flatutils::subBranchList(_branches, "eta30T1Met"));
  eta30T1NoCHSMet.setAddress(_tree, flatutils::subBranchList(_branches, "eta30T1NoCHSMet"));
  nhScaledMet.setAddress(_tree, flatutils::subBranchList(_branches, "nhScaledMet"));
  chMet.setAddress(_tree, flatutils::subBranchList(_branches, "chMet"));
  nhMet.setAddress(_tree, flatutils::subBranchList(_branches, "nhMet"));
  neMet.setAddress(_tree, flatutils::subBranchList(_branches, "neMet"));
  chGt30Met.setAddress(_tree, flatutils::subBranchList(_branches, "chGt30Met"));
  nhGt30Met.setAddress(_tree, flatutils::subBranchList(_branches, "nhGt30Met"));
  neGt30Met.setAddress(_tree, flatutils::subBranchList(_branches, "neGt30Met"));
  hlt.setAddress(_tree, flatutils::subBranchList(_branches, "hlt"));
}

void
simpletree::Event::book(TTree& _tree, flatutils::BranchList const& _branches/* = {"*"}*/)
{
  flatutils::book(_tree, "", "run", "", 'i', &run, _branches);
  flatutils::book(_tree, "", "lumi", "", 'i', &lumi, _branches);
  flatutils::book(_tree, "", "event", "", 'i', &event, _branches);
  flatutils::book(_tree, "", "weight", "", 'D', &weight, _branches);
  flatutils::book(_tree, "", "rho", "", 'D', &rho, _branches);
  flatutils::book(_tree, "", "npv", "", 's', &npv, _branches);
  flatutils::book(_tree, "", "genHt", "", 'F', &genHt, _branches);
  flatutils::book(_tree, "", "genZpt", "", 'F', &genZpt, _branches);
  flatutils::book(_tree, "", "ntau", "", 'i', &ntau, _branches);

  jets.book(_tree, flatutils::subBranchList(_branches, "jets"));
  photons.book(_tree, flatutils::subBranchList(_branches, "photons"));
  electrons.book(_tree, flatutils::subBranchList(_branches, "electrons"));
  muons.book(_tree, flatutils::subBranchList(_branches, "muons"));
  rawMet.book(_tree, flatutils::subBranchList(_branches, "rawMet"));
  t1Met.book(_tree, flatutils::subBranchList(_branches, "t1Met"));
  t1NoCHSMet.book(_tree, flatutils::subBranchList(_branches, "t1NoCHSMet"));
  eta30Met.book(_tree, flatutils::subBranchList(_branches, "eta30Met"));
  eta30T1Met.book(_tree, flatutils::subBranchList(_branches, "eta30T1Met"));
  eta30T1NoCHSMet.book(_tree, flatutils::subBranchList(_branches, "eta30T1NoCHSMet"));
  nhScaledMet.book(_tree, flatutils::subBranchList(_branches, "nhScaledMet"));
  chMet.book(_tree, flatutils::subBranchList(_branches, "chMet"));
  nhMet.book(_tree, flatutils::subBranchList(_branches, "nhMet"));
  neMet.book(_tree, flatutils::subBranchList(_branches, "neMet"));
  chGt30Met.book(_tree, flatutils::subBranchList(_branches, "chGt30Met"));
  nhGt30Met.book(_tree, flatutils::subBranchList(_branches, "nhGt30Met"));
  neGt30Met.book(_tree, flatutils::subBranchList(_branches, "neGt30Met"));
  hlt.book(_tree, flatutils::subBranchList(_branches, "hlt"));
}

void
simpletree::Weight::setStatus(TTree& _tree, Bool_t _status, flatutils::BranchList const& _branches/* = {"*"}*/)
{
  flatutils::setStatus(_tree, "", "run", _status, _branches);
  flatutils::setStatus(_tree, "", "lumi", _status, _branches);
  flatutils::setStatus(_tree, "", "event", _status, _branches);
  flatutils::setStatus(_tree, "", "weight", _status, _branches);
  flatutils::setStatus(_tree, "", "rho", _status, _branches);

}

void
simpletree::Weight::setAddress(TTree& _tree, flatutils::BranchList const& _branches/* = {"*"}*/)
{
  flatutils::setStatusAndAddress(_tree, "", "run", &run, _branches);
  flatutils::setStatusAndAddress(_tree, "", "lumi", &lumi, _branches);
  flatutils::setStatusAndAddress(_tree, "", "event", &event, _branches);
  flatutils::setStatusAndAddress(_tree, "", "weight", &weight, _branches);
  flatutils::setStatusAndAddress(_tree, "", "rho", &rho, _branches);

}

void
simpletree::Weight::book(TTree& _tree, flatutils::BranchList const& _branches/* = {"*"}*/)
{
  flatutils::book(_tree, "", "run", "", 'i', &run, _branches);
  flatutils::book(_tree, "", "lumi", "", 'i', &lumi, _branches);
  flatutils::book(_tree, "", "event", "", 'i', &event, _branches);
  flatutils::book(_tree, "", "weight", "", 'D', &weight, _branches);
  flatutils::book(_tree, "", "rho", "", 'D', &rho, _branches);

}

TTree*
simpletree::makeHLTPathTree()
{
  auto* tree(new TTree("HLTPath", "HLTPath"));
  TString* name(new TString);
  tree->Branch("name", "TString", &name);

  TString names[] = {
    "kPhoton120",
    "kPhoton165HE10",
    "kPhoton175",
    "kEle23Loose",
    "kEle27Loose",
    "kMu24",
    "kMu27",
    "kMETNoMu90MHTNoMu90",
    "kMETNoMu120MHTNoMu120",
    "nHLTPaths"
  };

  for (auto&& n : names) {
    *name = n;
    tree->Fill();
  }

  tree->ResetBranchAddresses();
  delete name;
  return tree;
}

