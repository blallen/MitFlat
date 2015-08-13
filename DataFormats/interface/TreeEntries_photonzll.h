#ifndef TreeEntries_photonzll_h
#define TreeEntries_photonzll_h
#include "MitFlat/DataFormats/interface/Collections_photonzll.h"

namespace photonzll {

  class Event {
  public:
    UInt_t run{};
    UInt_t lumi{};
    UInt_t event{};
    Double_t weight{};
    Double_t rho{};
    Float_t genHt{};
    Float_t genZpt{};
    JetCollection jets{};
    PhotonCollection photons{};
    Met rawMet{};
    Met t1Met{};
    Met t1NoCHSMet{};
    Met eta30Met{};
    Met eta30T1Met{};
    Met eta30T1NoCHSMet{};
    Met chMet{};
    Met nhMet{};
    Met neMet{};
    Met chGt30Met{};
    Met nhGt30Met{};
    Met neGt30Met{};
    ZCand z{};

    void setAddress(TTree&);
    void book(TTree&);
  };

  class Weight {
  public:
    UInt_t run{};
    UInt_t lumi{};
    UInt_t event{};
    Double_t weight{};
    Double_t rho{};

    void setAddress(TTree&);
    void book(TTree&);
  };

}

#endif
