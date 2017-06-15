#!/bin/bash

jsubmit=$2
build_dir='/u/home/bclary/batch_submit/'                                                                                                     
batch_dir='batch_jsubs/'                                                                                                                    
run_list='/u/home/bclary/eg1analysis/SKIMprotocol/analysiscode_v2.1/submit/runlist.txt'                                                     
run_directory="/lustre/expphy/work/hallb/claseg1dvcs/pass1/v3/root/root22_"                                                                 
prefix="root22_"                                                                                                                            
filetype="*.root"                                                                                                                                                                           
PIDskeletonjsub='/u/home/bclary/eg1analysis/SKIMprotocol/analysiscode_v2.1/submit/skeletonjsubPID.txt'                                                                                      
i=0 
analysisType=$1

echo "Executing script to create N jobs for N runs"



while read -r line
do
    echo "Creating jsub file for job type $analysisType for run $line"
    i=$((i+1))
    #Create jsub file for nth run
    jsubfile=$'job_'$i'_root22_'$analysisType'_'$line'.jsub'    
    echo "JOBNAME:  bc$analysisType" >> $jsubfile                                                                                                                             
    echo "OS:       centos7" >> $jsubfile                                                                                                                                     
    echo "TRACK:    simulation" >> $jsubfile                                                                                                                                       
    echo "MEMORY:   2042 MB" >> $jsubfile                                                                                                                                    
    echo "PROJECT:  clas12" >> $jsubfile                                                                                                                                     
    echo "COMMAND: /u/home/bclary/batch_submit/batch/analyzeRun.csh $line $analysisType" >> $jsubfile                                                                        
    echo "OTHER_FILES:" >> $jsubfile                                                                                                                                         
    echo "/u/home/bclary/eg1analysis/SKIMprotocol/analysiscode_v2.2/analysiscode_v2.1/stage1PID" >> $jsubfile                                                                                  
    
done < "$run_list"

echo " You have created $i jobs to be sent to the Jlab's farm "  
mv *.jsub /u/home/bclary/batch_submit/batch_jsubs

jsub_extension="*.jsub"

if [ "$jsubmit" = true ] ; then
    echo "Sending jobs to farm"
    for f in "$build_dir$batch_dir"*.jsub
    do
	jsub $f
    done
fi

 
