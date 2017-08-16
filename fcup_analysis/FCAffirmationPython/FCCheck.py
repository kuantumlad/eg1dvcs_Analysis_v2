##########################
##
##
## Brandon Clary
## 6/6/2017
## This python script is meant to
## to check if the clary_FCgoodfiles.txt 
## was used in the DB during the analysis
## If it was then the files in the PIDclary 
## folder will match the list here.
##
##
##########################

import glob
import os

#Change this root22_files path to another path with run files to compare
root22_files = glob.glob('/volatile/halla/sbs/bclary/eg1analysis/eg1dvcs_output/pid_output/clary_runs/PIDroot22*.root')

clary_fcgoodfile = open("clary_FCGoodFiles.txt","r")

#create a list of the files in the .txt file

goodfile = 0

for line in clary_fcgoodfile:

    if line[0] == '#' : continue
    pid_file = 'PID' + line.split()[0]
    pid_file_fullpath = '/volatile/halla/sbs/bclary/eg1analysis/eg1dvcs_output/pid_output/clary_runs/' + pid_file

    if( os.path.isfile(pid_file_fullpath) ):
        goodfile+=1
    else:
        print pid_file, ' does not exist in the ~/clary_runs/ folder


