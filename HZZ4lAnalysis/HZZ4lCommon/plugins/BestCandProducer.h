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
  double mZ = 91.2;
  double deltamZ = 1000000;

  for (unsigned int i=0 ; i<higgsColl->size() ; ++i ) {

    higgstype & ahiggs = (*higgsColl)[i];
    
    double m1 = ahiggs.leg1().mass();
    double m2 = ahiggs.leg2().mass();
    
    if(fabs(m1 - mZ)<deltamZ){
      deltamZ = fabs(m1 - mZ);
      bestCand = i;
    }
    if(fabs(m2 - mZ)<deltamZ){
      deltamZ = fabs(m2 - mZ);
      bestCand = i;
    }
  }
    
  for (unsigned int i=0 ; i<higgsColl->size() ; ++i ) {

    higgstype & ahiggs = (*higgsColl)[i];
    if(i==bestCand)
      ahiggs.addUserFloat("best",1);
    else
      ahiggs.addUserFloat("best",0);
  }
    // and put it into the event
     iEvent.put(higgsColl);
}



#endif
