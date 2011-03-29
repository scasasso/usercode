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

process.GlobalTag.globaltag = 'GR_R_39X_V5::All'


process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring(
  #'rfio:/castor/cern.ch/cms/store/user/emiglior/test/zzSkim/test/PAT_03Mar11/Mu_ZbbSkimDec22ReReco_PAT397_03Mar11.root'
  'rfio:/castor/cern.ch/cms/store/user/emiglior/zbb/ZbbSkimDec22ReReco_PAT397_17Mar11/Mu/MergedOutputFile_1_2_Ala.root'
    )
)



##################

# TRIGGER FILTER #
##################


### Trigger path FIRED in the event

import HLTrigger.HLTfilters.hltHighLevel_cfi 
process.hltFilter = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone() 
process.hltFilter.HLTPaths = [ "HLT_DoubleMu3_v*" ]
process.hltFilter.TriggerResultsTag = cms.InputTag("TriggerResults","","HLT")
process.hltFilter.throw  = cms.bool(False)
 

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

process.TFileService=cms.Service('TFileService',
                                 fileName=cms.string('Mu_2010_Plots_FromPAT_03Mar11.root')
                                 )
###############################################################
#First Analyzer: general spectra for all PATMuons + filter studies
################################################################
process.MuAllSpectra = cms.EDAnalyzer("MuAnalyzer",
                                      MuonCollection = cms.untracked.string('patMuonsWithTrigger'),
                                      JetCollectionPF = cms.untracked.string('cleanPatJetsPF'),
                                      ZllCollection = cms.untracked.string('zMMCand'),
                                      numEventsNames = cms.untracked.vstring('TotalEventCounter','AfterPVFilterCounter', 'AfterNSFilterCounter', 'AfterPATCounter', 'AfterCandidatesCounter', 'AfterJetsCounter')
                                      )


####################################################
#Second Analyzer: spectra about preselection analysis
####################################################
process.MuPreselSpectra = cms.EDAnalyzer("PreselAnalyzer",
                                      MuonCollection = cms.untracked.string('patMuonsWithTrigger'),
                                      ZllCollection = cms.untracked.string('zMMCand'),
                                                                           )

###############################################################
#Third Analyzer: Jet collections studies
################################################################
process.JetLepton = cms.EDAnalyzer("JetLeptonCleanAnalyzer",
                                   MuonCollection = cms.untracked.string('patMuonsWithTrigger'),
                                   ZllCollection = cms.untracked.string('zMMCand'),
                                   JetCollection = cms.untracked.string('cleanPatJets'),
                                   JetCollectionPU = cms.untracked.string('cleanPatJetsNoPU'),
                                   JetCollectionJPT = cms.untracked.string('cleanPatJetsJPT'),
                                   JetCollectionPF = cms.untracked.string('cleanPatJetsPF'),
                                   )



process.p = cms.Path(process.hltFilter * 
                     ( process.MuAllSpectra +
                       process.MuPreselSpectra +
                       process.JetLepton) )




