reset
st = 0
to = 1000
offset = 4
set xl "x"
set yl "psi"
unset key
set grid
set yr [0:0.5]
set term pngcairo enhanced size 640,480 font "Ubuntu, 12"
do for[i = st : to : offset]{
    pngname = sprintf('./res/output%04d.png', i / offset)
    set output pngname
    
    input = sprintf('./res/output%d.txt', i)
    graphtitle = sprintf("t = %.2f", i * 0.01)
    set title graphtitle
    plot input w l
}
set term qt
set output
reset
