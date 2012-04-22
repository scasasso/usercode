import FWCore.ParameterSet.Config as cms
from selections.higgs4e_cfi import *

# Build cmg::DiElectronDiElectronHiggs candidates
diElectronDiElectronHiggsFactory = cms.PSet(
       inputs = cms.InputTag("cmgDiElectronDiElectron")
)

cmgDiElectronDiElectronHiggs = cms.EDFilter(
    "DiElectronDiElectronHiggsPOProducer",
    cfg = diElectronDiElectronHiggsFactory.clone(),
    cuts = cms.PSet(
    PRLHiggs4e = PRLHiggs4e.clone()
    )
    )

cmgDiElectronDiElectronHiggsLD = cms.EDProducer(
    "DiElectronDiElectronHiggsLDProducer",
    src = cms.InputTag("cmgDiElectronDiElectronHiggs")
    )

PRLHiggs4e = cms.EDFilter(
    "DiElectronDiElectronHiggsSelector",
    src = cms.InputTag('cmgDiElectronDiElectronHiggs'),
    cut = cms.string('getSelection(\"cuts_PRLHiggs4e\")')
    )





higgs4eSequence = (
    cmgDiElectronDiElectronHiggs +
#    cmgDiElectronDiElectronHiggsLD
    PRLHiggs4e
    )
