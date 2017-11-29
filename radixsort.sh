#!/bin/bash

max_threads=16
if [[ $# != 0 ]]; then
	max_threads=$1
fi
cut_off=6

# para cada nr threads, para cada cut-off, fazer 10 repeticoes
for (( threads = 1; threads <= max_threads; threads *= 2 )); do
	export OMP_NUM_THREADS=	 $threads
	for (( rep = 0; rep < 10; rep++ )); do
		echo ---------------------------------------
		./a.out -co $cut_off
		echo ---------------------------------------
	done
done
