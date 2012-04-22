import FWCore.ParameterSet.Config as cms

import os

basePath = os.environ['CMSSW_BASE'] + '/src/CMGTools/Common/data/'

from CMGTools.Common.factories.cmgLepton_cfi import leptonFactory
electronFactory = cms.PSet(
       inputCollection = cms.InputTag("RhoCorrIsoSequence"),
       primaryVertexCollection = cms.InputTag("offlinePrimaryVerticesWithBS"),
       leptonFactory = leptonFactory.clone(),
       electronMVAFile = cms.string(basePath + "TMVA_BDTSimpleCat.weights.xml")
       )

from CMGTools.Common.selections.vbtfelectron_cfi import *
from CMGTools.Common.selections.cicelectron_cfi import *
from CMGTools.Common.selections.isolation_cfi import *
from HZZ4lAnalysis.HZZ4lCommon.selections.leptonCand_old_cfi import *

cmgElectron = cms.EDFilter("ElectronPOProducer",
    cfg = electronFactory.clone(),
    cuts = cms.PSet(
#     ecalDriven = cms.string('ecalDriven() == 1'),
#     isEB = cms.string('sourcePtr().isEB()'),
#     isEE = cms.string('sourcePtr().isEE()'),
#     # requires that the id variables have been filled
#     vbtf60ID      = vbtfelectron60ID.clone(),
#     vbtf70ID      = vbtfelectron70ID.clone(),
#     vbtf80ID      = vbtfelectron80ID.clone(),
#     vbtf90ID      = vbtfelectron90ID.clone(),
#     vbtf95ID      = vbtfelectron95ID.clone(),
#     vbtf60CR      = vbtfelectron60CR.clone(),
#     vbtf70CR      = vbtfelectron70CR.clone(),
#     vbtf80CR      = vbtfelectron80CR.clone(),
#     vbtf90CR      = vbtfelectron90CR.clone(),
#     vbtf95CR      = vbtfelectron95CR.clone(),       
#     veryLooseID   = cicVeryLooseID.clone(),
#     looseID       = cicLooseID.clone(),
#     mediumID      = cicMediumID.clone(),
#     tightID       = cicTightID.clone(),
#     superTightID  = cicSuperTightID.clone(),
#     veryLooseCR   = cicVeryLooseCR.clone(),
#     looseCR       = cicLooseCR.clone(),
#     mediumCR      = cicMediumCR.clone(),
#     tightCR       = cicTightCR.clone(),
#     superTightCR  = cicSuperTightCR.clone(),
#     veryLooseIP   = cicVeryLooseIP.clone(),
#     looseIP       = cicLooseIP.clone(),
#     mediumIP      = cicMediumIP.clone(),
#     tightIP       = cicTightIP.clone(),
#     superTightIP  = cicSuperTightIP.clone(),
    
    leptonCandLoose = electronCandLoose.clone(),
    leptonCandplusID = electronCandplusID.clone(),
    leptonCandInvertedSIPplusID = electronCandInvertedSIPplusID.clone(),
    leptonCandplusSIP = electronCandplusSIP.clone(),
    leptonCand = electronCand.clone(),
    leptonCandTight = electronCandTight.clone()
    )
                           )

# # Skim cmg::Electron collections to get the electron candidates
# cmgElectronSel = cms.EDFilter(
#     "CmgElectronSelector",
#     src = cms.InputTag("cmgElectron"),
#     cut = cms.string('getSelection(\"cuts_leptonCand\")')
#     )

# # Skim cmg::Electron collections to get the loose electron candidates
# softElectrons = cms.EDFilter(
#     "CmgElectronSelector",
#     src = cms.InputTag("cmgElectron"),
#     cut = cms.string('getSelection(\"cuts_leptonCandLoose\")')
#     )

# # Skim cmg::Electron collections to get the tight electron candidates
# tightElectrons = cms.EDFilter(
#     "CmgElectronSelector",
#     src = cms.InputTag("cmgElectron"),
#     cut = cms.string('getSelection(\"cuts_leptonCandTight\")')
#     )

# #Only SIP cut for Z+X control region
# invertedSIPElectrons = cms.EDFilter(
#     "CmgElectronSelector",
#     src = cms.InputTag("cmgElectron"),
#     cut =cms.string('getSelection(\"cuts_invertedSIP\")')
#     )

# Final sequence
electronSequence = cms.Sequence(
    cmgElectron 
#     softElectrons +
#     cmgElectronSel +
#     tightElectrons +
#     invertedSIPElectrons
    )
