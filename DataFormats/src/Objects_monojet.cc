#include "MitFlat/DataFormats/interface/Objects_monojet.h"

#include "MitFlat/DataFormats/interface/Collections_monojet.h"

#include "TTree.h"

monojet::Particle::Particle(ParticleCollection& col, UInt_t idx) :
  pt(col.pt[idx]),
  eta(col.eta[idx]),
  phi(col.phi[idx])
{
}

monojet::Jet::Jet(JetCollection& col, UInt_t idx) :
  Particle(col, idx),
  btag(col.btag[idx]),
  chFrac(col.chFrac[idx]),
  nhFrac(col.nhFrac[idx]),
  neFrac(col.neFrac[idx])
{
}

void
monojet::Met::setAddress(TTree& _tree, TString const& _objName)
{
  _tree.SetBranchAddress(_objName + ".met", &met);
  _tree.SetBranchAddress(_objName + ".phi", &phi);
  _tree.SetBranchAddress(_objName + ".metNoMu", &metNoMu);
  _tree.SetBranchAddress(_objName + ".phiNoMu", &phiNoMu);
}

void
monojet::Met::book(TTree& _tree, TString const& _objName)
{
  _tree.Branch(_objName + ".met", &met, "met/F");
  _tree.Branch(_objName + ".phi", &phi, "phi/F");
  _tree.Branch(_objName + ".metNoMu", &metNoMu, "metNoMu/F");
  _tree.Branch(_objName + ".phiNoMu", &phiNoMu, "phiNoMu/F");
}

monojet::Electron::Electron(ElectronCollection& col, UInt_t idx) :
  Particle(col, idx)
{
}

monojet::Muon::Muon(MuonCollection& col, UInt_t idx) :
  Particle(col, idx)
{
}

monojet::Tau::Tau(TauCollection& col, UInt_t idx) :
  Particle(col, idx),
  disc(col.disc[idx])
{
}

monojet::Photon::Photon(PhotonCollection& col, UInt_t idx) :
  Particle(col, idx)
{
}

void
monojet::Trigger::setAddress(TTree& _tree, TString const& _objName)
{
  _tree.SetBranchAddress(_objName + ".met90mht90", &met90mht90);
  _tree.SetBranchAddress(_objName + ".met120mht120", &met120mht120);
}

void
monojet::Trigger::book(TTree& _tree, TString const& _objName)
{
  _tree.Branch(_objName + ".met90mht90", &met90mht90, "met90mht90/O");
  _tree.Branch(_objName + ".met120mht120", &met120mht120, "met120mht120/O");
}

monojet::TriggerObj::TriggerObj(TriggerObjCollection& col, UInt_t idx) :
  Particle(col, idx)
{
}

