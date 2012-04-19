#include "AnalysisDataFormats/CMGTools/interface/CompoundTypes.h"
#include "HZZ4lAnalysis/DataFormats/interface/CompoundTypesHZZ4l.h"
#include "HZZ4lAnalysis/HZZ4lCommon/plugins/LDProducer.h"
#include "HZZ4lAnalysis/HZZ4lCommon/plugins/BestCandProducer.h"

#include "CommonTools/UtilAlgos/interface/ObjectSelector.h"
#include "CMGTools/Common/interface/GenericPhysicsObjectSelectorDefinition.h"
#include "CommonTools/UtilAlgos/interface/SingleObjectSelector.h"
#include "CommonTools/UtilAlgos/interface/StringCutObjectSelector.h"
#include "CommonTools/UtilAlgos/interface/Merger.h"


#include "FWCore/Framework/interface/MakerMacros.h"


typedef LDProducer<cmg::DiElectronDiElectronHiggs> DiElectronDiElectronHiggsLDProducer;
typedef LDProducer<cmg::DiElectronDiMuonHiggs> DiElectronDiMuonHiggsLDProducer;
typedef LDProducer<cmg::DiMuonDiMuonHiggs> DiMuonDiMuonHiggsLDProducer;
DEFINE_FWK_MODULE(DiElectronDiElectronHiggsLDProducer);
DEFINE_FWK_MODULE(DiElectronDiMuonHiggsLDProducer);
DEFINE_FWK_MODULE(DiMuonDiMuonHiggsLDProducer);

typedef BestCandProducer<cmg::DiElectronDiElectronHiggs> DiElectronDiElectronHiggsBestCandProducer;
typedef BestCandProducer<cmg::DiElectronDiMuonHiggs> DiElectronDiMuonHiggsBestCandProducer;
typedef BestCandProducer<cmg::DiMuonDiMuonHiggs> DiMuonDiMuonHiggsBestCandProducer;
DEFINE_FWK_MODULE(DiElectronDiElectronHiggsBestCandProducer);
DEFINE_FWK_MODULE(DiElectronDiMuonHiggsBestCandProducer);
DEFINE_FWK_MODULE(DiMuonDiMuonHiggsBestCandProducer);

typedef ObjectSelector<cmg::GenericPhysicsObjectSelectorDefinition<cmg::DiElectronDiElectron> > DiElectronDiElectronSelector;
typedef ObjectSelector<cmg::GenericPhysicsObjectSelectorDefinition<cmg::DiMuonDiMuon> > DiMuonDiMuonSelector;
typedef ObjectSelector<cmg::GenericPhysicsObjectSelectorDefinition<cmg::DiElectronDiMuon> > DiElectronDiMuonSelector;
DEFINE_FWK_MODULE(DiElectronDiElectronSelector);
DEFINE_FWK_MODULE(DiMuonDiMuonSelector);
DEFINE_FWK_MODULE(DiElectronDiMuonSelector);
