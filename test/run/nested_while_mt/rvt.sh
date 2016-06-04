mkdir -p proto; cp -pf "nested_while.c" "nested_while1.c" proto 
"/cygdrive/c/NewRVT/Debug/rvt"  -nofuf -mt "nested_while.c" "nested_while1.c" >& out 
echo -n $status > .status
