import FWCore.ParameterSet.Config as cms
#from CMGTools.Common.factories.cmgMuon_cfi import cmgMuon

dimuondimuonFactory = cms.PSet(
       leg1Collection = cms.InputTag("cmgDiMuon"),
       leg2Collection = cms.InputTag("cmgDiMuon"),
       metCollection = cms.InputTag("")
)


from HZZ4lAnalysis.HZZ4lCommon.selections.zmumu_cfi import zmumu

cmgDiMuonDiMuon = cms.EDFilter(
    "DiMuonDiMuonPOProducer",
    cfg = dimuondimuonFactory.clone(),
    cuts = cms.PSet( 
                     mass = cms.string("mass()>100")
                     )
    )
