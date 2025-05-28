set term png size 600,600
set ylabel "y"
set xlabel "x"
set out "./plots/Fletcher_0.1.png"

plot \
    "./data/Fletcher_0.100000.dat" u 1:2 with points pointtype 7 linecolor rgb "black" title "experiment", \
    "./data/Fletcher_0.100000.dat" u 1:3 with lines linecolor rgb "red" title "p exact", \
    "./data/Fletcher_0.100000.dat" u 1:4 with lines linecolor rgb "blue" title "p fit", 

set out

set term png size 600,600
set ylabel "y"
set xlabel "x"
set out "./plots/Polak_0.1.png"

plot \
    "./data/Polak_0.100000.dat" u 1:2 with points pointtype 7 linecolor rgb "black" title "experiment", \
    "./data/Polak_0.100000.dat" u 1:3 with lines linecolor rgb "red" title "p exact", \
    "./data/Polak_0.100000.dat" u 1:4 with lines linecolor rgb "blue" title "p fit", 

set out

set term png size 600,600
set ylabel "y"
set xlabel "x"
set out "./plots/Fletcher_1.0.png"

plot \
    "./data/Fletcher_1.000000.dat" u 1:2 with points pointtype 7 linecolor rgb "black" title "experiment", \
    "./data/Fletcher_1.000000.dat" u 1:3 with lines linecolor rgb "red" title "p exact", \
    "./data/Fletcher_1.000000.dat" u 1:4 with lines linecolor rgb "blue" title "p fit", 

set out

set term png size 600,600
set ylabel "y"
set xlabel "x"
set out "./plots/Polak_1.0.png"

plot \
    "./data/Polak_1.000000.dat" u 1:2 with points pointtype 7 linecolor rgb "black" title "experiment", \
    "./data/Polak_1.000000.dat" u 1:3 with lines linecolor rgb "red" title "p exact", \
    "./data/Polak_1.000000.dat" u 1:4 with lines linecolor rgb "blue" title "p fit", 

set out

set term png size 600,600
set ylabel "y"
set xlabel "x"
set out "./plots/Fletcher_0.1_larA.png"

plot \
    "./data/Fletcher_0.100000_largerA.dat" u 1:2 with points pointtype 7 linecolor rgb "black" title "experiment", \
    "./data/Fletcher_0.100000_largerA.dat" u 1:3 with lines linecolor rgb "red" title "p exact", \
    "./data/Fletcher_0.100000_largerA.dat" u 1:4 with lines linecolor rgb "blue" title "p fit", 

set out

set term png size 600,600
set ylabel "y"
set xlabel "x"
set out "./plots/Polak_0.1_larA.png"

plot \
    "./data/Polak_0.100000_largerA.dat" u 1:2 with points pointtype 7 linecolor rgb "black" title "experiment", \
    "./data/Polak_0.100000_largerA.dat" u 1:3 with lines linecolor rgb "red" title "p exact", \
    "./data/Polak_0.100000_largerA.dat" u 1:4 with lines linecolor rgb "blue" title "p fit", 

set out