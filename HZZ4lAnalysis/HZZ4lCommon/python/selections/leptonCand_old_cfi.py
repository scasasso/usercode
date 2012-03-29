import FWCore.ParameterSet.Config as cms


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

#Loose muon candidates (soft muons)
muonCandLoose = cms.PSet(
    isGlobalOrTracker = cms.string('isGlobal() || isTracker()'),
    pt = cms.string('pt() > 5')
    )

#Loose electron candidates (soft electrons)
electronCandLoose = cms.PSet(
    pt = cms.string('pt() > 5')
    )


#Electron Candidates
electronCand = cms.PSet(
    cicTight = cicTightID.clone(), #waiting to pass to MVA
    numberOfHits = cms.string('sourcePtr().gsfTrack().trackerExpectedHitsInner().numberOfHits()<=1'),
    looseiso = cms.string('sourcePtr().trackIso() < 0.7'), #Remember to switch to UserIso ASAP
    sip = cms.string('sourcePtr().dB()/sourcePtr().edB() < 100.'),
    pt = cms.string('pt() > 7'),
    eta = cms.string('abs(eta()) < 2.5')
    )

#Muon Candidates
muonCand = cms.PSet(
    isGlobal = cms.string('isGlobal()'),
    numberOfValidHits = cms.string('isGlobal() && sourcePtr().numberOfValidHits() > 10'), #need to get rid of the complaint of undefined ref to reco::Track. It's really the most safe choice to ask the muon to be Global?
    sip = cms.string('sourcePtr().dB()/sourcePtr().edB() < 100.'),
    looseiso = cms.string('sourcePtr().trackIso() < 0.7'), #Remember to switch to UserIso ASAP
    pt = cms.string('pt() > 5'),
    eta = cms.string('abs(eta()) < 2.4')
    )

#Tight Electron Candidates (Z1)
electronCandTight = cms.PSet(
    cicTight = cicTightID.clone(), #waiting to pass to MVA
    numberOfHits = cms.string('sourcePtr().gsfTrack().trackerExpectedHitsInner().numberOfHits()<=1'),
    looseiso = cms.string('sourcePtr().trackIso() < 0.7'), #Remember to switch to UserIso ASAP
    sip = cms.string('sourcePtr().dB()/sourcePtr().edB() < 4.'),
    pt = cms.string('pt() > 10'),
    eta = cms.string('abs(eta()) < 2.5')
    )

#Tight Muon Candidates (Z1)
muonCandTight = cms.PSet(
    isGlobal = cms.string('isGlobal()'),
    numberOfValidHits = cms.string('isGlobal() && sourcePtr().numberOfValidHits() > 10'), #need to get rid of the complaint of undefined ref to reco::Track. It's really the most safe choice to ask the muon to be Global?
    sip = cms.string('sourcePtr().dB()/sourcePtr().edB() < 4.'),
    looseiso = cms.string('sourcePtr().trackIso() < 0.7'), #Remember to switch to UserIso ASAP
    pt = cms.string('pt() > 10'),
    eta = cms.string('abs(eta()) < 2.4')
    )
