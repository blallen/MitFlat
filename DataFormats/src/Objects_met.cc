#include "MitFlat/DataFormats/interface/Objects_met.h"

#include "MitFlat/DataFormats/interface/Collections_met.h"

#include "TTree.h"

void
met::Met::setAddress(TTree& _tree, TString const& _objName)
{
  _tree.SetBranchAddress(_objName + ".met", &met);
  _tree.SetBranchAddress(_objName + ".phi", &phi);
  _tree.SetBranchAddress(_objName + ".sumEt", &sumEt);
}

void
met::Met::book(TTree& _tree, TString const& _objName)
{
  _tree.Branch(_objName + ".met", &met, "met/F");
  _tree.Branch(_objName + ".phi", &phi, "phi/F");
  _tree.Branch(_objName + ".sumEt", &sumEt, "sumEt/F");
}

