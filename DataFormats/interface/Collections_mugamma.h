#ifndef Collections_mugamma_h
#define Collections_mugamma_h
#include "MitFlat/DataFormats/interface/Objects_mugamma.h"
#include "MitFlat/DataFormats/interface/Utils.h"

class TTree;

namespace mugamma {

  class ParticleCollection {
  public:
    static UInt_t const NMAX = 256;
    typedef mugamma::Particle value_type;
    typedef value_type& reference;
    typedef value_type const& const_reference;
    typedef flatutils::iterator<Particle> iterator;
    typedef flatutils::const_iterator<Particle> const_iterator;

    ParticleCollection();
    virtual ~ParticleCollection();

    reference at(UInt_t idx);
    const_reference at(UInt_t idx) const;
    reference operator[](UInt_t);
    const_reference operator[](UInt_t) const;
    iterator begin() { return iterator(static_cast<Particle*>(array_), objSize_); }
    const_iterator begin() const { return const_iterator(static_cast<Particle*>(array_), objSize_); }
    iterator end() { auto* p(array_); flatutils::shiftAddr(p, size * objSize_); return iterator(static_cast<Particle*>(p), objSize_); }
    const_iterator end() const { auto* p(array_); flatutils::shiftAddr(p, size * objSize_); return const_iterator(static_cast<Particle*>(p), objSize_); }
    void clear() { resize(0); }
    void resize(UInt_t size);

    virtual void setAddress(TTree&, TString const& objName);
    virtual void book(TTree&, TString const& objName);

    UInt_t size = 0;
    Float_t pt[NMAX] = {};
    Float_t eta[NMAX] = {};
    Float_t phi[NMAX] = {};

  protected:
    ParticleCollection(Bool_t);
    UInt_t objSize_{0};
    value_type* array_{0};
  };

  class ParticleMCollection : public ParticleCollection {
  public:
    typedef mugamma::ParticleM value_type;
    typedef value_type& reference;
    typedef value_type const& const_reference;
    typedef flatutils::iterator<ParticleM> iterator;
    typedef flatutils::const_iterator<ParticleM> const_iterator;

    ParticleMCollection();
    virtual ~ParticleMCollection();

    reference at(UInt_t idx);
    const_reference at(UInt_t idx) const;
    reference operator[](UInt_t);
    const_reference operator[](UInt_t) const;
    iterator begin() { return iterator(static_cast<ParticleM*>(array_), objSize_); }
    const_iterator begin() const { return const_iterator(static_cast<ParticleM*>(array_), objSize_); }
    iterator end() { auto* p(array_); flatutils::shiftAddr(p, size * objSize_); return iterator(static_cast<ParticleM*>(p), objSize_); }
    const_iterator end() const { auto* p(array_); flatutils::shiftAddr(p, size * objSize_); return const_iterator(static_cast<ParticleM*>(p), objSize_); }

    virtual void setAddress(TTree&, TString const& objName);
    virtual void book(TTree&, TString const& objName);

    Float_t mass[NMAX] = {};

  protected:
    ParticleMCollection(Bool_t);
  };

  class JetCollection : public ParticleMCollection {
  public:
    typedef mugamma::Jet value_type;
    typedef value_type& reference;
    typedef value_type const& const_reference;
    typedef flatutils::iterator<Jet> iterator;
    typedef flatutils::const_iterator<Jet> const_iterator;

    JetCollection();
    virtual ~JetCollection();

    reference at(UInt_t idx);
    const_reference at(UInt_t idx) const;
    reference operator[](UInt_t);
    const_reference operator[](UInt_t) const;
    iterator begin() { return iterator(static_cast<Jet*>(array_), objSize_); }
    const_iterator begin() const { return const_iterator(static_cast<Jet*>(array_), objSize_); }
    iterator end() { auto* p(array_); flatutils::shiftAddr(p, size * objSize_); return iterator(static_cast<Jet*>(p), objSize_); }
    const_iterator end() const { auto* p(array_); flatutils::shiftAddr(p, size * objSize_); return const_iterator(static_cast<Jet*>(p), objSize_); }

    virtual void setAddress(TTree&, TString const& objName);
    virtual void book(TTree&, TString const& objName);


  protected:
    JetCollection(Bool_t);
  };

  class PhotonCollection : public ParticleCollection {
  public:
    typedef mugamma::Photon value_type;
    typedef value_type& reference;
    typedef value_type const& const_reference;
    typedef flatutils::iterator<Photon> iterator;
    typedef flatutils::const_iterator<Photon> const_iterator;

    PhotonCollection();
    virtual ~PhotonCollection();

    reference at(UInt_t idx);
    const_reference at(UInt_t idx) const;
    reference operator[](UInt_t);
    const_reference operator[](UInt_t) const;
    iterator begin() { return iterator(static_cast<Photon*>(array_), objSize_); }
    const_iterator begin() const { return const_iterator(static_cast<Photon*>(array_), objSize_); }
    iterator end() { auto* p(array_); flatutils::shiftAddr(p, size * objSize_); return iterator(static_cast<Photon*>(p), objSize_); }
    const_iterator end() const { auto* p(array_); flatutils::shiftAddr(p, size * objSize_); return const_iterator(static_cast<Photon*>(p), objSize_); }

    virtual void setAddress(TTree&, TString const& objName);
    virtual void book(TTree&, TString const& objName);

    Float_t chIso[NMAX] = {};
    Float_t nhIso[NMAX] = {};
    Float_t phIso[NMAX] = {};
    Float_t sieie[NMAX] = {};
    Float_t hOverE[NMAX] = {};
    Bool_t pixelVeto[NMAX] = {};
    Bool_t csafeVeto[NMAX] = {};
    Bool_t isLoose[NMAX] = {};
    Bool_t isMedium[NMAX] = {};
    Bool_t isTight[NMAX] = {};

  protected:
    PhotonCollection(Bool_t);
  };

  class ElectronCollection : public ParticleMCollection {
  public:
    typedef mugamma::Electron value_type;
    typedef value_type& reference;
    typedef value_type const& const_reference;
    typedef flatutils::iterator<Electron> iterator;
    typedef flatutils::const_iterator<Electron> const_iterator;

    ElectronCollection();
    virtual ~ElectronCollection();

    reference at(UInt_t idx);
    const_reference at(UInt_t idx) const;
    reference operator[](UInt_t);
    const_reference operator[](UInt_t) const;
    iterator begin() { return iterator(static_cast<Electron*>(array_), objSize_); }
    const_iterator begin() const { return const_iterator(static_cast<Electron*>(array_), objSize_); }
    iterator end() { auto* p(array_); flatutils::shiftAddr(p, size * objSize_); return iterator(static_cast<Electron*>(p), objSize_); }
    const_iterator end() const { auto* p(array_); flatutils::shiftAddr(p, size * objSize_); return const_iterator(static_cast<Electron*>(p), objSize_); }

    virtual void setAddress(TTree&, TString const& objName);
    virtual void book(TTree&, TString const& objName);

    Bool_t tight[NMAX] = {};

  protected:
    ElectronCollection(Bool_t);
  };

  class MuonCollection : public ParticleMCollection {
  public:
    typedef mugamma::Muon value_type;
    typedef value_type& reference;
    typedef value_type const& const_reference;
    typedef flatutils::iterator<Muon> iterator;
    typedef flatutils::const_iterator<Muon> const_iterator;

    MuonCollection();
    virtual ~MuonCollection();

    reference at(UInt_t idx);
    const_reference at(UInt_t idx) const;
    reference operator[](UInt_t);
    const_reference operator[](UInt_t) const;
    iterator begin() { return iterator(static_cast<Muon*>(array_), objSize_); }
    const_iterator begin() const { return const_iterator(static_cast<Muon*>(array_), objSize_); }
    iterator end() { auto* p(array_); flatutils::shiftAddr(p, size * objSize_); return iterator(static_cast<Muon*>(p), objSize_); }
    const_iterator end() const { auto* p(array_); flatutils::shiftAddr(p, size * objSize_); return const_iterator(static_cast<Muon*>(p), objSize_); }

    virtual void setAddress(TTree&, TString const& objName);
    virtual void book(TTree&, TString const& objName);

    Bool_t tight[NMAX] = {};

  protected:
    MuonCollection(Bool_t);
  };

}

#endif
