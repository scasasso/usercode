import FWCore.ParameterSet.Config as cms
from selections.higgs2e2mu_cfi import *
from HZZ4lAnalysis.HZZ4lCommon.selections.quadriLepton_cfi import *


# Build cmg::DiElectronDiMuonHiggs candidates
diElectronDiMuonHiggsFactory = cms.PSet(
       inputs = cms.InputTag("cmgDiElectronDiMuon")
)

cmgDiElectronDiMuonHiggs = cms.EDFilter(
    "DiElectronDiMuonHiggsPOProducer",
    cfg = diElectronDiMuonHiggsFactory.clone(),
    cuts = cms.PSet(
    PRLHiggs2e2mu = PRLHiggs2e2mu.clone(),
    mass = mass.clone(),
    massOfllCouples = massOfllCouples.clone()
    )
    )

cmgDiElectronDiMuonHiggsFlag = cms.EDProducer(
    "DiElectronDiMuonHiggsBestCandProducer",
    src = cms.InputTag("cmgDiElectronDiMuonHiggs")
    )


# cmgDiElectronDiMuonHiggsLD = cms.EDProducer(
#     "DiElectronDiMuonHiggsLDProducer",
#     src = cms.InputTag("cmgDiElectronDiMuonHiggs")
#     )

PRLHiggs2e2mu = cms.EDFilter(
    "DiElectronDiMuonHiggsSelector",
    src = cms.InputTag('cmgDiElectronDiMuonHiggsFlag'),
    cut = cms.string('userFloat("bestH2e2m")==1 && '+
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
#    cmgDiElectronDiMuonHiggsLD
    PRLHiggs2e2mu
    )
