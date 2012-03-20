#ifndef COMPOUNDTYPESHZZ4L_H_
#define COMPOUNDTYPESHZZ4L_H_

#include "AnalysisDataFormats/CMGTools/interface/BaseJet.h"
#include "AnalysisDataFormats/CMGTools/interface/DiObject.h"
#include "AnalysisDataFormats/CMGTools/interface/Electron.h"
#include "AnalysisDataFormats/CMGTools/interface/Muon.h"
#include "AnalysisDataFormats/CMGTools/interface/PFJet.h"
#include "AnalysisDataFormats/CMGTools/interface/CompoundTypes.h"

#include "AnalysisDataFormats/CMGTools/interface/GenericTypes.h"

#include "HZZ4lAnalysis/DataFormats/interface/HiggsCandidate.h"


namespace cmg{

  typedef cmg::DiObject<cmg::GenParticle,cmg::GenParticle> DiGenParticle;

  //Di Objects
  typedef cmg::DiObject<cmg::Electron,cmg::Muon> EMu;
    
  //Tri Objects
  typedef cmg::DiObject<cmg::DiMuon,cmg::Muon> DiMuonMu;
  typedef cmg::DiObject<cmg::DiMuon,cmg::Electron> DiMuonE;
  typedef cmg::DiObject<cmg::DiElectron,cmg::Electron> DiElectronE;
  typedef cmg::DiObject<cmg::DiElectron,cmg::Muon> DiElectronMu;

  //Quadri Objects
  typedef cmg::DiObject<cmg::DiMuon,cmg::DiMuon> DiMuonDiMuon;
  typedef cmg::DiObject<cmg::DiElectron,cmg::DiElectron> DiElectronDiElectron;
  typedef cmg::DiObject<cmg::DiElectron,cmg::DiMuon> DiElectronDiMuon;
  typedef cmg::DiObject<cmg::DiMuon,cmg::EMu> DiMuonEMu;
  typedef cmg::DiObject<cmg::DiElectron,cmg::EMu> DiElectronEMu;
  typedef cmg::DiObject<cmg::DiGenParticle,cmg::DiGenParticle> DiGenParticleDiGenParticle;

  //Higgs Candidates
  //typedef cmg::HiggsCandidate<cmg::DiGenParticle,cmg::DiGenParticle> DiGenParticleDiGenParticleHiggs;
  typedef cmg::HiggsCandidate<cmg::DiMuon,cmg::DiMuon> DiMuonDiMuonHiggs;
  typedef cmg::HiggsCandidate<cmg::DiElectron,cmg::DiElectron> DiElectronDiElectronHiggs;
  typedef cmg::HiggsCandidate<cmg::DiElectron,cmg::DiMuon> DiElectronDiMuonHiggs;


}

#endif /*COMPOUNDTYPESHZZ4L_H_*/
