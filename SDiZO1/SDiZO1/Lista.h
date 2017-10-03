#pragma once
#include <iostream>
#include <string>
using namespace std;


class Lista
{
	class Element
	{
	public:
		Element *nastepny, *poprzedni;
		int wartosc;
		Element();
		~Element();
	};

private:
	Element *poczatek, *koniec, *wybrany;
	unsigned rozmiar;
public:
	Lista();
	~Lista();
	Lista(string nazwa_pliku);
	Lista(int rozmiar);
	void NastepnyElement();
	void PoprzedniElement();
	void PoczatekListy();
	void KoniecListy();
	void WybranyElement(int numer);
	void DodajPoczatek(int wartosc);
	void DodajKoniec(int wartosc);
	void Dodaj(int numer, int wartosc);
	void UsunPoczatek();
	void UsunKoniec();
	void UsunZeSrodka();
	void Usun(int wartosc);
	bool Wyszukaj(int wartosc);
	void Wyswietl();

};

