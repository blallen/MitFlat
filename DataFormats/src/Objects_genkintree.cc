#include "../interface/Objects_genkintree.h"
#include "TTree.h"

void
genkintree::Particle::array_data::setStatus(TTree& _tree, TString const& _name, Bool_t _status, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  flatutils::setStatus(_tree, _name, "pt", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "eta", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "phi", _status, _branches, _whitelist);
}

void
genkintree::Particle::array_data::setAddress(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  flatutils::setStatusAndAddress(_tree, _name, "pt", pt, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "eta", eta, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "phi", phi, _branches, _whitelist);
}

void
genkintree::Particle::array_data::book(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  flatutils::book(_tree, _name, "pt", _name + ".size", 'F', pt, _branches, _whitelist);
  flatutils::book(_tree, _name, "eta", _name + ".size", 'F', eta, _branches, _whitelist);
  flatutils::book(_tree, _name, "phi", _name + ".size", 'F', phi, _branches, _whitelist);
}

genkintree::Particle::Particle(array_data& _data, UInt_t _idx) :
  pt(_data.pt[_idx]),
  eta(_data.eta[_idx]),
  phi(_data.phi[_idx])
{
}

genkintree::Particle::Particle(Particle const& _src) :
  pt(_src.pt),
  eta(_src.eta),
  phi(_src.phi)
{
}

genkintree::Particle&
genkintree::Particle::operator=(Particle const& _rhs)
{
  pt = _rhs.pt;
  eta = _rhs.eta;
  phi = _rhs.phi;
  return *this;
}

void
genkintree::Jet::array_data::setStatus(TTree& _tree, TString const& _name, Bool_t _status, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  Particle::array_data::setStatus(_tree, _name, _status, _branches, _whitelist);

  flatutils::setStatus(_tree, _name, "mass", _status, _branches, _whitelist);
}

void
genkintree::Jet::array_data::setAddress(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  Particle::array_data::setAddress(_tree, _name, _branches, _whitelist);

  flatutils::setStatusAndAddress(_tree, _name, "mass", mass, _branches, _whitelist);
}

void
genkintree::Jet::array_data::book(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  Particle::array_data::book(_tree, _name, _branches, _whitelist);

  flatutils::book(_tree, _name, "mass", _name + ".size", 'F', mass, _branches, _whitelist);
}

genkintree::Jet::Jet(array_data& _data, UInt_t _idx) :
  Particle(_data, _idx),
  mass(_data.mass[_idx])
{
}

genkintree::Jet::Jet(Jet const& _src) :
  Particle(_src),
  mass(_src.mass)
{
}

genkintree::Jet&
genkintree::Jet::operator=(Jet const& _rhs)
{
  Particle::operator=(_rhs);

  mass = _rhs.mass;
  return *this;
}

void
genkintree::Photon::array_data::setStatus(TTree& _tree, TString const& _name, Bool_t _status, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  Particle::array_data::setStatus(_tree, _name, _status, _branches, _whitelist);

  flatutils::setStatus(_tree, _name, "isot", _status, _branches, _whitelist);
}

void
genkintree::Photon::array_data::setAddress(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  Particle::array_data::setAddress(_tree, _name, _branches, _whitelist);

  flatutils::setStatusAndAddress(_tree, _name, "isot", isot, _branches, _whitelist);
}

void
genkintree::Photon::array_data::book(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  Particle::array_data::book(_tree, _name, _branches, _whitelist);

  flatutils::book(_tree, _name, "isot", _name + ".size", 'F', isot, _branches, _whitelist);
}

genkintree::Photon::Photon(array_data& _data, UInt_t _idx) :
  Particle(_data, _idx),
  isot(_data.isot[_idx])
{
}

genkintree::Photon::Photon(Photon const& _src) :
  Particle(_src),
  isot(_src.isot)
{
}

genkintree::Photon&
genkintree::Photon::operator=(Photon const& _rhs)
{
  Particle::operator=(_rhs);

  isot = _rhs.isot;
  return *this;
}

genkintree::Met::Met(Met const& _src) :
  name_(_src.name_),
  pt(_src.pt),
  phi(_src.phi)
{
}

void
genkintree::Met::setStatus(TTree& _tree, Bool_t _status, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  flatutils::setStatus(_tree, name_, "pt", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, name_, "phi", _status, _branches, _whitelist);
}

void
genkintree::Met::setAddress(TTree& _tree, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  flatutils::setStatusAndAddress(_tree, name_, "pt", &pt, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, name_, "phi", &phi, _branches, _whitelist);
}

void
genkintree::Met::book(TTree& _tree, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist)
{
  flatutils::book(_tree, name_, "pt", "", 'F', &pt, _branches, _whitelist);
  flatutils::book(_tree, name_, "phi", "", 'F', &phi, _branches, _whitelist);
}

genkintree::Met&
genkintree::Met::operator=(Met const& _rhs)
{
  pt = _rhs.pt;
  phi = _rhs.phi;
  return *this;
}

