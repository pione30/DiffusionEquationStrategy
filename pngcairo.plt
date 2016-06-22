reset
st = 0
to = 1000
offset = 4
se xl "x"
se yl "psi"
unse key
se grid
se yr [0:0.5]
se term pngcairo enhanced size 640,480 font "Ubuntu, 12"
do for[i = st : to : offset]{
    pngname = sprintf('./res/output%04d.png', i / offset)
    se output pngname
    
    input = sprintf('./res/output%d.txt', i)
    graphtitle = sprintf("t = %.2f", i * 0.01)
    se title graphtitle
    plot input w l
}
se term qt
se output
reset
