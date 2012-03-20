#ifndef __HZZ4lAnalysis_HZZ4lCommon_CompoundFactories_h__
#define __HZZ4lAnalysis_HZZ4lCommon_CompoundFactories_h__

#include "CMGTools/Common/interface/DiObjectFactory.h"
#include "HZZ4lAnalysis/DataFormats/interface/CompoundTypesHZZ4l.h"
#include "AnalysisDataFormats/CMGTools/interface/CompoundTypes.h"
#include "HZZ4lAnalysis/HZZ4lCommon/interface/HiggsCandidateFactory.h"

namespace cmg{
  typedef DiObjectFactory< cmg::DiGenParticle::type1, cmg::DiGenParticle::type2 > DiGenParticleFactory;

  //DiObject factories
  typedef DiObjectFactory< cmg::EMu::type1, cmg::EMu::type2 > EMuFactory;

  //TriObject factories
  typedef DiObjectFactory< cmg::DiMuonMu::type1, cmg::DiMuonMu::type2 > DiMuonMuFactory;
  typedef DiObjectFactory< cmg::DiMuonE::type1, cmg::DiMuonE::type2 > DiMuonEFactory;
  typedef DiObjectFactory< cmg::DiElectronE::type1, cmg::DiElectronE::type2 > DiElectronEFactory;
  typedef DiObjectFactory< cmg::DiElectronMu::type1, cmg::DiElectronMu::type2 > DiElectronMuFactory;

  //QuadriObject factories  
  typedef DiObjectFactory< cmg::DiMuonDiMuon::type1, cmg::DiMuonDiMuon::type2 > DiMuonDiMuonFactory;
  typedef DiObjectFactory< cmg::DiElectronDiElectron::type1, cmg::DiElectronDiElectron::type2 > DiElectronDiElectronFactory;
  typedef DiObjectFactory< cmg::DiElectronDiMuon::type1, cmg::DiElectronDiMuon::type2 > DiElectronDiMuonFactory;
  typedef DiObjectFactory< cmg::DiMuonEMu::type1, cmg::DiMuonEMu::type2 > DiMuonEMuFactory;
  typedef DiObjectFactory< cmg::DiElectronEMu::type1, cmg::DiElectronEMu::type2 > DiElectronEMuFactory;
  typedef DiObjectFactory< cmg::DiGenParticleDiGenParticle::type1, cmg::DiGenParticleDiGenParticle::type2 > DiGenParticleDiGenParticleFactory;

  //Higgs Candidate factories
  //typedef HiggsCandidateFactory< cmg::DiGenParticleDiGenParticle::type1, cmg::DiGenParticleDiGenParticle::type2 > DiGenParticleDiGenParticleHiggsFactory;
  typedef HiggsCandidateFactory< cmg::DiElectronDiMuon::type1, cmg::DiElectronDiMuon::type2 > DiElectronDiMuonHiggsFactory;
  typedef HiggsCandidateFactory< cmg::DiMuonDiMuon::type1, cmg::DiMuonDiMuon::type2 > DiMuonDiMuonHiggsFactory;
  typedef HiggsCandidateFactory< cmg::DiElectronDiElectron::type1, cmg::DiElectronDiElectron::type2 > DiElectronDiElectronHiggsFactory;

}


#endif
