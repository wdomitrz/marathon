#ifndef MARATHON_USER_H
#define MARATHON_USER_H

#include "movie.h"

#define MAXUSERINDEX 65535

struct User;
typedef struct User *UserPtr;
struct User {
    MoviePtr movies;
    UserPtr prevBrother;
    UserPtr nextBrother;
    UserPtr firstSon;
};

/*
 * Stworzenie nowego użytkownika o danym Id
 *  - userId - dane Id nowgo użytkownika
 */
UserPtr createUser(int userId);

/*
 * Zwolnienie użytkownika o daym Id niezwalniające jego synów
 *  - userId - dane Id użytkownika
 */
void freeUser(int userId);

/*
 * Zamiana danego Id na wskaźnik na użytkownika o tym Id
 *  - userId - dane Id użytkownika
 */
UserPtr usersIdToUsers(int userId);

/*
 * Inicjalizacja tablicy wskaźników na użytkowników indeksowanej ich Id
 */
int intializeUsers();

/*
 * Zwolnienie wszystkich użytkowników, a następnie tablicy wskaźników na użytkowników
 */
void freeAll();

#endif //MARATHON_USER_H
