#ifndef Collections_monojet_h
#define Collections_monojet_h
#include "MitFlat/DataFormats/interface/Objects_monojet.h"
#include "MitFlat/DataFormats/interface/Utils.h"

class TTree;

namespace monojet {

  class ParticleCollection {
  public:
    static UInt_t const NMAX = 256;
    typedef monojet::Particle value_type;
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

  class JetCollection : public ParticleCollection {
  public:
    typedef monojet::Jet value_type;
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

    Float_t btag[NMAX] = {};
    Float_t chFrac[NMAX] = {};
    Float_t nhFrac[NMAX] = {};
    Float_t neFrac[NMAX] = {};

  protected:
    JetCollection(Bool_t);
  };

  class ElectronCollection : public ParticleCollection {
  public:
    typedef monojet::Electron value_type;
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


  protected:
    ElectronCollection(Bool_t);
  };

  class MuonCollection : public ParticleCollection {
  public:
    typedef monojet::Muon value_type;
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


  protected:
    MuonCollection(Bool_t);
  };

  class TauCollection : public ParticleCollection {
  public:
    typedef monojet::Tau value_type;
    typedef value_type& reference;
    typedef value_type const& const_reference;
    typedef flatutils::iterator<Tau> iterator;
    typedef flatutils::const_iterator<Tau> const_iterator;

    TauCollection();
    virtual ~TauCollection();

    reference at(UInt_t idx);
    const_reference at(UInt_t idx) const;
    reference operator[](UInt_t);
    const_reference operator[](UInt_t) const;
    iterator begin() { return iterator(static_cast<Tau*>(array_), objSize_); }
    const_iterator begin() const { return const_iterator(static_cast<Tau*>(array_), objSize_); }
    iterator end() { auto* p(array_); flatutils::shiftAddr(p, size * objSize_); return iterator(static_cast<Tau*>(p), objSize_); }
    const_iterator end() const { auto* p(array_); flatutils::shiftAddr(p, size * objSize_); return const_iterator(static_cast<Tau*>(p), objSize_); }

    virtual void setAddress(TTree&, TString const& objName);
    virtual void book(TTree&, TString const& objName);

    Float_t disc[NMAX] = {};

  protected:
    TauCollection(Bool_t);
  };

  class PhotonCollection : public ParticleCollection {
  public:
    typedef monojet::Photon value_type;
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


  protected:
    PhotonCollection(Bool_t);
  };

  class TriggerObjCollection : public ParticleCollection {
  public:
    typedef monojet::TriggerObj value_type;
    typedef value_type& reference;
    typedef value_type const& const_reference;
    typedef flatutils::iterator<TriggerObj> iterator;
    typedef flatutils::const_iterator<TriggerObj> const_iterator;

    TriggerObjCollection();
    virtual ~TriggerObjCollection();

    reference at(UInt_t idx);
    const_reference at(UInt_t idx) const;
    reference operator[](UInt_t);
    const_reference operator[](UInt_t) const;
    iterator begin() { return iterator(static_cast<TriggerObj*>(array_), objSize_); }
    const_iterator begin() const { return const_iterator(static_cast<TriggerObj*>(array_), objSize_); }
    iterator end() { auto* p(array_); flatutils::shiftAddr(p, size * objSize_); return iterator(static_cast<TriggerObj*>(p), objSize_); }
    const_iterator end() const { auto* p(array_); flatutils::shiftAddr(p, size * objSize_); return const_iterator(static_cast<TriggerObj*>(p), objSize_); }

    virtual void setAddress(TTree&, TString const& objName);
    virtual void book(TTree&, TString const& objName);


  protected:
    TriggerObjCollection(Bool_t);
  };

}

#endif
