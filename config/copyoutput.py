import sys
import os
import ROOT

fileset = sys.argv[1]

if os.path.getsize(fileset + '.root') == 0:
    sys.exit(1)

source = ROOT.TFile.Open('simpletree.root')
target = ROOT.TFile.Open(fileset + '.root', 'update')

for key in source.GetListOfKeys():
    obj = key.ReadObj()
    if obj.InheritsFrom(ROOT.TTree.Class()):
        newobj = obj.CloneTree(-1, 'fast')
    else:
        newobj = obj.Clone()

    newobj.Write()
