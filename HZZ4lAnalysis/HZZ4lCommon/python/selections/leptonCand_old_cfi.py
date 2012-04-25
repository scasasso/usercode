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

###########################################
### Lepton  candidates for LLLL collections
###########################################

#Loose muon candidates (soft muons)
muonCandLoose = cms.PSet(
    isGlobalOrTracker = cms.string('isGlobal() || isTracker()'),
    pt = cms.string('pt() > 5')
    )

#Loose electron candidates (soft electrons)
electronCandLoose = cms.PSet(
    pt = cms.string('pt() > 7')
    )


########################################################
### Lepton candidates for extended phase space selection
########################################################

#Adding ID
muonCandplusID = cms.PSet(
    #isGlobalOrTracker = cms.string('isGlobal() || isTracker()'),
    pt = cms.string('pt() > 5'),
    isGlobal = cms.string('isGlobal()'),
    numberOfValidHits = cms.string('isGlobal() && sourcePtr().numberOfValidHits() > 10'), #need to get rid of the complaint of undefined ref to reco::Track. It's really the most safe choice to ask the muon to be Global?
    looseiso = cms.string('sourcePtr().userFloat("User1TkIso")/pt() < 0.7'), #Remember to switch to UserIso ASAP
    sipsanity = cms.string('sourcePtr().userFloat("SIP3D") < 100.'),
    eta = cms.string('abs(eta()) < 2.4')
    )

electronCandplusID = cms.PSet(
    pt = cms.string('pt() > 7'),
    cicTight = cicTightID.clone(), #waiting to pass to MVA
    numberOfHits = cms.string('sourcePtr().gsfTrack().trackerExpectedHitsInner().numberOfHits()<=1'),
    looseiso = cms.string('sourcePtr().userFloat("User1TkIso")/pt() < 0.7'), #Remember to switch to UserIso ASAP
    sipsanity = cms.string('sourcePtr().userFloat("SIP3D") < 100.'),
    eta = cms.string('abs(eta()) < 2.5')
    )



##############################################################
### Lepton candidates for Zbb and tt control regions selection
##############################################################

#Inverted SIP and ID
muonCandInvertedSIPplusID = cms.PSet(
    isGlobalOrTracker = cms.string('isGlobal() || isTracker()'),
    pt = cms.string('pt() > 5'),
    isGlobal = cms.string('isGlobal()'),
    numberOfValidHits = cms.string('isGlobal() && sourcePtr().numberOfValidHits() > 10'), #need to get rid of the complaint of undefined ref to reco::Track. It's really the most safe choice to ask the muon to be Global?
    sip = cms.string('sourcePtr().userFloat("SIP3D") > 5.')
    )

electronCandInvertedSIPplusID = cms.PSet(
    pt = cms.string('pt() > 7'),
    cicTight = cicTightID.clone(), #waiting to pass to MVA
    numberOfHits = cms.string('sourcePtr().gsfTrack().trackerExpectedHitsInner().numberOfHits()<=1'),
    sip = cms.string('sourcePtr().userFloat("SIP3D") > 5.')
    )

#######################################################
### Lepton candidates for Z+X control regions selection
#######################################################

muonCandplusSIP = cms.PSet(
    isGlobalOrTracker = cms.string('isGlobal() || isTracker()'),
    pt = cms.string('pt() > 5'),
    sip = cms.string('sourcePtr().userFloat("SIP3D") < 4.')
    )

electronCandplusSIP = cms.PSet(
    pt = cms.string('pt() > 7'),
    sip = cms.string('sourcePtr().userFloat("SIP3D") < 4.')
    )

######################################
### Lepton candidates for Z2 selection
######################################

#Electron Candidates (Z2)
electronCand = cms.PSet(
    cicTight = cicTightID.clone(), #waiting to pass to MVA
    numberOfHits = cms.string('sourcePtr().gsfTrack().trackerExpectedHitsInner().numberOfHits()<=1'),
    looseiso = cms.string('sourcePtr().userFloat("User1TkIso")/pt() < 0.7'), #Remember to switch to UserIso ASAP
    sip = cms.string('sourcePtr().userFloat("SIP3D") < 4.'),
    pt = cms.string('pt() > 7'),
    eta = cms.string('abs(eta()) < 2.5')
    )

#Muon Candidates (Z2)
muonCand = cms.PSet(
    isGlobal = cms.string('isGlobal()'),
    numberOfValidHits = cms.string('isGlobal() && sourcePtr().numberOfValidHits() > 10'), #need to get rid of the complaint of undefined ref to reco::Track. It's really the most safe choice to ask the muon to be Global?
    sip = cms.string('sourcePtr().userFloat("SIP3D") < 4.'),
    looseiso = cms.string('sourcePtr().userFloat("User1TkIso")/pt() < 0.7'), #Remember to switch to UserIso ASAP
    pt = cms.string('pt() > 5'),
    eta = cms.string('abs(eta()) < 2.4')
    )

######################################
### Lepton candidates for Z1 selection
######################################

#Tight Electron Candidates (Z1)
electronCandTight = cms.PSet(
    cicTight = cicTightID.clone(), #waiting to pass to MVA
    numberOfHits = cms.string('sourcePtr().gsfTrack().trackerExpectedHitsInner().numberOfHits()<=1'),
    looseiso = cms.string('sourcePtr().userFloat("User1TkIso")/pt() < 0.7'), #Remember to switch to UserIso ASAP
    sip = cms.string('sourcePtr().userFloat("SIP3D") < 4.'),
    pt = cms.string('pt() > 10'),
    eta = cms.string('abs(eta()) < 2.5')
    )

#Tight Muon Candidates (Z1)
muonCandTight = cms.PSet(
    isGlobal = cms.string('isGlobal()'),
    numberOfValidHits = cms.string('isGlobal() && sourcePtr().numberOfValidHits() > 10'), #need to get rid of the complaint of undefined ref to reco::Track. It's really the most safe choice to ask the muon to be Global?
    sip = cms.string('sourcePtr().userFloat("SIP3D") < 4.'),
    looseiso = cms.string('sourcePtr().userFloat("User1TkIso")/pt() < 0.7'), #Remember to switch to UserIso ASAP
    pt = cms.string('pt() > 10'),
    eta = cms.string('abs(eta()) < 2.4')
    )
