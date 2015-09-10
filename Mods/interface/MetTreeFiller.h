#ifndef MITFLAT_MODS_METTREEFILLER_H
#define MITFLAT_MODS_METTREEFILLER_H

#include "MitAna/TreeMod/interface/BaseMod.h"
#include "MitFlat/DataFormats/interface/TreeEntries_met.h"

namespace mithep {

  class MetTreeFiller : public BaseMod {
  public:
    MetTreeFiller(char const* name = "MetTreeFiller", char const* title = "Fill flat ntuples") : BaseMod(name, title) {}
    ~MetTreeFiller() {}

    void SetRawMetName(char const* n) { fRawMetName = n; }
    void SetType1MetName(char const* n) { fType1MetName = n; }

  protected:
    void Process() override;
    void SlaveBegin() override;

    // output
    TTree* fEventTree{0};

    met::Event fEvent;

    // input
    TString fRawMetName{"PFMet"};
    TString fType1MetName{"PFType1CorrectedMet"};

    ClassDef(MetTreeFiller, 0)
  };
}

#endif
