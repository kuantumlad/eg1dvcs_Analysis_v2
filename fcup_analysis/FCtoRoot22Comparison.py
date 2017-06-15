###################################
##
##   Brandon Clary
##   5-23-2017  
##   
##   This python code gets a root22 file and 
##   makes sure there is a corresponding 
##   fcrationom file. It then adds the file to 
##   a good run list for later use in the analysis.
##
##
###################################

import glob
import os

#Change this root22_files path to another path with run files to compare
#root22_files = glob.glob('/volatile/halla/sbs/bclary/eg1analysis/eg1dvcs_output/pid_output/clary_runs/PIDroot22*.root')
root22_files = glob.glob('/work/clas/claseg1dvcs/pass1/v3/root/root22*.root')
fcrationom_path = '/lustre/expphy/work/hallb/claseg1dvcs/pass1/v3/helicity/fcrationom/'

goodfile_counter = 0
badfile_counter = 0
for root22 in root22_files:

    root22 = root22.split('/')[-1]
    #print 'Root file is ', root22.split('_')[1] + '_pass1.' + root22.split('_')[2].split('.')[0]
    fcratio_pair = 'fcrationom_' + root22.split('_')[1] + '_pass1.' + root22.split('_')[2].split('.')[0] + '.txt'
    fcrationom_fullpath = fcrationom_path + fcratio_pair

    fcrationom_check = os.path.exists(fcrationom_fullpath)
    #print 'Corresponding fcrationom file is at ',fcrationom_fullpath

    if fcrationom_check:
        goodfile_counter+=1
        #print root22.split('/')[-1]
        #Open up fcrationom file for this root22 file. 
        fcnom_temp = open(fcrationom_fullpath,'r')
        for fcline in fcnom_temp:
            fc0 = fcline.split()[0]
            fc1 = fcline.split()[1]
            #print root22, " ", fc0, " ", fc1, " ", int(fc0)+int(fc1), " ", int(fc0)-int(fc1)
            print root22.split('/')[-1], " ", fc0, " ", fc1

    else:
        #print " ERROR ", root22.split('/')[-1], " not found"
        badfile_counter+=1

#print '>> Number of root22 files with a corresponding fcrationom file', goodfile_counter
#print '>> Number of fcratio files that are missing: ', badfile_counter

