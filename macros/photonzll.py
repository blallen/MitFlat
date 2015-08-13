from MitAna.TreeMod.bambu import mithep, analysis
import os

zmumu = True

mitdata = os.environ['MIT_DATA']

from MitPhysics.SelMods.BadEventsFilterMod import badEventsFilterMod
from MitPhysics.Mods.GoodPVFilterMod import goodPVFilterMod
from MitPhysics.Mods.JetIdMod import jetIdMod
from MitPhysics.Mods.MuonIdMod import muonIdMod
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

jecSources = [
    "Summer15_50nsV2_MC_L1FastJet_AK4PFchs.txt",
    "Summer15_50nsV2_MC_L2Relative_AK4PFchs.txt",
    "Summer15_50nsV2_MC_L3Absolute_AK4PFchs.txt"
]

jecSourcesNoCHS = [
    "Summer15_50nsV2_MC_L1FastJet_AK4PF.txt",
    "Summer15_50nsV2_MC_L2Relative_AK4PF.txt",
    "Summer15_50nsV2_MC_L3Absolute_AK4PF.txt"
]

for jec in jecSources:
    metCorrection.AddJetCorrectionFromFile(mitdata + '/JEC/' + jec)
    met30Correction.AddJetCorrectionFromFile(mitdata + '/JEC/' + jec)
    jetCorrection.AddCorrectionFromFile(mitdata + '/JEC/' + jec)

for jec in jecSourcesNoCHS:
    metCorrectionNoCHS.AddJetCorrectionFromFile(mitdata + '/JEC/' + jec)
    met30CorrectionNoCHS.AddJetCorrectionFromFile(mitdata + '/JEC/' + jec)

tightMuons = muonIdMod.clone('MuonTightId',
    InputName = 'Muons',
    OutputName = 'TightMuons',
    IdType = mithep.MuonTools.kMuonPOG2012CutBasedIdTight,
    IsoType = mithep.MuonTools.kPFIsoBetaPUCorrected
)

if zmumu:
    tightMuons.SetMinOutput(2)
    tightMuons.SetMaxOutput(2)

loosePhotons = photonIdMod.clone('LoosePhotons',
    OutputName = 'LoosePhotons'
)

photonLooseId = photonIdMod.clone('PhotonLooseId',
    IsFilterMode = False,
    OutputName = 'PhotonLooseId'
)

photonMediumId = photonLooseId.clone('PhotonMediumId',
    OutputName = 'PhotonMediumId',
    IdType = mithep.PhotonTools.kPhys14Medium,
    IsoType = mithep.PhotonTools.kPhys14MediumIso
)

photonTightId = photonMediumId.clone('PhotonTightId',
    OutputName = 'PhotonTightId',
    IdType = mithep.PhotonTools.kPhys14Tight,
    IsoType = mithep.PhotonTools.kPhys14TightIso
)

jetId = jetIdMod.clone()

jetCleaning = mithep.JetCleaningMod('JetCleaning',
    CleanJetsName = 'CleanJets',
    CleanMuonsName = tightMuons.GetOutputName(),
    CleanPhotonsName = loosePhotons.GetOutputName(),
    GoodJetsName = jetId.GetOutputName(),
    CleanElectronsName = '',
    CleanTausName = ''
)

photonzll = mithep.PhotonZllTree(
    EventTreeName = 'events',
    AllEventTreeName = 'allevents',
    RhoAlgo = mithep.PileupEnergyDensity.kFixedGridFastjetAll,
    JetsName = jetCleaning.GetOutputName(),
    PhotonsName = 'Photons',
    MuonsName = tightMuons.GetOutputName(),
    ElectronsName = mithep.Names.gkElectronBrn,
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
    CHMetName = exoticMets.GetCHMetName(),
    NHMetName = exoticMets.GetNHMetName(),
    NEMetName = exoticMets.GetNEMetName(),
    CHGt30MetName = exoticMets.GetCHGt30MetName(),
    NHGt30MetName = exoticMets.GetNHGt30MetName(),
    NEGt30MetName = exoticMets.GetNEGt30MetName(),
    IsMC = not analysis.isRealData,
    FillZmumu = zmumu,
    Condition = photonTightId
)

analysis.setSequence(
    badEventsFilterMod *
    goodPVFilterMod *
    separatePileUpMod *
    tightMuons *
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
    photonzll
)
