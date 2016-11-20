#include "../interface/SimpleTreeFiller.h"

void
fillP4(simpletree::Particle& _out, reco::Candidate const& _in)
{
  _out.pt = _in.pt();
  _out.eta = _in.eta();
  _out.phi = _in.phi();
}

void
fillP4(simpletree::ParticleM& _out, reco::Candidate const& _in)
{
  _out.pt = _in.pt();
  _out.eta = _in.eta();
  _out.phi = _in.phi();
  _out.mass = _in.mass();
}

void
fillP4(simpletree::RecoParticleM& _out, reco::Candidate const& _in)
{
  _out.pt = _in.pt();
  _out.eta = _in.eta();
  _out.phi = _in.phi();
  _out.mass = _in.mass();
}
