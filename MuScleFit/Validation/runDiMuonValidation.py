#!/usr/bin/env python

import os, subprocess
from optparse import OptionParser
from TreePath import *

def main():
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

    (opt, args) = parser.parse_args()

    os.system('gmake clean; gmake all')

    outCfgName = 'dimuon_validation'+opt.appendToCfg+'.cfg'
    outCfg = open(outCfgName,'w')

    if opt.recreateTrees==True:
      recreate = "RECREATE"
    else:    
       recreate = "READ"

    if opt.processZ==True:
#         outCfg.write("Z data "+subprocess.check_output(['cmsPfn',ZdataTree]).rstrip()+" "+ZdataTxt+" 70 110 "+recreate+" \n")
#         outCfg.write("Z mc "+subprocess.check_output(['cmsPfn',ZmcTree]).rstrip()+" "+ZmcTxt+" 70 110 "+recreate+" \n")
        outCfg.write("Z data "+ZdataTree+" "+ZdataTxt+" 70 110 "+recreate+" \n")
        outCfg.write("Z mc "+ZmcTree+" "+ZmcTxt+" 70 110 "+recreate+" \n")
    if opt.processY==True:
#         outCfg.write("Y data "+subprocess.check_output(['cmsPfn',YdataTree]).rstrip()+" "+YdataTxt+" 8.6 11.3 "+recreate+" \n")
#         outCfg.write("Y mc "+subprocess.check_output(['cmsPfn',YmcTree]).rstrip()+" "+YmcTxt+" 8.6 11.3 "+recreate+" \n")
        outCfg.write("Y data "+YdataTree+" "+YdataTxt+" 8.6 11.3 "+recreate+" \n")
        outCfg.write("Y mc "+YmcTree+" "+YmcTxt+" 8.6 11.3 "+recreate+" \n")
    if opt.processJPsi==True:
#         outCfg.write("JPsi data "+subprocess.check_output(['cmsPfn',JPsidataTree]).rstrip()+" "+JPsidataTxt+" 2.8 3.4 "+recreate+" \n")
#         outCfg.write("JPsi mc "+subprocess.check_output(['cmsPfn',JPsimcTree]).rstrip()+" "+JPsimcTxt+" 2.8 3.4 "+recreate+" \n")
        outCfg.write("JPsi data "+JPsidataTree+" "+JPsidataTxt+" 2.8 3.4 "+recreate+" \n")
        outCfg.write("JPsi mc "+JPsimcTree+" "+JPsimcTxt+" 2.8 3.4 "+recreate+" \n")

    outCfg.write("# stupid std::ifstream: this file should not end with an empty line!")

    outCfg.close()

    '''
    Create the output root files with TH3s'''
    validateString = "./validate "+outCfgName
    if opt.quiet == True:
        validateString += " >& /dev/null"
    os.system(validateString)


    '''
    Merge with hadd to have a single root file'''
    if os.path.exists('h3_afterCorrection.root') == True:
        os.system("rm h3_afterCorrection.root")
        
    os.system("hadd h3_afterCorrection.root `ls $TMPDIR/h3_*afterCorrection.root`")


    '''
    Run the Fitter'''

    os.system("root -b -q -l 'Fitter.C+(\"h3_afterCorrection.root\",\"TGEs_afterCorrection.root\",\"_afterCorrection\")'")

    '''
    Run the Plotter'''
    os.system("root -b -q -l 'Plotter.C+(\"TGEs_afterCorrection.root\",\"_afterCorrection\")'")

    '''
    Cosmetics'''
    os.system("mkdir "+opt.outDir)
    os.system("mv *afterCorrection*.root *afterCorrection*.png "+opt.outDir)

    
    


if __name__ == '__main__':
    main()
