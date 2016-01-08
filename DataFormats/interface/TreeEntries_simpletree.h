#ifndef TreeEntries_simpletree_h
#define TreeEntries_simpletree_h
#include "Collection.h"
#include "Objects_simpletree.h"

namespace simpletree {

  typedef flatutils::Collection<simpletree::Particle, flatutils::DynamicCollection> ParticleCollection;
  typedef flatutils::Collection<simpletree::ParticleM, simpletree::ParticleCollection> ParticleMCollection;
  typedef flatutils::Collection<simpletree::Jet, simpletree::ParticleMCollection> JetCollection;
  typedef flatutils::Collection<simpletree::Photon, simpletree::ParticleCollection> PhotonCollection;
  typedef flatutils::Collection<simpletree::Lepton, simpletree::ParticleMCollection> LeptonCollection;
  typedef flatutils::Collection<simpletree::Electron, simpletree::LeptonCollection> ElectronCollection;
  typedef flatutils::Collection<simpletree::Muon, simpletree::LeptonCollection> MuonCollection;
  typedef flatutils::Collection<simpletree::Tau, simpletree::ParticleMCollection> TauCollection;
  typedef flatutils::Collection<simpletree::Parton, simpletree::ParticleMCollection> PartonCollection;
  typedef flatutils::Collection<simpletree::MCParticle, simpletree::ParticleMCollection> MCParticleCollection;
  typedef flatutils::Collection<simpletree::GenJet, simpletree::JetCollection> GenJetCollection;
  typedef flatutils::Collection<simpletree::HLT, flatutils::StaticCollection> HLTCollection;
  typedef flatutils::Collection<simpletree::ReweightScale, flatutils::DynamicCollection> ReweightScaleCollection;

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

  TTree* makeHLTPathTree();

}

#endif
