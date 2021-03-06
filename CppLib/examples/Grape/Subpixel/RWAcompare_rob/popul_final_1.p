set term postscript eps enhanced color blacktext 'Helvetica' 24
set terminal postscript
set output '| epstopdf --filter >RWAcompare_rob/popul_final_1.pdf'
set ylabel 'Controls (GHz)'
set xlabel 'Time during Gate (ns)'
unset log y
set nokey
unset title
plot 'RWAcompare_rob/popul_final_1.dat' u 1:2w l,'RWAcompare_rob/popul_final_1.dat' u 1:3w l,'RWAcompare_rob/popul_final_1.dat' u 1:4w l
set output
quit
