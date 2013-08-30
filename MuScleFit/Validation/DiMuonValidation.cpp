// usage: 
// ./main myconfig_file.cfg
//
// to create 1 file with 6 th3f's do: 
// hadd h3_beforeCorrection.root `ls h3_*beforeCorrection.root`
// hadd h3_afterCorrection.root `ls h3_*afterCorrection.root` 

#include "../MuScleFitCorrector_v4_2/MuScleFitCorrector.h"
#include "MuonPair.h"
#include "LinkDef.h"

#include "TFile.h"
#include "TROOT.h"
#include "TTree.h"
#include "TChain.h"
#include "TH1F.h"
#include "TH3F.h"
#include "Rtypes.h"

#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>


using namespace std;

// helper class
class DiMuonValidator{
public:
  DiMuonValidator(string );
  ~DiMuonValidator(); // to be implemented with the "delete"'s
  void Fill();
private:
  string _resonanceId;
  string _evtType;
  MuScleFitCorrector *_corrector;
  TFile *_fileTreeIn;
  TFile *_fileTHOut[2];
  TH3F *_h3_MassVsEtaPt_beforeCorrection;
  TH3F *_h3_MassVsEtaPt_afterCorrection;
  TH1F *_h1_Mass_beforeCorrection;
  TH1F *_h1_Mass_afterCorrection;
};


DiMuonValidator::DiMuonValidator(string line){
  string minMass, maxMass;
  string fileNameTreeIn;
  string fileNameCorrectionIn;
  string fileMode;        // "RECREATE", "READ"

  // parse a line of the cfg file, e.g.
  // Z DATA root://eoscms//eos/cms/store/caf/user/emiglior/Alignment/ZMuMu/MuScleFit/Run2012C/CMSSW_53X/zmumuTree_53X.root MuScleFit_2012ABC_DATA_53X.txt 70 110 RECREATE

  istringstream iss(line);
  iss >>  _resonanceId >> _evtType >> fileNameTreeIn >> fileNameCorrectionIn >>  minMass >>  maxMass >> fileMode;
  //fileNameTreeIn="../input/zmumuTree_DATA.root";

  // create the MuScleFitCorrector
  _corrector = new MuScleFitCorrector(fileNameCorrectionIn.c_str());

  // root file with the pre-correction input Tree
  string fileNameTreeCutIn = string("/tmp/$USER/")+_resonanceId+string("_")+_evtType+string(".root");

  if ( fileMode == "RECREATE" ) {

    TChain *chain = new TChain("T");
    chain->Add(fileNameTreeIn.c_str());
    chain->GetEntry(0); 

    //Create a new file + a clone of old tree in new file
    _fileTreeIn = new TFile(fileNameTreeCutIn.c_str(),"RECREATE");

    int nentries = int(chain->GetEntries());
    cout << "+++++ No. of entries in the input tree: " << nentries << endl;

    // string for the cut on the selected invariant mass windowm    
    string mass_cut=minMass+string("*")+minMass+string("<2*(event.mu1.fCoordinates.fT*event.mu2.fCoordinates.fT-event.mu1.fCoordinates.fX*event.mu2.fCoordinates.fX-event.mu1.fCoordinates.fY*event.mu2.fCoordinates.fY-event.mu1.fCoordinates.fZ*event.mu2.fCoordinates.fZ) && 2*(event.mu1.fCoordinates.fT*event.mu2.fCoordinates.fT-event.mu1.fCoordinates.fX*event.mu2.fCoordinates.fX-event.mu1.fCoordinates.fY*event.mu2.fCoordinates.fY-event.mu1.fCoordinates.fZ*event.mu2.fCoordinates.fZ)<")+maxMass+string("*")+maxMass;
    // cout << mass_cut << endl; // DEBUG
    string run_cut("&& event.run<203746");  
    string all_cut=mass_cut+run_cut;

    //     TTree *newtree = chain->CopyTree(mass_cut.c_str(),"",500000); // use a sub-sample this when debugging
    TTree *newtree = chain->CopyTree(all_cut.c_str());
    newtree->AutoSave();

    nentries = int(newtree->GetEntries());
    cout << "+++++ No. of entries in the output tree: " << nentries << endl;

    delete chain;

  } else {
    _fileTreeIn = new TFile(fileNameTreeCutIn.c_str(),"READ");
  }

  // arrays for TH3F booking 
  const int nEtaBin = 24;
  const int nPtBin= 20;
  const int nMassBin = 500;

  // Output  
  string fileNameTHOut; 
  string h1title, h3title;

  // before corrections
  fileNameTHOut = string("/tmp/$USER/")+string("h3_")+_resonanceId+string("_")+_evtType+string("_beforeCorrection.root");
  _fileTHOut[0] = new TFile(fileNameTHOut.c_str(),"RECREATE");

  h1title = string("h1_")+_resonanceId+string("_")+_evtType;
  h3title = string("h3_")+_resonanceId+string("_")+_evtType;

  if(_resonanceId == "Z"){
    _h3_MassVsEtaPt_beforeCorrection = new TH3F( h3title.c_str(), "resonance mass",nEtaBin, 0., 2.4, nPtBin, 0., 100., nMassBin, atof(minMass.c_str()), atof(maxMass.c_str()) );//atof convert string to double  
  } else if(_resonanceId == "Y"){
    _h3_MassVsEtaPt_beforeCorrection = new TH3F( h3title.c_str(), "resonance mass",nEtaBin, 0., 2.4, nPtBin, 0.,  30., nMassBin, atof(minMass.c_str()), atof(maxMass.c_str()) );//atof convert string to double  
  } else if(_resonanceId == "JPsi"){
    _h3_MassVsEtaPt_beforeCorrection = new TH3F( h3title.c_str(), "resonance mass",nEtaBin, 0., 2.4, nPtBin, 0.,  40., nMassBin, atof(minMass.c_str()), atof(maxMass.c_str()) );//atof convert string to double  
  } 
  _h1_Mass_beforeCorrection = new TH1F( h1title.c_str(), "resonance mass", nMassBin, atof(minMass.c_str()), atof(maxMass.c_str()) );//atof convert string to double  

  // after corrections
  fileNameTHOut = string("/tmp/$USER/")+string("h3_")+_resonanceId+string("_")+_evtType+string("_afterCorrection.root");
  _fileTHOut[1] = new TFile(fileNameTHOut.c_str(),"RECREATE");
  if(_resonanceId == "Z"){
    _h3_MassVsEtaPt_afterCorrection = new TH3F( h3title.c_str(), "resonance mass",nEtaBin, 0., 2.4, nPtBin, 0., 100., nMassBin, atof(minMass.c_str()), atof(maxMass.c_str()) );//atof convert string to double  
  } else if(_resonanceId == "Y"){
    _h3_MassVsEtaPt_afterCorrection = new TH3F( h3title.c_str(), "resonance mass",nEtaBin, 0., 2.4, nPtBin, 0.,  30., nMassBin, atof(minMass.c_str()), atof(maxMass.c_str()) );//atof convert string to double  
  } else if(_resonanceId == "JPsi"){
    _h3_MassVsEtaPt_afterCorrection = new TH3F( h3title.c_str(), "resonance mass",nEtaBin, 0., 2.4, nPtBin, 0.,  40., nMassBin, atof(minMass.c_str()), atof(maxMass.c_str()) );//atof convert string to double  
  } 
  _h1_Mass_afterCorrection = new TH1F( h1title.c_str(), "resonance mass", nMassBin, atof(minMass.c_str()), atof(maxMass.c_str()) );//atof convert string to double  

}//end method


void DiMuonValidator::Fill(){


  TTree *treeIN =(TTree*)_fileTreeIn->Get("T"); //input tree named T
  
  // MuonPairs
  MuonPair *mupairIN_= 0;  

  // pre-correction
  TLorentzVector* muNeg_BC=0;
  TLorentzVector* muPos_BC=0;
  TLorentzVector* MuMu_BC=0;

  // post-correction
  TLorentzVector* muNeg_AC=0;
  TLorentzVector* muPos_AC=0;
  TLorentzVector* MuMu_AC=0;  
  
  // loop on the TTree
  if ( treeIN!=0 ) {              
    
    treeIN->SetBranchAddress("event", &mupairIN_); //select generated event    
    
    int nentries=treeIN->GetEntries();
    cout<<"Looping over tree entries ...";
    for(int entry=0; entry<nentries;  entry++){ 
    //    for(int entry=0; entry<100000;  entry++){ 
      treeIN->GetEntry(entry);
      if (entry%100000==0)cout<<"Reading muon pair n. "<<entry<<endl;

	// fetch muons before correction from the input tree
	muNeg_BC = new TLorentzVector(mupairIN_->mu1.Px(), mupairIN_->mu1.Py(), mupairIN_->mu1.Pz(), mupairIN_->mu1.E());
	muPos_BC = new TLorentzVector(mupairIN_->mu2.Px(), mupairIN_->mu2.Py(), mupairIN_->mu2.Pz(), mupairIN_->mu2.E());
	MuMu_BC = new TLorentzVector((*muNeg_BC)+(*muPos_BC));

	// make muons after correction       
	muNeg_AC = new TLorentzVector(*muNeg_BC);
	muPos_AC = new TLorentzVector(*muPos_BC);
	_corrector->applyPtCorrection(*muNeg_AC,-1); 
	_corrector->applyPtCorrection(*muPos_AC,+1);
	
	// for MC apply extra smearing
	if ( _evtType=="mc" ) {
	  _corrector->applyPtSmearing(*muNeg_AC,-1,false);
	  _corrector->applyPtSmearing(*muPos_AC,+1,false);
	}
	MuMu_AC = new TLorentzVector((*muNeg_AC)+(*muPos_AC));

	// fill histos
	_h3_MassVsEtaPt_beforeCorrection->Fill(fabs(muNeg_BC->Eta()), muNeg_BC->Pt(), MuMu_BC->M());
	_h3_MassVsEtaPt_beforeCorrection->Fill(fabs(muPos_BC->Eta()), muPos_BC->Pt(), MuMu_BC->M());
	_h1_Mass_beforeCorrection->Fill(MuMu_BC->M());
	_h3_MassVsEtaPt_afterCorrection->Fill(fabs(muNeg_AC->Eta()), muNeg_AC->Pt(), MuMu_AC->M()); 
	_h3_MassVsEtaPt_afterCorrection->Fill(fabs(muNeg_AC->Eta()), muNeg_AC->Pt(), MuMu_AC->M()); 
	_h1_Mass_afterCorrection->Fill(MuMu_AC->M()); 

	// clean up everything for the next iteration
	if ( muNeg_BC != 0 ) delete muNeg_BC; 
	if ( muPos_BC != 0 ) delete muPos_BC; 
	if ( MuMu_BC != 0 ) delete MuMu_BC; 
	if ( muNeg_AC != 0 ) delete muNeg_AC;
	if ( muPos_AC != 0 ) delete muPos_AC;
	if ( MuMu_AC != 0 ) delete MuMu_AC;

    }//loop over tree entries
    
  }//check if tree has any entry

  if ( treeIN !=0 ) delete treeIN;
}

DiMuonValidator::~DiMuonValidator(){
  //  cout << "DMV::~DMV() #1"<< _resonanceId+_evtType << endl;
  for (int i=0; i<2; i++) {
    _fileTHOut[i]->Write();
    _fileTHOut[i]->Close();
    if ( _fileTHOut[i] != 0 ) delete _fileTHOut[i];
  }
  //  cout << "DMV::~DMV() #2"<< endl;
  if ( _corrector != 0 ) delete _corrector;
  //  cout << "DMV::~DMV() #3"<< endl;
}

// main
int main(int argc, char *argv[]){
  
  DiMuonValidator* vDMV;
  
  // parse input cfg   
  string line_;
  ifstream cfgfile (argv[1]);
  //ifstream cfgfile ("dimuon_validation.cfg");
  if (cfgfile.is_open())
    {
      while ( cfgfile.good() )
	{
	  getline (cfgfile,line_);
	  if ( strncmp ("#",line_.c_str(),1) != 0 ) {
	    vDMV = new DiMuonValidator(line_);    
	    vDMV->Fill();
	    if ( vDMV !=0 ) delete vDMV;    
	  }  
	  cout << "reading cfg file " << line_ <<  endl;
	}
      cfgfile.close();
    }
  else cout << "Unable to open cfg file" << endl; 



  //
  return 0; 
}

