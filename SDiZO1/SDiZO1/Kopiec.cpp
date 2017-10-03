#include "stdafx.h"
#include "Kopiec.h"
#include <fstream>
#include <stdlib.h> 
#include <time.h>  
#include <math.h>


Kopiec::Kopiec(void)
{
	rozmiar = 1;
	tablica = new int[rozmiar];
	cr = cl = cp = "  ";
	cr[0] = 218; cr[1] = 196;
	cl[0] = 192; cl[1] = 196;
	cp[0] = 179;
}

Kopiec::Kopiec(int N)
{
	cr = cl = cp = "  ";
	cr[0] = 218; cr[1] = 196;
	cl[0] = 192; cl[1] = 196;
	cp[0] = 179;
	srand(time(NULL));
	//int wartosc;
	rozmiar = N;
	tablica = new int[rozmiar];
	int wartosc;
	wartosc = rand();
	tablica[0] = wartosc; //tworzy korzen
	for (int i = 1; i < rozmiar; i++)
	{
		wartosc = rand();
		tablica[i] = wartosc; //dodaje losowa wartosc do drzewa
		NaprawOdDolu(i); //naprawia od dolu
	}
}

Kopiec::Kopiec(string nazwa_pliku) //Odczyt z pliku
{
	cr = cl = cp = "  ";
	cr[0] = 218; cr[1] = 196;
	cl[0] = 192; cl[1] = 196;
	cp[0] = 179;
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
	plik >> wartosc;
	tablica[0] = wartosc; //tworzy korzen
	for (int i = 1; i < rozmiar; i++)
	{
		plik >> wartosc;
		tablica[i] = wartosc; //dodaje odczytana wartosc do drzewa
		NaprawOdDolu(i); //naprawia od dolu
	}
		cout << "Wczytano dane." << endl;
		plik.close();
}

Kopiec::~Kopiec(void)
{
	delete tablica;
	tablica = NULL;
}

//--------------------------------------------------

void Kopiec::Dodaj(int wartosc) //Dodawanie na koniec kopca
{
	//zrobienie miejsca dla nowej wartosci
	int* Tab;
	Tab = new int[this->rozmiar + 1];//pomocnicza tablica
	int pom = this->rozmiar;
	for (int i = 0; i < rozmiar; i++)
	{
		Tab[i] = tablica[i];
	}
	Tab[rozmiar] = wartosc;
	delete[] tablica;
	tablica = new int[pom + 1];
	this->rozmiar = pom + 1;
	for (int i = 0; i < rozmiar; i++)
	{
		tablica[i] = Tab[i];
	}
	//------------------------------------------------
	NaprawOdDolu(rozmiar - 1); //naprawienie struktury po dodaniu el. na koniec kopca
}

void Kopiec::NaprawOdDolu(int indeks)
{
	//Naprawa od dolu
	int i = indeks; //przypisuje do "i" indeks sprawdzanego potomka
	int pom = 0; //zmienna pomocnicza
	int k = (int)(floor((i - 1) / 2)); //indeks rodzica
	if (tablica[i] > tablica[k] && i != 0) //je¿eli wartoœæ syna jest wieksza od wartosci ojca
	{
		do
		{
			if (i == 0) { break; }
			else
			{
				pom = tablica[i];
				tablica[i] = tablica[k];
				tablica[k] = pom;
				i = k; //"i" do kolejnego obrotu petli zamienione na indeks rodzica
				k = (int)(floor((i - 1) / 2)); //obliczenie nowego indeksu rodzica dla nowego Tab[i]
			}
		} while (tablica[i] > tablica[k] /*|| i != 0*/); //warunek zakonczenia petli: rodzic ma wieksza wartosc, lub gdy syn dojdzie do korzenia
	}
}

void Kopiec::NaprawOdGory(int indeks)
{
	int i = indeks; //przypisuje do "i" indeks sprawdzanego rodzica
	int pom = 0; //zmienna pomocnicza
	int lewy = 2*i + 1; //lewy syn
	int prawy = 2*i + 2; //prawy syn

	do{
		if (prawy >= rozmiar && lewy < rozmiar) //je¿eli wartoœæ lewego >= prawego lub prawy nie istnieje, a lewy istnieje to:
		{
			if (tablica[i] < tablica[lewy]) //sprawdza czy wartoœæ syna jest wieksza od wartosci ojca
			{
				pom = tablica[i];
				tablica[i] = tablica[lewy];
				tablica[lewy] = pom;
			}
		}
		else if (prawy < rozmiar) //je¿eli wartoœæ prawego > lewego i prawy istnieje to:
		{
			if (tablica[i] < tablica[lewy] && tablica[lewy] < tablica[prawy]) //sprawdza czy wartoœæ syna jest wieksza od wartosci ojca
			{
				pom = tablica[i];
				tablica[i] = tablica[prawy];
				tablica[prawy] = pom;
			}
			
			if (tablica[i] < tablica[lewy] && tablica[lewy] >= tablica[prawy]) //sprawdza czy wartoœæ syna jest wieksza od wartosci ojca
			{
				pom = tablica[i];
				tablica[i] = tablica[lewy];
				tablica[lewy] = pom;
			}
		}
		i = lewy; //"i" do kolejnego obrotu petli zamienione na indeks lewego potomka
		lewy = 2 * i + 1; //obliczenie indeksu lewego potomka
		prawy = 2 * i + 2; //obliczenie indeksu prawego potomka
	} while (lewy < rozmiar); //dopóki istnieje lewy syn, gdy lewy nie istnieje to prawy równie¿
}

bool Kopiec::Wyszukaj(int wartosc)
{
	for (int i = 0; i < rozmiar; i++)
	{
		if (tablica[i] == wartosc) { return true; }	
	}
	return false;
}

void Kopiec::UsunWierzcholek() //usuwa korzen
{
	if (rozmiar == 0) //sprawdza czy tablica istnieje
	{
		cout << "Brak kopca" << endl;
	}
	else if (rozmiar == 1) //sam korzen
	{
		rozmiar=0;
		tablica = new int[0];
	}
	else if (rozmiar == 2) //korzen + lewy potomek
	{
		int pom = tablica[1];
		rozmiar = 1;
		tablica = new int[1];
		tablica[0] = pom;
	}
	else //inne przypadki
	{
		int* Tab;
		Tab = new int[rozmiar - 1]; //pomocnicza tablica
		Tab[0] = tablica[rozmiar - 1]; //zamiana z ostatnim elementem
		for (int i = 1; i < rozmiar-1; i++)
		{
			Tab[i] = tablica[i]; //przekopiowanie reszty
		}
		delete[] tablica;
		tablica = Tab;
		rozmiar--; //zmniejsza rozmiar tablicy o 1
		NaprawOdGory(0); //naprawa od korzenia
	}
}


//Usuwanie
int Kopiec::Znajdz(int wartosc) //pierwsza napotkana wartosc od gory
{
	for (int i = 0; i < rozmiar; i++)
	{
		if (tablica[i] == wartosc) { return i; }
	}
	return 0;
}

void Kopiec::Usun(int indeks)
{
	if (indeks == 0) { UsunWierzcholek();}
	else
	{
		int* Tab;
		Tab = new int[rozmiar - 1]; //pomocnicza tablica
		for (int i = 0; i < indeks; i++) //kopiowanie elementów do momentu napotkania wartosci do usuniecia
		{
			Tab[i] = tablica[i];
		}
		Tab[indeks] = tablica[rozmiar - 1]; //usuniecie i zastapienie wartoscia ostatniego indeksu
		for (int i = indeks+1; i < rozmiar - 1; i++)
		{
			Tab[i] = tablica[i]; //przekopiowanie reszty
		}
		//delete[] tablica;
		tablica = Tab;
		rozmiar--; //zmniejsza rozmiar tablicy o 1
		NaprawOdGory(indeks); //naprawa od zadanego indeksu
	}
}
//-------

void Kopiec::Wyswietl(string sp, string sn, int indeks)
{
	
	/*for (int i = 0; i < rozmiar;i++)
		{
			cout << tablica[i] <<endl;
		}*/
	string s;

	if (indeks < rozmiar)
	{
		s = sp;
		if (sn == cr) s[s.length() - 2] = ' ';
		Wyswietl(s + cp, cr, 2 * indeks + 2);

		s = s.substr(0, sp.length() - 2);

		cout << s << sn << tablica[indeks] << endl;

		s = sp;
		if (sn == cl) s[s.length() - 2] = ' ';
		Wyswietl(s + cp, cl, 2 * indeks + 1);
	}


}