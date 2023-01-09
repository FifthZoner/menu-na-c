#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "opcja4.h"

#define sizeLimit 50

// definicja struktury team
typedef struct {

	char* name;
	unsigned int wins;
	unsigned int lastNumberOfGoals[5];

}Team;


uint8_t teamsLength = 0;
// tak, powinno to byc statyczna ale nie zauwazylem i w sumie to i tak jest limit narzucony
Team** teams = NULL;

// wypisuje zawartosc podejynczej struktury
void printTeam(Team* team) {
	printf("Nazwa: %s\nIlosc wygranych: %i\nOstatnie wyniki: %i, %i, %i, %i, %i\n\n",
		team->name, team->wins, team->lastNumberOfGoals[0], team->lastNumberOfGoals[1],
		team->lastNumberOfGoals[2], team->lastNumberOfGoals[3], team->lastNumberOfGoals[4]);
}

// wypisuje wszystkie zawartosci struktury
void printTeams(Team** f1, uint8_t len) {
	printf("\n");
	for (uint8_t n = 0; n < len; n++) {
		printTeam(f1[n]);
	}
}

// zwraca wskaznik do 1 wypelnionej struktury
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

// zwalnia zaalokowana pamiec dla 1 struktury
void freeTeam(Team* team) {

	free(team->name);
	free(team);
}

// wczytuje nazwe pliku i zapisuje dane
void saveData() {
	char path[256];
	printf("Podaj nazwe pliku: ");
	scanf("%s", path);
	char mode = 0;
	while (mode != 'w' && mode != 'a') {
		printf("Nadpisac czy dodac (w - write over, a - add): ");
		scanf("\n%c", &mode);
	}
	FILE* file;
	if (mode == 'w') {
		file = fopen(path, "w");
	}
	else {
		file = fopen(path, "a");
	}
	if (file == NULL) {
		printf("Nie mozna otworzyc pliku!\n");
		return;
	}

	// wlasciwe zapisywanie

	// amount\n
	// name\n
	// wins goals[0] goals[1] goals[2] goals[3] goals[4]\n
	// ...
	// amount\n (przy dopisywaniu)
	// ...
	fprintf(file, "%i\n", teamsLength);
	for (uint8_t n = 0; n < teamsLength; n++) {
		fprintf(file, "%s\n%i %i %i %i %i %i\n", teams[n]->name, teams[n]->wins,
			teams[n]->lastNumberOfGoals[0], teams[n]->lastNumberOfGoals[1], 
			teams[n]->lastNumberOfGoals[2], teams[n]->lastNumberOfGoals[3], 
			teams[n]->lastNumberOfGoals[4]);
	}

	fclose(file);
}

// wczytuje nazwe pliku i dane
// przestaje przy limicie lub bledzie
void loadData() {

	char path[256];
	printf("Podaj nazwe pliku: ");
	scanf("%s", path);

	FILE* file = fopen(path, "r");

	if (file == NULL) {
		printf("Nie mozna otworzyc pliku!\n");
		return;
	}

	uint8_t amountToLoad = 0;
	while (fscanf(file, "%i\n", &amountToLoad) == 1) {
		
		if (teamsLength + amountToLoad > sizeLimit) {
			amountToLoad = sizeLimit - teamsLength;
		}

		void* ptr = (Team**)malloc(teams, sizeof(Team*) * (amountToLoad + teamsLength));
		if (ptr == NULL) {
			return;
			fclose(file);
		}

		teams = (Team**)ptr;

		for (uint8_t n = 0; n < amountToLoad; n++) {
			ptr = (Team*)malloc(sizeof(Team));
			((Team*)ptr)->name = (char*)malloc(1024);

			if (fscanf(file, "%s%i%i%i%i%i%i", ((Team*)ptr)->name, &((Team*)ptr)->wins,
				&((Team*)ptr)->lastNumberOfGoals[0], &((Team*)ptr)->lastNumberOfGoals[1],
				&((Team*)ptr)->lastNumberOfGoals[2], &((Team*)ptr)->lastNumberOfGoals[3],
				&((Team*)ptr)->lastNumberOfGoals[4]) == 7) {


				ptr = (char*)realloc(((Team*)ptr)->name, strlen(((Team*)ptr)->name) + 1);
			}
			else {
				free(((Team*)ptr)->name);
				free(ptr);
			}
		}

		teamsLength += amountToLoad;
	}
	
	fclose(file);
}

// zarzadza iloscia struktur typu Team w zadany przez uzytkownika sposob
void opcja4() {

	printf("Cos zrobic? (p - print all, a - add, d - delete last, s - save, l - load):\n");

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

		if (teamsLength < sizeLimit) {
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

	case 's':
		saveData();
		break;

	case 'l':
		loadData();
		break;

	default:

		printf("Zla akcja!\n");
		break;
	}
}

// zwalnia syf
void freeTeams() {
	if (teamsLength > 0) {

		for (uint32_t n = 0; n < teamsLength; n++) {
			freeTeam(teams[n]);
		}

		free(teams);
		teamsLength = 0;
	}
}