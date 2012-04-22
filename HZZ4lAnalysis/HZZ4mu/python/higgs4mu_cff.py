import FWCore.ParameterSet.Config as cms
from selections.higgs4mu_cfi import *


# Build cmg::DiMuonDiMuonHiggs candidates
diMuonDiMuonHiggsFactory = cms.PSet(
       inputs = cms.InputTag("cmgDiMuonDiMuon")
)

cmgDiMuonDiMuonHiggs = cms.EDFilter(
    "DiMuonDiMuonHiggsPOProducer",
    cfg = diMuonDiMuonHiggsFactory.clone(),
    cuts = cms.PSet(
    PRLHiggs4mu = PRLHiggs4mu.clone()
    )    
    )

cmgDiMuonDiMuonHiggsLD = cms.EDProducer(
    "DiMuonDiMuonHiggsLDProducer",
    src = cms.InputTag("cmgDiMuonDiMuonHiggs")
    )

PRLHiggs4mu = cms.EDFilter(
    "DiMuonDiMuonHiggsSelector",
    src = cms.InputTag('cmgDiMuonDiMuonHiggs'),
    cut = cms.string('getSelection(\"cuts_PRLHiggs4mu\")')
    )



higgs4muSequence = (
    cmgDiMuonDiMuonHiggs +
#    cmgDiMuonDiMuonHiggsLD
    PRLHiggs4mu
    )
