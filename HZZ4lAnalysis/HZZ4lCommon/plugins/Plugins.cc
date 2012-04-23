#include "AnalysisDataFormats/CMGTools/interface/CompoundTypes.h"
#include "HZZ4lAnalysis/DataFormats/interface/CompoundTypesHZZ4l.h"
#include "HZZ4lAnalysis/HZZ4lCommon/plugins/LDProducer.h"
#include "HZZ4lAnalysis/HZZ4lCommon/plugins/BestCandProducer.h"
#include "HZZ4lAnalysis/HZZ4lCommon/plugins/BestZProducer.h"

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

typedef ObjectSelector<cmg::GenericPhysicsObjectSelectorDefinition<cmg::DiElectronDiElectron> > DiElectronDiElectronSelector;
typedef ObjectSelector<cmg::GenericPhysicsObjectSelectorDefinition<cmg::DiMuonDiMuon> > DiMuonDiMuonSelector;
typedef ObjectSelector<cmg::GenericPhysicsObjectSelectorDefinition<cmg::DiElectronDiMuon> > DiElectronDiMuonSelector;
typedef ObjectSelector<cmg::GenericPhysicsObjectSelectorDefinition<cmg::DiElectronEMu> > DiElectronEMuSelector;
typedef ObjectSelector<cmg::GenericPhysicsObjectSelectorDefinition<cmg::DiMuonEMu> > DiMuonEMuSelector;
DEFINE_FWK_MODULE(DiElectronDiElectronSelector);
DEFINE_FWK_MODULE(DiMuonDiMuonSelector);
DEFINE_FWK_MODULE(DiElectronDiMuonSelector);
DEFINE_FWK_MODULE(DiElectronEMuSelector);
DEFINE_FWK_MODULE(DiMuonEMuSelector);

typedef ObjectSelector<cmg::GenericPhysicsObjectSelectorDefinition<cmg::DiElectronDiElectronHiggs> > DiElectronDiElectronHiggsSelector;
typedef ObjectSelector<cmg::GenericPhysicsObjectSelectorDefinition<cmg::DiMuonDiMuonHiggs> > DiMuonDiMuonHiggsSelector;
typedef ObjectSelector<cmg::GenericPhysicsObjectSelectorDefinition<cmg::DiElectronDiMuonHiggs> > DiElectronDiMuonHiggsSelector;
DEFINE_FWK_MODULE(DiElectronDiElectronHiggsSelector);
DEFINE_FWK_MODULE(DiMuonDiMuonHiggsSelector);
DEFINE_FWK_MODULE(DiElectronDiMuonHiggsSelector);

DEFINE_FWK_MODULE(BestZProducer);
