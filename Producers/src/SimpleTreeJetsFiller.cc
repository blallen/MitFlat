#include "../interface/SimpleTreeJetsFiller.h"

#include "FWCore/Framework/interface/ESHandle.h"

#include "DataFormats/PatCandidates/interface/Jet.h"

#include "CondFormats/JetMETObjects/interface/JetCorrectorParameters.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectionUncertainty.h"
#include "JetMETCorrections/Objects/interface/JetCorrectionsRecord.h"
#include "JetMETCorrections/Objects/interface/JetCorrector.h"

SimpleTreeJetsFiller::SimpleTreeJetsFiller(edm::ParameterSet const& _cfg, edm::ConsumesCollector& _coll) :
  SimpleTreeFiller("JetsFiller")
{
  getToken_(jetsToken_, _cfg, _coll, "jets");
}

SimpleTreeJetsFiller::~SimpleTreeJetsFiller()
{
  delete jecUncertainty_;
}

void
SimpleTreeJetsFiller::fill(simpletree::Event& _outEvent, edm::Event const& _inEvent, edm::EventSetup const& _setup)
{
  auto& inJets(getProduct_(_inEvent, jetsToken_, "jets"));

  auto& outJets(_outEvent.jets);

  if (!jecUncertainty_) {
    edm::ESHandle<JetCorrectorParametersCollection> jecColl;
    _setup.get<JetCorrectionsRecord>().get("AK4PFchs", jecColl);
    jecUncertainty_ = new JetCorrectionUncertainty((*jecColl)["Uncertainty"]);
  }

  for (auto& inJet : inJets) {
    double absEta(std::abs(inJet.eta()));
    if (absEta > 4.7)
      continue;

    if (dynamic_cast<pat::Jet const*>(&inJet)) {
      auto& patJet(static_cast<pat::Jet const&>(inJet));

      if (absEta <= 2.7) {
        if (patJet.neutralHadronEnergyFraction() >= 0.99)
          continue;
        if (patJet.neutralEmEnergyFraction() >= 0.99)
          continue;
        if (patJet.numberOfDaughters() < 2)
          continue;

        if (absEta <= 2.4) {
          if (patJet.chargedHadronEnergyFraction() <= 0.)
            continue;
          if (patJet.chargedEmEnergyFraction() >= 0.99)
            continue;
          if (patJet.chargedMultiplicity() == 0)
            continue;
        }
      }
      else {
        if (patJet.neutralEmEnergyFraction() >= 0.9)
          continue;

        if (absEta <= 3.) {
          if (patJet.neutralMultiplicity() < 3)
            continue;
        }
        else {
          if (patJet.neutralMultiplicity() < 11)
            continue;
        }
      }

      auto& outJet(outJets.create_back());

      fillP4(outJet, inJet);

      // TODO
      // jecUncertainty_->setJetEta(inJet.eta());
      // jecUncertainty_->setJetPt(inJet.pt());
      // double jesUp(jecUncertainty_->getUncertainty(true));
      // double jesDown(jecUncertainty_->getUncertainty(false));

      outJet.ptRaw = patJet.pt() * patJet.jecFactor("Uncorrected");
      // outJet.ptCorrUp = patJet.pt() * (1. + jesUp);
      // outJet.ptCorrDown = patJet.pt() * (1. - jesDown);
      // TODO
      outJet.ptResCorr = outJet.pt;
      outJet.phiResCorr = outJet.phi;
      outJet.cisv = patJet.bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags");
    }
  }
}
