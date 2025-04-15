#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define MAX_WORD_LEN 100
#define MAX_PLAYERS 4
#define WORDS_COUNT 20

const char *hasla[WORDS_COUNT] = {
    "programming",
    "computer",
    "science",
    "mathematics",
    "physics",
    "chemistry",
    "biology",
    "engineering",
    "technology",
    "artificial intelligence",
    "machine learning",
    "data science",
    "software development",
    "web development",
    "mobile development",
    "cloud computing",
    "cybersecurity",
    "networking",
    "database management",
    "information systems",
    "HID devices"};

typedef struct
{
    char name[50];
    int points;
} Player;

const char *random_word()
{
    int indeks = rand() % WORDS_COUNT;
    return hasla[indeks];
}
void init_word(const char *word, char *hidden_word)
{
    int i;
    for (i = 0; word[i] != '\0'; i++)
    {
        if (word[i] == ' ')
        {
            hidden_word[i] = ' ';
        }
        else
        {
            hidden_word[i] = '_';
        }
    }
    hidden_word[i] = '\0';
}
int check_guess(const char *word, char *hidden_word, char letter)
{
    int counter = 0;

    letter = tolower(letter); // Ignore letter case

    for (int i = 0; word[i] != '\0'; i++)
    {
        if (tolower(word[i]) == letter && hidden_word[i] == '_')
        {
            hidden_word[i] = word[i];
            counter++;
        }
    }

    return counter;
}

int is_guessed(const char *hidden_word)
{
    for (int i = 0; hidden_word[i] != '\0'; i++)
    {
        if (hidden_word[i] == '_')
        {
            return 0; // Nie odgadnięto
        }
    }
    return 1; // Odgadnięto
}

void print_game(const char *hidden_word, Player *players, int player_count)
{
    printf("\nAktualne hasło: %s\n\n", hidden_word);
    printf("Wyniki graczy:\n");
    for (int i = 0; i < player_count; i++)
    {
        printf("%s: %d punktów\n", players[i].name, players[i].points);
    }
    printf("\n");
}

int main()
{
    srand(time(NULL)); // Inicjalizacja generatora liczb losowych

    int player_count, found_letters, player, should_play;
    Player players[MAX_PLAYERS];
    char hidden_word[MAX_WORD_LEN];
    char letter;

    player = 0;
    should_play = 1;
    found_letters = 0;

    const char *word = random_word();

    do
    {
        printf("Podaj liczbę graczy (1-%d): ", MAX_PLAYERS);
        scanf("%d", &player_count);
        getchar(); // Pobranie znaku nowej linii
    } while (player_count < 1 || player_count > MAX_PLAYERS);

    for (int i = 0; i < player_count; i++)
    {
        printf("Podaj imię lub pseudonim gracza %d: ", i + 1);
        fgets(players[i].name, sizeof(players[i].name), stdin);

        // Usunięcie znaku nowej linii
        int len = strlen(players[i].name);
        if (len > 0 && players[i].name[len - 1] == '\n')
        {
            players[i].name[len - 1] = '\0';
        }

        players[i].points = 0;
    }

    // Inicjalizujemy ukryte hasło
    init_word(word, hidden_word);

    // Główna pętla gry
    while (should_play)
    {
        print_game(hidden_word, players, player_count);

        printf("Gracz %s, podaj literę: ", players[player].name);
        scanf(" %c", &letter);
        getchar();

        found_letters = check_guess(word, hidden_word, letter);

        if (found_letters > 0)
        {
            printf("Brawo! Znaleziono %d liter(y).\n", found_letters);
            players[player].points += found_letters;

            // Sprawdzamy, czy hasło zostało odgadnięte
            if (is_guessed(hidden_word))
            {
                printf("\nGRATULACJE! Hasło zostało odgadnięte!\n");
                printf("Hasło to: %s\n", word);
                print_game(hidden_word, players, player_count);
                should_play = 0;
            }
        }
        else
        {
            printf("Niestety, tej litery nie ma w haśle lub została już odkryta.\n");
            player = (player + 1) % player_count;
        }
    }

    // Wyłaniamy zwycięzcę
    int max_points = -1;
    int winner = -1;

    for (int i = 0; i < player_count; i++)
    {
        if (players[i].points > max_points)
        {
            max_points = players[i].points;
            winner = i;
        }
    }

    printf("\nZwycięzcą gry został %s z wynikiem %d punktów!\n",
           players[winner].name, players[winner].points);

    return 0;
}