#ifndef MITFLAT_MODS_GENKINTREEMOD_H
#define MITFLAT_MODS_GENKINTREEMOD_H

#include "MitAna/TreeMod/interface/BaseMod.h"
#include "MitFlat/DataFormats/interface/TreeEntries_genkintree.h"

#include "TString.h"
#include "TTree.h"
#include "TH1D.h"

#include "fastjet/JetDefinition.hh"
#include "fastjet/GhostedAreaSpec.hh"
#include "fastjet/AreaDefinition.hh"

namespace mithep {

  class GenKinTreeMod : public BaseMod {
  public:
    GenKinTreeMod(char const* name = "GenKinTreeMod", char const* title = "Fill flat ntuples") : BaseMod(name, title) {}
    ~GenKinTreeMod() {}

    void SetEventTreeName(char const* n) { fEventTreeName = n; }
    void SetOutputName(char const* p) { fOutputName = p; }

    void SetDebug(Bool_t d) { fDebug = d; }

  protected:
    void Process() override;
    void SlaveBegin() override;
    void SlaveTerminate() override;

    // output
    TString fOutputName{"genkintree.root"};
    TString fEventTreeName{"genEvents"};
    TTree* fEventTree{0};
    genkintree::Event fEvent;

    // input
    Bool_t fDebug{kFALSE};

    // fastjet
    fastjet::GhostedAreaSpec* fGAS{0};
    fastjet::AreaDefinition* fAreaDef{0};
    fastjet::JetDefinition* fJetDef{0};

    ClassDef(GenKinTreeMod, 0)
  };

}

#endif
