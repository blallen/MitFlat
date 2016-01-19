#include "TreeEntries_genkintree.h"

#ifdef __CLING__
#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;
#pragma link C++ nestedclass;
#pragma link C++ nestedtypedef;
#pragma link C++ namespace flatutils;
#pragma link C++ namespace genkintree;

#pragma link C++ class genkintree::Particle;
#pragma link C++ class genkintree::Jet;
#pragma link C++ class genkintree::Photon;
#pragma link C++ class genkintree::Met;
#pragma link C++ class flatutils::Collection<genkintree::Particle, flatutils::BaseCollection<kFALSE>>;
#pragma link C++ typedef genkintree::ParticleCollection;
#pragma link C++ class flatutils::Collection<genkintree::Jet, genkintree::ParticleCollection>;
#pragma link C++ typedef genkintree::JetCollection;
#pragma link C++ class flatutils::Collection<genkintree::Photon, genkintree::ParticleCollection>;
#pragma link C++ typedef genkintree::PhotonCollection;
#pragma link C++ class genkintree::Event;
#endif
