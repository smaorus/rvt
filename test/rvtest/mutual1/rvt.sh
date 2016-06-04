mkdir -p proto; cp -pf "mutual.c" "mutual1.c" proto 
"/cygdrive/c/NewRVT/debug/rv.exe"  -unitrv -fuf rv_pe.fuf -K 10 -mt "mutual.c" "mutual1.c" >& out 
echo -n $status > .status
