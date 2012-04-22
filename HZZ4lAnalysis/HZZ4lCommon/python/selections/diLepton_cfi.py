import FWCore.ParameterSet.Config as cms
from leptonCand_old_cfi import *

###########
### Z1 cuts
###########

#Z1mumu cuts
z1mumu = cms.PSet(
    os = cms.string('leg1().charge()*leg2().charge()<0'),
    mass = cms.string('mass() >= 50 && mass() < 120'),             
    leg1 = cms.string('leg1().getSelection(\"cuts_leptonCandTight\")'),
    leg2 = cms.string('leg2().getSelection(\"cuts_leptonCandTight\")'),
    ptleptons = cms.string('( leg1.pt() > 20. && leg2.pt() > 10. ) || ( leg2.pt() > 20. && leg1.pt() > 10. )'),
    isolation = cms.string('leg1().sourcePtr().userFloat("RhoCorrIso") + leg2().sourcePtr().userFloat("RhoCorrIso") < 0.35') #Rho correct isolation
    )

#Z1ee cuts
z1ee = cms.PSet(
    os = cms.string('leg1().charge()*leg2().charge()<0'),
    mass = cms.string('mass() >= 50 && mass() < 120'),
    leg1 = cms.string('leg1().getSelection(\"cuts_leptonCandTight\")'),
    leg2 = cms.string('leg2().getSelection(\"cuts_leptonCandTight\")'),
    ptleptons = cms.string('( leg1.pt() > 20. && leg2.pt() > 10. ) || ( leg2.pt() > 20. && leg1.pt() > 10. )'),
    isolation = cms.string('leg1().sourcePtr().userFloat("RhoCorrIso") + leg2().sourcePtr().userFloat("RhoCorrIso") < 0.35') #Rho correct isolation
    )

###########
### Z2 cuts
###########

#Z2mumu cuts
z2mumu = cms.PSet(
    os = cms.string('leg1().charge()*leg2().charge()<0'),
    mass = cms.string('mass() >= 12 && mass() < 120'),
    leg1 = cms.string('leg1().getSelection(\"cuts_leptonCand\")'),
    leg2 = cms.string('leg2().getSelection(\"cuts_leptonCand\")')
    )

#Z2ee cuts
z2ee = cms.PSet(
    os = cms.string('leg1().charge()*leg2().charge()<0'),
    mass = cms.string('mass() >= 12 && mass() < 120'),
    leg1 = cms.string('leg1().getSelection(\"cuts_leptonCand\")'),
    leg2 = cms.string('leg2().getSelection(\"cuts_leptonCand\")')
    )

#######################################
### Dilepton cuts before best Z1 choice
#######################################

zCandplusID = cms.PSet(
    os = cms.string('leg1().charge()*leg2().charge()<0'),
    leg1 = cms.string('leg1().getSelection(\"cuts_leptonCandplusID\")'),
    leg2 = cms.string('leg2().getSelection(\"cuts_leptonCandplusID\")')
    )

###################################################
### LL cuts for extended phase space control region
###################################################
llCandplusID = cms.PSet(
    leg1 = cms.string('leg1().getSelection(\"cuts_leptonCandplusID\")'),
    leg2 = cms.string('leg2().getSelection(\"cuts_leptonCandplusID\")')
    )


##################################
### LL cuts for Z+X control region
##################################

#OS-SF
llCandplusSIPOSSF = cms.PSet(
    os = cms.string('leg1().charge()*leg2().charge()<0'),
    leg1 = cms.string('leg1().getSelection(\"cuts_leptonCandplusSIP\")'),
    leg2 = cms.string('leg2().getSelection(\"cuts_leptonCandplusSIP\")')
    )

#SS-SF
llCandplusSIPSSSF = cms.PSet(
    ss = cms.string('leg1().charge()*leg2().charge()>0'),
    leg1 = cms.string('leg1().getSelection(\"cuts_leptonCandplusSIP\")'),
    leg2 = cms.string('leg2().getSelection(\"cuts_leptonCandplusSIP\")')
    )



##########################################
### LL cuts for Zbb and tt control regions
##########################################
llCandInvertedSIPplusID = cms.PSet(
    leg1 = cms.string('leg1().getSelection(\"cuts_leptonCandInvertedSIPplusID\")'),
    leg2 = cms.string('leg2().getSelection(\"cuts_leptonCandInvertedSIPplusID\")')
    )
