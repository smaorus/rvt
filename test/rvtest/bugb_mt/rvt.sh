mkdir -p proto; cp -pf "bugb.c" "bugb1.c" proto 
"/cygdrive/c/NewRVT/debug/rv.exe"  -unitrv -dk 3 -mt "bugb.c" "bugb1.c" >& out 
echo -n $status > .status
