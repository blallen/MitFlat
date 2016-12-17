#include "../interface/Objects_simpletree.h"
#include "TTree.h"

#include <algorithm>

namespace simpletree {

  TString PhotonL1ObjectName[] = {
    "fSEG34IorSEG40",
    "fSEG40IorSJet200",
    "fSEG34IorSEG40IorSJet200",
    "fSEG24",
    "fSEG30",
    "fSEG40"
  };

  TString PhotonHLTObjectName[] = {
    "fPh120",
    "fPh135",
    "fPh165HE10",
    "fPh175",
    "fPh22EBR9Iso",
    "fPh36EBR9Iso",
    "fPh50EBR9Iso",
    "fPh75EBR9Iso",
    "fPh90EBR9Iso",
    "fPh120EBR9Iso"
  };

  TString ElectronHLTObjectName[] = {
    "fEl27ERLoose",
    "fEl27Tight",
    "fEl120Ph",
    "fEl135Ph",
    "fEl165HE10Ph",
    "fEl175Ph",
    "fEl22EBR9IsoPh",
    "fEl36EBR9IsoPh",
    "fEl50EBR9IsoPh",
    "fEl75EBR9IsoPh",
    "fEl90EBR9IsoPh",
    "fEl120EBR9IsoPh"
  };

  TString MuonHLTObjectName[] = {
    "fMu20",
    "fMuTrk20",
    "fMu24",
    "fMu27"
  };

}

simpletree::Particle::array_data::array_data()
{
}

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
  flatutils::book(_tree, _name, "pt", "[" + _name + ".size]", 'F', pt, _branches, _whitelist);
  flatutils::book(_tree, _name, "eta", "[" + _name + ".size]", 'F', eta, _branches, _whitelist);
  flatutils::book(_tree, _name, "phi", "[" + _name + ".size]", 'F', phi, _branches, _whitelist);
}

void
simpletree::Particle::setStatus(TTree& _tree, TString const& _name, Bool_t _status, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  flatutils::setStatus(_tree, _name, "pt", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "eta", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "phi", _status, _branches, _whitelist);
}

void
simpletree::Particle::setAddress(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  flatutils::setStatusAndAddress(_tree, _name, "pt", &pt, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "eta", &eta, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "phi", &phi, _branches, _whitelist);
}

void
simpletree::Particle::book(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist)
{
  flatutils::book(_tree, _name, "pt", "", 'F', &pt, _branches, _whitelist);
  flatutils::book(_tree, _name, "eta", "", 'F', &eta, _branches, _whitelist);
  flatutils::book(_tree, _name, "phi", "", 'F', &phi, _branches, _whitelist);
}

/*static*/
std::vector<std::auto_ptr<simpletree::Particle::array_data>> simpletree::Particle::singlesData_{};
/*static*/
simpletree::SinglesPos simpletree::Particle::singlesPos_(-1, simpletree::Particle::array_data::NMAX - 1);
/*static*/
std::set<simpletree::SinglesPos> simpletree::Particle::usedSinglesPos_{};

/*static*/
simpletree::SinglesPos const&
simpletree::Particle::nextSinglesPos_()
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

simpletree::Particle::Particle() :
  pos_(nextSinglesPos_()),
  pt(singlesData_.at(singlesPos_.first)->pt[singlesPos_.second]),
  eta(singlesData_.at(singlesPos_.first)->eta[singlesPos_.second]),
  phi(singlesData_.at(singlesPos_.first)->phi[singlesPos_.second])
{
  usedSinglesPos_.insert(pos_);
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

simpletree::Particle::~Particle()
{
  if (pos_.first != unsigned(-1)) {
    usedSinglesPos_.erase(pos_);
    pos_.first = -1;
  }
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

simpletree::ParticleM::array_data::array_data() :
  Particle::array_data()
{
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

  flatutils::book(_tree, _name, "mass", "[" + _name + ".size]", 'F', mass, _branches, _whitelist);
}

void
simpletree::ParticleM::setStatus(TTree& _tree, TString const& _name, Bool_t _status, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  Particle::setStatus(_tree, _name, _status, _branches, _whitelist);

  flatutils::setStatus(_tree, _name, "mass", _status, _branches, _whitelist);
}

void
simpletree::ParticleM::setAddress(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  Particle::setAddress(_tree, _name, _branches, _whitelist);

  flatutils::setStatusAndAddress(_tree, _name, "mass", &mass, _branches, _whitelist);
}

void
simpletree::ParticleM::book(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist)
{
  Particle::book(_tree, _name, _branches, _whitelist);

  flatutils::book(_tree, _name, "mass", "", 'F', &mass, _branches, _whitelist);
}

/*static*/
std::vector<std::auto_ptr<simpletree::ParticleM::array_data>> simpletree::ParticleM::singlesData_{};
/*static*/
simpletree::SinglesPos simpletree::ParticleM::singlesPos_(-1, simpletree::ParticleM::array_data::NMAX - 1);
/*static*/
std::set<simpletree::SinglesPos> simpletree::ParticleM::usedSinglesPos_{};

/*static*/
simpletree::SinglesPos const&
simpletree::ParticleM::nextSinglesPos_()
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

simpletree::ParticleM::ParticleM() :
  Particle(*singlesData_.at(nextSinglesPos_().first), singlesPos_.second),
  mass(singlesData_.at(singlesPos_.first)->mass[singlesPos_.second])
{
  pos_ = singlesPos_;
  usedSinglesPos_.insert(pos_);
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

simpletree::ParticleM::~ParticleM()
{
  if (pos_.first != unsigned(-1)) {
    usedSinglesPos_.erase(pos_);
    pos_.first = -1;
  }
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

simpletree::RecoParticle::array_data::array_data() :
  Particle::array_data()
{
}

void
simpletree::RecoParticle::array_data::setStatus(TTree& _tree, TString const& _name, Bool_t _status, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  Particle::array_data::setStatus(_tree, _name, _status, _branches, _whitelist);

  flatutils::setStatus(_tree, _name, "loose", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "medium", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "tight", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "matchedGen", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "matchHLT", _status, _branches, _whitelist);
}

void
simpletree::RecoParticle::array_data::setAddress(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  Particle::array_data::setAddress(_tree, _name, _branches, _whitelist);

  flatutils::setStatusAndAddress(_tree, _name, "loose", loose, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "medium", medium, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "tight", tight, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "matchedGen", matchedGen, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "matchHLT", matchHLT, _branches, _whitelist);
}

void
simpletree::RecoParticle::array_data::book(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  Particle::array_data::book(_tree, _name, _branches, _whitelist);

  flatutils::book(_tree, _name, "loose", "[" + _name + ".size]", 'O', loose, _branches, _whitelist);
  flatutils::book(_tree, _name, "medium", "[" + _name + ".size]", 'O', medium, _branches, _whitelist);
  flatutils::book(_tree, _name, "tight", "[" + _name + ".size]", 'O', tight, _branches, _whitelist);
  flatutils::book(_tree, _name, "matchedGen", "[" + _name + ".size]", 'I', matchedGen, _branches, _whitelist);
  flatutils::book(_tree, _name, "matchHLT", TString::Format("[" + _name + ".size][%d]", nMaxHLTObjects), 'O', matchHLT, _branches, _whitelist);
}

void
simpletree::RecoParticle::setStatus(TTree& _tree, TString const& _name, Bool_t _status, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  Particle::setStatus(_tree, _name, _status, _branches, _whitelist);

  flatutils::setStatus(_tree, _name, "loose", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "medium", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "tight", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "matchedGen", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "matchHLT", _status, _branches, _whitelist);
}

void
simpletree::RecoParticle::setAddress(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  Particle::setAddress(_tree, _name, _branches, _whitelist);

  flatutils::setStatusAndAddress(_tree, _name, "loose", &loose, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "medium", &medium, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "tight", &tight, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "matchedGen", &matchedGen, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "matchHLT", matchHLT, _branches, _whitelist);
}

void
simpletree::RecoParticle::book(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist)
{
  Particle::book(_tree, _name, _branches, _whitelist);

  flatutils::book(_tree, _name, "loose", "", 'O', &loose, _branches, _whitelist);
  flatutils::book(_tree, _name, "medium", "", 'O', &medium, _branches, _whitelist);
  flatutils::book(_tree, _name, "tight", "", 'O', &tight, _branches, _whitelist);
  flatutils::book(_tree, _name, "matchedGen", "", 'I', &matchedGen, _branches, _whitelist);
  flatutils::book(_tree, _name, "matchHLT", TString::Format("[%d]", nMaxHLTObjects), 'O', matchHLT, _branches, _whitelist);
}

/*static*/
std::vector<std::auto_ptr<simpletree::RecoParticle::array_data>> simpletree::RecoParticle::singlesData_{};
/*static*/
simpletree::SinglesPos simpletree::RecoParticle::singlesPos_(-1, simpletree::RecoParticle::array_data::NMAX - 1);
/*static*/
std::set<simpletree::SinglesPos> simpletree::RecoParticle::usedSinglesPos_{};

/*static*/
simpletree::SinglesPos const&
simpletree::RecoParticle::nextSinglesPos_()
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

simpletree::RecoParticle::RecoParticle() :
  Particle(*singlesData_.at(nextSinglesPos_().first), singlesPos_.second),
  loose(singlesData_.at(singlesPos_.first)->loose[singlesPos_.second]),
  medium(singlesData_.at(singlesPos_.first)->medium[singlesPos_.second]),
  tight(singlesData_.at(singlesPos_.first)->tight[singlesPos_.second]),
  matchedGen(singlesData_.at(singlesPos_.first)->matchedGen[singlesPos_.second]),
  matchHLT(singlesData_.at(singlesPos_.first)->matchHLT[singlesPos_.second])
{
  pos_ = singlesPos_;
  usedSinglesPos_.insert(pos_);
}

simpletree::RecoParticle::RecoParticle(array_data& _data, UInt_t _idx) :
  Particle(_data, _idx),
  loose(_data.loose[_idx]),
  medium(_data.medium[_idx]),
  tight(_data.tight[_idx]),
  matchedGen(_data.matchedGen[_idx]),
  matchHLT(_data.matchHLT[_idx])
{
}

simpletree::RecoParticle::RecoParticle(RecoParticle const& _src) :
  Particle(_src),
  loose(_src.loose),
  medium(_src.medium),
  tight(_src.tight),
  matchedGen(_src.matchedGen)
{
  std::copy_n(_src.matchHLT, nMaxHLTObjects, matchHLT);
}

simpletree::RecoParticle::~RecoParticle()
{
  if (pos_.first != unsigned(-1)) {
    usedSinglesPos_.erase(pos_);
    pos_.first = -1;
  }
}

simpletree::RecoParticle&
simpletree::RecoParticle::operator=(RecoParticle const& _rhs)
{
  Particle::operator=(_rhs);

  loose = _rhs.loose;
  medium = _rhs.medium;
  tight = _rhs.tight;
  matchedGen = _rhs.matchedGen;
  std::copy_n(_rhs.matchHLT, nMaxHLTObjects, matchHLT);
  return *this;
}

void
simpletree::RecoParticle::init()
{
  Particle::init();

  loose = false;
  medium = false;
  tight = false;
  matchedGen = 0;
  std::fill(matchHLT, matchHLT + nMaxHLTObjects, false);
}

simpletree::RecoParticleM::array_data::array_data() :
  RecoParticle::array_data()
{
}

void
simpletree::RecoParticleM::array_data::setStatus(TTree& _tree, TString const& _name, Bool_t _status, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  RecoParticle::array_data::setStatus(_tree, _name, _status, _branches, _whitelist);

  flatutils::setStatus(_tree, _name, "mass", _status, _branches, _whitelist);
}

void
simpletree::RecoParticleM::array_data::setAddress(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  RecoParticle::array_data::setAddress(_tree, _name, _branches, _whitelist);

  flatutils::setStatusAndAddress(_tree, _name, "mass", mass, _branches, _whitelist);
}

void
simpletree::RecoParticleM::array_data::book(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  RecoParticle::array_data::book(_tree, _name, _branches, _whitelist);

  flatutils::book(_tree, _name, "mass", "[" + _name + ".size]", 'F', mass, _branches, _whitelist);
}

void
simpletree::RecoParticleM::setStatus(TTree& _tree, TString const& _name, Bool_t _status, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  RecoParticle::setStatus(_tree, _name, _status, _branches, _whitelist);

  flatutils::setStatus(_tree, _name, "mass", _status, _branches, _whitelist);
}

void
simpletree::RecoParticleM::setAddress(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  RecoParticle::setAddress(_tree, _name, _branches, _whitelist);

  flatutils::setStatusAndAddress(_tree, _name, "mass", &mass, _branches, _whitelist);
}

void
simpletree::RecoParticleM::book(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist)
{
  RecoParticle::book(_tree, _name, _branches, _whitelist);

  flatutils::book(_tree, _name, "mass", "", 'F', &mass, _branches, _whitelist);
}

/*static*/
std::vector<std::auto_ptr<simpletree::RecoParticleM::array_data>> simpletree::RecoParticleM::singlesData_{};
/*static*/
simpletree::SinglesPos simpletree::RecoParticleM::singlesPos_(-1, simpletree::RecoParticleM::array_data::NMAX - 1);
/*static*/
std::set<simpletree::SinglesPos> simpletree::RecoParticleM::usedSinglesPos_{};

/*static*/
simpletree::SinglesPos const&
simpletree::RecoParticleM::nextSinglesPos_()
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

simpletree::RecoParticleM::RecoParticleM() :
  RecoParticle(*singlesData_.at(nextSinglesPos_().first), singlesPos_.second),
  mass(singlesData_.at(singlesPos_.first)->mass[singlesPos_.second])
{
  pos_ = singlesPos_;
  usedSinglesPos_.insert(pos_);
}

simpletree::RecoParticleM::RecoParticleM(array_data& _data, UInt_t _idx) :
  RecoParticle(_data, _idx),
  mass(_data.mass[_idx])
{
}

simpletree::RecoParticleM::RecoParticleM(RecoParticleM const& _src) :
  RecoParticle(_src),
  mass(_src.mass)
{
}

simpletree::RecoParticleM::~RecoParticleM()
{
  if (pos_.first != unsigned(-1)) {
    usedSinglesPos_.erase(pos_);
    pos_.first = -1;
  }
}

simpletree::RecoParticleM&
simpletree::RecoParticleM::operator=(RecoParticleM const& _rhs)
{
  RecoParticle::operator=(_rhs);

  mass = _rhs.mass;
  return *this;
}

void
simpletree::RecoParticleM::init()
{
  RecoParticle::init();

  mass = 0.;
}

simpletree::Photon::array_data::array_data() :
  RecoParticle::array_data()
{
}

void
simpletree::Photon::array_data::setStatus(TTree& _tree, TString const& _name, Bool_t _status, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  RecoParticle::array_data::setStatus(_tree, _name, _status, _branches, _whitelist);

  flatutils::setStatus(_tree, _name, "scRawPt", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "chIso", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "chWorstIso", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "chIsoMax", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "nhIso", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "phIso", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "nhIsoS16", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "phIsoS16", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "ecalIso", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "hcalIso", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "sieie", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "sipip", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "sieip", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "hOverE", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "genIso", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "mipEnergy", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "mipChi2", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "mipSlope", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "mipIntercept", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "mipNhitCone", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "mipIsHalo", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "scPt", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "scEta", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "scPhi", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "e13", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "e31", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "e15", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "e22", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "e25", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "e33", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "e44", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "e55", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "emax", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "e2nd", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "e4", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "r9", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "etaWidth", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "phiWidth", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "time", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "timeSpan", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "genMatchDR", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "isEB", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "pixelVeto", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "electronVeto", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "csafeVeto", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "highpt", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "matchL1", _status, _branches, _whitelist);
}

void
simpletree::Photon::array_data::setAddress(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  RecoParticle::array_data::setAddress(_tree, _name, _branches, _whitelist);

  flatutils::setStatusAndAddress(_tree, _name, "scRawPt", scRawPt, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "chIso", chIso, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "chWorstIso", chWorstIso, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "chIsoMax", chIsoMax, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "nhIso", nhIso, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "phIso", phIso, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "nhIsoS16", nhIsoS16, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "phIsoS16", phIsoS16, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "ecalIso", ecalIso, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "hcalIso", hcalIso, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "sieie", sieie, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "sipip", sipip, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "sieip", sieip, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "hOverE", hOverE, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "genIso", genIso, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "mipEnergy", mipEnergy, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "mipChi2", mipChi2, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "mipSlope", mipSlope, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "mipIntercept", mipIntercept, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "mipNhitCone", mipNhitCone, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "mipIsHalo", mipIsHalo, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "scPt", scPt, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "scEta", scEta, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "scPhi", scPhi, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "e13", e13, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "e31", e31, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "e15", e15, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "e22", e22, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "e25", e25, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "e33", e33, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "e44", e44, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "e55", e55, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "emax", emax, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "e2nd", e2nd, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "e4", e4, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "r9", r9, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "etaWidth", etaWidth, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "phiWidth", phiWidth, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "time", time, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "timeSpan", timeSpan, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "genMatchDR", genMatchDR, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "isEB", isEB, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "pixelVeto", pixelVeto, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "electronVeto", electronVeto, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "csafeVeto", csafeVeto, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "highpt", highpt, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "matchL1", matchL1, _branches, _whitelist);
}

void
simpletree::Photon::array_data::book(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  RecoParticle::array_data::book(_tree, _name, _branches, _whitelist);

  flatutils::book(_tree, _name, "scRawPt", "[" + _name + ".size]", 'F', scRawPt, _branches, _whitelist);
  flatutils::book(_tree, _name, "chIso", "[" + _name + ".size]", 'F', chIso, _branches, _whitelist);
  flatutils::book(_tree, _name, "chWorstIso", "[" + _name + ".size]", 'F', chWorstIso, _branches, _whitelist);
  flatutils::book(_tree, _name, "chIsoMax", "[" + _name + ".size]", 'F', chIsoMax, _branches, _whitelist);
  flatutils::book(_tree, _name, "nhIso", "[" + _name + ".size]", 'F', nhIso, _branches, _whitelist);
  flatutils::book(_tree, _name, "phIso", "[" + _name + ".size]", 'F', phIso, _branches, _whitelist);
  flatutils::book(_tree, _name, "nhIsoS16", "[" + _name + ".size]", 'F', nhIsoS16, _branches, _whitelist);
  flatutils::book(_tree, _name, "phIsoS16", "[" + _name + ".size]", 'F', phIsoS16, _branches, _whitelist);
  flatutils::book(_tree, _name, "ecalIso", "[" + _name + ".size]", 'F', ecalIso, _branches, _whitelist);
  flatutils::book(_tree, _name, "hcalIso", "[" + _name + ".size]", 'F', hcalIso, _branches, _whitelist);
  flatutils::book(_tree, _name, "sieie", "[" + _name + ".size]", 'F', sieie, _branches, _whitelist);
  flatutils::book(_tree, _name, "sipip", "[" + _name + ".size]", 'F', sipip, _branches, _whitelist);
  flatutils::book(_tree, _name, "sieip", "[" + _name + ".size]", 'F', sieip, _branches, _whitelist);
  flatutils::book(_tree, _name, "hOverE", "[" + _name + ".size]", 'F', hOverE, _branches, _whitelist);
  flatutils::book(_tree, _name, "genIso", "[" + _name + ".size]", 'F', genIso, _branches, _whitelist);
  flatutils::book(_tree, _name, "mipEnergy", "[" + _name + ".size]", 'F', mipEnergy, _branches, _whitelist);
  flatutils::book(_tree, _name, "mipChi2", "[" + _name + ".size]", 'F', mipChi2, _branches, _whitelist);
  flatutils::book(_tree, _name, "mipSlope", "[" + _name + ".size]", 'F', mipSlope, _branches, _whitelist);
  flatutils::book(_tree, _name, "mipIntercept", "[" + _name + ".size]", 'F', mipIntercept, _branches, _whitelist);
  flatutils::book(_tree, _name, "mipNhitCone", "[" + _name + ".size]", 's', mipNhitCone, _branches, _whitelist);
  flatutils::book(_tree, _name, "mipIsHalo", "[" + _name + ".size]", 'O', mipIsHalo, _branches, _whitelist);
  flatutils::book(_tree, _name, "scPt", "[" + _name + ".size]", 'F', scPt, _branches, _whitelist);
  flatutils::book(_tree, _name, "scEta", "[" + _name + ".size]", 'F', scEta, _branches, _whitelist);
  flatutils::book(_tree, _name, "scPhi", "[" + _name + ".size]", 'F', scPhi, _branches, _whitelist);
  flatutils::book(_tree, _name, "e13", "[" + _name + ".size]", 'F', e13, _branches, _whitelist);
  flatutils::book(_tree, _name, "e31", "[" + _name + ".size]", 'F', e31, _branches, _whitelist);
  flatutils::book(_tree, _name, "e15", "[" + _name + ".size]", 'F', e15, _branches, _whitelist);
  flatutils::book(_tree, _name, "e22", "[" + _name + ".size]", 'F', e22, _branches, _whitelist);
  flatutils::book(_tree, _name, "e25", "[" + _name + ".size]", 'F', e25, _branches, _whitelist);
  flatutils::book(_tree, _name, "e33", "[" + _name + ".size]", 'F', e33, _branches, _whitelist);
  flatutils::book(_tree, _name, "e44", "[" + _name + ".size]", 'F', e44, _branches, _whitelist);
  flatutils::book(_tree, _name, "e55", "[" + _name + ".size]", 'F', e55, _branches, _whitelist);
  flatutils::book(_tree, _name, "emax", "[" + _name + ".size]", 'F', emax, _branches, _whitelist);
  flatutils::book(_tree, _name, "e2nd", "[" + _name + ".size]", 'F', e2nd, _branches, _whitelist);
  flatutils::book(_tree, _name, "e4", "[" + _name + ".size]", 'F', e4, _branches, _whitelist);
  flatutils::book(_tree, _name, "r9", "[" + _name + ".size]", 'F', r9, _branches, _whitelist);
  flatutils::book(_tree, _name, "etaWidth", "[" + _name + ".size]", 'F', etaWidth, _branches, _whitelist);
  flatutils::book(_tree, _name, "phiWidth", "[" + _name + ".size]", 'F', phiWidth, _branches, _whitelist);
  flatutils::book(_tree, _name, "time", "[" + _name + ".size]", 'F', time, _branches, _whitelist);
  flatutils::book(_tree, _name, "timeSpan", "[" + _name + ".size]", 'F', timeSpan, _branches, _whitelist);
  flatutils::book(_tree, _name, "genMatchDR", "[" + _name + ".size]", 'F', genMatchDR, _branches, _whitelist);
  flatutils::book(_tree, _name, "isEB", "[" + _name + ".size]", 'O', isEB, _branches, _whitelist);
  flatutils::book(_tree, _name, "pixelVeto", "[" + _name + ".size]", 'O', pixelVeto, _branches, _whitelist);
  flatutils::book(_tree, _name, "electronVeto", "[" + _name + ".size]", 'O', electronVeto, _branches, _whitelist);
  flatutils::book(_tree, _name, "csafeVeto", "[" + _name + ".size]", 'O', csafeVeto, _branches, _whitelist);
  flatutils::book(_tree, _name, "highpt", "[" + _name + ".size]", 'O', highpt, _branches, _whitelist);
  flatutils::book(_tree, _name, "matchL1", TString::Format("[" + _name + ".size][%d]", nPhotonL1Objects), 'O', matchL1, _branches, _whitelist);
}

void
simpletree::Photon::setStatus(TTree& _tree, TString const& _name, Bool_t _status, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  RecoParticle::setStatus(_tree, _name, _status, _branches, _whitelist);

  flatutils::setStatus(_tree, _name, "scRawPt", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "chIso", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "chWorstIso", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "chIsoMax", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "nhIso", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "phIso", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "nhIsoS16", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "phIsoS16", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "ecalIso", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "hcalIso", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "sieie", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "sipip", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "sieip", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "hOverE", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "genIso", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "mipEnergy", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "mipChi2", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "mipSlope", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "mipIntercept", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "mipNhitCone", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "mipIsHalo", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "scPt", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "scEta", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "scPhi", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "e13", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "e31", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "e15", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "e22", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "e25", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "e33", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "e44", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "e55", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "emax", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "e2nd", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "e4", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "r9", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "etaWidth", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "phiWidth", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "time", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "timeSpan", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "genMatchDR", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "isEB", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "pixelVeto", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "electronVeto", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "csafeVeto", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "highpt", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "matchL1", _status, _branches, _whitelist);
}

void
simpletree::Photon::setAddress(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  RecoParticle::setAddress(_tree, _name, _branches, _whitelist);

  flatutils::setStatusAndAddress(_tree, _name, "scRawPt", &scRawPt, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "chIso", &chIso, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "chWorstIso", &chWorstIso, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "chIsoMax", &chIsoMax, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "nhIso", &nhIso, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "phIso", &phIso, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "nhIsoS16", &nhIsoS16, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "phIsoS16", &phIsoS16, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "ecalIso", &ecalIso, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "hcalIso", &hcalIso, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "sieie", &sieie, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "sipip", &sipip, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "sieip", &sieip, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "hOverE", &hOverE, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "genIso", &genIso, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "mipEnergy", &mipEnergy, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "mipChi2", &mipChi2, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "mipSlope", &mipSlope, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "mipIntercept", &mipIntercept, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "mipNhitCone", &mipNhitCone, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "mipIsHalo", &mipIsHalo, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "scPt", &scPt, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "scEta", &scEta, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "scPhi", &scPhi, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "e13", &e13, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "e31", &e31, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "e15", &e15, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "e22", &e22, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "e25", &e25, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "e33", &e33, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "e44", &e44, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "e55", &e55, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "emax", &emax, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "e2nd", &e2nd, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "e4", &e4, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "r9", &r9, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "etaWidth", &etaWidth, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "phiWidth", &phiWidth, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "time", &time, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "timeSpan", &timeSpan, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "genMatchDR", &genMatchDR, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "isEB", &isEB, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "pixelVeto", &pixelVeto, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "electronVeto", &electronVeto, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "csafeVeto", &csafeVeto, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "highpt", &highpt, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "matchL1", matchL1, _branches, _whitelist);
}

void
simpletree::Photon::book(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist)
{
  RecoParticle::book(_tree, _name, _branches, _whitelist);

  flatutils::book(_tree, _name, "scRawPt", "", 'F', &scRawPt, _branches, _whitelist);
  flatutils::book(_tree, _name, "chIso", "", 'F', &chIso, _branches, _whitelist);
  flatutils::book(_tree, _name, "chWorstIso", "", 'F', &chWorstIso, _branches, _whitelist);
  flatutils::book(_tree, _name, "chIsoMax", "", 'F', &chIsoMax, _branches, _whitelist);
  flatutils::book(_tree, _name, "nhIso", "", 'F', &nhIso, _branches, _whitelist);
  flatutils::book(_tree, _name, "phIso", "", 'F', &phIso, _branches, _whitelist);
  flatutils::book(_tree, _name, "nhIsoS16", "", 'F', &nhIsoS16, _branches, _whitelist);
  flatutils::book(_tree, _name, "phIsoS16", "", 'F', &phIsoS16, _branches, _whitelist);
  flatutils::book(_tree, _name, "ecalIso", "", 'F', &ecalIso, _branches, _whitelist);
  flatutils::book(_tree, _name, "hcalIso", "", 'F', &hcalIso, _branches, _whitelist);
  flatutils::book(_tree, _name, "sieie", "", 'F', &sieie, _branches, _whitelist);
  flatutils::book(_tree, _name, "sipip", "", 'F', &sipip, _branches, _whitelist);
  flatutils::book(_tree, _name, "sieip", "", 'F', &sieip, _branches, _whitelist);
  flatutils::book(_tree, _name, "hOverE", "", 'F', &hOverE, _branches, _whitelist);
  flatutils::book(_tree, _name, "genIso", "", 'F', &genIso, _branches, _whitelist);
  flatutils::book(_tree, _name, "mipEnergy", "", 'F', &mipEnergy, _branches, _whitelist);
  flatutils::book(_tree, _name, "mipChi2", "", 'F', &mipChi2, _branches, _whitelist);
  flatutils::book(_tree, _name, "mipSlope", "", 'F', &mipSlope, _branches, _whitelist);
  flatutils::book(_tree, _name, "mipIntercept", "", 'F', &mipIntercept, _branches, _whitelist);
  flatutils::book(_tree, _name, "mipNhitCone", "", 's', &mipNhitCone, _branches, _whitelist);
  flatutils::book(_tree, _name, "mipIsHalo", "", 'O', &mipIsHalo, _branches, _whitelist);
  flatutils::book(_tree, _name, "scPt", "", 'F', &scPt, _branches, _whitelist);
  flatutils::book(_tree, _name, "scEta", "", 'F', &scEta, _branches, _whitelist);
  flatutils::book(_tree, _name, "scPhi", "", 'F', &scPhi, _branches, _whitelist);
  flatutils::book(_tree, _name, "e13", "", 'F', &e13, _branches, _whitelist);
  flatutils::book(_tree, _name, "e31", "", 'F', &e31, _branches, _whitelist);
  flatutils::book(_tree, _name, "e15", "", 'F', &e15, _branches, _whitelist);
  flatutils::book(_tree, _name, "e22", "", 'F', &e22, _branches, _whitelist);
  flatutils::book(_tree, _name, "e25", "", 'F', &e25, _branches, _whitelist);
  flatutils::book(_tree, _name, "e33", "", 'F', &e33, _branches, _whitelist);
  flatutils::book(_tree, _name, "e44", "", 'F', &e44, _branches, _whitelist);
  flatutils::book(_tree, _name, "e55", "", 'F', &e55, _branches, _whitelist);
  flatutils::book(_tree, _name, "emax", "", 'F', &emax, _branches, _whitelist);
  flatutils::book(_tree, _name, "e2nd", "", 'F', &e2nd, _branches, _whitelist);
  flatutils::book(_tree, _name, "e4", "", 'F', &e4, _branches, _whitelist);
  flatutils::book(_tree, _name, "r9", "", 'F', &r9, _branches, _whitelist);
  flatutils::book(_tree, _name, "etaWidth", "", 'F', &etaWidth, _branches, _whitelist);
  flatutils::book(_tree, _name, "phiWidth", "", 'F', &phiWidth, _branches, _whitelist);
  flatutils::book(_tree, _name, "time", "", 'F', &time, _branches, _whitelist);
  flatutils::book(_tree, _name, "timeSpan", "", 'F', &timeSpan, _branches, _whitelist);
  flatutils::book(_tree, _name, "genMatchDR", "", 'F', &genMatchDR, _branches, _whitelist);
  flatutils::book(_tree, _name, "isEB", "", 'O', &isEB, _branches, _whitelist);
  flatutils::book(_tree, _name, "pixelVeto", "", 'O', &pixelVeto, _branches, _whitelist);
  flatutils::book(_tree, _name, "electronVeto", "", 'O', &electronVeto, _branches, _whitelist);
  flatutils::book(_tree, _name, "csafeVeto", "", 'O', &csafeVeto, _branches, _whitelist);
  flatutils::book(_tree, _name, "highpt", "", 'O', &highpt, _branches, _whitelist);
  flatutils::book(_tree, _name, "matchL1", TString::Format("[%d]", nPhotonL1Objects), 'O', matchL1, _branches, _whitelist);
}

/*static*/
std::vector<std::auto_ptr<simpletree::Photon::array_data>> simpletree::Photon::singlesData_{};
/*static*/
simpletree::SinglesPos simpletree::Photon::singlesPos_(-1, simpletree::Photon::array_data::NMAX - 1);
/*static*/
std::set<simpletree::SinglesPos> simpletree::Photon::usedSinglesPos_{};

/*static*/
simpletree::SinglesPos const&
simpletree::Photon::nextSinglesPos_()
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

simpletree::Photon::Photon() :
  RecoParticle(*singlesData_.at(nextSinglesPos_().first), singlesPos_.second),
  scRawPt(singlesData_.at(singlesPos_.first)->scRawPt[singlesPos_.second]),
  chIso(singlesData_.at(singlesPos_.first)->chIso[singlesPos_.second]),
  chWorstIso(singlesData_.at(singlesPos_.first)->chWorstIso[singlesPos_.second]),
  chIsoMax(singlesData_.at(singlesPos_.first)->chIsoMax[singlesPos_.second]),
  nhIso(singlesData_.at(singlesPos_.first)->nhIso[singlesPos_.second]),
  phIso(singlesData_.at(singlesPos_.first)->phIso[singlesPos_.second]),
  nhIsoS16(singlesData_.at(singlesPos_.first)->nhIsoS16[singlesPos_.second]),
  phIsoS16(singlesData_.at(singlesPos_.first)->phIsoS16[singlesPos_.second]),
  ecalIso(singlesData_.at(singlesPos_.first)->ecalIso[singlesPos_.second]),
  hcalIso(singlesData_.at(singlesPos_.first)->hcalIso[singlesPos_.second]),
  sieie(singlesData_.at(singlesPos_.first)->sieie[singlesPos_.second]),
  sipip(singlesData_.at(singlesPos_.first)->sipip[singlesPos_.second]),
  sieip(singlesData_.at(singlesPos_.first)->sieip[singlesPos_.second]),
  hOverE(singlesData_.at(singlesPos_.first)->hOverE[singlesPos_.second]),
  genIso(singlesData_.at(singlesPos_.first)->genIso[singlesPos_.second]),
  mipEnergy(singlesData_.at(singlesPos_.first)->mipEnergy[singlesPos_.second]),
  mipChi2(singlesData_.at(singlesPos_.first)->mipChi2[singlesPos_.second]),
  mipSlope(singlesData_.at(singlesPos_.first)->mipSlope[singlesPos_.second]),
  mipIntercept(singlesData_.at(singlesPos_.first)->mipIntercept[singlesPos_.second]),
  mipNhitCone(singlesData_.at(singlesPos_.first)->mipNhitCone[singlesPos_.second]),
  mipIsHalo(singlesData_.at(singlesPos_.first)->mipIsHalo[singlesPos_.second]),
  scPt(singlesData_.at(singlesPos_.first)->scPt[singlesPos_.second]),
  scEta(singlesData_.at(singlesPos_.first)->scEta[singlesPos_.second]),
  scPhi(singlesData_.at(singlesPos_.first)->scPhi[singlesPos_.second]),
  e13(singlesData_.at(singlesPos_.first)->e13[singlesPos_.second]),
  e31(singlesData_.at(singlesPos_.first)->e31[singlesPos_.second]),
  e15(singlesData_.at(singlesPos_.first)->e15[singlesPos_.second]),
  e22(singlesData_.at(singlesPos_.first)->e22[singlesPos_.second]),
  e25(singlesData_.at(singlesPos_.first)->e25[singlesPos_.second]),
  e33(singlesData_.at(singlesPos_.first)->e33[singlesPos_.second]),
  e44(singlesData_.at(singlesPos_.first)->e44[singlesPos_.second]),
  e55(singlesData_.at(singlesPos_.first)->e55[singlesPos_.second]),
  emax(singlesData_.at(singlesPos_.first)->emax[singlesPos_.second]),
  e2nd(singlesData_.at(singlesPos_.first)->e2nd[singlesPos_.second]),
  e4(singlesData_.at(singlesPos_.first)->e4[singlesPos_.second]),
  r9(singlesData_.at(singlesPos_.first)->r9[singlesPos_.second]),
  etaWidth(singlesData_.at(singlesPos_.first)->etaWidth[singlesPos_.second]),
  phiWidth(singlesData_.at(singlesPos_.first)->phiWidth[singlesPos_.second]),
  time(singlesData_.at(singlesPos_.first)->time[singlesPos_.second]),
  timeSpan(singlesData_.at(singlesPos_.first)->timeSpan[singlesPos_.second]),
  genMatchDR(singlesData_.at(singlesPos_.first)->genMatchDR[singlesPos_.second]),
  isEB(singlesData_.at(singlesPos_.first)->isEB[singlesPos_.second]),
  pixelVeto(singlesData_.at(singlesPos_.first)->pixelVeto[singlesPos_.second]),
  electronVeto(singlesData_.at(singlesPos_.first)->electronVeto[singlesPos_.second]),
  csafeVeto(singlesData_.at(singlesPos_.first)->csafeVeto[singlesPos_.second]),
  highpt(singlesData_.at(singlesPos_.first)->highpt[singlesPos_.second]),
  matchL1(singlesData_.at(singlesPos_.first)->matchL1[singlesPos_.second])
{
  pos_ = singlesPos_;
  usedSinglesPos_.insert(pos_);
}

simpletree::Photon::Photon(array_data& _data, UInt_t _idx) :
  RecoParticle(_data, _idx),
  scRawPt(_data.scRawPt[_idx]),
  chIso(_data.chIso[_idx]),
  chWorstIso(_data.chWorstIso[_idx]),
  chIsoMax(_data.chIsoMax[_idx]),
  nhIso(_data.nhIso[_idx]),
  phIso(_data.phIso[_idx]),
  nhIsoS16(_data.nhIsoS16[_idx]),
  phIsoS16(_data.phIsoS16[_idx]),
  ecalIso(_data.ecalIso[_idx]),
  hcalIso(_data.hcalIso[_idx]),
  sieie(_data.sieie[_idx]),
  sipip(_data.sipip[_idx]),
  sieip(_data.sieip[_idx]),
  hOverE(_data.hOverE[_idx]),
  genIso(_data.genIso[_idx]),
  mipEnergy(_data.mipEnergy[_idx]),
  mipChi2(_data.mipChi2[_idx]),
  mipSlope(_data.mipSlope[_idx]),
  mipIntercept(_data.mipIntercept[_idx]),
  mipNhitCone(_data.mipNhitCone[_idx]),
  mipIsHalo(_data.mipIsHalo[_idx]),
  scPt(_data.scPt[_idx]),
  scEta(_data.scEta[_idx]),
  scPhi(_data.scPhi[_idx]),
  e13(_data.e13[_idx]),
  e31(_data.e31[_idx]),
  e15(_data.e15[_idx]),
  e22(_data.e22[_idx]),
  e25(_data.e25[_idx]),
  e33(_data.e33[_idx]),
  e44(_data.e44[_idx]),
  e55(_data.e55[_idx]),
  emax(_data.emax[_idx]),
  e2nd(_data.e2nd[_idx]),
  e4(_data.e4[_idx]),
  r9(_data.r9[_idx]),
  etaWidth(_data.etaWidth[_idx]),
  phiWidth(_data.phiWidth[_idx]),
  time(_data.time[_idx]),
  timeSpan(_data.timeSpan[_idx]),
  genMatchDR(_data.genMatchDR[_idx]),
  isEB(_data.isEB[_idx]),
  pixelVeto(_data.pixelVeto[_idx]),
  electronVeto(_data.electronVeto[_idx]),
  csafeVeto(_data.csafeVeto[_idx]),
  highpt(_data.highpt[_idx]),
  matchL1(_data.matchL1[_idx])
{
}

simpletree::Photon::Photon(Photon const& _src) :
  RecoParticle(_src),
  scRawPt(_src.scRawPt),
  chIso(_src.chIso),
  chWorstIso(_src.chWorstIso),
  chIsoMax(_src.chIsoMax),
  nhIso(_src.nhIso),
  phIso(_src.phIso),
  nhIsoS16(_src.nhIsoS16),
  phIsoS16(_src.phIsoS16),
  ecalIso(_src.ecalIso),
  hcalIso(_src.hcalIso),
  sieie(_src.sieie),
  sipip(_src.sipip),
  sieip(_src.sieip),
  hOverE(_src.hOverE),
  genIso(_src.genIso),
  mipEnergy(_src.mipEnergy),
  mipChi2(_src.mipChi2),
  mipSlope(_src.mipSlope),
  mipIntercept(_src.mipIntercept),
  mipNhitCone(_src.mipNhitCone),
  mipIsHalo(_src.mipIsHalo),
  scPt(_src.scPt),
  scEta(_src.scEta),
  scPhi(_src.scPhi),
  e13(_src.e13),
  e31(_src.e31),
  e15(_src.e15),
  e22(_src.e22),
  e25(_src.e25),
  e33(_src.e33),
  e44(_src.e44),
  e55(_src.e55),
  emax(_src.emax),
  e2nd(_src.e2nd),
  e4(_src.e4),
  r9(_src.r9),
  etaWidth(_src.etaWidth),
  phiWidth(_src.phiWidth),
  time(_src.time),
  timeSpan(_src.timeSpan),
  genMatchDR(_src.genMatchDR),
  isEB(_src.isEB),
  pixelVeto(_src.pixelVeto),
  electronVeto(_src.electronVeto),
  csafeVeto(_src.csafeVeto),
  highpt(_src.highpt)
{
  std::copy_n(_src.matchL1, nPhotonL1Objects, matchL1);
}

simpletree::Photon::~Photon()
{
  if (pos_.first != unsigned(-1)) {
    usedSinglesPos_.erase(pos_);
    pos_.first = -1;
  }
}

simpletree::Photon&
simpletree::Photon::operator=(Photon const& _rhs)
{
  RecoParticle::operator=(_rhs);

  scRawPt = _rhs.scRawPt;
  chIso = _rhs.chIso;
  chWorstIso = _rhs.chWorstIso;
  chIsoMax = _rhs.chIsoMax;
  nhIso = _rhs.nhIso;
  phIso = _rhs.phIso;
  nhIsoS16 = _rhs.nhIsoS16;
  phIsoS16 = _rhs.phIsoS16;
  ecalIso = _rhs.ecalIso;
  hcalIso = _rhs.hcalIso;
  sieie = _rhs.sieie;
  sipip = _rhs.sipip;
  sieip = _rhs.sieip;
  hOverE = _rhs.hOverE;
  genIso = _rhs.genIso;
  mipEnergy = _rhs.mipEnergy;
  mipChi2 = _rhs.mipChi2;
  mipSlope = _rhs.mipSlope;
  mipIntercept = _rhs.mipIntercept;
  mipNhitCone = _rhs.mipNhitCone;
  mipIsHalo = _rhs.mipIsHalo;
  scPt = _rhs.scPt;
  scEta = _rhs.scEta;
  scPhi = _rhs.scPhi;
  e13 = _rhs.e13;
  e31 = _rhs.e31;
  e15 = _rhs.e15;
  e22 = _rhs.e22;
  e25 = _rhs.e25;
  e33 = _rhs.e33;
  e44 = _rhs.e44;
  e55 = _rhs.e55;
  emax = _rhs.emax;
  e2nd = _rhs.e2nd;
  e4 = _rhs.e4;
  r9 = _rhs.r9;
  etaWidth = _rhs.etaWidth;
  phiWidth = _rhs.phiWidth;
  time = _rhs.time;
  timeSpan = _rhs.timeSpan;
  genMatchDR = _rhs.genMatchDR;
  isEB = _rhs.isEB;
  pixelVeto = _rhs.pixelVeto;
  electronVeto = _rhs.electronVeto;
  csafeVeto = _rhs.csafeVeto;
  highpt = _rhs.highpt;
  std::copy_n(_rhs.matchL1, nPhotonL1Objects, matchL1);
  return *this;
}

void
simpletree::Photon::init()
{
  RecoParticle::init();

  scRawPt = 0.;
  chIso = 0.;
  chWorstIso = 0.;
  chIsoMax = 0.;
  nhIso = 0.;
  phIso = 0.;
  nhIsoS16 = 0.;
  phIsoS16 = 0.;
  ecalIso = 0.;
  hcalIso = 0.;
  sieie = 0.;
  sipip = 0.;
  sieip = 0.;
  hOverE = 0.;
  genIso = 0.;
  mipEnergy = 0.;
  mipChi2 = 0.;
  mipSlope = 0.;
  mipIntercept = 0.;
  mipNhitCone = 0;
  mipIsHalo = false;
  scPt = 0.;
  scEta = 0.;
  scPhi = 0.;
  e13 = 0.;
  e31 = 0.;
  e15 = 0.;
  e22 = 0.;
  e25 = 0.;
  e33 = 0.;
  e44 = 0.;
  e55 = 0.;
  emax = 0.;
  e2nd = 0.;
  e4 = 0.;
  r9 = 0.;
  etaWidth = 0.;
  phiWidth = 0.;
  time = 0.;
  timeSpan = 0.;
  genMatchDR = 0.;
  isEB = false;
  pixelVeto = false;
  electronVeto = false;
  csafeVeto = false;
  highpt = false;
  std::fill(matchL1, matchL1 + nPhotonL1Objects, false);
}

double const simpletree::Photon::chIsoCuts[2][2][4]{{{3.32, 1.37, 0.76, 5.0}, {1.97, 1.10, 0.56, 5.0}},                  {{1.295, 0.441, 0.202, 5.0}, {1.011, 0.442, 0.034, 5.0}}};
double const simpletree::Photon::nhIsoCuts[2][2][4]{{{1.92, 1.06, 0.97, 100000.}, {11.86, 2.69, 2.09, 100000.}},         {{10.910, 2.725, 0.264, 100000.}, {5.931, 1.715, 0.586, 100000.}}};
double const simpletree::Photon::phIsoCuts[2][2][4]{{{0.81, 0.28, 0.08, 2.75}, {0.83, 0.39, 0.16, 2.00}},                {{3.630, 2.571, 2.362, 2.75}, {6.641, 3.863, 2.617, 2.00}}};
double const simpletree::Photon::sieieCuts[2][2][4]{{{0.0102, 0.0102, 0.0100, 0.0105}, {0.0274, 0.0268, 0.0268, 0.028}}, {{0.01031, 0.01022, 0.00994, 0.0105}, {0.03013, 0.03001, 0.03000, 0.028}}};
double const simpletree::Photon::hOverECuts[2][2][4]{{{0.05, 0.05, 0.05, 0.05}, {0.05, 0.05, 0.05, 0.05}},               {{0.0597, 0.0396, 0.0269, 0.05}, {0.0481, 0.0219, 0.0213, 0.05}}};

simpletree::Lepton::array_data::array_data() :
  RecoParticle::array_data()
{
}

void
simpletree::Lepton::array_data::setStatus(TTree& _tree, TString const& _name, Bool_t _status, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  RecoParticle::array_data::setStatus(_tree, _name, _status, _branches, _whitelist);

  flatutils::setStatus(_tree, _name, "positive", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "tauDecay", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "hadDecay", _status, _branches, _whitelist);
}

void
simpletree::Lepton::array_data::setAddress(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  RecoParticle::array_data::setAddress(_tree, _name, _branches, _whitelist);

  flatutils::setStatusAndAddress(_tree, _name, "positive", positive, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "tauDecay", tauDecay, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "hadDecay", hadDecay, _branches, _whitelist);
}

void
simpletree::Lepton::array_data::book(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  RecoParticle::array_data::book(_tree, _name, _branches, _whitelist);

  flatutils::book(_tree, _name, "positive", "[" + _name + ".size]", 'O', positive, _branches, _whitelist);
  flatutils::book(_tree, _name, "tauDecay", "[" + _name + ".size]", 'O', tauDecay, _branches, _whitelist);
  flatutils::book(_tree, _name, "hadDecay", "[" + _name + ".size]", 'O', hadDecay, _branches, _whitelist);
}

void
simpletree::Lepton::setStatus(TTree& _tree, TString const& _name, Bool_t _status, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  RecoParticle::setStatus(_tree, _name, _status, _branches, _whitelist);

  flatutils::setStatus(_tree, _name, "positive", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "tauDecay", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "hadDecay", _status, _branches, _whitelist);
}

void
simpletree::Lepton::setAddress(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  RecoParticle::setAddress(_tree, _name, _branches, _whitelist);

  flatutils::setStatusAndAddress(_tree, _name, "positive", &positive, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "tauDecay", &tauDecay, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "hadDecay", &hadDecay, _branches, _whitelist);
}

void
simpletree::Lepton::book(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist)
{
  RecoParticle::book(_tree, _name, _branches, _whitelist);

  flatutils::book(_tree, _name, "positive", "", 'O', &positive, _branches, _whitelist);
  flatutils::book(_tree, _name, "tauDecay", "", 'O', &tauDecay, _branches, _whitelist);
  flatutils::book(_tree, _name, "hadDecay", "", 'O', &hadDecay, _branches, _whitelist);
}

/*static*/
std::vector<std::auto_ptr<simpletree::Lepton::array_data>> simpletree::Lepton::singlesData_{};
/*static*/
simpletree::SinglesPos simpletree::Lepton::singlesPos_(-1, simpletree::Lepton::array_data::NMAX - 1);
/*static*/
std::set<simpletree::SinglesPos> simpletree::Lepton::usedSinglesPos_{};

/*static*/
simpletree::SinglesPos const&
simpletree::Lepton::nextSinglesPos_()
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

simpletree::Lepton::Lepton() :
  RecoParticle(*singlesData_.at(nextSinglesPos_().first), singlesPos_.second),
  positive(singlesData_.at(singlesPos_.first)->positive[singlesPos_.second]),
  tauDecay(singlesData_.at(singlesPos_.first)->tauDecay[singlesPos_.second]),
  hadDecay(singlesData_.at(singlesPos_.first)->hadDecay[singlesPos_.second])
{
  pos_ = singlesPos_;
  usedSinglesPos_.insert(pos_);
}

simpletree::Lepton::Lepton(array_data& _data, UInt_t _idx) :
  RecoParticle(_data, _idx),
  positive(_data.positive[_idx]),
  tauDecay(_data.tauDecay[_idx]),
  hadDecay(_data.hadDecay[_idx])
{
}

simpletree::Lepton::Lepton(Lepton const& _src) :
  RecoParticle(_src),
  positive(_src.positive),
  tauDecay(_src.tauDecay),
  hadDecay(_src.hadDecay)
{
}

simpletree::Lepton::~Lepton()
{
  if (pos_.first != unsigned(-1)) {
    usedSinglesPos_.erase(pos_);
    pos_.first = -1;
  }
}

simpletree::Lepton&
simpletree::Lepton::operator=(Lepton const& _rhs)
{
  RecoParticle::operator=(_rhs);

  positive = _rhs.positive;
  tauDecay = _rhs.tauDecay;
  hadDecay = _rhs.hadDecay;
  return *this;
}

void
simpletree::Lepton::init()
{
  RecoParticle::init();

  positive = false;
  tauDecay = false;
  hadDecay = false;
}

simpletree::Electron::array_data::array_data() :
  Lepton::array_data()
{
}

void
simpletree::Electron::array_data::setStatus(TTree& _tree, TString const& _name, Bool_t _status, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  Lepton::array_data::setStatus(_tree, _name, _status, _branches, _whitelist);

  flatutils::setStatus(_tree, _name, "chIsoPh", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "nhIsoPh", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "phIsoPh", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "combRelIso", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "ecalIso", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "hcalIso", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "sieie", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "sipip", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "sieip", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "hOverE", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "isEB", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "veto", _status, _branches, _whitelist);
}

void
simpletree::Electron::array_data::setAddress(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  Lepton::array_data::setAddress(_tree, _name, _branches, _whitelist);

  flatutils::setStatusAndAddress(_tree, _name, "chIsoPh", chIsoPh, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "nhIsoPh", nhIsoPh, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "phIsoPh", phIsoPh, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "combRelIso", combRelIso, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "ecalIso", ecalIso, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "hcalIso", hcalIso, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "sieie", sieie, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "sipip", sipip, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "sieip", sieip, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "hOverE", hOverE, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "isEB", isEB, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "veto", veto, _branches, _whitelist);
}

void
simpletree::Electron::array_data::book(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  Lepton::array_data::book(_tree, _name, _branches, _whitelist);

  flatutils::book(_tree, _name, "chIsoPh", "[" + _name + ".size]", 'F', chIsoPh, _branches, _whitelist);
  flatutils::book(_tree, _name, "nhIsoPh", "[" + _name + ".size]", 'F', nhIsoPh, _branches, _whitelist);
  flatutils::book(_tree, _name, "phIsoPh", "[" + _name + ".size]", 'F', phIsoPh, _branches, _whitelist);
  flatutils::book(_tree, _name, "combRelIso", "[" + _name + ".size]", 'F', combRelIso, _branches, _whitelist);
  flatutils::book(_tree, _name, "ecalIso", "[" + _name + ".size]", 'F', ecalIso, _branches, _whitelist);
  flatutils::book(_tree, _name, "hcalIso", "[" + _name + ".size]", 'F', hcalIso, _branches, _whitelist);
  flatutils::book(_tree, _name, "sieie", "[" + _name + ".size]", 'F', sieie, _branches, _whitelist);
  flatutils::book(_tree, _name, "sipip", "[" + _name + ".size]", 'F', sipip, _branches, _whitelist);
  flatutils::book(_tree, _name, "sieip", "[" + _name + ".size]", 'F', sieip, _branches, _whitelist);
  flatutils::book(_tree, _name, "hOverE", "[" + _name + ".size]", 'F', hOverE, _branches, _whitelist);
  flatutils::book(_tree, _name, "isEB", "[" + _name + ".size]", 'O', isEB, _branches, _whitelist);
  flatutils::book(_tree, _name, "veto", "[" + _name + ".size]", 'O', veto, _branches, _whitelist);
}

void
simpletree::Electron::setStatus(TTree& _tree, TString const& _name, Bool_t _status, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  Lepton::setStatus(_tree, _name, _status, _branches, _whitelist);

  flatutils::setStatus(_tree, _name, "chIsoPh", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "nhIsoPh", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "phIsoPh", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "combRelIso", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "ecalIso", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "hcalIso", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "sieie", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "sipip", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "sieip", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "hOverE", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "isEB", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "veto", _status, _branches, _whitelist);
}

void
simpletree::Electron::setAddress(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  Lepton::setAddress(_tree, _name, _branches, _whitelist);

  flatutils::setStatusAndAddress(_tree, _name, "chIsoPh", &chIsoPh, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "nhIsoPh", &nhIsoPh, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "phIsoPh", &phIsoPh, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "combRelIso", &combRelIso, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "ecalIso", &ecalIso, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "hcalIso", &hcalIso, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "sieie", &sieie, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "sipip", &sipip, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "sieip", &sieip, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "hOverE", &hOverE, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "isEB", &isEB, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "veto", &veto, _branches, _whitelist);
}

void
simpletree::Electron::book(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist)
{
  Lepton::book(_tree, _name, _branches, _whitelist);

  flatutils::book(_tree, _name, "chIsoPh", "", 'F', &chIsoPh, _branches, _whitelist);
  flatutils::book(_tree, _name, "nhIsoPh", "", 'F', &nhIsoPh, _branches, _whitelist);
  flatutils::book(_tree, _name, "phIsoPh", "", 'F', &phIsoPh, _branches, _whitelist);
  flatutils::book(_tree, _name, "combRelIso", "", 'F', &combRelIso, _branches, _whitelist);
  flatutils::book(_tree, _name, "ecalIso", "", 'F', &ecalIso, _branches, _whitelist);
  flatutils::book(_tree, _name, "hcalIso", "", 'F', &hcalIso, _branches, _whitelist);
  flatutils::book(_tree, _name, "sieie", "", 'F', &sieie, _branches, _whitelist);
  flatutils::book(_tree, _name, "sipip", "", 'F', &sipip, _branches, _whitelist);
  flatutils::book(_tree, _name, "sieip", "", 'F', &sieip, _branches, _whitelist);
  flatutils::book(_tree, _name, "hOverE", "", 'F', &hOverE, _branches, _whitelist);
  flatutils::book(_tree, _name, "isEB", "", 'O', &isEB, _branches, _whitelist);
  flatutils::book(_tree, _name, "veto", "", 'O', &veto, _branches, _whitelist);
}

/*static*/
std::vector<std::auto_ptr<simpletree::Electron::array_data>> simpletree::Electron::singlesData_{};
/*static*/
simpletree::SinglesPos simpletree::Electron::singlesPos_(-1, simpletree::Electron::array_data::NMAX - 1);
/*static*/
std::set<simpletree::SinglesPos> simpletree::Electron::usedSinglesPos_{};

/*static*/
simpletree::SinglesPos const&
simpletree::Electron::nextSinglesPos_()
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

simpletree::Electron::Electron() :
  Lepton(*singlesData_.at(nextSinglesPos_().first), singlesPos_.second),
  chIsoPh(singlesData_.at(singlesPos_.first)->chIsoPh[singlesPos_.second]),
  nhIsoPh(singlesData_.at(singlesPos_.first)->nhIsoPh[singlesPos_.second]),
  phIsoPh(singlesData_.at(singlesPos_.first)->phIsoPh[singlesPos_.second]),
  combRelIso(singlesData_.at(singlesPos_.first)->combRelIso[singlesPos_.second]),
  ecalIso(singlesData_.at(singlesPos_.first)->ecalIso[singlesPos_.second]),
  hcalIso(singlesData_.at(singlesPos_.first)->hcalIso[singlesPos_.second]),
  sieie(singlesData_.at(singlesPos_.first)->sieie[singlesPos_.second]),
  sipip(singlesData_.at(singlesPos_.first)->sipip[singlesPos_.second]),
  sieip(singlesData_.at(singlesPos_.first)->sieip[singlesPos_.second]),
  hOverE(singlesData_.at(singlesPos_.first)->hOverE[singlesPos_.second]),
  isEB(singlesData_.at(singlesPos_.first)->isEB[singlesPos_.second]),
  veto(singlesData_.at(singlesPos_.first)->veto[singlesPos_.second])
{
  pos_ = singlesPos_;
  usedSinglesPos_.insert(pos_);
}

simpletree::Electron::Electron(array_data& _data, UInt_t _idx) :
  Lepton(_data, _idx),
  chIsoPh(_data.chIsoPh[_idx]),
  nhIsoPh(_data.nhIsoPh[_idx]),
  phIsoPh(_data.phIsoPh[_idx]),
  combRelIso(_data.combRelIso[_idx]),
  ecalIso(_data.ecalIso[_idx]),
  hcalIso(_data.hcalIso[_idx]),
  sieie(_data.sieie[_idx]),
  sipip(_data.sipip[_idx]),
  sieip(_data.sieip[_idx]),
  hOverE(_data.hOverE[_idx]),
  isEB(_data.isEB[_idx]),
  veto(_data.veto[_idx])
{
}

simpletree::Electron::Electron(Electron const& _src) :
  Lepton(_src),
  chIsoPh(_src.chIsoPh),
  nhIsoPh(_src.nhIsoPh),
  phIsoPh(_src.phIsoPh),
  combRelIso(_src.combRelIso),
  ecalIso(_src.ecalIso),
  hcalIso(_src.hcalIso),
  sieie(_src.sieie),
  sipip(_src.sipip),
  sieip(_src.sieip),
  hOverE(_src.hOverE),
  isEB(_src.isEB),
  veto(_src.veto)
{
}

simpletree::Electron::~Electron()
{
  if (pos_.first != unsigned(-1)) {
    usedSinglesPos_.erase(pos_);
    pos_.first = -1;
  }
}

simpletree::Electron&
simpletree::Electron::operator=(Electron const& _rhs)
{
  Lepton::operator=(_rhs);

  chIsoPh = _rhs.chIsoPh;
  nhIsoPh = _rhs.nhIsoPh;
  phIsoPh = _rhs.phIsoPh;
  combRelIso = _rhs.combRelIso;
  ecalIso = _rhs.ecalIso;
  hcalIso = _rhs.hcalIso;
  sieie = _rhs.sieie;
  sipip = _rhs.sipip;
  sieip = _rhs.sieip;
  hOverE = _rhs.hOverE;
  isEB = _rhs.isEB;
  veto = _rhs.veto;
  return *this;
}

void
simpletree::Electron::init()
{
  Lepton::init();

  chIsoPh = 0.;
  nhIsoPh = 0.;
  phIsoPh = 0.;
  combRelIso = 0.;
  ecalIso = 0.;
  hcalIso = 0.;
  sieie = 0.;
  sipip = 0.;
  sieip = 0.;
  hOverE = 0.;
  isEB = false;
  veto = false;
}

simpletree::Muon::array_data::array_data() :
  Lepton::array_data()
{
}

void
simpletree::Muon::array_data::setStatus(TTree& _tree, TString const& _name, Bool_t _status, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  Lepton::array_data::setStatus(_tree, _name, _status, _branches, _whitelist);

  flatutils::setStatus(_tree, _name, "combRelIso", _status, _branches, _whitelist);
}

void
simpletree::Muon::array_data::setAddress(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  Lepton::array_data::setAddress(_tree, _name, _branches, _whitelist);

  flatutils::setStatusAndAddress(_tree, _name, "combRelIso", combRelIso, _branches, _whitelist);
}

void
simpletree::Muon::array_data::book(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  Lepton::array_data::book(_tree, _name, _branches, _whitelist);

  flatutils::book(_tree, _name, "combRelIso", "[" + _name + ".size]", 'F', combRelIso, _branches, _whitelist);
}

void
simpletree::Muon::setStatus(TTree& _tree, TString const& _name, Bool_t _status, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  Lepton::setStatus(_tree, _name, _status, _branches, _whitelist);

  flatutils::setStatus(_tree, _name, "combRelIso", _status, _branches, _whitelist);
}

void
simpletree::Muon::setAddress(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  Lepton::setAddress(_tree, _name, _branches, _whitelist);

  flatutils::setStatusAndAddress(_tree, _name, "combRelIso", &combRelIso, _branches, _whitelist);
}

void
simpletree::Muon::book(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist)
{
  Lepton::book(_tree, _name, _branches, _whitelist);

  flatutils::book(_tree, _name, "combRelIso", "", 'F', &combRelIso, _branches, _whitelist);
}

/*static*/
std::vector<std::auto_ptr<simpletree::Muon::array_data>> simpletree::Muon::singlesData_{};
/*static*/
simpletree::SinglesPos simpletree::Muon::singlesPos_(-1, simpletree::Muon::array_data::NMAX - 1);
/*static*/
std::set<simpletree::SinglesPos> simpletree::Muon::usedSinglesPos_{};

/*static*/
simpletree::SinglesPos const&
simpletree::Muon::nextSinglesPos_()
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

simpletree::Muon::Muon() :
  Lepton(*singlesData_.at(nextSinglesPos_().first), singlesPos_.second),
  combRelIso(singlesData_.at(singlesPos_.first)->combRelIso[singlesPos_.second])
{
  pos_ = singlesPos_;
  usedSinglesPos_.insert(pos_);
}

simpletree::Muon::Muon(array_data& _data, UInt_t _idx) :
  Lepton(_data, _idx),
  combRelIso(_data.combRelIso[_idx])
{
}

simpletree::Muon::Muon(Muon const& _src) :
  Lepton(_src),
  combRelIso(_src.combRelIso)
{
}

simpletree::Muon::~Muon()
{
  if (pos_.first != unsigned(-1)) {
    usedSinglesPos_.erase(pos_);
    pos_.first = -1;
  }
}

simpletree::Muon&
simpletree::Muon::operator=(Muon const& _rhs)
{
  Lepton::operator=(_rhs);

  combRelIso = _rhs.combRelIso;
  return *this;
}

void
simpletree::Muon::init()
{
  Lepton::init();

  combRelIso = 0.;
}

simpletree::Tau::array_data::array_data() :
  RecoParticleM::array_data()
{
}

void
simpletree::Tau::array_data::setStatus(TTree& _tree, TString const& _name, Bool_t _status, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  RecoParticleM::array_data::setStatus(_tree, _name, _status, _branches, _whitelist);

  flatutils::setStatus(_tree, _name, "decayMode", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "combIso", _status, _branches, _whitelist);
}

void
simpletree::Tau::array_data::setAddress(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  RecoParticleM::array_data::setAddress(_tree, _name, _branches, _whitelist);

  flatutils::setStatusAndAddress(_tree, _name, "decayMode", decayMode, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "combIso", combIso, _branches, _whitelist);
}

void
simpletree::Tau::array_data::book(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  RecoParticleM::array_data::book(_tree, _name, _branches, _whitelist);

  flatutils::book(_tree, _name, "decayMode", "[" + _name + ".size]", 'O', decayMode, _branches, _whitelist);
  flatutils::book(_tree, _name, "combIso", "[" + _name + ".size]", 'F', combIso, _branches, _whitelist);
}

void
simpletree::Tau::setStatus(TTree& _tree, TString const& _name, Bool_t _status, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  RecoParticleM::setStatus(_tree, _name, _status, _branches, _whitelist);

  flatutils::setStatus(_tree, _name, "decayMode", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "combIso", _status, _branches, _whitelist);
}

void
simpletree::Tau::setAddress(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  RecoParticleM::setAddress(_tree, _name, _branches, _whitelist);

  flatutils::setStatusAndAddress(_tree, _name, "decayMode", &decayMode, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "combIso", &combIso, _branches, _whitelist);
}

void
simpletree::Tau::book(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist)
{
  RecoParticleM::book(_tree, _name, _branches, _whitelist);

  flatutils::book(_tree, _name, "decayMode", "", 'O', &decayMode, _branches, _whitelist);
  flatutils::book(_tree, _name, "combIso", "", 'F', &combIso, _branches, _whitelist);
}

/*static*/
std::vector<std::auto_ptr<simpletree::Tau::array_data>> simpletree::Tau::singlesData_{};
/*static*/
simpletree::SinglesPos simpletree::Tau::singlesPos_(-1, simpletree::Tau::array_data::NMAX - 1);
/*static*/
std::set<simpletree::SinglesPos> simpletree::Tau::usedSinglesPos_{};

/*static*/
simpletree::SinglesPos const&
simpletree::Tau::nextSinglesPos_()
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

simpletree::Tau::Tau() :
  RecoParticleM(*singlesData_.at(nextSinglesPos_().first), singlesPos_.second),
  decayMode(singlesData_.at(singlesPos_.first)->decayMode[singlesPos_.second]),
  combIso(singlesData_.at(singlesPos_.first)->combIso[singlesPos_.second])
{
  pos_ = singlesPos_;
  usedSinglesPos_.insert(pos_);
}

simpletree::Tau::Tau(array_data& _data, UInt_t _idx) :
  RecoParticleM(_data, _idx),
  decayMode(_data.decayMode[_idx]),
  combIso(_data.combIso[_idx])
{
}

simpletree::Tau::Tau(Tau const& _src) :
  RecoParticleM(_src),
  decayMode(_src.decayMode),
  combIso(_src.combIso)
{
}

simpletree::Tau::~Tau()
{
  if (pos_.first != unsigned(-1)) {
    usedSinglesPos_.erase(pos_);
    pos_.first = -1;
  }
}

simpletree::Tau&
simpletree::Tau::operator=(Tau const& _rhs)
{
  RecoParticleM::operator=(_rhs);

  decayMode = _rhs.decayMode;
  combIso = _rhs.combIso;
  return *this;
}

void
simpletree::Tau::init()
{
  RecoParticleM::init();

  decayMode = false;
  combIso = 0.;
}

simpletree::Jet::array_data::array_data() :
  RecoParticleM::array_data()
{
}

void
simpletree::Jet::array_data::setStatus(TTree& _tree, TString const& _name, Bool_t _status, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  RecoParticleM::array_data::setStatus(_tree, _name, _status, _branches, _whitelist);

  flatutils::setStatus(_tree, _name, "ptRaw", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "ptCorrUp", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "ptCorrDown", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "ptResCorr", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "phiResCorr", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "cisv", _status, _branches, _whitelist);
}

void
simpletree::Jet::array_data::setAddress(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  RecoParticleM::array_data::setAddress(_tree, _name, _branches, _whitelist);

  flatutils::setStatusAndAddress(_tree, _name, "ptRaw", ptRaw, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "ptCorrUp", ptCorrUp, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "ptCorrDown", ptCorrDown, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "ptResCorr", ptResCorr, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "phiResCorr", phiResCorr, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "cisv", cisv, _branches, _whitelist);
}

void
simpletree::Jet::array_data::book(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  RecoParticleM::array_data::book(_tree, _name, _branches, _whitelist);

  flatutils::book(_tree, _name, "ptRaw", "[" + _name + ".size]", 'F', ptRaw, _branches, _whitelist);
  flatutils::book(_tree, _name, "ptCorrUp", "[" + _name + ".size]", 'F', ptCorrUp, _branches, _whitelist);
  flatutils::book(_tree, _name, "ptCorrDown", "[" + _name + ".size]", 'F', ptCorrDown, _branches, _whitelist);
  flatutils::book(_tree, _name, "ptResCorr", "[" + _name + ".size]", 'F', ptResCorr, _branches, _whitelist);
  flatutils::book(_tree, _name, "phiResCorr", "[" + _name + ".size]", 'F', phiResCorr, _branches, _whitelist);
  flatutils::book(_tree, _name, "cisv", "[" + _name + ".size]", 'F', cisv, _branches, _whitelist);
}

void
simpletree::Jet::setStatus(TTree& _tree, TString const& _name, Bool_t _status, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  RecoParticleM::setStatus(_tree, _name, _status, _branches, _whitelist);

  flatutils::setStatus(_tree, _name, "ptRaw", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "ptCorrUp", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "ptCorrDown", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "ptResCorr", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "phiResCorr", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "cisv", _status, _branches, _whitelist);
}

void
simpletree::Jet::setAddress(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  RecoParticleM::setAddress(_tree, _name, _branches, _whitelist);

  flatutils::setStatusAndAddress(_tree, _name, "ptRaw", &ptRaw, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "ptCorrUp", &ptCorrUp, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "ptCorrDown", &ptCorrDown, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "ptResCorr", &ptResCorr, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "phiResCorr", &phiResCorr, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "cisv", &cisv, _branches, _whitelist);
}

void
simpletree::Jet::book(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist)
{
  RecoParticleM::book(_tree, _name, _branches, _whitelist);

  flatutils::book(_tree, _name, "ptRaw", "", 'F', &ptRaw, _branches, _whitelist);
  flatutils::book(_tree, _name, "ptCorrUp", "", 'F', &ptCorrUp, _branches, _whitelist);
  flatutils::book(_tree, _name, "ptCorrDown", "", 'F', &ptCorrDown, _branches, _whitelist);
  flatutils::book(_tree, _name, "ptResCorr", "", 'F', &ptResCorr, _branches, _whitelist);
  flatutils::book(_tree, _name, "phiResCorr", "", 'F', &phiResCorr, _branches, _whitelist);
  flatutils::book(_tree, _name, "cisv", "", 'F', &cisv, _branches, _whitelist);
}

/*static*/
std::vector<std::auto_ptr<simpletree::Jet::array_data>> simpletree::Jet::singlesData_{};
/*static*/
simpletree::SinglesPos simpletree::Jet::singlesPos_(-1, simpletree::Jet::array_data::NMAX - 1);
/*static*/
std::set<simpletree::SinglesPos> simpletree::Jet::usedSinglesPos_{};

/*static*/
simpletree::SinglesPos const&
simpletree::Jet::nextSinglesPos_()
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

simpletree::Jet::Jet() :
  RecoParticleM(*singlesData_.at(nextSinglesPos_().first), singlesPos_.second),
  ptRaw(singlesData_.at(singlesPos_.first)->ptRaw[singlesPos_.second]),
  ptCorrUp(singlesData_.at(singlesPos_.first)->ptCorrUp[singlesPos_.second]),
  ptCorrDown(singlesData_.at(singlesPos_.first)->ptCorrDown[singlesPos_.second]),
  ptResCorr(singlesData_.at(singlesPos_.first)->ptResCorr[singlesPos_.second]),
  phiResCorr(singlesData_.at(singlesPos_.first)->phiResCorr[singlesPos_.second]),
  cisv(singlesData_.at(singlesPos_.first)->cisv[singlesPos_.second])
{
  pos_ = singlesPos_;
  usedSinglesPos_.insert(pos_);
}

simpletree::Jet::Jet(array_data& _data, UInt_t _idx) :
  RecoParticleM(_data, _idx),
  ptRaw(_data.ptRaw[_idx]),
  ptCorrUp(_data.ptCorrUp[_idx]),
  ptCorrDown(_data.ptCorrDown[_idx]),
  ptResCorr(_data.ptResCorr[_idx]),
  phiResCorr(_data.phiResCorr[_idx]),
  cisv(_data.cisv[_idx])
{
}

simpletree::Jet::Jet(Jet const& _src) :
  RecoParticleM(_src),
  ptRaw(_src.ptRaw),
  ptCorrUp(_src.ptCorrUp),
  ptCorrDown(_src.ptCorrDown),
  ptResCorr(_src.ptResCorr),
  phiResCorr(_src.phiResCorr),
  cisv(_src.cisv)
{
}

simpletree::Jet::~Jet()
{
  if (pos_.first != unsigned(-1)) {
    usedSinglesPos_.erase(pos_);
    pos_.first = -1;
  }
}

simpletree::Jet&
simpletree::Jet::operator=(Jet const& _rhs)
{
  RecoParticleM::operator=(_rhs);

  ptRaw = _rhs.ptRaw;
  ptCorrUp = _rhs.ptCorrUp;
  ptCorrDown = _rhs.ptCorrDown;
  ptResCorr = _rhs.ptResCorr;
  phiResCorr = _rhs.phiResCorr;
  cisv = _rhs.cisv;
  return *this;
}

void
simpletree::Jet::init()
{
  RecoParticleM::init();

  ptRaw = 0.;
  ptCorrUp = 0.;
  ptCorrDown = 0.;
  ptResCorr = 0.;
  phiResCorr = 0.;
  cisv = 0.;
}

simpletree::SuperCluster::array_data::array_data()
{
}

void
simpletree::SuperCluster::array_data::setStatus(TTree& _tree, TString const& _name, Bool_t _status, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  flatutils::setStatus(_tree, _name, "rawPt", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "eta", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "phi", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "isEB", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "time", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "sieie", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "sipip", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "e2e9", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "emax", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "e2nd", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "e4", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "timeSpan", _status, _branches, _whitelist);
}

void
simpletree::SuperCluster::array_data::setAddress(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  flatutils::setStatusAndAddress(_tree, _name, "rawPt", rawPt, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "eta", eta, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "phi", phi, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "isEB", isEB, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "time", time, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "sieie", sieie, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "sipip", sipip, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "e2e9", e2e9, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "emax", emax, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "e2nd", e2nd, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "e4", e4, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "timeSpan", timeSpan, _branches, _whitelist);
}

void
simpletree::SuperCluster::array_data::book(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  flatutils::book(_tree, _name, "rawPt", "[" + _name + ".size]", 'F', rawPt, _branches, _whitelist);
  flatutils::book(_tree, _name, "eta", "[" + _name + ".size]", 'F', eta, _branches, _whitelist);
  flatutils::book(_tree, _name, "phi", "[" + _name + ".size]", 'F', phi, _branches, _whitelist);
  flatutils::book(_tree, _name, "isEB", "[" + _name + ".size]", 'O', isEB, _branches, _whitelist);
  flatutils::book(_tree, _name, "time", "[" + _name + ".size]", 'F', time, _branches, _whitelist);
  flatutils::book(_tree, _name, "sieie", "[" + _name + ".size]", 'F', sieie, _branches, _whitelist);
  flatutils::book(_tree, _name, "sipip", "[" + _name + ".size]", 'F', sipip, _branches, _whitelist);
  flatutils::book(_tree, _name, "e2e9", "[" + _name + ".size]", 'F', e2e9, _branches, _whitelist);
  flatutils::book(_tree, _name, "emax", "[" + _name + ".size]", 'F', emax, _branches, _whitelist);
  flatutils::book(_tree, _name, "e2nd", "[" + _name + ".size]", 'F', e2nd, _branches, _whitelist);
  flatutils::book(_tree, _name, "e4", "[" + _name + ".size]", 'F', e4, _branches, _whitelist);
  flatutils::book(_tree, _name, "timeSpan", "[" + _name + ".size]", 'F', timeSpan, _branches, _whitelist);
}

void
simpletree::SuperCluster::setStatus(TTree& _tree, TString const& _name, Bool_t _status, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  flatutils::setStatus(_tree, _name, "rawPt", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "eta", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "phi", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "isEB", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "time", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "sieie", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "sipip", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "e2e9", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "emax", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "e2nd", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "e4", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "timeSpan", _status, _branches, _whitelist);
}

void
simpletree::SuperCluster::setAddress(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  flatutils::setStatusAndAddress(_tree, _name, "rawPt", &rawPt, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "eta", &eta, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "phi", &phi, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "isEB", &isEB, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "time", &time, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "sieie", &sieie, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "sipip", &sipip, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "e2e9", &e2e9, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "emax", &emax, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "e2nd", &e2nd, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "e4", &e4, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "timeSpan", &timeSpan, _branches, _whitelist);
}

void
simpletree::SuperCluster::book(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist)
{
  flatutils::book(_tree, _name, "rawPt", "", 'F', &rawPt, _branches, _whitelist);
  flatutils::book(_tree, _name, "eta", "", 'F', &eta, _branches, _whitelist);
  flatutils::book(_tree, _name, "phi", "", 'F', &phi, _branches, _whitelist);
  flatutils::book(_tree, _name, "isEB", "", 'O', &isEB, _branches, _whitelist);
  flatutils::book(_tree, _name, "time", "", 'F', &time, _branches, _whitelist);
  flatutils::book(_tree, _name, "sieie", "", 'F', &sieie, _branches, _whitelist);
  flatutils::book(_tree, _name, "sipip", "", 'F', &sipip, _branches, _whitelist);
  flatutils::book(_tree, _name, "e2e9", "", 'F', &e2e9, _branches, _whitelist);
  flatutils::book(_tree, _name, "emax", "", 'F', &emax, _branches, _whitelist);
  flatutils::book(_tree, _name, "e2nd", "", 'F', &e2nd, _branches, _whitelist);
  flatutils::book(_tree, _name, "e4", "", 'F', &e4, _branches, _whitelist);
  flatutils::book(_tree, _name, "timeSpan", "", 'F', &timeSpan, _branches, _whitelist);
}

/*static*/
std::vector<std::auto_ptr<simpletree::SuperCluster::array_data>> simpletree::SuperCluster::singlesData_{};
/*static*/
simpletree::SinglesPos simpletree::SuperCluster::singlesPos_(-1, simpletree::SuperCluster::array_data::NMAX - 1);
/*static*/
std::set<simpletree::SinglesPos> simpletree::SuperCluster::usedSinglesPos_{};

/*static*/
simpletree::SinglesPos const&
simpletree::SuperCluster::nextSinglesPos_()
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

simpletree::SuperCluster::SuperCluster() :
  pos_(nextSinglesPos_()),
  rawPt(singlesData_.at(singlesPos_.first)->rawPt[singlesPos_.second]),
  eta(singlesData_.at(singlesPos_.first)->eta[singlesPos_.second]),
  phi(singlesData_.at(singlesPos_.first)->phi[singlesPos_.second]),
  isEB(singlesData_.at(singlesPos_.first)->isEB[singlesPos_.second]),
  time(singlesData_.at(singlesPos_.first)->time[singlesPos_.second]),
  sieie(singlesData_.at(singlesPos_.first)->sieie[singlesPos_.second]),
  sipip(singlesData_.at(singlesPos_.first)->sipip[singlesPos_.second]),
  e2e9(singlesData_.at(singlesPos_.first)->e2e9[singlesPos_.second]),
  emax(singlesData_.at(singlesPos_.first)->emax[singlesPos_.second]),
  e2nd(singlesData_.at(singlesPos_.first)->e2nd[singlesPos_.second]),
  e4(singlesData_.at(singlesPos_.first)->e4[singlesPos_.second]),
  timeSpan(singlesData_.at(singlesPos_.first)->timeSpan[singlesPos_.second])
{
  usedSinglesPos_.insert(pos_);
}

simpletree::SuperCluster::SuperCluster(array_data& _data, UInt_t _idx) :
  rawPt(_data.rawPt[_idx]),
  eta(_data.eta[_idx]),
  phi(_data.phi[_idx]),
  isEB(_data.isEB[_idx]),
  time(_data.time[_idx]),
  sieie(_data.sieie[_idx]),
  sipip(_data.sipip[_idx]),
  e2e9(_data.e2e9[_idx]),
  emax(_data.emax[_idx]),
  e2nd(_data.e2nd[_idx]),
  e4(_data.e4[_idx]),
  timeSpan(_data.timeSpan[_idx])
{
}

simpletree::SuperCluster::SuperCluster(SuperCluster const& _src) :
  rawPt(_src.rawPt),
  eta(_src.eta),
  phi(_src.phi),
  isEB(_src.isEB),
  time(_src.time),
  sieie(_src.sieie),
  sipip(_src.sipip),
  e2e9(_src.e2e9),
  emax(_src.emax),
  e2nd(_src.e2nd),
  e4(_src.e4),
  timeSpan(_src.timeSpan)
{
}

simpletree::SuperCluster::~SuperCluster()
{
  if (pos_.first != unsigned(-1)) {
    usedSinglesPos_.erase(pos_);
    pos_.first = -1;
  }
}

simpletree::SuperCluster&
simpletree::SuperCluster::operator=(SuperCluster const& _rhs)
{
  rawPt = _rhs.rawPt;
  eta = _rhs.eta;
  phi = _rhs.phi;
  isEB = _rhs.isEB;
  time = _rhs.time;
  sieie = _rhs.sieie;
  sipip = _rhs.sipip;
  e2e9 = _rhs.e2e9;
  emax = _rhs.emax;
  e2nd = _rhs.e2nd;
  e4 = _rhs.e4;
  timeSpan = _rhs.timeSpan;
  return *this;
}

void
simpletree::SuperCluster::init()
{
  rawPt = 0.;
  eta = 0.;
  phi = 0.;
  isEB = false;
  time = 0.;
  sieie = 0.;
  sipip = 0.;
  e2e9 = 0.;
  emax = 0.;
  e2nd = 0.;
  e4 = 0.;
  timeSpan = 0.;
}

simpletree::Met::Met(TString const& _name) :
  name_(_name)
{
}

simpletree::Met::Met(Met const& _src) :
  name_(_src.name_),
  met(_src.met),
  phi(_src.phi),
  sumEt(_src.sumEt)
{
}

simpletree::Met::~Met()
{
}

void
simpletree::Met::setStatus(TTree& _tree, Bool_t _status, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  flatutils::setStatus(_tree, name_, "met", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, name_, "phi", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, name_, "sumEt", _status, _branches, _whitelist);
}

void
simpletree::Met::setAddress(TTree& _tree, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  flatutils::setStatusAndAddress(_tree, name_, "met", &met, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, name_, "phi", &phi, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, name_, "sumEt", &sumEt, _branches, _whitelist);
}

void
simpletree::Met::book(TTree& _tree, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist)
{
  flatutils::book(_tree, name_, "met", "", 'F', &met, _branches, _whitelist);
  flatutils::book(_tree, name_, "phi", "", 'F', &phi, _branches, _whitelist);
  flatutils::book(_tree, name_, "sumEt", "", 'F', &sumEt, _branches, _whitelist);
}

void
simpletree::Met::setStatus(TTree& _tree, TString const& _name, Bool_t _status, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  flatutils::setStatus(_tree, _name, "met", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "phi", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "sumEt", _status, _branches, _whitelist);
}

void
simpletree::Met::setAddress(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  flatutils::setStatusAndAddress(_tree, _name, "met", &met, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "phi", &phi, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "sumEt", &sumEt, _branches, _whitelist);
}

void
simpletree::Met::book(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist)
{
  flatutils::book(_tree, _name, "met", "", 'F', &met, _branches, _whitelist);
  flatutils::book(_tree, _name, "phi", "", 'F', &phi, _branches, _whitelist);
  flatutils::book(_tree, _name, "sumEt", "", 'F', &sumEt, _branches, _whitelist);
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
simpletree::Met::init()
{
  met = 0.;
  phi = 0.;
  sumEt = 0.;
}

simpletree::CorrectedMet::CorrectedMet(TString const& _name) :
  Met(_name)
{
}

simpletree::CorrectedMet::CorrectedMet(CorrectedMet const& _src) :
  Met(_src),
  metCorrUp(_src.metCorrUp),
  phiCorrUp(_src.phiCorrUp),
  metCorrDown(_src.metCorrDown),
  phiCorrDown(_src.phiCorrDown),
  metJetRes(_src.metJetRes),
  phiJetRes(_src.phiJetRes),
  metUnclUp(_src.metUnclUp),
  phiUnclUp(_src.phiUnclUp),
  metUnclDown(_src.metUnclDown),
  phiUnclDown(_src.phiUnclDown)
{
}

simpletree::CorrectedMet::~CorrectedMet()
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
  flatutils::setStatus(_tree, name_, "metJetRes", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, name_, "phiJetRes", _status, _branches, _whitelist);
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
  flatutils::setStatusAndAddress(_tree, name_, "metJetRes", &metJetRes, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, name_, "phiJetRes", &phiJetRes, _branches, _whitelist);
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
  flatutils::book(_tree, name_, "metJetRes", "", 'F', &metJetRes, _branches, _whitelist);
  flatutils::book(_tree, name_, "phiJetRes", "", 'F', &phiJetRes, _branches, _whitelist);
  flatutils::book(_tree, name_, "metUnclUp", "", 'F', &metUnclUp, _branches, _whitelist);
  flatutils::book(_tree, name_, "phiUnclUp", "", 'F', &phiUnclUp, _branches, _whitelist);
  flatutils::book(_tree, name_, "metUnclDown", "", 'F', &metUnclDown, _branches, _whitelist);
  flatutils::book(_tree, name_, "phiUnclDown", "", 'F', &phiUnclDown, _branches, _whitelist);
}

void
simpletree::CorrectedMet::setStatus(TTree& _tree, TString const& _name, Bool_t _status, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  Met::setStatus(_tree, _name, _status, _branches, _whitelist);

  flatutils::setStatus(_tree, _name, "metCorrUp", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "phiCorrUp", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "metCorrDown", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "phiCorrDown", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "metJetRes", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "phiJetRes", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "metUnclUp", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "phiUnclUp", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "metUnclDown", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "phiUnclDown", _status, _branches, _whitelist);
}

void
simpletree::CorrectedMet::setAddress(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  Met::setAddress(_tree, _name, _branches, _whitelist);

  flatutils::setStatusAndAddress(_tree, _name, "metCorrUp", &metCorrUp, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "phiCorrUp", &phiCorrUp, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "metCorrDown", &metCorrDown, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "phiCorrDown", &phiCorrDown, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "metJetRes", &metJetRes, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "phiJetRes", &phiJetRes, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "metUnclUp", &metUnclUp, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "phiUnclUp", &phiUnclUp, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "metUnclDown", &metUnclDown, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "phiUnclDown", &phiUnclDown, _branches, _whitelist);
}

void
simpletree::CorrectedMet::book(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist)
{
  Met::book(_tree, _name, _branches, _whitelist);

  flatutils::book(_tree, _name, "metCorrUp", "", 'F', &metCorrUp, _branches, _whitelist);
  flatutils::book(_tree, _name, "phiCorrUp", "", 'F', &phiCorrUp, _branches, _whitelist);
  flatutils::book(_tree, _name, "metCorrDown", "", 'F', &metCorrDown, _branches, _whitelist);
  flatutils::book(_tree, _name, "phiCorrDown", "", 'F', &phiCorrDown, _branches, _whitelist);
  flatutils::book(_tree, _name, "metJetRes", "", 'F', &metJetRes, _branches, _whitelist);
  flatutils::book(_tree, _name, "phiJetRes", "", 'F', &phiJetRes, _branches, _whitelist);
  flatutils::book(_tree, _name, "metUnclUp", "", 'F', &metUnclUp, _branches, _whitelist);
  flatutils::book(_tree, _name, "phiUnclUp", "", 'F', &phiUnclUp, _branches, _whitelist);
  flatutils::book(_tree, _name, "metUnclDown", "", 'F', &metUnclDown, _branches, _whitelist);
  flatutils::book(_tree, _name, "phiUnclDown", "", 'F', &phiUnclDown, _branches, _whitelist);
}

simpletree::CorrectedMet&
simpletree::CorrectedMet::operator=(CorrectedMet const& _rhs)
{
  Met::operator=(_rhs);

  metCorrUp = _rhs.metCorrUp;
  phiCorrUp = _rhs.phiCorrUp;
  metCorrDown = _rhs.metCorrDown;
  phiCorrDown = _rhs.phiCorrDown;
  metJetRes = _rhs.metJetRes;
  phiJetRes = _rhs.phiJetRes;
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
  metJetRes = 0.;
  phiJetRes = 0.;
  metUnclUp = 0.;
  phiUnclUp = 0.;
  metUnclDown = 0.;
  phiUnclDown = 0.;
}

simpletree::Parton::array_data::array_data() :
  ParticleM::array_data()
{
}

void
simpletree::Parton::array_data::setStatus(TTree& _tree, TString const& _name, Bool_t _status, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  ParticleM::array_data::setStatus(_tree, _name, _status, _branches, _whitelist);

  flatutils::setStatus(_tree, _name, "pid", _status, _branches, _whitelist);
}

void
simpletree::Parton::array_data::setAddress(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  ParticleM::array_data::setAddress(_tree, _name, _branches, _whitelist);

  flatutils::setStatusAndAddress(_tree, _name, "pid", pid, _branches, _whitelist);
}

void
simpletree::Parton::array_data::book(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  ParticleM::array_data::book(_tree, _name, _branches, _whitelist);

  flatutils::book(_tree, _name, "pid", "[" + _name + ".size]", 'B', pid, _branches, _whitelist);
}

void
simpletree::Parton::setStatus(TTree& _tree, TString const& _name, Bool_t _status, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  ParticleM::setStatus(_tree, _name, _status, _branches, _whitelist);

  flatutils::setStatus(_tree, _name, "pid", _status, _branches, _whitelist);
}

void
simpletree::Parton::setAddress(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  ParticleM::setAddress(_tree, _name, _branches, _whitelist);

  flatutils::setStatusAndAddress(_tree, _name, "pid", &pid, _branches, _whitelist);
}

void
simpletree::Parton::book(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist)
{
  ParticleM::book(_tree, _name, _branches, _whitelist);

  flatutils::book(_tree, _name, "pid", "", 'B', &pid, _branches, _whitelist);
}

/*static*/
std::vector<std::auto_ptr<simpletree::Parton::array_data>> simpletree::Parton::singlesData_{};
/*static*/
simpletree::SinglesPos simpletree::Parton::singlesPos_(-1, simpletree::Parton::array_data::NMAX - 1);
/*static*/
std::set<simpletree::SinglesPos> simpletree::Parton::usedSinglesPos_{};

/*static*/
simpletree::SinglesPos const&
simpletree::Parton::nextSinglesPos_()
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

simpletree::Parton::Parton() :
  ParticleM(*singlesData_.at(nextSinglesPos_().first), singlesPos_.second),
  pid(singlesData_.at(singlesPos_.first)->pid[singlesPos_.second])
{
  pos_ = singlesPos_;
  usedSinglesPos_.insert(pos_);
}

simpletree::Parton::Parton(array_data& _data, UInt_t _idx) :
  ParticleM(_data, _idx),
  pid(_data.pid[_idx])
{
}

simpletree::Parton::Parton(Parton const& _src) :
  ParticleM(_src),
  pid(_src.pid)
{
}

simpletree::Parton::~Parton()
{
  if (pos_.first != unsigned(-1)) {
    usedSinglesPos_.erase(pos_);
    pos_.first = -1;
  }
}

simpletree::Parton&
simpletree::Parton::operator=(Parton const& _rhs)
{
  ParticleM::operator=(_rhs);

  pid = _rhs.pid;
  return *this;
}

void
simpletree::Parton::init()
{
  ParticleM::init();

  pid = 0;
}

simpletree::MCParticle::array_data::array_data() :
  ParticleM::array_data()
{
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

  flatutils::book(_tree, _name, "pid", "[" + _name + ".size]", 'I', pid, _branches, _whitelist);
  flatutils::book(_tree, _name, "ancestor", "[" + _name + ".size]", 'b', ancestor, _branches, _whitelist);
}

void
simpletree::MCParticle::setStatus(TTree& _tree, TString const& _name, Bool_t _status, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  ParticleM::setStatus(_tree, _name, _status, _branches, _whitelist);

  flatutils::setStatus(_tree, _name, "pid", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "ancestor", _status, _branches, _whitelist);
}

void
simpletree::MCParticle::setAddress(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  ParticleM::setAddress(_tree, _name, _branches, _whitelist);

  flatutils::setStatusAndAddress(_tree, _name, "pid", &pid, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "ancestor", &ancestor, _branches, _whitelist);
}

void
simpletree::MCParticle::book(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist)
{
  ParticleM::book(_tree, _name, _branches, _whitelist);

  flatutils::book(_tree, _name, "pid", "", 'I', &pid, _branches, _whitelist);
  flatutils::book(_tree, _name, "ancestor", "", 'b', &ancestor, _branches, _whitelist);
}

/*static*/
std::vector<std::auto_ptr<simpletree::MCParticle::array_data>> simpletree::MCParticle::singlesData_{};
/*static*/
simpletree::SinglesPos simpletree::MCParticle::singlesPos_(-1, simpletree::MCParticle::array_data::NMAX - 1);
/*static*/
std::set<simpletree::SinglesPos> simpletree::MCParticle::usedSinglesPos_{};

/*static*/
simpletree::SinglesPos const&
simpletree::MCParticle::nextSinglesPos_()
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

simpletree::MCParticle::MCParticle() :
  ParticleM(*singlesData_.at(nextSinglesPos_().first), singlesPos_.second),
  pid(singlesData_.at(singlesPos_.first)->pid[singlesPos_.second]),
  ancestor(singlesData_.at(singlesPos_.first)->ancestor[singlesPos_.second])
{
  pos_ = singlesPos_;
  usedSinglesPos_.insert(pos_);
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

simpletree::MCParticle::~MCParticle()
{
  if (pos_.first != unsigned(-1)) {
    usedSinglesPos_.erase(pos_);
    pos_.first = -1;
  }
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

void
simpletree::GenJet::setStatus(TTree& _tree, TString const& _name, Bool_t _status, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  ParticleM::setStatus(_tree, _name, _status, _branches, _whitelist);

}

void
simpletree::GenJet::setAddress(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  ParticleM::setAddress(_tree, _name, _branches, _whitelist);

}

void
simpletree::GenJet::book(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist)
{
  ParticleM::book(_tree, _name, _branches, _whitelist);

}

/*static*/
std::vector<std::auto_ptr<simpletree::GenJet::array_data>> simpletree::GenJet::singlesData_{};
/*static*/
simpletree::SinglesPos simpletree::GenJet::singlesPos_(-1, simpletree::GenJet::array_data::NMAX - 1);
/*static*/
std::set<simpletree::SinglesPos> simpletree::GenJet::usedSinglesPos_{};

/*static*/
simpletree::SinglesPos const&
simpletree::GenJet::nextSinglesPos_()
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

simpletree::GenJet::GenJet() :
  ParticleM(*singlesData_.at(nextSinglesPos_().first), singlesPos_.second)
{
  pos_ = singlesPos_;
  usedSinglesPos_.insert(pos_);
}

simpletree::GenJet::GenJet(array_data& _data, UInt_t _idx) :
  ParticleM(_data, _idx)
{
}

simpletree::GenJet::GenJet(GenJet const& _src) :
  ParticleM(_src)
{
}

simpletree::GenJet::~GenJet()
{
  if (pos_.first != unsigned(-1)) {
    usedSinglesPos_.erase(pos_);
    pos_.first = -1;
  }
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

simpletree::HLTBits::HLTBits(TString const& _name) :
  name_(_name)
{
}

simpletree::HLTBits::HLTBits(HLTBits const& _src) :
  name_(_src.name_)
{
  std::copy_n(_src.words, 16, words);
}

simpletree::HLTBits::~HLTBits()
{
}

void
simpletree::HLTBits::setStatus(TTree& _tree, Bool_t _status, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  flatutils::setStatus(_tree, name_, "words", _status, _branches, _whitelist);
}

void
simpletree::HLTBits::setAddress(TTree& _tree, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  flatutils::setStatusAndAddress(_tree, name_, "words", words, _branches, _whitelist);
}

void
simpletree::HLTBits::book(TTree& _tree, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist)
{
  flatutils::book(_tree, name_, "words", TString::Format("[%d]", 16), 'i', words, _branches, _whitelist);
}

void
simpletree::HLTBits::setStatus(TTree& _tree, TString const& _name, Bool_t _status, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  flatutils::setStatus(_tree, _name, "words", _status, _branches, _whitelist);
}

void
simpletree::HLTBits::setAddress(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  flatutils::setStatusAndAddress(_tree, _name, "words", words, _branches, _whitelist);
}

void
simpletree::HLTBits::book(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist)
{
  flatutils::book(_tree, _name, "words", TString::Format("[%d]", 16), 'i', words, _branches, _whitelist);
}

simpletree::HLTBits&
simpletree::HLTBits::operator=(HLTBits const& _rhs)
{
  std::copy_n(_rhs.words, 16, words);
  return *this;
}

void
simpletree::HLTBits::init()
{
  std::fill(words, words + 16, 0);
}

simpletree::MetFilters::MetFilters(TString const& _name) :
  name_(_name)
{
}

simpletree::MetFilters::MetFilters(MetFilters const& _src) :
  name_(_src.name_),
  cschalo(_src.cschalo),
  globalHalo16(_src.globalHalo16),
  hbhe(_src.hbhe),
  hbheIso(_src.hbheIso),
  ecalDeadCell(_src.ecalDeadCell),
  badsc(_src.badsc),
  badTrack(_src.badTrack),
  badMuonTrack(_src.badMuonTrack)
{
}

simpletree::MetFilters::~MetFilters()
{
}

void
simpletree::MetFilters::setStatus(TTree& _tree, Bool_t _status, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  flatutils::setStatus(_tree, name_, "cschalo", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, name_, "globalHalo16", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, name_, "hbhe", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, name_, "hbheIso", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, name_, "ecalDeadCell", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, name_, "badsc", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, name_, "badTrack", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, name_, "badMuonTrack", _status, _branches, _whitelist);
}

void
simpletree::MetFilters::setAddress(TTree& _tree, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  flatutils::setStatusAndAddress(_tree, name_, "cschalo", &cschalo, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, name_, "globalHalo16", &globalHalo16, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, name_, "hbhe", &hbhe, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, name_, "hbheIso", &hbheIso, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, name_, "ecalDeadCell", &ecalDeadCell, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, name_, "badsc", &badsc, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, name_, "badTrack", &badTrack, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, name_, "badMuonTrack", &badMuonTrack, _branches, _whitelist);
}

void
simpletree::MetFilters::book(TTree& _tree, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist)
{
  flatutils::book(_tree, name_, "cschalo", "", 'O', &cschalo, _branches, _whitelist);
  flatutils::book(_tree, name_, "globalHalo16", "", 'O', &globalHalo16, _branches, _whitelist);
  flatutils::book(_tree, name_, "hbhe", "", 'O', &hbhe, _branches, _whitelist);
  flatutils::book(_tree, name_, "hbheIso", "", 'O', &hbheIso, _branches, _whitelist);
  flatutils::book(_tree, name_, "ecalDeadCell", "", 'O', &ecalDeadCell, _branches, _whitelist);
  flatutils::book(_tree, name_, "badsc", "", 'O', &badsc, _branches, _whitelist);
  flatutils::book(_tree, name_, "badTrack", "", 'O', &badTrack, _branches, _whitelist);
  flatutils::book(_tree, name_, "badMuonTrack", "", 'O', &badMuonTrack, _branches, _whitelist);
}

void
simpletree::MetFilters::setStatus(TTree& _tree, TString const& _name, Bool_t _status, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  flatutils::setStatus(_tree, _name, "cschalo", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "globalHalo16", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "hbhe", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "hbheIso", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "ecalDeadCell", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "badsc", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "badTrack", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "badMuonTrack", _status, _branches, _whitelist);
}

void
simpletree::MetFilters::setAddress(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  flatutils::setStatusAndAddress(_tree, _name, "cschalo", &cschalo, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "globalHalo16", &globalHalo16, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "hbhe", &hbhe, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "hbheIso", &hbheIso, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "ecalDeadCell", &ecalDeadCell, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "badsc", &badsc, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "badTrack", &badTrack, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "badMuonTrack", &badMuonTrack, _branches, _whitelist);
}

void
simpletree::MetFilters::book(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist)
{
  flatutils::book(_tree, _name, "cschalo", "", 'O', &cschalo, _branches, _whitelist);
  flatutils::book(_tree, _name, "globalHalo16", "", 'O', &globalHalo16, _branches, _whitelist);
  flatutils::book(_tree, _name, "hbhe", "", 'O', &hbhe, _branches, _whitelist);
  flatutils::book(_tree, _name, "hbheIso", "", 'O', &hbheIso, _branches, _whitelist);
  flatutils::book(_tree, _name, "ecalDeadCell", "", 'O', &ecalDeadCell, _branches, _whitelist);
  flatutils::book(_tree, _name, "badsc", "", 'O', &badsc, _branches, _whitelist);
  flatutils::book(_tree, _name, "badTrack", "", 'O', &badTrack, _branches, _whitelist);
  flatutils::book(_tree, _name, "badMuonTrack", "", 'O', &badMuonTrack, _branches, _whitelist);
}

simpletree::MetFilters&
simpletree::MetFilters::operator=(MetFilters const& _rhs)
{
  cschalo = _rhs.cschalo;
  globalHalo16 = _rhs.globalHalo16;
  hbhe = _rhs.hbhe;
  hbheIso = _rhs.hbheIso;
  ecalDeadCell = _rhs.ecalDeadCell;
  badsc = _rhs.badsc;
  badTrack = _rhs.badTrack;
  badMuonTrack = _rhs.badMuonTrack;
  return *this;
}

void
simpletree::MetFilters::init()
{
  cschalo = false;
  globalHalo16 = false;
  hbhe = false;
  hbheIso = false;
  ecalDeadCell = false;
  badsc = false;
  badTrack = false;
  badMuonTrack = false;
}

simpletree::Vertex::array_data::array_data()
{
}

void
simpletree::Vertex::array_data::setStatus(TTree& _tree, TString const& _name, Bool_t _status, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  flatutils::setStatus(_tree, _name, "x", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "y", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "z", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "ntrk", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "sumPt2", _status, _branches, _whitelist);
}

void
simpletree::Vertex::array_data::setAddress(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  flatutils::setStatusAndAddress(_tree, _name, "x", x, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "y", y, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "z", z, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "ntrk", ntrk, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "sumPt2", sumPt2, _branches, _whitelist);
}

void
simpletree::Vertex::array_data::book(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  flatutils::book(_tree, _name, "x", "[" + _name + ".size]", 'F', x, _branches, _whitelist);
  flatutils::book(_tree, _name, "y", "[" + _name + ".size]", 'F', y, _branches, _whitelist);
  flatutils::book(_tree, _name, "z", "[" + _name + ".size]", 'F', z, _branches, _whitelist);
  flatutils::book(_tree, _name, "ntrk", "[" + _name + ".size]", 's', ntrk, _branches, _whitelist);
  flatutils::book(_tree, _name, "sumPt2", "[" + _name + ".size]", 'F', sumPt2, _branches, _whitelist);
}

void
simpletree::Vertex::setStatus(TTree& _tree, TString const& _name, Bool_t _status, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  flatutils::setStatus(_tree, _name, "x", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "y", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "z", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "ntrk", _status, _branches, _whitelist);
  flatutils::setStatus(_tree, _name, "sumPt2", _status, _branches, _whitelist);
}

void
simpletree::Vertex::setAddress(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist/* = kTRUE*/)
{
  flatutils::setStatusAndAddress(_tree, _name, "x", &x, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "y", &y, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "z", &z, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "ntrk", &ntrk, _branches, _whitelist);
  flatutils::setStatusAndAddress(_tree, _name, "sumPt2", &sumPt2, _branches, _whitelist);
}

void
simpletree::Vertex::book(TTree& _tree, TString const& _name, flatutils::BranchList const& _branches/* = {"*"}*/, Bool_t _whitelist)
{
  flatutils::book(_tree, _name, "x", "", 'F', &x, _branches, _whitelist);
  flatutils::book(_tree, _name, "y", "", 'F', &y, _branches, _whitelist);
  flatutils::book(_tree, _name, "z", "", 'F', &z, _branches, _whitelist);
  flatutils::book(_tree, _name, "ntrk", "", 's', &ntrk, _branches, _whitelist);
  flatutils::book(_tree, _name, "sumPt2", "", 'F', &sumPt2, _branches, _whitelist);
}

/*static*/
std::vector<std::auto_ptr<simpletree::Vertex::array_data>> simpletree::Vertex::singlesData_{};
/*static*/
simpletree::SinglesPos simpletree::Vertex::singlesPos_(-1, simpletree::Vertex::array_data::NMAX - 1);
/*static*/
std::set<simpletree::SinglesPos> simpletree::Vertex::usedSinglesPos_{};

/*static*/
simpletree::SinglesPos const&
simpletree::Vertex::nextSinglesPos_()
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

simpletree::Vertex::Vertex() :
  pos_(nextSinglesPos_()),
  x(singlesData_.at(singlesPos_.first)->x[singlesPos_.second]),
  y(singlesData_.at(singlesPos_.first)->y[singlesPos_.second]),
  z(singlesData_.at(singlesPos_.first)->z[singlesPos_.second]),
  ntrk(singlesData_.at(singlesPos_.first)->ntrk[singlesPos_.second]),
  sumPt2(singlesData_.at(singlesPos_.first)->sumPt2[singlesPos_.second])
{
  usedSinglesPos_.insert(pos_);
}

simpletree::Vertex::Vertex(array_data& _data, UInt_t _idx) :
  x(_data.x[_idx]),
  y(_data.y[_idx]),
  z(_data.z[_idx]),
  ntrk(_data.ntrk[_idx]),
  sumPt2(_data.sumPt2[_idx])
{
}

simpletree::Vertex::Vertex(Vertex const& _src) :
  x(_src.x),
  y(_src.y),
  z(_src.z),
  ntrk(_src.ntrk),
  sumPt2(_src.sumPt2)
{
}

simpletree::Vertex::~Vertex()
{
  if (pos_.first != unsigned(-1)) {
    usedSinglesPos_.erase(pos_);
    pos_.first = -1;
  }
}

simpletree::Vertex&
simpletree::Vertex::operator=(Vertex const& _rhs)
{
  x = _rhs.x;
  y = _rhs.y;
  z = _rhs.z;
  ntrk = _rhs.ntrk;
  sumPt2 = _rhs.sumPt2;
  return *this;
}

void
simpletree::Vertex::init()
{
  x = 0.;
  y = 0.;
  z = 0.;
  ntrk = 0;
  sumPt2 = 0.;
}

