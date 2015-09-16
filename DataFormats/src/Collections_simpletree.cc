#include "MitFlat/DataFormats/interface/Collections_simpletree.h"
#include "TTree.h"
#include <stdexcept>
#include <memory>

simpletree::ParticleCollection::ParticleCollection(TString const& _name) :
  name_(_name)
{
  objSize_ = sizeof(Particle);
  array_ = std::allocator<Particle>().allocate(NMAX);
  for (unsigned iP(0); iP != NMAX; ++iP)
    new (static_cast<Particle*>(array_) + iP) Particle(*this, iP);
}

//protected
simpletree::ParticleCollection::ParticleCollection(TString const& _name, Bool_t) :
  name_(_name)
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
simpletree::ParticleCollection::setStatus(TTree& _tree, Bool_t _status, BranchList const& _branches/* = BranchList()*/)
{
  if (_branches.size() == 0 || _status)
    _tree.SetBranchStatus(name_ + ".size", _status);
  if (branchIn(&pt, _branches))
    _tree.SetBranchStatus(name_ + ".pt", _status);
  if (branchIn(&eta, _branches))
    _tree.SetBranchStatus(name_ + ".eta", _status);
  if (branchIn(&phi, _branches))
    _tree.SetBranchStatus(name_ + ".phi", _status);
}

void
simpletree::ParticleCollection::setAddress(TTree& _tree, BranchList const& _branches/* = BranchList()*/)
{
  setStatusAndAddress(_tree, name_ + ".size", &size);
  if (branchIn(&pt, _branches))
    setStatusAndAddress(_tree, name_ + ".pt", pt);
  if (branchIn(&eta, _branches))
    setStatusAndAddress(_tree, name_ + ".eta", eta);
  if (branchIn(&phi, _branches))
    setStatusAndAddress(_tree, name_ + ".phi", phi);
}

void
simpletree::ParticleCollection::book(TTree& _tree, BranchList const& _branches/* = BranchList()*/)
{
  _tree.Branch(name_ + ".size", &size, "size/i");
  if (branchIn(&pt, _branches))
    _tree.Branch(name_ + ".pt", pt, "pt[" + name_ + ".size]/F");
  if (branchIn(&eta, _branches))
    _tree.Branch(name_ + ".eta", eta, "eta[" + name_ + ".size]/F");
  if (branchIn(&phi, _branches))
    _tree.Branch(name_ + ".phi", phi, "phi[" + name_ + ".size]/F");
}

simpletree::ParticleMCollection::ParticleMCollection(TString const& _name) :
  ParticleCollection(_name, kFALSE)
{
  objSize_ = sizeof(ParticleM);
  array_ = std::allocator<ParticleM>().allocate(NMAX);
  for (unsigned iP(0); iP != NMAX; ++iP)
    new (static_cast<ParticleM*>(array_) + iP) ParticleM(*this, iP);
}

//protected
simpletree::ParticleMCollection::ParticleMCollection(TString const& _name, Bool_t) :
  ParticleCollection(_name, kFALSE)
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
simpletree::ParticleMCollection::setStatus(TTree& _tree, Bool_t _status, BranchList const& _branches/* = BranchList()*/)
{
  ParticleCollection::setStatus(_tree, _status, _branches);

  if (branchIn(&mass, _branches))
    _tree.SetBranchStatus(name_ + ".mass", _status);
}

void
simpletree::ParticleMCollection::setAddress(TTree& _tree, BranchList const& _branches/* = BranchList()*/)
{
  ParticleCollection::setAddress(_tree, _branches);

  if (branchIn(&mass, _branches))
    setStatusAndAddress(_tree, name_ + ".mass", mass);
}

void
simpletree::ParticleMCollection::book(TTree& _tree, BranchList const& _branches/* = BranchList()*/)
{
  ParticleCollection::book(_tree, _branches);

  if (branchIn(&mass, _branches))
    _tree.Branch(name_ + ".mass", mass, "mass[" + name_ + ".size]/F");
}

simpletree::JetCollection::JetCollection(TString const& _name) :
  ParticleMCollection(_name, kFALSE)
{
  objSize_ = sizeof(Jet);
  array_ = std::allocator<Jet>().allocate(NMAX);
  for (unsigned iP(0); iP != NMAX; ++iP)
    new (static_cast<Jet*>(array_) + iP) Jet(*this, iP);
}

//protected
simpletree::JetCollection::JetCollection(TString const& _name, Bool_t) :
  ParticleMCollection(_name, kFALSE)
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
simpletree::JetCollection::setStatus(TTree& _tree, Bool_t _status, BranchList const& _branches/* = BranchList()*/)
{
  ParticleMCollection::setStatus(_tree, _status, _branches);

}

void
simpletree::JetCollection::setAddress(TTree& _tree, BranchList const& _branches/* = BranchList()*/)
{
  ParticleMCollection::setAddress(_tree, _branches);

}

void
simpletree::JetCollection::book(TTree& _tree, BranchList const& _branches/* = BranchList()*/)
{
  ParticleMCollection::book(_tree, _branches);

}

simpletree::PhotonCollection::PhotonCollection(TString const& _name) :
  ParticleCollection(_name, kFALSE)
{
  objSize_ = sizeof(Photon);
  array_ = std::allocator<Photon>().allocate(NMAX);
  for (unsigned iP(0); iP != NMAX; ++iP)
    new (static_cast<Photon*>(array_) + iP) Photon(*this, iP);
}

//protected
simpletree::PhotonCollection::PhotonCollection(TString const& _name, Bool_t) :
  ParticleCollection(_name, kFALSE)
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
simpletree::PhotonCollection::setStatus(TTree& _tree, Bool_t _status, BranchList const& _branches/* = BranchList()*/)
{
  ParticleCollection::setStatus(_tree, _status, _branches);

  if (branchIn(&chIso, _branches))
    _tree.SetBranchStatus(name_ + ".chIso", _status);
  if (branchIn(&nhIso, _branches))
    _tree.SetBranchStatus(name_ + ".nhIso", _status);
  if (branchIn(&phIso, _branches))
    _tree.SetBranchStatus(name_ + ".phIso", _status);
  if (branchIn(&sieie, _branches))
    _tree.SetBranchStatus(name_ + ".sieie", _status);
  if (branchIn(&hOverE, _branches))
    _tree.SetBranchStatus(name_ + ".hOverE", _status);
  if (branchIn(&matchedGen, _branches))
    _tree.SetBranchStatus(name_ + ".matchedGen", _status);
  if (branchIn(&hadDecay, _branches))
    _tree.SetBranchStatus(name_ + ".hadDecay", _status);
  if (branchIn(&pixelVeto, _branches))
    _tree.SetBranchStatus(name_ + ".pixelVeto", _status);
  if (branchIn(&csafeVeto, _branches))
    _tree.SetBranchStatus(name_ + ".csafeVeto", _status);
  if (branchIn(&loose, _branches))
    _tree.SetBranchStatus(name_ + ".loose", _status);
  if (branchIn(&medium, _branches))
    _tree.SetBranchStatus(name_ + ".medium", _status);
  if (branchIn(&tight, _branches))
    _tree.SetBranchStatus(name_ + ".tight", _status);
  if (branchIn(&matchHLT165HE10, _branches))
    _tree.SetBranchStatus(name_ + ".matchHLT165HE10", _status);
  if (branchIn(&matchHLT175, _branches))
    _tree.SetBranchStatus(name_ + ".matchHLT175", _status);
}

void
simpletree::PhotonCollection::setAddress(TTree& _tree, BranchList const& _branches/* = BranchList()*/)
{
  ParticleCollection::setAddress(_tree, _branches);

  if (branchIn(&chIso, _branches))
    setStatusAndAddress(_tree, name_ + ".chIso", chIso);
  if (branchIn(&nhIso, _branches))
    setStatusAndAddress(_tree, name_ + ".nhIso", nhIso);
  if (branchIn(&phIso, _branches))
    setStatusAndAddress(_tree, name_ + ".phIso", phIso);
  if (branchIn(&sieie, _branches))
    setStatusAndAddress(_tree, name_ + ".sieie", sieie);
  if (branchIn(&hOverE, _branches))
    setStatusAndAddress(_tree, name_ + ".hOverE", hOverE);
  if (branchIn(&matchedGen, _branches))
    setStatusAndAddress(_tree, name_ + ".matchedGen", matchedGen);
  if (branchIn(&hadDecay, _branches))
    setStatusAndAddress(_tree, name_ + ".hadDecay", hadDecay);
  if (branchIn(&pixelVeto, _branches))
    setStatusAndAddress(_tree, name_ + ".pixelVeto", pixelVeto);
  if (branchIn(&csafeVeto, _branches))
    setStatusAndAddress(_tree, name_ + ".csafeVeto", csafeVeto);
  if (branchIn(&loose, _branches))
    setStatusAndAddress(_tree, name_ + ".loose", loose);
  if (branchIn(&medium, _branches))
    setStatusAndAddress(_tree, name_ + ".medium", medium);
  if (branchIn(&tight, _branches))
    setStatusAndAddress(_tree, name_ + ".tight", tight);
  if (branchIn(&matchHLT165HE10, _branches))
    setStatusAndAddress(_tree, name_ + ".matchHLT165HE10", matchHLT165HE10);
  if (branchIn(&matchHLT175, _branches))
    setStatusAndAddress(_tree, name_ + ".matchHLT175", matchHLT175);
}

void
simpletree::PhotonCollection::book(TTree& _tree, BranchList const& _branches/* = BranchList()*/)
{
  ParticleCollection::book(_tree, _branches);

  if (branchIn(&chIso, _branches))
    _tree.Branch(name_ + ".chIso", chIso, "chIso[" + name_ + ".size]/F");
  if (branchIn(&nhIso, _branches))
    _tree.Branch(name_ + ".nhIso", nhIso, "nhIso[" + name_ + ".size]/F");
  if (branchIn(&phIso, _branches))
    _tree.Branch(name_ + ".phIso", phIso, "phIso[" + name_ + ".size]/F");
  if (branchIn(&sieie, _branches))
    _tree.Branch(name_ + ".sieie", sieie, "sieie[" + name_ + ".size]/F");
  if (branchIn(&hOverE, _branches))
    _tree.Branch(name_ + ".hOverE", hOverE, "hOverE[" + name_ + ".size]/F");
  if (branchIn(&matchedGen, _branches))
    _tree.Branch(name_ + ".matchedGen", matchedGen, "matchedGen[" + name_ + ".size]/I");
  if (branchIn(&hadDecay, _branches))
    _tree.Branch(name_ + ".hadDecay", hadDecay, "hadDecay[" + name_ + ".size]/O");
  if (branchIn(&pixelVeto, _branches))
    _tree.Branch(name_ + ".pixelVeto", pixelVeto, "pixelVeto[" + name_ + ".size]/O");
  if (branchIn(&csafeVeto, _branches))
    _tree.Branch(name_ + ".csafeVeto", csafeVeto, "csafeVeto[" + name_ + ".size]/O");
  if (branchIn(&loose, _branches))
    _tree.Branch(name_ + ".loose", loose, "loose[" + name_ + ".size]/O");
  if (branchIn(&medium, _branches))
    _tree.Branch(name_ + ".medium", medium, "medium[" + name_ + ".size]/O");
  if (branchIn(&tight, _branches))
    _tree.Branch(name_ + ".tight", tight, "tight[" + name_ + ".size]/O");
  if (branchIn(&matchHLT165HE10, _branches))
    _tree.Branch(name_ + ".matchHLT165HE10", matchHLT165HE10, "matchHLT165HE10[" + name_ + ".size]/O");
  if (branchIn(&matchHLT175, _branches))
    _tree.Branch(name_ + ".matchHLT175", matchHLT175, "matchHLT175[" + name_ + ".size]/O");
}

simpletree::LeptonCollection::LeptonCollection(TString const& _name) :
  ParticleMCollection(_name, kFALSE)
{
  objSize_ = sizeof(Lepton);
  array_ = std::allocator<Lepton>().allocate(NMAX);
  for (unsigned iP(0); iP != NMAX; ++iP)
    new (static_cast<Lepton*>(array_) + iP) Lepton(*this, iP);
}

//protected
simpletree::LeptonCollection::LeptonCollection(TString const& _name, Bool_t) :
  ParticleMCollection(_name, kFALSE)
{
}

simpletree::LeptonCollection::~LeptonCollection()
{
  if (array_) {
    std::allocator<Lepton>().deallocate(static_cast<Lepton*>(array_), NMAX);
    array_ = 0;
  }
}

simpletree::LeptonCollection::reference
simpletree::LeptonCollection::at(UInt_t _idx)
{
  if (_idx < size) {
    auto* p(array_);
    flatutils::shiftAddr(p, _idx * objSize_);
    return *static_cast<Lepton*>(p);
  }

  throw std::out_of_range("LeptonCollection::at");
}

simpletree::LeptonCollection::const_reference
simpletree::LeptonCollection::at(UInt_t _idx) const
{
  if (_idx < size) {
    auto* p(array_);
    flatutils::shiftAddr(p, _idx * objSize_);
    return *static_cast<Lepton const*>(p);
  }

  throw std::out_of_range("LeptonCollection::at");
}

simpletree::LeptonCollection::reference
simpletree::LeptonCollection::operator[](UInt_t _idx)
{
  auto* p(array_);
  flatutils::shiftAddr(p, _idx * objSize_);
  return *static_cast<Lepton*>(p);
}

simpletree::LeptonCollection::const_reference
simpletree::LeptonCollection::operator[](UInt_t _idx) const
{
  auto* p(array_);
  flatutils::shiftAddr(p, _idx * objSize_);
  return *static_cast<Lepton const*>(p);
}

void
simpletree::LeptonCollection::push_back(const_reference val)
{
  UInt_t current(size);
  resize(current + 1);
  array_[current] = val;
}

void
simpletree::LeptonCollection::setStatus(TTree& _tree, Bool_t _status, BranchList const& _branches/* = BranchList()*/)
{
  ParticleMCollection::setStatus(_tree, _status, _branches);

  if (branchIn(&matchedGen, _branches))
    _tree.SetBranchStatus(name_ + ".matchedGen", _status);
  if (branchIn(&tauDecay, _branches))
    _tree.SetBranchStatus(name_ + ".tauDecay", _status);
  if (branchIn(&hadDecay, _branches))
    _tree.SetBranchStatus(name_ + ".hadDecay", _status);
  if (branchIn(&positive, _branches))
    _tree.SetBranchStatus(name_ + ".positive", _status);
  if (branchIn(&tight, _branches))
    _tree.SetBranchStatus(name_ + ".tight", _status);
}

void
simpletree::LeptonCollection::setAddress(TTree& _tree, BranchList const& _branches/* = BranchList()*/)
{
  ParticleMCollection::setAddress(_tree, _branches);

  if (branchIn(&matchedGen, _branches))
    setStatusAndAddress(_tree, name_ + ".matchedGen", matchedGen);
  if (branchIn(&tauDecay, _branches))
    setStatusAndAddress(_tree, name_ + ".tauDecay", tauDecay);
  if (branchIn(&hadDecay, _branches))
    setStatusAndAddress(_tree, name_ + ".hadDecay", hadDecay);
  if (branchIn(&positive, _branches))
    setStatusAndAddress(_tree, name_ + ".positive", positive);
  if (branchIn(&tight, _branches))
    setStatusAndAddress(_tree, name_ + ".tight", tight);
}

void
simpletree::LeptonCollection::book(TTree& _tree, BranchList const& _branches/* = BranchList()*/)
{
  ParticleMCollection::book(_tree, _branches);

  if (branchIn(&matchedGen, _branches))
    _tree.Branch(name_ + ".matchedGen", matchedGen, "matchedGen[" + name_ + ".size]/I");
  if (branchIn(&tauDecay, _branches))
    _tree.Branch(name_ + ".tauDecay", tauDecay, "tauDecay[" + name_ + ".size]/O");
  if (branchIn(&hadDecay, _branches))
    _tree.Branch(name_ + ".hadDecay", hadDecay, "hadDecay[" + name_ + ".size]/O");
  if (branchIn(&positive, _branches))
    _tree.Branch(name_ + ".positive", positive, "positive[" + name_ + ".size]/O");
  if (branchIn(&tight, _branches))
    _tree.Branch(name_ + ".tight", tight, "tight[" + name_ + ".size]/O");
}

simpletree::ElectronCollection::ElectronCollection(TString const& _name) :
  LeptonCollection(_name, kFALSE)
{
  objSize_ = sizeof(Electron);
  array_ = std::allocator<Electron>().allocate(NMAX);
  for (unsigned iP(0); iP != NMAX; ++iP)
    new (static_cast<Electron*>(array_) + iP) Electron(*this, iP);
}

//protected
simpletree::ElectronCollection::ElectronCollection(TString const& _name, Bool_t) :
  LeptonCollection(_name, kFALSE)
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
simpletree::ElectronCollection::setStatus(TTree& _tree, Bool_t _status, BranchList const& _branches/* = BranchList()*/)
{
  LeptonCollection::setStatus(_tree, _status, _branches);

  if (branchIn(&matchHLT23Loose, _branches))
    _tree.SetBranchStatus(name_ + ".matchHLT23Loose", _status);
  if (branchIn(&matchHLT27Loose, _branches))
    _tree.SetBranchStatus(name_ + ".matchHLT27Loose", _status);
}

void
simpletree::ElectronCollection::setAddress(TTree& _tree, BranchList const& _branches/* = BranchList()*/)
{
  LeptonCollection::setAddress(_tree, _branches);

  if (branchIn(&matchHLT23Loose, _branches))
    setStatusAndAddress(_tree, name_ + ".matchHLT23Loose", matchHLT23Loose);
  if (branchIn(&matchHLT27Loose, _branches))
    setStatusAndAddress(_tree, name_ + ".matchHLT27Loose", matchHLT27Loose);
}

void
simpletree::ElectronCollection::book(TTree& _tree, BranchList const& _branches/* = BranchList()*/)
{
  LeptonCollection::book(_tree, _branches);

  if (branchIn(&matchHLT23Loose, _branches))
    _tree.Branch(name_ + ".matchHLT23Loose", matchHLT23Loose, "matchHLT23Loose[" + name_ + ".size]/O");
  if (branchIn(&matchHLT27Loose, _branches))
    _tree.Branch(name_ + ".matchHLT27Loose", matchHLT27Loose, "matchHLT27Loose[" + name_ + ".size]/O");
}

simpletree::MuonCollection::MuonCollection(TString const& _name) :
  LeptonCollection(_name, kFALSE)
{
  objSize_ = sizeof(Muon);
  array_ = std::allocator<Muon>().allocate(NMAX);
  for (unsigned iP(0); iP != NMAX; ++iP)
    new (static_cast<Muon*>(array_) + iP) Muon(*this, iP);
}

//protected
simpletree::MuonCollection::MuonCollection(TString const& _name, Bool_t) :
  LeptonCollection(_name, kFALSE)
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
simpletree::MuonCollection::setStatus(TTree& _tree, Bool_t _status, BranchList const& _branches/* = BranchList()*/)
{
  LeptonCollection::setStatus(_tree, _status, _branches);

  if (branchIn(&matchHLT24, _branches))
    _tree.SetBranchStatus(name_ + ".matchHLT24", _status);
  if (branchIn(&matchHLT27, _branches))
    _tree.SetBranchStatus(name_ + ".matchHLT27", _status);
}

void
simpletree::MuonCollection::setAddress(TTree& _tree, BranchList const& _branches/* = BranchList()*/)
{
  LeptonCollection::setAddress(_tree, _branches);

  if (branchIn(&matchHLT24, _branches))
    setStatusAndAddress(_tree, name_ + ".matchHLT24", matchHLT24);
  if (branchIn(&matchHLT27, _branches))
    setStatusAndAddress(_tree, name_ + ".matchHLT27", matchHLT27);
}

void
simpletree::MuonCollection::book(TTree& _tree, BranchList const& _branches/* = BranchList()*/)
{
  LeptonCollection::book(_tree, _branches);

  if (branchIn(&matchHLT24, _branches))
    _tree.Branch(name_ + ".matchHLT24", matchHLT24, "matchHLT24[" + name_ + ".size]/O");
  if (branchIn(&matchHLT27, _branches))
    _tree.Branch(name_ + ".matchHLT27", matchHLT27, "matchHLT27[" + name_ + ".size]/O");
}

simpletree::HLTCollection::HLTCollection(TString const& _name) :
  name_(_name)
{
  objSize_ = sizeof(HLT);
  array_ = std::allocator<HLT>().allocate(NMAX);
  for (unsigned iP(0); iP != NMAX; ++iP)
    new (static_cast<HLT*>(array_) + iP) HLT(*this, iP);
}

//protected
simpletree::HLTCollection::HLTCollection(TString const& _name, Bool_t) :
  name_(_name)
{
}

simpletree::HLTCollection::~HLTCollection()
{
  if (array_) {
    std::allocator<HLT>().deallocate(static_cast<HLT*>(array_), NMAX);
    array_ = 0;
  }
}

simpletree::HLTCollection::reference
simpletree::HLTCollection::at(UInt_t _idx)
{
  if (_idx < size) {
    auto* p(array_);
    flatutils::shiftAddr(p, _idx * objSize_);
    return *static_cast<HLT*>(p);
  }

  throw std::out_of_range("HLTCollection::at");
}

simpletree::HLTCollection::const_reference
simpletree::HLTCollection::at(UInt_t _idx) const
{
  if (_idx < size) {
    auto* p(array_);
    flatutils::shiftAddr(p, _idx * objSize_);
    return *static_cast<HLT const*>(p);
  }

  throw std::out_of_range("HLTCollection::at");
}

simpletree::HLTCollection::reference
simpletree::HLTCollection::operator[](UInt_t _idx)
{
  auto* p(array_);
  flatutils::shiftAddr(p, _idx * objSize_);
  return *static_cast<HLT*>(p);
}

simpletree::HLTCollection::const_reference
simpletree::HLTCollection::operator[](UInt_t _idx) const
{
  auto* p(array_);
  flatutils::shiftAddr(p, _idx * objSize_);
  return *static_cast<HLT const*>(p);
}

void
simpletree::HLTCollection::setStatus(TTree& _tree, Bool_t _status, BranchList const& _branches/* = BranchList()*/)
{
  if (branchIn(&pass, _branches))
    _tree.SetBranchStatus(name_ + ".pass", _status);
}

void
simpletree::HLTCollection::setAddress(TTree& _tree, BranchList const& _branches/* = BranchList()*/)
{
  if (branchIn(&pass, _branches))
    setStatusAndAddress(_tree, name_ + ".pass", pass);
}

void
simpletree::HLTCollection::book(TTree& _tree, BranchList const& _branches/* = BranchList()*/)
{
  if (branchIn(&pass, _branches))
    _tree.Branch(name_ + ".pass", pass, "pass[" + TString::Format("%d", NMAX) + "]/O");
}

