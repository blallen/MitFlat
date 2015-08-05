#ifndef Objects_photonzll_h
#define Objects_photonzll_h
#include "Rtypes.h"
class TTree;

namespace photonzll {

  class ParticleCollection;
  class JetCollection;
  class PhotonCollection;

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

  };

  class Met {
  public:
    Met() {}
    virtual ~Met() {}
    virtual void setAddress(TTree&, TString const& objName);
    virtual void book(TTree&, TString const& objName);

    Float_t met;
    Float_t phi;
  };

  class Photon : public Particle {
  public:
    Photon(PhotonCollection&, UInt_t idx);
    virtual ~Photon() {}

    Float_t& chIso;
    Float_t& nhIso;
    Float_t& phIso;
    Float_t& sieie;
    Float_t& hOverE;
    Bool_t& pixelVeto;
    Bool_t& csafeVeto;
    Bool_t& isLoose;
    Bool_t& isMedium;
    Bool_t& isTight;
  };

  class ZCand {
  public:
    ZCand() {}
    virtual ~ZCand() {}
    virtual void setAddress(TTree&, TString const& objName);
    virtual void book(TTree&, TString const& objName);

    Float_t pt;
    Float_t eta;
    Float_t phi;
  };

}

#endif
