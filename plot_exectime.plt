reset

set term qt enhanced font ',12'

set grid
set title 'Execution Time of Solving Diffusion Equation (NT = 10^4)'
set key top left font ',11' 
set xl 'NX'
set yl 'time[ms]'

plot './res/exectime_P3GSL.txt' w lp t 'GSL', \
     './res/exectime_P25CrankNicolson_GaussSeidel.txt' w lp t 'CrankNicolson\_GaussSeidel', \
     './res/exectime_P20CrankNicolson_LAPACK.txt' w lp t 'CrankNicolson\_LAPACK', \
     './res/exectime_P4FFTW.txt' w lp t 'FFTW'

reset
