import FWCore.ParameterSet.Config as cms
from selections.higgs4e_cfi import *
from HZZ4lAnalysis.HZZ4lCommon.selections.quadriLepton_cfi import *

# Build cmg::DiElectronDiElectronHiggs candidates
diElectronDiElectronHiggsFactory = cms.PSet(
       inputs = cms.InputTag("cmgDiElectronDiElectron")
)

cmgDiElectronDiElectronHiggs = cms.EDFilter(
    "DiElectronDiElectronHiggsPOProducer",
    cfg = diElectronDiElectronHiggsFactory.clone(),
    cuts = cms.PSet(
    overlap = overlap.clone(),
    mass = mass.clone(),
    massOfllCouples = massOfllCouples.clone()
    )
    )

cmgDiElectronDiElectronHiggsSel = cms.EDFilter(
    "DiElectronDiElectronHiggsSelector",
    src = cms.InputTag('cmgDiElectronDiElectronHiggs'),
    cut = cms.string('getSelection(\"cuts_overlap\")')
    )

cmgDiElectronDiElectronHiggsSelFlag = cms.EDProducer(
    "DiElectronDiElectronHiggsBestCandProducer",
    src = cms.InputTag("cmgDiElectronDiElectronHiggsSel")
    )


# cmgDiElectronDiElectronHiggsLD = cms.EDProducer(
#     "DiElectronDiElectronHiggsLDProducer",
#     src = cms.InputTag("cmgDiElectronDiElectronHiggs")
#     )

PRLHiggs4e = cms.EDFilter(
    "DiElectronDiElectronHiggsSelector",
    src = cms.InputTag('cmgDiElectronDiElectronHiggsSelFlag'),
    cut = cms.string('userFloat("bestH_PRL")==1 && '+
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
    cmgDiElectronDiElectronHiggs +
    cmgDiElectronDiElectronHiggsSel +
    cmgDiElectronDiElectronHiggsSelFlag +
#    cmgDiElectronDiElectronHiggsLD
    PRLHiggs4e
    )
