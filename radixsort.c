#include <stdlib.h>
#include <math.h>
#include <stdio.h>




void radixsort(int array[], int size, int digit) {

	if(size <= 1 || digit < 0){
		return;
	}

	int *newarray[10];
	int newsize[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	for(int i = 0; i < 10; i++){
		newarray[i] = malloc(sizeof(int) * size);
	}

	for(int i = 0; i < size; i++){
		int s = pow(10, digit);
		int bucket = (array[i]/s)%10;

		newarray[bucket][newsize[bucket]++] = array[i];
	}

	int j = 0;
	for(int i = 0; i < 10; i++){
		
		radixsort(newarray[i], newsize[i], digit-1);

		for(int k = 0; k < newsize[i]; k++){
			array[j++] = newarray[i][k];
		}

		free(newarray[i]);
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
	int size = 10000000;
	int *array = malloc(sizeof(int) * size);
	for(int i = 0; i < size; i++){
		array[i] = rand()%100000000;
	}
	printf("Sorting\n");
	radixsort(array, size, 7);
	if (sorted(array, size)){
		printf("Sorted\n");
	}
	else {
		printf("Not Sorted\n");
	}
	return 0;
}
