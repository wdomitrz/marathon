#include <libio.h>  // Zawiera NULL
#include <stdlib.h> // Zawiera malloc()
#include "movie.h"

MoviePtr createMovie(int newMovieRating) {
    MoviePtr newMovie = malloc(sizeof(struct Movie));
    if (newMovie == NULL)
        return NULL;
    newMovie->movieRating = newMovieRating;
    newMovie->nextMovie = NULL;
    return newMovie;
}

MoviePtr createDecreasingMovieList() {
    MoviePtr newMovie = malloc(sizeof(struct Movie));
    if (newMovie == NULL)
        return NULL;
    newMovie->movieRating = -1;
    newMovie->nextMovie = NULL;
    return newMovie;
}

void freeMovies(MoviePtr currentList) {
    MoviePtr nextMovie;

    while (currentList != NULL) {
        nextMovie = currentList->nextMovie;
        free(currentList);
        currentList = nextMovie;
    }
}

int addMovieToList(MoviePtr currentList, int newMovieRating) {
    MoviePtr newMovie;

    // Znlezienie miejsca do wstawienia
    while (currentList->nextMovie != NULL && currentList->nextMovie->movieRating >= newMovieRating)
        currentList = currentList->nextMovie;

    // Sprawdzenie, czy taki film już istnieje
    if (currentList->movieRating == newMovieRating)
        return 1;

    // Utworzenie nowego filmu
    newMovie = createMovie(newMovieRating);
    if (newMovie == NULL)
        return 3; // Błąd alokacji

    // Ustawienie następnika nowego filmu
    newMovie->nextMovie = currentList->nextMovie;

    // Modyfikacja następnika poprzednika nowego filmu
    currentList->nextMovie = newMovie;

    return 0;
}

int delMovieFromList(MoviePtr currentMovie, int removeMovieRating) {
    MoviePtr filmToFree;
    while (currentMovie->nextMovie != NULL && currentMovie->nextMovie->movieRating != removeMovieRating) {
        currentMovie = currentMovie->nextMovie;
    }

    // Filmu nie znaleziono
    if (currentMovie->nextMovie == NULL)
        return 1;

    // Zapamiętanie który film mamy zwolnić
    filmToFree = currentMovie->nextMovie;
    currentMovie->nextMovie = currentMovie->nextMovie->nextMovie;

    // Zwalniamy aktualnie widziany film z listy
    free(filmToFree);
    return 0;
}

int addListToList(MoviePtr firstList, MoviePtr secondList, int maxPosition, int minRating) {
    int whereAdding = 1;
    MoviePtr addedMovie;

    // Pomijamy rozpatrywanie początku listy, który ma ranking -1
    secondList = secondList->nextMovie;

    while (secondList != NULL && secondList->movieRating >= minRating && whereAdding <= maxPosition) {
        if (firstList->nextMovie != NULL && firstList->nextMovie->movieRating == secondList->movieRating)
            // Pomijanie filmów, które by się duplikowały
            secondList = secondList->nextMovie;

        else if (firstList->nextMovie != NULL && firstList->nextMovie->movieRating > secondList->movieRating) {
            // Film z pierwszej listy ma lepszy ranking, niż ten z drugiej, więc patrzymy na kolejny
            firstList = firstList->nextMovie;
            whereAdding++;

        } else {
            // firstList->nextMovie == NULL || firstList->nextMovie->movieRating < secondList->movieRating, czyli możemy dodać film
            addedMovie = createMovie(secondList->movieRating);
            if (addedMovie == NULL)
                return 3; // Błąd alokacji

            // Wpinam nowy film do listy
            addedMovie->nextMovie = firstList->nextMovie;
            firstList->nextMovie = addedMovie;

            // Patrzę na kolejny film z listy drugiej
            secondList = secondList->nextMovie;
        }
    }

    return 0;
}