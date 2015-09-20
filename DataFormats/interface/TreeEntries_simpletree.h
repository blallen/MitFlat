#ifndef TreeEntries_simpletree_h
#define TreeEntries_simpletree_h
#include "MitFlat/DataFormats/interface/Collections_simpletree.h"

namespace simpletree {

  class Event {
  public:
    UInt_t run{};
    UInt_t lumi{};
    UInt_t event{};
    Double_t weight{};
    Double_t rho{};
    UShort_t npv{};
    Float_t genHt{};
    Float_t genZpt{};
    UInt_t ntau{};
    JetCollection jets = JetCollection("jets");
    PhotonCollection photons = PhotonCollection("photons");
    ElectronCollection electrons = ElectronCollection("electrons");
    MuonCollection muons = MuonCollection("muons");
    Met rawMet = Met("rawMet");
    Met t1Met = Met("t1Met");
    Met t1NoCHSMet = Met("t1NoCHSMet");
    Met eta30Met = Met("eta30Met");
    Met eta30T1Met = Met("eta30T1Met");
    Met eta30T1NoCHSMet = Met("eta30T1NoCHSMet");
    Met nhScaledMet = Met("nhScaledMet");
    Met chMet = Met("chMet");
    Met nhMet = Met("nhMet");
    Met neMet = Met("neMet");
    Met chGt30Met = Met("chGt30Met");
    Met nhGt30Met = Met("nhGt30Met");
    Met neGt30Met = Met("neGt30Met");
    HLTCollection hlt = HLTCollection("hlt");

    void setStatus(TTree&, Bool_t, flatutils::BranchList const& = {"*"});
    void setAddress(TTree&, flatutils::BranchList const& = {"*"});
    void book(TTree&, flatutils::BranchList const& = {"*"});
  };

  class Weight {
  public:
    UInt_t run{};
    UInt_t lumi{};
    UInt_t event{};
    Double_t weight{};
    Double_t rho{};

    void setStatus(TTree&, Bool_t, flatutils::BranchList const& = {"*"});
    void setAddress(TTree&, flatutils::BranchList const& = {"*"});
    void book(TTree&, flatutils::BranchList const& = {"*"});
  };

}

#endif
