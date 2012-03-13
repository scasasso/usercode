import FWCore.ParameterSet.Config as cms

# Build cmg::DiElectronDiMuon candidates
dielectrondimuonFactory = cms.PSet(
       leg1Collection = cms.InputTag("cmgDiElectron"),
       leg2Collection = cms.InputTag("cmgDiMuon"),
       metCollection = cms.InputTag("")
)


from HZZ4lAnalysis.HZZ4lCommon.selections.zmumu_cfi import zmumu
from HZZ4lAnalysis.HZZ4lCommon.selections.zee_cfi import zee

cmgDiElectronDiMuon = cms.EDFilter(
    "DiElectronDiMuonPOProducer",
    cfg = dielectrondimuonFactory.clone(),
    cuts = cms.PSet( 
    mass = cms.string("mass()>100")
    )
    )

# Build cmg::DiElectronDiMuonHiggs candidates
diElectronDiMuonHiggsFactory = cms.PSet(
       inputs = cms.InputTag("cmgDiElectronDiMuon")
)

cmgDiElectronDiMuonHiggs = cms.EDFilter(
    "DiElectronDiMuonHiggsPOProducer",
    cfg = diElectronDiMuonHiggsFactory.clone(),
    cuts = cms.PSet( 
    )
    
    )



higgs2e2muSequence = (
    cmgDiElectronDiMuon +
    cmgDiElectronDiMuonHiggs
    )
