entrada=$1
saida_prefixo=${entrada//entradas\//}

./ecosystem $entrada
gprof ecosystem gmon.out > saida/report-$saida_prefixo
gprof2dot -n0 -e0 saida/report-$saida_prefixo > saida/report-$saida_prefixo.dot
dot -Tpng -osaida/report-$saida_prefixo.png saida/report-$saida_prefixo.dot
