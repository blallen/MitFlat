#include "MitFlat/Mods/interface/MetTreeFiller.h"
#include "MitAna/DataTree/interface/MetCol.h"

ClassImp(mithep::MetTreeFiller)

void
mithep::MetTreeFiller::Process()
{
  auto* rawMetCol = GetObject<mithep::MetCol>(fRawMetName);
  auto* type1MetCol = GetObject<mithep::MetCol>(fType1MetName);

  auto& rawMet(*rawMetCol->At(0));
  auto& type1Met(*type1MetCol->At(0));

  fEvent.rawMet.met = rawMet.Pt();
  fEvent.rawMet.phi = rawMet.Phi();
  fEvent.rawMet.sumEt = rawMet.SumEt();

  fEvent.type1Met.met = type1Met.Pt();
  fEvent.type1Met.phi = type1Met.Phi();
  fEvent.type1Met.sumEt = type1Met.SumEt();

  fEventTree->Fill();
}

void
mithep::MetTreeFiller::SlaveBegin()
{
  fEventTree = new TTree("events", "Events");
  fEvent.book(*fEventTree);

  AddOutput(fEventTree);
}
