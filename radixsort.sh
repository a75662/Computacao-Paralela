#!/bin/bash

#if [[ $# != 0 ]]; then
#	export OMP_NUM_THREADS=$1
#fi

threads=( 1 2 4 8 10 12 16 20 24 28 32 36 40)
printf "Cut-Off","1 Thread","2 Threads","4 Threads","8 Threads,"
printf "10 Thread","12 Threads","16 Threads","20 Threads,"
printf "24 Thread","28 Threads","32 Threads","36 Threads,"
printf "40 Threads\n"

for (( rep = 0; rep < 10; rep++ ));
do
	for (( cut_off = 125; cut_off <= 75000000; cut_off*=2 ));
	do #75 000 000 +/- para caber na cache L3 da maquina do search(30Mb, 4bytes por int)
		printf $cut_off
		for num_threads in "${threads[@]}"
		do
			export OMP_NUM_THREADS=$num_threads
			printf ,
			# digit = 6 -> 0-10M
			./a.out -co $cut_off -s $((100000000)) -d 7
		done
		printf "\n"
	done
done
