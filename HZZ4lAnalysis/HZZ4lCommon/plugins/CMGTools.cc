#include "HZZ4lAnalysis/HZZ4lCommon/plugins/CMGTools.h"
#include "FWCore/Framework/interface/MakerMacros.h"




DEFINE_FWK_MODULE(DiGenParticlePOProducer);

//DiObject producers
DEFINE_FWK_MODULE(EMuPOProducer);

//TriObject producers
DEFINE_FWK_MODULE(DiMuonMuPOProducer);
DEFINE_FWK_MODULE(DiMuonEPOProducer);
DEFINE_FWK_MODULE(DiElectronEPOProducer);
DEFINE_FWK_MODULE(DiElectronMuPOProducer);

//QuadriObject producers
DEFINE_FWK_MODULE(DiMuonDiMuonPOProducer);
DEFINE_FWK_MODULE(DiElectronDiElectronPOProducer);
DEFINE_FWK_MODULE(DiElectronDiMuonPOProducer);
DEFINE_FWK_MODULE(DiMuonEMuPOProducer);
DEFINE_FWK_MODULE(DiElectronEMuPOProducer);
DEFINE_FWK_MODULE(DiGenParticleDiGenParticlePOProducer);

//Higgs Candidate producers
//DEFINE_FWK_MODULE(DiGenParticleDiGenParticleHiggsPOProducer);
DEFINE_FWK_MODULE(DiMuonDiMuonHiggsPOProducer);
DEFINE_FWK_MODULE(DiElectronDiElectronHiggsPOProducer);
DEFINE_FWK_MODULE(DiElectronDiMuonHiggsPOProducer);

