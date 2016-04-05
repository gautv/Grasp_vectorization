numberIterations=1
for instance in 56 66 76 86 96 106 116
do
	echo "Computing Instance ${instance}"
	(./test.sh ${instance} 0 10 0 10) &> ./dat/I${instance}_R${numberIterations}.dat
done
