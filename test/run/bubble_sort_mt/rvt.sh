mkdir -p proto; cp -pf "bubble_sort.c" "bubble_sort1.c" proto 
"/cygdrive/c/NewRVT/Debug/rvt"  -continue_on_fail -mt "bubble_sort.c" "bubble_sort1.c" >& out 
echo -n $status > .status
