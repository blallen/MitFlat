#include "MitFlat/DataFormats/interface/Objects_photonzll.h"

#include "MitFlat/DataFormats/interface/Collections_photonzll.h"

#include "TTree.h"

photonzll::Particle::Particle(ParticleCollection& col, UInt_t idx) :
  pt(col.pt[idx]),
  eta(col.eta[idx]),
  phi(col.phi[idx])
{
}

photonzll::ParticleM::ParticleM(ParticleMCollection& col, UInt_t idx) :
  Particle(col, idx),
  mass(col.mass[idx])
{
}

photonzll::Jet::Jet(JetCollection& col, UInt_t idx) :
  ParticleM(col, idx)
{
}

void
photonzll::Met::setAddress(TTree& _tree, TString const& _objName)
{
  _tree.SetBranchAddress(_objName + ".met", &met);
  _tree.SetBranchAddress(_objName + ".phi", &phi);
  _tree.SetBranchAddress(_objName + ".sumEt", &sumEt);
}

void
photonzll::Met::book(TTree& _tree, TString const& _objName)
{
  _tree.Branch(_objName + ".met", &met, "met/F");
  _tree.Branch(_objName + ".phi", &phi, "phi/F");
  _tree.Branch(_objName + ".sumEt", &sumEt, "sumEt/F");
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
  _tree.SetBranchAddress(_objName + ".pt0", &pt0);
  _tree.SetBranchAddress(_objName + ".eta0", &eta0);
  _tree.SetBranchAddress(_objName + ".phi0", &phi0);
  _tree.SetBranchAddress(_objName + ".pt1", &pt1);
  _tree.SetBranchAddress(_objName + ".eta1", &eta1);
  _tree.SetBranchAddress(_objName + ".phi1", &phi1);
}

void
photonzll::ZCand::book(TTree& _tree, TString const& _objName)
{
  _tree.Branch(_objName + ".pt0", &pt0, "pt0/F");
  _tree.Branch(_objName + ".eta0", &eta0, "eta0/F");
  _tree.Branch(_objName + ".phi0", &phi0, "phi0/F");
  _tree.Branch(_objName + ".pt1", &pt1, "pt1/F");
  _tree.Branch(_objName + ".eta1", &eta1, "eta1/F");
  _tree.Branch(_objName + ".phi1", &phi1, "phi1/F");
}

