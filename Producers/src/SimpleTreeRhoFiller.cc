#include "../interface/SimpleTreeRhoFiller.h"

SimpleTreeRhoFiller::SimpleTreeRhoFiller(edm::ParameterSet const& _cfg, edm::ConsumesCollector& _coll) :
  SimpleTreeFiller("RhoFiller")
{
  getToken_(rhoToken_, _cfg, _coll, "rho");
}

void
SimpleTreeRhoFiller::fill(simpletree::Event& _outEvent, edm::Event const& _inEvent, edm::EventSetup const& _setup)
{
  _outEvent.rho = getProduct_(_inEvent, rhoToken_, "rho");
}
