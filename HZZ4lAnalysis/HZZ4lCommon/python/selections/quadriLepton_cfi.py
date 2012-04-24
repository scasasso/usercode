import FWCore.ParameterSet.Config as cms

# Preamble with a nice typing exercise

mZ2min = '12.'

mass1 = "leg1.mass() > "+mZ2min
mass2 = "sqrt( (leg1.leg1.energy()+leg2.leg2.energy)*(leg1.leg1.energy()+leg2.leg2.energy) - (leg1.leg1.px()+leg2.leg2.px)*(leg1.leg1.px()+leg2.leg2.px) - (leg1.leg1.py()+leg2.leg2.py)*(leg1.leg1.py()+leg2.leg2.py) - (leg1.leg1.pz()+leg2.leg2.pz)*(leg1.leg1.pz()+leg2.leg2.pz) ) > "+mZ2min
mass3 = "sqrt( (leg2.leg1.energy()+leg1.leg2.energy)*(leg2.leg1.energy()+leg1.leg2.energy) - (leg2.leg1.px()+leg1.leg2.px)*(leg2.leg1.px()+leg1.leg2.px) - (leg2.leg1.py()+leg1.leg2.py)*(leg2.leg1.py()+leg1.leg2.py) - (leg2.leg1.pz()+leg1.leg2.pz)*(leg2.leg1.pz()+leg1.leg2.pz) ) > "+mZ2min
mass4 = "leg2.mass() > "+mZ2min

#######################################################################
### Cuts on quadrileptons to define Higgs candidate and control regions
#######################################################################

# Mass cut on candidate
mass = cms.PSet(
    masscut = cms.string("mass()>100")
    )

# Sanity check in order to build 4 lepton candidates with 4 DIFFERENT leptons
overlap = cms.PSet(
    overlapcut = cms.string("!( deltaR(leg1.leg1.eta,leg1.leg1.phi,leg2.leg1.eta,leg2.leg1.phi) < 0.01 || "+
                            "deltaR(leg1.leg2.eta,leg1.leg2.phi,leg2.leg1.eta,leg2.leg1.phi) < 0.01 || "+
                            "deltaR(leg1.leg1.eta,leg1.leg1.phi,leg2.leg2.eta,leg2.leg2.phi) < 0.01 || "+
                            "deltaR(leg1.leg2.eta,leg1.leg2.phi,leg2.leg2.eta,leg2.leg2.phi) < 0.01 )"
                            )
    )

# 3/4 ll mass > mZ2min
massOfllCouples = cms.PSet(
    massOfllCouplescut = cms.string("("+mass1+" && "+mass2+" && "+mass3+")"   + " || " +
                          "("+mass1+" && "+mass2+" && "+mass4+")"   + " || " +
                          "("+mass1+" && "+mass3+" && "+mass4+")"   + " || " +
                          "("+mass2+" && "+mass3+" && "+mass4+")"
                          )
    )

isoOfllCouples = cms.PSet(
    isoOfllCouplescut = cms.string('leg1.leg1.sourcePtr().userFloat("RhoCorrIso") + leg1.leg2.sourcePtr().userFloat("RhoCorrIso") < 0.35 && '+
                                   'leg1.leg1.sourcePtr().userFloat("RhoCorrIso") + leg2.leg1.sourcePtr().userFloat("RhoCorrIso") < 0.35 && '+
                                   'leg1.leg1.sourcePtr().userFloat("RhoCorrIso") + leg2.leg2.sourcePtr().userFloat("RhoCorrIso") < 0.35 && '+
                                   'leg1.leg2.sourcePtr().userFloat("RhoCorrIso") + leg2.leg1.sourcePtr().userFloat("RhoCorrIso") < 0.35 && '+
                                   'leg1.leg2.sourcePtr().userFloat("RhoCorrIso") + leg2.leg2.sourcePtr().userFloat("RhoCorrIso") < 0.35 && '+
                                   'leg2.leg1.sourcePtr().userFloat("RhoCorrIso") + leg2.leg2.sourcePtr().userFloat("RhoCorrIso") < 0.35'
                                   )
    )

SIP4Leptons = cms.PSet(
    SIP4Leptonscut = cms.string('leg1.leg1.sourcePtr().userFloat("SIP3D") < 4. && '+
                                'leg1.leg2.sourcePtr().userFloat("SIP3D") < 4. && '+
                                'leg2.leg1.sourcePtr().userFloat("SIP3D") < 4. && '+
                                'leg2.leg2.sourcePtr().userFloat("SIP3D") < 4.'
                                )
    )
