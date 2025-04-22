set term png size 600,600
set xrange [0 : 10]
set ylabel "found x"
set xlabel "iteration"
set out "x1_res.png"

plot \
    "bissection.dat" u 1:2 with linespoints pointtype 7 pointsize 1.0 linecolor rgb "black" title "bissection", \
    "secant.dat" u 1:2 with linespoints pointtype 7 pointsize 1.0 linecolor rgb "red" title "secant", \
    "newton.dat" u 1:2 with linespoints pointtype 7 pointsize 1.0 linecolor rgb "blue" title "newton"

set out

set term png size 600,600
set xrange [0 : 30]
set ylabel "found x"
set xlabel "iteration"
set out "x3_res.png"

plot \
    "secant3.dat" u 1:2 with linespoints pointtype 7 pointsize 1.0 linecolor rgb "red" title "secant", \
    "newton3.dat" u 1:2 with linespoints pointtype 7 pointsize 1.0 linecolor rgb "blue" title "newton"

set out

set term png size 600,600
set xrange [0 : 10]
set ylabel "found x"
set xlabel "iteration"
set out "x1_newton.png"

plot \
    "newton_modified.dat" u 1:2 with linespoints pointtype 7 pointsize 1.0 linecolor rgb "red" title "newton modified", \
    "newton.dat" u 1:2 with linespoints pointtype 7 pointsize 1.0 linecolor rgb "blue" title "newton"

set out

set term png size 600,600
set xrange [0 : 30]
set ylabel "found x"
set xlabel "iteration"
set out "x3_newton.png"

plot \
    "newton3_modified.dat" u 1:2 with linespoints pointtype 7 pointsize 1.0 linecolor rgb "red" title "newton modified", \
    "newton3.dat" u 1:2 with linespoints pointtype 7 pointsize 1.0 linecolor rgb "blue" title "newton"

set out

set term png size 600,600
set logscale y
set xrange [0 : 30]
set ylabel "delta"
set xlabel "iteration"
set out "x1_delta.png"

plot \
    "bissection.dat" u 1:3 with linespoints pointtype 7 pointsize 1.0 linecolor rgb "black" title "bissection", \
    "secant.dat" u 1:3 with linespoints pointtype 7 pointsize 1.0 linecolor rgb "red" title "secant", \
    "newton.dat" u 1:3 with linespoints pointtype 7 pointsize 1.0 linecolor rgb "blue" title "newton"

set out

set term png size 600,600
set xrange [0 : 200]
set logscale y
set ylabel "delta"
set xlabel "iteration"
set out "x3_delta.png"

plot \
    "secant3.dat" u 1:3 with linespoints pointtype 7 pointsize 1.0 linecolor rgb "red" title "secant", \
    "newton3.dat" u 1:3 with linespoints pointtype 7 pointsize 1.0 linecolor rgb "blue" title "newton"

set out

set term png size 600,600
set xrange [0 : 10]
set logscale y
set ylabel "delta"
set xlabel "iteration"
set out "x1_newton_delta.png"

plot \
    "newton_modified.dat" u 1:3 with linespoints pointtype 7 pointsize 1.0 linecolor rgb "red" title "newton modified", \
    "newton.dat" u 1:3 with linespoints pointtype 7 pointsize 1.0 linecolor rgb "blue" title "newton"

set out

set term png size 600,600
set xrange [0 : 30]
set logscale y
set ylabel "delta"
set xlabel "iteration"
set out "x3_newton_delta.png"

plot \
    "newton3_modified.dat" u 1:3 with linespoints pointtype 7 pointsize 1.0 linecolor rgb "red" title "newton modified", \
    "newton3.dat" u 1:3 with linespoints pointtype 7 pointsize 1.0 linecolor rgb "blue" title "newton"

set out
