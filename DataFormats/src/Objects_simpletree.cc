#include "MitFlat/DataFormats/interface/Objects_simpletree.h"

#include "MitFlat/DataFormats/interface/Collections_simpletree.h"

#include "TTree.h"

simpletree::Particle::Particle(ParticleCollection& col, UInt_t idx) :
  pt(col.pt[idx]),
  eta(col.eta[idx]),
  phi(col.phi[idx])
{
}
simpletree::Particle&
simpletree::Particle::operator=(Particle const& _rhs)
{
  pt = _rhs.pt;
  eta = _rhs.eta;
  phi = _rhs.phi;

  return *this;
}

simpletree::ParticleM::ParticleM(ParticleMCollection& col, UInt_t idx) :
  Particle(col, idx),
  mass(col.mass[idx])
{
}
simpletree::ParticleM&
simpletree::ParticleM::operator=(ParticleM const& _rhs)
{
  Particle::operator=(_rhs);

  mass = _rhs.mass;

  return *this;
}

simpletree::Jet::Jet(JetCollection& col, UInt_t idx) :
  ParticleM(col, idx)
{
}
simpletree::Jet&
simpletree::Jet::operator=(Jet const& _rhs)
{
  ParticleM::operator=(_rhs);


  return *this;
}

void
simpletree::Met::setAddress(TTree& _tree, TString const& _objName)
{
  _tree.SetBranchAddress(_objName + ".met", &met);
  _tree.SetBranchAddress(_objName + ".phi", &phi);
  _tree.SetBranchAddress(_objName + ".sumEt", &sumEt);
}

void
simpletree::Met::book(TTree& _tree, TString const& _objName)
{
  _tree.Branch(_objName + ".met", &met, "met/F");
  _tree.Branch(_objName + ".phi", &phi, "phi/F");
  _tree.Branch(_objName + ".sumEt", &sumEt, "sumEt/F");
}

simpletree::Met&
simpletree::Met::operator=(Met const& _rhs)
{
  met = _rhs.met;
  phi = _rhs.phi;
  sumEt = _rhs.sumEt;

  return *this;
}

simpletree::Photon::Photon(PhotonCollection& col, UInt_t idx) :
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
simpletree::Photon&
simpletree::Photon::operator=(Photon const& _rhs)
{
  Particle::operator=(_rhs);

  chIso = _rhs.chIso;
  nhIso = _rhs.nhIso;
  phIso = _rhs.phIso;
  sieie = _rhs.sieie;
  hOverE = _rhs.hOverE;
  pixelVeto = _rhs.pixelVeto;
  csafeVeto = _rhs.csafeVeto;
  isLoose = _rhs.isLoose;
  isMedium = _rhs.isMedium;
  isTight = _rhs.isTight;

  return *this;
}

simpletree::Electron::Electron(ElectronCollection& col, UInt_t idx) :
  ParticleM(col, idx),
  positive(col.positive[idx]),
  tight(col.tight[idx])
{
}
simpletree::Electron&
simpletree::Electron::operator=(Electron const& _rhs)
{
  ParticleM::operator=(_rhs);

  positive = _rhs.positive;
  tight = _rhs.tight;

  return *this;
}

simpletree::Muon::Muon(MuonCollection& col, UInt_t idx) :
  ParticleM(col, idx),
  positive(col.positive[idx]),
  tight(col.tight[idx])
{
}
simpletree::Muon&
simpletree::Muon::operator=(Muon const& _rhs)
{
  ParticleM::operator=(_rhs);

  positive = _rhs.positive;
  tight = _rhs.tight;

  return *this;
}

