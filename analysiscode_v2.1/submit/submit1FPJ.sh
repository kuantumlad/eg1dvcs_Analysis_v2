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

for file in "$run_directory"*.root
do
    i=$((i+1))
    jsubfile=$'job_'$i'_root22.jsub'
    if [ ! -f "$file" ];then
	continue
    fi
    echo "JOBNAME:  bcPID" >> $jsubfile
    echo "OS:       centos7" >> $jsubfile
    echo "TRACK:    debug" >> $jsubfile
    echo "MEMORY:   2048 MB" >> $jsubfile
    echo "PROJECT:  clas12" >> $jsubfile
    echo "COMMAND: /u/home/bclary/batch_submit/batch/execute_job.csh $file" >> $jsubfile
    echo "OTHER_FILES:" >> $jsubfile                                
    echo "/u/home/bclary/eg1analysis/SKIMprotocol/analysiscode_v2.1/stage1PID" >> $jsubfile

    mv $jsubfile /u/home/bclary/batch_submit/batch_help/

done

echo "Completed all jsub job files"
