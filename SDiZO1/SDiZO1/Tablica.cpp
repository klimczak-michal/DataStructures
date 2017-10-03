#include "stdafx.h"
#include "Tablica.h"
#include <fstream>
#include <stdlib.h> 
#include <time.h>  


Tablica::Tablica()
{
	rozmiar = 1;
	tablica = new int[rozmiar];
}


Tablica::~Tablica()
{
	delete tablica;
	*tablica = NULL;
}


Tablica::Tablica(string nazwa_pliku) //Odczyt z pliku
{
	fstream plik;
	plik.open(nazwa_pliku);
	if (plik.is_open() == false)
	{
		cout << "Nie udalo sie otworzyc pliku!" << endl;
		return;
	}
	int N, wartosc;
	plik >> N;
	this->rozmiar = N;
	this->tablica = new int[N];
	for (int i = 0; i < N; i++)
	{
		plik >> wartosc;
		tablica[i] = wartosc;
	}
	cout << "Wczytano dane." << endl;
	plik.close();
}

Tablica::Tablica(int N) //Losowe generowanie
{
	srand(time(NULL));
	int wartosc;
	this->rozmiar = N;
	this->tablica = new int[N];
	for (int i = 0; i < N; i++)
	{
		wartosc = rand();
		tablica[i] = wartosc;
	}
}

void Tablica::Usun(int indeks)
{
	int* Tab;
	Tab = new int[rozmiar - 1]; //pomocnicza tablica

	if (rozmiar == 0) //sprawdza czy tablica istnieje
	{
		cout << "Brak tablicy"<<endl;
	}
	else {
			if (indeks == 0) // jezeli poczatek tablicy
			{
				for (int i = 0; i < rozmiar-1; i++)
				{
					Tab[i] = tablica[i + 1]; //przesuwa na i-ty indeks wartosc i+1
				}
				delete[] tablica; 
				tablica = Tab;
				rozmiar--; //zmniejsza rozmiar tablicy o 1
			}

			else if (indeks == (rozmiar - 1)) //jezeli koniec tablicy
			{
				for (int i = 0; i < rozmiar-1; i++)
				{
					Tab[i] = tablica[i]; //przesuwa na i-ty indeks wartosc i+1
				}
				delete[] tablica;
				tablica = Tab;
				rozmiar--; //zmniejsza rozmiar tablicy o 1
			}
			else if (indeks >= rozmiar) { cout << "Za duzy indeks" << endl; }
			else //w kazdym innym przypadku
			{
				for (int i = 0; i < indeks; i++) //i = indeks -> zaczyna petle od zadanego miejsca
				{
					Tab[i] = tablica[i];
				}
				for (int i = indeks; i < rozmiar-1; i++) //i = indeks -> zaczyna petle od zadanego miejsca
				{
					Tab[i] = tablica[i+1];
				}
				delete[] tablica;
				tablica = Tab;
				rozmiar--; //zmniejsza rozmiar tablicy o 1
			}

	}
}

void Tablica::Dodaj(int indeks, int wartosc) //Dodawanie
{
	int* Tab;
	Tab = new int[rozmiar + 1]; //pomocnicza tablica
	if (rozmiar == 0) {Tablica();}
	else {
		if (indeks == 0) // jezeli poczatek tablicy
		{
			Tab[0] = wartosc;
			for (int i = 1; i < rozmiar+1; i++)
			{
				Tab[i] = tablica[i-1]; //przesuwa na i-ty indeks wartosc i-1
			}
			delete[] tablica;
			tablica = Tab;
			rozmiar++; //zwieksza rozmiar tablicy o 1
		}

		else if (indeks == rozmiar) //jezeli za ostatnim elementem tablicy
		{
			for (int i = 0; i < rozmiar+1; i++)
			{
				Tab[i] = tablica[i];
			}
			Tab[indeks] = wartosc;
			delete[] tablica;
			tablica = Tab;
			rozmiar++; //zwieksza rozmiar tablicy o 1
		}

		else //w kazdym innym przypadku
		{
			for (int i = 0; i < indeks; i++) //i = indeks -> zaczyna petle od zadanego miejsca
			{
				Tab[i] = tablica[i];
			}
			Tab[indeks] = wartosc;
			for (int i = indeks+1; i < rozmiar+1; i++) //i = indeks -> zaczyna petle od zadanego miejsca
			{
				Tab[i] = tablica[i-1];
			}
			delete[] tablica;
			tablica = Tab;
			rozmiar++; //zwieksza rozmiar tablicy o 1
		}

	}

}

void Tablica::Wyszukaj(int liczba)
{
	bool czyjest = false;
	for (int i = 0; i < rozmiar; i++)
	{
		if (tablica[i] == liczba) { czyjest = true; }
	}
	if (czyjest) cout <<liczba<< " jest w tablicy."<<endl;
	if (!czyjest) cout<<"Nie ma "<<liczba << " w tablicy." << endl;
}

void Tablica::Wyswietl()
{
	cout << "Tablica:" << endl;
	for (int i = 0; i < rozmiar; i++)
	{
		cout << tablica[i] << endl;
	}
}