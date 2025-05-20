set term png size 600,600
set ylabel "f(x) and s(x)"
set xlabel "x"
set out "./plots/fun5.png"

plot \
    "./data/5fun.dat" u 1:2 with lines  linecolor rgb "black" title "y(x)", \
    "./data/5fun.dat" u 1:3 with lines  linecolor rgb "red" title "s(x)", \

set out

set term png size 600,600
set ylabel "Interpolation error f(x) - s(x)"
set xlabel "x"
set out "./plots/err5.png"

plot \
    "./data/5fun.dat" u 1:4 with lines  linecolor rgb "black" title "e(x)"

set out

set term png size 600,600
set ylabel "Second derivative at nodes"
set xlabel "x"
set out "./plots/der5.png"

plot \
    "./data/5der.dat" u 1:3 with points pointtype 7 linecolor rgb "black" title "y(x)", \
    "./data/5der.dat" u 1:2 with points pointtype 7 linecolor rgb "red" title "s(x)", \

set out



set term png size 600,600
set ylabel "f(x) and s(x)"
set xlabel "x"
set out "./plots/fun10.png"

plot \
    "./data/10fun.dat" u 1:2 with lines  linecolor rgb "black" title "y(x)", \
    "./data/10fun.dat" u 1:3 with lines  linecolor rgb "red" title "s(x)", \

set out

set term png size 600,600
set ylabel "Interpolation error f(x) - s(x)"
set xlabel "x"
set out "./plots/err10.png"

plot \
    "./data/10fun.dat" u 1:4 with lines  linecolor rgb "black" title "e(x)"

set out

set term png size 600,600
set ylabel "Second derivative at nodes"
set xlabel "x"
set out "./plots/der10.png"

plot \
    "./data/10der.dat" u 1:3 with points pointtype 7 linecolor rgb "black" title "y(x)", \
    "./data/10der.dat" u 1:2 with points pointtype 7 linecolor rgb "red" title "s(x)", \

set out



set term png size 600,600
set ylabel "f(x) and s(x)"
set xlabel "x"
set out "./plots/fun50.png"

plot \
    "./data/50fun.dat" u 1:2 with lines  linecolor rgb "black" title "y(x)", \
    "./data/50fun.dat" u 1:3 with lines  linecolor rgb "red" title "s(x)", \

set out

set term png size 600,600
set ylabel "Interpolation error f(x) - s(x)"
set xlabel "x"
set out "./plots/err50.png"

plot \
    "./data/50fun.dat" u 1:4 with lines  linecolor rgb "black" title "e(x)"

set out

set term png size 600,600
set ylabel "Second derivative at nodes"
set xlabel "x"
set out "./plots/der50.png"

plot \
    "./data/50der.dat" u 1:3 with points pointtype 7 linecolor rgb "black" title "y(x)", \
    "./data/50der.dat" u 1:2 with points pointtype 7 linecolor rgb "red" title "s(x)", \

set out