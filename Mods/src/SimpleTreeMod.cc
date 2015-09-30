#include "MitFlat/Mods/interface/SimpleTreeMod.h"
#include "MitAna/DataTree/interface/EventHeader.h"
#include "MitAna/DataTree/interface/MCEventInfo.h"
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
#include "MitAna/DataTree/interface/TriggerMask.h"
#include "MitAna/DataTree/interface/TriggerTable.h"
#include "MitAna/DataTree/interface/TriggerObjectsTable.h"
#include "MitAna/DataTree/interface/TriggerObject.h"
#include "MitAna/DataTree/interface/Names.h"
#include "MitAna/DataCont/interface/Types.h"
#include "MitCommon/MathTools/interface/MathUtils.h"

#include "MitPhysics/Utils/interface/PhotonTools.h"
#include "MitPhysics/Utils/interface/IsolationTools.h"
#include "MitPhysics/Init/interface/Constants.h"

#include "TVector3.h"

#include <iostream>
#include <cstring>
#include <cmath>

ClassImp(mithep::SimpleTreeMod)

void
mithep::SimpleTreeMod::Process()
{
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

  if (fCondition && !fCondition->IsActive())
    return;

  auto* vertices = GetObject<mithep::VertexCol>(fVerticesName);
  auto* pfCandidates = GetObject<mithep::PFCandidateCol>(Names::gkPFCandidatesBrn);
  auto* triggerMask = GetObject<mithep::TriggerMask>(mithep::Names::gkHltBitBrn);
  mithep::MCParticleCol* mcParticles(0);
  std::vector<MCParticle*> finalState;

  auto* toTable = GetObject<mithep::TriggerObjectsTable>(TString(Names::gkHltObjBrn) + "Fwk");
  TList const* toLists[simpletree::nHLTPaths]{};

  fEvent.run = eventHeader->RunNum();
  fEvent.lumi = eventHeader->LumiSec();
  fEvent.event = eventHeader->EvtNum();
  fEvent.weight = 1.;
  fEvent.rho = energyDensity->At(0)->Rho(fRhoAlgo);
  fEvent.npv = vertices->GetEntries();

  for (unsigned iH(0); iH != simpletree::nHLTPaths; ++iH) {
    if (fHLTIds[iH] != -1) {
      fEvent.hlt[iH].pass = triggerMask->At(fHLTIds[iH]);
      if (fEvent.hlt[iH].pass)
        toLists[iH] = toTable->GetList(fHLTIds[iH]);
    }
    else
      fEvent.hlt[iH].pass = false;
  }

  if (fIsMC) {
    mcParticles = GetObject<mithep::MCParticleCol>("MCParticles");
    for (unsigned iP(0); iP != mcParticles->GetEntries(); ++iP) {
      if (mcParticles->At(iP)->Status() == 1)
        finalState.push_back(mcParticles->At(iP));
    }

    fEvent.weight = mcEvent->Weight();
    fEvent.genHt = 0.;
    fEvent.genBoson = 0;
    fEvent.genBosonPt = fEvent.genBosonEta = fEvent.genBosonPhi = fEvent.genBosonM = 0.;

    unsigned bosonIndex(-1);
    for (unsigned iP(0); iP != mcEvent->NPartons(); ++iP) {
      int pid(mcEvent->PartonId(iP));
      auto& p4(*mcEvent->PartonMom(iP));

      if (mcEvent->PartonStatus(iP) == 1 && pid != 12 && pid != 14 && pid != 16)
        fEvent.genHt += p4.Pt();

      if (pid == 23 || std::abs(pid) == 24) {
        fEvent.genBoson = pid;
        fEvent.genBosonPt = p4.Pt();
        fEvent.genBosonEta = p4.Eta();
        fEvent.genBosonPhi = p4.Phi();
        fEvent.genBosonM = p4.M();

        bosonIndex = iP + 1;
      }

      if (mcEvent->PartonMother1(iP) == bosonIndex || mcEvent->PartonMother2(iP) == bosonIndex) {
        if (pid > 10 && pid < 17) {
          fEvent.genLepton1 = pid;
          fEvent.genLepton1Pt = p4.Pt();
          fEvent.genLepton1Eta = p4.Eta();
          fEvent.genLepton1Phi = p4.Phi();
          fEvent.genLepton1M = p4.M();
        }
        else if (pid > -17 && pid < -10){
          fEvent.genLepton2 = pid;
          fEvent.genLepton2Pt = p4.Pt();
          fEvent.genLepton2Eta = p4.Eta();
          fEvent.genLepton2Phi = p4.Phi();
          fEvent.genLepton2M = p4.M();
        }
      }
    }
  }

  simpletree::Met* outMets[] = {
    &fEvent.rawMet,
    &fEvent.t1Met,
    &fEvent.t1NoCHSMet,
    &fEvent.nhScaledMet,
    &fEvent.chMet,
    &fEvent.nhMet,
    &fEvent.neMet
  };

  TString metNames[] = {
    fRawMetName,
    fT1MetName,
    fT1NoCHSMetName,
    fNHScaledMetName,
    fCHMetName,
    fNHMetName,
    fNEMetName
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

  if (fPhotonsName.Length() != 0) {
    auto* photons = GetObject<mithep::PhotonCol>(fPhotonsName);
    auto* electrons = GetObject<mithep::ElectronCol>(Names::gkElectronBrn);
    auto* conversions = GetObject<mithep::DecayParticleCol>(fConversionsName);

    auto* looseMask = GetObject<mithep::NFArrBool>(fLoosePhotonName);
    auto* mediumMask = GetObject<mithep::NFArrBool>(fMediumPhotonName);
    auto* tightMask = GetObject<mithep::NFArrBool>(fTightPhotonName);

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
      outPhoton.pt = inPhoton.Pt();
      outPhoton.eta = inPhoton.Eta();
      outPhoton.phi = inPhoton.Phi();
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
      outPhoton.hadDecay = false;
      outPhoton.drParton = -1.;

      if (fIsMC) {
        double minDR(-1.);
        mithep::MCParticle* matched(0);

        for (auto* part : finalState) {
          TVector3 caloDir(caloPos.X(), caloPos.Y(), caloPos.Z());
          auto&& vtx(part->Mother()->DecayVertex());
          caloDir -= TVector3(vtx.X(), vtx.Y(), vtx.Z());
          double dR(caloDir.DeltaR(TVector3(part->Px(), part->Py(), part->Pz())));
          if (dR < 0.1 && (minDR < 0. || dR < minDR)) {
            outPhoton.matchedGen = part->PdgId();
            unsigned absId(std::abs(outPhoton.matchedGen));
            if (dR < 0.1 && (absId == 11 || absId == 13))
              break;

            minDR = dR;
            matched = part;
          }
        }

        if (matched) {
          auto* mother(matched->DistinctMother());
          if ((mother->PdgId() == 2212 && !mother->HasMother()) || mother->StatusFlag(11)) // kFromHardProcessBeforeFSR
            outPhoton.hadDecay = false;
          else {
            unsigned motherId(std::abs(mother->PdgId()));
            outPhoton.hadDecay = (motherId == 21 || motherId > 25); // 21 probably never happens..
          }

          int iParton(-1);
          for (unsigned iP(0); iP != mcEvent->NPartons(); ++iP) {
            if (mcEvent->PartonId(iP) != 22)
              continue;

            auto& p4(*mcEvent->PartonMom(iP));
            if (mithep::MathUtils::DeltaR(p4, *matched) < 0.15) {
              iParton = iP;
              break;
            }
          }

          if (iParton != -1) {
            for (unsigned iP(0); iP != mcEvent->NPartons(); ++iP) {
              if (int(iP) == iParton)
                continue;

              double dR(mithep::MathUtils::DeltaR(mcEvent->PartonMom(iP), mcEvent->PartonMom(iParton)));
              if (outPhoton.drParton < 0. || dR < outPhoton.drParton)
                outPhoton.drParton = dR;
            }
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

  TString* looseMaskName[2] = {
    &fLooseElectronsName,
    &fLooseMuonsName
  };

  TString* mediumMaskName[2] = {
    &fMediumElectronsName,
    &fMediumMuonsName
  };

  TString* tightMaskName[2] = {
    &fTightElectronsName,
    &fTightMuonsName
  };

  simpletree::LeptonCollection* outputCollection[2] = {
    &fEvent.electrons,
    &fEvent.muons
  };

  bool* hltMatch[2][2] = {
    {
      fEvent.electrons.data.matchHLT23Loose,
      fEvent.electrons.data.matchHLT27Loose
    },
    {
      fEvent.muons.data.matchHLT24,
      fEvent.muons.data.matchHLT27
    }
  };

  simpletree::HLTPath hltPaths[2][2] = {
    {
      simpletree::kEle23Loose,
      simpletree::kEle27Loose
    },
    {
      simpletree::kMu24,
      simpletree::kMu27
    }
  };

  auto* puPF = GetObject<mithep::PFCandidateCol>(fPUPFCandidatesName);
  auto* pvPF = GetObject<mithep::PFCandidateCol>(fPVPFCandidatesName);

  for (unsigned iC(0); iC != 2; ++iC) {
    if (inputLeptonName[iC]->Length() != 0) {
      auto* leptons = GetObject<mithep::ParticleCol>(*inputLeptonName[iC]);
      if (!leptons) {
        SendError(kAbortAnalysis, "Process", *inputLeptonName[iC]);
        return;
      }

      auto* looseMask = GetObject<mithep::NFArrBool>(*looseMaskName[iC]);
      auto* mediumMask = GetObject<mithep::NFArrBool>(*mediumMaskName[iC]);
      auto* tightMask = GetObject<mithep::NFArrBool>(*tightMaskName[iC]);

      outputCollection[iC]->resize(leptons->GetEntries());
      for (unsigned iL = 0; iL != leptons->GetEntries(); ++iL) {
        auto& inLepton(*leptons->At(iL));
        auto& outLepton((*outputCollection[iC])[iL]);
        outLepton.pt = inLepton.Pt();
        outLepton.eta = inLepton.Eta();
        outLepton.phi = inLepton.Phi();
        outLepton.positive = inLepton.Charge() > 0.;
        outLepton.loose = looseMask->At(iL);
        outLepton.medium = mediumMask->At(iL);
        outLepton.tight = tightMask->At(iL);

        if (iC == 0) {
          auto& inElectron(static_cast<mithep::Electron&>(inLepton));
          auto& outElectron(static_cast<simpletree::Electron&>(outLepton));

          double scEta(inElectron.SCluster()->AbsEta());

          outElectron.isEB = (scEta < mithep::gkPhoEBEtaMax);

          outElectron.chIso = inElectron.PFChargedHadronIso();
          outElectron.nhIso = inElectron.PFNeutralHadronIso();
          outElectron.phIso = inElectron.PFPhotonIso();
          outElectron.puIso = IsolationTools::PFElectronIsolation(&inElectron, puPF, vertices->At(0), 10000., 0., 0.3, 0., mithep::PFCandidate::eHadron);
          outElectron.combRelIso = IsolationTools::PFEleCombinedIsolationRhoCorr(&inElectron, fEvent.rho, ElectronTools::kEleEASummer15) / inElectron.Pt();

          double chIso, nhIso, phIso;
          IsolationTools::PFEGIsoFootprintRemoved(&inElectron, vertices->At(0), pfCandidates, 0.3, chIso, nhIso, phIso);

          outElectron.chIsoPh = IsolationTools::PFPhotonIsolationRhoCorr(scEta, chIso, fEvent.rho, PhotonTools::kPhoEAPhys14, PhotonTools::kPhoChargedHadron03);
          outElectron.nhIsoPh = IsolationTools::PFPhotonIsolationRhoCorr(scEta, nhIso, fEvent.rho, PhotonTools::kPhoEAPhys14, PhotonTools::kPhoNeutralHadron03);
          outElectron.phIsoPh = IsolationTools::PFPhotonIsolationRhoCorr(scEta, phIso, fEvent.rho, PhotonTools::kPhoEAPhys14, PhotonTools::kPhoPhoton03);

          outElectron.sieie = inElectron.CoviEtaiEta5x5();
          outElectron.hOverE = inElectron.HadOverEmTow();
        }
        else {
          auto& inMuon(static_cast<mithep::Muon&>(inLepton));
          auto& outMuon(static_cast<simpletree::Muon&>(outLepton));

          double isoArr[4];
          double combIso(IsolationTools::BetaMwithPUCorrection(pvPF, puPF, &inMuon, 0.4, isoArr));

          outMuon.chIso = isoArr[0];
          outMuon.nhIso = isoArr[1];
          outMuon.phIso = isoArr[2];
          outMuon.puIso = isoArr[3];
          outMuon.combRelIso = combIso / inMuon.Pt();
        }

        for (unsigned iT(0); iT != 2; ++iT) {
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

  if (fTausName.Length() != 0) {
    auto* taus = GetObject<mithep::PFTauCol>(fTausName);
    if (!taus) {
      SendError(kAbortAnalysis, "Process", fTausName);
      return;
    }

    fEvent.ntau = taus->GetEntries();
  }

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
      outJet.pt = inJet.Pt();
      outJet.eta = inJet.Eta();
      outJet.phi = inJet.Phi();
      outJet.mass = inJet.Mass();
    }
  }

  fEventTree->Fill();
}

void
mithep::SimpleTreeMod::SlaveBegin()
{
  fEventTree = new TTree(fEventTreeName, "Events");
  fEvent.book(*fEventTree);

  fAllEventTree = new TTree(fAllEventTreeName, "Events");
  fAllEvent.book(*fAllEventTree);

  AddOutput(fEventTree);
  AddOutput(fAllEventTree);
  AddOutput(simpletree::makeHLTPathTree());
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
}
