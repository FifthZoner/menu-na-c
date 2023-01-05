#include <stdio.h>
#include <stdlib.h>
#include "opcja2.h"

// suma, tak nazwana z powodu polecenia
float mean(float* array, int len) {
	float value = 0;
	for (unsigned int n = 0; n < len; n++) {
		value += array[n];
	}
	return value;
}

// wypisuje sume 10 elementow zmiennoprzecinkowych wczytanych od uzytkownika
void opcja2() {

	printf("Wybrano opcje 2, wypisanie tablicy i mean ktore powinno bys srednia, a jest suma\nPodaj wartosci:\n");

	float* tab = (float*)malloc(10 * sizeof(float));

	for (unsigned short int n = 0; n < 10; n++) {
		scanf("%f", &tab[n]);
	}

	printArray(tab, 10);
	printf("Suma to: %f\n", mean(tab, 10));

	free(tab);
}