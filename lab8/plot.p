set term png size 600,600
set ylabel "test function and its interpolation"
set xlabel "x"
set out "./plots/equi5.png"

plot \
    "./data/equidistant5.dat" u 1:2 with lines  linecolor rgb "black" title "y(x)", \
    "./data/equidistant5.dat" u 1:3 with lines  linecolor rgb "red" title "W(x)", \
    "./data/equidistant5_nodes.dat" u 1:2 with points title "nodes"

set out

set term png size 600,600
set ylabel "test function and its interpolation"
set xlabel "x"
set out "./plots/equi10.png"

plot \
    "./data/equidistant10.dat" u 1:2 with lines  linecolor rgb "black" title "y(x)", \
    "./data/equidistant10.dat" u 1:3 with lines  linecolor rgb "red" title "W(x)", \
    "./data/equidistant10_nodes.dat" u 1:2 with points title "nodes"

set out

set term png size 600,600
set ylabel "test function and its interpolation"
set xlabel "x"
set out "./plots/equi20.png"

plot \
    "./data/equidistant20.dat" u 1:2 with lines  linecolor rgb "black" title "y(x)", \
    "./data/equidistant20.dat" u 1:3 with lines  linecolor rgb "red" title "W(x)", \
    "./data/equidistant20_nodes.dat" u 1:2 with points title "nodes"

set out

set term png size 600,600
set ylabel "test function and its interpolation"
set xlabel "x"
set out "./plots/cheb20.png"

plot \
    "./data/chebyshev20.dat" u 1:2 with lines  linecolor rgb "black" title "y(x)", \
    "./data/chebyshev20.dat" u 1:3 with lines  linecolor rgb "red" title "W(x)", \
    "./data/chebyshev20_nodes.dat" u 1:2 with points title "nodes"

set out

set term png size 600,600
set ylabel "error"
set xlabel "x"
set out "./plots/cheb20_err.png"

plot \
    "./data/chebyshev20.dat" u 1:4 with lines  linecolor rgb "black" title "err(x)", \
    "./data/chebyshev20_nodes.dat" u 1:2 with points title "nodes"

set out

set term png size 600,600
set ylabel "test function and its interpolation"
set xlabel "x"
set out "./plots/cheb30.png"

plot \
    "./data/chebyshev30.dat" u 1:2 with lines  linecolor rgb "black" title "y(x)", \
    "./data/chebyshev30.dat" u 1:3 with lines  linecolor rgb "red" title "W(x)", \
    "./data/chebyshev30_nodes.dat" u 1:2 with points title "nodes"

set out

set term png size 600,600
set ylabel "error"
set xlabel "x"
set out "./plots/cheb30_err.png"

plot \
    "./data/chebyshev30.dat" u 1:4 with lines  linecolor rgb "black" title "err(x)", \
    "./data/chebyshev30_nodes.dat" u 1:2 with points title "nodes"

set out