mkdir -p proto; cp -pf "c99test.c" "c99test1.c" proto 
"/cygdrive/c/NewRVT/Debug/rvt"  -nooutline_funcs -c99 -mt "c99test.c" "c99test1.c" >& out 
echo -n $status > .status
