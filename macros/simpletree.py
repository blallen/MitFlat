from MitAna.TreeMod.bambu import mithep, analysis
from MitAna.TreeMod.sequenceable import Chain
import os

####################################
### UTIL FUNCTIONS AND VARIABLES ###
####################################

mitdata = os.environ['MIT_DATA']

def switchBX(case25, case50):
    global analysis
    return case25 if analysis.custom['bx'] == '25ns' else case50

jecVersion = switchBX('25nsV6', '50nsV5')

if analysis.isRealData:
    jecPattern = mitdata + '/JEC/Summer15_' + jecVersion + '/Summer15_' + jecVersion + '_DATA_{level}_{jettype}.txt'
    jecLevels = ['L1FastJet', 'L2Relative', 'L3Absolute', 'L2L3Residual']

else:
    jecPattern = mitdata +'/JEC/Summer15_' + jecVersion + '/Summer15_' + jecVersion + '_MC_{level}_{jettype}.txt'
    jecLevels = ['L1FastJet', 'L2Relative', 'L3Absolute']

#########################################
### MODULES RUN WITH DEFAULT SETTINGS ###
#########################################

from MitPhysics.Mods.GoodPVFilterMod import goodPVFilterMod
from MitPhysics.Mods.SeparatePileUpMod import separatePileUpMod

#####################
### EVENT FILTERS ###
#####################

# this has to be in the same order as the HLTPaths enum
hltPaths = [
    ('Photon120', ['hltEG120HEFilter']),
    ('Photon135_PFMET100_JetIdCleaned', ['hltEG135HEFilter']),
    ('Photon165_HE10', ['hltEG165HE10Filter']),
    ('Photon175', ['hltEG175HEFilter']),
    ('Ele23_WPLoose_Gsf' if analysis.isRealData else 'Ele22_eta2p1_WP75_Gsf', ['hltEle23WPLooseGsfTrackIsoFilter']),
    ('Ele27_eta2p1_WPLoose_Gsf' if analysis.isRealData else 'HLT_Ele27_eta2p1_WP75_Gsf', ['hltEle27WPLooseGsfTrackIsoFilter']), # filter only matches data
    ('IsoMu20', ['hltL3crIsoL1sMu16L1f0L2f10QL3f20QL3trkIsoFiltered0p09']),
    ('IsoTkMu20', ['hltL3fL1sMu16L1f0Tkf20QL3trkIsoFiltered0p09']),
    ('IsoMu24_eta2p1', ['hltL3crIsoL1sMu20Eta2p1L1f0L2f10QL3f24QL3trkIsoFiltered0p09']),
    ('IsoMu27', ['hltL3crIsoL1sMu25L1f0L2f10QL3f27QL3trkIsoFiltered0p09']),
    ('PFMET170_NoiseCleaned', []),
    ('PFMETNoMu90_JetIdCleaned_PFMHTNoMu90_IDTight' if analysis.isRealData and analysis.custom['bx'] == '25ns' else 'PFMETNoMu90_NoiseCleaned_PFMHTNoMu90_IDTight', []),
    ('PFMETNoMu120_JetIdCleaned_PFMHTNoMu120_IDTight' if analysis.isRealData and analysis.custom['bx'] == '25ns' else 'PFMETNoMu120_NoiseCleaned_PFMHTNoMu120_IDTight', [])
]

hltMod = mithep.HLTMod(
    AbortIfNotAccepted = analysis.isRealData,
    ExportTrigObjects = False
)
for path, filters in hltPaths:
    hltMod.AddTrigger('HLT_' + path + '_v*')

################################
### JET/MET ID & CORRECTIONS ###
################################

jetCorrection = mithep.JetCorrectionMod('AK4JetCorrection',
    InputName = 'AKt4PFJetsCHS',
    CorrectedJetsName = 'CorrectedJets',
    RhoAlgo = mithep.PileupEnergyDensity.kFixedGridFastjetAll
)

looseAK4Jets = mithep.JetIdMod('AK4JetId',
    InputName = jetCorrection.GetOutputName(),
    OutputName = 'GoodAK4Jets',
    PFId = mithep.JetTools.kPFLoose,
    MVATrainingSet = mithep.JetIDMVA.k74CHS, # set to mithep.JetIDMVA.nMVATrainingTypes to turn off MVA
    MVACutWP = mithep.JetIDMVA.kLoose,
    MVACutsFile = os.environ['MIT_DATA'] + '/JetId/jetIDCuts_150807.dat',
    PtMin = 30.,
    EtaMax = 5.
)
looseAK4Jets.SetMVAWeightsFile(mitdata + '/JetId/TMVAClassificationCategory_BDTG.weights_jteta_0_2.xml', 0)
looseAK4Jets.SetMVAWeightsFile(mitdata + '/JetId/TMVAClassificationCategory_BDTG.weights_jteta_2_2p5.xml', 1)
looseAK4Jets.SetMVAWeightsFile(mitdata + '/JetId/TMVAClassificationCategory_BDTG.weights_jteta_2p5_3.xml', 2)
looseAK4Jets.SetMVAWeightsFile(mitdata + '/JetId/TMVAClassificationCategory_BDTG.weights_jteta_3_5.xml', 3)

metCorrection = mithep.MetCorrectionMod('MetCorrection',
    InputName = 'PFMet',
    OutputName = 'PFType1Met',
    JetsName = 'AKt4PFJetsCHS',
    RhoAlgo = mithep.PileupEnergyDensity.kFixedGridFastjetAll,
    MaxEMFraction = 0.9,
    SkipMuons = True,
    MuonGeometricMatch = True
)
metCorrection.ApplyType0(False)
metCorrection.ApplyType1(True)
metCorrection.ApplyShift(False)
metCorrection.IsData(analysis.isRealData)

for level in jecLevels:
    repl = {'level': level, 'jettype': 'AK4PFchs'}
    jetCorrection.AddCorrectionFromFile(jecPattern.format(**repl))
    metCorrection.AddJetCorrectionFromFile(jecPattern.format(**repl))

###########################
### LEPTON & PHOTON IDS ###
###########################

### ELECTRONS

baselineElectrons = mithep.ElectronIdMod('BaselineElectrons',
    InputName = mithep.Names.gkElectronBrn,
    OutputName = 'BaselineElectrons',
    IdType = mithep.ElectronTools.kNoId,
    IsoType = mithep.ElectronTools.kNoIso,
    ApplyEcalFiducial = True,
    ApplyD0Cut = False,
    ApplyDZCut = False,
    WhichVertex = 0,
    PtMin = 10.,
    EtaMax = 2.5,
    ApplyConvFilterType1 = False,
    ApplyConvFilterType2 = False,
    ApplyNExpectedHitsInnerCut = False,
    ChargeFilter = False,
    ConversionsName = 'Conversions'    
)

looseElectronId = mithep.ElectronIdMod('LooseElectronId',
    IsFilterMode = False,
    InputName = baselineElectrons.GetOutputName(),
    OutputName = 'LooseElectronId',
    IdType = mithep.ElectronTools.kSummer15Veto,
    IsoType = mithep.ElectronTools.kSummer15VetoIso,
    ApplyD0Cut = True,
    ApplyDZCut = True,
    ApplyConvFilterType1 = True,
    ApplyNExpectedHitsInnerCut = True
)

tightElectronId = looseElectronId.clone('TightElectronId',
    OutputName = 'TightElectronId',
    IdType = mithep.ElectronTools.kSummer15Tight,
    IsoType = mithep.ElectronTools.kSummer15TightIso
)

### MUONS

looseMuons = mithep.MuonIdMod('LooseMuons',
    InputName = 'Muons',
    OutputName = 'LooseMuons',
    IdType = mithep.MuonTools.kLoose,
    IsoType = mithep.MuonTools.kNoIso,
    PFNoPileupCandidatesName = 'pfNoPU',
    PFPileupCandidatesName = 'pfPU',
    ApplyD0Cut = True,
    ApplyDZCut = True,
    PtMin = 10.,
    EtaMax = 2.4
)

tightMuonId = looseMuons.clone('MuonTightId',
    IsFilterMode = False,
    InputName = looseMuons.GetOutputName(),
    OutputName = 'TightMuonId',
    IdType = mithep.MuonTools.kTight,
    IsoType = mithep.MuonTools.kPFIsoBetaPUCorrectedTight
)

### TAUS

looseTaus = mithep.PFTauIdMod('LooseTaus',
    InputName = 'HPSTaus',
    OutputName = 'LooseTaus',
    PtMin = 18.,
    EtaMax = 2.3
)
looseTaus.AddDiscriminator(mithep.PFTau.kDiscriminationByDecayModeFinding)
looseTaus.AddCutDiscriminator(mithep.PFTau.kDiscriminationByRawCombinedIsolationDBSumPtCorr3Hits, 5., False)

### PHOTONS

baselinePhotons = mithep.PhotonIdMod('BaselinePhotons',
    InputName = mithep.Names.gkPhotonBrn,
    OutputName = 'BaselinePhotons',
    IdType = mithep.PhotonTools.kNoId,
    IsoType = mithep.PhotonTools.kNoIso,
    PtMin = 30.,
    EtaMax = 3.
)

photonLooseId = mithep.PhotonIdMod('PhotonLooseId',
    IsFilterMode = False,
    InputName = baselinePhotons.GetOutputName(),
    OutputName = 'PhotonLooseId',
    IdType = mithep.PhotonTools.kSummer15Loose,
    IsoType = mithep.PhotonTools.kSummer15LooseIso
)

photonMediumId = photonLooseId.clone('PhotonMediumId',
    OutputName = 'PhotonMediumId',
    IdType = mithep.PhotonTools.kSummer15Medium,
    IsoType = mithep.PhotonTools.kSummer15MediumIso
)

photonTightId = photonLooseId.clone('PhotonTightId',
    OutputName = 'PhotonTightId',
    IdType = mithep.PhotonTools.kSummer15Tight,
    IsoType = mithep.PhotonTools.kSummer15TightIso
)

photonHighPtId = photonLooseId.clone('PhotonHighPtId',
    OutputName = 'PhotonHighPtId',
    IdType = mithep.PhotonTools.kHighPtV2,
    IsoType = mithep.PhotonTools.kHighPtV2Iso,
    PtMin = 100.
)

ntuples = mithep.SimpleTreeMod(
    EventTreeName = 'events',
    AllEventTreeName = 'allevents',
    RhoAlgo = mithep.PileupEnergyDensity.kFixedGridFastjetAll,
    JetsName = looseAK4Jets.GetOutputName(),
    PhotonsName = baselinePhotons.GetOutputName(),
    ElectronsName = baselineElectrons.GetOutputName(),
    LooseElectronsName = looseElectronId.GetOutputName(),
    TightElectronsName = tightElectronId.GetOutputName(),
    MuonsName = looseMuons.GetOutputName(),
    TightMuonsName = tightMuonId.GetOutputName(),
    TausName = looseTaus.GetOutputName(),
    ConversionsName = mithep.Names.gkMvfConversionBrn,
    VerticesName = mithep.ModNames.gkGoodVertexesName,
    LoosePhotonName = photonLooseId.GetOutputName(),
    MediumPhotonName = photonMediumId.GetOutputName(),
    TightPhotonName = photonTightId.GetOutputName(),
    HighPtPhotonName = photonHighPtId.GetOutputName(),
    RawMetName = 'PFMet',
    T1MetName = metCorrection.GetOutputName(),
    IsMC = not analysis.isRealData
)

for iP, (path, filters) in enumerate(hltPaths):
    for f in filters:
        ntuples.AddTriggerFilterName(iP, f)
    ntuples.SetTriggerPathName(iP, path)

recoChain = [
    hltMod,
    goodPVFilterMod
]

if analysis.isRealData:
    badEventsFilterMod = mithep.BadEventsFilterMod('BadEventsFilterMod',
        EEBadScFilter = True,
        HBHENoiseFilter = True,
        FillHist = True
    )

    recoChain.append(badEventsFilterMod)

else:
    generator = mithep.GeneratorMod(
        IsData = False,
        CopyArrays = False,
        MCMETName = "GenMet",
        FillHist = True
    )

    mcParticlesNoNu = mithep.MCParticleFilterMod('MCParticlesNoNu',
        InputName = mithep.Names.gkMCPartBrn,
        OutputName = 'MCParticlesNoNu',
        VetoParticleId = True
    )
    for pid in [12, 14, 16, 1000022]:
        mcParticlesNoNu.AddParticleId(pid)

    genJets = mithep.FastJetMod('GenJetsNoNu',
        InputName = mcParticlesNoNu.GetOutputName(),
        OutputJetsName = 'GenJetsNoNu',
        OutputType = mithep.kGenJet,
        ConeSize = 0.4,
        NoActiveArea = True,
        ParticleMinPt = 0.,
        JetMinPt = 3.
    )

    recoChain += [
        generator,
        mcParticlesNoNu,
        genJets
    ]

    ntuples.SetGenMetName(generator.GetMCMETName())
    ntuples.SetGenJetsName(genJets.GetOutputJetsName())

    if 'pdfrwgt' in analysis.custom and analysis.custom['pdfrwgt'] != '-':
        if analysis.custom['pdfrwgt'] == 'amc_74':
            ntuples.AddPdfReweightGroup('PDF_variation')
        elif analysis.custom['pdfrwgt'] == 'mg5_74':
            ntuples.AddPdfReweightGroup('NNPDF30_lo_as_0130.LHgrid')
        elif analysis.custom['pdfrwgt'] == 'pwhg_74':
            ntuples.AddPdfReweightId(1) # group id = 0 -> scale reweights, 1 -> pdf reweights
        else:
            print 'Unrecognized pdfrwgt option', analysis.custom['pdfrwgt']
            sys.exit(1)


recoChain += [
    separatePileUpMod,
    baselineElectrons,
    looseElectronId,
    tightElectronId,
    looseMuons,
    tightMuonId,
    looseTaus,
    metCorrection,
    baselinePhotons,
    photonLooseId,
    photonMediumId,
    photonTightId,
    photonHighPtId,
    jetCorrection,
    looseAK4Jets
]

ntuples.SetCondition(recoChain[-1])

analysis.setSequence(Chain(recoChain) + ntuples)
