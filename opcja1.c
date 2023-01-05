#include <stdio.h>
#include "opcja1.h"

// zwraca maksymalna z 10 liczb wczytanych od uzytkownika
float getMax() {
	float max = 0, current = 0;

	// pierwsza wartosc
	printf("Podaj 1. liczbe: ");
	scanf("%f", &current);
	max = current;

	for (unsigned short int n = 1; n < 10; n++) {

		printf("Podaj %i. liczbe: ", n + 1);
		scanf("%f", &current);

		if (current > max) {
			max = current;
		}
	}

	return max;
}

// wywoluje funkcje ktora zwraca maksymalna z 10 liczb wczytanych od uzytkownika
void opcja1() {
	printf("Wybrano opcje 1, podanie najwiekszej z 10 liczb\n");

	printf("Najwieksza z nich to: %f\n", getMax());
}