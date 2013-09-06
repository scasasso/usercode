// usage: 
// ./main myconfig_file.cfg
//
// to create 1 file with 6 th3f's do: 
// hadd h3_beforeCorrection.root `ls h3_*beforeCorrection.root`
// hadd h3_afterCorrection.root `ls h3_*afterCorrection.root` 

#include "MuonPair.h"
#include "LinkDef.h"

#include "TFile.h"
#include "TROOT.h"
#include "TTree.h"
#include "TChain.h"
#include "TH1F.h"
#include "TH3F.h"
#include "Rtypes.h"
#include "TObjString.h"

#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>


using namespace std;

bool newTree = false;


// main
int main(int argc, char *argv[]){
  
  TString fileNameTree = argv[1];
  TString minMass = argv[2];
  TString maxMass = argv[3];

  Int_t maxEntries = atoi(argv[4]);


  //std::cout << "maxEntries = " << maxEntries << std::endl;

  TChain *chain = new TChain("T");
  chain->Add(fileNameTree);
  chain->GetEntry(0); 
  
  int nentries = int(chain->GetEntries());
  cout << "+++++ No. of entries in the input tree: " << nentries << endl;

  // string for the cut on the selected invariant mass windowm    
  TString mass_cut=minMass+"*"+minMass+"<2*(event.mu1.fP4.fCoordinates.fT*event.mu2.fP4.fCoordinates.fT-event.mu1.fP4.fCoordinates.fX*event.mu2.fP4.fCoordinates.fX-event.mu1.fP4.fCoordinates.fY*event.mu2.fP4.fCoordinates.fY-event.mu1.fP4.fCoordinates.fZ*event.mu2.fP4.fCoordinates.fZ) && 2*(event.mu1.fP4.fCoordinates.fT*event.mu2.fP4.fCoordinates.fT-event.mu1.fP4.fCoordinates.fX*event.mu2.fP4.fCoordinates.fX-event.mu1.fP4.fCoordinates.fY*event.mu2.fP4.fCoordinates.fY-event.mu1.fP4.fCoordinates.fZ*event.mu2.fP4.fCoordinates.fZ)<"+maxMass+"*"+maxMass;
  //std::cout<<"String for cut: "+mass_cut<<std::endl;
  
  TString outFileName =  ((TObjString*)((((TObjString*)(fileNameTree.Tokenize("/"))->Last())->String().Tokenize("."))->At(0)))->String();


  TFile* fileTreeOut = TFile::Open(outFileName+"_Mass_"+minMass+"_"+maxMass+".root","RECREATE");
  fileTreeOut->cd();
  
  TTree *newtree = chain->CopyTree(mass_cut,"",maxEntries); // use a sub-sample this when debugging
  //TTree *newtree = chain->CopyTree(mass_cut);
  newtree->AutoSave();

  nentries = int(newtree->GetEntries());
  cout << "+++++ No. of entries in the output tree: " << nentries << endl;

  fileTreeOut->Write();
  fileTreeOut->Close();

  delete chain;

  
  return 0;
}

