#############################################################
####Instructions to install the package in CMSSW_4_2_8_patch7
#############################################################

# First install the CMGTools package by doing (see also https://twiki.cern.ch/twiki/bin/viewauth/CMS/CMGToolsReleasesExperimental#Colin_V2_5_0)
wget -O installCMGTools.py "http://cmssw.cvs.cern.ch/cgi-bin/cmssw.cgi/UserCode/CMG/CMGTools/Common/bin/installCMGTools.py?view=co"
python installCMGTools.py -r CMSSW_4_2_8_patch7 --recipe=exp_V2_5_0
cd CMGTools/CMSSW_4_2_8_patch7/src
cvs up -r 1.47 PhysicsTools/PatAlgos/python/tools/tauTools.py
cvs up -r V08-06-50 PhysicsTools/PatAlgos/python/tools/cmsswVersionTools.py
chmod +x CMGTools/Production/scripts/*.py
chmod +x CMGTools/Common/scripts/*.py
scram b -j 4 

# Then co from UserCode/scasasso
cvs co -d HZZ4lAnalysis UserCode/scasasso/HZZ4lAnalysis
scram b -j 4

# Produce CMGTuple (by now from PF2PATs provided in the tutorial, DoubleMu-like trigger)
cd HZZ4lAnalysis/HZZ4lCommon/prod
cmsRun cmgTuple_cfg.py maxEvents=howmanyyouwant #where howmanyyouwant = 5000 should be fine for a simple test
root -l HZZ4l_CMGTuple.root

# Produce a (very) dummy tree
cmsRun dummytreemaker_cfg.py
root -l HZZ4l_DummyTree.root

# (very) Dummy analyzer pyroot-based running on CMGTuples
python DummyAnalyzer2.py
root -l DummyHistos.root

