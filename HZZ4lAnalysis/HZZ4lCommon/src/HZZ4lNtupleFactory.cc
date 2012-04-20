#include <cassert>
#include <iostream>

#include "HZZ4lAnalysis/HZZ4lCommon/interface/HZZ4lNtupleFactory.h"

///--- Constructor ---
HZZ4lNtupleFactory::HZZ4lNtupleFactory(TString fileName)
{
  //---- create output tree ----
  _internalTree = true;
  _outFile = new TFile(fileName,"RECREATE");
  _outTree = new TTree("SimpleTree","SimpleTree");
  InitializeVariables();
  InitializeBranches();
}

HZZ4lNtupleFactory::HZZ4lNtupleFactory(TTree* outTree_input)
{
  //---- create output tree ----
  _internalTree = false;
  _outTree = outTree_input;
  InitializeVariables();
  InitializeBranches();
}

///--- Destructor ---
HZZ4lNtupleFactory::~HZZ4lNtupleFactory()
{
  //---- destroy everything ----
  if(_internalTree){
    delete _outTree;
    delete _outFile;
  }
}

///---- Write an event to TTree ----
void HZZ4lNtupleFactory::FillEvent()
{
  _outTree->Fill();

  //H variables
  _ZZMass.clear();
  _ZZMassErr.clear();
  _isBestCandidate.clear();
  _ZZPt.clear();
  _ZZEta.clear();
  _ZZPhi.clear();
  _ZZLD.clear();
  _ZZType.clear();

  //Z1 variables
  _Z1Mass.clear();
  _Z1Pt.clear();
  _Z1Eta.clear();
  _Z1Phi.clear();

  //Z2 variables
  _Z2Mass.clear();
  _Z2Pt.clear();
  _Z2Eta.clear();
  _Z2Phi.clear();

  //Angular variables
  _costhetastar.clear();
  _helphi.clear();
  _helphiZ1.clear();
  _helphiZ2.clear();
  _helcosthetaZ1.clear();
  _helcosthetaZ2.clear();
  _phistarZ1.clear();
  _phistarZ2.clear();

  //Lepton variables
  _Lep1Pt.clear();
  _Lep1Eta.clear();
  _Lep1Phi.clear();
  _Lep1LepId.clear();
  _Lep1SIP.clear();

  _Lep2Pt.clear();
  _Lep2Eta.clear();
  _Lep2Phi.clear();
  _Lep2LepId.clear();
  _Lep2SIP.clear();

  _Lep3Pt.clear();
  _Lep3Eta.clear();
  _Lep3Phi.clear();
  _Lep3LepId.clear();
  _Lep3SIP.clear();

  _Lep4Pt.clear();
  _Lep4Eta.clear();
  _Lep4Phi.clear();
  _Lep4LepId.clear();
  _Lep4SIP.clear();

  //Lepton isolation variables
  _Lep1chargedHadIso.clear();
  _Lep1chargedAllIso.clear();
  _Lep1PUchargedHadIso.clear();
  _Lep1neutralHadIso.clear();
  _Lep1photonIso.clear();
  _Lep1absIso.clear();
  _Lep1relIso.clear();

  _Lep2chargedHadIso.clear();
  _Lep2chargedAllIso.clear();
  _Lep2PUchargedHadIso.clear();
  _Lep2neutralHadIso.clear();
  _Lep2photonIso.clear();
  _Lep2absIso.clear();
  _Lep2relIso.clear();

  _Lep3chargedHadIso.clear();
  _Lep3chargedAllIso.clear();
  _Lep3PUchargedHadIso.clear();
  _Lep3neutralHadIso.clear();
  _Lep3photonIso.clear();
  _Lep3absIso.clear();
  _Lep3relIso.clear();

  _Lep4chargedHadIso.clear();
  _Lep4chargedAllIso.clear();
  _Lep4PUchargedHadIso.clear();
  _Lep4neutralHadIso.clear();
  _Lep4photonIso.clear();
  _Lep4absIso.clear();
  _Lep4relIso.clear();

  return;
}

///---- Write collection to file ----
void HZZ4lNtupleFactory::WriteNtuple()
{

  //---- if using TFileService, not use this
  if(_internalTree) _outFile->Write();
  else std::cerr << "Service not available: using TFileService" << std::endl ;
  return;
}

///---- Write to a text file branches declaration ----
void HZZ4lNtupleFactory::DumpBranches(TString filename) const
{
  //----- symply use MakeClass
  _outTree->MakeClass(filename);
  return;
}

void HZZ4lNtupleFactory::InitializeVariables()
{
  //Event variables
  _RunNumber = 0;
  _EventNumber = 0;
  _LumiNumber = 0;

  _Nmu = 0;
  _Nele = 0;

  _Nvtx = 0;

  return;
}

void HZZ4lNtupleFactory::InitializeBranches()
{
  //Event variables
  _outTree->Branch("RunNumber",&_RunNumber,"RunNumber/I");
  _outTree->Branch("EventNumber",&_EventNumber,"EventNumber/I");
  _outTree->Branch("LumiNumber",&_LumiNumber,"LumiNumber/I");
  _outTree->Branch("Nmu",&_Nmu,"Nmu/I");
  _outTree->Branch("Nele",&_Nele,"Nele/I");
  _outTree->Branch("Nvtx",&_Nvtx,"Nvtx/I");

  //H variables
  _outTree->Branch("ZZMass",&_ZZMass);
  _outTree->Branch("ZZMassErr",&_ZZMassErr);
  _outTree->Branch("isBestCandidate",&_isBestCandidate);
  _outTree->Branch("ZZPt",&_ZZPt);
  _outTree->Branch("ZZEta",&_ZZEta);
  _outTree->Branch("ZZPhi",&_ZZPhi);
  _outTree->Branch("ZZLD",&_ZZLD);
  _outTree->Branch("ZZType",&_ZZType);

  //Z1 variables
  _outTree->Branch("Z1Mass",&_Z1Mass);
  _outTree->Branch("Z1Pt",&_Z1Pt);
  _outTree->Branch("Z1Eta",&_Z1Eta);
  _outTree->Branch("Z1Phi",&_Z1Phi);

  //Z2 variables
  _outTree->Branch("Z2Mass",&_Z2Mass);
  _outTree->Branch("Z2Pt",&_Z2Pt);
  _outTree->Branch("Z2Eta",&_Z2Eta);
  _outTree->Branch("Z2Phi",&_Z2Phi);

  //Angular variables
  _outTree->Branch("costhetastar",&_costhetastar);
  _outTree->Branch("helphi",&_helphi);
  _outTree->Branch("helphiZ1",&_helphiZ1);
  _outTree->Branch("helphiZ2",&_helphiZ2);
  _outTree->Branch("helcosthetaZ1",&_helcosthetaZ1);
  _outTree->Branch("helcosthetaZ2",&_helcosthetaZ2);
  _outTree->Branch("phistarZ1",&_phistarZ1);
  _outTree->Branch("phistarZ2",&_phistarZ2);

  //Lepton variables
  _outTree->Branch("Lep1Pt",&_Lep1Pt);
  _outTree->Branch("Lep1Eta",&_Lep1Eta);
  _outTree->Branch("Lep1Phi",&_Lep1Phi);
  _outTree->Branch("Lep1LepId",&_Lep1LepId);
  _outTree->Branch("Lep1SIP",&_Lep1SIP);

  _outTree->Branch("Lep2Pt",&_Lep2Pt);
  _outTree->Branch("Lep2Eta",&_Lep2Eta);
  _outTree->Branch("Lep2Phi",&_Lep2Phi);
  _outTree->Branch("Lep2LepId",&_Lep2LepId);
  _outTree->Branch("Lep2SIP",&_Lep2SIP);

  _outTree->Branch("Lep3Pt",&_Lep3Pt);
  _outTree->Branch("Lep3Eta",&_Lep3Eta);
  _outTree->Branch("Lep3Phi",&_Lep3Phi);
  _outTree->Branch("Lep3LepId",&_Lep3LepId);
  _outTree->Branch("Lep3SIP",&_Lep3SIP);

  _outTree->Branch("Lep4Pt",&_Lep4Pt);
  _outTree->Branch("Lep4Eta",&_Lep4Eta);
  _outTree->Branch("Lep4Phi",&_Lep4Phi);
  _outTree->Branch("Lep4LepId",&_Lep4LepId);
  _outTree->Branch("Lep4SIP",&_Lep4SIP);

  //Lepton isolation variables
  _outTree->Branch("Lep1chargedHadIso",&_Lep1chargedHadIso);
  _outTree->Branch("Lep1chargedAllIso",&_Lep1chargedAllIso);
  _outTree->Branch("Lep1PUchargedHadIso",&_Lep1PUchargedHadIso);
  _outTree->Branch("Lep1neutralHadIso",&_Lep1neutralHadIso);
  _outTree->Branch("Lep1photonIso",&_Lep1photonIso);
  _outTree->Branch("Lep1absIso",&_Lep1absIso);
  _outTree->Branch("Lep1relIso",&_Lep1relIso);

  _outTree->Branch("Lep2chargedHadIso",&_Lep2chargedHadIso);
  _outTree->Branch("Lep2chargedAllIso",&_Lep2chargedAllIso);
  _outTree->Branch("Lep2PUchargedHadIso",&_Lep2PUchargedHadIso);
  _outTree->Branch("Lep2neutralHadIso",&_Lep2neutralHadIso);
  _outTree->Branch("Lep2photonIso",&_Lep2photonIso);
  _outTree->Branch("Lep2absIso",&_Lep2absIso);
  _outTree->Branch("Lep2relIso",&_Lep2relIso);

  _outTree->Branch("Lep3chargedHadIso",&_Lep3chargedHadIso);
  _outTree->Branch("Lep3chargedAllIso",&_Lep3chargedAllIso);
  _outTree->Branch("Lep3PUchargedHadIso",&_Lep3PUchargedHadIso);
  _outTree->Branch("Lep3neutralHadIso",&_Lep3neutralHadIso);
  _outTree->Branch("Lep3photonIso",&_Lep3photonIso);
  _outTree->Branch("Lep3absIso",&_Lep3absIso);
  _outTree->Branch("Lep3relIso",&_Lep3relIso);

  _outTree->Branch("Lep4chargedHadIso",&_Lep4chargedHadIso);
  _outTree->Branch("Lep4chargedAllIso",&_Lep4chargedAllIso);
  _outTree->Branch("Lep4PUchargedHadIso",&_Lep4PUchargedHadIso);
  _outTree->Branch("Lep4neutralHadIso",&_Lep4neutralHadIso);
  _outTree->Branch("Lep4photonIso",&_Lep4photonIso);
  _outTree->Branch("Lep4absIso",&_Lep4absIso);
  _outTree->Branch("Lep4relIso",&_Lep4relIso);
  return;
}

void HZZ4lNtupleFactory::createNewCandidate()
{
  _firstZStored = false;
  _LeptonIndex = 1;
  _LeptonIsoIndex = 1;
  return;
}

void HZZ4lNtupleFactory::FillEventInfo(const Int_t RunNumber, const Int_t EventNumber, const Int_t LumiNumber)
{
  _RunNumber = RunNumber;
  _EventNumber = EventNumber;
  _LumiNumber = LumiNumber;

  return;
}


void HZZ4lNtupleFactory::FillHInfo(const Double_t ZZMass, const Double_t ZZMassErr, const Int_t isBestCandidate, const Double_t ZZPt, const Double_t ZZEta, const Double_t ZZPhi, const Double_t ZZLD, const Int_t ZZType)
{
  _ZZMass.push_back(ZZMass);
  _ZZMassErr.push_back(ZZMassErr);
  _isBestCandidate.push_back(isBestCandidate);
  _ZZPt.push_back(ZZPt);
  _ZZEta.push_back(ZZEta);
  _ZZPhi.push_back(ZZPhi);
  _ZZLD.push_back(ZZLD);
  _ZZType.push_back(ZZType);

  return;
}

void HZZ4lNtupleFactory::FillZInfo(const Double_t ZMass, const Double_t ZPt, const Double_t ZEta, const Double_t ZPhi)
{
  if(!_firstZStored){
    _Z1Mass.push_back(ZMass);
    _Z1Pt.push_back(ZPt);
    _Z1Eta.push_back(ZEta);
    _Z1Phi.push_back(ZPhi);
    _firstZStored = true;
  }
  else{
    _Z2Mass.push_back(ZMass);
    _Z2Pt.push_back(ZPt);
    _Z2Eta.push_back(ZEta);
    _Z2Phi.push_back(ZPhi);
  }

  return;
}

void HZZ4lNtupleFactory::FillAngularInfo(const Double_t costhetastar, const Double_t helphi, const Double_t helphiZ1, const Double_t helphiZ2, const Double_t helcosthetaZ1, const Double_t helcosthetaZ2, const Double_t phistarZ1, const Double_t phistarZ2)
{
  _costhetastar.push_back(costhetastar);
  _helphi.push_back(helphi);
  _helphiZ1.push_back(helphiZ1);
  _helphiZ2.push_back(helphiZ2);
  _helcosthetaZ1.push_back(helcosthetaZ1);
  _helcosthetaZ2.push_back(helcosthetaZ2);
  _phistarZ1.push_back(phistarZ1);
  _phistarZ2.push_back(phistarZ2);

  return;
}

void HZZ4lNtupleFactory::FillLepInfo(const Double_t LepPt, const Double_t LepEta, const Double_t LepPhi, const Int_t LepId, const Double_t LepSIP)
{
  switch(_LeptonIndex){

  case 1:
    _Lep1Pt.push_back(LepPt);
    _Lep1Eta.push_back(LepEta);
    _Lep1Phi.push_back(LepPhi);
    _Lep1LepId.push_back(LepId);
    _Lep1SIP.push_back(LepSIP);
    break;

  case 2:
    _Lep2Pt.push_back(LepPt);
    _Lep2Eta.push_back(LepEta);
    _Lep2Phi.push_back(LepPhi);
    _Lep2LepId.push_back(LepId);
    _Lep2SIP.push_back(LepSIP);
    break;
  
  case 3:
    _Lep3Pt.push_back(LepPt);
    _Lep3Eta.push_back(LepEta);
    _Lep3Phi.push_back(LepPhi);
    _Lep3LepId.push_back(LepId);
    _Lep3SIP.push_back(LepSIP);
    break;

  case 4:
    _Lep4Pt.push_back(LepPt);
    _Lep4Eta.push_back(LepEta);
    _Lep4Phi.push_back(LepPhi);
    _Lep4LepId.push_back(LepId);
    _Lep4SIP.push_back(LepSIP);
    break;

  default:
    std::cout << "Error in indexing the muons! Will abort..." << std::endl;
    assert(0);
  }

  _LeptonIndex++;

  return;
}

void HZZ4lNtupleFactory::FillLepIsolInfo(const Double_t LepchargedHadIso, const Double_t LepchargedAllIso, const Double_t LepPUchargedHadIso, const Double_t LepneutralHadIso, const Double_t LepphotonIso, const Double_t LepabsIso, const Double_t LeprelIso)
{

  switch(_LeptonIsoIndex){

  case 1:
    _Lep1chargedHadIso.push_back(LepchargedHadIso);
    _Lep1chargedAllIso.push_back(LepchargedAllIso);
    _Lep1PUchargedHadIso.push_back(LepPUchargedHadIso);
    _Lep1neutralHadIso.push_back(LepneutralHadIso);
    _Lep1photonIso.push_back(LepphotonIso);
    _Lep1absIso.push_back(LepabsIso);
    _Lep1relIso.push_back(LeprelIso);
    break;

  case 2:
    _Lep2chargedHadIso.push_back(LepchargedHadIso);
    _Lep2chargedAllIso.push_back(LepchargedAllIso);
    _Lep2PUchargedHadIso.push_back(LepPUchargedHadIso);
    _Lep2neutralHadIso.push_back(LepneutralHadIso);
    _Lep2photonIso.push_back(LepphotonIso);
    _Lep2absIso.push_back(LepabsIso);
    _Lep2relIso.push_back(LeprelIso);
    break;
  
  case 3:
    _Lep3chargedHadIso.push_back(LepchargedHadIso);
    _Lep3chargedAllIso.push_back(LepchargedAllIso);
    _Lep3PUchargedHadIso.push_back(LepPUchargedHadIso);
    _Lep3neutralHadIso.push_back(LepneutralHadIso);
    _Lep3photonIso.push_back(LepphotonIso);
    _Lep3absIso.push_back(LepabsIso);
    _Lep3relIso.push_back(LeprelIso);
    break;

  case 4:
    _Lep4chargedHadIso.push_back(LepchargedHadIso);
    _Lep4chargedAllIso.push_back(LepchargedAllIso);
    _Lep4PUchargedHadIso.push_back(LepPUchargedHadIso);
    _Lep4neutralHadIso.push_back(LepneutralHadIso);
    _Lep4photonIso.push_back(LepphotonIso);
    _Lep4absIso.push_back(LepabsIso);
    _Lep4relIso.push_back(LeprelIso);
    break;

  default:
    std::cout << "Error in indexing the muon isolation variables! Will abort..." << std::endl;
    assert(0);
  }

  _LeptonIsoIndex++;

  return;
}






