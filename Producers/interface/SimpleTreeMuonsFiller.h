#ifndef MitFlat_Producers_SimpleTreeMuonsFiller_h
#define MitFlat_Producers_SimpleTreeMuonsFiller_h

#include "SimpleTreeFiller.h"

#include "DataFormats/Common/interface/View.h"
#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/TriggerObjectStandAlone.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"

class SimpleTreeMuonsFiller : public SimpleTreeFiller {
 public:
  SimpleTreeMuonsFiller(edm::ParameterSet const&, edm::ConsumesCollector&);
  ~SimpleTreeMuonsFiller() {}

  void fill(simpletree::Event&, edm::Event const&, edm::EventSetup const&) override;

 private:
  typedef edm::View<reco::Muon> MuonView;

  edm::EDGetTokenT<MuonView> muonsToken_;
  edm::EDGetTokenT<reco::VertexCollection> verticesToken_;
  edm::EDGetTokenT<pat::TriggerObjectStandAloneCollection> triggerObjectsToken_;

  bool useTrigger_;
  VString hltFilters_;
};

#endif
