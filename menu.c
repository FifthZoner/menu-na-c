#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

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

void opcja1() {
	printf("Wybrano opcje 1, podanie najwiekszej z 10 liczb\n");

	printf("Najwieksza z nich to: %f\n", getMax());

}

void printArray(float* array, int len) {

	for (unsigned int n = 0; n < len; n++) {
		printf("%f ", array[n]);
	}
	printf("\n");
}

float mean(float* array, int len) {
	float value = 0;
	for (unsigned int n = 0; n < len; n++) {
		value += array[n];
	}
	return value;
}

void opcja2(float* tab) {
	

	printArray(tab, 10);
	printf("Suma to: %f\n", mean(tab, 10));
}

int* uploadMemory(int* pointer, int n) {
	return (int*)realloc(pointer, n * sizeof(int));
}

void freeMemory(int* pointer) {
	free(pointer);
}

void ones(int* pointer, int len) {
	for (int n = 0; n < len; n++) {
		pointer[n] = 0;
	}
}

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

typedef struct {

	char* name;
	unsigned int wins;
	unsigned int lastNumberOfGoals[5];

}Team;


uint8_t teamsLength = 0;
// tak, powinno to byc statyczna ale nie zauwazylem i w sumie to i tak jest limit narzucony
Team** teams = NULL;

void printTeam(Team* team) {
	printf("Nazwa: %s\nIlosc wygranych: %i\nOstatnie wyniki: %i, %i, %i, %i, %i\n\n",
		team->name, team->wins, team->lastNumberOfGoals[0], team->lastNumberOfGoals[1],
		team->lastNumberOfGoals[2], team->lastNumberOfGoals[3], team->lastNumberOfGoals[4]);
}

void printTeams(Team** f1, uint8_t len) {
	printf("\n");
	for (uint8_t n = 0; n < len; n++) {
		printTeam(f1[n]);
	}
}

Team* scanTeam() {
	Team* temp;
	temp = (Team*)malloc(sizeof(Team));
	printf("Podaj ilosc wygranych: ");
	scanf("%i", &temp->wins);
	printf("Podaj 5 ostatnich ilosci goli:\n");
	scanf("%i %i %i %i %i",
		&temp->lastNumberOfGoals[0],
		&temp->lastNumberOfGoals[1],
		&temp->lastNumberOfGoals[2],
		&temp->lastNumberOfGoals[3],
		&temp->lastNumberOfGoals[4]);
	// tak, duzy bufor, ale trzeba byc gotowym na wszystko
	temp->name = (char*)malloc(1024 * sizeof(char));
	printf("Podaj nazwe druzyny: ");
	scanf("\n%[^\n]", temp->name);
	void* ptr = (char*)realloc(temp->name, strlen(temp->name) + 1);
	// nie przypisze jak cos nie tak
	if (ptr != NULL) {
		temp->name = (char*)ptr;
	}


	return temp;
}

void freeTeam(Team* team) {

	free(team->name);
	free(team);
}

inline void opcja4() {

	printf("Cos zrobic? (p - print all, a - add, d - delete last):\n");

	char result = 0;
	scanf("\n%c", &result);

	// do realloca
	void* ptr = NULL;

	switch (result) {
	case 'p':

		if (teamsLength > 0) {
			printTeams(teams, teamsLength);
		}
		else {
			printf("Pusto tu...\n");
		}

		break;

	case 'a':

		if (teamsLength < 50) {
			ptr = (Team**)realloc(teams, (teamsLength + 1) * sizeof(Team*));

			if (ptr != NULL) {

				teams = (Team**)ptr;
				teams[teamsLength] = scanTeam();
				teamsLength++;
			}
			else {
				// chyba null jest przy wielkosci 0 ale jakby co bo nie chce mi sie szukac
				printf("Pamieci nie udalo sie zaalokowac!\n");
			}
		}
		else {
			printf("Limit jest tu");
		}
		
		

		break;

	case 'd':

		if (teamsLength > 0) {


			teamsLength--;
			teams[teamsLength] = scanTeam();
			ptr = (Team**)realloc(teams, (teamsLength) * sizeof(Team*));

			if (ptr != NULL) {

				teams = (Team**)ptr;
			}
			else {
				// chyba null jest przy wielkosci 0 ale jakby co bo nie chce mi sie szukac
				// ostarni indeks nie bedzie brany pod uwage i moze zostanie zwolniony za nastepnym wywolaniem
				printf("Pamieci nie udalo sie zaalokowac!\n");
			}

			break;
		}
		else {
			printf("Nie da sie usunac czegos, czego nie ma!\n");
		}

		break;

	default:

		printf("Zla akcja!\n");
		break;
	}

}

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

						printf("Wybrano opcje 2, wypisanie tablicy i mean ktore powinno bys srednia, a jest suma\nPodaj wartosci:\n");

						float* tab = (float*)malloc(10 * sizeof(float));

						for (unsigned short int n = 0; n < 10; n++) {
							scanf("%f", &tab[n]);
						}

						opcja2(tab);

						free(tab);

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

	if (teamsLength > 0) {

		for (uint32_t n = 0; n < teamsLength; n++) {
			freeTeam(teams[n]);
		}

		free(teams);
	}
}

int main() {

	main_menu();

	return 0;
}