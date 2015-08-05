#ifndef MITFLAT_MODS_MONOJETTREE_H
#define MITFLAT_MODS_MONOJETTREE_H

#include "MitAna/TreeMod/interface/BaseMod.h"
#include "MitFlat/DataFormats/interface/TreeEntries_monojet.h"

#include "TString.h"
#include "TTree.h"

namespace mithep {

  class MonoJetTree : public BaseMod {
  public:
    MonoJetTree(char const* name = "MonoJetTree", char const* title = "Fill flat ntuples") : BaseMod(name, title) {}
    ~MonoJetTree() {}

    char const* GetTreeName() const { return fTreeName; }
    char const* GetJetsName() const { return fJetsName; }
    char const* GetElectronsName() const { return fElectronsName; }
    char const* GetMuonsName() const { return fMuonsName; }
    char const* GetTausName() const { return fTausName; }
    char const* GetPhotonsName() const { return fPhotonsName; }
    char const* GetTriggerObjectsName() const { return fTriggerObjectsName; }

    void SetTreeName(char const* n) { fTreeName = n; }
    void SetJetsName(char const* n) { fJetsName = n; }
    void SetElectronsName(char const* n) { fElectronsName = n; }
    void SetMuonsName(char const* n) { fMuonsName = n; }
    void SetTausName(char const* n) { fTausName = n; }
    void SetPhotonsName(char const* n) { fPhotonsName = n; }
    void SetTriggerObjectsName(char const* n) { fTriggerObjectsName = n; }

  protected:
    void Process() override;
    void SlaveBegin() override;
    void BeginRun() override;

    // output
    TString fTreeName = "events";
    TTree* fTree = 0;
    monojet::Event fEvent;

    // input
    TString fMetName = "PFMet";
    TString fJetsName = "AKt4PFJets";
    TString fElectronsName = "Electrons";
    TString fMuonsName = "Muons";
    TString fTausName = "HPSTaus";
    TString fPhotonsName = "Photons";
    TString fTriggerObjectsName = "HLTModTrigObjs";

    unsigned trigIds[2] = {};

    ClassDef(MonoJetTree, 0)
  };

}

#endif
