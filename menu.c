// bledy i ostrzezenia sprawdzone dla poziomu Wall w Visual Studio 2022
// jedyne ostrzerzenia sa zwiazane z exploitem spectre, nie jestem pewnien czy implementacja fixa zadziala poza vs wiec ja pominalem

#include "opcja1.h"
#include "opcja2.h"
#include "opcja3.h"
#include "opcja4.h"

#include <stdio.h>
#include <stdbool.h>

void main_menu( void ) {
	// zmienne 
	const unsigned int nrAlbumu = 173625;
	const unsigned short nrRoku = 1;
	int nrOpcji = 0;
	// wyœwietlanie menu
	printf("Program w jezyku C wykonany przez studenta o indeksie nr %i na %i roku studiow\n", nrAlbumu, nrRoku);

	bool keepRunning = true;

	do {
		// opcja
		while (1) {
			while (getchar() != '\n');
			printf("Menu:\n- opcja 1:\n- opcja 2:\n- opcja 3:\n- opcja 4:\nWybierz opcje: ");
			if (scanf_s("%i", &nrOpcji) != 1) {
				printf("Blad wejscia!\n");
			}
			else {
				break;
			}
		}

		// sprawdzanie zakresu
		if (nrOpcji < 5) {
			if (nrOpcji > 0) {
				//  w zakresie

				if (nrOpcji < 3) {
					if (nrOpcji == 1) {
						opcja1();
						continue;
					}
					else {
						opcja2();
						continue;
					}
				}
				else {
					if (nrOpcji == 3) {
						opcja3();
						continue;
					}
					else {
						opcja4();
						continue;
					}
				}

			}
			else if (nrOpcji == -1) {
				// koniec
				break;
			}
			else {
				printf("Opcja poza zakresem!\n");
			}
		}
		else {
			printf("Opcja poza zakresem!\n");
		}
		

	} while (keepRunning);

	printf("Do widzenia\n");

	freeTeams();
}

int main( void ) {

	main_menu();

	return 0;
}