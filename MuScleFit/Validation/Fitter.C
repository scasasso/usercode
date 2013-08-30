// Plain ROOT stuff
#include "TFile.h"
#include "TROOT.h"
#include "TSystem.h"
#include "TTree.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TH3F.h"
#include "TF1.h"
#include "TCanvas.h"  
#include "TPad.h"
#include "TBranch.h"
#include "TString.h"
#include "TGraphErrors.h"
#include "TMultiGraph.h"
#include "TProfile.h"

// Roofit stuff
#ifndef __CINT__
#include "RooGlobalFunc.h"
#endif
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooGaussian.h"
#include "RooVoigtian.h"
#include "RooExponential.h"
#include "RooPlot.h"
#include "RooDataHist.h"
#include "RooAddPdf.h"
#include "RooGaussModel.h"
#include "RooAddModel.h"
#include "RooPolynomial.h"
#include "RooCBShape.h"
#include "RooBreitWigner.h"
#include "RooChebychev.h"
#include "RooBernstein.h"
#include "RooGenericPdf.h"
#include "RooFFTConvPdf.h"

// Plain C++ stuff
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <sstream>

using namespace std;
using namespace RooFit;

const Double_t par_tolerance(0.000001);

namespace MyPDG {
  // PDG masses
  const Double_t mass_Z = 91.188;
  const Double_t width_Z = 2.495;
  const Double_t mass_Y = 9.460;
  const Double_t mass_JPsi = 3.097;
} 

class FitMM {
public:
  FitMM(const TH3& h3, float etaLow, float etaUp, float ptLow, float ptUp, TPad* , bool isMC);
  virtual ~FitMM() {}
  Double_t getPeak()       {return m_peak;} 
  Double_t getPeakError()  {return m_peak_err;}
  Double_t getSigma()      {return m_sigma;}
  Double_t getSigmaError() {return m_sigma_err;}
  void Banner() {}

protected:
  Double_t m_peak;       
  Double_t m_peak_err;	
  Double_t m_sigma;	
  Double_t m_sigma_err;	  
  Bool_t m_isMC;

  TH1D* m_h1_fits;

  TString m_etaLow_TS, m_etaUp_TS;
  TString m_ptLow_TS, m_ptUp_TS;
  TString m_titleString;
};


FitMM::FitMM(const TH3& h3, float etaLow, float etaUp, float ptLow, float ptUp, TPad* pad, bool isMC) : m_isMC(isMC) {
  int firstbinX = h3.GetXaxis()->FindBin(etaLow);
  int lastbinX  = h3.GetXaxis()->FindBin(etaUp);
  stringstream ssLowEta (stringstream::in | stringstream::out);
  stringstream ssUpEta (stringstream::in | stringstream::out);
  ssLowEta << etaLow; ssUpEta << etaUp;
  string etaLow_str = ssLowEta.str(); string etaUp_str = ssUpEta.str();
  m_etaLow_TS=TString(etaLow_str); m_etaUp_TS=TString(etaUp_str);
  
  int firstbinY = h3.GetYaxis()->FindBin(ptLow);
  int lastbinY = h3.GetYaxis()->FindBin(ptUp);
  stringstream ssLowPt (stringstream::in | stringstream::out);
  stringstream ssUpPt (stringstream::in | stringstream::out);
  ssLowPt << ptLow; ssUpPt << ptUp;
  string ptLow_str = ssLowPt.str(); string ptUp_str = ssUpPt.str();
  m_ptLow_TS=TString(ptLow_str); m_ptUp_TS=TString(ptUp_str);

  TString projString = "projY_"+m_ptLow_TS+"_"+m_ptUp_TS+"_"+m_etaLow_TS+"_"+m_etaUp_TS;
  m_titleString = "M_{#mu#mu} "+m_ptLow_TS+" < p_{T} < "+m_ptUp_TS+", "+m_etaLow_TS+" < #eta < "+m_etaUp_TS;
  m_h1_fits = h3.ProjectionZ(projString,firstbinX,lastbinX,firstbinY,lastbinY);

  pad->cd();
}


class FitZMM : public FitMM {
public:
  FitZMM(const TH3& h3, float etaLow, float etaUp, float ptLow, float ptUp, TPad* pad, bool isMC);
  void Banner();
  virtual ~FitZMM() {}
};

FitZMM::FitZMM(const TH3& h3, float etaLow, float etaUp, float ptLow, float ptUp, TPad* pad, bool isMC) :
  FitMM(h3, etaLow, etaUp, ptLow, ptUp, pad, isMC)  {
  Banner();

  // Fit with RooFit
  RooRealVar x("x", "M_{#mu#mu}",75., 105.);
  RooRealVar peak("peak", "peak", MyPDG::mass_Z, 80., 100.);
  RooRealVar width("width", "width", MyPDG::width_Z, 2.4, 2.7);
  width.setConstant(kTRUE);
  RooRealVar mean("mean", "mean", 0., -2., 2.);
  mean.setConstant(kTRUE);
  RooRealVar sigmaCB("sigma", "sigma", 1.5, 0.5, 3.);
  RooRealVar alpha("alpha", "alpha", 1.5, 0.05, 10.);
  RooRealVar n("n", "n", 1., 0.1, 100.);
  RooRealVar expCoeff("expCoeff", "expCoeff", 0., -10., 10.);
  
  RooRealVar a0("a0","a0", 0.,-10.,10.);
  RooRealVar a1("a1","a2", 0.,-10.,10.);
  RooRealVar a2("a2","a2", 0., -2., 2.);


  RooAbsPdf* bw = new RooBreitWigner("breitWigner", "breitWigner", x, peak, width);
  //RooGenericPdf *bw = new RooGenericPdf("Relativistic Breit-Wigner","RBW","@0/(pow(@0*@0 - @1*@1,2) + @2*@2*@0*@0*@0*@0/(@1*@1))", RooArgList(x,peak,width));
  RooAbsPdf* cb = new RooCBShape("crystalBall", "crystalBall", x, mean, sigmaCB, alpha, n);
  RooAbsPdf* signal = new RooFFTConvPdf("breitWignerTimesCB","breitWignerTimesCB",x, *bw, *cb);
  //  RooAbsPdf* background = new RooExponential("exponential", "exponential", x, expCoeff);
  RooGenericPdf* background = new RooGenericPdf("exponential","exponential","TMath::Exp(@1+@2*@0+@3*@0*@0)",RooArgList(x,a0,a1,a2));

  RooRealVar fSig("fSig", "fSig", 0.9, 0.4, 1.);
  RooAddPdf* model = new RooAddPdf("model", "model", RooArgList(*signal, *background), fSig);
  
  RooDataHist dh("dh", "dh", x, m_h1_fits);
  RooPlot* frame = x.frame();

  model->fitTo(dh);
  dh.plotOn(frame);
  if ( ! m_isMC ) {
    model->plotOn(frame, LineColor(kOrange+9));
    model->plotOn(frame, Components("exponential"), LineStyle(kDashed), LineColor(kOrange+9));
  } else {
    model->plotOn(frame);
    model->plotOn(frame, Components("exponential"), LineStyle(kDashed));
  }

  frame->SetTitle(m_titleString);
  frame->Draw();
  
  m_peak = peak.getVal();
  m_peak_err = peak.getError();
  m_sigma = sigmaCB.getVal();
  m_sigma_err = sigmaCB.getError();
  
  // clean up
  if ( bw != 0 ) delete bw;
  if ( cb != 0 ) delete cb;
  if ( signal != 0 ) delete signal;
  if ( background != 0 ) delete background;
  if ( model != 0 ) delete model;

}

void FitZMM::Banner(){
  char c = '#';
  TString resonance(" Z " );
  if ( !m_isMC ) {
    resonance+=" DATA ";
  } else {
    resonance+=" MC ";
  }
  cout << string(60, c) << endl;
  cout << "FITTING " <<  resonance+ " "+m_ptLow_TS+" < p_{T} < "+m_ptUp_TS+", "+m_etaLow_TS+" < #eta < "+m_etaUp_TS << endl;
  cout << string(60, c) << endl;
}

class FitYMM : public FitMM {
public:
  FitYMM(const TH3& h3, float etaLow, float etaUp, float ptLow, float ptUp, TPad* pad, bool isMC);
  void Banner();
  virtual ~FitYMM() {}
};

FitYMM::FitYMM(const TH3& h3, float etaLow, float etaUp, float ptLow, float ptUp, TPad* pad, bool isMC) :
  FitMM(h3, etaLow, etaUp, ptLow, ptUp, pad, isMC)  { 
  Banner();

  // Fit with RooFit
  RooRealVar x("x", "M_{#mu#mu}",8.7, 11.);
  if ( m_isMC ) x.setRange(8.8,10.);

  RooRealVar mean1("mean1", "mean1", MyPDG::mass_Y, 9.2, 9.8);
  RooRealVar sigmaCB1("sigma1", "sigma1", 0.08, 0.01, 1.);
  RooRealVar alpha1("alpha1", "alpha1", 1.5, 0.05, 10.);
  RooRealVar n1("n1", "n1", 1., 0.1, 100.);
  RooRealVar mean2("mean2", "mean2", 10.02, 9.8, 10.3);
  RooRealVar sigmaCB2("sigma2", "sigma2", 0.08, 0.01, 1.);
  RooRealVar alpha2("alpha2", "alpha2", 1.5, 0.05, 10.);
  RooRealVar n2("n2", "n2", 1., 0.1, 100.);
  RooRealVar mean3("mean3", "mean3", 10.36, 10.15, 10.55);
  RooRealVar sigmaCB3("sigma3", "sigma3", 0.08, 0.01, 1.);
  RooRealVar alpha3("alpha3", "alpha3", 1.5, 0.05, 10.);
  RooRealVar n3("n3", "n3", 1., 0.1, 100.);
  RooRealVar expCoeff("expCoeff", "expCoeff", 0., -10., 10.);
  RooRealVar a0("a0", "a0", 0.1, 0., 2.);
  RooRealVar a1("a1", "a1", 0.1, 0., 2.);
  RooRealVar a2("a2", "a2", 0.1, 0., 2.);
  RooRealVar a3("a3", "a3", 0.1, 0., 2.);
  RooRealVar a4("a4", "a4", 0.1, 0., 2.);

  RooAbsPdf* cb1 = new RooCBShape("crystalBall1", "crystalBall1", x, mean1, sigmaCB1, alpha1, n1);
  RooAbsPdf* cb2 = new RooCBShape("crystalBall2", "crystalBall2", x, mean2, sigmaCB1, alpha2, n2);
  RooAbsPdf* cb3 = new RooCBShape("crystalBall3", "crystalBall3", x, mean3, sigmaCB1, alpha3, n3);
  RooRealVar fCB1("fCB1","fCB1",0.3,0.,1.);
  RooRealVar fCB2("fCB2","fCB2",0.3,0.,1.);

  RooAddPdf* signal;
  if ( !m_isMC ) {
    signal = new RooAddPdf("tripleCB","tripleCB",RooArgList(*cb1,*cb2,*cb3), RooArgList(fCB1,fCB2));
  } else {
    signal = new RooAddPdf("singleCB","singleCB",RooArgList(*cb1), RooArgList());
  }

  //RooAbsPdf* background = new RooExponential("exponential", "exponential", x, expCoeff);
  RooAbsPdf* background = new RooBernstein("BernPol", "BernPol", x, RooArgList(a0,a1,a2,a3,a4));
  //RooAbsPdf* background = new RooChebychev("ChebyPol", "ChebyPol", x, RooArgList(a0,a1,a2,a3,a4));
  
  RooRealVar fSig("fSig", "fSig", 0.6, 0.3, 1.);
  RooAddPdf* model = new RooAddPdf("model", "model", RooArgList(*signal, *background), fSig);
  
  RooDataHist dh("dh", "dh", x, m_h1_fits);
  RooPlot* frame = x.frame();

  model->fitTo(dh);
  // RooGaussian *gauss1 = 0;
  // RooGaussian *gauss3 = 0;
  // if ( fabs(n1.getVal())>n1.getMax()*0.98 &&  fabs(n3.getVal())>n3.getMax()*0.98 ) {
  //   cout << " n1 && n3 AT LIMIT -> REFIT WITH A GAUSSIAN!" << endl;
  //   if ( model!=0 ) delete model;
  //   if ( signal!=0 ) delete signal;
  //   gauss1 = new RooGaussian("gauss","gauss",x, mean1, sigmaCB1);
  //   gauss3 = new RooGaussian("gauss","gauss",x, mean3, sigmaCB1);
  //   if ( !m_isMC ) {
  //     signal = new RooAddPdf("tripleCB","tripleCB",RooArgList(*gauss1,*cb2,*gauss3), RooArgList(fCB1,fCB2));
  //   } else {
  //     signal = new RooAddPdf("singleCB","singleCB",RooArgList(*gauss1), RooArgList());
  //   }
  //   model = new RooAddPdf("model", "model", RooArgList(*signal, *background), fSig);
  //   model->fitTo(dh);    
  // } else if ( fabs(n1.getVal())>n1.getMax()*0.98 ) {
  //   cout << " n1 AT LIMIT -> REFIT WITH A GAUSSIAN!" << endl;
  //   if ( model!=0 ) delete model;
  //   if ( signal!=0 ) delete signal;
  //   gauss1 = new RooGaussian("gauss","gauss",x, mean1, sigmaCB1);
  //   if ( !m_isMC ) {
  //     signal = new RooAddPdf("tripleCB","tripleCB",RooArgList(*gauss1,*cb2,*cb3), RooArgList(fCB1,fCB2));
  //   } else {
  //     signal = new RooAddPdf("singleCB","singleCB",RooArgList(*gauss1), RooArgList());
  //   }
  //   model = new RooAddPdf("model", "model", RooArgList(*signal, *background), fSig);
  //   model->fitTo(dh);    
  // } else if ( fabs(n3.getVal())>n3.getMax()*0.98 ) {
  //   cout << " n3 AT LIMIT -> REFIT WITH A GAUSSIAN!" << endl;
  //   if ( model!=0 ) delete model;
  //   if ( signal!=0 ) delete signal;
  //   gauss3 = new RooGaussian("gauss","gauss",x, mean3, sigmaCB1);
  //   if ( !m_isMC ) {
  //     signal = new RooAddPdf("tripleCB","tripleCB",RooArgList(*cb1,*cb2,*gauss3), RooArgList(fCB1,fCB2));
  //   } else {
  //     signal = new RooAddPdf("singleCB","singleCB",RooArgList(*gauss3), RooArgList());
  //   }
  //   model = new RooAddPdf("model", "model", RooArgList(*signal, *background), fSig);
  //   model->fitTo(dh);    
  // }
  // if ( fabs(a0.getVal())<par_tolerance ) { a0.setVal(0); a0.setConstant(kTRUE); refit=kTRUE;}
  // if ( fabs(a1.getVal())<par_tolerance ) { a1.setVal(0); a1.setConstant(kTRUE); refit=kTRUE;}
  // if ( fabs(a2.getVal())<par_tolerance ) { a2.setVal(0); a2.setConstant(kTRUE); refit=kTRUE;}
  // if ( fabs(a3.getVal())<par_tolerance ) { a3.setVal(0); a3.setConstant(kTRUE); refit=kTRUE;}
  // if ( fabs(a4.getVal())<par_tolerance ) { a4.setVal(0); a4.setConstant(kTRUE); refit=kTRUE;}
  // if ( refit )  model->fitTo(dh);

  dh.plotOn(frame);
  if ( ! m_isMC ) {
    model->plotOn(frame, LineColor(kOrange+9));
    model->plotOn(frame, Components("BernPol"), LineStyle(kDashed), LineColor(kOrange+9));
    // model->plotOn(frame, Components("ChebyPol"), LineStyle(kDashed), LineColor(kOrange+9));
  } else {
    model->plotOn(frame);
    model->plotOn(frame, Components("BernPol"), LineStyle(kDashed));
    // model->plotOn(frame, Components("ChebyPol"), LineStyle(kDashed));
  }

  frame->SetTitle(m_titleString);
  frame->Draw();
	
  m_peak = mean1.getVal();
  m_peak_err = mean1.getError();
  m_sigma = sigmaCB1.getVal();
  m_sigma_err = sigmaCB1.getError();

  // clean up
  if ( cb1 != 0 ) delete cb1;
  if ( cb2 != 0 ) delete cb2;
  if ( cb3 != 0 ) delete cb3;
  if ( signal != 0 ) delete signal;
  if ( background != 0 ) delete background;
  if ( model != 0 ) delete model;
}

void FitYMM::Banner(){
  char c = '#';
  TString resonance(" Y " );
  if ( !m_isMC ) {
    resonance+=" DATA ";
  } else {
    resonance+=" MC ";
  }
  cout << string(60, c) << endl;
  cout << "FITTING " <<  resonance+ " "+m_ptLow_TS+" < p_{T} < "+m_ptUp_TS+", "+m_etaLow_TS+" < #eta < "+m_etaUp_TS << endl;
  cout << string(60, c) << endl;
}

class FitJPsiMM : public FitMM {
public:
  FitJPsiMM(const TH3& h3, float etaLow, float etaUp, float ptLow, float ptUp, TPad* pad, bool isMC);
  void Banner(); 
  virtual ~FitJPsiMM() {}
};

FitJPsiMM::FitJPsiMM(const TH3& h3, float etaLow, float etaUp, float ptLow, float ptUp, TPad* pad, bool isMC) :
  FitMM(h3, etaLow, etaUp, ptLow, ptUp, pad, isMC)  {
  Banner(); 

  // Fit with RooFit
  RooRealVar x("x", "M_{#mu#mu}",2.9, 3.3);
  RooRealVar mean("mean", "mean", MyPDG::mass_JPsi, 2.9, 3.3);
  RooRealVar sigmaCB("sigma", "sigma", 0.05, 0.01, 1.);
  RooRealVar alpha("alpha", "alpha", 1.5, 0.05, 10.);
  RooRealVar n("n", "n", 1., 0.1, 100.);
  RooRealVar expCoeff("expCoeff", "expCoeff", 0., -10., 10.);
  RooRealVar a0("a0", "a0", 0.1, 0., 2.);
  RooRealVar a1("a1", "a1", 0.1, 0., 2.);
  RooRealVar a2("a2", "a2", 0.1, 0., 2.);
  RooRealVar a3("a3", "a3", 0.1, 0., 2.);
      
  RooAbsPdf* signal = new RooCBShape("crystalBall", "crystalBall", x, mean, sigmaCB, alpha, n);
  //RooAbsPdf* background = new RooExponential("exponential", "exponential", x, expCoeff);
  RooAbsPdf* background = new RooBernstein("BernPol", "BernPol", x, RooArgList(a0,a1,a2,a3));
  //RooAbsPdf* background = new RooChebychev("ChebyPol", "ChebyPol", x, RooArgList(a0,a1,a2,a3));
  
  RooRealVar fSig("fSig", "fSig", 0.8, 0.4, 1.);
  RooAddPdf* model = new RooAddPdf("model", "model", RooArgList(*signal, *background), fSig);
      
  RooDataHist dh("dh", "dh", x, m_h1_fits);
  RooPlot* frame = x.frame();

  model->fitTo(dh);
  // if ( fabs(n.getVal())>n.getMax()*0.95 ) {
  //   cout << " n AT LIMIT -> REFIT WITH A GAUSSIAN!" << endl;
  //   if ( model!=0 ) delete model;
  //   if ( signal!=0 ) delete signal;
  //   signal = new RooGaussian("gauss","gauss",x, mean, sigmaCB);
  //   model = new RooAddPdf("model", "model", RooArgList(*signal, *background), fSig);
  //   model->fitTo(dh);    
  // }
  // if ( fabs(a1.getVal())<par_tolerance ) { a1.setVal(0); a1.setConstant(kTRUE); refit=kTRUE;}
  // if ( fabs(a2.getVal())<par_tolerance ) { a2.setVal(0); a2.setConstant(kTRUE); refit=kTRUE;}
  // if ( fabs(a3.getVal())<par_tolerance ) { a3.setVal(0); a3.setConstant(kTRUE); refit=kTRUE;}
  // if ( refit )  model->fitTo(dh);
  dh.plotOn(frame);
  if ( ! m_isMC ) {
    model->plotOn(frame, LineColor(kOrange+9));
    model->plotOn(frame, Components("BernPol"), LineStyle(kDashed), LineColor(kOrange+9));
    //model->plotOn(frame, Components("ChebyPol"), LineStyle(kDashed), LineColor(kOrange+9));
  } else {
    model->plotOn(frame);
    model->plotOn(frame, Components("BernPol"), LineStyle(kDashed));
    //model->plotOn(frame, Components("ChebyPol"), LineStyle(kDashed));
  }

  frame->SetTitle(m_titleString);
  frame->Draw();

  m_peak = mean.getVal();
  m_peak_err = mean.getError();
  m_sigma = sigmaCB.getVal();
  m_sigma_err = sigmaCB.getError();

  // clean up
  if ( signal != 0 ) delete signal;
  if ( background != 0 ) delete background;
  if ( model != 0 ) delete model;
}

void FitJPsiMM::Banner(){
  char c = '#';
  TString resonance(" J/Psi " );
  if ( !m_isMC ) {
    resonance+=" DATA ";
  } else {
    resonance+=" MC ";
  }
  cout << string(60, c) << endl;
  cout << "FITTING " <<  resonance+ " "+m_ptLow_TS+" < p_{T} < "+m_ptUp_TS+", "+m_etaLow_TS+" < #eta < "+m_etaUp_TS << endl;
  cout << string(60, c) << endl;
}

void Fitter(const TString& inputFile = "test.root", const TString& outFile = "TGEs.root", const TString& append = ""){

  typedef TGraphErrors tge;

  // Eta/Pt bins (fine version)
  const UInt_t nEtaBin_Z = 4;
  const UInt_t nEtaBin_Y = 3;
  const UInt_t nEtaBin_JPsi = 5;
  const UInt_t nPtBin_Z = 4;
  const UInt_t nPtBin_Y = 2;
  const UInt_t nPtBin_JPsi = 5;

  // Eta/Pt bins (coarse version)
  const UInt_t nEtaBinCoa_Z = 1;
  const UInt_t nEtaBinCoa_Y = 2;
  const UInt_t nEtaBinCoa_JPsi = 3;
  const UInt_t nPtBinCoa_Z = 2;
  const UInt_t nPtBinCoa_Y = 1;
  const UInt_t nPtBinCoa_JPsi = 3;

  // Z (fine)
  double etaBound_Z[nEtaBin_Z+1] = {0., 0.8, 1.5, 2.1, 2.4};
  double etaBinCenter_Z[nEtaBin_Z];
  double etaBinCenterErr_Z[nEtaBin_Z];
  for (UInt_t i=0; i<nEtaBin_Z; ++i) {
    etaBinCenter_Z[i] = (etaBound_Z[i]+etaBound_Z[i+1])/2;
    etaBinCenterErr_Z[i] = fabs(etaBound_Z[i]-etaBound_Z[i+1])/2;
    // cout<<"etaBinCenter["<<i<<"] = "<<etaBinCenter[i]<<endl;
    // cout<<"etaBinCenterErr["<<i<<"] = "<<etaBinCenterErr[i]<<endl;
  }

  double ptBound_Z[nPtBin_Z+1] = {20., 30., 40., 50., 90.};
  double ptBinCenter_Z[nPtBin_Z];
  double ptBinCenterErr_Z[nPtBin_Z];
  for (UInt_t i=0; i<nPtBin_Z; ++i) {
    ptBinCenter_Z[i] = (ptBound_Z[i]+ptBound_Z[i+1])/2;
    ptBinCenterErr_Z[i] = fabs(ptBound_Z[i]-ptBound_Z[i+1])/2;
    // cout<<"ptBinCenter["<<i<<"] = "<<ptBinCenter[i]<<endl;
    // cout<<"ptBinCenterErr["<<i<<"] = "<<ptBinCenterErr[i]<<endl;
  }

  // Z (coarse)
  double etaBoundCoa_Z[nEtaBinCoa_Z+1] = {0., 2.4};

  double ptBoundCoa_Z[nPtBinCoa_Z+1] = {20., 45., 90.};

  // Y
  double etaBound_Y[nEtaBin_Y+1] = {0., 0.8, 1.5, 2.4};
  double etaBinCenter_Y[nEtaBin_Y];
  double etaBinCenterErr_Y[nEtaBin_Y];
  for (UInt_t i=0; i<nEtaBin_Y; ++i) {
    etaBinCenter_Y[i] = (etaBound_Y[i]+etaBound_Y[i+1])/2;
    etaBinCenterErr_Y[i] = fabs(etaBound_Y[i]-etaBound_Y[i+1])/2;
    // cout<<"etaBinCenter["<<i<<"] = "<<etaBinCenter[i]<<endl;
    // cout<<"etaBinCenterErr["<<i<<"] = "<<etaBinCenterErr[i]<<endl;
  }

  double ptBound_Y[nPtBin_Y+1] = {10., 20., 30.};
  double ptBinCenter_Y[nPtBin_Y];
  double ptBinCenterErr_Y[nPtBin_Y];
  for (UInt_t i=0; i<nPtBin_Y; ++i) {
    ptBinCenter_Y[i] = (ptBound_Y[i]+ptBound_Y[i+1])/2;
    ptBinCenterErr_Y[i] = fabs(ptBound_Y[i]-ptBound_Y[i+1])/2;
    // cout<<"ptBinCenter["<<i<<"] = "<<ptBinCenter[i]<<endl;
    // cout<<"ptBinCenterErr["<<i<<"] = "<<ptBinCenterErr[i]<<endl;
  }

  // Y (coarse)
  double etaBoundCoa_Y[nEtaBinCoa_Y+1] = {0., 0.7, 2.4};

  double ptBoundCoa_Y[nPtBinCoa_Y+1] = {10., 20.};

  // JPsi
  double etaBound_JPsi[nEtaBin_JPsi+1] = {0., 0.4, 0.8, 1.2, 1.6, 2.4};
  double etaBinCenter_JPsi[nEtaBin_JPsi];
  double etaBinCenterErr_JPsi[nEtaBin_JPsi];
  for (UInt_t i=0; i<nEtaBin_JPsi; ++i) {
    etaBinCenter_JPsi[i] = (etaBound_JPsi[i]+etaBound_JPsi[i+1])/2;
    etaBinCenterErr_JPsi[i] = fabs(etaBound_JPsi[i]-etaBound_JPsi[i+1])/2;
    // cout<<"etaBinCenter["<<i<<"] = "<<etaBinCenter[i]<<endl;
    // cout<<"etaBinCenterErr["<<i<<"] = "<<etaBinCenterErr[i]<<endl;
  }

  double ptBound_JPsi[nPtBin_JPsi+1] = {5., 10., 15., 20., 25., 40.};
  double ptBinCenter_JPsi[nPtBin_JPsi];
  double ptBinCenterErr_JPsi[nPtBin_JPsi];
  for (UInt_t i=0; i<nPtBin_JPsi; ++i) {
    ptBinCenter_JPsi[i] = (ptBound_JPsi[i]+ptBound_JPsi[i+1])/2;
    ptBinCenterErr_JPsi[i] = fabs(ptBound_JPsi[i]-ptBound_JPsi[i+1])/2;
    // cout<<"ptBinCenter["<<i<<"] = "<<ptBinCenter[i]<<endl;
    // cout<<"ptBinCenterErr["<<i<<"] = "<<ptBinCenterErr[i]<<endl;
  }

  // JPsi (coarse)
  double etaBoundCoa_JPsi[nEtaBinCoa_JPsi+1] = {0., 0.6, 1.2, 2.0};

  double ptBoundCoa_JPsi[nPtBinCoa_JPsi+1] = {5., 7., 10., 15.};



  // Canvas
  TCanvas* c_ZvsPt_data = new TCanvas("c_ZvsPt_data", "c_ZvsPt_data", 1000, 1000);
  //c_ZvsPt_data->Divide(nEtaBinCoa_Z, nPtBin_Z);
  c_ZvsPt_data->Divide(2,2);

  TCanvas* c_ZvsEta_data = new TCanvas("c_ZvsEta_data", "c_ZvsEta_data", 1800, 1400);
  c_ZvsEta_data->Divide(nPtBinCoa_Z, nEtaBin_Z);

  TCanvas* c_ZvsPt_mc = new TCanvas("c_ZvsPt_mc", "c_ZvsPt_mc", 1000, 1000);
  //c_ZvsPt_mc->Divide(nEtaBinCoa_Z, nPtBin_Z);
  c_ZvsPt_mc->Divide(2,2);

  TCanvas* c_ZvsEta_mc = new TCanvas("c_ZvsEta_mc", "c_ZvsEta_mc", 1800, 1400);
  c_ZvsEta_mc->Divide(nPtBinCoa_Z, nEtaBin_Z);

  TCanvas* c_YvsPt_data = new TCanvas("c_YvsPt_data", "c_YvsPt_data", 1800, 1400);
  c_YvsPt_data->Divide(nEtaBinCoa_Y, nPtBin_Y);

  TCanvas* c_YvsEta_data = new TCanvas("c_YvsEta_data", "c_YvsEta_data", 800, 1000);
  c_YvsEta_data->Divide(nPtBinCoa_Y, nEtaBin_Y);

  TCanvas* c_YvsPt_mc = new TCanvas("c_YvsPt_mc", "c_YvsPt_mc", 1800, 1400);
  c_YvsPt_mc->Divide(nEtaBinCoa_Y, nPtBin_Y);

  TCanvas* c_YvsEta_mc = new TCanvas("c_YvsEta_mc", "c_YvsEta_mc", 800, 1000);
  c_YvsEta_mc->Divide(nPtBinCoa_Y, nEtaBin_Y);

  TCanvas* c_JPsivsPt_data = new TCanvas("c_JPsivsPt_data", "c_JPsivsPt_data", 1800, 1400);
  c_JPsivsPt_data->Divide(nEtaBinCoa_JPsi, nPtBin_JPsi);

  TCanvas* c_JPsivsEta_data = new TCanvas("c_JPsivsEta_data", "c_JPsivsEta_data", 1800, 1400);
  c_JPsivsEta_data->Divide(nPtBinCoa_JPsi, nEtaBin_JPsi);

  TCanvas* c_JPsivsPt_mc = new TCanvas("c_JPsivsPt_mc", "c_JPsivsPt_mc", 1800, 1400);
  c_JPsivsPt_mc->Divide(nEtaBinCoa_JPsi, nPtBin_JPsi);

  TCanvas* c_JPsivsEta_mc = new TCanvas("c_JPsivsEta_mc", "c_JPsivsEta_mc", 1800, 1400);
  c_JPsivsEta_mc->Divide(nPtBinCoa_JPsi, nEtaBin_JPsi);

  // Fits with all events
  TCanvas* c_Z_data = new TCanvas("c_Z_data", "c_Z_data");
  TCanvas* c_Z_mc = new TCanvas("c_Z_mc", "c_Z_mc");
  TCanvas* c_Y_data = new TCanvas("c_Y_data", "c_Y_data");
  TCanvas* c_Y_mc = new TCanvas("c_Y_mc", "c_Y_mc");
  TCanvas* c_JPsi_data = new TCanvas("c_JPsi_data", "c_JPsi_data");
  TCanvas* c_JPsi_mc = new TCanvas("c_JPsi_mc", "c_JPsi_mc");

  
  TFile* fIn = TFile::Open(inputFile,"READ");

  //Get histograms from file
  TH3F* h3_Z_data = (TH3F*)fIn->Get("h3_Z_data");
  TH3F* h3_Z_mc = (TH3F*)fIn->Get("h3_Z_mc");
  TH3F* h3_Y_data = (TH3F*)fIn->Get("h3_Y_data");
  TH3F* h3_Y_mc = (TH3F*)fIn->Get("h3_Y_mc");
  TH3F* h3_JPsi_data = (TH3F*)fIn->Get("h3_JPsi_data");
  TH3F* h3_JPsi_mc = (TH3F*)fIn->Get("h3_JPsi_mc");

  Bool_t doZ = (h3_Z_data != 0 && h3_Z_mc != 0);
  Bool_t doY = (h3_Y_data != 0 && h3_Y_mc != 0);
  Bool_t doJPsi = (h3_JPsi_data != 0 && h3_JPsi_mc != 0);

  int padCounter(0);

  //Define the Fitters
  FitZMM* fZMM; FitYMM* fYMM; FitJPsiMM* fJPsiMM;

  //Define the arrays
  Double_t M_Z_pt_data[nEtaBinCoa_Z][nPtBin_Z]; Double_t M_Z_pt_Err_data[nEtaBinCoa_Z][nPtBin_Z]; 
  Double_t S_Z_pt_data[nEtaBinCoa_Z][nPtBin_Z]; Double_t S_Z_pt_Err_data[nEtaBinCoa_Z][nPtBin_Z];
  Double_t M_Z_eta_data[nPtBinCoa_Z][nEtaBin_Z]; Double_t M_Z_eta_Err_data[nPtBinCoa_Z][nEtaBin_Z]; 
  Double_t S_Z_eta_data[nPtBinCoa_Z][nEtaBin_Z]; Double_t S_Z_eta_Err_data[nPtBinCoa_Z][nEtaBin_Z];
  Double_t M_Z_pt_mc[nEtaBinCoa_Z][nPtBin_Z]; Double_t M_Z_pt_Err_mc[nEtaBinCoa_Z][nPtBin_Z]; 
  Double_t S_Z_pt_mc[nEtaBinCoa_Z][nPtBin_Z]; Double_t S_Z_pt_Err_mc[nEtaBinCoa_Z][nPtBin_Z];
  Double_t M_Z_eta_mc[nPtBinCoa_Z][nEtaBin_Z]; Double_t M_Z_eta_Err_mc[nPtBinCoa_Z][nEtaBin_Z]; 
  Double_t S_Z_eta_mc[nPtBinCoa_Z][nEtaBin_Z]; Double_t S_Z_eta_Err_mc[nPtBinCoa_Z][nEtaBin_Z];
  Double_t M_Y_pt_data[nEtaBinCoa_Y][nPtBin_Y]; Double_t M_Y_pt_Err_data[nEtaBinCoa_Y][nPtBin_Y]; 
  Double_t S_Y_pt_data[nEtaBinCoa_Y][nPtBin_Y]; Double_t S_Y_pt_Err_data[nEtaBinCoa_Y][nPtBin_Y];
  Double_t M_Y_eta_data[nPtBinCoa_Y][nEtaBin_Y]; Double_t M_Y_eta_Err_data[nPtBinCoa_Y][nEtaBin_Y]; 
  Double_t S_Y_eta_data[nPtBinCoa_Y][nEtaBin_Y]; Double_t S_Y_eta_Err_data[nPtBinCoa_Y][nEtaBin_Y];
  Double_t M_Y_pt_mc[nEtaBinCoa_Y][nPtBin_Y]; Double_t M_Y_pt_Err_mc[nEtaBinCoa_Y][nPtBin_Y]; 
  Double_t S_Y_pt_mc[nEtaBinCoa_Y][nPtBin_Y]; Double_t S_Y_pt_Err_mc[nEtaBinCoa_Y][nPtBin_Y];
  Double_t M_Y_eta_mc[nPtBinCoa_Y][nEtaBin_Y]; Double_t M_Y_eta_Err_mc[nPtBinCoa_Y][nEtaBin_Y]; 
  Double_t S_Y_eta_mc[nPtBinCoa_Y][nEtaBin_Y]; Double_t S_Y_eta_Err_mc[nPtBinCoa_Y][nEtaBin_Y];
  Double_t M_JPsi_pt_data[nEtaBinCoa_JPsi][nPtBin_JPsi]; Double_t M_JPsi_pt_Err_data[nEtaBinCoa_JPsi][nPtBin_JPsi]; 
  Double_t S_JPsi_pt_data[nEtaBinCoa_JPsi][nPtBin_JPsi]; Double_t S_JPsi_pt_Err_data[nEtaBinCoa_JPsi][nPtBin_JPsi];
  Double_t M_JPsi_eta_data[nPtBinCoa_JPsi][nEtaBin_JPsi]; Double_t M_JPsi_eta_Err_data[nPtBinCoa_JPsi][nEtaBin_JPsi]; 
  Double_t S_JPsi_eta_data[nPtBinCoa_JPsi][nEtaBin_JPsi]; Double_t S_JPsi_eta_Err_data[nPtBinCoa_JPsi][nEtaBin_JPsi];
  Double_t M_JPsi_pt_mc[nEtaBinCoa_JPsi][nPtBin_JPsi]; Double_t M_JPsi_pt_Err_mc[nEtaBinCoa_JPsi][nPtBin_JPsi]; 
  Double_t S_JPsi_pt_mc[nEtaBinCoa_JPsi][nPtBin_JPsi]; Double_t S_JPsi_pt_Err_mc[nEtaBinCoa_JPsi][nPtBin_JPsi];
  Double_t M_JPsi_eta_mc[nPtBinCoa_JPsi][nEtaBin_JPsi]; Double_t M_JPsi_eta_Err_mc[nPtBinCoa_JPsi][nEtaBin_JPsi]; 
  Double_t S_JPsi_eta_mc[nPtBinCoa_JPsi][nEtaBin_JPsi]; Double_t S_JPsi_eta_Err_mc[nPtBinCoa_JPsi][nEtaBin_JPsi];
  
    
  // Fit the Z vs. pt (data)
  if (doZ) {
    
    for (UInt_t iEtaBin_Z=0; iEtaBin_Z<nEtaBinCoa_Z; ++iEtaBin_Z){
      float etaLow = (float)etaBoundCoa_Z[iEtaBin_Z];
      float etaUp = (float)etaBoundCoa_Z[iEtaBin_Z+1];    
      for (UInt_t iPtBin_Z=0; iPtBin_Z<nPtBin_Z; ++iPtBin_Z){
  	padCounter++;
  	float ptLow = (float)ptBound_Z[iPtBin_Z];
  	float ptUp = (float)ptBound_Z[iPtBin_Z+1];
  	fZMM = new FitZMM(*h3_Z_data,etaLow,etaUp,ptLow,ptUp,(TPad*)c_ZvsPt_data->GetPad(padCounter),false);
	
  	M_Z_pt_data[iEtaBin_Z][iPtBin_Z]     = fZMM->getPeak();
  	M_Z_pt_Err_data[iEtaBin_Z][iPtBin_Z] = fZMM->getPeakError();
  	S_Z_pt_data[iEtaBin_Z][iPtBin_Z]     = fZMM->getSigma();
  	S_Z_pt_Err_data[iEtaBin_Z][iPtBin_Z] = fZMM->getSigmaError();
  	if ( fZMM!=0 ) delete fZMM;
      }// loop over pT bins
    }// loop over eta bins
    
    c_ZvsPt_data->SaveAs("fits_ZvsPt_data"+append+".png");  
    
    // Fit the Z vs. eta (data)
    padCounter = 0;
    for (UInt_t iPtBin_Z=0; iPtBin_Z<nPtBinCoa_Z; ++iPtBin_Z){
      float ptLow = (float)ptBoundCoa_Z[iPtBin_Z];
      float ptUp = (float)ptBoundCoa_Z[iPtBin_Z+1];
      for (UInt_t iEtaBin_Z=0; iEtaBin_Z<nEtaBin_Z; ++iEtaBin_Z){
  	padCounter++;
  	float etaLow = (float)etaBound_Z[iEtaBin_Z];
  	float etaUp = (float)etaBound_Z[iEtaBin_Z+1];
  	fZMM = new FitZMM(*h3_Z_data,etaLow,etaUp,ptLow,ptUp,(TPad*)c_ZvsEta_data->GetPad(padCounter),false);

  	M_Z_eta_data[iPtBin_Z][iEtaBin_Z]     = fZMM->getPeak();
  	M_Z_eta_Err_data[iPtBin_Z][iEtaBin_Z] = fZMM->getPeakError();
  	S_Z_eta_data[iPtBin_Z][iEtaBin_Z]     = fZMM->getSigma(); 
  	S_Z_eta_Err_data[iPtBin_Z][iEtaBin_Z] = fZMM->getSigmaError();
  	if ( fZMM!=0 ) delete fZMM;	
      }// loop over pT bins
    }// loop over eta bins
    
    c_ZvsEta_data->SaveAs("fits_ZvsEta_data"+append+".png");  

    // Fit the Z vs. pt (mc)
    padCounter=0;
    for (UInt_t iEtaBin_Z=0; iEtaBin_Z<nEtaBinCoa_Z; ++iEtaBin_Z){
      float etaLow = (float)etaBoundCoa_Z[iEtaBin_Z];
      float etaUp = (float)etaBoundCoa_Z[iEtaBin_Z+1];    
      for (UInt_t iPtBin_Z=0; iPtBin_Z<nPtBin_Z; ++iPtBin_Z){
  	padCounter++;
  	float ptLow = (float)ptBound_Z[iPtBin_Z];
  	float ptUp = (float)ptBound_Z[iPtBin_Z+1];
  	fZMM = new FitZMM(*h3_Z_mc,etaLow,etaUp,ptLow,ptUp,(TPad*)c_ZvsPt_mc->GetPad(padCounter),true);
	
  	M_Z_pt_mc[iEtaBin_Z][iPtBin_Z]     = fZMM->getPeak();
  	M_Z_pt_Err_mc[iEtaBin_Z][iPtBin_Z] = fZMM->getPeakError();
  	S_Z_pt_mc[iEtaBin_Z][iPtBin_Z]     = fZMM->getSigma();
  	S_Z_pt_Err_mc[iEtaBin_Z][iPtBin_Z] = fZMM->getSigmaError();
  	if ( fZMM!=0 ) delete fZMM;
      }// loop over pT bins
    }// loop over eta bins
    
    c_ZvsPt_mc->SaveAs("fits_ZvsPt_mc"+append+".png");  
    
    // Fit the Z vs. eta (mc)
    padCounter = 0;
    for (UInt_t iPtBin_Z=0; iPtBin_Z<nPtBinCoa_Z; ++iPtBin_Z){
      float ptLow = (float)ptBoundCoa_Z[iPtBin_Z];
      float ptUp = (float)ptBoundCoa_Z[iPtBin_Z+1];
      for (UInt_t iEtaBin_Z=0; iEtaBin_Z<nEtaBin_Z; ++iEtaBin_Z){
  	padCounter++;
  	float etaLow = (float)etaBound_Z[iEtaBin_Z];
  	float etaUp = (float)etaBound_Z[iEtaBin_Z+1];
  	fZMM = new FitZMM(*h3_Z_mc,etaLow,etaUp,ptLow,ptUp,(TPad*)c_ZvsEta_mc->GetPad(padCounter),true);
	
  	M_Z_eta_mc[iPtBin_Z][iEtaBin_Z]     = fZMM->getPeak();
  	M_Z_eta_Err_mc[iPtBin_Z][iEtaBin_Z] = fZMM->getPeakError();
  	S_Z_eta_mc[iPtBin_Z][iEtaBin_Z]     = fZMM->getSigma(); 
  	S_Z_eta_Err_mc[iPtBin_Z][iEtaBin_Z] = fZMM->getSigmaError();
  	if ( fZMM!=0 ) delete fZMM;	
      }// loop over pT bins
    }// loop over eta bins

   c_ZvsEta_mc->SaveAs("fits_ZvsEta_mc"+append+".png");  

   }// process the Z

   if (doY){

     // Fit the Y vs. pt (data)
     padCounter=0;
     for (UInt_t iEtaBin_Y=0; iEtaBin_Y<nEtaBinCoa_Y; ++iEtaBin_Y){
       float etaLow = (float)etaBoundCoa_Y[iEtaBin_Y];
       float etaUp = (float)etaBoundCoa_Y[iEtaBin_Y+1];    
       for (UInt_t iPtBin_Y=0; iPtBin_Y<nPtBin_Y; ++iPtBin_Y){
	 padCounter++;
	 float ptLow = (float)ptBound_Y[iPtBin_Y];
	 float ptUp = (float)ptBound_Y[iPtBin_Y+1];
	 fYMM = new FitYMM(*h3_Y_data,etaLow,etaUp,ptLow,ptUp,(TPad*)c_YvsPt_data->GetPad(padCounter),false);
	 
	 M_Y_pt_data[iEtaBin_Y][iPtBin_Y]     = fYMM->getPeak();
	 M_Y_pt_Err_data[iEtaBin_Y][iPtBin_Y] = fYMM->getPeakError();
	 S_Y_pt_data[iEtaBin_Y][iPtBin_Y]     = fYMM->getSigma();
	 S_Y_pt_Err_data[iEtaBin_Y][iPtBin_Y] = fYMM->getSigmaError();
	 if ( fYMM!=0 ) delete fYMM;
       }// loop over pT bins
     }// loop over eta bins
     
     c_YvsPt_data->SaveAs("fits_YvsPt_data"+append+".png");  
     
     // Fit the Y vs. eta (data)
     padCounter = 0;
     for (UInt_t iPtBin_Y=0; iPtBin_Y<nPtBinCoa_Y; ++iPtBin_Y){
       float ptLow = (float)ptBoundCoa_Y[iPtBin_Y];
       float ptUp = (float)ptBoundCoa_Y[iPtBin_Y+1];
       for (UInt_t iEtaBin_Y=0; iEtaBin_Y<nEtaBin_Y; ++iEtaBin_Y){
	 padCounter++;
	 float etaLow = (float)etaBound_Y[iEtaBin_Y];
	 float etaUp = (float)etaBound_Y[iEtaBin_Y+1];
	 fYMM = new FitYMM(*h3_Y_data,etaLow,etaUp,ptLow,ptUp,(TPad*)c_YvsEta_data->GetPad(padCounter),false);
	 
	 M_Y_eta_data[iPtBin_Y][iEtaBin_Y]     = fYMM->getPeak();
	 M_Y_eta_Err_data[iPtBin_Y][iEtaBin_Y] = fYMM->getPeakError();
	 S_Y_eta_data[iPtBin_Y][iEtaBin_Y]     = fYMM->getSigma(); 
	 S_Y_eta_Err_data[iPtBin_Y][iEtaBin_Y] = fYMM->getSigmaError();
	 if ( fYMM!=0 ) delete fYMM;	
       }// loop over pT bins
     }// loop over eta bins
     
    c_YvsEta_data->SaveAs("fits_YvsEta_data"+append+".png");  
    
    // Fit the Y vs. pt (mc)
    padCounter=0;
    for (UInt_t iEtaBin_Y=0; iEtaBin_Y<nEtaBinCoa_Y; ++iEtaBin_Y){
      float etaLow = (float)etaBoundCoa_Y[iEtaBin_Y];
      float etaUp = (float)etaBoundCoa_Y[iEtaBin_Y+1];    
      for (UInt_t iPtBin_Y=0; iPtBin_Y<nPtBin_Y; ++iPtBin_Y){
	padCounter++;
	float ptLow = (float)ptBound_Y[iPtBin_Y];
	float ptUp = (float)ptBound_Y[iPtBin_Y+1];
	fYMM = new FitYMM(*h3_Y_mc,etaLow,etaUp,ptLow,ptUp,(TPad*)c_YvsPt_mc->GetPad(padCounter),true);
	
	M_Y_pt_mc[iEtaBin_Y][iPtBin_Y]     = fYMM->getPeak();
	M_Y_pt_Err_mc[iEtaBin_Y][iPtBin_Y] = fYMM->getPeakError();
	S_Y_pt_mc[iEtaBin_Y][iPtBin_Y]     = fYMM->getSigma();
	S_Y_pt_Err_mc[iEtaBin_Y][iPtBin_Y] = fYMM->getSigmaError();
	if ( fYMM!=0 ) delete fYMM;
      }// loop over pT bins
    }// loop over eta bins
    
    c_YvsPt_mc->SaveAs("fits_YvsPt_mc"+append+".png");  
    
    // Fit the Y vs. eta (mc)
    padCounter = 0;
    for (UInt_t iPtBin_Y=0; iPtBin_Y<nPtBinCoa_Y; ++iPtBin_Y){
      float ptLow = (float)ptBoundCoa_Y[iPtBin_Y];
      float ptUp = (float)ptBoundCoa_Y[iPtBin_Y+1];
      for (UInt_t iEtaBin_Y=0; iEtaBin_Y<nEtaBin_Y; ++iEtaBin_Y){
	padCounter++;
	float etaLow = (float)etaBound_Y[iEtaBin_Y];
	float etaUp = (float)etaBound_Y[iEtaBin_Y+1];
	fYMM = new FitYMM(*h3_Y_mc,etaLow,etaUp,ptLow,ptUp,(TPad*)c_YvsEta_mc->GetPad(padCounter),true);
	
	M_Y_eta_mc[iPtBin_Y][iEtaBin_Y]     = fYMM->getPeak();
	M_Y_eta_Err_mc[iPtBin_Y][iEtaBin_Y] = fYMM->getPeakError();
	S_Y_eta_mc[iPtBin_Y][iEtaBin_Y]     = fYMM->getSigma(); 
	S_Y_eta_Err_mc[iPtBin_Y][iEtaBin_Y] = fYMM->getSigmaError();
	if ( fYMM!=0 ) delete fYMM;	
      }// loop over pT bins
    }// loop over eta bins
    
    c_YvsEta_mc->SaveAs("fits_YvsEta_mc"+append+".png");  
    
    
   }// process the Y

   if (doJPsi){

     // Fit the JPsi vs. pt (data)
     padCounter=0;
     for (UInt_t iEtaBin_JPsi=0; iEtaBin_JPsi<nEtaBinCoa_JPsi; ++iEtaBin_JPsi){
       float etaLow = (float)etaBoundCoa_JPsi[iEtaBin_JPsi];
       float etaUp = (float)etaBoundCoa_JPsi[iEtaBin_JPsi+1];    
       for (UInt_t iPtBin_JPsi=0; iPtBin_JPsi<nPtBin_JPsi; ++iPtBin_JPsi){
	 padCounter++;
	 float ptLow = (float)ptBound_JPsi[iPtBin_JPsi];
	 float ptUp = (float)ptBound_JPsi[iPtBin_JPsi+1];
	 fJPsiMM = new FitJPsiMM(*h3_JPsi_data,etaLow,etaUp,ptLow,ptUp,(TPad*)c_JPsivsPt_data->GetPad(padCounter),false);
	 
	 M_JPsi_pt_data[iEtaBin_JPsi][iPtBin_JPsi]     = fJPsiMM->getPeak();
	 M_JPsi_pt_Err_data[iEtaBin_JPsi][iPtBin_JPsi] = fJPsiMM->getPeakError();
	 S_JPsi_pt_data[iEtaBin_JPsi][iPtBin_JPsi]     = fJPsiMM->getSigma();
	 S_JPsi_pt_Err_data[iEtaBin_JPsi][iPtBin_JPsi] = fJPsiMM->getSigmaError();
	 if ( fJPsiMM!=0 ) delete fJPsiMM;
       }// loop over pT bins
     }// loop over eta bins
     
     c_JPsivsPt_data->SaveAs("fits_JPsivsPt_data"+append+".png");  
     
     // Fit the JPsi vs. eta (data)
     padCounter = 0;
     for (UInt_t iPtBin_JPsi=0; iPtBin_JPsi<nPtBinCoa_JPsi; ++iPtBin_JPsi){
       float ptLow = (float)ptBoundCoa_JPsi[iPtBin_JPsi];
       float ptUp = (float)ptBoundCoa_JPsi[iPtBin_JPsi+1];
       for (UInt_t iEtaBin_JPsi=0; iEtaBin_JPsi<nEtaBin_JPsi; ++iEtaBin_JPsi){
	 padCounter++;
	 float etaLow = (float)etaBound_JPsi[iEtaBin_JPsi];
	 float etaUp = (float)etaBound_JPsi[iEtaBin_JPsi+1];
	 fJPsiMM = new FitJPsiMM(*h3_JPsi_data,etaLow,etaUp,ptLow,ptUp,(TPad*)c_JPsivsEta_data->GetPad(padCounter),false);
	 
	 M_JPsi_eta_data[iPtBin_JPsi][iEtaBin_JPsi]     = fJPsiMM->getPeak();
	 M_JPsi_eta_Err_data[iPtBin_JPsi][iEtaBin_JPsi] = fJPsiMM->getPeakError();
	 S_JPsi_eta_data[iPtBin_JPsi][iEtaBin_JPsi]     = fJPsiMM->getSigma(); 
	 S_JPsi_eta_Err_data[iPtBin_JPsi][iEtaBin_JPsi] = fJPsiMM->getSigmaError();
	 if ( fJPsiMM!=0 ) delete fJPsiMM;	
       }// loop over pT bins
     }// loop over eta bins
     
     c_JPsivsEta_data->SaveAs("fits_JPsivsEta_data"+append+".png");  

     // Fit the JPsi vs. pt (mc)
     padCounter=0;
     for (UInt_t iEtaBin_JPsi=0; iEtaBin_JPsi<nEtaBinCoa_JPsi; ++iEtaBin_JPsi){
       float etaLow = (float)etaBoundCoa_JPsi[iEtaBin_JPsi];
       float etaUp = (float)etaBoundCoa_JPsi[iEtaBin_JPsi+1];    
       for (UInt_t iPtBin_JPsi=0; iPtBin_JPsi<nPtBin_JPsi; ++iPtBin_JPsi){
	 padCounter++;
	 float ptLow = (float)ptBound_JPsi[iPtBin_JPsi];
	 float ptUp = (float)ptBound_JPsi[iPtBin_JPsi+1];
	 fJPsiMM = new FitJPsiMM(*h3_JPsi_mc,etaLow,etaUp,ptLow,ptUp,(TPad*)c_JPsivsPt_mc->GetPad(padCounter),true);
	 
	 M_JPsi_pt_mc[iEtaBin_JPsi][iPtBin_JPsi]     = fJPsiMM->getPeak();
	 M_JPsi_pt_Err_mc[iEtaBin_JPsi][iPtBin_JPsi] = fJPsiMM->getPeakError();
	 S_JPsi_pt_mc[iEtaBin_JPsi][iPtBin_JPsi]     = fJPsiMM->getSigma();
	 S_JPsi_pt_Err_mc[iEtaBin_JPsi][iPtBin_JPsi] = fJPsiMM->getSigmaError();
	 if ( fJPsiMM!=0 ) delete fJPsiMM;
       }// loop over pT bins
     }// loop over eta bins

     c_JPsivsPt_mc->SaveAs("fits_JPsivsPt_mc"+append+".png");  

     // Fit the JPsi vs. eta (mc)
     padCounter = 0;
     for (UInt_t iPtBin_JPsi=0; iPtBin_JPsi<nPtBinCoa_JPsi; ++iPtBin_JPsi){
       float ptLow = (float)ptBoundCoa_JPsi[iPtBin_JPsi];
       float ptUp = (float)ptBoundCoa_JPsi[iPtBin_JPsi+1];
       for (UInt_t iEtaBin_JPsi=0; iEtaBin_JPsi<nEtaBin_JPsi; ++iEtaBin_JPsi){
	 padCounter++;
	 float etaLow = (float)etaBound_JPsi[iEtaBin_JPsi];
	 float etaUp = (float)etaBound_JPsi[iEtaBin_JPsi+1];
	 fJPsiMM = new FitJPsiMM(*h3_JPsi_mc,etaLow,etaUp,ptLow,ptUp,(TPad*)c_JPsivsEta_mc->GetPad(padCounter),true);

	 M_JPsi_eta_mc[iPtBin_JPsi][iEtaBin_JPsi]     = fJPsiMM->getPeak();
	 M_JPsi_eta_Err_mc[iPtBin_JPsi][iEtaBin_JPsi] = fJPsiMM->getPeakError();
	 S_JPsi_eta_mc[iPtBin_JPsi][iEtaBin_JPsi]     = fJPsiMM->getSigma(); 
	 S_JPsi_eta_Err_mc[iPtBin_JPsi][iEtaBin_JPsi] = fJPsiMM->getSigmaError();
	 if ( fJPsiMM!=0 ) delete fJPsiMM;	
       }// loop over pT bins
     }// loop over eta bins

     c_JPsivsEta_mc->SaveAs("fits_JPsivsEta_mc"+append+".png");  

   }// process the JPsi

  /*----------------------*/
  //  SUMMARY ALL EVENTS 
  /*----------------------*/

   float ptLow, ptUp, etaLow, etaUp;

   if (doZ){
     // Fit with all events Z
     ptLow = (float)ptBoundCoa_Z[0];
     ptUp = (float)ptBoundCoa_Z[nPtBinCoa_Z];
     etaLow = (float)etaBoundCoa_Z[0];
     etaUp = (float)etaBoundCoa_Z[nEtaBinCoa_Z];

     fZMM = new FitZMM(*h3_Z_data,etaLow,etaUp,ptLow,ptUp,c_Z_data,false);
     c_Z_data->SaveAs("c_Z_data"+append+".png");
     if ( fZMM!=0 ) delete fZMM;

     fZMM = new FitZMM(*h3_Z_mc,etaLow,etaUp,ptLow,ptUp,c_Z_mc,true);
     c_Z_mc->SaveAs("c_Z_mc"+append+".png");  
     if ( fZMM!=0 ) delete fZMM;
   }//process the Z

   if (doY){
     // Fit with all events Y
     ptLow = (float)ptBoundCoa_Y[0];
     ptUp = (float)ptBoundCoa_Y[nPtBinCoa_Y];
     etaLow = (float)etaBoundCoa_Y[0];
     etaUp = (float)etaBoundCoa_Y[nEtaBinCoa_Y];

     fYMM = new FitYMM(*h3_Y_data,etaLow,etaUp,ptLow,ptUp,c_Y_data,false);
     c_Y_data->SaveAs("c_Y_data"+append+".png");
     if ( fYMM!=0 ) delete fYMM;

     fYMM = new FitYMM(*h3_Y_mc,etaLow,etaUp,ptLow,ptUp,c_Y_mc,true);
     c_Y_mc->SaveAs("c_Y_mc"+append+".png");  
     if ( fYMM!=0 ) delete fYMM;
   }// process the Y

   // Fit with all events J/Psi
   if (doJPsi){
     ptLow = (float)ptBoundCoa_JPsi[0];
     ptUp = (float)ptBoundCoa_JPsi[nPtBinCoa_JPsi];
     etaLow = (float)etaBoundCoa_JPsi[0];
     etaUp = (float)etaBoundCoa_JPsi[nEtaBinCoa_JPsi];

     fJPsiMM = new FitJPsiMM(*h3_JPsi_data,etaLow,etaUp,ptLow,ptUp,c_JPsi_data,false);
     c_JPsi_data->SaveAs("c_JPsi_data"+append+".png");
     if ( fJPsiMM!=0 ) delete fJPsiMM;

     fJPsiMM = new FitJPsiMM(*h3_JPsi_mc,etaLow,etaUp,ptLow,ptUp,c_JPsi_mc,true);
     c_JPsi_mc->SaveAs("c_JPsi_mc"+append+".png");  
     if ( fJPsiMM!=0 ) delete fJPsiMM;
   }//process the JPsi

  
   // Create the output file
   TFile* fOut = new TFile(outFile,"RECREATE");
   
   //Define TGraphErrors
   tge* tge_scale_pt_Z_data[nEtaBinCoa_Z]; tge* tge_scale_eta_Z_data[nPtBinCoa_Z]; tge* tge_resol_pt_Z_data[nEtaBinCoa_Z]; tge* tge_resol_eta_Z_data[nPtBinCoa_Z];   
   tge* tge_scale_pt_Z_mc[nEtaBinCoa_Z]; tge* tge_scale_eta_Z_mc[nPtBinCoa_Z]; tge* tge_resol_pt_Z_mc[nEtaBinCoa_Z]; tge* tge_resol_eta_Z_mc[nPtBinCoa_Z];   
   tge* tge_scale_pt_Y_data[nEtaBinCoa_Y]; tge* tge_scale_eta_Y_data[nPtBinCoa_Y]; tge* tge_resol_pt_Y_data[nEtaBinCoa_Y]; tge* tge_resol_eta_Y_data[nPtBinCoa_Y];   
   tge* tge_scale_pt_Y_mc[nEtaBinCoa_Y]; tge* tge_scale_eta_Y_mc[nPtBinCoa_Y]; tge* tge_resol_pt_Y_mc[nEtaBinCoa_Y]; tge* tge_resol_eta_Y_mc[nPtBinCoa_Y];   
   tge* tge_scale_pt_JPsi_data[nEtaBinCoa_JPsi]; tge* tge_scale_eta_JPsi_data[nPtBinCoa_JPsi]; tge* tge_resol_pt_JPsi_data[nEtaBinCoa_JPsi]; tge* tge_resol_eta_JPsi_data[nPtBinCoa_JPsi];   
   tge* tge_scale_pt_JPsi_mc[nEtaBinCoa_JPsi]; tge* tge_scale_eta_JPsi_mc[nPtBinCoa_JPsi]; tge* tge_resol_pt_JPsi_mc[nEtaBinCoa_JPsi]; tge* tge_resol_eta_JPsi_mc[nPtBinCoa_JPsi];   
   
   TString indexString;

   // Initialize tge scale Z
   if (doZ){
     for (UInt_t i=0; i<nEtaBinCoa_Z; ++i){
       ostringstream convert; convert << i;
       indexString = convert.str();
       tge_scale_pt_Z_data[i] = new tge(nPtBin_Z, ptBinCenter_Z, M_Z_pt_data[i], ptBinCenterErr_Z, M_Z_pt_Err_data[i]);
       tge_scale_pt_Z_mc[i] = new tge(nPtBin_Z, ptBinCenter_Z, M_Z_pt_mc[i], ptBinCenterErr_Z, M_Z_pt_Err_mc[i]);
       tge_scale_pt_Z_data[i]->SetNameTitle("ScaleVsPt_Z_data_"+indexString, "ScaleVsPt_Z_data_"+indexString);
       tge_scale_pt_Z_data[i]->Write();
       tge_scale_pt_Z_mc[i]->SetNameTitle("ScaleVsPt_Z_mc_"+indexString, "ScaleVsPt_Z_mc_"+indexString);
       tge_scale_pt_Z_mc[i]->Write();
     }

     for (UInt_t i=0; i<nPtBinCoa_Z; ++i){
       ostringstream convert; convert << i;
       indexString = convert.str();
       tge_scale_eta_Z_data[i] = new tge(nEtaBin_Z, etaBinCenter_Z, M_Z_eta_data[i], etaBinCenterErr_Z, M_Z_eta_Err_data[i]);
       tge_scale_eta_Z_mc[i] = new tge(nEtaBin_Z, etaBinCenter_Z, M_Z_eta_mc[i], etaBinCenterErr_Z, M_Z_eta_Err_mc[i]);
       tge_scale_eta_Z_data[i]->SetNameTitle("ScaleVsEta_Z_data_"+indexString, "ScaleVsEta_Z_data_"+indexString);
       tge_scale_eta_Z_data[i]->Write();
       tge_scale_eta_Z_mc[i]->SetNameTitle("ScaleVsEta_Z_mc_"+indexString, "ScaleVsEta_Z_mc_"+indexString);
       tge_scale_eta_Z_mc[i]->Write();
     }

     // Initialize tge resol Z
     for (UInt_t i=0; i<nEtaBinCoa_Z; ++i){
       ostringstream convert; convert << i;
       indexString = convert.str();
       tge_resol_pt_Z_data[i] = new tge(nPtBin_Z, ptBinCenter_Z, S_Z_pt_data[i], ptBinCenterErr_Z, S_Z_pt_Err_data[i]);
       tge_resol_pt_Z_mc[i] = new tge(nPtBin_Z, ptBinCenter_Z, S_Z_pt_mc[i], ptBinCenterErr_Z, S_Z_pt_Err_mc[i]);
       tge_resol_pt_Z_data[i]->SetNameTitle("ResolVsPt_Z_data_"+indexString, "ResolVsPt_Z_data_"+indexString);
       tge_resol_pt_Z_data[i]->Write();
       tge_resol_pt_Z_mc[i]->SetNameTitle("ResolVsPt_Z_mc_"+indexString, "ResolVsPt_Z_mc_"+indexString);
       tge_resol_pt_Z_mc[i]->Write();
     }

     for (UInt_t i=0; i<nPtBinCoa_Z; ++i){
       ostringstream convert; convert << i;
       indexString = convert.str();
       tge_resol_eta_Z_data[i] = new tge(nEtaBin_Z, etaBinCenter_Z, S_Z_eta_data[i], etaBinCenterErr_Z, S_Z_eta_Err_data[i]);
       tge_resol_eta_Z_mc[i] = new tge(nEtaBin_Z, etaBinCenter_Z, S_Z_eta_mc[i], etaBinCenterErr_Z, S_Z_eta_Err_mc[i]);
       tge_resol_eta_Z_data[i]->SetNameTitle("ResolVsEta_Z_data_"+indexString, "ResolVsEta_Z_data_"+indexString);
       tge_resol_eta_Z_data[i]->Write();
       tge_resol_eta_Z_mc[i]->SetNameTitle("ResolVsEta_Z_mc_"+indexString, "ResolVsEta_Z_mc_"+indexString);
       tge_resol_eta_Z_mc[i]->Write();
     }
   }//process the Z

   // Initialize tge scale Y
   if (doY){
     for (UInt_t i=0; i<nEtaBinCoa_Y; ++i){
       ostringstream convert; convert << i;
       indexString = convert.str();
       tge_scale_pt_Y_data[i] = new tge(nPtBin_Y, ptBinCenter_Y, M_Y_pt_data[i], ptBinCenterErr_Y, M_Y_pt_Err_data[i]);
       tge_scale_pt_Y_mc[i] = new tge(nPtBin_Y, ptBinCenter_Y, M_Y_pt_mc[i], ptBinCenterErr_Y, M_Y_pt_Err_mc[i]);
       tge_scale_pt_Y_data[i]->SetNameTitle("ScaleVsPt_Y_data_"+indexString, "ScaleVsPt_Y_data_"+indexString);
       tge_scale_pt_Y_data[i]->Write();
       tge_scale_pt_Y_mc[i]->SetNameTitle("ScaleVsPt_Y_mc_"+indexString, "ScaleVsPt_Y_mc_"+indexString);
       tge_scale_pt_Y_mc[i]->Write();
     }

     for (UInt_t i=0; i<nPtBinCoa_Y; ++i){
       ostringstream convert; convert << i;
       indexString = convert.str();
       tge_scale_eta_Y_data[i] = new tge(nEtaBin_Y, etaBinCenter_Y, M_Y_eta_data[i], etaBinCenterErr_Y, M_Y_eta_Err_data[i]);
       tge_scale_eta_Y_mc[i] = new tge(nEtaBin_Y, etaBinCenter_Y, M_Y_eta_mc[i], etaBinCenterErr_Y, M_Y_eta_Err_mc[i]);
       tge_scale_eta_Y_data[i]->SetNameTitle("ScaleVsEta_Y_data_"+indexString, "ScaleVsEta_Y_data_"+indexString);
       tge_scale_eta_Y_data[i]->Write();
       tge_scale_eta_Y_mc[i]->SetNameTitle("ScaleVsEta_Y_mc_"+indexString, "ScaleVsEta_Y_mc_"+indexString);
       tge_scale_eta_Y_mc[i]->Write();
     }

     // Initialize tge resol Y
     for (UInt_t i=0; i<nEtaBinCoa_Y; ++i){
       ostringstream convert; convert << i;
       indexString = convert.str();
       tge_resol_pt_Y_data[i] = new tge(nPtBin_Y, ptBinCenter_Y, S_Y_pt_data[i], ptBinCenterErr_Y, S_Y_pt_Err_data[i]);
       tge_resol_pt_Y_mc[i] = new tge(nPtBin_Y, ptBinCenter_Y, S_Y_pt_mc[i], ptBinCenterErr_Y, S_Y_pt_Err_mc[i]);
       tge_resol_pt_Y_data[i]->SetNameTitle("ResolVsPt_Y_data_"+indexString, "ResolVsPt_Y_data_"+indexString);
       tge_resol_pt_Y_data[i]->Write();
       tge_resol_pt_Y_mc[i]->SetNameTitle("ResolVsPt_Y_mc_"+indexString, "ResolVsPt_Y_mc_"+indexString);
       tge_resol_pt_Y_mc[i]->Write();
     }

     for (UInt_t i=0; i<nPtBinCoa_Y; ++i){
       ostringstream convert; convert << i;
       indexString = convert.str();
       tge_resol_eta_Y_data[i] = new tge(nEtaBin_Y, etaBinCenter_Y, S_Y_eta_data[i], etaBinCenterErr_Y, S_Y_eta_Err_data[i]);
       tge_resol_eta_Y_mc[i] = new tge(nEtaBin_Y, etaBinCenter_Y, S_Y_eta_mc[i], etaBinCenterErr_Y, S_Y_eta_Err_mc[i]);
       tge_resol_eta_Y_data[i]->SetNameTitle("ResolVsEta_Y_data_"+indexString, "ResolVsEta_Y_data_"+indexString);
       tge_resol_eta_Y_data[i]->Write();
       tge_resol_eta_Y_mc[i]->SetNameTitle("ResolVsEta_Y_mc_"+indexString, "ResolVsEta_Y_mc_"+indexString);
       tge_resol_eta_Y_mc[i]->Write();
     }
   }//process the Y

   // Initialize tge scale JPsi
   if (doJPsi){
     for (UInt_t i=0; i<nEtaBinCoa_JPsi; ++i){
       ostringstream convert; convert << i;
       indexString = convert.str();
       tge_scale_pt_JPsi_data[i] = new tge(nPtBin_JPsi, ptBinCenter_JPsi, M_JPsi_pt_data[i], ptBinCenterErr_JPsi, M_JPsi_pt_Err_data[i]);
       tge_scale_pt_JPsi_mc[i] = new tge(nPtBin_JPsi, ptBinCenter_JPsi, M_JPsi_pt_mc[i], ptBinCenterErr_JPsi, M_JPsi_pt_Err_mc[i]);
       tge_scale_pt_JPsi_data[i]->SetNameTitle("ScaleVsPt_JPsi_data_"+indexString, "ScaleVsPt_JPsi_data_"+indexString);
       tge_scale_pt_JPsi_data[i]->Write();
       tge_scale_pt_JPsi_mc[i]->SetNameTitle("ScaleVsPt_JPsi_mc_"+indexString, "ScaleVsPt_JPsi_mc_"+indexString);
       tge_scale_pt_JPsi_mc[i]->Write();
     }

     for (UInt_t i=0; i<nPtBinCoa_JPsi; ++i){
       ostringstream convert; convert << i;
       indexString = convert.str();
       tge_scale_eta_JPsi_data[i] = new tge(nEtaBin_JPsi, etaBinCenter_JPsi, M_JPsi_eta_data[i], etaBinCenterErr_JPsi, M_JPsi_eta_Err_data[i]);
       tge_scale_eta_JPsi_mc[i] = new tge(nEtaBin_JPsi, etaBinCenter_JPsi, M_JPsi_eta_mc[i], etaBinCenterErr_JPsi, M_JPsi_eta_Err_mc[i]);
       tge_scale_eta_JPsi_data[i]->SetNameTitle("ScaleVsEta_JPsi_data_"+indexString, "ScaleVsEta_JPsi_data_"+indexString);
       tge_scale_eta_JPsi_data[i]->Write();
       tge_scale_eta_JPsi_mc[i]->SetNameTitle("ScaleVsEta_JPsi_mc_"+indexString, "ScaleVsEta_JPsi_mc_"+indexString);
       tge_scale_eta_JPsi_mc[i]->Write();
     }

     // Initialize tge resol JPsi
     for (UInt_t i=0; i<nEtaBinCoa_JPsi; ++i){
       ostringstream convert; convert << i;
       indexString = convert.str();
       tge_resol_pt_JPsi_data[i] = new tge(nPtBin_JPsi, ptBinCenter_JPsi, S_JPsi_pt_data[i], ptBinCenterErr_JPsi, S_JPsi_pt_Err_data[i]);
       tge_resol_pt_JPsi_mc[i] = new tge(nPtBin_JPsi, ptBinCenter_JPsi, S_JPsi_pt_mc[i], ptBinCenterErr_JPsi, S_JPsi_pt_Err_mc[i]);
       tge_resol_pt_JPsi_data[i]->SetNameTitle("ResolVsPt_JPsi_data_"+indexString, "ResolVsPt_JPsi_data_"+indexString);
       tge_resol_pt_JPsi_data[i]->Write();
       tge_resol_pt_JPsi_mc[i]->SetNameTitle("ResolVsPt_JPsi_mc_"+indexString, "ResolVsPt_JPsi_mc_"+indexString);
       tge_resol_pt_JPsi_mc[i]->Write();
     }

     for (UInt_t i=0; i<nPtBinCoa_JPsi; ++i){
       ostringstream convert; convert << i;
       indexString = convert.str();
       tge_resol_eta_JPsi_data[i] = new tge(nEtaBin_JPsi, etaBinCenter_JPsi, S_JPsi_eta_data[i], etaBinCenterErr_JPsi, S_JPsi_eta_Err_data[i]);
       tge_resol_eta_JPsi_mc[i] = new tge(nEtaBin_JPsi, etaBinCenter_JPsi, S_JPsi_eta_mc[i], etaBinCenterErr_JPsi, S_JPsi_eta_Err_mc[i]);
       tge_resol_eta_JPsi_data[i]->SetNameTitle("ResolVsEta_JPsi_data_"+indexString, "ResolVsEta_JPsi_data_"+indexString);
       tge_resol_eta_JPsi_data[i]->Write();
       tge_resol_eta_JPsi_mc[i]->SetNameTitle("ResolVsEta_JPsi_mc_"+indexString, "ResolVsEta_JPsi_mc_"+indexString);
       tge_resol_eta_JPsi_mc[i]->Write();
     }
   }//process the JPsi

 
   fOut->Write();
   fOut->Close();
   delete fIn;

}
