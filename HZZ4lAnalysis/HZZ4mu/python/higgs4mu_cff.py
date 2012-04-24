import FWCore.ParameterSet.Config as cms
from selections.higgs4mu_cfi import *
from HZZ4lAnalysis.HZZ4lCommon.selections.quadriLepton_cfi import *

cmgDiMuonDiMuonSel = cms.EDFilter(
    "DiMuonDiMuonSelector",
    src = cms.InputTag('cmgDiMuonDiMuon'),
    cut = cms.string('getSelection(\"cuts_overlap\")')
    )

# Build cmg::DiMuonDiMuonHiggs candidates
diMuonDiMuonHiggsFactory = cms.PSet(
       inputs = cms.InputTag("cmgDiMuonDiMuonSel")
)

cmgDiMuonDiMuonHiggs = cms.EDFilter(
    "DiMuonDiMuonHiggsPOProducer",
    cfg = diMuonDiMuonHiggsFactory.clone(),
    cuts = cms.PSet(  # inherited from source collection
    overlap = overlap.clone(),
    mass = mass.clone(),
    massOfllCouples = massOfllCouples.clone(),
    isoOfllCouples = isoOfllCouples.clone(),
    SIP4Leptons = SIP4Leptons.clone()
    )    
    )

cmgDiMuonDiMuonHiggsSelFlag = cms.EDProducer(
    "DiMuonDiMuonHiggsBestCandProducer",
    src = cms.InputTag("cmgDiMuonDiMuonHiggs"),
   )

cmgDiMuonDiMuonHiggsSelFlagLD = cms.EDProducer(
     "DiMuonDiMuonHiggsLDProducer",
     src = cms.InputTag("cmgDiMuonDiMuonHiggsSelFlag")
     )

PRLHiggs4mu = cms.EDFilter(
    "DiMuonDiMuonHiggsSelector",
    src = cms.InputTag('cmgDiMuonDiMuonHiggsSelFlagLD'),
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
    cmgDiMuonDiMuonSel +
    cmgDiMuonDiMuonHiggs +
    cmgDiMuonDiMuonHiggsSelFlag +
    cmgDiMuonDiMuonHiggsSelFlagLD +
    PRLHiggs4mu
    )
