#include "MitFlat/DataFormats/interface/Collections_simpletree.h"
#include "TTree.h"
#include <stdexcept>
#include <memory>

simpletree::ParticleCollection::ParticleCollection()
{
  objSize_ = sizeof(Particle);
  array_ = std::allocator<Particle>().allocate(NMAX);
  for (unsigned iP(0); iP != NMAX; ++iP)
    new (static_cast<Particle*>(array_) + iP) Particle(*this, iP);
}

//protected
simpletree::ParticleCollection::ParticleCollection(Bool_t)
{
}

simpletree::ParticleCollection::~ParticleCollection()
{
  if (array_) {
    std::allocator<Particle>().deallocate(static_cast<Particle*>(array_), NMAX);
    array_ = 0;
  }
}

simpletree::ParticleCollection::reference
simpletree::ParticleCollection::at(UInt_t _idx)
{
  if (_idx < size) {
    auto* p(array_);
    flatutils::shiftAddr(p, _idx * objSize_);
    return *static_cast<Particle*>(p);
  }

  throw std::out_of_range("ParticleCollection::at");
}

simpletree::ParticleCollection::const_reference
simpletree::ParticleCollection::at(UInt_t _idx) const
{
  if (_idx < size) {
    auto* p(array_);
    flatutils::shiftAddr(p, _idx * objSize_);
    return *static_cast<Particle const*>(p);
  }

  throw std::out_of_range("ParticleCollection::at");
}

simpletree::ParticleCollection::reference
simpletree::ParticleCollection::operator[](UInt_t _idx)
{
  auto* p(array_);
  flatutils::shiftAddr(p, _idx * objSize_);
  return *static_cast<Particle*>(p);
}

simpletree::ParticleCollection::const_reference
simpletree::ParticleCollection::operator[](UInt_t _idx) const
{
  auto* p(array_);
  flatutils::shiftAddr(p, _idx * objSize_);
  return *static_cast<Particle const*>(p);
}

void
simpletree::ParticleCollection::push_back(const_reference val)
{
  UInt_t current(size);
  resize(current + 1);
  array_[current] = val;
}

void
simpletree::ParticleCollection::resize(UInt_t _size)
{
  if (_size <= NMAX) {
    size = _size;
    return;
  }
  throw std::length_error("ParticleCollection::resize");
}

void
simpletree::ParticleCollection::setAddress(TTree& _tree, TString const& _objName)
{
  _tree.SetBranchAddress(_objName + ".size", &size);
  _tree.SetBranchAddress(_objName + ".pt", pt);
  _tree.SetBranchAddress(_objName + ".eta", eta);
  _tree.SetBranchAddress(_objName + ".phi", phi);
}

void
simpletree::ParticleCollection::book(TTree& _tree, TString const& _objName)
{
  _tree.Branch(_objName + ".size", &size, "size/i");
  _tree.Branch(_objName + ".pt", pt, "pt[" + _objName + ".size]/F");
  _tree.Branch(_objName + ".eta", eta, "eta[" + _objName + ".size]/F");
  _tree.Branch(_objName + ".phi", phi, "phi[" + _objName + ".size]/F");
}

simpletree::ParticleMCollection::ParticleMCollection() :
  ParticleCollection(kFALSE)
{
  objSize_ = sizeof(ParticleM);
  array_ = std::allocator<ParticleM>().allocate(NMAX);
  for (unsigned iP(0); iP != NMAX; ++iP)
    new (static_cast<ParticleM*>(array_) + iP) ParticleM(*this, iP);
}

//protected
simpletree::ParticleMCollection::ParticleMCollection(Bool_t) :
  ParticleCollection(kFALSE)
{
}

simpletree::ParticleMCollection::~ParticleMCollection()
{
  if (array_) {
    std::allocator<ParticleM>().deallocate(static_cast<ParticleM*>(array_), NMAX);
    array_ = 0;
  }
}

simpletree::ParticleMCollection::reference
simpletree::ParticleMCollection::at(UInt_t _idx)
{
  if (_idx < size) {
    auto* p(array_);
    flatutils::shiftAddr(p, _idx * objSize_);
    return *static_cast<ParticleM*>(p);
  }

  throw std::out_of_range("ParticleMCollection::at");
}

simpletree::ParticleMCollection::const_reference
simpletree::ParticleMCollection::at(UInt_t _idx) const
{
  if (_idx < size) {
    auto* p(array_);
    flatutils::shiftAddr(p, _idx * objSize_);
    return *static_cast<ParticleM const*>(p);
  }

  throw std::out_of_range("ParticleMCollection::at");
}

simpletree::ParticleMCollection::reference
simpletree::ParticleMCollection::operator[](UInt_t _idx)
{
  auto* p(array_);
  flatutils::shiftAddr(p, _idx * objSize_);
  return *static_cast<ParticleM*>(p);
}

simpletree::ParticleMCollection::const_reference
simpletree::ParticleMCollection::operator[](UInt_t _idx) const
{
  auto* p(array_);
  flatutils::shiftAddr(p, _idx * objSize_);
  return *static_cast<ParticleM const*>(p);
}

void
simpletree::ParticleMCollection::push_back(const_reference val)
{
  UInt_t current(size);
  resize(current + 1);
  array_[current] = val;
}

void
simpletree::ParticleMCollection::setAddress(TTree& _tree, TString const& _objName)
{
  ParticleCollection::setAddress(_tree, _objName);

  _tree.SetBranchAddress(_objName + ".mass", mass);
}

void
simpletree::ParticleMCollection::book(TTree& _tree, TString const& _objName)
{
  ParticleCollection::book(_tree, _objName);

  _tree.Branch(_objName + ".mass", mass, "mass[" + _objName + ".size]/F");
}

simpletree::JetCollection::JetCollection() :
  ParticleMCollection(kFALSE)
{
  objSize_ = sizeof(Jet);
  array_ = std::allocator<Jet>().allocate(NMAX);
  for (unsigned iP(0); iP != NMAX; ++iP)
    new (static_cast<Jet*>(array_) + iP) Jet(*this, iP);
}

//protected
simpletree::JetCollection::JetCollection(Bool_t) :
  ParticleMCollection(kFALSE)
{
}

simpletree::JetCollection::~JetCollection()
{
  if (array_) {
    std::allocator<Jet>().deallocate(static_cast<Jet*>(array_), NMAX);
    array_ = 0;
  }
}

simpletree::JetCollection::reference
simpletree::JetCollection::at(UInt_t _idx)
{
  if (_idx < size) {
    auto* p(array_);
    flatutils::shiftAddr(p, _idx * objSize_);
    return *static_cast<Jet*>(p);
  }

  throw std::out_of_range("JetCollection::at");
}

simpletree::JetCollection::const_reference
simpletree::JetCollection::at(UInt_t _idx) const
{
  if (_idx < size) {
    auto* p(array_);
    flatutils::shiftAddr(p, _idx * objSize_);
    return *static_cast<Jet const*>(p);
  }

  throw std::out_of_range("JetCollection::at");
}

simpletree::JetCollection::reference
simpletree::JetCollection::operator[](UInt_t _idx)
{
  auto* p(array_);
  flatutils::shiftAddr(p, _idx * objSize_);
  return *static_cast<Jet*>(p);
}

simpletree::JetCollection::const_reference
simpletree::JetCollection::operator[](UInt_t _idx) const
{
  auto* p(array_);
  flatutils::shiftAddr(p, _idx * objSize_);
  return *static_cast<Jet const*>(p);
}

void
simpletree::JetCollection::push_back(const_reference val)
{
  UInt_t current(size);
  resize(current + 1);
  array_[current] = val;
}

void
simpletree::JetCollection::setAddress(TTree& _tree, TString const& _objName)
{
  ParticleMCollection::setAddress(_tree, _objName);

}

void
simpletree::JetCollection::book(TTree& _tree, TString const& _objName)
{
  ParticleMCollection::book(_tree, _objName);

}

simpletree::PhotonCollection::PhotonCollection() :
  ParticleCollection(kFALSE)
{
  objSize_ = sizeof(Photon);
  array_ = std::allocator<Photon>().allocate(NMAX);
  for (unsigned iP(0); iP != NMAX; ++iP)
    new (static_cast<Photon*>(array_) + iP) Photon(*this, iP);
}

//protected
simpletree::PhotonCollection::PhotonCollection(Bool_t) :
  ParticleCollection(kFALSE)
{
}

simpletree::PhotonCollection::~PhotonCollection()
{
  if (array_) {
    std::allocator<Photon>().deallocate(static_cast<Photon*>(array_), NMAX);
    array_ = 0;
  }
}

simpletree::PhotonCollection::reference
simpletree::PhotonCollection::at(UInt_t _idx)
{
  if (_idx < size) {
    auto* p(array_);
    flatutils::shiftAddr(p, _idx * objSize_);
    return *static_cast<Photon*>(p);
  }

  throw std::out_of_range("PhotonCollection::at");
}

simpletree::PhotonCollection::const_reference
simpletree::PhotonCollection::at(UInt_t _idx) const
{
  if (_idx < size) {
    auto* p(array_);
    flatutils::shiftAddr(p, _idx * objSize_);
    return *static_cast<Photon const*>(p);
  }

  throw std::out_of_range("PhotonCollection::at");
}

simpletree::PhotonCollection::reference
simpletree::PhotonCollection::operator[](UInt_t _idx)
{
  auto* p(array_);
  flatutils::shiftAddr(p, _idx * objSize_);
  return *static_cast<Photon*>(p);
}

simpletree::PhotonCollection::const_reference
simpletree::PhotonCollection::operator[](UInt_t _idx) const
{
  auto* p(array_);
  flatutils::shiftAddr(p, _idx * objSize_);
  return *static_cast<Photon const*>(p);
}

void
simpletree::PhotonCollection::push_back(const_reference val)
{
  UInt_t current(size);
  resize(current + 1);
  array_[current] = val;
}

void
simpletree::PhotonCollection::setAddress(TTree& _tree, TString const& _objName)
{
  ParticleCollection::setAddress(_tree, _objName);

  _tree.SetBranchAddress(_objName + ".chIso", chIso);
  _tree.SetBranchAddress(_objName + ".nhIso", nhIso);
  _tree.SetBranchAddress(_objName + ".phIso", phIso);
  _tree.SetBranchAddress(_objName + ".sieie", sieie);
  _tree.SetBranchAddress(_objName + ".hOverE", hOverE);
  _tree.SetBranchAddress(_objName + ".pixelVeto", pixelVeto);
  _tree.SetBranchAddress(_objName + ".csafeVeto", csafeVeto);
  _tree.SetBranchAddress(_objName + ".isLoose", isLoose);
  _tree.SetBranchAddress(_objName + ".isMedium", isMedium);
  _tree.SetBranchAddress(_objName + ".isTight", isTight);
}

void
simpletree::PhotonCollection::book(TTree& _tree, TString const& _objName)
{
  ParticleCollection::book(_tree, _objName);

  _tree.Branch(_objName + ".chIso", chIso, "chIso[" + _objName + ".size]/F");
  _tree.Branch(_objName + ".nhIso", nhIso, "nhIso[" + _objName + ".size]/F");
  _tree.Branch(_objName + ".phIso", phIso, "phIso[" + _objName + ".size]/F");
  _tree.Branch(_objName + ".sieie", sieie, "sieie[" + _objName + ".size]/F");
  _tree.Branch(_objName + ".hOverE", hOverE, "hOverE[" + _objName + ".size]/F");
  _tree.Branch(_objName + ".pixelVeto", pixelVeto, "pixelVeto[" + _objName + ".size]/O");
  _tree.Branch(_objName + ".csafeVeto", csafeVeto, "csafeVeto[" + _objName + ".size]/O");
  _tree.Branch(_objName + ".isLoose", isLoose, "isLoose[" + _objName + ".size]/O");
  _tree.Branch(_objName + ".isMedium", isMedium, "isMedium[" + _objName + ".size]/O");
  _tree.Branch(_objName + ".isTight", isTight, "isTight[" + _objName + ".size]/O");
}

simpletree::ElectronCollection::ElectronCollection() :
  ParticleMCollection(kFALSE)
{
  objSize_ = sizeof(Electron);
  array_ = std::allocator<Electron>().allocate(NMAX);
  for (unsigned iP(0); iP != NMAX; ++iP)
    new (static_cast<Electron*>(array_) + iP) Electron(*this, iP);
}

//protected
simpletree::ElectronCollection::ElectronCollection(Bool_t) :
  ParticleMCollection(kFALSE)
{
}

simpletree::ElectronCollection::~ElectronCollection()
{
  if (array_) {
    std::allocator<Electron>().deallocate(static_cast<Electron*>(array_), NMAX);
    array_ = 0;
  }
}

simpletree::ElectronCollection::reference
simpletree::ElectronCollection::at(UInt_t _idx)
{
  if (_idx < size) {
    auto* p(array_);
    flatutils::shiftAddr(p, _idx * objSize_);
    return *static_cast<Electron*>(p);
  }

  throw std::out_of_range("ElectronCollection::at");
}

simpletree::ElectronCollection::const_reference
simpletree::ElectronCollection::at(UInt_t _idx) const
{
  if (_idx < size) {
    auto* p(array_);
    flatutils::shiftAddr(p, _idx * objSize_);
    return *static_cast<Electron const*>(p);
  }

  throw std::out_of_range("ElectronCollection::at");
}

simpletree::ElectronCollection::reference
simpletree::ElectronCollection::operator[](UInt_t _idx)
{
  auto* p(array_);
  flatutils::shiftAddr(p, _idx * objSize_);
  return *static_cast<Electron*>(p);
}

simpletree::ElectronCollection::const_reference
simpletree::ElectronCollection::operator[](UInt_t _idx) const
{
  auto* p(array_);
  flatutils::shiftAddr(p, _idx * objSize_);
  return *static_cast<Electron const*>(p);
}

void
simpletree::ElectronCollection::push_back(const_reference val)
{
  UInt_t current(size);
  resize(current + 1);
  array_[current] = val;
}

void
simpletree::ElectronCollection::setAddress(TTree& _tree, TString const& _objName)
{
  ParticleMCollection::setAddress(_tree, _objName);

  _tree.SetBranchAddress(_objName + ".positive", positive);
  _tree.SetBranchAddress(_objName + ".tight", tight);
}

void
simpletree::ElectronCollection::book(TTree& _tree, TString const& _objName)
{
  ParticleMCollection::book(_tree, _objName);

  _tree.Branch(_objName + ".positive", positive, "positive[" + _objName + ".size]/O");
  _tree.Branch(_objName + ".tight", tight, "tight[" + _objName + ".size]/O");
}

simpletree::MuonCollection::MuonCollection() :
  ParticleMCollection(kFALSE)
{
  objSize_ = sizeof(Muon);
  array_ = std::allocator<Muon>().allocate(NMAX);
  for (unsigned iP(0); iP != NMAX; ++iP)
    new (static_cast<Muon*>(array_) + iP) Muon(*this, iP);
}

//protected
simpletree::MuonCollection::MuonCollection(Bool_t) :
  ParticleMCollection(kFALSE)
{
}

simpletree::MuonCollection::~MuonCollection()
{
  if (array_) {
    std::allocator<Muon>().deallocate(static_cast<Muon*>(array_), NMAX);
    array_ = 0;
  }
}

simpletree::MuonCollection::reference
simpletree::MuonCollection::at(UInt_t _idx)
{
  if (_idx < size) {
    auto* p(array_);
    flatutils::shiftAddr(p, _idx * objSize_);
    return *static_cast<Muon*>(p);
  }

  throw std::out_of_range("MuonCollection::at");
}

simpletree::MuonCollection::const_reference
simpletree::MuonCollection::at(UInt_t _idx) const
{
  if (_idx < size) {
    auto* p(array_);
    flatutils::shiftAddr(p, _idx * objSize_);
    return *static_cast<Muon const*>(p);
  }

  throw std::out_of_range("MuonCollection::at");
}

simpletree::MuonCollection::reference
simpletree::MuonCollection::operator[](UInt_t _idx)
{
  auto* p(array_);
  flatutils::shiftAddr(p, _idx * objSize_);
  return *static_cast<Muon*>(p);
}

simpletree::MuonCollection::const_reference
simpletree::MuonCollection::operator[](UInt_t _idx) const
{
  auto* p(array_);
  flatutils::shiftAddr(p, _idx * objSize_);
  return *static_cast<Muon const*>(p);
}

void
simpletree::MuonCollection::push_back(const_reference val)
{
  UInt_t current(size);
  resize(current + 1);
  array_[current] = val;
}

void
simpletree::MuonCollection::setAddress(TTree& _tree, TString const& _objName)
{
  ParticleMCollection::setAddress(_tree, _objName);

  _tree.SetBranchAddress(_objName + ".positive", positive);
  _tree.SetBranchAddress(_objName + ".tight", tight);
}

void
simpletree::MuonCollection::book(TTree& _tree, TString const& _objName)
{
  ParticleMCollection::book(_tree, _objName);

  _tree.Branch(_objName + ".positive", positive, "positive[" + _objName + ".size]/O");
  _tree.Branch(_objName + ".tight", tight, "tight[" + _objName + ".size]/O");
}

