//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Apr 20 15:00:14 2012 by ROOT version 5.27/06b
// from TTree HZZ4l_Tree/Event Summary
// found on file: HZZ4l_DummyTree.root
//////////////////////////////////////////////////////////

#ifndef HZZ4lBaseclass_h
#define HZZ4lBaseclass_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

#include <vector>

class HZZ4lBaseclass {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Int_t           RunNumber;
   Int_t           EventNumber;
   Int_t           LumiNumber;
   Int_t           Nmu;
   Int_t           Nele;
   Int_t           Nvtx;
   std::vector<double>  *ZZMass;
   std::vector<double>  *ZZMassErr;
   std::vector<int>     *isBestCandidate;
   std::vector<double>  *ZZPt;
   std::vector<double>  *ZZEta;
   std::vector<double>  *ZZPhi;
   std::vector<double>  *ZZLD;
   std::vector<int>     *ZZType;
   std::vector<double>  *Z1Mass;
   std::vector<double>  *Z1Pt;
   std::vector<double>  *Z1Eta;
   std::vector<double>  *Z1Phi;
   std::vector<double>  *Z2Mass;
   std::vector<double>  *Z2Pt;
   std::vector<double>  *Z2Eta;
   std::vector<double>  *Z2Phi;
   std::vector<double>  *costhetastar;
   std::vector<double>  *helphi;
   std::vector<double>  *helphiZ1;
   std::vector<double>  *helphiZ2;
   std::vector<double>  *helcosthetaZ1;
   std::vector<double>  *helcosthetaZ2;
   std::vector<double>  *phistarZ1;
   std::vector<double>  *phistarZ2;
   std::vector<double>  *Lep1Pt;
   std::vector<double>  *Lep1Eta;
   std::vector<double>  *Lep1Phi;
   std::vector<int>     *Lep1LepId;
   std::vector<double>  *Lep1SIP;
   std::vector<double>  *Lep2Pt;
   std::vector<double>  *Lep2Eta;
   std::vector<double>  *Lep2Phi;
   std::vector<int>     *Lep2LepId;
   std::vector<double>  *Lep2SIP;
   std::vector<double>  *Lep3Pt;
   std::vector<double>  *Lep3Eta;
   std::vector<double>  *Lep3Phi;
   std::vector<int>     *Lep3LepId;
   std::vector<double>  *Lep3SIP;
   std::vector<double>  *Lep4Pt;
   std::vector<double>  *Lep4Eta;
   std::vector<double>  *Lep4Phi;
   std::vector<int>     *Lep4LepId;
   std::vector<double>  *Lep4SIP;
   std::vector<double>  *Lep1chargedHadIso;
   std::vector<double>  *Lep1chargedAllIso;
   std::vector<double>  *Lep1PUchargedHadIso;
   std::vector<double>  *Lep1neutralHadIso;
   std::vector<double>  *Lep1photonIso;
   std::vector<double>  *Lep1absIso;
   std::vector<double>  *Lep1relIso;
   std::vector<double>  *Lep2chargedHadIso;
   std::vector<double>  *Lep2chargedAllIso;
   std::vector<double>  *Lep2PUchargedHadIso;
   std::vector<double>  *Lep2neutralHadIso;
   std::vector<double>  *Lep2photonIso;
   std::vector<double>  *Lep2absIso;
   std::vector<double>  *Lep2relIso;
   std::vector<double>  *Lep3chargedHadIso;
   std::vector<double>  *Lep3chargedAllIso;
   std::vector<double>  *Lep3PUchargedHadIso;
   std::vector<double>  *Lep3neutralHadIso;
   std::vector<double>  *Lep3photonIso;
   std::vector<double>  *Lep3absIso;
   std::vector<double>  *Lep3relIso;
   std::vector<double>  *Lep4chargedHadIso;
   std::vector<double>  *Lep4chargedAllIso;
   std::vector<double>  *Lep4PUchargedHadIso;
   std::vector<double>  *Lep4neutralHadIso;
   std::vector<double>  *Lep4photonIso;
   std::vector<double>  *Lep4absIso;
   std::vector<double>  *Lep4relIso;

   // List of branches
   TBranch        *b_RunNumber;   //!
   TBranch        *b_EventNumber;   //!
   TBranch        *b_LumiNumber;   //!
   TBranch        *b_Nmu;   //!
   TBranch        *b_Nele;   //!
   TBranch        *b_Nvtx;   //!
   TBranch        *b_ZZMass;   //!
   TBranch        *b_ZZMassErr;   //!
   TBranch        *b_isBestCandidate;   //!
   TBranch        *b_ZZPt;   //!
   TBranch        *b_ZZEta;   //!
   TBranch        *b_ZZPhi;   //!
   TBranch        *b_ZZLD;   //!
   TBranch        *b_ZZType;   //!
   TBranch        *b_Z1Mass;   //!
   TBranch        *b_Z1Pt;   //!
   TBranch        *b_Z1Eta;   //!
   TBranch        *b_Z1Phi;   //!
   TBranch        *b_Z2Mass;   //!
   TBranch        *b_Z2Pt;   //!
   TBranch        *b_Z2Eta;   //!
   TBranch        *b_Z2Phi;   //!
   TBranch        *b_costhetastar;   //!
   TBranch        *b_helphi;   //!
   TBranch        *b_helphiZ1;   //!
   TBranch        *b_helphiZ2;   //!
   TBranch        *b_helcosthetaZ1;   //!
   TBranch        *b_helcosthetaZ2;   //!
   TBranch        *b_phistarZ1;   //!
   TBranch        *b_phistarZ2;   //!
   TBranch        *b_Lep1Pt;   //!
   TBranch        *b_Lep1Eta;   //!
   TBranch        *b_Lep1Phi;   //!
   TBranch        *b_Lep1LepId;   //!
   TBranch        *b_Lep1SIP;   //!
   TBranch        *b_Lep2Pt;   //!
   TBranch        *b_Lep2Eta;   //!
   TBranch        *b_Lep2Phi;   //!
   TBranch        *b_Lep2LepId;   //!
   TBranch        *b_Lep2SIP;   //!
   TBranch        *b_Lep3Pt;   //!
   TBranch        *b_Lep3Eta;   //!
   TBranch        *b_Lep3Phi;   //!
   TBranch        *b_Lep3LepId;   //!
   TBranch        *b_Lep3SIP;   //!
   TBranch        *b_Lep4Pt;   //!
   TBranch        *b_Lep4Eta;   //!
   TBranch        *b_Lep4Phi;   //!
   TBranch        *b_Lep4LepId;   //!
   TBranch        *b_Lep4SIP;   //!
   TBranch        *b_Lep1chargedHadIso;   //!
   TBranch        *b_Lep1chargedAllIso;   //!
   TBranch        *b_Lep1PUchargedHadIso;   //!
   TBranch        *b_Lep1neutralHadIso;   //!
   TBranch        *b_Lep1photonIso;   //!
   TBranch        *b_Lep1absIso;   //!
   TBranch        *b_Lep1relIso;   //!
   TBranch        *b_Lep2chargedHadIso;   //!
   TBranch        *b_Lep2chargedAllIso;   //!
   TBranch        *b_Lep2PUchargedHadIso;   //!
   TBranch        *b_Lep2neutralHadIso;   //!
   TBranch        *b_Lep2photonIso;   //!
   TBranch        *b_Lep2absIso;   //!
   TBranch        *b_Lep2relIso;   //!
   TBranch        *b_Lep3chargedHadIso;   //!
   TBranch        *b_Lep3chargedAllIso;   //!
   TBranch        *b_Lep3PUchargedHadIso;   //!
   TBranch        *b_Lep3neutralHadIso;   //!
   TBranch        *b_Lep3photonIso;   //!
   TBranch        *b_Lep3absIso;   //!
   TBranch        *b_Lep3relIso;   //!
   TBranch        *b_Lep4chargedHadIso;   //!
   TBranch        *b_Lep4chargedAllIso;   //!
   TBranch        *b_Lep4PUchargedHadIso;   //!
   TBranch        *b_Lep4neutralHadIso;   //!
   TBranch        *b_Lep4photonIso;   //!
   TBranch        *b_Lep4absIso;   //!
   TBranch        *b_Lep4relIso;   //!

   HZZ4lBaseclass(TTree *tree=0);
   virtual ~HZZ4lBaseclass();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef HZZ4lBaseclass_cxx
HZZ4lBaseclass::HZZ4lBaseclass(TTree *tree)
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("HZZ4l_DummyTree.root");
      if (!f) {
         f = new TFile("HZZ4l_DummyTree.root");
         f->cd("HZZ4l_DummyTree.root:/DummySelection");
      }
      tree = (TTree*)gDirectory->Get("HZZ4l_Tree");

   }
   Init(tree);
}

HZZ4lBaseclass::~HZZ4lBaseclass()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t HZZ4lBaseclass::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t HZZ4lBaseclass::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (!fChain->InheritsFrom(TChain::Class()))  return centry;
   TChain *chain = (TChain*)fChain;
   if (chain->GetTreeNumber() != fCurrent) {
      fCurrent = chain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void HZZ4lBaseclass::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   ZZMass = 0;
   ZZMassErr = 0;
   isBestCandidate = 0;
   ZZPt = 0;
   ZZEta = 0;
   ZZPhi = 0;
   ZZLD = 0;
   ZZType = 0;
   Z1Mass = 0;
   Z1Pt = 0;
   Z1Eta = 0;
   Z1Phi = 0;
   Z2Mass = 0;
   Z2Pt = 0;
   Z2Eta = 0;
   Z2Phi = 0;
   costhetastar = 0;
   helphi = 0;
   helphiZ1 = 0;
   helphiZ2 = 0;
   helcosthetaZ1 = 0;
   helcosthetaZ2 = 0;
   phistarZ1 = 0;
   phistarZ2 = 0;
   Lep1Pt = 0;
   Lep1Eta = 0;
   Lep1Phi = 0;
   Lep1LepId = 0;
   Lep1SIP = 0;
   Lep2Pt = 0;
   Lep2Eta = 0;
   Lep2Phi = 0;
   Lep2LepId = 0;
   Lep2SIP = 0;
   Lep3Pt = 0;
   Lep3Eta = 0;
   Lep3Phi = 0;
   Lep3LepId = 0;
   Lep3SIP = 0;
   Lep4Pt = 0;
   Lep4Eta = 0;
   Lep4Phi = 0;
   Lep4LepId = 0;
   Lep4SIP = 0;
   Lep1chargedHadIso = 0;
   Lep1chargedAllIso = 0;
   Lep1PUchargedHadIso = 0;
   Lep1neutralHadIso = 0;
   Lep1photonIso = 0;
   Lep1absIso = 0;
   Lep1relIso = 0;
   Lep2chargedHadIso = 0;
   Lep2chargedAllIso = 0;
   Lep2PUchargedHadIso = 0;
   Lep2neutralHadIso = 0;
   Lep2photonIso = 0;
   Lep2absIso = 0;
   Lep2relIso = 0;
   Lep3chargedHadIso = 0;
   Lep3chargedAllIso = 0;
   Lep3PUchargedHadIso = 0;
   Lep3neutralHadIso = 0;
   Lep3photonIso = 0;
   Lep3absIso = 0;
   Lep3relIso = 0;
   Lep4chargedHadIso = 0;
   Lep4chargedAllIso = 0;
   Lep4PUchargedHadIso = 0;
   Lep4neutralHadIso = 0;
   Lep4photonIso = 0;
   Lep4absIso = 0;
   Lep4relIso = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("RunNumber", &RunNumber, &b_RunNumber);
   fChain->SetBranchAddress("EventNumber", &EventNumber, &b_EventNumber);
   fChain->SetBranchAddress("LumiNumber", &LumiNumber, &b_LumiNumber);
   fChain->SetBranchAddress("Nmu", &Nmu, &b_Nmu);
   fChain->SetBranchAddress("Nele", &Nele, &b_Nele);
   fChain->SetBranchAddress("Nvtx", &Nvtx, &b_Nvtx);
   fChain->SetBranchAddress("ZZMass", &ZZMass, &b_ZZMass);
   fChain->SetBranchAddress("ZZMassErr", &ZZMassErr, &b_ZZMassErr);
   fChain->SetBranchAddress("isBestCandidate", &isBestCandidate, &b_isBestCandidate);
   fChain->SetBranchAddress("ZZPt", &ZZPt, &b_ZZPt);
   fChain->SetBranchAddress("ZZEta", &ZZEta, &b_ZZEta);
   fChain->SetBranchAddress("ZZPhi", &ZZPhi, &b_ZZPhi);
   fChain->SetBranchAddress("ZZLD", &ZZLD, &b_ZZLD);
   fChain->SetBranchAddress("ZZType", &ZZType, &b_ZZType);
   fChain->SetBranchAddress("Z1Mass", &Z1Mass, &b_Z1Mass);
   fChain->SetBranchAddress("Z1Pt", &Z1Pt, &b_Z1Pt);
   fChain->SetBranchAddress("Z1Eta", &Z1Eta, &b_Z1Eta);
   fChain->SetBranchAddress("Z1Phi", &Z1Phi, &b_Z1Phi);
   fChain->SetBranchAddress("Z2Mass", &Z2Mass, &b_Z2Mass);
   fChain->SetBranchAddress("Z2Pt", &Z2Pt, &b_Z2Pt);
   fChain->SetBranchAddress("Z2Eta", &Z2Eta, &b_Z2Eta);
   fChain->SetBranchAddress("Z2Phi", &Z2Phi, &b_Z2Phi);
   fChain->SetBranchAddress("costhetastar", &costhetastar, &b_costhetastar);
   fChain->SetBranchAddress("helphi", &helphi, &b_helphi);
   fChain->SetBranchAddress("helphiZ1", &helphiZ1, &b_helphiZ1);
   fChain->SetBranchAddress("helphiZ2", &helphiZ2, &b_helphiZ2);
   fChain->SetBranchAddress("helcosthetaZ1", &helcosthetaZ1, &b_helcosthetaZ1);
   fChain->SetBranchAddress("helcosthetaZ2", &helcosthetaZ2, &b_helcosthetaZ2);
   fChain->SetBranchAddress("phistarZ1", &phistarZ1, &b_phistarZ1);
   fChain->SetBranchAddress("phistarZ2", &phistarZ2, &b_phistarZ2);
   fChain->SetBranchAddress("Lep1Pt", &Lep1Pt, &b_Lep1Pt);
   fChain->SetBranchAddress("Lep1Eta", &Lep1Eta, &b_Lep1Eta);
   fChain->SetBranchAddress("Lep1Phi", &Lep1Phi, &b_Lep1Phi);
   fChain->SetBranchAddress("Lep1LepId", &Lep1LepId, &b_Lep1LepId);
   fChain->SetBranchAddress("Lep1SIP", &Lep1SIP, &b_Lep1SIP);
   fChain->SetBranchAddress("Lep2Pt", &Lep2Pt, &b_Lep2Pt);
   fChain->SetBranchAddress("Lep2Eta", &Lep2Eta, &b_Lep2Eta);
   fChain->SetBranchAddress("Lep2Phi", &Lep2Phi, &b_Lep2Phi);
   fChain->SetBranchAddress("Lep2LepId", &Lep2LepId, &b_Lep2LepId);
   fChain->SetBranchAddress("Lep2SIP", &Lep2SIP, &b_Lep2SIP);
   fChain->SetBranchAddress("Lep3Pt", &Lep3Pt, &b_Lep3Pt);
   fChain->SetBranchAddress("Lep3Eta", &Lep3Eta, &b_Lep3Eta);
   fChain->SetBranchAddress("Lep3Phi", &Lep3Phi, &b_Lep3Phi);
   fChain->SetBranchAddress("Lep3LepId", &Lep3LepId, &b_Lep3LepId);
   fChain->SetBranchAddress("Lep3SIP", &Lep3SIP, &b_Lep3SIP);
   fChain->SetBranchAddress("Lep4Pt", &Lep4Pt, &b_Lep4Pt);
   fChain->SetBranchAddress("Lep4Eta", &Lep4Eta, &b_Lep4Eta);
   fChain->SetBranchAddress("Lep4Phi", &Lep4Phi, &b_Lep4Phi);
   fChain->SetBranchAddress("Lep4LepId", &Lep4LepId, &b_Lep4LepId);
   fChain->SetBranchAddress("Lep4SIP", &Lep4SIP, &b_Lep4SIP);
   fChain->SetBranchAddress("Lep1chargedHadIso", &Lep1chargedHadIso, &b_Lep1chargedHadIso);
   fChain->SetBranchAddress("Lep1chargedAllIso", &Lep1chargedAllIso, &b_Lep1chargedAllIso);
   fChain->SetBranchAddress("Lep1PUchargedHadIso", &Lep1PUchargedHadIso, &b_Lep1PUchargedHadIso);
   fChain->SetBranchAddress("Lep1neutralHadIso", &Lep1neutralHadIso, &b_Lep1neutralHadIso);
   fChain->SetBranchAddress("Lep1photonIso", &Lep1photonIso, &b_Lep1photonIso);
   fChain->SetBranchAddress("Lep1absIso", &Lep1absIso, &b_Lep1absIso);
   fChain->SetBranchAddress("Lep1relIso", &Lep1relIso, &b_Lep1relIso);
   fChain->SetBranchAddress("Lep2chargedHadIso", &Lep2chargedHadIso, &b_Lep2chargedHadIso);
   fChain->SetBranchAddress("Lep2chargedAllIso", &Lep2chargedAllIso, &b_Lep2chargedAllIso);
   fChain->SetBranchAddress("Lep2PUchargedHadIso", &Lep2PUchargedHadIso, &b_Lep2PUchargedHadIso);
   fChain->SetBranchAddress("Lep2neutralHadIso", &Lep2neutralHadIso, &b_Lep2neutralHadIso);
   fChain->SetBranchAddress("Lep2photonIso", &Lep2photonIso, &b_Lep2photonIso);
   fChain->SetBranchAddress("Lep2absIso", &Lep2absIso, &b_Lep2absIso);
   fChain->SetBranchAddress("Lep2relIso", &Lep2relIso, &b_Lep2relIso);
   fChain->SetBranchAddress("Lep3chargedHadIso", &Lep3chargedHadIso, &b_Lep3chargedHadIso);
   fChain->SetBranchAddress("Lep3chargedAllIso", &Lep3chargedAllIso, &b_Lep3chargedAllIso);
   fChain->SetBranchAddress("Lep3PUchargedHadIso", &Lep3PUchargedHadIso, &b_Lep3PUchargedHadIso);
   fChain->SetBranchAddress("Lep3neutralHadIso", &Lep3neutralHadIso, &b_Lep3neutralHadIso);
   fChain->SetBranchAddress("Lep3photonIso", &Lep3photonIso, &b_Lep3photonIso);
   fChain->SetBranchAddress("Lep3absIso", &Lep3absIso, &b_Lep3absIso);
   fChain->SetBranchAddress("Lep3relIso", &Lep3relIso, &b_Lep3relIso);
   fChain->SetBranchAddress("Lep4chargedHadIso", &Lep4chargedHadIso, &b_Lep4chargedHadIso);
   fChain->SetBranchAddress("Lep4chargedAllIso", &Lep4chargedAllIso, &b_Lep4chargedAllIso);
   fChain->SetBranchAddress("Lep4PUchargedHadIso", &Lep4PUchargedHadIso, &b_Lep4PUchargedHadIso);
   fChain->SetBranchAddress("Lep4neutralHadIso", &Lep4neutralHadIso, &b_Lep4neutralHadIso);
   fChain->SetBranchAddress("Lep4photonIso", &Lep4photonIso, &b_Lep4photonIso);
   fChain->SetBranchAddress("Lep4absIso", &Lep4absIso, &b_Lep4absIso);
   fChain->SetBranchAddress("Lep4relIso", &Lep4relIso, &b_Lep4relIso);
   Notify();
}

Bool_t HZZ4lBaseclass::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void HZZ4lBaseclass::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t HZZ4lBaseclass::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef HZZ4lBaseclass_cxx
