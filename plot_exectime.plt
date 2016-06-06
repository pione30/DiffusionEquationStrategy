reset

set term qt enhanced font 'Ubuntu, 12'

set title 'Execution Time of Solving the Diffusion Equation (NT = 10^{\ 4})'
set key top left font 'Ubuntu, 11' 
set grid
set logscale x 2
set logscale y 10
set format x "2^{%L}"
set format y "10^{%L}"
set xr [2**10 : 2**15]
set xl 'NX'
set yl 'time[s]'
set dashtype 1 (10, 5)

plot './res/exectime_P3GSL.txt' u 1:($2 * 1.0e-3) w lp lw 2 t 'GSL', \
     './res/exectime_P25CrankNicolson_GaussSeidel.txt' u 1:($2 * 1.0e-3) w lp lw 2 t 'CrankNicolson\_GaussSeidel', \
     './res/exectime_P20CrankNicolson_LAPACK.txt' u 1:($2 * 1.0e-3) w lp lw 2 t 'CrankNicolson\_LAPACK', \
     './res/exectime_P4FFTW.txt' u 1:($2 * 1.0e-3) w lp lw 2 t 'FFTW', \
     2.0e-9*x**3 lc "black" dt 1 t "O(N^3)", \
     5.0e-7*x**2 lc "dark-blue" dt 1 t "O(N^2)", \
     4.5e-5*x*log(x) lc "dark-green" dt 1 t "O(NlogN)", \
     2.5e-4*x lc "dark-red" dt 1 t "O(N)"

reset
