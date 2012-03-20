import FWCore.ParameterSet.Config as cms

#Build cmg::DiElectronDiElectron candidates
dielectrondielectronFactory = cms.PSet(
       leg1Collection = cms.InputTag("zEECand"),
       leg2Collection = cms.InputTag("zEECand"),
       metCollection = cms.InputTag("")
)


EEEECand = cms.EDFilter(
    "DiElectronDiElectronPOProducer",
    cfg = dielectrondielectronFactory.clone(),
    cuts = cms.PSet(
    mass = cms.string("mass()>100")
    )
    )

# Build cmg::DiElectronDiElectronHiggs candidates
diElectronDiElectronHiggsFactory = cms.PSet(
       inputs = cms.InputTag("EEEECand")
)

cmgDiElectronDiElectronHiggs = cms.EDFilter(
    "DiElectronDiElectronHiggsPOProducer",
    cfg = diElectronDiElectronHiggsFactory.clone(),
    cuts = cms.PSet( 
    )
    
    )


higgs4eSequence = (
    cmgDiElectronDiElectronHiggs
    )
