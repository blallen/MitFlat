#include "../interface/SimpleTreeVerticesFiller.h"

#include "DataFormats/VertexReco/interface/Vertex.h"

SimpleTreeVerticesFiller::SimpleTreeVerticesFiller(edm::ParameterSet const& _cfg, edm::ConsumesCollector& _coll) :
  SimpleTreeFiller("VerticesFiller")
{
  getToken_(verticesToken_, _cfg, _coll, "vertices");
}

void
SimpleTreeVerticesFiller::fill(simpletree::Event& _outEvent, edm::Event const& _inEvent, edm::EventSetup const& _setup)
{
  auto& inVertices(getProduct_(_inEvent, verticesToken_, "vertices"));

  _outEvent.npv = 0;
  for (auto& vtx : inVertices) {
    if (vtx.ndof() < 4)
      continue;
    if (std::abs(vtx.z()) > 24.)
      continue;
    if (vtx.position().rho() > 2.)
      continue;

    ++_outEvent.npv;
  }

  // TODO
  _outEvent.npvTrue = 0.;
}
