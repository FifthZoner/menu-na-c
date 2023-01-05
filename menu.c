#include "opcja1.h"
#include "opcja2.h"
#include "opcja3.h"
#include "opcja4.h"

void main_menu() {
	// zmienne 
	const unsigned int nrAlbumu = 173625;
	const unsigned short nrRoku = 1;
	int nrOpcji = 0;
	// wyœwietlanie menu
	printf("Program w jezyku C wykonany przez studenta o indeksie nr %i na %i roku studiow\n", nrAlbumu, nrRoku);


	do {
		printf("Menu:\n- opcja 1:\n- opcja 2:\n- opcja 3:\n- opcja 4:\nWybierz opcje: ");
		// opcja
		scanf("%i", &nrOpcji);

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
		}
		printf("Opcja poza zakresem!\n");

	} while (15);

	printf("Do widzenia\n");

	freeTeams();
}

int main() {

	main_menu();

	return 0;
}