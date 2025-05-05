#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> // Dla typu bool i wartości true/false
#include <ctype.h>   // Dla funkcji tolower
#include <limits.h>  // Dla LONG_MAX (chociaż ftell zwraca long)

#include "types.h" // Definicje struktur i typów
#include "utils.h"
#include "ui.h"

// Stała definiująca nazwę pliku bazy danych
const char *FILENAME = "db";

// Funkcja do dodawania nowych rekordów
void addNewRecords(FILE *file)
{
  char continue_adding = 't';
  Record newRecord; // Jeden rekord w pamięci

  while (continue_adding == 't' || continue_adding == 'T')
  {
    printf("\n--- Dodawanie nowego rekordu ---\n");

    // Pobierz dane od użytkownika (bez ID)
    if (getRecordFromUser(&newRecord))
    {
      // Wygeneruj następne ID
      unsigned int next_id = getNextId(file);
      if (next_id == 0)
      { // Sprawdzenie błędu z getNextId (np. przepełnienie)
        fprintf(stderr, "Błąd krytyczny: Nie mozna wygenerowac nowego ID. Dodawanie rekordu przerwane.\n");
        break; // Przerwij pętlę dodawania
      }
      newRecord.id = next_id; // Przypisz wygenerowane ID

      // Zapisz kompletny rekord (z ID) do pliku
      if (appendRecord(file, &newRecord))
      {
        printf("Rekord pomyslnie dodany do pliku (ID: %u).\n", newRecord.id); // Pokaż użytkownikowi przydzielone ID
      }
      else
      {
        fprintf(stderr, "Błąd: Nie udalo sie zapisac rekordu do pliku.\n");
      }
    }
    else
    {
      fprintf(stderr, "Anulowano dodawanie rekordu z powodu bledu wprowadzania.\n");
      break;
    }

    printf("\nCzy chcesz dodac kolejny rekord? (T/N): ");
    int choice_char = getchar(); // Odczytaj znak
    continue_adding = (char)choice_char;
    if (choice_char != '\n' && choice_char != EOF)
    {
      clearInputBuffer();
    }
  }
}

// Funkcja do nawigacji po rekordach
void navigateRecords(FILE *file)
{
  long total_records = countRecords(file);
  if (total_records <= 0)
  {
    if (total_records == 0)
      printf("Baza danych jest pusta. Nie ma rekordow do nawigacji.\n");
    else
      fprintf(stderr, "Błąd odczytu liczby rekordow.\n");
    return;
  }

  long current_index = -1; // Zacznij od -1, aby pętla szukająca znalazła pierwszy
  Record currentRecord;    // Jeden rekord w pamięci
  bool record_displayed = false;

  // Znajdź pierwszy nieusunięty rekord
  long search_index = 0;
  while (search_index < total_records)
  {
    if (readRecord(file, &currentRecord, search_index))
    {
      if (!currentRecord.is_deleted)
      {
        current_index = search_index; // Znaleziono pierwszy aktywny
        printf("\n--- Aktualny Rekord (%ld/%ld) ---\n", current_index + 1, total_records);
        displayRecord(&currentRecord);
        record_displayed = true;
        break;
      }
    }
    else
    {
      fprintf(stderr, "Błąd odczytu rekordu na pozycji %ld podczas szukania pierwszego rekordu.\n", search_index);
      // Można przerwać lub kontynuować
    }
    search_index++;
  }

  if (!record_displayed)
  {
    printf("Nie znaleziono zadnych aktywnych rekordow do wyswietlenia.\n");
    return;
  }

  while (true)
  {
    printf("\nNawigacja: [P]oprzedni, [N]astepny, [W]yjscie: ");
    int choice_char = getchar();
    char choice = (char)choice_char;
    if (choice_char != '\n' && choice_char != EOF)
    {
      clearInputBuffer();
    }

    if (choice == 'p' || choice == 'P')
    {
      long prev_index = current_index - 1;
      bool found_prev = false;
      while (prev_index >= 0)
      {
        if (readRecord(file, &currentRecord, prev_index))
        {
          if (!currentRecord.is_deleted)
          {
            current_index = prev_index;
            printf("\n--- Poprzedni Rekord (%ld/%ld) ---\n", current_index + 1, total_records);
            displayRecord(&currentRecord);
            found_prev = true;
            break;
          }
        }
        else
        {
          fprintf(stderr, "Błąd odczytu rekordu na pozycji %ld podczas szukania poprzedniego.\n", prev_index);
        }
        prev_index--;
      }
      if (!found_prev)
      {
        printf("Jestes na pierwszym aktywnym rekordzie.\n");
      }
    }
    else if (choice == 'n' || choice == 'N')
    {
      long next_index = current_index + 1;
      bool found_next = false;
      while (next_index < total_records)
      {
        if (readRecord(file, &currentRecord, next_index))
        {
          if (!currentRecord.is_deleted)
          {
            current_index = next_index;
            printf("\n--- Nastepny Rekord (%ld/%ld) ---\n", current_index + 1, total_records);
            displayRecord(&currentRecord);
            found_next = true;
            break;
          }
        }
        else
        {
          fprintf(stderr, "Błąd odczytu rekordu na pozycji %ld podczas szukania nastepnego.\n", next_index);
        }
        next_index++;
      }
      if (!found_next)
      {
        printf("Jestes na ostatnim aktywnym rekordzie.\n");
      }
    }
    else if (choice == 'w' || choice == 'W')
    {
      break; // Wyjście z nawigacji
    }
    else
    {
      printf("Nieprawidlowa opcja.\n");
    }
  }
}

// Funkcja do wyszukiwania rekordów
void searchRecords(FILE *file)
{
  long total_records = countRecords(file);
  if (total_records <= 0)
  {
    if (total_records == 0)
      printf("Baza danych jest pusta. Nie mozna wyszukiwac.\n");
    else
      fprintf(stderr, "Błąd odczytu liczby rekordow.\n");
    return;
  }

  printf("\n--- Wyszukiwanie Rekordow ---\n");
  printf("Wybierz kryterium wyszukiwania:\n");
  printf("  1. Identyfikator (dziesietnie)\n"); // Zmieniono opis na dziesiętny
  printf("  2. Fragment nazwy\n");
  printf("  3. Dostepny budzet (cena <= budzet)\n");

  int choice;
  char buffer[256];
  int scan_result;

  while (true)
  {
    printf("Twoj wybor: ");
    if (!readLine(buffer, sizeof(buffer)))
    {
      fprintf(stderr, "Błąd odczytu wyboru kryterium.\n");
      return;
    }
    scan_result = sscanf(buffer, "%d", &choice);
    if (scan_result == 1 && choice >= 1 && choice <= 3)
    {
      char check_char;
      if (sscanf(buffer, "%d %c", &choice, &check_char) == 1)
        break;
      else
        fprintf(stderr, "Błąd: Nieprawidlowy wybor (dodatkowe znaki). Wybierz 1, 2 lub 3.\n");
    }
    else
    {
      fprintf(stderr, "Błąd: Nieprawidlowy wybor. Wybierz 1, 2 lub 3.\n");
    }
  }

  Record currentRecord; // Jeden rekord w pamięci
  bool found = false;
  long found_count = 0;

  switch (choice)
  {
  case 1:
  { // Wyszukiwanie po ID (teraz dziesiętnie)
    unsigned int search_id;
    printf("Podaj ID do wyszukania (liczba dziesietna): ");
    while (true)
    {
      if (!readLine(buffer, sizeof(buffer)))
      {
        fprintf(stderr, "Błąd odczytu ID do wyszukania.\n");
        return;
      }
      // Użyj %u dla unsigned int
      scan_result = sscanf(buffer, "%u", &search_id);
      if (scan_result == 1)
      {
        // Prosta walidacja - czy są tylko cyfry
        size_t len = strlen(buffer);
        bool valid_dec = true;
        for (size_t i = 0; i < len; ++i)
        {
          if (!isdigit(buffer[i]))
          {
            valid_dec = false;
            break;
          }
        }
        if (valid_dec)
          break;
        else
          fprintf(stderr, "Błąd: Wprowadzono nieprawidlowe znaki (oczekiwano liczby dziesietnej). Sprobuj ponownie.\n");
      }
      else
      {
        fprintf(stderr, "Błąd: Nieprawidlowy format liczby dziesietnej. Sprobuj ponownie.\n");
      }
    }

    for (long i = 0; i < total_records; ++i)
    {
      if (readRecord(file, &currentRecord, i))
      {
        // Sprawdzamy również usunięte, bo użytkownik może chcieć znaleźć usunięty po ID
        if (currentRecord.id == search_id)
        {
          if (!found)
            printf("\nZnaleziono rekord(y):\n");
          displayRecord(&currentRecord); // Wyświetli info, że usunięty, jeśli tak jest
          found = true;
          found_count++;
          // Zwykle ID jest unikalne, więc można dodać break;
          // break;
        }
      }
      else
      {
        fprintf(stderr, "Błąd odczytu rekordu na pozycji %ld podczas wyszukiwania po ID.\n", i);
      }
    }
    break;
  }
  case 2:
  { // Wyszukiwanie po fragmencie nazwy (bez zmian)
    char name_fragment[100];
    printf("Podaj fragment nazwy do wyszukania: ");
    if (!readLine(name_fragment, sizeof(name_fragment)))
    {
      fprintf(stderr, "Błąd odczytu fragmentu nazwy.\n");
      return;
    }
    if (strlen(name_fragment) == 0)
    {
      printf("Wyszukiwany fragment nazwy jest pusty. Przerywanie wyszukiwania.\n");
      return;
    }

    // Konwersja fragmentu do małych liter
    char lower_fragment[100];
    strncpy(lower_fragment, name_fragment, sizeof(lower_fragment) - 1);
    lower_fragment[sizeof(lower_fragment) - 1] = '\0';
    for (int k = 0; lower_fragment[k]; k++)
    {
      lower_fragment[k] = tolower(lower_fragment[k]);
    }

    for (long i = 0; i < total_records; ++i)
    {
      if (readRecord(file, &currentRecord, i))
      {
        if (!currentRecord.is_deleted)
        {
          char lower_record_name[100];
          strncpy(lower_record_name, currentRecord.name, sizeof(lower_record_name) - 1);
          lower_record_name[sizeof(lower_record_name) - 1] = '\0';
          for (int k = 0; lower_record_name[k]; k++)
          {
            lower_record_name[k] = tolower(lower_record_name[k]);
          }

          if (strstr(lower_record_name, lower_fragment) != NULL)
          {
            if (!found)
              printf("\nZnalezione rekordy:\n");
            displayRecord(&currentRecord);
            found = true;
            found_count++;
          }
        }
      }
      else
      {
        fprintf(stderr, "Błąd odczytu rekordu na pozycji %ld podczas wyszukiwania po nazwie.\n", i);
      }
    }
    break;
  }
  case 3:
  { // Wyszukiwanie po budżecie (bez zmian)
    double budget;
    printf("Podaj dostepny budzet (PLN): ");
    while (true)
    {
      if (!readLine(buffer, sizeof(buffer)))
      {
        fprintf(stderr, "Błąd odczytu budzetu.\n");
        return;
      }
      scan_result = sscanf(buffer, "%lf", &budget);
      if (scan_result == 1 && budget >= 0)
      {
        char check_char;
        if (sscanf(buffer, "%lf %c", &budget, &check_char) == 1)
          break;
        else
          fprintf(stderr, "Błąd: Nieprawidlowy budzet (dodatkowe znaki). Musi byc liczba nieujemna. Sprobuj ponownie.\n");
      }
      else
      {
        fprintf(stderr, "Błąd: Nieprawidlowy budzet. Musi byc liczba nieujemna. Sprobuj ponownie.\n");
      }
    }

    for (long i = 0; i < total_records; ++i)
    {
      if (readRecord(file, &currentRecord, i))
      {
        if (!currentRecord.is_deleted && currentRecord.price <= budget)
        {
          if (!found)
            printf("\nZnalezione rekordy (cena <= %.2f PLN):\n", budget);
          displayRecord(&currentRecord);
          found = true;
          found_count++;
        }
      }
      else
      {
        fprintf(stderr, "Błąd odczytu rekordu na pozycji %ld podczas wyszukiwania po budzecie.\n", i);
      }
    }
    break;
  }
  }

  if (!found)
  {
    printf("Nie znaleziono rekordow spelniajacych podane kryteria.\n");
  }
  else
  {
    printf("\nZnaleziono lacznie: %ld rekord(ow).\n", found_count);
  }
}

// Funkcja do korygowania ceny rekordu (wyszukiwanie po ID dziesiętnym)
void updatePrice(FILE *file)
{
  long total_records = countRecords(file);
  if (total_records <= 0)
  {
    if (total_records == 0)
      printf("Baza danych jest pusta. Nie mozna modyfikowac rekordow.\n");
    else
      fprintf(stderr, "Błąd odczytu liczby rekordow.\n");
    return;
  }

  printf("\n--- Korygowanie Ceny Rekordu ---\n");
  unsigned int search_id;
  char buffer[256];
  int scan_result;

  printf("Podaj ID rekordu, ktorego cene chcesz zmienic (liczba dziesietna): ");
  while (true)
  {
    if (!readLine(buffer, sizeof(buffer)))
    {
      fprintf(stderr, "Błąd odczytu ID do modyfikacji.\n");
      return;
    }
    scan_result = sscanf(buffer, "%u", &search_id);
    if (scan_result == 1)
    {
      size_t len = strlen(buffer);
      bool valid_dec = true;
      for (size_t i = 0; i < len; ++i)
      {
        if (!isdigit(buffer[i]))
        {
          valid_dec = false;
          break;
        }
      }
      if (valid_dec)
        break;
      else
        fprintf(stderr, "Błąd: Wprowadzono nieprawidlowe znaki (oczekiwano liczby dziesietnej). Sprobuj ponownie.\n");
    }
    else
    {
      fprintf(stderr, "Błąd: Nieprawidlowy format liczby dziesietnej. Sprobuj ponownie.\n");
    }
  }

  Record currentRecord; // Rekord w pamięci
  long record_index = -1;

  // Znajdź indeks rekordu
  for (long i = 0; i < total_records; ++i)
  {
    if (readRecord(file, &currentRecord, i))
    {
      // Szukamy tylko wśród nieusuniętych rekordów do modyfikacji
      if (!currentRecord.is_deleted && currentRecord.id == search_id)
      {
        record_index = i;
        break; // Znaleziono rekord
      }
    }
    else
    {
      fprintf(stderr, "Błąd odczytu rekordu na pozycji %ld podczas wyszukiwania do modyfikacji.\n", i);
    }
  }

  if (record_index == -1)
  {
    // Sprawdźmy jeszcze, czy rekord o tym ID istnieje, ale jest usunięty
    bool exists_but_deleted = false;
    for (long i = 0; i < total_records; ++i)
    {
      if (readRecord(file, &currentRecord, i))
      {
        if (currentRecord.is_deleted && currentRecord.id == search_id)
        {
          exists_but_deleted = true;
          break;
        }
      }
    }
    if (exists_but_deleted)
    {
      printf("Rekord o podanym ID [%u] istnieje, ale jest oznaczony jako usuniety. Nie mozna modyfikowac.\n", search_id);
    }
    else
    {
      printf("Nie znaleziono aktywnego rekordu o podanym ID [%u].\n", search_id);
    }
    return;
  }

  // Wyświetl aktualny rekord (mamy go już w currentRecord po znalezieniu indeksu)
  printf("\nZnaleziono rekord do modyfikacji:\n");
  // Trzeba go ponownie odczytać, bo pętla sprawdzająca usunięte mogła go nadpisać
  if (!readRecord(file, &currentRecord, record_index))
  {
    fprintf(stderr, "Krytyczny Błąd: Nie mozna odczytac rekordu [%u] do modyfikacji po znalezieniu.\n", search_id);
    return;
  }
  displayRecord(&currentRecord);

  // Pobierz nową cenę
  double new_price;
  printf("Podaj nowa cene/koszt w PLN: ");
  while (true)
  {
    if (!readLine(buffer, sizeof(buffer)))
    {
      fprintf(stderr, "Błąd odczytu nowej ceny.\n");
      return;
    }
    scan_result = sscanf(buffer, "%lf", &new_price);
    if (scan_result == 1 && new_price >= 0)
    {
      char check_char;
      if (sscanf(buffer, "%lf %c", &new_price, &check_char) == 1)
        break;
      else
        fprintf(stderr, "Błąd: Wprowadzono nieprawidlowa cene (dodatkowe znaki). Musi byc liczba nieujemna. Sprobuj ponownie.\n");
    }
    else
    {
      fprintf(stderr, "Błąd: Wprowadzono nieprawidlowa cene. Musi byc liczba nieujemna. Sprobuj ponownie.\n");
    }
  }

  // Zaktualizuj cenę w strukturze w pamięci
  currentRecord.price = new_price;

  // Zapisz zmodyfikowany rekord z powrotem do pliku na właściwej pozycji
  if (writeRecord(file, &currentRecord, record_index))
  {
    printf("Cena rekordu pomyslnie zaktualizowana.\n");
  }
  else
  {
    fprintf(stderr, "Błąd: Nie udalo sie zapisac zmian w pliku.\n");
  }
}

// Funkcja do "usuwania" rekordu (wyszukiwanie po ID)
// Rekord nie jest fizycznie usuwany, tylko oznaczany jako usunięty
void deleteRecord(FILE *file)
{
  long total_records = countRecords(file);
  if (total_records <= 0)
  {
    if (total_records == 0)
      printf("Baza danych jest pusta. Nie mozna usuwac rekordow.\n");
    else
      fprintf(stderr, "Błąd odczytu liczby rekordow.\n");
    return;
  }

  printf("\n--- Usuwanie Rekordu (Logiczne) ---\n");
  unsigned int search_id;
  char buffer[256];
  int scan_result;

  printf("Podaj ID rekordu, ktory chcesz usunac (liczba dziesietna): ");
  while (true)
  {
    if (!readLine(buffer, sizeof(buffer)))
    {
      fprintf(stderr, "Błąd odczytu ID do usuniecia.\n");
      return;
    }
    scan_result = sscanf(buffer, "%u", &search_id);
    if (scan_result == 1)
    {
      size_t len = strlen(buffer);
      bool valid_dec = true;
      for (size_t i = 0; i < len; ++i)
      {
        if (!isdigit(buffer[i]))
        {
          valid_dec = false;
          break;
        }
      }
      if (valid_dec)
        break;
      else
        fprintf(stderr, "Błąd: Wprowadzono nieprawidlowe znaki (oczekiwano liczby dziesietnej). Sprobuj ponownie.\n");
    }
    else
    {
      fprintf(stderr, "Błąd: Nieprawidlowy format liczby dziesietnej. Sprobuj ponownie.\n");
    }
  }

  Record currentRecord; // Rekord w pamięci
  long record_index = -1;

  // Znajdź indeks rekordu
  for (long i = 0; i < total_records; ++i)
  {
    if (readRecord(file, &currentRecord, i))
    {
      // Szukamy tylko wśród nieusuniętych rekordów do usunięcia
      if (!currentRecord.is_deleted && currentRecord.id == search_id)
      {
        record_index = i;
        break; // Znaleziono rekord
      }
    }
    else
    {
      fprintf(stderr, "Błąd odczytu rekordu na pozycji %ld podczas wyszukiwania do usuniecia.\n", i);
    }
  }

  if (record_index == -1)
  {
    // Sprawdźmy jeszcze, czy rekord o tym ID istnieje, ale jest już usunięty
    bool exists_but_deleted = false;
    for (long i = 0; i < total_records; ++i)
    {
      if (readRecord(file, &currentRecord, i))
      {
        if (currentRecord.is_deleted && currentRecord.id == search_id)
        {
          exists_but_deleted = true;
          break;
        }
      }
    }
    if (exists_but_deleted)
    {
      printf("Rekord o podanym ID [%u] jest juz oznaczony jako usuniety.\n", search_id);
    }
    else
    {
      printf("Nie znaleziono aktywnego rekordu o podanym ID [%u].\n", search_id);
    }
    return;
  }

  // Wyświetl rekord przed usunięciem (mamy go w currentRecord)
  printf("\nZnaleziono rekord do usuniecia:\n");
  // Ponowny odczyt dla pewności
  if (!readRecord(file, &currentRecord, record_index))
  {
    fprintf(stderr, "Krytyczny Błąd: Nie mozna odczytac rekordu [%u] do usuniecia po znalezieniu.\n", search_id);
    return;
  }
  displayRecord(&currentRecord);

  printf("Czy na pewno chcesz usunac ten rekord? (T/N): ");
  int choice_char = getchar();
  char confirm = (char)choice_char;
  if (choice_char != '\n' && choice_char != EOF)
  {
    clearInputBuffer();
  }

  if (confirm == 't' || confirm == 'T')
  {
    // Oznacz rekord jako usunięty w pamięci
    currentRecord.is_deleted = true;

    // Zapisz zmodyfikowany rekord z powrotem do pliku
    if (writeRecord(file, &currentRecord, record_index))
    {
      printf("Rekord pomyslnie oznaczony jako usuniety.\n");
    }
    else
    {
      fprintf(stderr, "Błąd: Nie udalo sie zapisac zmian w pliku.\n");
    }
  }
  else
  {
    printf("Usuwanie anulowane.\n");
  }
}

// Funkcja do wyświetlania wszystkich aktywnych rekordów
void listAllRecords(FILE *file)
{
  long total_records = countRecords(file);
  if (total_records <= 0)
  {
    if (total_records == 0)
      printf("Baza danych jest pusta.\n");
    else
      fprintf(stderr, "Błąd odczytu liczby rekordow.\n");
    return;
  }

  printf("\n--- Lista Wszystkich Aktywnych Rekordow ---\n");
  Record currentRecord; // Rekord w pamięci
  long active_count = 0;

  // Zapamiętaj pozycję, na wszelki wypadek gdyby readRecord ją zmieniał
  long original_pos = ftell(file);

  for (long i = 0; i < total_records; ++i)
  {
    if (readRecord(file, &currentRecord, i))
    {
      if (!currentRecord.is_deleted)
      {
        displayRecord(&currentRecord);
        active_count++;
      }
    }
    else
    {
      fprintf(stderr, "Błąd odczytu rekordu na pozycji %ld. Pomijanie.\n", i);
      // Jeśli wystąpił błąd odczytu, pozycja w pliku może być nieprawidłowa.
      // Spróbujmy ją przywrócić, aby kontynuować od następnego rekordu.
      // To jest próba ratunku, może nie zadziałać idealnie.
      long expected_pos = (i + 1) * sizeof(Record);
      if (fseek(file, expected_pos, SEEK_SET) != 0)
      {
        fprintf(stderr, "Nie udalo sie przywrocic pozycji pliku po bledzie odczytu. Przerywanie listowania.\n");
        break; // Przerwij listowanie, jeśli nie można odzyskać pozycji
      }
    }
  }

  // Przywróć oryginalną pozycję pliku
  if (original_pos != -1L)
  {
    fseek(file, original_pos, SEEK_SET);
  }

  if (active_count == 0)
  {
    printf("Brak aktywnych rekordow w bazie danych.\n");
  }
  else
  {
    printf("Wyswietlono %ld aktywnych rekordow.\n", active_count);
  }
}

// --- Główna funkcja programu ---
int main()
{
  FILE *dataFile; // Wskaźnik do pliku

  // Spróbuj otworzyć plik w trybie do odczytu i zapisu binarnego ("r+b")
  dataFile = fopen(FILENAME, "r+b");

  if (dataFile == NULL)
  {
    // Jeśli plik nie istnieje, otwórz go w trybie "w+b" (utworzy plik)
    // perror("Informacja: Nie mozna otworzyc pliku w trybie r+b, proba otwarcia w w+b");
    printf("Informacja: Plik '%s' nie istnieje lub nie mozna go otworzyc do odczytu/zapisu. Tworzenie nowego pliku.\n", FILENAME);
    dataFile = fopen(FILENAME, "w+b"); // Utwórz plik

    if (dataFile == NULL)
    {
      perror("Krytyczny Błąd: Nie mozna otworzyc ani utworzyc pliku bazy danych");
      return 1; // Zakończ program z kodem błędu
    }
    printf("Informacja: Utworzono nowy plik bazy danych '%s'.\n", FILENAME);
  }
  else
  {
    printf("Informacja: Otworzono istniejacy plik bazy danych '%s'.\n", FILENAME);
  }

  int choice;
  char buffer[20]; // Bufor do odczytu wyboru menu

  do
  {
    displayMenu();
    if (!readLine(buffer, sizeof(buffer)))
    {
      // Jeśli readLine zwróci false i jest EOF, to zakończ pętlę
      if (feof(stdin))
      {
        printf("\nOsiagnieto koniec wejscia (EOF). Zamykanie programu...\n");
        choice = 0; // Ustaw na wyjście
      }
      else
      {
        fprintf(stderr, "Błąd odczytu opcji menu. Ponow probe.\n");
        choice = -1; // Ustaw nieprawidłową wartość, aby kontynuować pętlę
      }
      continue;
    }

    // Sprawdź, czy wczytano pustą linię
    if (strlen(buffer) == 0)
    {
      choice = -1; // Traktuj pustą linię jako nieprawidłowy wybór
    }
    else if (sscanf(buffer, "%d", &choice) != 1)
    {
      choice = -1; // Nie udało się sparsować liczby
    }

    switch (choice)
    {
    case 1:
      addNewRecords(dataFile);
      break;
    case 2:
      navigateRecords(dataFile);
      break;
    case 3:
      searchRecords(dataFile);
      break;
    case 4:
      updatePrice(dataFile);
      break;
    case 5:
      deleteRecord(dataFile);
      break;
    case 6:
      listAllRecords(dataFile);
      break;
    case 0:
      printf("Zamykanie programu...\n");
      break;
    default:
      printf("Nieprawidlowa opcja. Sprobuj ponownie.\n");
    }
  } while (choice != 0);

  // Zamknij plik przed zakończeniem programu
  if (fclose(dataFile) != 0)
  {
    perror("Błąd podczas zamykania pliku");
    // Mimo błędu zamknięcia, program i tak się zakończy
    return 1; // Zwróć błąd
  }

  printf("Program zakonczony pomyslnie.\n");
  return 0; // Zakończ program pomyślnie
}
