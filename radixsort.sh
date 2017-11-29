#!/bin/bash

if [[ $# != 0 ]]; then
	export OMP_NUM_THREADS=$1
fi
# para cada cut-off, fazer 10 repeticoes
for (( cut_off = 8; cut_off >= 0; cut_off-- )); do
	for (( rep = 0; rep < 10; rep++ )); do
		echo ---------------------------------------
		./a.out -co $cut_off
		echo ---------------------------------------
	done
done
