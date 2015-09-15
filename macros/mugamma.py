from MitAna.TreeMod.bambu import mithep, analysis
import os

mitdata = os.environ['MIT_DATA']

from MitPhysics.SelMods.BadEventsFilterMod import badEventsFilterMod
from MitPhysics.Mods.GoodPVFilterMod import goodPVFilterMod
from MitPhysics.Mods.JetIdMod import jetIdMod
from MitPhysics.Mods.ElectronIdMod import electronIdMod
from MitPhysics.Mods.MuonIdMod import muonIdMod
from MitPhysics.Mods.PFTauIdMod import pfTauIdMod
from MitPhysics.Mods.PhotonIdMod import photonIdMod
from MitPhysics.Mods.SeparatePileUpMod import separatePileUpMod

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

met30Correction = metCorrection.clone('Met30Correction',
    InputName = 'Eta30Met',
    OutputName = 'PFType1Eta30Met',
    MaxJetEta = 3.
)

met30CorrectionNoCHS = met30Correction.clone('Met30CorrectionNoCHS',
    OutputName = 'PFType1Eta30MetNoCHS',
    JetsName = 'AKt4PFJets'
)

jetCorrection = mithep.JetCorrectionMod(
    InputName = 'AKt4PFJetsCHS',
    CorrectedJetsName = 'CorrectedJets',
    RhoAlgo = mithep.PileupEnergyDensity.kFixedGridFastjetAll
)

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

jecDir = mitdata + '/JEC/'

for jec in jecSources:
    metCorrection.AddJetCorrectionFromFile(jecDir + jec)
    met30Correction.AddJetCorrectionFromFile(jecDir + jec)
    jetCorrection.AddCorrectionFromFile(jecDir + jec)

for jec in jecSourcesNoCHS:
    metCorrectionNoCHS.AddJetCorrectionFromFile(jecDir + jec)
    met30CorrectionNoCHS.AddJetCorrectionFromFile(jecDir + jec)

looseElectrons = electronIdMod.clone('LooseElectrons',
    InputName = 'Electrons',
    OutputName = 'LooseElectrons',
    IdType = mithep.ElectronTools.kSummer15Veto,
    IsoType = mithep.ElectronTools.kSummer15VetoIso
)

tightElectronMask = electronIdMod.clone('ElectronTightId',
    InputName = looseElectrons.GetOutputName(),
    OutputName = 'TightElectronMask',
    IsFilterMode = False,
    IdType = mithep.ElectronTools.kSummer15Tight,
    IsoType = mithep.ElectronTools.kSummer15TightIso
)

tightElectrons = tightElectronMask.clone('TightElectrons',
    OutputName = 'TightElectrons',
    IsFilterMode = True
)

looseMuons = muonIdMod.clone('LooseMuons',
    InputName = 'Muons',
    OutputName = 'LooseMuons',
    IdType = mithep.MuonTools.kLoose,
    IsoType = mithep.MuonTools.kNoIso
)

tightMuonMask = muonIdMod.clone('MuonTightId',
    InputName = looseMuons.GetOutputName(),
    OutputName = 'TightMuonMask',
    IsFilterMode = False,
    IdType = mithep.MuonTools.kTight,
    IsoType = mithep.MuonTools.kPFIsoBetaPUCorrectedTight
)

tightMuons = tightMuonMask.clone('TightMuons',
    OutputName = 'TightMuons',
    IsFilterMode = True
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

loosePhotons = photonIdMod.clone('LoosePhotons',
    OutputName = 'LoosePhotons'
)

photonLooseId = photonIdMod.clone('PhotonLooseId',
    IsFilterMode = False,
    OutputName = 'PhotonLooseId'
)

photonMediumId = photonLooseId.clone('PhotonMediumId',
    OutputName = 'PhotonMediumId',
    IdType = mithep.PhotonTools.kSummer15Medium,
    IsoType = mithep.PhotonTools.kSummer15MediumIso
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
    CleanPhotonsName = loosePhotons.GetOutputName(),
    GoodJetsName = jetId.GetOutputName(),
    CleanElectronsName = tightElectrons.GetOutputName(),
    CleanTausName = tightTaus.GetOutputName()
)

ntuples = mithep.MuGammaTree(
    EventTreeName = 'events',
    AllEventTreeName = 'allevents',
    RhoAlgo = mithep.PileupEnergyDensity.kFixedGridFastjetAll,
    JetsName = jetCleaning.GetOutputName(),
    PhotonsName = 'Photons',
    ElectronsName = looseElectrons.GetOutputName(),
    TightElectronsName = tightElectronMask.GetOutputName(),
    MuonsName = looseMuons.GetOutputName(),
    TightMuonsName = tightMuonMask.GetOutputName(),
    TausName = vetoTaus.GetOutputName(),
    ConversionsName = mithep.Names.gkMvfConversionBrn,
    VerticesName = mithep.ModNames.gkGoodVertexesName,
    LoosePhotonName = photonLooseId.GetOutputName(),
    MediumPhotonName = photonMediumId.GetOutputName(),
    TightPhotonName = photonTightId.GetOutputName(),
    RawMetName = 'PFMet',
    T1MetName = metCorrection.GetOutputName(),
    T1NoCHSMetName = metCorrectionNoCHS.GetOutputName(),
    Eta30MetName = exoticMets.GetEta30MetName(),
    Eta30T1MetName = met30Correction.GetOutputName(),
    Eta30T1NoCHSMetName = met30CorrectionNoCHS.GetOutputName(),
    NHScaledMetName = exoticMets.GetNHScaledMetName(),
    CHMetName = exoticMets.GetCHMetName(),
    NHMetName = exoticMets.GetNHMetName(),
    NEMetName = exoticMets.GetNEMetName(),
    CHGt30MetName = exoticMets.GetCHGt30MetName(),
    NHGt30MetName = exoticMets.GetNHGt30MetName(),
    NEGt30MetName = exoticMets.GetNEGt30MetName(),
    IsMC = not analysis.isRealData,
    Condition = jetCleaning
)

analysis.setSequence(
    badEventsFilterMod *
    goodPVFilterMod *
    separatePileUpMod *
    looseElectrons *
    tightElectronMask *
    tightElectrons *
    looseMuons *
    tightMuonMask *
    tightMuons *
    vetoTaus *
    tightTaus *
    exoticMets *
    metCorrection *
    metCorrectionNoCHS *
    met30Correction *
    met30CorrectionNoCHS *
    loosePhotons *
    photonLooseId *
    photonMediumId *
    photonTightId *
    jetCorrection *
    jetId *
    jetCleaning +
    ntuples
)
