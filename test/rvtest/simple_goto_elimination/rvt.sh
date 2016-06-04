mkdir -p proto; cp -pf "simple_goto_elimination.c" "simple_goto_elimination1.c" proto 
"/cygdrive/c/NewRVT/debug/rv.exe"   "simple_goto_elimination.c" "simple_goto_elimination1.c" >& out 
echo -n $status > .status
