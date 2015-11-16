#include "MitFlat/Mods/interface/SimpleTreeMod.h"
#include "MitAna/DataTree/interface/EventHeader.h"
#include "MitAna/DataTree/interface/MCEventInfo.h"
#include "MitAna/DataTree/interface/MCRunInfo.h"
#include "MitAna/DataTree/interface/ParticleCol.h"
#include "MitAna/DataTree/interface/MetCol.h"
#include "MitAna/DataTree/interface/JetCol.h"
#include "MitAna/DataTree/interface/PhotonCol.h"
#include "MitAna/DataTree/interface/PFTauCol.h"
#include "MitAna/DataTree/interface/DecayParticleCol.h"
#include "MitAna/DataTree/interface/VertexCol.h"
#include "MitAna/DataTree/interface/PFCandidateCol.h"
#include "MitAna/DataTree/interface/VertexCol.h"
#include "MitAna/DataTree/interface/PileupEnergyDensityCol.h"
#include "MitAna/DataTree/interface/MCParticleCol.h"
#include "MitAna/DataTree/interface/GenJetCol.h"
#include "MitAna/DataTree/interface/TriggerMask.h"
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

#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>

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
mithep::SimpleTreeMod::Process()
{
  if (fDebug)
    Info("Process", "Begin event");

  auto* eventHeader = GetEventHeader();
  auto* energyDensity = GetObject<mithep::PileupEnergyDensityCol>(mithep::Names::gkPileupEnergyDensityBrn);

  fAllEvent.run = eventHeader->RunNum();
  fAllEvent.lumi = eventHeader->LumiSec();
  fAllEvent.event = eventHeader->EvtNum();
  fAllEvent.weight = 1.;
  fAllEvent.rho = energyDensity->At(0)->Rho(fRhoAlgo);
  
  mithep::MCEventInfo* mcEvent = 0;
  if (fIsMC) {
    mcEvent = GetObject<mithep::MCEventInfo>(mithep::Names::gkMCEvtInfoBrn);
    fAllEvent.weight = mcEvent->Weight();
  }

  fAllEventTree->Fill();

  if (fDebug)
    Info("Process", "Filled allevent");

  if (fCondition && !fCondition->IsActive())
    return;

  auto* vertices = GetObject<mithep::VertexCol>(fVerticesName);
  auto* pfCandidates = GetObject<mithep::PFCandidateCol>(Names::gkPFCandidatesBrn);
  auto* triggerMask = GetObject<mithep::TriggerMask>(mithep::Names::gkHltBitBrn);
  std::vector<MCParticle*> finalState;
  TVector3 genVertex;

  auto* toTable = GetObject<mithep::TriggerObjectsTable>(TString(Names::gkHltObjBrn) + "Fwk");
  TList const* toLists[simpletree::nHLTPaths]{};

  // basic event info

  if (fDebug)
    Info("Process", "Fill event info");

  fEvent.run = eventHeader->RunNum();
  fEvent.lumi = eventHeader->LumiSec();
  fEvent.event = eventHeader->EvtNum();
  fEvent.weight = 1.;
  fEvent.rho = energyDensity->At(0)->Rho(fRhoAlgo);
  fEvent.npv = vertices->GetEntries();

  // event weights

  if (fDebug)
    Info("Process", "Fill event weights");

  if (fIsMC) {
    fEvent.weight = mcEvent->Weight();

    unsigned iR(0);

    if (mcEvent->NReweightScaleFactors() > 8) {
      for (unsigned iW : {1, 2, 3, 4, 6, 8})
        fEvent.reweight[iR++].scale = mcEvent->ReweightScaleFactor(iW);
      for (unsigned id : fPdfReweightIds)
        fEvent.reweight[iR++].scale = mcEvent->ReweightScaleFactor(id);
    }
  }

  // gen particles

  if (fDebug)
    Info("Process", "Fill gen particles");
  
  if (fIsMC) {
    unsigned nP(0);
    std::map<unsigned, unsigned> partonMap;
    for (unsigned iP(0); iP != mcEvent->NPartons(); ++iP) {
      if (mcEvent->PartonStatus(iP) == -1)
        continue;

      int pid(mcEvent->PartonId(iP));
      auto& p4(*mcEvent->PartonMom(iP));

      partonMap[iP] = nP;

      auto& outParton(fEvent.partons[nP++]);

      fillP4_(outParton, p4);

      outParton.pid = pid;
      outParton.frixIso = false;

      if (pid == 22) {
        outParton.frixIso = true;

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
            outParton.frixIso = false;
            break;
          }
        }
      }
    }

    fEvent.partons.resize(nP);

    auto* mcParticles = GetObject<mithep::MCParticleCol>("MCParticles");
    for (unsigned iP(0); iP != mcParticles->GetEntries(); ++iP) {
      if (mcParticles->At(iP)->Status() == 1)
        finalState.push_back(mcParticles->At(iP));
    }

    auto&& decayVtx(mcParticles->At(0)->DecayVertex());
    genVertex.SetXYZ(decayVtx.X(), decayVtx.Y(), decayVtx.Z());

    unsigned nF(0);
    for (auto* mcp : finalState) {
      auto const* mother(mcp);
      // status 23: outgoing from hardest process
      while (mother && mother->Status() != 23)
        mother = mother->Mother();

      if (!mother)
        continue;

      unsigned motherId(std::abs(mother->PdgId()));
      if (motherId < 6 || motherId == 21)
        continue;

      auto& outFS(fEvent.partonFinalStates[nF++]);

      fillP4_(outFS, *mcp);

      outFS.pid = mcp->PdgId();

      outFS.ancestor = -1;
      double dRMin(-1.);
      for (unsigned iP(0); iP != mcEvent->NPartons(); ++iP) {
        if (mcEvent->PartonStatus(iP) != 1)
          continue;

        double dR(mithep::MathUtils::DeltaR(*mother, *mcEvent->PartonMom(iP)));
        if (dRMin < 0. || dR < dRMin) {
          outFS.ancestor = partonMap[iP];
          dRMin = dR;
        }
      }
    }
    fEvent.partonFinalStates.resize(nF);
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

  if (fDebug)
    Info("Process", "Fill triggers");

  for (unsigned iH(0); iH != simpletree::nHLTPaths; ++iH) {
    if (fHLTIds[iH] != -1) {
      fEvent.hlt[iH].pass = triggerMask->At(fHLTIds[iH]);
      if (fEvent.hlt[iH].pass)
        toLists[iH] = toTable->GetList(fHLTIds[iH]);
    }
    else
      fEvent.hlt[iH].pass = false;
  }

  // MET

  if (fDebug)
    Info("Process", "Fill MET");

  simpletree::Met* outMets[] = {
    &fEvent.rawMet,
    &fEvent.t1Met,
    &fEvent.genMet
  };

  TString metNames[] = {
    fRawMetName,
    fT1MetName,
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

    fEvent.photons.resize(photons->GetEntries());

    unsigned nP(0);
    for (unsigned iP(0); iP != photons->GetEntries(); ++iP) {
      auto& inPhoton(*photons->At(iP));
      if (inPhoton.Pt() < 10.)
        continue;

      auto& outPhoton(fEvent.photons[nP]);

      double chIso, nhIso, phIso;
      IsolationTools::PFEGIsoFootprintRemoved(&inPhoton, vertices->At(0), pfCandidates, 0.3, chIso, nhIso, phIso);
      double scEta(inPhoton.SCluster()->AbsEta());

      outPhoton.isEB = (scEta < mithep::gkPhoEBEtaMax);

      fillP4_(outPhoton, inPhoton);

      outPhoton.chIso = IsolationTools::PFPhotonIsolationRhoCorr(scEta, chIso, fEvent.rho, PhotonTools::kPhoEAPhys14, PhotonTools::kPhoChargedHadron03);
      outPhoton.nhIso = IsolationTools::PFPhotonIsolationRhoCorr(scEta, nhIso, fEvent.rho, PhotonTools::kPhoEAPhys14, PhotonTools::kPhoNeutralHadron03);
      if (outPhoton.isEB)
        outPhoton.nhIso -= std::exp(0.0028 * inPhoton.Pt() + 0.5408);
      else
        outPhoton.nhIso -= 0.01725 * inPhoton.Pt();
      outPhoton.phIso = IsolationTools::PFPhotonIsolationRhoCorr(scEta, phIso, fEvent.rho, PhotonTools::kPhoEAPhys14, PhotonTools::kPhoPhoton03);
      if (outPhoton.isEB)
        outPhoton.phIso -= 0.0014 * inPhoton.Pt();
      else
        outPhoton.phIso -= 0.0091 * inPhoton.Pt();
      outPhoton.sieie = inPhoton.CoviEtaiEta5x5();
      outPhoton.hOverE = inPhoton.HadOverEmTow();
      outPhoton.pixelVeto = !inPhoton.HasPixelSeed();
      outPhoton.csafeVeto = PhotonTools::PassElectronVetoConvRecovery(&inPhoton, electrons, conversions, vertices->At(0));
      outPhoton.loose = looseMask->At(iP);
      outPhoton.medium = mediumMask->At(iP);
      outPhoton.tight = tightMask->At(iP);
      outPhoton.highpt = highPtMask->At(iP);

      auto&& caloPos(inPhoton.CaloPos());

      bool* hltMatch[] = {
        &outPhoton.matchHLT120,
        &outPhoton.matchHLT135MET100,
        &outPhoton.matchHLT165HE10,
        &outPhoton.matchHLT175
      };
      simpletree::HLTPath hltPaths[] = {
        simpletree::kPhoton120,
        simpletree::kPhoton135MET100,
        simpletree::kPhoton165HE10,
        simpletree::kPhoton175
      };

      for (unsigned iT(0); iT != sizeof(hltMatch) / sizeof(bool*); ++iT) {
        simpletree::HLTPath iPath(hltPaths[iT]);
        if (!toLists[iPath]) {
          *hltMatch[iT] = false;
          continue;
        }

        int iO(0);
        for (; iO != toLists[iPath]->GetEntries(); ++iO) {
          auto& trigObj(*static_cast<mithep::TriggerObject*>(toLists[iPath]->At(iO)));
          double dEta(caloPos.Eta() - trigObj.Eta());
          double dPhi(TVector2::Phi_mpi_pi(caloPos.Phi() - trigObj.Phi()));
          if (dEta * dEta + dPhi * dPhi < 0.0225)
            break;
        }
        *hltMatch[iT] = (iO != toLists[iPath]->GetEntries());
      }

      outPhoton.matchedGen = 0;

      if (fIsMC) {
        // find matched gen
        // 22 -> gen photon with no matching parton
        // -22 -> gen photon with matching isolated parton
        // 11/-11 -> electrons
        // 111 -> everything else

        for (auto& fs : fEvent.partonFinalStates) {
          if (fs.pid != 22)
            continue;
          if (fs.ancestor >= fEvent.partons.size())
            continue;

          auto& parton(fEvent.partons[fs.ancestor]);
          if (parton.pid != 22 || !parton.frixIso)
            continue;

          TVector3 caloDir(caloPos.X(), caloPos.Y(), caloPos.Z());          
          caloDir -= genVertex;
          auto&& partP4(fs.p4());
          if (caloDir.DeltaR(TVector3(partP4.X(), partP4.Y(), partP4.Z())) < 0.1) {
            outPhoton.matchedGen = -22;
            break;
          }
        }

        if (outPhoton.matchedGen == 0) {
          mithep::MCParticle const* matched(0);
          double minDR(-1.);

          for (auto* part : finalState) {
            TVector3 caloDir(caloPos.X(), caloPos.Y(), caloPos.Z());          
            caloDir -= genVertex;

            double dR(caloDir.DeltaR(TVector3(part->Px(), part->Py(), part->Pz())));
            if (dR < 0.1 && (minDR < 0. || dR < minDR)) {
              outPhoton.matchedGen = part->PdgId();
              unsigned absId(std::abs(outPhoton.matchedGen));
              if (absId == 11 || absId == 13)
                break;

              minDR = dR;
              matched = part;
            }
          }

          if (outPhoton.matchedGen == 22 && matched) {
            auto* mother(matched->DistinctMother());
            if (!(mother->PdgId() == 2212 && !mother->HasMother()) && (mother->PdgId() == 21 || std::abs(mother->PdgId()) > 25))
              outPhoton.matchedGen = 111;
          }
        }
      }

      ++nP;
    }

    fEvent.photons.resize(nP);
  }

  TString* inputLeptonName[2] = {
    &fElectronsName,
    &fMuonsName
  };

  TString* tightMaskName[2] = {
    &fTightElectronsName,
    &fTightMuonsName
  };

  simpletree::LeptonCollection* outputCollection[2] = {
    &fEvent.electrons,
    &fEvent.muons
  };

  bool* eleHLTMatch[] = {
    fEvent.electrons.data.matchHLT23Loose,
    fEvent.electrons.data.matchHLT27Loose,
    fEvent.electrons.data.matchHLT120Ph,
    fEvent.electrons.data.matchHLT135MET100Ph,
    fEvent.electrons.data.matchHLT165HE10Ph,
    fEvent.electrons.data.matchHLT175Ph
  };
  bool* muHLTMatch[] = {
    fEvent.muons.data.matchHLT24,
    fEvent.muons.data.matchHLT27
  };

  bool** hltMatch[2] = {eleHLTMatch, muHLTMatch};

  simpletree::HLTPath eleHLTPaths[] = {
    simpletree::kEle23Loose,
    simpletree::kEle27Loose,
    simpletree::kPhoton120,
    simpletree::kPhoton135MET100,
    simpletree::kPhoton165HE10,
    simpletree::kPhoton175
  };
  simpletree::HLTPath muHLTPaths[] = {
    simpletree::kMu24,
    simpletree::kMu27
  };

  simpletree::HLTPath* hltPaths[2] = {eleHLTPaths, muHLTPaths};

  unsigned nHLTPaths[2] = {sizeof(eleHLTPaths) / sizeof(simpletree::HLTPath), sizeof(muHLTPaths) / sizeof(simpletree::HLTPath)};

  if (fDebug)
    Info("Process", "Fill leptons");

  for (unsigned iC(0); iC != 2; ++iC) {
    if (inputLeptonName[iC]->Length() != 0) {
      auto* leptons = GetObject<mithep::ParticleCol>(*inputLeptonName[iC]);
      if (!leptons) {
        SendError(kAbortAnalysis, "Process", *inputLeptonName[iC]);
        return;
      }

      mithep::NFArrBool* looseMask = 0;
      auto* tightMask = GetObject<mithep::NFArrBool>(*tightMaskName[iC]);
      if (iC == 0)
        looseMask = GetObject<mithep::NFArrBool>(fLooseElectronsName);

      outputCollection[iC]->resize(leptons->GetEntries());
      for (unsigned iL = 0; iL != leptons->GetEntries(); ++iL) {
        auto& inLepton(*leptons->At(iL));
        auto& outLepton((*outputCollection[iC])[iL]);

        fillP4_(outLepton, inLepton);

        outLepton.positive = inLepton.Charge() > 0.;
        outLepton.tight = tightMask->At(iL);

        if (iC == 0) {
          auto& inElectron(static_cast<mithep::Electron&>(inLepton));
          auto& outElectron(static_cast<simpletree::Electron&>(outLepton));

          outElectron.loose = looseMask->At(iL);
          outElectron.isEB = inElectron.SCluster()->AbsEta() < mithep::gkEleEBEtaMax;
          
          double chIso, nhIso, phIso;
          IsolationTools::PFEGIsoFootprintRemoved(&inElectron, vertices->At(0), pfCandidates, 0.3, chIso, nhIso, phIso);
          double scEta(inElectron.SCluster()->AbsEta());

          outElectron.chIsoPh = IsolationTools::PFPhotonIsolationRhoCorr(scEta, chIso, fEvent.rho, PhotonTools::kPhoEAPhys14, PhotonTools::kPhoChargedHadron03);
          outElectron.nhIsoPh = IsolationTools::PFPhotonIsolationRhoCorr(scEta, nhIso, fEvent.rho, PhotonTools::kPhoEAPhys14, PhotonTools::kPhoNeutralHadron03);
          outElectron.phIsoPh = IsolationTools::PFPhotonIsolationRhoCorr(scEta, phIso, fEvent.rho, PhotonTools::kPhoEAPhys14, PhotonTools::kPhoPhoton03);

          outElectron.sieie = inElectron.CoviEtaiEta5x5();
          outElectron.hOverE = inElectron.HadOverEmTow();
        }
        else {
          outLepton.loose = true;
        }

        for (unsigned iT(0); iT != nHLTPaths[iC]; ++iT) {
          simpletree::HLTPath iPath(hltPaths[iC][iT]);
          if (!toLists[iPath]) {
            hltMatch[iC][iT][iL] = false;
            continue;
          }

          int iO(0);
          for (; iO != toLists[iPath]->GetEntries(); ++iO) {
            auto& obj(*static_cast<mithep::TriggerObject*>(toLists[iPath]->At(iO)));
            if (mithep::MathUtils::DeltaR(inLepton, obj) < 0.1)
              break;
          }
          hltMatch[iC][iT][iL] = (iO != toLists[iPath]->GetEntries());
        }

        if (fIsMC) {
          outLepton.matchedGen = 0;

          double minDR(-1.);
          mithep::MCParticle* matched(0);

          for (auto* part : finalState) {
            double dR(mithep::MathUtils::DeltaR(inLepton, *part));
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
  }

  if (fDebug)
    Info("Process", "Fill taus");

  if (fTausName.Length() != 0) {
    auto* taus = GetObject<mithep::PFTauCol>(fTausName);
    if (!taus) {
      SendError(kAbortAnalysis, "Process", fTausName);
      return;
    }

    fEvent.taus.resize(taus->GetEntries());
    for (unsigned iT(0); iT != taus->GetEntries(); ++iT) {
      auto& inTau(*taus->At(iT));
      auto& outTau(fEvent.taus[iT]);

      fillP4_(outTau, inTau);

      outTau.decayMode = inTau.PFTauDiscriminator(mithep::PFTau::kDiscriminationByDecayModeFinding) > 0.5;
      outTau.combIso = inTau.PFTauDiscriminator(mithep::PFTau::kDiscriminationByRawCombinedIsolationDBSumPtCorr3Hits);
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

    fEvent.jets.resize(jets->GetEntries());
    for (unsigned iJ = 0; iJ != jets->GetEntries(); ++iJ) {
      auto& inJet(*jets->At(iJ));
      auto& outJet(fEvent.jets[iJ]);

      fillP4_(outJet, inJet);
    }
  }

  fEventTree->Fill();
}

void
mithep::SimpleTreeMod::SlaveBegin()
{
  auto* outputFile = TFile::Open(fOutputName, "recreate");
  outputFile->cd();

  fEventTree = new TTree(fEventTreeName, "Events");
  fEvent.book(*fEventTree);

  fAllEventTree = new TTree(fAllEventTreeName, "Events");
  fAllEvent.book(*fAllEventTree);

  simpletree::makeHLTPathTree();
}

void
mithep::SimpleTreeMod::SlaveTerminate()
{
  auto* outputFile = fEventTree->GetCurrentFile();
  outputFile->cd();

  fEventTree->Write();
  fAllEventTree->Write();
  delete outputFile;
}

void
mithep::SimpleTreeMod::BeginRun()
{
  auto* hltTable = GetObject<mithep::TriggerTable>(TString::Format("%sFwk", mithep::Names::gkHltTableBrn));
  mithep::TriggerName const* triggerName(0);

  for (unsigned iH(0); iH != simpletree::nHLTPaths; ++iH) {
    triggerName = hltTable->GetWildcard("HLT_" + fTriggerPathName[iH] + "_v");
    if (triggerName)
      fHLTIds[iH] = triggerName->Id();
    else
      fHLTIds[iH] = -1;
  }

  if (fIsMC && (fPdfReweightGroupNames.size() != 0 || fPdfReweightGroupIds.size() != 0)) {
    auto* mcRunInfo = GetMCRunInfo();

    for (auto& name : fPdfReweightGroupNames) {
      unsigned iG = 0;
      for (; iG != mcRunInfo->NWeightGroups(); ++iG) {
        if (name == mcRunInfo->WeightGroupType(iG))
          break;
      }
      if (iG == mcRunInfo->NWeightGroups()) {
        SendError(kAbortAnalysis, "BeginRun", "PDF reweight factor group " + name + " not found");
      }

      if (std::find(fPdfReweightGroupIds.begin(), fPdfReweightGroupIds.end(), iG) == fPdfReweightGroupIds.end());
      fPdfReweightGroupIds.push_back(iG);
    }

    fPdfReweightGroupNames.clear();

    for (unsigned gid : fPdfReweightGroupIds) {
      for (unsigned iC = 0; iC != mcRunInfo->NWeights(); ++iC) {
        if (mcRunInfo->WeightGroup(iC) != gid)
          continue;

        fPdfReweightIds.push_back(mcRunInfo->WeightPositionInEvent(iC));
      }
    }

    fPdfReweightGroupIds.clear();

    fEvent.reweight.resize(6 + fPdfReweightIds.size());
  }
}
