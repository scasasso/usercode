import FWCore.ParameterSet.Config as cms

from HZZ4lAnalysis.HZZ4lCommon.eventContent.particleFlow_cff import *
from HZZ4lAnalysis.HZZ4lCommon.eventContent.traditional_cff import *
from HZZ4lAnalysis.HZZ4lCommon.eventContent.trigger_cff import *
from HZZ4lAnalysis.HZZ4lCommon.eventContent.gen_cff import *
from HZZ4lAnalysis.HZZ4lCommon.eventContent.eventCleaning_cff import *
from HZZ4lAnalysis.HZZ4lCommon.eventContent.runInfoAccounting_cff import *

patObjects = cms.untracked.vstring(
    'keep patMuons_selectedPat*_*_*',
    'keep patElectrons_selectedPat*_*_*',
    'drop patTaus_selectedPat*_*_*',
    #COLIN : the following should be in traditional_cff
    'keep cmgPhotons_selectedPat*_*_*',
    'keep recoVertexs_offlinePrimaryVertices_*_*'
    )

everything = particleFlow + patObjects + runInfoAccounting + trigger + gen + eventCleaning

#eventually add traditional

MHT = particleFlowMHT + traditionalMHT
