#include <stdio.h>
#include "movie.h"
#include "marathon.h"

int addMovie(UserPtr currentUser, int movieRating) {
    if (currentUser == NULL)
        return 1;
    return addMovieToList(currentUser->movies, movieRating);
}

int delMovie(UserPtr currentUser, int movieRating) {
    if (currentUser == NULL)
        return 1;
    return delMovieFromList(currentUser->movies, movieRating);
}

int addUser(UserPtr currentUser, int userId) {
    UserPtr newUser;
    if (userId > MAXUSERINDEX || userId < 0 || currentUser == NULL || usersIdToUsers(userId) != NULL)
        return 1; // Niepoprawny indeks nowego użytkownika, brak dodającego, lub nowy użytkownik już istnieje

    newUser = createUser(userId);
    if (newUser == NULL)
        return 3; // Błąd alokacji

    newUser->prevBrother = currentUser->firstSon;
    newUser->nextBrother = currentUser->firstSon->nextBrother;
    newUser->prevBrother->nextBrother = newUser;
    newUser->nextBrother->prevBrother = newUser;
    return 0;
}

int delUser(int userId) {
    // Zamiana Id użytkownika na wskaźnik na niego
    UserPtr currentUser = usersIdToUsers(userId);
    if (userId == 0 || currentUser == NULL)
        return 1; // próba usunięcia użytkownika 0, lub brak użytkownika

    // Przepinanie braci użytkownika i jego synów, jeśli istnieją
    if (currentUser->firstSon->nextBrother == currentUser->firstSon) {
        // Brak synow, to moi bracia stają się swoimi braćmi
        currentUser->prevBrother->nextBrother = currentUser->nextBrother;
        currentUser->nextBrother->prevBrother = currentUser->prevBrother;
    } else {
        // moi synowie, ktorzy nie są synem straznikiem (widmo) staja sie synami ojca (braćmi moich braci)
        currentUser->prevBrother->nextBrother = currentUser->firstSon->nextBrother;
        currentUser->firstSon->nextBrother->prevBrother = currentUser->prevBrother;
        currentUser->nextBrother->prevBrother = currentUser->firstSon->prevBrother;
        currentUser->firstSon->prevBrother->nextBrother = currentUser->nextBrother;
    }

    // Zwolnienie użytkownika i jego filmów
    freeUser(userId);
    return 0;
}

/*
 * Dokleja do danej listy wynik polecenia maraton (z treści zadania) wykonanego dla danego użytkownika, dla długości
 * nie większej niż lengthToCut i z założeniem, że wszytkie filmy wyjściowe musią mieć ranking nie mniejszy od minRating
 *  - currentList - lista do której doklejam filmy
 *  - currentUser - użytkownik dla którego rozpatruję "maraton"
 *  - lengthToCut - liczba początkowych filmów, które mają znaczenie
 *  - minRating - minimalny ranking filmów, które mogą zostać doklejone do listy
 */
int marathon(MoviePtr currentList, UserPtr currentUser, int lengthToCut, int minRating) {
    int outCode;
    UserPtr son;

    outCode = addListToList(currentList, currentUser->movies, lengthToCut, minRating);

    // Sprawdzenie, czy dodanie do listy się powiodło
    if (outCode == 1 || outCode == 3)
        return outCode;

    // Zmiana minimalnego rankingu
    if (currentUser->movies->nextMovie != NULL && currentUser->movies->nextMovie->movieRating > minRating)
        minRating = currentUser->movies->nextMovie->movieRating;

    son = currentUser->firstSon->nextBrother;
    while (son != currentUser->firstSon) {
        // Dodanie filmów od syna
        outCode = marathon(currentList, son, lengthToCut, minRating);

        // Sprawdzenie, czy operacja się powiodła
        if (outCode == 1 || outCode == 3)
            return outCode;

        son = son->nextBrother;
    }
    return 0;
}

int marathonPrint(UserPtr currentUser, int k) {
    MoviePtr marathonOutput, marathonOutBegin;
    int outCode;

    if (currentUser == NULL)
        return 1;   // Nieistniejący użytkownik

    // Stworzenie pustej listy na maraton
    marathonOutput = createDecreasingMovieList();
    // Błąd alokacji pamięci
    if (marathonOutput == NULL)
        return 3;

    // Wykonanie "maratonu" dla danego użytkownika
    outCode = marathon(marathonOutput, currentUser, k, 0);
    // Sprawdzenie, czy "maraton" się powiódł
    if (outCode != 0) {
        freeMovies(marathonOutput);
        return outCode;
    }

    // Zmienna pomocnicza do zwalniania całej pamięci
    marathonOutBegin = marathonOutput;

    // Sprawdzenie, czy istnieją filmy spełniające założenia maratonu (jeśli k = 0, to też nie istnieją, bo nic nie należy do zbioru mocy 0)
    if (marathonOutput->nextMovie == NULL)
        printf("NONE\n");
    else {
        // Wypisuje maksymalnie k filmów z listy otrzymanej po maratonie dla danego użytkownika
        while (k-- && marathonOutput->nextMovie != NULL) {
            marathonOutput = marathonOutput->nextMovie;
            printf("%d", marathonOutput->movieRating);
            if (k != 0 && marathonOutput->nextMovie != NULL)
                printf(" ");
        }
        printf("\n");
    }

    freeMovies(marathonOutBegin);
    return 0;
}
