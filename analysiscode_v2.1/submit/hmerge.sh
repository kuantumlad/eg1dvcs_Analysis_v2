#!/bin/bash

HISTOUT="/lustre/expphy/volatile/halla/sbs/bclary/eg1analysis/eg1dvcs_output/h_pid_output/PIDclary_runs/"
PREFIX="PIDroot22_"
OUTPREFIX="h_pid"
DVCSOUT="/lustre/expphy/volatile/halla/sbs/bclary/eg1analysis/eg1dvcs_output/dvcs_output/h_dvcscuts/"
DVCSPREFIX="h_dvcs_"
EXT=".root"


MergePrompt (){

    echo ">> This script will aid you in merging root files. "
    echo ">> Merge PID, DVCS, OR MC files ?"
    echo ">> Please enter PID, DVCS, or MC."
    read analysisType 

}


PIDMerge (){

    cd "/lustre/expphy/volatile/halla/sbs/bclary/eg1analysis/eg1dvcs_output/pid_output/clary_runs"
    echo ">>Currently in " 
    pwd

    ls * | awk -F'[_]' '{print $2}' | sort -u |

    while read RunNum
    do 
	echo "-- Merging files from run $RunNum"
	HFILE=$PREFIX$RunNum$EXT
	hadd -a -f -k $HFILE $PREFIX$RunNum"_"*$EXT

	echo "-- Moving $HFILE to $HOUT"
	mv $HFILE $HISTOUT
    done

    echo ">> PID files succesfully merged."
    echo ">> Complete"
    exit
}


DVCSMerge (){
    
    cd "/lustre/expphy/volatile/halla/sbs/bclary/eg1analysis/eg1dvcs_output/dvcs_output/DVCSclary_runs"
    echo ">>Currently in " 
    pwd

    ls * | awk -F'[_]' '{print $3}' | cut -f 1 -d '.' | sort -u |

    while read RunNum
    do 
	echo "-- Merging files from run $RunNum"
	if ((RunNum <= 59161 || RunNum < 59221))
	then
	    echo "$RunNum in Group A Run"
	    hadd -k -a -f h_eg1_groupA.root $DVCSPREFIX$RunNum$EXT
	elif ((RunNum <= 59221 || RunNum < 60223))
	then
	    echo "$RunNum in Goup B Run"
	    hadd -k -a -f h_eg1_groupB.root $DVCSPREFIX$RunNum$EXT
	else
	    echo "Group C"
	fi
    done

    echo ">> DVCS files succesfully merged."
    echo ">> Now merging Group A and B together" 
    hadd -k -a -f h_eg1_groupAB.root h_eg1_groupA.root h_eg1_groupB.root

    echo ">> Complete"
    exit
}

MergePrompt
if [ "$analysisType" == "PID" ];
then
    PIDMerge
elif [ "$analysisType" == "DVCS" ];
then
    DVCSMerge
fi
