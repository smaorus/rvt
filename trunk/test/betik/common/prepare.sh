#!/bin/tcsh -f

foreach f (`grep -l 'typedef' *.h *.c`)
    $0/../convert.sh $f
end

#foreach f (*.h *.c)
#    $0/../report.sh 'Expanding enum type names in file ' $f 
#    sed -e 's/statement_type_t/enum statement_type/g' $f | sed -e 's/value_type_t/enum value_type/g' | sed -e 's/token_type_t/enum token_type/g' | sed -e 's/object_type_t/enum object_type/g' | sed -e 's/seatest_action_t/enum seatest_action/g' | sed -e 's/static//g' >! .tmp_$f
#    mv .tmp_$f $f
#end

foreach f (`grep -l 'conio' *.h *.c`)
    $0/../report.sh 'Replacing getch() with getchar() in ' $f 
    grep -v '#include\s*<conio' $f | sed 's/getch\([^0-9A-Za-z_]\)/getchar\1/g' > .tmp_$f  
    mv .tmp_$f $f
end

# $0/../report.sh Fetching enums.h
# cp $0/../enums.h .

$0/../report.sh Concatenating all into a.c
cat common.h token.h parser.h interpreter.h runtime.h seatest.h *.c | grep -v '#include\s*"' > tmp_$$
mv tmp_$$ a.c
