#ifndef TreeEntries_mugamma_h
#define TreeEntries_mugamma_h
#include "MitFlat/DataFormats/interface/Collections_mugamma.h"

namespace mugamma {

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
    ElectronCollection electrons{};
    MuonCollection muons{};
    UInt_t ntau{};
    Met rawMet{};
    Met t1Met{};
    Met t1NoCHSMet{};
    Met eta30Met{};
    Met eta30T1Met{};
    Met eta30T1NoCHSMet{};
    Met nhScaledMet{};
    Met chMet{};
    Met nhMet{};
    Met neMet{};
    Met chGt30Met{};
    Met nhGt30Met{};
    Met neGt30Met{};

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
