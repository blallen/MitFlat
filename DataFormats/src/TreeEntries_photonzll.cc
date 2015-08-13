#include "MitFlat/DataFormats/interface/TreeEntries_photonzll.h"
#include "TTree.h"

void
photonzll::Event::setAddress(TTree& _tree)
{
  _tree.SetBranchAddress("run", &run);
  _tree.SetBranchAddress("lumi", &lumi);
  _tree.SetBranchAddress("event", &event);
  _tree.SetBranchAddress("weight", &weight);
  _tree.SetBranchAddress("rho", &rho);
  _tree.SetBranchAddress("genHt", &genHt);
  _tree.SetBranchAddress("genZpt", &genZpt);

  jets.setAddress(_tree, "jets");
  photons.setAddress(_tree, "photons");
  rawMet.setAddress(_tree, "rawMet");
  t1Met.setAddress(_tree, "t1Met");
  t1NoCHSMet.setAddress(_tree, "t1NoCHSMet");
  eta30Met.setAddress(_tree, "eta30Met");
  eta30T1Met.setAddress(_tree, "eta30T1Met");
  eta30T1NoCHSMet.setAddress(_tree, "eta30T1NoCHSMet");
  chMet.setAddress(_tree, "chMet");
  nhMet.setAddress(_tree, "nhMet");
  neMet.setAddress(_tree, "neMet");
  chGt30Met.setAddress(_tree, "chGt30Met");
  nhGt30Met.setAddress(_tree, "nhGt30Met");
  neGt30Met.setAddress(_tree, "neGt30Met");
  z.setAddress(_tree, "z");
}

void
photonzll::Event::book(TTree& _tree)
{
  _tree.Branch("run", &run, "run/i");
  _tree.Branch("lumi", &lumi, "lumi/i");
  _tree.Branch("event", &event, "event/i");
  _tree.Branch("weight", &weight, "weight/D");
  _tree.Branch("rho", &rho, "rho/D");
  _tree.Branch("genHt", &genHt, "genHt/F");
  _tree.Branch("genZpt", &genZpt, "genZpt/F");

  jets.book(_tree, "jets");
  photons.book(_tree, "photons");
  rawMet.book(_tree, "rawMet");
  t1Met.book(_tree, "t1Met");
  t1NoCHSMet.book(_tree, "t1NoCHSMet");
  eta30Met.book(_tree, "eta30Met");
  eta30T1Met.book(_tree, "eta30T1Met");
  eta30T1NoCHSMet.book(_tree, "eta30T1NoCHSMet");
  chMet.book(_tree, "chMet");
  nhMet.book(_tree, "nhMet");
  neMet.book(_tree, "neMet");
  chGt30Met.book(_tree, "chGt30Met");
  nhGt30Met.book(_tree, "nhGt30Met");
  neGt30Met.book(_tree, "neGt30Met");
  z.book(_tree, "z");
}

void
photonzll::Weight::setAddress(TTree& _tree)
{
  _tree.SetBranchAddress("run", &run);
  _tree.SetBranchAddress("lumi", &lumi);
  _tree.SetBranchAddress("event", &event);
  _tree.SetBranchAddress("weight", &weight);
  _tree.SetBranchAddress("rho", &rho);

}

void
photonzll::Weight::book(TTree& _tree)
{
  _tree.Branch("run", &run, "run/i");
  _tree.Branch("lumi", &lumi, "lumi/i");
  _tree.Branch("event", &event, "event/i");
  _tree.Branch("weight", &weight, "weight/D");
  _tree.Branch("rho", &rho, "rho/D");

}

