mkdir -p proto; cp -pf "collatz.c" "collatz1.c" proto 
"/cygdrive/c/NewRVT/debug/rv.exe"  -nooutline_funcs "collatz.c" "collatz1.c" >& out 
echo -n $status > .status
