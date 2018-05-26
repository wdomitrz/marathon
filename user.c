#include <libio.h>  // Zawiera NULL
#include <stdlib.h> // Zawiera malloc() i free()
#include "user.h"

UserPtr *usersPointers;

/*
 * Lista użytkowników to "fanomowy" użytkownik bez filmów
 * Ten użytkownik zawsze jest pierwszy na liście
 */
UserPtr createUserList() {   // straznik stwarzany w celu ulatwienia implementacje
    UserPtr newUser = malloc(sizeof(struct User));
    if (newUser == NULL)
        return NULL;
    newUser->movies = NULL;
    newUser->prevBrother = newUser;     // na poczatku straznik jest jedynym synem, czyli swoim wlasnym lewo
    newUser->nextBrother = newUser;    // i prawostronnym bratem
    newUser->firstSon = NULL;
    return newUser;
}

UserPtr createUser(int userId) {
    UserPtr newUser = malloc(sizeof(struct User));
    if (newUser == NULL)
        return NULL;
    newUser->movies = createDecreasingMovieList();
    if (newUser->movies == NULL)
        return NULL;
    newUser->prevBrother = NULL;
    newUser->nextBrother = NULL;
    newUser->firstSon = createUserList();    // listaSynów, czyli strażnik (syn widmo)
    usersPointers[userId] = newUser;
    return newUser;
}

void freeUser(int userId) {
    UserPtr currentUser = usersIdToUsers(userId);
    if (currentUser == NULL)
        return;
    freeMovies(currentUser->movies);
    free(currentUser->firstSon);
    free(currentUser);
    usersPointers[userId] = NULL;
}

UserPtr usersIdToUsers(int userId) {
    if (userId >= 0 && userId <= MAXUSERINDEX)
        return usersPointers[userId];
    else
        return NULL;
}

int intializeUsers() {
    int i;

    //Utworzenie tablicy wrzytkowników
    usersPointers = malloc((MAXUSERINDEX + 1) * sizeof(UserPtr));
    if (usersPointers == NULL) {
        // Błąd alokacji
        return 3;
    }

    //Utworzenie użytkownika 0
    usersPointers[0] = createUser(0);
    if (usersPointers == NULL) {
        // Błąd alokacji
        free(usersPointers);
        return 3;
    }

    for (i = 1; i <= MAXUSERINDEX; i++)
        usersPointers[i] = NULL;
    return 0;
}

/*
 * Zwolnienie wszystkich użytkowników będących potomkami danego użytkownika
 */
void freeRecursive(UserPtr currentUser) {
    UserPtr son;
    if(currentUser == NULL)
        return;

    freeMovies(currentUser->movies);

    son = currentUser->firstSon->nextBrother;
    while(son != currentUser->firstSon){
        son = son->nextBrother;
        freeRecursive(son->prevBrother);
    }
    free(son);
    free(currentUser);
}

void freeAll(){
    freeRecursive(usersIdToUsers(0));
    free(usersPointers);
}