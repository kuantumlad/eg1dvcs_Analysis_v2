#compile analysis code

echo "Compiling..."
echo " "
#g++ -c src/inelastic.cc src/Check.cc src/Kinematics.cc src/temp.C -pthread -std=c++11 -m64 -I/home/brandon/Documents/root_v5/root/include
g++ -c src/DiagnoseStage2.cc src/Cuts.cc src/CutManager.cc src/Eventh22.cc src/Loadh22.cc src/HistogramTool.cc src/DVCSHistogramTool.cc src/RunDB.cc src/SkimManager.cc src/PhysicsCuts.cc src/PhysicsEvent.cc src/PhysicsEventBuilder.cc src/PhysicsCutManager.cc src/Calculator.cc src/BuildtDVCS.cc src/BuildtPID.cc src/LoadDVCS.cc src/EventDVCS.cc src/AnalysisManager.cc src/EventPID.cc src/LoadPID.cc src/LoadMC.cc src/EventMC.cc -pthread -std=c++11 -m64 -I/Users/bclary/Documents/root/root-6.06.04/include
mv *.o linker/

cd linker/
echo "Linking..."
echo " "
g++ DiagnoseStage2.o Cuts.o CutManager.o Eventh22.o Loadh22.o HistogramTool.o DVCSHistogramTool.o RunDB.o SkimManager.o PhysicsCuts.o PhysicsEvent.o PhysicsEventBuilder.o PhysicsCutManager.o Calculator.o BuildtDVCS.o BuildtPID.o LoadDVCS.o EventDVCS.o AnalysisManager.o EventPID.o LoadPID.o LoadMC.o EventMC.o -o analysis -L/Users/bclary/Documents/root/root-6.06.04/lib -lGui -lCore -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lTree -lGeom -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lThread -pthread -lm -ldl -rdynamic -lsqlite3
#g++ inelastic.o Check.o Kinematics.o temp.o -o analysis -L/home/brandon/Documents/root_v5/root/lib -lGui -lCore -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lTree -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lThread -pthread -lm -ldl -rdynamic

mv ./analysis ../
echo "Executing..."
echo " "
cd ../
echo "$1"
./analysis #$1

#mv PIDroot22* ../../../run\ data/DVCSresults/


if [ -e compile_analysis.sh~ ]
then 
    rm compile_analysis.sh~
fi
