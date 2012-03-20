#ifndef __HZZ4lAnalysis_HZZ4lCommon_CMGTools_h__
#define __HZZ4lAnalysis_HZZ4lCommon_CMGTools_h__


#include "HZZ4lAnalysis/HZZ4lCommon/interface/CompoundFactories.h"
#include "CMGTools/Common/plugins/PhysicsObjectProducer.h"


typedef PhysicsObjectProducer<cmg::DiGenParticleFactory> DiGenParticlePOProducer;

//DiObject producers
typedef PhysicsObjectProducer<cmg::EMuFactory> EMuPOProducer;

//TriObject producers
typedef PhysicsObjectProducer<cmg::DiMuonMuFactory> DiMuonMuPOProducer;
typedef PhysicsObjectProducer<cmg::DiMuonEFactory> DiMuonEPOProducer;
typedef PhysicsObjectProducer<cmg::DiElectronEFactory> DiElectronEPOProducer;
typedef PhysicsObjectProducer<cmg::DiElectronMuFactory> DiElectronMuPOProducer;

//QuadriObject producers
typedef PhysicsObjectProducer<cmg::DiMuonDiMuonFactory> DiMuonDiMuonPOProducer;
typedef PhysicsObjectProducer<cmg::DiElectronDiElectronFactory> DiElectronDiElectronPOProducer;
typedef PhysicsObjectProducer<cmg::DiElectronDiMuonFactory> DiElectronDiMuonPOProducer;
typedef PhysicsObjectProducer<cmg::DiMuonEMuFactory> DiMuonEMuPOProducer;
typedef PhysicsObjectProducer<cmg::DiElectronEMuFactory> DiElectronEMuPOProducer;
typedef PhysicsObjectProducer<cmg::DiGenParticleDiGenParticleFactory> DiGenParticleDiGenParticlePOProducer;

//Higgs Candidate producers
//typedef PhysicsObjectProducer<cmg::DiGenParticleDiGenParticleHiggsFactory> DiGenParticleDiGenParticleHiggsPOProducer;
typedef PhysicsObjectProducer<cmg::DiMuonDiMuonHiggsFactory> DiMuonDiMuonHiggsPOProducer;
typedef PhysicsObjectProducer<cmg::DiElectronDiElectronHiggsFactory> DiElectronDiElectronHiggsPOProducer;
typedef PhysicsObjectProducer<cmg::DiElectronDiMuonHiggsFactory> DiElectronDiMuonHiggsPOProducer;


#endif
