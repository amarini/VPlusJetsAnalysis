#!/bin/bash

echo "V00-09"
read

OUTDIR=~/work/V00-09/Output_V00-09/
for config in data/config_MM.ini data/config_EE.ini data/config_TT.ini; do
#
for j in {0..9} ; do

[ "$config" == "data/config_MM.ini" ] && CHID=4;
[ "$config" == "data/config_EE.ini" ] && CHID=1;
[ "$config" == "data/config_TT.ini" ] && CHID=2;

	
bsub -q 1nh -o output/log.txt <<EOF
export "SCRAM_ARCH=slc5_amd64_gcc462"
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/afs/cern.ch/work/a/amarini/RooUnfold-1.1.1/
cd ~/work/CMSSW_5_3_7/src/amarini/VPlusJetsAnalysis/
cmsenv
source /afs/cern.ch/sw/lcg/app/releases/ROOT/5.34.07/x86_64-slc5-gcc46-opt/root/bin/thisroot.sh
./tpexe $config $j 10
EOF
done
done

