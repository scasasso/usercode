import FWCore.ParameterSet.Config as cms
from selections.higgs4e_cfi import *
from HZZ4lAnalysis.HZZ4lCommon.selections.quadriLepton_cfi import *


cmgDiElectronDiElectronSel = cms.EDFilter(
    "DiElectronDiElectronSelector",
    src = cms.InputTag('cmgDiElectronDiElectron'),
    cut = cms.string('getSelection(\"cuts_overlap\")')
    )

# Build cmg::DiElectronDiElectronHiggs candidates
diElectronDiElectronHiggsFactory = cms.PSet(
       inputs = cms.InputTag("cmgDiElectronDiElectronSel")
)

cmgDiElectronDiElectronHiggs = cms.EDFilter(
    "DiElectronDiElectronHiggsPOProducer",
    cfg = diElectronDiElectronHiggsFactory.clone(),
    cuts = cms.PSet(  # inherited from source collection
    overlap = overlap.clone(),
    mass = mass.clone(),
    massOfllCouples = massOfllCouples.clone(),
    isoOfllCouples = isoOfllCouples.clone(),
    SIP4Leptons = SIP4Leptons.clone()
    )
    )

cmgDiElectronDiElectronHiggsSelFlag = cms.EDProducer(
    "DiElectronDiElectronHiggsBestCandProducer",
    src = cms.InputTag("cmgDiElectronDiElectronHiggs"),
    )

cmgDiElectronDiElectronHiggsSelFlagLD = cms.EDProducer(
     "DiElectronDiElectronHiggsLDProducer",
     src = cms.InputTag("cmgDiElectronDiElectronHiggsSelFlag")
     )

PRLHiggs4e = cms.EDFilter(
    "DiElectronDiElectronHiggsSelector",
    src = cms.InputTag('cmgDiElectronDiElectronHiggsSelFlagLD'),
    cut = cms.string('getSelection(\"cuts_massOfllCouples\") && userFloat("bestH_PRL")==1 && '+
                     'leg1.leg1.sourcePtr().userFloat("RhoCorrIso") + leg1.leg2.sourcePtr().userFloat("RhoCorrIso") < 0.35 && '+
                     'leg1.leg1.sourcePtr().userFloat("RhoCorrIso") + leg2.leg1.sourcePtr().userFloat("RhoCorrIso") < 0.35 && '+
                     'leg1.leg1.sourcePtr().userFloat("RhoCorrIso") + leg2.leg2.sourcePtr().userFloat("RhoCorrIso") < 0.35 && '+
                     'leg1.leg2.sourcePtr().userFloat("RhoCorrIso") + leg2.leg1.sourcePtr().userFloat("RhoCorrIso") < 0.35 && '+
                     'leg1.leg2.sourcePtr().userFloat("RhoCorrIso") + leg2.leg2.sourcePtr().userFloat("RhoCorrIso") < 0.35 && '+
                     'leg2.leg1.sourcePtr().userFloat("RhoCorrIso") + leg2.leg2.sourcePtr().userFloat("RhoCorrIso") < 0.35 && '+
                     'leg1.leg1.sourcePtr().userFloat("SIP3D") < 4. && '+
                     'leg1.leg2.sourcePtr().userFloat("SIP3D") < 4. && '+
                     'leg2.leg1.sourcePtr().userFloat("SIP3D") < 4. && '+
                     'leg2.leg2.sourcePtr().userFloat("SIP3D") < 4.'
                     )
    )





higgs4eSequence = (
    cmgDiElectronDiElectronSel +
    cmgDiElectronDiElectronHiggs +
    cmgDiElectronDiElectronHiggsSelFlag +
    cmgDiElectronDiElectronHiggsSelFlagLD +
    PRLHiggs4e
    )
