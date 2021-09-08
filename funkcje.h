/** @file */

// zabezpieczenie przed wielokrotnym dołączaniem pliku nagłówkowego
#ifndef FUNKCJE_H 
#define FUNKCJE_H

#include <fstream>
#include <string>
#include "struktury.h"

using namespace std;

/** Funkcja znajduje przełącznik "-i", następnie otwiera plik o nazwie argumentu po przełączniku.
 * @param argc ilość argumentów
 * @param argv wektor argumentów
 * @param dane strumień wejściowy
 */
void znajdzPrzelacznikInput(int argc, char* argv[], ifstream& dane);

/** Funkcja znajduje przełącznik "-o", następnie otwiera plik o nazwie argumentu po przełączniku.
 * @param argc ilość argumentów
 * @param argv wektor argumentów
 * @param raport strumień wyjściowy
 */
void znajdzPrzelacznikOutput(int argc, char* argv[], ofstream& raport);

/** Funkcja tworzy nowy element struktury "samochod" na końcu listy lub jako jej pierwszy element.
 * @param pHead przekazywany przez referencje wskaźnik na liste samochodów
 */
void nowySamochod(samochod*& pHead);

/** Funkcja zwraca wskaźnik na ostatni element listy.
 * @param pHead przekazywany przez referencje wskaźnik na liste samochodów
 * @return wskaźnik na ostatni element listy
 */
samochod* ostatniSamochod(samochod* pHead);

/** Funkcja tworzy nowy element struktury "numer_rejestracyjny" na końcu listy lub jako jej pierwszy element.
 * @param pHead przekazywany przez referencje wskaźnik na liste numerów rejestracyjnych
 * @param data_rejestracji parametr przypisywany tworzonemu elementowi listy
 * @param nr_rejestracyjny parametr przypisywany tworzonemu elementowi listy
 */
void nowyNumerRejestracyjny(numer_rejestracyjny*& pHead, string data_rejestracji, string nr_rejestracyjny);

/** Funkcja zwraca wskaźnik na ostatni element listy.
 * @param pHead przekazywany przez referencje wskaźnik na liste numerów rejestracyjnych
 * @return wskaźnik na ostatni element listy
 */
numer_rejestracyjny* ostatniNumerRejestracyjny(numer_rejestracyjny* pHead);

/** Funkcja tworzy nowy element struktury "wlasciciel" na końcu listy lub jako jej pierwszy element.
 * @param pHead przekazywany przez referencje wskaźnik na liste właścicieli
 * @param data_nabycia parametr przypisywany tworzonemu elementowi listy
 * @param nazwa parametr przypisywany tworzonemu elementowi listy
 */
void nowyWlasciciel(wlasciciel*& pHead, string data_nabycia, string nazwa);

/** Funkcja zwraca wskaźnik na ostatni element listy.
 * @param pHead przekazywany przez referencje wskaźnik na liste właścicieli
 * @return wskaźnik na ostatni element listy
 */
wlasciciel* ostatniWlasciciel(wlasciciel* pHead);

/** tworzy nowy element struktury "wypisany_wlasciciel" na końcu listy lub jako jej pierwszy element.
 * @param pHead przekazywany przez referencje wskaźnik na liste wypisanych właścicieli
 * @param nazwa parametr przypisywany tworzonemu elementowi listy
 */
void nowyWypisanyWlasciciel(wypisany_wlasciciel*& pHead, string nazwa);

/** Funkcja odczytuje z pliku wejściowego dane o numerach rejestracyjnych samochodów i tworzy ich liste przypisaną do danego samochodu.
 * @param samochody lista wszystkich odczytanych do tej pory samochodów
 * @param dane dane wejściowe
 */
void stworzListeRejestracji(samochod* samochody, ifstream& dane);

/** Funkcja odczytuje z pliku wejściowego dane o właścicielach samochodów i tworzy ich liste przypisaną do danego samochodu. Funkcja znajduje przecinki i na tej podstawie określa ilość właścicieli w 1 linii.
 * @param samochody lista wszystkich odczytanych do tej pory samochodów
 * @param dane dane wejściowe
 */
void stworzListeWlascicieli(samochod* samochody, ifstream& dane);

/** Funkcja tworzy liste samochodów i przypisuje im dane z pliku wejściowego, następnie tworzy liste rejestracji i liste właścicieli na aktualnie stworzonym samochodzie.
 * @param samochody lista wszystkich odczytanych do tej pory samochodów
 * @param dane dane wejściowe
 */
void stworzListeSamochodow(samochod*& samochody, ifstream& dane);

/** Funkcja wyprowadza na strumień wyjściowy dane o okresie posiadania samochodu przez danego właściciela.
 * @param wlasciciele lista właścicieli
 * @param raport strumień wyjściowy
 */
void wypiszOkresPosiadania(wlasciciel* wlasciciele, ofstream& raport);

/** Funkcja wypisuje dane o samochodzie do strumienia wyjściowego.
 * @param raport strumień wyjściowy
 * @param samochody lista samochodów
 */
void wypiszSamochod(ofstream& raport, samochod* samochody);

/** Funkcja przeszukuje liste samochodów i ich listy właścicieli w celu znalezienia odpowiadającej nazwy właściciela wprowadzonej w argumencie funkcji.
 * @param samochody lista przeszukiwanych samochodów
 * @param nazwa_wlasciciela nazwa właściciela którego samochodu szukamy
 * @return wskaźnik pierwszego znalezionego samochodu właściciela
 */
samochod* znajdzKolejnySamochodWlasciciela(samochod* samochody, string nazwa_wlasciciela);

/** Funkcja zwraca wskaźnik do szukanego właściciela o podanej nazwie.
 * @param samochody lista samochodów
 * @param nazwa_wlasciciela nazwa szukanego właściciela
 * @return wskaźnik szukanego właściciela
 */
wlasciciel* znajdzWlascicielaSamochodu(samochod* samochody, string nazwa_wlasciciela);

/** Funkcja wypisuje wszystkie samochody posiadane przez danego właściciela.
 * @param samochody lista samochodów
 * @param raport strumień wyjściowy
 * @param wlasciciele lista właścicieli
 */
void wypiszSamochodyWlasciciela(samochod* samochody, ofstream& raport, wlasciciel* wlasciciele);

/** Funkcja sprawdza czy raport danego właściciela został już wypisany żeby uniknąć podwójnego wypisania.
 * @param wypisani_wlasciciele lista wypisanych właścicieli
 * @param nazwa_wlasciciela szukana nazwa właściciela
 * @return true gdy powstał już raport dla tego właściciela
 * @return false gdy jeszcze nie ma raportu dla tego właściciela
 */
bool czyWlascicielZostalWypisany(wypisany_wlasciciel* wypisani_wlasciciele, string nazwa_wlasciciela);

/** Funkcja usuwa wszystkie elementy listy wypisanych właścicieli i zeruje ich wskaźniki.
 * @param pHead wskaźnik na liste wypisanych właścicieli
 */
void usunListeWypisanychWlascicieli(wypisany_wlasciciel*& pHead);

/** Funkcja tworzy raport dla każdego właściciela o posiadanych przez niego samochodach.
 * @param samochody lista samochodów
 * @param raport strumień wyjściowy
 */
void stworzRaport(samochod* samochody, ofstream& raport);

/** Funkcja usuwa wszystkie elementy listy właścicieli i zeruje ich wskaźniki.
 * @param wlasciciele lista właścicieli
 */
void usunWlascicieli(wlasciciel*& wlasciciele);

/** Funkcja usuwa wszystkie elementy listy numerów rejestracyjnych i zeruje ich wskaźniki.
 * @param rejestracje lista rejestracji
 */
void usunRejestracje(numer_rejestracyjny*& rejestracje);

/** Funkcja usuwa wszystkie elementy listy samochodów i usuwa listy właścicieli, i rejestracji przypisanych każdemu samochodowi. Zeruje wskaźniki wszystkich usuniętych elementów.
 * @param samochody lista samochodów
 */
void usunSamochody(samochod*& samochody);

#endif  // koniec zabezpieczenia jednokrotnego dołączania pliku nagłówkowego
