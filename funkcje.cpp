#include <iostream>
#include <string>
#include <fstream>
#include "funkcje.h"

using namespace std;

void znajdzPrzelacznikInput(int argc, char* argv[], ifstream& dane)
{
    for (int i = 0; i < argc - 1; i++)  // Pętla szukająca przełącznik
    {
        string przelacznik = argv[i];
        if (przelacznik == "-i" && argv[i+1] != "\0" && argv[i+1] != "-o")
        {
            dane.open(argv[i+1]);
            if (!dane.good())
            {
                cout << "Plik do odczytu nie istnieje" << endl;
                return;
            }
        }
    }
}

void znajdzPrzelacznikOutput(int argc, char* argv[], ofstream& raport)
{
    for (int i = 0; i < argc - 1; i++)  // Pętla szukająca przełącznik
    {
        string przelacznik = argv[i];
        if (przelacznik == "-o" && argv[i+1] != "\0" && argv[i+1] != "-i")
        {
            raport.open(argv[i+1]);
        }
    }
}

void nowySamochod(samochod*& pHead)
{
    if (!pHead)
        pHead = new samochod;
    else
    {
        auto p = pHead;
        while (p->pNext)
            p = p->pNext;
        p->pNext = new samochod;
    }
}

samochod* ostatniSamochod(samochod* pHead)
{
    while (pHead->pNext)
        pHead = pHead->pNext;
    return pHead;
}

void nowyNumerRejestracyjny(numer_rejestracyjny*& pHead, string data_rejestracji, string nr_rejestracyjny)
{
    if (!pHead)
        pHead = new numer_rejestracyjny {data_rejestracji, nr_rejestracyjny, nullptr};
    else
    {
        auto p = pHead;
        while (p->pNext)
            p = p->pNext;
        p->pNext = new numer_rejestracyjny {data_rejestracji, nr_rejestracyjny, nullptr};
    }
}

numer_rejestracyjny* ostatniNumerRejestracyjny(numer_rejestracyjny* pHead)
{
    while (pHead->pNext)
        pHead = pHead->pNext;
    return pHead;
}

void nowyWlasciciel(wlasciciel*& pHead, string data_nabycia, string nazwa)
{
    if (!pHead)
        pHead = new wlasciciel {data_nabycia, nazwa, nullptr};
    else
    {
        auto p = pHead;
        while (p->pNext)
            p = p->pNext;
        p->pNext = new wlasciciel {data_nabycia, nazwa, nullptr};
    }
}

wlasciciel* ostatniWlasciciel(wlasciciel* pHead)
{
    while (pHead->pNext)
        pHead = pHead->pNext;
    return pHead;
}

void nowyWypisanyWlasciciel(wypisany_wlasciciel*& pHead, string nazwa)
{
    if (!pHead)
        pHead = new wypisany_wlasciciel {nazwa, nullptr};
    else
    {
        auto p = pHead;
        while (p->pNext)
            p = p->pNext;
        p->pNext = new wypisany_wlasciciel {nazwa, nullptr};
    }
    
}

void stworzListeRejestracji(samochod* samochody, ifstream& dane)
{
    string wyraz;
    string data_rejestracji;
    string nr_rejestracyjny;
    dane >> wyraz;
    while (wyraz != "wlaciciele:")
    {
        data_rejestracji = wyraz;
        dane >> wyraz;
        nr_rejestracyjny = wyraz;
        nowyNumerRejestracyjny(ostatniSamochod(samochody)->rejestracje, data_rejestracji, nr_rejestracyjny);
        dane >> wyraz;
    }
}

void stworzListeWlascicieli(samochod* samochody, ifstream& dane)
{
    string wyraz;
    string imie;
    string nazwisko;
    string nazwa;
    string data_nabycia;
    dane >> wyraz;
    while (wyraz != "---")
    {
        data_nabycia = wyraz;
        dane >> wyraz;
        imie = wyraz;
        dane >> wyraz;
        nazwisko = wyraz.substr(0, wyraz.find(","));
        nazwa = imie + " " + nazwisko;
        nowyWlasciciel(ostatniSamochod(samochody)->wlasciciele, data_nabycia, nazwa);
        while (wyraz.find(",") != string::npos)
        {
            dane >> wyraz;
            imie = wyraz;
            dane >> wyraz;
            nazwisko = wyraz.substr(0, wyraz.find(","));
            nazwa = imie + " " + nazwisko;
            nowyWlasciciel(ostatniSamochod(samochody)->wlasciciele, data_nabycia, nazwa);
        }
        dane >> wyraz;
        if (dane.eof())
            return;
    }
}

void stworzListeSamochodow(samochod*& samochody, ifstream& dane)
{
    string wyraz;
    while (dane >> wyraz)
    {
        if (wyraz == "samochod")
        {
            nowySamochod(samochody);
        }
        else if (wyraz == "marka:")
        {
            dane >> wyraz;
            ostatniSamochod(samochody)->marka = wyraz;
        }
        else if (wyraz == "model:")
        {
            dane >> wyraz;
            ostatniSamochod(samochody)->model = wyraz;
        }
        else if (wyraz == "produkcji:")
        {
            dane >> wyraz;
            ostatniSamochod(samochody)->rok_produkcji = stoi(wyraz);
        }
        else if (wyraz == "pojemnosc")
        {
            dane >> wyraz;
            dane >> wyraz;
            ostatniSamochod(samochody)->pojemnosc_silnika = stoi(wyraz);
        }
        else if (wyraz == "silnika:")
        {
            dane >> wyraz;
            ostatniSamochod(samochody)->nr_silnika = wyraz;
        }
        else if (wyraz == "nadwozia:")
        {
            dane >> wyraz;
            ostatniSamochod(samochody)->nr_nadwozia = wyraz;
        }
        else if (wyraz == "rejestracji:")
        {
            dane >> wyraz;
            ostatniSamochod(samochody)->data_pierwszej_rejestracji = wyraz;
        }
        else if (wyraz == "rejestracyjne:")
        {
            stworzListeRejestracji(samochody, dane);
            stworzListeWlascicieli(samochody, dane);
        }
    }
}

void wypiszOkresPosiadania(wlasciciel* wlasciciele, ofstream& raport)
{
    raport << "Okres posiadania: od " << wlasciciele->data_nabycia << " do ";
    if (wlasciciele->pNext)
    {
        while (wlasciciele->data_nabycia == wlasciciele->pNext->data_nabycia)
        {
            wlasciciele = wlasciciele->pNext;
            if (! wlasciciele->pNext)
            {
                raport << "teraz" << endl;
                return;
            }
        }
        raport << wlasciciele->pNext->data_nabycia << endl;
    }
    else
        raport << "teraz" << endl;
}

void wypiszSamochod(ofstream& raport, samochod* samochody)
{
    raport << "marka: " << samochody->marka << endl;
    raport << "model: " << samochody->model << endl;
    raport << "rok produkcji: " << samochody->rok_produkcji << endl;
    raport << "pojemnosc silnika: " << samochody->pojemnosc_silnika << endl;
    raport << "nr silnika: " << samochody->nr_silnika << endl;
    raport << "nr nadwozia: " << samochody->nr_nadwozia << endl;
    raport << "data pierwszej rejestracji: " << samochody->data_pierwszej_rejestracji << endl;
    raport << "numery rejestracyjne: " << endl;
    auto pRejestracje = samochody->rejestracje;
    while (pRejestracje)
    {
        raport << pRejestracje->data_rejestracji << " " << pRejestracje->nr_rejestracyjny << endl;
        pRejestracje = pRejestracje->pNext;
    }
    raport << endl;
}

samochod* znajdzKolejnySamochodWlasciciela(samochod* samochody, string nazwa_wlasciciela)
{
    samochody = samochody->pNext;
    wlasciciel* pWlasciciele;
    while (samochody)
    {
        pWlasciciele = samochody->wlasciciele;
        while (pWlasciciele)
        {
            if (nazwa_wlasciciela == pWlasciciele->nazwa)
                return samochody;
            pWlasciciele = pWlasciciele->pNext;
        }
        samochody = samochody->pNext;
    }
    return nullptr;
}

wlasciciel* znajdzWlascicielaSamochodu(samochod* samochody, string nazwa_wlasciciela)
{
    wlasciciel* pWlasciciele = samochody->wlasciciele;
    while (pWlasciciele)
    {
        if (nazwa_wlasciciela == pWlasciciele->nazwa)
            return pWlasciciele;
        pWlasciciele = pWlasciciele->pNext;
    }
    return nullptr;
}

void wypiszSamochodyWlasciciela(samochod* samochody, ofstream& raport, wlasciciel* wlasciciele)
{
    int licznik = 1;
    samochod* kolejny_samochod;
    raport << "--- " << wlasciciele->nazwa << " ---" << endl;
    raport << "Samochod nr " << licznik << ":" << endl;
    wypiszOkresPosiadania(wlasciciele, raport);
    wypiszSamochod(raport, samochody);
    kolejny_samochod = znajdzKolejnySamochodWlasciciela(samochody, wlasciciele->nazwa);
    while (kolejny_samochod)
    {
        raport << "Samochod nr " << ++licznik << ":" << endl;
        wypiszOkresPosiadania(znajdzWlascicielaSamochodu(kolejny_samochod, wlasciciele->nazwa), raport);
        wypiszSamochod(raport, kolejny_samochod);
        kolejny_samochod = znajdzKolejnySamochodWlasciciela(kolejny_samochod, wlasciciele->nazwa);
    }    
}

bool czyWlascicielZostalWypisany(wypisany_wlasciciel* wypisani_wlasciciele, string nazwa_wlasciciela)
{
    while (wypisani_wlasciciele)
    {
        if (wypisani_wlasciciele->nazwa == nazwa_wlasciciela)
            return true;
        wypisani_wlasciciele = wypisani_wlasciciele->pNext;
    }
    return false;
}

void usunListeWypisanychWlascicieli(wypisany_wlasciciel*& pHead)
{
    if (pHead)
    {
        usunListeWypisanychWlascicieli(pHead->pNext);
        delete pHead;
        pHead = nullptr;
    }
}

void stworzRaport(samochod* samochody, ofstream& raport)
{
    wypisany_wlasciciel* wypisani_wlasciciele = nullptr;
    wlasciciel* pWlasciciele;
    bool znaleziono_wlasciciela;
    while (samochody)
    {
        pWlasciciele = samochody->wlasciciele;
        while (pWlasciciele)
        {
            znaleziono_wlasciciela = czyWlascicielZostalWypisany(wypisani_wlasciciele, pWlasciciele->nazwa);
            if (! znaleziono_wlasciciela)
            {
                nowyWypisanyWlasciciel(wypisani_wlasciciele, pWlasciciele->nazwa);
                wypiszSamochodyWlasciciela(samochody, raport, pWlasciciele);
            }
            pWlasciciele = pWlasciciele->pNext;
        }
        samochody = samochody->pNext;
    }
    usunListeWypisanychWlascicieli(wypisani_wlasciciele);
}

void usunWlascicieli(wlasciciel*& wlasciciele)
{
    if (wlasciciele)
    {
        usunWlascicieli(wlasciciele->pNext);
        delete wlasciciele;
        wlasciciele = nullptr;
    }
}

void usunRejestracje(numer_rejestracyjny*& rejestracje)
{
    if (rejestracje)
    {
        usunRejestracje(rejestracje->pNext);
        delete rejestracje;
        rejestracje = nullptr;
    }
}

void usunSamochody(samochod*& samochody)
{
    if (samochody)
    {
        usunSamochody(samochody->pNext);
        usunWlascicieli(samochody->wlasciciele);
        usunRejestracje(samochody->rejestracje);
        delete samochody;
        samochody = nullptr;
    }
}