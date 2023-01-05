#include <stdio.h>
#include <stdlib.h>
#include "opcja3.h"

// wypisywanie tablicy
void printArray(float* array, int len) {

	for (unsigned int n = 0; n < len; n++) {
		printf("%f ", array[n]);
	}
	printf("\n");
}

// alokuje pamiec
int* uploadMemory(int* pointer, int n) {
	return (int*)realloc(pointer, n * sizeof(int));
}

// zwalnia pamiec
void freeMemory(int* pointer) {
	free(pointer);
}

// mimo nazwy zapisuje tablice zerami
void ones(int* pointer, int len) {
	for (int n = 0; n < len; n++) {
		pointer[n] = 0;
	}
}

// tworzy tablice o podanej wielkosci, wypelnia ja zerami i wyswietla
void opcja3() {
	printf("Wybrano opcje 3\n");

	printf("Podaj wielkosc tablicy do stworzenia: ");
	int n = 0;
	scanf("%i", &n);

	int* tab = uploadMemory(NULL, n);

	ones(tab, n);

	printf("Stworzona tablica wyglada nastepujaco:\n");
	printArray(tab, n);

	freeMemory(tab);

}