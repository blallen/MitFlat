#include "/home/ballen/cms/cmssw/044/CMSSW_8_0_7_patch3/src/MitFlat/DataFormats/interface/TreeEntries_simpletree.h"

#ifdef __CLING__
#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;
#pragma link C++ nestedclass;
#pragma link C++ nestedtypedef;
#pragma link C++ namespace flatutils;
#pragma link C++ namespace simpletree;

#pragma link C++ class simpletree::Particle;
#pragma link C++ class simpletree::ParticleM;
#pragma link C++ class simpletree::Jet;
#pragma link C++ class simpletree::Met;
#pragma link C++ class simpletree::CorrectedMet;
#pragma link C++ class simpletree::Photon;
#pragma link C++ class simpletree::Lepton;
#pragma link C++ class simpletree::Electron;
#pragma link C++ class simpletree::Muon;
#pragma link C++ class simpletree::Tau;
#pragma link C++ class simpletree::Parton;
#pragma link C++ class simpletree::MCParticle;
#pragma link C++ class simpletree::GenJet;
#pragma link C++ class simpletree::HLTBits;
#pragma link C++ class simpletree::MetFilters;
#pragma link C++ class flatutils::Collection<simpletree::Particle, flatutils::DynamicCollection>;
#pragma link C++ typedef simpletree::ParticleCollection;
#pragma link C++ class flatutils::Collection<simpletree::ParticleM, simpletree::ParticleCollection>;
#pragma link C++ typedef simpletree::ParticleMCollection;
#pragma link C++ class flatutils::Collection<simpletree::Jet, simpletree::ParticleMCollection>;
#pragma link C++ typedef simpletree::JetCollection;
#pragma link C++ class flatutils::Collection<simpletree::Photon, simpletree::ParticleCollection>;
#pragma link C++ typedef simpletree::PhotonCollection;
#pragma link C++ class flatutils::Collection<simpletree::Lepton, simpletree::ParticleCollection>;
#pragma link C++ typedef simpletree::LeptonCollection;
#pragma link C++ class flatutils::Collection<simpletree::Electron, simpletree::LeptonCollection>;
#pragma link C++ typedef simpletree::ElectronCollection;
#pragma link C++ class flatutils::Collection<simpletree::Muon, simpletree::LeptonCollection>;
#pragma link C++ typedef simpletree::MuonCollection;
#pragma link C++ class flatutils::Collection<simpletree::Tau, simpletree::ParticleMCollection>;
#pragma link C++ typedef simpletree::TauCollection;
#pragma link C++ class flatutils::Collection<simpletree::Parton, simpletree::ParticleMCollection>;
#pragma link C++ typedef simpletree::PartonCollection;
#pragma link C++ class flatutils::Collection<simpletree::MCParticle, simpletree::ParticleMCollection>;
#pragma link C++ typedef simpletree::MCParticleCollection;
#pragma link C++ class flatutils::Collection<simpletree::GenJet, simpletree::ParticleMCollection>;
#pragma link C++ typedef simpletree::GenJetCollection;
#pragma link C++ class simpletree::Event;
#pragma link C++ class simpletree::Run;
#endif
