#!/bin/bash

jsubmit=false
build_dir='/u/home/bclary/batch_submit/'
batch_dir='batch'
run_list='/u/home/bclary/eg1analysis/SKIMprotocol/analysiscode_v2.1/submit/runlist.txt'
run_directory="/lustre/expphy/work/hallb/claseg1dvcs/pass1/v3/root/root22_"
prefix="root22_"
filetype="*.root"
PIDskeletonjsub='/u/home/bclary/eg1analysis/SKIMprotocol/analysiscode_v2.1/submit/skeletonjsubPID.txt'
i=0
echo "Executing script to create jsub files" 

cd $build_dir$batch_dir

while read -r line
do
   filepath="$run_directory$line"
   i=$((i+1))

   #Create files to submit as jobs to the farm
   jsubfile=$'job_'$i'_root22_'$line'.jsub'

   #Second .jsub
   cp $PIDskeletonjsub $jsubfile
   #Append desired files to analyze to jsub file
   for f in "$filepath"*.root	     
   do
       # Boolean statement to ignore files not of the current run number
       if [ ! -f "$f" ]
       then
	   continue
       fi
   echo $f >> $jsubfile
   done
done < "$run_list"

if [ "$jsubsubmit" = true ] ; then
echo "Sending jobs to farm."	
    for f in "$build_dir$batch_dir"*.jsub
    do
	jsub $f
    done    
fi
echo "Complete - all jobs have been sent to farm"
