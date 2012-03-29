import FWCore.ParameterSet.Config as cms
from CMGTools.Common.factories.cmgDiObject_cfi import diObjectFactory
from HZZ4lAnalysis.HZZ4lCommon.selections.diLepton_cfi import *

# Build mumu candidates (no charge requirements)
dimuonFactory = diObjectFactory.clone(
       leg1Collection = cms.InputTag("cmgMuon"),
       leg2Collection = cms.InputTag("cmgMuon"),
       metCollection = cms.InputTag("")
       )

cmgDiMuon = cms.EDFilter(
    "DiMuonPOProducer",
    cfg = dimuonFactory.clone(),
    cuts = cms.PSet(
    z1mumu = z1mumu.clone(),
    zCand = zCand.clone(),
    llCand = llCand.clone()
      )
    )

# Build ee candidates (no charge requirements)
diElectronFactory = diObjectFactory.clone(
       leg1Collection = cms.InputTag("cmgElectron"),
       leg2Collection = cms.InputTag("cmgElectron"),
       metCollection = cms.InputTag("")
)


cmgDiElectron = cms.EDFilter(
    "DiElectronPOProducer",
    cfg = diElectronFactory.clone(),
    cuts = cms.PSet(
    z1ee = z1ee.clone(),
    zCand = zCand.clone(),
    llCand = llCand.clone()
      ),
    )

# Build emu candidates (no charge requirements)
emuFactory = diObjectFactory.clone(
       leg1Collection = cms.InputTag("cmgElectron"),
       leg2Collection = cms.InputTag("cmgMuon"),
)

cmgEMuCand = cms.EDFilter(
    "EMuPOProducer",
    cfg = emuFactory.clone(),
    cuts = cms.PSet(
    llCand = llCand.clone()
      ),
    )

#Skim the mumu collection
MMCand = cms.EDFilter(
    "CmgDiMuonSelector",
    src = cms.InputTag( "cmgDiMuon" ),
    cut = cms.string( "getSelection(\"cuts_llCand\")" )
    )

#Skim the ee collection
EECand = cms.EDFilter(
    "CmgDiElectronSelector",
    src = cms.InputTag( "cmgDiElectron" ),
    cut = cms.string( "getSelection(\"cuts_llCand\")" )
    )

#Skim the emu collection
EMCand = cms.EDFilter(
    "CmgEMuSelector",
    src = cms.InputTag( "cmgEMuCand" ),
    cut = cms.string( "getSelection(\"cuts_llCand\")" )
    )

#Skim the mumu collection
zMMCand = cms.EDFilter(
    "CmgDiMuonSelector",
    src = cms.InputTag( "cmgDiMuon" ),
    cut = cms.string( "getSelection(\"cuts_zCand\")" )
    )

#Skim the ee collection
zEECand = cms.EDFilter(
    "CmgDiElectronSelector",
    src = cms.InputTag( "cmgDiElectron" ),
    cut = cms.string( "getSelection(\"cuts_zCand\")" )
    )

# Skim the mumu collection to get the Z1 candidates
Z1MMCand = cms.EDFilter(
    "CmgDiMuonSelector",
    src = cms.InputTag( "cmgDiMuon" ),
    cut = cms.string( "getSelection(\"cuts_z1mumu\")" )
    )

# Skim the ee collection to get the Z1 candidates
Z1EECand = cms.EDFilter(
    "CmgDiElectronSelector",
    src = cms.InputTag( "cmgDiElectron" ),
    cut = cms.string( "getSelection(\"cuts_z1ee\")" )
    )


diLeptonSequence = cms.Sequence(
    cmgDiMuon +
    cmgDiElectron +
    cmgEMuCand +
    MMCand +
    EECand +
    EMCand +
    zMMCand +
    zEECand +
    Z1MMCand +
    Z1EECand
)
