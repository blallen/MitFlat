#ifndef MITFLAT_MODS_SIMPLETREEMOD_H
#define MITFLAT_MODS_SIMPLETREEMOD_H

#include "MitAna/TreeMod/interface/BaseMod.h"
#include "MitFlat/DataFormats/interface/TreeEntries_simpletree.h"

#include "TString.h"
#include "TTree.h"

namespace mithep {

  class SimpleTreeMod : public BaseMod {
  public:
    SimpleTreeMod(char const* name = "SimpleTreeMod", char const* title = "Fill flat ntuples") : BaseMod(name, title) {}
    ~SimpleTreeMod() {}

    void SetEventTreeName(char const* n) { fEventTreeName = n; }
    void SetAllEventTreeName(char const* n) { fAllEventTreeName = n; }
    void SetRhoAlgo(UInt_t a) { fRhoAlgo = a; }
    void SetJetsName(char const* n) { fJetsName = n; }
    void SetPhotonsName(char const* n) { fPhotonsName = n; }
    void SetElectronsName(char const* n) { fElectronsName = n; }
    void SetLooseElectronsName(char const* n) { fLooseElectronsName = n; }
    void SetMediumElectronsName(char const* n) { fMediumElectronsName = n; }
    void SetTightElectronsName(char const* n) { fTightElectronsName = n; }
    void SetMuonsName(char const* n) { fMuonsName = n; }
    void SetLooseMuonsName(char const* n) { fLooseMuonsName = n; }
    void SetMediumMuonsName(char const* n) { fMediumMuonsName = n; }
    void SetTightMuonsName(char const* n) { fTightMuonsName = n; }
    void SetTausName(char const* n) { fTausName = n; }
    void SetConversionsName(char const* n) { fConversionsName = n; }
    void SetVerticesName(char const* n) { fVerticesName = n; }
    void SetLoosePhotonName(char const* n) { fLoosePhotonName = n; }
    void SetMediumPhotonName(char const* n) { fMediumPhotonName = n; }
    void SetTightPhotonName(char const* n) { fTightPhotonName = n; }
    void SetPUPFCandidatesName(char const* n) { fPUPFCandidatesName = n; }
    void SetPVPFCandidatesName(char const* n) { fPVPFCandidatesName = n; }
    void SetRawMetName(char const* n) { fRawMetName = n; }
    void SetT1MetName(char const* n) { fT1MetName = n; }
    void SetT1NoCHSMetName(char const* n) { fT1NoCHSMetName = n; }
    void SetNHScaledMetName(char const* n) { fNHScaledMetName = n; }
    void SetCHMetName(char const* n) { fCHMetName = n; }
    void SetNHMetName(char const* n) { fNHMetName = n; }
    void SetNEMetName(char const* n) { fNEMetName = n; }
    void AddTriggerFilterName(UInt_t p, char const* n) { fTriggerFilterName[p].emplace_back(n); }
    void SetTriggerPathName(UInt_t p, char const* n) { fTriggerPathName[p] = n; }
    void SetIsMC(Bool_t k) { fIsMC = k; }

    void SetCondition(BaseMod* m) { fCondition = m; }

  protected:
    void Process() override;
    void SlaveBegin() override;
    void BeginRun() override;

    // output
    TString fEventTreeName{"events"};
    TString fAllEventTreeName{"all"};
    TTree* fEventTree{0};
    TTree* fAllEventTree{0};
    simpletree::Event fEvent;
    simpletree::Weight fAllEvent;

    // input
    UInt_t fRhoAlgo{0};
    TString fVerticesName{"PrimaryVertexes"};
    TString fJetsName{"AKt4PFJets"};
    TString fPhotonsName{"Photons"};
    TString fElectronsName{"Electrons"};
    TString fLooseElectronsName{"LooseElectrons"};
    TString fMediumElectronsName{"MediumElectrons"};
    TString fTightElectronsName{"TightElectrons"};
    TString fMuonsName{"Muons"};
    TString fLooseMuonsName{"LooseMuons"};
    TString fMediumMuonsName{"MediumMuons"};
    TString fTightMuonsName{"TightMuons"};
    TString fTausName{"HPSTaus"};
    TString fConversionsName{"Conversions"};
    TString fLoosePhotonName{"LoosePhotons"};
    TString fMediumPhotonName{"MediumPhotons"};
    TString fTightPhotonName{"TightPhotons"};
    TString fPUPFCandidatesName{"pfPU"};
    TString fPVPFCandidatesName{"pfNoPU"};
    TString fRawMetName{"PFMet"};
    TString fT1MetName{""};
    TString fT1NoCHSMetName{""};
    TString fNHScaledMetName{""};
    TString fCHMetName{""};
    TString fNHMetName{""};
    TString fNEMetName{""};
    std::vector<TString> fTriggerFilterName[simpletree::nHLTPaths]{};
    TString fTriggerPathName[simpletree::nHLTPaths]{};

    Bool_t fIsMC{kTRUE};

    BaseMod* fCondition{0};

    int fHLTIds[simpletree::nHLTPaths] = {};

    ClassDef(SimpleTreeMod, 0)
  };

}

#endif
