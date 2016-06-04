mkdir -p proto; cp -pf "collatz.c" "collatz1.c" proto 
"/cygdrive/c/NewRVT/Debug/rvt"  -nooutline_funcs -mt -nofuf "collatz.c" "collatz1.c" >& out 
echo -n $status > .status
