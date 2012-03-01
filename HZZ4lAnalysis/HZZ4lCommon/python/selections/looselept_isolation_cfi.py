import FWCore.ParameterSet.Config as cms

looselept_isolation = cms.PSet(
    iso = cms.string('relIso() < 0.7')
    )
