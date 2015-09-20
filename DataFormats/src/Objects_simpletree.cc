#include "MitFlat/DataFormats/interface/Objects_simpletree.h"
#include "MitFlat/DataFormats/interface/Collections_simpletree.h"

#include "TTree.h"

simpletree::Particle::Particle(ParticleCollection& col, UInt_t idx) :
  pt(col.pt[idx]),
  eta(col.eta[idx]),
  phi(col.phi[idx])
{
}

simpletree::Particle::Particle(Particle const& _src) :
  pt(_src.pt),
  eta(_src.eta),
  phi(_src.phi)
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

simpletree::ParticleM::ParticleM(ParticleM const& _src) :
  Particle(_src),
  mass(_src.mass)
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

simpletree::Jet::Jet(Jet const& _src) :
  ParticleM(_src)
{
}

simpletree::Jet&
simpletree::Jet::operator=(Jet const& _rhs)
{
  ParticleM::operator=(_rhs);

  return *this;
}

simpletree::Met::Met(Met const& _src) :
  name_(_src.name_),
  met(_src.met),
  phi(_src.phi),
  sumEt(_src.sumEt)
{
}

void
simpletree::Met::setStatus(TTree& _tree, Bool_t _status, flatutils::BranchList const& _branches/* = {"*"}*/)
{
  flatutils::setStatus(_tree, name_, "met", _status, _branches);
  flatutils::setStatus(_tree, name_, "phi", _status, _branches);
  flatutils::setStatus(_tree, name_, "sumEt", _status, _branches);
}

void
simpletree::Met::setAddress(TTree& _tree, flatutils::BranchList const& _branches/* = {"*"}*/)
{
  flatutils::setStatusAndAddress(_tree, name_, "met", &met, _branches);
  flatutils::setStatusAndAddress(_tree, name_, "phi", &phi, _branches);
  flatutils::setStatusAndAddress(_tree, name_, "sumEt", &sumEt, _branches);
}

void
simpletree::Met::book(TTree& _tree, flatutils::BranchList const& _branches/* = {"*"}*/)
{
  flatutils::book(_tree, name_, "met", "", 'F', &met, _branches);
  flatutils::book(_tree, name_, "phi", "", 'F', &phi, _branches);
  flatutils::book(_tree, name_, "sumEt", "", 'F', &sumEt, _branches);
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
  matchHLT120(col.matchHLT120[idx]),
  matchHLT165HE10(col.matchHLT165HE10[idx]),
  matchHLT175(col.matchHLT175[idx])
{
}

simpletree::Photon::Photon(Photon const& _src) :
  Particle(_src),
  chIso(_src.chIso),
  nhIso(_src.nhIso),
  phIso(_src.phIso),
  sieie(_src.sieie),
  hOverE(_src.hOverE),
  matchedGen(_src.matchedGen),
  hadDecay(_src.hadDecay),
  pixelVeto(_src.pixelVeto),
  csafeVeto(_src.csafeVeto),
  loose(_src.loose),
  medium(_src.medium),
  tight(_src.tight),
  matchHLT120(_src.matchHLT120),
  matchHLT165HE10(_src.matchHLT165HE10),
  matchHLT175(_src.matchHLT175)
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
  matchHLT120 = _rhs.matchHLT120;
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
  loose(col.loose[idx]),
  tight(col.tight[idx])
{
}

simpletree::Lepton::Lepton(Lepton const& _src) :
  ParticleM(_src),
  matchedGen(_src.matchedGen),
  tauDecay(_src.tauDecay),
  hadDecay(_src.hadDecay),
  positive(_src.positive),
  loose(_src.loose),
  tight(_src.tight)
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
  loose = _rhs.loose;
  tight = _rhs.tight;
  return *this;
}

simpletree::Electron::Electron(ElectronCollection& col, UInt_t idx) :
  Lepton(col, idx),
  chIsoPh(col.chIsoPh[idx]),
  nhIsoPh(col.nhIsoPh[idx]),
  phIsoPh(col.phIsoPh[idx]),
  sieie(col.sieie[idx]),
  hOverE(col.hOverE[idx]),
  matchHLT23Loose(col.matchHLT23Loose[idx]),
  matchHLT27Loose(col.matchHLT27Loose[idx])
{
}

simpletree::Electron::Electron(Electron const& _src) :
  Lepton(_src),
  chIsoPh(_src.chIsoPh),
  nhIsoPh(_src.nhIsoPh),
  phIsoPh(_src.phIsoPh),
  sieie(_src.sieie),
  hOverE(_src.hOverE),
  matchHLT23Loose(_src.matchHLT23Loose),
  matchHLT27Loose(_src.matchHLT27Loose)
{
}

simpletree::Electron&
simpletree::Electron::operator=(Electron const& _rhs)
{
  Lepton::operator=(_rhs);

  chIsoPh = _rhs.chIsoPh;
  nhIsoPh = _rhs.nhIsoPh;
  phIsoPh = _rhs.phIsoPh;
  sieie = _rhs.sieie;
  hOverE = _rhs.hOverE;
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

simpletree::Muon::Muon(Muon const& _src) :
  Lepton(_src),
  matchHLT24(_src.matchHLT24),
  matchHLT27(_src.matchHLT27)
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

simpletree::HLT::HLT(HLT const& _src) :
  pass(_src.pass)
{
}

simpletree::HLT&
simpletree::HLT::operator=(HLT const& _rhs)
{
  pass = _rhs.pass;
  return *this;
}

