/**
 * Program: Algorytm X (problem dokladnego pokrycia)
 **
 * Dzialanie:
 * - Wczytuje filtr z pierwszego wiersza wejscia ('+' lub '-')
 * - Wczytuje zbior wierszy danych
 * - Znajduje rekurencyjnie taki podzbior wierszy, ktory po nalozeniu
 * na siebie tworzy kompletny ciag znakow (roznych od '_')
 * - Wypisuje wyniki po przefiltrowaniu (tylko kolumny z '+')
 *
 * Autor: Anna Koziara <ak479522@students.mimuw.edu.pl> 
 */

#include <stdio.h>

#include <stdlib.h>

#include <stdbool.h>

/* Maksymalna liczba wierszy danych wejsciowych */
#define MAX_WIER 200

/* Maksymalna dlugosc wiersza */
#define MAX_KOL 300

/**
 * - Wczytuje pierwszy wiersz danych wejsciowych, ktory jest filtrem
 * - Oblicza liczbe kolumn danych wejsciowych na podstawie długości tego wiersza
 */
void wczytanie_filtra(int filtr[], int * l_kolumn) {
  int znak_filtr = getchar();
  while (znak_filtr != '\n' && znak_filtr != EOF) {
    filtr[ * l_kolumn] = znak_filtr;
    ++( * l_kolumn);
    znak_filtr = getchar();
  }
}

/**
 * - Wczytuje wiersze danych wejsciowych
 * - Oblicza ilosc wczytywanych wierszy
 */
void wczytanie_zbiorow(int D[][MAX_KOL], int * l_wierszy, int l_kolumn) {
  int wczytany = getchar();
  while (wczytany != EOF) {
    for (int i = 0; i < l_kolumn; i++) {
      D[ * l_wierszy][i] = wczytany;
      wczytany = getchar();
    }
    ++( * l_wierszy);
    wczytany = getchar();
  }
}

/**
 * - Uzupelnia tablice wynikowa podkreslnikami ('_'), ktore informuja,
 * o tym, ze dana pozycja jest jeszcze niepokryta
 */
void przygotowanie_tablicy_pokryc(int wyniki[], int l_kolumn) {
  for (int i = 0; i < l_kolumn; i++) {
    wyniki[i] = '_';
  }
}

/**
 * - Sprawdza czy znaki z aktualnego wiersza nie koliduja z aktualnym pokryciem
 * - Kolizja nastepuje, gdy w obydwu tablicach, na tej samej pozycji, wystepuja
 * znaki rozne od '_'
 */
bool czy_kolizja(int D[][MAX_KOL], int wyniki[], int nr_wiersza, int l_kolumn) {
  bool blad = 0;
  int nr_kolumny = 0;
  while (nr_kolumny < l_kolumn && blad == 0) {
    if (wyniki[nr_kolumny] != '_' && D[nr_wiersza][nr_kolumny] != '_') {
      /* kolizja: dwie wartosci niepuste nachodza na siebie */
      blad = 1;
    }
    ++nr_kolumny;
  }
  return blad;
}

/**
 * - Aktualizuje tablice wynikow, uzupelniajac ja wynikami z wybranego wiersza
 */
void uzupelnianie(int D[][MAX_KOL], int wyniki[], int nr_wiersza, int l_kolumn) {
  for (int i = 0; i < l_kolumn; i++) {
    if (D[nr_wiersza][i] != '_') {
      wyniki[i] = D[nr_wiersza][i];
    }
  }
}

/**
 * - Wypisuje znalezione dokladne pokrycie, stosujac filtr 
 */
void filtrowanie(int wyniki[], int filtr[], int l_kolumn) {
  for (int i = 0; i < l_kolumn; i++) {
    if (filtr[i] == '+') {
      printf("%c", wyniki[i]);
    }
  }
  printf("\n");
}

/**
 * - Zwraca tablice wynikow z wartosciami znajdujacymi sie w tej tablicy
 * przed dodaniem nowego wiersza 
 */
void cofanie_zmian(int D[][MAX_KOL], int wyniki[], int nr_wiersza, int l_kolumn) {
  for (int i = 0; i < l_kolumn; i++) {
    if (D[nr_wiersza][i] != '_') {
      wyniki[i] = '_';
    }
  }
}

/**
 * - Za pomoca rekurencji szuka wszystkich mozliwosci zupelnego pokrycia
 * - Znajduje pierwsza pozycje w pokryciu na ktorej nie ma znaku
 * - Szuka wiersza majacego znak ktory uzupelni pokrycie w danej kolumnie
 * - Wyklucza wiersze ktorych elementy pokrywaja sie z aktualnym pokryciem
 */
void pokrycia(int l_kolumn, int l_wierszy, int D[][MAX_KOL], int wyniki[], int filtr[]) {
  int pozycja = 0;

  /* Znajduje pierwsza niepokryta kolumne */
  while (wyniki[pozycja] != '_' && pozycja < l_kolumn) {
    ++pozycja;
  }

  /* Warunek, gdy wszystkie pola w zupelnym pokryciu sa zapelnione */
  if (pozycja == l_kolumn) {
    filtrowanie(wyniki, filtr, l_kolumn);
  }
  /* Krok rekurencyjny */
  else {
    for (int w = 0; w < l_wierszy; w++) {
      /* Sprawdzenie czy dany wiersz zapelnia rozpartywane puste pole */
      if (D[w][pozycja] != '_') {

        /* Sprawdzenie czy wiersz nie koliduje z aktualnym pokryciem */
        if (czy_kolizja(D, wyniki, w, l_kolumn) == 0) {

          /* Wprowadzenie nowego wiersza do pokrycia */
          uzupelnianie(D, wyniki, w, l_kolumn);

          /* Kontynuacja rekurencji */
          pokrycia(l_kolumn, l_wierszy, D, wyniki, filtr);

          /* Powrot do poprzedniego stanu tablicy */
          cofanie_zmian(D, wyniki, w, l_kolumn);
        }
      }
    }
  }
}

/**
 * Glowna funkcja programu
 */

int main() {
  /* Inicjalizacja tablicy przechowujacej dane z filtra */
  int * filtr = (int * ) malloc(MAX_KOL * sizeof(int));

  /* Inicjalizacja tablicy przechowujacej wiersze w postaci ciagu znakow */
  int D[MAX_WIER][MAX_KOL];

  /* Inicjalizacja tablicy przechowujacej informacje o pokryciu */
  int * wyniki = (int * ) malloc(MAX_KOL * sizeof(int));

  int l_kolumn = 0;
  wczytanie_filtra(filtr, & l_kolumn);

  int l_wierszy = 0;
  wczytanie_zbiorow(D, & l_wierszy, l_kolumn);

  /* Przygotowanie tablicy wynikow przed rozpoczeciem rekurencji */
  przygotowanie_tablicy_pokryc(wyniki, l_kolumn);

  /* Rozpoczecie algorytmu szukania dokladnego pokrycia */
  pokrycia(l_kolumn, l_wierszy, D, wyniki, filtr);

  /* Zwolnienie pamieci */
  free(filtr);
  free(wyniki);
}