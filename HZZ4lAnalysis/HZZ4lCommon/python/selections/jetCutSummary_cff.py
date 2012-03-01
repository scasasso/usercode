import FWCore.ParameterSet.Config as cms

from HZZ4lAnalysis.HZZ4lCommon.selections.cutSummaryPFJet_cfi import *

jetCutSummarySequence = cms.Sequence(
    cutSummaryPFJet
    )
