from MitAna.TreeMod.bambu import mithep, analysis

ntuples = mithep.GenKinTreeMod(
    OutputName = 'genkintree.root'
)

analysis.setSequence(ntuples)
