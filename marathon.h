#ifndef MARATHON_MARATHON_H
#define MARATHON_MARATHON_H

#include "user.h"

/*
 * Dodanie filmu do listy danego użytkownika
 *  - currentUser - użytkownik, do którego listy ma być dodany film
 *  - movieRating - ranking filmu do dodania
 */
int addMovie(UserPtr currentUser, int newMovieRating);

/*
 * Usunięcie filmu z listy danego użytkownika
 *  - currentUser - użytkownik, z którego listy ma być usunięty film
 *  - movieRating - ranking filmu do usunięcia
 */
int delMovie(UserPtr currentUser, int removeMovieRating);

/*
 * Dodanie nowego użytkownika przez danego użytkownika
 *  - currentUser - użytkownik dodający
 *  - userId - Id użytkownika dodawanego
 */
int addUser(UserPtr currentUser, int userId);

/*
 * Usunięcie użytkownika o podanym Id
 *  - userId - Id użytkownika dodawanego
 */
int delUser(int userId);

/*
 * Zrobienie operacji maraton zawierające w sobi wypisywanie
 *  - currentUser - użytkownik od którego robimy maraton
 *  - k - liczba filmów do maratonu
 */
int marathonPrint(UserPtr currentUser, int k);

#endif //MARATHON_MARATHON_H
