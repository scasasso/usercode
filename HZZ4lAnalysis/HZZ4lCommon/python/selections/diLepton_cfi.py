import FWCore.ParameterSet.Config as cms
from leptonCand_old_cfi import *

#Z1mumu cuts
z1mumu = cms.PSet(
    os = cms.string('leg1().charge()*leg2().charge()<0'),
    mass = cms.string('mass() >= 50 && mass() < 120'),             
    leg1 = cms.string('leg1().getSelection(\"cuts_leptonCandTight\")'),# to be implemented
    leg1_revisited = cms.PSet(
    pt = cms.string('leg1().pt() > 20')
    ),
    leg2 = cms.string('leg2().getSelection(\"cuts_leptonCandTight\")'),# to be implemented
    leg2_revisited = cms.PSet(
    pt = cms.string('leg2().pt() > 10')
    ),
    isolation = cms.string('leg1().sourcePtr().userFloat("RhoCorrIso") + leg2().sourcePtr().userFloat("RhoCorrIso") < 0.35') #Rho correct isolation
    )

#Z1ee cuts
z1ee = cms.PSet(
    os = cms.string('leg1().charge()*leg2().charge()<0'),
    mass = cms.string('mass() >= 50 && mass() < 120'),             
    leg1 = cms.string('leg1().getSelection(\"cuts_leptonCandTight\")'),# to be implemented
    leg1_revisited = cms.PSet(
    pt = cms.string('leg1().pt() > 20')
    ),
    leg2 = cms.string('leg2().getSelection(\"cuts_leptonCandTight\")'),# to be implemented
    leg2_revisited = cms.PSet(
    pt = cms.string('leg2().pt() > 10')
    ),
    isolation = cms.string('leg1().sourcePtr().userFloat("RhoCorrIso") + leg2().sourcePtr().userFloat("RhoCorrIso") < 0.35') #Rho correct isolation
    )

#llCand (EMu, diLeps)
llCand = cms.PSet(
    leg1 = cms.string('leg1().getSelection(\"cuts_leptonCandLoose\")'),
    leg2 = cms.string('leg2().getSelection(\"cuts_leptonCandLoose\")')
    )

#zCand (zMM, zEE, zLL)
zCand = cms.PSet(
    os = cms.string('leg1().charge()*leg2().charge()<0'),
    leg1 = cms.string('leg1().getSelection(\"cuts_leptonCandLoose\")'),
    leg2 = cms.string('leg2().getSelection(\"cuts_leptonCandLoose\")')
    )
