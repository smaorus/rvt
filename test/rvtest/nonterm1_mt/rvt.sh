mkdir -p proto; cp -pf "nonterm.c" "nonterm1.c" proto 
"/cygdrive/c/NewRVT/debug/rv.exe"  -unitrv -mt "nonterm.c" "nonterm1.c" >& out 
echo -n $status > .status
