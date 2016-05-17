#ifndef Objects_simpletree_h
#define Objects_simpletree_h
#include "Utils.h"
#include "Math/GenVector/LorentzVector.h"
#include "Math/GenVector/PtEtaPhiM4D.h"
#include "TLorentzVector.h"
#include "TVector2.h"
#include <cmath>
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
    kPhoton50VBF,
    kPhoton75VBF,
    kPhoton90VBF,
    kPhoton120VBF,
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
    virtual void init();

    virtual LorentzVectorM p4() const { return LorentzVectorM(pt, eta, phi, 0.); }
    virtual TLorentzVector p4v() const { TLorentzVector p4; p4.SetPtEtaPhiM(pt, eta, phi, 0.); return p4; }
    double dEta(Particle const& p) const { return eta - p.eta; }
    double dPhi(Particle const& p) const { return TVector2::Phi_mpi_pi(phi - p.phi); }
    double dR2(Particle const& p) const { double d1(dEta(p)); double d2(dPhi(p)); return d1 * d1 + d2 * d2; }
    double dR(Particle const& p) const { return std::sqrt(dR2(p)); }

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
    virtual void init();

    LorentzVectorM p4() const override { return LorentzVectorM(pt, eta, phi, mass); }
    TLorentzVector p4v() const { TLorentzVector p4; p4.SetPtEtaPhiM(pt, eta, phi, mass); return p4; }

  public:
    Float_t& mass;
  };

  class Jet : public ParticleM {
  public:
    struct array_data : public ParticleM::array_data {
      Bool_t mjid[NMAX]{};
      Float_t ptRaw[NMAX]{};
      Float_t ptCorrUp[NMAX]{};
      Float_t ptCorrDown[NMAX]{};
      Float_t cisv[NMAX]{};

      void setStatus(TTree&, TString const&, Bool_t, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
      void setAddress(TTree&, TString const&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
      void book(TTree&, TString const&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
    };

    Jet(array_data&, UInt_t idx);
    Jet(Jet const&);
    virtual ~Jet() {}
    Jet& operator=(Jet const&);
    virtual void init();

  public:
    Bool_t& mjid;
    Float_t& ptRaw;
    Float_t& ptCorrUp;
    Float_t& ptCorrDown;
    Float_t& cisv;
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
    virtual void init();

    virtual TVector2 v() const { TVector2 vec; vec.SetMagPhi(met, phi); return vec; }

  protected:
    TString name_;

  public:
    Float_t met{};
    Float_t phi{};
    Float_t sumEt{};
    Float_t et{};
  };

  class CorrectedMet : public Met {
  public:
    CorrectedMet(TString const& name) : Met(name) {}
    CorrectedMet(CorrectedMet const&);
    virtual ~CorrectedMet() {}
    CorrectedMet& operator=(CorrectedMet const&);

    void setName(TString const& name) { name_ = name; }
    virtual void setStatus(TTree&, Bool_t, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
    virtual void setAddress(TTree&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
    virtual void book(TTree&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
    virtual void init();

    virtual TVector2 vCorr(int corr = 0) const { if (corr == 0) return v(); TVector2 vec; switch (corr) { case 1: vec.SetMagPhi(metCorrUp, phiCorrUp); break; case -1: vec.SetMagPhi(metCorrDown, phiCorrDown); break; } return vec; }

  public:
    Float_t metCorrUp{};
    Float_t phiCorrUp{};
    Float_t metCorrDown{};
    Float_t phiCorrDown{};
    Float_t metUnclUp{};
    Float_t phiUnclUp{};
    Float_t metUnclDown{};
    Float_t phiUnclDown{};
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
      Float_t chWorstIso[NMAX]{};
      Float_t chIsoMax[NMAX]{};
      Float_t nhIso[NMAX]{};
      Float_t phIso[NMAX]{};
      Float_t ecalIso[NMAX]{};
      Float_t hcalIso[NMAX]{};
      Float_t sieie[NMAX]{};
      Float_t hOverE[NMAX]{};
      Float_t genIso[NMAX]{};
      Float_t mipEnergy[NMAX]{};
      Float_t mipChi2[NMAX]{};
      Float_t mipSlope[NMAX]{};
      Float_t mipIntercept[NMAX]{};
      UShort_t mipNhitCone[NMAX]{};
      Bool_t mipIsHalo[NMAX]{};
      Float_t e15[NMAX]{};
      Float_t e25[NMAX]{};
      Float_t e33[NMAX]{};
      Float_t e55[NMAX]{};
      Float_t r9[NMAX]{};
      Float_t etaWidth[NMAX]{};
      Float_t phiWidth[NMAX]{};
      Float_t s4[NMAX]{};
      Float_t time[NMAX]{};
      Float_t timeSpan[NMAX]{};
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
      Bool_t matchHLT50VBF[NMAX]{};
      Bool_t matchHLT75VBF[NMAX]{};
      Bool_t matchHLT90VBF[NMAX]{};
      Bool_t matchHLT120VBF[NMAX]{};

      void setStatus(TTree&, TString const&, Bool_t, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
      void setAddress(TTree&, TString const&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
      void book(TTree&, TString const&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
    };

    Photon(array_data&, UInt_t idx);
    Photon(Photon const&);
    virtual ~Photon() {}
    Photon& operator=(Photon const&);
    virtual void init();

    bool passCHIso(UInt_t wp) const { return chIso < chIsoCuts[isEB ? 0 : 1][wp]; }
    bool passNHIso(UInt_t wp) const { return nhIso < nhIsoCuts[isEB ? 0 : 1][wp]; }
    bool passPhIso(UInt_t wp) const { return phIso < phIsoCuts[isEB ? 0 : 1][wp]; }
    bool passSieie(UInt_t wp) const { return sieie < sieieCuts[isEB ? 0 : 1][wp]; }
    bool passHOverE(UInt_t wp) const { return hOverE < hOverECuts[isEB ? 0 : 1][wp]; }

  public:
    Float_t& chIso;
    Float_t& chWorstIso;
    Float_t& chIsoMax;
    Float_t& nhIso;
    Float_t& phIso;
    Float_t& ecalIso;
    Float_t& hcalIso;
    Float_t& sieie;
    Float_t& hOverE;
    Float_t& genIso;
    Float_t& mipEnergy;
    Float_t& mipChi2;
    Float_t& mipSlope;
    Float_t& mipIntercept;
    UShort_t& mipNhitCone;
    Bool_t& mipIsHalo;
    Float_t& e15;
    Float_t& e25;
    Float_t& e33;
    Float_t& e55;
    Float_t& r9;
    Float_t& etaWidth;
    Float_t& phiWidth;
    Float_t& s4;
    Float_t& time;
    Float_t& timeSpan;
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
    Bool_t& matchHLT50VBF;
    Bool_t& matchHLT75VBF;
    Bool_t& matchHLT90VBF;
    Bool_t& matchHLT120VBF;
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
    virtual void init();

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
      Float_t chIso[NMAX]{};
      Float_t nhIso[NMAX]{};
      Float_t phIso[NMAX]{};
      Float_t chIsoPh[NMAX]{};
      Float_t nhIsoPh[NMAX]{};
      Float_t phIsoPh[NMAX]{};
      Float_t ecalIso[NMAX]{};
      Float_t hcalIso[NMAX]{};
      Float_t sieie[NMAX]{};
      Float_t hOverE[NMAX]{};
      Bool_t isEB[NMAX]{};
      Bool_t veto[NMAX]{};
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
    virtual void init();

    bool passCHIsoPh(UInt_t wp) const { return chIsoPh < Photon::chIsoCuts[isEB ? 0 : 1][wp]; }
    bool passNHIsoPh(UInt_t wp) const { return nhIsoPh < Photon::nhIsoCuts[isEB ? 0 : 1][wp]; }
    bool passPhIsoPh(UInt_t wp) const { return phIsoPh < Photon::phIsoCuts[isEB ? 0 : 1][wp]; }
    bool passSieiePh(UInt_t wp) const { return sieie < Photon::sieieCuts[isEB ? 0 : 1][wp]; }
    bool passHOverEPh(UInt_t wp) const { return hOverE < Photon::hOverECuts[isEB ? 0 : 1][wp]; }

  public:
    Float_t& chIso;
    Float_t& nhIso;
    Float_t& phIso;
    Float_t& chIsoPh;
    Float_t& nhIsoPh;
    Float_t& phIsoPh;
    Float_t& ecalIso;
    Float_t& hcalIso;
    Float_t& sieie;
    Float_t& hOverE;
    Bool_t& isEB;
    Bool_t& veto;
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
      Float_t combRelIso[NMAX]{};
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
    virtual void init();

  public:
    Float_t& combRelIso;
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
    virtual void init();

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
    virtual void init();

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
    virtual void init();

  public:
    Int_t& pid;
    UShort_t& ancestor;
  };

  class GenJet : public ParticleM {
  public:
    struct array_data : public ParticleM::array_data {
    };

    GenJet(array_data&, UInt_t idx);
    GenJet(GenJet const&);
    virtual ~GenJet() {}
    GenJet& operator=(GenJet const&);
    virtual void init();
  };

  class HLT {
  public:
    struct array_data {
      static UInt_t const NMAX{17};

      Bool_t pass[NMAX]{};

      void setStatus(TTree&, TString const&, Bool_t, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
      void setAddress(TTree&, TString const&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
      void book(TTree&, TString const&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
    };

    HLT(array_data&, UInt_t idx);
    HLT(HLT const&);
    virtual ~HLT() {}
    HLT& operator=(HLT const&);
    virtual void init();

  public:
    Bool_t& pass;
  };

  class MetFilters {
  public:
    MetFilters(TString const& name) : name_(name) {}
    MetFilters(MetFilters const&);
    virtual ~MetFilters() {}
    MetFilters& operator=(MetFilters const&);

    void setName(TString const& name) { name_ = name; }
    virtual void setStatus(TTree&, Bool_t, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
    virtual void setAddress(TTree&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
    virtual void book(TTree&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
    virtual void init();

    virtual bool pass() const { return !cschalo && !hbhe && !hbheIso && !badsc && !badTrack && !badMuonTrack; }

  protected:
    TString name_;

  public:
    Bool_t cschalo{};
    Bool_t hbhe{};
    Bool_t hbheIso{};
    Bool_t badsc{};
    Bool_t badTrack{};
    Bool_t badMuonTrack{};
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
    virtual void init();

  public:
    Float_t& scale;
  };
}

#endif
