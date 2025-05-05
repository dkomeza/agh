#pragma once

#include "types.h"
#include <stdbool.h> // Dla typu bool
#include <stdio.h>   // Dla FILE

void clearInputBuffer();
bool readLine(char *buffer, int size);
const char *offerTypeToString(OfferType type);

/**
 * Funkcja do odczytu rekordu z pliku na podanej pozycji (indeksie)
 * @returns true w przypadku sukcesu, false w przypadku błędu
 */
bool readRecord(FILE *file, Record *record, long index);

/**
 * Funkcja do zapisu rekordu do pliku na podanej pozycji (indeksie)
 * @returns true w przypadku sukcesu, false w przypadku błędu
 */
bool writeRecord(FILE *file, const Record *record, long index);

/**
 * Funkcja do dopisywania rekordu na końcu pliku
 * @returns true w przypadku sukcesu, false w przypadku błędu
 */
bool appendRecord(FILE *file, const Record *record);

// Funkcja do obliczania liczby rekordów w pliku
long countRecords(FILE *file);

/**
 * Automatycznie generuje następne ID na podstawie istniejących rekordów w pliku.
 */
unsigned int getNextId(FILE *file);