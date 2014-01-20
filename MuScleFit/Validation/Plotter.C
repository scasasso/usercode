// Plain ROOT stuff
#include "TFile.h"
#include "TCanvas.h"
#include "TGraphErrors.h"
#include "TMultiGraph.h"
#include "TColor.h"
#include "TStyle.h"
#include "TAxis.h"
#include "TLine.h"
#include "TLegend.h"
#include "TPaveText.h"
#include "TROOT.h"


// Plain C++ stuff
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

Double_t computeErrorScale(Double_t, Double_t, Double_t);

Double_t computeErrorResol(Double_t, Double_t, Double_t, Double_t);

Double_t computeErrorPdg(Double_t, Double_t);

void Plotter(const TString& inputFile = "TGEs.root", const TString& append = "_raw"){

  gROOT->ProcessLine(".L tdrstyle.C"); 
  gROOT->ProcessLine("setTDRStyle()");

  // PDG masses
  const Double_t mass_Z = 91.188;
  const Double_t mass_Y = 9.460;
  const Double_t mass_JPsi = 3.097;

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

  // Legend labels 
  const TString legLabels_Z_pt[nEtaBinCoa_Z] = {"Z |#eta| 0.0-2.4"};
  const TString legLabels_Z_eta[nPtBinCoa_Z] = {"Z p_{T} 20-45 GeV", "Z p_{T} 45-90 GeV"};
  const TString legLabels_Y_pt[nEtaBinCoa_Y] = {"Y |#eta| 0.0-0.7", "Y |#eta| 0.7-2.4"};
  const TString legLabels_Y_eta[nPtBinCoa_Y] = {"Y p_{T} 10-20 GeV"};
  const TString legLabels_JPsi_pt[nEtaBinCoa_JPsi] = {"J/#Psi |#eta| 0.0-0.6", "J/#Psi |#eta| 0.6-1.2", "J/#Psi |#eta| 1.2-2.0"};
  const TString legLabels_JPsi_eta[nPtBinCoa_JPsi] = {"J/#Psi p_{T} 5-7 GeV", "J/#Psi p_{T} 7-10 GeV", "J/#Psi p_{T} 10-15 GeV"};

  
  TFile* fOpen = TFile::Open(inputFile,"READ");

  // Laziness ;)
  typedef TGraphErrors tge;
  typedef TMultiGraph mg;

  //Define TGraphErrors
  tge* tge_scale_pt_Z_data[nEtaBinCoa_Z]; tge* tge_scale_eta_Z_data[nPtBinCoa_Z]; tge* tge_resol_pt_Z_data[nEtaBinCoa_Z]; tge* tge_resol_eta_Z_data[nPtBinCoa_Z];   
  tge* tge_scale_pt_Z_mc[nEtaBinCoa_Z]; tge* tge_scale_eta_Z_mc[nPtBinCoa_Z]; tge* tge_resol_pt_Z_mc[nEtaBinCoa_Z]; tge* tge_resol_eta_Z_mc[nPtBinCoa_Z];   
  tge* tge_scale_pt_Y_data[nEtaBinCoa_Y]; tge* tge_scale_eta_Y_data[nPtBinCoa_Y]; tge* tge_resol_pt_Y_data[nEtaBinCoa_Y]; tge* tge_resol_eta_Y_data[nPtBinCoa_Y];   
  tge* tge_scale_pt_Y_mc[nEtaBinCoa_Y]; tge* tge_scale_eta_Y_mc[nPtBinCoa_Y]; tge* tge_resol_pt_Y_mc[nEtaBinCoa_Y]; tge* tge_resol_eta_Y_mc[nPtBinCoa_Y];   
  tge* tge_scale_pt_JPsi_data[nEtaBinCoa_JPsi]; tge* tge_scale_eta_JPsi_data[nPtBinCoa_JPsi]; tge* tge_resol_pt_JPsi_data[nEtaBinCoa_JPsi]; tge* tge_resol_eta_JPsi_data[nPtBinCoa_JPsi];   
  tge* tge_scale_pt_JPsi_mc[nEtaBinCoa_JPsi]; tge* tge_scale_eta_JPsi_mc[nPtBinCoa_JPsi]; tge* tge_resol_pt_JPsi_mc[nEtaBinCoa_JPsi]; tge* tge_resol_eta_JPsi_mc[nPtBinCoa_JPsi];   

  // Define arrays
  Double_t* mass_Z_pt_data[nEtaBinCoa_Z] = {0}; Double_t* mass_Z_pt_mc[nEtaBinCoa_Z] = {0};     Double_t* xPt_Z_pt = {0};
  Double_t* mass_Z_eta_data[nPtBinCoa_Z] = {0}; Double_t* mass_Z_eta_mc[nPtBinCoa_Z] = {0};   Double_t* xEta_Z_eta = {0};
  Double_t* sigma_Z_pt_data[nEtaBinCoa_Z] = {0}; Double_t* sigma_Z_pt_mc[nEtaBinCoa_Z] = {0};   
  Double_t* sigma_Z_eta_data[nPtBinCoa_Z] = {0}; Double_t* sigma_Z_eta_mc[nPtBinCoa_Z] = {0}; 
  Double_t* mass_Z_pt_data_Err[nEtaBinCoa_Z] = {0}; Double_t* mass_Z_pt_mc_Err[nEtaBinCoa_Z] = {0};    Double_t* xPt_Z_pt_Err = {0};	 
  Double_t* mass_Z_eta_data_Err[nPtBinCoa_Z] = {0}; Double_t* mass_Z_eta_mc_Err[nPtBinCoa_Z] = {0};  Double_t* xEta_Z_eta_Err = {0};
  Double_t* sigma_Z_pt_data_Err[nEtaBinCoa_Z] = {0}; Double_t* sigma_Z_pt_mc_Err[nEtaBinCoa_Z] = {0};  
  Double_t* sigma_Z_eta_data_Err[nPtBinCoa_Z] = {0}; Double_t* sigma_Z_eta_mc_Err[nPtBinCoa_Z] = {0};
  Double_t* mass_Y_pt_data[nEtaBinCoa_Y] = {0}; Double_t* mass_Y_pt_mc[nEtaBinCoa_Y] = {0};     Double_t* xPt_Y_pt = {0};
  Double_t* mass_Y_eta_data[nPtBinCoa_Y] = {0}; Double_t* mass_Y_eta_mc[nPtBinCoa_Y] = {0};   Double_t* xEta_Y_eta = {0};
  Double_t* sigma_Y_pt_data[nEtaBinCoa_Y] = {0}; Double_t* sigma_Y_pt_mc[nEtaBinCoa_Y] = {0};   
  Double_t* sigma_Y_eta_data[nPtBinCoa_Y] = {0}; Double_t* sigma_Y_eta_mc[nPtBinCoa_Y] = {0}; 
  Double_t* mass_Y_pt_data_Err[nEtaBinCoa_Y] = {0}; Double_t* mass_Y_pt_mc_Err[nEtaBinCoa_Y] = {0};    Double_t* xPt_Y_pt_Err = {0};	 
  Double_t* mass_Y_eta_data_Err[nPtBinCoa_Y] = {0}; Double_t* mass_Y_eta_mc_Err[nPtBinCoa_Y] = {0};  Double_t* xEta_Y_eta_Err = {0};
  Double_t* sigma_Y_pt_data_Err[nEtaBinCoa_Y] = {0}; Double_t* sigma_Y_pt_mc_Err[nEtaBinCoa_Y] = {0};  
  Double_t* sigma_Y_eta_data_Err[nPtBinCoa_Y] = {0}; Double_t* sigma_Y_eta_mc_Err[nPtBinCoa_Y] = {0};
  Double_t* mass_JPsi_pt_data[nEtaBinCoa_JPsi] = {0}; Double_t* mass_JPsi_pt_mc[nEtaBinCoa_JPsi] = {0}; Double_t* xPt_JPsi_pt = {0};
  Double_t* mass_JPsi_eta_data[nPtBinCoa_JPsi] = {0}; Double_t* mass_JPsi_eta_mc[nPtBinCoa_JPsi] = {0}; Double_t* xEta_JPsi_eta = {0};
  Double_t* sigma_JPsi_pt_data[nEtaBinCoa_JPsi] = {0}; Double_t* sigma_JPsi_pt_mc[nEtaBinCoa_JPsi] = {0};   
  Double_t* sigma_JPsi_eta_data[nPtBinCoa_JPsi] = {0}; Double_t* sigma_JPsi_eta_mc[nPtBinCoa_JPsi] = {0}; 
  Double_t* mass_JPsi_pt_data_Err[nEtaBinCoa_JPsi] = {0}; Double_t* mass_JPsi_pt_mc_Err[nEtaBinCoa_JPsi] = {0};    Double_t* xPt_JPsi_pt_Err = {0};	 
  Double_t* mass_JPsi_eta_data_Err[nPtBinCoa_JPsi] = {0}; Double_t* mass_JPsi_eta_mc_Err[nPtBinCoa_JPsi] = {0};  Double_t* xEta_JPsi_eta_Err = {0};
  Double_t* sigma_JPsi_pt_data_Err[nEtaBinCoa_JPsi] = {0}; Double_t* sigma_JPsi_pt_mc_Err[nEtaBinCoa_JPsi] = {0};  
  Double_t* sigma_JPsi_eta_data_Err[nPtBinCoa_JPsi] = {0}; Double_t* sigma_JPsi_eta_mc_Err[nPtBinCoa_JPsi] = {0};


  // Define bools 
  Bool_t plotZ = (tge*)fOpen->Get("ScaleVsPt_Z_data_0") != 0;
  Bool_t plotY = (tge*)fOpen->Get("ScaleVsPt_Y_data_0") != 0;
  Bool_t plotJPsi = (tge*)fOpen->Get("ScaleVsPt_JPsi_data_0") != 0;

  if (plotZ){
    // Initialize tge scale Z
    for (UInt_t i=0; i<nEtaBinCoa_Z; ++i){
      ostringstream convert; convert << i;
      TString appendString(convert.str());
      tge_scale_pt_Z_data[i] = (tge*)fOpen->Get("ScaleVsPt_Z_data_"+appendString);
      tge_scale_pt_Z_mc[i]   = (tge*)fOpen->Get("ScaleVsPt_Z_mc_"+appendString);
      mass_Z_pt_data[i] = tge_scale_pt_Z_data[i]->GetY();
      mass_Z_pt_mc[i] = tge_scale_pt_Z_mc[i]->GetY();
      mass_Z_pt_data_Err[i] = tge_scale_pt_Z_data[i]->GetEY();
      mass_Z_pt_mc_Err[i] = tge_scale_pt_Z_mc[i]->GetEY();
      xPt_Z_pt = tge_scale_pt_Z_data[i]->GetX(); //same also for MC and for resolution
      xPt_Z_pt_Err = tge_scale_pt_Z_data[i]->GetEX(); //same also for MC and for resolution
    }


    for (UInt_t i=0; i<nPtBinCoa_Z; ++i){
      ostringstream convert; convert << i;
      TString appendString(convert.str());
      tge_scale_eta_Z_data[i] = (tge*)fOpen->Get("ScaleVsEta_Z_data_"+appendString);
      tge_scale_eta_Z_mc[i]   = (tge*)fOpen->Get("ScaleVsEta_Z_mc_"+appendString);
      mass_Z_eta_data[i] = tge_scale_eta_Z_data[i]->GetY();
      mass_Z_eta_mc[i] = tge_scale_eta_Z_mc[i]->GetY();
      mass_Z_eta_data_Err[i] = tge_scale_eta_Z_data[i]->GetEY();
      mass_Z_eta_mc_Err[i] = tge_scale_eta_Z_mc[i]->GetEY();
      xEta_Z_eta = tge_scale_eta_Z_data[i]->GetX(); //same also for MC and for resolution
      xEta_Z_eta_Err = tge_scale_eta_Z_data[i]->GetEX(); //same also for MC and for resolution
    }

    // Initialize tge resol Z
    for (UInt_t i=0; i<nEtaBinCoa_Z; ++i){
      ostringstream convert; convert << i;
      TString appendString(convert.str());
      tge_resol_pt_Z_data[i] = (tge*)fOpen->Get("ResolVsPt_Z_data_"+appendString);
      tge_resol_pt_Z_mc[i]   = (tge*)fOpen->Get("ResolVsPt_Z_mc_"+appendString);
      sigma_Z_pt_data[i] = tge_resol_pt_Z_data[i]->GetY();
      sigma_Z_pt_mc[i] = tge_resol_pt_Z_mc[i]->GetY();
      sigma_Z_pt_data_Err[i] = tge_resol_pt_Z_data[i]->GetEY();
      sigma_Z_pt_mc_Err[i] = tge_resol_pt_Z_mc[i]->GetEY();
    }

    for (UInt_t i=0; i<nPtBinCoa_Z; ++i){
      ostringstream convert; convert << i;
      TString appendString(convert.str());
      tge_resol_eta_Z_data[i] = (tge*)fOpen->Get("ResolVsEta_Z_data_"+appendString);
      tge_resol_eta_Z_mc[i]   = (tge*)fOpen->Get("ResolVsEta_Z_mc_"+appendString);
      sigma_Z_eta_data[i] = tge_resol_eta_Z_data[i]->GetY();
      sigma_Z_eta_mc[i] = tge_resol_eta_Z_mc[i]->GetY();
      sigma_Z_eta_data_Err[i] = tge_resol_eta_Z_data[i]->GetEY();
      sigma_Z_eta_mc_Err[i] = tge_resol_eta_Z_mc[i]->GetEY();
    }
  }// plot Z

  // Initialize tge scale Y
  if (plotY){
    for (UInt_t i=0; i<nEtaBinCoa_Y; ++i){
      ostringstream convert; convert << i;
      TString appendString(convert.str());
      tge_scale_pt_Y_data[i] = (tge*)fOpen->Get("ScaleVsPt_Y_data_"+appendString);
      tge_scale_pt_Y_mc[i]   = (tge*)fOpen->Get("ScaleVsPt_Y_mc_"+appendString);
      mass_Y_pt_data[i] = tge_scale_pt_Y_data[i]->GetY();
      mass_Y_pt_mc[i] = tge_scale_pt_Y_mc[i]->GetY();
      mass_Y_pt_data_Err[i] = tge_scale_pt_Y_data[i]->GetEY();
      mass_Y_pt_mc_Err[i] = tge_scale_pt_Y_mc[i]->GetEY();
      xPt_Y_pt = tge_scale_pt_Y_data[i]->GetX(); //same also for MC and for resolution
      xPt_Y_pt_Err = tge_scale_pt_Y_data[i]->GetEX(); //same also for MC and for resolution
    }

    for (UInt_t i=0; i<nPtBinCoa_Y; ++i){
      ostringstream convert; convert << i;
      TString appendString(convert.str());
      tge_scale_eta_Y_data[i] = (tge*)fOpen->Get("ScaleVsEta_Y_data_"+appendString);
      tge_scale_eta_Y_mc[i]   = (tge*)fOpen->Get("ScaleVsEta_Y_mc_"+appendString);
      mass_Y_eta_data[i] = tge_scale_eta_Y_data[i]->GetY();
      mass_Y_eta_mc[i] = tge_scale_eta_Y_mc[i]->GetY();
      mass_Y_eta_data_Err[i] = tge_scale_eta_Y_data[i]->GetEY();
      mass_Y_eta_mc_Err[i] = tge_scale_eta_Y_mc[i]->GetEY();
      xEta_Y_eta = tge_scale_eta_Y_data[i]->GetX(); //same also for MC and for resolution
      xEta_Y_eta_Err = tge_scale_eta_Y_data[i]->GetEX(); //same also for MC and for resolution
    }

    // Initialize tge resol Y
    for (UInt_t i=0; i<nEtaBinCoa_Y; ++i){
      ostringstream convert; convert << i;
      TString appendString(convert.str());
      tge_resol_pt_Y_data[i] = (tge*)fOpen->Get("ResolVsPt_Y_data_"+appendString);
      tge_resol_pt_Y_mc[i]   = (tge*)fOpen->Get("ResolVsPt_Y_mc_"+appendString);
      sigma_Y_pt_data[i] = tge_resol_pt_Y_data[i]->GetY();
      sigma_Y_pt_mc[i] = tge_resol_pt_Y_mc[i]->GetY();
      sigma_Y_pt_data_Err[i] = tge_resol_pt_Y_data[i]->GetEY();
      sigma_Y_pt_mc_Err[i] = tge_resol_pt_Y_mc[i]->GetEY();
    }

    for (UInt_t i=0; i<nPtBinCoa_Y; ++i){
      ostringstream convert; convert << i;
      TString appendString(convert.str());
      tge_resol_eta_Y_data[i] = (tge*)fOpen->Get("ResolVsEta_Y_data_"+appendString);
      tge_resol_eta_Y_mc[i]   = (tge*)fOpen->Get("ResolVsEta_Y_mc_"+appendString);
      sigma_Y_eta_data[i] = tge_resol_eta_Y_data[i]->GetY();
      sigma_Y_eta_mc[i] = tge_resol_eta_Y_mc[i]->GetY();
      sigma_Y_eta_data_Err[i] = tge_resol_eta_Y_data[i]->GetEY();
      sigma_Y_eta_mc_Err[i] = tge_resol_eta_Y_mc[i]->GetEY();
    }
  }// plot Y

  // Initialize tge scale JPsi
  if (plotJPsi){
    for (UInt_t i=0; i<nEtaBinCoa_JPsi; ++i){
      ostringstream convert; convert << i;
      TString appendString(convert.str());
      tge_scale_pt_JPsi_data[i] = (tge*)fOpen->Get("ScaleVsPt_JPsi_data_"+appendString);
      tge_scale_pt_JPsi_mc[i]   = (tge*)fOpen->Get("ScaleVsPt_JPsi_mc_"+appendString);
      mass_JPsi_pt_data[i] = tge_scale_pt_JPsi_data[i]->GetY();
      mass_JPsi_pt_mc[i] = tge_scale_pt_JPsi_mc[i]->GetY();
      mass_JPsi_pt_data_Err[i] = tge_scale_pt_JPsi_data[i]->GetEY();
      mass_JPsi_pt_mc_Err[i] = tge_scale_pt_JPsi_mc[i]->GetEY();
      xPt_JPsi_pt = tge_scale_pt_JPsi_data[i]->GetX(); //same also for MC and for resolution
      xPt_JPsi_pt_Err = tge_scale_pt_JPsi_data[i]->GetEX(); //same also for MC and for resolution
    }

    for (UInt_t i=0; i<nPtBinCoa_JPsi; ++i){
      ostringstream convert; convert << i;
      TString appendString(convert.str());
      tge_scale_eta_JPsi_data[i] = (tge*)fOpen->Get("ScaleVsEta_JPsi_data_"+appendString);
      tge_scale_eta_JPsi_mc[i]   = (tge*)fOpen->Get("ScaleVsEta_JPsi_mc_"+appendString);
      mass_JPsi_eta_data[i] = tge_scale_eta_JPsi_data[i]->GetY();
      mass_JPsi_eta_mc[i] = tge_scale_eta_JPsi_mc[i]->GetY();
      mass_JPsi_eta_data_Err[i] = tge_scale_eta_JPsi_data[i]->GetEY();
      mass_JPsi_eta_mc_Err[i] = tge_scale_eta_JPsi_mc[i]->GetEY();
      xEta_JPsi_eta = tge_scale_eta_JPsi_data[i]->GetX(); //same also for MC and for resolution
      xEta_JPsi_eta_Err = tge_scale_eta_JPsi_data[i]->GetEX(); //same also for MC and for resolution
    }

    // Initialize tge resol JPsi
    for (UInt_t i=0; i<nEtaBinCoa_JPsi; ++i){
      ostringstream convert; convert << i;
      TString appendString(convert.str());
      tge_resol_pt_JPsi_data[i] = (tge*)fOpen->Get("ResolVsPt_JPsi_data_"+appendString);
      tge_resol_pt_JPsi_mc[i]   = (tge*)fOpen->Get("ResolVsPt_JPsi_mc_"+appendString);
      sigma_JPsi_pt_data[i] = tge_resol_pt_JPsi_data[i]->GetY();
      sigma_JPsi_pt_mc[i] = tge_resol_pt_JPsi_mc[i]->GetY();
      sigma_JPsi_pt_data_Err[i] = tge_resol_pt_JPsi_data[i]->GetEY();
      sigma_JPsi_pt_mc_Err[i] = tge_resol_pt_JPsi_mc[i]->GetEY();
    }

    for (UInt_t i=0; i<nPtBinCoa_JPsi; ++i){
      ostringstream convert; convert << i;
      TString appendString(convert.str());
      tge_resol_eta_JPsi_data[i] = (tge*)fOpen->Get("ResolVsEta_JPsi_data_"+appendString);
      tge_resol_eta_JPsi_mc[i]   = (tge*)fOpen->Get("ResolVsEta_JPsi_mc_"+appendString);
      sigma_JPsi_eta_data[i] = tge_resol_eta_JPsi_data[i]->GetY();
      sigma_JPsi_eta_mc[i] = tge_resol_eta_JPsi_mc[i]->GetY();
      sigma_JPsi_eta_data_Err[i] = tge_resol_eta_JPsi_data[i]->GetEY();
      sigma_JPsi_eta_mc_Err[i] = tge_resol_eta_JPsi_mc[i]->GetEY();
    }
  } // plot JPsi

  // Define arrays for new TGraphs

  // Data - MC
  Double_t dMass_Z_pt[nEtaBinCoa_Z][nPtBin_Z] = {{0}};          Double_t dMass_Z_pt_Err[nEtaBinCoa_Z][nPtBin_Z] = {{0}}; 	     
  Double_t dMass_Z_eta[nPtBinCoa_Z][nEtaBin_Z] = {{0}}; 	       Double_t dMass_Z_eta_Err[nPtBinCoa_Z][nEtaBin_Z] = {{0}}; 	     
  Double_t dSigma_Z_pt[nEtaBinCoa_Z][nPtBin_Z] = {{0}}; 	       Double_t dSigma_Z_pt_Err[nEtaBinCoa_Z][nPtBin_Z] = {{0}}; 	     
  Double_t dSigma_Z_eta[nPtBinCoa_Z][nEtaBin_Z] = {{0}};        Double_t dSigma_Z_eta_Err[nPtBinCoa_Z][nEtaBin_Z] = {{0}};      
  Double_t dMass_Y_pt[nEtaBinCoa_Y][nPtBin_Y] = {{0}}; 	       Double_t dMass_Y_pt_Err[nEtaBinCoa_Y][nPtBin_Y] = {{0}}; 	     
  Double_t dMass_Y_eta[nPtBinCoa_Y][nEtaBin_Y] = {{0}};	       Double_t dMass_Y_eta_Err[nPtBinCoa_Y][nEtaBin_Y] = {{0}};	     
  Double_t dSigma_Y_pt[nEtaBinCoa_Y][nPtBin_Y] = {{0}}; 	       Double_t dSigma_Y_pt_Err[nEtaBinCoa_Y][nPtBin_Y] = {{0}}; 	     
  Double_t dSigma_Y_eta[nPtBinCoa_Y][nEtaBin_Y] = {{0}};        Double_t dSigma_Y_eta_Err[nPtBinCoa_Y][nEtaBin_Y] = {{0}};      
  Double_t dMass_JPsi_pt[nEtaBinCoa_JPsi][nPtBin_JPsi] = {{0}};    Double_t dMass_JPsi_pt_Err[nEtaBinCoa_JPsi][nPtBin_JPsi] = {{0}};  
  Double_t dMass_JPsi_eta[nPtBinCoa_JPsi][nEtaBin_JPsi] = {{0}};   Double_t dMass_JPsi_eta_Err[nPtBinCoa_JPsi][nEtaBin_JPsi] = {{0}}; 
  Double_t dSigma_JPsi_pt[nEtaBinCoa_JPsi][nPtBin_JPsi] = {{0}};   Double_t dSigma_JPsi_pt_Err[nEtaBinCoa_JPsi][nPtBin_JPsi] = {{0}}; 
  Double_t dSigma_JPsi_eta[nPtBinCoa_JPsi][nEtaBin_JPsi] = {{0}};  Double_t dSigma_JPsi_eta_Err[nPtBinCoa_JPsi][nEtaBin_JPsi] = {{0}};

  // Data/MC - PDG
  Double_t dMassPdg_data_Z_pt[nEtaBinCoa_Z][nPtBin_Z] = {{0}};          Double_t dMassPdg_data_Z_pt_Err[nEtaBinCoa_Z][nPtBin_Z] = {{0}}; 	     
  Double_t dMassPdg_data_Z_eta[nPtBinCoa_Z][nEtaBin_Z] = {{0}};          Double_t dMassPdg_data_Z_eta_Err[nPtBinCoa_Z][nEtaBin_Z] = {{0}}; 	     
  Double_t dMassPdg_data_Y_pt[nEtaBinCoa_Y][nPtBin_Y] = {{0}};          Double_t dMassPdg_data_Y_pt_Err[nEtaBinCoa_Y][nPtBin_Y] = {{0}}; 	     
  Double_t dMassPdg_data_Y_eta[nPtBinCoa_Y][nEtaBin_Y] = {{0}};          Double_t dMassPdg_data_Y_eta_Err[nPtBinCoa_Y][nEtaBin_Y] = {{0}}; 	     
  Double_t dMassPdg_data_JPsi_pt[nEtaBinCoa_JPsi][nPtBin_JPsi] = {{0}};          Double_t dMassPdg_data_JPsi_pt_Err[nEtaBinCoa_JPsi][nPtBin_JPsi] = {{0}}; 	     
  Double_t dMassPdg_data_JPsi_eta[nPtBinCoa_JPsi][nEtaBin_JPsi] = {{0}};          Double_t dMassPdg_data_JPsi_eta_Err[nPtBinCoa_JPsi][nEtaBin_JPsi] = {{0}}; 	     

  Double_t dMassPdg_mc_Z_pt[nEtaBinCoa_Z][nPtBin_Z] = {{0}};          Double_t dMassPdg_mc_Z_pt_Err[nEtaBinCoa_Z][nPtBin_Z] = {{0}}; 	     
  Double_t dMassPdg_mc_Z_eta[nPtBinCoa_Z][nEtaBin_Z] = {{0}};          Double_t dMassPdg_mc_Z_eta_Err[nPtBinCoa_Z][nEtaBin_Z] = {{0}}; 	     
  Double_t dMassPdg_mc_Y_pt[nEtaBinCoa_Y][nPtBin_Y] = {{0}};          Double_t dMassPdg_mc_Y_pt_Err[nEtaBinCoa_Y][nPtBin_Y] = {{0}}; 	     
  Double_t dMassPdg_mc_Y_eta[nPtBinCoa_Y][nEtaBin_Y] = {{0}};          Double_t dMassPdg_mc_Y_eta_Err[nPtBinCoa_Y][nEtaBin_Y] = {{0}}; 	     
  Double_t dMassPdg_mc_JPsi_pt[nEtaBinCoa_JPsi][nPtBin_JPsi] = {{0}};          Double_t dMassPdg_mc_JPsi_pt_Err[nEtaBinCoa_JPsi][nPtBin_JPsi] = {{0}}; 	     
  Double_t dMassPdg_mc_JPsi_eta[nPtBinCoa_JPsi][nEtaBin_JPsi] = {{0}};          Double_t dMassPdg_mc_JPsi_eta_Err[nPtBinCoa_JPsi][nEtaBin_JPsi] = {{0}}; 	     



  // "Delta" arrays filling for scale/resolution Z
  if (plotZ){
    for (UInt_t i=0; i<nEtaBinCoa_Z; ++i){
      for (UInt_t j=0; j<nPtBin_Z; ++j){
	Double_t e1_mass = mass_Z_pt_data_Err[i][j];
	Double_t e2_mass = mass_Z_pt_mc_Err[i][j];
	Double_t e1_sigma = sigma_Z_pt_data_Err[i][j];
	Double_t e2_sigma = sigma_Z_pt_mc_Err[i][j];
	// Double_t dMass = (mass_Z_pt_data[i][j] - mass_Z_pt_mc[i][j])/mass_Z_pt_data[i][j]; //buggy
	Double_t dMass = (mass_Z_pt_data[i][j] - mass_Z_pt_mc[i][j])/mass_Z;
	// Double_t dMassErr = computeErrorScale(e1_mass,e2_mass,mass_Z_pt_data[i][j],mass_Z_pt_mc[i][j]); //buggy
	Double_t dMassErr = computeErrorScale(e1_mass,e2_mass,mass_Z);
	// Double_t dSigma = (sigma_Z_pt_data[i][j] - sigma_Z_pt_mc[i][j])/sigma_Z_pt_data[i][j]; //buggy
	Double_t dSigma = (sigma_Z_pt_data[i][j] - sigma_Z_pt_mc[i][j])/sigma_Z_pt_mc[i][j];
	Double_t dSigmaErr = computeErrorResol(e1_sigma,e2_sigma,sigma_Z_pt_data[i][j],sigma_Z_pt_mc[i][j]);
	dMass_Z_pt[i][j] = dMass; dMass_Z_pt_Err[i][j] = dMassErr;
	dSigma_Z_pt[i][j] = dSigma; dSigma_Z_pt_Err[i][j] = dSigmaErr;
	// cout<<"Mass_data["<<i<<"]["<<j<<"] = "<<mass_Z_pt_data[i][j]<<endl;
	// cout<<"Mass_mc["<<i<<"]["<<j<<"] = "<<mass_Z_pt_mc[i][j]<<endl;
	// cout<<"Sigma_data["<<i<<"]["<<j<<"] = "<<sigma_Z_pt_data[i][j]<<endl;
	// cout<<"Sigma_mc["<<i<<"]["<<j<<"] = "<<sigma_Z_pt_mc[i][j]<<endl;
	// cout<<"dMass["<<i<<"]["<<j<<"] = "<<dMass<<" +- "<<dMassErr<<endl;
	// cout<<"dSigma["<<i<<"]["<<j<<"] = "<<dSigma<<" +- "<<dSigmaErr<<endl;
	Double_t dMassPdg_data = (mass_Z_pt_data[i][j] - mass_Z)/mass_Z;
	Double_t dMassPdg_data_Err = computeErrorPdg(e1_mass, mass_Z);
	dMassPdg_data_Z_pt[i][j] = dMassPdg_data; dMassPdg_data_Z_pt_Err[i][j] = dMassPdg_data_Err;
	Double_t dMassPdg_mc = (mass_Z_pt_mc[i][j] - mass_Z)/mass_Z;
	Double_t dMassPdg_mc_Err = computeErrorPdg(e2_mass,mass_Z);
	dMassPdg_mc_Z_pt[i][j] = dMassPdg_mc; dMassPdg_mc_Z_pt_Err[i][j] = dMassPdg_mc_Err;
      }
    }

    for (UInt_t i=0; i<nPtBinCoa_Z; ++i){
      for (UInt_t j=0; j<nEtaBin_Z; ++j){
	Double_t e1_mass = mass_Z_eta_data_Err[i][j];
	Double_t e2_mass = mass_Z_eta_mc_Err[i][j];
	Double_t e1_sigma = sigma_Z_eta_data_Err[i][j];
	Double_t e2_sigma = sigma_Z_eta_mc_Err[i][j];
	// Double_t dMass = (mass_Z_eta_data[i][j] - mass_Z_eta_mc[i][j])/mass_Z_eta_data[i][j]; //buggy
	Double_t dMass = (mass_Z_eta_data[i][j] - mass_Z_eta_mc[i][j])/mass_Z;
	// Double_t dMassErr = computeErrorScale(e1_mass,e2_mass,mass_Z_eta_data[i][j],mass_Z_eta_mc[i][j]); //buggy
	Double_t dMassErr = computeErrorScale(e1_mass,e2_mass,mass_Z);
	// Double_t dSigma = (sigma_Z_eta_data[i][j] - sigma_Z_eta_mc[i][j])/sigma_Z_eta_data[i][j]; //buggy
	Double_t dSigma = (sigma_Z_eta_data[i][j] - sigma_Z_eta_mc[i][j])/sigma_Z_eta_mc[i][j];
	Double_t dSigmaErr = computeErrorResol(e1_sigma,e2_sigma,sigma_Z_eta_data[i][j],sigma_Z_eta_mc[i][j]);
	dMass_Z_eta[i][j] = dMass; dMass_Z_eta_Err[i][j] = dMassErr;
	dSigma_Z_eta[i][j] = dSigma; dSigma_Z_eta_Err[i][j] = dSigmaErr;
	// cout<<"Mass_data["<<i<<"]["<<j<<"] = "<<mass_Z_eta_data[i][j]<<endl;
	// cout<<"Mass_mc["<<i<<"]["<<j<<"] = "<<mass_Z_eta_mc[i][j]<<endl;
	// cout<<"Sigma_data["<<i<<"]["<<j<<"] = "<<sigma_Z_eta_data[i][j]<<endl;
	// cout<<"Sigma_mc["<<i<<"]["<<j<<"] = "<<sigma_Z_eta_mc[i][j]<<endl;
	// cout<<"dMass["<<i<<"]["<<j<<"] = "<<dMass<<" +- "<<dMassErr<<endl;
	// cout<<"dSigma["<<i<<"]["<<j<<"] = "<<dSigma<<" +- "<<dSigmaErr<<endl;
	Double_t dMassPdg_data = (mass_Z_eta_data[i][j] - mass_Z)/mass_Z;
	Double_t dMassPdg_data_Err = computeErrorPdg(e1_mass,mass_Z);
	dMassPdg_data_Z_eta[i][j] = dMassPdg_data; dMassPdg_data_Z_eta_Err[i][j] = dMassPdg_data_Err;
	Double_t dMassPdg_mc = (mass_Z_eta_mc[i][j] - mass_Z)/mass_Z;
	Double_t dMassPdg_mc_Err = computeErrorPdg(e2_mass,mass_Z);
	dMassPdg_mc_Z_eta[i][j] = dMassPdg_mc; dMassPdg_mc_Z_eta_Err[i][j] = dMassPdg_mc_Err;
      }
    }
  }// plot Z

  // "Delta" arrays filling for scale/resolution Y
  if (plotY){
    for (UInt_t i=0; i<nEtaBinCoa_Y; ++i){
      for (UInt_t j=0; j<nPtBin_Y; ++j){
	Double_t e1_mass = mass_Y_pt_data_Err[i][j];
	Double_t e2_mass = mass_Y_pt_mc_Err[i][j];
	Double_t e1_sigma = sigma_Y_pt_data_Err[i][j];
	Double_t e2_sigma = sigma_Y_pt_mc_Err[i][j];
	// Double_t dMass = (mass_Y_pt_data[i][j] - mass_Y_pt_mc[i][j])/mass_Y_pt_data[i][j]; //buggy
	Double_t dMass = (mass_Y_pt_data[i][j] - mass_Y_pt_mc[i][j])/mass_Y;
	// Double_t dMassErr = computeErrorScale(e1_mass,e2_mass,mass_Y_pt_data[i][j],mass_Y_pt_mc[i][j]); //buggy
	Double_t dMassErr = computeErrorScale(e1_mass,e2_mass,mass_Y);
	// Double_t dSigma = (sigma_Y_pt_data[i][j] - sigma_Y_pt_mc[i][j])/sigma_Y_pt_data[i][j]; //buggy
	Double_t dSigma = (sigma_Y_pt_data[i][j] - sigma_Y_pt_mc[i][j])/sigma_Y_pt_mc[i][j];
	Double_t dSigmaErr = computeErrorResol(e1_sigma,e2_sigma,sigma_Y_pt_data[i][j],sigma_Y_pt_mc[i][j]);
	dMass_Y_pt[i][j] = dMass; dMass_Y_pt_Err[i][j] = dMassErr;
	dSigma_Y_pt[i][j] = dSigma; dSigma_Y_pt_Err[i][j] = dSigmaErr;
	// cout<<"Mass_data["<<i<<"]["<<j<<"] = "<<mass_Y_pt_data[i][j]<<endl;
	// cout<<"Mass_mc["<<i<<"]["<<j<<"] = "<<mass_Y_pt_mc[i][j]<<endl;
	// cout<<"Sigma_data["<<i<<"]["<<j<<"] = "<<sigma_Y_pt_data[i][j]<<endl;
	// cout<<"Sigma_mc["<<i<<"]["<<j<<"] = "<<sigma_Y_pt_mc[i][j]<<endl;
	//cout<<"dMass["<<i<<"]["<<j<<"] = "<<dMass<<" +- "<<dMassErr<<endl;
	// cout<<"dSigma["<<i<<"]["<<j<<"] = "<<dSigma<<" +- "<<dSigmaErr<<endl;
	Double_t dMassPdg_data = (mass_Y_pt_data[i][j] - mass_Y)/mass_Y;
	Double_t dMassPdg_data_Err = computeErrorPdg(e1_mass,mass_Y);
	dMassPdg_data_Y_pt[i][j] = dMassPdg_data; dMassPdg_data_Y_pt_Err[i][j] = dMassPdg_data_Err;
	Double_t dMassPdg_mc = (mass_Y_pt_mc[i][j] - mass_Y)/mass_Y;
	Double_t dMassPdg_mc_Err = computeErrorPdg(e2_mass,mass_Y);
	dMassPdg_mc_Y_pt[i][j] = dMassPdg_mc; dMassPdg_mc_Y_pt_Err[i][j] = dMassPdg_mc_Err;
      }
    }

    for (UInt_t i=0; i<nPtBinCoa_Y; ++i){
      for (UInt_t j=0; j<nEtaBin_Y; ++j){
	Double_t e1_mass = mass_Y_eta_data_Err[i][j];
	Double_t e2_mass = mass_Y_eta_mc_Err[i][j];
	Double_t e1_sigma = sigma_Y_eta_data_Err[i][j];
	Double_t e2_sigma = sigma_Y_eta_mc_Err[i][j];
	// Double_t dMass = (mass_Y_eta_data[i][j] - mass_Y_eta_mc[i][j])/mass_Y_eta_data[i][j]; //buggy
	Double_t dMass = (mass_Y_eta_data[i][j] - mass_Y_eta_mc[i][j])/mass_Y;
	// Double_t dMassErr = computeErrorScale(e1_mass,e2_mass,mass_Y_eta_data[i][j],mass_Y_eta_mc[i][j]); //buggy
	Double_t dMassErr = computeErrorScale(e1_mass,e2_mass,mass_Y);
	// Double_t dSigma = (sigma_Y_eta_data[i][j] - sigma_Y_eta_mc[i][j])/sigma_Y_eta_data[i][j]; //buggy
	Double_t dSigma = (sigma_Y_eta_data[i][j] - sigma_Y_eta_mc[i][j])/sigma_Y_eta_mc[i][j];
	Double_t dSigmaErr = computeErrorResol(e1_sigma,e2_sigma,sigma_Y_eta_data[i][j],sigma_Y_eta_mc[i][j]);
	dMass_Y_eta[i][j] = dMass; dMass_Y_eta_Err[i][j] = dMassErr;
	dSigma_Y_eta[i][j] = dSigma; dSigma_Y_eta_Err[i][j] = dSigmaErr;
	// cout<<"Mass_data["<<i<<"]["<<j<<"] = "<<mass_Y_eta_data[i][j]<<endl;
	// cout<<"Mass_mc["<<i<<"]["<<j<<"] = "<<mass_Y_eta_mc[i][j]<<endl;
	// cout<<"Sigma_data["<<i<<"]["<<j<<"] = "<<sigma_Y_eta_data[i][j]<<endl;
	// cout<<"Sigma_mc["<<i<<"]["<<j<<"] = "<<sigma_Y_eta_mc[i][j]<<endl;
	// cout<<"dMass["<<i<<"]["<<j<<"] = "<<dMass<<" +- "<<dMassErr<<endl;
	// cout<<"dSigma["<<i<<"]["<<j<<"] = "<<dSigma<<" +- "<<dSigmaErr<<endl;
	Double_t dMassPdg_data = (mass_Y_eta_data[i][j] - mass_Y)/mass_Y;
	Double_t dMassPdg_data_Err = computeErrorPdg(e1_mass,mass_Y);
	dMassPdg_data_Y_eta[i][j] = dMassPdg_data; dMassPdg_data_Y_eta_Err[i][j] = dMassPdg_data_Err;
	Double_t dMassPdg_mc = (mass_Y_eta_mc[i][j] - mass_Y)/mass_Y;
	Double_t dMassPdg_mc_Err = computeErrorPdg(e2_mass,mass_Y);
	dMassPdg_mc_Y_eta[i][j] = dMassPdg_mc; dMassPdg_mc_Y_eta_Err[i][j] = dMassPdg_mc_Err;
      }
    }
  } // plot Y

  // "Delta" arrays filling for scale/resolution JPsi
  if (plotJPsi){
    for (UInt_t i=0; i<nEtaBinCoa_JPsi; ++i){
      for (UInt_t j=0; j<nPtBin_JPsi; ++j){
	Double_t e1_mass = mass_JPsi_pt_data_Err[i][j];
	Double_t e2_mass = mass_JPsi_pt_mc_Err[i][j];
	Double_t e1_sigma = sigma_JPsi_pt_data_Err[i][j];
	Double_t e2_sigma = sigma_JPsi_pt_mc_Err[i][j];
	// Double_t dMass = (mass_JPsi_pt_data[i][j] - mass_JPsi_pt_mc[i][j])/mass_JPsi_pt_data[i][j]; //buggy
	Double_t dMass = (mass_JPsi_pt_data[i][j] - mass_JPsi_pt_mc[i][j])/mass_JPsi;
	// Double_t dMassErr = computeErrorScale(e1_mass,e2_mass,mass_JPsi_pt_data[i][j],mass_JPsi_pt_mc[i][j]); //buggy
	Double_t dMassErr = computeErrorScale(e1_mass,e2_mass,mass_JPsi);
	// Double_t dSigma = (sigma_JPsi_pt_data[i][j] - sigma_JPsi_pt_mc[i][j])/sigma_JPsi_pt_data[i][j];
	Double_t dSigma = (sigma_JPsi_pt_data[i][j] - sigma_JPsi_pt_mc[i][j])/sigma_JPsi_pt_mc[i][j];
	Double_t dSigmaErr = computeErrorResol(e1_sigma,e2_sigma,sigma_JPsi_pt_data[i][j],sigma_JPsi_pt_mc[i][j]);
	dMass_JPsi_pt[i][j] = dMass; dMass_JPsi_pt_Err[i][j] = dMassErr;
	dSigma_JPsi_pt[i][j] = dSigma; dSigma_JPsi_pt_Err[i][j] = dSigmaErr;
	// cout<<"Mass_data["<<i<<"]["<<j<<"] = "<<mass_JPsi_pt_data[i][j]<<endl;
	// cout<<"Mass_mc["<<i<<"]["<<j<<"] = "<<mass_JPsi_pt_mc[i][j]<<endl;
	// cout<<"Sigma_data["<<i<<"]["<<j<<"] = "<<sigma_JPsi_pt_data[i][j]<<endl;
	// cout<<"Sigma_mc["<<i<<"]["<<j<<"] = "<<sigma_JPsi_pt_mc[i][j]<<endl;
	// cout<<"dMass["<<i<<"]["<<j<<"] = "<<dMass<<" +- "<<dMassErr<<endl;
	// cout<<"dSigma["<<i<<"]["<<j<<"] = "<<dSigma<<" +- "<<dSigmaErr<<endl;
	Double_t dMassPdg_data = (mass_JPsi_pt_data[i][j] - mass_JPsi)/mass_JPsi;
	Double_t dMassPdg_data_Err = computeErrorPdg(e1_mass,mass_JPsi);
	dMassPdg_data_JPsi_pt[i][j] = dMassPdg_data; dMassPdg_data_JPsi_pt_Err[i][j] = dMassPdg_data_Err;
	Double_t dMassPdg_mc = (mass_JPsi_pt_mc[i][j] - mass_JPsi)/mass_JPsi;
	Double_t dMassPdg_mc_Err = computeErrorPdg(e2_mass,mass_JPsi);
	dMassPdg_mc_JPsi_pt[i][j] = dMassPdg_mc; dMassPdg_mc_JPsi_pt_Err[i][j] = dMassPdg_mc_Err;
      }
    }

    for (UInt_t i=0; i<nPtBinCoa_JPsi; ++i){
      for (UInt_t j=0; j<nEtaBin_JPsi; ++j){
	Double_t e1_mass = mass_JPsi_eta_data_Err[i][j];
	Double_t e2_mass = mass_JPsi_eta_mc_Err[i][j];
	Double_t e1_sigma = sigma_JPsi_eta_data_Err[i][j];
	Double_t e2_sigma = sigma_JPsi_eta_mc_Err[i][j];
	// Double_t dMass = (mass_JPsi_eta_data[i][j] - mass_JPsi_eta_mc[i][j])/mass_JPsi_eta_data[i][j]; //buggy
	Double_t dMass = (mass_JPsi_eta_data[i][j] - mass_JPsi_eta_mc[i][j])/mass_JPsi;
	// Double_t dMassErr = computeErrorScale(e1_mass,e2_mass,mass_JPsi_eta_data[i][j],mass_JPsi_eta_mc[i][j]); //buggy
	Double_t dMassErr = computeErrorScale(e1_mass,e2_mass,mass_JPsi);
	// Double_t dSigma = (sigma_JPsi_eta_data[i][j] - sigma_JPsi_eta_mc[i][j])/sigma_JPsi_eta_data[i][j]; //buggy
	Double_t dSigma = (sigma_JPsi_eta_data[i][j] - sigma_JPsi_eta_mc[i][j])/sigma_JPsi_eta_mc[i][j];
	Double_t dSigmaErr = computeErrorResol(e1_sigma,e2_sigma,sigma_JPsi_eta_data[i][j],sigma_JPsi_eta_mc[i][j]);
	dMass_JPsi_eta[i][j] = dMass; dMass_JPsi_eta_Err[i][j] = dMassErr;
	dSigma_JPsi_eta[i][j] = dSigma; dSigma_JPsi_eta_Err[i][j] = dSigmaErr;
	// cout<<"Mass_data["<<i<<"]["<<j<<"] = "<<mass_JPsi_eta_data[i][j]<<endl;
	// cout<<"Mass_mc["<<i<<"]["<<j<<"] = "<<mass_JPsi_eta_mc[i][j]<<endl;
	// cout<<"Sigma_data["<<i<<"]["<<j<<"] = "<<sigma_JPsi_eta_data[i][j]<<endl;
	// cout<<"Sigma_mc["<<i<<"]["<<j<<"] = "<<sigma_JPsi_eta_mc[i][j]<<endl;
	// cout<<"dMass["<<i<<"]["<<j<<"] = "<<dMass<<" +- "<<dMassErr<<endl;
	// cout<<"dSigma["<<i<<"]["<<j<<"] = "<<dSigma<<" +- "<<dSigmaErr<<endl;
	Double_t dMassPdg_data = (mass_JPsi_eta_data[i][j] - mass_JPsi)/mass_JPsi;
	Double_t dMassPdg_data_Err = computeErrorPdg(e1_mass,mass_JPsi);
	dMassPdg_data_JPsi_eta[i][j] = dMassPdg_data; dMassPdg_data_JPsi_eta_Err[i][j] = dMassPdg_data_Err;
	Double_t dMassPdg_mc = (mass_JPsi_eta_mc[i][j] - mass_JPsi)/mass_JPsi;
	Double_t dMassPdg_mc_Err = computeErrorPdg(e2_mass,mass_JPsi);
	dMassPdg_mc_JPsi_eta[i][j] = dMassPdg_mc; dMassPdg_mc_JPsi_eta_Err[i][j] = dMassPdg_mc_Err;
      }
    }
  }//plot JPsi


  //Define final TGraphs
  tge* tge_dMass_Z_pt[nEtaBinCoa_Z];        tge* tge_dMass_Z_eta[nPtBinCoa_Z];
  tge* tge_dMass_Y_pt[nEtaBinCoa_Y];        tge* tge_dMass_Y_eta[nPtBinCoa_Y];
  tge* tge_dMass_JPsi_pt[nEtaBinCoa_JPsi];  tge* tge_dMass_JPsi_eta[nPtBinCoa_JPsi];
  tge* tge_dSigma_Z_pt[nEtaBinCoa_Z];       tge* tge_dSigma_Z_eta[nPtBinCoa_Z];
  tge* tge_dSigma_Y_pt[nEtaBinCoa_Y];       tge* tge_dSigma_Y_eta[nPtBinCoa_Y];
  tge* tge_dSigma_JPsi_pt[nEtaBinCoa_JPsi]; tge* tge_dSigma_JPsi_eta[nPtBinCoa_JPsi];

  tge* tge_dMassPdg_data_Z_pt[nEtaBinCoa_Z];       tge* tge_dMassPdg_data_Z_eta[nPtBinCoa_Z];        
  tge* tge_dMassPdg_data_Y_pt[nEtaBinCoa_Y];       tge* tge_dMassPdg_data_Y_eta[nPtBinCoa_Y]; 
  tge* tge_dMassPdg_data_JPsi_pt[nEtaBinCoa_JPsi]; tge* tge_dMassPdg_data_JPsi_eta[nPtBinCoa_JPsi]; 
  tge* tge_dMassPdg_mc_Z_pt[nEtaBinCoa_Z];       tge* tge_dMassPdg_mc_Z_eta[nPtBinCoa_Z];        
  tge* tge_dMassPdg_mc_Y_pt[nEtaBinCoa_Y];       tge* tge_dMassPdg_mc_Y_eta[nPtBinCoa_Y]; 
  tge* tge_dMassPdg_mc_JPsi_pt[nEtaBinCoa_JPsi]; tge* tge_dMassPdg_mc_JPsi_eta[nPtBinCoa_JPsi]; 


  mg* mg_dMass_pt = new mg("mg_dMass_pt", "#DeltaM/M vs. pT"); 
  mg* mg_dMass_eta = new mg("mg_dMass_eta", "#DeltaM/M vs. #eta"); 
  mg* mg_dSigma_pt = new mg("mg_dSigma_pt", "#Delta#sigma/#sigma vs. pT"); 
  mg* mg_dSigma_eta = new mg("mg_dSigma_eta", "#Delta#sigma/#sigma vs. #eta"); 

  mg* mg_dMassPdg_data_pt = new mg("mg_dMassPdg_data_pt", "#DeltaM/M (pdg) vs. pT"); 
  mg* mg_dMassPdg_data_eta = new mg("mg_dMassPdg_data_eta", "#DeltaM/M (pdg) vs. #eta"); 
  mg* mg_dMassPdg_mc_pt = new mg("mg_dMassPdg_mc_pt", "#DeltaM/M (pdg) vs. pT"); 
  mg* mg_dMassPdg_mc_eta = new mg("mg_dMassPdg_mc_eta", "#DeltaM/M (pdg) vs. #eta"); 


  // Define styles
  // const Color_t colorList_Z[10]       = {kBlue, kBlue, kBlue, kBlue, kBlue, kBlue, kBlue, kBlue, kBlue, kBlue};
  // const Color_t colorList_Y[10]       = {kGreen, kGreen, kGreen, kGreen, kGreen, kGreen, kGreen, kGreen, kGreen, kGreen};
  // const Color_t colorList_JPsi[10]    = {kRed, kRed, kRed, kRed, kRed, kRed, kRed, kRed, kRed, kRed};
  const Int_t colorList_Z[10]       = {4,4,4,4,4,4,4,4,4,4};
  const Int_t colorList_Y[10]       = {kGreen+3, kGreen+3, kGreen+3, kGreen+3, kGreen+3, kGreen+3, kGreen+3, kGreen+3, kGreen+3, kGreen+3};
  const Int_t colorList_JPsi[10]    = {2,2,2,2,2,2,2,2,2,2};
  const Int_t markerStyleList_Z[6]    = {20, 25, 21, 13, 14, 15};
  const Int_t markerStyleList_Y[6]    = {28, 34, 33, 13, 14, 15};
  const Int_t markerStyleList_JPsi[6] = {26, 33, 32, 27, 22, 15};

  TLegend* legScalePt = new TLegend(0.55,0.70,0.95,0.90);
  legScalePt->SetFillColor(0);
  legScalePt->SetTextFont(42);
  legScalePt->SetTextSize(0.035);

  TLegend* legScaleEta = new TLegend(0.55,0.70,0.95,0.90);
  legScaleEta->SetFillColor(0);
  legScaleEta->SetTextFont(42);
  legScaleEta->SetTextSize(0.035);

  TLegend* legResolPt = new TLegend(0.55,0.20,0.95,0.40);
  legResolPt->SetFillColor(0);
  legResolPt->SetTextFont(42);
  legResolPt->SetTextSize(0.035);

  TLegend* legResolEta = new TLegend(0.55,0.70,0.95,0.90);
  legResolEta->SetFillColor(0);
  legResolEta->SetTextFont(42);
  legResolEta->SetTextSize(0.035);

  // Shift x-axis for nice plotting
  Double_t ptOffset_Z = 2.; Double_t etaOffset_Z = 0.05;
  Double_t ptOffset_Y = 1.; Double_t etaOffset_Y = 0.05;
  Double_t ptOffset_JPsi = 1.; Double_t etaOffset_JPsi = 0.05;
  Double_t xPt_Z_pt_shift[nEtaBinCoa_Z][nPtBin_Z] = {{0}};
  Double_t xEta_Z_eta_shift[nPtBinCoa_Z][nEtaBin_Z] = {{0}};
  Double_t xPt_Y_pt_shift[nEtaBinCoa_Y][nPtBin_Y] = {{0}};
  Double_t xEta_Y_eta_shift[nPtBinCoa_Y][nEtaBin_Y] = {{0}};
  Double_t xPt_JPsi_pt_shift[nEtaBinCoa_JPsi][nPtBin_JPsi] = {{0}};
  Double_t xEta_JPsi_eta_shift[nPtBinCoa_JPsi][nEtaBin_JPsi] = {{0}};

  if (plotZ){
    for (UInt_t i=0; i<nEtaBinCoa_Z; ++i) {
      for (UInt_t j=0; j<nPtBin_Z; ++j) {
	xPt_Z_pt_shift[i][j] = xPt_Z_pt[j] + i*ptOffset_Z;
      }
    }

    for (UInt_t i=0; i<nPtBinCoa_Z; ++i) {
      for (UInt_t j=0; j<nEtaBin_Z; ++j) {
	xEta_Z_eta_shift[i][j] = xEta_Z_eta[j] + i*etaOffset_Z;
	//cout<<"xEta_Z_eta_shift["<<i<<"]["<<j<<"] = "<<xEta_Z_eta_shift[i][j]<<endl;
      }
    }
  }// plot Z

  if (plotY){
    for (UInt_t i=0; i<nEtaBinCoa_Y; ++i) {
      for (UInt_t j=0; j<nPtBin_Y; ++j) {
	xPt_Y_pt_shift[i][j] = xPt_Y_pt[j] + i*ptOffset_Y;
      }
    }

    for (UInt_t i=0; i<nPtBinCoa_Y; ++i) {
      for (UInt_t j=0; j<nEtaBin_Y; ++j) {
	xEta_Y_eta_shift[i][j] = xEta_Y_eta[j] + i*etaOffset_Y;
      }
    }
  }// plot Y

  if (plotJPsi){
    for (UInt_t i=0; i<nEtaBinCoa_JPsi; ++i) {
      for (UInt_t j=0; j<nPtBin_JPsi; ++j) {
	xPt_JPsi_pt_shift[i][j] = xPt_JPsi_pt[j] + i*ptOffset_JPsi;
	//cout<<"xPt_JPsi_pt_shift["<<i<<"]["<<j<<"] = "<<xPt_JPsi_pt_shift[i][j]<<endl;
      }
    }

    for (UInt_t i=0; i<nPtBinCoa_JPsi; ++i) {
      for (UInt_t j=0; j<nEtaBin_JPsi; ++j) {
	xEta_JPsi_eta_shift[i][j] = xEta_JPsi_eta[j] + i*etaOffset_JPsi;
      }
    }
  }//plot JPsi


  // Fill MultiGraph with Z info
  if (plotZ){
    for (UInt_t i=0; i<nEtaBinCoa_Z; ++i){
      //tge_dMass_Z_pt[i] = new tge(nPtBin_Z, xPt_Z_pt_shift[i], dMass_Z_pt[i], xPt_Z_pt_Err, dMass_Z_pt_Err[i]);
      tge_dMass_Z_pt[i] = new tge(nPtBin_Z, xPt_Z_pt_shift[i], dMass_Z_pt[i], 0, dMass_Z_pt_Err[i]);
      tge_dMass_Z_pt[i]->SetMarkerStyle(markerStyleList_Z[i]);
      tge_dMass_Z_pt[i]->SetMarkerColor(colorList_Z[i]);
      tge_dMass_Z_pt[i]->SetLineColor(colorList_Z[i]);
      legScalePt->AddEntry(tge_dMass_Z_pt[i], legLabels_Z_pt[i], "P");
      //tge_dSigma_Z_pt[i] = new tge(nPtBin_Z, xPt_Z_pt_shift[i], dSigma_Z_pt[i], xPt_Z_pt_Err, dSigma_Z_pt_Err[i]);
      tge_dSigma_Z_pt[i] = new tge(nPtBin_Z, xPt_Z_pt_shift[i], dSigma_Z_pt[i], 0, dSigma_Z_pt_Err[i]);
      tge_dSigma_Z_pt[i]->SetMarkerStyle(markerStyleList_Z[i]);
      tge_dSigma_Z_pt[i]->SetMarkerColor(colorList_Z[i]);
      tge_dSigma_Z_pt[i]->SetLineColor(colorList_Z[i]);
      legResolPt->AddEntry(tge_dSigma_Z_pt[i], legLabels_Z_pt[i], "P");
      mg_dMass_pt->Add(tge_dMass_Z_pt[i]);
      mg_dSigma_pt->Add(tge_dSigma_Z_pt[i]);

      //tge_dMassPdg_data_Z_pt[i] = new tge(nPtBin_Z, xPt_Z_pt_shift[i], dMassPdg_data_Z_pt[i], xPt_Z_pt_Err, dMassPdg_data_Z_pt_Err[i]);
      tge_dMassPdg_data_Z_pt[i] = new tge(nPtBin_Z, xPt_Z_pt_shift[i], dMassPdg_data_Z_pt[i], 0, dMassPdg_data_Z_pt_Err[i]);
      tge_dMassPdg_data_Z_pt[i]->SetMarkerStyle(markerStyleList_Z[i]);
      tge_dMassPdg_data_Z_pt[i]->SetMarkerColor(colorList_Z[i]);
      tge_dMassPdg_data_Z_pt[i]->SetLineColor(colorList_Z[i]);
      mg_dMassPdg_data_pt->Add(tge_dMassPdg_data_Z_pt[i]);
      //tge_dMassPdg_mc_Z_pt[i] = new tge(nPtBin_Z, xPt_Z_pt_shift[i], dMassPdg_mc_Z_pt[i], xPt_Z_pt_Err, dMassPdg_mc_Z_pt_Err[i]);
      tge_dMassPdg_mc_Z_pt[i] = new tge(nPtBin_Z, xPt_Z_pt_shift[i], dMassPdg_mc_Z_pt[i], 0, dMassPdg_mc_Z_pt_Err[i]);
      tge_dMassPdg_mc_Z_pt[i]->SetMarkerStyle(markerStyleList_Z[i]);
      tge_dMassPdg_mc_Z_pt[i]->SetMarkerColor(colorList_Z[i]);
      tge_dMassPdg_mc_Z_pt[i]->SetLineColor(colorList_Z[i]);
      mg_dMassPdg_mc_pt->Add(tge_dMassPdg_mc_Z_pt[i]);
    }

    for (UInt_t i=0; i<nPtBinCoa_Z; ++i){
      //tge_dMass_Z_eta[i] = new tge(nEtaBin_Z, xEta_Z_eta_shift[i], dMass_Z_eta[i], xEta_Z_eta_Err, dMass_Z_eta_Err[i]);
      tge_dMass_Z_eta[i] = new tge(nEtaBin_Z, xEta_Z_eta_shift[i], dMass_Z_eta[i], 0, dMass_Z_eta_Err[i]);
      tge_dMass_Z_eta[i]->SetMarkerStyle(markerStyleList_Z[i]);
      tge_dMass_Z_eta[i]->SetMarkerColor(colorList_Z[i]);
      tge_dMass_Z_eta[i]->SetLineColor(colorList_Z[i]);
      legScaleEta->AddEntry(tge_dMass_Z_eta[i], legLabels_Z_eta[i], "P");
      //tge_dSigma_Z_eta[i] = new tge(nEtaBin_Z, xEta_Z_eta_shift[i], dSigma_Z_eta[i], xEta_Z_eta_Err, dSigma_Z_eta_Err[i]);
      tge_dSigma_Z_eta[i] = new tge(nEtaBin_Z, xEta_Z_eta_shift[i], dSigma_Z_eta[i], 0, dSigma_Z_eta_Err[i]);
      tge_dSigma_Z_eta[i]->SetMarkerStyle(markerStyleList_Z[i]);
      tge_dSigma_Z_eta[i]->SetMarkerColor(colorList_Z[i]);
      tge_dSigma_Z_eta[i]->SetLineColor(colorList_Z[i]);
      legResolEta->AddEntry(tge_dSigma_Z_eta[i], legLabels_Z_eta[i], "P");
      mg_dMass_eta->Add(tge_dMass_Z_eta[i]);
      mg_dSigma_eta->Add(tge_dSigma_Z_eta[i]);
      //for (UInt_t j=0; j<nEtaBin_Z; ++j) cout<<"dMass_Z_eta["<<i<<"]["<<j<<"] = "<<dMass_Z_eta[i][j]<<endl;

      //tge_dMassPdg_data_Z_eta[i] = new tge(nEtaBin_Z, xEta_Z_eta_shift[i], dMassPdg_data_Z_eta[i], xEta_Z_eta_Err, dMassPdg_data_Z_eta_Err[i]);
      tge_dMassPdg_data_Z_eta[i] = new tge(nEtaBin_Z, xEta_Z_eta_shift[i], dMassPdg_data_Z_eta[i], 0, dMassPdg_data_Z_eta_Err[i]);
      tge_dMassPdg_data_Z_eta[i]->SetMarkerStyle(markerStyleList_Z[i]);
      tge_dMassPdg_data_Z_eta[i]->SetMarkerColor(colorList_Z[i]);
      tge_dMassPdg_data_Z_eta[i]->SetLineColor(colorList_Z[i]);
      mg_dMassPdg_data_eta->Add(tge_dMassPdg_data_Z_eta[i]);
      //tge_dMassPdg_mc_Z_eta[i] = new tge(nEtaBin_Z, xEta_Z_eta_shift[i], dMassPdg_mc_Z_eta[i], xEta_Z_eta_Err, dMassPdg_mc_Z_eta_Err[i]);
      tge_dMassPdg_mc_Z_eta[i] = new tge(nEtaBin_Z, xEta_Z_eta_shift[i], dMassPdg_mc_Z_eta[i], 0, dMassPdg_mc_Z_eta_Err[i]);
      tge_dMassPdg_mc_Z_eta[i]->SetMarkerStyle(markerStyleList_Z[i]);
      tge_dMassPdg_mc_Z_eta[i]->SetMarkerColor(colorList_Z[i]);
      tge_dMassPdg_mc_Z_eta[i]->SetLineColor(colorList_Z[i]);
      mg_dMassPdg_mc_eta->Add(tge_dMassPdg_mc_Z_eta[i]);
    }
  } // plotZ


  // Fill MultiGraph with Y info
  if (plotY){
    for (UInt_t i=0; i<nEtaBinCoa_Y; ++i){
      //tge_dMass_Y_pt[i] = new tge(nPtBin_Y, xPt_Y_pt_shift[i], dMass_Y_pt[i], xPt_Y_pt_Err, dMass_Y_pt_Err[i]);
      tge_dMass_Y_pt[i] = new tge(nPtBin_Y, xPt_Y_pt_shift[i], dMass_Y_pt[i], 0, dMass_Y_pt_Err[i]);
      tge_dMass_Y_pt[i]->SetMarkerStyle(markerStyleList_Y[i]);
      tge_dMass_Y_pt[i]->SetMarkerColor(colorList_Y[i]);
      tge_dMass_Y_pt[i]->SetLineColor(colorList_Y[i]);
      legScalePt->AddEntry(tge_dMass_Y_pt[i], legLabels_Y_pt[i], "P");
      //tge_dSigma_Y_pt[i] = new tge(nPtBin_Y, xPt_Y_pt_shift[i], dSigma_Y_pt[i], xPt_Y_pt_Err, dSigma_Y_pt_Err[i]);
      tge_dSigma_Y_pt[i] = new tge(nPtBin_Y, xPt_Y_pt_shift[i], dSigma_Y_pt[i], 0, dSigma_Y_pt_Err[i]);
      tge_dSigma_Y_pt[i]->SetMarkerStyle(markerStyleList_Y[i]);
      tge_dSigma_Y_pt[i]->SetMarkerColor(colorList_Y[i]);
      tge_dSigma_Y_pt[i]->SetLineColor(colorList_Y[i]);
      legResolPt->AddEntry(tge_dSigma_Y_pt[i], legLabels_Y_pt[i], "P");
      mg_dMass_pt->Add(tge_dMass_Y_pt[i]);
      mg_dSigma_pt->Add(tge_dSigma_Y_pt[i]);

      //tge_dMassPdg_data_Y_pt[i] = new tge(nPtBin_Y, xPt_Y_pt_shift[i], dMassPdg_data_Y_pt[i], xPt_Y_pt_Err, dMassPdg_data_Y_pt_Err[i]);
      tge_dMassPdg_data_Y_pt[i] = new tge(nPtBin_Y, xPt_Y_pt_shift[i], dMassPdg_data_Y_pt[i], 0, dMassPdg_data_Y_pt_Err[i]);
      tge_dMassPdg_data_Y_pt[i]->SetMarkerStyle(markerStyleList_Y[i]);
      tge_dMassPdg_data_Y_pt[i]->SetMarkerColor(colorList_Y[i]);
      tge_dMassPdg_data_Y_pt[i]->SetLineColor(colorList_Y[i]);
      mg_dMassPdg_data_pt->Add(tge_dMassPdg_data_Y_pt[i]);
      //tge_dMassPdg_mc_Y_pt[i] = new tge(nPtBin_Y, xPt_Y_pt_shift[i], dMassPdg_mc_Y_pt[i], xPt_Y_pt_Err, dMassPdg_mc_Y_pt_Err[i]);
      tge_dMassPdg_mc_Y_pt[i] = new tge(nPtBin_Y, xPt_Y_pt_shift[i], dMassPdg_mc_Y_pt[i], 0, dMassPdg_mc_Y_pt_Err[i]);
      tge_dMassPdg_mc_Y_pt[i]->SetMarkerStyle(markerStyleList_Y[i]);
      tge_dMassPdg_mc_Y_pt[i]->SetMarkerColor(colorList_Y[i]);
      tge_dMassPdg_mc_Y_pt[i]->SetLineColor(colorList_Y[i]);
      mg_dMassPdg_mc_pt->Add(tge_dMassPdg_mc_Y_pt[i]);
    }

    for (UInt_t i=0; i<nPtBinCoa_Y; ++i){
      //tge_dMass_Y_eta[i] = new tge(nEtaBin_Y, xEta_Y_eta_shift[i], dMass_Y_eta[i], xEta_Y_eta_Err, dMass_Y_eta_Err[i]);
      tge_dMass_Y_eta[i] = new tge(nEtaBin_Y, xEta_Y_eta_shift[i], dMass_Y_eta[i], 0, dMass_Y_eta_Err[i]);
      tge_dMass_Y_eta[i]->SetMarkerStyle(markerStyleList_Y[i]);
      tge_dMass_Y_eta[i]->SetMarkerColor(colorList_Y[i]);
      tge_dMass_Y_eta[i]->SetLineColor(colorList_Y[i]);
      legScaleEta->AddEntry(tge_dMass_Y_eta[i], legLabels_Y_eta[i], "P");
      //tge_dSigma_Y_eta[i] = new tge(nEtaBin_Y, xEta_Y_eta_shift[i], dSigma_Y_eta[i], xEta_Y_eta_Err, dSigma_Y_eta_Err[i]);
      tge_dSigma_Y_eta[i] = new tge(nEtaBin_Y, xEta_Y_eta_shift[i], dSigma_Y_eta[i], 0, dSigma_Y_eta_Err[i]);
      tge_dSigma_Y_eta[i]->SetMarkerStyle(markerStyleList_Y[i]);
      tge_dSigma_Y_eta[i]->SetMarkerColor(colorList_Y[i]);
      tge_dSigma_Y_eta[i]->SetLineColor(colorList_Y[i]);
      legResolEta->AddEntry(tge_dSigma_Y_eta[i], legLabels_Y_eta[i], "P");
      mg_dMass_eta->Add(tge_dMass_Y_eta[i]);
      mg_dSigma_eta->Add(tge_dSigma_Y_eta[i]);
      //for (UInt_t j=0; j<nEtaBin_Z; ++j) cout<<"dMass_Z_eta["<<i<<"]["<<j<<"] = "<<dMass_Z_eta[i][j]<<endl;

      //tge_dMassPdg_data_Y_eta[i] = new tge(nEtaBin_Y, xEta_Y_eta_shift[i], dMassPdg_data_Y_eta[i], xEta_Y_eta_Err, dMassPdg_data_Y_eta_Err[i]);
      tge_dMassPdg_data_Y_eta[i] = new tge(nEtaBin_Y, xEta_Y_eta_shift[i], dMassPdg_data_Y_eta[i], 0, dMassPdg_data_Y_eta_Err[i]);
      tge_dMassPdg_data_Y_eta[i]->SetMarkerStyle(markerStyleList_Y[i]);
      tge_dMassPdg_data_Y_eta[i]->SetMarkerColor(colorList_Y[i]);
      tge_dMassPdg_data_Y_eta[i]->SetLineColor(colorList_Y[i]);
      mg_dMassPdg_data_eta->Add(tge_dMassPdg_data_Y_eta[i]);
      //tge_dMassPdg_mc_Y_eta[i] = new tge(nEtaBin_Y, xEta_Y_eta_shift[i], dMassPdg_mc_Y_eta[i], xEta_Y_eta_Err, dMassPdg_mc_Y_eta_Err[i]);
      tge_dMassPdg_mc_Y_eta[i] = new tge(nEtaBin_Y, xEta_Y_eta_shift[i], dMassPdg_mc_Y_eta[i], 0, dMassPdg_mc_Y_eta_Err[i]);
      tge_dMassPdg_mc_Y_eta[i]->SetMarkerStyle(markerStyleList_Y[i]);
      tge_dMassPdg_mc_Y_eta[i]->SetMarkerColor(colorList_Y[i]);
      tge_dMassPdg_mc_Y_eta[i]->SetLineColor(colorList_Y[i]);
      mg_dMassPdg_mc_eta->Add(tge_dMassPdg_mc_Y_eta[i]);
    }
  }//plot Y

  // Fill MultiGraph with JPsi info
  if (plotJPsi){
    for (UInt_t i=0; i<nEtaBinCoa_JPsi; ++i){
      //tge_dMass_JPsi_pt[i] = new tge(nPtBin_JPsi, xPt_JPsi_pt_shift[i], dMass_JPsi_pt[i], xPt_JPsi_pt_Err, dMass_JPsi_pt_Err[i]);
      tge_dMass_JPsi_pt[i] = new tge(nPtBin_JPsi, xPt_JPsi_pt_shift[i], dMass_JPsi_pt[i], 0, dMass_JPsi_pt_Err[i]);
      tge_dMass_JPsi_pt[i]->SetMarkerStyle(markerStyleList_JPsi[i]);
      tge_dMass_JPsi_pt[i]->SetMarkerColor(colorList_JPsi[i]);
      tge_dMass_JPsi_pt[i]->SetLineColor(colorList_JPsi[i]);
      legScalePt->AddEntry(tge_dMass_JPsi_pt[i], legLabels_JPsi_pt[i], "P");
      //tge_dSigma_JPsi_pt[i] = new tge(nPtBin_JPsi, xPt_JPsi_pt_shift[i], dSigma_JPsi_pt[i], xPt_JPsi_pt_Err, dSigma_JPsi_pt_Err[i]);
      tge_dSigma_JPsi_pt[i] = new tge(nPtBin_JPsi, xPt_JPsi_pt_shift[i], dSigma_JPsi_pt[i], 0, dSigma_JPsi_pt_Err[i]);
      tge_dSigma_JPsi_pt[i]->SetMarkerStyle(markerStyleList_JPsi[i]);
      tge_dSigma_JPsi_pt[i]->SetMarkerColor(colorList_JPsi[i]);
      tge_dSigma_JPsi_pt[i]->SetLineColor(colorList_JPsi[i]);
      legResolPt->AddEntry(tge_dSigma_JPsi_pt[i], legLabels_JPsi_pt[i], "P");
      mg_dMass_pt->Add(tge_dMass_JPsi_pt[i]);
      mg_dSigma_pt->Add(tge_dSigma_JPsi_pt[i]);

      //tge_dMassPdg_data_JPsi_pt[i] = new tge(nPtBin_JPsi, xPt_JPsi_pt_shift[i], dMassPdg_data_JPsi_pt[i], xPt_JPsi_pt_Err, dMassPdg_data_JPsi_pt_Err[i]);
      tge_dMassPdg_data_JPsi_pt[i] = new tge(nPtBin_JPsi, xPt_JPsi_pt_shift[i], dMassPdg_data_JPsi_pt[i], 0, dMassPdg_data_JPsi_pt_Err[i]);
      tge_dMassPdg_data_JPsi_pt[i]->SetMarkerStyle(markerStyleList_JPsi[i]);
      tge_dMassPdg_data_JPsi_pt[i]->SetMarkerColor(colorList_JPsi[i]);
      tge_dMassPdg_data_JPsi_pt[i]->SetLineColor(colorList_JPsi[i]);
      mg_dMassPdg_data_pt->Add(tge_dMassPdg_data_JPsi_pt[i]);
      //tge_dMassPdg_mc_JPsi_pt[i] = new tge(nPtBin_JPsi, xPt_JPsi_pt_shift[i], dMassPdg_mc_JPsi_pt[i], xPt_JPsi_pt_Err, dMassPdg_mc_JPsi_pt_Err[i]);
      tge_dMassPdg_mc_JPsi_pt[i] = new tge(nPtBin_JPsi, xPt_JPsi_pt_shift[i], dMassPdg_mc_JPsi_pt[i], 0, dMassPdg_mc_JPsi_pt_Err[i]);
      tge_dMassPdg_mc_JPsi_pt[i]->SetMarkerStyle(markerStyleList_JPsi[i]);
      tge_dMassPdg_mc_JPsi_pt[i]->SetMarkerColor(colorList_JPsi[i]);
      tge_dMassPdg_mc_JPsi_pt[i]->SetLineColor(colorList_JPsi[i]);
      mg_dMassPdg_mc_pt->Add(tge_dMassPdg_mc_JPsi_pt[i]);
    }

    for (UInt_t i=0; i<nPtBinCoa_JPsi; ++i){
      //tge_dMass_JPsi_eta[i] = new tge(nEtaBin_JPsi, xEta_JPsi_eta_shift[i], dMass_JPsi_eta[i], xEta_JPsi_eta_Err, dMass_JPsi_eta_Err[i]);
      tge_dMass_JPsi_eta[i] = new tge(nEtaBin_JPsi, xEta_JPsi_eta_shift[i], dMass_JPsi_eta[i], 0, dMass_JPsi_eta_Err[i]);
      tge_dMass_JPsi_eta[i]->SetMarkerStyle(markerStyleList_JPsi[i]);
      tge_dMass_JPsi_eta[i]->SetMarkerColor(colorList_JPsi[i]);
      tge_dMass_JPsi_eta[i]->SetLineColor(colorList_JPsi[i]);
      legScaleEta->AddEntry(tge_dMass_JPsi_eta[i], legLabels_JPsi_eta[i], "P");
      //tge_dSigma_JPsi_eta[i] = new tge(nEtaBin_JPsi, xEta_JPsi_eta_shift[i], dSigma_JPsi_eta[i], xEta_JPsi_eta_Err, dSigma_JPsi_eta_Err[i]);
      tge_dSigma_JPsi_eta[i] = new tge(nEtaBin_JPsi, xEta_JPsi_eta_shift[i], dSigma_JPsi_eta[i], 0, dSigma_JPsi_eta_Err[i]);
      tge_dSigma_JPsi_eta[i]->SetMarkerStyle(markerStyleList_JPsi[i]);
      tge_dSigma_JPsi_eta[i]->SetMarkerColor(colorList_JPsi[i]);
      tge_dSigma_JPsi_eta[i]->SetLineColor(colorList_JPsi[i]);
      legResolEta->AddEntry(tge_dSigma_JPsi_eta[i], legLabels_JPsi_eta[i], "P");
      mg_dMass_eta->Add(tge_dMass_JPsi_eta[i]);
      mg_dSigma_eta->Add(tge_dSigma_JPsi_eta[i]);
      //for (UInt_t j=0; j<nEtaBin_Z; ++j) cout<<"dMass_Z_eta["<<i<<"]["<<j<<"] = "<<dMass_Z_eta[i][j]<<endl;

      //tge_dMassPdg_data_JPsi_eta[i] = new tge(nEtaBin_JPsi, xEta_JPsi_eta_shift[i], dMassPdg_data_JPsi_eta[i], xEta_JPsi_eta_Err, dMassPdg_data_JPsi_eta_Err[i]);
      tge_dMassPdg_data_JPsi_eta[i] = new tge(nEtaBin_JPsi, xEta_JPsi_eta_shift[i], dMassPdg_data_JPsi_eta[i], 0, dMassPdg_data_JPsi_eta_Err[i]);
      tge_dMassPdg_data_JPsi_eta[i]->SetMarkerStyle(markerStyleList_JPsi[i]);
      tge_dMassPdg_data_JPsi_eta[i]->SetMarkerColor(colorList_JPsi[i]);
      tge_dMassPdg_data_JPsi_eta[i]->SetLineColor(colorList_JPsi[i]);
      mg_dMassPdg_data_eta->Add(tge_dMassPdg_data_JPsi_eta[i]);
      //tge_dMassPdg_mc_JPsi_eta[i] = new tge(nEtaBin_JPsi, xEta_JPsi_eta_shift[i], dMassPdg_mc_JPsi_eta[i], xEta_JPsi_eta_Err, dMassPdg_mc_JPsi_eta_Err[i]);
      tge_dMassPdg_mc_JPsi_eta[i] = new tge(nEtaBin_JPsi, xEta_JPsi_eta_shift[i], dMassPdg_mc_JPsi_eta[i], 0, dMassPdg_mc_JPsi_eta_Err[i]);
      tge_dMassPdg_mc_JPsi_eta[i]->SetMarkerStyle(markerStyleList_JPsi[i]);
      tge_dMassPdg_mc_JPsi_eta[i]->SetMarkerColor(colorList_JPsi[i]);
      tge_dMassPdg_mc_JPsi_eta[i]->SetLineColor(colorList_JPsi[i]);
      mg_dMassPdg_mc_eta->Add(tge_dMassPdg_mc_JPsi_eta[i]);
    }
  }// plot JPsi


  // Plotting

  TPaveText *cmsprel = new TPaveText(0.2, 0.95, 0.99, 0.99, "NDC");
  cmsprel->SetTextSize(0.035);
  cmsprel->SetTextFont(42);
  cmsprel->SetFillColor(0);
  cmsprel->SetBorderSize(0);
  cmsprel->SetMargin(0.01);
  cmsprel->SetTextAlign(12); // align left
  cmsprel->AddText(0.0,0.5,"CMS Preliminary");
  cmsprel->AddText(0.53,0.5,"#sqrt{s} = 8 TeV, L=19.5 fb^{-1}");


  TCanvas* cScalePt = new TCanvas("cScalePt","cScalePt");
  cScalePt->SetGridy();
  cScalePt->cd();
  mg_dMass_pt->Draw("AP");
  cScalePt->SaveAs("ScalePt"+append+".png");
  cScalePt->SaveAs("ScalePt"+append+".pdf");
  cScalePt->SaveAs("ScalePt"+append+".eps");
  cScalePt->SaveAs("ScalePt"+append+".root"); 
  mg_dMass_pt->GetYaxis()->SetTitle("#DeltaM/M (data-MC)");
  //mg_dMass_pt->GetYaxis()->SetTitleOffset(1.4);
  mg_dMass_pt->GetXaxis()->SetTitle("p_{T} (GeV)");
  //mg_dMass_pt->GetXaxis()->SetTitleOffset(1.2);
  mg_dMass_pt->GetYaxis()->SetRangeUser(-0.003,0.003);
  mg_dMass_pt->GetXaxis()->SetRangeUser(0.,70.);
  legScalePt->Draw("same");
  cmsprel->Draw("same");
  cScalePt->SaveAs("ScalePt"+append+".png");
  cScalePt->SaveAs("ScalePt"+append+".pdf");
  cScalePt->SaveAs("ScalePt"+append+".eps");
  cScalePt->SaveAs("ScalePt"+append+".root");


  TCanvas* cScaleEta = new TCanvas("cScaleEta","cScaleEta");
  cScaleEta->SetGridy();
  cScaleEta->cd();
  mg_dMass_eta->Draw("AP");
  mg_dMass_eta->GetYaxis()->SetTitle("#DeltaM/M (data-MC)");
  //mg_dMass_eta->GetYaxis()->SetTitleOffset(1.4);
  mg_dMass_eta->GetXaxis()->SetTitle("|#eta|");
  //mg_dMass_eta->GetXaxis()->SetTitleOffset(1.2);
  mg_dMass_eta->GetYaxis()->SetRangeUser(-0.003,0.003);
  mg_dMass_eta->GetXaxis()->SetRangeUser(0.,2.5);
  legScaleEta->Draw("same");
  cScaleEta->SaveAs("ScaleEta"+append+".png");
  cScaleEta->SaveAs("ScaleEta"+append+".pdf");
  cScaleEta->SaveAs("ScaleEta"+append+".eps");
  cScaleEta->SaveAs("ScaleEta"+append+".root");

  TCanvas* cResolPt = new TCanvas("cResolPt","cResolPt");
  cResolPt->SetGridy();
  cResolPt->cd();
  mg_dSigma_pt->Draw("AP");
  mg_dSigma_pt->GetYaxis()->SetTitle("#Delta#sigma/#sigma (data-MC)");
  //mg_dSigma_pt->GetYaxis()->SetTitleOffset(1.4);
  mg_dSigma_pt->GetXaxis()->SetTitle("p_{T} (GeV)");
  //mg_dSigma_pt->GetXaxis()->SetTitleOffset(1.2);
  mg_dSigma_pt->GetYaxis()->SetRangeUser(-0.2,0.2);
  mg_dSigma_pt->GetXaxis()->SetRangeUser(0.,70.);
  legResolPt->Draw("same");
  cResolPt->SaveAs("ResolPt"+append+".png");
  cResolPt->SaveAs("ResolPt"+append+".pdf");
  cResolPt->SaveAs("ResolPt"+append+".eps");
  cResolPt->SaveAs("ResolPt"+append+".root");

  TCanvas* cResolEta = new TCanvas("cResolEta","cResolEta");
  cResolEta->SetGridy();
  cResolEta->cd();
  mg_dSigma_eta->Draw("AP");
  mg_dSigma_eta->GetYaxis()->SetTitle("#Delta#sigma/#sigma (data-MC)");
  //mg_dSigma_eta->GetYaxis()->SetTitleOffset(1.4);
  mg_dSigma_eta->GetXaxis()->SetTitle("|#eta|");
  //mg_dSigma_eta->GetXaxis()->SetTitleOffset(1.2);
  mg_dSigma_eta->GetYaxis()->SetRangeUser(-0.2,0.2);
  mg_dSigma_eta->GetXaxis()->SetRangeUser(0.,2.5);
  legResolEta->Draw("same");
  cResolEta->SaveAs("ResolEta"+append+".png");
  cResolEta->SaveAs("ResolEta"+append+".pdf");
  cResolEta->SaveAs("ResolEta"+append+".eps");
  cResolEta->SaveAs("ResolEta"+append+".root");

  TCanvas* cScalePdg_data_Pt = new TCanvas("cScalePdg_data_Pt","cScalePdg_data_Pt");
  cScalePdg_data_Pt->SetGridy();
  cScalePdg_data_Pt->cd();
  mg_dMassPdg_data_pt->Draw("AP");
  mg_dMassPdg_data_pt->GetYaxis()->SetTitle("#DeltaM/M (data-PDG)");
  //mg_dMassPdg_data_pt->GetYaxis()->SetTitleOffset(1.4);
  mg_dMassPdg_data_pt->GetXaxis()->SetTitle("p_{T} (GeV)");
  //mg_dMassPdg_data_pt->GetXaxis()->SetTitleOffset(1.2);
  mg_dMassPdg_data_pt->GetYaxis()->SetRangeUser(-0.005,0.005);
  mg_dMassPdg_data_pt->GetXaxis()->SetRangeUser(0.,70.);
  legScalePt->Draw("same");
  cScalePdg_data_Pt->SaveAs("ScalePdg_data_Pt"+append+".png");
  cScalePdg_data_Pt->SaveAs("ScalePdg_data_Pt"+append+".pdf");
  cScalePdg_data_Pt->SaveAs("ScalePdg_data_Pt"+append+".eps");
  cScalePdg_data_Pt->SaveAs("ScalePdg_data_Pt"+append+".root");

  TCanvas* cScalePdg_data_Eta = new TCanvas("cScalePdg_data_Eta","cScalePdg_data_Eta");
  cScalePdg_data_Eta->SetGridy();
  cScalePdg_data_Eta->cd();
  mg_dMassPdg_data_eta->Draw("AP");
  mg_dMassPdg_data_eta->GetYaxis()->SetTitle("#DeltaM/M (data-PDG)");
  //mg_dMassPdg_data_eta->GetYaxis()->SetTitleOffset(1.4);
  mg_dMassPdg_data_eta->GetXaxis()->SetTitle("#eta");
  //mg_dMassPdg_data_eta->GetXaxis()->SetTitleOffset(1.2);
  mg_dMassPdg_data_eta->GetYaxis()->SetRangeUser(-0.005,0.005);
  mg_dMassPdg_data_eta->GetXaxis()->SetRangeUser(0.,2.5);
  legScaleEta->Draw("same");
  cScalePdg_data_Eta->SaveAs("ScalePdg_data_Eta"+append+".png");
  cScalePdg_data_Eta->SaveAs("ScalePdg_data_Eta"+append+".pdf");
  cScalePdg_data_Eta->SaveAs("ScalePdg_data_Eta"+append+".eps");
  cScalePdg_data_Eta->SaveAs("ScalePdg_data_Eta"+append+".root"); 

  TCanvas* cScalePdg_mc_Pt = new TCanvas("cScalePdg_mc_Pt","cScalePdg_mc_Pt");
  cScalePdg_mc_Pt->SetGridy();
  cScalePdg_mc_Pt->cd();
  mg_dMassPdg_mc_pt->Draw("AP");
  mg_dMassPdg_mc_pt->GetYaxis()->SetTitle("#DeltaM/M (mc-PDG)");
  //mg_dMassPdg_mc_pt->GetYaxis()->SetTitleOffset(1.4);
  mg_dMassPdg_mc_pt->GetXaxis()->SetTitle("p_{T} (GeV)");
  //mg_dMassPdg_mc_pt->GetXaxis()->SetTitleOffset(1.2);
  mg_dMassPdg_mc_pt->GetYaxis()->SetRangeUser(-0.005,0.005);
  mg_dMassPdg_mc_pt->GetXaxis()->SetRangeUser(0.,70.);
  legScalePt->Draw("same");
  cScalePdg_mc_Pt->SaveAs("ScalePdg_mc_Pt"+append+".png");
  cScalePdg_mc_Pt->SaveAs("ScalePdg_mc_Pt"+append+".pdf");
  cScalePdg_mc_Pt->SaveAs("ScalePdg_mc_Pt"+append+".eps");
  cScalePdg_mc_Pt->SaveAs("ScalePdg_mc_Pt"+append+".root");

  TCanvas* cScalePdg_mc_Eta = new TCanvas("cScalePdg_mc_Eta","cScalePdg_mc_Eta");
  cScalePdg_mc_Eta->SetGridy();
  cScalePdg_mc_Eta->cd();
  mg_dMassPdg_mc_eta->Draw("AP");
  mg_dMassPdg_mc_eta->GetYaxis()->SetTitle("#DeltaM/M (mc-PDG)");
  //mg_dMassPdg_mc_eta->GetYaxis()->SetTitleOffset(1.4);
  mg_dMassPdg_mc_eta->GetXaxis()->SetTitle("#eta");
  //mg_dMassPdg_mc_eta->GetXaxis()->SetTitleOffset(1.2);
  mg_dMassPdg_mc_eta->GetYaxis()->SetRangeUser(-0.005,0.005);
  mg_dMassPdg_mc_eta->GetXaxis()->SetRangeUser(0.,2.5);
  legScaleEta->Draw("same");
  cScalePdg_mc_Eta->SaveAs("ScalePdg_mc_Eta"+append+".png");
  cScalePdg_mc_Eta->SaveAs("ScalePdg_mc_Eta"+append+".pdf");
  cScalePdg_mc_Eta->SaveAs("ScalePdg_mc_Eta"+append+".eps");
  cScalePdg_mc_Eta->SaveAs("ScalePdg_mc_Eta"+append+".root"); 
 


} // end main


Double_t computeErrorScale(Double_t e_data, Double_t e_mc, Double_t v_pdg){
  return sqrt( pow(e_data,2) + pow(e_mc,2) )/v_pdg;
}

Double_t computeErrorResol(Double_t e_data, Double_t e_mc, Double_t v_data, Double_t v_mc){
  return fabs((v_data-v_mc)/v_mc)*sqrt( pow(e_data/v_data,2) + pow(e_mc/v_mc,2) );
}


Double_t computeErrorPdg(Double_t e, Double_t nominalMass){
  return e/nominalMass;
}
