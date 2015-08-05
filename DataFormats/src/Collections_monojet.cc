#include "MitFlat/DataFormats/interface/Collections_monojet.h"
#include "TTree.h"
#include <stdexcept>
#include <memory>

monojet::ParticleCollection::ParticleCollection()
{
  objSize_ = sizeof(Particle);
  array_ = std::allocator<Particle>().allocate(NMAX);
  for (unsigned iP(0); iP != NMAX; ++iP)
    new (static_cast<Particle*>(array_) + iP) Particle(*this, iP);
}

//protected
monojet::ParticleCollection::ParticleCollection(Bool_t)
{
}

monojet::ParticleCollection::~ParticleCollection()
{
  if (array_) {
    std::allocator<Particle>().deallocate(static_cast<Particle*>(array_), NMAX);
    array_ = 0;
  }
}

monojet::ParticleCollection::reference
monojet::ParticleCollection::at(UInt_t _idx)
{
  if (_idx < size) {
    auto* p(array_);
    flatutils::shiftAddr(p, _idx * objSize_);
    return *static_cast<Particle*>(p);
  }

  throw std::out_of_range("ParticleCollection::at");
}

monojet::ParticleCollection::const_reference
monojet::ParticleCollection::at(UInt_t _idx) const
{
  if (_idx < size) {
    auto* p(array_);
    flatutils::shiftAddr(p, _idx * objSize_);
    return *static_cast<Particle const*>(p);
  }

  throw std::out_of_range("ParticleCollection::at");
}

monojet::ParticleCollection::reference
monojet::ParticleCollection::operator[](UInt_t _idx)
{
  auto* p(array_);
  flatutils::shiftAddr(p, _idx * objSize_);
  return *static_cast<Particle*>(p);
}

monojet::ParticleCollection::const_reference
monojet::ParticleCollection::operator[](UInt_t _idx) const
{
  auto* p(array_);
  flatutils::shiftAddr(p, _idx * objSize_);
  return *static_cast<Particle const*>(p);
}

void
monojet::ParticleCollection::resize(UInt_t _size)
{
  if (_size <= NMAX) {
    size = _size;
    return;
  }
  throw std::length_error("ParticleCollection::resize");
}

void
monojet::ParticleCollection::setAddress(TTree& _tree, TString const& _objName)
{
  _tree.SetBranchAddress(_objName + ".size", &size);
  _tree.SetBranchAddress(_objName + ".pt", pt);
  _tree.SetBranchAddress(_objName + ".eta", eta);
  _tree.SetBranchAddress(_objName + ".phi", phi);
}

void
monojet::ParticleCollection::book(TTree& _tree, TString const& _objName)
{
  _tree.Branch(_objName + ".size", &size, "size/i");
  _tree.Branch(_objName + ".pt", pt, "pt[" + _objName + ".size]/F");
  _tree.Branch(_objName + ".eta", eta, "eta[" + _objName + ".size]/F");
  _tree.Branch(_objName + ".phi", phi, "phi[" + _objName + ".size]/F");
}

monojet::JetCollection::JetCollection() :
  ParticleCollection(kFALSE)
{
  objSize_ = sizeof(Jet);
  array_ = std::allocator<Jet>().allocate(NMAX);
  for (unsigned iP(0); iP != NMAX; ++iP)
    new (static_cast<Jet*>(array_) + iP) Jet(*this, iP);
}

//protected
monojet::JetCollection::JetCollection(Bool_t) :
  ParticleCollection(kFALSE)
{
}

monojet::JetCollection::~JetCollection()
{
  if (array_) {
    std::allocator<Jet>().deallocate(static_cast<Jet*>(array_), NMAX);
    array_ = 0;
  }
}

monojet::JetCollection::reference
monojet::JetCollection::at(UInt_t _idx)
{
  if (_idx < size) {
    auto* p(array_);
    flatutils::shiftAddr(p, _idx * objSize_);
    return *static_cast<Jet*>(p);
  }

  throw std::out_of_range("JetCollection::at");
}

monojet::JetCollection::const_reference
monojet::JetCollection::at(UInt_t _idx) const
{
  if (_idx < size) {
    auto* p(array_);
    flatutils::shiftAddr(p, _idx * objSize_);
    return *static_cast<Jet const*>(p);
  }

  throw std::out_of_range("JetCollection::at");
}

monojet::JetCollection::reference
monojet::JetCollection::operator[](UInt_t _idx)
{
  auto* p(array_);
  flatutils::shiftAddr(p, _idx * objSize_);
  return *static_cast<Jet*>(p);
}

monojet::JetCollection::const_reference
monojet::JetCollection::operator[](UInt_t _idx) const
{
  auto* p(array_);
  flatutils::shiftAddr(p, _idx * objSize_);
  return *static_cast<Jet const*>(p);
}

void
monojet::JetCollection::setAddress(TTree& _tree, TString const& _objName)
{
  ParticleCollection::setAddress(_tree, _objName);

  _tree.SetBranchAddress(_objName + ".btag", btag);
  _tree.SetBranchAddress(_objName + ".chFrac", chFrac);
  _tree.SetBranchAddress(_objName + ".nhFrac", nhFrac);
  _tree.SetBranchAddress(_objName + ".neFrac", neFrac);
}

void
monojet::JetCollection::book(TTree& _tree, TString const& _objName)
{
  ParticleCollection::book(_tree, _objName);

  _tree.Branch(_objName + ".btag", btag, "btag[" + _objName + ".size]/F");
  _tree.Branch(_objName + ".chFrac", chFrac, "chFrac[" + _objName + ".size]/F");
  _tree.Branch(_objName + ".nhFrac", nhFrac, "nhFrac[" + _objName + ".size]/F");
  _tree.Branch(_objName + ".neFrac", neFrac, "neFrac[" + _objName + ".size]/F");
}

monojet::ElectronCollection::ElectronCollection() :
  ParticleCollection(kFALSE)
{
  objSize_ = sizeof(Electron);
  array_ = std::allocator<Electron>().allocate(NMAX);
  for (unsigned iP(0); iP != NMAX; ++iP)
    new (static_cast<Electron*>(array_) + iP) Electron(*this, iP);
}

//protected
monojet::ElectronCollection::ElectronCollection(Bool_t) :
  ParticleCollection(kFALSE)
{
}

monojet::ElectronCollection::~ElectronCollection()
{
  if (array_) {
    std::allocator<Electron>().deallocate(static_cast<Electron*>(array_), NMAX);
    array_ = 0;
  }
}

monojet::ElectronCollection::reference
monojet::ElectronCollection::at(UInt_t _idx)
{
  if (_idx < size) {
    auto* p(array_);
    flatutils::shiftAddr(p, _idx * objSize_);
    return *static_cast<Electron*>(p);
  }

  throw std::out_of_range("ElectronCollection::at");
}

monojet::ElectronCollection::const_reference
monojet::ElectronCollection::at(UInt_t _idx) const
{
  if (_idx < size) {
    auto* p(array_);
    flatutils::shiftAddr(p, _idx * objSize_);
    return *static_cast<Electron const*>(p);
  }

  throw std::out_of_range("ElectronCollection::at");
}

monojet::ElectronCollection::reference
monojet::ElectronCollection::operator[](UInt_t _idx)
{
  auto* p(array_);
  flatutils::shiftAddr(p, _idx * objSize_);
  return *static_cast<Electron*>(p);
}

monojet::ElectronCollection::const_reference
monojet::ElectronCollection::operator[](UInt_t _idx) const
{
  auto* p(array_);
  flatutils::shiftAddr(p, _idx * objSize_);
  return *static_cast<Electron const*>(p);
}

void
monojet::ElectronCollection::setAddress(TTree& _tree, TString const& _objName)
{
  ParticleCollection::setAddress(_tree, _objName);

}

void
monojet::ElectronCollection::book(TTree& _tree, TString const& _objName)
{
  ParticleCollection::book(_tree, _objName);

}

monojet::MuonCollection::MuonCollection() :
  ParticleCollection(kFALSE)
{
  objSize_ = sizeof(Muon);
  array_ = std::allocator<Muon>().allocate(NMAX);
  for (unsigned iP(0); iP != NMAX; ++iP)
    new (static_cast<Muon*>(array_) + iP) Muon(*this, iP);
}

//protected
monojet::MuonCollection::MuonCollection(Bool_t) :
  ParticleCollection(kFALSE)
{
}

monojet::MuonCollection::~MuonCollection()
{
  if (array_) {
    std::allocator<Muon>().deallocate(static_cast<Muon*>(array_), NMAX);
    array_ = 0;
  }
}

monojet::MuonCollection::reference
monojet::MuonCollection::at(UInt_t _idx)
{
  if (_idx < size) {
    auto* p(array_);
    flatutils::shiftAddr(p, _idx * objSize_);
    return *static_cast<Muon*>(p);
  }

  throw std::out_of_range("MuonCollection::at");
}

monojet::MuonCollection::const_reference
monojet::MuonCollection::at(UInt_t _idx) const
{
  if (_idx < size) {
    auto* p(array_);
    flatutils::shiftAddr(p, _idx * objSize_);
    return *static_cast<Muon const*>(p);
  }

  throw std::out_of_range("MuonCollection::at");
}

monojet::MuonCollection::reference
monojet::MuonCollection::operator[](UInt_t _idx)
{
  auto* p(array_);
  flatutils::shiftAddr(p, _idx * objSize_);
  return *static_cast<Muon*>(p);
}

monojet::MuonCollection::const_reference
monojet::MuonCollection::operator[](UInt_t _idx) const
{
  auto* p(array_);
  flatutils::shiftAddr(p, _idx * objSize_);
  return *static_cast<Muon const*>(p);
}

void
monojet::MuonCollection::setAddress(TTree& _tree, TString const& _objName)
{
  ParticleCollection::setAddress(_tree, _objName);

}

void
monojet::MuonCollection::book(TTree& _tree, TString const& _objName)
{
  ParticleCollection::book(_tree, _objName);

}

monojet::TauCollection::TauCollection() :
  ParticleCollection(kFALSE)
{
  objSize_ = sizeof(Tau);
  array_ = std::allocator<Tau>().allocate(NMAX);
  for (unsigned iP(0); iP != NMAX; ++iP)
    new (static_cast<Tau*>(array_) + iP) Tau(*this, iP);
}

//protected
monojet::TauCollection::TauCollection(Bool_t) :
  ParticleCollection(kFALSE)
{
}

monojet::TauCollection::~TauCollection()
{
  if (array_) {
    std::allocator<Tau>().deallocate(static_cast<Tau*>(array_), NMAX);
    array_ = 0;
  }
}

monojet::TauCollection::reference
monojet::TauCollection::at(UInt_t _idx)
{
  if (_idx < size) {
    auto* p(array_);
    flatutils::shiftAddr(p, _idx * objSize_);
    return *static_cast<Tau*>(p);
  }

  throw std::out_of_range("TauCollection::at");
}

monojet::TauCollection::const_reference
monojet::TauCollection::at(UInt_t _idx) const
{
  if (_idx < size) {
    auto* p(array_);
    flatutils::shiftAddr(p, _idx * objSize_);
    return *static_cast<Tau const*>(p);
  }

  throw std::out_of_range("TauCollection::at");
}

monojet::TauCollection::reference
monojet::TauCollection::operator[](UInt_t _idx)
{
  auto* p(array_);
  flatutils::shiftAddr(p, _idx * objSize_);
  return *static_cast<Tau*>(p);
}

monojet::TauCollection::const_reference
monojet::TauCollection::operator[](UInt_t _idx) const
{
  auto* p(array_);
  flatutils::shiftAddr(p, _idx * objSize_);
  return *static_cast<Tau const*>(p);
}

void
monojet::TauCollection::setAddress(TTree& _tree, TString const& _objName)
{
  ParticleCollection::setAddress(_tree, _objName);

  _tree.SetBranchAddress(_objName + ".disc", disc);
}

void
monojet::TauCollection::book(TTree& _tree, TString const& _objName)
{
  ParticleCollection::book(_tree, _objName);

  _tree.Branch(_objName + ".disc", disc, "disc[" + _objName + ".size]/F");
}

monojet::PhotonCollection::PhotonCollection() :
  ParticleCollection(kFALSE)
{
  objSize_ = sizeof(Photon);
  array_ = std::allocator<Photon>().allocate(NMAX);
  for (unsigned iP(0); iP != NMAX; ++iP)
    new (static_cast<Photon*>(array_) + iP) Photon(*this, iP);
}

//protected
monojet::PhotonCollection::PhotonCollection(Bool_t) :
  ParticleCollection(kFALSE)
{
}

monojet::PhotonCollection::~PhotonCollection()
{
  if (array_) {
    std::allocator<Photon>().deallocate(static_cast<Photon*>(array_), NMAX);
    array_ = 0;
  }
}

monojet::PhotonCollection::reference
monojet::PhotonCollection::at(UInt_t _idx)
{
  if (_idx < size) {
    auto* p(array_);
    flatutils::shiftAddr(p, _idx * objSize_);
    return *static_cast<Photon*>(p);
  }

  throw std::out_of_range("PhotonCollection::at");
}

monojet::PhotonCollection::const_reference
monojet::PhotonCollection::at(UInt_t _idx) const
{
  if (_idx < size) {
    auto* p(array_);
    flatutils::shiftAddr(p, _idx * objSize_);
    return *static_cast<Photon const*>(p);
  }

  throw std::out_of_range("PhotonCollection::at");
}

monojet::PhotonCollection::reference
monojet::PhotonCollection::operator[](UInt_t _idx)
{
  auto* p(array_);
  flatutils::shiftAddr(p, _idx * objSize_);
  return *static_cast<Photon*>(p);
}

monojet::PhotonCollection::const_reference
monojet::PhotonCollection::operator[](UInt_t _idx) const
{
  auto* p(array_);
  flatutils::shiftAddr(p, _idx * objSize_);
  return *static_cast<Photon const*>(p);
}

void
monojet::PhotonCollection::setAddress(TTree& _tree, TString const& _objName)
{
  ParticleCollection::setAddress(_tree, _objName);

}

void
monojet::PhotonCollection::book(TTree& _tree, TString const& _objName)
{
  ParticleCollection::book(_tree, _objName);

}

monojet::TriggerObjCollection::TriggerObjCollection() :
  ParticleCollection(kFALSE)
{
  objSize_ = sizeof(TriggerObj);
  array_ = std::allocator<TriggerObj>().allocate(NMAX);
  for (unsigned iP(0); iP != NMAX; ++iP)
    new (static_cast<TriggerObj*>(array_) + iP) TriggerObj(*this, iP);
}

//protected
monojet::TriggerObjCollection::TriggerObjCollection(Bool_t) :
  ParticleCollection(kFALSE)
{
}

monojet::TriggerObjCollection::~TriggerObjCollection()
{
  if (array_) {
    std::allocator<TriggerObj>().deallocate(static_cast<TriggerObj*>(array_), NMAX);
    array_ = 0;
  }
}

monojet::TriggerObjCollection::reference
monojet::TriggerObjCollection::at(UInt_t _idx)
{
  if (_idx < size) {
    auto* p(array_);
    flatutils::shiftAddr(p, _idx * objSize_);
    return *static_cast<TriggerObj*>(p);
  }

  throw std::out_of_range("TriggerObjCollection::at");
}

monojet::TriggerObjCollection::const_reference
monojet::TriggerObjCollection::at(UInt_t _idx) const
{
  if (_idx < size) {
    auto* p(array_);
    flatutils::shiftAddr(p, _idx * objSize_);
    return *static_cast<TriggerObj const*>(p);
  }

  throw std::out_of_range("TriggerObjCollection::at");
}

monojet::TriggerObjCollection::reference
monojet::TriggerObjCollection::operator[](UInt_t _idx)
{
  auto* p(array_);
  flatutils::shiftAddr(p, _idx * objSize_);
  return *static_cast<TriggerObj*>(p);
}

monojet::TriggerObjCollection::const_reference
monojet::TriggerObjCollection::operator[](UInt_t _idx) const
{
  auto* p(array_);
  flatutils::shiftAddr(p, _idx * objSize_);
  return *static_cast<TriggerObj const*>(p);
}

void
monojet::TriggerObjCollection::setAddress(TTree& _tree, TString const& _objName)
{
  ParticleCollection::setAddress(_tree, _objName);

}

void
monojet::TriggerObjCollection::book(TTree& _tree, TString const& _objName)
{
  ParticleCollection::book(_tree, _objName);

}

