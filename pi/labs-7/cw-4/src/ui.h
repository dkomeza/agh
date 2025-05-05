#pragma once

#include "types.h"

// Funkcja wyświetlająca menu główne
void displayMenu();
// Funkcja do wyświetlania pojedynczego rekordu
void displayRecord(const Record *record);
// Funkcja do pobierania danych rekordu od użytkownika (bez ID)
bool getRecordFromUser(Record *newRecord);
