#!/bin/bash

if [[ $# != 0 ]]; then
	export OMP_NUM_THREADS=$1
fi

printf "Cut-Off","1 Thread","2 Threads","4 Threads","8 Threads\n"

for (( rep = 0; rep < 10; rep++ )); do
	for (( cut_off = 500; cut_off <= 1024000; cut_off*=2 )); do
		printf $cut_off
		for (( num_threads = 1; num_threads <= 8; num_threads*=2 )); do
			export OMP_NUM_THREADS=$num_threads
			printf ,
			# digit = 6 -> 0-10M
			./a.out -co $cut_off -s $((1500000)) -d 6
		done
		printf "\n"
	done
done
