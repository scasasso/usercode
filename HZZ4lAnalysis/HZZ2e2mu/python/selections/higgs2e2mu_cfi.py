import FWCore.ParameterSet.Config as cms

mZ2min = '12.'

mass1 = "leg1.mass() > "+mZ2min
mass2 = "sqrt( (leg1.leg1.energy()+leg2.leg2.energy)*(leg1.leg1.energy()+leg2.leg2.energy) - (leg1.leg1.px()+leg2.leg2.px)*(leg1.leg1.px()+leg2.leg2.px) - (leg1.leg1.py()+leg2.leg2.py)*(leg1.leg1.py()+leg2.leg2.py) - (leg1.leg1.pz()+leg2.leg2.pz)*(leg1.leg1.pz()+leg2.leg2.pz) ) > "+mZ2min
mass3 = "sqrt( (leg2.leg1.energy()+leg1.leg2.energy)*(leg2.leg1.energy()+leg1.leg2.energy) - (leg2.leg1.px()+leg1.leg2.px)*(leg2.leg1.px()+leg1.leg2.px) - (leg2.leg1.py()+leg1.leg2.py)*(leg2.leg1.py()+leg1.leg2.py) - (leg2.leg1.pz()+leg1.leg2.pz)*(leg2.leg1.pz()+leg1.leg2.pz) ) > "+mZ2min
mass4 = "leg2.mass() > "+mZ2min


#PRL Higgs candidate selection
PRLHiggs2e2mu = cms.PSet(
    mass = cms.string("mass()>100"),
    z1 = cms.string('leg1().getSelection(\"cuts_z1ee\") || leg2().getSelection(\"cuts_z1mumu\")'),
    z2 = cms.string('leg1().getSelection(\"cuts_z2ee\") || leg2().getSelection(\"cuts_z2mumu\")'),
    masscomb = cms.string("("+mass1+" && "+mass2+" && "+mass3+")"   + " || " +
                          "("+mass1+" && "+mass2+" && "+mass4+")"   + " || " +
                          "("+mass1+" && "+mass3+" && "+mass4+")"   + " || " +
                          "("+mass2+" && "+mass3+" && "+mass4+")"
                          )
    )
