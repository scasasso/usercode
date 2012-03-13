import FWCore.ParameterSet.Config as cms

cutSummaryMuon = cms.EDAnalyzer(
    "CutSummaryAnalyzer",
    inputCollection = cms.InputTag("cmgMuon")
)

cutSummaryElectron = cms.EDAnalyzer(
    "CutSummaryAnalyzer",
    inputCollection = cms.InputTag("cmgElectron")
)

cutSummaryZ1mumu = cms.EDAnalyzer(
    "CutSummaryAnalyzer",
    inputCollection = cms.InputTag("cmgDiMuon")
)

cutSummaryZ1ee = cms.EDAnalyzer(
    "CutSummaryAnalyzer",
    inputCollection = cms.InputTag("cmgDiElectron")
)


cutSummarySequence = cms.Sequence(
    cutSummaryMuon +
    cutSummaryElectron +
    cutSummaryZ1mumu +
    cutSummaryZ1ee
    )

