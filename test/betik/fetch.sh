#!/bin/tcsh -f

set ver = $1
$0/../common/report.sh Deleting directories ver$ver c$ver if exist 
\rm -rf ver$ver c$ver
set code = "`grep -w $1 $0/../short_change_log | cut -f3 -d' '`" 
mkdir -p ver$1/source 
cd ver$1/source 
hg clone -r $code https://code.google.com/p/betik/
cd betik
cd ../..
cp -r source changed
cd changed/betik
../../../common/prepare.sh
cd ../../..
@ prevVer = $1 - 1
set cDir = c$1
mkdir $cDir
cp ver$1/changed/betik/a.c $cDir/a1.c
cp ver$prevVer/changed/betik/a.c $cDir
echo Created directory $cDir with a.c from version $prevVer and a1.c from $1 

# mkdir -p ver$1/source 
# cd ver$1/source 
# hg clone -r $2 https://code.google.com/p/betik/
# cd betik
# @ nextVer = $1 + 1
# rm -f *.h
# cp ../../../ver196/source/betik/*.h .
# diff common.h ../../../ver$nextVer/source/betik/common.h
# cd ../..
# cp -r source changed
# cd changed/betik
# ../../../common/prepare.sh
# cd ../../..
# mkdir c$nextVer
# cp ver$1/changed/betik/a.c c$nextVer
# cp ver$nextVer/changed/betik/a.c c$nextVer/a1.c
