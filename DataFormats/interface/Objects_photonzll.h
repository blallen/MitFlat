#ifndef Objects_photonzll_h
#define Objects_photonzll_h
#include "MitCommon/DataFormats/interface/Types.h"
#include "TVector2.h"
#include "Rtypes.h"
class TTree;

namespace photonzll {

  class ParticleCollection;
  class ParticleMCollection;
  class JetCollection;
  class PhotonCollection;

  class Particle {
  public:
    Particle(ParticleCollection&, UInt_t idx);
    virtual ~Particle() {}

    virtual mithep::FourVectorM p4() const { return mithep::FourVectorM(pt, eta, phi, 0.); }

    Float_t& pt;
    Float_t& eta;
    Float_t& phi;
  };

  class ParticleM : public Particle {
  public:
    ParticleM(ParticleMCollection&, UInt_t idx);
    virtual ~ParticleM() {}

    mithep::FourVectorM p4() const { return mithep::FourVectorM(pt, eta, phi, mass); }

    Float_t& mass;
  };

  class Jet : public ParticleM {
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

    TVector2 v() const { TVector2 vec; vec.SetMagPhi(met, phi); return vec; }

    Float_t met;
    Float_t phi;
    Float_t sumEt;
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

    mithep::FourVectorM pMu(UInt_t iM) const { if (iM == 0) return mithep::FourVectorM(pt0, eta0, phi0, 0.106); else return mithep::FourVectorM(pt1, eta1, phi1, 0.106); }
    mithep::FourVectorM pZ() const { return pMu(0) + pMu(1); }

    Float_t pt0;
    Float_t eta0;
    Float_t phi0;
    Float_t pt1;
    Float_t eta1;
    Float_t phi1;
  };

}

#endif
