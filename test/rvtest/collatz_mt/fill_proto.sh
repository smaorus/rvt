set genstatus = 0 
set destdir = "`pwd`"/proto 
set cmpfiles = "`pwd`"/.cmpfiles 
rm -rf "$cmpfiles" >& /dev/zero 
foreach f (rv_mt.fuf rv_out.gv) 
  echo $f >> "$cmpfiles" 
  if (-f $f) then 
    mv -f $f "$destdir/" >>& .status 
  else 
    cp -f ".././tests/collatz_mt/"/$f "$destdir/" >>& .status 
  endif 
  if ($status != 0) set genstatus = $status 
end
rm -rf rv_mt.fuf rv_out.gv >& /dev/zero 
exit($genstatus)
