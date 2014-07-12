set term postscript eps enhanced color blacktext 'Helvetica' 24
set terminal png
set output 'popul_int.png'
set xlabel 'Time during Gate (ns)'
unset log y
set nokey
unset title
plot 'popul_int.dat' u 1:2 w l lw 4,'popul_int.dat' u 1:3 w l lw 4,'popul_int.dat' u 1:4 w l lw 4,'popul_int.dat' u 1:5 w l lw 4,'popul_int.dat' u 1:6 w l lw 4,'popul_int.dat' u 1:7 w l lw 4
set output
quit