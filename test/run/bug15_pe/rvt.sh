mkdir -p proto; cp -pf "bug15.c" "bug15tag.c" proto 
"/cygdrive/c/NewRVT/Debug/rvt"  -nooutline_funcs "bug15.c" "bug15tag.c" >& out 
echo -n $status > .status
