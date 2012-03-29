import FWCore.ParameterSet.Config as cms

# Build cmg::DiMuonDiMuon candidates
dimuondimuonFactory = cms.PSet(
       leg1Collection = cms.InputTag("zMMCand"),
       leg2Collection = cms.InputTag("zMMCand"),
       metCollection = cms.InputTag("")
)


MMMMCand = cms.EDFilter(
    "DiMuonDiMuonPOProducer",
    cfg = dimuondimuonFactory.clone(),
    cuts = cms.PSet( 
    mass = cms.string("mass()>100")
    )
    )

MMMMCandSel = cms.EDFilter(
    "DiMuonDiMuonSelector",
    src = cms.InputTag("MMMMCand"),
    cut = cms.string("getSelection(\"cuts_mass\")")
    )

# Build cmg::DiMuonDiMuonHiggs candidates
diMuonDiMuonHiggsFactory = cms.PSet(
       inputs = cms.InputTag("MMMMCandSel")
)

cmgDiMuonDiMuonHiggs = cms.EDFilter(
    "DiMuonDiMuonHiggsPOProducer",
    cfg = diMuonDiMuonHiggsFactory.clone(),
    cuts = cms.PSet( 
    )
    
    )

cmgDiMuonDiMuonHiggsLD = cms.EDProducer(
    "DiMuonDiMuonHiggsLDProducer",
    src = cms.InputTag("cmgDiMuonDiMuonHiggs")
    )

higgs4muSequence = (
    cmgDiMuonDiMuonHiggs +
    cmgDiMuonDiMuonHiggsLD
    )
