#pragma once

#include <stdbool.h> // Dla typu bool

// Typ wyliczeniowy dla rodzaju oferty
typedef enum
{
  SALE = 1, // Sprzedaż
  RENT,     // Wypożyczenie
} OfferType;

// Struktura reprezentująca pojedynczy rekord w bazie danych
typedef struct
{
  unsigned int id;          // Identyfikator (liczba całkowita bez znaku) - generowany automatycznie
  char name[100];           // Nazwa dzieła
  int year;                 // Rok powstania (może być ujemny)
  OfferType offer_type;     // Rodzaj oferty
  double price;             // Koszt/cena w PLN
  char genre[50];           // Gatunek/Rodzaj
  char author_creator[100]; // Autor/Twórca
  bool is_deleted;          // Flaga wskazująca, czy rekord jest usunięty
} Record;