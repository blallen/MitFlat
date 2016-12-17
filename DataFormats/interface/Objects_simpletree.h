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
#include <memory>
#include <set>
#include <utility>
class TTree;

namespace simpletree {

  typedef std::pair<unsigned, unsigned> SinglesPos;
  typedef ROOT::Math::LorentzVector<ROOT::Math::PtEtaPhiM4D<double>> LorentzVectorM;

  enum PhotonL1Object {
    fSEG34IorSEG40,
    fSEG40IorSJet200,
    fSEG34IorSEG40IorSJet200,
    fSEG24,
    fSEG30,
    fSEG40,
    nPhotonL1Objects
  };

  extern TString PhotonL1ObjectName[nPhotonL1Objects];

  enum PhotonHLTObject {
    fPh120,
    fPh135,
    fPh165HE10,
    fPh175,
    fPh22EBR9Iso,
    fPh36EBR9Iso,
    fPh50EBR9Iso,
    fPh75EBR9Iso,
    fPh90EBR9Iso,
    fPh120EBR9Iso,
    nPhotonHLTObjects
  };

  extern TString PhotonHLTObjectName[nPhotonHLTObjects];

  enum ElectronHLTObject {
    fEl27ERLoose,
    fEl27Tight,
    fEl120Ph,
    fEl135Ph,
    fEl165HE10Ph,
    fEl175Ph,
    fEl22EBR9IsoPh,
    fEl36EBR9IsoPh,
    fEl50EBR9IsoPh,
    fEl75EBR9IsoPh,
    fEl90EBR9IsoPh,
    fEl120EBR9IsoPh,
    nElectronHLTObjects
  };

  extern TString ElectronHLTObjectName[nElectronHLTObjects];

  enum MuonHLTObject {
    fMu20,
    fMuTrk20,
    fMu24,
    fMu27,
    nMuonHLTObjects
  };

  extern TString MuonHLTObjectName[nMuonHLTObjects];

  unsigned const nMaxHLTObjects(nElectronHLTObjects);

  class Particle {
  public:
    struct array_data {
      static UInt_t const NMAX{256};

      array_data();

      Float_t pt[NMAX]{};
      Float_t eta[NMAX]{};
      Float_t phi[NMAX]{};

      void setStatus(TTree&, TString const&, Bool_t, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
      void setAddress(TTree&, TString const&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
      void book(TTree&, TString const&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
    };

    Particle();
    Particle(array_data&, UInt_t idx);
    Particle(Particle const&);
    virtual ~Particle();
    Particle& operator=(Particle const&);
    virtual void setStatus(TTree&, TString const&, Bool_t, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
    virtual void setAddress(TTree&, TString const&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
    virtual void book(TTree&, TString const&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
    virtual void init();

    LorentzVectorM p4() const { return LorentzVectorM(pt, eta, phi, m()); }
    TLorentzVector p4v() const { TLorentzVector p4; p4.SetPtEtaPhiM(pt, eta, phi, m()); return p4; }
    virtual double e() const { return pt * std::cosh(eta); }
    double p() const { return pt * std::cosh(eta); }
    double px() const { return pt * std::cos(phi); }
    double py() const { return pt * std::sin(phi); }
    double pz() const { return pt * std::sinh(eta); }
    virtual double m() const { return 0.; }
    double dEta(Particle const& p) const { return eta - p.eta; }
    double dPhi(Particle const& p) const { return TVector2::Phi_mpi_pi(phi - p.phi); }
    double dR2(Particle const& p) const { double d1(dEta(p)); double d2(dPhi(p)); return d1 * d1 + d2 * d2; }
    double dR(Particle const& p) const { return std::sqrt(dR2(p)); }

  private:
    static std::vector<std::auto_ptr<array_data>> singlesData_;
    static SinglesPos singlesPos_;
    static std::set<SinglesPos> usedSinglesPos_;
    static SinglesPos const& nextSinglesPos_();

  protected:
    SinglesPos pos_{-1, -1};

  public:
    Float_t& pt;
    Float_t& eta;
    Float_t& phi;
  };

  class ParticleM : public Particle {
  public:
    struct array_data : public Particle::array_data {
      array_data();

      Float_t mass[NMAX]{};

      void setStatus(TTree&, TString const&, Bool_t, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
      void setAddress(TTree&, TString const&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
      void book(TTree&, TString const&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
    };

    ParticleM();
    ParticleM(array_data&, UInt_t idx);
    ParticleM(ParticleM const&);
    virtual ~ParticleM();
    ParticleM& operator=(ParticleM const&);
    void setStatus(TTree&, TString const&, Bool_t, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE) override;
    void setAddress(TTree&, TString const&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE) override;
    void book(TTree&, TString const&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE) override;
    void init() override;

    double e() const override { return std::sqrt(std::pow(pt * std::cosh(eta), 2.) + m() * m()); }
    double m() const override { return mass; }

  private:
    static std::vector<std::auto_ptr<array_data>> singlesData_;
    static SinglesPos singlesPos_;
    static std::set<SinglesPos> usedSinglesPos_;
    static SinglesPos const& nextSinglesPos_();

  public:
    Float_t& mass;
  };

  class RecoParticle : public Particle {
  public:
    struct array_data : public Particle::array_data {
      array_data();

      Bool_t loose[NMAX]{};
      Bool_t medium[NMAX]{};
      Bool_t tight[NMAX]{};
      Int_t matchedGen[NMAX]{};
      Bool_t matchHLT[NMAX][nMaxHLTObjects]{};

      void setStatus(TTree&, TString const&, Bool_t, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
      void setAddress(TTree&, TString const&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
      void book(TTree&, TString const&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
    };

    RecoParticle();
    RecoParticle(array_data&, UInt_t idx);
    RecoParticle(RecoParticle const&);
    virtual ~RecoParticle();
    RecoParticle& operator=(RecoParticle const&);
    void setStatus(TTree&, TString const&, Bool_t, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE) override;
    void setAddress(TTree&, TString const&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE) override;
    void book(TTree&, TString const&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE) override;
    void init() override;

  private:
    static std::vector<std::auto_ptr<array_data>> singlesData_;
    static SinglesPos singlesPos_;
    static std::set<SinglesPos> usedSinglesPos_;
    static SinglesPos const& nextSinglesPos_();

  public:
    Bool_t& loose;
    Bool_t& medium;
    Bool_t& tight;
    Int_t& matchedGen;
    Bool_t* matchHLT{0}; //[nMaxHLTObjects]
  };

  class RecoParticleM : public RecoParticle {
  public:
    struct array_data : public RecoParticle::array_data {
      array_data();

      Float_t mass[NMAX]{};

      void setStatus(TTree&, TString const&, Bool_t, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
      void setAddress(TTree&, TString const&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
      void book(TTree&, TString const&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
    };

    RecoParticleM();
    RecoParticleM(array_data&, UInt_t idx);
    RecoParticleM(RecoParticleM const&);
    virtual ~RecoParticleM();
    RecoParticleM& operator=(RecoParticleM const&);
    void setStatus(TTree&, TString const&, Bool_t, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE) override;
    void setAddress(TTree&, TString const&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE) override;
    void book(TTree&, TString const&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE) override;
    void init() override;

    double e() const override { return std::sqrt(std::pow(pt * std::cosh(eta), 2.) + m() * m()); }
    double m() const override { return mass; }

  private:
    static std::vector<std::auto_ptr<array_data>> singlesData_;
    static SinglesPos singlesPos_;
    static std::set<SinglesPos> usedSinglesPos_;
    static SinglesPos const& nextSinglesPos_();

  public:
    Float_t& mass;
  };

  class Photon : public RecoParticle {
  public:
    static double const chIsoCuts[2][3];
    static double const nhIsoCuts[2][3];
    static double const phIsoCuts[2][3];
    static double const sieieCuts[2][3];
    static double const hOverECuts[2][3];

    struct array_data : public RecoParticle::array_data {
      array_data();

      Float_t scRawPt[NMAX]{};
      Float_t chIso[NMAX]{};
      Float_t chWorstIso[NMAX]{};
      Float_t chIsoMax[NMAX]{};
      Float_t nhIso[NMAX]{};
      Float_t phIso[NMAX]{};
      Float_t nhIsoS16[NMAX]{};
      Float_t phIsoS16[NMAX]{};
      Float_t ecalIso[NMAX]{};
      Float_t hcalIso[NMAX]{};
      Float_t sieie[NMAX]{};
      Float_t sipip[NMAX]{};
      Float_t sieip[NMAX]{};
      Float_t hOverE[NMAX]{};
      Float_t genIso[NMAX]{};
      Float_t mipEnergy[NMAX]{};
      Float_t mipChi2[NMAX]{};
      Float_t mipSlope[NMAX]{};
      Float_t mipIntercept[NMAX]{};
      UShort_t mipNhitCone[NMAX]{};
      Bool_t mipIsHalo[NMAX]{};
      Float_t scPt[NMAX]{};
      Float_t scEta[NMAX]{};
      Float_t scPhi[NMAX]{};
      Float_t e13[NMAX]{};
      Float_t e31[NMAX]{};
      Float_t e15[NMAX]{};
      Float_t e22[NMAX]{};
      Float_t e25[NMAX]{};
      Float_t e33[NMAX]{};
      Float_t e44[NMAX]{};
      Float_t e55[NMAX]{};
      Float_t emax[NMAX]{};
      Float_t e2nd[NMAX]{};
      Float_t e4[NMAX]{};
      Float_t r9[NMAX]{};
      Float_t etaWidth[NMAX]{};
      Float_t phiWidth[NMAX]{};
      Float_t time[NMAX]{};
      Float_t timeSpan[NMAX]{};
      Float_t genMatchDR[NMAX]{};
      Bool_t isEB[NMAX]{};
      Bool_t pixelVeto[NMAX]{};
      Bool_t electronVeto[NMAX]{};
      Bool_t csafeVeto[NMAX]{};
      Bool_t highpt[NMAX]{};
      Bool_t matchL1[NMAX][nPhotonL1Objects]{};

      void setStatus(TTree&, TString const&, Bool_t, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
      void setAddress(TTree&, TString const&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
      void book(TTree&, TString const&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
    };

    Photon();
    Photon(array_data&, UInt_t idx);
    Photon(Photon const&);
    virtual ~Photon();
    Photon& operator=(Photon const&);
    void setStatus(TTree&, TString const&, Bool_t, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE) override;
    void setAddress(TTree&, TString const&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE) override;
    void book(TTree&, TString const&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE) override;
    void init() override;

    bool passCHIso(UInt_t wp) const { return chIso < chIsoCuts[isEB ? 0 : 1][wp]; }
    bool passNHIso(UInt_t wp) const { return nhIso < nhIsoCuts[isEB ? 0 : 1][wp]; }
    bool passPhIso(UInt_t wp) const { return phIso < phIsoCuts[isEB ? 0 : 1][wp]; }
    bool passSieie(UInt_t wp) const { return sieie < sieieCuts[isEB ? 0 : 1][wp]; }
    bool passHOverE(UInt_t wp) const { return hOverE < hOverECuts[isEB ? 0 : 1][wp]; }

  private:
    static std::vector<std::auto_ptr<array_data>> singlesData_;
    static SinglesPos singlesPos_;
    static std::set<SinglesPos> usedSinglesPos_;
    static SinglesPos const& nextSinglesPos_();

  public:
    Float_t& scRawPt;
    Float_t& chIso;
    Float_t& chWorstIso;
    Float_t& chIsoMax;
    Float_t& nhIso;
    Float_t& phIso;
    Float_t& nhIsoS16;
    Float_t& phIsoS16;
    Float_t& ecalIso;
    Float_t& hcalIso;
    Float_t& sieie;
    Float_t& sipip;
    Float_t& sieip;
    Float_t& hOverE;
    Float_t& genIso;
    Float_t& mipEnergy;
    Float_t& mipChi2;
    Float_t& mipSlope;
    Float_t& mipIntercept;
    UShort_t& mipNhitCone;
    Bool_t& mipIsHalo;
    Float_t& scPt;
    Float_t& scEta;
    Float_t& scPhi;
    Float_t& e13;
    Float_t& e31;
    Float_t& e15;
    Float_t& e22;
    Float_t& e25;
    Float_t& e33;
    Float_t& e44;
    Float_t& e55;
    Float_t& emax;
    Float_t& e2nd;
    Float_t& e4;
    Float_t& r9;
    Float_t& etaWidth;
    Float_t& phiWidth;
    Float_t& time;
    Float_t& timeSpan;
    Float_t& genMatchDR;
    Bool_t& isEB;
    Bool_t& pixelVeto;
    Bool_t& electronVeto;
    Bool_t& csafeVeto;
    Bool_t& highpt;
    Bool_t* matchL1{0}; //[nPhotonL1Objects]
  };

  class Lepton : public RecoParticle {
  public:
    struct array_data : public RecoParticle::array_data {
      array_data();

      Bool_t positive[NMAX]{};
      Bool_t tauDecay[NMAX]{};
      Bool_t hadDecay[NMAX]{};

      void setStatus(TTree&, TString const&, Bool_t, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
      void setAddress(TTree&, TString const&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
      void book(TTree&, TString const&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
    };

    Lepton();
    Lepton(array_data&, UInt_t idx);
    Lepton(Lepton const&);
    virtual ~Lepton();
    Lepton& operator=(Lepton const&);
    void setStatus(TTree&, TString const&, Bool_t, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE) override;
    void setAddress(TTree&, TString const&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE) override;
    void book(TTree&, TString const&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE) override;
    void init() override;

    int charge() const { return positive ? 1 : -1; }

  private:
    static std::vector<std::auto_ptr<array_data>> singlesData_;
    static SinglesPos singlesPos_;
    static std::set<SinglesPos> usedSinglesPos_;
    static SinglesPos const& nextSinglesPos_();

  public:
    Bool_t& positive;
    Bool_t& tauDecay;
    Bool_t& hadDecay;
  };

  class Electron : public Lepton {
  public:
    struct array_data : public Lepton::array_data {
      array_data();

      Float_t chIsoPh[NMAX]{};
      Float_t nhIsoPh[NMAX]{};
      Float_t phIsoPh[NMAX]{};
      Float_t combRelIso[NMAX]{};
      Float_t ecalIso[NMAX]{};
      Float_t hcalIso[NMAX]{};
      Float_t sieie[NMAX]{};
      Float_t sipip[NMAX]{};
      Float_t sieip[NMAX]{};
      Float_t hOverE[NMAX]{};
      Bool_t isEB[NMAX]{};
      Bool_t veto[NMAX]{};

      void setStatus(TTree&, TString const&, Bool_t, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
      void setAddress(TTree&, TString const&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
      void book(TTree&, TString const&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
    };

    Electron();
    Electron(array_data&, UInt_t idx);
    Electron(Electron const&);
    virtual ~Electron();
    Electron& operator=(Electron const&);
    void setStatus(TTree&, TString const&, Bool_t, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE) override;
    void setAddress(TTree&, TString const&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE) override;
    void book(TTree&, TString const&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE) override;
    void init() override;

    double m() const override { return 5.109989e-4; }
    bool passCHIsoPh(UInt_t wp) const { return chIsoPh < Photon::chIsoCuts[isEB ? 0 : 1][wp]; }
    bool passNHIsoPh(UInt_t wp) const { return nhIsoPh < Photon::nhIsoCuts[isEB ? 0 : 1][wp]; }
    bool passPhIsoPh(UInt_t wp) const { return phIsoPh < Photon::phIsoCuts[isEB ? 0 : 1][wp]; }
    bool passSieiePh(UInt_t wp) const { return sieie < Photon::sieieCuts[isEB ? 0 : 1][wp]; }
    bool passHOverEPh(UInt_t wp) const { return hOverE < Photon::hOverECuts[isEB ? 0 : 1][wp]; }

  private:
    static std::vector<std::auto_ptr<array_data>> singlesData_;
    static SinglesPos singlesPos_;
    static std::set<SinglesPos> usedSinglesPos_;
    static SinglesPos const& nextSinglesPos_();

  public:
    Float_t& chIsoPh;
    Float_t& nhIsoPh;
    Float_t& phIsoPh;
    Float_t& combRelIso;
    Float_t& ecalIso;
    Float_t& hcalIso;
    Float_t& sieie;
    Float_t& sipip;
    Float_t& sieip;
    Float_t& hOverE;
    Bool_t& isEB;
    Bool_t& veto;
  };

  class Muon : public Lepton {
  public:
    struct array_data : public Lepton::array_data {
      array_data();

      Float_t combRelIso[NMAX]{};

      void setStatus(TTree&, TString const&, Bool_t, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
      void setAddress(TTree&, TString const&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
      void book(TTree&, TString const&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
    };

    Muon();
    Muon(array_data&, UInt_t idx);
    Muon(Muon const&);
    virtual ~Muon();
    Muon& operator=(Muon const&);
    void setStatus(TTree&, TString const&, Bool_t, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE) override;
    void setAddress(TTree&, TString const&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE) override;
    void book(TTree&, TString const&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE) override;
    void init() override;

    double m() const override { return 1.05658e-2; }

  private:
    static std::vector<std::auto_ptr<array_data>> singlesData_;
    static SinglesPos singlesPos_;
    static std::set<SinglesPos> usedSinglesPos_;
    static SinglesPos const& nextSinglesPos_();

  public:
    Float_t& combRelIso;
  };

  class Tau : public RecoParticleM {
  public:
    struct array_data : public RecoParticleM::array_data {
      array_data();

      Bool_t decayMode[NMAX]{};
      Float_t combIso[NMAX]{};

      void setStatus(TTree&, TString const&, Bool_t, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
      void setAddress(TTree&, TString const&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
      void book(TTree&, TString const&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
    };

    Tau();
    Tau(array_data&, UInt_t idx);
    Tau(Tau const&);
    virtual ~Tau();
    Tau& operator=(Tau const&);
    void setStatus(TTree&, TString const&, Bool_t, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE) override;
    void setAddress(TTree&, TString const&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE) override;
    void book(TTree&, TString const&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE) override;
    void init() override;

  private:
    static std::vector<std::auto_ptr<array_data>> singlesData_;
    static SinglesPos singlesPos_;
    static std::set<SinglesPos> usedSinglesPos_;
    static SinglesPos const& nextSinglesPos_();

  public:
    Bool_t& decayMode;
    Float_t& combIso;
  };

  class Jet : public RecoParticleM {
  public:
    struct array_data : public RecoParticleM::array_data {
      array_data();

      Float_t ptRaw[NMAX]{};
      Float_t ptCorrUp[NMAX]{};
      Float_t ptCorrDown[NMAX]{};
      Float_t ptResCorr[NMAX]{};
      Float_t phiResCorr[NMAX]{};
      Float_t cisv[NMAX]{};

      void setStatus(TTree&, TString const&, Bool_t, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
      void setAddress(TTree&, TString const&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
      void book(TTree&, TString const&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
    };

    Jet();
    Jet(array_data&, UInt_t idx);
    Jet(Jet const&);
    virtual ~Jet();
    Jet& operator=(Jet const&);
    void setStatus(TTree&, TString const&, Bool_t, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE) override;
    void setAddress(TTree&, TString const&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE) override;
    void book(TTree&, TString const&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE) override;
    void init() override;

  private:
    static std::vector<std::auto_ptr<array_data>> singlesData_;
    static SinglesPos singlesPos_;
    static std::set<SinglesPos> usedSinglesPos_;
    static SinglesPos const& nextSinglesPos_();

  public:
    Float_t& ptRaw;
    Float_t& ptCorrUp;
    Float_t& ptCorrDown;
    Float_t& ptResCorr;
    Float_t& phiResCorr;
    Float_t& cisv;
  };

  class SuperCluster {
  public:
    struct array_data {
      static UInt_t const NMAX{128};

      array_data();

      Float_t rawPt[NMAX]{};
      Float_t eta[NMAX]{};
      Float_t phi[NMAX]{};
      Bool_t isEB[NMAX]{};
      Float_t time[NMAX]{};
      Float_t sieie[NMAX]{};
      Float_t sipip[NMAX]{};
      Float_t e2e9[NMAX]{};
      Float_t emax[NMAX]{};
      Float_t e2nd[NMAX]{};
      Float_t e4[NMAX]{};
      Float_t timeSpan[NMAX]{};

      void setStatus(TTree&, TString const&, Bool_t, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
      void setAddress(TTree&, TString const&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
      void book(TTree&, TString const&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
    };

    SuperCluster();
    SuperCluster(array_data&, UInt_t idx);
    SuperCluster(SuperCluster const&);
    virtual ~SuperCluster();
    SuperCluster& operator=(SuperCluster const&);
    virtual void setStatus(TTree&, TString const&, Bool_t, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
    virtual void setAddress(TTree&, TString const&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
    virtual void book(TTree&, TString const&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
    virtual void init();

  private:
    static std::vector<std::auto_ptr<array_data>> singlesData_;
    static SinglesPos singlesPos_;
    static std::set<SinglesPos> usedSinglesPos_;
    static SinglesPos const& nextSinglesPos_();

  protected:
    SinglesPos pos_{-1, -1};

  public:
    Float_t& rawPt;
    Float_t& eta;
    Float_t& phi;
    Bool_t& isEB;
    Float_t& time;
    Float_t& sieie;
    Float_t& sipip;
    Float_t& e2e9;
    Float_t& emax;
    Float_t& e2nd;
    Float_t& e4;
    Float_t& timeSpan;
  };

  class Met {
  public:
    Met(TString const& name);
    Met(Met const&);
    virtual ~Met();
    Met& operator=(Met const&);

    void setName(TString const& name) { name_ = name; }
    virtual void setStatus(TTree&, Bool_t, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
    virtual void setStatus(TTree&, TString const&, Bool_t, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
    virtual void setAddress(TTree&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
    virtual void setAddress(TTree&, TString const&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
    virtual void book(TTree&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
    virtual void book(TTree&, TString const&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
    virtual void init();

    virtual TVector2 v() const { TVector2 vec; vec.SetMagPhi(met, phi); return vec; }

  protected:
    TString name_;

  public:
    Float_t met{};
    Float_t phi{};
    Float_t sumEt{};
  };

  class CorrectedMet : public Met {
  public:
    CorrectedMet(TString const& name);
    CorrectedMet(CorrectedMet const&);
    virtual ~CorrectedMet();
    CorrectedMet& operator=(CorrectedMet const&);
    void setStatus(TTree&, Bool_t, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE) override;
    void setStatus(TTree&, TString const&, Bool_t, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE) override;
    void setAddress(TTree&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE) override;
    void setAddress(TTree&, TString const&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE) override;
    void book(TTree&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE) override;
    void book(TTree&, TString const&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE) override;
    void init() override;

    virtual TVector2 vCorr(int corr = 0) const { if (corr == 0) return v(); TVector2 vec; switch (corr) { case 1: vec.SetMagPhi(metCorrUp, phiCorrUp); break; case -1: vec.SetMagPhi(metCorrDown, phiCorrDown); break; } return vec; }

  public:
    Float_t metCorrUp{};
    Float_t phiCorrUp{};
    Float_t metCorrDown{};
    Float_t phiCorrDown{};
    Float_t metJetRes{};
    Float_t phiJetRes{};
    Float_t metUnclUp{};
    Float_t phiUnclUp{};
    Float_t metUnclDown{};
    Float_t phiUnclDown{};
  };

  class Parton : public ParticleM {
  public:
    struct array_data : public ParticleM::array_data {
      array_data();

      Char_t pid[NMAX]{};

      void setStatus(TTree&, TString const&, Bool_t, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
      void setAddress(TTree&, TString const&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
      void book(TTree&, TString const&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
    };

    Parton();
    Parton(array_data&, UInt_t idx);
    Parton(Parton const&);
    virtual ~Parton();
    Parton& operator=(Parton const&);
    void setStatus(TTree&, TString const&, Bool_t, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE) override;
    void setAddress(TTree&, TString const&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE) override;
    void book(TTree&, TString const&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE) override;
    void init() override;

  private:
    static std::vector<std::auto_ptr<array_data>> singlesData_;
    static SinglesPos singlesPos_;
    static std::set<SinglesPos> usedSinglesPos_;
    static SinglesPos const& nextSinglesPos_();

  public:
    Char_t& pid;
  };

  class MCParticle : public ParticleM {
  public:
    struct array_data : public ParticleM::array_data {
      array_data();

      Int_t pid[NMAX]{};
      UChar_t ancestor[NMAX]{};

      void setStatus(TTree&, TString const&, Bool_t, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
      void setAddress(TTree&, TString const&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
      void book(TTree&, TString const&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
    };

    MCParticle();
    MCParticle(array_data&, UInt_t idx);
    MCParticle(MCParticle const&);
    virtual ~MCParticle();
    MCParticle& operator=(MCParticle const&);
    void setStatus(TTree&, TString const&, Bool_t, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE) override;
    void setAddress(TTree&, TString const&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE) override;
    void book(TTree&, TString const&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE) override;
    void init() override;

  private:
    static std::vector<std::auto_ptr<array_data>> singlesData_;
    static SinglesPos singlesPos_;
    static std::set<SinglesPos> usedSinglesPos_;
    static SinglesPos const& nextSinglesPos_();

  public:
    Int_t& pid;
    UChar_t& ancestor;
  };

  class GenJet : public ParticleM {
  public:
    struct array_data : public ParticleM::array_data {
    };

    GenJet();
    GenJet(array_data&, UInt_t idx);
    GenJet(GenJet const&);
    virtual ~GenJet();
    GenJet& operator=(GenJet const&);
    void setStatus(TTree&, TString const&, Bool_t, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE) override;
    void setAddress(TTree&, TString const&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE) override;
    void book(TTree&, TString const&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE) override;
    void init() override;

  private:
    static std::vector<std::auto_ptr<array_data>> singlesData_;
    static SinglesPos singlesPos_;
    static std::set<SinglesPos> usedSinglesPos_;
    static SinglesPos const& nextSinglesPos_();
  };

  class HLTBits {
  public:
    HLTBits(TString const& name);
    HLTBits(HLTBits const&);
    virtual ~HLTBits();
    HLTBits& operator=(HLTBits const&);

    void setName(TString const& name) { name_ = name; }
    virtual void setStatus(TTree&, Bool_t, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
    virtual void setStatus(TTree&, TString const&, Bool_t, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
    virtual void setAddress(TTree&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
    virtual void setAddress(TTree&, TString const&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
    virtual void book(TTree&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
    virtual void book(TTree&, TString const&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
    virtual void init();

    void set(unsigned iB) { words[iB / 32] |= (1 << (iB % 32)); }
    bool pass(unsigned iB) const { return ((words[iB / 32] >> (iB % 32)) & 1) != 0; }

  protected:
    TString name_;

  public:
    UInt_t words[16]{};
  };

  class MetFilters {
  public:
    MetFilters(TString const& name);
    MetFilters(MetFilters const&);
    virtual ~MetFilters();
    MetFilters& operator=(MetFilters const&);

    void setName(TString const& name) { name_ = name; }
    virtual void setStatus(TTree&, Bool_t, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
    virtual void setStatus(TTree&, TString const&, Bool_t, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
    virtual void setAddress(TTree&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
    virtual void setAddress(TTree&, TString const&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
    virtual void book(TTree&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
    virtual void book(TTree&, TString const&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
    virtual void init();

    virtual bool pass() const { return !globalHalo16 && !hbhe && !hbheIso && !ecalDeadCell && !badsc && !badTrack && !badMuonTrack; }

  protected:
    TString name_;

  public:
    Bool_t cschalo{};
    Bool_t globalHalo16{};
    Bool_t hbhe{};
    Bool_t hbheIso{};
    Bool_t ecalDeadCell{};
    Bool_t badsc{};
    Bool_t badTrack{};
    Bool_t badMuonTrack{};
  };

  class Vertex {
  public:
    struct array_data {
      static UInt_t const NMAX{128};

      array_data();

      Float_t x[NMAX]{};
      Float_t y[NMAX]{};
      Float_t z[NMAX]{};
      UShort_t ntrk[NMAX]{};
      Float_t sumPt2[NMAX]{};

      void setStatus(TTree&, TString const&, Bool_t, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
      void setAddress(TTree&, TString const&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
      void book(TTree&, TString const&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
    };

    Vertex();
    Vertex(array_data&, UInt_t idx);
    Vertex(Vertex const&);
    virtual ~Vertex();
    Vertex& operator=(Vertex const&);
    virtual void setStatus(TTree&, TString const&, Bool_t, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
    virtual void setAddress(TTree&, TString const&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
    virtual void book(TTree&, TString const&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
    virtual void init();

  private:
    static std::vector<std::auto_ptr<array_data>> singlesData_;
    static SinglesPos singlesPos_;
    static std::set<SinglesPos> usedSinglesPos_;
    static SinglesPos const& nextSinglesPos_();

  protected:
    SinglesPos pos_{-1, -1};

  public:
    Float_t& x;
    Float_t& y;
    Float_t& z;
    UShort_t& ntrk;
    Float_t& sumPt2;
  };
}

#endif
