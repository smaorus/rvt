set genstatus = 0 
set destdir = "`pwd`"/proto 
set cmpfiles = "`pwd`"/.cmpfiles 
rm -rf "$cmpfiles" >& /dev/zero 
foreach f (*.gv) 
  echo $f >> "$cmpfiles" 
  if (-f $f) then 
    mv -f $f "$destdir/" >>& .status 
  else 
    cp -f "../../rvtest/tests/mt1/"/$f "$destdir/" >>& .status 
  endif 
  if ($status != 0) set genstatus = $status 
end
rm -rf *.gv >& /dev/zero 
exit($genstatus)
