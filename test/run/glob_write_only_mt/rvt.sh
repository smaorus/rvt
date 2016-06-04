mkdir -p proto; cp -pf "rec_soundness.c" "rec_soundness1.c" proto 
"/cygdrive/c/NewRVT/Debug/rvt"  -mt "rec_soundness.c" "rec_soundness1.c" >& out 
echo -n $status > .status
