#ifndef HZZ4lAnalysis_HZZ4lCommon_BestCandProducer_h
#define HZZ4lAnalysis_HZZ4lCommon_BestCandProducer_h

#include <memory>
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/EDProducer.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "DataFormats/Common/interface/ValueMap.h"
#include "HZZ4lAnalysis/DataFormats/interface/HiggsCandidate.h"

#include <sstream>
#include <string>
#include <vector>


template <class higgstype>
class BestCandProducer : public edm::EDProducer { 
public:
  explicit BestCandProducer(const edm::ParameterSet& iConfig) :
    src_(iConfig.getParameter<edm::InputTag>("src"))

  {
    produces<std::vector<higgstype> >();
  }
  
  virtual ~BestCandProducer() {}
  
  void produce(edm::Event & iEvent, const edm::EventSetup & iSetup) ;

private:	
  edm::InputTag src_ ;
  
};

template <class higgstype>
void BestCandProducer<higgstype>::produce(edm::Event & iEvent, const edm::EventSetup & iSetup) {

  // read input collection
  edm::Handle<std::vector<higgstype> > higgscandidates;
  iEvent.getByLabel(src_, higgscandidates);
  
  std::auto_ptr<std::vector<higgstype> > higgsColl( new std::vector<higgstype> (*higgscandidates) );

  unsigned int bestCand=999;
  unsigned int bestCand2e2m=999;
  double ptMax = -999;

  for (unsigned int i=0 ; i<higgsColl->size() ; ++i ) {
    
    higgstype & ahiggs = (*higgsColl)[i];

    if ( !( ahiggs.getSelection("cuts_mass") && ahiggs.leg1().getSelection("cuts_zCandplusID") && ahiggs.leg2().getSelection("cuts_zCandplusID") ) ) continue;
 
    double mH = ahiggs.mass();
    double m1 = ahiggs.leg1().mass();
    double m2 = ahiggs.leg2().mass();
    double pt1 = ahiggs.leg1().leg1().pt() + ahiggs.leg1().leg2().pt();
    double pt2 = ahiggs.leg2().leg1().pt() + ahiggs.leg2().leg2().pt();
    float isBestZ1 = ahiggs.leg1().userFloat("bestZ");
    float isBestZ2 = ahiggs.leg2().userFloat("bestZ");
    
    if(isBestZ1 == 2){
      if(m2>12 && mH>100 && pt2>ptMax){
	bestCand=i;
	ptMax = pt2;
      }
    }
    else if(isBestZ2 == 2){
      if(m1>12 && mH>100 && pt1>ptMax){
	bestCand=i;
	ptMax = pt1;
      }
    }
    if((isBestZ1==2 && isBestZ2==1) || (isBestZ1==1 && isBestZ2==2)){
      bestCand2e2m=i;
    }
  }
  
    
  for (unsigned int i=0 ; i<higgsColl->size() ; ++i ) {

    higgstype & ahiggs = (*higgsColl)[i];
    if(i==bestCand)
      ahiggs.addUserFloat("bestH_PRL",1);
    else
      ahiggs.addUserFloat("bestH_PRL",0);
    if(i==bestCand2e2m)
      ahiggs.addUserFloat("bestH2e2m",1);
    else
      ahiggs.addUserFloat("bestH2e2m",0);
  }
    // and put it into the event
     iEvent.put(higgsColl);
}



#endif
