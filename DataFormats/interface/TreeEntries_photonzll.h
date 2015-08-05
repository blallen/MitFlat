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
    JetCollection jets{};
    PhotonCollection photons{};
    Met rawMet{};
    Met t1Met{};
    Met eta30Met{};
    Met eta30T1Met{};
    Met chMet{};
    Met nhMet{};
    Met neMet{};
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

    void setAddress(TTree&);
    void book(TTree&);
  };

}

#endif
