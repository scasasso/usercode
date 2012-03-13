import FWCore.ParameterSet.Config as cms


from CMGTools.Common.jet_cff import *
from CMGTools.Common.met_cff import *
from HZZ4lAnalysis.HZZ4lCommon.muon_cff import *
from HZZ4lAnalysis.HZZ4lCommon.diLepton_cff import *
from HZZ4lAnalysis.HZZ4lCommon.electron_cff import *
from CMGTools.Common.tau_cff import *
from HZZ4lAnalysis.HZZ4lCommon.higgs_cff import *
from HZZ4lAnalysis.HZZ4lCommon.cutSummary_cff import *
from CMGTools.Common.histogram_cff import *
from CMGTools.Common.trigger_cff import *

from HZZ4lAnalysis.HZZ4lCommon.miscProducers.misc_cff import *

cmgObjectSequence = cms.Sequence(
    jetSequence +
    metSequence +
    muonSequence +
    electronSequence +
    diLeptonSequence +
    tauSequence +
    higgsSequence +
    triggerSequence
    )


analysisSequence = cms.Sequence(
    # build the CMG objects and select them
    cmgObjectSequence +
    # build miscellaneous objects not inheriting from cmg::PhysicsObject
    miscSequence + 
    # summary of cuts for all objects, after skimming
    cutSummarySequence 
    # histograms for all objects, after skimming
    #histogramSequence 
    )
