import FWCore.ParameterSet.Config as cms

#Electron candidates

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
    #numberOfHits = cms.string('sourcePtr().gsfTrack().trackerExpectedHitsInner().numberOfHits()<=1'),
    looseiso = cms.string('relIso() < 0.7'), #ASAP: implement hCalIso + eCalIso + UserIso / pT
    #sip = cms.string('sourcePtr().dB() < 100.'),#complaint about reco::Track reference (v3 PAT should fix it?)
    pt = cms.string('pt() > 7'),
    eta = cms.string('abs(eta()) < 2.5')
    )

#Muon Candidates
muonCand = cms.PSet(
    isGlobal = cms.string('isGlobal()'),
    #numberOfValidHits = cms.string('sourcePtr().numberOfValidHits() > 10'), #complaint about reco::Track reference (v3 PAT should fix it?)
    #sip = cms.string('sourcePtr().dB() < 100.'),#complaint about reco::Track reference (v3 PAT should fix it?)
    looseiso = cms.string('relIso() < 0.7'), #ASAP: implement hCalIso + eCalIso + UserIso / pT
    pt = cms.string('pt() > 5'),
    eta = cms.string('abs(eta()) < 2.4')
    )
