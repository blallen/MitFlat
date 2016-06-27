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

    void SetRhoAlgo(UInt_t a) { fRhoAlgo = a; }
    void SetJetsName(char const* n) { fJetsName = n; }
    void SetLooseJetsName(char const* n) { fLooseJetsName = n; }
    void SetMinJetPt(Double_t p) { fMinJetPt = p; }
    void SetJetsCorrUpName(char const* n) { fJetsCorrUpName = n; }
    void SetJetsCorrDownName(char const* n) { fJetsCorrDownName = n; }
    void SetJetsResUpName(char const* n) { fJetsResUpName = n; }
    void SetJetsResDownName(char const* n) { fJetsResDownName = n; }
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
    void SetResUpMetName(char const* n) { fResUpMetName = n; }
    void SetResDownMetName(char const* n) { fResDownMetName = n; }
    void SetUnclUpMetName(char const* n) { fUnclUpMetName = n; }
    void SetUnclDownMetName(char const* n) { fUnclDownMetName = n; }
    void SetGenMetName(char const* n) { fGenMetName = n; }
    void SetGenJetsName(char const* n) { fGenJetsName = n; }
    void SetUseTrigger(Bool_t b) { fUseTrigger = b; }
    void SetFillPhotonDetails(Bool_t b) { fPhotonDetails = b; }
    void SetPhotonL1ModuleName(char const* f, char const* n);
    void SetPhotonTriggerModuleName(char const* f, char const* n);
    void SetElectronTriggerModuleName(char const* f, char const* n);
    void SetMuonTriggerModuleName(char const* f, char const* n);
    void SetPdfReweight(char const* n) { fPdfReweightName = n; }
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
    Bool_t Notify() override;

    // output
    TString fOutputName{"simpletree.root"};
    TTree* fEventTree{0};
    TTree* fRunTree{0};
    TTree* fHLTTree{0};
    TH1D* fEventCounter{0};
    simpletree::Event fEvent;
    simpletree::Run fRun;
    std::vector<TString>* fHLTPaths{0};

    // input
    UInt_t fRhoAlgo{0};
    TString fVerticesName{"PrimaryVertexes"};
    TString fJetsName{"AKt4PFJets"};
    TString fLooseJetsName{""};
    Double_t fMinJetPt{30.};
    TString fJetsCorrUpName{""};
    TString fJetsCorrDownName{""};
    TString fJetsResUpName{""};
    TString fJetsResDownName{""};
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
    TString fResUpMetName{""};
    TString fResDownMetName{""};
    TString fUnclUpMetName{""};
    TString fUnclDownMetName{""};
    TString fGenMetName{""};
    TString fGenJetsName{""};
    Bool_t fUseTrigger{kTRUE};
    Bool_t fPhotonDetails{kFALSE};
    TString fPhotonL1ModuleName[simpletree::nPhotonL1Objects]{};
    TString fPhotonTriggerModuleName[simpletree::nPhotonHLTObjects]{};
    TString fElectronTriggerModuleName[simpletree::nElectronHLTObjects]{};
    TString fMuonTriggerModuleName[simpletree::nMuonHLTObjects]{};
    TString fPdfReweightName{}; // original code name: amc_74, mg5_74, pwhg_74
    std::vector<unsigned> fPdfReweightIds{};
    Int_t fCentralReweightId{-1};
    TString fMetFilterName{""};

    Bool_t fIsMC{kTRUE};

    Bool_t fDebug{kFALSE};

    BaseMod* fCondition{0};

    int fCurrentTriggerTable{-1}; // internal variable to detect HLT menu / file transition
    std::map<TString, unsigned> fTriggerTableMap{};
    std::vector<unsigned short> fHLTIds{};

    ClassDef(SimpleTreeMod, 0)
  };

}

#endif
