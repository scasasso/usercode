import FWCore.ParameterSet.Config as cms

from HZZ4lAnalysis.HZZ4lCommon.selections.jetCutSummary_cff import *
from HZZ4lAnalysis.HZZ4lCommon.selections.muonCutSummary_cff import *
from HZZ4lAnalysis.HZZ4lCommon.selections.electronCutSummary_cff import *
#from CMGTools.Common.selections.tauCutSummary_cff import *


cutSummarySequence = cms.Sequence(
    jetCutSummarySequence + 
    muonCutSummarySequence + 
    electronCutSummarySequence
    #tauCutSummarySequence  
    )

