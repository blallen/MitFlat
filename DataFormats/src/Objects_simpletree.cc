#include "MitFlat/DataFormats/interface/Objects_simpletree.h"
#include "TTree.h"

void
simpletree::Particle::array_data::setStatus(TTree& _tree, TString const& _name, Bool_t _status, flatutils::BranchList const& _branches/* = {"*"}*/)
{
  flatutils::setStatus(_tree, _name, "pt", _status, _branches);
  flatutils::setStatus(_tree, _name, "eta", _status, _branches);
  flatutils::setStatus(_tree, _name, "phi", _status, _branches);
}

void
simpletree::Particle::array_data::setAddress(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/)
{
  flatutils::setStatusAndAddress(_tree, _name, "pt", pt, _branches);
  flatutils::setStatusAndAddress(_tree, _name, "eta", eta, _branches);
  flatutils::setStatusAndAddress(_tree, _name, "phi", phi, _branches);
}

void
simpletree::Particle::array_data::book(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/)
{
  flatutils::book(_tree, _name, "pt", "", 'F', pt, _branches);
  flatutils::book(_tree, _name, "eta", "", 'F', eta, _branches);
  flatutils::book(_tree, _name, "phi", "", 'F', phi, _branches);
}

simpletree::Particle::Particle(array_data& _data, UInt_t _idx) :
  pt(_data.pt[_idx]),
  eta(_data.eta[_idx]),
  phi(_data.phi[_idx])
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

void
simpletree::ParticleM::array_data::setStatus(TTree& _tree, TString const& _name, Bool_t _status, flatutils::BranchList const& _branches/* = {"*"}*/)
{
  Particle::array_data::setStatus(_tree, _name, _status, _branches);

  flatutils::setStatus(_tree, _name, "mass", _status, _branches);
}

void
simpletree::ParticleM::array_data::setAddress(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/)
{
  Particle::array_data::setAddress(_tree, _name, _branches);

  flatutils::setStatusAndAddress(_tree, _name, "mass", mass, _branches);
}

void
simpletree::ParticleM::array_data::book(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/)
{
  Particle::array_data::book(_tree, _name, _branches);

  flatutils::book(_tree, _name, "mass", "", 'F', mass, _branches);
}

simpletree::ParticleM::ParticleM(array_data& _data, UInt_t _idx) :
  Particle(_data, _idx),
  mass(_data.mass[_idx])
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

simpletree::Jet::Jet(array_data& _data, UInt_t _idx) :
  ParticleM(_data, _idx)
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

void
simpletree::Photon::array_data::setStatus(TTree& _tree, TString const& _name, Bool_t _status, flatutils::BranchList const& _branches/* = {"*"}*/)
{
  Particle::array_data::setStatus(_tree, _name, _status, _branches);

  flatutils::setStatus(_tree, _name, "chIso", _status, _branches);
  flatutils::setStatus(_tree, _name, "nhIso", _status, _branches);
  flatutils::setStatus(_tree, _name, "phIso", _status, _branches);
  flatutils::setStatus(_tree, _name, "sieie", _status, _branches);
  flatutils::setStatus(_tree, _name, "hOverE", _status, _branches);
  flatutils::setStatus(_tree, _name, "matchedGen", _status, _branches);
  flatutils::setStatus(_tree, _name, "hadDecay", _status, _branches);
  flatutils::setStatus(_tree, _name, "pixelVeto", _status, _branches);
  flatutils::setStatus(_tree, _name, "csafeVeto", _status, _branches);
  flatutils::setStatus(_tree, _name, "loose", _status, _branches);
  flatutils::setStatus(_tree, _name, "medium", _status, _branches);
  flatutils::setStatus(_tree, _name, "tight", _status, _branches);
  flatutils::setStatus(_tree, _name, "matchHLT120", _status, _branches);
  flatutils::setStatus(_tree, _name, "matchHLT165HE10", _status, _branches);
  flatutils::setStatus(_tree, _name, "matchHLT175", _status, _branches);
}

void
simpletree::Photon::array_data::setAddress(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/)
{
  Particle::array_data::setAddress(_tree, _name, _branches);

  flatutils::setStatusAndAddress(_tree, _name, "chIso", chIso, _branches);
  flatutils::setStatusAndAddress(_tree, _name, "nhIso", nhIso, _branches);
  flatutils::setStatusAndAddress(_tree, _name, "phIso", phIso, _branches);
  flatutils::setStatusAndAddress(_tree, _name, "sieie", sieie, _branches);
  flatutils::setStatusAndAddress(_tree, _name, "hOverE", hOverE, _branches);
  flatutils::setStatusAndAddress(_tree, _name, "matchedGen", matchedGen, _branches);
  flatutils::setStatusAndAddress(_tree, _name, "hadDecay", hadDecay, _branches);
  flatutils::setStatusAndAddress(_tree, _name, "pixelVeto", pixelVeto, _branches);
  flatutils::setStatusAndAddress(_tree, _name, "csafeVeto", csafeVeto, _branches);
  flatutils::setStatusAndAddress(_tree, _name, "loose", loose, _branches);
  flatutils::setStatusAndAddress(_tree, _name, "medium", medium, _branches);
  flatutils::setStatusAndAddress(_tree, _name, "tight", tight, _branches);
  flatutils::setStatusAndAddress(_tree, _name, "matchHLT120", matchHLT120, _branches);
  flatutils::setStatusAndAddress(_tree, _name, "matchHLT165HE10", matchHLT165HE10, _branches);
  flatutils::setStatusAndAddress(_tree, _name, "matchHLT175", matchHLT175, _branches);
}

void
simpletree::Photon::array_data::book(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/)
{
  Particle::array_data::book(_tree, _name, _branches);

  flatutils::book(_tree, _name, "chIso", "", 'F', chIso, _branches);
  flatutils::book(_tree, _name, "nhIso", "", 'F', nhIso, _branches);
  flatutils::book(_tree, _name, "phIso", "", 'F', phIso, _branches);
  flatutils::book(_tree, _name, "sieie", "", 'F', sieie, _branches);
  flatutils::book(_tree, _name, "hOverE", "", 'F', hOverE, _branches);
  flatutils::book(_tree, _name, "matchedGen", "", 'I', matchedGen, _branches);
  flatutils::book(_tree, _name, "hadDecay", "", 'O', hadDecay, _branches);
  flatutils::book(_tree, _name, "pixelVeto", "", 'O', pixelVeto, _branches);
  flatutils::book(_tree, _name, "csafeVeto", "", 'O', csafeVeto, _branches);
  flatutils::book(_tree, _name, "loose", "", 'O', loose, _branches);
  flatutils::book(_tree, _name, "medium", "", 'O', medium, _branches);
  flatutils::book(_tree, _name, "tight", "", 'O', tight, _branches);
  flatutils::book(_tree, _name, "matchHLT120", "", 'O', matchHLT120, _branches);
  flatutils::book(_tree, _name, "matchHLT165HE10", "", 'O', matchHLT165HE10, _branches);
  flatutils::book(_tree, _name, "matchHLT175", "", 'O', matchHLT175, _branches);
}

simpletree::Photon::Photon(array_data& _data, UInt_t _idx) :
  Particle(_data, _idx),
  chIso(_data.chIso[_idx]),
  nhIso(_data.nhIso[_idx]),
  phIso(_data.phIso[_idx]),
  sieie(_data.sieie[_idx]),
  hOverE(_data.hOverE[_idx]),
  matchedGen(_data.matchedGen[_idx]),
  hadDecay(_data.hadDecay[_idx]),
  pixelVeto(_data.pixelVeto[_idx]),
  csafeVeto(_data.csafeVeto[_idx]),
  loose(_data.loose[_idx]),
  medium(_data.medium[_idx]),
  tight(_data.tight[_idx]),
  matchHLT120(_data.matchHLT120[_idx]),
  matchHLT165HE10(_data.matchHLT165HE10[_idx]),
  matchHLT175(_data.matchHLT175[_idx])
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

void
simpletree::Lepton::array_data::setStatus(TTree& _tree, TString const& _name, Bool_t _status, flatutils::BranchList const& _branches/* = {"*"}*/)
{
  ParticleM::array_data::setStatus(_tree, _name, _status, _branches);

  flatutils::setStatus(_tree, _name, "matchedGen", _status, _branches);
  flatutils::setStatus(_tree, _name, "tauDecay", _status, _branches);
  flatutils::setStatus(_tree, _name, "hadDecay", _status, _branches);
  flatutils::setStatus(_tree, _name, "positive", _status, _branches);
  flatutils::setStatus(_tree, _name, "loose", _status, _branches);
  flatutils::setStatus(_tree, _name, "tight", _status, _branches);
}

void
simpletree::Lepton::array_data::setAddress(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/)
{
  ParticleM::array_data::setAddress(_tree, _name, _branches);

  flatutils::setStatusAndAddress(_tree, _name, "matchedGen", matchedGen, _branches);
  flatutils::setStatusAndAddress(_tree, _name, "tauDecay", tauDecay, _branches);
  flatutils::setStatusAndAddress(_tree, _name, "hadDecay", hadDecay, _branches);
  flatutils::setStatusAndAddress(_tree, _name, "positive", positive, _branches);
  flatutils::setStatusAndAddress(_tree, _name, "loose", loose, _branches);
  flatutils::setStatusAndAddress(_tree, _name, "tight", tight, _branches);
}

void
simpletree::Lepton::array_data::book(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/)
{
  ParticleM::array_data::book(_tree, _name, _branches);

  flatutils::book(_tree, _name, "matchedGen", "", 'I', matchedGen, _branches);
  flatutils::book(_tree, _name, "tauDecay", "", 'O', tauDecay, _branches);
  flatutils::book(_tree, _name, "hadDecay", "", 'O', hadDecay, _branches);
  flatutils::book(_tree, _name, "positive", "", 'O', positive, _branches);
  flatutils::book(_tree, _name, "loose", "", 'O', loose, _branches);
  flatutils::book(_tree, _name, "tight", "", 'O', tight, _branches);
}

simpletree::Lepton::Lepton(array_data& _data, UInt_t _idx) :
  ParticleM(_data, _idx),
  matchedGen(_data.matchedGen[_idx]),
  tauDecay(_data.tauDecay[_idx]),
  hadDecay(_data.hadDecay[_idx]),
  positive(_data.positive[_idx]),
  loose(_data.loose[_idx]),
  tight(_data.tight[_idx])
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

void
simpletree::Electron::array_data::setStatus(TTree& _tree, TString const& _name, Bool_t _status, flatutils::BranchList const& _branches/* = {"*"}*/)
{
  Lepton::array_data::setStatus(_tree, _name, _status, _branches);

  flatutils::setStatus(_tree, _name, "chIsoPh", _status, _branches);
  flatutils::setStatus(_tree, _name, "nhIsoPh", _status, _branches);
  flatutils::setStatus(_tree, _name, "phIsoPh", _status, _branches);
  flatutils::setStatus(_tree, _name, "sieie", _status, _branches);
  flatutils::setStatus(_tree, _name, "hOverE", _status, _branches);
  flatutils::setStatus(_tree, _name, "matchHLT23Loose", _status, _branches);
  flatutils::setStatus(_tree, _name, "matchHLT27Loose", _status, _branches);
}

void
simpletree::Electron::array_data::setAddress(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/)
{
  Lepton::array_data::setAddress(_tree, _name, _branches);

  flatutils::setStatusAndAddress(_tree, _name, "chIsoPh", chIsoPh, _branches);
  flatutils::setStatusAndAddress(_tree, _name, "nhIsoPh", nhIsoPh, _branches);
  flatutils::setStatusAndAddress(_tree, _name, "phIsoPh", phIsoPh, _branches);
  flatutils::setStatusAndAddress(_tree, _name, "sieie", sieie, _branches);
  flatutils::setStatusAndAddress(_tree, _name, "hOverE", hOverE, _branches);
  flatutils::setStatusAndAddress(_tree, _name, "matchHLT23Loose", matchHLT23Loose, _branches);
  flatutils::setStatusAndAddress(_tree, _name, "matchHLT27Loose", matchHLT27Loose, _branches);
}

void
simpletree::Electron::array_data::book(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/)
{
  Lepton::array_data::book(_tree, _name, _branches);

  flatutils::book(_tree, _name, "chIsoPh", "", 'F', chIsoPh, _branches);
  flatutils::book(_tree, _name, "nhIsoPh", "", 'F', nhIsoPh, _branches);
  flatutils::book(_tree, _name, "phIsoPh", "", 'F', phIsoPh, _branches);
  flatutils::book(_tree, _name, "sieie", "", 'F', sieie, _branches);
  flatutils::book(_tree, _name, "hOverE", "", 'F', hOverE, _branches);
  flatutils::book(_tree, _name, "matchHLT23Loose", "", 'O', matchHLT23Loose, _branches);
  flatutils::book(_tree, _name, "matchHLT27Loose", "", 'O', matchHLT27Loose, _branches);
}

simpletree::Electron::Electron(array_data& _data, UInt_t _idx) :
  Lepton(_data, _idx),
  chIsoPh(_data.chIsoPh[_idx]),
  nhIsoPh(_data.nhIsoPh[_idx]),
  phIsoPh(_data.phIsoPh[_idx]),
  sieie(_data.sieie[_idx]),
  hOverE(_data.hOverE[_idx]),
  matchHLT23Loose(_data.matchHLT23Loose[_idx]),
  matchHLT27Loose(_data.matchHLT27Loose[_idx])
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

void
simpletree::Muon::array_data::setStatus(TTree& _tree, TString const& _name, Bool_t _status, flatutils::BranchList const& _branches/* = {"*"}*/)
{
  Lepton::array_data::setStatus(_tree, _name, _status, _branches);

  flatutils::setStatus(_tree, _name, "matchHLT24", _status, _branches);
  flatutils::setStatus(_tree, _name, "matchHLT27", _status, _branches);
}

void
simpletree::Muon::array_data::setAddress(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/)
{
  Lepton::array_data::setAddress(_tree, _name, _branches);

  flatutils::setStatusAndAddress(_tree, _name, "matchHLT24", matchHLT24, _branches);
  flatutils::setStatusAndAddress(_tree, _name, "matchHLT27", matchHLT27, _branches);
}

void
simpletree::Muon::array_data::book(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/)
{
  Lepton::array_data::book(_tree, _name, _branches);

  flatutils::book(_tree, _name, "matchHLT24", "", 'O', matchHLT24, _branches);
  flatutils::book(_tree, _name, "matchHLT27", "", 'O', matchHLT27, _branches);
}

simpletree::Muon::Muon(array_data& _data, UInt_t _idx) :
  Lepton(_data, _idx),
  matchHLT24(_data.matchHLT24[_idx]),
  matchHLT27(_data.matchHLT27[_idx])
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

void
simpletree::HLT::array_data::setStatus(TTree& _tree, TString const& _name, Bool_t _status, flatutils::BranchList const& _branches/* = {"*"}*/)
{
  flatutils::setStatus(_tree, _name, "pass", _status, _branches);
}

void
simpletree::HLT::array_data::setAddress(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/)
{
  flatutils::setStatusAndAddress(_tree, _name, "pass", pass, _branches);
}

void
simpletree::HLT::array_data::book(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/)
{
  flatutils::book(_tree, _name, "pass", "", 'O', pass, _branches);
}

simpletree::HLT::HLT(array_data& _data, UInt_t _idx) :
  pass(_data.pass[_idx])
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

