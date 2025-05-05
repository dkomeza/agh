#include "ui.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> // Dla typu bool

#include "utils.h"

void displayMenu()
{
  printf("\n--- Menu Bazy Danych ---\n");
  printf("1. Dodaj nowy rekord (automatyczne ID)\n"); // Zaktualizowano opis
  printf("2. Nawiguj po rekordach (Poprzedni/Nastepny)\n");
  printf("3. Wyszukaj rekordy\n");
  printf("4. Zmien cene rekordu\n");
  printf("5. Usun rekord (logicznie)\n");
  printf("6. Wyswietl wszystkie aktywne rekordy\n");
  printf("0. Wyjscie\n");
  printf("------------------------\n");
  printf("Wybierz opcje: ");
}

void displayRecord(const Record *record)
{
  if (record == NULL)
    return;
  if (record->is_deleted)
  {
    printf("Rekord usuniety (ID: %u)\n", record->id); // %u dla unsigned int
    return;
  }
  printf("----------------------------------------\n");
  printf("ID             : %u\n", record->id);
  printf("Nazwa          : %s\n", record->name);
  printf("Rok powstania  : %d%s\n", record->year, (record->year < 0 ? " p.n.e." : ""));
  printf("Rodzaj oferty  : %s\n", offerTypeToString(record->offer_type));
  printf("Cena/Koszt     : %.2f PLN\n", record->price); // %.2f dla dwóch miejsc po przecinku
  printf("Gatunek        : %s\n", record->genre);
  printf("Autor/Tworca   : %s\n", record->author_creator);
  printf("----------------------------------------\n");
}

// Zwraca true, jeśli dane zostały poprawnie wczytane, false w przeciwnym razie.
bool getRecordFromUser(Record *newRecord)
{
  if (newRecord == NULL)
    return false;

  char buffer[256]; // Bufor pomocniczy do odczytu
  int offer_choice;
  int scan_result;

  newRecord->is_deleted = false; // Nowy rekord nie jest usunięty

  // --- Pobieranie Nazwy ---
  printf("Podaj nazwe dzieła: ");
  if (!readLine(newRecord->name, sizeof(newRecord->name)))
  {
    fprintf(stderr, "Błąd odczytu nazwy.\n");
    return false;
  }
  // Sprawdzenie czy nazwa nie jest pusta
  if (strlen(newRecord->name) == 0)
  {
    fprintf(stderr, "Błąd: Nazwa dzieła nie może być pusta.\n");
    return false;
  }

  // --- Pobieranie Roku ---
  while (true)
  {
    printf("Podaj rok powstania (liczba calkowita, np. -753 dla 753 p.n.e.): ");
    if (!readLine(buffer, sizeof(buffer)))
    {
      fprintf(stderr, "Błąd odczytu roku.\n");
      return false;
    }
    scan_result = sscanf(buffer, "%d", &newRecord->year);
    if (scan_result == 1)
    {
      char check_char;
      if (sscanf(buffer, "%d %c", &newRecord->year, &check_char) == 1)
      {
        break; // Poprawna liczba całkowita
      }
      else
      {
        fprintf(stderr, "Błąd: Wprowadzono nieprawidlowa liczbe (zawiera dodatkowe znaki). Sprobuj ponownie.\n");
      }
    }
    else
    {
      fprintf(stderr, "Błąd: Wprowadzono nieprawidlowa liczbe. Sprobuj ponownie.\n");
    }
  }

  // --- Pobieranie Rodzaju Oferty ---
  printf("Wybierz rodzaj oferty:\n");
  printf("  1. Sprzedaz\n");
  printf("  2. Wypozyczenie\n");
  while (true)
  {
    printf("Twoj wybor: ");
    if (!readLine(buffer, sizeof(buffer)))
    {
      fprintf(stderr, "Błąd odczytu wyboru oferty.\n");
      return false;
    }
    scan_result = sscanf(buffer, "%d", &offer_choice);
    if (scan_result == 1 && offer_choice >= 1 && offer_choice <= 3)
    {
      char check_char;
      if (sscanf(buffer, "%d %c", &offer_choice, &check_char) == 1)
      {
        break; // Poprawny wybór
      }
      else
      {
        fprintf(stderr, "Błąd: Nieprawidlowy wybor (dodatkowe znaki). Wybierz 1, 2 lub 3.\n");
      }
    }
    else
    {
      fprintf(stderr, "Błąd: Nieprawidlowy wybor. Wybierz 1, 2 lub 3.\n");
    }
  }
  newRecord->offer_type = (OfferType)offer_choice; // Rzutowanie na enum

  // --- Pobieranie Ceny ---
  while (true)
  {
    printf("Podaj koszt/cene w PLN (np. 19.99): ");
    if (!readLine(buffer, sizeof(buffer)))
    {
      fprintf(stderr, "Błąd odczytu ceny.\n");
      return false;
    }
    scan_result = sscanf(buffer, "%lf", &newRecord->price); // %lf dla double
    if (scan_result == 1 && newRecord->price >= 0)
    {
      char check_char;
      if (sscanf(buffer, "%lf %c", &newRecord->price, &check_char) == 1)
      {
        break; // Poprawna cena
      }
      else
      {
        fprintf(stderr, "Błąd: Wprowadzono nieprawidlowa cene (dodatkowe znaki). Musi byc liczba nieujemna. Sprobuj ponownie.\n");
      }
    }
    else
    {
      fprintf(stderr, "Błąd: Wprowadzono nieprawidlowa cene. Musi byc liczba nieujemna. Sprobuj ponownie.\n");
    }
  }

  // --- Pobieranie Gatunku ---
  printf("Podaj gatunek/rodzaj (np. Dramat, Obraz olejny): ");
  if (!readLine(newRecord->genre, sizeof(newRecord->genre)))
  {
    fprintf(stderr, "Błąd odczytu gatunku.\n");
    return false;
  }
  if (strlen(newRecord->genre) == 0)
    printf("Informacja: Gatunek pozostawiono pusty.\n");

  // --- Pobieranie Autora/Twórcy ---
  printf("Podaj autora/tworce (np. Leonardo da Vinci): ");
  if (!readLine(newRecord->author_creator, sizeof(newRecord->author_creator)))
  {
    fprintf(stderr, "Błąd odczytu autora/tworcy.\n");
    return false;
  }
  if (strlen(newRecord->author_creator) == 0)
  {
    printf("Informacja: Autor/Tworca pozostawiono pusty.\n");
  }

  return true; // Wszystkie dane (oprócz ID) wczytane poprawnie
}
