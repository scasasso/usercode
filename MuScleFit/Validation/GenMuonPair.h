#ifndef GenMuonPair_h
#define GenMuonPair_h

#include "TObject.h"
#include "Muon.h"


class GenMuonPair : public TObject
{
public:
  GenMuonPair() :
    mu1(lorentzVector(0,0,0,0),-1),
    mu2(lorentzVector(0,0,0,0),1),
    motherId(0)//,
    //    statusMu(-1),
  {}

  GenMuonPair(const MuScleFitMuon & initMu1, const MuScleFitMuon & initMu2,
	      const int initMotherId) :
    mu1(initMu1),
    mu2(initMu2),
    motherId(initMotherId)
  {
  }

  /// Used to copy the content of another GenMuonPair
  void copy(const GenMuonPair & copyPair)
  {
    mu1 = copyPair.mu1;
    mu2 = copyPair.mu2;
    motherId = copyPair.motherId;
  }

  MuScleFitMuon mu1;
  MuScleFitMuon mu2;
  Int_t motherId;

  ClassDef(GenMuonPair, 3)
    };
#if !defined(__CINT__) || defined(__MAKECINT__) 
ClassImp(GenMuonPair)
#endif  

#endif
