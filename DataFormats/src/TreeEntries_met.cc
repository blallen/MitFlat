#include "MitFlat/DataFormats/interface/TreeEntries_met.h"
#include "TTree.h"

void
met::Event::setAddress(TTree& _tree)
{
  _tree.SetBranchAddress("run", &run);
  _tree.SetBranchAddress("event", &event);

  rawMet.setAddress(_tree, "rawMet");
  type1Met.setAddress(_tree, "type1Met");
}

void
met::Event::book(TTree& _tree)
{
  _tree.Branch("run", &run, "run/i");
  _tree.Branch("event", &event, "event/i");

  rawMet.book(_tree, "rawMet");
  type1Met.book(_tree, "type1Met");
}

