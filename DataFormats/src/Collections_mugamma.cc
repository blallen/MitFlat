#include "MitFlat/DataFormats/interface/Collections_mugamma.h"
#include "TTree.h"
#include <stdexcept>
#include <memory>

mugamma::ParticleCollection::ParticleCollection()
{
  objSize_ = sizeof(Particle);
  array_ = std::allocator<Particle>().allocate(NMAX);
  for (unsigned iP(0); iP != NMAX; ++iP)
    new (static_cast<Particle*>(array_) + iP) Particle(*this, iP);
}

//protected
mugamma::ParticleCollection::ParticleCollection(Bool_t)
{
}

mugamma::ParticleCollection::~ParticleCollection()
{
  if (array_) {
    std::allocator<Particle>().deallocate(static_cast<Particle*>(array_), NMAX);
    array_ = 0;
  }
}

mugamma::ParticleCollection::reference
mugamma::ParticleCollection::at(UInt_t _idx)
{
  if (_idx < size) {
    auto* p(array_);
    flatutils::shiftAddr(p, _idx * objSize_);
    return *static_cast<Particle*>(p);
  }

  throw std::out_of_range("ParticleCollection::at");
}

mugamma::ParticleCollection::const_reference
mugamma::ParticleCollection::at(UInt_t _idx) const
{
  if (_idx < size) {
    auto* p(array_);
    flatutils::shiftAddr(p, _idx * objSize_);
    return *static_cast<Particle const*>(p);
  }

  throw std::out_of_range("ParticleCollection::at");
}

mugamma::ParticleCollection::reference
mugamma::ParticleCollection::operator[](UInt_t _idx)
{
  auto* p(array_);
  flatutils::shiftAddr(p, _idx * objSize_);
  return *static_cast<Particle*>(p);
}

mugamma::ParticleCollection::const_reference
mugamma::ParticleCollection::operator[](UInt_t _idx) const
{
  auto* p(array_);
  flatutils::shiftAddr(p, _idx * objSize_);
  return *static_cast<Particle const*>(p);
}

void
mugamma::ParticleCollection::resize(UInt_t _size)
{
  if (_size <= NMAX) {
    size = _size;
    return;
  }
  throw std::length_error("ParticleCollection::resize");
}

void
mugamma::ParticleCollection::setAddress(TTree& _tree, TString const& _objName)
{
  _tree.SetBranchAddress(_objName + ".size", &size);
  _tree.SetBranchAddress(_objName + ".pt", pt);
  _tree.SetBranchAddress(_objName + ".eta", eta);
  _tree.SetBranchAddress(_objName + ".phi", phi);
}

void
mugamma::ParticleCollection::book(TTree& _tree, TString const& _objName)
{
  _tree.Branch(_objName + ".size", &size, "size/i");
  _tree.Branch(_objName + ".pt", pt, "pt[" + _objName + ".size]/F");
  _tree.Branch(_objName + ".eta", eta, "eta[" + _objName + ".size]/F");
  _tree.Branch(_objName + ".phi", phi, "phi[" + _objName + ".size]/F");
}

mugamma::ParticleMCollection::ParticleMCollection() :
  ParticleCollection(kFALSE)
{
  objSize_ = sizeof(ParticleM);
  array_ = std::allocator<ParticleM>().allocate(NMAX);
  for (unsigned iP(0); iP != NMAX; ++iP)
    new (static_cast<ParticleM*>(array_) + iP) ParticleM(*this, iP);
}

//protected
mugamma::ParticleMCollection::ParticleMCollection(Bool_t) :
  ParticleCollection(kFALSE)
{
}

mugamma::ParticleMCollection::~ParticleMCollection()
{
  if (array_) {
    std::allocator<ParticleM>().deallocate(static_cast<ParticleM*>(array_), NMAX);
    array_ = 0;
  }
}

mugamma::ParticleMCollection::reference
mugamma::ParticleMCollection::at(UInt_t _idx)
{
  if (_idx < size) {
    auto* p(array_);
    flatutils::shiftAddr(p, _idx * objSize_);
    return *static_cast<ParticleM*>(p);
  }

  throw std::out_of_range("ParticleMCollection::at");
}

mugamma::ParticleMCollection::const_reference
mugamma::ParticleMCollection::at(UInt_t _idx) const
{
  if (_idx < size) {
    auto* p(array_);
    flatutils::shiftAddr(p, _idx * objSize_);
    return *static_cast<ParticleM const*>(p);
  }

  throw std::out_of_range("ParticleMCollection::at");
}

mugamma::ParticleMCollection::reference
mugamma::ParticleMCollection::operator[](UInt_t _idx)
{
  auto* p(array_);
  flatutils::shiftAddr(p, _idx * objSize_);
  return *static_cast<ParticleM*>(p);
}

mugamma::ParticleMCollection::const_reference
mugamma::ParticleMCollection::operator[](UInt_t _idx) const
{
  auto* p(array_);
  flatutils::shiftAddr(p, _idx * objSize_);
  return *static_cast<ParticleM const*>(p);
}

void
mugamma::ParticleMCollection::setAddress(TTree& _tree, TString const& _objName)
{
  ParticleCollection::setAddress(_tree, _objName);

  _tree.SetBranchAddress(_objName + ".mass", mass);
}

void
mugamma::ParticleMCollection::book(TTree& _tree, TString const& _objName)
{
  ParticleCollection::book(_tree, _objName);

  _tree.Branch(_objName + ".mass", mass, "mass[" + _objName + ".size]/F");
}

mugamma::JetCollection::JetCollection() :
  ParticleMCollection(kFALSE)
{
  objSize_ = sizeof(Jet);
  array_ = std::allocator<Jet>().allocate(NMAX);
  for (unsigned iP(0); iP != NMAX; ++iP)
    new (static_cast<Jet*>(array_) + iP) Jet(*this, iP);
}

//protected
mugamma::JetCollection::JetCollection(Bool_t) :
  ParticleMCollection(kFALSE)
{
}

mugamma::JetCollection::~JetCollection()
{
  if (array_) {
    std::allocator<Jet>().deallocate(static_cast<Jet*>(array_), NMAX);
    array_ = 0;
  }
}

mugamma::JetCollection::reference
mugamma::JetCollection::at(UInt_t _idx)
{
  if (_idx < size) {
    auto* p(array_);
    flatutils::shiftAddr(p, _idx * objSize_);
    return *static_cast<Jet*>(p);
  }

  throw std::out_of_range("JetCollection::at");
}

mugamma::JetCollection::const_reference
mugamma::JetCollection::at(UInt_t _idx) const
{
  if (_idx < size) {
    auto* p(array_);
    flatutils::shiftAddr(p, _idx * objSize_);
    return *static_cast<Jet const*>(p);
  }

  throw std::out_of_range("JetCollection::at");
}

mugamma::JetCollection::reference
mugamma::JetCollection::operator[](UInt_t _idx)
{
  auto* p(array_);
  flatutils::shiftAddr(p, _idx * objSize_);
  return *static_cast<Jet*>(p);
}

mugamma::JetCollection::const_reference
mugamma::JetCollection::operator[](UInt_t _idx) const
{
  auto* p(array_);
  flatutils::shiftAddr(p, _idx * objSize_);
  return *static_cast<Jet const*>(p);
}

void
mugamma::JetCollection::setAddress(TTree& _tree, TString const& _objName)
{
  ParticleMCollection::setAddress(_tree, _objName);

}

void
mugamma::JetCollection::book(TTree& _tree, TString const& _objName)
{
  ParticleMCollection::book(_tree, _objName);

}

mugamma::PhotonCollection::PhotonCollection() :
  ParticleCollection(kFALSE)
{
  objSize_ = sizeof(Photon);
  array_ = std::allocator<Photon>().allocate(NMAX);
  for (unsigned iP(0); iP != NMAX; ++iP)
    new (static_cast<Photon*>(array_) + iP) Photon(*this, iP);
}

//protected
mugamma::PhotonCollection::PhotonCollection(Bool_t) :
  ParticleCollection(kFALSE)
{
}

mugamma::PhotonCollection::~PhotonCollection()
{
  if (array_) {
    std::allocator<Photon>().deallocate(static_cast<Photon*>(array_), NMAX);
    array_ = 0;
  }
}

mugamma::PhotonCollection::reference
mugamma::PhotonCollection::at(UInt_t _idx)
{
  if (_idx < size) {
    auto* p(array_);
    flatutils::shiftAddr(p, _idx * objSize_);
    return *static_cast<Photon*>(p);
  }

  throw std::out_of_range("PhotonCollection::at");
}

mugamma::PhotonCollection::const_reference
mugamma::PhotonCollection::at(UInt_t _idx) const
{
  if (_idx < size) {
    auto* p(array_);
    flatutils::shiftAddr(p, _idx * objSize_);
    return *static_cast<Photon const*>(p);
  }

  throw std::out_of_range("PhotonCollection::at");
}

mugamma::PhotonCollection::reference
mugamma::PhotonCollection::operator[](UInt_t _idx)
{
  auto* p(array_);
  flatutils::shiftAddr(p, _idx * objSize_);
  return *static_cast<Photon*>(p);
}

mugamma::PhotonCollection::const_reference
mugamma::PhotonCollection::operator[](UInt_t _idx) const
{
  auto* p(array_);
  flatutils::shiftAddr(p, _idx * objSize_);
  return *static_cast<Photon const*>(p);
}

void
mugamma::PhotonCollection::setAddress(TTree& _tree, TString const& _objName)
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
mugamma::PhotonCollection::book(TTree& _tree, TString const& _objName)
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

mugamma::ElectronCollection::ElectronCollection() :
  ParticleMCollection(kFALSE)
{
  objSize_ = sizeof(Electron);
  array_ = std::allocator<Electron>().allocate(NMAX);
  for (unsigned iP(0); iP != NMAX; ++iP)
    new (static_cast<Electron*>(array_) + iP) Electron(*this, iP);
}

//protected
mugamma::ElectronCollection::ElectronCollection(Bool_t) :
  ParticleMCollection(kFALSE)
{
}

mugamma::ElectronCollection::~ElectronCollection()
{
  if (array_) {
    std::allocator<Electron>().deallocate(static_cast<Electron*>(array_), NMAX);
    array_ = 0;
  }
}

mugamma::ElectronCollection::reference
mugamma::ElectronCollection::at(UInt_t _idx)
{
  if (_idx < size) {
    auto* p(array_);
    flatutils::shiftAddr(p, _idx * objSize_);
    return *static_cast<Electron*>(p);
  }

  throw std::out_of_range("ElectronCollection::at");
}

mugamma::ElectronCollection::const_reference
mugamma::ElectronCollection::at(UInt_t _idx) const
{
  if (_idx < size) {
    auto* p(array_);
    flatutils::shiftAddr(p, _idx * objSize_);
    return *static_cast<Electron const*>(p);
  }

  throw std::out_of_range("ElectronCollection::at");
}

mugamma::ElectronCollection::reference
mugamma::ElectronCollection::operator[](UInt_t _idx)
{
  auto* p(array_);
  flatutils::shiftAddr(p, _idx * objSize_);
  return *static_cast<Electron*>(p);
}

mugamma::ElectronCollection::const_reference
mugamma::ElectronCollection::operator[](UInt_t _idx) const
{
  auto* p(array_);
  flatutils::shiftAddr(p, _idx * objSize_);
  return *static_cast<Electron const*>(p);
}

void
mugamma::ElectronCollection::setAddress(TTree& _tree, TString const& _objName)
{
  ParticleMCollection::setAddress(_tree, _objName);

  _tree.SetBranchAddress(_objName + ".tight", tight);
}

void
mugamma::ElectronCollection::book(TTree& _tree, TString const& _objName)
{
  ParticleMCollection::book(_tree, _objName);

  _tree.Branch(_objName + ".tight", tight, "tight[" + _objName + ".size]/O");
}

mugamma::MuonCollection::MuonCollection() :
  ParticleMCollection(kFALSE)
{
  objSize_ = sizeof(Muon);
  array_ = std::allocator<Muon>().allocate(NMAX);
  for (unsigned iP(0); iP != NMAX; ++iP)
    new (static_cast<Muon*>(array_) + iP) Muon(*this, iP);
}

//protected
mugamma::MuonCollection::MuonCollection(Bool_t) :
  ParticleMCollection(kFALSE)
{
}

mugamma::MuonCollection::~MuonCollection()
{
  if (array_) {
    std::allocator<Muon>().deallocate(static_cast<Muon*>(array_), NMAX);
    array_ = 0;
  }
}

mugamma::MuonCollection::reference
mugamma::MuonCollection::at(UInt_t _idx)
{
  if (_idx < size) {
    auto* p(array_);
    flatutils::shiftAddr(p, _idx * objSize_);
    return *static_cast<Muon*>(p);
  }

  throw std::out_of_range("MuonCollection::at");
}

mugamma::MuonCollection::const_reference
mugamma::MuonCollection::at(UInt_t _idx) const
{
  if (_idx < size) {
    auto* p(array_);
    flatutils::shiftAddr(p, _idx * objSize_);
    return *static_cast<Muon const*>(p);
  }

  throw std::out_of_range("MuonCollection::at");
}

mugamma::MuonCollection::reference
mugamma::MuonCollection::operator[](UInt_t _idx)
{
  auto* p(array_);
  flatutils::shiftAddr(p, _idx * objSize_);
  return *static_cast<Muon*>(p);
}

mugamma::MuonCollection::const_reference
mugamma::MuonCollection::operator[](UInt_t _idx) const
{
  auto* p(array_);
  flatutils::shiftAddr(p, _idx * objSize_);
  return *static_cast<Muon const*>(p);
}

void
mugamma::MuonCollection::setAddress(TTree& _tree, TString const& _objName)
{
  ParticleMCollection::setAddress(_tree, _objName);

  _tree.SetBranchAddress(_objName + ".tight", tight);
}

void
mugamma::MuonCollection::book(TTree& _tree, TString const& _objName)
{
  ParticleMCollection::book(_tree, _objName);

  _tree.Branch(_objName + ".tight", tight, "tight[" + _objName + ".size]/O");
}

