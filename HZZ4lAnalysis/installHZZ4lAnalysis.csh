#! /bin/csh

#Remove conflict declarations
rm -fr AnalysisDataFormats/CMGTools/interface/CompoundTypes.h 
rm -fr AnalysisDataFormats/CMGTools/src/classes.h
rm -fr AnalysisDataFormats/CMGTools/src/classes_def.xml
rm -fr CMGTools/Common/interface/CompoundFactories.h
rm -fr CMGTools/Common/plugins/CMGTools.h
rm -fr CMGTools/Common/plugins/CMGTools.cc

#Download the new versions (wget to avoid conflicts between same CVS repository)
wget -O AnalysisDataFormats/CMGTools/interface/CompoundTypes.h "http://cmssw.cvs.cern.ch/cgi-bin/cmssw.cgi/UserCode/scasasso/AnalysisDataFormats/CMGTools/interface/CompoundTypes.h?view=co"
wget -O AnalysisDataFormats/CMGTools/src/classes.h "http://cmssw.cvs.cern.ch/cgi-bin/cmssw.cgi/UserCode/scasasso/AnalysisDataFormats/CMGTools/src/classes.h?view=co"
wget -O AnalysisDataFormats/CMGTools/src/classes_def.xml "http://cmssw.cvs.cern.ch/cgi-bin/cmssw.cgi/UserCode/scasasso/AnalysisDataFormats/CMGTools/src/classes_def.xml?view=co"
wget -O CMGTools/Common/interface/CompoundFactories.h "http://cmssw.cvs.cern.ch/cgi-bin/cmssw.cgi/UserCode/scasasso/CMGTools/Common/interface/CompoundFactories.h?view=co"
wget -O CMGTools/Common/plugins/CMGTools.h "http://cmssw.cvs.cern.ch/cgi-bin/cmssw.cgi/UserCode/scasasso/CMGTools/Common/plugins/CMGTools.h?view=co"
wget -O CMGTools/Common/plugins/CMGTools.cc "http://cmssw.cvs.cern.ch/cgi-bin/cmssw.cgi/UserCode/scasasso/CMGTools/Common/plugins/CMGTools.cc?view=co"

#cvs co of the analysis package
cvs co -d HZZ4lAnalysis UserCode/scasasso/HZZ4lAnalysis
scram b -j 4

