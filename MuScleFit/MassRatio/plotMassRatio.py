# Standard classes
from tdrStyle import setTdrStyle
import ROOT as r
from ROOT import TH1F, TFile, TCanvas, TString, TF1, TFormula, TPad, TStyle, gStyle, TLine, TLegend, TPaveText

# RooFit classes
from ROOT import RooRealVar, RooDataHist, RooAddPdf, RooBreitWigner, RooGaussian, RooExponential, RooVoigtian, RooAbsPdf, RooArgList, RooPlot, RooArgSet, RooAbsData, RooCBShape, RooNumConvPdf, RooFFTConvPdf, RooGenericPdf, RooFit, RooAbsReal

# Std python
import math as math
import os
from optparse import OptionParser

def main():

    parser = OptionParser()
    parser.add_option("-d", "--dir", type="string", dest="outDir", metavar="DIR", default="./",
                      help="output directory for .png")
        

    (options, args) = parser.parse_args()

    if os.path.exists(options.outDir) and options.outDir!="./":
        print "Sorry, file ",options.outDir," already exist, choose another name\n"
        exit(1)
    else:
        os.system("mkdir -p "+options.outDir)


    """
    Set the style ...
    """

    myNewStyle = TStyle("myNewStyle","A better style for my plots")
    setStyle(myNewStyle)

    TH1F.SetDefaultSumw2(True)

    # Histogram range
    xlow = 70.
    xup = 110.
    
    # Mass range for fit
    minM_fit = 75.
    maxM_fit = 105.

    # Ratio plot range
    minR = 0.8
    maxR = 1.2

    # TLines for ratio plot
    line = TLine(minM_fit,1,maxM_fit,1)
    line.SetLineWidth(2)
    line.SetLineColor(2)

    # Canvas
    spectrum_height = 0.75
    ratio_correction = 1.4
    ratio_height = (1-spectrum_height)*ratio_correction
    xOffset = 0.08
    yOffset = 0.04

    cTest = TCanvas("cTest","cTest")
    
    c2 = TCanvas("c2","c2")
    c2.SetFillColor(0)
    c2.Divide(1,2)

    
    c3 = TCanvas("c3","c3")
    c3.SetFillColor(0)
    c3.Divide(1,2)

    # Files MuScleFit
    fDataBefore = TFile("h3_Z_data_beforeCorrection.root")
    fDataAfter  = TFile("h3_Z_data_afterCorrection.root")
    fMcBefore = TFile("h3_Z_mc_beforeCorrection.root")
    fMcAfter  = TFile("h3_Z_mc_afterCorrection.root")
    
                
    # Retrieve histograms and fit
    hDataBefore = fDataBefore.Get("h1_Z_data")
    hDataAfter  = fDataAfter.Get("h1_Z_data")
    hMcBefore   = fMcBefore.Get("h1_Z_mc")
    hMcAfter    = fMcAfter.Get("h1_Z_mc")

    # Identifiers
    ids = ["data_before","data_after","mc_before","mc_after"]

    # Create histograms dictionary
    histos = {}
    histos["data_before"] = hDataBefore
    histos["data_after"]  = hDataAfter
    histos["mc_before"]   = hMcBefore
    histos["mc_after"]    = hMcAfter

    histosSubtr = {}

    # Create parameters dictionary
    expPars = {}
    signalPars = {}

    for i in ids:
        # RooFit definitions
        ## RooRealVars
        x = RooRealVar("x","M_{#mu#mu} (GeV)",minM_fit,maxM_fit)
        mean = RooRealVar("mean","mean",91.19,87.,94.)
        meanCB = RooRealVar("meanCB","meanCB",0.,-10.,10.)
        meanCB.setConstant(True)
        width = RooRealVar("width","width",2.4952,2.3,2.6)
        width.setConstant(True)
        sigma = RooRealVar("sigma","sigma",1.3,0.001,3.)
        #    sigma.setConstant(True)
        slope = RooRealVar("slope","slope",-0.1,-1.0,0.)
        #    slope.setConstant(True)
        alpha = RooRealVar("alpha","alpha",1.,0.,30.)
        #    alpha.setConstant(True)
        N = RooRealVar("N","N",2.,0.,100.)
        #    N.setConstant(True)
        fsig = RooRealVar("fsig","fsig",0.9,0.,1.0)
        
        ## PDFs
        relBW = RooGenericPdf("relBW","relBW","@0/(pow(@0*@0-@1*@1,2) + @2*@2*@0*@0*@0*@0/(@1*@1))",RooArgList(x,mean,width))
        CB = RooCBShape("CB","CB",x,meanCB,sigma,alpha,N)
        expo = RooExponential("expo","expo",x,slope)
        relBWTimesCB = RooFFTConvPdf("relBWTimesCB","relBWTimesCB",x,relBW,CB)
        relBWTimesCBPlusExp = RooAddPdf("relBWTimesCBPlusExp","relBWTimesCBPlusExp",relBWTimesCB,expo,fsig)

        # Fit
        frame = x.frame()
        h = histos[i]
        # h.Rebin(10)
        h.Sumw2()
        nbin = h.GetNbinsX()
        dh = RooDataHist("dh","dh",RooArgList(x),h)
        dh.plotOn(frame)
        relBWTimesCBPlusExp.fitTo(dh)
        relBWTimesCBPlusExp.plotOn(frame)
        relBWTimesCBPlusExp.paramOn(frame)

        # Plot
        c = TCanvas("c_"+i,"c_"+i) 
        c.SetFillColor(0)
        c.cd()
        frame.Draw()
        c.SaveAs(options.outDir+"/DimuonWithFit_"+i+".png")
        
        # Extract the result of the fit
        expParams = []
        expCoef = slope.getValV()
        fSig    = fsig.getValV()
        binLow = h.GetXaxis().FindBin(minM_fit)
        binHigh = h.GetXaxis().FindBin(maxM_fit)
        nEntries = h.Integral(binLow,binHigh)
        expParams = [expCoef,fSig,nEntries,binLow,binHigh]
        expPars[i] = expParams

        signalParams = [mean.getVal(),width.getVal(),meanCB.getVal(),sigma.getVal(),alpha.getVal(),N.getVal()]
        signalPars[i] = signalParams

        # Subtract the bkg from the histograms
        h_woBkg = h.Clone()
        h_bkg = TH1F("h_bkg_"+i,"Histogram of bkg events",nbin,xlow,xup)
        
        h_bkg.Sumw2()
        expNorm = (math.fabs(expCoef)*(1-fSig)*nEntries)/(math.exp(expCoef*minM_fit)-math.exp(expCoef*maxM_fit))
        for ibin in range(binLow,binHigh):
            w = integrateExp(expNorm,expCoef,h_bkg.GetBinLowEdge(ibin),h_bkg.GetBinLowEdge(ibin+1))
            h_bkg.SetBinContent(ibin,w)

        h_woBkg.Add(h_bkg,-1)
        nEvts_woBkg = h_woBkg.Integral(binLow,binHigh)
        h_woBkg.Scale(1/nEvts_woBkg)
        histosSubtr[i] = h_woBkg


        del expParams, c
        del relBWTimesCBPlusExp, relBW, CB, relBWTimesCB, expo
        del x, mean, width, sigma, fsig, N, alpha, slope, meanCB
        del frame, dh, h, h_woBkg, h_bkg



    # BEFORE CORRECTIONS
    
#     # RooFit definitions (again, sorry)
#     ## RooRealVars
#     x = RooRealVar("x","M_{#mu#mu} (GeV)",minM_fit,maxM_fit)
#     mean = RooRealVar("mean","mean",91.19)
#     meanCB = RooRealVar("meanCB","meanCB",0.)
#     width = RooRealVar("width","width",2.4952)
#     sigma = RooRealVar("sigma","sigma",1.3)
#     alpha = RooRealVar("alpha","alpha",1.)
#     N = RooRealVar("N","N",2.)

#     ## PDFs (again, sorry)
#     relBW = RooGenericPdf("relBW","relBW","@0/(pow(@0*@0-@1*@1,2) + @2*@2*@0*@0*@0*@0/(@1*@1))",RooArgList(x,mean,width))
#     CB = RooCBShape("CB","CB",x,meanCB,sigma,alpha,N)
#     relBWTimesCB = RooFFTConvPdf("relBWTimesCB","relBWTimesCB",x,relBW,CB)

    
    # Ratio plot after background subtraction
    histosSubtr["data_before"].GetXaxis().SetRangeUser(minM_fit,maxM_fit)
    histosSubtr["data_before"].GetYaxis().SetRangeUser(0.,histosSubtr["data_before"].GetMaximum()+0.1*histosSubtr["data_before"].GetMaximum())
    histosSubtr["data_before"].SetLineColor(1)

    histosSubtr["mc_before"].GetXaxis().SetRangeUser(minM_fit,maxM_fit)
    if histosSubtr["mc_before"].GetMaximum()>histosSubtr["data_before"].GetMaximum():
        histosSubtr["data_before"].GetYaxis().SetRangeUser(0.,histosSubtr["mc_before"].GetMaximum()+0.1*histosSubtr["mc_before"].GetMaximum())
    histosSubtr["mc_before"].SetLineColor(2)

    ## This is the simple overlay of the normalized spectra
    # c2.cd(1)
    r.SetOwnership(c2, False)
    c2_spectrum = c2.GetListOfPrimitives().FindObject("c2_1")
    c2_ratio    = c2.GetListOfPrimitives().FindObject("c2_2")
    c2_spectrum.SetPad(0.+xOffset, (1 - spectrum_height)+yOffset, 1.+xOffset, 1.+yOffset)
    c2_ratio.SetPad(0.+xOffset, 0.+yOffset, 1.+xOffset, ratio_height+yOffset)
    c2_ratio.SetTopMargin(0)   
    c2_ratio.SetBottomMargin(0.2)
    c2_spectrum.SetLeftMargin(0.12)
    c2_spectrum.SetRightMargin(0.15)
    c2_ratio.SetLeftMargin(0.12)
    c2_ratio.SetRightMargin(0.15)

    leg=0
    leg = TLegend(0.10,0.75,0.40,0.90)
    leg.SetHeader("Before corrections")
    leg.SetFillColor(0)
    leg.SetTextSize(0.06)
    leg.AddEntry(histosSubtr["data_before"],"DATA")
    leg.AddEntry(histosSubtr["mc_before"],"MC")
    setHistoStyle(histosSubtr["data_before"])
    setHistoStyle(histosSubtr["mc_before"])
    histosSubtr["data_before"].SetTitle("Dimuon mass spectrum (after background subtraction) data vs. MC")
    histosSubtr["data_before"].GetXaxis().SetTitle("M_{#mu#mu} (GeV)")
    histosSubtr["data_before"].GetYaxis().SetTitle("Arbitrary units")
    histosSubtr["mc_before"].GetXaxis().SetTitle("M_{#mu#mu} (GeV)")
    histosSubtr["mc_before"].GetYaxis().SetTitle("Arbitrary units")
    
    c2_spectrum.cd()
#     c2_spectrum.SetLogy()
    histosSubtr["data_before"].Draw("HIST")
    histosSubtr["mc_before"].Draw("HISTsame")
    tpt_pars_data = TPaveText(0.13, 0.45, 0.4, 0.59, "NDC")
    tpt_pars_data.SetTextSize(0.045)
    tpt_pars_data.SetTextFont(42)
    tpt_pars_data.SetFillColor(0)
    tpt_pars_data.SetBorderSize(0)
    tpt_pars_data.SetMargin(0.01)
    tpt_pars_data.SetTextAlign(12)
    tpt_pars_data.AddText(0.0,0.9,"M^{fit}_{Z,data} = "+str(round(signalPars["data_before"][0],2))+" GeV")
    tpt_pars_data.AddText(0.0,0.4,"#sigma_{CB,data} = "+str(round(signalPars["data_before"][3],2))+" GeV")
    tpt_pars_data.Draw("same")
    
    tpt_pars_mc = TPaveText(0.13, 0.30, 0.4, 0.44, "NDC")
    tpt_pars_mc.SetTextSize(0.045)
    tpt_pars_mc.SetTextFont(42)
    tpt_pars_mc.SetFillColor(0)
    tpt_pars_mc.SetBorderSize(0)
    tpt_pars_mc.SetMargin(0.01)
    tpt_pars_mc.SetTextAlign(12)
    tpt_pars_mc.SetTextColor(2)
    tpt_pars_mc.AddText(0.0,0.9,"M^{fit}_{Z,MC} = "+str(round(signalPars["mc_before"][0],2))+" GeV")
    tpt_pars_mc.AddText(0.0,0.4,"#sigma_{CB,MC} = "+str(round(signalPars["mc_before"][3],2))+" GeV")
    tpt_pars_mc.Draw("same")
    leg.Draw("same")
    
#     mean.setVal(signalPars["data_before"][0])
#     sigma.setVal(signalPars["data_before"][3])
#     alpha.setVal(signalPars["data_before"][4])
#     N.setVal(signalPars["data_before"][5])
#     dh_data = RooDataHist("dh_data","dh_data",RooArgList(x),histosSubtr["data_before"])
#     frame_data = x.frame()
#     dh_data.plotOn(frame_data,RooFit.LineColor(1),RooFit.DrawOption("B"))
#     # relBWTimesCB.plotOn(frame_data,RooFit.LineColor(1))
#     frame_data.Draw()

#     mean.setVal(signalPars["mc_before"][0])
#     # mean.setVal(97)
#     sigma.setVal(signalPars["mc_before"][3])
#     alpha.setVal(signalPars["mc_before"][4])
#     N.setVal(signalPars["mc_before"][5])
#     dh_mc = RooDataHist("dh_mc","dh_mc",RooArgList(x),histosSubtr["mc_before"])
#     frame_mc = x.frame()
#     # dh_mc.plotOn(frame_mc,RooFit.LineColor(2),RooFit.MarkerColor(2),RooFit.MarkerSize(0.4),RooFit.DrawOption("HIST"))
#     # relBWTimesCB.plotOn(frame_mc,RooFit.LineColor(2))
#     # frame_mc.Draw("same")


    ## Ratio histogram
    h_Num_woBkg = histosSubtr["data_before"].Clone()
    h_Den_woBkg = histosSubtr["mc_before"].Clone()
    # h_Num_woBkg.Rebin(10)
    # h_Den_woBkg.Rebin(10)
    h_Num_woBkg.Divide(h_Den_woBkg)
    h_Num_woBkg.GetXaxis().SetRangeUser(minM_fit,maxM_fit)
    h_Num_woBkg.GetYaxis().SetRangeUser(minR,maxR)
    h_Num_woBkg.GetXaxis().SetTitleSize(0.09)
    h_Num_woBkg.GetYaxis().SetTitleSize(0.09)
    h_Num_woBkg.GetXaxis().SetLabelSize(0.08)
    h_Num_woBkg.GetYaxis().SetLabelSize(0.08)
    h_Num_woBkg.GetYaxis().SetTitleOffset(0.45)

    ## This is the DATA/MC ratio
    c2_ratio.cd()
    h_Num_woBkg.GetYaxis().SetTitle("DATA/MC Ratio")
    h_Num_woBkg.SetTitle("")
    # setHistoStyle(h_Num_woBkg)
    h_Num_woBkg.SetMarkerStyle(20)
    h_Num_woBkg.SetMarkerSize(0.85)
    h_Num_woBkg.Draw("E")
    line.Draw("same")
    c2.SaveAs(options.outDir+"/DimuonAfterBkgSub_beforeCorrections.png")
    c2.SaveAs(options.outDir+"/DimuonAfterBkgSub_beforeCorrections.pdf")
    c2.SaveAs(options.outDir+"/DimuonAfterBkgSub_beforeCorrections.eps")

    del tpt_pars_data, tpt_pars_mc, h_Num_woBkg


    # AFTER CORRECTIONS
    
#     # RooFit definitions (again, sorry)
#     ## RooRealVars
#     x = RooRealVar("x","M_{#mu#mu} (GeV)",minM_fit,maxM_fit)
#     mean = RooRealVar("mean","mean",91.19)
#     meanCB = RooRealVar("meanCB","meanCB",0.)
#     width = RooRealVar("width","width",2.4952)
#     sigma = RooRealVar("sigma","sigma",1.3)
#     alpha = RooRealVar("alpha","alpha",1.)
#     N = RooRealVar("N","N",2.)

#     ## PDFs (again, sorry)
#     relBW = RooGenericPdf("relBW","relBW","@0/(pow(@0*@0-@1*@1,2) + @2*@2*@0*@0*@0*@0/(@1*@1))",RooArgList(x,mean,width))
#     CB = RooCBShape("CB","CB",x,meanCB,sigma,alpha,N)
#     relBWTimesCB = RooFFTConvPdf("relBWTimesCB","relBWTimesCB",x,relBW,CB)

    
    # Ratio plot after background subtraction
    histosSubtr["data_after"].GetXaxis().SetRangeUser(minM_fit,maxM_fit)
    histosSubtr["data_after"].GetYaxis().SetRangeUser(0.,histosSubtr["data_after"].GetMaximum()+0.1*histosSubtr["data_after"].GetMaximum())
    histosSubtr["data_after"].SetLineColor(1)

    histosSubtr["mc_after"].GetXaxis().SetRangeUser(minM_fit,maxM_fit)
    if histosSubtr["mc_after"].GetMaximum()>histosSubtr["data_after"].GetMaximum():
        histosSubtr["data_after"].GetYaxis().SetRangeUser(0.,histosSubtr["mc_after"].GetMaximum()+0.1*histosSubtr["mc_after"].GetMaximum())
    histosSubtr["mc_after"].SetLineColor(2)

    ## This is the simple overlay of the normalized spectra
    # c3.cd(1)
    r.SetOwnership(c3, False)
    c3_spectrum = c3.GetListOfPrimitives().FindObject("c3_1")
    c3_ratio    = c3.GetListOfPrimitives().FindObject("c3_2")
    c3_spectrum.SetPad(0.+xOffset, (1 - spectrum_height)+yOffset, 1.+xOffset, 1.+yOffset)
    c3_ratio.SetPad(0.+xOffset, 0.+yOffset, 1.+xOffset, ratio_height+yOffset)
    c3_ratio.SetTopMargin(0)   
    c3_ratio.SetBottomMargin(0.2)
    c3_spectrum.SetLeftMargin(0.12)
    c3_spectrum.SetRightMargin(0.15)
    c3_ratio.SetLeftMargin(0.12)
    c3_ratio.SetRightMargin(0.15)

    leg=0
    leg = TLegend(0.10,0.75,0.40,0.90)
    leg.SetHeader("After corrections")
    leg.SetFillColor(0)
    leg.SetTextSize(0.06)
    leg.AddEntry(histosSubtr["data_after"],"DATA")
    leg.AddEntry(histosSubtr["mc_after"],"MC")
    setHistoStyle(histosSubtr["data_after"])
    setHistoStyle(histosSubtr["mc_after"])
    histosSubtr["data_after"].SetTitle("Dimuon mass spectrum (after background subtraction) data vs. MC")
    histosSubtr["data_after"].GetXaxis().SetTitle("M_{#mu#mu} (GeV)")
    histosSubtr["data_after"].GetYaxis().SetTitle("Arbitrary units")
    histosSubtr["mc_after"].GetXaxis().SetTitle("M_{#mu#mu} (GeV)")
    histosSubtr["mc_after"].GetYaxis().SetTitle("Arbitrary units")
    
    c3_spectrum.cd()
#     c3_spectrum.SetLogy()
    histosSubtr["data_after"].Draw("HIST")
    histosSubtr["mc_after"].Draw("HISTsame")
    tpt_pars_data = 0
    tpt_pars_data = TPaveText(0.13, 0.45, 0.4, 0.59, "NDC")
    tpt_pars_data.SetTextSize(0.045)
    tpt_pars_data.SetTextFont(42)
    tpt_pars_data.SetFillColor(0)
    tpt_pars_data.SetBorderSize(0)
    tpt_pars_data.SetMargin(0.01)
    tpt_pars_data.SetTextAlign(12)
    tpt_pars_data.AddText(0.0,0.9,"M^{fit}_{Z,data} = "+str(round(signalPars["data_after"][0],2))+" GeV")
    tpt_pars_data.AddText(0.0,0.4,"#sigma_{CB,data} = "+str(round(signalPars["data_after"][3],2))+" GeV")
    tpt_pars_data.Draw("same")

    tpt_pars_mc = 0
    tpt_pars_mc = TPaveText(0.13, 0.30, 0.4, 0.44, "NDC")
    tpt_pars_mc.SetTextSize(0.045)
    tpt_pars_mc.SetTextFont(42)
    tpt_pars_mc.SetFillColor(0)
    tpt_pars_mc.SetBorderSize(0)
    tpt_pars_mc.SetMargin(0.01)
    tpt_pars_mc.SetTextAlign(12)
    tpt_pars_mc.SetTextColor(2)
    tpt_pars_mc.AddText(0.0,0.9,"M^{fit}_{Z,MC} = "+str(round(signalPars["mc_after"][0],2))+" GeV")
    tpt_pars_mc.AddText(0.0,0.4,"#sigma_{CB,MC} = "+str(round(signalPars["mc_after"][3],2))+" GeV")
    tpt_pars_mc.Draw("same")
    leg.Draw("same")
    
#     mean.setVal(signalPars["data_after"][0])
#     sigma.setVal(signalPars["data_after"][3])
#     alpha.setVal(signalPars["data_after"][4])
#     N.setVal(signalPars["data_after"][5])
#     dh_data = RooDataHist("dh_data","dh_data",RooArgList(x),histosSubtr["data_after"])
#     frame_data = x.frame()
#     dh_data.plotOn(frame_data,RooFit.LineColor(1),RooFit.DrawOption("B"))
#     # relBWTimesCB.plotOn(frame_data,RooFit.LineColor(1))
#     frame_data.Draw()

#     mean.setVal(signalPars["mc_after"][0])
#     # mean.setVal(97)
#     sigma.setVal(signalPars["mc_after"][3])
#     alpha.setVal(signalPars["mc_after"][4])
#     N.setVal(signalPars["mc_after"][5])
#     dh_mc = RooDataHist("dh_mc","dh_mc",RooArgList(x),histosSubtr["mc_after"])
#     frame_mc = x.frame()
#     # dh_mc.plotOn(frame_mc,RooFit.LineColor(2),RooFit.MarkerColor(2),RooFit.MarkerSize(0.4),RooFit.DrawOption("HIST"))
#     # relBWTimesCB.plotOn(frame_mc,RooFit.LineColor(2))
#     # frame_mc.Draw("same")


    ## Ratio histogram
    h_Num_woBkg = histosSubtr["data_after"].Clone()
    h_Den_woBkg = histosSubtr["mc_after"].Clone()
    # h_Num_woBkg.Rebin(10)
    # h_Den_woBkg.Rebin(10)
    h_Num_woBkg.Divide(h_Den_woBkg)
    h_Num_woBkg.GetXaxis().SetRangeUser(minM_fit,maxM_fit)
    h_Num_woBkg.GetYaxis().SetRangeUser(minR,maxR)
    h_Num_woBkg.GetXaxis().SetTitleSize(0.09)
    h_Num_woBkg.GetYaxis().SetTitleSize(0.09)
    h_Num_woBkg.GetXaxis().SetLabelSize(0.08)
    h_Num_woBkg.GetYaxis().SetLabelSize(0.08)
    h_Num_woBkg.GetYaxis().SetTitleOffset(0.45)

    ## This is the DATA/MC ratio
    c3_ratio.cd()
    h_Num_woBkg.GetYaxis().SetTitle("DATA/MC Ratio")
    h_Num_woBkg.SetTitle("")
    # setHistoStyle(h_Num_woBkg)
    h_Num_woBkg.SetMarkerStyle(20)
    h_Num_woBkg.SetMarkerSize(0.85)
    h_Num_woBkg.Draw("E")
    line.Draw("same")
    c3.SaveAs(options.outDir+"/DimuonAfterBkgSub_afterCorrections.png")
    c3.SaveAs(options.outDir+"/DimuonAfterBkgSub_afterCorrections.pdf")
    c3.SaveAs(options.outDir+"/DimuonAfterBkgSub_afterCorrections.eps")







## Want to avoid installing SciPy ...
def integrateExp(A,l,low,up):
    return (A/l)*(math.exp(up*l)-math.exp(low*l))

## Simple helper for setting the style of the histograms
def setHistoStyle(histo):
    """
    This is simply esthetic...
    """
    histo.SetFillColor(0)
    histo.SetTitleSize(0.5);
    histo.SetTitleFont(42); 
    histo.SetLineWidth(2);
    histo.GetYaxis().SetTitleOffset(1.1);
    histo.GetXaxis().SetTitleOffset(0.9);
    histo.GetYaxis().SetTitleSize(0.05);
    histo.GetXaxis().SetTitleSize(0.045);
    histo.GetXaxis().SetTitleFont(42); 
    histo.GetYaxis().SetTitleFont(42);  
    histo.GetXaxis().SetLabelSize(0.04); 
    histo.GetYaxis().SetLabelSize(0.04);
    histo.GetXaxis().SetLabelFont(42);
    histo.GetYaxis().SetLabelFont(42); 
    return

def setStyle(newStyle):
    newStyle.SetOptTitle(0);
    newStyle.SetOptStat(0)
    newStyle.SetTitleFont(42);
    newStyle.SetTitleColor(1);
    newStyle.SetTitleTextColor(1);
    newStyle.SetTitleBorderSize(0);
    newStyle.SetTitleFontSize(0.06);
    newStyle.SetOptStat(0);
    newStyle.SetTitleFillColor(10);
    newStyle.SetTitleBorderSize(0);
    newStyle.SetCanvasBorderMode(0);
    newStyle.SetFrameBorderMode(0);
    newStyle.SetPadBorderMode(0);
    newStyle.SetNdivisions(303);
    newStyle.SetStatColor(0);
    newStyle.SetStatFont(42);
    newStyle.SetStatFontSize(0.05);#///---> newStyle.SetStatFontSize(0.025);
    newStyle.SetStatTextColor(1);
    newStyle.SetStatFormat("6.4g");
    newStyle.SetStatBorderSize(1);
    
    newStyle.SetPadTickX(1);  #// To get tick marks on the opposite side of the frame
    newStyle.SetPadTickY(1);
    newStyle.SetPadBorderMode(0); 
    newStyle.SetPadTopMargin(0.1);
    newStyle.SetPadBottomMargin(0.13);
    newStyle.SetPadLeftMargin(0.14);
    newStyle.SetPadRightMargin(0.14);
    newStyle.SetCanvasDefH(600); #//Height of canvas
    newStyle.SetCanvasDefW(600); #//Width of canvas

    newStyle.cd()


if __name__ == "__main__":
    main()
    



