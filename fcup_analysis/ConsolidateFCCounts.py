###################################################
##                                               
## Brandon Clary
## 5/23/2017
## Purpose: To consildate the FC counts for 
## postive and negative helicity states into one
## managable file. This code only grabs the files
## that are on the good run list.
## 
##
###################################################
#from __future__ import print_function
import glob
import os

fc_rationom_filelist = glob.glob('/lustre/expphy/work/hallb/claseg1dvcs/pass1/v3/helicity/fcrationom/fcrationom_*.txt')
good_abrun_list = open('/u/home/bclary/eg1analysis/SKIMprotocol/analysiscode_v2.2/fcup_analysis/rates_good_ab.list','r')
fc_rationom_list = glob.glob('/u/home/bclary/eg1analysis/SKIMprotocol/analysiscode_v2.2/fcup_analysis/FCFiles.txt')
good_fcrationom_list = open('/u/home/bclary/eg1analysis/SKIMprotocol/analysiscode_v2.2/fcup_analysis/FCGoodFile.txt','r')

#Create the FCFiles list
#for filename in files:
#    print os.path.basename(filename)


#Create the good FC files list
#using Angella's run list
#for line in good_abrun_list:    
 #   run = line.split(' ')[0]
 #   #No space or argument in split removes newlines and tabs
 #   subrun = line.split()[1]
 #   ab = 'a'
    
#   if( len(subrun) >= 3 ):
#       ab = 'b'
#       subrun = int(subrun) - 100
        #str(subrun)
#       if( subrun < 10 ):
        #format the number to match file names
#           subrun = '%02d' % (subrun,)
            
    #This is a good fcration file that is from A.Biselli's list of good runs
#   good_fcratio = 'fcrationom_' + run + '_pass1.' + ab + str(subrun) + '.txt'
#   print good_fcratio 


#This section of code is responsible for reading
#from the FCGoodFile.txt and reading its associated FC values 
#into a new text document called 'Biselli_FCperFile.txt (made from here good list
#and any files that do not exists into 'Biselli_FCerror.txt'

biselli_fcOut = open("Biselli_GoodFCperFile.txt","w")
biselli_fcErrorOut = open("Biselli_FCerror.txt","w")
i = 0
for line in good_fcrationom_list:
    fcfile = line.split()[0]
    if '#' in fcfile:
        continue
    fcnom_path = '/lustre/expphy/work/hallb/claseg1dvcs/pass1/v3/helicity/fcrationom/' + fcfile
    
    fcnom_check = glob.glob(fcnom_path)
    run = fcfile.split('_')[1]
    subrun = fcfile.split('.')[1]
    rootfile = 'root22_' + run + '_' + subrun + '.root'
    if os.path.exists(fcnom_path):
        fcnom_temp = open(fcnom_path,'r')
        for fcline in fcnom_temp:
            fc0 = fcline.split()[0]
            fc1 = fcline.split()[1]
     
            print rootfile, " ", fc0, " ", fc1, " ", int(fc0)+int(fc1), " ", int(fc0)-int(fc1)
           #bs_out = rootfile + " " + fc0, " " + fc1 + " " + int(fc0)+int(fc1) + " " + int(fc0)-int(fc1)
           #print bs_out

    fcnom_temp.close()
    
           
    #i+=1
    #if i == 5:
    #    break 
        

    if not os.path.exists(fcnom_path):
        print fcfile
        #bserror_out = fcfile + "\n"
       # biselli_fcErrorOut.write(str(bserror_out))
