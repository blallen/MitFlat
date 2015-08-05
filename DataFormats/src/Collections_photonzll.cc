#include "MitFlat/DataFormats/interface/Collections_photonzll.h"
#include "TTree.h"
#include <stdexcept>
#include <memory>

photonzll::ParticleCollection::ParticleCollection()
{
  objSize_ = sizeof(Particle);
  array_ = std::allocator<Particle>().allocate(NMAX);
  for (unsigned iP(0); iP != NMAX; ++iP)
    new (static_cast<Particle*>(array_) + iP) Particle(*this, iP);
}

//protected
photonzll::ParticleCollection::ParticleCollection(Bool_t)
{
}

photonzll::ParticleCollection::~ParticleCollection()
{
  if (array_) {
    std::allocator<Particle>().deallocate(static_cast<Particle*>(array_), NMAX);
    array_ = 0;
  }
}

photonzll::ParticleCollection::reference
photonzll::ParticleCollection::at(UInt_t _idx)
{
  if (_idx < size) {
    auto* p(array_);
    flatutils::shiftAddr(p, _idx * objSize_);
    return *static_cast<Particle*>(p);
  }

  throw std::out_of_range("ParticleCollection::at");
}

photonzll::ParticleCollection::const_reference
photonzll::ParticleCollection::at(UInt_t _idx) const
{
  if (_idx < size) {
    auto* p(array_);
    flatutils::shiftAddr(p, _idx * objSize_);
    return *static_cast<Particle const*>(p);
  }

  throw std::out_of_range("ParticleCollection::at");
}

photonzll::ParticleCollection::reference
photonzll::ParticleCollection::operator[](UInt_t _idx)
{
  auto* p(array_);
  flatutils::shiftAddr(p, _idx * objSize_);
  return *static_cast<Particle*>(p);
}

photonzll::ParticleCollection::const_reference
photonzll::ParticleCollection::operator[](UInt_t _idx) const
{
  auto* p(array_);
  flatutils::shiftAddr(p, _idx * objSize_);
  return *static_cast<Particle const*>(p);
}

void
photonzll::ParticleCollection::resize(UInt_t _size)
{
  if (_size <= NMAX) {
    size = _size;
    return;
  }
  throw std::length_error("ParticleCollection::resize");
}

void
photonzll::ParticleCollection::setAddress(TTree& _tree, TString const& _objName)
{
  _tree.SetBranchAddress(_objName + ".size", &size);
  _tree.SetBranchAddress(_objName + ".pt", pt);
  _tree.SetBranchAddress(_objName + ".eta", eta);
  _tree.SetBranchAddress(_objName + ".phi", phi);
}

void
photonzll::ParticleCollection::book(TTree& _tree, TString const& _objName)
{
  _tree.Branch(_objName + ".size", &size, "size/i");
  _tree.Branch(_objName + ".pt", pt, "pt[" + _objName + ".size]/F");
  _tree.Branch(_objName + ".eta", eta, "eta[" + _objName + ".size]/F");
  _tree.Branch(_objName + ".phi", phi, "phi[" + _objName + ".size]/F");
}

photonzll::JetCollection::JetCollection() :
  ParticleCollection(kFALSE)
{
  objSize_ = sizeof(Jet);
  array_ = std::allocator<Jet>().allocate(NMAX);
  for (unsigned iP(0); iP != NMAX; ++iP)
    new (static_cast<Jet*>(array_) + iP) Jet(*this, iP);
}

//protected
photonzll::JetCollection::JetCollection(Bool_t) :
  ParticleCollection(kFALSE)
{
}

photonzll::JetCollection::~JetCollection()
{
  if (array_) {
    std::allocator<Jet>().deallocate(static_cast<Jet*>(array_), NMAX);
    array_ = 0;
  }
}

photonzll::JetCollection::reference
photonzll::JetCollection::at(UInt_t _idx)
{
  if (_idx < size) {
    auto* p(array_);
    flatutils::shiftAddr(p, _idx * objSize_);
    return *static_cast<Jet*>(p);
  }

  throw std::out_of_range("JetCollection::at");
}

photonzll::JetCollection::const_reference
photonzll::JetCollection::at(UInt_t _idx) const
{
  if (_idx < size) {
    auto* p(array_);
    flatutils::shiftAddr(p, _idx * objSize_);
    return *static_cast<Jet const*>(p);
  }

  throw std::out_of_range("JetCollection::at");
}

photonzll::JetCollection::reference
photonzll::JetCollection::operator[](UInt_t _idx)
{
  auto* p(array_);
  flatutils::shiftAddr(p, _idx * objSize_);
  return *static_cast<Jet*>(p);
}

photonzll::JetCollection::const_reference
photonzll::JetCollection::operator[](UInt_t _idx) const
{
  auto* p(array_);
  flatutils::shiftAddr(p, _idx * objSize_);
  return *static_cast<Jet const*>(p);
}

void
photonzll::JetCollection::setAddress(TTree& _tree, TString const& _objName)
{
  ParticleCollection::setAddress(_tree, _objName);

}

void
photonzll::JetCollection::book(TTree& _tree, TString const& _objName)
{
  ParticleCollection::book(_tree, _objName);

}

photonzll::PhotonCollection::PhotonCollection() :
  ParticleCollection(kFALSE)
{
  objSize_ = sizeof(Photon);
  array_ = std::allocator<Photon>().allocate(NMAX);
  for (unsigned iP(0); iP != NMAX; ++iP)
    new (static_cast<Photon*>(array_) + iP) Photon(*this, iP);
}

//protected
photonzll::PhotonCollection::PhotonCollection(Bool_t) :
  ParticleCollection(kFALSE)
{
}

photonzll::PhotonCollection::~PhotonCollection()
{
  if (array_) {
    std::allocator<Photon>().deallocate(static_cast<Photon*>(array_), NMAX);
    array_ = 0;
  }
}

photonzll::PhotonCollection::reference
photonzll::PhotonCollection::at(UInt_t _idx)
{
  if (_idx < size) {
    auto* p(array_);
    flatutils::shiftAddr(p, _idx * objSize_);
    return *static_cast<Photon*>(p);
  }

  throw std::out_of_range("PhotonCollection::at");
}

photonzll::PhotonCollection::const_reference
photonzll::PhotonCollection::at(UInt_t _idx) const
{
  if (_idx < size) {
    auto* p(array_);
    flatutils::shiftAddr(p, _idx * objSize_);
    return *static_cast<Photon const*>(p);
  }

  throw std::out_of_range("PhotonCollection::at");
}

photonzll::PhotonCollection::reference
photonzll::PhotonCollection::operator[](UInt_t _idx)
{
  auto* p(array_);
  flatutils::shiftAddr(p, _idx * objSize_);
  return *static_cast<Photon*>(p);
}

photonzll::PhotonCollection::const_reference
photonzll::PhotonCollection::operator[](UInt_t _idx) const
{
  auto* p(array_);
  flatutils::shiftAddr(p, _idx * objSize_);
  return *static_cast<Photon const*>(p);
}

void
photonzll::PhotonCollection::setAddress(TTree& _tree, TString const& _objName)
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
photonzll::PhotonCollection::book(TTree& _tree, TString const& _objName)
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

