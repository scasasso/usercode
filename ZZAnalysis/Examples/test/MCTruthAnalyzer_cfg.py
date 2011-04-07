#################
#PATMuons analysis
##################

import FWCore.ParameterSet.Config as cms

process = cms.Process("TEST")
# Messages
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.destinations = ['cout', 'cerr']
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.MagneticField_38T_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")

process.GlobalTag.globaltag = 'START39_V8::All'

process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring(
    #'rfio:/castor/cern.ch/cms/store/user/emiglior/zbb/ZbbSkimDec22ReReco_PAT397_17Mar11/DYJetsToLL_TuneZ2/MergedOutputFile_1_1_yxe.root'   ## DY +Jets
    # 'rfio:/castor/cern.ch/cms/store/user/emiglior/zbb/ZbbSkimDec22ReReco_PAT397_17Mar11/TTJets_TuneZ2/MergedOutputFile_1_1_4on.root'   ## TT +Jets
    # 'rfio:/castor/cern.ch/cms/store/user/emiglior/zbb/ZbbSkimDec22ReReco_PAT397_17Mar11/ZccToLL/MergedOutputFile_1_2_Qog.root'   ## Zcc
     'rfio:/castor/cern.ch/cms/store/user/emiglior/zbb/ZbbSkimDec22ReReco_PAT397_17Mar11/ZbbToLL/MergedOutputFile_1_2_L4s.root'   ## Zbb
    )
                            )

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

process.TFileService=cms.Service('TFileService',
                                 fileName=cms.string('MCTruth_Zbb_2010_Plots_FromPAT_03Mar11-filter.root')
                                 )

###############################################################
#MC filter: select events with muons from b semileptonic decays 
###############################################################
process.MCFilter = cms.EDFilter("LeptFromDecayFilter",
                                src = cms.InputTag("prunedGen"),
                                JetCollection = cms.InputTag("cleanPatJetsPF"),
                                ElectronCollection = cms.InputTag("patElectronsWithTrigger"),
                                MuonCollection = cms.InputTag("patMuonsWithTrigger"),
                                ZmmCollection = cms.InputTag('zMMCand'),
                                DecayChainSelection = cms.untracked.string('b>m')
                                    )

####################################################
#MC Analyzer: spectra of MC Truth Analyzer
####################################################
#process.MCAnalyzer = cms.EDAnalyzer("MCTruthAnalyzer",
#                                    src = cms.InputTag("prunedGen"),
#                                    JetCollection = cms.InputTag("patJets"),
#                                    ElectronCollection = cms.InputTag("patElectronsWithTrigger"),
#                                    MuonCollection = cms.InputTag("patMuonsWithTrigger"),
#                                    ZmmCollection = cms.InputTag('zMMCand')
#                                    )

process.p = cms.Path(process.MCFilter)




