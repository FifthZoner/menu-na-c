#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "opcja4.h"

#if !_MSC_VER
#define scanf_s scanf
#define fscanf_s fscanf
#define strnlen_s strnlen
#endif

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

// wypisuje zawartosc podejynczej struktury, podac wskaznik do niej
void printTeam(Team* team) {
	printf("Nazwa: %s\nIlosc wygranych: %i\nOstatnie wyniki: %i, %i, %i, %i, %i\n\n",
		team->name, team->wins, team->lastNumberOfGoals[0], team->lastNumberOfGoals[1],
		team->lastNumberOfGoals[2], team->lastNumberOfGoals[3], team->lastNumberOfGoals[4]);
}

// wypisuje wszystkie zawartosci struktury, podac wskaznik do wskaznikow do struktur i dlugosc
void printTeams(Team** f1, uint8_t len) {
	printf("\n");
	for (uint8_t n = 0; n < len; n++) {
		printTeam(f1[n]);
	}
}

// zwraca wskaznik do 1 wypelnionej struktury
Team* scanTeam(void) {
	Team* temp;
	temp = (Team*)malloc(sizeof(Team));
	if (temp == NULL) {
		printf("Blad alokacji!\n");
		return NULL;
	}
	while (1) {
		printf("Podaj ilosc wygranych: ");
		if (scanf_s("%i", &temp->wins) != 1) {
			while (getchar() != '\n');
			printf("Blad wejscia!\n");
		}
		else {
			while (getchar() != '\n');
			break;
		}
	}
	while (1) {
		printf("Podaj 5 ostatnich ilosci goli:\n");
		if (scanf_s("%i %i %i %i %i",
			&temp->lastNumberOfGoals[0],
			&temp->lastNumberOfGoals[1],
			&temp->lastNumberOfGoals[2],
			&temp->lastNumberOfGoals[3],
			&temp->lastNumberOfGoals[4]) != 5) {
			while (getchar() != '\n');
			printf("Blad wejscia!\n");
		}
		else {
			while (getchar() != '\n');
			break;
		}
	}
	// tak, duzy bufor, ale trzeba byc gotowym na wszystko
	temp->name = (char*)malloc(1024 * sizeof(char));
	if (temp->name == NULL) {
		printf("Blad alokacji!\n");
		free(temp);
		return NULL;
	}
	while (1) {
		printf("Podaj nazwe druzyny: ");
		if (scanf_s("\n%[^\n]", temp->name, 1024) != 1) {
			while (getchar() != '\n');
			printf("Blad wejscia!\n");
		}
		else {
			while (getchar() != '\n');
			break;
		}
	}
	void* ptr = (char*)realloc(temp->name, strnlen_s(temp->name, sizeof(temp->name)) + 1);
	// nie przypisze jak cos nie tak
	if (ptr != NULL) {
		temp->name = (char*)ptr;
	}


	return temp;
}

// zwalnia zaalokowana pamiec dla 1 struktury, podac wskaznik do niej
void freeTeam(Team* team) {

	free(team->name);
	free(team);
}

// wczytuje nazwe pliku i zapisuje dane
void saveData(void) {

	while (getchar() != '\n');

	char path[256];
	memset(path, '\0', sizeof(path));
	*path = '\0';
	while (1) {
		printf("Podaj nazwe pliku: ");
		if (scanf_s("%[^\n]", path, (unsigned int)sizeof(path)) != 1) {
			printf("Blad wejscia!\n");
		}
		else {
			break;
		}
	}
	char mode = 0;
	while (mode != 'w' && mode != 'a') {
		while (1) {
			printf("Nadpisac czy dodac (w - write over, a - add): ");
			if (scanf_s("%c", &mode, 2) != 1) {
				while (getchar() != '\n');
				printf("Blad wejscia!\n");
			}
			else {
				break;
			}
		}
		
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
	// taki syntax:
	// 
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
void loadData( void ) {

	while (getchar() != '\n');

	char path[256];
	memset(path, '\0', sizeof(path));
	*path = '\0';
	while (1) {
		printf("Podaj nazwe pliku: ");
		if (scanf_s("%[^\n]", path, 256) != 1) {
			printf("Blad lub za dluga nazwa!\n");
		}
		else {
			break;
		}
	}
	

	FILE* file = fopen(path, "r");

	if (file == NULL) {
		printf("Nie mozna otworzyc pliku!\n");
		return;
	}

	unsigned int amountToLoad = 0;
	while (fscanf_s(file, "%i\n", &amountToLoad) == 1) {

		
		if (teamsLength + amountToLoad > sizeLimit) {
			amountToLoad = sizeLimit - teamsLength;
		}

		Team** temp = (Team**)realloc(teams, (unsigned long long)(teamsLength + amountToLoad) * sizeof(Team*));
		if (temp == NULL) {
			printf("Blad alokacji!\n");
			fclose(file);
			return;
		}
		teams = temp;
		for (uint8_t n = 0; n < amountToLoad; n++) {
			Team* ptr = (Team*)malloc(sizeof(Team));
			if (ptr == NULL) {
				printf("Blad alokacji!\n");
				free(ptr);
				fclose(file);
				teamsLength += n;

				// skracanie
				Team** temp1 = (Team**)realloc(teams, teamsLength * sizeof(Team*));
				if (temp1 == NULL) {
					// w duzej czesci przypdakow program powinien dalej dzialac
					printf("Blad skracania tablicy!\nKontynuacja niezalecana!\n");
					return;
				}
				teams = temp1;
				return;
			}
			ptr->name = (char*)malloc(1024 * sizeof(char));
			if (ptr->name == NULL) {
				printf("Blad alokacji!\n");
				free(ptr);
				fclose(file);
				teamsLength += n;

				// skracanie
				Team** temp2 = (Team**)realloc(teams, teamsLength * sizeof(Team*));
				if (temp2 == NULL) {
					// w duzej czesci przypdakow program powinien dalej dzialac
					printf("Blad skracania tablicy!\nKontynuacja niezalecana!\n");
					return;
				}
				teams = temp2;
				return;
			}

			if (fscanf_s(file, "%[^\n]%i %i %i %i %i %i\n", ptr->name, 1024, &ptr->wins,
				&ptr->lastNumberOfGoals[0], &ptr->lastNumberOfGoals[1],
				&ptr->lastNumberOfGoals[2], &ptr->lastNumberOfGoals[3],
				&ptr->lastNumberOfGoals[4]) == 7) {

				char* temp3 = (char*)realloc(ptr->name, strnlen_s(ptr->name, 1024) + 1);
				
				if (temp3 == NULL) {
					printf("Blad alokacji przy skracaniu, kontynuowanie z wiêksz¹ pamiecia!\n");
				}
				else {
					ptr->name = temp3;
				}
				teams[teamsLength + n] = ptr;
			}
			else {
				free(((Team*)ptr)->name);
				free(ptr);
			}
		}

		teamsLength += (uint8_t)amountToLoad;
	}
	
	fclose(file);
}

// zarzadza iloscia struktur typu Team w zadany przez uzytkownika sposob
void opcja4(void) {

	char result = 0;

	while (1) {
		printf("Cos zrobic? (p - print all, a - add, d - delete last, s - save, l - load):\n");
		if (scanf_s("%c", &result, 1) != 1) {
			while (getchar() != '\n');
			printf("Blad wejscia!\n");
		}
		else {
			break;
		}
	}

	// do realloca
	void* ptr = NULL;
	Team* ptr2 = NULL;

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
			ptr2 = scanTeam();
			if (ptr2 == NULL) {
				printf("Nie mozna bylo wczytac danych!\n");
			}
			else {
				ptr = (Team**)realloc(teams, (unsigned long long)(teamsLength + 1) * sizeof(Team*));

				if (ptr != NULL) {

					teams = (Team**)ptr;
					teams[teamsLength] = ptr2;
					teamsLength++;
				}
				else {
					// chyba null jest przy wielkosci 0 ale jakby co bo nie chce mi sie szukac
					printf("Blad alokacji!\n");
				}
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
				// ostatni indeks nie bedzie brany pod uwage i moze zostanie zwolniony za nastepnym wywolaniem
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
void freeTeams( void ) {
	if (teamsLength > 0) {
		for (uint8_t n = 0; n < teamsLength; n++) {
			freeTeam(teams[n]);
		}
		free(teams);
		teams = NULL;
		teamsLength = 0;
	}
}