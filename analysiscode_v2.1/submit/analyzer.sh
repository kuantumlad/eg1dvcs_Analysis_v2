#!/bin/bash

#######################################################
##
##   Bash script to send jobs to JLabs farm
##   for either PID, DVCS, or Monte Carlo analysis
##
##   By: Brandon A. Clary
##   Version 1.1 - 5/13/2017
##
#######################################################

root22_location="/lustre/expphy/work/hallb/claseg1dvcs/pass1/v3/root/root22_"                                                                 
root22_prefix="root22_"                                                                                                                
EXT="*.root"

jsub_dir='/u/home/bclary/batch_submit/batch_jsubs/'


UserPrompt (){

    echo ">> Please enter the type of analysis: PID or DVCS or MC-"
    read analysisType

    echo ">> Do you want to submit the jobs to the farm? Enter true or false: "
    read jsubmit
    
}

Confirm (){

    echo ">> Do you want to continue? Enter y or n."
    echo "   y - will create jsub files."
    echo "   n - will exit program."
    read proceed

    if [ "$proceed" = "y" ]
    then 
	# 0 = true
	return 0
    elif [ "$proceed" = "n" ]
    then
	# 1 = false
	return 1
    fi
}

CreateJSubs (){

    goodrunlist='/u/home/bclary/eg1analysis/SKIMprotocol/analysiscode_v2.1/submit/runlist.txt'                                                     
    echo ">> Creating jsub files for $analysisType analysis"
    local i=0
    while read -r line
    do
	echo ">>>Making jsub file for job type $analysisType for run $line"
	i=$((i+1))
    #Create jsub file for nth run
	jsubfile=$'job_'$i'_root22_'$analysisType'_'$line'.jsub'    
	echo "JOBNAME:  bc$analysisType""_"$i >> $jsubfile                                                                                                                             
	echo "OS:       centos7" >> $jsubfile                                                                                                                                     
	echo "TRACK:    simulation" >> $jsubfile                                                                                                                                       
	echo "MEMORY:   2042 MB" >> $jsubfile                                                                                                                                    
	echo "PROJECT:  clas12" >> $jsubfile                                                                                                                                     
	echo "COMMAND: /u/home/bclary/batch_submit/batch/analyzeRun$analysisType.csh $line $analysisType" >> $jsubfile                                                                        
	echo "OTHER_FILES:" >> $jsubfile                                                                                                                                         
	echo "/u/home/bclary/eg1analysis/SKIMprotocol/analysiscode_v2.2/analysiscode_v2.1/stage1PID" >> $jsubfile
    done < "$goodrunlist"
    MoveJSubs i
}

MoveJSubs (){

    echo ">> $1 Jobs have been created for submission to the farm"
    echo ">> Moving the jsub files to $jsub_dir"
    mv *.jsub $jsub_dir
}

SubmitJSubs (){

    cd $jsub_dir
    if [ $jsubmit = false ]
    then
	testfile=$(ls | head -1)
	echo ">> Testing submission of one job to farm for $analysisType"
	jsub $jsub_dir$testfile
    elif [ $jsubmit = true ]
    then
	echo ">> Submitting all jobs to farm"
	for f in "$jsub_dir"*.jsub
	do
	    jsub $f
	done
    fi
    echo ">> Finished submitting jobs to farm"
}

UserPrompt
if Confirm
then
    CreateJSubs analysis
    SubmitJSubs jsubmit
fi



