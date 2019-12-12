entrada=$1

./ecosystem $entrada
gprof ecosystem gmon.out > saida/report-$entrada.txt
gprof2dot -n0 -e0 saida/report-$entrada.txt > saida/report-$entrada.dot
dot -Tpng -osaida/report-$entrada.png saida/report-$entrada.dot
