set term png size 600,600
set ylabel "Eigenvalue"  #--------- "Updated title to reflect multiple plots"
set out "eigenvalues.png"

plot "eigenval0.dat" u 1:2 w l title "lambda 0" lc rgb "red", \
     "eigenval1.dat" u 1:2 w l title "lambda 1" lc rgb "green", \
     "eigenval2.dat" u 1:2 w l title "lambda 2" lc rgb "blue", \
     "eigenval3.dat" u 1:2 w l title "lambda 3" lc rgb "cyan", \
     "eigenval4.dat" u 1:2 w l title "lambda 4" lc rgb "magenta", \
     "eigenval5.dat" u 1:2 w l title "lambda 5" lc rgb "orange", \
     "eigenval6.dat" u 1:2 w l title "lambda 6" lc rgb "brown", \
     "eigenval7.dat" u 1:2 w l title "lambda 7" lc rgb "violet", \
     "eigenval8.dat" u 1:2 w l title "lambda 8" lc rgb "gold", \
     "eigenval9.dat" u 1:2 w l title "lambda 9" lc rgb "turquoise"

set out