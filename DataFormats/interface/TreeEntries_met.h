#ifndef TreeEntries_met_h
#define TreeEntries_met_h
#include "MitFlat/DataFormats/interface/Collections_met.h"

namespace met {

  class Event {
  public:
    UInt_t run{};
    UInt_t event{};
    Met rawMet{};
    Met type1Met{};

    void setAddress(TTree&);
    void book(TTree&);
  };

}

#endif
