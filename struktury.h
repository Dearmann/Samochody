/** @file */

#ifndef STRUKTURY_H
#define STRUKTURY_H

#include <string>

/** Struktura reprezentująca numery rejestracyjne samochodu */
struct numer_rejestracyjny
{
    std::string data_rejestracji;   ///< data w której numer rejestracyjny samochodu został zarejestrowany
    std::string nr_rejestracyjny;   ///< numer rejestracyjny
    numer_rejestracyjny* pNext;     ///< wskaźnik na następny numer rejestracyjny
};

/** Struktura reprezentująca właścicieli samochodu */
struct wlasciciel
{
    std::string data_nabycia;   ///< data nabycia samochodu przez właściciela
    std::string nazwa;          ///< nazwa właściciela
    wlasciciel* pNext;          ///< wskaźnik do następnego właściciela samochodu
};

/** Struktura reprezentująca samochód */
struct samochod
{
    std::string marka;                      ///< marka samochodu
    std::string model;                      ///< model samochodu
    int rok_produkcji;                      ///< rok produkcji samochodu
    int pojemnosc_silnika;                  ///< pojemność silnika samochodu
    std::string nr_silnika;                 ///< numer silnika samochodu
    std::string nr_nadwozia;                ///< numer nadwozia samochodu
    std::string data_pierwszej_rejestracji; ///< data pierwszej rejestracji samochodu
    numer_rejestracyjny* rejestracje;       ///< lista rejestracji samochodu
    wlasciciel* wlasciciele;                ///< lista właścicieli samochodu
    samochod* pNext;                        ///< wskaźnik do następnego samochodu listy
};

/** Struktura reprezentująca właścicieli dla ktorych raport został już sporządzony */
struct wypisany_wlasciciel
{
    std::string nazwa;          ///< nazwa wypisanego właściciela
    wypisany_wlasciciel* pNext; ///< wskaźnik do następnego wypisanego właściciela
};

#endif
