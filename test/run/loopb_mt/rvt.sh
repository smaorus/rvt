mkdir -p proto; cp -pf "loopb.c" "loopb1.c" proto 
"/cygdrive/c/NewRVT/Debug/rvt"  -dk 2 -mt "loopb.c" "loopb1.c" >& out 
echo -n $status > .status
