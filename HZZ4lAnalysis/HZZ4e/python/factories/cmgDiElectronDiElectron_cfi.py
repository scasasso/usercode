import FWCore.ParameterSet.Config as cms
#from CMGTools.Common.factories.cmgElectron_cfi import cmgElectron

dielectrondielectronFactory = cms.PSet(
       leg1Collection = cms.InputTag("cmgDiElectron"),
       leg2Collection = cms.InputTag("cmgDiElectron"),
       metCollection = cms.InputTag("")
)


#from HZZ4lAnalysis.HZZ4lCommon.selections.zee_cfi import zee

cmgDiElectronDiElectron = cms.EDFilter(
    "DiElectronDiElectronPOProducer",
    cfg = dielectrondielectronFactory.clone(),
    cuts = cms.PSet( mass = cms.string("mass()>100") )
    )