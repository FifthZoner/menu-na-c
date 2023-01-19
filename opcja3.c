#include <stdio.h>
#include <stdlib.h>
#include "opcja3.h"

#if !_MSC_VER
#define scanf_s scanf
#define fscanf_s fscanf
#define strnlen_s strnlen
#endif

// wypisywanie tablicy, podac tablice float i dlugosc
void printArrayInt(int* array, unsigned int len) {

	for (unsigned int n = 0; n < len; n++) {
		printf("%i ", array[n]);
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
void opcja3( void ) {
	printf("Wybrano opcje 3\n");
	int n = 0;
	while (1) {
		
		printf("Podaj wielkosc tablicy do stworzenia: ");
		if (scanf_s("%i", &n) != 1) {
			while (getchar() != '\n');
			printf("Blad wejscia!\n");
		}
		else {
			break;
		}
	}

	int* tab = uploadMemory(NULL, n);

	ones(tab, n);

	printf("Stworzona tablica wyglada nastepujaco:\n");
	printArrayInt(tab, n);

	freeMemory(tab);
}