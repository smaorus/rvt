mkdir -p proto; cp -pf "gcd_refined.c" "gcd_refined1.c" proto 
"/cygdrive/c/NewRVT/debug/rv.exe"  -refined -nooutline_funcs "gcd_refined.c" "gcd_refined1.c" >& out 
echo -n $status > .status
