set term png size 1200,600
set ylabel "y"
set xlabel "x"
set out "./plots/1024noised.png"

plot \
    "./data/N1024f+noised.dat" u 1:3 with lines linecolor rgb "black" title "noised data"

set out

set term png size 1200,600
set ylabel "y"
set xlabel "x"
set out "./plots/1024real.png"

plot \
    "./data/N1024re_im.dat" u 1:2 with lines linecolor rgb "blue" title "real"

set out

set term png size 1200,600
set ylabel "y"
set xlabel "x"
set out "./plots/1024imaginary.png"

plot \
    "./data/N1024re_im.dat" u 1:3 with lines linecolor rgb "red" title "imaginary"

set out

set term png size 1200,600
set ylabel "y"
set xlabel "x"
set out "./plots/1024denoised.png"

plot \
    "./data/N1024denoised.dat" u 1:2 with points pointtype 7 linecolor rgb "red" title "denoised", \
    "./data/N1024f+noised.dat" u 1:2 with lines linecolor rgb "black" title "pure"

set out








set term png size 1200,600
set ylabel "y"
set xlabel "x"
set out "./plots/4096noised.png"

plot \
    "./data/N4096f+noised.dat" u 1:3 with lines linecolor rgb "black" title "noised data"

set out

set term png size 1200,600
set ylabel "y"
set xlabel "x"
set out "./plots/4096real.png"

plot \
    "./data/N4096re_im.dat" u 1:2 with lines linecolor rgb "blue" title "real"

set out

set term png size 1200,600
set ylabel "y"
set xlabel "x"
set out "./plots/4096imaginary.png"

plot \
    "./data/N4096re_im.dat" u 1:3 with lines linecolor rgb "red" title "imaginary"

set out

set term png size 1200,600
set ylabel "y"
set xlabel "x"
set out "./plots/4096denoised.png"

plot \
    "./data/N4096denoised.dat" u 1:2 with points pointtype 7 linecolor rgb "red" title "denoised", \
    "./data/N4096f+noised.dat" u 1:2 with lines linecolor rgb "black" title "pure"

set out