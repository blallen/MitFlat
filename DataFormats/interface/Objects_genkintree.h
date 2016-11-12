#ifndef Objects_genkintree_h
#define Objects_genkintree_h
#include "Utils.h"
#include "Math/GenVector/LorentzVector.h"
#include "Math/GenVector/PtEtaPhiM4D.h"
#include "TVector2.h"
#include "TString.h"
#include "Rtypes.h"
#include <memory>
#include <set>
#include <utility>
class TTree;

namespace genkintree {

  typedef std::pair<unsigned, unsigned> SinglesPos;
  typedef ROOT::Math::LorentzVector<ROOT::Math::PtEtaPhiM4D<double>> LorentzVectorM;

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

    virtual LorentzVectorM p4() const { return LorentzVectorM(pt, eta, phi, 0.); }

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

    LorentzVectorM p4() const override { return LorentzVectorM(pt, eta, phi, mass); }

  private:
    static std::vector<std::auto_ptr<array_data>> singlesData_;
    static SinglesPos singlesPos_;
    static std::set<SinglesPos> usedSinglesPos_;
    static SinglesPos const& nextSinglesPos_();

  public:
    Float_t& mass;
  };

  class Parton : public Particle {
  public:
    struct array_data : public Particle::array_data {
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

  class Boson : public ParticleM {
  public:
    struct array_data : public ParticleM::array_data {
      array_data();

      UShort_t flavor[NMAX]{};

      void setStatus(TTree&, TString const&, Bool_t, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
      void setAddress(TTree&, TString const&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
      void book(TTree&, TString const&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
    };

    Boson();
    Boson(array_data&, UInt_t idx);
    Boson(Boson const&);
    virtual ~Boson();
    Boson& operator=(Boson const&);
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
    UShort_t& flavor;
  };

  class Photon : public Particle {
  public:
    struct array_data : public Particle::array_data {
      array_data();

      Float_t isot[NMAX]{};

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

  private:
    static std::vector<std::auto_ptr<array_data>> singlesData_;
    static SinglesPos singlesPos_;
    static std::set<SinglesPos> usedSinglesPos_;
    static SinglesPos const& nextSinglesPos_();

  public:
    Float_t& isot;
  };

  class Lepton : public Particle {
  public:
    struct array_data : public Particle::array_data {
      array_data();

      Char_t charge[NMAX]{};
      Float_t minDRJ[NMAX]{};

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

  private:
    static std::vector<std::auto_ptr<array_data>> singlesData_;
    static SinglesPos singlesPos_;
    static std::set<SinglesPos> usedSinglesPos_;
    static SinglesPos const& nextSinglesPos_();

  public:
    Char_t& charge;
    Float_t& minDRJ;
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

    TVector2 v() const { TVector2 vec; vec.SetMagPhi(pt, phi); return vec; }

  protected:
    TString name_;

  public:
    Float_t pt{};
    Float_t phi{};
  };
}

#endif
