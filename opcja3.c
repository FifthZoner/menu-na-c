#include <stdio.h>
#include <stdlib.h>
#include "opcja3.h"

// wypisywanie tablicy, podac tablice float i dlugosc
void printArray(float* array, int len) {

	for (unsigned int n = 0; n < len; n++) {
		printf("%f ", array[n]);
	}
	printf("\n");
}

// alokuje pamiec lub realokuje, podac wskaznik i ilosc int'ow
int* uploadMemory(int* pointer, int n) {
	return (int*)realloc(pointer, n * sizeof(int));
}

// zwalnia pamiec, podac wskaznik
void freeMemory(int* pointer) {
	free(pointer);
}

// mimo nazwy zapisuje tablice zerami, podac tablice int i dlugosc
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