#!/bin/bash


i="0"
# first input_directory variable is for creating the PIDroot22* files, second for event selection
#input_directory='/lustre/expphy/work/hallb/claseg1dvcs/pass1/v3/root/'
input_directory='/lustre/expphy/volatile/halla/sbs/bclary/eg1analysis/eg1dvcs_output/pid_output/smallrun/'
pid_output_directory='/lustre/expphy/volatile/halla/sbs/bclary/eg1analysis/eg1dvcs_output/pid_output/smallrun/'

file_prefix='root22_'
file_extension='.root'
temp='_a0'
temp2='_a'
runNumber=$1
analysisTask=$2                                     

files_to_search="$input_directory$file_prefix$runNumber$file_extension"

while [ $i -lt 25 ]
do

    if [ $i -lt 10 ]
    then
	file="$file_prefix$runNumber$temp$i$file_extension"
	echo "$input_directory $file $analysisTask"
    elif [ $i -ge 10 ]
    then
	file="$file_prefix$runNumber$temp2$i$file_extension"
	echo "$input_directory $file $analysisTask"
    fi
    
    ./stage1PID $input_directory $file $analysisTask
    mv PIDroot22*.root $pid_output_directory 
    i=$[$i+1]
    echo " Done with  $i file "
    
done