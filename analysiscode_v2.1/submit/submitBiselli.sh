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
biselliInput='/volatile/halla/sbs/bclary/eg1analysis/biselli_output/'*.root

for f in $biselliInput; do
echo " $f"
done

echo "Executing script to create N jobs for N runs"

#While loop is for the pid part of the analysis
while read -r line
do

#for f in $biselliInput; do

   echo "Creating jsub file for job type $analysisType for run $line"
    i=$((i+1))
    #Create jsub file for nth run
    jsubfile=$'job_'$i'_root22_'$analysisType'_'$line'.jsub'    
    echo "JOBNAME:  bc$analysisType" >> $jsubfile                                                                                                                             
    echo "OS:       centos7" >> $jsubfile                                                                                                                                     
    echo "TRACK:    debug" >> $jsubfile                                                                                                                                       
    echo "MEMORY:   2042 MB" >> $jsubfile                                                                                                                                     
    echo "PROJECT:  clas12" >> $jsubfile                                                
    #for PID use $line in place of $f below
    # vice versa for DVCS with dap
    echo "COMMAND: /u/home/bclary/batch_submit/batch/analyzeBiselli.csh $analysisType $line" >> $jsubfile                                                                        
    echo "OTHER_FILES:" >> $jsubfile                                                                                                                                         
#  dap is for dvcs phase
#    echo "/u/home/bclary/eg1analysis/biselli_code/biselli_eg1dvcs/dap/dap" >> $jsubfile
    #Uncomment below line to use for the PID phase
    echo "/u/home/bclary/eg1analysis/biselli_code/biselli_eg1dvcs/nt22filter/nt22filter" >> $jsubfile                                                                                  
    #echo "/u/home/bclary/eg1analysis/biselli_code/biselli_eg1dvcs/dap/dap" >> $jsubfile
done < "$run_list"
#done
mv *.jsub /u/home/bclary/batch_submit/batch_jsubs

jsub_extension="*.jsub"

if [ "$jsubmit" = true ] ; then
    echo "Sending jobs to farm"
    for f in "$build_dir$batch_dir"*.jsub
    do
	jsub $f
    done
fi

 
