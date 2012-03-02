#### Example of PyROOT macro (not framework-aware) running on CMGTuple
#### Usage: python DummyAnalyzer.py


from ROOT import *
import os, sys
from CMGTools.RootTools.Style import *
from CMGTools.RootTools.RootInit import *
from CMGTools.RootTools.RootTools import *

#Get Tree from file
rootfile = 'HZZ4l_CMGTuple.root'
events = Chain('Events', rootfile)

#compare the Z candidate before and after the selection
cmgDiMuon = 'cmgMuoncmgMuoncmgDiObjects_cmgDiMuon__CMG'
events.SetAlias('cmgDiMuon', cmgDiMuon)
c2 = TCanvas()
events.Draw('cmgDiMuon.obj.mass()')
events.Draw('cmgDiMuon.obj.mass()', 'cmgDiMuon.obj.getSelection("cuts_zmumu")', 'ESAME')
c2.Print ("ZCandMass.png")
