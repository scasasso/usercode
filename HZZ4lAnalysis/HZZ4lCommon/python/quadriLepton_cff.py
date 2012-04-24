import FWCore.ParameterSet.Config as cms

from CMGTools.Common.factories.cmgDiObject_cfi import diObjectFactory
from HZZ4lAnalysis.HZZ4mu.higgs4mu_cff import *
from HZZ4lAnalysis.HZZ4e.higgs4e_cff import *
from HZZ4lAnalysis.HZZ2e2mu.higgs2e2mu_cff import *
from HZZ4lAnalysis.HZZ4lCommon.selections.quadriLepton_cfi import *

#############################
### Basic 4 lepton candidates
#############################

# MMEM
mmemFactory = diObjectFactory.clone(
       leg1Collection = cms.InputTag("ZCandFlag","cmgDiMuon"),
       leg2Collection = cms.InputTag("cmgEMu"),
       metCollection = cms.InputTag("")
       )

cmgDiMuonEMu = cms.EDFilter(
    "DiMuonEMuPOProducer",
    cfg = mmemFactory.clone(),
    cuts = cms.PSet(
    mass = mass.clone(),
    overlap = overlap.clone(),
    massOfllCouples = massOfllCouples.clone()
    )
    )

# EEEM
eeemFactory = diObjectFactory.clone(
       leg1Collection = cms.InputTag("ZCandFlag","cmgDiElectron"),
       leg2Collection = cms.InputTag("cmgEMu"),
       metCollection = cms.InputTag("")
       )

cmgDiElectronEMu = cms.EDFilter(
    "DiElectronEMuPOProducer",
    cfg = eeemFactory.clone(),
    cuts = cms.PSet(
    mass = mass.clone(),
    overlap = overlap.clone(),
    massOfllCouples = massOfllCouples.clone()
    )
    )

# MMMM
mmmmFactory = diObjectFactory.clone(
       leg1Collection = cms.InputTag("ZCandFlag","cmgDiMuon"),
       leg2Collection = cms.InputTag("ZCandFlag","cmgDiMuon"),
       metCollection = cms.InputTag("")
       )

cmgDiMuonDiMuon = cms.EDFilter(
    "DiMuonDiMuonPOProducer",
    cfg = mmmmFactory.clone(),
    cuts = cms.PSet(
    mass = mass.clone(),
    overlap = overlap.clone(),
    massOfllCouples = massOfllCouples.clone()
    )
    )

# EEEE
eeeeFactory = diObjectFactory.clone(
       leg1Collection = cms.InputTag("ZCandFlag","cmgDiElectron"),
       leg2Collection = cms.InputTag("ZCandFlag","cmgDiElectron"),
       metCollection = cms.InputTag("")
       )

cmgDiElectronDiElectron = cms.EDFilter(
    "DiElectronDiElectronPOProducer",
    cfg = eeeeFactory.clone(),
    cuts = cms.PSet(
    mass = mass.clone(),
    overlap = overlap.clone(),
    massOfllCouples = massOfllCouples.clone()
    )
    )

# EEMM
eemmFactory = diObjectFactory.clone(
       leg1Collection = cms.InputTag("ZCandFlag","cmgDiElectron"),
       leg2Collection = cms.InputTag("ZCandFlag","cmgDiMuon"),
       metCollection = cms.InputTag("")
       )

cmgDiElectronDiMuon = cms.EDFilter(
    "DiElectronDiMuonPOProducer",
    cfg = eemmFactory.clone(),
    cuts = cms.PSet(
    mass = mass.clone(),
    massOfllCouples = massOfllCouples.clone()
    )
    )

##############################################
### 4 lepton candidates for Z+X control region
##############################################

# Z1(MM)+MM SS
Z1MMMMSSCand = cms.EDFilter(
    "DiMuonDiMuonSelector",
    src = cms.InputTag("cmgDiMuonDiMuon"),
    cut = cms.string("leg1.getSelection(\'cuts_z1mumu\') && leg2.getSelection(\'cuts_llCandplusSIPSSSF\') && getSelection(\'cuts_mass\') && getSelection(\'cuts_overlap\') && getSelection(\'cuts_massOfllCouples\')")
    )

# Z1(MM)+EE SS
Z1MMEESSCand = cms.EDFilter(
    "DiElectronDiMuonSelector",
    src = cms.InputTag("cmgDiElectronDiMuon"),
    cut = cms.string("leg2.getSelection(\'cuts_z1mumu\') && leg1.getSelection(\'cuts_llCandplusSIPSSSF\') && getSelection(\'cuts_mass\') && getSelection(\'cuts_massOfllCouples\')")
    )

# Z1(EE)+EE SS
Z1EEEESSCand = cms.EDFilter(
    "DiElectronDiElectronSelector",
    src = cms.InputTag("cmgDiElectronDiElectron"),
    cut = cms.string("leg1.getSelection(\'cuts_z1ee\') && leg2.getSelection(\'cuts_llCandplusSIPSSSF\') && getSelection(\'cuts_mass\') && getSelection(\'cuts_overlap\') && getSelection(\'cuts_massOfllCouples\')")
    )

# Z1(EE)+MM SS
Z1EEMMSSCand = cms.EDFilter(
    "DiElectronDiMuonSelector",
    src = cms.InputTag("cmgDiElectronDiMuon"),
    cut = cms.string("leg1.getSelection(\'cuts_z1ee\') && leg2.getSelection(\'cuts_llCandplusSIPSSSF\') && getSelection(\'cuts_mass\') && getSelection(\'cuts_massOfllCouples\')")
    )

# Z1(MM)+MM OS
Z1MMMMOSCand = cms.EDFilter(
    "DiMuonDiMuonSelector",
    src = cms.InputTag("cmgDiMuonDiMuon"),
    cut = cms.string("leg1.getSelection(\'cuts_z1mumu\') && leg2.getSelection(\'cuts_llCandplusSIPOSSF\') && getSelection(\'cuts_mass\') && getSelection(\'cuts_overlap\') && getSelection(\'cuts_massOfllCouples\')")
    )

# Z1(MM)+EE OS
Z1MMEEOSCand = cms.EDFilter(
    "DiElectronDiMuonSelector",
    src = cms.InputTag("cmgDiElectronDiMuon"),
    cut = cms.string("leg2.getSelection(\'cuts_z1mumu\') && leg1.getSelection(\'cuts_llCandplusSIPOSSF\') && getSelection(\'cuts_mass\') && getSelection(\'cuts_massOfllCouples\')")
    )

# Z1(EE)+EE OS
Z1EEEEOSCand = cms.EDFilter(
    "DiElectronDiElectronSelector",
    src = cms.InputTag("cmgDiElectronDiElectron"),
    cut = cms.string("leg1.getSelection(\'cuts_z1ee\') && leg2.getSelection(\'cuts_llCandplusSIPOSSF\') && getSelection(\'cuts_mass\') && getSelection(\'cuts_overlap\') && getSelection(\'cuts_massOfllCouples\')")
    )

# Z1(EE)+MM OS
Z1EEMMOSCand = cms.EDFilter(
    "DiElectronDiMuonSelector",
    src = cms.InputTag("cmgDiElectronDiMuon"),
    cut = cms.string("leg1.getSelection(\'cuts_z1ee\') && leg2.getSelection(\'cuts_llCandplusSIPOSSF\') && getSelection(\'cuts_mass\') && getSelection(\'cuts_massOfllCouples\')")
    )

#####################################################
### 4 lepton candidates for Zbb and tt control region
#####################################################

# Z1(MM)+MM (inverted SIP) 
Z1MMMMInvSIPCand = cms.EDFilter(
    "DiMuonDiMuonSelector",
    src = cms.InputTag("cmgDiMuonDiMuon"),
    cut = cms.string("leg1.getSelection(\'cuts_z1mumu\') && leg2.getSelection(\'cuts_llCandInvertedSIPplusID\') && getSelection(\'cuts_overlap\')")
    )

# Z1(MM)+EE (inverted SIP)
Z1MMEEInvSIPCand = cms.EDFilter(
    "DiElectronDiMuonSelector",
    src = cms.InputTag("cmgDiElectronDiMuon"),
    cut = cms.string("leg2.getSelection(\'cuts_z1mumu\') && leg1.getSelection(\'cuts_llCandInvertedSIPplusID\')")
    )

# Z1(EE)+EE (inverted SIP)
Z1EEEEInvSIPCand = cms.EDFilter(
    "DiElectronDiElectronSelector",
    src = cms.InputTag("cmgDiElectronDiElectron"),
    cut = cms.string("leg1.getSelection(\'cuts_z1ee\') && leg2.getSelection(\'cuts_llCandInvertedSIPplusID\') && getSelection(\'cuts_overlap\')")
    )

# Z1(EE)+MM (inverted SIP)
Z1EEMMInvSIPCand = cms.EDFilter(
    "DiElectronDiMuonSelector",
    src = cms.InputTag("cmgDiElectronDiMuon"),
    cut = cms.string("leg1.getSelection(\'cuts_z1ee\') && leg2.getSelection(\'cuts_llCandInvertedSIPplusID\')")
    )

# Z1(EE)+EM (inverted SIP)
Z1EEEMInvSIPCand = cms.EDFilter(
    "DiElectronEMuSelector",
    src = cms.InputTag("cmgDiElectronEMu"),
    cut = cms.string("leg1.getSelection(\'cuts_z1ee\') && leg2.getSelection(\'cuts_llCandInvertedSIPplusID\') && getSelection(\'cuts_overlap\')")
    )

# Z1(MM)+EM (inverted SIP)
Z1MMEMInvSIPCand = cms.EDFilter(
    "DiMuonEMuSelector",
    src = cms.InputTag("cmgDiMuonEMu"),
    cut = cms.string("leg1.getSelection(\'cuts_z1mumu\') && leg2.getSelection(\'cuts_llCandInvertedSIPplusID\') && getSelection(\'cuts_overlap\')")
    )

###############################################################
### 4 lepton candidates for extended phase space control region
###############################################################

# Z1(MM)+MM (plus ID) 
Z1MMMMplusIDCand = cms.EDFilter(
    "DiMuonDiMuonSelector",
    src = cms.InputTag("cmgDiMuonDiMuon"),
    cut = cms.string("leg1.getSelection(\'cuts_z1mumu\') && leg2.getSelection(\'cuts_llCandplusID\') && getSelection(\'cuts_overlap\')")
    )

# Z1(MM)+EE (plus ID)
Z1MMEEplusIDCand = cms.EDFilter(
    "DiElectronDiMuonSelector",
    src = cms.InputTag("cmgDiElectronDiMuon"),
    cut = cms.string("leg2.getSelection(\'cuts_z1mumu\') && leg1.getSelection(\'cuts_llCandplusID\')")
    )

# Z1(EE)+EE (plus ID)
Z1EEEEplusIDCand = cms.EDFilter(
    "DiElectronDiElectronSelector",
    src = cms.InputTag("cmgDiElectronDiElectron"),
    cut = cms.string("leg1.getSelection(\'cuts_z1ee\') && leg2.getSelection(\'cuts_llCandplusID\') && getSelection(\'cuts_overlap\')")
    )

# Z1(EE)+MM (plus ID)
Z1EEMMplusIDCand = cms.EDFilter(
    "DiElectronDiMuonSelector",
    src = cms.InputTag("cmgDiElectronDiMuon"),
    cut = cms.string("leg1.getSelection(\'cuts_z1ee\') && leg2.getSelection(\'cuts_llCandplusID\')")
    )

# Z1(EE)+EM (plus ID)
Z1EEEMplusIDCand = cms.EDFilter(
    "DiElectronEMuSelector",
    src = cms.InputTag("cmgDiElectronEMu"),
    cut = cms.string("leg1.getSelection(\'cuts_z1ee\') && leg2.getSelection(\'cuts_llCandplusID\') && getSelection(\'cuts_overlap\')")
    )

# Z1(MM)+EM (plus ID)
Z1MMEMplusIDCand = cms.EDFilter(
    "DiMuonEMuSelector",
    src = cms.InputTag("cmgDiMuonEMu"),
    cut = cms.string("leg1.getSelection(\'cuts_z1mumu\') && leg2.getSelection(\'cuts_llCandplusID\') && getSelection(\'cuts_overlap\')")
    )




quadriLeptonSequence = (
    #basic
    cmgDiMuonEMu +
    cmgDiElectronEMu +
    cmgDiMuonDiMuon +
    cmgDiElectronDiElectron +
    cmgDiElectronDiMuon +
    #Z+X SS
    Z1MMMMSSCand +
    Z1MMEESSCand +
    Z1EEMMSSCand +
    Z1EEEESSCand +
    #Z+X OS
    Z1MMMMOSCand +
    Z1MMEEOSCand +
    Z1EEMMOSCand +
    Z1EEEEOSCand +
    #Zbb/tt
    Z1MMMMInvSIPCand +
    Z1MMEEInvSIPCand +
    Z1EEMMInvSIPCand +
    Z1EEEEInvSIPCand +
    Z1EEEMInvSIPCand +
    Z1MMEMInvSIPCand +
    #EPS
    Z1MMMMplusIDCand +
    Z1MMEEplusIDCand +
    Z1EEMMplusIDCand +
    Z1EEEEplusIDCand +
    Z1EEEMplusIDCand +
    Z1MMEMplusIDCand 
    
    )


