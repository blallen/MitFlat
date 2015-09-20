#ifndef Objects_simpletree_h
#define Objects_simpletree_h
#include "Utils.h"
#include "Math/GenVector/LorentzVector.h"
#include "Math/GenVector/PtEtaPhiM4D.h"
#include "TVector2.h"
#include "TString.h"
#include "Rtypes.h"
class TTree;

namespace simpletree {

  typedef ROOT::Math::LorentzVector<ROOT::Math::PtEtaPhiM4D<double>> LorentzVectorM;

  enum HLTPath {
    kPhoton120,
    kPhoton165HE10,
    kPhoton175,
    kEle23Loose,
    kEle27Loose,
    kMu24,
    kMu27,
    kMETNoMu90MHTNoMu90,
    kMETNoMu120MHTNoMu120,
    nHLTPaths
  };

  class Particle {
  public:
    struct array_data {
      static UInt_t const NMAX{256};

      Float_t pt[NMAX]{};
      Float_t eta[NMAX]{};
      Float_t phi[NMAX]{};

      void setStatus(TTree&, TString const&, Bool_t, flatutils::BranchList const& = {"*"});
      void setAddress(TTree&, TString const&, flatutils::BranchList const& = {"*"});
      void book(TTree&, TString const&, flatutils::BranchList const& = {"*"});
    };

    Particle(array_data&, UInt_t idx);
    Particle(Particle const&);
    virtual ~Particle() {}
    Particle& operator=(Particle const&);

    virtual LorentzVectorM p4() const { return LorentzVectorM(pt, eta, phi, 0.); }

  public:
    Float_t& pt;
    Float_t& eta;
    Float_t& phi;
  };

  class ParticleM : public Particle {
  public:
    struct array_data : public Particle::array_data {
      Float_t mass[NMAX]{};

      void setStatus(TTree&, TString const&, Bool_t, flatutils::BranchList const& = {"*"});
      void setAddress(TTree&, TString const&, flatutils::BranchList const& = {"*"});
      void book(TTree&, TString const&, flatutils::BranchList const& = {"*"});
    };

    ParticleM(array_data&, UInt_t idx);
    ParticleM(ParticleM const&);
    virtual ~ParticleM() {}
    ParticleM& operator=(ParticleM const&);

    LorentzVectorM p4() const { return LorentzVectorM(pt, eta, phi, mass); }

  public:
    Float_t& mass;
  };

  class Jet : public ParticleM {
  public:
    struct array_data : public ParticleM::array_data {
    };

    Jet(array_data&, UInt_t idx);
    Jet(Jet const&);
    virtual ~Jet() {}
    Jet& operator=(Jet const&);
  };

  class Met {
  public:
    Met(TString const& name) : name_(name) {}
    Met(Met const&);
    virtual ~Met() {}
    Met& operator=(Met const&);

    void setName(TString const& name) { name_ = name; }
    virtual void setStatus(TTree&, Bool_t, flatutils::BranchList const& = {"*"});
    virtual void setAddress(TTree&, flatutils::BranchList const& = {"*"});
    virtual void book(TTree&, flatutils::BranchList const& = {"*"});

    TVector2 v() const { TVector2 vec; vec.SetMagPhi(met, phi); return vec; }

  protected:
    TString name_;

  public:
    Float_t met{};
    Float_t phi{};
    Float_t sumEt{};
  };

  class Photon : public Particle {
  public:
    struct array_data : public Particle::array_data {
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

      void setStatus(TTree&, TString const&, Bool_t, flatutils::BranchList const& = {"*"});
      void setAddress(TTree&, TString const&, flatutils::BranchList const& = {"*"});
      void book(TTree&, TString const&, flatutils::BranchList const& = {"*"});
    };

    Photon(array_data&, UInt_t idx);
    Photon(Photon const&);
    virtual ~Photon() {}
    Photon& operator=(Photon const&);

  public:
    Float_t& chIso;
    Float_t& nhIso;
    Float_t& phIso;
    Float_t& sieie;
    Float_t& hOverE;
    Int_t& matchedGen;
    Bool_t& hadDecay;
    Bool_t& pixelVeto;
    Bool_t& csafeVeto;
    Bool_t& loose;
    Bool_t& medium;
    Bool_t& tight;
    Bool_t& matchHLT120;
    Bool_t& matchHLT165HE10;
    Bool_t& matchHLT175;
  };

  class Lepton : public ParticleM {
  public:
    struct array_data : public ParticleM::array_data {
      Int_t matchedGen[NMAX]{};
      Bool_t tauDecay[NMAX]{};
      Bool_t hadDecay[NMAX]{};
      Bool_t positive[NMAX]{};
      Bool_t loose[NMAX]{};
      Bool_t tight[NMAX]{};

      void setStatus(TTree&, TString const&, Bool_t, flatutils::BranchList const& = {"*"});
      void setAddress(TTree&, TString const&, flatutils::BranchList const& = {"*"});
      void book(TTree&, TString const&, flatutils::BranchList const& = {"*"});
    };

    Lepton(array_data&, UInt_t idx);
    Lepton(Lepton const&);
    virtual ~Lepton() {}
    Lepton& operator=(Lepton const&);

    int charge() const { return positive ? 1 : -1; }

  public:
    Int_t& matchedGen;
    Bool_t& tauDecay;
    Bool_t& hadDecay;
    Bool_t& positive;
    Bool_t& loose;
    Bool_t& tight;
  };

  class Electron : public Lepton {
  public:
    struct array_data : public Lepton::array_data {
      Float_t chIsoPh[NMAX]{};
      Float_t nhIsoPh[NMAX]{};
      Float_t phIsoPh[NMAX]{};
      Float_t sieie[NMAX]{};
      Float_t hOverE[NMAX]{};
      Bool_t matchHLT23Loose[NMAX]{};
      Bool_t matchHLT27Loose[NMAX]{};

      void setStatus(TTree&, TString const&, Bool_t, flatutils::BranchList const& = {"*"});
      void setAddress(TTree&, TString const&, flatutils::BranchList const& = {"*"});
      void book(TTree&, TString const&, flatutils::BranchList const& = {"*"});
    };

    Electron(array_data&, UInt_t idx);
    Electron(Electron const&);
    virtual ~Electron() {}
    Electron& operator=(Electron const&);

  public:
    Float_t& chIsoPh;
    Float_t& nhIsoPh;
    Float_t& phIsoPh;
    Float_t& sieie;
    Float_t& hOverE;
    Bool_t& matchHLT23Loose;
    Bool_t& matchHLT27Loose;
  };

  class Muon : public Lepton {
  public:
    struct array_data : public Lepton::array_data {
      Bool_t matchHLT24[NMAX]{};
      Bool_t matchHLT27[NMAX]{};

      void setStatus(TTree&, TString const&, Bool_t, flatutils::BranchList const& = {"*"});
      void setAddress(TTree&, TString const&, flatutils::BranchList const& = {"*"});
      void book(TTree&, TString const&, flatutils::BranchList const& = {"*"});
    };

    Muon(array_data&, UInt_t idx);
    Muon(Muon const&);
    virtual ~Muon() {}
    Muon& operator=(Muon const&);

  public:
    Bool_t& matchHLT24;
    Bool_t& matchHLT27;
  };

  class HLT {
  public:
    struct array_data {
      static UInt_t const NMAX{9};

      Bool_t pass[NMAX]{};

      void setStatus(TTree&, TString const&, Bool_t, flatutils::BranchList const& = {"*"});
      void setAddress(TTree&, TString const&, flatutils::BranchList const& = {"*"});
      void book(TTree&, TString const&, flatutils::BranchList const& = {"*"});
    };

    HLT(array_data&, UInt_t idx);
    HLT(HLT const&);
    virtual ~HLT() {}
    HLT& operator=(HLT const&);

  public:
    Bool_t& pass;
  };
}

#endif
