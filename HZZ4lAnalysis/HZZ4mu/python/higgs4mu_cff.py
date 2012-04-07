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
    mass = cms.string("mass()>100"),
    overlap = cms.string("deltaR(leg1.leg1.eta,leg1.leg1.phi,leg2.leg1.eta,leg2.leg1.phi) < 0.01 || "+
                         "deltaR(leg1.leg2.eta,leg1.leg2.phi,leg2.leg1.eta,leg2.leg1.phi) < 0.01 || "+
                         "deltaR(leg1.leg1.eta,leg1.leg1.phi,leg2.leg2.eta,leg2.leg2.phi) < 0.01 || "+
                         "deltaR(leg1.leg2.eta,leg1.leg2.phi,leg2.leg2.eta,leg2.leg2.phi) < 0.01"
                         )
    )
    )

MMMMCandSel = cms.EDFilter(
    "DiMuonDiMuonSelector",
    src = cms.InputTag("MMMMCand"),
    cut = cms.string("getSelection(\"cuts_mass\") && getSelection(\"cuts_overlap\")")
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
