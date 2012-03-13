import FWCore.ParameterSet.Config as cms

# Build cmg::DiMuonDiMuon candidates
dimuondimuonFactory = cms.PSet(
       leg1Collection = cms.InputTag("cmgDiMuon"),
       leg2Collection = cms.InputTag("cmgDiMuon"),
       metCollection = cms.InputTag("")
)


from HZZ4lAnalysis.HZZ4lCommon.selections.zmumu_cfi import zmumu

cmgDiMuonDiMuon = cms.EDFilter(
    "DiMuonDiMuonPOProducer",
    cfg = dimuondimuonFactory.clone(),
    cuts = cms.PSet( 
    mass = cms.string("mass()>100")
    )
    )

# Build cmg::DiMuonDiMuonHiggs candidates
diMuonDiMuonHiggsFactory = cms.PSet(
       inputs = cms.InputTag("cmgDiMuonDiMuon")
)

cmgDiMuonDiMuonHiggs = cms.EDFilter(
    "DiMuonDiMuonHiggsPOProducer",
    cfg = diMuonDiMuonHiggsFactory.clone(),
    cuts = cms.PSet( 
    )
    
    )



higgs4muSequence = (
    cmgDiMuonDiMuon +
    cmgDiMuonDiMuonHiggs
    )
