run()
{
exe=$1
entrada=$2
saida_prefixo=${entrada//entradas\//}

echo Running $entrada
./$exe $entrada

echo Analyzing $entrada
gprof $exe gmon.out > saida/report-$saida_prefixo
gprof2dot -n0 -e0 saida/report-$saida_prefixo > saida/report-$saida_prefixo.dot
dot -Tpng -osaida/report-$saida_prefixo.png saida/report-$saida_prefixo.dot

echo $entrada  finished.
echo
}

ARGC=$#

if [ $ARGC -gt 1 ]; then
	run $1 $2
else
	for entry in entradas/*
	do
		run $1 "$entry"
	done
fi;
