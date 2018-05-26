#ifndef MARATHON_MOVIE_H
#define MARATHON_MOVIE_H

struct Movie;
typedef struct Movie *MoviePtr;
struct Movie {
    int movieRating;
    MoviePtr nextMovie;
};

/*
 * Stworzenie filmu o danym rankingu
 *  - newMovieRating - ranking nowego filmu
 */
MoviePtr createMovie(int newMovieRating);

/*
 * Lista filmów to "fanomowy" film z rankingiem -1
 * Ten film zawsze jest pierwszy na liście
 */
MoviePtr createDecreasingMovieList();

/*
 * Zwolnienie całej listy filmów
 *  - currentList - Lista do zwolnienia
 */
void freeMovies(MoviePtr currentList);

/*
 * Dopisanie do danej listy jednego filmu
 *  - currentList - dana lista
 *  - newMovieRating - ranking filmu do dopisania
 */
int addMovieToList(MoviePtr currentList, int newMovieRating);

/*
 * Usunięcie z danej listy danego filmu
 *  - currentMovie - aktualne widziany film z listy
 *  - newMovieRating - ranking filmu do usunięcia
 */
int delMovieFromList(MoviePtr currentMovie, int removeMovieRating);

/*
 * Dodanie do danej listy pewną liczbę filmów z drugiej listy, na pozycje nie większe od danej
 * wartości i mające ranking nie mnijszy niż dana wartość
 *  - firstList - lista, do kórej doklejamy
 *  - secondList - lista, z której doklejamy (elementy tej listy pozostają niezmodyfikowane)
 *  - maxPosition - maksymalna pozycja doklejonych filmów
 *  - minRating - minimalmny ranking rozpatrywanych filmów z drugiej listy
 */
int addListToList(MoviePtr firstList, MoviePtr secondList, int maxPosition, int minRating);

#endif //MARATHON_MOVIE_H
