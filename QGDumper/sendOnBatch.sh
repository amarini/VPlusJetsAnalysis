#!/bin/bash

for config in data/config_MM.ini data/config_EE.ini data/config_TT.ini ; do
for type in {0..1} ;do
#
#for j in {0..9} ; do

	
bsub -q 1nh -o output/log_QG.txt <<EOF
export "SCRAM_ARCH=slc5_amd64_gcc462"
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/afs/cern.ch/work/a/amarini/RooUnfold-1.1.1/
cd ~/work/CMSSW_5_3_7/src/amarini/VPlusJetsAnalysis/
cmsenv
./qgexe data/config_nJets.ini $config $type
EOF

done
done
#done

