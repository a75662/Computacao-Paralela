#include <stdlib.h>
#include <math.h>
#include <stdio.h>

void radixsort(int array[], int size, int digit) {

	if(size <= 1 || digit < 0){
		return;
	}

	int count[11] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, size};
	int *aux = malloc(sizeof(int) * size);

	int i, num = pow(10, digit);

	for(i = 0; i < size; i++)
		count[(array[i]/num) % 10]++;

	for(i = 1; i < 10; i++)
		count[i] += count[i-1];

	for(i = 0; i < size; i++)
		aux[--count[(array[i]/num) % 10]] = array[i];

	for(i = 0; i < size; i++)
		array[i] = aux[i];

	free(aux);

	for(int i = 0; i < 10; i++){
		radixsort(array + count[i], count[i+1]-count[i], digit-1);
	}
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

int main(int argc, char const *argv[])
{
	int size = 100000000;
	int *array = malloc(sizeof(int) * size);
	for(int i = 0; i < size; i++){
		array[i] = rand()%1000000000;
	}
	printf("Sorting\n");

	radixsort(array, size, 8);

	if (sorted(array, size)){
		printf("Sorted\n");
	}
	else {
		printf("Not Sorted\n");
	}
	return 0;
}


