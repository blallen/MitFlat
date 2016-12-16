#ifndef MitFlat_Producers_SimpleTreeFiller_h
#define MitFlat_Producers_SimpleTreeFiller_h

#include "FWCore/Framework/interface/ConsumesCollector.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/Candidate/interface/Candidate.h"

#include "MitFlat/DataFormats/interface/TreeEntries_simpletree.h"

#include "TFile.h"

class SimpleTreeFiller {
 public:
  SimpleTreeFiller(std::string const& fillerName) : fillerName_(fillerName) {}
  virtual ~SimpleTreeFiller() {}

  virtual void addBranch(flatutils::BranchList&) {}
  virtual void addOutput(TFile&) {}
  virtual void fill(simpletree::Event&, edm::Event const&, edm::EventSetup const&) = 0;
  virtual void fillRun(simpletree::Run&, edm::Run const&, edm::EventSetup const&) {}

 protected:
  typedef std::vector<std::string> VString;

  template<class Product, edm::BranchType B = edm::InEvent>
  void getToken_(edm::EDGetTokenT<Product>&, edm::ParameterSet const&, edm::ConsumesCollector&, std::string const& pname, bool mandatory = true);

  template<class Product>
  Product const& getProduct_(edm::Event const&, edm::EDGetTokenT<Product> const&, std::string name);

  std::string fillerName_;
};

template<class Product, edm::BranchType B/* = edm::Event*/>
void
SimpleTreeFiller::getToken_(edm::EDGetTokenT<Product>& _token, edm::ParameterSet const& _cfg, edm::ConsumesCollector& _coll, std::string const& _pname, bool _mandatory/* = true*/)
{
  std::string paramValue;
  
  if (_mandatory)
    paramValue = _cfg.getUntrackedParameter<std::string>(_pname);
  else
    paramValue = _cfg.getUntrackedParameter<std::string>(_pname, "");

  if (paramValue.empty()) {
    if (_mandatory)
      throw edm::Exception(edm::errors::Configuration, fillerName_ + "::getToken_()")
        << "Missing or empty parameter " << _pname;
    else
      _token = edm::EDGetTokenT<Product>();
  }
  else {
    edm::InputTag tag(paramValue);
    _token = _coll.consumes<Product, B>(tag);
  }
}

template<class Product>
Product const&
SimpleTreeFiller::getProduct_(edm::Event const& _event, edm::EDGetTokenT<Product> const& _token, std::string _name)
{
  edm::Handle<Product> handle;
  if (!_event.getByToken(_token, handle))
    throw cms::Exception("ProductNotFound") << _name;
  return *handle;
}

void fillP4(simpletree::Particle&, reco::Candidate const&);
void fillP4(simpletree::ParticleM&, reco::Candidate const&);
void fillP4(simpletree::RecoParticleM&, reco::Candidate const&);

#endif
