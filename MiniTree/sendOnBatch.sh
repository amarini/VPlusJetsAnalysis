#!/bin/bash

QUEUE=8nh
echo "V00-09"
read

OUTDIR=~/work/V00-09/Output_V00-09/
NJOBS=1
for type in {0..6} ; do
for config in data/config_MM.ini data/config_EE.ini data/config_TT.ini; do
#
for j in 0 ; do # 0..NJOBS-1

[ "$config" == "data/config_MM.ini" ] && CHID=4;
[ "$config" == "data/config_EE.ini" ] && CHID=1;
[ "$config" == "data/config_TT.ini" ] && CHID=2;

	
bsub -q $QUEUE -o output/log_type${type}_chid${CHID}_${j}_${NJOBS}.txt <<EOF
export "SCRAM_ARCH=slc5_amd64_gcc462"
cd ~/work/CMSSW_5_3_7/src/amarini/VPlusJetsAnalysis/
eval \`scramv1 runtime -sh\`
./tree.exe $config $j ${NJOBS} $type
EOF

done
done
done


#source /afs/cern.ch/sw/lcg/app/releases/ROOT/5.34.07/x86_64-slc5-gcc46-opt/root/bin/thisroot.sh
