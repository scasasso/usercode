import FWCore.ParameterSet.Config as cms

cutSummaryDiMuon = cms.EDAnalyzer(
    "CutSummaryAnalyzer",
    inputCollection = cms.InputTag("cmgDiMuonSel")
)
