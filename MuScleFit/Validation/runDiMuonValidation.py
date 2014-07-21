#!/usr/bin/env python

import os, subprocess
from optparse import OptionParser
from TreePath import *
import subprocess
import shlex


def processCmd(cmd):

    args = shlex.split(cmd)
    sp = subprocess.Popen(args, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    out, err = sp.communicate()

    return out, err



def parseOption():

    parser = OptionParser()
    parser.add_option("-d", "--outDir", dest="outDir", type="string", metavar="<my out directory>", default="./",
                      help="Specify output directory where to store the results of the validation")
    parser.add_option("-q", "--quiet", dest="quiet", action="store_true", default=False,
                      help="If fired run the validation in quiet mode")
    parser.add_option("-z", "--processZ", action="store_true", dest="processZ", default=False,
                      help="If fired the script will process the Z resonance")
    parser.add_option("-y", "--processY", action="store_true", dest="processY", default=False,
                      help="If fired the script will process the Y resonance")
    parser.add_option("-j", "--processJPsi", action="store_true", dest="processJPsi", default=False,
                      help="If fired the script will process the JPsi resonance")
    parser.add_option("-r", "--recreateTrees", action="store_true", dest="recreateTrees", default=False,
                      help="If fired the script will recreate the input trees (it may take several minutes)")
    parser.add_option("-a", "--appendToCfg", type="string", dest="appendToCfg", metavar="<my string>", default="",
                      help="Specify a string to the cfg name (to avoid overwriting it in the future)")

    global opt, args
    (opt, args) = parser.parse_args()

    if( os.path.isdir(opt.outDir) == True ):
        input = raw_input( 'The directory ' + opt.outDir + ' exists. Are you sure you want to continue? its contents will be overwritten [y/n]' )
        
        if input == 'n':
            sys.exit(1)
        elif input == "y":            
            os.system('rm -rf ' + opt.outDir)
            os.system('mkdir -p ' +opt.outDir)
        else:
            print 'I told you to type \"y\" or \"n\" and that was your only chance, I am exiting'
            sys.exit(1)
    else: os.system('mkdir -p ' +opt.outDir)
            

def main():
    
    # Compile executable
    os.system('gmake clean; gmake all')

    # Create datacard for the executable
    outCfgName = 'dimuon_validation'+opt.appendToCfg+'.cfg'
    outCfg = open(outCfgName,'w')
    
    # ROOT TFile option
    if opt.recreateTrees==True:
      recreate = "RECREATE"
    else:    
       recreate = "READ"
       
    # Process Z
    if opt.processZ==True:

        # Check parameter files
        try:
            ZdataTxt
            print "Using correction for Z in data:\n",ZdataTxt
        except NameError:
            print "Define the corrections to be used for Z in data, in TreePath.py under \"ZdataTxt\""
            sys.exit()
        if not os.path.exists(ZdataTxt):
            print "File ",ZdataTxt,"does not exist!"
            sys.exit()            

        try:
            ZmcTxt 
            print "Using correction for Z in MC:\n",ZmcTxt           
        except NameError:
            print "Define the corrections to be used for Z in MC, in TreePath.py under \"ZmcTxt\""            
            sys.exit()
        if not os.path.exists(ZmcTxt):
            print "File ",ZmcTxt,"does not exist!"
            sys.exit()

        # Check tree files            
        try:
            fileSize = float(processCmd("cmsLs "+ZdataTree)[0].split()[1])/(1024*1024)
            print "Tree for Z->mumu data: ",ZdataTree
            if fileSize<1: #MB
                print "Something is wrong with file ",ZdataTree
                sys.exit()            
        except ValueError:
            print "Tree file doe not seem to exist:\n",ZdataTree
            sys.exit()

        try:
            fileSize = float(processCmd("cmsLs "+ZmcTree)[0].split()[1])/(1024*1024)
            print "Tree for Z->mumu mc: ",ZmcTree
            if fileSize<1: #MB
                print "Something is wrong with file ",ZmcTree
                sys.exit()            
        except ValueError:
            print "Tree file doe not seem to exist:\n",ZmcTree
            sys.exit()
                    

        ZdataTree_pfn = processCmd('cmsPfn '+ZdataTree)[0].strip()
        ZmcTree_pfn = processCmd('cmsPfn '+ZmcTree)[0].strip()        
        outCfg.write("Z data "+ZdataTree_pfn+" "+ZdataTxt+" 70 110 "+recreate+" \n")
        outCfg.write("Z mc "+ZmcTree_pfn+" "+ZmcTxt+" 70 110 "+recreate+" \n")

    # Process Y
    if opt.processY==True:

        # Check parameter files
        try:
            YdataTxt
            print "Using correction for Y in data:\n",YdataTxt
        except NameError:
            print "Define the corrections to be used for Y in data, in TreePath.py under \"YdataTxt\""
            sys.exit()
        if not os.path.exists(YdataTxt):
            print "File ",YdataTxt,"does not exist!"
            sys.exit()            

        try:
            YmcTxt 
            print "Using correction for Y in MC:\n",YmcTxt           
        except NameError:
            print "Define the corrections to be used for Y in MC, in TreePath.py under \"YmcTxt\""            
            sys.exit()
        if not os.path.exists(YmcTxt):
            print "File ",YmcTxt,"does not exist!"
            sys.exit()

        # Check tree files            
        try:
            fileSize = float(processCmd("cmsLs "+YdataTree)[0].split()[1])/(1024*1024)
            print "Tree for Y->mumu data: ",YdataTree
            if fileSize<1: #MB
                print "Something is wrong with file ",YdataTree
                sys.exit()            
        except ValueError:
            print "Tree file doe not seem to exist:\n",YdataTree
            sys.exit()

        try:
            fileSize = float(processCmd("cmsLs "+YmcTree)[0].split()[1])/(1024*1024)
            print "Tree for Y->mumu mc: ",YmcTree
            if fileSize<1: #MB
                print "Something is wrong with file ",YmcTree
                sys.exit()            
        except ValueError:
            print "Tree file doe not seem to exist:\n",YmcTree
            sys.exit()

        YdataTree_pfn = processCmd('cmsPfn '+YdataTree)[0].strip()
        YmcTree_pfn = processCmd('cmsPfn '+YmcTree)[0].strip()                
        outCfg.write("Y data "+YdataTree_pfn+" "+YdataTxt+" 8.6 11.3 "+recreate+" \n")
        outCfg.write("Y mc "+YmcTree_pfn+" "+YmcTxt+" 8.6 11.3 "+recreate+" \n")

    # Process JPsi        
    if opt.processJPsi==True:

        # Check parameter files
        try:
            JPsidataTxt
            print "Using correction for JPsi in data:\n",JPsidataTxt
        except NameError:
            print "Define the corrections to be used for JPsi in data, in TreePath.py under \"JPsidataTxt\""
            sys.exit()
        if not os.path.exists(JPsidataTxt):
            print "File ",JPsidataTxt,"does not exist!"
            sys.exit()            

        try:
            JPsimcTxt 
            print "Using correction for JPsi in MC:\n",JPsimcTxt           
        except NameError:
            print "Define the corrections to be used for JPsi in MC, in TreePath.py under \"JPsimcTxt\""            
            sys.exit()
        if not os.path.exists(JPsimcTxt):
            print "File ",JPsimcTxt,"does not exist!"
            sys.exit()

        # Check tree files            
        try:
            fileSize = float(processCmd("cmsLs "+JPsidataTree)[0].split()[1])/(1024*1024)
            print "Tree for JPsi->mumu data: ",JPsidataTree
            if fileSize<1: #MB
                print "Something is wrong with file ",JPsidataTree
                sys.exit()            
        except ValueError:
            print "Tree file doe not seem to exist:\n",JPsidataTree
            sys.exit()

        try:
            fileSize = float(processCmd("cmsLs "+JPsimcTree)[0].split()[1])/(1024*1024)
            print "Tree for JPsi->mumu mc: ",JPsimcTree
            if fileSize<1: #MB
                print "Something is wrong with file ",JPsimcTree
                sys.exit()            
        except ValueError:
            print "Tree file doe not seem to exist:\n",JPsimcTree
            sys.exit()

        JPsidataTree_pfn = processCmd('cmsPfn '+JPsidataTree)[0].strip()
        JPsimcTree_pfn = processCmd('cmsPfn '+JPsimcTree)[0].strip()                
        outCfg.write("JPsi data "+JPsidataTree_pfn+" "+JPsidataTxt+" 2.8 3.4 "+recreate+" \n")
        outCfg.write("JPsi mc "+JPsimcTree_pfn+" "+JPsimcTxt+" 2.8 3.4 "+recreate+" \n")
        

    outCfg.write("# stupid std::ifstream: this file should not end with an empty line!")

    outCfg.close()

    # Create the output root files with TH3s
    validateString = "./validate "+outCfgName
    if opt.quiet == True:
        validateString += " >& /dev/null"
        print "Validate command will be issued in silent mode, don't panic or Ctrl+C or Ctrl+Z if you do not see outpout in your shell ..."
    os.system(validateString)


    # Merge with hadd to have a single root file
    if os.path.exists('h3_afterCorrection.root'): os.system("rm h3_afterCorrection.root")
    if os.path.exists('h3_beforeCorrection.root'): os.system("rm h3_beforeCorrection.root")    
        
    os.system("hadd h3_afterCorrection.root `ls $TMPDIR/h3_*afterCorrection.root`")
    os.system("hadd h3_beforeCorrection.root `ls $TMPDIR/h3_*beforeCorrection.root`")


    # Run the Fitter
    os.system("root -b -q -l 'Fitter.C+(\"h3_afterCorrection.root\",\"TGEs_afterCorrection.root\",\"_afterCorrection\")'")
    os.system("root -b -q -l 'Fitter.C+(\"h3_beforeCorrection.root\",\"TGEs_beforeCorrection.root\",\"_beforeCorrection\")'")


    # Run the Plotter
    os.system("root -b -q -l 'Plotter.C+(\"TGEs_afterCorrection.root\",\"_afterCorrection\")'")
    os.system("root -b -q -l 'Plotter.C+(\"TGEs_beforeCorrection.root\",\"_beforeCorrection\")'")    

    # Mv plots in the output directory
    os.system("mv *Correction*.root *Correction*.png *Correction*.pdf *Correction*.eps "+opt.outDir)


        
if __name__ == '__main__':

    parseOption()
    main()
