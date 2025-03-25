# ------------------- EIGENVALUES -------------------- #


# generating the eigenvalues with n = 100

set term png size 600,600 enhanced font 'Arial,12'
set out 'figures/eigenvalues100.png'

set grid

plot "eigenvalues/ev100.dat" u 1:2 title "eigenvalues"  lw 2 lc rgb "red", \
     "eigenvalues/evex100.dat" u 1:2 title "exact eigenvalues"  lw 2 lc rgb "blue"

set out

# generating the eigenvalues with n = 1000

set term png size 600,600 enhanced font 'Arial,12'
set out 'figures/eigenvalues1000.png'

set grid

plot "eigenvalues/ev1000.dat" u 1:2 title "eigenvalues"  lw 2 lc rgb "red", \
     "eigenvalues/evex1000.dat" u 1:2 title "exact eigenvalues"  lw 2 lc rgb "blue"

set out

# ------------------- EIGENVECTORS -------------------- #

# generating the eigenvectors (1) for n = 100

set term png size 600,600 enhanced font 'Arial,12'
set out 'figures/eigenvectors100_1.png'

set grid

plot "eigenvectors/ev1001.dat" u 1:2 title "eigenvectors"  lw 2 lc rgb "red", \
     "eigenvectors/evex1001.dat" u 1:2 title "exact eigenvectors" w l  lw 2 lc rgb "blue"

set out

# generating the eigenvectors (1) for n = 1000

set term png size 600,600 enhanced font 'Arial,12'
set out 'figures/eigenvectors1000_1.png'

set grid

plot "eigenvectors/ev10001.dat" u 1:2 title "eigenvectors"  lw 2 lc rgb "red", \
     "eigenvectors/evex10001.dat" u 1:2 title "exact eigenvectors" w l  lw 2 lc rgb "blue"

set out

# generating the eigenvectors (2) for n = 100

set term png size 600,600 enhanced font 'Arial,12'
set out 'figures/eigenvectors100_2.png'

set grid

plot "eigenvectors/ev1002.dat" u 1:2 title "eigenvectors"  lw 2 lc rgb "red", \
     "eigenvectors/evex1002.dat" u 1:2 title "exact eigenvectors" w l  lw 2 lc rgb "blue"

set out

# generating the eigenvectors (2) for n = 1000

set term png size 600,600 enhanced font 'Arial,12'
set out 'figures/eigenvectors1000_2.png'

set grid

plot "eigenvectors/ev10002.dat" u 1:2 title "eigenvectors"  lw 2 lc rgb "red", \
     "eigenvectors/evex10002.dat" u 1:2 title "exact eigenvectors" w l  lw 2 lc rgb "blue"

set out

# generating the eigenvectors (3) for n = 100

set term png size 600,600 enhanced font 'Arial,12'
set out 'figures/eigenvectors100_3.png'

set grid

plot "eigenvectors/ev1003.dat" u 1:2 title "eigenvectors"  lw 2 lc rgb "red", \
     "eigenvectors/evex1003.dat" u 1:2 title "exact eigenvectors" w l  lw 2 lc rgb "blue"

set out

# generating the eigenvectors (3) for n = 1000

set term png size 600,600 enhanced font 'Arial,12'
set out 'figures/eigenvectors1000_3.png'

set grid

plot "eigenvectors/ev10003.dat" u 1:2 title "eigenvectors"  lw 2 lc rgb "red", \
     "eigenvectors/evex10003.dat" u 1:2 title "exact eigenvectors" w l  lw 2 lc rgb "blue"

set out

# generating the eigenvectors (15) for n = 100

set term png size 600,600 enhanced font 'Arial,12'
set out 'figures/eigenvectors100_15.png'

set grid

plot "eigenvectors/ev10015.dat" u 1:2 title "eigenvectors"  lw 2 lc rgb "red", \
     "eigenvectors/evex10015.dat" u 1:2 title "exact eigenvectors" w l  lw 2 lc rgb "blue"

set out

# generating the eigenvectors (15) for n = 1000

set term png size 600,600 enhanced font 'Arial,12'
set out 'figures/eigenvectors1000_15.png'

set grid

plot "eigenvectors/ev100015.dat" u 1:2 title "eigenvectors"  lw 2 lc rgb "red", \
     "eigenvectors/evex100015.dat" u 1:2 title "exact eigenvectors" w l  lw 2 lc rgb "blue"

set out

# generating the eigenvectors (20) for n = 100

set term png size 600,600 enhanced font 'Arial,12'
set out 'figures/eigenvectors100_20.png'

set grid

plot "eigenvectors/ev10020.dat" u 1:2 title "eigenvectors"  lw 2 lc rgb "red", \
     "eigenvectors/evex10020.dat" u 1:2 title "exact eigenvectors" w l  lw 2 lc rgb "blue"

set out

# generating the eigenvectors (20) for n = 1000

set term png size 600,600 enhanced font 'Arial,12'
set out 'figures/eigenvectors1000_20.png'

set grid

plot "eigenvectors/ev100020.dat" u 1:2 title "eigenvectors"  lw 2 lc rgb "red", \
     "eigenvectors/evex100020.dat" u 1:2 title "exact eigenvectors" w l  lw 2 lc rgb "blue"

set out

# generating the eigenvectors (30) for n = 100

set term png size 600,600 enhanced font 'Arial,12'
set out 'figures/eigenvectors100_30.png'

set grid

plot "eigenvectors/ev10030.dat" u 1:2 title "eigenvectors"  lw 2 lc rgb "red", \
     "eigenvectors/evex10030.dat" u 1:2 title "exact eigenvectors" w l  lw 2 lc rgb "blue"

set out

# generating the eigenvectors (30) for n = 1000

set term png size 600,600 enhanced font 'Arial,12'
set out 'figures/eigenvectors1000_30.png'

set grid

plot "eigenvectors/ev100030.dat" u 1:2 title "eigenvectors"  lw 2 lc rgb "red", \
     "eigenvectors/evex100030.dat" u 1:2 title "exact eigenvectors" w l  lw 2 lc rgb "blue"

set out