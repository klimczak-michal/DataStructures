#include "stdafx.h"
#include "Lista.h"
#include <fstream>
#include <stdlib.h> 
#include <time.h> 

Lista::Element::Element()
{
	wartosc = 0;
	poprzedni = NULL;
	nastepny = NULL;
}

Lista::Element::~Element()
{
	poprzedni = NULL;
	nastepny = NULL;
}

Lista::Lista()
{
	poczatek = NULL;
	koniec = NULL;
	wybrany = NULL;
	rozmiar = 0;

}

Lista::Lista(string nazwa_pliku)
{
	fstream plik;
	plik.open(nazwa_pliku);
	if (plik.is_open() == false)
	{
		cout << "Nie udalo sie otworzyc pliku!" << endl;
		return;
	}
	int roz, wartosc;
	plik >> roz;
	for (int i = 0; i < roz; i++)
	{
		plik >> wartosc;
		DodajKoniec(wartosc);
	}
	cout << "Wczytano dane." << endl;
	plik.close();
}

Lista::Lista(int N) //Losowe generowanie
{
	srand(time(NULL));
	int wartosc;
	this->rozmiar = N;
	for (int i = 0; i < N; i++)
	{
		wartosc = rand();
		DodajKoniec(wartosc);
	}
}

Lista::~Lista()
{
	delete poczatek;
	poczatek = NULL;
	delete koniec;
	koniec = NULL;
	delete wybrany;
	wybrany = NULL;
}

void Lista::NastepnyElement()
{
	if (wybrany == koniec) { wybrany = NULL; } //brak nastepnego
	else { wybrany = wybrany->nastepny; }
}

void Lista::PoprzedniElement()
{
	if (wybrany == poczatek) { wybrany = NULL; } //brak poprzedniego
	else { wybrany = wybrany->poprzedni; }
}

void Lista::PoczatekListy()
{
	wybrany = poczatek;
}

void Lista::KoniecListy()
{
	wybrany = koniec;
}

void Lista::WybranyElement(int numer)
{
	PoczatekListy(); //ustawienie sie na poczatek listy
	for (int i = 0; i < numer; i++) //przejscie pod wybrany indeks
	{
		NastepnyElement();
	}
}

void Lista::DodajPoczatek(int wartosc)
{
	if (rozmiar == 0)
	{
		Element* nowy = new Element; //nowy JEDYNY element
		nowy->wartosc = wartosc;
		poczatek = nowy;
		koniec = nowy;
		wybrany = nowy;
		rozmiar++;
		return;
	}
	Element* nowy = new Element;
	nowy->wartosc = wartosc; 
	poczatek->poprzedni = nowy; //przypisanie poprzedniego elementu dla starego poczatku
	nowy->nastepny = poczatek; //przypisanie nastepnego elementu nowemu poczatkowi
	poczatek = nowy;
	rozmiar++;
}

void Lista::DodajKoniec(int wartosc)
{
	if (rozmiar == 0) //nowy JEDYNY element
	{
		Element* nowy = new Element;
		nowy->wartosc = wartosc;
		poczatek = nowy;
		koniec = nowy;
		wybrany = nowy;
		rozmiar++;
		return;
	}
	Element* nowy = new Element;
	nowy->wartosc = wartosc;
	nowy->poprzedni = koniec; //przypisanie poprzedniego elementu nowemu koncowi
	koniec->nastepny = nowy; //przypisanie nastepnego elementu staremu koncowi
	koniec = nowy;
	rozmiar++;
}

void Lista::Dodaj(int numer, int wartosc)
{
	if (numer == 0) //dodanie przed indeks 0
	{
		DodajPoczatek(wartosc);
		return;
	}
	if (numer == rozmiar) //dodanie za ostatni element
	{
		DodajKoniec(wartosc);
		return;
	}
	if (numer > rozmiar)
	{
		cout << "Podano zbyt duza wartosc" << endl;
		return;
	}
		Element* nowy = new Element;
		nowy->wartosc = wartosc;
		WybranyElement(numer); //przejscie do wybranego elementu
		nowy->nastepny = wybrany; //nowy element wchodzi na miejsce wybranego elementu
		nowy->poprzedni = wybrany->poprzedni;
		(wybrany->poprzedni)->nastepny = nowy; //zamiana nastepnego elementu na nowy dla el. poprzedzajacego nowy el.
		wybrany->poprzedni = nowy;
		rozmiar++;	
}

void Lista::UsunPoczatek()
{
	PoczatekListy();
	poczatek = poczatek->nastepny;
	if (rozmiar == 1)
		koniec = NULL;
	else
		poczatek->poprzedni = NULL;
	delete wybrany;
	PoczatekListy();
	rozmiar--;
}

void Lista::UsunKoniec()
{
	KoniecListy();
	koniec = koniec->poprzedni;
	if (rozmiar == 1)
		poczatek = NULL;
	else
		koniec->nastepny = NULL;
	delete wybrany;
	KoniecListy();
	rozmiar--;
}

void Lista::UsunZeSrodka()
{
	if (rozmiar == 0)
	{
		cout << "Lista jest pusta." << endl;
		return;
	}
	if (rozmiar == 1)
	{
		UsunPoczatek();
		return;
	}
	Element* pomocniczy = wybrany;
	(wybrany->poprzedni)->nastepny = wybrany->nastepny;
	(wybrany->nastepny)->poprzedni = wybrany->poprzedni;
	wybrany = wybrany->poprzedni;
	delete pomocniczy;
	pomocniczy = NULL;
	rozmiar--;
}

void Lista::Usun(int wartosc)
{
	bool jest = false;
	if (rozmiar == 0)
	{
		cout << "Lista jest pusta." << endl;
		return;
	}
	if (rozmiar == 1)
	{
		UsunPoczatek();
		return;
		jest = true;
	}
	PoczatekListy();

	do{ //petla sprawdzajaca
		if (wybrany->wartosc == wartosc) //gdy znajdzie
		{
			jest = true; 
			if (wybrany == poczatek) //sprawdza czy znaleziony el. jest poczatkiem
			{
				UsunPoczatek();
				break;
			}
			else if (wybrany == koniec) //sprawdza czy znaleziony el. jest koncem
			{
				UsunKoniec();
				break;
			}
			else //w przeciwnym przypadku usuwa el. ze "srodka" i naprawia strukture
			{
				UsunZeSrodka();
				break;
			}
			
		}
		NastepnyElement(); //"i++"
	} while (wybrany != NULL);
	if (!jest)
	{
		cout << "Nie znaleziono." << endl;
		return;
	}
	cout << "Usunieto" << endl;
}

bool Lista::Wyszukaj(int wartosc)
{
	PoczatekListy();
	for (int i = 0; i < rozmiar; i++)
	{
		if (wybrany->wartosc == wartosc)
		{
			return true;
		}
		NastepnyElement();
	}
	return false;
}

void Lista::Wyswietl()
{
	PoczatekListy();
	cout << "Od poczatku:\n";
	for (int i = 0; i < rozmiar; i++)
	{
		cout << wybrany->wartosc<<endl;

		NastepnyElement();
	}
	cout << "Od konca:\n";
	KoniecListy();
	for (int i = 0; i < rozmiar; i++)
	{
		cout << wybrany->wartosc << endl;
		PoprzedniElement();
	}
}