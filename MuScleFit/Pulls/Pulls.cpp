// usage: 
// make
// ./pull /tmp/ymumuTree_Upsilon1SToMuMu.root
//
#include "../Validation/MuonPair.h"
#include "GenMuonPair.h"

#include "LinkDef.h"
#include "TFile.h"
#include "TROOT.h"
#include "TTree.h"
#include "TLegend.h"
#include "TPaveText.h"
#include "TLatex.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TProfile.h"
#include "TF1.h"
#include "TCanvas.h"  
#include "TPad.h"
#include "TBranch.h"
#include "TString.h"
#include "../MuScleFitCorrector_v4_2/MuScleFitCorrector.h"
#include "Rtypes.h"

#include <iostream>
#include <stdio.h>

using namespace std;

// Gaussian fit helper
TF1* drawGFit(TH1 * h1, double nsigmasL, double nsigmasR, double min, double max, TPad * pad);
TF1* drawResGausFit(TH1 * h1, TPad * pad);

class HistosManager {
public:
  HistosManager(const char*, const char*, int, double, double, int);
  void monitor(double x1_raw, double x2_raw, double mass);
  void analyze(double x1_reco, double k1_reco, double k1_gen, 
	       double x2_reco, double k2_reco, double k2_gen, 
	       double sigmaRelPt1[], double sigmaRelPt2[]);
  void draw(const char*);

private:

  const int nBin;
  double* xBin;
  // array of h1 for residuals 
  TH1D** h_DeltaKvsX_neg;  
  TH1D** h_DeltaKvsX_pos;  

  // monitor input eta distribution
  TH1D* h1_X_Y1S;
  TH1D* h1_X_Z  ;
  TH1D* h1_X_all;

  // Summary profiles of the resolution expected from the paramerization
  TProfile** hp_ResKvsX_neg;
  TProfile** hp_ResKvsX_pos;

  // Summary hitsos of the residual offset from MC truth
  TH1D* h_MeanDeltaKvsX_neg_2s;
  TH1D* h_MeanDeltaKvsX_pos_2s;

  // Summary hitsos of the measured resolution from MC truth
  TH1D* h_SigmaKvsX_neg_2s;
  TH1D* h_SigmaKvsX_pos_2s;

  TH1D* h_SigmaKvsX_neg_3s;
  TH1D* h_SigmaKvsX_pos_3s;

  // Summary histos of the chi2/ndof of the gaussian fits
  TH1D* h_Chi2NDFvsX_neg_2s;
  TH1D* h_Chi2NDFvsX_pos_2s;
  TH1D* h_Chi2NDFvsX_neg_3s;
  TH1D* h_Chi2NDFvsX_pos_3s;

  // Summary histos 
  TH1D* h_RatiovsX_neg_2s;
  TH1D* h_RatiovsX_pos_2s;

  int nCor;
};
  
  
HistosManager::HistosManager(const char* xName, const char* xLabel, int nX, double x0, double dx, int nC) : nBin(nX), nCor(nC) {

  char h_name[50];
  char h_label[50];

  xBin = new double[nBin+1];
  xBin[0]=x0;

  h_DeltaKvsX_neg = new TH1D* [nBin];
  h_DeltaKvsX_pos = new TH1D* [nBin];
  
  for ( int iBin=0; iBin<nBin; iBin++ ) {    
    
    xBin[iBin+1]=xBin[iBin]+dx;

    sprintf(h_name ,"h_DeltaKvs%s_neg_bin%d", xName, iBin);
    sprintf(h_label,"(k{reco}-k{gen})/k{gen} (%s{-})",xLabel);
    h_DeltaKvsX_neg[iBin] = new TH1D(h_name,h_label,50,-0.1,0.1);
    sprintf(h_name ,"h_DeltaKvs%s_pos_bin%d", xName, iBin);
    sprintf(h_label,"(k{reco}-k{gen})/k{gen} (%s{+})",xLabel);
    h_DeltaKvsX_pos[iBin] = new TH1D(h_name,h_label,50,-0.1,0.1);
  }

  // monitor input distribution
  sprintf(h_name ,"h_%s_Y1S", xName);
  sprintf(h_label,";%s (#mu);",xLabel);
  h1_X_Y1S = new TH1D(h_name,h_label,nBin,xBin);
  sprintf (h_name, "h_%s_Z" , xName);
  h1_X_Z   = new TH1D(h_name,h_label,nBin,xBin);
  sprintf (h_name, "h_%s_all", xName);
  h1_X_all = new TH1D(h_name,h_label,nBin,xBin);

  // Summary profiles of the resolution expected from the paramerization
  hp_ResKvsX_neg = new TProfile* [nCor];
  hp_ResKvsX_pos = new TProfile* [nCor];
  sprintf(h_name ,"hp_resKvs%s_neg0", xName);
  sprintf(h_label,";%s (#mu^{-}); #sigma(#kappa)/#kappa",xLabel);
  hp_ResKvsX_neg[0] = new TProfile(h_name,h_label,nBin,xBin," ");
  sprintf(h_name, "hp_resKvs%s_neg1", xName);
  if ( nCor>1) hp_ResKvsX_neg[1] = new TProfile(h_name,h_label,nBin,xBin," ");
  sprintf (h_name, "hp_resKvs%s_neg2", xName);
  if ( nCor>2) hp_ResKvsX_neg[2] = new TProfile(h_name,h_label,nBin,xBin," ");

  sprintf(h_name ,"hp_resKvs%s_pos0", xName);
  sprintf(h_label,";%s (#mu^{+}); #sigma(#kappa)/#kappa",xLabel);
  hp_ResKvsX_pos[0] = new TProfile(h_name,h_label,nBin,xBin," ");
  sprintf (h_name, "hp_resKvs%s_pos1", xName);
  if ( nCor>1 ) hp_ResKvsX_pos[1] = new TProfile(h_name,h_label,nBin,xBin," ");
  sprintf (h_name, "hp_resKvs%s_pos2", xName);
  if ( nCor>2 ) hp_ResKvsX_pos[2] = new TProfile(h_name,h_label,nBin,xBin," ");

  hp_ResKvsX_neg[0]->SetLineWidth(2);
  hp_ResKvsX_neg[0]->SetLineColor(kBlue);
  hp_ResKvsX_neg[0]->GetYaxis()->SetTitleOffset(1.4);
  if ( nCor>1 ) {
    hp_ResKvsX_neg[1]->SetLineWidth(2);
    hp_ResKvsX_neg[1]->SetLineColor(kBlack);
    hp_ResKvsX_neg[1]->GetYaxis()->SetTitleOffset(1.4);
  }
  if ( nCor>2 ) {
    hp_ResKvsX_neg[2]->SetLineWidth(2);
    hp_ResKvsX_neg[2]->SetLineColor(kCyan);
    hp_ResKvsX_neg[2]->GetYaxis()->SetTitleOffset(1.4);
  }

  hp_ResKvsX_pos[0]->SetLineWidth(2); 
  hp_ResKvsX_pos[0]->SetLineColor(kBlue); 
  hp_ResKvsX_pos[0]->GetYaxis()->SetTitleOffset(1.4); 
  if ( nCor>1 ) {
    hp_ResKvsX_pos[1]->SetLineWidth(2); 
    hp_ResKvsX_pos[1]->SetLineColor(kBlack);
    hp_ResKvsX_pos[1]->GetYaxis()->SetTitleOffset(1.4); 
  }
  if ( nCor>2 ) {
    hp_ResKvsX_pos[2]->SetLineWidth(2); 
    hp_ResKvsX_pos[2]->SetLineColor(kCyan);
    hp_ResKvsX_pos[2]->GetYaxis()->SetTitleOffset(1.4); 
  }

  // Summary hitsos of the residual offset from MC truth
  sprintf(h_name ,"h_meandeltaKvs%s_neg_2s", xName);
  sprintf(h_label,";%s (#mu^{-}); #Delta(#kappa)/#kappa",xLabel);
  h_MeanDeltaKvsX_neg_2s = new TH1D(h_name,h_label,nBin,xBin);

  sprintf(h_name ,"h_meandeltaKvs%s_pos_2s", xName);
  sprintf(h_label,";%s (#mu^{+}); #Delta(#kappa)/#kappa",xLabel);
  h_MeanDeltaKvsX_pos_2s = new TH1D(h_name,h_label,nBin,xBin);

  h_MeanDeltaKvsX_neg_2s->SetMarkerStyle(kFullCircle); 
  h_MeanDeltaKvsX_neg_2s->SetMarkerSize(0.5); 
  h_MeanDeltaKvsX_neg_2s->SetMarkerColor(kRed); 
  h_MeanDeltaKvsX_neg_2s->SetLineColor(kRed);

  h_MeanDeltaKvsX_pos_2s->SetMarkerStyle(kFullCircle); 
  h_MeanDeltaKvsX_pos_2s->SetMarkerSize(0.5); 
  h_MeanDeltaKvsX_pos_2s->SetMarkerColor(kRed); 
  h_MeanDeltaKvsX_pos_2s->SetLineColor(kRed); 
 
  // Summary hitsos of the measured resolution from MC truth
  sprintf(h_name ,"h_sigmaKvs%s_neg_2s", xName);
  sprintf(h_label,";%s (#mu^{-}); #Delta(#kappa)/#kappa",xLabel);
  h_SigmaKvsX_neg_2s = new TH1D(h_name,h_label,nBin,xBin);
  sprintf(h_name ,"h_sigmaKvs%s_pos_2s", xName);
  sprintf(h_label,";%s (#mu^{+}); #Delta(#kappa)/#kappa",xLabel);
  h_SigmaKvsX_pos_2s = new TH1D(h_name,h_label,nBin,xBin);

  h_SigmaKvsX_neg_2s->SetMarkerStyle(kFullCircle); 
  h_SigmaKvsX_neg_2s->SetMarkerSize(0.5); 
  h_SigmaKvsX_neg_2s->SetMarkerColor(kRed); 
  h_SigmaKvsX_neg_2s->SetLineColor(kRed);

  h_SigmaKvsX_pos_2s->SetMarkerStyle(kFullCircle); 
  h_SigmaKvsX_pos_2s->SetMarkerSize(0.5); 
  h_SigmaKvsX_pos_2s->SetMarkerColor(kRed); 
  h_SigmaKvsX_pos_2s->SetLineColor(kRed); 

  sprintf (h_name, "h_sigmaKvs%s_neg_3s", xName);
  h_SigmaKvsX_neg_3s = new TH1D(h_name,";#eta (#mu^{-}); #sigma(#kappa)/#kappa",nBin,xBin);
  sprintf (h_name, "h_sigmaKvs%s_pos_3s", xName);
  h_SigmaKvsX_pos_3s = new TH1D(h_name,";#eta (#mu^{+}); #sigma(#kappa)/#kappa",nBin,xBin);

  h_SigmaKvsX_neg_3s->SetMarkerStyle(kFullCircle); 
  h_SigmaKvsX_neg_3s->SetMarkerSize(0.5); 
  h_SigmaKvsX_neg_3s->SetMarkerColor(kGreen); 
  h_SigmaKvsX_neg_3s->SetLineColor(kGreen);

  h_SigmaKvsX_pos_3s->SetMarkerStyle(kFullCircle); 
  h_SigmaKvsX_pos_3s->SetMarkerSize(0.5); 
  h_SigmaKvsX_pos_3s->SetMarkerColor(kGreen); 
  h_SigmaKvsX_pos_3s->SetLineColor(kGreen); 

  // Summary histos of the chi2/ndof of the gaussian fits
  sprintf(h_name ,"h_Chi2NDFvs%s_neg_2s", xName);
  sprintf(h_label,";%s (#mu^{-}); #chi^{2}/ndof",xLabel);
  h_Chi2NDFvsX_neg_2s = new TH1D(h_name,h_label,nBin,xBin);

  sprintf(h_name ,"h_Chi2NDFvs%s_pos_2s", xName);
  sprintf(h_label,";%s (#mu^{+}); #chi^{2}/ndof",xLabel);
  h_Chi2NDFvsX_pos_2s = new TH1D(h_name,h_label,nBin,xBin);

  h_Chi2NDFvsX_neg_2s->SetMarkerStyle(kFullCircle); 
  h_Chi2NDFvsX_neg_2s->SetMarkerSize(0.5); 
  h_Chi2NDFvsX_neg_2s->SetMarkerColor(kRed); 
  h_Chi2NDFvsX_neg_2s->SetLineColor(kRed);
  h_Chi2NDFvsX_neg_2s->SetStats(0);

  h_Chi2NDFvsX_pos_2s->SetMarkerStyle(kFullCircle); 
  h_Chi2NDFvsX_pos_2s->SetMarkerSize(0.5); 
  h_Chi2NDFvsX_pos_2s->SetMarkerColor(kRed); 
  h_Chi2NDFvsX_pos_2s->SetLineColor(kRed); 
  h_Chi2NDFvsX_pos_2s->SetStats(0);

  sprintf(h_name ,"h_Chi2NDFvs%s_neg_3s", xName);
  sprintf(h_label,";%s (#mu^{-}); #chi^{2}/ndof",xLabel);
  h_Chi2NDFvsX_neg_3s = new TH1D(h_name,h_label,nBin,xBin);
  sprintf(h_name ,"h_Chi2NDFvs%s_pos_3s", xName);
  sprintf(h_label,";%s (#mu^{+}); #chi^{2}/ndof",xLabel);
  h_Chi2NDFvsX_pos_3s = new TH1D(h_name,h_label,nBin,xBin);

  h_Chi2NDFvsX_neg_3s->SetMarkerStyle(kFullCircle); 
  h_Chi2NDFvsX_neg_3s->SetMarkerSize(0.5); 
  h_Chi2NDFvsX_neg_3s->SetMarkerColor(kGreen); 
  h_Chi2NDFvsX_neg_3s->SetLineColor(kGreen);
  h_Chi2NDFvsX_neg_3s->SetStats(0);

  h_Chi2NDFvsX_pos_3s->SetMarkerStyle(kFullCircle); 
  h_Chi2NDFvsX_pos_3s->SetMarkerSize(0.5); 
  h_Chi2NDFvsX_pos_3s->SetMarkerColor(kGreen); 
  h_Chi2NDFvsX_pos_3s->SetLineColor(kGreen); 
  h_Chi2NDFvsX_pos_3s->SetStats(0);

  // Summary histos 
  sprintf(h_name ,"h_Ratiovs%s_neg_2s", xName);
  sprintf(h_label,";%s (#mu^{-}); #sigma(MuFit)/#sigma(MC 2S)",xLabel);
  h_RatiovsX_neg_2s = new TH1D(h_name,h_label,nBin,xBin);
  sprintf(h_name ,"h_Ratiovs%s_pos_2s", xName);
  sprintf(h_label,";%s (#mu^{+}); #sigma(MuFit)/#sigma(MC 2S)",xLabel);
  h_RatiovsX_pos_2s = new TH1D(h_name,h_label,nBin,xBin);

  h_RatiovsX_neg_2s->SetMarkerStyle(kFullCircle); 
  h_RatiovsX_neg_2s->SetMarkerSize(0.5); 
  h_RatiovsX_neg_2s->SetMarkerColor(kRed); 
  h_RatiovsX_neg_2s->SetLineColor(kRed);
  h_RatiovsX_neg_2s->SetStats(0);

  h_RatiovsX_pos_2s->SetMarkerStyle(kFullCircle); 
  h_RatiovsX_pos_2s->SetMarkerSize(0.5); 
  h_RatiovsX_pos_2s->SetMarkerColor(kRed); 
  h_RatiovsX_pos_2s->SetLineColor(kRed); 
  h_RatiovsX_pos_2s->SetStats(0);
 
}

void HistosManager::monitor(double x1_raw, double x2_raw, double mass){


  // monitor input eta distribution
  h1_X_all->Fill(x1_raw);
  h1_X_all->Fill(x2_raw);
  if ( fabs(mass-10.)<2 ) {
    h1_X_Y1S->Fill(x1_raw);
    h1_X_Y1S->Fill(x2_raw);    
  }  else if ( fabs(mass-91.)<21 )  {
    h1_X_Z->Fill(x1_raw);
    h1_X_Z->Fill(x2_raw);
  }
      
}

void HistosManager::analyze(double x1_reco, double k1_reco, double k1_gen, 
			    double x2_reco, double k2_reco, double k2_gen, 
			    double sigmaRelPt1[], double sigmaRelPt2[]){
  //---------------- fill TH1 for resolution vs X
  int iBin = h_SigmaKvsX_neg_2s->GetXaxis()->FindBin(x1_reco)-1;
  if ( iBin > -1 && iBin < nBin ) { 
    h_DeltaKvsX_neg[iBin]->Fill(k1_reco/k1_gen-1.);
    for ( int iCor=0; iCor<nCor; iCor++ ) hp_ResKvsX_neg[iCor]->Fill(x1_reco,sigmaRelPt1[iCor]);
  }
  
  iBin = h_SigmaKvsX_pos_2s->GetXaxis()->FindBin(x2_reco)-1;
  if ( iBin > -1 && iBin < nBin ) { 
    h_DeltaKvsX_pos[iBin]->Fill(k2_reco/k2_gen-1.);
    for ( int iCor=0; iCor<nCor; iCor++ ) hp_ResKvsX_pos[iCor]->Fill(x2_reco,sigmaRelPt2[iCor]);
  }

  return;
}


void HistosManager::draw(const char* xName){

    char buffer[50];

    double nRMS(2);
    double mean, sigma;
    double mean_err, sigma_err;
    double chi2, ndof;
    double ratio, ratio_err;
    double r1, r2;

    //---------------- MONITORING X
    TCanvas* c1 = new TCanvas("c1","c1",900,900);
    c1->SetFillColor(kWhite);  
    h1_X_all->SetMinimum(0);
    h1_X_all->Draw();
    h1_X_Y1S->SetLineColor(kRed); h1_X_Y1S->Draw("same");
    h1_X_Z->SetLineColor(kBlue);  h1_X_Z->Draw("same");

    sprintf (buffer,"%sMonitor.pdf",xName);
    c1->SaveAs(buffer);

    // parameters for nice plotting
    int w, h;

    // define the size of the "up/down" plots
    double up_height     = 0.8;  // please tune so that the upper figures size will meet your requirement
    double dw_correction = 1.40; // please tune so that the smaller canvas size will work in your environment
    double font_size_dw  = 0.1;  // please tune the font size parameter for bottom figure    
    double dw_height    = (1. - up_height) * dw_correction;

    //---------------- RESOLUTION VS X

    // array of helper function for gaussian fit of the h1 residuals
    TF1** gaus_DeltaKvsX_neg_2s = new TF1* [nBin];
    TF1** gaus_DeltaKvsX_pos_2s = new TF1* [nBin];  
    TF1** gaus_DeltaKvsX_neg_3s = new TF1* [nBin];
    TF1** gaus_DeltaKvsX_pos_3s = new TF1* [nBin];  

    // canvas with table of 1D fit
    TCanvas* c1X_neg = new TCanvas("c1X_neg","c1X_neg",900,900);
    c1X_neg->SetFillColor(kWhite);  
    w = ceil(sqrt(nBin));
    h = round(sqrt(nBin));   
    c1X_neg->Divide(w,h);
    for ( int iBin=0; iBin<nBin; iBin++ ) {    
      c1X_neg->cd(iBin+1);
      gaus_DeltaKvsX_neg_2s[iBin] = drawGFit(h_DeltaKvsX_neg[iBin],nRMS  ,nRMS  ,-0.1,0.1, (TPad*)c1X_neg->GetPad(iBin+1));
      gaus_DeltaKvsX_neg_3s[iBin] = drawGFit(h_DeltaKvsX_neg[iBin],nRMS+1,nRMS+1,-0.1,0.1, (TPad*)c1X_neg->GetPad(iBin+1));

      mean = gaus_DeltaKvsX_neg_2s[iBin]->GetParameter("Mean");    
      mean_err = gaus_DeltaKvsX_neg_2s[iBin]->GetParError(1);
      h_MeanDeltaKvsX_neg_2s->SetBinContent(iBin+1,mean);
      h_MeanDeltaKvsX_neg_2s->SetBinError(iBin+1,mean_err);

      sigma = gaus_DeltaKvsX_neg_2s[iBin]->GetParameter("Sigma");    
      sigma_err = gaus_DeltaKvsX_neg_2s[iBin]->GetParError(2);
      h_SigmaKvsX_neg_2s->SetBinContent(iBin+1,sigma);
      h_SigmaKvsX_neg_2s->SetBinError(iBin+1,sigma_err);

      chi2 = gaus_DeltaKvsX_neg_2s[iBin]->GetChisquare();    
      ndof = (double)gaus_DeltaKvsX_neg_2s[iBin]->GetNDF();
      if ( ndof>0 ) h_Chi2NDFvsX_neg_2s->SetBinContent(iBin+1,chi2/ndof);

      if ( sigma > 0 ) {
	ratio = hp_ResKvsX_neg[0]->GetBinContent(iBin+1)/sigma;
	r1 = hp_ResKvsX_neg[0]->GetBinError(iBin+1)/hp_ResKvsX_neg[0]->GetBinContent(iBin+1);
	r2 = sigma_err/sigma; 
	ratio_err = ratio*sqrt(r1*r1+r2*r2);
	h_RatiovsX_neg_2s->SetBinContent(iBin+1,ratio);
	h_RatiovsX_neg_2s->SetBinError(iBin+1,ratio_err);
      }

      sigma = gaus_DeltaKvsX_neg_3s[iBin]->GetParameter("Sigma");    
      sigma_err = gaus_DeltaKvsX_neg_3s[iBin]->GetParError(2);
      h_SigmaKvsX_neg_3s->SetBinContent(iBin+1,sigma);
      h_SigmaKvsX_neg_3s->SetBinError(iBin+1,sigma_err);

      chi2 = gaus_DeltaKvsX_neg_3s[iBin]->GetChisquare();    
      ndof = (double)gaus_DeltaKvsX_neg_3s[iBin]->GetNDF();
      if ( ndof>0 ) h_Chi2NDFvsX_neg_3s->SetBinContent(iBin+1,chi2/ndof);

      h_DeltaKvsX_neg[iBin]->Draw();     
    }
    sprintf (buffer,"DeltaKvs%sTH1_neg.pdf",xName);
    c1X_neg->SaveAs(buffer);

    // canvas with table of 1D fit    
    TCanvas* c1X_pos = new TCanvas("c1X_pos","c1X_pos",900,900);
    c1X_pos->SetFillColor(kWhite);  
    c1X_pos->Divide(w,h);
    for ( int iBin=0; iBin<nBin; iBin++ ) { 
      c1X_pos->cd(iBin+1);   
      gaus_DeltaKvsX_pos_2s[iBin] = drawGFit(h_DeltaKvsX_pos[iBin],nRMS  ,nRMS  ,-0.1,0.1, (TPad*)c1X_pos->GetPad(iBin+1));
      gaus_DeltaKvsX_pos_3s[iBin] = drawGFit(h_DeltaKvsX_pos[iBin],nRMS+1,nRMS+1,-0.1,0.1, (TPad*)c1X_pos->GetPad(iBin+1));

      mean = gaus_DeltaKvsX_pos_2s[iBin]->GetParameter("Mean");    
      mean_err = gaus_DeltaKvsX_pos_2s[iBin]->GetParError(2);
      h_MeanDeltaKvsX_pos_2s->SetBinContent(iBin+1,mean);
      h_MeanDeltaKvsX_pos_2s->SetBinError(iBin+1,mean_err);

      sigma = gaus_DeltaKvsX_pos_2s[iBin]->GetParameter("Sigma");    
      sigma_err = gaus_DeltaKvsX_pos_2s[iBin]->GetParError(2);
      h_SigmaKvsX_pos_2s->SetBinContent(iBin+1,sigma);
      h_SigmaKvsX_pos_2s->SetBinError(iBin+1,sigma_err);

      chi2 = gaus_DeltaKvsX_pos_2s[iBin]->GetChisquare();    
      ndof = (double)gaus_DeltaKvsX_pos_2s[iBin]->GetNDF();
      if ( ndof>0 ) h_Chi2NDFvsX_pos_2s->SetBinContent(iBin+1,chi2/ndof);

      if ( sigma > 0 ) { 
	ratio = hp_ResKvsX_pos[0]->GetBinContent(iBin+1)/sigma;
	r1 = hp_ResKvsX_pos[0]->GetBinError(iBin+1)/hp_ResKvsX_pos[0]->GetBinContent(iBin+1);
	r2 = sigma_err/sigma; 
	ratio_err = ratio*sqrt(r1*r1+r2*r2);
	h_RatiovsX_pos_2s->SetBinContent(iBin+1,ratio);
	h_RatiovsX_pos_2s->SetBinError(iBin+1,ratio_err);
      }

      sigma = gaus_DeltaKvsX_pos_3s[iBin]->GetParameter("Sigma");    
      sigma_err = gaus_DeltaKvsX_pos_3s[iBin]->GetParError(2);
      h_SigmaKvsX_pos_3s->SetBinContent(iBin+1,sigma);
      h_SigmaKvsX_pos_3s->SetBinError(iBin+1,sigma_err);

      chi2 = gaus_DeltaKvsX_pos_3s[iBin]->GetChisquare();    
      ndof = (double)gaus_DeltaKvsX_pos_3s[iBin]->GetNDF();
      if ( ndof>0 ) h_Chi2NDFvsX_pos_3s->SetBinContent(iBin+1,chi2/ndof);

      h_DeltaKvsX_pos[iBin]->Draw(); 
    }
    sprintf (buffer,"DeltaKvs%sTH1_pos.pdf",xName);
    c1X_pos->SaveAs(buffer);

    TCanvas* c2BX = new TCanvas("c2BX","c2BX",600,900);
    c2BX->SetFillColor(kWhite);  
    c2BX->Divide(1,4);

    TPad* c2BX_1up = (TPad*) c2BX->GetListOfPrimitives()->FindObject("c2BX_1");
    TPad* c2BX_1dw = (TPad*) c2BX->GetListOfPrimitives()->FindObject("c2BX_2");
    TPad* c2BX_2up = (TPad*) c2BX->GetListOfPrimitives()->FindObject("c2BX_3");
    TPad* c2BX_2dw = (TPad*) c2BX->GetListOfPrimitives()->FindObject("c2BX_4");
    
    // set pad size
    c2BX_1up->SetPad(0., 0.5+0.5*(1 - up_height), 1., 0.5+0.5);
    c2BX_1dw->SetPad(0., 0.5                    , 1., 0.5+0.5*dw_height);
    c2BX_1up->SetFrameFillColor(0);
    c2BX_1up->SetFillColor(0);
    c2BX_1dw->SetFillColor(0);
    c2BX_1dw->SetFrameFillColor(0);
  
    // set top margin 0 for bottom figure
    c2BX_1dw->SetTopMargin(0);    

    // draw top figure
    c2BX_1up->cd(); 
    h_MeanDeltaKvsX_neg_2s->SetStats(0); 
    h_MeanDeltaKvsX_neg_2s->Draw(); 
    h_MeanDeltaKvsX_neg_2s->GetYaxis()->SetRangeUser(-0.005,+0.005);     

    TLegend* leg = new TLegend(0.35,0.75,0.75,0.85);  
    leg->SetBorderSize(1);
    leg->SetFillColor(kWhite);
    leg->SetTextFont(42);
    leg->AddEntry(h_MeanDeltaKvsX_neg_2s,"from MC truth post-MuScleFit","PL");
    leg->Draw("same");

    // draw bottom figure
    c2BX_1dw->cd();
    c2BX_1dw->SetLogy();
    h_Chi2NDFvsX_neg_2s->GetXaxis()->SetLabelSize(font_size_dw);
    h_Chi2NDFvsX_neg_2s->GetXaxis()->SetTitleSize(font_size_dw);
    h_Chi2NDFvsX_neg_2s->GetYaxis()->SetLabelSize(font_size_dw);
    h_Chi2NDFvsX_neg_2s->GetYaxis()->SetTitleSize(font_size_dw);
    h_Chi2NDFvsX_neg_2s->GetYaxis()->SetTitleOffset(0.4);
    h_Chi2NDFvsX_neg_2s->GetXaxis()->SetTitleOffset(0.1);
    h_Chi2NDFvsX_neg_2s->Draw("p"); 

    // set pad size
    c2BX_2up->SetPad(0., 0.5*(1 - up_height), 1., 0.5);
    c2BX_2dw->SetPad(0., 0.                 , 1., 0.5*dw_height);
    c2BX_2up->SetFrameFillColor(0);
    c2BX_2up->SetFillColor(0);
    c2BX_2dw->SetFillColor(0);
    c2BX_2dw->SetFrameFillColor(0);
  
    // set top margin 0 for bottom figure
    c2BX_2dw->SetTopMargin(0);    

    // draw top figure
    c2BX_2up->cd(); 
    h_MeanDeltaKvsX_pos_2s->SetStats(0); 
    h_MeanDeltaKvsX_pos_2s->Draw(); 
    h_MeanDeltaKvsX_pos_2s->GetYaxis()->SetRangeUser(-0.005,+0.005);     

    // draw bottom figure
    c2BX_2dw->cd();
    c2BX_2dw->SetLogy();
    h_Chi2NDFvsX_pos_2s->GetXaxis()->SetLabelSize(font_size_dw);
    h_Chi2NDFvsX_pos_2s->GetXaxis()->SetTitleSize(font_size_dw);
    h_Chi2NDFvsX_pos_2s->GetYaxis()->SetLabelSize(font_size_dw);
    h_Chi2NDFvsX_pos_2s->GetYaxis()->SetTitleSize(font_size_dw);
    h_Chi2NDFvsX_pos_2s->GetYaxis()->SetTitleOffset(0.4);
    h_Chi2NDFvsX_pos_2s->GetXaxis()->SetTitleOffset(0.1);
    h_Chi2NDFvsX_pos_2s->Draw("p"); 

    sprintf (buffer,"MeanDeltaKvs%sTProfile.pdf",xName);
    c2BX->SaveAs(buffer);

    //--
    TCanvas* c2X = new TCanvas("c2X","c2X",600,900);
    c2X->SetFillColor(kWhite);  
    c2X->Divide(1,4);

    TPad* c2X_1up = (TPad*) c2X->GetListOfPrimitives()->FindObject("c2X_1");
    TPad* c2X_1dw = (TPad*) c2X->GetListOfPrimitives()->FindObject("c2X_2");
    TPad* c2X_2up = (TPad*) c2X->GetListOfPrimitives()->FindObject("c2X_3");
    TPad* c2X_2dw = (TPad*) c2X->GetListOfPrimitives()->FindObject("c2X_4");
    
    // set pad size
    c2X_1up->SetPad(0., 0.5+0.5*(1 - up_height), 1., 0.5+0.5);
    c2X_1dw->SetPad(0., 0.5                    , 1., 0.5+0.5*dw_height);
    c2X_1up->SetFrameFillColor(0);
    c2X_1up->SetFillColor(0);
    c2X_1dw->SetFillColor(0);
    c2X_1dw->SetFrameFillColor(0);
  
    // set top margin 0 for bottom figure
    c2X_1dw->SetTopMargin(0);    

    // draw top figure
    c2X_1up->cd(); 
    hp_ResKvsX_neg[0]->SetStats(0);
    hp_ResKvsX_neg[0]->Draw(); 
    hp_ResKvsX_neg[0]->GetYaxis()->SetRangeUser(0.,0.05);     
    if ( nCor > 1 ) {
      hp_ResKvsX_neg[1]->SetStats(0);
      hp_ResKvsX_neg[1]->Draw("same"); 
    }
    if ( nCor > 2 ) {
      hp_ResKvsX_neg[2]->SetStats(0);
      hp_ResKvsX_neg[2]->Draw("same"); 
    }
    h_SigmaKvsX_neg_2s->Draw("same"); 
    h_SigmaKvsX_neg_3s->Draw("same"); 

    TLegend* leg2 = new TLegend(0.35,0.75,0.75,0.85);  
    leg2->SetBorderSize(1);
    leg2->SetFillColor(kWhite);
    leg2->SetTextFont(42);
    //    leg2->AddEntry(hp_ResKvsX_neg[0],"from MINUIT","PL");
    leg2->AddEntry(hp_ResKvsX_neg[0],"from MuScleFit Y1S+Z Type50 V1 tol=0.005","PL");
    if ( nCor > 1 ) leg2->AddEntry(hp_ResKvsX_neg[1],"from MuScleFit Y1S+Z Type50 V1 n_{TkHits}> 8  tol=0.005","PL");
    if ( nCor > 2 ) leg2->AddEntry(hp_ResKvsX_neg[2],"from MuScleFit Y1S+Z Type50 MINUIT","PL");
    leg2->AddEntry(h_SigmaKvsX_neg_2s,"from MC truth 2RMS","PL");
    leg2->AddEntry(h_SigmaKvsX_neg_3s,"from MC truth 3RMS","PL");
    leg2->Draw("same");

    // draw bottom figure
    c2X_1dw->cd();
    c2X_1dw->SetLogy();
    h_Chi2NDFvsX_neg_3s->GetXaxis()->SetLabelSize(font_size_dw);
    h_Chi2NDFvsX_neg_3s->GetXaxis()->SetTitleSize(font_size_dw);
    h_Chi2NDFvsX_neg_3s->GetYaxis()->SetLabelSize(font_size_dw);
    h_Chi2NDFvsX_neg_3s->GetYaxis()->SetTitleSize(font_size_dw);
    h_Chi2NDFvsX_neg_3s->GetYaxis()->SetTitleOffset(0.4);
    h_Chi2NDFvsX_neg_3s->GetXaxis()->SetTitleOffset(0.1);
    h_Chi2NDFvsX_neg_3s->Draw("p"); 
    h_Chi2NDFvsX_neg_2s->Draw("pSAME"); 

    // set pad size
    c2X_2up->SetPad(0., 0.5*(1 - up_height), 1., 0.5);
    c2X_2dw->SetPad(0., 0.                 , 1., 0.5*dw_height);
    c2X_2up->SetFrameFillColor(0);
    c2X_2up->SetFillColor(0);
    c2X_2dw->SetFillColor(0);
    c2X_2dw->SetFrameFillColor(0);
  
    // set top margin 0 for bottom figure
    c2X_2dw->SetTopMargin(0);    

    // draw top figure
    c2X_2up->cd(); 
    hp_ResKvsX_pos[0]->SetStats(0);
    hp_ResKvsX_pos[0]->Draw(); 
    hp_ResKvsX_pos[0]->GetYaxis()->SetRangeUser(0.,0.05);     
    if ( nCor > 1 ) {
      hp_ResKvsX_pos[1]->SetStats(0);
      hp_ResKvsX_pos[1]->Draw("same"); 
    }
    if ( nCor > 2 ) {
      hp_ResKvsX_pos[2]->SetStats(0);
      hp_ResKvsX_pos[2]->Draw("same"); 
    }
    h_SigmaKvsX_pos_2s->Draw("same"); 
    h_SigmaKvsX_pos_3s->Draw("same"); 

    // draw bottom figure
    c2X_2dw->cd();
    c2X_2dw->SetLogy();
    h_Chi2NDFvsX_pos_3s->GetXaxis()->SetLabelSize(font_size_dw);
    h_Chi2NDFvsX_pos_3s->GetXaxis()->SetTitleSize(font_size_dw);
    h_Chi2NDFvsX_pos_3s->GetYaxis()->SetLabelSize(font_size_dw);
    h_Chi2NDFvsX_pos_3s->GetYaxis()->SetTitleSize(font_size_dw);
    h_Chi2NDFvsX_pos_3s->GetYaxis()->SetTitleOffset(0.4);
    h_Chi2NDFvsX_pos_3s->GetXaxis()->SetTitleOffset(0.1);
    h_Chi2NDFvsX_pos_3s->Draw("p"); 
    h_Chi2NDFvsX_pos_2s->Draw("pSAME"); 

    sprintf (buffer,"ResKvs%sTProfile.pdf",xName);
    c2X->SaveAs(buffer);

    //------

    TCanvas* c2XRatio = new TCanvas("c2XRatio","c2XRatio",600,900);
    c2XRatio->SetFillColor(kWhite);  
    c2XRatio->Divide(1,4);

    TPad* c2XRatio_1up = (TPad*) c2XRatio->GetListOfPrimitives()->FindObject("c2XRatio_1");
    TPad* c2XRatio_1dw = (TPad*) c2XRatio->GetListOfPrimitives()->FindObject("c2XRatio_2");
    TPad* c2XRatio_2up = (TPad*) c2XRatio->GetListOfPrimitives()->FindObject("c2XRatio_3");
    TPad* c2XRatio_2dw = (TPad*) c2XRatio->GetListOfPrimitives()->FindObject("c2XRatio_4");
    
    // set pad size
    c2XRatio_1up->SetPad(0., 0.5+0.5*(1 - up_height), 1., 0.5+0.5);
    c2XRatio_1dw->SetPad(0., 0.5                    , 1., 0.5+0.5*dw_height);
    c2XRatio_1up->SetFrameFillColor(0);
    c2XRatio_1up->SetFillColor(0);
    c2XRatio_1dw->SetFillColor(0);
    c2XRatio_1dw->SetFrameFillColor(0);
  
    // set top margin 0 for bottom figure
    c2XRatio_1dw->SetTopMargin(0);    

    // draw top figure
    c2XRatio_1up->cd(); 
    hp_ResKvsX_neg[0]->SetStats(0);
    hp_ResKvsX_neg[0]->Draw(); 
    hp_ResKvsX_neg[0]->GetYaxis()->SetRangeUser(0.,0.05);     
    if ( nCor > 1 ) {
      hp_ResKvsX_neg[1]->SetStats(0);
      hp_ResKvsX_neg[1]->Draw("same"); 
    }
    if ( nCor > 2 ) {
      hp_ResKvsX_neg[2]->SetStats(0);
      hp_ResKvsX_neg[2]->Draw("same"); 
    }
    h_SigmaKvsX_neg_2s->Draw("same"); 
    h_SigmaKvsX_neg_3s->Draw("same"); 

    leg->Draw("same");
  
    // draw bottom figure
    c2XRatio_1dw->cd();
    c2XRatio_1dw->SetGrid();
    h_RatiovsX_neg_2s->GetXaxis()->SetLabelSize(font_size_dw);
    h_RatiovsX_neg_2s->GetXaxis()->SetTitleSize(font_size_dw);
    h_RatiovsX_neg_2s->GetYaxis()->SetLabelSize(font_size_dw);
    h_RatiovsX_neg_2s->GetYaxis()->SetTitleSize(font_size_dw);
    h_RatiovsX_neg_2s->GetYaxis()->SetTitleOffset(0.4);
    h_RatiovsX_neg_2s->GetXaxis()->SetTitleOffset(0.1);
    h_RatiovsX_neg_2s->GetYaxis()->SetRangeUser(0.80,1.20);
    h_RatiovsX_neg_2s->Draw("p"); 

    // set pad size
    c2XRatio_2up->SetPad(0., 0.5*(1 - up_height), 1., 0.5);
    c2XRatio_2dw->SetPad(0., 0.                 , 1., 0.5*dw_height);
    c2XRatio_2up->SetFrameFillColor(0);
    c2XRatio_2up->SetFillColor(0);
    c2XRatio_2dw->SetFillColor(0);
    c2XRatio_2dw->SetFrameFillColor(0);
  
    // set top margin 0 for bottom figure
    c2XRatio_2dw->SetTopMargin(0);    

    // draw top figure
    c2XRatio_2up->cd(); 
    hp_ResKvsX_pos[0]->SetStats(0);
    hp_ResKvsX_pos[0]->Draw(); 
    hp_ResKvsX_pos[0]->GetYaxis()->SetRangeUser(0.,0.05);     
    if ( nCor > 1 ) {
      hp_ResKvsX_pos[1]->SetStats(0);
      hp_ResKvsX_pos[1]->Draw("same"); 
    }
    if ( nCor > 2 ) {
      hp_ResKvsX_pos[2]->SetStats(0);
      hp_ResKvsX_pos[2]->Draw("same"); 
    }
    h_SigmaKvsX_pos_2s->Draw("same"); 
    h_SigmaKvsX_pos_3s->Draw("same"); 

    // draw bottom figure
    c2XRatio_2dw->cd();
    c2XRatio_2dw->SetGrid();
    h_RatiovsX_pos_2s->GetXaxis()->SetLabelSize(font_size_dw);
    h_RatiovsX_pos_2s->GetXaxis()->SetTitleSize(font_size_dw);
    h_RatiovsX_pos_2s->GetYaxis()->SetLabelSize(font_size_dw);
    h_RatiovsX_pos_2s->GetYaxis()->SetTitleSize(font_size_dw);
    h_RatiovsX_pos_2s->GetYaxis()->SetTitleOffset(0.4);
    h_RatiovsX_pos_2s->GetXaxis()->SetTitleOffset(0.1);
    h_RatiovsX_pos_2s->GetYaxis()->SetRangeUser(0.80,1.20);
    h_RatiovsX_pos_2s->Draw("p"); 

    sprintf (buffer,"ResKvs%sTProfileV2.pdf",xName);
    c2XRatio->SaveAs(buffer);

}


int main(int argc, char *argv[]){

  // Parse arguments
  TString inputTree = argv[1];
//   // the 2nd argument is the center of the abs(eta) bin for the resolution vs pT studies
//   // width of the eta bin is +-0.05
//   double eta; sscanf(argv[2],"%lf",&eta);

//   double etaMin = -0.05;   //eta-0.05;
//   double etaMax =  2.45;   //eta+0.05;

//   //  double etaMin =  1.05;   //eta-0.05;
//   //  double etaMax =  1.55;   //eta+0.05;

  const int nCor(1);

  TFile *fout = TFile::Open("TH2.root","RECREATE");

  //---------------- STUDY OF RESOLUTION VS eta
  HistosManager hmEta("Eta","#eta",48,-2.4,0.1,nCor);

  //---------------- STUDY OF RESOLUTION VS pT
  HistosManager hmPt("pT","pT",24,5.0,3.0,nCor);

  //---------------- STUDY OF RESOLUTION VS phi
  HistosManager hmPhi("phi","#phi",42,-3.15,0.15,nCor);


 //-------------------
  
  //Corrector objects
  MuScleFitCorrector* corrector_[nCor];
  //corrector_[0] = new MuScleFitCorrector("../MuScleFitCorrector_v4_2/MuScleFit_2012_MC_53XIDEAL_smearReReco.txt");
  corrector_[0]   = new MuScleFitCorrector("../MuScleFitCorrector_v4_2/MuScleFit_2012_MC_53X_smearReReco.txt");
  // corrector_[0]   = new MuScleFitCorrector("../MuScleFitCorrector_v4_2/MuScleFit_2011_MC_44X.txt");

  //  corrector_[0] = new MuScleFitCorrector("../MuScleFitCorrector_v4_2/ResolutionStudy/MuScleFit_2012_MC_53X_Type50V1_Y1SandZ_TOL005.txt");
  //  if ( nCor>0 ) corrector_[1]   = new MuScleFitCorrector("../MuScleFitCorrector_v4_2/ResolutionStudy/MuScleFit_2012_MC_53X_Type50V0_Y1S.txt");
  //  if ( nCor>1 ) corrector_[1]   = new MuScleFitCorrector("../MuScleFitCorrector_v4_2/ResolutionStudy/MuScleFit_2012_MC_53X_Type50Minuit_Y1SandZ_ptErrLT03.txt");
  //  if ( nCor>1 ) corrector_[1]   = new MuScleFitCorrector("../MuScleFitCorrector_v4_2/ResolutionStudy/MuScleFit_2012_MC_53X_Type50V1_Y1sandZ_nTkHitsGT8_TOL005.txt");
  // input tree containing Generated events and Reco events  
  cout<<"Opening the file ..."<<endl;
  
  TFile *fin = TFile::Open(inputTree,"READ");
  fin->cd();

  cout<<"Getting the tree ..."<<endl;
  TTree *treeIN =(TTree*)fin->Get("T"); //input tree named T
  
  // MuonPairs
  GenMuonPair *mupairGenIN_= 0;
  MuonPair *mupairIN_= 0;  

  TLorentzVector* muNeg=0;
  TLorentzVector* muPos=0;
  TLorentzVector* mumu=0;

  if ( treeIN!=0 ) {              
    
    treeIN->SetBranchAddress("genEvent",    &mupairGenIN_); //select generated event
    treeIN->SetBranchAddress("event",       &mupairIN_);    //select generated event    
    
    int nentries=treeIN->GetEntries();
    cout<<"Looping over tree entries ...";
    for(int entry=0; entry<nentries;  entry++){ 
      //for(int entry=0; entry<5;  entry++){ 
      treeIN->GetEntry(entry);
      if (entry%50000==0)cout<<"Reading muon pair n. "<<entry<<endl;

      // cout<<"Pt1 = "<<mupairIN_->mu1.fP4.Pt()<<"; Pt2 = "<<mupairIN_->mu2.fP4.Pt()<<endl;

      // fetch muons before correction from the input tree
      muNeg = new TLorentzVector(mupairIN_->mu1.fP4.Px(), mupairIN_->mu1.fP4.Py(), mupairIN_->mu1.fP4.Pz(), mupairIN_->mu1.fP4.E());
      muPos = new TLorentzVector(mupairIN_->mu2.fP4.Px(), mupairIN_->mu2.fP4.Py(), mupairIN_->mu2.fP4.Pz(), mupairIN_->mu2.fP4.E());

      mumu = new TLorentzVector((*muNeg)+(*muPos));
      hmEta.monitor(muNeg->Eta(),muPos->Eta(),mumu->M());
      hmPt.monitor(muNeg->Pt(),muPos->Pt(),mumu->M());
      hmPhi.monitor(muNeg->Phi(),muPos->Phi(),mumu->M());

      // comment next two lines in case muons have been alread corrected
      corrector_[0]->applyPtCorrection(*muNeg,-1); 
      corrector_[0]->applyPtCorrection(*muPos,+1);

      // Get pts and etas
      double pt1_reco = muNeg->Pt(); double eta1_reco = muNeg->Eta(); double phi1_reco = muNeg->Phi();
      double pt2_reco = muPos->Pt(); double eta2_reco = muPos->Eta(); double phi2_reco = muPos->Phi();
      double pt1_gen = mupairGenIN_->mu1.fP4.Pt(); double eta1_gen = mupairGenIN_->mu1.fP4.Eta();
      double pt2_gen = mupairGenIN_->mu2.fP4.Pt(); double eta2_gen = mupairGenIN_->mu2.fP4.Eta();
      
      if ( muNeg != 0  ) delete muNeg; 
      if ( muPos != 0  ) delete muPos; 
      if ( mumu !=0  ) delete mumu; 

      // Get curvatures
      double k1_reco = -1/pt1_reco;
      double k2_reco =  1/pt2_reco;      
      double k1_gen = -1/pt1_gen;
      double k2_gen =  1/pt2_gen;      

      // pT resolution (from parametrization) for the current  muon pair
      double sigmaRelPt1[nCor];
      double sigmaRelPt2[nCor]; 
      double sigmaPt1[nCor]; 
      double sigmaPt2[nCor]; 

      
      for ( int iCor=0; iCor<nCor; iCor++ ){
	// Resolution function
	resolutionFunctionBase<double *> * resolutionFunction = corrector_[iCor]->getResolFunction();

	vector<double> resolPar = corrector_[iCor]->getResolMCParVec();
	// cout<<"Size = "<<resolPar.size()<<endl;
	vector<double>::const_iterator resolMCParIt = resolPar.begin();
	double * resolParArray;
	const int arraySize = resolPar.size();
	resolParArray = new double[arraySize];
	for ( int iPar=0; iPar<arraySize; ++iPar) {
	  double parameter = *resolMCParIt;
	  resolParArray[iPar] = parameter;
	  ++resolMCParIt;
	  // if (entry==0) cout<<"Parameter = "<<parameter<<endl;
	}
	// pT resolution (from parametrization) for the current  muon pair
	sigmaRelPt1[iCor] = resolutionFunction->sigmaPt(pt1_reco, eta1_reco, resolParArray);
	sigmaRelPt2[iCor] = resolutionFunction->sigmaPt(pt2_reco, eta2_reco, resolParArray);
	sigmaPt1[iCor] = k1_reco*resolutionFunction->sigmaPt(pt1_reco, eta1_reco, resolParArray);
	sigmaPt2[iCor] = k2_reco*resolutionFunction->sigmaPt(pt2_reco, eta2_reco, resolParArray);

      }
      
      hmEta.analyze(eta1_reco, k1_reco, k1_gen, eta2_reco,  k2_reco, k2_gen, sigmaRelPt1, sigmaRelPt2);
      hmPt.analyze(pt1_reco, k1_reco, k1_gen, pt2_reco, k2_reco, k2_gen, sigmaRelPt1, sigmaRelPt2);
      hmPhi.analyze(phi1_reco, k1_reco, k1_gen, phi2_reco, k2_reco, k2_gen, sigmaRelPt1, sigmaRelPt2);
      	
    }//loop over tree entries

    hmEta.draw("Eta");
    hmPt.draw("pT");   
    hmPhi.draw("Phi");   
    
  }//check if tree has any entry

  cout<<"Closing file ..."<<endl;
  //close & write 
  fin->Close();
  if ( fin!=0 ) delete fin;


  fout->cd();
  /* TODO #4  h2_SigmaKvsEtaPt_all->Write(); */
  fout->Close();

  return 0;
  
} //main


TF1* drawGFit(TH1 * h1, double nsigmasL, double nsigmasR, double fmin, double fmax, TPad * pad){

  //gPad->SetGrid(1,1);
  //gStyle->SetGridColor(15);
  pad->cd();
  pad->SetLogy();
  double xmin = h1->GetXaxis()->GetXmin();
  double xmax = h1->GetXaxis()->GetXmax();
  h1->GetXaxis()->SetRangeUser(fmin,fmax);

   
  //Start with a fit on +-1 RMS
  double minfit = max(h1->GetMean() - h1->GetRMS(),xmin);
  double maxfit = min(h1->GetMean() + h1->GetRMS(),xmax);
  static int i = 0;
  TString nameF1 = TString("g") + (Long_t)i;
  i++;
  TF1* g1 = new TF1(nameF1,"gaus",minfit,maxfit);

  if ( nsigmasL == 2 ) {
    g1->SetLineColor(kRed);
  }  else { 
    g1->SetLineColor(kGreen);
  }
  g1->SetLineWidth(2);
  h1->Fit(g1,"RQ");
  
  //Now fit with N sigma of the previous fit
  minfit = max(g1->GetParameter("Mean") - nsigmasL*g1->GetParameter("Sigma"),xmin);
  maxfit = min(g1->GetParameter("Mean") + nsigmasR*g1->GetParameter("Sigma"),xmax);
  g1->SetRange(minfit,maxfit);
  h1->Fit(g1,"RQ");

  //One more iteration
  minfit = max(g1->GetParameter("Mean") - nsigmasL*g1->GetParameter("Sigma"),xmin);
  maxfit = min(g1->GetParameter("Mean") + nsigmasR*g1->GetParameter("Sigma"),xmax);
  g1->SetRange(minfit,maxfit);
  h1->Fit(g1,"RQ");

  /*
  TF1* g2 = (TF1*)g1->Clone();
  g2->SetLineStyle(2);
  g2->SetTitle("g2");
  g2->SetRange(min,max);
  //  g2->Draw("same");
  */

  //  gPad->Draw();
  return g1;
}



TF1* drawResGausFit(TH1 * h1, TPad * pad){

  pad->cd();
   
  static int i = 0;
  TString nameF1 = TString("r") + (Long_t)i;
  i++;
   TF1* g1 = new TF1(nameF1,"sqrt([0]*[0]*x*x+[1]*[1])",3.,50.);
  //TF1* g1 = new TF1(nameF1,"[0]*x+[1]",3.,50.);
  g1->SetParameters(0.01,0.0003);
  g1->SetLineColor(kMagenta);
  g1->SetLineWidth(2);
  h1->Draw();
  h1->Fit(g1,"RQ0");
  h1->GetYaxis()->SetRangeUser(0.,0.05);     
  
  return g1;
}





