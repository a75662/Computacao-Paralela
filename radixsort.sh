#!/bin/bash

#if [[ $# != 0 ]]; then
#	export OMP_NUM_THREADS=$1
#fi

threads=(1 2 4 8 12 16 20)

printf "Cut-Off"
for num_threads in "${threads[@]}"
do
	printf ",%d," $num_threads
done
printf "\n"

for (( rep = 0; rep < 10; rep++ )); do
	for (( cut_off = 125; cut_off <= 64000; cut_off*=2 )); do
		printf $cut_off
		for num_threads in "${threads[@]}"
		do
			export OMP_NUM_THREADS=$num_threads
			printf ,
			# digit = 6 -> 0-10M
			./a.out -co $cut_off -s 1500000 -d 6
		done
		printf "\n"
	done
done
