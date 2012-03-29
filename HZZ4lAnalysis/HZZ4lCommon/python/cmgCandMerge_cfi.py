import FWCore.ParameterSet.Config as cms

#Merge softMuons and softElectrons
softLeptons = cms.EDProducer(
    "CandViewMerger",
    src = cms.VInputTag(
    cms.InputTag("softMuons"),
    cms.InputTag("softElectrons")
    ),
    )

# Build DiLepton candidates (no charge requirements) merging cmg EMu, DiMuon, DiElectron collections
cmgDiLepton = cms.EDProducer(
    "CandViewMerger",
    src = cms.VInputTag(
    cms.InputTag("cmgDiMuon"),
    cms.InputTag("cmgDiElectron"),
    cms.InputTag("cmgEMuCand")
    ),
    )

# Skim cmgDiLepton to create the diLeps collection (loose cuts on leptons)
diLeps = cms.EDProducer(
    "CandViewMerger",
    src = cms.VInputTag(
    cms.InputTag("MMCand"),
    cms.InputTag("EECand"),
    cms.InputTag("EMCand")
    ),
    )

#Merge zMMECand and zEEECand
zLLECand = cms.EDProducer(
    "CandViewMerger",
    src = cms.VInputTag(
    cms.InputTag("zMMECand"),
    cms.InputTag("zEEECand")
    ),
    )

#Merge zMMMCand and zEEMCand
zLLMCand = cms.EDProducer(
    "CandViewMerger",
    src = cms.VInputTag(
    cms.InputTag("zMMMCand"),
    cms.InputTag("zEEMCand")
    ),
    )

#Merge zLLECand and zLLMCand
zLLlCand = cms.EDProducer(
    "CandViewMerger",
    src = cms.VInputTag(
    cms.InputTag("zLLECand"),
    cms.InputTag("zLLMCand")
    ),
    )

#Merge zMMemCand and zEEemCand
zLLllCand = cms.EDProducer(
    "CandViewMerger",
    src = cms.VInputTag(
    cms.InputTag("zMMemCand"),
    cms.InputTag("zEEemCand")
    ),
    )

#Final sequence for leptons
leptonMergingSequence = cms.Sequence(
    softLeptons
    )

#Final sequence for dileptons
dileptonMergingSequence = cms.Sequence(
    cmgDiLepton +
    diLeps
    )

#Final sequence for trileptons
trileptonMergingSequence = cms.Sequence(
    zLLECand +
    zLLMCand +
    zLLlCand
    )

#Final sequence for quadrileptons
quadrileptonMergingSequence = cms.Sequence(
    zLLllCand
    )
