import FWCore.ParameterSet.Config as cms

from HZZ4lAnalysis.HZZ4lCommon.selections.cutSummaryMuon_cfi import *
from HZZ4lAnalysis.HZZ4lCommon.selections.cutSummaryDiMuon_cfi import *

muonCutSummarySequence = cms.Sequence(
    cutSummaryMuon +
    cutSummaryDiMuon
    )
