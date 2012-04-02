######################################################################
## Main cmsRun configuration file for the CMGTools tutorial.
## See also:
##   https://twiki.cern.ch/twiki/bin/view/CMS/CMGToolsTutorial
######################################################################

import FWCore.ParameterSet.Config as cms
import FWCore.ParameterSet.VarParsing as VarParsing
from PhysicsTools.PatAlgos.patTemplate_cfg import *
from HZZ4lAnalysis.HZZ4lCommon.eventContent.everything_cff import everything
from CMGTools.Common.Tools.getGlobalTag import getGlobalTag
from CMGTools.Common.physicsObjectPrinter_cfi import physicsObjectPrinter
from CMGTools.Production.datasetToSource import *

##########

sep_line = "-" * 50
print
print sep_line
print "CMGTools HZZ4l Analysis"
print sep_line

##########

process.setName_("CMG")

#Setup options 
options = VarParsing.VarParsing()
options.register('maxEvents',-1,VarParsing.VarParsing.multiplicity.singleton,VarParsing.VarParsing.varType.int,"Number of events to process (-1 for all)")
options.parseArguments()


Pick up the data files (ggHZZTo4l).
process.source = datasetToSource(
    "cmgtools",
    "/GluGluToHToZZTo4L_M-120_7TeV-powheg-pythia6/Fall11-PU_S6_START42_V14B-v1/AODSIM/V4/PAT_CMG_4_0_0",
    "tree_CMG_.*root"
   )

# One can limit the number of files to avoid some of the CASTOR
# overhead (i.e., faster start-up).
nFilesMax = 5
print "WARNING: Restricting input to the first %d files (of the %d found)" % \
      (nFilesMax, len(process.source.fileNames))
if len(process.source.fileNames) > nFilesMax:
    process.source.fileNames = process.source.fileNames[:nFilesMax - 1]

print "Will process the following files:"
for fileName in process.source.fileNames:
    print "  %s" % fileName

# One can limit the number of events to process.
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(options.maxEvents)
    )
tmp = process.maxEvents.input.value()
if tmp > -1:
    print "Will process at most %d events" % tmp

# One can limit the number of lumi-sections to process.
process.maxLuminosityBlocks = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
    )
tmp = process.maxLuminosityBlocks.input.value()
if tmp > -1:
    print "Will process at most %d lumi-sections" % tmp

# Output module for EDM events (ntuple).
process.out.fileName = cms.untracked.string("HZZ4l_CMGTuple.root")
process.out.outputCommands = cms.untracked.vstring('drop *', 'keep *_*_*_CMG')
process.out.outputCommands.extend(everything)
process.out.dropMetaData = cms.untracked.string("PRIOR")

# Output file for histograms etc.
process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string("histograms_HZZ4l.root"))

# Add RhoCorrIso to pat::Muon and pat::Electron
process.RhoCorrIsoSequence = cms.EDProducer("IsoRhoCorrProducer",
                                            muonSrc = cms.untracked.InputTag("selectedPatMuons"),
                                            electronSrc = cms.untracked.InputTag("selectedPatElectrons"),
                                            rhoSrc = cms.untracked.InputTag("kt6PFJetsAK5","rho","PAT")
                                            )

# Load the default analysis sequence.
process.load("HZZ4lAnalysis.HZZ4lCommon.analysis_cff")

##########

# Now tune the default analysis sequence to our needs by modifying the
# parameters of the modules present in this sequence.

# Switch on production of trigger objects.
process.cmgTriggerObject.cfg.useTriggerObjects = cms.untracked.bool(True)

##########

runOnMC = False

if runOnMC:
    process.load("CMGTools.Common.runInfoAccounting_cfi")
    process.outpath += process.runInfoAccounting

process.p = cms.Path(
    process.RhoCorrIsoSequence +
    process.analysisSequence
    )

process.GlobalTag.globaltag = cms.string(getGlobalTag(runOnMC))

process.schedule = cms.Schedule(
    process.p,
    process.outpath
    )

##########

# How much feedback do we want from the framework?
process.MessageLogger.cerr.FwkReport.reportEvery = 100
process.options = cms.untracked.PSet(wantSummary = cms.untracked.bool(True))

######################################################################
