import FWCore.ParameterSet.Config as cms


# Build cmg::Muon object
from CMGTools.Common.factories.cmgLepton_cfi import leptonFactory
muonFactory = cms.PSet(
       inputCollection = cms.InputTag("RhoCorrIsoSequence"),
       trackType = cms.int32(0),#use the global track,
       muonIDType = cms.string("All"),#the flag for muonID
       leptonFactory = leptonFactory.clone()
       )

from CMGTools.Common.selections.isolation_cfi import isolation
from CMGTools.Common.selections.vbtfmuon_cfi import vbtfmuon
from HZZ4lAnalysis.HZZ4lCommon.selections.leptonCand_old_cfi import *

cmgMuon = cms.EDFilter("MuonPOProducer",
    cfg = muonFactory.clone(),
    cuts = cms.PSet(
    leptonCandLoose = muonCandLoose.clone(),
    leptonCandplusID = muonCandplusID.clone(),
    leptonCandInvertedSIPplusID = muonCandInvertedSIPplusID.clone(),
    leptonCandplusSIP = muonCandplusSIP.clone(),
    leptonCand = muonCand.clone(),
    leptonCandTight = muonCandTight.clone()
    )    
)

# # Skim cmg::Muon collections to get the muon candidates
# cmgMuonSel = cms.EDFilter(
#     "CmgMuonSelector",
#     src = cms.InputTag( "cmgMuon" ),
#     cut = cms.string('getSelection(\"cuts_leptonCand\")')
#     )

# # Skim cmg::Muon collections to get the loose muon candidates
# softMuons = cms.EDFilter(
#     "CmgMuonSelector",
#     src = cms.InputTag( "cmgMuon" ),
#     cut = cms.string('getSelection(\"cuts_leptonCandLoose\")')
#     )

# # Skim cmg::Muon collections to get the tight muon candidates
# tightMuons = cms.EDFilter(
#     "CmgMuonSelector",
#     src = cms.InputTag( "cmgMuon" ),
#     cut = cms.string('getSelection(\"cuts_leptonCandTight\")')
#     )


# #Only SIP cut for Z+X control region
# invertedSIPMuons = cms.EDFilter(
#     "CmgMuonSelector",
#     src = cms.InputTag("cmgMuon"),
#     cut =cms.string('getSelection(\"cuts_invertedSIP\")')
#     )

#Final sequence
muonSequence = cms.Sequence(
    cmgMuon 
#     softMuons +
#     cmgMuonSel +
#     tightMuons +
#     invertedSIPMuons
    )
