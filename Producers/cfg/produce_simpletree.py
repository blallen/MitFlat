from FWCore.ParameterSet.VarParsing import VarParsing

options = VarParsing('analysis')
options.parseArguments()

import FWCore.ParameterSet.Config as cms

process = cms.Process('NTUPLES')

process.source = cms.Source('PoolSource',
    fileNames = cms.untracked.vstring(options.inputFiles)
)

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(options.maxEvents)
)

process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')
process.GlobalTag.globaltag = '80X_dataRun2_Prompt_v11'

process.load("Configuration.Geometry.GeometryIdeal_cff")
process.load('Configuration.StandardSequences.Services_cff')
process.load("Configuration.StandardSequences.MagneticField_cff")

#process.out = cms.OutputModule('PoolOutputModule',
#    fileName = cms.untracked.string('test.root')
#)

from PhysicsTools.SelectorUtils.tools.vid_id_tools import setupAllVIDIdsInModule, setupVIDElectronSelection, setupVIDPhotonSelection, switchOnVIDPhotonIdProducer, switchOnVIDElectronIdProducer, DataFormat

switchOnVIDPhotonIdProducer(process, DataFormat.MiniAOD)
switchOnVIDElectronIdProducer(process, DataFormat.MiniAOD)
setupAllVIDIdsInModule(process, 'RecoEgamma.PhotonIdentification.Identification.cutBasedPhotonID_Spring15_25ns_V1_cff', setupVIDPhotonSelection)
setupAllVIDIdsInModule(process, 'RecoEgamma.ElectronIdentification.Identification.cutBasedElectronID_Spring15_25ns_V1_cff', setupVIDElectronSelection)

photonId = 'egmPhotonIDs:cutBasedPhotonID-Spring15-25ns-V1-standalone-'
photonEA = 'RecoEgamma/PhotonIdentification/data/Spring15/effAreaPhotons_cone03_'
electronId = 'egmGsfElectronIDs:cutBasedElectronID-Spring15-25ns-V1-standalone-'
electronEA = 'RecoEgamma/ElectronIdentification/data/Spring15/effAreaElectrons_cone03_'

process.ntuples = cms.EDAnalyzer('SimpleTreeProducer',
    useTrigger = cms.untracked.bool(True),
    photons = cms.untracked.string('slimmedPhotons'),
    electrons = cms.untracked.string('slimmedElectrons'),
    muons = cms.untracked.string('slimmedMuons'),
    taus = cms.untracked.string('slimmedTaus'),
    jets = cms.untracked.string('slimmedJets'),
    t1met = cms.untracked.string('slimmedMETs'),
    vertices = cms.untracked.string('offlineSlimmedPrimaryVertices'),
    superClusters = cms.untracked.string('reducedEgamma:reducedSuperClusters'),
    ebHits = cms.untracked.string('reducedEgamma:reducedEBRecHits'),
    eeHits = cms.untracked.string('reducedEgamma:reducedEERecHits'),
    rho = cms.untracked.string('fixedGridRhoFastjetAll'),
    photonLooseId = cms.untracked.string(photonId + 'loose'),
    photonMediumId = cms.untracked.string(photonId + 'medium'),
    photonTightId = cms.untracked.string(photonId + 'tight'),
    photonCHIso = cms.untracked.string('photonIDValueMapProducer:phoChargedIsolation'),
    photonNHIso = cms.untracked.string('photonIDValueMapProducer:phoNeutralHadronIsolation'),
    photonPhIso = cms.untracked.string('photonIDValueMapProducer:phoPhotonIsolation'),
    photonWCHIso = cms.untracked.string('photonIDValueMapProducer:phoWorstChargedIsolation'),
    photonCHIsoEA = cms.untracked.FileInPath(photonEA + 'pfChargedHadrons_25ns_NULLcorrection.txt'),
    photonNHIsoEA = cms.untracked.FileInPath(photonEA + 'pfNeutralHadrons_25ns_90percentBased.txt'),
    photonPhIsoEA = cms.untracked.FileInPath(photonEA + 'pfPhotons_25ns_90percentBased.txt'),
    electronVetoId = cms.untracked.string(electronId + 'veto'),
    electronLooseId = cms.untracked.string(electronId + 'loose'),
    electronMediumId = cms.untracked.string(electronId + 'medium'),
    electronTightId = cms.untracked.string(electronId + 'tight'),
    electronCombIsoEA = cms.untracked.FileInPath(electronEA + 'pfNeuHadronsAndPhotons_25ns.txt'),
#    electronEcalIsoEA = cms.untracked.FileInPath(electronEA + 'pfNeuHadronsAndPhotons_25ns.txt'), files in ikrav/cmssw:egm_id_80X-v1 RecoEgamma/ElectronIdentification/data/Summer16
#    electronHcalIsoEA = cms.untracked.FileInPath(electronEA + 'pfNeuHadronsAndPhotons_25ns.txt'),
    triggerObjects = cms.untracked.string('selectedPatTrigger'),
    triggerResults = cms.untracked.string('TriggerResults::HLT'),
    metFilters = cms.untracked.string('TriggerResults::RECO'),
    badTrack = cms.untracked.string('BadChargedCandidateSummer16Filter'),
    badMuonTrack = cms.untracked.string('BadPFMuonSummer16Filter'),
    photonL1Filters = cms.untracked.vstring(
        'hltL1sSingleEG34IorSingleEG40',
        'hltL1sSingleEG40IorSingleJet200',
        'hltL1sSingleEG34IorSingleEG40IorSingleJet200',
        'hltL1sSingleEG24',
        'hltL1sSingleEG30',
        'hltL1sSingleEG40'
    ),
    photonHLTFilters = cms.untracked.vstring(
        'hltEG120HEFilter',
        'hltEG135HEFilter',
        'hltEG165HE10Filter',
        'hltEG175HEFilter',
        'hltEG22R9Id90HE10Iso40EBOnlyTrackIsoFilter',
        'hltEG36R9Id90HE10Iso40EBOnlyTrackIsoFilter',
        'hltEG50R9Id90HE10Iso40EBOnlyTrackIsoFilter',
        'hltEG75R9Id90HE10Iso40EBOnlyTrackIsoFilter',
        'hltEG90R9Id90HE10Iso40EBOnlyTrackIsoFilter',
        'hltEG120R9Id90HE10Iso40EBOnlyTrackIsoFilter'
    ),
    electronHLTFilters = cms.untracked.vstring(
        'dummy',
        'dummy',
        'hltEG120HEFilter',
        'hltEG135HEFilter',
        'hltEG165HE10Filter',
        'hltEG175HEFilter',
        'hltEG22R9Id90HE10Iso40EBOnlyTrackIsoFilter',
        'hltEG36R9Id90HE10Iso40EBOnlyTrackIsoFilter',
        'hltEG50R9Id90HE10Iso40EBOnlyTrackIsoFilter',
        'hltEG75R9Id90HE10Iso40EBOnlyTrackIsoFilter',
        'hltEG90R9Id90HE10Iso40EBOnlyTrackIsoFilter',
        'hltEG120R9Id90HE10Iso40EBOnlyTrackIsoFilter'
    ),
    muonHLTFilters = cms.untracked.vstring(
        'hltL3crIsoL1sMu18L1f0L2f10QL3f20QL3trkIsoFiltered0p09',
        'hltL3fL1sMu18L1f0Tkf20QL3trkIsoFiltered0p09',
        'hltL3crIsoL1sMu22L1f0L2f10QL3f24QL3trkIsoFiltered0p09',
        'hltL3crIsoL1sMu22Or25L1f0L2f10QL3f27QL3trkIsoFiltered0p09'
    )
)

process.load('RecoMET.METFilters.BadPFMuonSummer16Filter_cfi')
process.BadPFMuonSummer16Filter.muons = cms.InputTag("slimmedMuons")
process.BadPFMuonSummer16Filter.PFCandidates = cms.InputTag("packedPFCandidates")
process.BadPFMuonSummer16Filter.taggingMode = cms.bool(True)

process.load('RecoMET.METFilters.BadChargedCandidateSummer16Filter_cfi')
process.BadChargedCandidateSummer16Filter.muons = cms.InputTag("slimmedMuons")
process.BadChargedCandidateSummer16Filter.PFCandidates = cms.InputTag("packedPFCandidates")
process.BadChargedCandidateSummer16Filter.taggingMode = cms.bool(True)

process.path = cms.Path(
    process.photonIDValueMapProducer +
    process.egmPhotonIDs +
    process.egmGsfElectronIDs +
    process.BadChargedCandidateSummer16Filter +
    process.BadPFMuonSummer16Filter +
    process.ntuples
)

#process.ep = cms.EndPath(
#    process.out
#)
