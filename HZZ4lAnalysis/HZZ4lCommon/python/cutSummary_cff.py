import FWCore.ParameterSet.Config as cms

cutSummaryMuon = cms.EDAnalyzer(
    "CutSummaryAnalyzer",
    inputCollection = cms.InputTag("cmgMuon")
)

cutSummaryElectron = cms.EDAnalyzer(
    "CutSummaryAnalyzer",
    inputCollection = cms.InputTag("cmgElectron")
)

cutSummaryDiMuon = cms.EDAnalyzer(
    "CutSummaryAnalyzer",
    inputCollection = cms.InputTag("cmgDiMuon")
)

cutSummaryDiElectron = cms.EDAnalyzer(
    "CutSummaryAnalyzer",
    inputCollection = cms.InputTag("cmgDiElectron")
)

cutSummaryDiMuonDiMuonHiggs = cms.EDAnalyzer(
    "CutSummaryAnalyzer",
    inputCollection = cms.InputTag("cmgDiMuonDiMuonHiggs")
)

cutSummaryDiElectronDiMuonHiggs = cms.EDAnalyzer(
    "CutSummaryAnalyzer",
    inputCollection = cms.InputTag("cmgDiElectronDiMuonHiggs")
)

cutSummaryDiElectronDiElectronHiggs = cms.EDAnalyzer(
    "CutSummaryAnalyzer",
    inputCollection = cms.InputTag("cmgDiElectronDiElectronHiggs")
)


cutSummarySequence = cms.Sequence(
    cutSummaryMuon +
    cutSummaryElectron +
    cutSummaryDiMuon +
    cutSummaryDiElectron +
    cutSummaryDiMuonDiMuonHiggs +
    cutSummaryDiElectronDiMuonHiggs +
    cutSummaryDiElectronDiElectronHiggs
    )

