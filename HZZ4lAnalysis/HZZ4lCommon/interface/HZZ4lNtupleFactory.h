#ifndef HZZ4lNtupleFactory_h
#define HZZ4lNtupleFactory_h

#include <vector>

#include <TString.h>
#include <TFile.h>
#include <TTree.h>

class HZZ4lNtupleFactory{
  
 protected:
  
 public:
  HZZ4lNtupleFactory(TString namefile);
  HZZ4lNtupleFactory(TTree* outTree_input);
  ~HZZ4lNtupleFactory();

  void FillEvent();
  void WriteNtuple();
  void DumpBranches(TString filename) const;

  void createNewCandidate();
  void FillEventInfo(const Int_t RunNumber, const Int_t EventNumber, const Int_t LumiNumber);
  void FillHInfo(const Double_t ZZMass, const Double_t ZZMassErr, const Int_t isBestCandidate, const Double_t ZZPt, const Double_t ZZEta, const Double_t ZZPhi, const Double_t ZZLD, const Int_t ZZType);
  void FillZInfo(const Double_t ZMass, const Double_t ZPt, const Double_t ZEta, const Double_t ZPhi);
  void FillAngularInfo(const Double_t costhetastar, const Double_t helphi, const Double_t helphiZ1, const Double_t helphiZ2, const Double_t helcosthetaZ1, const Double_t helcosthetaZ2, const Double_t phistarZ1, const Double_t phistarZ2);
  void FillLepInfo(const Double_t LepPt, const Double_t LepEta, const Double_t LepPhi, const Int_t LepId, const Double_t SIP);
  void FillLepIsolInfo(const Double_t LepchargedHadIso, const Double_t LepchargedAllIso, const Double_t LepPUchargedHadIso, const Double_t LepneutralHadIso, const Double_t LepphotonIso, const Double_t LepabsIso, const Double_t LeprelIso);

 private:

  TTree* _outTree;
  Bool_t _internalTree;
  
  TFile* _outFile;

  void InitializeBranches();
  void InitializeVariables();

  Bool_t _firstZStored;
  Int_t _LeptonIndex;
  Int_t _LeptonIsoIndex;

  //Event variables
  Int_t _RunNumber;
  Int_t _EventNumber;
  Int_t _LumiNumber;

  Int_t _Nmu;
  Int_t _Nele;

  Int_t _Nvtx;

  //H variables
  std::vector<Double_t> _ZZMass;
  std::vector<Double_t> _ZZMassErr;
  std::vector<Int_t> _isBestCandidate;
  std::vector<Double_t> _ZZPt;
  std::vector<Double_t> _ZZEta;
  std::vector<Double_t> _ZZPhi;
  std::vector<Double_t> _ZZLD;
  std::vector<Int_t> _ZZType;

  //Z1 variables
  std::vector<Double_t> _Z1Mass;
  std::vector<Double_t> _Z1Pt;
  std::vector<Double_t> _Z1Eta;
  std::vector<Double_t> _Z1Phi;

  //Z2 variables
  std::vector<Double_t> _Z2Mass;
  std::vector<Double_t> _Z2Pt;
  std::vector<Double_t> _Z2Eta;
  std::vector<Double_t> _Z2Phi;

  //Angular variables
  std::vector<Double_t> _costhetastar;
  std::vector<Double_t> _helphi;
  std::vector<Double_t> _helphiZ1;
  std::vector<Double_t> _helphiZ2;
  std::vector<Double_t> _helcosthetaZ1;
  std::vector<Double_t> _helcosthetaZ2;
  std::vector<Double_t> _phistarZ1;
  std::vector<Double_t> _phistarZ2;

  //Lepton variables
  std::vector<Double_t> _Lep1Pt;
  std::vector<Double_t> _Lep1Eta;
  std::vector<Double_t> _Lep1Phi;
  std::vector<Int_t>   _Lep1LepId;
  std::vector<Double_t> _Lep1SIP;

  std::vector<Double_t> _Lep2Pt;
  std::vector<Double_t> _Lep2Eta;
  std::vector<Double_t> _Lep2Phi;
  std::vector<Int_t>   _Lep2LepId;
  std::vector<Double_t> _Lep2SIP;

  std::vector<Double_t> _Lep3Pt;
  std::vector<Double_t> _Lep3Eta;
  std::vector<Double_t> _Lep3Phi;
  std::vector<Int_t>   _Lep3LepId;
  std::vector<Double_t> _Lep3SIP;

  std::vector<Double_t> _Lep4Pt;
  std::vector<Double_t> _Lep4Eta;
  std::vector<Double_t> _Lep4Phi;
  std::vector<Int_t>   _Lep4LepId;
  std::vector<Double_t> _Lep4SIP;

  //Lepton isolation variables
  std::vector<Double_t> _Lep1chargedHadIso;
  std::vector<Double_t> _Lep1chargedAllIso;
  std::vector<Double_t> _Lep1PUchargedHadIso;
  std::vector<Double_t> _Lep1neutralHadIso;
  std::vector<Double_t> _Lep1photonIso;
  std::vector<Double_t> _Lep1absIso;
  std::vector<Double_t> _Lep1relIso;

  std::vector<Double_t> _Lep2chargedHadIso;
  std::vector<Double_t> _Lep2chargedAllIso;
  std::vector<Double_t> _Lep2PUchargedHadIso;
  std::vector<Double_t> _Lep2neutralHadIso;
  std::vector<Double_t> _Lep2photonIso;
  std::vector<Double_t> _Lep2absIso;
  std::vector<Double_t> _Lep2relIso;

  std::vector<Double_t> _Lep3chargedHadIso;
  std::vector<Double_t> _Lep3chargedAllIso;
  std::vector<Double_t> _Lep3PUchargedHadIso;
  std::vector<Double_t> _Lep3neutralHadIso;
  std::vector<Double_t> _Lep3photonIso;
  std::vector<Double_t> _Lep3absIso;
  std::vector<Double_t> _Lep3relIso;

  std::vector<Double_t> _Lep4chargedHadIso;
  std::vector<Double_t> _Lep4chargedAllIso;
  std::vector<Double_t> _Lep4PUchargedHadIso;
  std::vector<Double_t> _Lep4neutralHadIso;
  std::vector<Double_t> _Lep4photonIso;
  std::vector<Double_t> _Lep4absIso;
  std::vector<Double_t> _Lep4relIso;

};

#endif
