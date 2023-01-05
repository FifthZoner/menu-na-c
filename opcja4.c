#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "opcja4.h"

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

// zarzadza iloscia struktur typu Team w zadany przez uzytkownika sposob
void opcja4() {

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