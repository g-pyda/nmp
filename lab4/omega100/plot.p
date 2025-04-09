set term png size 600,600
set ylabel "Vector Component (v)"  #--------- "Updated title"
set xlabel "Vector index"
set out "vec_v.png"
plot "vector.dat" u 1:3 w l title "Vector (v)"

set out

set term png size 600,600
set ylabel "Vector Component (ro)"  #--------- "Updated title"
set xlabel "Vector index"
set out "vec_ro.png"
plot "vector.dat" u 1:2 w l title "Vector (ro)"

set out

set term png size 600,600
set logscale x  #--------- "Enable logarithmic scale for x-axis"
set xlabel "Iteration (in logarithmic scale)"  #--------- "Label for clarity"
set ylabel "Norm (v)"  #--------- "Updated title to reflect output"
set out "norms_v.png"
plot "norms.dat" u 1:2 w l title "Norm (v)"

set out

set term png size 600,600
set logscale x
set logscale y
set xlabel "Iteration (in logarithmic scale)"
set ylabel "Norm (r)"  #--------- "Updated title"
set out "norms_r.png"
plot "norms.dat" u 1:3 w l title "Norm (r)"

set out