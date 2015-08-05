#include "MitFlat/DataFormats/interface/Objects_photonzll.h"

#include "MitFlat/DataFormats/interface/Collections_photonzll.h"

#include "TTree.h"

photonzll::Particle::Particle(ParticleCollection& col, UInt_t idx) :
  pt(col.pt[idx]),
  eta(col.eta[idx]),
  phi(col.phi[idx])
{
}

photonzll::Jet::Jet(JetCollection& col, UInt_t idx) :
  Particle(col, idx)
{
}

void
photonzll::Met::setAddress(TTree& _tree, TString const& _objName)
{
  _tree.SetBranchAddress(_objName + ".met", &met);
  _tree.SetBranchAddress(_objName + ".phi", &phi);
}

void
photonzll::Met::book(TTree& _tree, TString const& _objName)
{
  _tree.Branch(_objName + ".met", &met, "met/F");
  _tree.Branch(_objName + ".phi", &phi, "phi/F");
}

photonzll::Photon::Photon(PhotonCollection& col, UInt_t idx) :
  Particle(col, idx),
  chIso(col.chIso[idx]),
  nhIso(col.nhIso[idx]),
  phIso(col.phIso[idx]),
  sieie(col.sieie[idx]),
  hOverE(col.hOverE[idx]),
  pixelVeto(col.pixelVeto[idx]),
  csafeVeto(col.csafeVeto[idx]),
  isLoose(col.isLoose[idx]),
  isMedium(col.isMedium[idx]),
  isTight(col.isTight[idx])
{
}

void
photonzll::ZCand::setAddress(TTree& _tree, TString const& _objName)
{
  _tree.SetBranchAddress(_objName + ".pt", &pt);
  _tree.SetBranchAddress(_objName + ".eta", &eta);
  _tree.SetBranchAddress(_objName + ".phi", &phi);
}

void
photonzll::ZCand::book(TTree& _tree, TString const& _objName)
{
  _tree.Branch(_objName + ".pt", &pt, "pt/F");
  _tree.Branch(_objName + ".eta", &eta, "eta/F");
  _tree.Branch(_objName + ".phi", &phi, "phi/F");
}

