#!/bin/bash

if [[ $# != 0 ]]; then
	export OMP_NUM_THREADS=$1
fi

printf Threads,"Cut-Off\n"
for (( num_threads = 1; num_threads <= 8; num_threads *= 2)); do
	export OMP_NUM_THREADS=$num_threads
	for (( cut_off = 3; cut_off > 0; cut_off-- )); do
		printf $num_threads,$cut_off
		for (( rep = 0; rep < 10; rep++ )); do
			printf ","
			./a.out -co $cut_off -s 8000 -d 3
		done
		printf "\n"
	done
done
