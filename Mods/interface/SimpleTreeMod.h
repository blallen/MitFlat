#ifndef MITFLAT_MODS_SIMPLETREEMOD_H
#define MITFLAT_MODS_SIMPLETREEMOD_H

#include "MitAna/TreeMod/interface/BaseMod.h"
#include "MitFlat/DataFormats/interface/TreeEntries_simpletree.h"
#include "MitPhysics/Utils/interface/PhotonTools.h"
#include "MitPhysics/Utils/interface/ElectronTools.h"

#include "TString.h"
#include "TTree.h"
#include "TH1D.h"

namespace mithep {

  class SimpleTreeMod : public BaseMod {
  public:
    SimpleTreeMod(char const* name = "SimpleTreeMod", char const* title = "Fill flat ntuples") : BaseMod(name, title) {}
    ~SimpleTreeMod() {}

    void SetEventTreeName(char const* n) { fEventTreeName = n; }
    void SetRhoAlgo(UInt_t a) { fRhoAlgo = a; }
    void SetJetsName(char const* n) { fJetsName = n; }
    void SetJetsCorrUpName(char const* n) { fJetsCorrUpName = n; }
    void SetJetsCorrDownName(char const* n) { fJetsCorrDownName = n; }
    void SetPhotonsName(char const* n) { fPhotonsName = n; }
    void SetPhotonIsoType(UInt_t i) { fPhotonIsoType = i; }
    void SetElectronsName(char const* n) { fElectronsName = n; }
    void SetElectronIsoType(UInt_t i) { fElectronIsoType = i; }
    void SetVetoElectronsName(char const* n) { fVetoElectronsName = n; }
    void SetLooseElectronsName(char const* n) { fLooseElectronsName = n; }
    void SetTightElectronsName(char const* n) { fTightElectronsName = n; }
    void SetMuonsName(char const* n) { fMuonsName = n; }
    void SetTightMuonsName(char const* n) { fTightMuonsName = n; }
    void SetTausName(char const* n) { fTausName = n; }
    void SetConversionsName(char const* n) { fConversionsName = n; }
    void SetVerticesName(char const* n) { fVerticesName = n; }
    void SetLoosePhotonName(char const* n) { fLoosePhotonName = n; }
    void SetMediumPhotonName(char const* n) { fMediumPhotonName = n; }
    void SetTightPhotonName(char const* n) { fTightPhotonName = n; }
    void SetHighPtPhotonName(char const* n) { fHighPtPhotonName = n; }
    void SetPileupCandsName(char const* n) { fPileupCandsName = n; }
    void SetRawMetName(char const* n) { fRawMetName = n; }
    void SetT1MetName(char const* n) { fT1MetName = n; }
    void SetCorrUpMetName(char const* n) { fCorrUpMetName = n; }
    void SetCorrDownMetName(char const* n) { fCorrDownMetName = n; }
    void SetUnclUpMetName(char const* n) { fUnclUpMetName = n; }
    void SetUnclDownMetName(char const* n) { fUnclDownMetName = n; }
    void SetGenMetName(char const* n) { fGenMetName = n; }
    void SetGenJetsName(char const* n) { fGenJetsName = n; }
    void SetUseTrigger(Bool_t b) { fUseTrigger = b; }
    void SetPhotonTriggerModuleName(UInt_t p, char const* n) { fPhotonTriggerModuleName[p] = n; }
    void SetElectronTriggerModuleName(UInt_t p, char const* n) { fElectronTriggerModuleName[p] = n; }
    void SetMuonTriggerModuleName(UInt_t p, char const* n) { fMuonTriggerModuleName[p] = n; }
    void SetTriggerPathName(UInt_t p, char const* n) { fTriggerPathName[p] = n; }
    void AddPdfReweightGroup(char const* n) { fPdfReweightGroupNames.push_back(n); }
    void AddPdfReweightId(UInt_t id) { fPdfReweightGroupIds.push_back(id); }
    void SetMetFilterName(char const* n) { fMetFilterName = n; }
    void SetIsMC(Bool_t k) { fIsMC = k; }

    void SetCondition(BaseMod* m) { fCondition = m; }
    void SetOutputName(char const* p) { fOutputName = p; }

    void SetDebug(Bool_t d) { fDebug = d; }

  protected:
    void Process() override;
    void SlaveBegin() override;
    void SlaveTerminate() override;
    void BeginRun() override;

    // output
    TString fOutputName{"simpletree.root"};
    TString fEventTreeName{"events"};
    TTree* fEventTree{0};
    TH1D* fEventCounter{0};
    simpletree::Event fEvent;

    // input
    UInt_t fRhoAlgo{0};
    TString fVerticesName{"PrimaryVertexes"};
    TString fJetsName{"AKt4PFJets"};
    TString fJetsCorrUpName{""};
    TString fJetsCorrDownName{""};
    TString fPhotonsName{"Photons"};
    UInt_t fPhotonIsoType{PhotonTools::kSpring15MediumIso};
    TString fElectronsName{"Electrons"};
    UInt_t fElectronIsoType{ElectronTools::kSummer15LooseIso};
    TString fVetoElectronsName{"VetoElectrons"};
    TString fLooseElectronsName{"LooseElectrons"};
    TString fTightElectronsName{"TightElectrons"};
    TString fMuonsName{"Muons"};
    TString fTightMuonsName{"TightMuons"};
    TString fTausName{"HPSTaus"};
    TString fConversionsName{"Conversions"};
    TString fLoosePhotonName{"LoosePhotons"};
    TString fMediumPhotonName{"MediumPhotons"};
    TString fTightPhotonName{"TightPhotons"};
    TString fHighPtPhotonName{"HighPtPhotons"};
    TString fPileupCandsName{"PileupCandidates"};
    TString fRawMetName{"PFMet"};
    TString fT1MetName{""};
    TString fCorrUpMetName{""};
    TString fCorrDownMetName{""};
    TString fUnclUpMetName{""};
    TString fUnclDownMetName{""};
    TString fGenMetName{""};
    TString fGenJetsName{""};
    Bool_t fUseTrigger{kTRUE};
    TString fPhotonTriggerModuleName[simpletree::nPhotonHLTObjects]{};
    TString fElectronTriggerModuleName[simpletree::nElectronHLTObjects]{};
    TString fMuonTriggerModuleName[simpletree::nMuonHLTObjects]{};
    TString fTriggerPathName[simpletree::nHLTPaths]{};
    std::vector<TString> fPdfReweightGroupNames{};
    std::vector<UInt_t> fPdfReweightGroupIds{};
    std::vector<unsigned> fPdfReweightIds{};
    TString fMetFilterName{""};

    Bool_t fIsMC{kTRUE};

    Bool_t fDebug{kFALSE};

    BaseMod* fCondition{0};

    int fHLTIds[simpletree::nHLTPaths] = {};

    ClassDef(SimpleTreeMod, 0)
  };

}

#endif
