import FWCore.ParameterSet.Config as cms

from HZZ4lAnalysis.HZZ4mu.higgs4mu_cff import higgs4muSequence
from HZZ4lAnalysis.HZZ4e.higgs4e_cff import higgs4eSequence
from HZZ4lAnalysis.HZZ2e2mu.higgs2e2mu_cff import higgs2e2muSequence

higgsSequence = (
    higgs4muSequence +
    higgs4eSequence +
    higgs2e2muSequence
    )
