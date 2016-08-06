#!/bin/tcsh -f

exit 0
set tmpf = .tmp_$1
set resf = .res_$1
rm -f $tmpf

$0/../report.sh Removing typedef enum from $1

sed -e 's/\\/--@@--/g' $1 >! $resf 
foreach lin ("`cat $resf`")
    echo -n "$lin" '@-@-@' >> $tmpf
end

sed -e 's/typedef\s*\(@-@-@\)*\s*\(struct\)\s*\(@-@-@\)*\s*{\([^{]*\)}\s*\(@-@-@\)*\s*\([A-Za-z_][0-9A-Za-z_]*\)_t\s*\(@-@-@\)*\s*;/\1\2 \6 \3{\4}\5\7;\n #define \6@@@---@@@ \2 \6\n/g' $tmpf |\
 sed -e 's/typedef\s*\(@-@-@\)*\s*\(enum\)\s*\(@-@-@\)*\s*{\([^{]*\)}\s*\(@-@-@\)*\s*\([A-Za-z_][0-9A-Za-z_]*\)_t\s*\(@-@-@\)*\s*;/\1\2 \6 \3{\4}\5\7;\n #define \6@@@---@@@ \2 \6\n/g' |\
  sed -e 's/@@@---@@@/_t/g' | sed -e 's/@-@-@/\r\n/g' | sed -e 's/--@@--/\\/g' >! $resf
rm -f $tmpf
mv $resf $1
