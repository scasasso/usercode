// -*- C++ -*-
//
// Package:    MCTruthAnalyzer
// Class:      MCTruthAnalyzer
// 
/**\class MCTruthAnalyzer MCTruthAnalyzer.cc GenAnalyzer/MCTruthAnalyzer/src/MCTruthAnalyzer.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Stefano Casasso,,,
//         Created:  Thu Mar 24 14:59:11 CET 2011
// $Id$
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/ServiceRegistry/interface/Service.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

// includes from Alberto's code
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/Candidate/interface/CompositeCandidate.h"
#include "CommonTools/CandUtils/interface/AddFourMomenta.h"
#include "DataFormats/Common/interface/GetProduct.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/MuonReco/interface/MuonFwd.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/CompositeCandidate.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "SimGeneral/HepPDTRecord/interface/PDTRecord.h"
#include "SimGeneral/HepPDTRecord/interface/ParticleDataTable.h"

//
// class declaration
//
#include "TH1I.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TMath.h"

using namespace edm;
using namespace std;
using namespace reco;

class MCTruthAnalyzer : public edm::EDAnalyzer {
   public:
      explicit MCTruthAnalyzer(const edm::ParameterSet&);
      ~MCTruthAnalyzer();


   private:
      virtual void beginJob() ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
      edm::InputTag genParticles_;
  
  //Mu counter
  TH1I *h1NMuons_;
  //Mu from Z
  TH1F *h1PtMuFromZ_;
  TH1F *h1EtaMuFromZ_;
  TH1F *h1PhiMuFromZ_;
  //Mu from Tau
  TH1F *h1PtMuFromTau_;
  TH1F *h1EtaMuFromTau_;
  TH1F *h1PhiMuFromTau_;
  //Mu from heavy flavour
  TH1F *h1PtMuFromHF_;
  TH1F *h1EtaMuFromHF_;
  TH1F *h1PhiMuFromHF_;
  //Mu mother Id
  TH1I *h1MotherIdMuon_;
  //Invariant mass
  //TH1F *h1InvMassMuFromZ_;

      // ----------member data ---------------------------
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
MCTruthAnalyzer::MCTruthAnalyzer(const edm::ParameterSet& iConfig)

{
  genParticles_=iConfig.getParameter<InputTag>("src");
   //now do what ever initialization is needed

}


MCTruthAnalyzer::~MCTruthAnalyzer()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to for each event  ------------
void
MCTruthAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{

  Int_t theMuonCounter_(0);

   // get gen particle candidates
   edm::Handle<GenParticleCollection> genParticlesCollection;
   iEvent.getByLabel(genParticles_, genParticlesCollection);

   for( GenParticleCollection::const_iterator genp = genParticlesCollection->begin();genp != genParticlesCollection->end(); ++ genp ) {  // loop over GEN particles
     
     //do a copy of the genParticle, not to skip anythin in the loop
     const reco::Candidate* p = &(*genp);
     
     //if final-state muons
     
     if( abs( p->pdgId() )==13 ){
       //cout<<"found a Gen Muon!"<<endl;
       theMuonCounter_++;
       
       //Fill Spectra for all muons
       //h1PtMuon_->Fill(p->pt()); 
       //h1EtaMuon_->Fill(p->eta()); 
       //h1PhiMuon_->Fill(p->phi());

       //Check muon's mother
       while (p->mother()!=0 && abs(p->mother()->pdgId()) == 13) {
	 p = p->mother();
       }
       h1MotherIdMuon_->Fill(p->mother()->pdgId());

       //Now muons are not mother of themselves

       //Now get muons from Z
       if( abs(p->mother()->pdgId()) == 23 ){
	 h1PtMuFromZ_->Fill(p->pt());
	 h1EtaMuFromZ_->Fill(p->eta());
	 h1PhiMuFromZ_->Fill(p->phi());
       }
       /*
       if( abs(p->mother()->pdgId() == 23 ) ){
	 if ( p->charge() > 0 )MuPlus.push_back(p);
	 else MuMinus.push_back(p);
       }
       */
       //Now get muons from tau
       if( abs(p->mother()->pdgId()) == 15 ){
	 h1PtMuFromTau_->Fill(p->pt());
	 h1EtaMuFromTau_->Fill(p->eta());
	 h1PhiMuFromTau_->Fill(p->phi());
       }
       //Now get muons from heavy flavour
       if( (abs(p->mother()->pdgId()) > 411 && abs(p->mother()->pdgId()) < 435) || // c-mesons
	   (abs(p->mother()->pdgId()) > 441 && abs(p->mother()->pdgId()) < 445)  ||// ccbar
	   (abs(p->mother()->pdgId()) > 511 && abs(p->mother()->pdgId()) < 545) ||// b-mesons
	   (abs(p->mother()->pdgId()) > 551 && abs(p->mother()->pdgId()) < 557) ||// bbbar
	   (abs(p->mother()->pdgId()) > 4122 && abs(p->mother()->pdgId()) < 4444) ||// c-barions
	   (abs(p->mother()->pdgId()) > 5122 && abs(p->mother()->pdgId()) < 5554) // b-barions
	   ) {
	 h1PtMuFromHF_->Fill(p->pt());
	 h1EtaMuFromHF_->Fill(p->eta());
	 h1PhiMuFromHF_->Fill(p->phi());
       }



     } 
   }
   //  h1NMuons_->Fill(genParticlesCollection->size());
   h1NMuons_->Fill(theMuonCounter_);
}


// ------------ method called once each job just before starting event loop  ------------
void 
MCTruthAnalyzer::beginJob()
{
  edm::Service<TFileService> fs;
  h1NMuons_ = fs->make<TH1I>("NMuons","Number of muons per event",20,-0.5,19.5);
  //Mu from Z
  h1PtMuFromZ_ = fs->make<TH1F>("pTMuonsFromZ","p_{T}^{gen} muon",250,0,120);
  h1EtaMuFromZ_ = fs->make<TH1F>("etaMuonsFromZ","#eta^{gen} muon",80,-5,5);
  h1PhiMuFromZ_ = fs->make<TH1F>("phiMuonsFromZ","#phi^{gen} muon",80,-TMath::Pi(),TMath::Pi());
  //Mu from Tau
  h1PtMuFromTau_ = fs->make<TH1F>("pTMuonsFromTau","p_{T}^{gen} muon",250,0,120);
  h1EtaMuFromTau_ = fs->make<TH1F>("etaMuonsFromTau","#eta^{gen} muon",80,-5,5);
  h1PhiMuFromTau_ = fs->make<TH1F>("phiMuonsFromTau","#phi^{gen} muon",80,-TMath::Pi(),TMath::Pi());
  //Mu from Heavy flavour
  h1PtMuFromHF_ = fs->make<TH1F>("pTMuonsfromHF","p_{T}^{gen} muon",250,0,120);
  h1EtaMuFromHF_ = fs->make<TH1F>("etaMuonsfromHF","#eta^{gen} muon",80,-5,5);
  h1PhiMuFromHF_ = fs->make<TH1F>("phiMuonsfromHF","#phi^{gen} muon",80,-TMath::Pi(),TMath::Pi());

  h1MotherIdMuon_ = fs->make<TH1I>("MotherIdMuon","PDGId of muon's mother",500,-0.5,499.5);
  /*
  //Mu vector
  vector MuPlus = vector();
  vector MuMinus = vector();
  */
}

// ------------ method called once each job just after ending the event loop  ------------
void 
MCTruthAnalyzer::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(MCTruthAnalyzer);
