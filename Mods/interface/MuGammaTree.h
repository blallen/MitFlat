#ifndef MITFLAT_MODS_MUGAMMATREE_H
#define MITFLAT_MODS_MUGAMMATREE_H

#include "MitAna/TreeMod/interface/BaseMod.h"
#include "MitFlat/DataFormats/interface/TreeEntries_mugamma.h"

#include "TString.h"
#include "TTree.h"

namespace mithep {

  class MuGammaTree : public BaseMod {
  public:
    MuGammaTree(char const* name = "MuGammaTree", char const* title = "Fill flat ntuples") : BaseMod(name, title) {}
    ~MuGammaTree() {}

    void SetEventTreeName(char const* n) { fEventTreeName = n; }
    void SetAllEventTreeName(char const* n) { fAllEventTreeName = n; }
    void SetRhoAlgo(UInt_t a) { fRhoAlgo = a; }
    void SetJetsName(char const* n) { fJetsName = n; }
    void SetPhotonsName(char const* n) { fPhotonsName = n; }
    void SetElectronsName(char const* n) { fElectronsName = n; }
    void SetTightElectronsName(char const* n) { fTightElectronsName = n; }
    void SetMuonsName(char const* n) { fMuonsName = n; }
    void SetTightMuonsName(char const* n) { fTightMuonsName = n; }
    void SetTausName(char const* n) { fTausName = n; }
    void SetConversionsName(char const* n) { fConversionsName = n; }
    void SetVerticesName(char const* n) { fVerticesName = n; }
    void SetLoosePhotonName(char const* n) { fLoosePhotonName = n; }
    void SetMediumPhotonName(char const* n) { fMediumPhotonName = n; }
    void SetTightPhotonName(char const* n) { fTightPhotonName = n; }
    void SetRawMetName(char const* n) { fRawMetName = n; }
    void SetT1MetName(char const* n) { fT1MetName = n; }
    void SetT1NoCHSMetName(char const* n) { fT1NoCHSMetName = n; }
    void SetEta30MetName(char const* n) { fEta30MetName = n; }
    void SetEta30T1MetName(char const* n) { fEta30T1MetName = n; }
    void SetEta30T1NoCHSMetName(char const* n) { fEta30T1NoCHSMetName = n; }
    void SetNHScaledMetName(char const* n) { fNHScaledMetName = n; }
    void SetCHMetName(char const* n) { fCHMetName = n; }
    void SetNHMetName(char const* n) { fNHMetName = n; }
    void SetNEMetName(char const* n) { fNEMetName = n; }
    void SetCHGt30MetName(char const* n) { fCHGt30MetName = n; }
    void SetNHGt30MetName(char const* n) { fNHGt30MetName = n; }
    void SetNEGt30MetName(char const* n) { fNEGt30MetName = n; }
    void SetIsMC(Bool_t k) { fIsMC = k; }

    void SetCondition(BaseMod* m) { fCondition = m; }

  protected:
    void Process() override;
    void SlaveBegin() override;

    // output
    TString fEventTreeName{"events"};
    TString fAllEventTreeName{"all"};
    TTree* fEventTree{0};
    TTree* fAllEventTree{0};
    mugamma::Event fEvent;
    mugamma::Weight fAllEvent;

    // input
    UInt_t fRhoAlgo{0};
    TString fJetsName{"AKt4PFJets"};
    TString fPhotonsName{"Photons"};
    TString fElectronsName{"Electrons"};
    TString fTightElectronsName{"TightElectrons"};
    TString fMuonsName{"Muons"};
    TString fTightMuonsName{"TightMuons"};
    TString fTausName{"HPSTaus"};
    TString fConversionsName{"Conversions"};
    TString fVerticesName{"PrimaryVertexes"};
    TString fLoosePhotonName{"LoosePhotons"};
    TString fMediumPhotonName{"MediumPhotons"};
    TString fTightPhotonName{"TightPhotons"};
    TString fRawMetName{"PFMet"};
    TString fT1MetName{"PFMet"};
    TString fT1NoCHSMetName{"PFMet"};
    TString fEta30MetName{"PFMet"};
    TString fEta30T1MetName{"PFMet"};
    TString fEta30T1NoCHSMetName{"PFMet"};
    TString fNHScaledMetName{"PFMet"};
    TString fCHMetName{"PFMet"};
    TString fNHMetName{"PFMet"};
    TString fNEMetName{"PFMet"};
    TString fCHGt30MetName{"PFMet"};
    TString fNHGt30MetName{"PFMet"};
    TString fNEGt30MetName{"PFMet"};

    Bool_t fIsMC{kTRUE};

    BaseMod* fCondition{0};

    ClassDef(MuGammaTree, 0)
  };

}

#endif
