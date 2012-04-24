import FWCore.ParameterSet.Config as cms
from selections.higgs4mu_cfi import *
from HZZ4lAnalysis.HZZ4lCommon.selections.quadriLepton_cfi import *


# Build cmg::DiMuonDiMuonHiggs candidates
diMuonDiMuonHiggsFactory = cms.PSet(
       inputs = cms.InputTag("cmgDiMuonDiMuon")
)

cmgDiMuonDiMuonHiggs = cms.EDFilter(
    "DiMuonDiMuonHiggsPOProducer",
    cfg = diMuonDiMuonHiggsFactory.clone(),
    cuts = cms.PSet(
    overlap = overlap.clone(),
    mass = mass.clone(),
    massOfllCouples = massOfllCouples.clone()
    )    
    )

cmgDiMuonDiMuonHiggsSel = cms.EDFilter(
    "DiMuonDiMuonHiggsSelector",
    src = cms.InputTag('cmgDiMuonDiMuonHiggs'),
    cut = cms.string('getSelection(\"cuts_overlap\")')
    )

cmgDiMuonDiMuonHiggsSelFlag = cms.EDProducer(
    "DiMuonDiMuonHiggsBestCandProducer",
    src = cms.InputTag("cmgDiMuonDiMuonHiggsSel")
    )


# cmgDiMuonDiMuonHiggsLD = cms.EDProducer(
#     "DiMuonDiMuonHiggsLDProducer",
#     src = cms.InputTag("cmgDiMuonDiMuonHiggs")
#     )

PRLHiggs4mu = cms.EDFilter(
    "DiMuonDiMuonHiggsSelector",
    src = cms.InputTag('cmgDiMuonDiMuonHiggsSelFlag'),
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



higgs4muSequence = (
    cmgDiMuonDiMuonHiggs +
    cmgDiMuonDiMuonHiggsSel +
    cmgDiMuonDiMuonHiggsSelFlag +
#    cmgDiMuonDiMuonHiggsLD
    PRLHiggs4mu
    )
