#ifndef MARATHON_MARATHONINPUT_H
#define MARATHON_MARATHONINPUT_H

#define MAXINPUTLENGTH (8 + 1 + 10 + 1 + 10 + 1)

/*
 * Funkcja obsługuje wejścia programu czytając jedną linię.
 * Zwraca 1 jeśli napotkała znak EOF, w przeciwnym przypadku zwraca 0.
 * Używane jest:
 *  - line - miejsce w pamięci, gdzie wejście wczytywane jest znak po znaku
 *  - operation - miejsce na operację. Możliwe operacje to:
 *      "#"
 *      "error"
 *      Operacje zawarte w treści zadania
 *      Dowolna inna operacja podana na wejściu zadania (interpretowana jak "error")
 *  - firstParam - miejsce na ustawienie pierwszego parametru, jeśli taki jest potrzebny
 *  - secondParam - miejsce na ustawienie drugiego parametru, jeśli taki jest potrzebny
 */
int getMarathonLine(char *line, char *operation, int *firstParam, int *secondParam);

#endif //MARATHON_MARATHONINPUT_H
