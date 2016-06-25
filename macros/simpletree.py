sfrom MitAna.TreeMod.bambu import mithep, analysis
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

def switchRun(case2, case1):
    global run
    return case2 if run == 2 else case1

rhoAlgo = switchRun(mithep.PileupEnergyDensity.kFixedGridFastjetAll, mithep.PileupEnergyDensity.kHighEta)

if run == 2:
    jecVersion = 'Spring16_25nsV3'
else:
    jecVersion = 'Summer13_V4'

#########################################
### MODULES RUN WITH DEFAULT SETTINGS ###
#########################################

from MitPhysics.Mods.GoodPVFilterMod import goodPVFilterMod
from MitPhysics.Mods.SeparatePileUpMod import separatePileUpMod

#####################
### EVENT FILTERS ###
#####################

if run == 2:
    photonL1Objects = [
        ('fSEG34IorSEG40', 'hltL1sSingleEG34IorSingleEG40'), # HLT_Photon120
        ('fSEG40IorSJet200', 'hltL1sSingleEG40IorSingleJet200'), # HLT_Photon135_PFMET100
        ('fSEG34IorSEG40IorSJet200', 'hltL1sSingleEG34IorSingleEG40IorSingleJet200'), # HLT_Photon165_HE10
        ('fSEG24', 'hltL1sSingleEG24'), # HLT_Photon22_MET/VBF
        ('fSEG30', 'hltL1sSingleEG30'), # HLT_Photon36_MET/VBF
        ('fSEG40', 'hltL1sSingleEG40') # HLT_PhotonX_MET/VBF
    ]

    photonHLTObjects = [
        ('fPh120', 'hltEG120HEFilter'), # HLT_Photon120
        ('fPh135', 'hltEG135HEFilter'), # HLT_Photon135_PFMET100
        ('fPh165HE10', 'hltEG165HE10Filter'), # HLT_Photon165_HE10
        ('fPh175', 'hltEG175HEFilter'), # HLT_Photon175
        ('fPh22EBR9Iso', 'hltEG22R9Id90HE10Iso40EBOnlyTrackIsoFilter'),
        ('fPh36EBR9Iso', 'hltEG36R9Id90HE10Iso40EBOnlyTrackIsoFilter'),
        ('fPh50EBR9Iso', 'hltEG50R9Id90HE10Iso40EBOnlyTrackIsoFilter'),
        ('fPh75EBR9Iso', 'hltEG75R9Id90HE10Iso40EBOnlyTrackIsoFilter'),
        ('fPh90EBR9Iso', 'hltEG90R9Id90HE10Iso40EBOnlyTrackIsoFilter'),
        ('fPh120EBR9Iso', 'hltEG120R9Id90HE10Iso40EBOnlyTrackIsoFilter')
    ]

    electronHLTObjects = [
        ('fEl23Loose', 'hltEle23WPLooseGsfTrackIsoFilter'), # HLT_Ele23_WPLoose_Gsf
        ('fEl27Loose', 'hltEle27noerWPLooseGsfTrackIsoFilter'), # HLT_Ele27_WPLoose_Gsf
        ('fEl120Ph', 'hltEG120HEFilter'),
        ('fEl135Ph', 'hltEG135HEFilter'),
        ('fEl165HE10Ph', 'hltEG165HE10Filter'),
        ('fEl175Ph', 'hltEG175HEFilter'),
        ('fEl22EBR9IsoPh', 'hltEG22R9Id90HE10Iso40EBOnlyTrackIsoFilter'),
        ('fEl36EBR9IsoPh', 'hltEG36R9Id90HE10Iso40EBOnlyTrackIsoFilter'),
        ('fEl50EBR9IsoPh', 'hltEG50R9Id90HE10Iso40EBOnlyTrackIsoFilter'),
        ('fEl75EBR9IsoPh', 'hltEG75R9Id90HE10Iso40EBOnlyTrackIsoFilter'),
        ('fEl90EBR9IsoPh', 'hltEG90R9Id90HE10Iso40EBOnlyTrackIsoFilter'),
        ('fEl120EBR9IsoPh', 'hltEG120R9Id90HE10Iso40EBOnlyTrackIsoFilter')
    ]

    muonHLTObjects = [
        ('fMu20', 'hltL3crIsoL1sMu18L1f0L2f10QL3f20QL3trkIsoFiltered0p09'), # HLT_IsoMu20
        ('fMuTrk20', 'hltL3fL1sMu18L1f0Tkf20QL3trkIsoFiltered0p09'), # HLT_IsoTkMu20
        ('fMu24', 'hltL3crIsoL1sMu22L1f0L2f10QL3f24QL3trkIsoFiltered0p09'), # HLT_IsoMu24
        ('fMu27', 'hltL3crIsoL1sMu22Or25L1f0L2f10QL3f27QL3trkIsoFiltered0p09')
    ]
    
else:
    photonL1Objects = []
    photonHLTObjects = []
    electronHLTObjects = []
    muonHLTObjects = []

################################
### JET/MET ID & CORRECTIONS ###
################################

jetCorrection = mithep.JetCorrectionMod('JetCorrection',
    InputName = switchRun('AKt4PFJetsCHS', 'AKt5PFJets'),
    CorrectedJetsName = 'CorrectedJets',
    RhoAlgo = rhoAlgo
)

correctedJets = jetCorrection.GetOutputName()

if not analysis.isRealData:
    jetSmearing = mithep.JetCorrectionMod('JetSmearing',
        InputName = looseJets.GetOutputName(),
        CorrectedJetsName = 'SmearedJets'
    )

    correctedJets = jetCorrection.GetOutputName()

looseJets = mithep.JetIdMod('JetId',
    InputName = correctedJets,
    OutputName = 'GoodJets',
    PFId = mithep.JetTools.kPFLoose,
    PtMin = 20.,
    EtaMax = 5.,
    MVACutWP = mithep.JetIDMVA.kLoose,
    FillHist = True
)
if run == 2:
    synchWith = '80Xv1'

    if synchWith == '76':
        looseJets.SetMVATrainingSet(mithep.JetIDMVA.k74CHS)
        looseJets.SetMVAWeightsFile(mitdata + '/JetId/TMVAClassificationCategory_BDTG.weights_jteta_0_2_newNames.xml', 0)
        looseJets.SetMVAWeightsFile(mitdata + '/JetId/TMVAClassificationCategory_BDTG.weights_jteta_2_2p5_newNames.xml', 1)
        looseJets.SetMVAWeightsFile(mitdata + '/JetId/TMVAClassificationCategory_BDTG.weights_jteta_2p5_3_newNames.xml', 2)
        looseJets.SetMVAWeightsFile(mitdata + '/JetId/TMVAClassificationCategory_BDTG.weights_jteta_3_5_newNames.xml', 3)
        looseJets.SetMVACutsFile(mitdata + '/JetId/jetIDCuts_150807.dat')
        looseJets.SetUseBuggyPullForMVA(True)
        looseJets.SetUseBuggyCovarianceForMVA(True)
    elif synchWith == '80Xv1':
        # to synch with 80X MINIAODv1 or privately recomputed 76X using tag pileupJetId76X of https://github.com/jbrands/cmssw.git
        looseJets.SetMVATrainingSet(mithep.JetIDMVA.k76CHS)
        looseJets.SetMVAWeightsFile(mitdata + '/JetId/pileupJetId_76x_Eta0to2p5_BDT.weights.xml', 0)
        looseJets.SetMVAWeightsFile(mitdata + '/JetId/pileupJetId_76x_Eta2p5to2p75_BDT.weights.xml', 1)
        looseJets.SetMVAWeightsFile(mitdata + '/JetId/pileupJetId_76x_Eta2p75to3_BDT.weights.xml', 2)
        looseJets.SetMVAWeightsFile(mitdata + '/JetId/pileupJetId_76x_Eta3to5_BDT.weights.xml', 3)
        looseJets.SetMVACutsFile(mitdata + '/JetId/jetIDCuts_160225.dat')
        looseJets.SetUseBuggyCovarianceForMVA(True)
    elif synchWith == '80Xv2':
        # to synch with 80X MINIAODv2
        looseJets.SetMVATrainingSet(mithep.JetIDMVA.k80CHS)
        looseJets.SetMVAWeightsFile(mitdata + '/JetId/pileupJetId_80x_Eta0to2p5_BDT.weights.xml', 0)
        looseJets.SetMVAWeightsFile(mitdata + '/JetId/pileupJetId_80x_Eta2p5to2p75_BDT.weights.xml', 1)
        looseJets.SetMVAWeightsFile(mitdata + '/JetId/pileupJetId_80x_Eta2p75to3_BDT.weights.xml', 2)
        looseJets.SetMVAWeightsFile(mitdata + '/JetId/pileupJetId_80x_Eta3to5_BDT.weights.xml', 3)
        looseJets.SetMVACutsFile(mitdata + '/JetId/jetIDCuts_160416.dat')
        looseJets.SetUseBuggyCovarianceForMVA(True)

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
    JetsName = correctedJets,
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

if analysis.isRealData:
    jecPattern = mitdata + '/JEC/{version}/{version}_DATA_{level}_{jettype}.txt'
    jecLevels = ['L1FastJet', 'L2Relative', 'L3Absolute', 'L2L3Residual']

else:
    jecPattern = mitdata +'/JEC/{version}/{version}_MC_{level}_{jettype}.txt'
    jecLevels = ['L1FastJet', 'L2Relative', 'L3Absolute']

for level in jecLevels:
    repl = {'version': jecVersion, 'level': level, 'jettype': switchRun('AK4PFchs', 'AK5PF')}
    jetCorrection.AddCorrectionFromFile(jecPattern.format(**repl))
    metCorrectionJESUp.AddJetCorrectionFromFile(jecPattern.format(**repl))
    metCorrectionJESDown.AddJetCorrectionFromFile(jecPattern.format(**repl))

if run == 2 and not analysis.isRealData:
    jetSmearing.AddCorrectionFromFile(jecPattern.format(version = 'Fall15_V2', level = 'PtResolution', jettype = 'AK4PFchs'))
    jetSmearing.AddCorrectionFromFile(jecPattern.format(version = 'Fall15_V2', level = 'PhiResolution', jettype = 'AK4PFchs'))
    jetSmearing.AddCorrectionFromFile(jecPattern.format(version = 'Fall15_V2', level = 'SF', jettype = 'AK4PFchs'))

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
    ConversionsName = 'Conversions',
    FillHist = True
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
    ApplyNExpectedHitsInnerCut = True,
    FillHist = True
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
    EtaMax = 2.4,
    FillHist = True
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
    EtaMax = 2.3,
    FillHist = True
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
    EtaMax = 3.,
    FillHist = True
)

photonLooseId = mithep.PhotonIdMod('PhotonLooseId',
    IsFilterMode = False,
    InputName = baselinePhotons.GetOutputName(),
    OutputName = 'PhotonLooseId',
    IdType = mithep.PhotonTools.kSpring15Loose,
    IsoType = mithep.PhotonTools.kSpring15LooseIso,
    FillHist = True
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

# TODO SimpleTreeMod should use its own JetCorrector to compute res up & down jet and met

ntuples = mithep.SimpleTreeMod(
    RhoAlgo = rhoAlgo,
    JetsName = looseJets.GetOutputName(),
    JetsCorrUpName = jetUncertaintyUp.GetOutputName(),
    JetsCorrDownName = jetUncertaintyDown.GetOutputName(),
    PhotonsName = baselinePhotons.GetOutputName(),
    PhotonIsoType = mithep.PhotonTools.kSpring15MediumIso,
    ElectronsName = baselineElectrons.GetOutputName(),
    ElectronIsoType = mithep.ElectronTools.kSummer15LooseIso,
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
    FillPhotonDetails = analysis.custom['phdetail'],
    IsMC = not analysis.isRealData
)

if (analysis.book.endswith('044') and not analysis.isRealData) or ('usehlt' in analysis.custom and not analysis.custom['usehlt']):
    analysis.SetUseHLT(False)
    ntuples.SetUseTrigger(False)

else:
    for fname, filt in photonL1Objects:
        ntuples.SetPhotonL1ModuleName(fname, filt)
    
    for fname, filt in photonHLTObjects:
        ntuples.SetPhotonTriggerModuleName(fname, filt)
    
    for fname, filt in electronHLTObjects:
        ntuples.SetElectronTriggerModuleName(fname, filt)
    
    for fname, filt in muonHLTObjects:
        ntuples.SetMuonTriggerModuleName(fname, filt)

recoChain = [goodPVFilterMod]

#if analysis.isRealData:
#    eventlistDir = '/cvmfs/cvmfs.cmsaf.mit.edu/hidsk0001/cmsprod/cms/MitPhysics/data/eventfilter'
#
#    badEventsFilterMod = mithep.BadEventsFilterMod('BadEventsFilterMod',
#        FillHist = True,
#        TaggingMode = True
#    )
#    badEventsFilterMod.SetFilter('HBHENoiseFilter')
#    badEventsFilterMod.SetFilter('EEBadScFilter')
#    badEventsFilterMod.AddEventList('CSCTightHaloFilter', eventlistDir + '/csc2015_Dec01.txt')
#    badEventsFilterMod.AddEventList('EEBadScFilter', eventlistDir + '/ecalscn1043093_Dec01.txt')
#    badEventsFilterMod.AddEventList('CHTrackResolutionFilter', eventlistDir + '/badResolutionTrack_Jan13.txt')
#    badEventsFilterMod.AddEventList('MuBadTrackFilter', eventlistDir + '/muonBadTrack_Jan13.txt')
#    badEventsFilterMod.AddEventList('HBHENoiseIsoFilter', eventlistDir + '/hbheiso_Jan13.txt')
#
#    recoChain.append(badEventsFilterMod)
#
#    ntuples.SetMetFilterName(badEventsFilterMod.GetOutputName())

if not analysis.isRealData:
    generator = mithep.GeneratorMod(
        IsData = False,
        CopyArrays = False,
        MCMETName = "GenMet",
        FillHist = False
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
        ntuples.SetPdfReweight(analysis.custom['pdfrwgt'])

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
