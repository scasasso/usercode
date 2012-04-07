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
    mass = cms.string("mass()>100"),
    overlap = cms.string("deltaR(leg1.leg1.eta,leg1.leg1.phi,leg2.leg1.eta,leg2.leg1.phi) < 0.01 || "+
                         "deltaR(leg1.leg2.eta,leg1.leg2.phi,leg2.leg1.eta,leg2.leg1.phi) < 0.01 || "+
                         "deltaR(leg1.leg1.eta,leg1.leg1.phi,leg2.leg2.eta,leg2.leg2.phi) < 0.01 || "+
                         "deltaR(leg1.leg2.eta,leg1.leg2.phi,leg2.leg2.eta,leg2.leg2.phi) < 0.01"
                         )
    )
    )

EEEECandSel = cms.EDFilter(
    "DiElectronDiElectronSelector",
    src = cms.InputTag("EEEECand"),
    cut = cms.string("getSelection(\"cuts_mass\") && getSelection(\"cuts_overlap\")")
    )


# Build cmg::DiElectronDiElectronHiggs candidates
diElectronDiElectronHiggsFactory = cms.PSet(
       inputs = cms.InputTag("EEEECandSel")
)

cmgDiElectronDiElectronHiggs = cms.EDFilter(
    "DiElectronDiElectronHiggsPOProducer",
    cfg = diElectronDiElectronHiggsFactory.clone(),
    cuts = cms.PSet( 
    )
    
    )

cmgDiElectronDiElectronHiggsLD = cms.EDProducer(
    "DiElectronDiElectronHiggsLDProducer",
    src = cms.InputTag("cmgDiElectronDiElectronHiggs")
    )

higgs4eSequence = (
    cmgDiElectronDiElectronHiggs +
    cmgDiElectronDiElectronHiggsLD
    )
