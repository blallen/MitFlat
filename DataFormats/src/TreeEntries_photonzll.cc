#include "MitFlat/DataFormats/interface/TreeEntries_photonzll.h"
#include "TTree.h"

void
photonzll::Event::setAddress(TTree& _tree)
{
  _tree.SetBranchAddress("run", &run);
  _tree.SetBranchAddress("lumi", &lumi);
  _tree.SetBranchAddress("event", &event);
  _tree.SetBranchAddress("weight", &weight);

  jets.setAddress(_tree, "jets");
  photons.setAddress(_tree, "photons");
  rawMet.setAddress(_tree, "rawMet");
  t1Met.setAddress(_tree, "t1Met");
  eta30Met.setAddress(_tree, "eta30Met");
  eta30T1Met.setAddress(_tree, "eta30T1Met");
  chMet.setAddress(_tree, "chMet");
  nhMet.setAddress(_tree, "nhMet");
  neMet.setAddress(_tree, "neMet");
  z.setAddress(_tree, "z");
}

void
photonzll::Event::book(TTree& _tree)
{
  _tree.Branch("run", &run, "run/i");
  _tree.Branch("lumi", &lumi, "lumi/i");
  _tree.Branch("event", &event, "event/i");
  _tree.Branch("weight", &weight, "weight/D");

  jets.book(_tree, "jets");
  photons.book(_tree, "photons");
  rawMet.book(_tree, "rawMet");
  t1Met.book(_tree, "t1Met");
  eta30Met.book(_tree, "eta30Met");
  eta30T1Met.book(_tree, "eta30T1Met");
  chMet.book(_tree, "chMet");
  nhMet.book(_tree, "nhMet");
  neMet.book(_tree, "neMet");
  z.book(_tree, "z");
}

void
photonzll::Weight::setAddress(TTree& _tree)
{
  _tree.SetBranchAddress("run", &run);
  _tree.SetBranchAddress("lumi", &lumi);
  _tree.SetBranchAddress("event", &event);
  _tree.SetBranchAddress("weight", &weight);

}

void
photonzll::Weight::book(TTree& _tree)
{
  _tree.Branch("run", &run, "run/i");
  _tree.Branch("lumi", &lumi, "lumi/i");
  _tree.Branch("event", &event, "event/i");
  _tree.Branch("weight", &weight, "weight/D");

}

