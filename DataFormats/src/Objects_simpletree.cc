#include "../interface/Objects_simpletree.h"
#include "TTree.h"

void
simpletree::Particle::array_data::setStatus(TTree& _tree, TString const& _name, Bool_t _status, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  flatutils::setStatus(_tree, _name, "pt", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "eta", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "phi", _status, _branches, _whitelist);
}

void
simpletree::Particle::array_data::setAddress(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  flatutils::setStatusAndAddress(_tree, _name, "pt", pt, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "eta", eta, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "phi", phi, _branches, _whitelist);
}

void
simpletree::Particle::array_data::book(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  flatutils::book(_tree, _name, "pt", _name + ".size", 'F', pt, _branches, _whitelist);
  flatutils::book(_tree, _name, "eta", _name + ".size", 'F', eta, _branches, _whitelist);
  flatutils::book(_tree, _name, "phi", _name + ".size", 'F', phi, _branches, _whitelist);
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
simpletree::Particle::init()
{
  pt = 0.;
  eta = 0.;
  phi = 0.;
}

void
simpletree::ParticleM::array_data::setStatus(TTree& _tree, TString const& _name, Bool_t _status, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  Particle::array_data::setStatus(_tree, _name, _status, _branches, _whitelist);

  flatutils::setStatus(_tree, _name, "mass", _status, _branches, _whitelist);
}

void
simpletree::ParticleM::array_data::setAddress(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  Particle::array_data::setAddress(_tree, _name, _branches, _whitelist);

  flatutils::setStatusAndAddress(_tree, _name, "mass", mass, _branches, _whitelist);
}

void
simpletree::ParticleM::array_data::book(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  Particle::array_data::book(_tree, _name, _branches, _whitelist);

  flatutils::book(_tree, _name, "mass", _name + ".size", 'F', mass, _branches, _whitelist);
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

void
simpletree::ParticleM::init()
{
  Particle::init();

  mass = 0.;
}

void
simpletree::Jet::array_data::setStatus(TTree& _tree, TString const& _name, Bool_t _status, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  ParticleM::array_data::setStatus(_tree, _name, _status, _branches, _whitelist);

  flatutils::setStatus(_tree, _name, "mjid", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "ptRaw", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "ptCorrUp", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "ptCorrDown", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "cisv", _status, _branches, _whitelist);
}

void
simpletree::Jet::array_data::setAddress(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  ParticleM::array_data::setAddress(_tree, _name, _branches, _whitelist);

  flatutils::setStatusAndAddress(_tree, _name, "mjid", mjid, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "ptRaw", ptRaw, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "ptCorrUp", ptCorrUp, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "ptCorrDown", ptCorrDown, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "cisv", cisv, _branches, _whitelist);
}

void
simpletree::Jet::array_data::book(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  ParticleM::array_data::book(_tree, _name, _branches, _whitelist);

  flatutils::book(_tree, _name, "mjid", _name + ".size", 'O', mjid, _branches, _whitelist);
  flatutils::book(_tree, _name, "ptRaw", _name + ".size", 'F', ptRaw, _branches, _whitelist);
  flatutils::book(_tree, _name, "ptCorrUp", _name + ".size", 'F', ptCorrUp, _branches, _whitelist);
  flatutils::book(_tree, _name, "ptCorrDown", _name + ".size", 'F', ptCorrDown, _branches, _whitelist);
  flatutils::book(_tree, _name, "cisv", _name + ".size", 'F', cisv, _branches, _whitelist);
}

simpletree::Jet::Jet(array_data& _data, UInt_t _idx) :
  ParticleM(_data, _idx),
  mjid(_data.mjid[_idx]),
  ptRaw(_data.ptRaw[_idx]),
  ptCorrUp(_data.ptCorrUp[_idx]),
  ptCorrDown(_data.ptCorrDown[_idx]),
  cisv(_data.cisv[_idx])
{
}

simpletree::Jet::Jet(Jet const& _src) :
  ParticleM(_src),
  mjid(_src.mjid),
  ptRaw(_src.ptRaw),
  ptCorrUp(_src.ptCorrUp),
  ptCorrDown(_src.ptCorrDown),
  cisv(_src.cisv)
{
}

simpletree::Jet&
simpletree::Jet::operator=(Jet const& _rhs)
{
  ParticleM::operator=(_rhs);

  mjid = _rhs.mjid;
  ptRaw = _rhs.ptRaw;
  ptCorrUp = _rhs.ptCorrUp;
  ptCorrDown = _rhs.ptCorrDown;
  cisv = _rhs.cisv;
  return *this;
}

void
simpletree::Jet::init()
{
  ParticleM::init();

  mjid = false;
  ptRaw = 0.;
  ptCorrUp = 0.;
  ptCorrDown = 0.;
  cisv = 0.;
}

simpletree::Met::Met(Met const& _src) :
  name_(_src.name_),
  met(_src.met),
  phi(_src.phi),
  sumEt(_src.sumEt),
  et(_src.et)
{
}

void
simpletree::Met::setStatus(TTree& _tree, Bool_t _status, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  flatutils::setStatus(_tree, name_, "met", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, name_, "phi", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, name_, "sumEt", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, name_, "et", _status, _branches, _whitelist);
}

void
simpletree::Met::setAddress(TTree& _tree, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  flatutils::setStatusAndAddress(_tree, name_, "met", &met, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, name_, "phi", &phi, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, name_, "sumEt", &sumEt, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, name_, "et", &et, _branches, _whitelist);
}

void
simpletree::Met::book(TTree& _tree, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist)
{
  flatutils::book(_tree, name_, "met", "", 'F', &met, _branches, _whitelist);
  flatutils::book(_tree, name_, "phi", "", 'F', &phi, _branches, _whitelist);
  flatutils::book(_tree, name_, "sumEt", "", 'F', &sumEt, _branches, _whitelist);
  flatutils::book(_tree, name_, "et", "", 'F', &et, _branches, _whitelist);
}

simpletree::Met&
simpletree::Met::operator=(Met const& _rhs)
{
  met = _rhs.met;
  phi = _rhs.phi;
  sumEt = _rhs.sumEt;
  et = _rhs.et;
  return *this;
}

void
simpletree::Met::init()
{
  met = 0.;
  phi = 0.;
  sumEt = 0.;
  et = 0.;
}

simpletree::CorrectedMet::CorrectedMet(CorrectedMet const& _src) :
  Met(_src),
  metCorrUp(_src.metCorrUp),
  phiCorrUp(_src.phiCorrUp),
  metCorrDown(_src.metCorrDown),
  phiCorrDown(_src.phiCorrDown),
  metUnclUp(_src.metUnclUp),
  phiUnclUp(_src.phiUnclUp),
  metUnclDown(_src.metUnclDown),
  phiUnclDown(_src.phiUnclDown)
{
}

void
simpletree::CorrectedMet::setStatus(TTree& _tree, Bool_t _status, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  Met::setStatus(_tree, _status, _branches, _whitelist);

  flatutils::setStatus(_tree, name_, "metCorrUp", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, name_, "phiCorrUp", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, name_, "metCorrDown", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, name_, "phiCorrDown", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, name_, "metUnclUp", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, name_, "phiUnclUp", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, name_, "metUnclDown", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, name_, "phiUnclDown", _status, _branches, _whitelist);
}

void
simpletree::CorrectedMet::setAddress(TTree& _tree, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  Met::setAddress(_tree, _branches, _whitelist);

  flatutils::setStatusAndAddress(_tree, name_, "metCorrUp", &metCorrUp, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, name_, "phiCorrUp", &phiCorrUp, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, name_, "metCorrDown", &metCorrDown, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, name_, "phiCorrDown", &phiCorrDown, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, name_, "metUnclUp", &metUnclUp, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, name_, "phiUnclUp", &phiUnclUp, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, name_, "metUnclDown", &metUnclDown, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, name_, "phiUnclDown", &phiUnclDown, _branches, _whitelist);
}

void
simpletree::CorrectedMet::book(TTree& _tree, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist)
{
  Met::book(_tree, _branches, _whitelist);

  flatutils::book(_tree, name_, "metCorrUp", "", 'F', &metCorrUp, _branches, _whitelist);
  flatutils::book(_tree, name_, "phiCorrUp", "", 'F', &phiCorrUp, _branches, _whitelist);
  flatutils::book(_tree, name_, "metCorrDown", "", 'F', &metCorrDown, _branches, _whitelist);
  flatutils::book(_tree, name_, "phiCorrDown", "", 'F', &phiCorrDown, _branches, _whitelist);
  flatutils::book(_tree, name_, "metUnclUp", "", 'F', &metUnclUp, _branches, _whitelist);
  flatutils::book(_tree, name_, "phiUnclUp", "", 'F', &phiUnclUp, _branches, _whitelist);
  flatutils::book(_tree, name_, "metUnclDown", "", 'F', &metUnclDown, _branches, _whitelist);
  flatutils::book(_tree, name_, "phiUnclDown", "", 'F', &phiUnclDown, _branches, _whitelist);
}

simpletree::CorrectedMet&
simpletree::CorrectedMet::operator=(CorrectedMet const& _rhs)
{
  Met::operator=(_rhs);

  metCorrUp = _rhs.metCorrUp;
  phiCorrUp = _rhs.phiCorrUp;
  metCorrDown = _rhs.metCorrDown;
  phiCorrDown = _rhs.phiCorrDown;
  metUnclUp = _rhs.metUnclUp;
  phiUnclUp = _rhs.phiUnclUp;
  metUnclDown = _rhs.metUnclDown;
  phiUnclDown = _rhs.phiUnclDown;
  return *this;
}

void
simpletree::CorrectedMet::init()
{
  Met::init();

  metCorrUp = 0.;
  phiCorrUp = 0.;
  metCorrDown = 0.;
  phiCorrDown = 0.;
  metUnclUp = 0.;
  phiUnclUp = 0.;
  metUnclDown = 0.;
  phiUnclDown = 0.;
}

void
simpletree::Photon::array_data::setStatus(TTree& _tree, TString const& _name, Bool_t _status, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  Particle::array_data::setStatus(_tree, _name, _status, _branches, _whitelist);

  flatutils::setStatus(_tree, _name, "chIso", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "chWorstIso", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "chIsoMax", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "nhIso", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "phIso", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "ecalIso", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "hcalIso", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "sieie", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "hOverE", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "genIso", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "mipEnergy", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "mipChi2", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "mipSlope", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "mipIntercept", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "mipNhitCone", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "mipIsHalo", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "e15", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "e25", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "e33", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "e55", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "r9", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "etaWidth", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "phiWidth", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "s4", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "time", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "timeSpan", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "matchedGen", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "isEB", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "pixelVeto", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "electronVeto", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "csafeVeto", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "loose", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "medium", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "tight", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "highpt", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "matchHLT120", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "matchHLT135MET100", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "matchHLT165HE10", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "matchHLT175", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "matchHLT50VBF", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "matchHLT75VBF", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "matchHLT90VBF", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "matchHLT120VBF", _status, _branches, _whitelist);
}

void
simpletree::Photon::array_data::setAddress(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  Particle::array_data::setAddress(_tree, _name, _branches, _whitelist);

  flatutils::setStatusAndAddress(_tree, _name, "chIso", chIso, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "chWorstIso", chWorstIso, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "chIsoMax", chIsoMax, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "nhIso", nhIso, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "phIso", phIso, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "ecalIso", ecalIso, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "hcalIso", hcalIso, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "sieie", sieie, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "hOverE", hOverE, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "genIso", genIso, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "mipEnergy", mipEnergy, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "mipChi2", mipChi2, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "mipSlope", mipSlope, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "mipIntercept", mipIntercept, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "mipNhitCone", mipNhitCone, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "mipIsHalo", mipIsHalo, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "e15", e15, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "e25", e25, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "e33", e33, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "e55", e55, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "r9", r9, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "etaWidth", etaWidth, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "phiWidth", phiWidth, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "s4", s4, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "time", time, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "timeSpan", timeSpan, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "matchedGen", matchedGen, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "isEB", isEB, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "pixelVeto", pixelVeto, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "electronVeto", electronVeto, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "csafeVeto", csafeVeto, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "loose", loose, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "medium", medium, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "tight", tight, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "highpt", highpt, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "matchHLT120", matchHLT120, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "matchHLT135MET100", matchHLT135MET100, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "matchHLT165HE10", matchHLT165HE10, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "matchHLT175", matchHLT175, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "matchHLT50VBF", matchHLT50VBF, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "matchHLT75VBF", matchHLT75VBF, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "matchHLT90VBF", matchHLT90VBF, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "matchHLT120VBF", matchHLT120VBF, _branches, _whitelist);
}

void
simpletree::Photon::array_data::book(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  Particle::array_data::book(_tree, _name, _branches, _whitelist);

  flatutils::book(_tree, _name, "chIso", _name + ".size", 'F', chIso, _branches, _whitelist);
  flatutils::book(_tree, _name, "chWorstIso", _name + ".size", 'F', chWorstIso, _branches, _whitelist);
  flatutils::book(_tree, _name, "chIsoMax", _name + ".size", 'F', chIsoMax, _branches, _whitelist);
  flatutils::book(_tree, _name, "nhIso", _name + ".size", 'F', nhIso, _branches, _whitelist);
  flatutils::book(_tree, _name, "phIso", _name + ".size", 'F', phIso, _branches, _whitelist);
  flatutils::book(_tree, _name, "ecalIso", _name + ".size", 'F', ecalIso, _branches, _whitelist);
  flatutils::book(_tree, _name, "hcalIso", _name + ".size", 'F', hcalIso, _branches, _whitelist);
  flatutils::book(_tree, _name, "sieie", _name + ".size", 'F', sieie, _branches, _whitelist);
  flatutils::book(_tree, _name, "hOverE", _name + ".size", 'F', hOverE, _branches, _whitelist);
  flatutils::book(_tree, _name, "genIso", _name + ".size", 'F', genIso, _branches, _whitelist);
  flatutils::book(_tree, _name, "mipEnergy", _name + ".size", 'F', mipEnergy, _branches, _whitelist);
  flatutils::book(_tree, _name, "mipChi2", _name + ".size", 'F', mipChi2, _branches, _whitelist);
  flatutils::book(_tree, _name, "mipSlope", _name + ".size", 'F', mipSlope, _branches, _whitelist);
  flatutils::book(_tree, _name, "mipIntercept", _name + ".size", 'F', mipIntercept, _branches, _whitelist);
  flatutils::book(_tree, _name, "mipNhitCone", _name + ".size", 's', mipNhitCone, _branches, _whitelist);
  flatutils::book(_tree, _name, "mipIsHalo", _name + ".size", 'O', mipIsHalo, _branches, _whitelist);
  flatutils::book(_tree, _name, "e15", _name + ".size", 'F', e15, _branches, _whitelist);
  flatutils::book(_tree, _name, "e25", _name + ".size", 'F', e25, _branches, _whitelist);
  flatutils::book(_tree, _name, "e33", _name + ".size", 'F', e33, _branches, _whitelist);
  flatutils::book(_tree, _name, "e55", _name + ".size", 'F', e55, _branches, _whitelist);
  flatutils::book(_tree, _name, "r9", _name + ".size", 'F', r9, _branches, _whitelist);
  flatutils::book(_tree, _name, "etaWidth", _name + ".size", 'F', etaWidth, _branches, _whitelist);
  flatutils::book(_tree, _name, "phiWidth", _name + ".size", 'F', phiWidth, _branches, _whitelist);
  flatutils::book(_tree, _name, "s4", _name + ".size", 'F', s4, _branches, _whitelist);
  flatutils::book(_tree, _name, "time", _name + ".size", 'F', time, _branches, _whitelist);
  flatutils::book(_tree, _name, "timeSpan", _name + ".size", 'F', timeSpan, _branches, _whitelist);
  flatutils::book(_tree, _name, "matchedGen", _name + ".size", 'I', matchedGen, _branches, _whitelist);
  flatutils::book(_tree, _name, "isEB", _name + ".size", 'O', isEB, _branches, _whitelist);
  flatutils::book(_tree, _name, "pixelVeto", _name + ".size", 'O', pixelVeto, _branches, _whitelist);
  flatutils::book(_tree, _name, "electronVeto", _name + ".size", 'O', electronVeto, _branches, _whitelist);
  flatutils::book(_tree, _name, "csafeVeto", _name + ".size", 'O', csafeVeto, _branches, _whitelist);
  flatutils::book(_tree, _name, "loose", _name + ".size", 'O', loose, _branches, _whitelist);
  flatutils::book(_tree, _name, "medium", _name + ".size", 'O', medium, _branches, _whitelist);
  flatutils::book(_tree, _name, "tight", _name + ".size", 'O', tight, _branches, _whitelist);
  flatutils::book(_tree, _name, "highpt", _name + ".size", 'O', highpt, _branches, _whitelist);
  flatutils::book(_tree, _name, "matchHLT120", _name + ".size", 'O', matchHLT120, _branches, _whitelist);
  flatutils::book(_tree, _name, "matchHLT135MET100", _name + ".size", 'O', matchHLT135MET100, _branches, _whitelist);
  flatutils::book(_tree, _name, "matchHLT165HE10", _name + ".size", 'O', matchHLT165HE10, _branches, _whitelist);
  flatutils::book(_tree, _name, "matchHLT175", _name + ".size", 'O', matchHLT175, _branches, _whitelist);
  flatutils::book(_tree, _name, "matchHLT50VBF", _name + ".size", 'O', matchHLT50VBF, _branches, _whitelist);
  flatutils::book(_tree, _name, "matchHLT75VBF", _name + ".size", 'O', matchHLT75VBF, _branches, _whitelist);
  flatutils::book(_tree, _name, "matchHLT90VBF", _name + ".size", 'O', matchHLT90VBF, _branches, _whitelist);
  flatutils::book(_tree, _name, "matchHLT120VBF", _name + ".size", 'O', matchHLT120VBF, _branches, _whitelist);
}

simpletree::Photon::Photon(array_data& _data, UInt_t _idx) :
  Particle(_data, _idx),
  chIso(_data.chIso[_idx]),
  chWorstIso(_data.chWorstIso[_idx]),
  chIsoMax(_data.chIsoMax[_idx]),
  nhIso(_data.nhIso[_idx]),
  phIso(_data.phIso[_idx]),
  ecalIso(_data.ecalIso[_idx]),
  hcalIso(_data.hcalIso[_idx]),
  sieie(_data.sieie[_idx]),
  hOverE(_data.hOverE[_idx]),
  genIso(_data.genIso[_idx]),
  mipEnergy(_data.mipEnergy[_idx]),
  mipChi2(_data.mipChi2[_idx]),
  mipSlope(_data.mipSlope[_idx]),
  mipIntercept(_data.mipIntercept[_idx]),
  mipNhitCone(_data.mipNhitCone[_idx]),
  mipIsHalo(_data.mipIsHalo[_idx]),
  e15(_data.e15[_idx]),
  e25(_data.e25[_idx]),
  e33(_data.e33[_idx]),
  e55(_data.e55[_idx]),
  r9(_data.r9[_idx]),
  etaWidth(_data.etaWidth[_idx]),
  phiWidth(_data.phiWidth[_idx]),
  s4(_data.s4[_idx]),
  time(_data.time[_idx]),
  timeSpan(_data.timeSpan[_idx]),
  matchedGen(_data.matchedGen[_idx]),
  isEB(_data.isEB[_idx]),
  pixelVeto(_data.pixelVeto[_idx]),
  electronVeto(_data.electronVeto[_idx]),
  csafeVeto(_data.csafeVeto[_idx]),
  loose(_data.loose[_idx]),
  medium(_data.medium[_idx]),
  tight(_data.tight[_idx]),
  highpt(_data.highpt[_idx]),
  matchHLT120(_data.matchHLT120[_idx]),
  matchHLT135MET100(_data.matchHLT135MET100[_idx]),
  matchHLT165HE10(_data.matchHLT165HE10[_idx]),
  matchHLT175(_data.matchHLT175[_idx]),
  matchHLT50VBF(_data.matchHLT50VBF[_idx]),
  matchHLT75VBF(_data.matchHLT75VBF[_idx]),
  matchHLT90VBF(_data.matchHLT90VBF[_idx]),
  matchHLT120VBF(_data.matchHLT120VBF[_idx])
{
}

simpletree::Photon::Photon(Photon const& _src) :
  Particle(_src),
  chIso(_src.chIso),
  chWorstIso(_src.chWorstIso),
  chIsoMax(_src.chIsoMax),
  nhIso(_src.nhIso),
  phIso(_src.phIso),
  ecalIso(_src.ecalIso),
  hcalIso(_src.hcalIso),
  sieie(_src.sieie),
  hOverE(_src.hOverE),
  genIso(_src.genIso),
  mipEnergy(_src.mipEnergy),
  mipChi2(_src.mipChi2),
  mipSlope(_src.mipSlope),
  mipIntercept(_src.mipIntercept),
  mipNhitCone(_src.mipNhitCone),
  mipIsHalo(_src.mipIsHalo),
  e15(_src.e15),
  e25(_src.e25),
  e33(_src.e33),
  e55(_src.e55),
  r9(_src.r9),
  etaWidth(_src.etaWidth),
  phiWidth(_src.phiWidth),
  s4(_src.s4),
  time(_src.time),
  timeSpan(_src.timeSpan),
  matchedGen(_src.matchedGen),
  isEB(_src.isEB),
  pixelVeto(_src.pixelVeto),
  electronVeto(_src.electronVeto),
  csafeVeto(_src.csafeVeto),
  loose(_src.loose),
  medium(_src.medium),
  tight(_src.tight),
  highpt(_src.highpt),
  matchHLT120(_src.matchHLT120),
  matchHLT135MET100(_src.matchHLT135MET100),
  matchHLT165HE10(_src.matchHLT165HE10),
  matchHLT175(_src.matchHLT175),
  matchHLT50VBF(_src.matchHLT50VBF),
  matchHLT75VBF(_src.matchHLT75VBF),
  matchHLT90VBF(_src.matchHLT90VBF),
  matchHLT120VBF(_src.matchHLT120VBF)
{
}

simpletree::Photon&
simpletree::Photon::operator=(Photon const& _rhs)
{
  Particle::operator=(_rhs);

  chIso = _rhs.chIso;
  chWorstIso = _rhs.chWorstIso;
  chIsoMax = _rhs.chIsoMax;
  nhIso = _rhs.nhIso;
  phIso = _rhs.phIso;
  ecalIso = _rhs.ecalIso;
  hcalIso = _rhs.hcalIso;
  sieie = _rhs.sieie;
  hOverE = _rhs.hOverE;
  genIso = _rhs.genIso;
  mipEnergy = _rhs.mipEnergy;
  mipChi2 = _rhs.mipChi2;
  mipSlope = _rhs.mipSlope;
  mipIntercept = _rhs.mipIntercept;
  mipNhitCone = _rhs.mipNhitCone;
  mipIsHalo = _rhs.mipIsHalo;
  e15 = _rhs.e15;
  e25 = _rhs.e25;
  e33 = _rhs.e33;
  e55 = _rhs.e55;
  r9 = _rhs.r9;
  etaWidth = _rhs.etaWidth;
  phiWidth = _rhs.phiWidth;
  s4 = _rhs.s4;
  time = _rhs.time;
  timeSpan = _rhs.timeSpan;
  matchedGen = _rhs.matchedGen;
  isEB = _rhs.isEB;
  pixelVeto = _rhs.pixelVeto;
  electronVeto = _rhs.electronVeto;
  csafeVeto = _rhs.csafeVeto;
  loose = _rhs.loose;
  medium = _rhs.medium;
  tight = _rhs.tight;
  highpt = _rhs.highpt;
  matchHLT120 = _rhs.matchHLT120;
  matchHLT135MET100 = _rhs.matchHLT135MET100;
  matchHLT165HE10 = _rhs.matchHLT165HE10;
  matchHLT175 = _rhs.matchHLT175;
  matchHLT50VBF = _rhs.matchHLT50VBF;
  matchHLT75VBF = _rhs.matchHLT75VBF;
  matchHLT90VBF = _rhs.matchHLT90VBF;
  matchHLT120VBF = _rhs.matchHLT120VBF;
  return *this;
}

void
simpletree::Photon::init()
{
  Particle::init();

  chIso = 0.;
  chWorstIso = 0.;
  chIsoMax = 0.;
  nhIso = 0.;
  phIso = 0.;
  ecalIso = 0.;
  hcalIso = 0.;
  sieie = 0.;
  hOverE = 0.;
  genIso = 0.;
  mipEnergy = 0.;
  mipChi2 = 0.;
  mipSlope = 0.;
  mipIntercept = 0.;
  mipNhitCone = 0;
  mipIsHalo = false;
  e15 = 0.;
  e25 = 0.;
  e33 = 0.;
  e55 = 0.;
  r9 = 0.;
  etaWidth = 0.;
  phiWidth = 0.;
  s4 = 0.;
  time = 0.;
  timeSpan = 0.;
  matchedGen = 0;
  isEB = false;
  pixelVeto = false;
  electronVeto = false;
  csafeVeto = false;
  loose = false;
  medium = false;
  tight = false;
  highpt = false;
  matchHLT120 = false;
  matchHLT135MET100 = false;
  matchHLT165HE10 = false;
  matchHLT175 = false;
  matchHLT50VBF = false;
  matchHLT75VBF = false;
  matchHLT90VBF = false;
  matchHLT120VBF = false;
}

double const simpletree::Photon::chIsoCuts[2][3]{{3.32, 1.37, 0.76}, {1.97, 1.10, 0.56}};
double const simpletree::Photon::nhIsoCuts[2][3]{{1.92, 1.06, 0.97}, {11.86, 2.69, 2.09}};
double const simpletree::Photon::phIsoCuts[2][3]{{0.81, 0.28, 0.08}, {0.83, 0.39, 0.16}};
double const simpletree::Photon::sieieCuts[2][3]{{0.0102, 0.0102, 0.0100}, {0.0274, 0.0268, 0.0268}};
double const simpletree::Photon::hOverECuts[2][3]{{0.05, 0.05, 0.05}, {0.05, 0.05, 0.05}};

void
simpletree::Lepton::array_data::setStatus(TTree& _tree, TString const& _name, Bool_t _status, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  ParticleM::array_data::setStatus(_tree, _name, _status, _branches, _whitelist);

  flatutils::setStatus(_tree, _name, "matchedGen", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "tauDecay", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "hadDecay", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "positive", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "loose", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "tight", _status, _branches, _whitelist);
}

void
simpletree::Lepton::array_data::setAddress(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  ParticleM::array_data::setAddress(_tree, _name, _branches, _whitelist);

  flatutils::setStatusAndAddress(_tree, _name, "matchedGen", matchedGen, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "tauDecay", tauDecay, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "hadDecay", hadDecay, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "positive", positive, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "loose", loose, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "tight", tight, _branches, _whitelist);
}

void
simpletree::Lepton::array_data::book(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  ParticleM::array_data::book(_tree, _name, _branches, _whitelist);

  flatutils::book(_tree, _name, "matchedGen", _name + ".size", 'I', matchedGen, _branches, _whitelist);
  flatutils::book(_tree, _name, "tauDecay", _name + ".size", 'O', tauDecay, _branches, _whitelist);
  flatutils::book(_tree, _name, "hadDecay", _name + ".size", 'O', hadDecay, _branches, _whitelist);
  flatutils::book(_tree, _name, "positive", _name + ".size", 'O', positive, _branches, _whitelist);
  flatutils::book(_tree, _name, "loose", _name + ".size", 'O', loose, _branches, _whitelist);
  flatutils::book(_tree, _name, "tight", _name + ".size", 'O', tight, _branches, _whitelist);
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
simpletree::Lepton::init()
{
  ParticleM::init();

  matchedGen = 0;
  tauDecay = false;
  hadDecay = false;
  positive = false;
  loose = false;
  tight = false;
}

void
simpletree::Electron::array_data::setStatus(TTree& _tree, TString const& _name, Bool_t _status, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  Lepton::array_data::setStatus(_tree, _name, _status, _branches, _whitelist);

  flatutils::setStatus(_tree, _name, "chIso", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "nhIso", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "phIso", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "chIsoPh", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "nhIsoPh", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "phIsoPh", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "ecalIso", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "hcalIso", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "sieie", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "hOverE", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "isEB", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "veto", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "matchHLT23Loose", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "matchHLT27Loose", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "matchHLT120Ph", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "matchHLT135MET100Ph", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "matchHLT165HE10Ph", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "matchHLT175Ph", _status, _branches, _whitelist);
}

void
simpletree::Electron::array_data::setAddress(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  Lepton::array_data::setAddress(_tree, _name, _branches, _whitelist);

  flatutils::setStatusAndAddress(_tree, _name, "chIso", chIso, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "nhIso", nhIso, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "phIso", phIso, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "chIsoPh", chIsoPh, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "nhIsoPh", nhIsoPh, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "phIsoPh", phIsoPh, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "ecalIso", ecalIso, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "hcalIso", hcalIso, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "sieie", sieie, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "hOverE", hOverE, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "isEB", isEB, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "veto", veto, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "matchHLT23Loose", matchHLT23Loose, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "matchHLT27Loose", matchHLT27Loose, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "matchHLT120Ph", matchHLT120Ph, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "matchHLT135MET100Ph", matchHLT135MET100Ph, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "matchHLT165HE10Ph", matchHLT165HE10Ph, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "matchHLT175Ph", matchHLT175Ph, _branches, _whitelist);
}

void
simpletree::Electron::array_data::book(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  Lepton::array_data::book(_tree, _name, _branches, _whitelist);

  flatutils::book(_tree, _name, "chIso", _name + ".size", 'F', chIso, _branches, _whitelist);
  flatutils::book(_tree, _name, "nhIso", _name + ".size", 'F', nhIso, _branches, _whitelist);
  flatutils::book(_tree, _name, "phIso", _name + ".size", 'F', phIso, _branches, _whitelist);
  flatutils::book(_tree, _name, "chIsoPh", _name + ".size", 'F', chIsoPh, _branches, _whitelist);
  flatutils::book(_tree, _name, "nhIsoPh", _name + ".size", 'F', nhIsoPh, _branches, _whitelist);
  flatutils::book(_tree, _name, "phIsoPh", _name + ".size", 'F', phIsoPh, _branches, _whitelist);
  flatutils::book(_tree, _name, "ecalIso", _name + ".size", 'F', ecalIso, _branches, _whitelist);
  flatutils::book(_tree, _name, "hcalIso", _name + ".size", 'F', hcalIso, _branches, _whitelist);
  flatutils::book(_tree, _name, "sieie", _name + ".size", 'F', sieie, _branches, _whitelist);
  flatutils::book(_tree, _name, "hOverE", _name + ".size", 'F', hOverE, _branches, _whitelist);
  flatutils::book(_tree, _name, "isEB", _name + ".size", 'O', isEB, _branches, _whitelist);
  flatutils::book(_tree, _name, "veto", _name + ".size", 'O', veto, _branches, _whitelist);
  flatutils::book(_tree, _name, "matchHLT23Loose", _name + ".size", 'O', matchHLT23Loose, _branches, _whitelist);
  flatutils::book(_tree, _name, "matchHLT27Loose", _name + ".size", 'O', matchHLT27Loose, _branches, _whitelist);
  flatutils::book(_tree, _name, "matchHLT120Ph", _name + ".size", 'O', matchHLT120Ph, _branches, _whitelist);
  flatutils::book(_tree, _name, "matchHLT135MET100Ph", _name + ".size", 'O', matchHLT135MET100Ph, _branches, _whitelist);
  flatutils::book(_tree, _name, "matchHLT165HE10Ph", _name + ".size", 'O', matchHLT165HE10Ph, _branches, _whitelist);
  flatutils::book(_tree, _name, "matchHLT175Ph", _name + ".size", 'O', matchHLT175Ph, _branches, _whitelist);
}

simpletree::Electron::Electron(array_data& _data, UInt_t _idx) :
  Lepton(_data, _idx),
  chIso(_data.chIso[_idx]),
  nhIso(_data.nhIso[_idx]),
  phIso(_data.phIso[_idx]),
  chIsoPh(_data.chIsoPh[_idx]),
  nhIsoPh(_data.nhIsoPh[_idx]),
  phIsoPh(_data.phIsoPh[_idx]),
  ecalIso(_data.ecalIso[_idx]),
  hcalIso(_data.hcalIso[_idx]),
  sieie(_data.sieie[_idx]),
  hOverE(_data.hOverE[_idx]),
  isEB(_data.isEB[_idx]),
  veto(_data.veto[_idx]),
  matchHLT23Loose(_data.matchHLT23Loose[_idx]),
  matchHLT27Loose(_data.matchHLT27Loose[_idx]),
  matchHLT120Ph(_data.matchHLT120Ph[_idx]),
  matchHLT135MET100Ph(_data.matchHLT135MET100Ph[_idx]),
  matchHLT165HE10Ph(_data.matchHLT165HE10Ph[_idx]),
  matchHLT175Ph(_data.matchHLT175Ph[_idx])
{
}

simpletree::Electron::Electron(Electron const& _src) :
  Lepton(_src),
  chIso(_src.chIso),
  nhIso(_src.nhIso),
  phIso(_src.phIso),
  chIsoPh(_src.chIsoPh),
  nhIsoPh(_src.nhIsoPh),
  phIsoPh(_src.phIsoPh),
  ecalIso(_src.ecalIso),
  hcalIso(_src.hcalIso),
  sieie(_src.sieie),
  hOverE(_src.hOverE),
  isEB(_src.isEB),
  veto(_src.veto),
  matchHLT23Loose(_src.matchHLT23Loose),
  matchHLT27Loose(_src.matchHLT27Loose),
  matchHLT120Ph(_src.matchHLT120Ph),
  matchHLT135MET100Ph(_src.matchHLT135MET100Ph),
  matchHLT165HE10Ph(_src.matchHLT165HE10Ph),
  matchHLT175Ph(_src.matchHLT175Ph)
{
}

simpletree::Electron&
simpletree::Electron::operator=(Electron const& _rhs)
{
  Lepton::operator=(_rhs);

  chIso = _rhs.chIso;
  nhIso = _rhs.nhIso;
  phIso = _rhs.phIso;
  chIsoPh = _rhs.chIsoPh;
  nhIsoPh = _rhs.nhIsoPh;
  phIsoPh = _rhs.phIsoPh;
  ecalIso = _rhs.ecalIso;
  hcalIso = _rhs.hcalIso;
  sieie = _rhs.sieie;
  hOverE = _rhs.hOverE;
  isEB = _rhs.isEB;
  veto = _rhs.veto;
  matchHLT23Loose = _rhs.matchHLT23Loose;
  matchHLT27Loose = _rhs.matchHLT27Loose;
  matchHLT120Ph = _rhs.matchHLT120Ph;
  matchHLT135MET100Ph = _rhs.matchHLT135MET100Ph;
  matchHLT165HE10Ph = _rhs.matchHLT165HE10Ph;
  matchHLT175Ph = _rhs.matchHLT175Ph;
  return *this;
}

void
simpletree::Electron::init()
{
  Lepton::init();

  chIso = 0.;
  nhIso = 0.;
  phIso = 0.;
  chIsoPh = 0.;
  nhIsoPh = 0.;
  phIsoPh = 0.;
  ecalIso = 0.;
  hcalIso = 0.;
  sieie = 0.;
  hOverE = 0.;
  isEB = false;
  veto = false;
  matchHLT23Loose = false;
  matchHLT27Loose = false;
  matchHLT120Ph = false;
  matchHLT135MET100Ph = false;
  matchHLT165HE10Ph = false;
  matchHLT175Ph = false;
}

void
simpletree::Muon::array_data::setStatus(TTree& _tree, TString const& _name, Bool_t _status, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  Lepton::array_data::setStatus(_tree, _name, _status, _branches, _whitelist);

  flatutils::setStatus(_tree, _name, "combRelIso", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "matchHLT20", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "matchHLTTrk20", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "matchHLT24", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "matchHLT27", _status, _branches, _whitelist);
}

void
simpletree::Muon::array_data::setAddress(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  Lepton::array_data::setAddress(_tree, _name, _branches, _whitelist);

  flatutils::setStatusAndAddress(_tree, _name, "combRelIso", combRelIso, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "matchHLT20", matchHLT20, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "matchHLTTrk20", matchHLTTrk20, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "matchHLT24", matchHLT24, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "matchHLT27", matchHLT27, _branches, _whitelist);
}

void
simpletree::Muon::array_data::book(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  Lepton::array_data::book(_tree, _name, _branches, _whitelist);

  flatutils::book(_tree, _name, "combRelIso", _name + ".size", 'F', combRelIso, _branches, _whitelist);
  flatutils::book(_tree, _name, "matchHLT20", _name + ".size", 'O', matchHLT20, _branches, _whitelist);
  flatutils::book(_tree, _name, "matchHLTTrk20", _name + ".size", 'O', matchHLTTrk20, _branches, _whitelist);
  flatutils::book(_tree, _name, "matchHLT24", _name + ".size", 'O', matchHLT24, _branches, _whitelist);
  flatutils::book(_tree, _name, "matchHLT27", _name + ".size", 'O', matchHLT27, _branches, _whitelist);
}

simpletree::Muon::Muon(array_data& _data, UInt_t _idx) :
  Lepton(_data, _idx),
  combRelIso(_data.combRelIso[_idx]),
  matchHLT20(_data.matchHLT20[_idx]),
  matchHLTTrk20(_data.matchHLTTrk20[_idx]),
  matchHLT24(_data.matchHLT24[_idx]),
  matchHLT27(_data.matchHLT27[_idx])
{
}

simpletree::Muon::Muon(Muon const& _src) :
  Lepton(_src),
  combRelIso(_src.combRelIso),
  matchHLT20(_src.matchHLT20),
  matchHLTTrk20(_src.matchHLTTrk20),
  matchHLT24(_src.matchHLT24),
  matchHLT27(_src.matchHLT27)
{
}

simpletree::Muon&
simpletree::Muon::operator=(Muon const& _rhs)
{
  Lepton::operator=(_rhs);

  combRelIso = _rhs.combRelIso;
  matchHLT20 = _rhs.matchHLT20;
  matchHLTTrk20 = _rhs.matchHLTTrk20;
  matchHLT24 = _rhs.matchHLT24;
  matchHLT27 = _rhs.matchHLT27;
  return *this;
}

void
simpletree::Muon::init()
{
  Lepton::init();

  combRelIso = 0.;
  matchHLT20 = false;
  matchHLTTrk20 = false;
  matchHLT24 = false;
  matchHLT27 = false;
}

void
simpletree::Tau::array_data::setStatus(TTree& _tree, TString const& _name, Bool_t _status, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  ParticleM::array_data::setStatus(_tree, _name, _status, _branches, _whitelist);

  flatutils::setStatus(_tree, _name, "decayMode", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "combIso", _status, _branches, _whitelist);
}

void
simpletree::Tau::array_data::setAddress(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  ParticleM::array_data::setAddress(_tree, _name, _branches, _whitelist);

  flatutils::setStatusAndAddress(_tree, _name, "decayMode", decayMode, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "combIso", combIso, _branches, _whitelist);
}

void
simpletree::Tau::array_data::book(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  ParticleM::array_data::book(_tree, _name, _branches, _whitelist);

  flatutils::book(_tree, _name, "decayMode", _name + ".size", 'O', decayMode, _branches, _whitelist);
  flatutils::book(_tree, _name, "combIso", _name + ".size", 'F', combIso, _branches, _whitelist);
}

simpletree::Tau::Tau(array_data& _data, UInt_t _idx) :
  ParticleM(_data, _idx),
  decayMode(_data.decayMode[_idx]),
  combIso(_data.combIso[_idx])
{
}

simpletree::Tau::Tau(Tau const& _src) :
  ParticleM(_src),
  decayMode(_src.decayMode),
  combIso(_src.combIso)
{
}

simpletree::Tau&
simpletree::Tau::operator=(Tau const& _rhs)
{
  ParticleM::operator=(_rhs);

  decayMode = _rhs.decayMode;
  combIso = _rhs.combIso;
  return *this;
}

void
simpletree::Tau::init()
{
  ParticleM::init();

  decayMode = false;
  combIso = 0.;
}

void
simpletree::Parton::array_data::setStatus(TTree& _tree, TString const& _name, Bool_t _status, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  ParticleM::array_data::setStatus(_tree, _name, _status, _branches, _whitelist);

  flatutils::setStatus(_tree, _name, "pid", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "status", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "frixIso", _status, _branches, _whitelist);
}

void
simpletree::Parton::array_data::setAddress(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  ParticleM::array_data::setAddress(_tree, _name, _branches, _whitelist);

  flatutils::setStatusAndAddress(_tree, _name, "pid", pid, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "status", status, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "frixIso", frixIso, _branches, _whitelist);
}

void
simpletree::Parton::array_data::book(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  ParticleM::array_data::book(_tree, _name, _branches, _whitelist);

  flatutils::book(_tree, _name, "pid", _name + ".size", 'I', pid, _branches, _whitelist);
  flatutils::book(_tree, _name, "status", _name + ".size", 'S', status, _branches, _whitelist);
  flatutils::book(_tree, _name, "frixIso", _name + ".size", 'O', frixIso, _branches, _whitelist);
}

simpletree::Parton::Parton(array_data& _data, UInt_t _idx) :
  ParticleM(_data, _idx),
  pid(_data.pid[_idx]),
  status(_data.status[_idx]),
  frixIso(_data.frixIso[_idx])
{
}

simpletree::Parton::Parton(Parton const& _src) :
  ParticleM(_src),
  pid(_src.pid),
  status(_src.status),
  frixIso(_src.frixIso)
{
}

simpletree::Parton&
simpletree::Parton::operator=(Parton const& _rhs)
{
  ParticleM::operator=(_rhs);

  pid = _rhs.pid;
  status = _rhs.status;
  frixIso = _rhs.frixIso;
  return *this;
}

void
simpletree::Parton::init()
{
  ParticleM::init();

  pid = 0;
  status = 0;
  frixIso = false;
}

void
simpletree::MCParticle::array_data::setStatus(TTree& _tree, TString const& _name, Bool_t _status, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  ParticleM::array_data::setStatus(_tree, _name, _status, _branches, _whitelist);

  flatutils::setStatus(_tree, _name, "pid", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "ancestor", _status, _branches, _whitelist);
}

void
simpletree::MCParticle::array_data::setAddress(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  ParticleM::array_data::setAddress(_tree, _name, _branches, _whitelist);

  flatutils::setStatusAndAddress(_tree, _name, "pid", pid, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "ancestor", ancestor, _branches, _whitelist);
}

void
simpletree::MCParticle::array_data::book(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  ParticleM::array_data::book(_tree, _name, _branches, _whitelist);

  flatutils::book(_tree, _name, "pid", _name + ".size", 'I', pid, _branches, _whitelist);
  flatutils::book(_tree, _name, "ancestor", _name + ".size", 's', ancestor, _branches, _whitelist);
}

simpletree::MCParticle::MCParticle(array_data& _data, UInt_t _idx) :
  ParticleM(_data, _idx),
  pid(_data.pid[_idx]),
  ancestor(_data.ancestor[_idx])
{
}

simpletree::MCParticle::MCParticle(MCParticle const& _src) :
  ParticleM(_src),
  pid(_src.pid),
  ancestor(_src.ancestor)
{
}

simpletree::MCParticle&
simpletree::MCParticle::operator=(MCParticle const& _rhs)
{
  ParticleM::operator=(_rhs);

  pid = _rhs.pid;
  ancestor = _rhs.ancestor;
  return *this;
}

void
simpletree::MCParticle::init()
{
  ParticleM::init();

  pid = 0;
  ancestor = 0;
}

simpletree::GenJet::GenJet(array_data& _data, UInt_t _idx) :
  ParticleM(_data, _idx)
{
}

simpletree::GenJet::GenJet(GenJet const& _src) :
  ParticleM(_src)
{
}

simpletree::GenJet&
simpletree::GenJet::operator=(GenJet const& _rhs)
{
  ParticleM::operator=(_rhs);

  return *this;
}

void
simpletree::GenJet::init()
{
  ParticleM::init();

}

void
simpletree::HLT::array_data::setStatus(TTree& _tree, TString const& _name, Bool_t _status, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  flatutils::setStatus(_tree, _name, "pass", _status, _branches, _whitelist);
}

void
simpletree::HLT::array_data::setAddress(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  flatutils::setStatusAndAddress(_tree, _name, "pass", pass, _branches, _whitelist);
}

void
simpletree::HLT::array_data::book(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  flatutils::book(_tree, _name, "pass", TString::Format("%d", 17), 'O', pass, _branches, _whitelist);
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

void
simpletree::HLT::init()
{
  pass = false;
}

simpletree::MetFilters::MetFilters(MetFilters const& _src) :
  name_(_src.name_),
  cschalo(_src.cschalo),
  hbhe(_src.hbhe),
  hbheIso(_src.hbheIso),
  badsc(_src.badsc),
  badTrack(_src.badTrack),
  badMuonTrack(_src.badMuonTrack)
{
}

void
simpletree::MetFilters::setStatus(TTree& _tree, Bool_t _status, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  flatutils::setStatus(_tree, name_, "cschalo", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, name_, "hbhe", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, name_, "hbheIso", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, name_, "badsc", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, name_, "badTrack", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, name_, "badMuonTrack", _status, _branches, _whitelist);
}

void
simpletree::MetFilters::setAddress(TTree& _tree, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  flatutils::setStatusAndAddress(_tree, name_, "cschalo", &cschalo, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, name_, "hbhe", &hbhe, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, name_, "hbheIso", &hbheIso, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, name_, "badsc", &badsc, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, name_, "badTrack", &badTrack, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, name_, "badMuonTrack", &badMuonTrack, _branches, _whitelist);
}

void
simpletree::MetFilters::book(TTree& _tree, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist)
{
  flatutils::book(_tree, name_, "cschalo", "", 'O', &cschalo, _branches, _whitelist);
  flatutils::book(_tree, name_, "hbhe", "", 'O', &hbhe, _branches, _whitelist);
  flatutils::book(_tree, name_, "hbheIso", "", 'O', &hbheIso, _branches, _whitelist);
  flatutils::book(_tree, name_, "badsc", "", 'O', &badsc, _branches, _whitelist);
  flatutils::book(_tree, name_, "badTrack", "", 'O', &badTrack, _branches, _whitelist);
  flatutils::book(_tree, name_, "badMuonTrack", "", 'O', &badMuonTrack, _branches, _whitelist);
}

simpletree::MetFilters&
simpletree::MetFilters::operator=(MetFilters const& _rhs)
{
  cschalo = _rhs.cschalo;
  hbhe = _rhs.hbhe;
  hbheIso = _rhs.hbheIso;
  badsc = _rhs.badsc;
  badTrack = _rhs.badTrack;
  badMuonTrack = _rhs.badMuonTrack;
  return *this;
}

void
simpletree::MetFilters::init()
{
  cschalo = false;
  hbhe = false;
  hbheIso = false;
  badsc = false;
  badTrack = false;
  badMuonTrack = false;
}

void
simpletree::ReweightScale::array_data::setStatus(TTree& _tree, TString const& _name, Bool_t _status, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  flatutils::setStatus(_tree, _name, "scale", _status, _branches, _whitelist);
}

void
simpletree::ReweightScale::array_data::setAddress(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  flatutils::setStatusAndAddress(_tree, _name, "scale", scale, _branches, _whitelist);
}

void
simpletree::ReweightScale::array_data::book(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  flatutils::book(_tree, _name, "scale", TString::Format("%d", 256), 'F', scale, _branches, _whitelist);
}

simpletree::ReweightScale::ReweightScale(array_data& _data, UInt_t _idx) :
  scale(_data.scale[_idx])
{
}

simpletree::ReweightScale::ReweightScale(ReweightScale const& _src) :
  scale(_src.scale)
{
}

simpletree::ReweightScale&
simpletree::ReweightScale::operator=(ReweightScale const& _rhs)
{
  scale = _rhs.scale;
  return *this;
}

void
simpletree::ReweightScale::init()
{
  scale = 0.;
}

