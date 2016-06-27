import sys
import os
import ROOT

fileset = sys.argv[1]

if os.path.getsize(fileset + '.root') == 0:
    sys.exit(1)

source = ROOT.TFile.Open('simpletree.root')
target = ROOT.TFile.Open(fileset + '.root', 'update')

trees = set()

for key in source.GetListOfKeys():
    obj = key.ReadObj()
    if obj.InheritsFrom(ROOT.TTree.Class()):
        trees.add(obj.GetName())
        continue

    newobj = obj.Clone()
    newobj.Write()

# clone only the last version
for tree in trees:
    clonetree = source.Get(tree).CloneTree(-1, 'fast')
    clonetree.Write()
