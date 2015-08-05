#ifndef Objects_monojet_h
#define Objects_monojet_h
#include "Rtypes.h"
class TTree;

namespace monojet {

  class ParticleCollection;
  class JetCollection;
  class ElectronCollection;
  class MuonCollection;
  class TauCollection;
  class PhotonCollection;
  class TriggerObjCollection;

  class Particle {
  public:
    Particle(ParticleCollection&, UInt_t idx);
    virtual ~Particle() {}

    Float_t& pt;
    Float_t& eta;
    Float_t& phi;
  };

  class Jet : public Particle {
  public:
    Jet(JetCollection&, UInt_t idx);
    virtual ~Jet() {}

    Float_t& btag;
    Float_t& chFrac;
    Float_t& nhFrac;
    Float_t& neFrac;
  };

  class Met {
  public:
    Met() {}
    virtual ~Met() {}
    virtual void setAddress(TTree&, TString const& objName);
    virtual void book(TTree&, TString const& objName);

    Float_t met;
    Float_t phi;
    Float_t metNoMu;
    Float_t phiNoMu;
  };

  class Electron : public Particle {
  public:
    Electron(ElectronCollection&, UInt_t idx);
    virtual ~Electron() {}

  };

  class Muon : public Particle {
  public:
    Muon(MuonCollection&, UInt_t idx);
    virtual ~Muon() {}

  };

  class Tau : public Particle {
  public:
    Tau(TauCollection&, UInt_t idx);
    virtual ~Tau() {}

    Float_t& disc;
  };

  class Photon : public Particle {
  public:
    Photon(PhotonCollection&, UInt_t idx);
    virtual ~Photon() {}

  };

  class Trigger {
  public:
    Trigger() {}
    virtual ~Trigger() {}
    virtual void setAddress(TTree&, TString const& objName);
    virtual void book(TTree&, TString const& objName);

    Bool_t met90mht90;
    Bool_t met120mht120;
  };

  class TriggerObj : public Particle {
  public:
    TriggerObj(TriggerObjCollection&, UInt_t idx);
    virtual ~TriggerObj() {}

  };

}

#endif
