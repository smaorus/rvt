mkdir -p proto; cp -pf "struct.c" "struct1.c" proto 
"/cygdrive/c/NewRVT/Debug/rvt"  -nooutline_funcs "struct.c" "struct1.c" >& out 
echo -n $status > .status
