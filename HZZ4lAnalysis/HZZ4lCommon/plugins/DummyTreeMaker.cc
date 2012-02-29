// -*- C++ -*-
//
// Package:    DummyTreeMaker
// Class:      DummyTreeMaker
// 
/**\class DummyTreeMaker DummyTreeMaker.cc HZZ4lAnalysis/DummyTreeMaker/src/DummyTreeMaker.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Stefano Casasso,,,
//         Created:  Tue Feb 28 14:33:03 CET 2012
// $Id$
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "AnalysisDataFormats/CMGTools/interface/Muon.h"
#include "AnalysisDataFormats/CMGTools/interface/PFJet.h"
#include "AnalysisDataFormats/CMGTools/interface/CompoundTypes.h"
#include "HZZ4lAnalysis/DataFormats/interface/CompoundTypesHZZ4l.h"
#include "HZZ4lAnalysis/HZZ4lCommon/interface/DummyTree.h"
//
// class declaration
//

class DummyTreeMaker : public edm::EDAnalyzer {
public:
  explicit DummyTreeMaker(const edm::ParameterSet&);
  ~DummyTreeMaker();
  
  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);
  
  
private:
  virtual void beginJob() ;
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void endJob() ;
  
  virtual void beginRun(edm::Run const&, edm::EventSetup const&);
  virtual void endRun(edm::Run const&, edm::EventSetup const&);
  virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
  virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
  
  // ----------member data ---------------------------
  //Input tags
  //edm::InputTag higgsSrc_;
  
  DummyTree *myDummyTree;
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
DummyTreeMaker::DummyTreeMaker(const edm::ParameterSet& iConfig)

{
   //now do what ever initialization is needed
  //higgsSrc_(iConfig.getUntrackedParameter<edm::InputTag>("higgsSrc"))

}


DummyTreeMaker::~DummyTreeMaker()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
DummyTreeMaker::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
   using namespace cmg;

   //Get Higgs Collection
   edm::Handle< std::vector<cmg::DiObject<cmg::DiObject<cmg::Muon, cmg::Muon>, cmg::DiObject<cmg::Muon, cmg::Muon> > > > higgsHandle;
   iEvent.getByLabel(std::string("higgsSequence"),higgsHandle);

   myDummyTree->resetStruct();
   HZZ4lSummary &ev = myDummyTree->getEvent();
   //HiggsCandidate &hig = ev.getHiggs();

   ev.run    = iEvent.id().run();
   ev.lumi   = iEvent.luminosityBlock();
   ev.event  = iEvent.id().event();

   //This is not the proper way to fill the tree, since I'm not choosing the candidate...

   for(std::vector<cmg::DiObject<cmg::DiObject<cmg::Muon, cmg::Muon>, cmg::DiObject<cmg::Muon, cmg::Muon> > >::const_iterator higgs=higgsHandle->begin(); higgs!=higgsHandle->end(); ++higgs){
     
     ev.Higgs_.pT_l1 = higgs->leg1().leg1().pt();
     ev.Higgs_.pT_l2 = higgs->leg1().leg2().pt();
     ev.Higgs_.pT_l3 = higgs->leg2().leg1().pt();
     ev.Higgs_.pT_l4 = higgs->leg2().leg2().pt();
     
   }
   if ( higgsHandle->size() != 0 ) myDummyTree->fillTree();
   
}


// ------------ method called once each job just before starting event loop  ------------
void 
DummyTreeMaker::beginJob()
{
  edm::Service<TFileService> fs;
  myDummyTree = new DummyTree();
  myDummyTree->initTree( fs->make<TTree>("HZZ4l_Tree","Event Summary") );
}

// ------------ method called once each job just after ending the event loop  ------------
void 
DummyTreeMaker::endJob() 
{
}

// ------------ method called when starting to processes a run  ------------
void 
DummyTreeMaker::beginRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run  ------------
void 
DummyTreeMaker::endRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void 
DummyTreeMaker::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void 
DummyTreeMaker::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
DummyTreeMaker::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(DummyTreeMaker);
