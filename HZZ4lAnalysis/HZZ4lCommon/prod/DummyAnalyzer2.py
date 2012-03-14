#### Example of FWLite PyROOT macro running on CMGTuples
#### Usage python DummyAnalyzer2.py 


import os, sys
import math
from array import array
from ROOT import *
print "loading FWLite libraries... ",
from DataFormats.FWLite import Events, Handle
print "done."


def main():

    inputfilename = 'HZZ4l_CMGTuple.root'
    events = Events ( inputfilename )

    outfilename = "DummyHistos.root"
    outputroot = TFile( outfilename, "RECREATE")

    handle4mu = Handle ("vector<cmg::DiObject<cmg::DiObject<cmg::Muon,cmg::Muon>,cmg::DiObject<cmg::Muon,cmg::Muon> > >")
    label4mu =  ("cmgDiMuonDiMuon")

    histogram = {}

    histogram[ 'higgs_pt_4mu' ] = TH1F("higgs_pt_4mu", "p_{T} of 4mu - Higgs candidate", 100, 0, 500)
    histogram[ 'higgs_eta_4mu' ] = TH1F("higgs_eta_4mu", "#eta of 4mu - Higgs candidate", 100, -3., 3.)
    
    for ih in histogram.keys():
        histogram[ih].SetXTitle( histogram[ih].GetTitle() )

    # loop over events
    i = 0 # event counter
    
    for event in events:
        i = i + 1
        if i%100 == 0:
            print  "processing entry # " + str(i) + " from Run "+ str(event.eventAuxiliary().id().run()) + " lumi "+str(event.eventAuxiliary().id().luminosityBlock())

        event.getByLabel (label4mu, handle4mu)
        # get the product
        higgs_4mu = handle4mu.product()

        for ahiggs in higgs_4mu:

            histogram["higgs_pt_4mu"].Fill( ahiggs.pt() )
            histogram["higgs_eta_4mu"].Fill( ahiggs.eta() )

    # close loop over entries    
    outputroot.cd()

    # write histograms to file
    for key in histogram.keys():
        histogram[key].Write()

    outputroot.Close()
    
    
    
if __name__ == '__main__':
    main()
