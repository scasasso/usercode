import FWCore.ParameterSet.Config as cms

process = cms.Process("TEST")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring(
                                                               'file:HZZ4l_CMGTuple.root'
                                                               )
                            )

process.DummySelection = cms.EDAnalyzer('HZZ4lNtupleMaker'
                              )

process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string('HZZ4l_DummyTree.root')
                                   )

process.p = cms.Path(process.DummySelection)
