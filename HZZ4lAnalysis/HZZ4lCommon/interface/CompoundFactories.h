#ifndef __HZZ4lAnalysis_HZZ4lCommon_CompoundFactories_h__
#define __HZZ4lAnalysis_HZZ4lCommon_CompoundFactories_h__

#include "CMGTools/Common/interface/DiObjectFactory.h"
#include "HZZ4lAnalysis/DataFormats/interface/CompoundTypesHZZ4l.h"
#include "AnalysisDataFormats/CMGTools/interface/CompoundTypes.h"
//#include "HZZ4lAnalysis/HZZ4lCommon/interface/HiggsCandidateFactory.h"

namespace cmg{
  typedef DiObjectFactory< cmg::DiGenParticle::type1, cmg::DiGenParticle::type2 > DiGenParticleFactory;
  
  typedef DiObjectFactory< cmg::DiMuonDiMuon::type1, cmg::DiMuonDiMuon::type2 > DiMuonDiMuonFactory;
  typedef DiObjectFactory< cmg::DiElectronDiElectron::type1, cmg::DiElectronDiElectron::type2 > DiElectronDiElectronFactory;
  typedef DiObjectFactory< cmg::DiElectronDiMuon::type1, cmg::DiElectronDiMuon::type2 > DiElectronDiMuonFactory;
  typedef DiObjectFactory< cmg::DiGenParticleDiGenParticle::type1, cmg::DiGenParticleDiGenParticle::type2 > DiGenParticleDiGenParticleFactory;

  /* COMMENTED BECAUSE HIGGSCANDIDATEFACTORY CLASS NOT YET IMPLEMENTED
  typedef HiggsCandidateFactory< cmg::DiElectronDiElectron::type1, cmg::DiElectronDiElectron::type2 > DiElectronDiElectronHiggsFactory;
  typedef HiggsCandidateFactory< cmg::DiMuonDiMuon::type1, cmg::DiMuonDiMuon::type2 > DiMuonDiMuonHiggsFactory;
  typedef HiggsCandidateFactory< cmg::DiGenParticleDiGenParticle::type1, cmg::DiGenParticleDiGenParticle::type2 > DiGenParticleDiGenParticleHiggsFactory;
  */  
}


#endif