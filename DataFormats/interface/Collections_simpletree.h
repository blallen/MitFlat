#ifndef Collections_simpletree_h
#define Collections_simpletree_h
#include "MitFlat/DataFormats/interface/Objects_simpletree.h"
#include "MitFlat/DataFormats/interface/Utils.h"

class TTree;

namespace simpletree {

  class ParticleCollection {
  public:
    static UInt_t const NMAX = 256;
    typedef simpletree::Particle value_type;
    typedef value_type& reference;
    typedef value_type const& const_reference;
    typedef flatutils::iterator<Particle> iterator;
    typedef flatutils::const_iterator<Particle> const_iterator;

    ParticleCollection(TString const& name = "particles");
    ParticleCollection(ParticleCollection const&);
    virtual ~ParticleCollection();
    ParticleCollection& operator=(ParticleCollection const&);

    reference at(UInt_t idx);
    const_reference at(UInt_t idx) const;
    reference operator[](UInt_t);
    const_reference operator[](UInt_t) const;
    iterator begin() { return iterator(static_cast<Particle*>(array_), objSize_); }
    const_iterator begin() const { return const_iterator(static_cast<Particle*>(array_), objSize_); }
    iterator end() { auto* p(array_); flatutils::shiftAddr(p, size * objSize_); return iterator(static_cast<Particle*>(p), objSize_); }
    const_iterator end() const { auto* p(array_); flatutils::shiftAddr(p, size * objSize_); return const_iterator(static_cast<Particle*>(p), objSize_); }
    void push_back(const_reference);
    void clear() { resize(0); }
    void resize(UInt_t size);

    void setName(TString const& name) { name_ = name; }
    virtual void setStatus(TTree&, Bool_t, BranchList const& = BranchList());
    virtual void setAddress(TTree&, BranchList const& = BranchList());
    virtual void book(TTree&, BranchList const& = BranchList());

  protected:
    ParticleCollection(TString const&, Bool_t);
    TString name_;
    UInt_t objSize_{0};
    value_type* array_{0};

  public:
    UInt_t size{0};
    Float_t pt[NMAX]{};
    Float_t eta[NMAX]{};
    Float_t phi[NMAX]{};
  };

  class ParticleMCollection : public ParticleCollection {
  public:
    typedef simpletree::ParticleM value_type;
    typedef value_type& reference;
    typedef value_type const& const_reference;
    typedef flatutils::iterator<ParticleM> iterator;
    typedef flatutils::const_iterator<ParticleM> const_iterator;

    ParticleMCollection(TString const& name = "particlems");
    ParticleMCollection(ParticleMCollection const&);
    virtual ~ParticleMCollection();
    ParticleMCollection& operator=(ParticleMCollection const&);

    reference at(UInt_t idx);
    const_reference at(UInt_t idx) const;
    reference operator[](UInt_t);
    const_reference operator[](UInt_t) const;
    iterator begin() { return iterator(static_cast<ParticleM*>(array_), objSize_); }
    const_iterator begin() const { return const_iterator(static_cast<ParticleM*>(array_), objSize_); }
    iterator end() { auto* p(array_); flatutils::shiftAddr(p, size * objSize_); return iterator(static_cast<ParticleM*>(p), objSize_); }
    const_iterator end() const { auto* p(array_); flatutils::shiftAddr(p, size * objSize_); return const_iterator(static_cast<ParticleM*>(p), objSize_); }
    void push_back(const_reference);

    void setName(TString const& name) { name_ = name; }
    virtual void setStatus(TTree&, Bool_t, BranchList const& = BranchList());
    virtual void setAddress(TTree&, BranchList const& = BranchList());
    virtual void book(TTree&, BranchList const& = BranchList());

  protected:
    ParticleMCollection(TString const&, Bool_t);

  public:
    Float_t mass[NMAX]{};
  };

  class JetCollection : public ParticleMCollection {
  public:
    typedef simpletree::Jet value_type;
    typedef value_type& reference;
    typedef value_type const& const_reference;
    typedef flatutils::iterator<Jet> iterator;
    typedef flatutils::const_iterator<Jet> const_iterator;

    JetCollection(TString const& name = "jets");
    JetCollection(JetCollection const&);
    virtual ~JetCollection();
    JetCollection& operator=(JetCollection const&);

    reference at(UInt_t idx);
    const_reference at(UInt_t idx) const;
    reference operator[](UInt_t);
    const_reference operator[](UInt_t) const;
    iterator begin() { return iterator(static_cast<Jet*>(array_), objSize_); }
    const_iterator begin() const { return const_iterator(static_cast<Jet*>(array_), objSize_); }
    iterator end() { auto* p(array_); flatutils::shiftAddr(p, size * objSize_); return iterator(static_cast<Jet*>(p), objSize_); }
    const_iterator end() const { auto* p(array_); flatutils::shiftAddr(p, size * objSize_); return const_iterator(static_cast<Jet*>(p), objSize_); }
    void push_back(const_reference);

    void setName(TString const& name) { name_ = name; }
    virtual void setStatus(TTree&, Bool_t, BranchList const& = BranchList());
    virtual void setAddress(TTree&, BranchList const& = BranchList());
    virtual void book(TTree&, BranchList const& = BranchList());

  protected:
    JetCollection(TString const&, Bool_t);
  };

  class PhotonCollection : public ParticleCollection {
  public:
    typedef simpletree::Photon value_type;
    typedef value_type& reference;
    typedef value_type const& const_reference;
    typedef flatutils::iterator<Photon> iterator;
    typedef flatutils::const_iterator<Photon> const_iterator;

    PhotonCollection(TString const& name = "photons");
    PhotonCollection(PhotonCollection const&);
    virtual ~PhotonCollection();
    PhotonCollection& operator=(PhotonCollection const&);

    reference at(UInt_t idx);
    const_reference at(UInt_t idx) const;
    reference operator[](UInt_t);
    const_reference operator[](UInt_t) const;
    iterator begin() { return iterator(static_cast<Photon*>(array_), objSize_); }
    const_iterator begin() const { return const_iterator(static_cast<Photon*>(array_), objSize_); }
    iterator end() { auto* p(array_); flatutils::shiftAddr(p, size * objSize_); return iterator(static_cast<Photon*>(p), objSize_); }
    const_iterator end() const { auto* p(array_); flatutils::shiftAddr(p, size * objSize_); return const_iterator(static_cast<Photon*>(p), objSize_); }
    void push_back(const_reference);

    void setName(TString const& name) { name_ = name; }
    virtual void setStatus(TTree&, Bool_t, BranchList const& = BranchList());
    virtual void setAddress(TTree&, BranchList const& = BranchList());
    virtual void book(TTree&, BranchList const& = BranchList());

  protected:
    PhotonCollection(TString const&, Bool_t);

  public:
    Float_t chIso[NMAX]{};
    Float_t nhIso[NMAX]{};
    Float_t phIso[NMAX]{};
    Float_t sieie[NMAX]{};
    Float_t hOverE[NMAX]{};
    Int_t matchedGen[NMAX]{};
    Bool_t hadDecay[NMAX]{};
    Bool_t pixelVeto[NMAX]{};
    Bool_t csafeVeto[NMAX]{};
    Bool_t loose[NMAX]{};
    Bool_t medium[NMAX]{};
    Bool_t tight[NMAX]{};
    Bool_t matchHLT165HE10[NMAX]{};
    Bool_t matchHLT175[NMAX]{};
  };

  class LeptonCollection : public ParticleMCollection {
  public:
    typedef simpletree::Lepton value_type;
    typedef value_type& reference;
    typedef value_type const& const_reference;
    typedef flatutils::iterator<Lepton> iterator;
    typedef flatutils::const_iterator<Lepton> const_iterator;

    LeptonCollection(TString const& name = "leptons");
    LeptonCollection(LeptonCollection const&);
    virtual ~LeptonCollection();
    LeptonCollection& operator=(LeptonCollection const&);

    reference at(UInt_t idx);
    const_reference at(UInt_t idx) const;
    reference operator[](UInt_t);
    const_reference operator[](UInt_t) const;
    iterator begin() { return iterator(static_cast<Lepton*>(array_), objSize_); }
    const_iterator begin() const { return const_iterator(static_cast<Lepton*>(array_), objSize_); }
    iterator end() { auto* p(array_); flatutils::shiftAddr(p, size * objSize_); return iterator(static_cast<Lepton*>(p), objSize_); }
    const_iterator end() const { auto* p(array_); flatutils::shiftAddr(p, size * objSize_); return const_iterator(static_cast<Lepton*>(p), objSize_); }
    void push_back(const_reference);

    void setName(TString const& name) { name_ = name; }
    virtual void setStatus(TTree&, Bool_t, BranchList const& = BranchList());
    virtual void setAddress(TTree&, BranchList const& = BranchList());
    virtual void book(TTree&, BranchList const& = BranchList());

  protected:
    LeptonCollection(TString const&, Bool_t);

  public:
    Int_t matchedGen[NMAX]{};
    Bool_t tauDecay[NMAX]{};
    Bool_t hadDecay[NMAX]{};
    Bool_t positive[NMAX]{};
    Bool_t loose[NMAX]{};
    Bool_t tight[NMAX]{};
  };

  class ElectronCollection : public LeptonCollection {
  public:
    typedef simpletree::Electron value_type;
    typedef value_type& reference;
    typedef value_type const& const_reference;
    typedef flatutils::iterator<Electron> iterator;
    typedef flatutils::const_iterator<Electron> const_iterator;

    ElectronCollection(TString const& name = "electrons");
    ElectronCollection(ElectronCollection const&);
    virtual ~ElectronCollection();
    ElectronCollection& operator=(ElectronCollection const&);

    reference at(UInt_t idx);
    const_reference at(UInt_t idx) const;
    reference operator[](UInt_t);
    const_reference operator[](UInt_t) const;
    iterator begin() { return iterator(static_cast<Electron*>(array_), objSize_); }
    const_iterator begin() const { return const_iterator(static_cast<Electron*>(array_), objSize_); }
    iterator end() { auto* p(array_); flatutils::shiftAddr(p, size * objSize_); return iterator(static_cast<Electron*>(p), objSize_); }
    const_iterator end() const { auto* p(array_); flatutils::shiftAddr(p, size * objSize_); return const_iterator(static_cast<Electron*>(p), objSize_); }
    void push_back(const_reference);

    void setName(TString const& name) { name_ = name; }
    virtual void setStatus(TTree&, Bool_t, BranchList const& = BranchList());
    virtual void setAddress(TTree&, BranchList const& = BranchList());
    virtual void book(TTree&, BranchList const& = BranchList());

  protected:
    ElectronCollection(TString const&, Bool_t);

  public:
    Float_t chIsoPh[NMAX]{};
    Float_t nhIsoPh[NMAX]{};
    Float_t phIsoPh[NMAX]{};
    Float_t sieie[NMAX]{};
    Float_t hOverE[NMAX]{};
    Bool_t matchHLT23Loose[NMAX]{};
    Bool_t matchHLT27Loose[NMAX]{};
  };

  class MuonCollection : public LeptonCollection {
  public:
    typedef simpletree::Muon value_type;
    typedef value_type& reference;
    typedef value_type const& const_reference;
    typedef flatutils::iterator<Muon> iterator;
    typedef flatutils::const_iterator<Muon> const_iterator;

    MuonCollection(TString const& name = "muons");
    MuonCollection(MuonCollection const&);
    virtual ~MuonCollection();
    MuonCollection& operator=(MuonCollection const&);

    reference at(UInt_t idx);
    const_reference at(UInt_t idx) const;
    reference operator[](UInt_t);
    const_reference operator[](UInt_t) const;
    iterator begin() { return iterator(static_cast<Muon*>(array_), objSize_); }
    const_iterator begin() const { return const_iterator(static_cast<Muon*>(array_), objSize_); }
    iterator end() { auto* p(array_); flatutils::shiftAddr(p, size * objSize_); return iterator(static_cast<Muon*>(p), objSize_); }
    const_iterator end() const { auto* p(array_); flatutils::shiftAddr(p, size * objSize_); return const_iterator(static_cast<Muon*>(p), objSize_); }
    void push_back(const_reference);

    void setName(TString const& name) { name_ = name; }
    virtual void setStatus(TTree&, Bool_t, BranchList const& = BranchList());
    virtual void setAddress(TTree&, BranchList const& = BranchList());
    virtual void book(TTree&, BranchList const& = BranchList());

  protected:
    MuonCollection(TString const&, Bool_t);

  public:
    Bool_t matchHLT24[NMAX]{};
    Bool_t matchHLT27[NMAX]{};
  };

  class HLTCollection {
  public:
    static UInt_t const NMAX = 8;
    static UInt_t const size = NMAX;
    typedef simpletree::HLT value_type;
    typedef value_type& reference;
    typedef value_type const& const_reference;
    typedef flatutils::iterator<HLT> iterator;
    typedef flatutils::const_iterator<HLT> const_iterator;

    HLTCollection(TString const& name = "hlts");
    HLTCollection(HLTCollection const&);
    virtual ~HLTCollection();
    HLTCollection& operator=(HLTCollection const&);

    reference at(UInt_t idx);
    const_reference at(UInt_t idx) const;
    reference operator[](UInt_t);
    const_reference operator[](UInt_t) const;
    iterator begin() { return iterator(static_cast<HLT*>(array_), objSize_); }
    const_iterator begin() const { return const_iterator(static_cast<HLT*>(array_), objSize_); }
    iterator end() { auto* p(array_); flatutils::shiftAddr(p, size * objSize_); return iterator(static_cast<HLT*>(p), objSize_); }
    const_iterator end() const { auto* p(array_); flatutils::shiftAddr(p, size * objSize_); return const_iterator(static_cast<HLT*>(p), objSize_); }

    void setName(TString const& name) { name_ = name; }
    virtual void setStatus(TTree&, Bool_t, BranchList const& = BranchList());
    virtual void setAddress(TTree&, BranchList const& = BranchList());
    virtual void book(TTree&, BranchList const& = BranchList());

  protected:
    HLTCollection(TString const&, Bool_t);
    TString name_;
    UInt_t objSize_{0};
    value_type* array_{0};

  public:
    Bool_t pass[NMAX]{};
  };

}
#endif
