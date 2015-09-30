#ifndef TreeEntries_simpletree_h
#define TreeEntries_simpletree_h
#include "MitFlat/DataFormats/interface/Collection.h"
#include "MitFlat/DataFormats/interface/Objects_simpletree.h"

namespace simpletree {

  typedef flatutils::Collection<Particle, flatutils::BaseCollection<kFALSE>> ParticleCollection;
  typedef flatutils::Collection<ParticleM, ParticleCollection> ParticleMCollection;
  typedef flatutils::Collection<Jet, ParticleMCollection> JetCollection;
  typedef flatutils::Collection<Isolatable, ParticleCollection> IsolatableCollection;
  typedef flatutils::Collection<Photon, IsolatableCollection> PhotonCollection;
  typedef flatutils::Collection<Lepton, IsolatableCollection> LeptonCollection;
  typedef flatutils::Collection<Electron, LeptonCollection> ElectronCollection;
  typedef flatutils::Collection<Muon, LeptonCollection> MuonCollection;
  typedef flatutils::Collection<HLT, flatutils::BaseCollection<kTRUE>> HLTCollection;

  class Event {
  public:
    UInt_t run{};
    UInt_t lumi{};
    UInt_t event{};
    Double_t weight{};
    Double_t rho{};
    UShort_t npv{};
    Float_t genHt{};
    Short_t genBoson{};
    Float_t genBosonPt{};
    Float_t genBosonEta{};
    Float_t genBosonPhi{};
    Float_t genBosonM{};
    Short_t genLepton1{};
    Float_t genLepton1Pt{};
    Float_t genLepton1Eta{};
    Float_t genLepton1Phi{};
    Float_t genLepton1M{};
    Short_t genLepton2{};
    Float_t genLepton2Pt{};
    Float_t genLepton2Eta{};
    Float_t genLepton2Phi{};
    Float_t genLepton2M{};
    UInt_t ntau{};
    JetCollection jets = JetCollection("jets");
    PhotonCollection photons = PhotonCollection("photons");
    ElectronCollection electrons = ElectronCollection("electrons");
    MuonCollection muons = MuonCollection("muons");
    Met rawMet = Met("rawMet");
    Met t1Met = Met("t1Met");
    Met t1NoCHSMet = Met("t1NoCHSMet");
    Met nhScaledMet = Met("nhScaledMet");
    Met chMet = Met("chMet");
    Met nhMet = Met("nhMet");
    Met neMet = Met("neMet");
    HLTCollection hlt = HLTCollection("hlt");

    void setStatus(TTree&, Bool_t, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
    void setAddress(TTree&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
    void book(TTree&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
  };

  class Weight {
  public:
    UInt_t run{};
    UInt_t lumi{};
    UInt_t event{};
    Double_t weight{};
    Double_t rho{};

    void setStatus(TTree&, Bool_t, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
    void setAddress(TTree&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
    void book(TTree&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
  };

  TTree* makeHLTPathTree();

}

#endif
