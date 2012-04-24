import FWCore.ParameterSet.Config as cms
from HZZ4lAnalysis.HZZ4lCommon.selections.quadriLepton_cfi import *

# Build cmg::DiElectronDiElectronHiggs candidates
diElectronDiMuonHiggsFactory = cms.PSet(
       inputs = cms.InputTag("cmgDiElectronDiMuon")
)

cmgDiElectronDiMuonHiggs = cms.EDFilter(
    "DiElectronDiMuonHiggsPOProducer",
    cfg = diElectronDiMuonHiggsFactory.clone(),
    cuts = cms.PSet(  # inherited from source collection
    overlap = overlap.clone(),
    mass = mass.clone(),
    )
    )

cmgDiElectronDiMuonHiggsFlag = cms.EDProducer(
    "DiElectronDiMuonHiggsBestCandProducer",
    src = cms.InputTag("cmgDiElectronDiMuonHiggs"),
    cuts = cms.PSet(
    isoOfllCouples = isoOfllCouples.clone(),
    SIP4Leptons = SIP4Leptons.clone()
    )
    )

cmgDiElectronDiMuonHiggsFlagLD = cms.EDProducer(
     "DiElectronDiMuonHiggsLDProducer",
     src = cms.InputTag("cmgDiElectronDiMuonHiggsFlag")
     )

PRLHiggs2e2mu = cms.EDFilter(
    "DiElectronDiMuonHiggsSelector",
    src = cms.InputTag('cmgDiElectronDiMuonHiggsFlag'),
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



higgs2e2muSequence = (
    cmgDiElectronDiMuonHiggs +
    cmgDiElectronDiMuonHiggsFlag +
    cmgDiElectronDiMuonHiggsFlagLD +
    PRLHiggs2e2mu
    )
