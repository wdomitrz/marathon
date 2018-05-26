# Definicje makr
INCLUDE_MAIN=input-output.h generator.h
CC=gcc
OBJ=.o
EXE=
SRC=.c
CFLAGS=-Wall -Wextra -std=c11 -O2
SRCS_MAIN=movie.c user.c marathon.c marathoninput.c main.c
LDFLAGS=-Wall -Wextra

.PHONY: all clean cleano

# Domyślnie wykonywane jest pierwsze polecenie
all: $(SRCS_MAIN:$(SRC)=$(OBJ)) main

# Polecenie czyszczenia
clean:
	@echo "Usuwamy pliki .o"
	-rm *$(OBJ)
	@echo "Usuwamy plik wykonywalny"
	-rm main

# Polecenie czyszczenia bez pliku wykonywalnego
cleano:
	@echo "Usuwamy pliki .o"
	rm *$(OBJ)

# Kompilator (.c,.h->.o)
$(SRC)$(OBJ): $*$(SRC)
	$(CC) $(CFLAGS) -c $<

# Linker (.o->exec)
main: $(SRCS_MAIN:$(SRC)=$(OBJ))
	$(CC) $(LDFLAGS) -o main $^

# Zależności dla różnych plików
main.o: main.c marathon.h
marathoninput: marathoninput.c marathoninput.h
marathon.o: marathon.c marathon.h user.h movie.h
user.o: user.c user.h movie.h
movie.o: movie.c movie.h