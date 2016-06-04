mkdir -p proto; cp -pf "gcd_refined.c" "gcd_refined1.c" proto 
"/cygdrive/c/NewRVT/Debug/rvt"  -mt -nooutline_funcs -refined "gcd_refined.c" "gcd_refined1.c" >& out 
echo -n $status > .status
