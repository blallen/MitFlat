#ifndef TreeEntries_simpletree_h
#define TreeEntries_simpletree_h
#include "MitFlat/DataFormats/interface/Collection.h"
#include "MitFlat/DataFormats/interface/Objects_simpletree.h"

namespace simpletree {

  typedef flatutils::Collection<Particle, flatutils::BaseCollection<kFALSE>> ParticleCollection;
  typedef flatutils::Collection<ParticleM, ParticleCollection> ParticleMCollection;
  typedef flatutils::Collection<Jet, ParticleMCollection> JetCollection;
  typedef flatutils::Collection<Photon, ParticleCollection> PhotonCollection;
  typedef flatutils::Collection<Lepton, ParticleMCollection> LeptonCollection;
  typedef flatutils::Collection<Electron, LeptonCollection> ElectronCollection;
  typedef flatutils::Collection<Muon, LeptonCollection> MuonCollection;
  typedef flatutils::Collection<Tau, ParticleMCollection> TauCollection;
  typedef flatutils::Collection<Parton, ParticleMCollection> PartonCollection;
  typedef flatutils::Collection<MCParticle, ParticleMCollection> MCParticleCollection;
  typedef flatutils::Collection<GenJet, JetCollection> GenJetCollection;
  typedef flatutils::Collection<HLT, flatutils::BaseCollection<kTRUE>> HLTCollection;
  typedef flatutils::Collection<ReweightScale, flatutils::BaseCollection<kFALSE>> ReweightScaleCollection;

  class Event {
  public:
    UInt_t run{};
    UInt_t lumi{};
    UInt_t event{};
    Double_t weight{};
    Double_t rho{};
    UShort_t npv{};
    PartonCollection partons = PartonCollection("partons");
    MCParticleCollection partonFinalStates = MCParticleCollection("partonFinalStates");
    JetCollection jets = JetCollection("jets");
    GenJetCollection genJets = GenJetCollection("genJets");
    PhotonCollection photons = PhotonCollection("photons");
    ElectronCollection electrons = ElectronCollection("electrons");
    MuonCollection muons = MuonCollection("muons");
    TauCollection taus = TauCollection("taus");
    Met rawMet = Met("rawMet");
    Met t1Met = Met("t1Met");
    Met genMet = Met("genMet");
    HLTCollection hlt = HLTCollection("hlt");
    ReweightScaleCollection reweight = ReweightScaleCollection("reweight");

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
