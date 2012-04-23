#ifndef HZZ4lAnalysis_HZZ4lCommon_BestZProducer_h
#define HZZ4lAnalysis_HZZ4lCommon_BestZProducer_h

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


class BestZProducer : public edm::EDProducer { 
public:
  explicit BestZProducer(const edm::ParameterSet& iConfig) :
    srcMuMu_(iConfig.getParameter<edm::InputTag>("srcMuMu")),
    srcEleEle_(iConfig.getParameter<edm::InputTag>("srcEleEle"))
  {
    produces<std::vector<cmg::DiObject<cmg::Muon, cmg::Muon> > >();
    produces<std::vector<cmg::DiObject<cmg::Electron, cmg::Electron> > >();
 }
  
  virtual ~BestZProducer() {}
  
  void produce(edm::Event & iEvent, const edm::EventSetup & iSetup) ;

private:	
  edm::InputTag srcMuMu_ ;
  edm::InputTag srcEleEle_ ;
  
};

void BestZProducer::produce(edm::Event & iEvent, const edm::EventSetup & iSetup) {

  double mZ = 91.2;

  // read input collection Z->mumu
  edm::Handle< std::vector<cmg::DiObject<cmg::Muon, cmg::Muon> > > zmumucandidates;  
  iEvent.getByLabel(srcMuMu_, zmumucandidates);

  // chose the best Z->mumu
  unsigned int bestZmumu = 999;
  double deltamZmumu = 1000000;
  std::auto_ptr<std::vector<cmg::DiObject<cmg::Muon, cmg::Muon> > > zmumuColl( new std::vector<cmg::DiObject<cmg::Muon, cmg::Muon> > (*zmumucandidates) );
 
  for(unsigned int i=0 ; i<zmumuColl->size() ; ++i ){
    cmg::DiObject<cmg::Muon, cmg::Muon>  & zmumu = (*zmumuColl)[i];

    if(fabs(mZ - zmumu.mass())<deltamZmumu){
      deltamZmumu = fabs(mZ - zmumu.mass());
      bestZmumu=i;
    }
  }
    
  // read input collection Z->eleele
  edm::Handle< std::vector<cmg::DiObject<cmg::Electron, cmg::Electron> > > zeleelecandidates;  
  iEvent.getByLabel(srcEleEle_, zeleelecandidates);

  // chose the best Z->eleele
  unsigned int bestZeleele = 999;
  double deltamZeleele = 1000000;
  std::auto_ptr<std::vector<cmg::DiObject<cmg::Electron, cmg::Electron> > > zeleeleColl( new std::vector<cmg::DiObject<cmg::Electron, cmg::Electron> > (*zeleelecandidates) );
 
  for(unsigned int i=0 ; i<zeleeleColl->size() ; ++i ){
    cmg::DiObject<cmg::Electron, cmg::Electron>  & zeleele = (*zeleeleColl)[i];

    if(fabs(mZ - zeleele.mass())<deltamZeleele){
      deltamZeleele = fabs(mZ - zeleele.mass());
      bestZeleele=i;
    }
  }
   
  //chose the best Z btw mumu and eleele
  unsigned int bestZFlavor = 999;
  if(deltamZmumu<deltamZeleele) {
    bestZFlavor=0;
  }
  else {
    bestZFlavor=1;
  }

  //store the info of the best Z into mumu collection
  for(unsigned int i=0 ; i<zmumuColl->size() ; ++i ){
    cmg::DiObject<cmg::Muon, cmg::Muon>  & zmumu = (*zmumuColl)[i];
   if(i==bestZmumu && bestZFlavor==0)
      zmumu.addUserFloat("bestZ",2);
    else if(i==bestZmumu && bestZFlavor!=0)
      zmumu.addUserFloat("bestZ",1);
    else
      zmumu.addUserFloat("bestZ",0);
  }
 
  //store the info of the best Z into eleele collection
  for(unsigned int i=0 ; i<zeleeleColl->size() ; ++i ){
    cmg::DiObject<cmg::Electron, cmg::Electron>  & zeleele = (*zeleeleColl)[i];

    if(i==bestZeleele && bestZFlavor==1)
      zeleele.addUserFloat("bestZ",2);
    else if(i==bestZeleele && bestZFlavor!=1)
      zeleele.addUserFloat("bestZ",1);
    else
      zeleele.addUserFloat("bestZ",0);

  }
 
 
    // and put it into the event
     iEvent.put(zmumuColl);
     iEvent.put(zeleeleColl);
}



#endif
