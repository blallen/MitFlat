#ifndef TreeEntries_genkintree_h
#define TreeEntries_genkintree_h
#include "Collection.h"
#include "Objects_genkintree.h"

namespace genkintree {

  typedef flatutils::Collection<Particle, flatutils::DynamicCollection> ParticleCollection;
  typedef flatutils::Collection<ParticleM, ParticleCollection> ParticleMCollection;
  typedef flatutils::Collection<Parton, ParticleCollection> PartonCollection;
  typedef flatutils::Collection<Boson, ParticleMCollection> BosonCollection;
  typedef flatutils::Collection<Photon, ParticleCollection> PhotonCollection;
  typedef flatutils::Collection<Lepton, ParticleCollection> LeptonCollection;

  class Event {
  public:
    Event();

    Double_t weight{};
    PartonCollection partons = PartonCollection("partons");
    PhotonCollection photons = PhotonCollection("photons");
    LeptonCollection electrons = LeptonCollection("electrons");
    LeptonCollection muons = LeptonCollection("muons");
    ParticleCollection neutrinos = ParticleCollection("neutrinos");
    Boson boson = Boson();
    ParticleMCollection jets = ParticleMCollection("jets");
    Met met = Met("met");

    void setStatus(TTree&, Bool_t, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
    void setAddress(TTree&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
    void book(TTree&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
    void init();
    TTree* getInput() const { return input_; }

  protected:
    TTree* input_{0}; // set by setAddress
  };

}

#endif
