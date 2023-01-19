#include <stdio.h>
#include <stdlib.h>
#include "opcja2.h"

#if !_MSC_VER
#define scanf_s scanf
#define fscanf_s fscanf
#define strnlen_s strnlen
#endif

// suma, tak nazwana z powodu polecenia, podac tablice float i dlugosc
float mean(float* array, unsigned int len) {
	float value = 0;
	for (unsigned int n = 0; n < len; n++) {
		value += array[n];
	}
	return value;
}

// wypisywanie tablicy, podac tablice float i dlugosc
void printArray(float* array, unsigned int len) {

	for (unsigned int n = 0; n < len; n++) {
		printf("%f ", array[n]);
	}
	printf("\n");
}

// wypisuje sume 10 elementow zmiennoprzecinkowych wczytanych od uzytkownika
void opcja2( void ) {

	printf("Wybrano opcje 2, wypisanie tablicy i mean ktore powinno bys srednia, a jest suma\nPodaj wartosci:\n");

	float* tab = (float*)malloc(10 * sizeof(float));

	if (tab == NULL) {
		printf("Blad alokacji!\n");
		return;
	}

	for (unsigned short int n = 0; n < 10; n++) {

		while (1) {
			if (scanf_s("%f", &tab[n]) != 1) {
				while (getchar() != '\n');
				printf("Blad wejscia!\n");
			}
			else {
				while (getchar() != '\n');
				break;
			}
		}
	}

	printArray(tab, 10);
	printf("Suma to: %f\n", mean(tab, 10));

	free(tab);
}