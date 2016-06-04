set genstatus = 0 
set destdir = "`pwd`"/proto 
set cmpfiles = "`pwd`"/.cmpfiles 
rm -rf "$cmpfiles" >& /dev/zero 
foreach f (rv_pe.fuf UninitVar-Loop_f_for1_side0.gv UninitVar-Loop_f_for1_side1.gv) 
  echo $f >> "$cmpfiles" 
  if (-f $f) then 
    mv -f $f "$destdir/" >>& .status 
  else 
    cp -f "../../rvtest/tests/c99test_pe/"/$f "$destdir/" >>& .status 
  endif 
  if ($status != 0) set genstatus = $status 
end
rm -rf rv_pe.fuf UninitVar-Loop_f_for1_side0.gv UninitVar-Loop_f_for1_side1.gv >& /dev/zero 
exit($genstatus)
