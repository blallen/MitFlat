from MitAna.TreeMod.bambu import mithep, analysis
from MitAna.TreeMod.sequenceable import Chain
import os

####################################
### UTIL FUNCTIONS AND VARIABLES ###
####################################

mitdata = os.environ['MIT_DATA']

if 'run' in analysis.custom:
    run = int(analysis.custom['run'])
else:
    run = 2

if 'bx' in analysis.custom:
    bx = analysis.custom['bx']
else:
    bx = '25ns'

def switchBX(case25, case50):
    global bx
    return case25 if bx == '25ns' else case50

def switchRun(case2, case1):
    global run
    return case2 if run == 2 else case1

rhoAlgo = switchRun(mithep.PileupEnergyDensity.kFixedGridFastjetAll, mithep.PileupEnergyDensity.kHighEta)

if run == 2:
    jecVersion = switchBX('25nsV6', '50nsV5')

    if analysis.isRealData:
        jecPattern = mitdata + '/JEC/Summer15_' + jecVersion + '/Summer15_' + jecVersion + '_DATA_{level}_{jettype}.txt'
        jecLevels = ['L1FastJet', 'L2Relative', 'L3Absolute', 'L2L3Residual']
    
    else:
        jecPattern = mitdata +'/JEC/Summer15_' + jecVersion + '/Summer15_' + jecVersion + '_MC_{level}_{jettype}.txt'
        jecLevels = ['L1FastJet', 'L2Relative', 'L3Absolute']

else:
    if analysis.isRealData:
        jecPattern = mitdata + '/JEC/Summer13_V4/Summer13_V4_DATA_{level}_{jettype}.txt'
        jecLevels = ['L1FastJet', 'L2Relative', 'L3Absolute', 'L2L3Residual']
    
    else:
        jecPattern = mitdata +'/JEC/Summer13_V4/Summer13_V4_MC_{level}_{jettype}.txt'
        jecLevels = ['L1FastJet', 'L2Relative', 'L3Absolute']


#########################################
### MODULES RUN WITH DEFAULT SETTINGS ###
#########################################

from MitPhysics.Mods.GoodPVFilterMod import goodPVFilterMod
from MitPhysics.Mods.SeparatePileUpMod import separatePileUpMod

#####################
### EVENT FILTERS ###
#####################

if run == 2:
    import ROOT
    ROOT.gSystem.Load('libMitFlatDataFormats.so')
    simpletree = ROOT.simpletree

    # this has to be in the same order as the HLTPaths enum
    hltPaths = [
        (simpletree.kPhoton120, 'Photon120'),
        (simpletree.kPhoton135MET100, 'Photon135_PFMET100_JetIdCleaned'),
        (simpletree.kPhoton165HE10, 'Photon165_HE10'),
        (simpletree.kPhoton175, 'Photon175'),
        (simpletree.kPhoton22MET40, 'Photon22_R9Id90_HE10_Iso40_EBOnly_PFMET40'),
        (simpletree.kPhoton22VBF, 'Photon22_R9Id90_HE10_Iso40_EBOnly_VBF'),
        (simpletree.kPhoton36MET40, 'Photon36_R9Id90_HE10_Iso40_EBOnly_PFMET40'),
        (simpletree.kPhoton36VBF, 'Photon36_R9Id90_HE10_Iso40_EBOnly_VBF'),
        (simpletree.kPhoton50MET40, 'Photon50_R9Id90_HE10_Iso40_EBOnly_PFMET40'),
        (simpletree.kPhoton50VBF, 'Photon50_R9Id90_HE10_Iso40_EBOnly_VBF'),
        (simpletree.kPhoton75MET40, 'Photon75_R9Id90_HE10_Iso40_EBOnly_PFMET40'),
        (simpletree.kPhoton75VBF, 'Photon75_R9Id90_HE10_Iso40_EBOnly_VBF'),
        (simpletree.kPhoton90MET40, 'Photon90_R9Id90_HE10_Iso40_EBOnly_PFMET40'),
        (simpletree.kPhoton90VBF, 'Photon90_R9Id90_HE10_Iso40_EBOnly_VBF'),
        (simpletree.kPhoton120MET40, 'Photon120_R9Id90_HE10_Iso40_EBOnly_PFMET40'),
        (simpletree.kPhoton120VBF, 'Photon120_R9Id90_HE10_Iso40_EBOnly_VBF'),
        (simpletree.kEle23Loose, 'Ele23_WPLoose_Gsf' if analysis.isRealData else 'Ele22_eta2p1_WP75_Gsf'),
        (simpletree.kEle27Loose, 'Ele27_eta2p1_WPLoose_Gsf' if analysis.isRealData else 'HLT_Ele27_eta2p1_WP75_Gsf'), # filter only matches data
        (simpletree.kMu20, 'IsoMu20'),
        (simpletree.kTrkMu20, 'IsoTkMu20'),
        (simpletree.kMu24eta2p1, 'IsoMu24_eta2p1'),
        (simpletree.kMu27, 'IsoMu27'),
        (simpletree.kMET170, 'PFMET170_NoiseCleaned'),
        (simpletree.kMETNoMu90MHTNoMu90, 'PFMETNoMu90_JetIdCleaned_PFMHTNoMu90_IDTight' if analysis.isRealData and bx == '25ns' else 'PFMETNoMu90_NoiseCleaned_PFMHTNoMu90_IDTight'),
        (simpletree.kMETNoMu120MHTNoMu120, 'PFMETNoMu120_JetIdCleaned_PFMHTNoMu120_IDTight' if analysis.isRealData and bx == '25ns' else 'PFMETNoMu120_NoiseCleaned_PFMHTNoMu120_IDTight')
    ]

    photonHLTObjects = [
        (simpletree.fPh120, 'hltEG120HEFilter'),
        (simpletree.fPh135, 'hltEG135HEFilter'),
        (simpletree.fPh165HE10, 'hltEG165HE10Filter'),
        (simpletree.fPh175, 'hltEG175HEFilter'),  
        (simpletree.fPh22EBR9Iso, 'hltEG22R9Id90HE10Iso40EBOnlyTrackIsoFilter'),
        (simpletree.fPh36EBR9Iso, 'hltEG36R9Id90HE10Iso40EBOnlyTrackIsoFilter'),
        (simpletree.fPh50EBR9Iso, 'hltEG50R9Id90HE10Iso40EBOnlyTrackIsoFilter'),
        (simpletree.fPh75EBR9Iso, 'hltEG75R9Id90HE10Iso40EBOnlyTrackIsoFilter'),
        (simpletree.fPh90EBR9Iso, 'hltEG90R9Id90HE10Iso40EBOnlyTrackIsoFilter'),
        (simpletree.fPh120EBR9Iso, 'hltEG120R9Id90HE10Iso40EBOnlyTrackIsoFilter')
    ]

    electronHLTObjects = [
        (simpletree.fEl23Loose, 'hltEle23WPLooseGsfTrackIsoFilter'),
        (simpletree.fEl27Loose, 'hltEle27WPLooseGsfTrackIsoFilter'),
        (simpletree.fEl120Ph, 'hltEG120HEFilter'),  
        (simpletree.fEl135Ph, 'hltEG135HEFilter'),  
        (simpletree.fEl165HE10Ph, 'hltEG165HE10Filter'),
        (simpletree.fEl175Ph, 'hltEG175HEFilter'),
        (simpletree.fEl22EBR9IsoPh, 'hltEG22R9Id90HE10Iso40EBOnlyTrackIsoFilter'),
        (simpletree.fEl36EBR9IsoPh, 'hltEG36R9Id90HE10Iso40EBOnlyTrackIsoFilter'),
        (simpletree.fEl50EBR9IsoPh, 'hltEG50R9Id90HE10Iso40EBOnlyTrackIsoFilter'),
        (simpletree.fEl75EBR9IsoPh, 'hltEG75R9Id90HE10Iso40EBOnlyTrackIsoFilter'),
        (simpletree.fEl90EBR9IsoPh, 'hltEG90R9Id90HE10Iso40EBOnlyTrackIsoFilter'),
        (simpletree.fEl120EBR9IsoPh, 'hltEG120R9Id90HE10Iso40EBOnlyTrackIsoFilter')
    ]

    muonHLTObjects = [
        (simpletree.fMu20, 'hltL3crIsoL1sMu16L1f0L2f10QL3f20QL3trkIsoFiltered0p09'),
        (simpletree.fMuTrk20, 'hltL3fL1sMu16L1f0Tkf20QL3trkIsoFiltered0p09'),
        (simpletree.fMu24, 'hltL3crIsoL1sMu20Eta2p1L1f0L2f10QL3f24QL3trkIsoFiltered0p09'),
        (simpletree.fMu27, 'hltL3crIsoL1sMu25L1f0L2f10QL3f27QL3trkIsoFiltered0p09')
    ]
    
else:
    hltPaths = [
        (0, 'DiPFJet40_PFMETnoMu65_MJJ600VBF_LeadingJets'),
        (1, 'DiPFJet40_PFMETnoMu65_MJJ800VBF_AllJets'),
        (2, 'IsoMu24_eta2p1'),
        (3, 'IsoMu24'),
        (4, 'Ele27_WP80')
    ]

    photonHLTObjects = []
    electronHLTObjects = []
    muonHLTObjects = []

hltMod = mithep.HLTMod(
    AbortIfNotAccepted = analysis.isRealData,
    ExportTrigObjects = False
)
for iPath, path in hltPaths:
    hltMod.AddTrigger('HLT_' + path + '_v*')

################################
### JET/MET ID & CORRECTIONS ###
################################

jetCorrection = mithep.JetCorrectionMod('JetCorrection',
    InputName = switchRun('AKt4PFJetsCHS', 'AKt5PFJets'),
    CorrectedJetsName = 'CorrectedJets',
    RhoAlgo = rhoAlgo
)

looseJets = mithep.JetIdMod('JetId',
    InputName = jetCorrection.GetOutputName(),
    OutputName = 'GoodJets',
    PFId = mithep.JetTools.kPFLoose,
    PtMin = 20.,
    EtaMax = 5.
)
if run == 2:
    looseJets.SetMVATrainingSet(mithep.JetIDMVA.k74CHS)
    looseJets.SetMVACutWP(mithep.JetIDMVA.kLoose)
    looseJets.SetMVACutsFile(os.environ['MIT_DATA'] + '/JetId/jetIDCuts_150807.dat')

    looseJets.SetMVAWeightsFile(mitdata + '/JetId/TMVAClassificationCategory_BDTG.weights_jteta_0_2.xml', 0)
    looseJets.SetMVAWeightsFile(mitdata + '/JetId/TMVAClassificationCategory_BDTG.weights_jteta_2_2p5.xml', 1)
    looseJets.SetMVAWeightsFile(mitdata + '/JetId/TMVAClassificationCategory_BDTG.weights_jteta_2p5_3.xml', 2)
    looseJets.SetMVAWeightsFile(mitdata + '/JetId/TMVAClassificationCategory_BDTG.weights_jteta_3_5.xml', 3)
else:
    looseJets.SetMVATrainingSet(mithep.JetIDMVA.nMVATypes)

jetUncertaintyUp = mithep.JetCorrectionMod('JetUncertaintyUp',
    InputName = looseJets.GetOutputName(),
    CorrectedJetsName = 'JetUncertaintyUp',
    UncertaintySigma = 1.
)

jetUncertaintyDown = mithep.JetCorrectionMod('JetUncertaintyDown',
    InputName = looseJets.GetOutputName(),
    CorrectedJetsName = 'JetUncertaintyDown',
    UncertaintySigma = -1.
)

metCorrection = mithep.MetCorrectionMod('MetCorrection',
    InputName = 'PFMet',
    OutputName = 'PFType1Met',
    JetsName = jetCorrection.GetOutputName(),
    RhoAlgo = rhoAlgo,
    MaxEMFraction = 0.9,
    SkipMuons = True,
    MuonGeometricMatch = switchRun(True, False)
)
metCorrection.ApplyType0(False)
metCorrection.ApplyType1(True)
metCorrection.ApplyShift(False)
metCorrection.IsData(analysis.isRealData)

metCorrectionJESUp = metCorrection.clone('MetCorrectionJESUp',
    OutputName = 'PFType1CorrectedMetJESUp',
    JetsName = switchRun('AKt4PFJetsCHS', 'AKt5PFJets'),
    JESUncertaintySigma = 1.
)
metCorrectionJESDown = metCorrectionJESUp.clone('MetCorrectionJESDown',
    OutputName = 'PFType1CorrectedMetJESDown',
    JESUncertaintySigma = -1.
)

metCorrectionUnclUp = metCorrection.clone('MetCorrectionUnclUp',
    OutputName = 'PFType1CorrectedMetUnclUp',
    UnclusteredVariation = 0.1
)
metCorrectionUnclUp.ApplyUnclustered(True)

metCorrectionUnclDown = metCorrectionUnclUp.clone('MetCorrectionUnclDown',
    OutputName = 'PFType1CorrectedMetUnclDown',
    UnclusteredVariation = -0.1
)

for level in jecLevels:
    repl = {'level': level, 'jettype': switchRun('AK4PFchs', 'AK5PF')}
    jetCorrection.AddCorrectionFromFile(jecPattern.format(**repl))
    metCorrectionJESUp.AddJetCorrectionFromFile(jecPattern.format(**repl))
    metCorrectionJESDown.AddJetCorrectionFromFile(jecPattern.format(**repl))

repl = {'level': 'Uncertainty', 'jettype': 'AK4PFchs'}
metCorrectionJESUp.AddJetCorrectionFromFile(jecPattern.format(**repl))
metCorrectionJESDown.AddJetCorrectionFromFile(jecPattern.format(**repl))
jetUncertaintyUp.AddCorrectionFromFile(jecPattern.format(**repl))
jetUncertaintyDown.AddCorrectionFromFile(jecPattern.format(**repl))

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

vetoElectronId = mithep.ElectronIdMod('VetoElectronId',
    IsFilterMode = False,
    InputName = baselineElectrons.GetOutputName(),
    OutputName = 'VetoElectronId',
    IdType = mithep.ElectronTools.kSummer15Veto,
    IsoType = mithep.ElectronTools.kSummer15VetoIso,
    ApplyD0Cut = True,
    ApplyDZCut = True,
    ApplyConvFilterType1 = True,
    ApplyNExpectedHitsInnerCut = True
)

looseElectronId = vetoElectronId.clone('LooseElectronId',
    OutputName = 'LooseElectronId',
    IdType = mithep.ElectronTools.kSummer15Loose,
    IsoType = mithep.ElectronTools.kSummer15LooseIso
)

tightElectronId = vetoElectronId.clone('TightElectronId',
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
    PFNoPileupCandidatesName = separatePileUpMod.GetPFNoPileUpName(),
    PFPileupCandidatesName = separatePileUpMod.GetPFPileUpName(),
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
looseTaus.AddDiscriminator(mithep.PFTau.iDecayModeFinding)
looseTaus.AddCutDiscriminator(mithep.PFTau.dByCombinedIsolationDeltaBetaCorrRaw3Hits, 5., False)

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
    IdType = mithep.PhotonTools.kSpring15Loose,
    IsoType = mithep.PhotonTools.kSpring15LooseIso
)

photonMediumId = photonLooseId.clone('PhotonMediumId',
    OutputName = 'PhotonMediumId',
    IdType = mithep.PhotonTools.kSpring15Medium,
    IsoType = mithep.PhotonTools.kSpring15MediumIso
)

photonTightId = photonLooseId.clone('PhotonTightId',
    OutputName = 'PhotonTightId',
    IdType = mithep.PhotonTools.kSpring15Tight,
    IsoType = mithep.PhotonTools.kSpring15TightIso
)

photonHighPtId = photonLooseId.clone('PhotonHighPtId',
    OutputName = 'PhotonHighPtId',
    IdType = mithep.PhotonTools.kHighPtV2,
    IsoType = mithep.PhotonTools.kHighPtV2Iso,
    PtMin = 100.
)

ntuples = mithep.SimpleTreeMod(
    EventTreeName = 'events',
    RhoAlgo = rhoAlgo,
    JetsName = looseJets.GetOutputName(),
    JetsCorrUpName = jetUncertaintyUp.GetOutputName(),
    JetsCorrDownName = jetUncertaintyDown.GetOutputName(),
    PhotonsName = baselinePhotons.GetOutputName(),
    PhotonIsoType = mithep.PhotonTools.kSpring15MediumIso,
    ElectronsName = baselineElectrons.GetOutputName(),
    VetoElectronsName = vetoElectronId.GetOutputName(),
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
    PileupCandsName = separatePileUpMod.GetPFPileUpName(),
    RawMetName = 'PFMet',
    T1MetName = metCorrection.GetOutputName(),
    CorrUpMetName = metCorrectionJESUp.GetOutputName(),
    CorrDownMetName = metCorrectionJESDown.GetOutputName(),
    UnclUpMetName = metCorrectionUnclUp.GetOutputName(),
    UnclDownMetName = metCorrectionUnclDown.GetOutputName(),
    IsMC = not analysis.isRealData
)

if analysis.book.endswith('044') or ('usehlt' in analysis.custom and not analysis.custom['usehlt']):
    recoChain = [hltMod]

    for iPath, path in hltPaths:
        ntuples.SetTriggerPathName(iPath, path)
    
    for iFilt, filt in photonHLTObjects:
        ntuples.SetPhotonTriggerModuleName(iFilt, filt)
    
    for iFilt, filt in electronHLTObjects:
        ntuples.SetElectronTriggerModuleName(iFilt, filt)
    
    for iFilt, filt in muonHLTObjects:
        ntuples.SetMuonTriggerModuleName(iFilt, filt)

else:
    analysis.SetUseHLT(False)
    ntuples.SetUseTrigger(False)
    recoChain = []

recoChain.append(goodPVFilterMod)

if analysis.isRealData:
    eventlistDir = '/cvmfs/cvmfs.cmsaf.mit.edu/hidsk0001/cmsprod/cms/MitPhysics/data/eventfilter'

    badEventsFilterMod = mithep.BadEventsFilterMod('BadEventsFilterMod',
        FillHist = True,
        TaggingMode = True
    )
    badEventsFilterMod.SetFilter('HBHENoiseFilter')
    badEventsFilterMod.SetFilter('EEBadScFilter')
    badEventsFilterMod.AddEventList('CSCTightHaloFilter', eventlistDir + '/csc2015_Dec01.txt')
    badEventsFilterMod.AddEventList('EEBadScFilter', eventlistDir + '/ecalscn1043093_Dec01.txt')
    badEventsFilterMod.AddEventList('CHTrackResolutionFilter', eventlistDir + '/badResolutionTrack_Jan13.txt')
    badEventsFilterMod.AddEventList('MuBadTrackFilter', eventlistDir + '/muonBadTrack_Jan13.txt')
    badEventsFilterMod.AddEventList('HBHENoiseIsoFilter', eventlistDir + '/hbheiso_Jan13.txt')

    recoChain.append(badEventsFilterMod)

    ntuples.SetMetFilterName(badEventsFilterMod.GetOutputName())

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
        ConeSize = switchRun(0.4, 0.5),
        NoActiveArea = True,
        ParticleMinPt = 0.,
        JetMinPt = 20.
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
    baselinePhotons, # skim >= 1 photon with pT > 30
    separatePileUpMod,
    baselineElectrons,
    vetoElectronId,
    looseElectronId,
    tightElectronId,
    looseMuons,
    tightMuonId,
    looseTaus,
    jetCorrection,
    metCorrection,
    metCorrectionJESUp,
    metCorrectionJESDown,
    metCorrectionUnclUp,
    metCorrectionUnclDown,
    photonLooseId,
    photonMediumId,
    photonTightId,
    photonHighPtId,
    looseJets,
    jetUncertaintyUp,
    jetUncertaintyDown
]

#baselinePhotons.SetMinOutput(1)
#looseJets.SetMinOutput(2)
ntuples.SetCondition(recoChain[-1])

analysis.setSequence(Chain(recoChain) + ntuples)
