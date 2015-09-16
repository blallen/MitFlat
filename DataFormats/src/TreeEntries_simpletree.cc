#include "MitFlat/DataFormats/interface/TreeEntries_simpletree.h"
#include "TTree.h"

void
simpletree::Event::setStatus(TTree& _tree, Bool_t _status, BranchList const& _branches/* = BranchList()*/)
{
  if (branchIn(&run, _branches))
    _tree.SetBranchStatus("run", _status);
  if (branchIn(&lumi, _branches))
    _tree.SetBranchStatus("lumi", _status);
  if (branchIn(&event, _branches))
    _tree.SetBranchStatus("event", _status);
  if (branchIn(&weight, _branches))
    _tree.SetBranchStatus("weight", _status);
  if (branchIn(&rho, _branches))
    _tree.SetBranchStatus("rho", _status);
  if (branchIn(&npv, _branches))
    _tree.SetBranchStatus("npv", _status);
  if (branchIn(&genHt, _branches))
    _tree.SetBranchStatus("genHt", _status);
  if (branchIn(&genZpt, _branches))
    _tree.SetBranchStatus("genZpt", _status);
  if (branchIn(&ntau, _branches))
    _tree.SetBranchStatus("ntau", _status);

  if (branchIn(&jets, _branches))
    jets.setStatus(_tree, _status);
  if (branchIn(&photons, _branches))
    photons.setStatus(_tree, _status);
  if (branchIn(&electrons, _branches))
    electrons.setStatus(_tree, _status);
  if (branchIn(&muons, _branches))
    muons.setStatus(_tree, _status);
  if (branchIn(&rawMet, _branches))
    rawMet.setStatus(_tree, _status);
  if (branchIn(&t1Met, _branches))
    t1Met.setStatus(_tree, _status);
  if (branchIn(&t1NoCHSMet, _branches))
    t1NoCHSMet.setStatus(_tree, _status);
  if (branchIn(&eta30Met, _branches))
    eta30Met.setStatus(_tree, _status);
  if (branchIn(&eta30T1Met, _branches))
    eta30T1Met.setStatus(_tree, _status);
  if (branchIn(&eta30T1NoCHSMet, _branches))
    eta30T1NoCHSMet.setStatus(_tree, _status);
  if (branchIn(&nhScaledMet, _branches))
    nhScaledMet.setStatus(_tree, _status);
  if (branchIn(&chMet, _branches))
    chMet.setStatus(_tree, _status);
  if (branchIn(&nhMet, _branches))
    nhMet.setStatus(_tree, _status);
  if (branchIn(&neMet, _branches))
    neMet.setStatus(_tree, _status);
  if (branchIn(&chGt30Met, _branches))
    chGt30Met.setStatus(_tree, _status);
  if (branchIn(&nhGt30Met, _branches))
    nhGt30Met.setStatus(_tree, _status);
  if (branchIn(&neGt30Met, _branches))
    neGt30Met.setStatus(_tree, _status);
  if (branchIn(&hlt, _branches))
    hlt.setStatus(_tree, _status);
}

void
simpletree::Event::setAddress(TTree& _tree, BranchList const& _branches/* = BranchList()*/)
{
  if (branchIn(&run, _branches))
    setStatusAndAddress(_tree, "run", &run);
  if (branchIn(&lumi, _branches))
    setStatusAndAddress(_tree, "lumi", &lumi);
  if (branchIn(&event, _branches))
    setStatusAndAddress(_tree, "event", &event);
  if (branchIn(&weight, _branches))
    setStatusAndAddress(_tree, "weight", &weight);
  if (branchIn(&rho, _branches))
    setStatusAndAddress(_tree, "rho", &rho);
  if (branchIn(&npv, _branches))
    setStatusAndAddress(_tree, "npv", &npv);
  if (branchIn(&genHt, _branches))
    setStatusAndAddress(_tree, "genHt", &genHt);
  if (branchIn(&genZpt, _branches))
    setStatusAndAddress(_tree, "genZpt", &genZpt);
  if (branchIn(&ntau, _branches))
    setStatusAndAddress(_tree, "ntau", &ntau);

  if (branchIn(&jets, _branches))
    jets.setAddress(_tree);
  if (branchIn(&photons, _branches))
    photons.setAddress(_tree);
  if (branchIn(&electrons, _branches))
    electrons.setAddress(_tree);
  if (branchIn(&muons, _branches))
    muons.setAddress(_tree);
  if (branchIn(&rawMet, _branches))
    rawMet.setAddress(_tree);
  if (branchIn(&t1Met, _branches))
    t1Met.setAddress(_tree);
  if (branchIn(&t1NoCHSMet, _branches))
    t1NoCHSMet.setAddress(_tree);
  if (branchIn(&eta30Met, _branches))
    eta30Met.setAddress(_tree);
  if (branchIn(&eta30T1Met, _branches))
    eta30T1Met.setAddress(_tree);
  if (branchIn(&eta30T1NoCHSMet, _branches))
    eta30T1NoCHSMet.setAddress(_tree);
  if (branchIn(&nhScaledMet, _branches))
    nhScaledMet.setAddress(_tree);
  if (branchIn(&chMet, _branches))
    chMet.setAddress(_tree);
  if (branchIn(&nhMet, _branches))
    nhMet.setAddress(_tree);
  if (branchIn(&neMet, _branches))
    neMet.setAddress(_tree);
  if (branchIn(&chGt30Met, _branches))
    chGt30Met.setAddress(_tree);
  if (branchIn(&nhGt30Met, _branches))
    nhGt30Met.setAddress(_tree);
  if (branchIn(&neGt30Met, _branches))
    neGt30Met.setAddress(_tree);
  if (branchIn(&hlt, _branches))
    hlt.setAddress(_tree);
}

void
simpletree::Event::book(TTree& _tree, BranchList const& _branches/* = BranchList()*/)
{
  if (branchIn(&run, _branches))
    _tree.Branch("run", &run, "run/i");
  if (branchIn(&lumi, _branches))
    _tree.Branch("lumi", &lumi, "lumi/i");
  if (branchIn(&event, _branches))
    _tree.Branch("event", &event, "event/i");
  if (branchIn(&weight, _branches))
    _tree.Branch("weight", &weight, "weight/D");
  if (branchIn(&rho, _branches))
    _tree.Branch("rho", &rho, "rho/D");
  if (branchIn(&npv, _branches))
    _tree.Branch("npv", &npv, "npv/s");
  if (branchIn(&genHt, _branches))
    _tree.Branch("genHt", &genHt, "genHt/F");
  if (branchIn(&genZpt, _branches))
    _tree.Branch("genZpt", &genZpt, "genZpt/F");
  if (branchIn(&ntau, _branches))
    _tree.Branch("ntau", &ntau, "ntau/i");

  if (branchIn(&jets, _branches))
    jets.book(_tree);
  if (branchIn(&photons, _branches))
    photons.book(_tree);
  if (branchIn(&electrons, _branches))
    electrons.book(_tree);
  if (branchIn(&muons, _branches))
    muons.book(_tree);
  if (branchIn(&rawMet, _branches))
    rawMet.book(_tree);
  if (branchIn(&t1Met, _branches))
    t1Met.book(_tree);
  if (branchIn(&t1NoCHSMet, _branches))
    t1NoCHSMet.book(_tree);
  if (branchIn(&eta30Met, _branches))
    eta30Met.book(_tree);
  if (branchIn(&eta30T1Met, _branches))
    eta30T1Met.book(_tree);
  if (branchIn(&eta30T1NoCHSMet, _branches))
    eta30T1NoCHSMet.book(_tree);
  if (branchIn(&nhScaledMet, _branches))
    nhScaledMet.book(_tree);
  if (branchIn(&chMet, _branches))
    chMet.book(_tree);
  if (branchIn(&nhMet, _branches))
    nhMet.book(_tree);
  if (branchIn(&neMet, _branches))
    neMet.book(_tree);
  if (branchIn(&chGt30Met, _branches))
    chGt30Met.book(_tree);
  if (branchIn(&nhGt30Met, _branches))
    nhGt30Met.book(_tree);
  if (branchIn(&neGt30Met, _branches))
    neGt30Met.book(_tree);
  if (branchIn(&hlt, _branches))
    hlt.book(_tree);
}

void
simpletree::Weight::setStatus(TTree& _tree, Bool_t _status, BranchList const& _branches/* = BranchList()*/)
{
  if (branchIn(&run, _branches))
    _tree.SetBranchStatus("run", _status);
  if (branchIn(&lumi, _branches))
    _tree.SetBranchStatus("lumi", _status);
  if (branchIn(&event, _branches))
    _tree.SetBranchStatus("event", _status);
  if (branchIn(&weight, _branches))
    _tree.SetBranchStatus("weight", _status);
  if (branchIn(&rho, _branches))
    _tree.SetBranchStatus("rho", _status);

}

void
simpletree::Weight::setAddress(TTree& _tree, BranchList const& _branches/* = BranchList()*/)
{
  if (branchIn(&run, _branches))
    setStatusAndAddress(_tree, "run", &run);
  if (branchIn(&lumi, _branches))
    setStatusAndAddress(_tree, "lumi", &lumi);
  if (branchIn(&event, _branches))
    setStatusAndAddress(_tree, "event", &event);
  if (branchIn(&weight, _branches))
    setStatusAndAddress(_tree, "weight", &weight);
  if (branchIn(&rho, _branches))
    setStatusAndAddress(_tree, "rho", &rho);

}

void
simpletree::Weight::book(TTree& _tree, BranchList const& _branches/* = BranchList()*/)
{
  if (branchIn(&run, _branches))
    _tree.Branch("run", &run, "run/i");
  if (branchIn(&lumi, _branches))
    _tree.Branch("lumi", &lumi, "lumi/i");
  if (branchIn(&event, _branches))
    _tree.Branch("event", &event, "event/i");
  if (branchIn(&weight, _branches))
    _tree.Branch("weight", &weight, "weight/D");
  if (branchIn(&rho, _branches))
    _tree.Branch("rho", &rho, "rho/D");

}

