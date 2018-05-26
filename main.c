#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "marathon.h"
#include "marathoninput.h"

int main() {
    int firstParam, secondParam, outCode = 0;
    char *line, *operation;

    line = malloc((MAXINPUTLENGTH + 1) * sizeof(char));
    if (line == NULL)
        exit(1);
    operation = malloc(10 * sizeof(char));
    if (operation == NULL) {
        free(line);
        exit(1);
    }
    if (3 == intializeUsers()) {
        free(line);
        free(operation);
        exit(1);
    }

    while (getMarathonLine(line, operation, &firstParam, &secondParam) == 0) {
        /*
         * Oznaczenia kodów wyjścia ponirzej używanych funkcji (outCode = ?):
         *  0 - wymagane wypisanie "OK\n"
         *  1 - wymagane wypiszanie "ERROR\n" na wyjście diagnostyczne
         *  3 - wymagane wyczyszczenie pamięci i wyjście z programu z kodem 1 (możliwe np. po błędzie alokacji pamięci)
         *  inne - wymagane niewypisywanie dodatkowych informacji
         */
        if (strcmp(operation, "#") == 0)
            outCode = 2; // Linia do zignowowania - komentarz, albo wiersz pusty
        else if (strcmp(operation, "marathon") == 0) {
            outCode = marathonPrint(usersIdToUsers(firstParam), secondParam);
            if (outCode == 0)
                outCode = 2; // Jeśli ta operacja się powiodła, to nie jest oczekiwana żadna dodatkowa informacja na wyjście
        } else if (strcmp(operation, "addUser") == 0)
            outCode = addUser(usersIdToUsers(firstParam), secondParam);
        else if (strcmp(operation, "delUser") == 0)
            outCode = delUser(firstParam);
        else if (strcmp(operation, "addMovie") == 0)
            outCode = addMovie(usersIdToUsers(firstParam), secondParam);
        else if (strcmp(operation, "delMovie") == 0)
            outCode = delMovie(usersIdToUsers(firstParam), secondParam);
        else
            outCode = 1; // Inny kod operacji (w tym "error")

        // Wypisywanie dodatkowych informacji
        if (outCode == 0)
            printf("OK\n");
        else if (outCode == 1)
            fprintf(stderr, "ERROR\n");
        else if (outCode == 3)
            break;
    }

    // Sprawdzenie, czy ostatni wiersz (zawieracjący EOF) był pusty, lub był komentarzem. Jeśli nie, to trzeba wypisać "error", bo poprawne wiersze kończą się '\n'
    if (strcmp(operation, "#") != 0)
        fprintf(stderr, "ERROR\n");

    free(line);
    free(operation);
    freeAll();
    if (outCode == 3)
        return 1;
    return 0;
}