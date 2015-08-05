#ifndef TreeEntries_monojet_h
#define TreeEntries_monojet_h
#include "MitFlat/DataFormats/interface/Collections_monojet.h"

namespace monojet {

  class Event {
  public:
    UInt_t runNumber{};
    UInt_t lumiNumber{};
    UInt_t eventNumber{};
    MuonCollection muons{};
    PhotonCollection photons{};
    Trigger trigger{};
    Met met{};
    TriggerObjCollection eg135s{};
    TriggerObjCollection eg120s{};
    TriggerObjCollection eg165s{};

    void setAddress(TTree&);
    void book(TTree&);
  };

}

#endif
