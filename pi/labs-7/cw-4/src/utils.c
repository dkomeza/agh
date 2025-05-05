#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

// Funkcja do czyszczenia bufora wejściowego
void clearInputBuffer()
{
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}

bool readLine(char *buffer, int size)
{
  if (fgets(buffer, size, stdin) != NULL)
  {
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n')
    {
      buffer[len - 1] = '\0';
    }
    else
    {
      if (!feof(stdin))
        clearInputBuffer();
    }
    return true;
  }
  if (!feof(stdin))
  {
    clearInputBuffer();
    return false;
  }
  return false;
}

const char *offerTypeToString(OfferType type)
{
  switch (type)
  {
  case SALE:
    return "Sprzedaz";
  case RENT:
    return "Wypozyczenie";
  default:
    return "Nieznany";
  }
}

bool readRecord(FILE *file, Record *record, long index)
{
  if (file == NULL || record == NULL || index < 0)
    return false;

  long offset = index * sizeof(Record);

  if (fseek(file, offset, SEEK_SET) != 0)
    return false; // Błąd przy ustawianiu pozycji

  size_t items_read = fread(record, sizeof(Record), 1, file);
  if (items_read == 1)
    return true;
  else
  {
    if (feof(file))
      perror("Rekord nie został odczytany w całości (fread)");
    else if (ferror(file))
      perror("Błąd podczas odczytu rekordu z pliku (fread)");
    return false; // Błąd odczytu lub koniec pliku
  }
}

bool writeRecord(FILE *file, const Record *record, long index)
{
  if (file == NULL || record == NULL || index < 0)
    return false;

  long offset = index * sizeof(Record);
  if (fseek(file, offset, SEEK_SET) != 0)
    return false;

  size_t items_written = fwrite(record, sizeof(Record), 1, file);
  if (items_written != 1)
  {
    perror("Błąd podczas zapisu rekordu do pliku (fwrite)");
    return false;
  }

  // Upewnij się, że dane zostały zapisane na dysk
  if (fflush(file) != 0)
  {
    perror("Błąd podczas oprozniania bufora pliku (fflush)");
  }

  return true; // Sukces
}

bool appendRecord(FILE *file, const Record *record)
{
  if (file == NULL || record == NULL)
    return false;

  if (fseek(file, 0, SEEK_END) != 0)
  {
    perror("Błąd podczas ustawiania pozycji na koniec pliku (fseek)");
    return false;
  }

  size_t items_written = fwrite(record, sizeof(Record), 1, file);

  if (items_written != 1)
  {
    perror("Błąd podczas dopisywania rekordu do pliku (fwrite)");
    return false;
  }

  // Upewnij się, że dane zostały zapisane na dysk
  if (fflush(file) != 0)
  {
    perror("Błąd podczas oprozniania bufora pliku (fflush)");
  }

  return true; // Sukces
}

long countRecords(FILE *file)
{
  if (file == NULL)
    return 0;

  // Zapamiętaj bieżącą pozycję
  long current_pos = ftell(file);
  if (current_pos == -1L)
  {
    perror("Błąd odczytu biezacej pozycji pliku (ftell)");
    return -1; // Zwróć błąd
  }

  // Przejdź na koniec pliku
  if (fseek(file, 0, SEEK_END) != 0)
  {
    perror("Błąd podczas ustawiania pozycji na koniec pliku (fseek)");
    fseek(file, current_pos, SEEK_SET); // Przywróć pierwotną pozycję w razie błędu
    return -1;                          // Zwróć błąd
  }

  // Odczytaj rozmiar pliku
  long file_size = ftell(file);
  if (file_size == -1L)
  {
    perror("Błąd odczytu rozmiaru pliku (ftell)");
    fseek(file, current_pos, SEEK_SET); // Przywróć pierwotną pozycję
    return -1;                          // Zwróć błąd
  }

  // Przywróć pierwotną pozycję wskaźnika
  if (fseek(file, current_pos, SEEK_SET) != 0)
  {
    perror("Błąd podczas przywracania pozycji pliku (fseek)");
  }

  // Oblicz liczbę rekordów
  if (sizeof(Record) == 0)
  {
    fprintf(stderr, "Błąd: Rozmiar rekordu wynosi zero.\n");
    return -1;
  }
  // Sprawdzenie, czy rozmiar pliku jest wielokrotnością rozmiaru rekordu (jakiś błąd )
  if (file_size % sizeof(Record) != 0)
  {
    fprintf(stderr, "Ostrzezenie: Rozmiar pliku (%ld) nie jest wielokrotnoscia rozmiaru rekordu (%zu).\n", file_size, sizeof(Record));
  }

  return file_size / sizeof(Record);
}

unsigned int getNextId(FILE *file)
{
  if (file == NULL)
    return 1;

  long current_pos = ftell(file);
  if (current_pos == -1L)
  {
    perror("getNextId: Błąd odczytu biezacej pozycji pliku (ftell)");
    return 1;
  }

  long total_records = countRecords(file);
  if (total_records < 0)
  {
    fprintf(stderr, "getNextId: Błąd podczas zliczania rekordow.\n");
    fseek(file, current_pos, SEEK_SET); // Przywróć pozycję
    return 1;
  }
  if (total_records == 0)
  {
    fseek(file, current_pos, SEEK_SET);
    return 1;
  }

  unsigned int max_id = 0;
  Record tempRecord; // Tymczasowy rekord do odczytu

  for (long i = 0; i < total_records; ++i)
  {
    if (readRecord(file, &tempRecord, i))
    {
      if (tempRecord.id > max_id)
        max_id = tempRecord.id;
    }
    else
      fprintf(stderr, "getNextId: Błąd odczytu rekordu na pozycji %ld.\n", i);
  }

  if (fseek(file, current_pos, SEEK_SET) != 0)
    perror("getNextId: Błąd podczas przywracania pozycji pliku (fseek)");

  if (max_id == UINT_MAX)
  {
    fprintf(stderr, "Krytyczny Błąd: Osiagnieto maksymalna wartosc ID (%u). Nie mozna wygenerowac nowego ID.\n", UINT_MAX);
    return 0;
  }

  return max_id + 1;
}
