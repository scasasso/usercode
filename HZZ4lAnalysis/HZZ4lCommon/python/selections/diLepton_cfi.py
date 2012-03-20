import FWCore.ParameterSet.Config as cms
from leptonCand_old_cfi import *

#Z1mumu cuts
zmumu = cms.PSet(
    os = cms.string('leg1().charge()*leg2().charge()<0'),
    mass = cms.string('mass() >= 50 && mass() < 120'),             
    leg1_quality = cms.string(''),# to be implemented
    isolation = cms.string(''),
    leg2_quality = cms.string(''),# to be implemented
    leg1_kinematics = cms.PSet(
    pt = cms.string('pt() > 20')
    ),
    leg2_kinematics = cms.PSet(
    pt = cms.string('pt() > 10')
    ),
    )

#Z1ee cuts
zee = cms.PSet(
    os = cms.string('leg1().charge()*leg2().charge()<0'),
    mass = cms.string('mass() >= 50 && mass() < 120'),             
    leg1_quality = cms.string(''),# to be implemented
    isolation = cms.string(''),
    leg2_quality = cms.string(''),# to be implemented
    leg1_kinematics = cms.PSet(
    pt = cms.string('pt() > 20')
    ),
    leg2_kinematics = cms.PSet(
    pt = cms.string('pt() > 10')
    ),
    )

#zCand (zMM, zEE, zLL)
zCand = cms.PSet(
    os = cms.string('leg1().charge()*leg2().charge()<0'),
    )
