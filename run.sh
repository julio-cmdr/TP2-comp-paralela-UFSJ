run()
{
entrada=$1
saida_prefixo=${entrada//entradas\//}

echo Running $entrada
./ecosystem $entrada

echo Analyzing $entrada
gprof ecosystem gmon.out > saida/report-$saida_prefixo
gprof2dot -n0 -e0 saida/report-$saida_prefixo > saida/report-$saida_prefixo.dot
dot -Tpng -osaida/report-$saida_prefixo.png saida/report-$saida_prefixo.dot

echo $entrada  finished.
echo
}

ARGC=$#

if [ $ARGC -gt 0 ]; then
	run $1
else
	for entry in entradas/*
	do
		run "$entry"
	done
fi;
