#include <stdio.h>
#include <string.h>
#include "marathoninput.h"

int getMarathonLine(char *line, char *operation, int *firstParam, int *secondParam) {
    int i = 0, j, paramIter, spacesCounter = 0, spacePlace = 0;
    char c;
    long helper = 0;

    // Wczytanie całego wiersza zapamiętjąc tylko liczące się znaki
    while ((c = getchar()) != '\n' && c != EOF)
        if (i < MAXINPUTLENGTH)
            line[i++] = c;

    // Jeśli cały wiersz jest pusty, albo jest komentarzem, to go ignorujemy
    if (i == 0 || line[0] == '#') {
        sscanf("#", "%s", operation);
        if (c == EOF)
            return 1;
        return 0;
    }

    // Rozpoczęty wiersz, niebędący komentarzem, a kończący się znakiem EOF, a nie '\n' nie może być poprawny
    if (c == EOF) {
        sscanf("error", "%s", operation);
        return 1;
    }

    // Jeśli wiersz jest za długi, to nie może być poprawnym wejściem
    if (i > MAXINPUTLENGTH) {
        sscanf("error", "%s", operation);
        return 0;
    }

    // Ustawienie ostatniego znaku w strungu na '\0' (informacja o końcówce stringa)
    line[i] = '\0';

    // Zliczenie spacji
    for (j = 0; j < i && j < MAXINPUTLENGTH; j++)
        if (line[j] == ' ')
            spacesCounter++;

    // Poprawne wejście może mieć dokładnie jedną, lub dokładnie dwie spacje
    if (spacesCounter != 1 && spacesCounter != 2) {
        sscanf("error", "%s", operation);
        return 0;
    }

    // Znalezienie pierwszej spacji
    for (j = 0; j < i && j < MAXINPUTLENGTH; j++)
        if (line[j] == ' ') {
            spacePlace = j;
            break;
        }
    if (spacePlace > 8 || line[spacePlace + 1] == ' ') {
        // Spacja za daleko, żeby wejście było poprawne, lub dwie spacje obok siebie
        sscanf("error", "%s", operation);
        return 0;
    }
    // Wczytanie możliwej operacji
    sscanf(line, "%9s", operation);
    /*
     * Wczytanie pierwszego i drugiego argumentu (oprócz nazwy operacji) do zmiennej typy long long, alb sprawdzać, czy nie jest ona za duża
     *
     * W przypadku, kiedy jest dokładnie jeden parametr, to drugi wczytany parametr to będzie tym samym, co pierwszy,
     * bo nigdy nie znajdziemy drugiej spacji, czyli nigdy nie przesuniemy spacePlace na inne miejsce
     *
     * W przeciwnym przypadku wczytamy dwa różne parametry, bo przestawimy spacePlace w momencie znalezienaj kolejnej spacji
     */
    for (paramIter = 0; paramIter < 2; paramIter++) {

        helper = 0;

        // Sprawdzenie zer wiodących w liczbie
        if (line[spacePlace + 1] == '0' && ('0' <= line[spacePlace + 2] && line[spacePlace + 2] <= '9')) {
            sscanf("error", "%s", operation);
            return 0;
        }
        for (j = spacePlace + 1; j < i; j++) {
            if (line[j] < '0' || line[j] > '9') {
                if (line[j] == ' ') {
                    // Doszliśmy do kolejnej spacji, czyli skończyliśmy wczytywać pierwszy parametr
                    spacePlace = j;
                    break;
                } else {
                    sscanf("error", "%s", operation);
                    return 0;
                }
            } else {
                helper *= 10;
                helper += (line[j] - '0');
                if (helper > 2147483647) {
                    sscanf("error", "%s", operation);
                    return 0;
                }
            }
        }

        // Ustawienie parametru
        if (paramIter == 0)
            *firstParam = (int) helper;
        else
            *secondParam = (int) helper;
    }

    // Sprawdzenie, czy dana liczba paramerów jest poprawna - jest dokładnie jeden tylko dla operacji "delUser"
    if (spacesCounter == 1 && strcmp(operation, "delUser") != 0)
        sscanf("error", "%s", operation);
    if (spacesCounter == 2 && strcmp(operation, "delUser") == 0)
        sscanf("error", "%s", operation);

    return 0;
}