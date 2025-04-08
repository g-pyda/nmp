set term png size 600,600
set logscale x
set xlabel "Iteration (in logarithmic scale)"
set ylabel "Norm (v) for different omega values"  #--------- "Updated title to reflect multiple plots"
set out "norms_v.png"

plot "omega150/norms.dat" u 1:2 w l title "Omega 1.5" lc rgb "red", \
     "omega190/norms.dat" u 1:2 w l title "Omega 1.9" lc rgb "blue", \
     "omega199/norms.dat" u 1:2 w l title "Omega 1.99" lc rgb "green"

set out

set term png size 600,600
set logscale x
set xlabel "Iteration (in logarithmic scale)"
set ylabel "Norm (v) for different omega values"  #--------- "Updated title to reflect multiple plots"
set out "norms_v_add.png"

plot "rand/norms.dat" u 1:2 w l title "x = 0" lc rgb "red", \
     "omega199/norms.dat" u 1:3 w l title "x = 1" lc rgb "blue", \
     "zeroes/norms.dat" u 1:2 w l title "x = rand()" lc rgb "green"

set out

set term png size 600,600
set logscale x
set logscale y
set xlabel "Iteration (in logarithmic scale)"
set ylabel "Norm (r) for different omega values"  #--------- "Updated title to reflect multiple plots"
set out "norms_r.png"

plot "omega150/norms.dat" u 1:3 w l title "Omega 1.5" lc rgb "red", \
     "omega190/norms.dat" u 1:3 w l title "Omega 1.9" lc rgb "blue", \
     "omega199/norms.dat" u 1:3 w l title "Omega 1.99" lc rgb "green"

set out

set term png size 600,600
set logscale x
set logscale y
set xlabel "Iteration (in logarithmic scale)"
set ylabel "Norm (r) for different omega values"  #--------- "Updated title to reflect multiple plots"
set out "norms_r_add.png"

plot "rand/norms.dat" u 1:3 w l title "x = 0" lc rgb "red", \
     "omega199/norms.dat" u 1:3 w l title "x = 1" lc rgb "blue", \
     "zeroes/norms.dat" u 1:3 w l title "x = rand()" lc rgb "green"

set out
