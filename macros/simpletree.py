from MitAna.TreeMod.bambu import mithep, analysis
from MitAna.TreeMod.sequenceable import Chain
import os

mitdata = os.environ['MIT_DATA']

from MitPhysics.SelMods.BadEventsFilterMod import badEventsFilterMod
from MitPhysics.Mods.GoodPVFilterMod import goodPVFilterMod
from MitPhysics.Mods.SeparatePileUpMod import separatePileUpMod
from MitPhysics.Mods.JetIdMod import jetIdMod

# this has to be in the same order as the HLTPaths enum
hltPaths = [
    ('Photon120', ['hltEG120HEFilter']),
    ('Photon135_PFMET100_JetIdCleaned', ['hltEG135HEFilter']),
    ('Photon165_HE10', ['hltEG165HE10Filter']),
    ('Photon175', ['hltEG175HEFilter']),
    ('Ele23_WPLoose_Gsf' if analysis.isRealData else 'Ele23_CaloIdL_TrackIdL_IsoVL', ['hltEle23WPLooseGsfTrackIsoFilter']),
    ('Ele27_eta2p1_WPLoose_Gsf' if analysis.isRealData else 'HLT_Ele27_eta2p1_WP75_Gsf', ['hltEle27WPLooseGsfTrackIsoFilter']), # filter only matches data
    ('IsoMu24_eta2p1', ['hltL3crIsoL1sMu20Eta2p1L1f0L2f10QL3f24QL3trkIsoFiltered0p09']),
    ('IsoMu27', ['hltL3crIsoL1sMu25L1f0L2f10QL3f27QL3trkIsoFiltered0p09']),
    ('PFMET170_NoiseCleaned', []),
    ('PFMETNoMu90_JetIdCleaned_PFMHTNoMu90_IDTight' if analysis.isRealData and analysis.custom['bx'] == '25ns' else 'PFMETNoMu90_NoiseCleaned_PFMHTNoMu90_IDTight', []),
    ('PFMETNoMu120_JetIdCleaned_PFMHTNoMu120_IDTight' if analysis.isRealData and analysis.custom['bx'] == '25ns' else 'PFMETNoMu120_NoiseCleaned_PFMHTNoMu120_IDTight', [])
]

hltMod = mithep.HLTMod(
    AbortIfNotAccepted = analysis.isRealData,
)
for path, filters in hltPaths:
    hltMod.AddTrigger('HLT_' + path + '_v*')

exoticMets = mithep.ExoticMetsMod()

metCorrection = mithep.MetCorrectionMod('MetCorrection',
    InputName = 'PFMet',
    OutputName = 'PFType1Met',
    JetsName = 'AKt4PFJetsCHS',
    RhoAlgo = mithep.PileupEnergyDensity.kFixedGridFastjetAll,
    MaxEMFraction = 0.9,
    SkipMuons = True
)
metCorrection.ApplyType0(False)
metCorrection.ApplyType1(True)
metCorrection.ApplyShift(False)
metCorrection.IsData(analysis.isRealData)

metCorrectionNoCHS = metCorrection.clone('MetCorrectionNoCHS',
    OutputName = 'PFType1MetNoCHS',
    JetsName = 'AKt4PFJets'
)

jetCorrection = mithep.JetCorrectionMod(
    InputName = 'AKt4PFJetsCHS',
    CorrectedJetsName = 'CorrectedJets',
    RhoAlgo = mithep.PileupEnergyDensity.kFixedGridFastjetAll
)

if analysis.custom['bx'] == '25ns':
    if analysis.isRealData:
        jecSources = [
            "Summer15_25nsV2_DATA_L1FastJet_AK4PFchs.txt",
            "Summer15_25nsV2_DATA_L2Relative_AK4PFchs.txt",
            "Summer15_25nsV2_DATA_L3Absolute_AK4PFchs.txt",
            "Summer15_25nsV2_DATA_L2L3Residual_AK4PFchs.txt"
        ]
        
        jecSourcesNoCHS = [
            "Summer15_25nsV2_DATA_L1FastJet_AK4PF.txt",
            "Summer15_25nsV2_DATA_L2Relative_AK4PF.txt",
            "Summer15_25nsV2_DATA_L3Absolute_AK4PF.txt",
            "Summer15_25nsV2_DATA_L2L3Residual_AK4PF.txt"
        ]
    else:
        jecSources = [
            "Summer15_25nsV2_MC_L1FastJet_AK4PFchs.txt",
            "Summer15_25nsV2_MC_L2Relative_AK4PFchs.txt",
            "Summer15_25nsV2_MC_L3Absolute_AK4PFchs.txt"
        ]
        
        jecSourcesNoCHS = [
            "Summer15_25nsV2_MC_L1FastJet_AK4PF.txt",
            "Summer15_25nsV2_MC_L2Relative_AK4PF.txt",
            "Summer15_25nsV2_MC_L3Absolute_AK4PF.txt"
        ]

else:
    if analysis.isRealData:
        jecSources = [
            "Summer15_50nsV5_DATA_L1FastJet_AK4PFchs.txt",
            "Summer15_50nsV5_DATA_L2Relative_AK4PFchs.txt",
            "Summer15_50nsV5_DATA_L3Absolute_AK4PFchs.txt",
            "Summer15_50nsV5_DATA_L2L3Residual_AK4PFchs.txt"
        ]
        
        jecSourcesNoCHS = [
            "Summer15_50nsV2_MC_L1FastJet_AK4PF.txt",
            "Summer15_50nsV5_DATA_L2Relative_AK4PF.txt",
            "Summer15_50nsV5_DATA_L3Absolute_AK4PF.txt",
            "Summer15_50nsV5_DATA_L2L3Residual_AK4PF.txt"
        ]
    else:
        jecSources = [
            "Summer15_50nsV5_MC_L1FastJet_AK4PFchs.txt",
            "Summer15_50nsV5_MC_L2Relative_AK4PFchs.txt",
            "Summer15_50nsV5_MC_L3Absolute_AK4PFchs.txt"
        ]
        
        jecSourcesNoCHS = [
            "Summer15_50nsV5_MC_L1FastJet_AK4PF.txt",
            "Summer15_50nsV5_MC_L2Relative_AK4PF.txt",
            "Summer15_50nsV5_MC_L3Absolute_AK4PF.txt"
        ]


jecDir = mitdata + '/JEC/'

for jec in jecSources:
    metCorrection.AddJetCorrectionFromFile(jecDir + jec)
    jetCorrection.AddCorrectionFromFile(jecDir + jec)

for jec in jecSourcesNoCHS:
    metCorrectionNoCHS.AddJetCorrectionFromFile(jecDir + jec)

baselineElectrons = mithep.ElectronIdMod('BaselineElectrons',
    InputName = 'Electrons',
    OutputName = 'BaselineElectrons',
    IdType = mithep.ElectronTools.kNoId,
    IsoType = mithep.ElectronTools.kNoIso,
    ApplyEcalFiducial = True,
    ApplyD0Cut = False,
    ApplyDZCut = False,
    PtMin = 10.,
    EtaMax = 2.5
)

looseElectronMask = baselineElectrons.clone('ElectronLooseId',
    InputName = baselineElectrons.GetOutputName(),
    OutputName = 'LooseElectronMask',
    IsFilterMode = False,
    ApplyD0Cut = True,
    ApplyDZCut = True,
    IdType = mithep.ElectronTools.kSummer15Veto,
    IsoType = mithep.ElectronTools.kSummer15VetoIso
)

mediumElectronMask = looseElectronMask.clone('ElectronMediumId',
    OutputName = 'MediumElectronMask',
    IdType = mithep.ElectronTools.kSummer15Medium,
    IsoType = mithep.ElectronTools.kSummer15MediumIso
)

tightElectronMask = looseElectronMask.clone('ElectronTightId',
    OutputName = 'TightElectronMask',
    IdType = mithep.ElectronTools.kSummer15Tight,
    IsoType = mithep.ElectronTools.kSummer15TightIso
)

tightElectrons = mithep.MaskCollectionMod('TightElectrons',
    InputName = baselineElectrons.GetOutputName(),
    MaskName = tightElectronMask.GetOutputName(),
    OutputName = 'TightElectrons'
)

baselineMuons = mithep.MuonIdMod('BaseLineMuons',
    InputName = 'Muons',
    OutputName = 'BaselineMuons',
    MuonClassType = mithep.MuonTools.kPFGlobalorTracker,
    IdType = mithep.MuonTools.kNoId,
    IsoType = mithep.MuonTools.kNoIso,
    ApplyD0Cut = False,
    ApplyDZCut = False
)

looseMuonMask = baselineMuons.clone('MuonLooseId',
    IsFilterMode = False,
    InputName = baselineMuons.GetOutputName(),
    OutputName = 'LooseMuonMask',
    IdType = mithep.MuonTools.kLoose,
    IsoType = mithep.MuonTools.kPFIsoBetaPUCorrectedLoose,
    PFNoPileupCandidatesName = 'pfNoPU',
    PFPileupCandidatesName = 'pfPU',
    ApplyD0Cut = False,
    ApplyDZCut = False
)

mediumMuonMask = looseMuonMask.clone('MuonMediumId',
    OutputName = 'MediumMuonMask',
    IdType = mithep.MuonTools.kMedium,
    IsoType = mithep.MuonTools.kPFIsoBetaPUCorrectedLoose,
    ApplyD0Cut = True,
    ApplyDZCut = True
)

tightMuonMask = looseMuonMask.clone('MuonTightId',
    OutputName = 'TightMuonMask',
    IdType = mithep.MuonTools.kTight,
    IsoType = mithep.MuonTools.kPFIsoBetaPUCorrectedTight,
    ApplyD0Cut = True,
    ApplyDZCut = True
)

tightMuons = mithep.MaskCollectionMod('TightMuons',
    InputName = baselineMuons.GetOutputName(),
    MaskName = tightMuonMask.GetOutputName(),
    OutputName = 'TightMuons'
)

vetoTaus = mithep.PFTauIdMod('VetoTauId',
    InputName = 'HPSTaus',
    OutputName = 'VetoTaus',
    PtMin = 18.,
    EtaMax = 2.3
)
vetoTaus.AddDiscriminator(mithep.PFTau.kDiscriminationByLooseCombinedIsolationDBSumPtCorr3Hits)
vetoTaus.AddDiscriminator(mithep.PFTau.kDiscriminationByTightMuonRejection3)
vetoTaus.AddDiscriminator(mithep.PFTau.kDiscriminationByMVA5TightElectronRejection)

tightTaus = mithep.PFTauIdMod('TightTauId',
    InputName = vetoTaus.GetOutputName(),
    OutputName = 'TightTaus'
)
tightTaus.AddDiscriminator(mithep.PFTau.kDiscriminationByTightCombinedIsolationDBSumPtCorr3Hits)

baselinePhotons = mithep.PhotonIdMod('BaselinePhotons',
    OutputName = 'BaselinePhotons',
    IdType = mithep.PhotonTools.kNoId,
    IsoType = mithep.PhotonTools.kNoIso,
    PtMin = 15.,
    EtaMax = 2.5
)

photonLooseId = baselinePhotons.clone('PhotonLooseId',
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

mediumPhotons = mithep.MaskCollectionMod('MediumPhotons',
    InputName = baselinePhotons.GetOutputName(),
    MaskName = photonMediumId.GetOutputName(),
    OutputName = 'MediumPhotons'
)

photonTightId = photonMediumId.clone('PhotonTightId',
    OutputName = 'PhotonTightId',
    IdType = mithep.PhotonTools.kSummer15Tight,
    IsoType = mithep.PhotonTools.kSummer15TightIso
)

jetId = jetIdMod.clone()

jetCleaning = mithep.JetCleaningMod('JetCleaning',
    CleanJetsName = 'CleanJets',
    CleanMuonsName = tightMuons.GetOutputName(),
    CleanPhotonsName = mediumPhotons.GetOutputName(),
    GoodJetsName = jetId.GetOutputName(),
    CleanElectronsName = tightElectrons.GetOutputName(),
    CleanTausName = tightTaus.GetOutputName()
)

ntuples = mithep.SimpleTreeMod(
    EventTreeName = 'events',
    AllEventTreeName = 'allevents',
    RhoAlgo = mithep.PileupEnergyDensity.kFixedGridFastjetAll,
    JetsName = jetCleaning.GetOutputName(),
    PhotonsName = baselinePhotons.GetOutputName(),
    ElectronsName = baselineElectrons.GetOutputName(),
    LooseElectronsName = looseElectronMask.GetOutputName(),
    MediumElectronsName = mediumElectronMask.GetOutputName(),
    TightElectronsName = tightElectronMask.GetOutputName(),
    MuonsName = baselineMuons.GetOutputName(),
    LooseMuonsName = looseMuonMask.GetOutputName(),
    MediumMuonsName = mediumMuonMask.GetOutputName(),
    TightMuonsName = tightMuonMask.GetOutputName(),
    TausName = vetoTaus.GetOutputName(),
    ConversionsName = mithep.Names.gkMvfConversionBrn,
    VerticesName = mithep.ModNames.gkGoodVertexesName,
    LoosePhotonName = photonLooseId.GetOutputName(),
    MediumPhotonName = photonMediumId.GetOutputName(),
    TightPhotonName = photonTightId.GetOutputName(),
    PUPFCandidatesName = separatePileUpMod.GetPFPileUpName(),
    PVPFCandidatesName = separatePileUpMod.GetPFNoPileUpName(),
    RawMetName = 'PFMet',
    T1MetName = metCorrection.GetOutputName(),
    T1NoCHSMetName = metCorrectionNoCHS.GetOutputName(),
    NHScaledMetName = exoticMets.GetNHScaledMetName(),
    CHMetName = exoticMets.GetCHMetName(),
    NHMetName = exoticMets.GetNHMetName(),
    NEMetName = exoticMets.GetNEMetName(),
    IsMC = not analysis.isRealData,
    Condition = jetCleaning
)

for iP, (path, filters) in enumerate(hltPaths):
    for f in filters:
        ntuples.AddTriggerFilterName(iP, f)
    ntuples.SetTriggerPathName(iP, path)

analysis.setSequence(
    hltMod *
    badEventsFilterMod *
    goodPVFilterMod *
    separatePileUpMod *
    baselineElectrons *
    looseElectronMask *
    mediumElectronMask *
    tightElectronMask *
    tightElectrons *
    baselineMuons *
    looseMuonMask *
    mediumMuonMask *
    tightMuonMask *
    tightMuons *
    vetoTaus *
    tightTaus *
    exoticMets *
    metCorrection *
    metCorrectionNoCHS *
    baselinePhotons *
    photonLooseId *
    photonMediumId *
    photonTightId *
    mediumPhotons *
    jetCorrection *
    jetId *
    jetCleaning +
    ntuples
)
