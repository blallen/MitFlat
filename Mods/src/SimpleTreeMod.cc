#include "MitFlat/Mods/interface/SimpleTreeMod.h"
#include "MitAna/DataTree/interface/EventHeader.h"
#include "MitAna/DataTree/interface/RunInfo.h"
#include "MitAna/DataTree/interface/MCEventInfo.h"
#include "MitAna/DataTree/interface/MCRunInfo.h"
#include "MitAna/DataTree/interface/ParticleCol.h"
#include "MitAna/DataTree/interface/MetCol.h"
#include "MitAna/DataTree/interface/JetCol.h"
#include "MitAna/DataTree/interface/PFJet.h"
#include "MitAna/DataTree/interface/PhotonCol.h"
#include "MitAna/DataTree/interface/PFTauCol.h"
#include "MitAna/DataTree/interface/DecayParticleCol.h"
#include "MitAna/DataTree/interface/VertexCol.h"
#include "MitAna/DataTree/interface/PFCandidateCol.h"
#include "MitAna/DataTree/interface/VertexCol.h"
#include "MitAna/DataTree/interface/PileupEnergyDensityCol.h"
#include "MitAna/DataTree/interface/MCParticleCol.h"
#include "MitAna/DataTree/interface/GenJetCol.h"
#include "MitAna/DataTree/interface/PileupInfoCol.h"
#include "MitAna/DataTree/interface/TriggerMask.h"
#include "MitAna/DataTree/interface/TriggerName.h"
#include "MitAna/DataTree/interface/TriggerTable.h"
#include "MitAna/DataTree/interface/TriggerObjectsTable.h"
#include "MitAna/DataTree/interface/TriggerObject.h"
#include "MitAna/DataTree/interface/Names.h"
#include "MitAna/DataCont/interface/Types.h"
#include "MitCommon/MathTools/interface/MathUtils.h"
#include "MitCommon/DataFormats/interface/Types.h"

#include "MitPhysics/Utils/interface/PhotonTools.h"
#include "MitPhysics/Utils/interface/IsolationTools.h"
#include "MitPhysics/Init/interface/Constants.h"

#include "TVector3.h"
#include "TObjArray.h"

#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <functional>
#include <vector>

ClassImp(mithep::SimpleTreeMod)

void
fillP4_(simpletree::Particle& _out, mithep::Particle const& _in)
{
  _out.pt = _in.Pt();
  _out.eta = _in.Eta();
  _out.phi = _in.Phi();
}

void
fillP4_(simpletree::ParticleM& _out, mithep::Particle const& _in)
{
  _out.pt = _in.Pt();
  _out.eta = _in.Eta();
  _out.phi = _in.Phi();
  _out.mass = _in.Mass();
}

void
fillP4_(simpletree::ParticleM& _out, mithep::FourVector const& _in)
{
  _out.pt = _in.Pt();
  _out.eta = _in.Eta();
  _out.phi = _in.Phi();
  _out.mass = _in.M();
}

void
fillP4_(simpletree::ParticleM& _out, mithep::FourVectorM const& _in)
{
  _out.pt = _in.Pt();
  _out.eta = _in.Eta();
  _out.phi = _in.Phi();
  _out.mass = _in.M();
}

void
mithep::SimpleTreeMod::SetPhotonL1ModuleName(char const* f, char const* n)
{
  unsigned iF(std::find(simpletree::PhotonL1ObjectName, simpletree::PhotonL1ObjectName + simpletree::nPhotonL1Objects, f) - simpletree::PhotonL1ObjectName);
  if (iF == simpletree::nPhotonL1Objects)
    return;

  fPhotonL1ModuleName[iF] = n;
}

void
mithep::SimpleTreeMod::SetPhotonTriggerModuleName(char const* f, char const* n)
{
  unsigned iF(std::find(simpletree::PhotonHLTObjectName, simpletree::PhotonHLTObjectName + simpletree::nPhotonHLTObjects, f) - simpletree::PhotonHLTObjectName);
  if (iF == simpletree::nPhotonHLTObjects)
    return;

  fPhotonTriggerModuleName[iF] = n;
}

void
mithep::SimpleTreeMod::SetElectronTriggerModuleName(char const* f, char const* n)
{
  unsigned iF(std::find(simpletree::ElectronHLTObjectName, simpletree::ElectronHLTObjectName + simpletree::nElectronHLTObjects, f) - simpletree::ElectronHLTObjectName);
  if (iF == simpletree::nElectronHLTObjects)
    return;

  fElectronTriggerModuleName[iF] = n;
}

void
mithep::SimpleTreeMod::SetMuonTriggerModuleName(char const* f, char const* n)
{
  unsigned iF(std::find(simpletree::MuonHLTObjectName, simpletree::MuonHLTObjectName + simpletree::nMuonHLTObjects, f) - simpletree::MuonHLTObjectName);
  if (iF == simpletree::nMuonHLTObjects)
    return;

  fMuonTriggerModuleName[iF] = n;
}

void
mithep::SimpleTreeMod::Process()
{
  if (fDebug)
    Info("Process", "Begin event");

  fEventCounter->Fill(0.5, 1.);

  auto* eventHeader = GetEventHeader();

  mithep::MCEventInfo* mcEvent = 0;
  if (fIsMC) {
    mcEvent = GetObject<mithep::MCEventInfo>(mithep::Names::gkMCEvtInfoBrn);

    double weight = mcEvent->Weight();

    double centralReweight(1.);
    if (fCentralReweightId != -1)
      centralReweight = mcEvent->ReweightScaleFactor(fCentralReweightId);

    weight *= centralReweight;

    fEventCounter->Fill(1.5, weight);

    double binCenter(2.5);
    if (mcEvent->NReweightScaleFactors() != 0) {
      for (unsigned iW : {1, 2, 3, 4, 6, 8}) {
        fEventCounter->Fill(binCenter, weight * mcEvent->ReweightScaleFactor(iW));
        binCenter += 1.;
      }
    }

    // compatible only with Monte Carlo PDF reweights
    double sumd2(0.);
    for (unsigned id : fPdfReweightIds) {
      double d(mcEvent->ReweightScaleFactor(id) - centralReweight);
      sumd2 += d * d;
    }
    double dw(std::sqrt(sumd2 / (fPdfReweightIds.size() - 1)));
    fEventCounter->Fill(8.5, weight * (1. + dw));
    fEventCounter->Fill(9.5, weight * (1. - dw));
  }
  else
    fEventCounter->Fill(1.5, 1.);

  if (fDebug)
    Info("Process", "Filled event counter");

  if (fCondition && !fCondition->IsActive())
    return;

  fEvent.init();

  auto* vertices = GetObject<mithep::VertexCol>(fVerticesName);
  auto* pfCandidates = GetObject<mithep::PFCandidateCol>(Names::gkPFCandidatesBrn);
  auto* energyDensity = GetObject<mithep::PileupEnergyDensityCol>(mithep::Names::gkPileupEnergyDensityBrn);
  std::vector<mithep::MCParticle const*> finalState;
  std::vector<mithep::MCParticle const*> promptFinalState;
  TVector3 genVertex;

  // basic event info

  if (fDebug)
    Info("Process", "Fill event info");

  fEvent.run = eventHeader->RunNum();
  fEvent.lumi = eventHeader->LumiSec();
  fEvent.event = eventHeader->EvtNum();
  fEvent.rho = energyDensity->At(0)->Rho(fRhoAlgo);
  fEvent.npv = vertices->GetEntries();

  if (fIsMC) {
    auto* puInfo = GetObject<mithep::PileupInfoCol>("PileupInfo");
    fEvent.npvTrue = 0.;
    for (unsigned iP = 0; iP != puInfo->GetEntries(); ++iP) {
      auto& pu(*puInfo->At(iP));
      if (pu.GetBunchCrossing() == 0)
        fEvent.npvTrue += pu.GetPU_NumMean();
    }
  }

  // event weights

  if (fDebug)
    Info("Process", "Fill event weights");

  if (fIsMC) {
    fEvent.weight = mcEvent->Weight();

    double centralReweight(1.);
    if (fCentralReweightId != -1)
      centralReweight = mcEvent->ReweightScaleFactor(fCentralReweightId);

    fEvent.weight *= centralReweight;

    if (mcEvent->NReweightScaleFactors() != 0) {
      unsigned iR(0);
      for (unsigned iW : {1, 2, 3, 4, 6, 8})
        fEvent.scaleReweight[iR++] = mcEvent->ReweightScaleFactor(iW);
    }

    // compatible only with Monte Carlo PDF reweights
    double sumd2(0.);
    for (unsigned id : fPdfReweightIds) {
      double d(mcEvent->ReweightScaleFactor(id) - centralReweight);
      sumd2 += d * d;
    }
    fEvent.pdfDW = std::sqrt(sumd2 / (fPdfReweightIds.size() - 1));
  }

  // met filters

  if (!fIsMC && fMetFilterName.Length() != 0) {
    auto* filterNames = GetObject<TObjArray>(fMetFilterName + "Names");
    auto* filterResults = GetObject<NFArrBool>(fMetFilterName);

    fEvent.metFilters.cschalo = false;
    fEvent.metFilters.globalHalo16 = false;
    fEvent.metFilters.hbhe = false;
    fEvent.metFilters.hbheIso = false;
    fEvent.metFilters.badsc = false;
    fEvent.metFilters.badTrack = false;
    fEvent.metFilters.badMuonTrack = false;

    for (unsigned iF(0); iF != filterResults->GetEntries(); ++iF) {
      TString name(filterNames->At(iF)->GetName());

      if (name == "CSCTightHaloFilter")
        fEvent.metFilters.cschalo |= filterResults->At(iF);
      else if (name == "GlobalTightHaloFilter")
        fEvent.metFilters.globalHalo16 |= filterResults->At(iF);
      else if (name == "HBHENoiseFilter")
        fEvent.metFilters.hbhe |= filterResults->At(iF);
      else if (name == "HBHENoiseIsoFilter")
        fEvent.metFilters.hbheIso |= filterResults->At(iF);
      else if (name == "EEBadScFilter")
        fEvent.metFilters.badsc |= filterResults->At(iF);
      else if (name == "BadChargedCandidateFilter")
        fEvent.metFilters.badTrack |= filterResults->At(iF);
      else if (name == "BadPFMuonFilter")
        fEvent.metFilters.badMuonTrack |= filterResults->At(iF);
      else
        SendError(kWarning, "Process", "MET filter " + name + " is not supported");
    }
  }

  // gen particles

  if (fDebug)
    Info("Process", "Fill gen particles");
  
  if (fIsMC) {
    unsigned nP(0);
    for (unsigned iP(0); iP != mcEvent->NPartons(); ++iP) {
      if (mcEvent->PartonStatus(iP) != 1)
        continue;

      int pid(mcEvent->PartonId(iP));
      unsigned absId(std::abs(pid));

      auto& p4(*mcEvent->PartonMom(iP));

      auto& outParton(fEvent.partons[nP++]);

      fillP4_(outParton, p4);

      if (absId > 127) {
        if (absId % 1000000 < 40) { // "SUSY Particles". Also used for dark matter
          if (pid > 0)
            pid = (pid % 1000000) + 64;
          else
            pid = (pid % 1000000) - 64;
        }
        else // unknown!
          pid = 0;
      }

      if (pid == 22) {
        // Check Frixione isolation on photons
        std::map<double, double> isoDep;
        for (unsigned iQ(0); iQ != mcEvent->NPartons(); ++iQ) {
          if (iQ == iP || mcEvent->PartonStatus(iQ) != 1)
            continue;

          double dR(mithep::MathUtils::DeltaR(p4, *mcEvent->PartonMom(iQ)));
          if (dR < 0.4)
            isoDep.emplace(dR, mcEvent->PartonMom(iQ)->E());
        }
        double isoSum(0.);
        for (auto iso : isoDep) {
          double dR(iso.first);
          isoSum += iso.second;
          if (isoSum > mcEvent->PartonMom(iP)->E() * 1. * ((1. - std::cos(dR)) / (1. - std::cos(0.4)))/*to the n=1 power*/) {
            pid = -22; // photon not isolated; call it "anti-photon"
            break;
          }
        }
      }

      outParton.pid = pid;
    }

    fEvent.partons.resize(nP);

    auto* mcParticles = GetObject<mithep::MCParticleCol>("MCParticles");
    for (unsigned iP(0); iP != mcParticles->GetEntries(); ++iP) {
      if (mcParticles->At(iP)->Status() == 1)
        finalState.push_back(mcParticles->At(iP));
    }

    auto&& decayVtx(mcParticles->At(0)->DecayVertex());
    genVertex.SetXYZ(decayVtx.X(), decayVtx.Y(), decayVtx.Z());

    for (auto* mcp : finalState) {
      auto const* mother(mcp);

      while (mother) {
        unsigned mId(mother->AbsPdgId());
        if ((mother->Status() == 2 || (mother->Status() > 70 && mother->Status() < 100)) && ((mId / 100) % 10 != 0 || mId < 7 || mId == 21 || mId == 13 || mId == 15)) {
          // mother is a decaying lepton or hadron
          auto* copy = mother;
          while (true) {
            auto* daughter = copy->FindDaughter(copy->PdgId(), true);
            if (daughter)
              copy = daughter;
            else
              break;
          }
          if (copy == mother) {
            // mother is the last copy
            break;
          }
        }

        mother = mother->Mother();
      }

      if (mother) // is a decay product
        continue;

      fEvent.promptFinalStates.resize(fEvent.promptFinalStates.size() + 1);
      promptFinalState.push_back(mcp);

      auto& outFS(fEvent.promptFinalStates.back());

      fillP4_(outFS, *mcp);
      outFS.pid = mcp->PdgId();

      outFS.ancestor = -1;
      for (unsigned iP(0); iP != fEvent.partons.size(); ++iP) {
        auto& parton(fEvent.partons[iP]);
        if (parton.dR2(outFS) < 0.0225) {
          outFS.ancestor = iP;
          break;
        }
      }
    }
  }

  // gen jet

  if (fDebug)
    Info("Process", "Fill gen jets");

  if (fIsMC && fGenJetsName.Length() != 0) {
    auto* genJets = GetObject<mithep::GenJetCol>(fGenJetsName);
    fEvent.genJets.resize(genJets->GetEntries());

    for (unsigned iJ(0); iJ != genJets->GetEntries(); ++iJ) {
      auto& inJet(*genJets->At(iJ));
      auto& outJet(fEvent.genJets[iJ]);

      fillP4_(outJet, inJet);
    }
  }

  // triggers

  std::vector<mithep::TriggerObject const*> photonL1Objects[simpletree::nPhotonL1Objects];
  std::vector<mithep::TriggerObject const*> photonHLTObjects[simpletree::nPhotonHLTObjects];
  std::vector<mithep::TriggerObject const*> electronHLTObjects[simpletree::nElectronHLTObjects];
  std::vector<mithep::TriggerObject const*> muonHLTObjects[simpletree::nMuonHLTObjects];

  if (fUseTrigger) {
    if (fDebug)
      Info("Process", "Fill triggers");

    for (auto& word : fEvent.hltBits.words)
      word = 0;

    auto* triggerMask = GetObject<mithep::TriggerMask>(mithep::Names::gkHltBitBrn);

    for (unsigned iH(0); iH != fHLTIds.size(); ++iH) {
      unsigned short hltId(fHLTIds[iH]);
      if (triggerMask->At(hltId))
        fEvent.hltBits.set(iH);
    }

    auto* triggerObjects = GetObject<mithep::TriggerObjectCol>(TString(Names::gkHltObjBrn) + "Arr");

    for (unsigned iO(0); iO != triggerObjects->GetEntries(); ++iO) {
      auto& obj(*triggerObjects->At(iO));

      for (unsigned iF(0); iF != simpletree::nPhotonL1Objects; ++iF) {
        if (fPhotonL1ModuleName[iF] == obj.ModuleName()) {
          photonL1Objects[iF].push_back(&obj);
          break;
        }
      }

      for (unsigned iF(0); iF != simpletree::nPhotonHLTObjects; ++iF) {
        if (fPhotonTriggerModuleName[iF] == obj.ModuleName()) {
          photonHLTObjects[iF].push_back(&obj);
          break;
        }
      }

      for (unsigned iF(0); iF != simpletree::nElectronHLTObjects; ++iF) {
        if (fElectronTriggerModuleName[iF] == obj.ModuleName()) {
          electronHLTObjects[iF].push_back(&obj);
          break;
        }
      }

      for (unsigned iF(0); iF != simpletree::nMuonHLTObjects; ++iF) {
        if (fMuonTriggerModuleName[iF] == obj.ModuleName()) {
          muonHLTObjects[iF].push_back(&obj);
          break;
        }
      }
    }
  }

  // MET

  if (fDebug)
    Info("Process", "Fill MET");

  simpletree::Met* outMets[] = {
    &fEvent.rawMet,
    &fEvent.t1Met,
    &fEvent.caloMet,
    &fEvent.genMet
  };

  TString metNames[] = {
    fRawMetName,
    fT1MetName,
    fCaloMetName,
    fGenMetName
  };

  for (unsigned iM = 0; iM != sizeof(outMets) / sizeof(simpletree::Met*); ++iM) {
    if (metNames[iM].Length() == 0)
      continue;

    auto* mets = GetObject<mithep::MetCol>(metNames[iM]);
    if (!mets) {
      SendError(kAbortAnalysis, "Process", metNames[iM]);
      return;
    }
    auto& inMet(*mets->At(0));
    auto& outMet(*outMets[iM]);
    outMet.met = inMet.Pt();
    outMet.phi = inMet.Phi();
    outMet.sumEt = inMet.SumEt();
  }

  TString varNames[] = {
    fCorrUpMetName,
    fCorrDownMetName,
    fJetResMetName,
    fUnclUpMetName,
    fUnclDownMetName
  };

  float* varMets[][2] = {
    {&fEvent.t1Met.metCorrUp, &fEvent.t1Met.phiCorrUp},
    {&fEvent.t1Met.metCorrDown, &fEvent.t1Met.phiCorrDown},
    {&fEvent.t1Met.metJetRes, &fEvent.t1Met.phiJetRes},
    {&fEvent.t1Met.metUnclUp, &fEvent.t1Met.phiUnclUp},
    {&fEvent.t1Met.metUnclDown, &fEvent.t1Met.phiUnclDown}
  };

  for (unsigned iV(0); iV != sizeof(varNames) / sizeof(TString); ++iV) {
    auto& name(varNames[iV]);
    float& met(*varMets[iV][0]);
    float& phi(*varMets[iV][1]);

    if (name.Length() != 0) {
      auto* mets = GetObject<mithep::MetCol>(name);
      if (!mets) {
        SendError(kAbortAnalysis, "Process", name);
        return;
      }
      auto& inMet(*mets->At(0));
      met = inMet.Pt();
      phi = inMet.Phi();
    }
  }

  if (fDebug)
    Info("Process", "Fill photons");

  if (fPhotonsName.Length() != 0) {
    auto* photons = GetObject<mithep::PhotonCol>(fPhotonsName);
    auto* electrons = GetObject<mithep::ElectronCol>(Names::gkElectronBrn);
    auto* conversions = GetObject<mithep::DecayParticleCol>(fConversionsName);

    auto* looseMask = GetObject<mithep::NFArrBool>(fLoosePhotonName);
    auto* mediumMask = GetObject<mithep::NFArrBool>(fMediumPhotonName);
    auto* tightMask = GetObject<mithep::NFArrBool>(fTightPhotonName);
    auto* highPtMask = GetObject<mithep::NFArrBool>(fHighPtPhotonName);

    unsigned nP(0);
    for (unsigned iP(0); iP != photons->GetEntries(); ++iP) {
      auto& inPhoton(*photons->At(iP));
      if (inPhoton.Pt() < 10.)
        continue;

      auto& superCluster(*inPhoton.SCluster());
      auto& seedCluster(*superCluster.Seed());

      fEvent.photons.resize(nP + 1);
      auto& outPhoton(fEvent.photons[nP++]);

      double scEta(superCluster.AbsEta());

      outPhoton.scRawPt = superCluster.RawEnergy() / std::cosh(scEta);

      outPhoton.isEB = (scEta < mithep::gkPhoEBEtaMax);

      fillP4_(outPhoton, inPhoton);

      double chIso, nhIso, phIso;
      IsolationTools::PFEGIsoFootprintRemoved(&inPhoton, vertices->At(0), pfCandidates, 0.3, chIso, nhIso, phIso);
      PhotonTools::IsoLeakageCorrection(&inPhoton, PhotonTools::EPhIsoType(fPhotonIsoType), chIso, nhIso, phIso);

      // save the maximum iso with no rho correction
      double chIsoMax(chIso);

      PhotonTools::IsoRhoCorrection(&inPhoton, PhotonTools::EPhIsoType(fPhotonIsoType), fEvent.rho, chIso, nhIso, phIso);
      outPhoton.chIso = chIso;
      outPhoton.nhIso = nhIso;
      outPhoton.phIso = phIso;

      // compare to the chIso without rho correction using other vertices
      for (unsigned iV(1); iV < vertices->GetEntries(); ++iV) {
        IsolationTools::PFEGIsoFootprintRemoved(&inPhoton, vertices->At(iV), pfCandidates, 0.3, chIso, nhIso, phIso);
        PhotonTools::IsoLeakageCorrection(&inPhoton, PhotonTools::EPhIsoType(fPhotonIsoType), chIso, nhIso, phIso);
        if (chIso > chIsoMax)
          chIsoMax = chIso;
      }

      outPhoton.chIsoMax = chIsoMax;

      outPhoton.ecalIso = inPhoton.EcalPFClusterIso();
      outPhoton.hcalIso = inPhoton.HcalPFClusterIso();

      // PFWorst iso is not done quite right, but we'll play along
      double chWorstIso = IsolationTools::PFChargedIsolation(&inPhoton, 0, 0.3, 0., pfCandidates, 0, vertices);

      // Bhawna's measurements https://indico.cern.ch/event/497362/contribution/0/attachments/1229353/1801307/Monophoton_checks_meeting16Feb.pdf
      if (scEta < 1.)
        chWorstIso -= 0.078 * fEvent.rho;
      else if (scEta < 1.5)
        chWorstIso -= 0.089 * fEvent.rho;

      outPhoton.chWorstIso = std::max(chWorstIso, 0.);

      outPhoton.sieie = inPhoton.CoviEtaiEta5x5();
      outPhoton.sipip = inPhoton.CoviPhiiPhi();
      outPhoton.sieip = inPhoton.CoviEtaiPhi();
      outPhoton.hOverE = inPhoton.HadOverEmTow();

      outPhoton.mipEnergy = inPhoton.MipTotEnergy();
      outPhoton.mipChi2 = inPhoton.MipChi2();
      outPhoton.mipSlope = inPhoton.MipSlope();
      outPhoton.mipIntercept = inPhoton.MipIntercept();
      outPhoton.mipNhitCone = inPhoton.MipNhitCone();
      outPhoton.mipIsHalo = inPhoton.MipIsHalo();
      outPhoton.scPt = superCluster.Et();
      outPhoton.scEta = superCluster.Eta();
      outPhoton.scPhi = superCluster.Phi();
      outPhoton.e13 = seedCluster.E1x3();
      outPhoton.e31 = seedCluster.E3x1();
      outPhoton.e15 = inPhoton.E15();
      outPhoton.e22 = seedCluster.E2x2();
      outPhoton.e25 = inPhoton.E25();
      outPhoton.e33 = inPhoton.E33();
      outPhoton.e44 = seedCluster.E4x4();
      outPhoton.e55 = inPhoton.E55();
      outPhoton.emax = seedCluster.EMax();
      outPhoton.e2nd = seedCluster.E2nd();
      outPhoton.e4 = seedCluster.ETop() + seedCluster.ERight() + seedCluster.EBottom() + seedCluster.ELeft();
      outPhoton.r9 = inPhoton.R9();
      outPhoton.etaWidth = inPhoton.EtaWidth();
      outPhoton.phiWidth = inPhoton.PhiWidth();
      outPhoton.time = superCluster.SeedTime();
      outPhoton.timeSpan = superCluster.LeadTimeSpan();
      outPhoton.pixelVeto = !inPhoton.HasPixelSeed();
      outPhoton.electronVeto = true;
      for (unsigned iE(0); iE != electrons->GetEntries(); ++iE) {
        if (electrons->At(iE)->SCluster() == &superCluster) {
          outPhoton.electronVeto = false;
          break;
        }
      }
      outPhoton.csafeVeto = PhotonTools::PassElectronVetoConvRecovery(&inPhoton, electrons, conversions, vertices->At(0));
      outPhoton.loose = looseMask->At(iP);
      outPhoton.medium = mediumMask->At(iP);
      outPhoton.tight = tightMask->At(iP);
      outPhoton.highpt = highPtMask->At(iP);

      auto&& caloPos(inPhoton.CaloPos());

      if (fUseTrigger) {
        for (unsigned iF(0); iF != simpletree::nPhotonL1Objects; ++iF) {
          outPhoton.matchL1[iF] = false;

          for (auto* obj : photonL1Objects[iF]) {
            double dEta(caloPos.Eta() - obj->Eta());
            double dPhi(TVector2::Phi_mpi_pi(caloPos.Phi() - obj->Phi()));
            if (dEta * dEta + dPhi * dPhi < 0.09) {
              outPhoton.matchL1[iF] = true;
              break;
            }
          }
        }

        for (unsigned iF(0); iF != simpletree::nPhotonHLTObjects; ++iF) {
          outPhoton.matchHLT[iF] = false;

          for (auto* obj : photonHLTObjects[iF]) {
            double dEta(caloPos.Eta() - obj->Eta());
            double dPhi(TVector2::Phi_mpi_pi(caloPos.Phi() - obj->Phi()));
            if (dEta * dEta + dPhi * dPhi < 0.0225) {
              outPhoton.matchHLT[iF] = true;
              break;
            }
          }
        }
      }

      outPhoton.genMatchDR = -1.;
      outPhoton.matchedGen = 0;
      outPhoton.genIso = 0.;

      if (fIsMC) {
        // find matched gen
        // 22 -> gen photon with no matching parton
        // -22 -> gen photon with matching isolated parton
        // 11/-11 -> electrons
        // 111 -> everything else

        TVector3 caloDir(caloPos.X(), caloPos.Y(), caloPos.Z());          
        caloDir -= genVertex;

        mithep::MCParticle const* matched(0);

        for (unsigned iFS(0); iFS != fEvent.promptFinalStates.size(); ++iFS) {
          auto& fs(fEvent.promptFinalStates[iFS]);
          if (fs.pid != 22)
            continue;
          if (fs.ancestor >= fEvent.partons.size())
            continue;

          auto& parton(fEvent.partons[fs.ancestor]);
          if (parton.pid != 22) // 22: frixione-isolated photon
            continue;

          auto&& partP4(fs.p4());
          double dR(caloDir.DeltaR(TVector3(partP4.X(), partP4.Y(), partP4.Z())));
          if (dR < 0.1) {
            matched = promptFinalState[iFS];
            outPhoton.genMatchDR = dR;
            outPhoton.matchedGen = -22;
            break;
          }
        }

        if (!matched) {
          double minDR(-1.);
          bool leptonMatched(false);

          for (auto* part : finalState) {
            double dR(caloDir.DeltaR(TVector3(part->Px(), part->Py(), part->Pz())));
            if (dR > 0.1)
              continue;

            bool isLepton(part->AbsPdgId() == 11 || part->AbsPdgId() == 13);

            if (minDR < 0. || isLepton || (dR < minDR && !leptonMatched)) {
              outPhoton.genMatchDR = dR;
              outPhoton.matchedGen = part->PdgId();

              minDR = dR;
              if (isLepton)
                leptonMatched = true;

              matched = part;
            }
          }

          if (outPhoton.matchedGen == 22 && matched) {
            auto* mother(matched->DistinctMother());
            if (!(mother->PdgId() == 2212 && !mother->HasMother()) && std::abs(mother->PdgId()) > 25)
              outPhoton.matchedGen = 111;
          }
        }

        if (matched) {
          for (auto* part : finalState) {
            if (part == matched)
              continue;

            double dR(mithep::MathUtils::DeltaR(*part, *matched));
            if (dR < 0.3)
              outPhoton.genIso += part->Pt();
          }
        }
      }
    }
  }

  if (fElectronsName.Length() != 0) {
    if (fDebug)
      Info("Process", "Fill electrons");

    auto* electrons = GetObject<mithep::ElectronCol>(fElectronsName);
    if (!electrons) {
      SendError(kAbortAnalysis, "Process", fElectronsName);
      return;
    }

    auto* vetoMask = GetObject<mithep::NFArrBool>(fVetoElectronsName);
    auto* looseMask = GetObject<mithep::NFArrBool>(fLooseElectronsName);
    auto* tightMask = GetObject<mithep::NFArrBool>(fTightElectronsName);

    fEvent.electrons.resize(electrons->GetEntries());

    for (unsigned iE = 0; iE != electrons->GetEntries(); ++iE) {
      auto& inElectron(*electrons->At(iE));
      auto& outElectron(fEvent.electrons[iE]);

      fillP4_(outElectron, inElectron);

      outElectron.positive = inElectron.Charge() > 0.;
      outElectron.tight = tightMask->At(iE);

      outElectron.veto = vetoMask->At(iE);
      outElectron.loose = looseMask->At(iE);
      outElectron.isEB = inElectron.SCluster()->AbsEta() < mithep::gkEleEBEtaMax;
          
      double chIso, nhIso, phIso;
      IsolationTools::PFEGIsoFootprintRemoved(&inElectron, vertices->At(0), pfCandidates, 0.3, chIso, nhIso, phIso);
      double combRelIso(ElectronTools::CombinedIsoRhoCorr(ElectronTools::EElIsoType(fElectronIsoType), chIso, nhIso + phIso, fEvent.rho, inElectron.SCluster()->AbsEta()) / inElectron.Pt());

      PhotonTools::IsoLeakageCorrection(PhotonTools::EPhIsoType(fPhotonIsoType), inElectron.Et(), inElectron.SCluster()->AbsEta(), chIso, nhIso, phIso);
      PhotonTools::IsoRhoCorrection(PhotonTools::EPhIsoType(fPhotonIsoType), fEvent.rho, inElectron.SCluster()->AbsEta(), chIso, nhIso, phIso);

      outElectron.chIsoPh = chIso;
      outElectron.nhIsoPh = nhIso;
      outElectron.phIsoPh = phIso;

      outElectron.combRelIso = combRelIso;
      outElectron.ecalIso = inElectron.EcalPFClusterIso();
      outElectron.hcalIso = inElectron.HcalPFClusterIso();

      outElectron.sieie = inElectron.CoviEtaiEta5x5();
      outElectron.sipip = inElectron.CoviPhiiPhi();
      outElectron.sieip = inElectron.CoviEtaiPhi();
      outElectron.hOverE = inElectron.HadOverEmTow();

      if (fUseTrigger) {
        for (unsigned iF(0); iF != simpletree::nElectronHLTObjects; ++iF) {
          outElectron.matchHLT[iF] = false;

          for (auto* obj : electronHLTObjects[iF]) {
            double dEta(outElectron.eta - obj->Eta());
            double dPhi(TVector2::Phi_mpi_pi(outElectron.phi - obj->Phi()));
            if (dEta * dEta + dPhi * dPhi < 0.0225) {
              outElectron.matchHLT[iF] = true;
              break;
            }
          }
        }
      }
    }
  }

  if (fMuonsName.Length() != 0) {
    if (fDebug)
      Info("Process", "Fill muons");

    auto* muons = GetObject<mithep::MuonCol>(fMuonsName);
    if (!muons) {
      SendError(kAbortAnalysis, "Process", fMuonsName);
      return;
    }

    auto* tightMask = GetObject<mithep::NFArrBool>(fTightMuonsName);
    auto* pileupCands = GetObject<mithep::PFCandidateCol>(fPileupCandsName);

    fEvent.muons.resize(muons->GetEntries());

    for (unsigned iM = 0; iM != muons->GetEntries(); ++iM) {
      auto& inMuon(*muons->At(iM));
      auto& outMuon(fEvent.muons[iM]);

      fillP4_(outMuon, inMuon);

      outMuon.positive = inMuon.Charge() > 0.;
      outMuon.tight = tightMask->At(iM);

      outMuon.loose = true;
      outMuon.combRelIso = IsolationTools::BetaMwithPUCorrection(pfCandidates, pileupCands, &inMuon, 0.4) / outMuon.pt;

      if (fUseTrigger) {
        for (unsigned iF(0); iF != simpletree::nMuonHLTObjects; ++iF) {
          outMuon.matchHLT[iF] = false;

          for (auto* obj : muonHLTObjects[iF]) {
            double dEta(outMuon.eta - obj->Eta());
            double dPhi(TVector2::Phi_mpi_pi(outMuon.phi - obj->Phi()));
            if (dEta * dEta + dPhi * dPhi < 0.0225) {
              outMuon.matchHLT[iF] = true;
              break;
            }
          }
        }
      }
    }
  }

  if (fIsMC) {
    simpletree::LeptonCollection* leptonCollections[] = {&fEvent.electrons, &fEvent.muons};
    for (auto* leptons : leptonCollections) {
      for (auto& outLepton : *leptons) {
        outLepton.matchedGen = 0;

        double minDR(-1.);
        mithep::MCParticle const* matched(0);

        for (auto* part : finalState) {
          double dEta(part->Eta() - outLepton.eta);
          double dPhi(TVector2::Phi_mpi_pi(part->Phi() - outLepton.phi));
          double dR(std::sqrt(dEta * dEta + dPhi * dPhi));

          if (dR < 0.05 && (minDR < 0. || dR < minDR)) {
            outLepton.matchedGen = part->PdgId();

            minDR = dR;
            matched = part;
          }
        }

        if (matched) {
          auto* mother(matched->DistinctMother());
          if ((mother->PdgId() == 2212 && !mother->HasMother()) || mother->StatusFlag(11)) // kFromHardProcessBeforeFSR
            outLepton.tauDecay = outLepton.hadDecay = false;
          else {
            unsigned motherId(std::abs(mother->PdgId()));
            outLepton.tauDecay = (motherId == 15);
            outLepton.hadDecay = (motherId == 21 || motherId > 25);
          }
        }
        else {
          outLepton.tauDecay = outLepton.hadDecay = false;
        }
      }
    }
  }

  if (fTausName.Length() != 0) {
    auto* taus = GetObject<mithep::PFTauCol>(fTausName);
    if (!taus) {
      SendError(kAbortAnalysis, "Process", fTausName);
      return;
    }

    if (fDebug)
      Info("Process", "Fill taus: input %d", taus->GetEntries());

    unsigned nT(0);
    for (unsigned iT(0); iT != taus->GetEntries(); ++iT) {
      auto& inTau(*taus->At(iT));

      if (!inTau.PFTauIdentifier(mithep::PFTau::iDecayModeFindingNewDMs))
        continue;

      fEvent.taus.resize(nT + 1);
      auto& outTau(fEvent.taus[nT++]);

      fillP4_(outTau, inTau);

      outTau.decayMode = inTau.PFTauIdentifier(mithep::PFTau::iDecayModeFinding);
      outTau.combIso = inTau.PFTauDiscriminant(mithep::PFTau::dByCombinedIsolationDeltaBetaCorrRaw3Hits);
    }
  }

  if (fDebug)
    Info("Process", "Fill jets");

  if (fJetsName.Length() != 0) {
    auto* jets = GetObject<mithep::JetCol>(fJetsName);
    if (!jets) {
      SendError(kAbortAnalysis, "Process", fJetsName);
      return;
    }

    auto* looseMask = GetObject<mithep::NFArrBool>(fLooseJetsName);

    auto* jetsCorrUp = GetObject<mithep::JetCol>(fJetsCorrUpName);
    auto* jetsCorrDown = GetObject<mithep::JetCol>(fJetsCorrDownName);
    mithep::JetCol* jetsResCorr(0);
    if (fJetsResCorrName.Length() != 0)
      jetsResCorr = GetObject<mithep::JetCol>(fJetsResCorrName);

    unsigned nJ(0);

    for (unsigned iJ = 0; iJ != jets->GetEntries(); ++iJ) {
      if (!looseMask->At(iJ))
        continue;

      auto& outJet(fEvent.jets[nJ]);

      double maxPt(0.);

      auto& inJet(*jets->At(iJ));
      maxPt = inJet.Pt();

      mithep::JetCol* corrs[] = {
        jetsCorrUp,
        jetsCorrDown,
        jetsResCorr,
      };
      float* targs[] = {
        &outJet.ptCorrUp,
        &outJet.ptCorrDown,
        &outJet.ptResCorr,
      };

      for (unsigned iC(0); iC != sizeof(corrs) / sizeof(mithep::JetCol*); ++iC) {
        if (corrs[iC]) {
          double pt(corrs[iC]->At(iJ)->Pt());
          *targs[iC] = pt;
          if (pt > maxPt)
            maxPt = pt;
        }
      }

      if (maxPt < fMinJetPt)
        continue;

      ++nJ;

      fillP4_(outJet, inJet);

      auto&& pRaw(inJet.RawMom());

      outJet.ptRaw = pRaw.Pt();

      if (jetsResCorr)
        outJet.phiResCorr = jetsResCorr->At(iJ)->Phi();

      if (inJet.ObjType() == mithep::kPFJet) {
        auto& inPFJet(static_cast<PFJet const&>(inJet));
        double eRaw(pRaw.E());
        outJet.medium = (inPFJet.NeutralHadronEnergy() / eRaw < 0.8 && inPFJet.ChargedHadronEnergy() / eRaw > 0.1);
      }

      outJet.cisv = inJet.BJetTagsDisc(mithep::Jet::kCombinedInclusiveSecondaryVertexV2);
    }

    fEvent.jets.resize(nJ);
  }

  fEvent.vertices.resize(vertices->GetEntries());

  for (unsigned iV(0); iV != vertices->GetEntries(); ++iV) {
    auto& vertex(*vertices->At(iV));
    auto& outVertex(fEvent.vertices[iV]);

    outVertex.x = vertex.X();
    outVertex.y = vertex.Y();
    outVertex.z = vertex.Z();
    outVertex.ntrk = vertex.NTracks();
    outVertex.sumPt2 = 0.;
    for (unsigned iT(0); iT != vertex.NTracks(); ++iT)
      outVertex.sumPt2 += std::pow(vertex.Trk(iT)->Pt(), 2.);
  }

  fEventTree->Fill();
}

void
mithep::SimpleTreeMod::SlaveBegin()
{
  auto* outputFile = TFile::Open(fOutputName, "recreate");
  outputFile->cd();

  fEventTree = new TTree("events", "Events");

  flatutils::BranchList unusedBranches;

  if (fIsMC)
    unusedBranches = {
      "metFilters",
    };
  else
    unusedBranches = {
      "weight",
      "scaleReweight",
      "pdfDW",
      "npvTrue",
      "partons",
      "promptFinalStates",
      "genJets",
      "genMet",
      "jets.ptResCorr",
      "jets.phiResCorr",
      "t1Met.metJetRes",
      "t1Met.phiJetRes",
      "*.genIso",
      "*.matchedGen",
      "*.genMatchDR",
      "*.tauDecay",
      "*.hadDecay"
    };

  if (!fPhotonDetails) {
    for (auto& bname : flatutils::BranchList{
      "photons.mipChi2",
      "photons.mipSlope",
      "photons.mipIntercept",
      "photons.mipNhitCone",
      "photons.mipIsHalo",
      "photons.e13",
      "photons.e31",
      "photons.e15",
      "photons.e22",
      "photons.e25",
      "photons.e33",
      "photons.e44",
      "photons.e55",
      "photons.emax",
      "photons.e2nd",
      "photons.e4",
      "photons.etaWidth",
      "photons.phiWidth",
      "photons.timeSpan"
        })
      unusedBranches.push_back(bname);
  }

  if (!fUseTrigger) {
    unusedBranches.emplace_back("hltBits");
    unusedBranches.emplace_back("*.matchHLT");
    unusedBranches.emplace_back("*.matchL1");
  }

  unusedBranches.emplace_back("superClusters");

  fEvent.book(*fEventTree, unusedBranches, false);

  fRunTree = new TTree("runs", "Runs");
  fRun.book(*fRunTree);

  if (fUseTrigger) {
    fHLTTree = new TTree("hlt", "HLT");
    fHLTPaths = new std::vector<TString>;
    fHLTTree->Branch("paths", "std::vector<TString>", &fHLTPaths);
  }

  if (fIsMC)
    fEventCounter = new TH1D("counter", "", 10, 0, 10.);
  else
    fEventCounter = new TH1D("counter", "", 2, 0., 2.);

  fEventCounter->GetXaxis()->SetBinLabel(1, "NEntries");
  fEventCounter->GetXaxis()->SetBinLabel(2, "SumW");
  if (fIsMC) {
    fEventCounter->GetXaxis()->SetBinLabel(3, "muR=1 muF=2");
    fEventCounter->GetXaxis()->SetBinLabel(4, "muR=1 muF=0.5");
    fEventCounter->GetXaxis()->SetBinLabel(5, "muR=2 muF=1");
    fEventCounter->GetXaxis()->SetBinLabel(6, "muR=2 muF=2");
    fEventCounter->GetXaxis()->SetBinLabel(7, "muR=0.5 muF=1");
    fEventCounter->GetXaxis()->SetBinLabel(8, "muR=0.5 muF=2");
    fEventCounter->GetXaxis()->SetBinLabel(9, "NNPDF up");
    fEventCounter->GetXaxis()->SetBinLabel(10, "NNPDF down");
  }
}

void
mithep::SimpleTreeMod::SlaveTerminate()
{
  auto* outputFile = fEventTree->GetCurrentFile();
  outputFile->cd();

  fEventTree->Write();
  fRunTree->Write();
  if (fUseTrigger)
    fHLTTree->Write();
  fEventCounter->Write();
  delete outputFile;

  delete fHLTPaths;
}

void
mithep::SimpleTreeMod::BeginRun()
{
  mithep::RunInfo const* runInfo = GetRunInfo();
  fRun.run = runInfo->RunNum();  

  if (fUseTrigger) {
    if (runInfo->HltEntry() != fCurrentTriggerTable) {
      fCurrentTriggerTable = runInfo->HltEntry();

      fHLTIds.clear();

      // HLT tables are not IDed in Bambu -> need to actually extract all path names to compare the menus across files
      auto* hltTable = GetObject<mithep::TriggerTable>(TString::Format("%sFwk", mithep::Names::gkHltTableBrn));
      TString allPaths;
      for (auto* triggerName : *hltTable) {
        allPaths += triggerName->GetName();
        allPaths += " ";

        if (std::strstr(triggerName->GetName(), "HLT_") == triggerName->GetName())
          fHLTIds.push_back(static_cast<mithep::TriggerName const*>(triggerName)->Id());
      }

      auto ttItr(fTriggerTableMap.find(allPaths));
      if (ttItr != fTriggerTableMap.end())
        fRun.hltMenu = ttItr->second;
      else {
        fRun.hltMenu = fTriggerTableMap.size();
        fTriggerTableMap[allPaths] = fRun.hltMenu;

        fHLTPaths->clear();

        auto* paths(allPaths.Tokenize(" "));
        for (auto* path : *paths) {
          if (std::strstr(path->GetName(), "HLT_") == path->GetName())
            fHLTPaths->emplace_back(path->GetName());
        }
        delete paths;

        fHLTTree->Fill();
      }
    }
  }

  fRunTree->Fill();

  if (fIsMC) {
    if (fPdfReweightName.Length() != 0) {
      auto* mcRunInfo = GetMCRunInfo();

      TString groupName;
      int groupId(-1);

      if (fPdfReweightName == "amc_74")
        groupName = "PDF_variation";
      else if (fPdfReweightName == "mg5_74")
        groupName = "NNPDF30_lo_as_0130.LHgrid";
      else if (fPdfReweightName == "pwhg_74")
        groupId = 1;

      if (groupId == -1) {
        unsigned iG = 0;
        for (; iG != mcRunInfo->NWeightGroups(); ++iG) {
          if (groupName == mcRunInfo->WeightGroupType(iG))
            break;
        }
        if (iG == mcRunInfo->NWeightGroups()) {
          SendError(kAbortAnalysis, "BeginRun", "PDF reweight factor group " + groupName + " not found");
        }

        groupId = iG;
      }

      if (groupId != -1) {
        for (unsigned iC = 0; iC != mcRunInfo->NWeights(); ++iC) {
          if (mcRunInfo->WeightGroup(iC) != groupId)
            continue;

          fPdfReweightIds.push_back(mcRunInfo->WeightPositionInEvent(iC));
        }
      }

      if (fPdfReweightName == "mg5_74") {
        auto minItr(std::min_element(fPdfReweightIds.begin(), fPdfReweightIds.end()));
        fCentralReweightId = *minItr;
        fPdfReweightIds.erase(minItr);
      }
    }
  }
}

Bool_t
mithep::SimpleTreeMod::Notify()
{
  fCurrentTriggerTable = -1;
  return true;
}
