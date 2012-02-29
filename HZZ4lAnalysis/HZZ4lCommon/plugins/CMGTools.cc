#include "HZZ4lAnalysis/HZZ4lCommon/plugins/CMGTools.h"
#include "FWCore/Framework/interface/MakerMacros.h"




DEFINE_FWK_MODULE(DiGenParticlePOProducer);


DEFINE_FWK_MODULE(DiMuonDiMuonPOProducer);
DEFINE_FWK_MODULE(DiElectronDiElectronPOProducer);
DEFINE_FWK_MODULE(DiElectronDiMuonPOProducer);

DEFINE_FWK_MODULE(DiGenParticleDiGenParticlePOProducer);

/* COMMENTED BECAUSE HIGGSCANDIDATEFACTORY CLASS NOT YET IMPLEMENTED
DEFINE_FWK_MODULE(DiGenParticleDiGenParticleHiggsPOProducer);
DEFINE_FWK_MODULE(DiMuonDiMuonHiggsPOProducer);
DEFINE_FWK_MODULE(DiElectronDiElectronHiggsPOProducer);
*/
