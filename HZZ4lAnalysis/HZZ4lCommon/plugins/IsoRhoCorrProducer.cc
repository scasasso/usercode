// -*- C++ -*-
//
// Package:    IsoRhoCorrProducer
// Class:      IsoRhoCorrProducer
// 
/*
 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Stefano Casasso,,,
//         Created:  Thu Mar 15 14:21:33 CET 2012
// $Id$
//
//

// system include files
#include <memory>
#include <cmath>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/Common/interface/ValueMap.h"
#include "DataFormats/RecoCandidate/interface/RecoCandidate.h"

#include <Math/VectorUtil.h>

using namespace edm;
using namespace std;

class IsoRhoCorrProducer : public edm::EDProducer {
public:
  explicit IsoRhoCorrProducer(const edm::ParameterSet&);
  ~IsoRhoCorrProducer();
  
private:
  virtual void beginJob() ;
  virtual void produce(edm::Event&, const edm::EventSetup&);
  virtual void endJob() ;
  
  const edm::InputTag muonSrc_;    
  const edm::InputTag electronSrc_;    
  const edm::InputTag rhoSrc_;
  
};

IsoRhoCorrProducer::IsoRhoCorrProducer(const edm::ParameterSet& iConfig):
  muonSrc_(iConfig.getUntrackedParameter<edm::InputTag>("muonSrc")),
  electronSrc_(iConfig.getUntrackedParameter<edm::InputTag>("electronSrc")),
  rhoSrc_(iConfig.getUntrackedParameter<edm::InputTag>("rhoSrc"))
{
  produces<std::vector<pat::Muon> >();
  produces<std::vector<pat::Electron> >();
}

void IsoRhoCorrProducer::produce(edm::Event& iEvent, const edm::EventSetup& iSetup) {

  edm::Handle<vector<pat::Muon> > muonHandle;
  iEvent.getByLabel(muonSrc_,  muonHandle);

  edm::Handle<vector<pat::Electron> > electronHandle;
  iEvent.getByLabel(electronSrc_,  electronHandle);

  edm::Handle<double> rhoHandle;
  iEvent.getByLabel(rhoSrc_, rhoHandle);
  double rho = rhoHandle.product();

  auto_ptr<vector<pat::Muon> > muonColl( new vector<pat::Muon> (*muonHandle) );
  auto_ptr<vector<pat::Electron> > electronColl( new vector<pat::Electron> (*electronHandle) );

  //Loop over muons
  for (unsigned int i = 0; i< muonColl->size();++i){
    pat::Muon & m = (*muonColl)[i];

    float RhoCorrIso = -1.; //the user float we want to add to pat::Muon
    float ecalIso = m.ecalIso();
    float hcalIso = m.hcalIso();
    float trackIso = m.trackIso();
    float eta = m.eta();
    //float rho = m.userFloat("rhoMu");

    const float AreaEcal[2]    = {0.074, 0.045}; //   barrel/endcap
    const float AreaHcal[2]    = {0.022 , 0.030 }; //   barrel/endcap
    
    Int_t ifid = (eta < 1.479) ? 0 : 1;
    
    ecalIso = ecalIso - AreaEcal[ifid] * rho;
    hcalIso = hcalIso - AreaHcal[ifid] * rho;

    RhoCorrIso = (ecalIso + hcalIso + trackIso)/m.pt();

    m.addUserFloat("RhoCorrIso",RhoCorrIso);
  }

  //Loop over electrons
  for (unsigned int i = 0; i< electronColl->size();++i){
    pat::Electron & e = (*electronColl)[i];

    float RhoCorrIso = -1.; //the user float we want to add to pat::Electron
    float ecalIso = e.ecalIso();
    float hcalIso = e.hcalIso();
    float trackIso = e.trackIso();
    //float rho = e.userFloat("rhoMu");
    
    const float AreaEcal[2]    = {0.101, 0.046}; //   barrel/endcap
    const float AreaHcal[2]    = {0.021 , 0.040 }; //   barrel/endcap
    
    Int_t ifid;
    Bool_t isBarrel = e.isEB();
    if (isBarrel) ifid =0;
    else ifid=1;
    
    ecalIso = ecalIso - AreaEcal[ifid] * rho;
    hcalIso = hcalIso - AreaHcal[ifid] * rho;

    RhoCorrIso = (ecalIso + hcalIso + trackIso)/e.pt();

    e.addUserFloat("RhoCorrIso",RhoCorrIso);
  }

  
  iEvent.put( muonColl);
  iEvent.put( electronColl);
  
}

IsoRhoCorrProducer::~IsoRhoCorrProducer() { }
void IsoRhoCorrProducer::beginJob() { }
void IsoRhoCorrProducer::endJob() { } 
DEFINE_FWK_MODULE(IsoRhoCorrProducer);
