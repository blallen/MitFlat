#include "MitFlat/DataFormats/interface/TreeEntries_simpletree.h"
#include "TTree.h"
#include "TFile.h"
#include "TDirectory.h"

void
simpletree::Event::setStatus(TTree& _tree, Bool_t _status, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  flatutils::setStatus(_tree, "", "run", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, "", "lumi", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, "", "event", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, "", "weight", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, "", "rho", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, "", "npv", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, "", "genHt", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, "", "genBoson", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, "", "genBosonPt", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, "", "genBosonEta", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, "", "genBosonPhi", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, "", "genBosonM", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, "", "genLepton1", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, "", "genLepton1Pt", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, "", "genLepton1Eta", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, "", "genLepton1Phi", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, "", "genLepton1M", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, "", "genLepton2", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, "", "genLepton2Pt", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, "", "genLepton2Eta", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, "", "genLepton2Phi", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, "", "genLepton2M", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, "", "ntau", _status, _branches, _whitelist);

  jets.setStatus(_tree, _status, flatutils::subBranchList(_branches, "jets"), _whitelist);
  photons.setStatus(_tree, _status, flatutils::subBranchList(_branches, "photons"), _whitelist);
  electrons.setStatus(_tree, _status, flatutils::subBranchList(_branches, "electrons"), _whitelist);
  muons.setStatus(_tree, _status, flatutils::subBranchList(_branches, "muons"), _whitelist);
  rawMet.setStatus(_tree, _status, flatutils::subBranchList(_branches, "rawMet"), _whitelist);
  t1Met.setStatus(_tree, _status, flatutils::subBranchList(_branches, "t1Met"), _whitelist);
  t1NoCHSMet.setStatus(_tree, _status, flatutils::subBranchList(_branches, "t1NoCHSMet"), _whitelist);
  nhScaledMet.setStatus(_tree, _status, flatutils::subBranchList(_branches, "nhScaledMet"), _whitelist);
  chMet.setStatus(_tree, _status, flatutils::subBranchList(_branches, "chMet"), _whitelist);
  nhMet.setStatus(_tree, _status, flatutils::subBranchList(_branches, "nhMet"), _whitelist);
  neMet.setStatus(_tree, _status, flatutils::subBranchList(_branches, "neMet"), _whitelist);
  hlt.setStatus(_tree, _status, flatutils::subBranchList(_branches, "hlt"), _whitelist);
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
  flatutils::setStatusAndAddress(_tree, "", "genHt", &genHt, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, "", "genBoson", &genBoson, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, "", "genBosonPt", &genBosonPt, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, "", "genBosonEta", &genBosonEta, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, "", "genBosonPhi", &genBosonPhi, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, "", "genBosonM", &genBosonM, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, "", "genLepton1", &genLepton1, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, "", "genLepton1Pt", &genLepton1Pt, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, "", "genLepton1Eta", &genLepton1Eta, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, "", "genLepton1Phi", &genLepton1Phi, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, "", "genLepton1M", &genLepton1M, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, "", "genLepton2", &genLepton2, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, "", "genLepton2Pt", &genLepton2Pt, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, "", "genLepton2Eta", &genLepton2Eta, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, "", "genLepton2Phi", &genLepton2Phi, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, "", "genLepton2M", &genLepton2M, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, "", "ntau", &ntau, _branches, _whitelist);

  jets.setAddress(_tree, flatutils::subBranchList(_branches, "jets"), _whitelist);
  photons.setAddress(_tree, flatutils::subBranchList(_branches, "photons"), _whitelist);
  electrons.setAddress(_tree, flatutils::subBranchList(_branches, "electrons"), _whitelist);
  muons.setAddress(_tree, flatutils::subBranchList(_branches, "muons"), _whitelist);
  rawMet.setAddress(_tree, flatutils::subBranchList(_branches, "rawMet"), _whitelist);
  t1Met.setAddress(_tree, flatutils::subBranchList(_branches, "t1Met"), _whitelist);
  t1NoCHSMet.setAddress(_tree, flatutils::subBranchList(_branches, "t1NoCHSMet"), _whitelist);
  nhScaledMet.setAddress(_tree, flatutils::subBranchList(_branches, "nhScaledMet"), _whitelist);
  chMet.setAddress(_tree, flatutils::subBranchList(_branches, "chMet"), _whitelist);
  nhMet.setAddress(_tree, flatutils::subBranchList(_branches, "nhMet"), _whitelist);
  neMet.setAddress(_tree, flatutils::subBranchList(_branches, "neMet"), _whitelist);
  hlt.setAddress(_tree, flatutils::subBranchList(_branches, "hlt"), _whitelist);
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
  flatutils::book(_tree, "", "genHt", "", 'F', &genHt, _branches, _whitelist);
  flatutils::book(_tree, "", "genBoson", "", 'S', &genBoson, _branches, _whitelist);
  flatutils::book(_tree, "", "genBosonPt", "", 'F', &genBosonPt, _branches, _whitelist);
  flatutils::book(_tree, "", "genBosonEta", "", 'F', &genBosonEta, _branches, _whitelist);
  flatutils::book(_tree, "", "genBosonPhi", "", 'F', &genBosonPhi, _branches, _whitelist);
  flatutils::book(_tree, "", "genBosonM", "", 'F', &genBosonM, _branches, _whitelist);
  flatutils::book(_tree, "", "genLepton1", "", 'S', &genLepton1, _branches, _whitelist);
  flatutils::book(_tree, "", "genLepton1Pt", "", 'F', &genLepton1Pt, _branches, _whitelist);
  flatutils::book(_tree, "", "genLepton1Eta", "", 'F', &genLepton1Eta, _branches, _whitelist);
  flatutils::book(_tree, "", "genLepton1Phi", "", 'F', &genLepton1Phi, _branches, _whitelist);
  flatutils::book(_tree, "", "genLepton1M", "", 'F', &genLepton1M, _branches, _whitelist);
  flatutils::book(_tree, "", "genLepton2", "", 'S', &genLepton2, _branches, _whitelist);
  flatutils::book(_tree, "", "genLepton2Pt", "", 'F', &genLepton2Pt, _branches, _whitelist);
  flatutils::book(_tree, "", "genLepton2Eta", "", 'F', &genLepton2Eta, _branches, _whitelist);
  flatutils::book(_tree, "", "genLepton2Phi", "", 'F', &genLepton2Phi, _branches, _whitelist);
  flatutils::book(_tree, "", "genLepton2M", "", 'F', &genLepton2M, _branches, _whitelist);
  flatutils::book(_tree, "", "ntau", "", 'i', &ntau, _branches, _whitelist);

  jets.book(_tree, flatutils::subBranchList(_branches, "jets"), _whitelist);
  photons.book(_tree, flatutils::subBranchList(_branches, "photons"), _whitelist);
  electrons.book(_tree, flatutils::subBranchList(_branches, "electrons"), _whitelist);
  muons.book(_tree, flatutils::subBranchList(_branches, "muons"), _whitelist);
  rawMet.book(_tree, flatutils::subBranchList(_branches, "rawMet"), _whitelist);
  t1Met.book(_tree, flatutils::subBranchList(_branches, "t1Met"), _whitelist);
  t1NoCHSMet.book(_tree, flatutils::subBranchList(_branches, "t1NoCHSMet"), _whitelist);
  nhScaledMet.book(_tree, flatutils::subBranchList(_branches, "nhScaledMet"), _whitelist);
  chMet.book(_tree, flatutils::subBranchList(_branches, "chMet"), _whitelist);
  nhMet.book(_tree, flatutils::subBranchList(_branches, "nhMet"), _whitelist);
  neMet.book(_tree, flatutils::subBranchList(_branches, "neMet"), _whitelist);
  hlt.book(_tree, flatutils::subBranchList(_branches, "hlt"), _whitelist);
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
  TString* name(new TString);
  tree->Branch("name", "TString", &name);

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
    *name = n;
    tree->Fill();
  }

  tree->ResetBranchAddresses();
  delete name;
  return tree;
}

