#pragma once
#include <iostream>
#include <string>
using namespace std;

class Kopiec
{

private:
	int rozmiar;
	int* tablica;
	string cr, cl, cp;

public:
		Kopiec(void);
		Kopiec(int rozmiar);
		Kopiec(string nazwa_pliku);
		~Kopiec(void);

		void Dodaj(int wartosc);
		void UsunWierzcholek();
		int Znajdz(int wartosc); //wyszukuje i podaje indeks szukanej wartosci
		void Usun(int indeks);
		bool Wyszukaj(int wartosc); //sprawdza czy podana wartosc jest w drzewie, zwraca true/false
		void NaprawOdDolu(int indeks);
		void NaprawOdGory(int indeks);
		void Wyswietl(string sp, string sn, int indeks);
};


