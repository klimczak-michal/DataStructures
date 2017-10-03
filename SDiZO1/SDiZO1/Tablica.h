#pragma once
#include <iostream>
using namespace std;

class Tablica
{
private:
	int rozmiar;
	int* tablica;
public:
	Tablica();
	Tablica(string nazwa_pliku); //Odczyt z pliku
	Tablica(int N); //Losowe generowanie
	void Usun(int indeks); //Usuwanie
	void Dodaj(int indeks, int wartosc); //Dodawanie
	void Wyszukaj(int liczba); //Wyszukiwanie
	void Wyswietl(); //Wyswietlanie
	~Tablica();
};

