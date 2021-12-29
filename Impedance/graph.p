set style data lines;
set size 1.0, 1.0;
set origin 0.0, 0.0;
set multiplot;

set size 1.0, 0.5;
set origin 0, 0.5;
set grid;
set logscale x 10;
set logscale y 10;
set title "Module";
set xlabel "Frequence (Hz)";
set ylabel "Impedance |Z|";
plot "Impedance.dat" using 1:2 title "Module";

set size 1.0, 0.5;
set origin 0, 0;

set title "Phase";
set ylabel "Phase (degrees)";
set xlabel "Frequence (Hz)";
unset logscale y;
plot "Impedance.dat" using 1:3 title "Phase";
pause -1 "Hit return";
exit;