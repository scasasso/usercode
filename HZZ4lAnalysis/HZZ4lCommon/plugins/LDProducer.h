#ifndef HZZ4lAnalysis_HZZ4lCommon_LDProducer_h
#define HZZ4lAnalysis_HZZ4lCommon_LDProducer_h

#include <memory>
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/EDProducer.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "DataFormats/Common/interface/ValueMap.h"
#include "HZZ4lAnalysis/DataFormats/interface/HiggsCandidate.h"

#include "RooDataSet.h"
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooDataHist.h"
#include "RooHistPdf.h"
#include "RooGaussian.h"
#include "TCanvas.h"
#include "TString.h"
#include "TAxis.h"
#include "RooPlot.h"
#include "TFile.h"
#include "TLegend.h"
#include "TGraphErrors.h"
#include "TChain.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TH3F.h"
#include "TF1.h"
#include "TString.h"
#include "TLorentzVector.h"
#include <sstream>
#include <string>
#include <vector>
#include "HZZ4lAnalysis/HZZ4lCommon/src/AngularPdfFactory.cc"
#include "HZZ4lAnalysis/HZZ4lCommon/src/RooqqZZ_JHU.cc"
#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#include "TMVA/MethodCuts.h"


using namespace RooFit;

template <class higgstype>
class LDProducer : public edm::EDProducer { 
public:
  explicit LDProducer(const edm::ParameterSet& iConfig) :
    src_(iConfig.getParameter<edm::InputTag>("src"))

  {
    produces<std::vector<higgstype> >();
  }
  
  virtual ~LDProducer() {}
  
  void produce(edm::Event & iEvent, const edm::EventSetup & iSetup) ;

  void beginJob();
  
private:	
  edm::InputTag src_ ;
  vector<double> my8DTemplate(bool normalized,double mZZ, double m1, double m2, double costhetastar, double costheta1, double costheta2, double phi, double phi1);
  pair<double,double> likelihoodDiscriminant (double mZZ, double m1, double m2, double costhetastar, double costheta1, double costheta2, double phi, double phi1,  double scaleFactor);
  void checkZorder(double& z1mass, double& z2mass, double& costhetastar, double& costheta1, double& costheta2, double& phi, double& phistar1);
  TFile *f;

  
};

template <class higgstype>
void LDProducer<higgstype>::produce(edm::Event & iEvent, const edm::EventSetup & iSetup) {

  // read input collection
  edm::Handle<std::vector<higgstype> > higgscandidates;
  iEvent.getByLabel(src_, higgscandidates);
  
  std::auto_ptr<std::vector<higgstype> > higgsColl( new std::vector<higgstype> (*higgscandidates) );

  for (unsigned int i=0 ; i<higgsColl->size() ; ++i ) {

    higgstype & ahiggs = (*higgsColl)[i];

    double mzz = ahiggs.mass();
    double m1 = ahiggs.leg1().mass();
    double m2 = ahiggs.leg2().mass();
    double costhetastar = ahiggs.costhetastar();
    double helcosthetaZl1 = ahiggs.helcosthetaZl1();
    double helcosthetaZl2 = ahiggs.helcosthetaZl2();
    double helphi = ahiggs.helphi();
    double helphiZl1 = ahiggs.phistarZl1();

    pair<double,double> P = likelihoodDiscriminant(mzz, m1, m2, costhetastar, helcosthetaZl1, helcosthetaZl2, helphi, helphiZl1);
    float psig = P.first;
    float pbkg = P.second;
    float ld = psig/(psig + pbkg);

    ahiggs.addUserFloat("LD",ld);
    ahiggs.addUserFloat("PSig",psig);
    ahiggs.addUserFloat("PBkg",pbkg);
    
  }

     // and put it into the event
     iEvent.put(higgsColl);
}

template<class higgstype>
void LDProducer<higgstype>::beginJob(){

  f = new TFile("../src/datafiles/my8DTemplateNotNorm.root","READ");
  
}


template <class higgstype>
vector<double> LDProducer<higgstype>::my8DTemplate(bool normalized,double mZZ, double m1, double m2, double costhetastar, double costheta1, double costheta2, double phi, double phi1){
  //read from a file the 3D and 2D template
  TH1F *h_mzz= (TH1F*)(f->Get("h_mzz"));
  TH3F *h_mzzm1m2= (TH3F*)(f->Get("h_mzzm1m2"));
  TH2F *h_mzzcosthetastar= (TH2F*)(f->Get("h_mzzcosthetastar"));
  TH2F *h_mzzcostheta1= (TH2F*)(f->Get("h_mzzcostheta1"));
  TH2F *h_mzzcostheta2= (TH2F*)(f->Get("h_mzzcostheta2"));
  TH2F *h_mzzphi1= (TH2F*)(f->Get("h_mzzphi1"));
  TH2F *h_mzzphi= (TH2F*)(f->Get("h_mzzphi"));

  //multiply the P values
  double n = h_mzz->GetBinContent(h_mzz->FindBin(mZZ));
  double Pmzzm1m2 = h_mzzm1m2->GetBinContent(h_mzzm1m2->FindBin(mZZ,m1,m2));

  // - - - - - - - - - - - - - - - whitbeck
  // if bin has no events: add 1
  // safety feature to prevent LD = 1 as a
  // result of low statistics

  if(Pmzzm1m2==0){
    Pmzzm1m2++;
    }
  // - - - - - - - - - - - - - - - 

  double Pmzzcosthetastar = h_mzzcosthetastar->GetBinContent(h_mzzcosthetastar->FindBin(mZZ,costhetastar));
  double Pmzzcostheta2 = h_mzzcostheta2->GetBinContent(h_mzzcostheta2->FindBin(mZZ,costheta2));
  double Pmzzcostheta1 = h_mzzcostheta1->GetBinContent(h_mzzcostheta1->FindBin(mZZ,costheta1));
  double Pmzzphi1 = h_mzzphi1->GetBinContent(h_mzzphi1->FindBin(mZZ,phi1));
  double Pmzzphi = h_mzzphi->GetBinContent(h_mzzphi->FindBin(mZZ,phi));

  //normalization
  double binwidth_mzzm1m2 = h_mzzm1m2->GetYaxis()->GetBinWidth(1) * h_mzzm1m2->GetZaxis()->GetBinWidth(1);
  double binwidth_mzzcosthetastar = h_mzzcosthetastar->GetYaxis()->GetBinWidth(1);
  double binwidth_mzzcostheta1 = h_mzzcostheta1->GetYaxis()->GetBinWidth(1);
  double binwidth_mzzcostheta2 = h_mzzcostheta1->GetYaxis()->GetBinWidth(1);
  double binwidth_mzzphi1 = h_mzzphi1->GetYaxis()->GetBinWidth(1);
  double binwidth_mzzphi = h_mzzphi->GetYaxis()->GetBinWidth(1);

  double Pmzzm1m2_norm = Pmzzm1m2/(n*binwidth_mzzm1m2); 
  double Pmzzcosthetastar_norm = Pmzzcosthetastar/(n*binwidth_mzzcosthetastar);
  double Pmzzcostheta1_norm = Pmzzcostheta1/(n*binwidth_mzzcostheta1);
  double Pmzzcostheta2_norm = Pmzzcostheta2/(n*binwidth_mzzcostheta2);
  double Pmzzphi1_norm = Pmzzphi1/(n*binwidth_mzzphi1);
  double Pmzzphi_norm = Pmzzphi/(n*binwidth_mzzphi);

  vector <double> P;
  P.push_back(Pmzzm1m2);
  P.push_back(Pmzzcosthetastar);
  P.push_back(Pmzzcostheta1);
  P.push_back(Pmzzcostheta2);
  P.push_back(Pmzzphi);
  P.push_back(Pmzzphi1);

  vector <double> P_norm;
  P_norm.push_back(Pmzzm1m2_norm);
  P_norm.push_back(Pmzzcosthetastar_norm);
  P_norm.push_back(Pmzzcostheta1_norm);
  P_norm.push_back(Pmzzcostheta2_norm);
  P_norm.push_back(Pmzzphi_norm);
  P_norm.push_back(Pmzzphi1_norm);

  delete h_mzz;
  delete h_mzzm1m2;
  delete h_mzzcosthetastar;
  delete h_mzzcostheta1;
  delete h_mzzcostheta2;
  delete h_mzzphi1;
  delete h_mzzphi;
  
  if(normalized)
    return P_norm;
  else
    return P;
}

template <class higgstype>
pair<double,double> LDProducer<higgstype>::likelihoodDiscriminant (double mZZ, double m1, double m2, double costhetastar, double costheta1, double costheta2, double phi, double phi1, double scaleFactor=5.0){
 RooRealVar* z1mass_rrv = new RooRealVar("z1mass","m_{Z1}",0,180);
  RooRealVar* z2mass_rrv = new RooRealVar("z2mass","m_{Z2}",0,120); 
  RooRealVar* costhetastar_rrv = new RooRealVar("costhetastar","cos#theta^{*}",-1,1);  
  RooRealVar* costheta1_rrv = new RooRealVar("costheta1","cos#theta_{1}",-1,1);  
  RooRealVar* costheta2_rrv = new RooRealVar("costheta2","cos#theta_{2}",-1,1);
  RooRealVar* phi_rrv= new RooRealVar("phi","#Phi",-3.1415,3.1415);
  RooRealVar* phi1_rrv= new RooRealVar("phi1","#Phi^{*}_{1}",-3.1415,3.1415);
  RooRealVar* mzz_rrv= new RooRealVar("mzz","mZZ",100,800);
  AngularPdfFactory *SMHiggs = new AngularPdfFactory(z1mass_rrv,z2mass_rrv,costheta1_rrv,costheta2_rrv,phi_rrv,mzz_rrv);
  RooqqZZ_JHU* SMZZ = new RooqqZZ_JHU("SMZZ","SMZZ",*z1mass_rrv,*z2mass_rrv,*costheta1_rrv,*costheta2_rrv,*phi_rrv,*costhetastar_rrv,*phi1_rrv,*mzz_rrv);
  SMHiggs->makeSMHiggs();
  SMHiggs->makeParamsConst(true);

  checkZorder(m1,m2,costhetastar,costheta1,costheta2,phi,phi1);
  
  z1mass_rrv->setVal(m1);  
  z2mass_rrv->setVal(m2);
  costhetastar_rrv->setVal(costhetastar);
  costheta1_rrv->setVal(costheta1);
  costheta2_rrv->setVal(costheta2);
  phi_rrv->setVal(phi);
  phi1_rrv->setVal(phi1);
  mzz_rrv->setVal(mZZ);

  vector <double> P=my8DTemplate(1, mZZ,  m1,  m2,  costhetastar,  costheta1,  costheta2,  phi,  phi1);
  
  double Pbackg;
  double Psig; 
  if(mZZ>100 && mZZ<180){
    Pbackg = P[0]*P[1]*P[2]*P[3]*P[4]*P[5]*scaleFactor;
    Psig=SMHiggs->getVal(mZZ);
  }
  if(mZZ>180&&mZZ<=2*91.188){
    z1mass_rrv->setVal(mZZ/2.);
    z2mass_rrv->setVal(mZZ/2.);
    Pbackg = SMZZ->getVal()/(SMZZ->createIntegral(RooArgSet(*costhetastar_rrv,*costheta1_rrv,*costheta2_rrv,*phi_rrv,*phi1_rrv))->getVal());
    Psig = SMHiggs->PDF->getVal()/(SMHiggs->PDF->createIntegral(RooArgSet(*costheta1_rrv,*costheta2_rrv,*phi_rrv))->getVal());
  }
  if(mZZ>2*91.188){
    z1mass_rrv->setVal(91.188);
    z2mass_rrv->setVal(91.188);
    Pbackg = SMZZ->getVal()/(SMZZ->createIntegral(RooArgSet(*costhetastar_rrv,*costheta1_rrv,*costheta2_rrv,*phi_rrv,*phi1_rrv))->getVal());
    Psig = SMHiggs->PDF->getVal()/(SMHiggs->PDF->createIntegral(RooArgSet(*costheta1_rrv,*costheta2_rrv,*phi_rrv))->getVal());
  }

  // - - - - - - - - - - - - - - - - - - - - - Whitbeck 
  // check whether P[i] is zero and print warning
  // message if so

  string varName[6]={"m1/m2","costhetastar","costheta1","coshteta2","phi","phi1"};
  for(int iVar=0; iVar<6; iVar++){

    if(P[iVar]==0 && (m1+m2)<mZZ && m2>12 && mZZ>100 && mZZ<180)
	cout << " uh oh... Probability of " << varName[iVar] << " is zero." << endl;
  }
  // - - - - - - - - - - - - - - - - - - - - - 

  delete z1mass_rrv; 
  delete z2mass_rrv; 
  delete costheta1_rrv;
  delete costheta2_rrv;
  delete phi_rrv;
  delete mzz_rrv; 
  delete SMZZ;
  delete SMHiggs;

  return make_pair(Psig,Pbackg);

}

template <class higgstype>
void LDProducer<higgstype>::checkZorder(double& z1mass, double& z2mass,
		 double& costhetastar, double& costheta1,
		 double& costheta2, double& phi, 
		 double& phistar1){

  double tempZ1mass=z1mass;
  double tempZ2mass=z2mass;
  double tempH1=costheta1;
  double tempH2=costheta2;
  double tempHs=costhetastar;
  double tempPhi1=phistar1;
  double tempPhi=phi;

  if(z2mass>z1mass){
    cout<<"inverted"<<endl;
    z1mass=tempZ2mass;
    z2mass=tempZ1mass;
    costhetastar=-tempHs;
    costheta1=tempH2;
    costheta2=tempH1;
    phi=tempPhi;
    phistar1=-tempPhi1-tempPhi;
    if(phistar1>3.1415)
      phistar1=phistar1-2*3.1415;
    if(phistar1<-3.1415)
      phistar1=phistar1+2*3.1415;

  }else
    return;

}

#endif
