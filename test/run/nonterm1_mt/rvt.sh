mkdir -p proto; cp -pf "nonterm.c" "nonterm1.c" proto 
"/cygdrive/c/NewRVT/Debug/rvt"  -mt "nonterm.c" "nonterm1.c" >& out 
echo -n $status > .status
