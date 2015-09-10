#ifndef Objects_met_h
#define Objects_met_h
#include "Rtypes.h"
class TTree;

namespace met {


  class Met {
  public:
    Met() {}
    virtual ~Met() {}
    virtual void setAddress(TTree&, TString const& objName);
    virtual void book(TTree&, TString const& objName);

    Float_t met;
    Float_t phi;
    Float_t sumEt;
  };

}

#endif
