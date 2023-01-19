#include <stdio.h>
#include "opcja1.h"

// zwraca maksymalna z 10 liczb wczytanych od uzytkownika
float getMax( void ){
	float max = 0, current = 0;

	// pierwsza wartosc
	while (1) {
		printf("Podaj 1. liczbe: ");
		if (scanf_s("%f", &current) != 1) {
			while (getchar() != '\n');
			printf("Blad wejscia!\n");
		}
		else {
			while (getchar() != '\n');
			break;
		}
	}
	
	max = current;

	for (unsigned short int n = 1; n < 10; n++) {

		while (1) {
			printf("Podaj %i. liczbe: ", n + 1);
			if (scanf_s("%f", &current) != 1) {
				while (getchar() != '\n');
				printf("Blad wejscia!\n");
			}
			else {
				while (getchar() != '\n');
				break;
			}
		}

		if (current > max) {
			max = current;
		}
	}

	return max;
}

// wywoluje funkcje ktora zwraca maksymalna z 10 liczb wczytanych od uzytkownika
void opcja1( void ) {
	printf("Wybrano opcje 1, podanie najwiekszej z 10 liczb\n");

	printf("Najwieksza z nich to: %f\n", getMax());
}