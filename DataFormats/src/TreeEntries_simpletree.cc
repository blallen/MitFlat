#include "../interface/TreeEntries_simpletree.h"
#include "TTree.h"
#include "TFile.h"
#include "TDirectory.h"

#include <cstring>

simpletree::Event::Event()
{
}

void
simpletree::Event::setStatus(TTree& _tree, Bool_t _status, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  flatutils::setStatus(_tree, "", "run", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, "", "lumi", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, "", "event", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, "", "weight", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, "", "scaleReweight", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, "", "pdfDW", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, "", "rho", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, "", "npvTrue", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, "", "npv", _status, _branches, _whitelist);

  partons.setStatus(_tree, _status, flatutils::subBranchList(_branches, "partons"), _whitelist);
  promptFinalStates.setStatus(_tree, _status, flatutils::subBranchList(_branches, "promptFinalStates"), _whitelist);
  jets.setStatus(_tree, _status, flatutils::subBranchList(_branches, "jets"), _whitelist);
  genJets.setStatus(_tree, _status, flatutils::subBranchList(_branches, "genJets"), _whitelist);
  photons.setStatus(_tree, _status, flatutils::subBranchList(_branches, "photons"), _whitelist);
  electrons.setStatus(_tree, _status, flatutils::subBranchList(_branches, "electrons"), _whitelist);
  muons.setStatus(_tree, _status, flatutils::subBranchList(_branches, "muons"), _whitelist);
  taus.setStatus(_tree, _status, flatutils::subBranchList(_branches, "taus"), _whitelist);
  superClusters.setStatus(_tree, _status, flatutils::subBranchList(_branches, "superClusters"), _whitelist);
  rawMet.setStatus(_tree, _status, flatutils::subBranchList(_branches, "rawMet"), _whitelist);
  t1Met.setStatus(_tree, _status, flatutils::subBranchList(_branches, "t1Met"), _whitelist);
  caloMet.setStatus(_tree, _status, flatutils::subBranchList(_branches, "caloMet"), _whitelist);
  genMet.setStatus(_tree, _status, flatutils::subBranchList(_branches, "genMet"), _whitelist);
  hltBits.setStatus(_tree, _status, flatutils::subBranchList(_branches, "hltBits"), _whitelist);
  metFilters.setStatus(_tree, _status, flatutils::subBranchList(_branches, "metFilters"), _whitelist);
  vertices.setStatus(_tree, _status, flatutils::subBranchList(_branches, "vertices"), _whitelist);
}

void
simpletree::Event::setAddress(TTree& _tree, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  flatutils::setStatusAndAddress(_tree, "", "run", &run, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, "", "lumi", &lumi, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, "", "event", &event, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, "", "weight", &weight, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, "", "scaleReweight", scaleReweight, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, "", "pdfDW", &pdfDW, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, "", "rho", &rho, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, "", "npvTrue", &npvTrue, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, "", "npv", &npv, _branches, _whitelist);

  partons.setAddress(_tree, flatutils::subBranchList(_branches, "partons"), _whitelist);
  promptFinalStates.setAddress(_tree, flatutils::subBranchList(_branches, "promptFinalStates"), _whitelist);
  jets.setAddress(_tree, flatutils::subBranchList(_branches, "jets"), _whitelist);
  genJets.setAddress(_tree, flatutils::subBranchList(_branches, "genJets"), _whitelist);
  photons.setAddress(_tree, flatutils::subBranchList(_branches, "photons"), _whitelist);
  electrons.setAddress(_tree, flatutils::subBranchList(_branches, "electrons"), _whitelist);
  muons.setAddress(_tree, flatutils::subBranchList(_branches, "muons"), _whitelist);
  taus.setAddress(_tree, flatutils::subBranchList(_branches, "taus"), _whitelist);
  superClusters.setAddress(_tree, flatutils::subBranchList(_branches, "superClusters"), _whitelist);
  rawMet.setAddress(_tree, flatutils::subBranchList(_branches, "rawMet"), _whitelist);
  t1Met.setAddress(_tree, flatutils::subBranchList(_branches, "t1Met"), _whitelist);
  caloMet.setAddress(_tree, flatutils::subBranchList(_branches, "caloMet"), _whitelist);
  genMet.setAddress(_tree, flatutils::subBranchList(_branches, "genMet"), _whitelist);
  hltBits.setAddress(_tree, flatutils::subBranchList(_branches, "hltBits"), _whitelist);
  metFilters.setAddress(_tree, flatutils::subBranchList(_branches, "metFilters"), _whitelist);
  vertices.setAddress(_tree, flatutils::subBranchList(_branches, "vertices"), _whitelist);

  input_ = &_tree;
}

void
simpletree::Event::book(TTree& _tree, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  flatutils::book(_tree, "", "run", "", 'i', &run, _branches, _whitelist);
  flatutils::book(_tree, "", "lumi", "", 'i', &lumi, _branches, _whitelist);
  flatutils::book(_tree, "", "event", "", 'i', &event, _branches, _whitelist);
  flatutils::book(_tree, "", "weight", "", 'D', &weight, _branches, _whitelist);
  flatutils::book(_tree, "", "scaleReweight", "[6]", 'F', scaleReweight, _branches, _whitelist);
  flatutils::book(_tree, "", "pdfDW", "", 'F', &pdfDW, _branches, _whitelist);
  flatutils::book(_tree, "", "rho", "", 'F', &rho, _branches, _whitelist);
  flatutils::book(_tree, "", "npvTrue", "", 'F', &npvTrue, _branches, _whitelist);
  flatutils::book(_tree, "", "npv", "", 's', &npv, _branches, _whitelist);

  partons.book(_tree, flatutils::subBranchList(_branches, "partons"), _whitelist);
  promptFinalStates.book(_tree, flatutils::subBranchList(_branches, "promptFinalStates"), _whitelist);
  jets.book(_tree, flatutils::subBranchList(_branches, "jets"), _whitelist);
  genJets.book(_tree, flatutils::subBranchList(_branches, "genJets"), _whitelist);
  photons.book(_tree, flatutils::subBranchList(_branches, "photons"), _whitelist);
  electrons.book(_tree, flatutils::subBranchList(_branches, "electrons"), _whitelist);
  muons.book(_tree, flatutils::subBranchList(_branches, "muons"), _whitelist);
  taus.book(_tree, flatutils::subBranchList(_branches, "taus"), _whitelist);
  superClusters.book(_tree, flatutils::subBranchList(_branches, "superClusters"), _whitelist);
  rawMet.book(_tree, flatutils::subBranchList(_branches, "rawMet"), _whitelist);
  t1Met.book(_tree, flatutils::subBranchList(_branches, "t1Met"), _whitelist);
  caloMet.book(_tree, flatutils::subBranchList(_branches, "caloMet"), _whitelist);
  genMet.book(_tree, flatutils::subBranchList(_branches, "genMet"), _whitelist);
  hltBits.book(_tree, flatutils::subBranchList(_branches, "hltBits"), _whitelist);
  metFilters.book(_tree, flatutils::subBranchList(_branches, "metFilters"), _whitelist);
  vertices.book(_tree, flatutils::subBranchList(_branches, "vertices"), _whitelist);
}

void
simpletree::Event::init()
{
  run = 0;
  lumi = 0;
  event = 0;
  weight = 0.;
  std::fill(scaleReweight, scaleReweight + 6, 0.);
  pdfDW = 0.;
  rho = 0.;
  npvTrue = 0.;
  npv = 0;

  partons.init();
  promptFinalStates.init();
  jets.init();
  genJets.init();
  photons.init();
  electrons.init();
  muons.init();
  taus.init();
  superClusters.init();
  rawMet.init();
  t1Met.init();
  caloMet.init();
  genMet.init();
  hltBits.init();
  metFilters.init();
  vertices.init();
}

simpletree::Run::Run()
{
}

void
simpletree::Run::setStatus(TTree& _tree, Bool_t _status, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  flatutils::setStatus(_tree, "", "run", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, "", "hltMenu", _status, _branches, _whitelist);

}

void
simpletree::Run::setAddress(TTree& _tree, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  flatutils::setStatusAndAddress(_tree, "", "run", &run, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, "", "hltMenu", &hltMenu, _branches, _whitelist);


  input_ = &_tree;
}

void
simpletree::Run::book(TTree& _tree, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  flatutils::book(_tree, "", "run", "", 'i', &run, _branches, _whitelist);
  flatutils::book(_tree, "", "hltMenu", "", 'i', &hltMenu, _branches, _whitelist);

}

void
simpletree::Run::init()
{
  run = 0;
  hltMenu = 0;

}

TTree*
simpletree::makePhotonL1ObjectTree()
{
  auto* tree(new TTree("PhotonL1Object", "PhotonL1Object"));
  char name[1024];
  tree->Branch("name", name, "name/C");

  TString names[] = {
    "fSEG34IorSEG40",
    "fSEG40IorSJet200",
    "fSEG34IorSEG40IorSJet200",
    "fSEG24",
    "fSEG30",
    "fSEG40",
    "nPhotonL1Objects"
  };

  for (auto&& n : names) {
    std::strcpy(name, n.Data());
    tree->Fill();
  }

  tree->ResetBranchAddresses();
  return tree;
}

TTree*
simpletree::makePhotonHLTObjectTree()
{
  auto* tree(new TTree("PhotonHLTObject", "PhotonHLTObject"));
  char name[1024];
  tree->Branch("name", name, "name/C");

  TString names[] = {
    "fPh120",
    "fPh135",
    "fPh165HE10",
    "fPh175",
    "fPh22EBR9Iso",
    "fPh36EBR9Iso",
    "fPh50EBR9Iso",
    "fPh75EBR9Iso",
    "fPh90EBR9Iso",
    "fPh120EBR9Iso",
    "nPhotonHLTObjects"
  };

  for (auto&& n : names) {
    std::strcpy(name, n.Data());
    tree->Fill();
  }

  tree->ResetBranchAddresses();
  return tree;
}

TTree*
simpletree::makeElectronHLTObjectTree()
{
  auto* tree(new TTree("ElectronHLTObject", "ElectronHLTObject"));
  char name[1024];
  tree->Branch("name", name, "name/C");

  TString names[] = {
    "fEl27ERLoose",
    "fEl27Tight",
    "fEl120Ph",
    "fEl135Ph",
    "fEl165HE10Ph",
    "fEl175Ph",
    "fEl22EBR9IsoPh",
    "fEl36EBR9IsoPh",
    "fEl50EBR9IsoPh",
    "fEl75EBR9IsoPh",
    "fEl90EBR9IsoPh",
    "fEl120EBR9IsoPh",
    "nElectronHLTObjects"
  };

  for (auto&& n : names) {
    std::strcpy(name, n.Data());
    tree->Fill();
  }

  tree->ResetBranchAddresses();
  return tree;
}

TTree*
simpletree::makeMuonHLTObjectTree()
{
  auto* tree(new TTree("MuonHLTObject", "MuonHLTObject"));
  char name[1024];
  tree->Branch("name", name, "name/C");

  TString names[] = {
    "fMu20",
    "fMuTrk20",
    "fMu24",
    "fMu27",
    "nMuonHLTObjects"
  };

  for (auto&& n : names) {
    std::strcpy(name, n.Data());
    tree->Fill();
  }

  tree->ResetBranchAddresses();
  return tree;
}

