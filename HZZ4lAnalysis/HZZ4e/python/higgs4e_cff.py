import FWCore.ParameterSet.Config as cms

#Build cmg::DiElectronDiElectron candidates
dielectrondielectronFactory = cms.PSet(
       leg1Collection = cms.InputTag("cmgDiElectron"),
       leg2Collection = cms.InputTag("cmgDiElectron"),
       metCollection = cms.InputTag("")
)


from HZZ4lAnalysis.HZZ4lCommon.selections.zee_cfi import zee

cmgDiElectronDiElectron = cms.EDFilter(
    "DiElectronDiElectronPOProducer",
    cfg = dielectrondielectronFactory.clone(),
    cuts = cms.PSet(
    mass = cms.string("mass()>100")
    )
    )

# Build cmg::DiElectronDiElectronHiggs candidates
diElectronDiElectronHiggsFactory = cms.PSet(
       inputs = cms.InputTag("cmgDiElectronDiElectron")
)

cmgDiElectronDiElectronHiggs = cms.EDFilter(
    "DiElectronDiElectronHiggsPOProducer",
    cfg = diElectronDiElectronHiggsFactory.clone(),
    cuts = cms.PSet( 
    )
    
    )


higgs4eSequence = (
    cmgDiElectronDiElectron +
    cmgDiElectronDiElectronHiggs
    )
