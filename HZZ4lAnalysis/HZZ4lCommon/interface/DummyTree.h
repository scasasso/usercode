#ifndef dummytree_h
#define dummytree_h

#if !defined(__CINT__) || defined(__MAKECINT__)

#include <string.h>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <set>
#include <cmath>

#include "TTree.h"

#endif

struct HiggsCandidate {

  Float_t pT_l1, pT_l2, pT_l3, pT_l4;

};

struct HZZ4lSummary {

  Int_t run,lumi,event;
  //Int_t nvtx;

  //Higgs Candidates
  HiggsCandidate Higgs_;

  HiggsCandidate &getHiggs() { return Higgs_; }

};

class DummyTree {

 public:
  //Constructor / Destructor
  DummyTree(){};
  ~DummyTree(){};

  //HZZ4lSummary
  HZZ4lSummary evSummary_;

  HZZ4lSummary &getEvent() { return evSummary_; }

  void resetStruct();
  void initTree(TTree *t);
  void fillTree();

 private:
  TTree * t_;  
  
};

#endif
