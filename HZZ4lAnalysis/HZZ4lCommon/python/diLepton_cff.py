import FWCore.ParameterSet.Config as cms

# Build emu candidates (no charge requirements)
from CMGTools.Common.factories.cmgDiObject_cfi import diObjectFactory

emuFactory = diObjectFactory.clone(
       leg1Collection = cms.InputTag("cmgElectronSel"),
       leg2Collection = cms.InputTag("cmgMuonSel"),
)

cmgEMu = cms.EDFilter(
    "EMuPOProducer",
    cfg = emuFactory.clone(),
    cuts = cms.PSet(

      ),
    )

# Build mumu candidates (no charge requirements)
dimuonFactory = diObjectFactory.clone(
       leg1Collection = cms.InputTag("cmgMuonSel"),
       leg2Collection = cms.InputTag("cmgMuonSel"),
       metCollection = cms.InputTag("")
       )

from HZZ4lAnalysis.HZZ4lCommon.selections.zmumu_cfi import *

cmgDiMuon = cms.EDFilter(
    "DiMuonPOProducer",
    cfg = dimuonFactory.clone(),
    cuts = cms.PSet(
    zmumu = zmumu.clone()
      )
    )

# Build ee candidates (no charge requirements)
diElectronFactory = diObjectFactory.clone(
       leg1Collection = cms.InputTag("cmgElectronSel"),
       leg2Collection = cms.InputTag("cmgElectronSel"),
       metCollection = cms.InputTag("")
)

from HZZ4lAnalysis.HZZ4lCommon.selections.zee_cfi import *

cmgDiElectron = cms.EDFilter(
    "DiElectronPOProducer",
    cfg = diElectronFactory.clone(),
    cuts = cms.PSet(
    zee = zee.clone()
      ),
    )
# Skim the mumu collection to get the Z1 candidates
cmgZ1mumuSel = cms.EDFilter(
    "CmgDiMuonSelector",
    src = cms.InputTag( "cmgDiMuon" ),
    cut = cms.string( "getSelection(\"cuts_zmumu\")" )
    )

# Skim the ee collection to get the Z1 candidates
cmgZ1eeSel = cms.EDFilter(
    "CmgDiElectronSelector",
    src = cms.InputTag( "cmgDiElectron" ),
    cut = cms.string( "getSelection(\"cuts_zee\")" )
    )


diLeptonSequence = cms.Sequence(
    cmgEMu +
    cmgDiMuon +
    cmgDiElectron +
    cmgZ1mumuSel +
    cmgZ1eeSel
)
