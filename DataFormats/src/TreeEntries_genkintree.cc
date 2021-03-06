#include "../interface/TreeEntries_genkintree.h"
#include "TTree.h"
#include "TFile.h"
#include "TDirectory.h"

#include <cstring>

genkintree::Event::Event()
{
}

void
genkintree::Event::setStatus(TTree& _tree, Bool_t _status, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  flatutils::setStatus(_tree, "", "weight", _status, _branches, _whitelist);

  partons.setStatus(_tree, _status, flatutils::subBranchList(_branches, "partons"), _whitelist);
  photons.setStatus(_tree, _status, flatutils::subBranchList(_branches, "photons"), _whitelist);
  electrons.setStatus(_tree, _status, flatutils::subBranchList(_branches, "electrons"), _whitelist);
  muons.setStatus(_tree, _status, flatutils::subBranchList(_branches, "muons"), _whitelist);
  neutrinos.setStatus(_tree, _status, flatutils::subBranchList(_branches, "neutrinos"), _whitelist);
  boson.setStatus(_tree, "boson", _status, flatutils::subBranchList(_branches, "boson"), _whitelist);
  jets.setStatus(_tree, _status, flatutils::subBranchList(_branches, "jets"), _whitelist);
  met.setStatus(_tree, _status, flatutils::subBranchList(_branches, "met"), _whitelist);
}

void
genkintree::Event::setAddress(TTree& _tree, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  flatutils::setStatusAndAddress(_tree, "", "weight", &weight, _branches, _whitelist);

  partons.setAddress(_tree, flatutils::subBranchList(_branches, "partons"), _whitelist);
  photons.setAddress(_tree, flatutils::subBranchList(_branches, "photons"), _whitelist);
  electrons.setAddress(_tree, flatutils::subBranchList(_branches, "electrons"), _whitelist);
  muons.setAddress(_tree, flatutils::subBranchList(_branches, "muons"), _whitelist);
  neutrinos.setAddress(_tree, flatutils::subBranchList(_branches, "neutrinos"), _whitelist);
  boson.setAddress(_tree, "boson", flatutils::subBranchList(_branches, "boson"), _whitelist);
  jets.setAddress(_tree, flatutils::subBranchList(_branches, "jets"), _whitelist);
  met.setAddress(_tree, flatutils::subBranchList(_branches, "met"), _whitelist);

  input_ = &_tree;
}

void
genkintree::Event::book(TTree& _tree, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  flatutils::book(_tree, "", "weight", "", 'D', &weight, _branches, _whitelist);

  partons.book(_tree, flatutils::subBranchList(_branches, "partons"), _whitelist);
  photons.book(_tree, flatutils::subBranchList(_branches, "photons"), _whitelist);
  electrons.book(_tree, flatutils::subBranchList(_branches, "electrons"), _whitelist);
  muons.book(_tree, flatutils::subBranchList(_branches, "muons"), _whitelist);
  neutrinos.book(_tree, flatutils::subBranchList(_branches, "neutrinos"), _whitelist);
  boson.book(_tree, "boson", flatutils::subBranchList(_branches, "boson"), _whitelist);
  jets.book(_tree, flatutils::subBranchList(_branches, "jets"), _whitelist);
  met.book(_tree, flatutils::subBranchList(_branches, "met"), _whitelist);
}

void
genkintree::Event::init()
{
  weight = 0.;

  partons.init();
  photons.init();
  electrons.init();
  muons.init();
  neutrinos.init();
  boson.init();
  jets.init();
  met.init();
}

