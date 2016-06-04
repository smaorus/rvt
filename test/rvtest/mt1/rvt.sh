mkdir -p proto; cp -pf "try_side0.c" "try1_side1.c" proto 
"/cygdrive/c/NewRVT/debug/rv.exe"  -debug 7777777 -fuf rv_pe.fuf -K 3 -mt -lb 0 "try_side0.c" "try1_side1.c" >& out 
echo -n $status > .status
