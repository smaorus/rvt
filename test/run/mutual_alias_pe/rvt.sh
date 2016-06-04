mkdir -p proto; cp -pf "mutual_alias.c" "mutual_alias1.c" proto 
"/cygdrive/c/NewRVT/Debug/rvt"  -completeness 1 "mutual_alias.c" "mutual_alias1.c" >& out 
echo -n $status > .status
