#!/bin/sh 


source /afs/cern.ch/sw/lcg/external/gcc/4.7.2/x86_64-slc6-gcc47-opt/setup.sh
source /afs/cern.ch/sw/lcg/app/releases/ROOT/5.34.07/x86_64-slc6-gcc46-opt/root/bin/thisroot.sh

export PATH=$PATH:/afs/cern.ch/sw/lcg/external/xrootd/3.1.0p2/x86_64-slc6-gcc47-opt/bin
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/afs/cern.ch/sw/lcg/external/xrootd/3.1.0p2/x86_64-slc6-gcc47-opt/lib

touch foo.C
echo '{std::cout<<"Congratulations: you have set up ROOT and Roofit!"<<std::endl;} ' >> foo.C

root -l -q foo.C

rm foo.C



