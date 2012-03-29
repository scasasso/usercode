import FWCore.ParameterSet.Config as cms

# Build cmg::DiElectronDiMuon candidates
dielectrondimuonFactory = cms.PSet(
       leg1Collection = cms.InputTag("zEECand"),
       leg2Collection = cms.InputTag("zMMCand"),
       metCollection = cms.InputTag("")
)


EEMMCand = cms.EDFilter(
    "DiElectronDiMuonPOProducer",
    cfg = dielectrondimuonFactory.clone(),
    cuts = cms.PSet( 
    mass = cms.string("mass()>100")
    )
    )

EEMMCandSel = cms.EDFilter(
    "DiElectronDiMuonSelector",
    src = cms.InputTag("EEMMCand"),
    cut = cms.string("getSelection(\"cuts_mass\")")
    )

# Build cmg::DiElectronDiMuonHiggs candidates
diElectronDiMuonHiggsFactory = cms.PSet(
       inputs = cms.InputTag("EEMMCandSel")
)

cmgDiElectronDiMuonHiggs = cms.EDFilter(
    "DiElectronDiMuonHiggsPOProducer",
    cfg = diElectronDiMuonHiggsFactory.clone(),
    cuts = cms.PSet( 
    )
    
    )

cmgDiElectronDiMuonHiggsLD = cms.EDProducer(
    "DiElectronDiMuonHiggsLDProducer",
    src = cms.InputTag("cmgDiElectronDiMuonHiggs")
    )



higgs2e2muSequence = (
    cmgDiElectronDiMuonHiggs +
    cmgDiElectronDiMuonHiggsLD
    )
