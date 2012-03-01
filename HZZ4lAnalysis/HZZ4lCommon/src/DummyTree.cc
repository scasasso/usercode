#include "HZZ4lAnalysis/HZZ4lCommon/interface/DummyTree.h"

using namespace std;

void DummyTree::resetStruct(){

  //Higgs struct
  evSummary_.Higgs_.pT_l1 = 0; evSummary_.Higgs_.pT_l2 = 0; evSummary_.Higgs_.pT_l3 = 0; evSummary_.Higgs_.pT_l4 = 0;

  //Event Summary
  evSummary_.run = 0; evSummary_.lumi = 0; evSummary_.event = 0; //evSummary_.nvtx = 0;

}

void DummyTree::initTree(TTree *t){

  t_ = t;

  //Branches
  t_->Branch("run", &evSummary_.run, "run/I");
  t_->Branch("lumi", &evSummary_.lumi, "lumi/I");
  t_->Branch("event", &evSummary_.event, "event/I");
  //t_->Branch("nvtx", &evSummary_.nvtx, "nvtx/I");

  t_->Branch("h_pT_l1", &evSummary_.Higgs_.pT_l1, "pT_l1/F");
  t_->Branch("h_pT_l2", &evSummary_.Higgs_.pT_l2, "pT_l2/F");
  t_->Branch("h_pT_l3", &evSummary_.Higgs_.pT_l3, "pT_l3/F");
  t_->Branch("h_pT_l4", &evSummary_.Higgs_.pT_l4, "pT_l4/F");


}

void DummyTree::fillTree(){

  if(t_) t_->Fill();

}
