mkdir -p proto; cp -pf "alias.c" "alias1.c" proto 
"/cygdrive/c/NewRVT/Debug/rvt"  -mt "alias.c" "alias1.c" >& out 
echo -n $status > .status
