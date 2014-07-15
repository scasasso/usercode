from ROOT import TStyle


def setTdrStyle():
    myStyle = TStyle('myStyle','a better style for my plot')
    
    # For the canvas:
    myStyle.SetCanvasBorderMode(0);
    myStyle.SetCanvasColor(0);
    myStyle.SetCanvasDefH(600); #Height of canvas
    myStyle.SetCanvasDefW(600); #Width of canvas
    myStyle.SetCanvasDefX(0);   #POsition on screen
    myStyle.SetCanvasDefY(0);
    
    # For the Pad:
    myStyle.SetPadBorderMode(0);
    myStyle.SetPadColor(0);
    myStyle.SetPadGridX(False);
    myStyle.SetPadGridY(False);
    myStyle.SetGridColor(0);
    myStyle.SetGridStyle(3);
    myStyle.SetGridWidth(1);
    
    # For the frame:
    myStyle.SetFrameBorderMode(0);
    myStyle.SetFrameBorderSize(1);
    myStyle.SetFrameFillColor(0);
    myStyle.SetFrameFillStyle(0);
    myStyle.SetFrameLineColor(1);
    myStyle.SetFrameLineStyle(1);
    myStyle.SetFrameLineWidth(1);
    
    # For the histo:
    myStyle.SetHistLineColor(1);
    myStyle.SetHistLineStyle(0);
    myStyle.SetHistLineWidth(1);
    
    myStyle.SetEndErrorSize(2);
    
    #For the fit/function:
    myStyle.SetOptFit(1);
    myStyle.SetFitFormat("5.4g");
    myStyle.SetFuncColor(2);
    myStyle.SetFuncStyle(1);
    myStyle.SetFuncWidth(1);
    
    #For the date:
    myStyle.SetOptDate(0);
    
    # For the statistics box:
    myStyle.SetOptFile(0);
    myStyle.SetOptStat(0); # To display the mean and RMS:   SetOptStat("mr");
    myStyle.SetStatColor(0);
    myStyle.SetStatFont(40);
    myStyle.SetStatFontSize(0.025);
    myStyle.SetStatTextColor(1);
    myStyle.SetStatFormat("6.4g");
    myStyle.SetStatBorderSize(1);
    myStyle.SetStatH(0.1);
    myStyle.SetStatW(0.15);
    
    # Margins:
    myStyle.SetPadTopMargin(0.07);
    myStyle.SetPadBottomMargin(0.15);
    myStyle.SetPadLeftMargin(0.2);
    myStyle.SetPadRightMargin(0.05);
    
    # For the Global title:
    
    myStyle.SetOptTitle(0);
    myStyle.SetTitleColor(1);
    myStyle.SetTitleTextColor(1);
    myStyle.SetTitleFillColor(10);
    myStyle.SetTitleFontSize(0.05);

    # For the axis titles:

    myStyle.SetTitleColor(1, "XYZ");
    #myStyle.SetTitleFont(40, "XYZ");
    myStyle.SetTitleSize(0.055, "XYZ");

    # For the axis labels:

    myStyle.SetLabelColor(1, "XYZ");
    myStyle.SetLabelFont(40, "XYZ");
    myStyle.SetLabelOffset(0.007, "XYZ");
    myStyle.SetLabelSize(0.05, "XYZ");
    
    # For the axis:
    
    myStyle.SetAxisColor(1, "XYZ");
    myStyle.SetStripDecimals(True);
    myStyle.SetTickLength(0.03, "XYZ");
    myStyle.SetNdivisions(510, "XYZ");
    myStyle.SetPadTickX(1);  # To get tick marks on the opposite side of the frame
    myStyle.SetPadTickY(1);
  
    # Change for log plots:
    myStyle.SetOptLogx(0);
    myStyle.SetOptLogy(0);
    myStyle.SetOptLogz(0);
    
    # Postscript options:
    myStyle.SetPaperSize(20.,20.);
    
    myStyle.cd()
