mkdir -p proto; cp -pf "mutual_alias.c" "mutual_alias1.c" proto 
"/cygdrive/c/NewRVT/Debug/rvt"  -continue_on_fail -dk 2 -fuf rv_pe.fuf -mt "mutual_alias.c" "mutual_alias1.c" >& out 
echo -n $status > .status
