#ifndef TreeEntries_simpletree_h
#define TreeEntries_simpletree_h
#include "Collection.h"
#include "Objects_simpletree.h"

namespace simpletree {

  typedef flatutils::Collection<Particle, flatutils::DynamicCollection> ParticleCollection;
  typedef flatutils::Collection<ParticleM, ParticleCollection> ParticleMCollection;
  typedef flatutils::Collection<Jet, ParticleMCollection> JetCollection;
  typedef flatutils::Collection<Photon, ParticleCollection> PhotonCollection;
  typedef flatutils::Collection<Lepton, ParticleCollection> LeptonCollection;
  typedef flatutils::Collection<Electron, LeptonCollection> ElectronCollection;
  typedef flatutils::Collection<Muon, LeptonCollection> MuonCollection;
  typedef flatutils::Collection<Tau, ParticleMCollection> TauCollection;
  typedef flatutils::Collection<Parton, ParticleMCollection> PartonCollection;
  typedef flatutils::Collection<MCParticle, ParticleMCollection> MCParticleCollection;
  typedef flatutils::Collection<GenJet, ParticleMCollection> GenJetCollection;

  class Event {
  public:
    Event();

    UInt_t run{};
    UInt_t lumi{};
    UInt_t event{};
    Double_t weight{1.};
    Double_t scaleReweight[6]{};
    Double_t pdfDW{};
    Double_t rho{};
    Float_t npvTrue{};
    UShort_t npv{};
    PartonCollection partons = PartonCollection("partons");
    MCParticleCollection promptFinalStates = MCParticleCollection("promptFinalStates");
    JetCollection jets = JetCollection("jets");
    GenJetCollection genJets = GenJetCollection("genJets");
    PhotonCollection photons = PhotonCollection("photons");
    ElectronCollection electrons = ElectronCollection("electrons");
    MuonCollection muons = MuonCollection("muons");
    TauCollection taus = TauCollection("taus");
    Met rawMet = Met("rawMet");
    CorrectedMet t1Met = CorrectedMet("t1Met");
    Met caloMet = Met("caloMet");
    Met genMet = Met("genMet");
    HLTBits hltBits = HLTBits("hltBits");
    MetFilters metFilters = MetFilters("metFilters");

    void setStatus(TTree&, Bool_t, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
    void setAddress(TTree&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
    void book(TTree&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
    void init();
    TTree* getInput() const { return input_; }

  protected:
    TTree* input_{0}; // set by setAddress
  };

  class Run {
  public:
    Run();

    UInt_t run{};
    UInt_t hltMenu{};

    void setStatus(TTree&, Bool_t, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
    void setAddress(TTree&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
    void book(TTree&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
    void init();
    TTree* getInput() const { return input_; }

  protected:
    TTree* input_{0}; // set by setAddress
  };

  TTree* makePhotonL1ObjectTree();
  TTree* makePhotonHLTObjectTree();
  TTree* makeElectronHLTObjectTree();
  TTree* makeMuonHLTObjectTree();

}

#endif
