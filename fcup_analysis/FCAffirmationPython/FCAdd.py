from __future__ import with_statement
import glob
import os
import re

fcrationom_path = '/lustre/expphy/work/hallb/claseg1dvcs/pass1/v3/helicity/fcrationom/'
fcratio_path = '/lustre/expphy/work/hallb/claseg1dvcs/pass1/v3/helicity/fcratio/'

#runlist contains the set of runs spanning the experiment
runlist = open('/u/home/bclary/eg1analysis/SKIMprotocol/analysiscode_v2.2/analysiscode_v2.1/submit/runlist.txt','r')

#Add the fcrationom values for FC0 and FC1 over each run 


#commenting out to test run 58800 against angelas
#for run in runlist:
    #print run.split()
    #fc_files_to_add = "/volatile/halla/sbs/bclary/eg1analysis/eg1dvcs_output/pid_output/clary_runs/PIDroot22_58800" + run.strip() + "*.root"
fc_files_to_add = "/volatile/halla/sbs/bclary/eg1analysis/eg1dvcs_output/pid_output/clary_runs/PIDroot22_58989" + "*.root"
print fc_files_to_add
fc_file = glob.glob(fc_files_to_add)
fc_file.sort()
fc_0 = 0
fc_1 = 0
for fc in fc_file:
    print "fc is ",fc
    fc_file_to_open = fcrationom_path + "fcrationom_" + fc.split('/')[-1].split('_')[1] + "_pass1." + fc.split('/')[-1].split('_')[2].split('.')[0] + ".txt" 
    fc_file_to_open_check = fcratio_path + "fcratio_" + fc.split('/')[-1].split('_')[1] + "_pass1." + fc.split('/')[-1].split('_')[2].split('.')[0] + ".txt" 
    with open(fc_file_to_open,'r') as f:
        fc0_fc1 = re.split(r'\s{1,}',f.readline())
    print ' fcrationom values', fc0_fc1[1], ' ', fc0_fc1[2]
    #if os.path.isfile(fc_file_to_open_check):
    print 'total before ', fc_0 + fc_1
    fc_0 = fc_0 + int(fc0_fc1[1])
    fc_1 = fc_1 + int(fc0_fc1[2])
    print 'total after ', fc_0 + fc_1
    #else:
#    print 'No ', fc_file_to_open_check, ' exists'

#    print run.strip(), fc_0, fc_1
