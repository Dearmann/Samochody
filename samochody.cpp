#include <iostream>
#include <string>
#include <fstream>
#include "struktury.h"
#include "funkcje.h"

using namespace std;

int main(int argc, char* argv[])
{
    int ilosc_argumentow = 5;
    if (argc != ilosc_argumentow)
    {
        cout << "Program wywolac: ./samochody.exe -i <plik wejsciowy> -o <plik wyjsciowy>" << endl;
        return 0;
    }

    ifstream dane;
    ofstream raport;

    znajdzPrzelacznikInput(argc, argv, dane);
    znajdzPrzelacznikOutput(argc, argv, raport);

    samochod* samochody = nullptr;
    stworzListeSamochodow(samochody, dane);

    stworzRaport(samochody, raport);

    usunSamochody(samochody);
    dane.close();
    raport.close();
}