#ifndef Objects_simpletree_h
#define Objects_simpletree_h
#include "MitFlat/DataFormats/interface/Utils.h"
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
    kPhoton135MET100,
    kPhoton165HE10,
    kPhoton175,
    kEle23Loose,
    kEle27Loose,
    kMu20,
    kTrkMu20,
    kMu24eta2p1,
    kMu27,
    kMET170,
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

      void setStatus(TTree&, TString const&, Bool_t, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
      void setAddress(TTree&, TString const&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
      void book(TTree&, TString const&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
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

      void setStatus(TTree&, TString const&, Bool_t, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
      void setAddress(TTree&, TString const&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
      void book(TTree&, TString const&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
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
    virtual void setStatus(TTree&, Bool_t, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
    virtual void setAddress(TTree&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
    virtual void book(TTree&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);

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
    static double const chIsoCuts[2][3];
    static double const nhIsoCuts[2][3];
    static double const phIsoCuts[2][3];
    static double const sieieCuts[2][3];
    static double const hOverECuts[2][3];

    struct array_data : public Particle::array_data {
      Float_t chIso[NMAX]{};
      Float_t nhIso[NMAX]{};
      Float_t phIso[NMAX]{};
      Float_t sieie[NMAX]{};
      Float_t hOverE[NMAX]{};
      Float_t genIso[NMAX]{};
      Int_t matchedGen[NMAX]{};
      Bool_t isEB[NMAX]{};
      Bool_t pixelVeto[NMAX]{};
      Bool_t electronVeto[NMAX]{};
      Bool_t csafeVeto[NMAX]{};
      Bool_t loose[NMAX]{};
      Bool_t medium[NMAX]{};
      Bool_t tight[NMAX]{};
      Bool_t highpt[NMAX]{};
      Bool_t matchHLT120[NMAX]{};
      Bool_t matchHLT135MET100[NMAX]{};
      Bool_t matchHLT165HE10[NMAX]{};
      Bool_t matchHLT175[NMAX]{};

      void setStatus(TTree&, TString const&, Bool_t, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
      void setAddress(TTree&, TString const&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
      void book(TTree&, TString const&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
    };

    Photon(array_data&, UInt_t idx);
    Photon(Photon const&);
    virtual ~Photon() {}
    Photon& operator=(Photon const&);

    bool passCHIso(UInt_t wp) const { return chIso < chIsoCuts[isEB ? 0 : 1][wp]; }
    bool passNHIso(UInt_t wp) const { return nhIso < nhIsoCuts[isEB ? 0 : 1][wp]; }
    bool passPhIso(UInt_t wp) const { return phIso < phIsoCuts[isEB ? 0 : 1][wp]; }
    bool passSieie(UInt_t wp) const { return sieie < sieieCuts[isEB ? 0 : 1][wp]; }
    bool passHOverE(UInt_t wp) const { return hOverE < hOverECuts[isEB ? 0 : 1][wp]; }

  public:
    Float_t& chIso;
    Float_t& nhIso;
    Float_t& phIso;
    Float_t& sieie;
    Float_t& hOverE;
    Float_t& genIso;
    Int_t& matchedGen;
    Bool_t& isEB;
    Bool_t& pixelVeto;
    Bool_t& electronVeto;
    Bool_t& csafeVeto;
    Bool_t& loose;
    Bool_t& medium;
    Bool_t& tight;
    Bool_t& highpt;
    Bool_t& matchHLT120;
    Bool_t& matchHLT135MET100;
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

      void setStatus(TTree&, TString const&, Bool_t, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
      void setAddress(TTree&, TString const&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
      void book(TTree&, TString const&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
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
      Bool_t isEB[NMAX]{};
      Bool_t matchHLT23Loose[NMAX]{};
      Bool_t matchHLT27Loose[NMAX]{};
      Bool_t matchHLT120Ph[NMAX]{};
      Bool_t matchHLT135MET100Ph[NMAX]{};
      Bool_t matchHLT165HE10Ph[NMAX]{};
      Bool_t matchHLT175Ph[NMAX]{};

      void setStatus(TTree&, TString const&, Bool_t, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
      void setAddress(TTree&, TString const&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
      void book(TTree&, TString const&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
    };

    Electron(array_data&, UInt_t idx);
    Electron(Electron const&);
    virtual ~Electron() {}
    Electron& operator=(Electron const&);

    bool passCHIsoPh(UInt_t wp) const { return chIsoPh < Photon::chIsoCuts[isEB ? 0 : 1][wp]; }
    bool passNHIsoPh(UInt_t wp) const { return nhIsoPh < Photon::nhIsoCuts[isEB ? 0 : 1][wp]; }
    bool passPhIsoPh(UInt_t wp) const { return phIsoPh < Photon::phIsoCuts[isEB ? 0 : 1][wp]; }
    bool passSieiePh(UInt_t wp) const { return sieie < Photon::sieieCuts[isEB ? 0 : 1][wp]; }
    bool passHOverEPh(UInt_t wp) const { return hOverE < Photon::hOverECuts[isEB ? 0 : 1][wp]; }

  public:
    Float_t& chIsoPh;
    Float_t& nhIsoPh;
    Float_t& phIsoPh;
    Float_t& sieie;
    Float_t& hOverE;
    Bool_t& isEB;
    Bool_t& matchHLT23Loose;
    Bool_t& matchHLT27Loose;
    Bool_t& matchHLT120Ph;
    Bool_t& matchHLT135MET100Ph;
    Bool_t& matchHLT165HE10Ph;
    Bool_t& matchHLT175Ph;
  };

  class Muon : public Lepton {
  public:
    struct array_data : public Lepton::array_data {
      Bool_t matchHLT20[NMAX]{};
      Bool_t matchHLTTrk20[NMAX]{};
      Bool_t matchHLT24[NMAX]{};
      Bool_t matchHLT27[NMAX]{};

      void setStatus(TTree&, TString const&, Bool_t, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
      void setAddress(TTree&, TString const&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
      void book(TTree&, TString const&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
    };

    Muon(array_data&, UInt_t idx);
    Muon(Muon const&);
    virtual ~Muon() {}
    Muon& operator=(Muon const&);

  public:
    Bool_t& matchHLT20;
    Bool_t& matchHLTTrk20;
    Bool_t& matchHLT24;
    Bool_t& matchHLT27;
  };

  class Tau : public ParticleM {
  public:
    struct array_data : public ParticleM::array_data {
      Bool_t decayMode[NMAX]{};
      Float_t combIso[NMAX]{};

      void setStatus(TTree&, TString const&, Bool_t, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
      void setAddress(TTree&, TString const&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
      void book(TTree&, TString const&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
    };

    Tau(array_data&, UInt_t idx);
    Tau(Tau const&);
    virtual ~Tau() {}
    Tau& operator=(Tau const&);

  public:
    Bool_t& decayMode;
    Float_t& combIso;
  };

  class Parton : public ParticleM {
  public:
    struct array_data : public ParticleM::array_data {
      Int_t pid[NMAX]{};
      Short_t status[NMAX]{};
      Bool_t frixIso[NMAX]{};

      void setStatus(TTree&, TString const&, Bool_t, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
      void setAddress(TTree&, TString const&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
      void book(TTree&, TString const&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
    };

    Parton(array_data&, UInt_t idx);
    Parton(Parton const&);
    virtual ~Parton() {}
    Parton& operator=(Parton const&);

  public:
    Int_t& pid;
    Short_t& status;
    Bool_t& frixIso;
  };

  class MCParticle : public ParticleM {
  public:
    struct array_data : public ParticleM::array_data {
      Int_t pid[NMAX]{};
      UShort_t ancestor[NMAX]{};

      void setStatus(TTree&, TString const&, Bool_t, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
      void setAddress(TTree&, TString const&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
      void book(TTree&, TString const&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
    };

    MCParticle(array_data&, UInt_t idx);
    MCParticle(MCParticle const&);
    virtual ~MCParticle() {}
    MCParticle& operator=(MCParticle const&);

  public:
    Int_t& pid;
    UShort_t& ancestor;
  };

  class GenJet : public Jet {
  public:
    struct array_data : public Jet::array_data {
    };

    GenJet(array_data&, UInt_t idx);
    GenJet(GenJet const&);
    virtual ~GenJet() {}
    GenJet& operator=(GenJet const&);
  };

  class HLT {
  public:
    struct array_data {
      static UInt_t const NMAX{13};

      Bool_t pass[NMAX]{};

      void setStatus(TTree&, TString const&, Bool_t, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
      void setAddress(TTree&, TString const&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
      void book(TTree&, TString const&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
    };

    HLT(array_data&, UInt_t idx);
    HLT(HLT const&);
    virtual ~HLT() {}
    HLT& operator=(HLT const&);

  public:
    Bool_t& pass;
  };

  class ReweightScale {
  public:
    struct array_data {
      static UInt_t const NMAX{256};

      Float_t scale[NMAX]{};

      void setStatus(TTree&, TString const&, Bool_t, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
      void setAddress(TTree&, TString const&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
      void book(TTree&, TString const&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
    };

    ReweightScale(array_data&, UInt_t idx);
    ReweightScale(ReweightScale const&);
    virtual ~ReweightScale() {}
    ReweightScale& operator=(ReweightScale const&);

  public:
    Float_t& scale;
  };
}

#endif
