#pragma once
#include <iostream>
#include <string>
using namespace std;

struct Wezel
{
	Wezel * gora;
	Wezel * lewy;
	Wezel * prawy;
	int wartosc;
	char kolor; //R - czerwony, B - czarny
	
};

class DrzewoCzCz
{
private:
	Wezel straznik; //Pusty wezel, bedzie sluzyl za wszystkie liscie w drzewie
	Wezel *korzen;
	string cr, cl, cp; //wyswietlanie
public:
	DrzewoCzCz();
	DrzewoCzCz(string nazwa_pliku); //Odczyt z pliku
	DrzewoCzCz(int N); //Losowe generowanie
	~DrzewoCzCz();
	void Wyswietl(string sp, string sn, Wezel * podany); // Wypisuje drzewo od podanego
	void print(); // Wypisuje cale drzewo
	void UsunDrzewo(Wezel * podany); // Usuwa drzewo
	Wezel * Znajdz(int wartosc); // Wyszukuje wêze³ o podanej wartoœci
	bool CzyJest(int warotsc); //Wyszukuje i zwraca czy istnieje wêze³ o zadanym kluczu
	Wezel * NajmniejszyWezel(Wezel * podany); // Wyszukuje najmniejszy wêze³ dla podanego poddrzewa
	Wezel * Nastepnik(Wezel * podany);// Wyszukuje nastêpnik podanego wêz³a
	void Rotacja_L(Wezel * A); // Rotacja w lewo wzglêdem A
	void Rotacja_R(Wezel * A); // Rotacja w prawo wzglêdem A
	void Wstaw(int wartosc);   // Wstawia wêze³ o zadanej wartosci
	void Usun(Wezel * podany); // Usuwa podany
};

