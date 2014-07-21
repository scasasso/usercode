#ifndef MuonPair_h
#define MuonPair_h

#include "TObject.h"
#include "Muon.h"


class MuonPair : public TObject
{
public:
  MuonPair() :
    mu1(lorentzVector(0,0,0,0),-1),
    mu2(lorentzVector(0,0,0,0),1),
    run(0),
    event(0)
      {}
    
    MuonPair(const MuScleFitMuon & initMu1, const MuScleFitMuon & initMu2, const UInt_t & initRun=0,  const UInt_t & initEvent=0) :
      mu1(initMu1),
      mu2(initMu2),
      run(initRun),
      event(initEvent)
	{}

      
      /// Used to copy the content of another MuonPair
      void copy(const MuonPair & copyPair)
      {
	mu1 = copyPair.mu1;
	mu2 = copyPair.mu2;
	run= copyPair.run;
	event= copyPair.event;
      }
      
      MuScleFitMuon mu1;
      MuScleFitMuon mu2;
      UInt_t run;
      UInt_t event;
      
      ClassDef(MuonPair, 3)
	};
#if !defined(__CINT__) || defined(__MAKECINT__) 
ClassImp(MuonPair)
#endif

#endif
