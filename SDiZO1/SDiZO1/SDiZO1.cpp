// SDiZO1.cpp : Defines the entry point for the console application.
/*
Poprawione:
- dodany dekonstruktor do listy
- poprawione usuwanie w liœcie (usuwa³o wszystkie duplikaty i wysypywa³o program)
- poprawione dodawanie do listy (mo¿na dodaæ za ostatni element i przed ka¿dy dowolny)
- poprawione wyswietlanie kopca i drzewa czerwono-czarnego
*/

#include "stdafx.h"
#include "Tablica.h"
#include "Lista.h"
#include "Kopiec.h"
#include "DrzewoCzCz.h"
#include <iostream>
#include <string>
#include <conio.h>
#include <Windows.h>
using namespace std;



LARGE_INTEGER startTimer()
{
	LARGE_INTEGER start;
	DWORD_PTR oldmask = SetThreadAffinityMask(GetCurrentThread(), 0);
	QueryPerformanceCounter(&start);
	SetThreadAffinityMask(GetCurrentThread(), oldmask);
	return
		start;
}
LARGE_INTEGER endTimer()
{
	LARGE_INTEGER stop;
	DWORD_PTR oldmask = SetThreadAffinityMask(GetCurrentThread(), 0);
	QueryPerformanceCounter(&stop);
	SetThreadAffinityMask(GetCurrentThread(), oldmask);
	return
		stop;
}



void MenuTablica(Tablica *Tab)
{
	char wybor;
	string nazwa_pliku;
	int wartosc, indeks;
	do{
		cout << "TABLICA" << endl << "1. Zbuduj z pliku" << endl << "2. Usun" << endl << "3. Dodaj" << endl << "4. Znajdz" << endl << "5. Utworz losowo" << endl << "6. Wyswietl" << endl << "Escape - wroc" << endl << "Wybierz opcje: " << endl;
		wybor = _getch();
		switch (wybor)
		{
		case '1':
			delete Tab;
			Tab = NULL;
			cout << "Podaj nazwe pliku (sama nazwa, rozszerzenie .txt jest dodawane autmatycznie): " << endl;
			cin >> nazwa_pliku;
			nazwa_pliku = nazwa_pliku + ".txt";
			Tab = new Tablica(nazwa_pliku);
			break;
		case '2':
			cout << "Podaj nr indeksu ktorego wartosc chcesz usunac: " << endl;
			cin >> indeks;
			Tab->Usun(indeks);
			break;
		case '3':
			cout << "Podaj nr indeksu, do ktorego chcesz wstawic wartosc: " << endl;
			cin >> indeks;
			cout << "Podaj liczbe" << endl;
			cin >> wartosc;
			Tab->Dodaj(indeks, wartosc);
			break;
		case '4':
			cout << "Podaj liczbe, ktorej szukasz" << endl;
			cin >> wartosc;
			Tab->Wyszukaj(wartosc);
			break;
		case '5':
			delete Tab;
			Tab = NULL;
			cout << "Podaj rozmiar losowo wygenerowanej tablicy: " << endl;
			cin >> indeks;
			Tab = new Tablica(indeks);
			break;
		case '6':
			Tab->Wyswietl();
			break;
		case 27: break;
		default:
			cout << "Zla wartosc" << endl;
			break;
		}
	} while (wybor != 27);
}

void MenuLista(Lista *List)
{
	char wybor;
	string nazwa_pliku;
	int wartosc, numer;
	bool jest;
	do{
		cout << "LISTA DWUKIERRUNKOWA" << endl << "1. Zbuduj z pliku" << endl << "2. Usun" << endl << "3. Dodaj" << endl << "4. Znajdz" << endl << "5. Utworz losowo" << endl << "6. Wyswietl" << endl << "Escape - wroc" << endl << "Wybierz opcje: " << endl;
		wybor = _getch();
		switch (wybor)
		{
		case '1':
			delete List;
			List = NULL;
			cout << "Podaj nazwe pliku (sama nazwa, rozszerzenie .txt jest dodawane autmatycznie): " << endl;
			cin >> nazwa_pliku;
			nazwa_pliku = nazwa_pliku + ".txt";
			List = new Lista(nazwa_pliku);
			break;
		case '2':
			cout << "Podaj wartosc ktora chcesz usunac: " << endl;
			cin >> numer;
			List->Usun(numer);
			break;
		case '3':
			cout << "Podaj nr indeksu, do ktorego chcesz wstawic wartosc: " << endl;
			cin >> numer;
			cout << "Podaj liczbe" << endl;
			cin >> wartosc;
			List->Dodaj(numer, wartosc);
			break;
		case '4':
			cout << "Podaj liczbe, ktorej szukasz" << endl;
			cin >> wartosc;
			jest = List->Wyszukaj(wartosc);
			if (jest) cout << "Jest w liscie" << endl;
			if (!jest) cout << "Nie ma w liscie" << endl;

			break;
		case '5':
			delete List;
			List = NULL;
			cout << "Podaj rozmiar losowo wygenerowanej tablicy: " << endl;
			cin >> numer;
			List = new Lista(numer);
			break;
		case '6':
			List->Wyswietl();
			break;
		case 27: break;
		default:
			cout << "Zla wartosc" << endl;
			break;
		}
	} while (wybor != 27);
}

void MenuKopiec(Kopiec* Tab)
{
	char wybor;
	string nazwa_pliku;
	int wartosc, numer;
	bool jest;
	do{
		cout << "KOPIEC BINARNY" << endl << "1. Zbuduj z pliku" << endl << "2. Usun" << endl << "3. Dodaj" << endl << "4. Znajdz" << endl << "5. Utworz losowo" << endl << "6. Wyswietl" << endl << "Escape - wroc" << endl << "Wybierz opcje: " << endl;
		wybor = _getch();
		switch (wybor)
		{
		case '1':
			delete Tab;
			Tab = NULL;
			cout << "Podaj nazwe pliku (sama nazwa, rozszerzenie .txt jest dodawane autmatycznie): " << endl;
			cin >> nazwa_pliku;
			nazwa_pliku = nazwa_pliku + ".txt";
			Tab = new Kopiec(nazwa_pliku);
			break;
		case '2':
			cout << "Podaj wartosc, ktora chcesz usunac: " << endl;
			cin >> wartosc;
			Tab->Usun(Tab->Znajdz(wartosc));
			break;
		case '3':
			cout << "Podaj wartosc ktora chcesz dodac: " << endl;
			cin >> wartosc;
			Tab->Dodaj(wartosc);
			break;
		case '4':
			cout << "Podaj liczbe, ktorej szukasz" << endl;
			cin >> wartosc;
			jest = Tab->Wyszukaj(wartosc);
			if (jest) cout << "Jest w kopcu" << endl;
			if (!jest) cout << "Nie ma w kopcu" << endl;
			break;
		case '5':
			delete Tab;
			Tab = NULL;
			cout << "Podaj rozmiar losowo wygenerowanego kopca: " << endl;
			cin >> numer;
			Tab = new Kopiec(numer);
			break;
		case '6':
			Tab->Wyswietl("", "",0);
			break;
		case 27: break;
		default:
			cout << "Zla wartosc" << endl;
			break;
		}
	} while (wybor != 27);
}

void MenuDrzewo(DrzewoCzCz* Drzewo)
{
	char wybor;
	string nazwa_pliku;
	int wartosc, numer; 
	bool czyjest;
	do{
		cout << "DRZEWO CZERWONO-CZARNE" << endl << "1. Zbuduj z pliku" << endl << "2. Usun" << endl << "3. Dodaj" << endl << "4. Znajdz" << endl << "5. Utworz losowo" << endl << "6. Wyswietl" << endl << "Escape - wroc" << endl << "Wybierz opcje: " << endl;
		wybor = _getch();
		switch (wybor)
		{
		case '1':
			delete Drzewo;
			Drzewo = NULL;
			cout << "Podaj nazwe pliku (sama nazwa, rozszerzenie .txt jest dodawane autmatycznie): " << endl;
			cin >> nazwa_pliku;
			nazwa_pliku = nazwa_pliku + ".txt";
			Drzewo = new DrzewoCzCz(nazwa_pliku);
			break;
		case '2':
			cout << "Podaj wartosc, ktora chcesz usunac: " << endl;
			cin >> wartosc;
			if (Drzewo->CzyJest(wartosc) == true)
			{
				Drzewo->Usun(Drzewo->Znajdz(wartosc));
			}
			break;
		case '3':
			cout << "Podaj wartosc ktora chcesz dodac: " << endl;
			cin >> wartosc;
			Drzewo->Wstaw(wartosc);
			break;
		case '4':
			cout << "Podaj liczbe, ktorej szukasz" << endl;
			cin >> wartosc;
			czyjest = Drzewo->CzyJest(wartosc);
			if (czyjest) cout << wartosc << " jest w drzewie." << endl;
			if (!czyjest) cout << "Nie ma " << wartosc << " w drzewie." << endl;
			break;
		case '5':
			delete Drzewo;
			Drzewo = NULL;
			cout << "Podaj rozmiar losowo wygenerowanego kopca: " << endl;
			cin >> numer;
			Drzewo = new DrzewoCzCz(numer);
			break;
		case '6':
			Drzewo->print();
			break;
		case 27: break;
		default:
			cout << "Zla wartosc" << endl;
			break;
		}
	} while (wybor != 27);
}


int _tmain(int argc, _TCHAR* argv[])
{
	//testowanie czasu
	/*
	Tablica* Tab = new Tablica();
	string nazwa_pliku;
	int wartosc=0, indeks=0;

	cout << "Podaj rozmiar losowo wygenerowanej tablicy: " << endl;
	cin >> indeks;
	LARGE_INTEGER performanceCountStart, performanceCountEnd;
	performanceCountStart = startTimer(); //zapamiêtujemy czas pocz¹tkowy
	Tab = new Tablica(indeks);  //tutaj funkcje, których mierzymy wydajnoœæ
	performanceCountEnd = endTimer(); //zapamiêtujemy koniec czasu
	double
		tm = performanceCountEnd.QuadPart
		-
		performanceCountStart.QuadPart;
	cout << endl <<
		"Time:"
		<< tm << endl;
	*/

	//menu g³owne programu
	Tablica* Tab = new Tablica();
	Lista* List = new Lista();
	Kopiec* BTree = new Kopiec();
	DrzewoCzCz* RBTree = new DrzewoCzCz();
	
	char wybor;
	do{
		cout << "1. Tablica" << endl << "2. Lista dwukierunkowa" << endl << "3. Kopiec binarny" << endl << "4. Drzewo czerwono-czarne" << endl << "Escape - koniec" << endl << "Wybierz opcje: " << endl;
		wybor = _getch();
		switch (wybor)
		{
		case '1': MenuTablica(Tab); break;
		case '2': MenuLista(List); break;
		case '3': MenuKopiec(BTree); break;
		case '4': MenuDrzewo(RBTree); break;
		case '27': break;
		default: cout << "Zla opcja"; break;
		}
	} while (wybor != 27);

	delete Tab;
	Tab = NULL;
	delete List;
	List = NULL;
	delete BTree;
	BTree = NULL;
	delete RBTree;
	RBTree = NULL;

	return 0;
}