import FWCore.ParameterSet.Config as cms

dielectrondimuonFactory = cms.PSet(
       leg1Collection = cms.InputTag("cmgDiElectron"),
       leg2Collection = cms.InputTag("cmgDiMuon"),
       metCollection = cms.InputTag("")
)


#from HZZ4lAnalysis.HZZ4lCommon.selections.zmumu_cfi import zmumu

cmgDiElectronDiMuon = cms.EDFilter(
    "DiElectronDiMuonPOProducer",
    cfg = dielectrondimuonFactory.clone(),
    cuts = cms.PSet( #z1 = cms.string("leg1().getSelection(\"cuts_zmumu\") || leg2().getSelection(\"cuts_zmumu\")"),
                     mass = cms.string("mass()>100")
                     )
    )
