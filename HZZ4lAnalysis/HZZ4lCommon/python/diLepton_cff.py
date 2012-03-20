import FWCore.ParameterSet.Config as cms
from CMGTools.Common.factories.cmgDiObject_cfi import diObjectFactory

# Build mumu candidates (no charge requirements)
dimuonFactory = diObjectFactory.clone(
       leg1Collection = cms.InputTag("softMuons"),
       leg2Collection = cms.InputTag("softMuons"),
       metCollection = cms.InputTag("")
       )

from HZZ4lAnalysis.HZZ4lCommon.selections.diLepton_cfi import *

cmgDiMuon = cms.EDFilter(
    "DiMuonPOProducer",
    cfg = dimuonFactory.clone(),
    cuts = cms.PSet(
    zmumu = zmumu.clone(),
    zCand = zCand.clone()
      )
    )

# Build ee candidates (no charge requirements)
diElectronFactory = diObjectFactory.clone(
       leg1Collection = cms.InputTag("softElectrons"),
       leg2Collection = cms.InputTag("softElectrons"),
       metCollection = cms.InputTag("")
)


cmgDiElectron = cms.EDFilter(
    "DiElectronPOProducer",
    cfg = diElectronFactory.clone(),
    cuts = cms.PSet(
    zee = zee.clone(),
    zCand = zCand.clone()
      ),
    )

# Build emu candidates (no charge requirements)
emuFactory = diObjectFactory.clone(
       leg1Collection = cms.InputTag("softElectrons"),
       leg2Collection = cms.InputTag("softMuons"),
)

EMuCand = cms.EDFilter(
    "EMuPOProducer",
    cfg = emuFactory.clone(),
    cuts = cms.PSet(

      ),
    )

#Skim the mumu collection
zMMCand = cms.EDFilter(
    "CmgDiMuonSelector",
    src = cms.InputTag( "cmgDiMuon" ),
    cut = cms.string( "getSelection(\"cuts_zCand\")" )
    )

# Skim the mumu collection to get the Z1 candidates
cmgZ1mumuSel = cms.EDFilter(
    "CmgDiMuonSelector",
    src = cms.InputTag( "cmgDiMuon" ),
    cut = cms.string( "getSelection(\"cuts_zmumu\")" )
    )

#Skim the ee collection
zEECand = cms.EDFilter(
    "CmgDiElectronSelector",
    src = cms.InputTag( "cmgDiElectron" ),
    cut = cms.string( "getSelection(\"cuts_zCand\")" )
    )

# Skim the ee collection to get the Z1 candidates
cmgZ1eeSel = cms.EDFilter(
    "CmgDiElectronSelector",
    src = cms.InputTag( "cmgDiElectron" ),
    cut = cms.string( "getSelection(\"cuts_zee\")" )
    )


diLeptonSequence = cms.Sequence(
    EMuCand +
    cmgDiMuon +
    cmgDiElectron +
    zMMCand +
    zEECand +
    cmgZ1mumuSel +
    cmgZ1eeSel
)
