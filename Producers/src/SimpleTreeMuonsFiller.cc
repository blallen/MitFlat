#include "../interface/SimpleTreeMuonsFiller.h"

#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/MuonReco/interface/MuonSelectors.h"
#include "DataFormats/Math/interface/deltaR.h"

SimpleTreeMuonsFiller::SimpleTreeMuonsFiller(edm::ParameterSet const& _cfg, edm::ConsumesCollector& _coll) :
  SimpleTreeFiller("MuonsFiller")
{
  getToken_(muonsToken_, _cfg, _coll, "muons");
  getToken_(verticesToken_, _cfg, _coll, "vertices");

  if (useTrigger_) {
    getToken_(triggerObjectsToken_, _cfg, _coll, "triggerObjects");
    hltFilters_ = _cfg.getUntrackedParameter<VString>("muonHLTFilters");
    if (hltFilters_.size() != simpletree::nMuonHLTObjects)
      throw edm::Exception(edm::errors::Configuration, "SimpleTreeMuonsFiller")
        << "muonHLTFilters.size()";
  }
}

void
SimpleTreeMuonsFiller::fill(simpletree::Event& _outEvent, edm::Event const& _inEvent, edm::EventSetup const& _setup)
{
  auto& inMuons(getProduct_(_inEvent, muonsToken_, "muons"));
  auto& vertices(getProduct_(_inEvent, verticesToken_, "vertices"));

  std::vector<pat::TriggerObjectStandAlone const*> hltObjects[simpletree::nMuonHLTObjects];
  if (useTrigger_) {
    auto& triggerObjects(getProduct_(_inEvent, triggerObjectsToken_, "triggerObjects"));
    for (auto& obj : triggerObjects) {
      for (unsigned iF(0); iF != simpletree::nMuonHLTObjects; ++iF) {
        if (obj.hasFilterLabel(hltFilters_[iF]))
          hltObjects[iF].push_back(&obj);
      }
    }
  }

  auto& outMuons(_outEvent.muons);

  for (auto& inMuon : inMuons) {
    if (inMuon.pt() < 10.)
      continue;
    if (std::abs(inMuon.eta()) > 2.4)
      continue;

    auto& outMuon(outMuons.create_back());

    fillP4(outMuon, inMuon);

    auto& pfIso(inMuon.pfIsolationR04());

    outMuon.combRelIso = (pfIso.sumChargedHadronPt + std::max(0., pfIso.sumNeutralHadronEt + pfIso.sumPhotonEt - 0.5 * pfIso.sumPUPt)) / outMuon.pt;

    outMuon.loose = muon::isLooseMuon(inMuon);
    if (vertices.size() == 0)
      outMuon.tight = false;
    else
      outMuon.tight = muon::isTightMuon(inMuon, vertices.at(0)) && outMuon.combRelIso < 0.15;

    if (useTrigger_) {
      for (unsigned iF(0); iF != simpletree::nMuonHLTObjects; ++iF) {
        for (auto* obj : hltObjects[iF]) {
          if (reco::deltaR(inMuon, *obj) < 0.3) {
            outMuon.matchHLT[iF] = true;
            break;
          }
        }
      }
    }
  }
}
