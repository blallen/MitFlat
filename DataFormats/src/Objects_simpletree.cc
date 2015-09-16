#include "MitFlat/DataFormats/interface/Objects_simpletree.h"

#include "MitFlat/DataFormats/interface/Collections_simpletree.h"

#include "TTree.h"

#include <algorithm>

Bool_t
simpletree::branchIn(void* _bPtr, BranchList const& _bList)
{
  return _bList.size() == 0 || std::find(_bList.begin(), _bList.end(), _bPtr) != _bList.end();
}

void
simpletree::setStatusAndAddress(TTree& _tree, TString const& _bName, void* _bPtr)
{
  if (!_tree.GetBranchStatus(_bName))
    _tree.SetBranchStatus(_bName, true);
  _tree.SetBranchAddress(_bName, _bPtr);
}

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
simpletree::Met::setStatus(TTree& _tree, Bool_t _status, BranchList const& _branches/* = BranchList()*/)
{
  if (branchIn(&met, _branches))
    _tree.SetBranchStatus(name_ + ".met", _status);
  if (branchIn(&phi, _branches))
    _tree.SetBranchStatus(name_ + ".phi", _status);
  if (branchIn(&sumEt, _branches))
    _tree.SetBranchStatus(name_ + ".sumEt", _status);
}

void
simpletree::Met::setAddress(TTree& _tree, BranchList const& _branches/* = BranchList()*/)
{
  if (branchIn(&met, _branches))
    setStatusAndAddress(_tree, name_ + ".met", &met);
  if (branchIn(&phi, _branches))
    setStatusAndAddress(_tree, name_ + ".phi", &phi);
  if (branchIn(&sumEt, _branches))
    setStatusAndAddress(_tree, name_ + ".sumEt", &sumEt);
}

void
simpletree::Met::book(TTree& _tree, BranchList const& _branches/* = BranchList()*/)
{
  if (branchIn(&met, _branches))
    _tree.Branch(name_ + ".met", &met, "met/F");
  if (branchIn(&phi, _branches))
    _tree.Branch(name_ + ".phi", &phi, "phi/F");
  if (branchIn(&sumEt, _branches))
    _tree.Branch(name_ + ".sumEt", &sumEt, "sumEt/F");
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
  matchedGen(col.matchedGen[idx]),
  hadDecay(col.hadDecay[idx]),
  pixelVeto(col.pixelVeto[idx]),
  csafeVeto(col.csafeVeto[idx]),
  loose(col.loose[idx]),
  medium(col.medium[idx]),
  tight(col.tight[idx]),
  matchHLT165HE10(col.matchHLT165HE10[idx]),
  matchHLT175(col.matchHLT175[idx])
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
  matchedGen = _rhs.matchedGen;
  hadDecay = _rhs.hadDecay;
  pixelVeto = _rhs.pixelVeto;
  csafeVeto = _rhs.csafeVeto;
  loose = _rhs.loose;
  medium = _rhs.medium;
  tight = _rhs.tight;
  matchHLT165HE10 = _rhs.matchHLT165HE10;
  matchHLT175 = _rhs.matchHLT175;

  return *this;
}

simpletree::Lepton::Lepton(LeptonCollection& col, UInt_t idx) :
  ParticleM(col, idx),
  matchedGen(col.matchedGen[idx]),
  tauDecay(col.tauDecay[idx]),
  hadDecay(col.hadDecay[idx]),
  positive(col.positive[idx]),
  tight(col.tight[idx])
{
}
simpletree::Lepton&
simpletree::Lepton::operator=(Lepton const& _rhs)
{
  ParticleM::operator=(_rhs);

  matchedGen = _rhs.matchedGen;
  tauDecay = _rhs.tauDecay;
  hadDecay = _rhs.hadDecay;
  positive = _rhs.positive;
  tight = _rhs.tight;

  return *this;
}

simpletree::Electron::Electron(ElectronCollection& col, UInt_t idx) :
  Lepton(col, idx),
  matchHLT23Loose(col.matchHLT23Loose[idx]),
  matchHLT27Loose(col.matchHLT27Loose[idx])
{
}
simpletree::Electron&
simpletree::Electron::operator=(Electron const& _rhs)
{
  Lepton::operator=(_rhs);

  matchHLT23Loose = _rhs.matchHLT23Loose;
  matchHLT27Loose = _rhs.matchHLT27Loose;

  return *this;
}

simpletree::Muon::Muon(MuonCollection& col, UInt_t idx) :
  Lepton(col, idx),
  matchHLT24(col.matchHLT24[idx]),
  matchHLT27(col.matchHLT27[idx])
{
}
simpletree::Muon&
simpletree::Muon::operator=(Muon const& _rhs)
{
  Lepton::operator=(_rhs);

  matchHLT24 = _rhs.matchHLT24;
  matchHLT27 = _rhs.matchHLT27;

  return *this;
}

simpletree::HLT::HLT(HLTCollection& col, UInt_t idx) :
  pass(col.pass[idx])
{
}
simpletree::HLT&
simpletree::HLT::operator=(HLT const& _rhs)
{
  pass = _rhs.pass;

  return *this;
}

