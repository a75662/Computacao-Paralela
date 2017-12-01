#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <omp.h>
#include <string.h>

int cut_off;
double seq_time;

void cutoffradixsort(int array[], int size, int digit, int *aux) {

	if(size <= 1 || digit < 0){
		return;
	}

	int count[11] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, size};
	//int *aux = malloc(sizeof(int) * size);

	int i, num = pow(10, digit);

	for(i = 0; i < size; i++)
		count[(array[i]/num) % 10]++;

	//double it = omp_get_wtime();

	for(i = 1; i < 10; i++)
		count[i] += count[i-1];

	for(i = 0; i < size; i++)
		aux[--count[(array[i]/num) % 10]] = array[i];

	/*double ft = omp_get_wtime();
	if (seq_time == 0) {
		seq_time = ft - it;
	}*/

	for(i = 0; i < size; i++)
		array[i] = aux[i];

	//free(aux);

	for(int i = 0; i < 10; i++){
		cutoffradixsort(array + count[i], count[i+1]-count[i], digit-1, aux + count[i]);
	}
}

void radixsort(int array[], int size, int digit, int *aux) {

	if(size <= 1 || digit < 0){
		return;
	}

	if (size < cut_off) {
		return cutoffradixsort(array, size, digit, aux);
	}

	int count[11] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, size};
	//int *aux = malloc(sizeof(int) * size);

	int i, num = pow(10, digit);

	for(i = 0; i < size; i++)
		count[(array[i]/num) % 10]++;

	for(i = 1; i < 10; i++)
		count[i] += count[i-1];

	for(i = 0; i < size; i++)
		aux[--count[(array[i]/num) % 10]] = array[i];

	for(i = 0; i < size; i++)
		array[i] = aux[i];

	//free(aux);

	for(int i = 0; i < 10; i++){
		#pragma omp task
		radixsort(array + count[i], count[i+1]-count[i], digit-1, aux + count[i]);
	}
	#pragma omp taskwait
}

void firstradixsort(int array[], int size, int digit) {

	if(size <= 1 || digit < 0){
		return;
	}
	/*
	if (size < cut_off) {
		return cutoffradixsort(array, size, digit);
	}
	*/
	int count[11] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, size};
	int *aux = malloc(sizeof(int) * size);

	int i, num = pow(10, digit);

	#pragma omp parallel
	{

		#pragma omp for reduction(+:count)
		//#pragma omp single
		for(i = 0; i < size; i++){
			int c = (array[i]/num) % 10;
			count[c]++;
		}

		#pragma omp single
		{
			double it = omp_get_wtime();

			for(i = 1; i < 10; i++)
				count[i] += count[i-1];

			//#pragma omp for
			//#pragma omp single
			for(i = 0; i < size; i++){
				int c = (array[i]/num) % 10;

				int ind;
				//#pragma omp atomic capture
				ind = --count[c];

				aux[ind] = array[i];
			}

			double ft = omp_get_wtime();

			seq_time = ft-it;
		}

		#pragma omp for
		for(i = 0; i < size; i++)
			array[i] = aux[i];

		#pragma omp single
		{
			//free(aux);

			//#pragma omp single
			for(int i = 0; i < 10; i++){
				#pragma omp task
				radixsort(array + count[i], count[i+1]-count[i], digit-1, aux + count[i]);
			}
			#pragma omp taskwait
		}
	}

	free(aux);
}

void print(int array[], int size){
	for(int i = 0; i < size; i++){
		printf("%d ", array[i]);
	}
	printf("\n");
}

int sorted(int array[], int size){
	for (int i = 1; i < size; i++){
		if(array[i] < array[i-1])
			return 0;
	}
	return 1;
}

void parse_args(int argc, const char *argv[], int *digit, int *size) {
	*digit = 8;
	*size = pow(10, 8);
	cut_off = pow(2, 16); // cache L2
	if (argc > 2) {
		if (strcmp(argv[1], "-d") == 0) {
			*digit = atoi(argv[2]);
		}
		else if (strcmp(argv[1], "-s") == 0) {
			*size = atoi(argv[2]);
		}
		else if (strcmp(argv[1], "-co") == 0) {
			cut_off = atoi(argv[2]);
		}
	}
	if (argc > 4) {
		if (strcmp(argv[3], "-d") == 0) {
			*digit = atoi(argv[4]);
		}
		else if (strcmp(argv[3], "-s") == 0) {
			*size = atoi(argv[4]);
		}
		else if (strcmp(argv[3], "-co") == 0) {
			cut_off = atoi(argv[4]);
		}
	}
	if (argc > 6) {
		if (strcmp(argv[5], "-d") == 0) {
			*digit = atoi(argv[6]);
		}
		else if (strcmp(argv[5], "-s") == 0) {
			*size = atoi(argv[6]);
		}
		else if (strcmp(argv[5], "-co") == 0) {
			cut_off = atoi(argv[6]);
		}
	}
}

int main(int argc, char const *argv[])
{
	int digit, size;
	parse_args(argc, argv, &digit, &size);

	int *array = malloc(sizeof(int) * size);

	int q = pow(10, digit+1);
	for(int i = 0; i < size; i++){
		array[i] = rand()%q;
	}

	int num_threads;

	#pragma omp parallel
	#pragma omp single
	num_threads = omp_get_num_threads();
	//printf("Sorting with %d thread(s)\n", num_threads);
	//printf("Cut-off: %d\n", cut_off);

	double it, ft;

	if (num_threads == 1) {
		int *aux = malloc(sizeof(int) * size);

		it = omp_get_wtime();
		cutoffradixsort(array, size, digit, aux);
		ft = omp_get_wtime();

		free(aux);
	}
	else {
		it = omp_get_wtime();
		firstradixsort(array, size, digit);
		ft = omp_get_wtime();
	}

	if (sorted(array, size)){
		//printf("Sorted in %f seconds\n", ft - it);
		printf("%f,", ft-it);
		//printf("Sequential time: %f seconds\n", seq_time);
		printf("%f", seq_time);
	}
	else {
		printf("Not Sorted\n");
	}
	return 0;
}
