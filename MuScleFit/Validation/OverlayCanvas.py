import ROOT

################################################
def getModifiedTMultiGraph(file, color, canvas):
################################################
    """ main function to acces to the TGraphErrors and return them with a modified style """
# read-in canavas
    tFile = ROOT.TFile(file+'.root','read')
    cIn = tFile.Get(canvas)
# 
    for ca in cIn.GetListOfPrimitives():
# Get TGraph from MultiGraph        
        if ca.InheritsFrom('TMultiGraph'):
            for igraph in range(0, ca.GetListOfGraphs().GetSize()):
                ca.GetListOfGraphs().At(igraph).SetMarkerColor(color)
                ca.GetListOfGraphs().At(igraph).SetLineColor(color)
            mg = ca
            break

    return mg


############
def main():
############
    ROOT.gStyle.SetOptTitle(0)
    ROOT.gStyle.SetMarkerSize(1.2)

### m(mumu) vs. Eta

    # dictionary for Z
    #dict_Eta = {'ScalePdg_mc_Eta_afterCorrection_V0':ROOT.kBlack,\
    #            'ScalePdg_mc_Eta_afterCorrection_V1':ROOT.kBlue, \
    #            'ScalePdg_mc_Eta_Z_afterCorrection_V2':ROOT.kGreen,\
    #            'ScalePdg_mc_Eta_Z_afterCorrection_V3':ROOT.kRed}
    
    # dictionary for Y
    dict_Eta = {'ScalePdg_mc_Eta_Y_afterCorrection_V0':ROOT.kBlack,\
                'ScalePdg_mc_Eta_Y_afterCorrection_V3':ROOT.kRed}

    legLabels_Z_eta = ['p_{T} 20-45 GeV', 'p_{T} 45-90 GeV']
    legLabels_Y_eta = ['p_{T} 10-20 GeV']
    
    legScaleEta = ROOT.TLegend(0.12,0.13,0.47,0.39)
    legScaleEta.SetFillColor(0)
    legScaleEta.SetTextFont(42)
    legScaleEta.SetTextSize(0.03)
    legScaleEta.SetBorderSize(0)

    first = True
    for kName, vColor in dict_Eta.items():
        print kName
        if first: 
            first = False 
            mg_eta = getModifiedTMultiGraph(kName, vColor, 'cScalePdg_mc_Eta')
        else:
            mg_eta.Add(getModifiedTMultiGraph(kName, vColor, 'cScalePdg_mc_Eta'))
            
    for igraph in range(0,mg_eta.GetListOfGraphs().GetSize()):
# extraLabel should be set to describe the input dataset
        extraLabel = ' ' 
        if mg_eta.GetListOfGraphs().At(igraph).GetLineColor() == ROOT.kBlack:
            #        extraLabel += 'MadGraph AODSIM'         
            extraLabel += 'AODSIM'         
        elif mg_eta.GetListOfGraphs().At(igraph).GetLineColor() == ROOT.kBlue:
            extraLabel += 'POWHEG AODSIM'         
        elif mg_eta.GetListOfGraphs().At(igraph).GetLineColor() == ROOT.kGreen:
            extraLabel += 'POWHEG rereco START53'         
        elif mg_eta.GetListOfGraphs().At(igraph).GetLineColor() == ROOT.kRed:
            #        extraLabel += 'POWHEG rereco MC_53'            
            extraLabel += 'rereco MC_53'            
            #    legScaleEta.AddEntry(mg_eta.GetListOfGraphs().At(igraph),legLabels_Z_eta[igraph%2]+extraLabel,'P')
        legScaleEta.AddEntry(mg_eta.GetListOfGraphs().At(igraph),legLabels_Y_eta[0]+extraLabel,'P')


    cScalePdg_mc_Eta = ROOT.TCanvas('cScalePdg_mc_Eta_Y','cScalePdg_mc_Eta_Y',1200,700)
    cScalePdg_mc_Eta.SetGridy()
    cScalePdg_mc_Eta.cd()
    mg_eta.Draw('AP')
    mg_eta.GetYaxis().SetTitle('#DeltaM/M (mc-PDG)')
    mg_eta.GetYaxis().SetTitleOffset(0.9)
    mg_eta.GetXaxis().SetTitle('#eta')
    mg_eta.GetXaxis().SetTitleOffset(0.9)
    mg_eta.GetYaxis().SetRangeUser(-0.005,0.005)
    mg_eta.GetXaxis().SetRangeUser(0.,2.5)
    legScaleEta.Draw('same');
    cScalePdg_mc_Eta.SaveAs('ScalePdg_mc_Eta_Y.png')

### m(mumu) vs. pT

    # dictionary for Z
    #dict_Pt = {'ScalePdg_mc_Pt_afterCorrection_V0':ROOT.kBlack,\
    #           'ScalePdg_mc_Pt_afterCorrection_V1':ROOT.kBlue, \
    #           'ScalePdg_mc_Pt_Z_afterCorrection_V2':ROOT.kGreen,\
    #           'ScalePdg_mc_Pt_Z_afterCorrection_V3':ROOT.kRed}

    # dictionary for Y
    dict_Pt = {'ScalePdg_mc_Pt_Y_afterCorrection_V0':ROOT.kBlack,\
               'ScalePdg_mc_Pt_Y_afterCorrection_V3':ROOT.kRed}

    legLabels_Z_pt = ['|#eta| 0.0-2.4']
    legLabels_Y_pt = ['|#eta| 0.0-0.7', '|#eta| 0.7-2.4']
    legScalePt = ROOT.TLegend(0.12,0.13,0.47,0.26)
    legScalePt.SetFillColor(0)
    legScalePt.SetTextFont(42)
    legScalePt.SetTextSize(0.03)
    legScalePt.SetBorderSize(0)

    first = True
    for kName, vColor in dict_Pt.items():
        if first: 
            first = False 
            mg_pt = getModifiedTMultiGraph(kName, vColor, 'cScalePdg_mc_Pt')
        else:
            mg_pt.Add(getModifiedTMultiGraph(kName, vColor, 'cScalePdg_mc_Pt'))

    for igraph in range(0,mg_pt.GetListOfGraphs().GetSize()):
# extraLabel should be set to describe the input dataset
        extraLabel = ' ' 
        if mg_pt.GetListOfGraphs().At(igraph).GetLineColor() == ROOT.kBlack:
            #        extraLabel += 'MadGraph AODSIM'         
            extraLabel += 'AODSIM'         
        elif mg_pt.GetListOfGraphs().At(igraph).GetLineColor() == ROOT.kBlue:
            extraLabel += 'POWHEG AODSIM'         
        elif mg_pt.GetListOfGraphs().At(igraph).GetLineColor() == ROOT.kGreen:
            extraLabel += 'POWHEG rereco START53'         
        elif mg_pt.GetListOfGraphs().At(igraph).GetLineColor() == ROOT.kRed:
            #        extraLabel += 'POWHEG rereco MC_53'            
            extraLabel += 'rereco MC_53'            
            #    legScalePt.AddEntry(mg_pt.GetListOfGraphs().At(igraph),legLabels_Z_pt[0]+extraLabel,'P')
            legScalePt.AddEntry(mg_pt.GetListOfGraphs().At(igraph),legLabels_Y_pt[igraph%2]+extraLabel,'P')
   
    cScalePdg_mc_Pt = ROOT.TCanvas('cScalePdg_mc_Pt_Y','cScalePdg_mc_Pt_Y',1200,700)
    cScalePdg_mc_Pt.SetGridy()
    cScalePdg_mc_Pt.cd()
    mg_pt.Draw('AP')
    mg_pt.GetYaxis().SetTitle('#DeltaM/M (mc-PDG)')
    mg_pt.GetYaxis().SetTitleOffset(0.9)
    mg_pt.GetXaxis().SetTitle('p_{T} (GeV)')
    mg_pt.GetXaxis().SetTitleOffset(0.9)
    mg_pt.GetYaxis().SetRangeUser(-0.005,0.005)
    mg_pt.GetXaxis().SetRangeUser(0.,70.)
    legScalePt.Draw('same')
    cScalePdg_mc_Pt.SaveAs('ScalePdg_mc_Pt_Y.png')


##################################
if __name__ == "__main__":        
    main()
