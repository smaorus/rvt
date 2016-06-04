mkdir -p proto; cp -pf "try_side0.c" "try1_side1.c" proto 
"/cygdrive/c/NewRVT/debug/rv.exe"   "try_side0.c" "try1_side1.c" >& out 
echo -n $status > .status
