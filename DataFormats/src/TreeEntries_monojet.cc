#include "MitFlat/DataFormats/interface/TreeEntries_monojet.h"
#include "TTree.h"

void
monojet::Event::setAddress(TTree& _tree)
{
  _tree.SetBranchAddress("runNumber", &runNumber);
  _tree.SetBranchAddress("lumiNumber", &lumiNumber);
  _tree.SetBranchAddress("eventNumber", &eventNumber);

  muons.setAddress(_tree, "muons");
  photons.setAddress(_tree, "photons");
  trigger.setAddress(_tree, "trigger");
  met.setAddress(_tree, "met");
  eg135s.setAddress(_tree, "eg135s");
  eg120s.setAddress(_tree, "eg120s");
  eg165s.setAddress(_tree, "eg165s");
}

void
monojet::Event::book(TTree& _tree)
{
  _tree.Branch("runNumber", &runNumber, "runNumber/i");
  _tree.Branch("lumiNumber", &lumiNumber, "lumiNumber/i");
  _tree.Branch("eventNumber", &eventNumber, "eventNumber/i");

  muons.book(_tree, "muons");
  photons.book(_tree, "photons");
  trigger.book(_tree, "trigger");
  met.book(_tree, "met");
  eg135s.book(_tree, "eg135s");
  eg120s.book(_tree, "eg120s");
  eg165s.book(_tree, "eg165s");
}

