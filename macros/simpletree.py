from MitAna.TreeMod.bambu import mithep, analysis
from MitAna.TreeMod.sequenceable import Chain
import os

####################################
### UTIL FUNCTIONS AND VARIABLES ###
####################################

mitdata = os.environ['MIT_DATA']

if 'run' in analysis.custom:
    run = analysis.custom['run']
else:
    run = 2

if 'phdetail' in analysis.custom:
    phdetail = analysis.custom['phdetail']
else:
    phdetail = True

if run == 2:
    jetsName = 'AKt4PFJetsCHS'
    jecVersion = 'Spring16_25nsV6'
    jerVersion = 'Spring16_25nsV6'
    jecName = 'AK4PFchs'
    jetCone = 0.4
    rhoAlgo = mithep.PileupEnergyDensity.kFixedGridFastjetAll

else:
    jetsName = 'AKt5PFJets'
    jecVersion = 'Summer13_V4'
    jerVersion = ''
    jecName = 'AK5PF'
    jetCone = 0.5
    rhoAlgo = mithep.PileupEnergyDensity.kHighEta

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
### JET/MET CORRECTIONS & ID ###
################################

if analysis.isRealData:
    jecPattern = mitdata + '/JEC/{version}/{version}_DATA_{level}_' + jecName + '.txt'
    jecLevels = ['L1FastJet', 'L2Relative', 'L3Absolute', 'L2L3Residual']

else:
    jecPattern = mitdata +'/JEC/{version}/{version}_MC_{level}_' + jecName + '.txt'
    jecLevels = ['L1FastJet', 'L2Relative', 'L3Absolute']

fiducialJets = mithep.JetIdMod('FiducialJets',
    InputName = jetsName,
    OutputName = 'FiducialJets',
    PtMin = 0.,
    EtaMax = 4.7,
    JetEEMFractionMinCut = -1.
)

correctedJets = mithep.JetCorrectionMod('JetCorrection',
    InputName = fiducialJets.GetName(),
    CorrectedJetsName = 'CorrectedJets',
    RhoAlgo = rhoAlgo
)

correctedJetsJESUp = mithep.JetCorrectionMod('JetCorrectionJESUp',
    InputName = correctedJets.GetOutputName(),
    CorrectedJetsName = 'CorrectedJetsJESUp',
    UncertaintySigma = 1.
)

correctedJetsJESDown = mithep.JetCorrectionMod('JetCorrectionJESDown',
    InputName = correctedJets.GetOutputName(),
    CorrectedJetsName = 'CorrectedJetsJESDown',
    UncertaintySigma = -1.
)

for level in jecLevels:
    repl = {'version': jecVersion, 'level': level}
    correctedJets.AddCorrectionFromFile(jecPattern.format(**repl))

for mod in [correctedJetsJESUp, correctedJetsJESDown]:
    repl = {'version': jecVersion, 'level': 'Uncertainty'}
    mod.AddCorrectionFromFile(jecPattern.format(**repl))

correctedMet = mithep.MetCorrectionMod('MetCorrection',
    InputName = 'PFMet',
    OutputName = 'PFType1Met',
    JetsName = correctedJets.GetOutputName(),
    RhoAlgo = rhoAlgo,
    MaxEMFraction = 0.9,
    SkipMuons = True,
    MuonGeometricMatch = False
)
correctedMet.ApplyType0(False)
correctedMet.ApplyType1(True)
correctedMet.ApplyShift(False)
correctedMet.IsData(analysis.isRealData)

correctedMetJESUp = correctedMet.clone('MetCorrectionJESUp',
    OutputName = 'PFType1MetJESUp',
    JetsName = correctedJetsJESUp.GetOutputName()
)

correctedMetJESDown = correctedMet.clone('MetCorrectionJESDown',
    OutputName = 'PFType1MetJESDown',
    JetsName = correctedJetsJESDown.GetOutputName()
)

correctedMetUnclUp = correctedMet.clone('MetCorrectionUnclUp',
    OutputName = 'PFType1MetUnclUp',
    UnclusteredVariation = 0.1
)
correctedMetUnclUp.ApplyUnclustered(True)

correctedMetUnclDown = correctedMetUnclUp.clone('MetCorrectionUnclDown',
    OutputName = 'PFType1MetUnclDown',
    UnclusteredVariation = -0.1
)

jetLooseId = mithep.JetIdMod('JetId',
    InputName = correctedJets.GetOutputName(),
    OutputName = 'GoodJetsMask',
    PFId = mithep.JetTools.kPFLoose,
    PtMin = 0.,
    EtaMax = 5.,
    MVACutWP = mithep.JetIDMVA.kLoose,
    FillHist = True,
    IsFilterMode = False,
    MinOutput = 2
)

if run == 2:
    jetLooseId.SetMVATrainingSet(mithep.JetIDMVA.k80CHS)
    jetLooseId.SetMVAWeightsFile(mitdata + '/JetId/pileupJetId_80XvarFix_Eta0to2p5_BDT.weights.xml', 0)
    jetLooseId.SetMVAWeightsFile(mitdata + '/JetId/pileupJetId_80XvarFix_Eta2p5to2p75_BDT.weights.xml', 1)
    jetLooseId.SetMVAWeightsFile(mitdata + '/JetId/pileupJetId_80XvarFix_Eta2p75to3_BDT.weights.xml', 2)
    jetLooseId.SetMVAWeightsFile(mitdata + '/JetId/pileupJetId_80XvarFix_Eta3to5_BDT.weights.xml', 3)
    jetLooseId.SetMVACutsFile(mitdata + '/JetId/jetIDCuts_160715.dat')

else:
    jetLooseId.SetMVATrainingSet(mithep.JetIDMVA.nMVATypes)

dijetFilter = mithep.JetIdMod('DijetFilter',
    InputName = correctedJets.GetOutputName(),
    OutputName = 'HighPtJets',
    PtMin = 50.,
    EtaMax = 5.,
    JetEEMFractionMinCut = -1.,
    FillHist = True,
    MinOutput = 2
)

jetbaseSequence = fiducialJets * correctedJets * jetLooseId
jetMetCorrSequence = correctedJetsJESUp * correctedJetsJESDown * correctedMet * correctedMetJESUp * correctedMetJESDown * correctedMetUnclUp * correctedMetUnclDown

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
    IsoType = mithep.ElectronTools.kSummer15TightIso,
    MinOutput = 1 # will be placed out of the reco chain
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
    IsoType = mithep.MuonTools.kPFIsoBetaPUCorrectedTight,
    MinOutput = 1 # will be placed out of the reco chain
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

photonHighPtFilter = baselinePhotons.clone('PhotonHighPtFilter',
    PtMin = 100.,
    OutputName = 'HighPtPhotons', # not used
    MinOutput = 1
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

leptonIdSequence = vetoElectronId * looseElectronId * looseTaus
photonIdSequence = photonLooseId * photonMediumId * photonTightId * photonHighPtId

#####################################
### CONSTRUCT NTUPLES INPUT CHAIN ###
#####################################

preskimSequence = goodPVFilterMod * separatePileUpMod * (
    jetbaseSequence * dijetFilter +
    baselinePhotons * photonHighPtFilter +
    baselineElectrons * tightElectronId +
    looseMuons * tightMuonId
)

BExpr = mithep.BooleanMod.Expression
skimExpr = BExpr(
    dijetFilter,
    BExpr(photonHighPtFilter,
        BExpr(tightElectronId, tightMuonId, BExpr.kOR),
        BExpr.kOR),
    BExpr.kOR   
)

skim = mithep.BooleanMod('Skim',
    Expression = skimExpr
)

recoSequence = leptonIdSequence * photonIdSequence * jetMetCorrSequence

###############
### NTUPLES ###
###############

ntuples = mithep.SimpleTreeMod(
    RhoAlgo = rhoAlgo,
    JetsName = correctedJets.GetOutputName(),
    LooseJetsName = jetLooseId.GetOutputName(),
    MinJetPt = 30.,
    JetsCorrUpName = correctedJetsJESUp.GetOutputName(),
    JetsCorrDownName = correctedJetsJESDown.GetOutputName(),
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
    T1MetName = correctedMet.GetOutputName(),
    CorrUpMetName = correctedMetJESUp.GetOutputName(),
    CorrDownMetName = correctedMetJESDown.GetOutputName(),
    UnclUpMetName = correctedMetUnclUp.GetOutputName(),
    UnclDownMetName = correctedMetUnclDown.GetOutputName(),
    CaloMetName = 'CaloMet',
    FillPhotonDetails = phdetail,
    IsMC = not analysis.isRealData
)

if 'usehlt' in analysis.custom and not analysis.custom['usehlt']:
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

################################
### DATA/MC SPECIFIC MODULES ###
################################

if analysis.isRealData:
    badEventsFilterMod = mithep.BadEventsFilterMod('BadEventsFilterMod',
        FillHist = True,
        TaggingMode = True
    )
    badEventsFilterMod.SetFilter('HBHENoiseFilter')
    badEventsFilterMod.SetFilter('HBHENoiseIsoFilter')
    badEventsFilterMod.SetFilter('EEBadScFilter')
    badEventsFilterMod.SetFilter('CSCTightHaloFilter')
    badEventsFilterMod.SetFilter('GlobalTightHaloFilter')
    badEventsFilterMod.SetFilter('BadPFMuonFilter')
    badEventsFilterMod.SetFilter('BadChargedCandidateFilter')

    recoSequence *= badEventsFilterMod

    ntuples.SetMetFilterName(badEventsFilterMod.GetOutputName())

else:
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
        ConeSize = jetCone,
        NoActiveArea = True,
        ParticleMinPt = 0.,
        JetMinPt = 0.
    )

    storedGenJets = mithep.GenJetFilterMod('FilteredGenJets',
        InputName = genJets.GetOutputJetsName(),
        OutputName = 'FilteredGenJets',
        PtMin = 20.,
        EtaMax = 10.
    )
    storedGenJets.PublishPerEvent(False)

    recoSequence *= generator * mcParticlesNoNu * genJets * storedGenJets

    ntuples.SetGenMetName(generator.GetMCMETName())
    ntuples.SetGenJetsName(storedGenJets.GetOutputName())

    if 'pdfrwgt' in analysis.custom and analysis.custom['pdfrwgt'] != '-':
        ntuples.SetPdfReweight(analysis.custom['pdfrwgt'])

    if jerVersion != '':
        smearedJets = mithep.JetCorrectionMod('JetSmearing',
            InputName = correctedJets.GetOutputName(),
            CorrectedJetsName = 'SmearedJets',
            GenJetsName = genJets.GetOutputJetsName()
        )

        jc = mithep.JetCorrector.Corrector
        for level, ftype in [('PtResolution', jc.kPtResolution), ('PhiResolution', jc.kPhiResolution), ('SF', jc.nFactorTypes)]:
            smearedJets.AddCorrectionFromFile(jecPattern.format(version = jerVersion, level = level), ftype)

        correctedMetJER = correctedMet.clone('MetCorrectionJER',
            OutputName = 'PFType1MetJER',
            JetsName = smearedJets.GetOutputName()
        )
    
        recoSequence *= smearedJets * correctedMetJER

        ntuples.SetJetsResCorrName(smearedJets.GetOutputName())
        ntuples.SetJetResMetName(correctedMetJER.GetOutputName())

ntuples.SetCondition(list(recoSequence)[-1])

analysis.setSequence(preskimSequence + (skim * recoSequence) + ntuples)
