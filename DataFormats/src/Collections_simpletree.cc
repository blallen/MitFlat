#include "MitFlat/DataFormats/interface/Collections_simpletree.h"
#include "TTree.h"
#include <stdexcept>
#include <memory>

simpletree::ParticleCollection::ParticleCollection(TString const& _name) :
  name_(_name)
{
  objSize_ = sizeof(value_type);
  array_ = std::allocator<value_type>().allocate(NMAX);
  auto* p(array_);
  for (unsigned iP(0); iP != NMAX; ++iP) {
    new (static_cast<pointer>(p)) value_type(*this, iP);
    flatutils::shiftAddr(p, objSize_);
  }
}

simpletree::ParticleCollection::ParticleCollection(ParticleCollection const& _src) :
  name_(_src.name_)
{
  objSize_ = sizeof(value_type);
  array_ = std::allocator<value_type>().allocate(NMAX);
  auto* p(array_);
  for (unsigned iP(0); iP != NMAX; ++iP) {
    new (static_cast<pointer>(p)) value_type(*this, iP);
    static_cast<pointer>(p)->operator=(_src[iP]);
    flatutils::shiftAddr(p, objSize_);
  }
}

//protected
simpletree::ParticleCollection::ParticleCollection(TString const& _name, Bool_t) :
  name_(_name)
{
}

simpletree::ParticleCollection::~ParticleCollection()
{
  if (array_) {
    std::allocator<value_type>().deallocate(static_cast<pointer>(array_), NMAX);
    array_ = 0;
  }
}

simpletree::ParticleCollection&
simpletree::ParticleCollection::operator=(self_type const& _rhs)
{
  name_ = _rhs.name_;
  auto* p(array_);
  for (unsigned iP(0); iP != NMAX; ++iP) {
    static_cast<pointer>(p)->operator=(_rhs[iP]);
    flatutils::shiftAddr(p, objSize_);
  }
  return *this;
}

simpletree::ParticleCollection::reference
simpletree::ParticleCollection::at(UInt_t _idx)
{
  if (_idx >= size)
    throw std::out_of_range("ParticleCollection::at");

  auto* p(array_);
  flatutils::shiftAddr(p, _idx * objSize_);
  return *static_cast<pointer>(p);
}

simpletree::ParticleCollection::const_reference
simpletree::ParticleCollection::at(UInt_t _idx) const
{
  if (_idx < size)
    throw std::out_of_range("ParticleCollection::at");

  auto* p(array_);
  flatutils::shiftAddr(p, _idx * objSize_);
  return *static_cast<const_pointer>(p);
}

simpletree::ParticleCollection::reference
simpletree::ParticleCollection::operator[](UInt_t _idx)
{
  auto* p(array_);
  flatutils::shiftAddr(p, _idx * objSize_);
  return *static_cast<pointer>(p);
}

simpletree::ParticleCollection::const_reference
simpletree::ParticleCollection::operator[](UInt_t _idx) const
{
  auto* p(array_);
  flatutils::shiftAddr(p, _idx * objSize_);
  return *static_cast<const_pointer>(p);
}

void
simpletree::ParticleCollection::push_back(const_reference val)
{
  if (size == NMAX)
    throw std::length_error("ParticleCollection::push_back");

  auto* p(array_);
  flatutils::shiftAddr(p, size * objSize_);
  static_cast<pointer>(p)->operator=(val);
  ++size;
}

void
simpletree::ParticleCollection::resize(UInt_t _size)
{
  if (_size > NMAX)
    throw std::length_error("ParticleCollection::resize");

  size = _size;
}

void
simpletree::ParticleCollection::setStatus(TTree& _tree, Bool_t _status, flatutils::BranchList const& _branches/* = {"*"}*/)
{
  if (_status || flatutils::branchIn("size", _branches))
    _tree.SetBranchStatus(name_ + ".size", _status);
  flatutils::setStatus(_tree, name_, "pt", _status, _branches);
  flatutils::setStatus(_tree, name_, "eta", _status, _branches);
  flatutils::setStatus(_tree, name_, "phi", _status, _branches);
}

void
simpletree::ParticleCollection::setAddress(TTree& _tree, flatutils::BranchList const& _branches/* = {"*"}*/)
{
  flatutils::setStatusAndAddress(_tree, name_, "size", &size, {"size"});
  flatutils::setStatusAndAddress(_tree, name_, "pt", pt, _branches);
  flatutils::setStatusAndAddress(_tree, name_, "eta", eta, _branches);
  flatutils::setStatusAndAddress(_tree, name_, "phi", phi, _branches);
}

void
simpletree::ParticleCollection::book(TTree& _tree, flatutils::BranchList const& _branches/* = {"*"}*/)
{
  _tree.Branch(name_ + ".size", &size, "size/i");
  flatutils::book(_tree, name_, "pt", name_ + ".size", 'F', pt, _branches);
  flatutils::book(_tree, name_, "eta", name_ + ".size", 'F', eta, _branches);
  flatutils::book(_tree, name_, "phi", name_ + ".size", 'F', phi, _branches);
}

simpletree::ParticleMCollection::ParticleMCollection(TString const& _name) :
  ParticleCollection(_name, kFALSE)
{
  objSize_ = sizeof(value_type);
  array_ = std::allocator<value_type>().allocate(NMAX);
  auto* p(array_);
  for (unsigned iP(0); iP != NMAX; ++iP) {
    new (static_cast<pointer>(p)) value_type(*this, iP);
    flatutils::shiftAddr(p, objSize_);
  }
}

simpletree::ParticleMCollection::ParticleMCollection(ParticleMCollection const& _src) :
  ParticleCollection(_src.name_, kFALSE)
{
  objSize_ = sizeof(value_type);
  array_ = std::allocator<value_type>().allocate(NMAX);
  auto* p(array_);
  for (unsigned iP(0); iP != NMAX; ++iP) {
    new (static_cast<pointer>(p)) value_type(*this, iP);
    static_cast<pointer>(p)->operator=(_src[iP]);
    flatutils::shiftAddr(p, objSize_);
  }
}

//protected
simpletree::ParticleMCollection::ParticleMCollection(TString const& _name, Bool_t) :
  ParticleCollection(_name, kFALSE)
{
}

simpletree::ParticleMCollection::~ParticleMCollection()
{
  if (array_) {
    std::allocator<value_type>().deallocate(static_cast<pointer>(array_), NMAX);
    array_ = 0;
  }
}

simpletree::ParticleMCollection&
simpletree::ParticleMCollection::operator=(self_type const& _rhs)
{
  ParticleCollection::operator=(_rhs);
  auto* p(array_);
  for (unsigned iP(0); iP != NMAX; ++iP) {
    static_cast<pointer>(p)->operator=(_rhs[iP]);
    flatutils::shiftAddr(p, objSize_);
  }
  return *this;
}

simpletree::ParticleMCollection::reference
simpletree::ParticleMCollection::at(UInt_t _idx)
{
  if (_idx >= size)
    throw std::out_of_range("ParticleMCollection::at");

  auto* p(array_);
  flatutils::shiftAddr(p, _idx * objSize_);
  return *static_cast<pointer>(p);
}

simpletree::ParticleMCollection::const_reference
simpletree::ParticleMCollection::at(UInt_t _idx) const
{
  if (_idx < size)
    throw std::out_of_range("ParticleMCollection::at");

  auto* p(array_);
  flatutils::shiftAddr(p, _idx * objSize_);
  return *static_cast<const_pointer>(p);
}

simpletree::ParticleMCollection::reference
simpletree::ParticleMCollection::operator[](UInt_t _idx)
{
  auto* p(array_);
  flatutils::shiftAddr(p, _idx * objSize_);
  return *static_cast<pointer>(p);
}

simpletree::ParticleMCollection::const_reference
simpletree::ParticleMCollection::operator[](UInt_t _idx) const
{
  auto* p(array_);
  flatutils::shiftAddr(p, _idx * objSize_);
  return *static_cast<const_pointer>(p);
}

void
simpletree::ParticleMCollection::push_back(const_reference val)
{
  if (size == NMAX)
    throw std::length_error("ParticleMCollection::push_back");

  auto* p(array_);
  flatutils::shiftAddr(p, size * objSize_);
  static_cast<pointer>(p)->operator=(val);
  ++size;
}

void
simpletree::ParticleMCollection::setStatus(TTree& _tree, Bool_t _status, flatutils::BranchList const& _branches/* = {"*"}*/)
{
  ParticleCollection::setStatus(_tree, _status, _branches);

  flatutils::setStatus(_tree, name_, "mass", _status, _branches);
}

void
simpletree::ParticleMCollection::setAddress(TTree& _tree, flatutils::BranchList const& _branches/* = {"*"}*/)
{
  ParticleCollection::setAddress(_tree, _branches);

  flatutils::setStatusAndAddress(_tree, name_, "mass", mass, _branches);
}

void
simpletree::ParticleMCollection::book(TTree& _tree, flatutils::BranchList const& _branches/* = {"*"}*/)
{
  ParticleCollection::book(_tree, _branches);

  flatutils::book(_tree, name_, "mass", name_ + ".size", 'F', mass, _branches);
}

simpletree::JetCollection::JetCollection(TString const& _name) :
  ParticleMCollection(_name, kFALSE)
{
  objSize_ = sizeof(value_type);
  array_ = std::allocator<value_type>().allocate(NMAX);
  auto* p(array_);
  for (unsigned iP(0); iP != NMAX; ++iP) {
    new (static_cast<pointer>(p)) value_type(*this, iP);
    flatutils::shiftAddr(p, objSize_);
  }
}

simpletree::JetCollection::JetCollection(JetCollection const& _src) :
  ParticleMCollection(_src.name_, kFALSE)
{
  objSize_ = sizeof(value_type);
  array_ = std::allocator<value_type>().allocate(NMAX);
  auto* p(array_);
  for (unsigned iP(0); iP != NMAX; ++iP) {
    new (static_cast<pointer>(p)) value_type(*this, iP);
    static_cast<pointer>(p)->operator=(_src[iP]);
    flatutils::shiftAddr(p, objSize_);
  }
}

//protected
simpletree::JetCollection::JetCollection(TString const& _name, Bool_t) :
  ParticleMCollection(_name, kFALSE)
{
}

simpletree::JetCollection::~JetCollection()
{
  if (array_) {
    std::allocator<value_type>().deallocate(static_cast<pointer>(array_), NMAX);
    array_ = 0;
  }
}

simpletree::JetCollection&
simpletree::JetCollection::operator=(self_type const& _rhs)
{
  ParticleMCollection::operator=(_rhs);
  auto* p(array_);
  for (unsigned iP(0); iP != NMAX; ++iP) {
    static_cast<pointer>(p)->operator=(_rhs[iP]);
    flatutils::shiftAddr(p, objSize_);
  }
  return *this;
}

simpletree::JetCollection::reference
simpletree::JetCollection::at(UInt_t _idx)
{
  if (_idx >= size)
    throw std::out_of_range("JetCollection::at");

  auto* p(array_);
  flatutils::shiftAddr(p, _idx * objSize_);
  return *static_cast<pointer>(p);
}

simpletree::JetCollection::const_reference
simpletree::JetCollection::at(UInt_t _idx) const
{
  if (_idx < size)
    throw std::out_of_range("JetCollection::at");

  auto* p(array_);
  flatutils::shiftAddr(p, _idx * objSize_);
  return *static_cast<const_pointer>(p);
}

simpletree::JetCollection::reference
simpletree::JetCollection::operator[](UInt_t _idx)
{
  auto* p(array_);
  flatutils::shiftAddr(p, _idx * objSize_);
  return *static_cast<pointer>(p);
}

simpletree::JetCollection::const_reference
simpletree::JetCollection::operator[](UInt_t _idx) const
{
  auto* p(array_);
  flatutils::shiftAddr(p, _idx * objSize_);
  return *static_cast<const_pointer>(p);
}

void
simpletree::JetCollection::push_back(const_reference val)
{
  if (size == NMAX)
    throw std::length_error("JetCollection::push_back");

  auto* p(array_);
  flatutils::shiftAddr(p, size * objSize_);
  static_cast<pointer>(p)->operator=(val);
  ++size;
}

void
simpletree::JetCollection::setStatus(TTree& _tree, Bool_t _status, flatutils::BranchList const& _branches/* = {"*"}*/)
{
  ParticleMCollection::setStatus(_tree, _status, _branches);

}

void
simpletree::JetCollection::setAddress(TTree& _tree, flatutils::BranchList const& _branches/* = {"*"}*/)
{
  ParticleMCollection::setAddress(_tree, _branches);

}

void
simpletree::JetCollection::book(TTree& _tree, flatutils::BranchList const& _branches/* = {"*"}*/)
{
  ParticleMCollection::book(_tree, _branches);

}

simpletree::PhotonCollection::PhotonCollection(TString const& _name) :
  ParticleCollection(_name, kFALSE)
{
  objSize_ = sizeof(value_type);
  array_ = std::allocator<value_type>().allocate(NMAX);
  auto* p(array_);
  for (unsigned iP(0); iP != NMAX; ++iP) {
    new (static_cast<pointer>(p)) value_type(*this, iP);
    flatutils::shiftAddr(p, objSize_);
  }
}

simpletree::PhotonCollection::PhotonCollection(PhotonCollection const& _src) :
  ParticleCollection(_src.name_, kFALSE)
{
  objSize_ = sizeof(value_type);
  array_ = std::allocator<value_type>().allocate(NMAX);
  auto* p(array_);
  for (unsigned iP(0); iP != NMAX; ++iP) {
    new (static_cast<pointer>(p)) value_type(*this, iP);
    static_cast<pointer>(p)->operator=(_src[iP]);
    flatutils::shiftAddr(p, objSize_);
  }
}

//protected
simpletree::PhotonCollection::PhotonCollection(TString const& _name, Bool_t) :
  ParticleCollection(_name, kFALSE)
{
}

simpletree::PhotonCollection::~PhotonCollection()
{
  if (array_) {
    std::allocator<value_type>().deallocate(static_cast<pointer>(array_), NMAX);
    array_ = 0;
  }
}

simpletree::PhotonCollection&
simpletree::PhotonCollection::operator=(self_type const& _rhs)
{
  ParticleCollection::operator=(_rhs);
  auto* p(array_);
  for (unsigned iP(0); iP != NMAX; ++iP) {
    static_cast<pointer>(p)->operator=(_rhs[iP]);
    flatutils::shiftAddr(p, objSize_);
  }
  return *this;
}

simpletree::PhotonCollection::reference
simpletree::PhotonCollection::at(UInt_t _idx)
{
  if (_idx >= size)
    throw std::out_of_range("PhotonCollection::at");

  auto* p(array_);
  flatutils::shiftAddr(p, _idx * objSize_);
  return *static_cast<pointer>(p);
}

simpletree::PhotonCollection::const_reference
simpletree::PhotonCollection::at(UInt_t _idx) const
{
  if (_idx < size)
    throw std::out_of_range("PhotonCollection::at");

  auto* p(array_);
  flatutils::shiftAddr(p, _idx * objSize_);
  return *static_cast<const_pointer>(p);
}

simpletree::PhotonCollection::reference
simpletree::PhotonCollection::operator[](UInt_t _idx)
{
  auto* p(array_);
  flatutils::shiftAddr(p, _idx * objSize_);
  return *static_cast<pointer>(p);
}

simpletree::PhotonCollection::const_reference
simpletree::PhotonCollection::operator[](UInt_t _idx) const
{
  auto* p(array_);
  flatutils::shiftAddr(p, _idx * objSize_);
  return *static_cast<const_pointer>(p);
}

void
simpletree::PhotonCollection::push_back(const_reference val)
{
  if (size == NMAX)
    throw std::length_error("PhotonCollection::push_back");

  auto* p(array_);
  flatutils::shiftAddr(p, size * objSize_);
  static_cast<pointer>(p)->operator=(val);
  ++size;
}

void
simpletree::PhotonCollection::setStatus(TTree& _tree, Bool_t _status, flatutils::BranchList const& _branches/* = {"*"}*/)
{
  ParticleCollection::setStatus(_tree, _status, _branches);

  flatutils::setStatus(_tree, name_, "chIso", _status, _branches);
  flatutils::setStatus(_tree, name_, "nhIso", _status, _branches);
  flatutils::setStatus(_tree, name_, "phIso", _status, _branches);
  flatutils::setStatus(_tree, name_, "sieie", _status, _branches);
  flatutils::setStatus(_tree, name_, "hOverE", _status, _branches);
  flatutils::setStatus(_tree, name_, "matchedGen", _status, _branches);
  flatutils::setStatus(_tree, name_, "hadDecay", _status, _branches);
  flatutils::setStatus(_tree, name_, "pixelVeto", _status, _branches);
  flatutils::setStatus(_tree, name_, "csafeVeto", _status, _branches);
  flatutils::setStatus(_tree, name_, "loose", _status, _branches);
  flatutils::setStatus(_tree, name_, "medium", _status, _branches);
  flatutils::setStatus(_tree, name_, "tight", _status, _branches);
  flatutils::setStatus(_tree, name_, "matchHLT120", _status, _branches);
  flatutils::setStatus(_tree, name_, "matchHLT165HE10", _status, _branches);
  flatutils::setStatus(_tree, name_, "matchHLT175", _status, _branches);
}

void
simpletree::PhotonCollection::setAddress(TTree& _tree, flatutils::BranchList const& _branches/* = {"*"}*/)
{
  ParticleCollection::setAddress(_tree, _branches);

  flatutils::setStatusAndAddress(_tree, name_, "chIso", chIso, _branches);
  flatutils::setStatusAndAddress(_tree, name_, "nhIso", nhIso, _branches);
  flatutils::setStatusAndAddress(_tree, name_, "phIso", phIso, _branches);
  flatutils::setStatusAndAddress(_tree, name_, "sieie", sieie, _branches);
  flatutils::setStatusAndAddress(_tree, name_, "hOverE", hOverE, _branches);
  flatutils::setStatusAndAddress(_tree, name_, "matchedGen", matchedGen, _branches);
  flatutils::setStatusAndAddress(_tree, name_, "hadDecay", hadDecay, _branches);
  flatutils::setStatusAndAddress(_tree, name_, "pixelVeto", pixelVeto, _branches);
  flatutils::setStatusAndAddress(_tree, name_, "csafeVeto", csafeVeto, _branches);
  flatutils::setStatusAndAddress(_tree, name_, "loose", loose, _branches);
  flatutils::setStatusAndAddress(_tree, name_, "medium", medium, _branches);
  flatutils::setStatusAndAddress(_tree, name_, "tight", tight, _branches);
  flatutils::setStatusAndAddress(_tree, name_, "matchHLT120", matchHLT120, _branches);
  flatutils::setStatusAndAddress(_tree, name_, "matchHLT165HE10", matchHLT165HE10, _branches);
  flatutils::setStatusAndAddress(_tree, name_, "matchHLT175", matchHLT175, _branches);
}

void
simpletree::PhotonCollection::book(TTree& _tree, flatutils::BranchList const& _branches/* = {"*"}*/)
{
  ParticleCollection::book(_tree, _branches);

  flatutils::book(_tree, name_, "chIso", name_ + ".size", 'F', chIso, _branches);
  flatutils::book(_tree, name_, "nhIso", name_ + ".size", 'F', nhIso, _branches);
  flatutils::book(_tree, name_, "phIso", name_ + ".size", 'F', phIso, _branches);
  flatutils::book(_tree, name_, "sieie", name_ + ".size", 'F', sieie, _branches);
  flatutils::book(_tree, name_, "hOverE", name_ + ".size", 'F', hOverE, _branches);
  flatutils::book(_tree, name_, "matchedGen", name_ + ".size", 'I', matchedGen, _branches);
  flatutils::book(_tree, name_, "hadDecay", name_ + ".size", 'O', hadDecay, _branches);
  flatutils::book(_tree, name_, "pixelVeto", name_ + ".size", 'O', pixelVeto, _branches);
  flatutils::book(_tree, name_, "csafeVeto", name_ + ".size", 'O', csafeVeto, _branches);
  flatutils::book(_tree, name_, "loose", name_ + ".size", 'O', loose, _branches);
  flatutils::book(_tree, name_, "medium", name_ + ".size", 'O', medium, _branches);
  flatutils::book(_tree, name_, "tight", name_ + ".size", 'O', tight, _branches);
  flatutils::book(_tree, name_, "matchHLT120", name_ + ".size", 'O', matchHLT120, _branches);
  flatutils::book(_tree, name_, "matchHLT165HE10", name_ + ".size", 'O', matchHLT165HE10, _branches);
  flatutils::book(_tree, name_, "matchHLT175", name_ + ".size", 'O', matchHLT175, _branches);
}

simpletree::LeptonCollection::LeptonCollection(TString const& _name) :
  ParticleMCollection(_name, kFALSE)
{
  objSize_ = sizeof(value_type);
  array_ = std::allocator<value_type>().allocate(NMAX);
  auto* p(array_);
  for (unsigned iP(0); iP != NMAX; ++iP) {
    new (static_cast<pointer>(p)) value_type(*this, iP);
    flatutils::shiftAddr(p, objSize_);
  }
}

simpletree::LeptonCollection::LeptonCollection(LeptonCollection const& _src) :
  ParticleMCollection(_src.name_, kFALSE)
{
  objSize_ = sizeof(value_type);
  array_ = std::allocator<value_type>().allocate(NMAX);
  auto* p(array_);
  for (unsigned iP(0); iP != NMAX; ++iP) {
    new (static_cast<pointer>(p)) value_type(*this, iP);
    static_cast<pointer>(p)->operator=(_src[iP]);
    flatutils::shiftAddr(p, objSize_);
  }
}

//protected
simpletree::LeptonCollection::LeptonCollection(TString const& _name, Bool_t) :
  ParticleMCollection(_name, kFALSE)
{
}

simpletree::LeptonCollection::~LeptonCollection()
{
  if (array_) {
    std::allocator<value_type>().deallocate(static_cast<pointer>(array_), NMAX);
    array_ = 0;
  }
}

simpletree::LeptonCollection&
simpletree::LeptonCollection::operator=(self_type const& _rhs)
{
  ParticleMCollection::operator=(_rhs);
  auto* p(array_);
  for (unsigned iP(0); iP != NMAX; ++iP) {
    static_cast<pointer>(p)->operator=(_rhs[iP]);
    flatutils::shiftAddr(p, objSize_);
  }
  return *this;
}

simpletree::LeptonCollection::reference
simpletree::LeptonCollection::at(UInt_t _idx)
{
  if (_idx >= size)
    throw std::out_of_range("LeptonCollection::at");

  auto* p(array_);
  flatutils::shiftAddr(p, _idx * objSize_);
  return *static_cast<pointer>(p);
}

simpletree::LeptonCollection::const_reference
simpletree::LeptonCollection::at(UInt_t _idx) const
{
  if (_idx < size)
    throw std::out_of_range("LeptonCollection::at");

  auto* p(array_);
  flatutils::shiftAddr(p, _idx * objSize_);
  return *static_cast<const_pointer>(p);
}

simpletree::LeptonCollection::reference
simpletree::LeptonCollection::operator[](UInt_t _idx)
{
  auto* p(array_);
  flatutils::shiftAddr(p, _idx * objSize_);
  return *static_cast<pointer>(p);
}

simpletree::LeptonCollection::const_reference
simpletree::LeptonCollection::operator[](UInt_t _idx) const
{
  auto* p(array_);
  flatutils::shiftAddr(p, _idx * objSize_);
  return *static_cast<const_pointer>(p);
}

void
simpletree::LeptonCollection::push_back(const_reference val)
{
  if (size == NMAX)
    throw std::length_error("LeptonCollection::push_back");

  auto* p(array_);
  flatutils::shiftAddr(p, size * objSize_);
  static_cast<pointer>(p)->operator=(val);
  ++size;
}

void
simpletree::LeptonCollection::setStatus(TTree& _tree, Bool_t _status, flatutils::BranchList const& _branches/* = {"*"}*/)
{
  ParticleMCollection::setStatus(_tree, _status, _branches);

  flatutils::setStatus(_tree, name_, "matchedGen", _status, _branches);
  flatutils::setStatus(_tree, name_, "tauDecay", _status, _branches);
  flatutils::setStatus(_tree, name_, "hadDecay", _status, _branches);
  flatutils::setStatus(_tree, name_, "positive", _status, _branches);
  flatutils::setStatus(_tree, name_, "loose", _status, _branches);
  flatutils::setStatus(_tree, name_, "tight", _status, _branches);
}

void
simpletree::LeptonCollection::setAddress(TTree& _tree, flatutils::BranchList const& _branches/* = {"*"}*/)
{
  ParticleMCollection::setAddress(_tree, _branches);

  flatutils::setStatusAndAddress(_tree, name_, "matchedGen", matchedGen, _branches);
  flatutils::setStatusAndAddress(_tree, name_, "tauDecay", tauDecay, _branches);
  flatutils::setStatusAndAddress(_tree, name_, "hadDecay", hadDecay, _branches);
  flatutils::setStatusAndAddress(_tree, name_, "positive", positive, _branches);
  flatutils::setStatusAndAddress(_tree, name_, "loose", loose, _branches);
  flatutils::setStatusAndAddress(_tree, name_, "tight", tight, _branches);
}

void
simpletree::LeptonCollection::book(TTree& _tree, flatutils::BranchList const& _branches/* = {"*"}*/)
{
  ParticleMCollection::book(_tree, _branches);

  flatutils::book(_tree, name_, "matchedGen", name_ + ".size", 'I', matchedGen, _branches);
  flatutils::book(_tree, name_, "tauDecay", name_ + ".size", 'O', tauDecay, _branches);
  flatutils::book(_tree, name_, "hadDecay", name_ + ".size", 'O', hadDecay, _branches);
  flatutils::book(_tree, name_, "positive", name_ + ".size", 'O', positive, _branches);
  flatutils::book(_tree, name_, "loose", name_ + ".size", 'O', loose, _branches);
  flatutils::book(_tree, name_, "tight", name_ + ".size", 'O', tight, _branches);
}

simpletree::ElectronCollection::ElectronCollection(TString const& _name) :
  LeptonCollection(_name, kFALSE)
{
  objSize_ = sizeof(value_type);
  array_ = std::allocator<value_type>().allocate(NMAX);
  auto* p(array_);
  for (unsigned iP(0); iP != NMAX; ++iP) {
    new (static_cast<pointer>(p)) value_type(*this, iP);
    flatutils::shiftAddr(p, objSize_);
  }
}

simpletree::ElectronCollection::ElectronCollection(ElectronCollection const& _src) :
  LeptonCollection(_src.name_, kFALSE)
{
  objSize_ = sizeof(value_type);
  array_ = std::allocator<value_type>().allocate(NMAX);
  auto* p(array_);
  for (unsigned iP(0); iP != NMAX; ++iP) {
    new (static_cast<pointer>(p)) value_type(*this, iP);
    static_cast<pointer>(p)->operator=(_src[iP]);
    flatutils::shiftAddr(p, objSize_);
  }
}

//protected
simpletree::ElectronCollection::ElectronCollection(TString const& _name, Bool_t) :
  LeptonCollection(_name, kFALSE)
{
}

simpletree::ElectronCollection::~ElectronCollection()
{
  if (array_) {
    std::allocator<value_type>().deallocate(static_cast<pointer>(array_), NMAX);
    array_ = 0;
  }
}

simpletree::ElectronCollection&
simpletree::ElectronCollection::operator=(self_type const& _rhs)
{
  LeptonCollection::operator=(_rhs);
  auto* p(array_);
  for (unsigned iP(0); iP != NMAX; ++iP) {
    static_cast<pointer>(p)->operator=(_rhs[iP]);
    flatutils::shiftAddr(p, objSize_);
  }
  return *this;
}

simpletree::ElectronCollection::reference
simpletree::ElectronCollection::at(UInt_t _idx)
{
  if (_idx >= size)
    throw std::out_of_range("ElectronCollection::at");

  auto* p(array_);
  flatutils::shiftAddr(p, _idx * objSize_);
  return *static_cast<pointer>(p);
}

simpletree::ElectronCollection::const_reference
simpletree::ElectronCollection::at(UInt_t _idx) const
{
  if (_idx < size)
    throw std::out_of_range("ElectronCollection::at");

  auto* p(array_);
  flatutils::shiftAddr(p, _idx * objSize_);
  return *static_cast<const_pointer>(p);
}

simpletree::ElectronCollection::reference
simpletree::ElectronCollection::operator[](UInt_t _idx)
{
  auto* p(array_);
  flatutils::shiftAddr(p, _idx * objSize_);
  return *static_cast<pointer>(p);
}

simpletree::ElectronCollection::const_reference
simpletree::ElectronCollection::operator[](UInt_t _idx) const
{
  auto* p(array_);
  flatutils::shiftAddr(p, _idx * objSize_);
  return *static_cast<const_pointer>(p);
}

void
simpletree::ElectronCollection::push_back(const_reference val)
{
  if (size == NMAX)
    throw std::length_error("ElectronCollection::push_back");

  auto* p(array_);
  flatutils::shiftAddr(p, size * objSize_);
  static_cast<pointer>(p)->operator=(val);
  ++size;
}

void
simpletree::ElectronCollection::setStatus(TTree& _tree, Bool_t _status, flatutils::BranchList const& _branches/* = {"*"}*/)
{
  LeptonCollection::setStatus(_tree, _status, _branches);

  flatutils::setStatus(_tree, name_, "chIsoPh", _status, _branches);
  flatutils::setStatus(_tree, name_, "nhIsoPh", _status, _branches);
  flatutils::setStatus(_tree, name_, "phIsoPh", _status, _branches);
  flatutils::setStatus(_tree, name_, "sieie", _status, _branches);
  flatutils::setStatus(_tree, name_, "hOverE", _status, _branches);
  flatutils::setStatus(_tree, name_, "matchHLT23Loose", _status, _branches);
  flatutils::setStatus(_tree, name_, "matchHLT27Loose", _status, _branches);
}

void
simpletree::ElectronCollection::setAddress(TTree& _tree, flatutils::BranchList const& _branches/* = {"*"}*/)
{
  LeptonCollection::setAddress(_tree, _branches);

  flatutils::setStatusAndAddress(_tree, name_, "chIsoPh", chIsoPh, _branches);
  flatutils::setStatusAndAddress(_tree, name_, "nhIsoPh", nhIsoPh, _branches);
  flatutils::setStatusAndAddress(_tree, name_, "phIsoPh", phIsoPh, _branches);
  flatutils::setStatusAndAddress(_tree, name_, "sieie", sieie, _branches);
  flatutils::setStatusAndAddress(_tree, name_, "hOverE", hOverE, _branches);
  flatutils::setStatusAndAddress(_tree, name_, "matchHLT23Loose", matchHLT23Loose, _branches);
  flatutils::setStatusAndAddress(_tree, name_, "matchHLT27Loose", matchHLT27Loose, _branches);
}

void
simpletree::ElectronCollection::book(TTree& _tree, flatutils::BranchList const& _branches/* = {"*"}*/)
{
  LeptonCollection::book(_tree, _branches);

  flatutils::book(_tree, name_, "chIsoPh", name_ + ".size", 'F', chIsoPh, _branches);
  flatutils::book(_tree, name_, "nhIsoPh", name_ + ".size", 'F', nhIsoPh, _branches);
  flatutils::book(_tree, name_, "phIsoPh", name_ + ".size", 'F', phIsoPh, _branches);
  flatutils::book(_tree, name_, "sieie", name_ + ".size", 'F', sieie, _branches);
  flatutils::book(_tree, name_, "hOverE", name_ + ".size", 'F', hOverE, _branches);
  flatutils::book(_tree, name_, "matchHLT23Loose", name_ + ".size", 'O', matchHLT23Loose, _branches);
  flatutils::book(_tree, name_, "matchHLT27Loose", name_ + ".size", 'O', matchHLT27Loose, _branches);
}

simpletree::MuonCollection::MuonCollection(TString const& _name) :
  LeptonCollection(_name, kFALSE)
{
  objSize_ = sizeof(value_type);
  array_ = std::allocator<value_type>().allocate(NMAX);
  auto* p(array_);
  for (unsigned iP(0); iP != NMAX; ++iP) {
    new (static_cast<pointer>(p)) value_type(*this, iP);
    flatutils::shiftAddr(p, objSize_);
  }
}

simpletree::MuonCollection::MuonCollection(MuonCollection const& _src) :
  LeptonCollection(_src.name_, kFALSE)
{
  objSize_ = sizeof(value_type);
  array_ = std::allocator<value_type>().allocate(NMAX);
  auto* p(array_);
  for (unsigned iP(0); iP != NMAX; ++iP) {
    new (static_cast<pointer>(p)) value_type(*this, iP);
    static_cast<pointer>(p)->operator=(_src[iP]);
    flatutils::shiftAddr(p, objSize_);
  }
}

//protected
simpletree::MuonCollection::MuonCollection(TString const& _name, Bool_t) :
  LeptonCollection(_name, kFALSE)
{
}

simpletree::MuonCollection::~MuonCollection()
{
  if (array_) {
    std::allocator<value_type>().deallocate(static_cast<pointer>(array_), NMAX);
    array_ = 0;
  }
}

simpletree::MuonCollection&
simpletree::MuonCollection::operator=(self_type const& _rhs)
{
  LeptonCollection::operator=(_rhs);
  auto* p(array_);
  for (unsigned iP(0); iP != NMAX; ++iP) {
    static_cast<pointer>(p)->operator=(_rhs[iP]);
    flatutils::shiftAddr(p, objSize_);
  }
  return *this;
}

simpletree::MuonCollection::reference
simpletree::MuonCollection::at(UInt_t _idx)
{
  if (_idx >= size)
    throw std::out_of_range("MuonCollection::at");

  auto* p(array_);
  flatutils::shiftAddr(p, _idx * objSize_);
  return *static_cast<pointer>(p);
}

simpletree::MuonCollection::const_reference
simpletree::MuonCollection::at(UInt_t _idx) const
{
  if (_idx < size)
    throw std::out_of_range("MuonCollection::at");

  auto* p(array_);
  flatutils::shiftAddr(p, _idx * objSize_);
  return *static_cast<const_pointer>(p);
}

simpletree::MuonCollection::reference
simpletree::MuonCollection::operator[](UInt_t _idx)
{
  auto* p(array_);
  flatutils::shiftAddr(p, _idx * objSize_);
  return *static_cast<pointer>(p);
}

simpletree::MuonCollection::const_reference
simpletree::MuonCollection::operator[](UInt_t _idx) const
{
  auto* p(array_);
  flatutils::shiftAddr(p, _idx * objSize_);
  return *static_cast<const_pointer>(p);
}

void
simpletree::MuonCollection::push_back(const_reference val)
{
  if (size == NMAX)
    throw std::length_error("MuonCollection::push_back");

  auto* p(array_);
  flatutils::shiftAddr(p, size * objSize_);
  static_cast<pointer>(p)->operator=(val);
  ++size;
}

void
simpletree::MuonCollection::setStatus(TTree& _tree, Bool_t _status, flatutils::BranchList const& _branches/* = {"*"}*/)
{
  LeptonCollection::setStatus(_tree, _status, _branches);

  flatutils::setStatus(_tree, name_, "matchHLT24", _status, _branches);
  flatutils::setStatus(_tree, name_, "matchHLT27", _status, _branches);
}

void
simpletree::MuonCollection::setAddress(TTree& _tree, flatutils::BranchList const& _branches/* = {"*"}*/)
{
  LeptonCollection::setAddress(_tree, _branches);

  flatutils::setStatusAndAddress(_tree, name_, "matchHLT24", matchHLT24, _branches);
  flatutils::setStatusAndAddress(_tree, name_, "matchHLT27", matchHLT27, _branches);
}

void
simpletree::MuonCollection::book(TTree& _tree, flatutils::BranchList const& _branches/* = {"*"}*/)
{
  LeptonCollection::book(_tree, _branches);

  flatutils::book(_tree, name_, "matchHLT24", name_ + ".size", 'O', matchHLT24, _branches);
  flatutils::book(_tree, name_, "matchHLT27", name_ + ".size", 'O', matchHLT27, _branches);
}

simpletree::HLTCollection::HLTCollection(TString const& _name) :
  name_(_name)
{
  objSize_ = sizeof(value_type);
  array_ = std::allocator<value_type>().allocate(NMAX);
  auto* p(array_);
  for (unsigned iP(0); iP != NMAX; ++iP) {
    new (static_cast<pointer>(p)) value_type(*this, iP);
    flatutils::shiftAddr(p, objSize_);
  }
}

simpletree::HLTCollection::HLTCollection(HLTCollection const& _src) :
  name_(_src.name_)
{
  objSize_ = sizeof(value_type);
  array_ = std::allocator<value_type>().allocate(NMAX);
  auto* p(array_);
  for (unsigned iP(0); iP != NMAX; ++iP) {
    new (static_cast<pointer>(p)) value_type(*this, iP);
    static_cast<pointer>(p)->operator=(_src[iP]);
    flatutils::shiftAddr(p, objSize_);
  }
}

//protected
simpletree::HLTCollection::HLTCollection(TString const& _name, Bool_t) :
  name_(_name)
{
}

simpletree::HLTCollection::~HLTCollection()
{
  if (array_) {
    std::allocator<value_type>().deallocate(static_cast<pointer>(array_), NMAX);
    array_ = 0;
  }
}

simpletree::HLTCollection&
simpletree::HLTCollection::operator=(self_type const& _rhs)
{
  name_ = _rhs.name_;
  auto* p(array_);
  for (unsigned iP(0); iP != NMAX; ++iP) {
    static_cast<pointer>(p)->operator=(_rhs[iP]);
    flatutils::shiftAddr(p, objSize_);
  }
  return *this;
}

simpletree::HLTCollection::reference
simpletree::HLTCollection::at(UInt_t _idx)
{
  if (_idx >= size)
    throw std::out_of_range("HLTCollection::at");

  auto* p(array_);
  flatutils::shiftAddr(p, _idx * objSize_);
  return *static_cast<pointer>(p);
}

simpletree::HLTCollection::const_reference
simpletree::HLTCollection::at(UInt_t _idx) const
{
  if (_idx < size)
    throw std::out_of_range("HLTCollection::at");

  auto* p(array_);
  flatutils::shiftAddr(p, _idx * objSize_);
  return *static_cast<const_pointer>(p);
}

simpletree::HLTCollection::reference
simpletree::HLTCollection::operator[](UInt_t _idx)
{
  auto* p(array_);
  flatutils::shiftAddr(p, _idx * objSize_);
  return *static_cast<pointer>(p);
}

simpletree::HLTCollection::const_reference
simpletree::HLTCollection::operator[](UInt_t _idx) const
{
  auto* p(array_);
  flatutils::shiftAddr(p, _idx * objSize_);
  return *static_cast<const_pointer>(p);
}

void
simpletree::HLTCollection::setStatus(TTree& _tree, Bool_t _status, flatutils::BranchList const& _branches/* = {"*"}*/)
{
  flatutils::setStatus(_tree, name_, "pass", _status, _branches);
}

void
simpletree::HLTCollection::setAddress(TTree& _tree, flatutils::BranchList const& _branches/* = {"*"}*/)
{
  flatutils::setStatusAndAddress(_tree, name_, "pass", pass, _branches);
}

void
simpletree::HLTCollection::book(TTree& _tree, flatutils::BranchList const& _branches/* = {"*"}*/)
{
  flatutils::book(_tree, name_, "pass", TString::Format("%d", NMAX), 'O', pass, _branches);
}

