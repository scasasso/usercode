import FWCore.ParameterSet.Config as cms

zmumu = cms.PSet(
    os = cms.string('leg1().charge()*leg2().charge()<0'),
    mass = cms.string('mass() >= 60 && mass() < 120'),             
    leg1_quality = cms.string('leg1().getSelection(\"cuts_vbtfmuon\")'),
    isolation = cms.string('leg1().getSelection(\"cuts_isomuon\")'),
    leg2_quality = cms.string('leg2().getSelection(\"cuts_vbtfmuon_isGlobal\")'),
    leg1_kinematics = cms.PSet(
                               pt = cms.string('leg1().pt() > 15'),
                               eta = cms.string('fabs(leg1().eta()) < 2.1'),
                               phi = cms.string('fabs(leg1().phi()) < 10')
    ),
    leg2_kinematics = cms.PSet(
                               pt = cms.string('leg2().pt() > 10'),
                               eta = cms.string('fabs(leg2().eta()) < 2.4'),
                               phi = cms.string('fabs(leg2().phi()) < 10')
    )
)
