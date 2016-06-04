mkdir -p proto; cp -pf "mccarthy.c" "mccarthy1.c" proto 
"/cygdrive/c/NewRVT/Debug/rvt"  -mt "mccarthy.c" "mccarthy1.c" >& out 
echo -n $status > .status
