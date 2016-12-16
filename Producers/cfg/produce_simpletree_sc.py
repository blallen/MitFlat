from FWCore.ParameterSet.VarParsing import VarParsing

options = VarParsing('analysis')
options.register('lumis', default = [], mult = VarParsing.multiplicity.list, mytype = VarParsing.varType.string, info = 'lumis')
options.register('fillers', default = [], mult = VarParsing.multiplicity.list, mytype = VarParsing.varType.string, info = 'Fillers')
options.register('tags', default = [], mult = VarParsing.multiplicity.list, mytype = VarParsing.varType.string, info = 'Tags')
options._tags.pop('numEvent%d')
options._tagOrder.remove('numEvent%d')
options.parseArguments()

import FWCore.ParameterSet.Config as cms

from Configuration.StandardSequences.Eras import eras

process = cms.Process('NTUPLES', eras.Run2_2016)

process.source = cms.Source('PoolSource',
    fileNames = cms.untracked.vstring(options.inputFiles)
)
if len(options.lumis) != 0:
    process.source.lumisToProcess = cms.untracked.VLuminosityBlockRange(*options.lumis)

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(options.maxEvents)
)

#process.out = cms.OutputModule('PoolOutputModule',
#    fileName = cms.untracked.string('test.root')
#)

process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')
process.GlobalTag.globaltag = '80X_dataRun2_2016SeptRepro_v6'

process.load("Configuration.Geometry.GeometryIdeal_cff")
process.load('Configuration.StandardSequences.Services_cff')
process.load("Configuration.StandardSequences.MagneticField_cff")

### SuperClusters

process.load('RecoLuminosity.LumiProducer.bunchSpacingProducer_cfi')

process.load("RecoParticleFlow.PFClusterProducer.particleFlowRecHitECAL_cfi")
process.particleFlowRecHitECAL.producers[0].src = 'reducedEcalRecHitsEB'
process.particleFlowRecHitECAL.producers[1].src = 'reducedEcalRecHitsEE'
process.particleFlowRecHitECAL.producers[0].qualityTests[1].timingCleaning = False
process.particleFlowRecHitECAL.producers[1].qualityTests[1].timingCleaning = False
process.load("RecoParticleFlow.PFClusterProducer.particleFlowRecHitPS_cfi")
process.particleFlowRecHitPS.producers[0].src = 'reducedEcalRecHitsES'
process.load("RecoParticleFlow.PFClusterProducer.particleFlowClusterECALUncorrected_cfi")
process.particleFlowClusterECALUncorrected.recHitCleaners = []
process.load("RecoParticleFlow.PFClusterProducer.particleFlowClusterPS_cfi")
process.load("RecoParticleFlow.PFClusterProducer.particleFlowClusterECAL_cfi")
process.particleFlowClusterECAL.energyCorrector.recHitsEBLabel = 'reducedEcalRecHitsEB'
process.particleFlowClusterECAL.energyCorrector.recHitsEELabel = 'reducedEcalRecHitsEE'
process.load("RecoEcal.EgammaClusterProducers.particleFlowSuperClusterECAL_cfi")
process.particleFlowSuperClusterECAL.useRegression = False

superClusterSequence = cms.Sequence(
    process.bunchSpacingProducer +
    process.particleFlowRecHitECAL +
    process.particleFlowRecHitPS +
    process.particleFlowClusterECALUncorrected +
    process.particleFlowClusterPS +
    process.particleFlowClusterECAL +
    process.particleFlowSuperClusterECAL
)

### MET Filters

process.load('RecoMET.METFilters.metFilters_cff')
process.EcalDeadCellTriggerPrimitiveFilter.taggingMode = cms.bool(True)
process.eeBadScFilter.taggingMode = cms.bool(True)
process.globalTightHalo2016Filter.taggingMode = cms.bool(True)
process.BadPFMuonFilter.taggingMode = cms.bool(True)
process.BadChargedCandidateFilter.taggingMode = cms.bool(True)

metFilterSequence = cms.Sequence(
    process.HBHENoiseFilterResultProducer +
    process.EcalDeadCellTriggerPrimitiveFilter +
    process.eeBadScFilter +
    process.globalTightHalo2016Filter +
    process.BadPFMuonFilter +
    process.BadChargedCandidateFilter
)

### NTUPLES

process.ntuples = cms.EDAnalyzer('SimpleTreeProducer',
    fillers = cms.untracked.vstring('SuperClusters', 'T1Met', 'MetFilters'),
    useTrigger = cms.untracked.bool(True),
    t1met = cms.untracked.string('pfMet'),
    superClusters = cms.untracked.string('particleFlowSuperClusterECAL:particleFlowSuperClusterECALBarrel:NTUPLES'),
    ebHits = cms.untracked.string('reducedEcalRecHitsEB'),
    eeHits = cms.untracked.string('reducedEcalRecHitsEE'),
    hbhe = cms.untracked.string('HBHENoiseFilterResultProducer:HBHENoiseFilterResult'),
    hbheIso = cms.untracked.string('HBHENoiseFilterResultProducer:HBHEIsoNoiseFilterResult'),
    ecalDeadCell = cms.untracked.string('EcalDeadCellTriggerPrimitiveFilter'),
    badsc = cms.untracked.string('eeBadScFilter'),
    globalHalo16 = cms.untracked.string('globalTightHalo2016Filter'),
    badTrack = cms.untracked.string('BadChargedCandidateFilter'),
    badMuonTrack = cms.untracked.string('BadPFMuonFilter'),
    outputFile = cms.untracked.string(options.outputFile)
)

if len(options.fillers) != 0:
    process.ntuples.fillers = options.fillers

for tagSpec in options.tags:
    prod, tag = tagSpec.split('=')
    setattr(process.ntuples, prod, tag)

process.path = cms.Path(
    superClusterSequence +
    metFilterSequence +
    process.ntuples
)

#process.ep = cms.EndPath(
#    process.out
#)
