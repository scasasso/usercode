import FWCore.ParameterSet.Config as cms
from selections.higgs2e2mu_cfi import *


# Build cmg::DiElectronDiMuonHiggs candidates
diElectronDiMuonHiggsFactory = cms.PSet(
       inputs = cms.InputTag("cmgDiElectronDiMuon")
)

cmgDiElectronDiMuonHiggs = cms.EDFilter(
    "DiElectronDiMuonHiggsPOProducer",
    cfg = diElectronDiMuonHiggsFactory.clone(),
    cuts = cms.PSet(
    PRLHiggs2e2mu = PRLHiggs2e2mu.clone()
    )
    )

cmgDiElectronDiMuonHiggsLD = cms.EDProducer(
    "DiElectronDiMuonHiggsLDProducer",
    src = cms.InputTag("cmgDiElectronDiMuonHiggs")
    )

PRLHiggs2e2mu = cms.EDFilter(
    "DiElectronDiMuonHiggsSelector",
    src = cms.InputTag('cmgDiElectronDiMuonHiggs'),
    cut = cms.string('getSelection(\"cuts_PRLHiggs2e2mu\")')
    )



higgs2e2muSequence = (
    cmgDiElectronDiMuonHiggs +
#    cmgDiElectronDiMuonHiggsLD
    PRLHiggs2e2mu
    )
