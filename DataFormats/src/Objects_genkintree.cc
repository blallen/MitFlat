#include "../interface/Objects_genkintree.h"
#include "TTree.h"

#include <algorithm>

genkintree::Particle::array_data::array_data()
{
}

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
  flatutils::book(_tree, _name, "pt", "[" + _name + ".size]", 'F', pt, _branches, _whitelist);
  flatutils::book(_tree, _name, "eta", "[" + _name + ".size]", 'F', eta, _branches, _whitelist);
  flatutils::book(_tree, _name, "phi", "[" + _name + ".size]", 'F', phi, _branches, _whitelist);
}

void
genkintree::Particle::setStatus(TTree& _tree, TString const& _name, Bool_t _status, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  flatutils::setStatus(_tree, _name, "pt", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "eta", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "phi", _status, _branches, _whitelist);
}

void
genkintree::Particle::setAddress(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  flatutils::setStatusAndAddress(_tree, _name, "pt", &pt, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "eta", &eta, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "phi", &phi, _branches, _whitelist);
}

void
genkintree::Particle::book(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist)
{
  flatutils::book(_tree, _name, "pt", "", 'F', &pt, _branches, _whitelist);
  flatutils::book(_tree, _name, "eta", "", 'F', &eta, _branches, _whitelist);
  flatutils::book(_tree, _name, "phi", "", 'F', &phi, _branches, _whitelist);
}

/*static*/
std::vector<std::auto_ptr<genkintree::Particle::array_data>> genkintree::Particle::singlesData_{};
/*static*/
genkintree::SinglesPos genkintree::Particle::singlesPos_(-1, genkintree::Particle::array_data::NMAX - 1);
/*static*/
std::set<genkintree::SinglesPos> genkintree::Particle::usedSinglesPos_{};

/*static*/
genkintree::SinglesPos const&
genkintree::Particle::nextSinglesPos_()
{
  for (unsigned iC(0); iC != singlesData_.size(); ++iC) {
    singlesPos_.first = iC;
    for (singlesPos_.second = 0; singlesPos_.second != array_data::NMAX; ++singlesPos_.second) {
      if (usedSinglesPos_.find(singlesPos_) == usedSinglesPos_.end())
        break;
    }
  }

  if (singlesPos_.first == unsigned(singlesData_.size() - 1) && singlesPos_.second == array_data::NMAX - 1) {
    singlesData_.emplace_back(new array_data);
    singlesPos_.first = singlesData_.size() - 1;
    singlesPos_.second = 0;
  }

  return singlesPos_;
}

genkintree::Particle::Particle() :
  pos_(nextSinglesPos_()),
  pt(singlesData_.at(singlesPos_.first)->pt[singlesPos_.second]),
  eta(singlesData_.at(singlesPos_.first)->eta[singlesPos_.second]),
  phi(singlesData_.at(singlesPos_.first)->phi[singlesPos_.second])
{
  usedSinglesPos_.insert(pos_);
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

genkintree::Particle::~Particle()
{
  if (pos_.first != unsigned(-1)) {
    usedSinglesPos_.erase(pos_);
    pos_.first = -1;
  }
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
genkintree::Particle::init()
{
  pt = 0.;
  eta = 0.;
  phi = 0.;
}

genkintree::ParticleM::array_data::array_data() :
  Particle::array_data()
{
}

void
genkintree::ParticleM::array_data::setStatus(TTree& _tree, TString const& _name, Bool_t _status, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  Particle::array_data::setStatus(_tree, _name, _status, _branches, _whitelist);

  flatutils::setStatus(_tree, _name, "mass", _status, _branches, _whitelist);
}

void
genkintree::ParticleM::array_data::setAddress(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  Particle::array_data::setAddress(_tree, _name, _branches, _whitelist);

  flatutils::setStatusAndAddress(_tree, _name, "mass", mass, _branches, _whitelist);
}

void
genkintree::ParticleM::array_data::book(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  Particle::array_data::book(_tree, _name, _branches, _whitelist);

  flatutils::book(_tree, _name, "mass", "[" + _name + ".size]", 'F', mass, _branches, _whitelist);
}

void
genkintree::ParticleM::setStatus(TTree& _tree, TString const& _name, Bool_t _status, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  Particle::setStatus(_tree, _name, _status, _branches, _whitelist);

  flatutils::setStatus(_tree, _name, "mass", _status, _branches, _whitelist);
}

void
genkintree::ParticleM::setAddress(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  Particle::setAddress(_tree, _name, _branches, _whitelist);

  flatutils::setStatusAndAddress(_tree, _name, "mass", &mass, _branches, _whitelist);
}

void
genkintree::ParticleM::book(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist)
{
  Particle::book(_tree, _name, _branches, _whitelist);

  flatutils::book(_tree, _name, "mass", "", 'F', &mass, _branches, _whitelist);
}

/*static*/
std::vector<std::auto_ptr<genkintree::ParticleM::array_data>> genkintree::ParticleM::singlesData_{};
/*static*/
genkintree::SinglesPos genkintree::ParticleM::singlesPos_(-1, genkintree::ParticleM::array_data::NMAX - 1);
/*static*/
std::set<genkintree::SinglesPos> genkintree::ParticleM::usedSinglesPos_{};

/*static*/
genkintree::SinglesPos const&
genkintree::ParticleM::nextSinglesPos_()
{
  for (unsigned iC(0); iC != singlesData_.size(); ++iC) {
    singlesPos_.first = iC;
    for (singlesPos_.second = 0; singlesPos_.second != array_data::NMAX; ++singlesPos_.second) {
      if (usedSinglesPos_.find(singlesPos_) == usedSinglesPos_.end())
        break;
    }
  }

  if (singlesPos_.first == unsigned(singlesData_.size() - 1) && singlesPos_.second == array_data::NMAX - 1) {
    singlesData_.emplace_back(new array_data);
    singlesPos_.first = singlesData_.size() - 1;
    singlesPos_.second = 0;
  }

  return singlesPos_;
}

genkintree::ParticleM::ParticleM() :
  Particle(*singlesData_.at(nextSinglesPos_().first), singlesPos_.second),
  mass(singlesData_.at(singlesPos_.first)->mass[singlesPos_.second])
{
  pos_ = singlesPos_;
  usedSinglesPos_.insert(pos_);
}

genkintree::ParticleM::ParticleM(array_data& _data, UInt_t _idx) :
  Particle(_data, _idx),
  mass(_data.mass[_idx])
{
}

genkintree::ParticleM::ParticleM(ParticleM const& _src) :
  Particle(_src),
  mass(_src.mass)
{
}

genkintree::ParticleM::~ParticleM()
{
  if (pos_.first != unsigned(-1)) {
    usedSinglesPos_.erase(pos_);
    pos_.first = -1;
  }
}

genkintree::ParticleM&
genkintree::ParticleM::operator=(ParticleM const& _rhs)
{
  Particle::operator=(_rhs);

  mass = _rhs.mass;
  return *this;
}

void
genkintree::ParticleM::init()
{
  Particle::init();

  mass = 0.;
}

genkintree::Parton::array_data::array_data() :
  Particle::array_data()
{
}

void
genkintree::Parton::array_data::setStatus(TTree& _tree, TString const& _name, Bool_t _status, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  Particle::array_data::setStatus(_tree, _name, _status, _branches, _whitelist);

  flatutils::setStatus(_tree, _name, "pid", _status, _branches, _whitelist);
}

void
genkintree::Parton::array_data::setAddress(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  Particle::array_data::setAddress(_tree, _name, _branches, _whitelist);

  flatutils::setStatusAndAddress(_tree, _name, "pid", pid, _branches, _whitelist);
}

void
genkintree::Parton::array_data::book(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  Particle::array_data::book(_tree, _name, _branches, _whitelist);

  flatutils::book(_tree, _name, "pid", "[" + _name + ".size]", 'B', pid, _branches, _whitelist);
}

void
genkintree::Parton::setStatus(TTree& _tree, TString const& _name, Bool_t _status, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  Particle::setStatus(_tree, _name, _status, _branches, _whitelist);

  flatutils::setStatus(_tree, _name, "pid", _status, _branches, _whitelist);
}

void
genkintree::Parton::setAddress(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  Particle::setAddress(_tree, _name, _branches, _whitelist);

  flatutils::setStatusAndAddress(_tree, _name, "pid", &pid, _branches, _whitelist);
}

void
genkintree::Parton::book(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist)
{
  Particle::book(_tree, _name, _branches, _whitelist);

  flatutils::book(_tree, _name, "pid", "", 'B', &pid, _branches, _whitelist);
}

/*static*/
std::vector<std::auto_ptr<genkintree::Parton::array_data>> genkintree::Parton::singlesData_{};
/*static*/
genkintree::SinglesPos genkintree::Parton::singlesPos_(-1, genkintree::Parton::array_data::NMAX - 1);
/*static*/
std::set<genkintree::SinglesPos> genkintree::Parton::usedSinglesPos_{};

/*static*/
genkintree::SinglesPos const&
genkintree::Parton::nextSinglesPos_()
{
  for (unsigned iC(0); iC != singlesData_.size(); ++iC) {
    singlesPos_.first = iC;
    for (singlesPos_.second = 0; singlesPos_.second != array_data::NMAX; ++singlesPos_.second) {
      if (usedSinglesPos_.find(singlesPos_) == usedSinglesPos_.end())
        break;
    }
  }

  if (singlesPos_.first == unsigned(singlesData_.size() - 1) && singlesPos_.second == array_data::NMAX - 1) {
    singlesData_.emplace_back(new array_data);
    singlesPos_.first = singlesData_.size() - 1;
    singlesPos_.second = 0;
  }

  return singlesPos_;
}

genkintree::Parton::Parton() :
  Particle(*singlesData_.at(nextSinglesPos_().first), singlesPos_.second),
  pid(singlesData_.at(singlesPos_.first)->pid[singlesPos_.second])
{
  pos_ = singlesPos_;
  usedSinglesPos_.insert(pos_);
}

genkintree::Parton::Parton(array_data& _data, UInt_t _idx) :
  Particle(_data, _idx),
  pid(_data.pid[_idx])
{
}

genkintree::Parton::Parton(Parton const& _src) :
  Particle(_src),
  pid(_src.pid)
{
}

genkintree::Parton::~Parton()
{
  if (pos_.first != unsigned(-1)) {
    usedSinglesPos_.erase(pos_);
    pos_.first = -1;
  }
}

genkintree::Parton&
genkintree::Parton::operator=(Parton const& _rhs)
{
  Particle::operator=(_rhs);

  pid = _rhs.pid;
  return *this;
}

void
genkintree::Parton::init()
{
  Particle::init();

  pid = 0;
}

genkintree::Boson::array_data::array_data() :
  ParticleM::array_data()
{
}

void
genkintree::Boson::array_data::setStatus(TTree& _tree, TString const& _name, Bool_t _status, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  ParticleM::array_data::setStatus(_tree, _name, _status, _branches, _whitelist);

  flatutils::setStatus(_tree, _name, "flavor", _status, _branches, _whitelist);
}

void
genkintree::Boson::array_data::setAddress(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  ParticleM::array_data::setAddress(_tree, _name, _branches, _whitelist);

  flatutils::setStatusAndAddress(_tree, _name, "flavor", flavor, _branches, _whitelist);
}

void
genkintree::Boson::array_data::book(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  ParticleM::array_data::book(_tree, _name, _branches, _whitelist);

  flatutils::book(_tree, _name, "flavor", "[" + _name + ".size]", 's', flavor, _branches, _whitelist);
}

void
genkintree::Boson::setStatus(TTree& _tree, TString const& _name, Bool_t _status, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  ParticleM::setStatus(_tree, _name, _status, _branches, _whitelist);

  flatutils::setStatus(_tree, _name, "flavor", _status, _branches, _whitelist);
}

void
genkintree::Boson::setAddress(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  ParticleM::setAddress(_tree, _name, _branches, _whitelist);

  flatutils::setStatusAndAddress(_tree, _name, "flavor", &flavor, _branches, _whitelist);
}

void
genkintree::Boson::book(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist)
{
  ParticleM::book(_tree, _name, _branches, _whitelist);

  flatutils::book(_tree, _name, "flavor", "", 's', &flavor, _branches, _whitelist);
}

/*static*/
std::vector<std::auto_ptr<genkintree::Boson::array_data>> genkintree::Boson::singlesData_{};
/*static*/
genkintree::SinglesPos genkintree::Boson::singlesPos_(-1, genkintree::Boson::array_data::NMAX - 1);
/*static*/
std::set<genkintree::SinglesPos> genkintree::Boson::usedSinglesPos_{};

/*static*/
genkintree::SinglesPos const&
genkintree::Boson::nextSinglesPos_()
{
  for (unsigned iC(0); iC != singlesData_.size(); ++iC) {
    singlesPos_.first = iC;
    for (singlesPos_.second = 0; singlesPos_.second != array_data::NMAX; ++singlesPos_.second) {
      if (usedSinglesPos_.find(singlesPos_) == usedSinglesPos_.end())
        break;
    }
  }

  if (singlesPos_.first == unsigned(singlesData_.size() - 1) && singlesPos_.second == array_data::NMAX - 1) {
    singlesData_.emplace_back(new array_data);
    singlesPos_.first = singlesData_.size() - 1;
    singlesPos_.second = 0;
  }

  return singlesPos_;
}

genkintree::Boson::Boson() :
  ParticleM(*singlesData_.at(nextSinglesPos_().first), singlesPos_.second),
  flavor(singlesData_.at(singlesPos_.first)->flavor[singlesPos_.second])
{
  pos_ = singlesPos_;
  usedSinglesPos_.insert(pos_);
}

genkintree::Boson::Boson(array_data& _data, UInt_t _idx) :
  ParticleM(_data, _idx),
  flavor(_data.flavor[_idx])
{
}

genkintree::Boson::Boson(Boson const& _src) :
  ParticleM(_src),
  flavor(_src.flavor)
{
}

genkintree::Boson::~Boson()
{
  if (pos_.first != unsigned(-1)) {
    usedSinglesPos_.erase(pos_);
    pos_.first = -1;
  }
}

genkintree::Boson&
genkintree::Boson::operator=(Boson const& _rhs)
{
  ParticleM::operator=(_rhs);

  flavor = _rhs.flavor;
  return *this;
}

void
genkintree::Boson::init()
{
  ParticleM::init();

  flavor = 0;
}

genkintree::Photon::array_data::array_data() :
  Particle::array_data()
{
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

  flatutils::book(_tree, _name, "isot", "[" + _name + ".size]", 'F', isot, _branches, _whitelist);
}

void
genkintree::Photon::setStatus(TTree& _tree, TString const& _name, Bool_t _status, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  Particle::setStatus(_tree, _name, _status, _branches, _whitelist);

  flatutils::setStatus(_tree, _name, "isot", _status, _branches, _whitelist);
}

void
genkintree::Photon::setAddress(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  Particle::setAddress(_tree, _name, _branches, _whitelist);

  flatutils::setStatusAndAddress(_tree, _name, "isot", &isot, _branches, _whitelist);
}

void
genkintree::Photon::book(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist)
{
  Particle::book(_tree, _name, _branches, _whitelist);

  flatutils::book(_tree, _name, "isot", "", 'F', &isot, _branches, _whitelist);
}

/*static*/
std::vector<std::auto_ptr<genkintree::Photon::array_data>> genkintree::Photon::singlesData_{};
/*static*/
genkintree::SinglesPos genkintree::Photon::singlesPos_(-1, genkintree::Photon::array_data::NMAX - 1);
/*static*/
std::set<genkintree::SinglesPos> genkintree::Photon::usedSinglesPos_{};

/*static*/
genkintree::SinglesPos const&
genkintree::Photon::nextSinglesPos_()
{
  for (unsigned iC(0); iC != singlesData_.size(); ++iC) {
    singlesPos_.first = iC;
    for (singlesPos_.second = 0; singlesPos_.second != array_data::NMAX; ++singlesPos_.second) {
      if (usedSinglesPos_.find(singlesPos_) == usedSinglesPos_.end())
        break;
    }
  }

  if (singlesPos_.first == unsigned(singlesData_.size() - 1) && singlesPos_.second == array_data::NMAX - 1) {
    singlesData_.emplace_back(new array_data);
    singlesPos_.first = singlesData_.size() - 1;
    singlesPos_.second = 0;
  }

  return singlesPos_;
}

genkintree::Photon::Photon() :
  Particle(*singlesData_.at(nextSinglesPos_().first), singlesPos_.second),
  isot(singlesData_.at(singlesPos_.first)->isot[singlesPos_.second])
{
  pos_ = singlesPos_;
  usedSinglesPos_.insert(pos_);
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

genkintree::Photon::~Photon()
{
  if (pos_.first != unsigned(-1)) {
    usedSinglesPos_.erase(pos_);
    pos_.first = -1;
  }
}

genkintree::Photon&
genkintree::Photon::operator=(Photon const& _rhs)
{
  Particle::operator=(_rhs);

  isot = _rhs.isot;
  return *this;
}

void
genkintree::Photon::init()
{
  Particle::init();

  isot = 0.;
}

genkintree::Lepton::array_data::array_data() :
  Particle::array_data()
{
}

void
genkintree::Lepton::array_data::setStatus(TTree& _tree, TString const& _name, Bool_t _status, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  Particle::array_data::setStatus(_tree, _name, _status, _branches, _whitelist);

  flatutils::setStatus(_tree, _name, "charge", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "minDRJ", _status, _branches, _whitelist);
}

void
genkintree::Lepton::array_data::setAddress(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  Particle::array_data::setAddress(_tree, _name, _branches, _whitelist);

  flatutils::setStatusAndAddress(_tree, _name, "charge", charge, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "minDRJ", minDRJ, _branches, _whitelist);
}

void
genkintree::Lepton::array_data::book(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  Particle::array_data::book(_tree, _name, _branches, _whitelist);

  flatutils::book(_tree, _name, "charge", "[" + _name + ".size]", 'B', charge, _branches, _whitelist);
  flatutils::book(_tree, _name, "minDRJ", "[" + _name + ".size]", 'F', minDRJ, _branches, _whitelist);
}

void
genkintree::Lepton::setStatus(TTree& _tree, TString const& _name, Bool_t _status, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  Particle::setStatus(_tree, _name, _status, _branches, _whitelist);

  flatutils::setStatus(_tree, _name, "charge", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "minDRJ", _status, _branches, _whitelist);
}

void
genkintree::Lepton::setAddress(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  Particle::setAddress(_tree, _name, _branches, _whitelist);

  flatutils::setStatusAndAddress(_tree, _name, "charge", &charge, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "minDRJ", &minDRJ, _branches, _whitelist);
}

void
genkintree::Lepton::book(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist)
{
  Particle::book(_tree, _name, _branches, _whitelist);

  flatutils::book(_tree, _name, "charge", "", 'B', &charge, _branches, _whitelist);
  flatutils::book(_tree, _name, "minDRJ", "", 'F', &minDRJ, _branches, _whitelist);
}

/*static*/
std::vector<std::auto_ptr<genkintree::Lepton::array_data>> genkintree::Lepton::singlesData_{};
/*static*/
genkintree::SinglesPos genkintree::Lepton::singlesPos_(-1, genkintree::Lepton::array_data::NMAX - 1);
/*static*/
std::set<genkintree::SinglesPos> genkintree::Lepton::usedSinglesPos_{};

/*static*/
genkintree::SinglesPos const&
genkintree::Lepton::nextSinglesPos_()
{
  for (unsigned iC(0); iC != singlesData_.size(); ++iC) {
    singlesPos_.first = iC;
    for (singlesPos_.second = 0; singlesPos_.second != array_data::NMAX; ++singlesPos_.second) {
      if (usedSinglesPos_.find(singlesPos_) == usedSinglesPos_.end())
        break;
    }
  }

  if (singlesPos_.first == unsigned(singlesData_.size() - 1) && singlesPos_.second == array_data::NMAX - 1) {
    singlesData_.emplace_back(new array_data);
    singlesPos_.first = singlesData_.size() - 1;
    singlesPos_.second = 0;
  }

  return singlesPos_;
}

genkintree::Lepton::Lepton() :
  Particle(*singlesData_.at(nextSinglesPos_().first), singlesPos_.second),
  charge(singlesData_.at(singlesPos_.first)->charge[singlesPos_.second]),
  minDRJ(singlesData_.at(singlesPos_.first)->minDRJ[singlesPos_.second])
{
  pos_ = singlesPos_;
  usedSinglesPos_.insert(pos_);
}

genkintree::Lepton::Lepton(array_data& _data, UInt_t _idx) :
  Particle(_data, _idx),
  charge(_data.charge[_idx]),
  minDRJ(_data.minDRJ[_idx])
{
}

genkintree::Lepton::Lepton(Lepton const& _src) :
  Particle(_src),
  charge(_src.charge),
  minDRJ(_src.minDRJ)
{
}

genkintree::Lepton::~Lepton()
{
  if (pos_.first != unsigned(-1)) {
    usedSinglesPos_.erase(pos_);
    pos_.first = -1;
  }
}

genkintree::Lepton&
genkintree::Lepton::operator=(Lepton const& _rhs)
{
  Particle::operator=(_rhs);

  charge = _rhs.charge;
  minDRJ = _rhs.minDRJ;
  return *this;
}

void
genkintree::Lepton::init()
{
  Particle::init();

  charge = 0;
  minDRJ = 0.;
}

genkintree::Met::Met(TString const& _name) :
  name_(_name)
{
}

genkintree::Met::Met(Met const& _src) :
  name_(_src.name_),
  pt(_src.pt),
  phi(_src.phi)
{
}

genkintree::Met::~Met()
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

void
genkintree::Met::setStatus(TTree& _tree, TString const& _name, Bool_t _status, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  flatutils::setStatus(_tree, _name, "pt", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "phi", _status, _branches, _whitelist);
}

void
genkintree::Met::setAddress(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  flatutils::setStatusAndAddress(_tree, _name, "pt", &pt, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "phi", &phi, _branches, _whitelist);
}

void
genkintree::Met::book(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist)
{
  flatutils::book(_tree, _name, "pt", "", 'F', &pt, _branches, _whitelist);
  flatutils::book(_tree, _name, "phi", "", 'F', &phi, _branches, _whitelist);
}

genkintree::Met&
genkintree::Met::operator=(Met const& _rhs)
{
  pt = _rhs.pt;
  phi = _rhs.phi;
  return *this;
}

void
genkintree::Met::init()
{
  pt = 0.;
  phi = 0.;
}

