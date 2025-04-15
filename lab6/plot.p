set term png size 600,600
set ylabel "y(x)"
set xlabel "x"
set out "m8n6/polynomial.png"

plot \
    "m8n6/functions.dat" u 1:3 with lines linecolor rgb "black" title "x * cos(x)", \
    "m8n6/functions.dat" u 1:2 with points pointtype 7 pointsize 1.0 linecolor rgb "red" title "obtained polynomial", \
    "m8n6/data.dat" u 1:2 with points pointtype 7 pointsize 1.5 linecolor rgb "black" title "initial points"

set out

set term png size 600,600
set ylabel "y(x)"
set xlabel "x"
set out "m30n10/polynomial.png"

plot \
    "m30n10/functions.dat" u 1:3 with lines linecolor rgb "black" title "x * cos(x)", \
    "m30n10/functions.dat" u 1:2 with points pointtype 7 pointsize 1.0 linecolor rgb "red" title "obtained polynomial", \
    "m30n10/data.dat" u 1:2 with points pointtype 7 pointsize 1.5 linecolor rgb "black" title "initial points"

set out

set term png size 600,600
set ylabel "y(x)"
set xlabel "x"
set out "m30n20/polynomial.png"

plot \
    "m30n20/functions.dat" u 1:3 with lines linecolor rgb "black" title "x * cos(x)", \
    "m30n20/functions.dat" u 1:2 with points pointtype 7 pointsize 1.0 linecolor rgb "red" title "obtained polynomial", \
    "m30n20/data.dat" u 1:2 with points pointtype 7 pointsize 1.5 linecolor rgb "black" title "initial points"

set out
