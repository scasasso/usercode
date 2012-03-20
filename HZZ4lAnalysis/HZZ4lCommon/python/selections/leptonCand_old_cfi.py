import FWCore.ParameterSet.Config as cms

#Electron candidates

#Useful functions

#electron identification
def addCiCIDSelection(var):
    cicid = cms.PSet(
        selection = cms.string('test_bit(sourcePtr().electronID(\"%s\"),0)' % var)
    )
    return cicid
  
cicVeryLooseID  = addCiCIDSelection('eidVeryLoose')
cicLooseID      = addCiCIDSelection('eidLoose')
cicMediumID     = addCiCIDSelection('eidMedium')
cicTightID      = addCiCIDSelection('eidTight')
cicSuperTightID = addCiCIDSelection('eidSuperTight')

#Electron Candidates
electronCand = cms.PSet(
    cicTight = cicTightID.clone(), #waiting to pass to MVA
    numberOfHits = cms.string('sourcePtr().gsfTrack().trackerExpectedHitsInner().numberOfHits()<=1'),
    looseiso = cms.string('sourcePtr.userFloat("RhoCorrIso") < 0.7'),
    sip = cms.string('sourcePtr().dB()/sourcePtr().edB() < 100.'),
    pt = cms.string('pt() > 7'),
    eta = cms.string('abs(eta()) < 2.5')
    )

#Muon Candidates
muonCand = cms.PSet(
    isGlobal = cms.string('isGlobal()'),
    numberOfValidHits = cms.string('isGlobal() && sourcePtr().numberOfValidHits() > 10'), #need to get rid of the complaint of undefined ref to reco::Track. It's really the most safe choice to ask the muon to be Global?
    sip = cms.string('sourcePtr().dB()/sourcePtr().edB() < 100.'),
    looseiso = cms.string('sourcePtr.userFloat("RhoCorrIso") < 0.7'),
    pt = cms.string('pt() > 5'),
    eta = cms.string('abs(eta()) < 2.4')
    )

#Loose muon candidates
muonCandLoose = cms.PSet(
    isGlobalOrTracker = cms.string('isGlobal() || isTracker()'),
    pt = cms.string('pt() > 5')
    )

#Lose electron candidates
electronCandLoose = cms.PSet(
    pt = cms.string('pt() > 5')
    )
