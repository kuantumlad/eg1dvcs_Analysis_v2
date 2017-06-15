#!/bin/bash

###################
##
## Main Analyzer
##
##################


Opener (){

    echo "---------------------- EG1-DVCS Analyzer -----------------------"
    echo " "
    echo "  A shell script to easily submit jobs and merge output file    "
    echo "                     By: Brandon Clary                          "
    echo "                        Version 1.0                             "
    echo " -------------------------------------------------------------- "

}

UserPrompt (){

    echo ">> Are you submitting jobs or merging files ?"
    echo ">> Please type 'submit' or 'merge' then press enter"

    read task
   
}

Opener
UserPrompt

if [ "$task" == "submit" ];
then
    echo ">> Program will now execute submission script. "
    ./analyzer.sh
elif [ "$task" == "merge" ];
then
    echo ">> Program will now execute merging script. "
    ./hmerge.sh
fi

