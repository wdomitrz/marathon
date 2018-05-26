#!/bin/bash

# Aby testować z valgrindem należy zmienić false na true.
# UWAGA! Znacznie spowalnia to działanie skryptu
VALGRIND=false

prog=$1
dir=$2

if [[ -z  ${prog}  ]] || [ ! -f ${prog} ]
then
    echo "Proszę podać nazwę istniejącego programu!"
else
    touch out.myout
    touch err.myerr
    liczbaUdanych=0
    liczbaNieudanych=0
    for file in ${dir}/*.in
    do
        if [ -f ${file} ]
        then
            ./${prog} < ${file} > out.myout 2> err.myerr
            kod=$?
            if ${VALGRIND}
            then
                valgrind --error-exitcode=15 --leak-check=full --show-leak-kinds=all --errors-for-leak-kinds=all ./${prog} < ${file} > /dev/null 2> /dev/null
                pamiec=$?
                if diff -B out.myout ${file%in}out >/dev/null && diff -B err.myerr ${file%in}err >/dev/null && [ ${kod} -eq 0 ] && [ ! ${pamiec} -eq 15 ]
                then
                    Udane[liczbaUdanych]="Plik: ${file};  Kod: ${kod}; Brak przecieku pamięci!!!"
                    ((liczbaUdanych++))
                else
                    if [ ${pamiec} -eq 15 ]
                    then
                        Nieudane[liczbaNieudanych]="Plik: ${file};    Kod: ${kod}; Wykryto przeciek pamięci!!!"
                    else
                        Nieudane[liczbaNieudanych]="Plik: ${file};    Kod: ${kod}; Brak przecieku pamięci!!!"
                    fi
                    ((liczbaNieudanych++))
                fi
            else
                if diff -B out.myout ${file%in}out >/dev/null && diff -B err.myerr ${file%in}err >/dev/null && [ ${kod} -eq 0 ]
                then
                    Udane[liczbaUdanych]="Plik: ${file};  Kod: ${kod};"
                    ((liczbaUdanych++))

                else
                    Nieudane[liczbaNieudanych]="Plik: ${file};    Kod: ${kod};"
                    ((liczbaNieudanych++))
                fi
            fi
        fi
    done
    rm out.myout err.myerr
    if [ ${liczbaUdanych} -eq 0 ]
    then
        echo "Brak testów udanych."
    else

        if $VALGRIND
        then
            echo "Lista testów udanych z kodami wyjścia, bez przecieku pamięci:"
        else
            echo "Lista testów udanych z kodami wyjścia:"
        fi

        for i in "${Udane[@]}";
        do
            echo $i
        done
    fi

    if [ ${liczbaNieudanych} -eq 0 ]
    then
        if $VALGRIND
        then
            echo "Brak testów nieudanych (do testów nieudanych wliczam te z przeciekami pamięci)"
        else
            echo "Brak testów nieudanych"
        fi
    else
        if $VALGRIND
        then
            echo "Lista testów nieudanych z kodami wyjścia (do testów nieudanych wliczam te z przeciekami pamięci):"
        else
            echo "Lista testów nieudanych z kodami wyjścia:"
        fi
        for i in "${Nieudane[@]}";
        do
            echo $i
        done
    fi

fi
