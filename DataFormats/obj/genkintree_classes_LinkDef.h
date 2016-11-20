#include "/home/yiiyama/cms/studies/ewknlo/MitFlat/DataFormats/interface/TreeEntries_genkintree.h"

#ifdef __CLING__
#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;
#pragma link C++ nestedclass;
#pragma link C++ nestedtypedef;
#pragma link C++ namespace flatutils;
#pragma link C++ namespace genkintree;

#pragma link C++ class genkintree::Particle;
#pragma link C++ class genkintree::ParticleM;
#pragma link C++ class genkintree::Parton;
#pragma link C++ class genkintree::Boson;
#pragma link C++ class genkintree::Photon;
#pragma link C++ class genkintree::Lepton;
#pragma link C++ class genkintree::Met;
#pragma link C++ class flatutils::Collection<genkintree::Particle, flatutils::DynamicCollection>;
#pragma link C++ typedef genkintree::ParticleCollection;
#pragma link C++ class flatutils::Collection<genkintree::ParticleM, genkintree::ParticleCollection>;
#pragma link C++ typedef genkintree::ParticleMCollection;
#pragma link C++ class flatutils::Collection<genkintree::Parton, genkintree::ParticleCollection>;
#pragma link C++ typedef genkintree::PartonCollection;
#pragma link C++ class flatutils::Collection<genkintree::Boson, genkintree::ParticleMCollection>;
#pragma link C++ typedef genkintree::BosonCollection;
#pragma link C++ class flatutils::Collection<genkintree::Photon, genkintree::ParticleCollection>;
#pragma link C++ typedef genkintree::PhotonCollection;
#pragma link C++ class flatutils::Collection<genkintree::Lepton, genkintree::ParticleCollection>;
#pragma link C++ typedef genkintree::LeptonCollection;
#pragma link C++ class genkintree::Event;
#endif
