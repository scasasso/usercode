#ifndef __HZZ4lAnalysis_HZZ4lCommon_CMGTools_h__
#define __HZZ4lAnalysis_HZZ4lCommon_CMGTools_h__


#include "HZZ4lAnalysis/HZZ4lCommon/interface/CompoundFactories.h"
#include "CMGTools/Common/plugins/PhysicsObjectProducer.h"


typedef PhysicsObjectProducer<cmg::DiGenParticleFactory> DiGenParticlePOProducer;

typedef PhysicsObjectProducer<cmg::EMuFactory> EMuPOProducer;

typedef PhysicsObjectProducer<cmg::DiMuonDiMuonFactory> DiMuonDiMuonPOProducer;
typedef PhysicsObjectProducer<cmg::DiElectronDiElectronFactory> DiElectronDiElectronPOProducer;
typedef PhysicsObjectProducer<cmg::DiElectronDiMuonFactory> DiElectronDiMuonPOProducer;
typedef PhysicsObjectProducer<cmg::DiGenParticleDiGenParticleFactory> DiGenParticleDiGenParticlePOProducer;

//typedef PhysicsObjectProducer<cmg::DiGenParticleDiGenParticleHiggsFactory> DiGenParticleDiGenParticleHiggsPOProducer;

typedef PhysicsObjectProducer<cmg::DiMuonDiMuonHiggsFactory> DiMuonDiMuonHiggsPOProducer;
typedef PhysicsObjectProducer<cmg::DiElectronDiElectronHiggsFactory> DiElectronDiElectronHiggsPOProducer;
typedef PhysicsObjectProducer<cmg::DiElectronDiMuonHiggsFactory> DiElectronDiMuonHiggsPOProducer;


#endif
