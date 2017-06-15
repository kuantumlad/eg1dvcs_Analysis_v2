#!/bin/bash
#######################################
##
##
##
## hmerge 
## Brandon Clary
##
## Purpose: Merge the root files from each run together
## bc had wont.
##
#########################################
#set environment for the code
#in particular source the binary to execute on the farm
#setenv PATH /u/home/bclary/eg1analysis/SKIMprotocol/analysiscode_v2.1:$PATH  
#setenv JLAB_VERSION 2.0
#setenv JLAB_ROOT /site/12gev_phys
#source $JLAB_ROOT/$JLAB_VERSION/ce/jlab.csh

#set input_directory = '/lustre/expphy/work/hallb/claseg1dvcs/pass1/v3/root/'
#set output_directory  = '/lustre/expphy/volatile/halla/sbs/bclary/eg1analysis/eg1dvcs_output/pid_output/'
#set file_prefix = 'root22_'
#set file_extension = '*.root'
#set runNumber = $1
#set analysisTask = $2                                                                                                                                                                         
#set files_to_search = "$input_directory$file_prefix$runNumber$file_extension"

#set pid_output_directory = '/lustre/expphy/volatile/halla/sbs/bclary/eg1analysis/eg1dvcs_output/pid_output/'
#set dvcs_output_directory = '/lustre/expphy/volatile/halla/sbs/bclary/eg1analysis/eg1dvcs_output/dvcs_output/'
#set pid_prefix = 'PIDroot22_'
#set dvcs_files_to_search = "$pid_output_directory$pid_prefix$runNumber$file_extension"
#set h_pidoutput = '/lustre/expphy/volatile/halla/sbs/bclary/eg1analysis/eg1dvcs_output/h_pid_output/'
#executable program that will create PIDroot22 files 
HISTOUT="/lustre/expphy/volatile/halla/sbs/bclary/eg1analysis/eg1dvcs_output/h_pid_output/"
PREFIX="PIDroot22_"
EXT=".root"
OUTPREFIX="h_pid"

DVCSOUT="/lustre/expphy/volatile/halla/sbs/bclary/eg1analysis/eg1dvcs_output/dvcs_output/h_dvcscuts/"
DVCSPREFIX="h_dvcs_"

echo "changing to directory to merge histogram files "
#cd "/lustre/expphy/volatile/halla/sbs/bclary/eg1analysis/eg1dvcs_output/pid_output/testrun" #$output_directory
cd "/lustre/expphy/volatile/halla/sbs/bclary/eg1analysis/eg1dvcs_output/dvcs_output"
pwd

#ls * | awk -F'[_]' '{print $2}' | sort -u |
ls * | awk -F'[_]' '{print $3}' | cut -f 1 -d '.' | sort -u |

#find . -type f -newermt 2017-03-19 ! -newermt 2017-03-22 -print |
#'ls -l PID*.root | grep "Mar" | awk '{print $9}'

while read RunNum
do

#if [ ! -f "$1" ]
#then
#    if [ $i -gt 0 ]
#    then 
    #pwd
    #for f in "$HISTOUT"*.root; do
    #echo $f	
    echo "run Number - " $RunNum
    if ((RunNum <= 59161 || RunNum < 59221))
    then
	echo "$RunNum in Group A Run"
	hadd -k -T -a h_eg1_groupA.root $DVCSPREFIX$RunNum$EXT
    elif ((RunNum <= 59221 || RunNum < 60223))
    then
	echo "$RunNum in Goup B Run"
	hadd -k -T -a h_eg1_groupB.root $DVCSPREFIX$RunNum$EXT
    else
	echo "Group C"
    fi

    #echo "merging files from run $RunNum"
    #HFILE=$PREFIX$RunNum$EXT
    #echo "output file is $HFILE"
    #echo "$PREFIX""$RunNum""_"*"$EXT"
    #hadd -a -f -k $HFILE $PREFIX$RunNum"_"*$EXT
#    fi
    #echo " Moving $HFILE to $HOUT"
    #mv $HFILE $HISTOUT
    #done	
      #echo "$file"
#fi


done
echo " Complete"

#echo *.root



#echo "$dvcs_files_to_search"
#foreach file ($dvcs_files_to_search)
    #if (! -e $file:t)
    #then
    #echo "File $file does not exist"
    #continue
    #endif
    #hadd -T -a h_testme.root 
   # echo "making h_PID$runNumber.root now"
   # set hout = 'h_pid'
   # set newfile = "$h_pidoutput$hout$runNumber.root"
#    hadd -k -T "h_PID$runNumber.root" $dvcs_files_to_search #files_to_search 
    #stage1PID $pid_output_directory $file:t $analysisTask
    #echo "$pid_output_directory $file:t $analysisTask"
    #set outputfile = "*.root"
    #if ( -e $outputfile )
 #   then
     #mv PID*.root $pid_output_directory
 #   else
  #  continue
   # endif

    #mv h_*.root $dvcs_output_directory

    #mv $newfile $h_pidoutput
#end


