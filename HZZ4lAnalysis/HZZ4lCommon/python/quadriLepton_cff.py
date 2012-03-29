import FWCore.ParameterSet.Config as cms

from CMGTools.Common.factories.cmgDiObject_cfi import diObjectFactory
from HZZ4lAnalysis.HZZ4mu.higgs4mu_cff import *
from HZZ4lAnalysis.HZZ4e.higgs4e_cff import *
from HZZ4lAnalysis.HZZ2e2mu.higgs2e2mu_cff import *

mmemFactory = diObjectFactory.clone(
       leg1Collection = cms.InputTag("zMMCand"),
       leg2Collection = cms.InputTag("cmgEMuCand"),
       metCollection = cms.InputTag("")
       )

zMMemCand = cms.EDFilter(
    "DiMuonEMuPOProducer",
    cfg = mmemFactory.clone(),
    cuts = cms.PSet(
   
      )
    )

eeemFactory = diObjectFactory.clone(
       leg1Collection = cms.InputTag("zEECand"),
       leg2Collection = cms.InputTag("cmgEMuCand"),
       metCollection = cms.InputTag("")
       )

zEEemCand = cms.EDFilter(
    "DiElectronEMuPOProducer",
    cfg = eeemFactory.clone(),
    cuts = cms.PSet(
   
      )
    )


quadriLeptonSequence = (
    MMMMCand +
    MMMMCandSel +
    EEEECand +
    EEEECandSel +
    EEMMCand +
    EEMMCandSel +
    zMMemCand +
    zEEemCand
    )


