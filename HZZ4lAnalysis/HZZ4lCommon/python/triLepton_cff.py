import FWCore.ParameterSet.Config as cms
from CMGTools.Common.factories.cmgDiObject_cfi import diObjectFactory

mmmFactory = diObjectFactory.clone(
       leg1Collection = cms.InputTag("zMMCand"),
       leg2Collection = cms.InputTag("softMuons"),
       metCollection = cms.InputTag("")
       )

zMMMCand = cms.EDFilter(
    "DiMuonMuPOProducer",
    cfg = mmmFactory.clone(),
    cuts = cms.PSet(
   
      )
    )

mmeFactory = diObjectFactory.clone(
       leg1Collection = cms.InputTag("zMMCand"),
       leg2Collection = cms.InputTag("softElectrons"),
       metCollection = cms.InputTag("")
       )

zMMECand = cms.EDFilter(
    "DiMuonEPOProducer",
    cfg = mmeFactory.clone(),
    cuts = cms.PSet(
   
      )
    )

eeeFactory = diObjectFactory.clone(
       leg1Collection = cms.InputTag("zEECand"),
       leg2Collection = cms.InputTag("softElectrons"),
       metCollection = cms.InputTag("")
       )

zEEECand = cms.EDFilter(
    "DiElectronEPOProducer",
    cfg = eeeFactory.clone(),
    cuts = cms.PSet(
   
      )
    )

eemFactory = diObjectFactory.clone(
       leg1Collection = cms.InputTag("zEECand"),
       leg2Collection = cms.InputTag("softMuons"),
       metCollection = cms.InputTag("")
       )

zEEMCand = cms.EDFilter(
    "DiElectronMuPOProducer",
    cfg = eemFactory.clone(),
    cuts = cms.PSet(
   
      )
    )

#Final sequence
triLeptonSequence = cms.Sequence(
    zMMMCand +
    zMMECand +
    zEEECand +
    zEEMCand
    )
