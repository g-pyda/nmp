set term png size 600,600
set ylabel "f(x) and R_N_,_M(x)"
set xlabel "x"
set out "./plots/n2m2.png"

plot \
    "./data/n2m2.dat" u 1:2 with lines linecolor rgb "black" title "y(x)", \
    "./data/n2m2.dat" u 1:3 with lines linecolor rgb "red" title "R_N_,_M(x)", \

set out

set term png size 600,600
set ylabel "f(x) and R_N_,_M(x)"
set xlabel "x"
set out "./plots/n4m4.png"

plot \
    "./data/n4m4.dat" u 1:2 with lines linecolor rgb "black" title "y(x)", \
    "./data/n4m4.dat" u 1:3 with lines linecolor rgb "red" title "R_N_,_M(x)", \

set out

set term png size 600,600
set ylabel "f(x) and R_N_,_M(x)"
set xlabel "x"
set out "./plots/n6m6.png"

plot \
    "./data/n6m6.dat" u 1:2 with lines linecolor rgb "black" title "y(x)", \
    "./data/n6m6.dat" u 1:3 with lines linecolor rgb "red" title "R_N_,_M(x)", \

set out

set term png size 600,600
set ylabel "f(x) and R_N_,_M(x)"
set xlabel "x"
set out "./plots/n2m4.png"

plot \
    "./data/n2m4.dat" u 1:2 with lines linecolor rgb "black" title "y(x)", \
    "./data/n2m4.dat" u 1:3 with lines linecolor rgb "red" title "R_N_,_M(x)", \

set out

set term png size 600,600
set ylabel "f(x) and R_N_,_M(x)"
set xlabel "x"
set out "./plots/n2m6.png"

plot \
    "./data/n2m6.dat" u 1:2 with lines linecolor rgb "black" title "y(x)", \
    "./data/n2m6.dat" u 1:3 with lines linecolor rgb "red" title "R_N_,_M(x)", \

set out

set term png size 600,600
set ylabel "f(x) and R_N_,_M(x)"
set xlabel "x"
set out "./plots/n2m8.png"

plot \
    "./data/n2m8.dat" u 1:2 with lines linecolor rgb "black" title "y(x)", \
    "./data/n2m8.dat" u 1:3 with lines linecolor rgb "red" title "R_N_,_M(x)", \

set out
