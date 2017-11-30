#!/bin/bash

max_threads=16
if [[ $# != 0 ]]; then
	max_threads=$1
fi
<<<<<<< HEAD
cut_off=6

# para cada nr threads, para cada cut-off, fazer 10 repeticoes
for (( threads = 1; threads <= max_threads; threads *= 2 )); do
	export OMP_NUM_THREADS=	 $threads
	for (( rep = 0; rep < 10; rep++ )); do
		echo ---------------------------------------
		./a.out -co $cut_off
		echo ---------------------------------------
=======

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
>>>>>>> master
	done
done
