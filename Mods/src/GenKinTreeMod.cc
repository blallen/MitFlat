#include "../interface/GenKinTreeMod.h"

#include "MitAna/DataTree/interface/MCEventInfo.h"
#include "MitAna/DataTree/interface/MCParticleCol.h"
#include "MitAna/DataTree/interface/Names.h"

#include "TVector2.h"
#include "TVector3.h"
#include "TFile.h"

#include "fastjet/PseudoJet.hh"
#include "fastjet/ClusterSequence.hh"
#include "fastjet/ClusterSequenceArea.hh"

#include <vector>
#include <map>
#include <cmath>

ClassImp(mithep::GenKinTreeMod)

double const OneMinusCosDR(1. - std::cos(0.4));

class reverse_sort {
public:
  bool operator()(double lhs, double rhs) { return lhs > rhs; }
};

void
mithep::GenKinTreeMod::Process()
{
  auto* mcEventInfo(GetObject<mithep::MCEventInfo>(mithep::Names::gkMCEvtInfoBrn));
  auto* mcParticles(GetObject<mithep::MCParticleCol>(mithep::Names::gkMCPartBrn));

  fEvent.weight = mcEventInfo->Weight();

  std::vector<fastjet::PseudoJet> particles;

  std::map<double, unsigned, reverse_sort> iPhotons;
  std::map<double, unsigned, reverse_sort> iElectrons;
  std::map<double, unsigned, reverse_sort> iMuons;
  std::map<double, unsigned, reverse_sort> iNeutrinos;
  TVector2 metV;

  for (unsigned iP(0); iP != mcParticles->GetEntries(); ++iP) {
    auto& part(*mcParticles->At(iP));
    if (part.Status() != 1)
      continue;

    double pt(part.Pt());

    bool isNeutrino(false);
    switch (std::abs(part.PdgId())) {
    case 11:
      iElectrons.emplace(pt, iP);
      break;
    case 13:
      iMuons.emplace(pt, iP);
      break;
    case 12:
    case 14:
    case 16:
      iNeutrinos.emplace(pt, iP);
      metV -= TVector2(part.Px(), part.Py());
      isNeutrino = true;
      break;
    case 22:
      iPhotons.emplace(pt, iP);
      break;
    default:
      break;
    }

    if (isNeutrino || pt < 1.e-6)
      continue;

    particles.emplace_back(part.Px(), part.Py(), part.Pz(), part.E());
    particles.back().set_user_index(iP);
  }

  auto* clustering(new fastjet::ClusterSequenceArea(particles, *fJetDef, *fAreaDef));
  auto&& clustered(fastjet::sorted_by_pt(clustering->inclusive_jets(20.)));

  if (clustered.size() > 0)
    clustering->delete_self_when_unused();

  unsigned iJ(0);
  for (auto&& inJet : clustered) {
    auto& jet(fEvent.jets[iJ]);
    jet.pt = inJet.pt();
    jet.eta = inJet.eta();
    jet.phi = inJet.phi();
    jet.mass = inJet.m();
    ++iJ;
  }
  fEvent.jets.resize(iJ);

  unsigned iPh(0);
  for (auto& pt2I : iPhotons) {
    auto& inPhoton(*mcParticles->At(pt2I.second));
    if (inPhoton.Pt() < 10.)
      break;

    auto& photon(fEvent.photons[iPh]);

    std::map<double, double> isoDep;
    for (auto& part : particles) {
      if (part.user_index() == int(pt2I.second))
        continue;

      double dEta(inPhoton.Eta() - part.eta());
      double dPhi(TVector2::Phi_mpi_pi(inPhoton.Phi() - part.phi()));
      double dR(std::sqrt(dEta * dEta + dPhi * dPhi));
      if (dR < 0.4)
        isoDep.emplace(dR, part.e());
    }

    double isoSum(0.);
    double maxReduced(0.);
    for (auto&& iso : isoDep) {
      isoSum += iso.second;
      double reduced(isoSum * OneMinusCosDR / (1. - std::cos(iso.first)));
      if (reduced > maxReduced)
        maxReduced = reduced;
    }
    photon.isot = maxReduced * std::sin(inPhoton.Theta());

    photon.pt = inPhoton.Pt();
    photon.eta = inPhoton.Eta();
    photon.phi = inPhoton.Phi();
    ++iPh;
  }
  fEvent.photons.resize(iPh);

  unsigned iEl(0);
  for (auto& pt2I : iElectrons) {
    auto& inElectron(*mcParticles->At(pt2I.second));
    if (inElectron.Pt() < 2.)
      break;

    auto& electron(fEvent.electrons[iEl]);

    electron.pt = inElectron.Pt();
    electron.eta = inElectron.Eta();
    electron.phi = inElectron.Phi();
    ++iEl;
  }
  fEvent.electrons.resize(iEl);

  unsigned iMu(0);
  for (auto& pt2I : iMuons) {
    auto& inMuon(*mcParticles->At(pt2I.second));
    if (inMuon.Pt() < 2.)
      break;

    auto& muon(fEvent.muons[iMu]);

    muon.pt = inMuon.Pt();
    muon.eta = inMuon.Eta();
    muon.phi = inMuon.Phi();
    ++iMu;
  }
  fEvent.muons.resize(iMu);

  unsigned iNu(0);
  for (auto& pt2I : iNeutrinos) {
    auto& inNeutrino(*mcParticles->At(pt2I.second));

    auto& neutrino(fEvent.neutrinos[iNu]);

    neutrino.pt = inNeutrino.Pt();
    neutrino.eta = inNeutrino.Eta();
    neutrino.phi = inNeutrino.Phi();
    ++iNu;
  }
  fEvent.neutrinos.resize(iPh);

  fEvent.met.pt = metV.Mod();
  fEvent.met.phi = TVector2::Phi_mpi_pi(metV.Phi());

  fEventTree->Fill();

  delete clustering;
}

void
mithep::GenKinTreeMod::SlaveBegin()
{
  fGAS = new fastjet::GhostedAreaSpec(7., 1, 0.01);
  fAreaDef = new fastjet::AreaDefinition(fastjet::active_area_explicit_ghosts, *fGAS);
  fJetDef = new fastjet::JetDefinition(fastjet::antikt_algorithm, 0.4);

  auto* outputFile(TFile::Open(fOutputName, "recreate"));
  outputFile->cd();

  fEventTree = new TTree(fEventTreeName, "Events");
  fEvent.book(*fEventTree);
}

void
mithep::GenKinTreeMod::SlaveTerminate()
{
  delete fGAS;
  delete fAreaDef;
  delete fJetDef;

  auto* outputFile(fEventTree->GetCurrentFile());
  outputFile->cd();
  outputFile->Write();
  delete outputFile;
}
