#include "MitFlat/DataFormats/interface/Objects_mugamma.h"

#include "MitFlat/DataFormats/interface/Collections_mugamma.h"

#include "TTree.h"

mugamma::Particle::Particle(ParticleCollection& col, UInt_t idx) :
  pt(col.pt[idx]),
  eta(col.eta[idx]),
  phi(col.phi[idx])
{
}

mugamma::ParticleM::ParticleM(ParticleMCollection& col, UInt_t idx) :
  Particle(col, idx),
  mass(col.mass[idx])
{
}

mugamma::Jet::Jet(JetCollection& col, UInt_t idx) :
  ParticleM(col, idx)
{
}

void
mugamma::Met::setAddress(TTree& _tree, TString const& _objName)
{
  _tree.SetBranchAddress(_objName + ".met", &met);
  _tree.SetBranchAddress(_objName + ".phi", &phi);
  _tree.SetBranchAddress(_objName + ".sumEt", &sumEt);
}

void
mugamma::Met::book(TTree& _tree, TString const& _objName)
{
  _tree.Branch(_objName + ".met", &met, "met/F");
  _tree.Branch(_objName + ".phi", &phi, "phi/F");
  _tree.Branch(_objName + ".sumEt", &sumEt, "sumEt/F");
}

mugamma::Photon::Photon(PhotonCollection& col, UInt_t idx) :
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

mugamma::Electron::Electron(ElectronCollection& col, UInt_t idx) :
  ParticleM(col, idx),
  tight(col.tight[idx])
{
}

mugamma::Muon::Muon(MuonCollection& col, UInt_t idx) :
  ParticleM(col, idx),
  tight(col.tight[idx])
{
}

