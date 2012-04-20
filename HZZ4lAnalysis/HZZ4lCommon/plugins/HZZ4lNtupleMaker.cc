// -*- C++ -*-
//
// Package:    HZZ4lNtupleMaker
// Class:      HZZ4lNtupleMaker
// 
/**\class HZZ4lNtupleMaker HZZ4lNtupleMaker.cc HZZ4lAnalysis/HZZ4lNtupleMaker/src/HZZ4lNtupleMaker.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Stefano Casasso,,,
//         Created:  Tue Feb 28 14:33:03 CET 2012
// $Id: HZZ4lNtupleMaker.cc,v 1.2 2012/03/01 12:56:37 scasasso Exp $
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
#include "HZZ4lAnalysis/DataFormats/interface/HiggsCandidate.h"

#include "HZZ4lAnalysis/HZZ4lCommon/interface/HZZ4lNtupleFactory.h"
//
// class declaration
//
class HZZ4lNtupleMaker : public edm::EDAnalyzer {
public:
  explicit HZZ4lNtupleMaker(const edm::ParameterSet&);
  ~HZZ4lNtupleMaker();
  
  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);
  
  
private:
  virtual void beginJob() ;
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  template <class higgstype> void FillCandidate(higgstype higgs, const Int_t Htype);
  virtual void endJob() ;
  
  virtual void beginRun(edm::Run const&, edm::EventSetup const&);
  virtual void endRun(edm::Run const&, edm::EventSetup const&);
  virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
  virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);

  // ----------member data ---------------------------
  //Input tags
  //edm::InputTag higgsSrc_;
  
  HZZ4lNtupleFactory *myTree;
};

//
// constructors and destructor
//
HZZ4lNtupleMaker::HZZ4lNtupleMaker(const edm::ParameterSet& iConfig)
{
}


HZZ4lNtupleMaker::~HZZ4lNtupleMaker()
{
}


//
// member functions
//

// ------------ method called for each event  ------------
void HZZ4lNtupleMaker::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  //Get Higgs Collections

  //4Mu
  edm::Handle<std::vector<cmg::DiMuonDiMuonHiggs> > higgsMuMuHandle;
  iEvent.getByLabel(std::string("cmgDiMuonDiMuonHiggsLD"), higgsMuMuHandle);

  //4E
  edm::Handle<std::vector<cmg::DiElectronDiElectronHiggs> > higgsEEHandle;
  iEvent.getByLabel(std::string("cmgDiElectronDiElectronHiggsLD"), higgsEEHandle);

  //2Mu2E
  edm::Handle<std::vector<cmg::DiElectronDiMuonHiggs> > higgsEMuHandle;
  iEvent.getByLabel(std::string("cmgDiElectronDiMuonHiggsLD"), higgsEMuHandle);


  if (higgsMuMuHandle->size() == 0 && higgsEEHandle->size() == 0 && higgsEMuHandle->size() == 0) return;

  //Save general event info in the tree
  myTree->FillEventInfo(iEvent.id().run(), iEvent.id().event(), iEvent.luminosityBlock());

  for(std::vector<cmg::DiMuonDiMuonHiggs >::const_iterator higgs=higgsMuMuHandle->begin(); higgs!=higgsMuMuHandle->end(); ++higgs){
    FillCandidate(higgs, 0);
  }

  for(std::vector<cmg::DiElectronDiElectronHiggs >::const_iterator higgs=higgsEEHandle->begin(); higgs!=higgsEEHandle->end(); ++higgs){
    FillCandidate(higgs, 1);
  }

  for(std::vector<cmg::DiElectronDiMuonHiggs >::const_iterator higgs=higgsEMuHandle->begin(); higgs!=higgsEMuHandle->end(); ++higgs){
    FillCandidate(higgs, 2);
  }

  myTree->FillEvent();

  return;
}

template <class higgstype>
void HZZ4lNtupleMaker::FillCandidate(higgstype higgs, const Int_t Htype)
{
  //Initialize a new candidate into the tree
  myTree->createNewCandidate();

  //FIXME: Dobbiamo salvare info su qualita' del fit a H?
  //Chi2 e chi2constr

  //Fill the info on the Higgs candidate
  const Double_t ZZMass = higgs->mass();
  const Double_t ZZMassErr = 0.;   //FIXME higgs->massErr();
  const Double_t ZZisBestCand = false; //FIXME
  const Double_t ZZPt = higgs->pt();
  const Double_t ZZEta = higgs->eta();
  const Double_t ZZPhi = higgs->phi();
  const Double_t ZZLD = higgs->userFloat("LD");

  //convention: 0 -> 4mu   1 -> 4e   2 -> 2mu2e
  const Int_t HiggsType = Htype;

  myTree->FillHInfo(ZZMass, ZZMassErr, ZZisBestCand, ZZPt, ZZEta, ZZPhi, ZZLD, HiggsType);

  //Fill the info on the Z1 and Z2 candidates
  const Double_t Z1Mass = higgs->leg1().mass();
  const Double_t Z1Pt =   higgs->leg1().pt();
  const Double_t Z1Eta =  higgs->leg1().eta();
  const Double_t Z1Phi =  higgs->leg1().phi();

  const Double_t Z2Mass = higgs->leg2().mass();
  const Double_t Z2Pt =   higgs->leg2().pt();
  const Double_t Z2Eta =  higgs->leg2().eta();
  const Double_t Z2Phi =  higgs->leg2().phi();

  myTree->FillZInfo(Z1Mass, Z1Pt, Z1Eta, Z1Phi);
  myTree->FillZInfo(Z2Mass, Z2Pt, Z2Eta, Z2Phi);

  //Fill the angular variables
  myTree->FillAngularInfo(higgs->costhetastar(), higgs->helphi(), higgs->helphiZl1(), higgs->helphiZl2(), higgs->helcosthetaZl1(), higgs->helcosthetaZl2(), higgs->phistarZl1(), higgs->phistarZl2());

  //Fill the info on the lepton candidates
  const Double_t Lep1Pt =   higgs->leg1().leg1().pt();
  const Double_t Lep1Eta =  higgs->leg1().leg1().eta();
  const Double_t Lep1Phi =  higgs->leg1().leg1().phi();
  const Int_t Lep1Id =     higgs->leg1().leg1().pdgId();
  const Int_t Lep1SIP =    0.; //FIXME higgs->leg1().leg1().SIP();

  const Double_t Lep2Pt =   higgs->leg1().leg2().pt();
  const Double_t Lep2Eta =  higgs->leg1().leg2().eta();
  const Double_t Lep2Phi =  higgs->leg1().leg2().phi();
  const Int_t Lep2Id =     higgs->leg1().leg2().pdgId();
  const Int_t Lep2SIP =    0.; //FIXME higgs->leg1().leg2().SIP();

  const Double_t Lep3Pt =   higgs->leg2().leg1().pt();
  const Double_t Lep3Eta =  higgs->leg2().leg1().eta();
  const Double_t Lep3Phi =  higgs->leg2().leg1().phi();
  const Int_t Lep3Id =     higgs->leg2().leg1().pdgId();
  const Int_t Lep3SIP =    0.; //FIXME higgs->leg2().leg1().SIP();

  const Double_t Lep4Pt =   higgs->leg2().leg2().pt();
  const Double_t Lep4Eta =  higgs->leg2().leg2().eta();
  const Double_t Lep4Phi =  higgs->leg2().leg2().phi();
  const Int_t Lep4Id =     higgs->leg2().leg2().pdgId();
  const Int_t Lep4SIP =    0.; //FIXME higgs->leg2().leg2().SIP();

  myTree->FillLepInfo(Lep1Pt,Lep1Eta,Lep1Phi,Lep1Id,Lep1SIP);
  myTree->FillLepInfo(Lep2Pt,Lep2Eta,Lep2Phi,Lep2Id,Lep2SIP);
  myTree->FillLepInfo(Lep3Pt,Lep3Eta,Lep3Phi,Lep3Id,Lep3SIP);
  myTree->FillLepInfo(Lep4Pt,Lep4Eta,Lep4Phi,Lep4Id,Lep4SIP);
     
  //Isolation variables
  const Double_t Lep1chargedHadIso   = higgs->leg1().leg1().chargedHadronIso();
  const Double_t Lep1chargedAllIso   = higgs->leg1().leg1().chargedAllIso();
  const Double_t Lep1PUchargedHadIso = higgs->leg1().leg1().puChargedHadronIso();
  const Double_t Lep1neutralHadIso   = higgs->leg1().leg1().neutralHadronIso();
  const Double_t Lep1photonIso       = higgs->leg1().leg1().photonIso();
  const Double_t Lep1absIso          = higgs->leg1().leg1().absIso();
  const Double_t Lep1relIso          = higgs->leg1().leg1().relIso();

  const Double_t Lep2chargedHadIso   = higgs->leg1().leg2().chargedHadronIso();
  const Double_t Lep2chargedAllIso   = higgs->leg1().leg2().chargedAllIso();
  const Double_t Lep2PUchargedHadIso = higgs->leg1().leg2().puChargedHadronIso();
  const Double_t Lep2neutralHadIso   = higgs->leg1().leg2().neutralHadronIso();
  const Double_t Lep2photonIso       = higgs->leg1().leg2().photonIso();
  const Double_t Lep2absIso          = higgs->leg1().leg2().absIso();
  const Double_t Lep2relIso          = higgs->leg1().leg2().relIso();

  const Double_t Lep3chargedHadIso   = higgs->leg2().leg1().chargedHadronIso();
  const Double_t Lep3chargedAllIso   = higgs->leg2().leg1().chargedAllIso();
  const Double_t Lep3PUchargedHadIso = higgs->leg2().leg1().puChargedHadronIso();
  const Double_t Lep3neutralHadIso   = higgs->leg2().leg1().neutralHadronIso();
  const Double_t Lep3photonIso       = higgs->leg2().leg1().photonIso();
  const Double_t Lep3absIso          = higgs->leg2().leg1().absIso();
  const Double_t Lep3relIso          = higgs->leg2().leg1().relIso();

  const Double_t Lep4chargedHadIso   = higgs->leg2().leg2().chargedHadronIso();
  const Double_t Lep4chargedAllIso   = higgs->leg2().leg2().chargedAllIso();
  const Double_t Lep4PUchargedHadIso = higgs->leg2().leg2().puChargedHadronIso();
  const Double_t Lep4neutralHadIso   = higgs->leg2().leg2().neutralHadronIso();
  const Double_t Lep4photonIso       = higgs->leg2().leg2().photonIso();
  const Double_t Lep4absIso          = higgs->leg2().leg2().absIso();
  const Double_t Lep4relIso          = higgs->leg2().leg2().relIso();

  myTree->FillLepIsolInfo(Lep1chargedHadIso, Lep1chargedAllIso, Lep1PUchargedHadIso, Lep1neutralHadIso, Lep1photonIso, Lep1absIso, Lep1relIso);
  myTree->FillLepIsolInfo(Lep2chargedHadIso, Lep2chargedAllIso, Lep2PUchargedHadIso, Lep2neutralHadIso, Lep2photonIso, Lep2absIso, Lep2relIso);
  myTree->FillLepIsolInfo(Lep3chargedHadIso, Lep3chargedAllIso, Lep3PUchargedHadIso, Lep3neutralHadIso, Lep3photonIso, Lep3absIso, Lep3relIso);
  myTree->FillLepIsolInfo(Lep4chargedHadIso, Lep4chargedAllIso, Lep4PUchargedHadIso, Lep4neutralHadIso, Lep4photonIso, Lep4absIso, Lep4relIso);

  return;
}



// ------------ method called once each job just before starting event loop  ------------
void HZZ4lNtupleMaker::beginJob()
{
  edm::Service<TFileService> fs;
  myTree = new HZZ4lNtupleFactory( fs->make<TTree>("HZZ4l_Tree","Event Summary") );
}

// ------------ method called once each job just after ending the event loop  ------------
void HZZ4lNtupleMaker::endJob() 
{
}

// ------------ method called when starting to processes a run  ------------
void HZZ4lNtupleMaker::beginRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run  ------------
void HZZ4lNtupleMaker::endRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void HZZ4lNtupleMaker::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void HZZ4lNtupleMaker::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void HZZ4lNtupleMaker::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(HZZ4lNtupleMaker);
