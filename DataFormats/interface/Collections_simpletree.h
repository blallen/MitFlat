#ifndef Collections_simpletree_h
#define Collections_simpletree_h
#include "MitFlat/DataFormats/interface/Objects_simpletree.h"
#include "MitFlat/DataFormats/interface/Utils.h"

class TTree;

namespace simpletree {

  class ParticleCollection {
  public:
    static UInt_t const NMAX = 256;
    typedef ParticleCollection self_type;
    typedef ParticleCollection container_type;
    typedef Particle value_type;
    typedef value_type* pointer;
    typedef value_type const* const_pointer;
    typedef value_type& reference;
    typedef value_type const& const_reference;
    typedef flatutils::iterator<container_type> iterator;
    typedef flatutils::const_iterator<container_type> const_iterator;

    ParticleCollection(TString const& name = "particles");
    ParticleCollection(ParticleCollection const&);
    virtual ~ParticleCollection();
    ParticleCollection& operator=(self_type const&);

    reference at(UInt_t idx);
    const_reference at(UInt_t idx) const;
    reference operator[](UInt_t);
    const_reference operator[](UInt_t) const;
    iterator begin() { return iterator(array_, objSize_); }
    const_iterator begin() const { return const_iterator(array_, objSize_); }
    iterator end() { return flatutils::end<container_type>(array_, objSize_, size); }
    const_iterator end() const { return flatutils::cend<container_type>(array_, objSize_, size); }
    void push_back(const_reference);
    void clear() { resize(0); }
    void resize(UInt_t size);

    void setName(TString const& name) { name_ = name; }
    virtual void setStatus(TTree&, Bool_t, flatutils::BranchList const& = {"*"});
    virtual void setAddress(TTree&, flatutils::BranchList const& = {"*"});
    virtual void book(TTree&, flatutils::BranchList const& = {"*"});

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
    typedef ParticleMCollection self_type;
    typedef ParticleMCollection container_type;
    typedef ParticleM value_type;
    typedef value_type* pointer;
    typedef value_type const* const_pointer;
    typedef value_type& reference;
    typedef value_type const& const_reference;
    typedef flatutils::iterator<container_type> iterator;
    typedef flatutils::const_iterator<container_type> const_iterator;

    ParticleMCollection(TString const& name = "particlems");
    ParticleMCollection(ParticleMCollection const&);
    virtual ~ParticleMCollection();
    ParticleMCollection& operator=(self_type const&);

    reference at(UInt_t idx);
    const_reference at(UInt_t idx) const;
    reference operator[](UInt_t);
    const_reference operator[](UInt_t) const;
    iterator begin() { return iterator(array_, objSize_); }
    const_iterator begin() const { return const_iterator(array_, objSize_); }
    iterator end() { return flatutils::end<container_type>(array_, objSize_, size); }
    const_iterator end() const { return flatutils::cend<container_type>(array_, objSize_, size); }
    void push_back(const_reference);

    void setName(TString const& name) { name_ = name; }
    virtual void setStatus(TTree&, Bool_t, flatutils::BranchList const& = {"*"});
    virtual void setAddress(TTree&, flatutils::BranchList const& = {"*"});
    virtual void book(TTree&, flatutils::BranchList const& = {"*"});

  protected:
    ParticleMCollection(TString const&, Bool_t);

  public:
    Float_t mass[NMAX]{};
  };

  class JetCollection : public ParticleMCollection {
  public:
    typedef JetCollection self_type;
    typedef JetCollection container_type;
    typedef Jet value_type;
    typedef value_type* pointer;
    typedef value_type const* const_pointer;
    typedef value_type& reference;
    typedef value_type const& const_reference;
    typedef flatutils::iterator<container_type> iterator;
    typedef flatutils::const_iterator<container_type> const_iterator;

    JetCollection(TString const& name = "jets");
    JetCollection(JetCollection const&);
    virtual ~JetCollection();
    JetCollection& operator=(self_type const&);

    reference at(UInt_t idx);
    const_reference at(UInt_t idx) const;
    reference operator[](UInt_t);
    const_reference operator[](UInt_t) const;
    iterator begin() { return iterator(array_, objSize_); }
    const_iterator begin() const { return const_iterator(array_, objSize_); }
    iterator end() { return flatutils::end<container_type>(array_, objSize_, size); }
    const_iterator end() const { return flatutils::cend<container_type>(array_, objSize_, size); }
    void push_back(const_reference);

    void setName(TString const& name) { name_ = name; }
    virtual void setStatus(TTree&, Bool_t, flatutils::BranchList const& = {"*"});
    virtual void setAddress(TTree&, flatutils::BranchList const& = {"*"});
    virtual void book(TTree&, flatutils::BranchList const& = {"*"});

  protected:
    JetCollection(TString const&, Bool_t);
  };

  class PhotonCollection : public ParticleCollection {
  public:
    typedef PhotonCollection self_type;
    typedef PhotonCollection container_type;
    typedef Photon value_type;
    typedef value_type* pointer;
    typedef value_type const* const_pointer;
    typedef value_type& reference;
    typedef value_type const& const_reference;
    typedef flatutils::iterator<container_type> iterator;
    typedef flatutils::const_iterator<container_type> const_iterator;

    PhotonCollection(TString const& name = "photons");
    PhotonCollection(PhotonCollection const&);
    virtual ~PhotonCollection();
    PhotonCollection& operator=(self_type const&);

    reference at(UInt_t idx);
    const_reference at(UInt_t idx) const;
    reference operator[](UInt_t);
    const_reference operator[](UInt_t) const;
    iterator begin() { return iterator(array_, objSize_); }
    const_iterator begin() const { return const_iterator(array_, objSize_); }
    iterator end() { return flatutils::end<container_type>(array_, objSize_, size); }
    const_iterator end() const { return flatutils::cend<container_type>(array_, objSize_, size); }
    void push_back(const_reference);

    void setName(TString const& name) { name_ = name; }
    virtual void setStatus(TTree&, Bool_t, flatutils::BranchList const& = {"*"});
    virtual void setAddress(TTree&, flatutils::BranchList const& = {"*"});
    virtual void book(TTree&, flatutils::BranchList const& = {"*"});

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
    Bool_t matchHLT120[NMAX]{};
    Bool_t matchHLT165HE10[NMAX]{};
    Bool_t matchHLT175[NMAX]{};
  };

  class LeptonCollection : public ParticleMCollection {
  public:
    typedef LeptonCollection self_type;
    typedef LeptonCollection container_type;
    typedef Lepton value_type;
    typedef value_type* pointer;
    typedef value_type const* const_pointer;
    typedef value_type& reference;
    typedef value_type const& const_reference;
    typedef flatutils::iterator<container_type> iterator;
    typedef flatutils::const_iterator<container_type> const_iterator;

    LeptonCollection(TString const& name = "leptons");
    LeptonCollection(LeptonCollection const&);
    virtual ~LeptonCollection();
    LeptonCollection& operator=(self_type const&);

    reference at(UInt_t idx);
    const_reference at(UInt_t idx) const;
    reference operator[](UInt_t);
    const_reference operator[](UInt_t) const;
    iterator begin() { return iterator(array_, objSize_); }
    const_iterator begin() const { return const_iterator(array_, objSize_); }
    iterator end() { return flatutils::end<container_type>(array_, objSize_, size); }
    const_iterator end() const { return flatutils::cend<container_type>(array_, objSize_, size); }
    void push_back(const_reference);

    void setName(TString const& name) { name_ = name; }
    virtual void setStatus(TTree&, Bool_t, flatutils::BranchList const& = {"*"});
    virtual void setAddress(TTree&, flatutils::BranchList const& = {"*"});
    virtual void book(TTree&, flatutils::BranchList const& = {"*"});

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
    typedef ElectronCollection self_type;
    typedef ElectronCollection container_type;
    typedef Electron value_type;
    typedef value_type* pointer;
    typedef value_type const* const_pointer;
    typedef value_type& reference;
    typedef value_type const& const_reference;
    typedef flatutils::iterator<container_type> iterator;
    typedef flatutils::const_iterator<container_type> const_iterator;

    ElectronCollection(TString const& name = "electrons");
    ElectronCollection(ElectronCollection const&);
    virtual ~ElectronCollection();
    ElectronCollection& operator=(self_type const&);

    reference at(UInt_t idx);
    const_reference at(UInt_t idx) const;
    reference operator[](UInt_t);
    const_reference operator[](UInt_t) const;
    iterator begin() { return iterator(array_, objSize_); }
    const_iterator begin() const { return const_iterator(array_, objSize_); }
    iterator end() { return flatutils::end<container_type>(array_, objSize_, size); }
    const_iterator end() const { return flatutils::cend<container_type>(array_, objSize_, size); }
    void push_back(const_reference);

    void setName(TString const& name) { name_ = name; }
    virtual void setStatus(TTree&, Bool_t, flatutils::BranchList const& = {"*"});
    virtual void setAddress(TTree&, flatutils::BranchList const& = {"*"});
    virtual void book(TTree&, flatutils::BranchList const& = {"*"});

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
    typedef MuonCollection self_type;
    typedef MuonCollection container_type;
    typedef Muon value_type;
    typedef value_type* pointer;
    typedef value_type const* const_pointer;
    typedef value_type& reference;
    typedef value_type const& const_reference;
    typedef flatutils::iterator<container_type> iterator;
    typedef flatutils::const_iterator<container_type> const_iterator;

    MuonCollection(TString const& name = "muons");
    MuonCollection(MuonCollection const&);
    virtual ~MuonCollection();
    MuonCollection& operator=(self_type const&);

    reference at(UInt_t idx);
    const_reference at(UInt_t idx) const;
    reference operator[](UInt_t);
    const_reference operator[](UInt_t) const;
    iterator begin() { return iterator(array_, objSize_); }
    const_iterator begin() const { return const_iterator(array_, objSize_); }
    iterator end() { return flatutils::end<container_type>(array_, objSize_, size); }
    const_iterator end() const { return flatutils::cend<container_type>(array_, objSize_, size); }
    void push_back(const_reference);

    void setName(TString const& name) { name_ = name; }
    virtual void setStatus(TTree&, Bool_t, flatutils::BranchList const& = {"*"});
    virtual void setAddress(TTree&, flatutils::BranchList const& = {"*"});
    virtual void book(TTree&, flatutils::BranchList const& = {"*"});

  protected:
    MuonCollection(TString const&, Bool_t);

  public:
    Bool_t matchHLT24[NMAX]{};
    Bool_t matchHLT27[NMAX]{};
  };

  class HLTCollection {
  public:
    static UInt_t const NMAX = 9;
    static UInt_t const size = NMAX;
    typedef HLTCollection self_type;
    typedef HLTCollection container_type;
    typedef HLT value_type;
    typedef value_type* pointer;
    typedef value_type const* const_pointer;
    typedef value_type& reference;
    typedef value_type const& const_reference;
    typedef flatutils::iterator<container_type> iterator;
    typedef flatutils::const_iterator<container_type> const_iterator;

    HLTCollection(TString const& name = "hlts");
    HLTCollection(HLTCollection const&);
    virtual ~HLTCollection();
    HLTCollection& operator=(self_type const&);

    reference at(UInt_t idx);
    const_reference at(UInt_t idx) const;
    reference operator[](UInt_t);
    const_reference operator[](UInt_t) const;
    iterator begin() { return iterator(array_, objSize_); }
    const_iterator begin() const { return const_iterator(array_, objSize_); }
    iterator end() { return flatutils::end<container_type>(array_, objSize_, size); }
    const_iterator end() const { return flatutils::cend<container_type>(array_, objSize_, size); }

    void setName(TString const& name) { name_ = name; }
    virtual void setStatus(TTree&, Bool_t, flatutils::BranchList const& = {"*"});
    virtual void setAddress(TTree&, flatutils::BranchList const& = {"*"});
    virtual void book(TTree&, flatutils::BranchList const& = {"*"});

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
