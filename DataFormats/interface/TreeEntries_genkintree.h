#ifndef TreeEntries_genkintree_h
#define TreeEntries_genkintree_h
#include "Collection.h"
#include "Objects_genkintree.h"

namespace genkintree {

  typedef flatutils::Collection<Particle, flatutils::BaseCollection<kFALSE>> ParticleCollection;
  typedef flatutils::Collection<Jet, ParticleCollection> JetCollection;
  typedef flatutils::Collection<Photon, ParticleCollection> PhotonCollection;

  class Event {
  public:
    Double_t weight{};
    PhotonCollection photons = PhotonCollection("photons");
    ParticleCollection electrons = ParticleCollection("electrons");
    ParticleCollection muons = ParticleCollection("muons");
    ParticleCollection neutrinos = ParticleCollection("neutrinos");
    JetCollection jets = JetCollection("jets");
    Met met = Met("met");

    void setStatus(TTree&, Bool_t, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
    void setAddress(TTree&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
    void book(TTree&, flatutils::BranchList const& = {"*"}, Bool_t whitelist = kTRUE);
  };

}

#endif
