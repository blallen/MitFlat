#ifndef Objects_simpletree_h
#define Objects_simpletree_h
#include "Math/GenVector/LorentzVector.h"
#include "Math/GenVector/PtEtaPhiM4D.h"
#include "TVector2.h"
#include "TString.h"
#include "Rtypes.h"
class TTree;

namespace simpletree {

  typedef ROOT::Math::LorentzVector<ROOT::Math::PtEtaPhiM4D<double>> LorentzVectorM;
  typedef std::vector<void*> BranchList;

  Bool_t branchIn(void* bPtr, BranchList const&);
  void setStatusAndAddress(TTree&, TString const& bName, void* bPtr);

  enum HLTPath {
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

  class ParticleCollection;
  class ParticleMCollection;
  class JetCollection;
  class PhotonCollection;
  class LeptonCollection;
  class ElectronCollection;
  class MuonCollection;
  class HLTCollection;
  class Particle {
  public:
    Particle(ParticleCollection&, UInt_t idx);
    virtual ~Particle() {}
    Particle& operator=(Particle const&);

    virtual LorentzVectorM p4() const { return LorentzVectorM(pt, eta, phi, 0.); }

    Float_t& pt;
    Float_t& eta;
    Float_t& phi;
  };

  class ParticleM : public Particle {
  public:
    ParticleM(ParticleMCollection&, UInt_t idx);
    virtual ~ParticleM() {}
    ParticleM& operator=(ParticleM const&);

    LorentzVectorM p4() const { return LorentzVectorM(pt, eta, phi, mass); }

    Float_t& mass;
  };

  class Jet : public ParticleM {
  public:
    Jet(JetCollection&, UInt_t idx);
    virtual ~Jet() {}
    Jet& operator=(Jet const&);

  };

  class Met {
  public:
    Met(TString const& name = "met") : name_(name) {}
    virtual ~Met() {}
    virtual void setStatus(TTree&, Bool_t, BranchList const& = BranchList());
    virtual void setAddress(TTree&, BranchList const& = BranchList());
    virtual void book(TTree&, BranchList const& = BranchList());
    Met& operator=(Met const&);

    TVector2 v() const { TVector2 vec; vec.SetMagPhi(met, phi); return vec; }

    Float_t met;
    Float_t phi;
    Float_t sumEt;
  private:
    TString const name_;
  };

  class Photon : public Particle {
  public:
    Photon(PhotonCollection&, UInt_t idx);
    virtual ~Photon() {}
    Photon& operator=(Photon const&);

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
    Bool_t& matchHLT165HE10;
    Bool_t& matchHLT175;
  };

  class Lepton : public ParticleM {
  public:
    Lepton(LeptonCollection&, UInt_t idx);
    virtual ~Lepton() {}
    Lepton& operator=(Lepton const&);

    int charge() const { return positive ? 1 : -1; }

    Int_t& matchedGen;
    Bool_t& tauDecay;
    Bool_t& hadDecay;
    Bool_t& positive;
    Bool_t& tight;
  };

  class Electron : public Lepton {
  public:
    Electron(ElectronCollection&, UInt_t idx);
    virtual ~Electron() {}
    Electron& operator=(Electron const&);

    Bool_t& matchHLT23Loose;
    Bool_t& matchHLT27Loose;
  };

  class Muon : public Lepton {
  public:
    Muon(MuonCollection&, UInt_t idx);
    virtual ~Muon() {}
    Muon& operator=(Muon const&);

    Bool_t& matchHLT24;
    Bool_t& matchHLT27;
  };

  class HLT {
  public:
    HLT(HLTCollection&, UInt_t idx);
    virtual ~HLT() {}
    HLT& operator=(HLT const&);

    Bool_t& pass;
  };

}

#endif
