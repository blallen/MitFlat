#ifndef Objects_genkintree_h
#define Objects_genkintree_h
#include "Utils.h"
#include "Math/GenVector/LorentzVector.h"
#include "Math/GenVector/PtEtaPhiM4D.h"
#include "TVector2.h"
#include "TString.h"
#include "Rtypes.h"
class TTree;

namespace genkintree {

  typedef ROOT::Math::LorentzVector<ROOT::Math::PtEtaPhiM4D<double>> LorentzVectorM;

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

  class Jet : public Particle {
  public:
    struct array_data : public Particle::array_data {
      Float_t mass[NMAX]{};

      void setStatus(TTree&, TString const&, Bool_t, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
      void setAddress(TTree&, TString const&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
      void book(TTree&, TString const&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
    };

    Jet(array_data&, UInt_t idx);
    Jet(Jet const&);
    virtual ~Jet() {}
    Jet& operator=(Jet const&);

    LorentzVectorM p4() const { return LorentzVectorM(pt, eta, phi, mass); }

  public:
    Float_t& mass;
  };

  class Photon : public Particle {
  public:
    struct array_data : public Particle::array_data {
      Float_t isot[NMAX]{};

      void setStatus(TTree&, TString const&, Bool_t, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
      void setAddress(TTree&, TString const&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
      void book(TTree&, TString const&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
    };

    Photon(array_data&, UInt_t idx);
    Photon(Photon const&);
    virtual ~Photon() {}
    Photon& operator=(Photon const&);

  public:
    Float_t& isot;
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

    TVector2 v() const { TVector2 vec; vec.SetMagPhi(pt, phi); return vec; }

  protected:
    TString name_;

  public:
    Float_t pt{};
    Float_t phi{};
  };
}

#endif
