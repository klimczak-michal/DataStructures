#include "stdafx.h"
#include "DrzewoCzCz.h"
#include <fstream>
#include <stdlib.h> 
#include <time.h> 

DrzewoCzCz::DrzewoCzCz(string nazwa_pliku) //Odczyt z pliku
{
	cr = cl = cp = "  ";
	cr[0] = 218; cr[1] = 196;
	cl[0] = 192; cl[1] = 196;
	cp[0] = 179;
	straznik.kolor = 'B';          // Inicjujemy stra¿nika
	straznik.gora = &straznik;
	straznik.lewy = &straznik;
	straznik.prawy = &straznik;
	korzen = &straznik;           // Korzeñ wskazuje stra¿nika

	fstream plik;
	plik.open(nazwa_pliku);
	if (plik.is_open() == false)
	{
		cout << "Nie udalo sie otworzyc pliku!" << endl;
		return;
	}
	int N, wartosc;
	plik >> N;
	int* tab = new int[N];
	for (int i = 0; i < N; i++)
	{
		plik >> wartosc;
		tab[i] = wartosc;
	}
	cout << "Wczytano dane." << endl;
	plik.close();

	for (int i = 0; i < N; i++)
	{
		Wstaw(tab[i]);
	}
}
DrzewoCzCz::DrzewoCzCz(int N) //Losowe generowanie
{
	cr = cl = cp = "  ";
	cr[0] = 218; cr[1] = 196;
	cl[0] = 192; cl[1] = 196;
	cp[0] = 179;
	straznik.kolor = 'B';          // Inicjujemy stra¿nika
	straznik.gora = &straznik;
	straznik.lewy = &straznik;
	straznik.prawy = &straznik;
	korzen = &straznik;           // Korzeñ wskazuje stra¿nika

	srand(time(NULL));
	int *tab = new int[N];

	for (int i = 0; i < N; i++)
	{
		tab[i] = rand();
	}

	for (int i = 0; i < N; i++)
	{
		Wstaw(tab[i]);
	}

}

DrzewoCzCz::DrzewoCzCz()
{
	cr = cl = cp = "  ";
	cr[0] = 218; cr[1] = 196;
	cl[0] = 192; cl[1] = 196;
	cp[0] = 179;
	straznik.kolor = 'B';          // Inicjujemy stra¿nika
	straznik.gora = &straznik;
	straznik.lewy = &straznik;
	straznik.prawy = &straznik;
	korzen = &straznik;           // Korzeñ wskazuje stra¿nika
}


DrzewoCzCz::~DrzewoCzCz()
{
	UsunDrzewo(korzen); 
}

void DrzewoCzCz::UsunDrzewo(Wezel * podany)
{
	if (podany != &straznik)
	{
		UsunDrzewo(podany->lewy);   // usuwamy lewe poddrzewo
		UsunDrzewo(podany->prawy);  // usuwamy prawe poddrzewo
		delete podany;              // usuwamy sam wêze³
	}
}


void DrzewoCzCz::Wyswietl(string sp, string sn, Wezel * podany)
{
	/*if (podany != &straznik)
	{
		Wyswietl(podany->prawy);
		cout << " " << podany->kolor << ":" << podany->wartosc << endl;

		Wyswietl(podany->lewy);
	}*/

	string t;

	if (podany != &straznik)
	{
		t = sp;
		if (sn == cr) t[t.length() - 2] = ' ';
		Wyswietl(t + cp, cr, podany->prawy);

		t = t.substr(0, sp.length() - 2);
		cout << t << sn << podany->kolor << ":" << podany->wartosc << endl;

		t = sp;
		if (sn == cl) t[t.length() - 2] = ' ';
		Wyswietl(t + cp, cl, podany->lewy);
	}
}

void DrzewoCzCz::print()
{
	Wyswietl("", "", korzen);
}

Wezel * DrzewoCzCz::Znajdz(int wartosc)
{
	Wezel * pom;

	pom = korzen;
	while ((pom != &straznik) && (pom->wartosc != wartosc)) //dopoki nie znajdzie, albo dojdzie do konca drzewa
		if (wartosc < pom->wartosc) pom = pom->lewy; //jak mniejszy to szuka w lewym poddrzewie
		else pom = pom->prawy;
		if (pom == &straznik) return NULL;
		return pom;
}

bool DrzewoCzCz::CzyJest(int wartosc)
{
	Wezel * pom;

	pom = korzen;
	while ((pom != &straznik) && (pom->wartosc != wartosc)) //dopoki nie znajdzie, albo dojdzie do konca drzewa
		if (wartosc < pom->wartosc) pom = pom->lewy; //jak mniejszy to szuka w lewym poddrzewie
		else pom = pom->prawy;

		if (pom == &straznik) {return false;} //jezeli doszedl do konca to znaczy ze nie znalazl
		return true; //w przeciwnym przypadku znalazl
}

Wezel * DrzewoCzCz::NajmniejszyWezel(Wezel * podany)
{
	if (podany != &straznik)
		while (podany->lewy != &straznik) podany = podany->lewy;
	return podany;
}

Wezel * DrzewoCzCz::Nastepnik(Wezel * podany)
{
	Wezel * pom;

	if (podany != &straznik)
	{
		if (podany->prawy != &straznik) return NajmniejszyWezel(podany->prawy);
		else
		{
			pom = podany->gora;
			while ((pom != &straznik) && (podany == podany->prawy))
			{
				podany = pom;
				pom = pom->gora;
			}
			return pom;
		}
	}
	return &straznik;
}

void DrzewoCzCz::Rotacja_L(Wezel * A)
{
	Wezel *B, *pom;

	B = A->prawy;
	if (B != &straznik)
	{
		pom = A->gora;
		A->prawy = B->lewy;
		if (A->prawy != &straznik) A->prawy->gora = A;

		B->lewy = A;
		B->gora = pom;
		A->gora = B;

		if (pom != &straznik)
		{
			if (pom->lewy == A) pom->lewy = B; else pom->prawy = B;
		}
		else korzen = B;
	}
}

void DrzewoCzCz::Rotacja_R(Wezel * A)
{
	Wezel *B, *pom;

	B = A->lewy;
	if (B != &straznik)
	{
		pom = A->gora;
		A->lewy = B->prawy;
		if (A->lewy != &straznik) A->lewy->gora = A;

		B->prawy = A;
		B->gora = pom;
		A->gora = B;

		if (pom != &straznik)
		{
			if (pom->lewy == A) pom->lewy = B; else pom->prawy = B;
		}
		else korzen = B;
	}
}

void DrzewoCzCz::Wstaw(int wartosc)
{
	Wezel *X, *Y;

	X = new Wezel;        // Nowy wêze³
	X->lewy = &straznik;          
	X->prawy = &straznik;
	X->gora = korzen;
	X->wartosc = wartosc;
	if (X->gora == &straznik) korzen = X; // X staje siê korzeniem
	else
		while (true)             // Szukamy liœcia do zast¹pienia przez X
		{
		if (wartosc < X->gora->wartosc)
		{
			if (X->gora->lewy == &straznik)
			{
				X->gora->lewy = X;  // X zastêpuje lewy liœæ
				break;
			}
			X->gora = X->gora->lewy;
		}
		else
		{
			if (X->gora->prawy == &straznik)
			{
				X->gora->prawy = X; // X zastêpuje prawy liœæ
				break;
			}
			X->gora = X->gora->prawy;
		}
		}
	X->kolor = 'R';         // Wêze³ kolorujemy na czerwono
	while ((X != korzen) && (X->gora->kolor == 'R')) //dopoki X nie jest korzeniem i ojciec jest czerwony
	{
		if (X->gora == X->gora->gora->lewy) //ojciec X jest lewym synem dziadka X
		{
			Y = X->gora->gora->prawy; // Y -> wujek X

			if (Y->kolor == 'R') //Przypadek 1 - wujek jest czerwony
			{
				X->gora->kolor = 'B';
				Y->kolor = 'B';
				X->gora->gora->kolor = 'R';
				X = X->gora->gora;
				continue;
			}

			if (X == X->gora->prawy) // Przypadek 2 - X jest prawym synem 
			{
				X = X->gora;
				Rotacja_L(X);
			}

			X->gora->kolor = 'B'; //else
			X->gora->gora->kolor = 'R';
			Rotacja_R(X->gora->gora);
			break;
		}
		else
		{                  // Przypadki lustrzane
			Y = X->gora->gora->lewy;

			if (Y->kolor == 'R') // Przypadek 1
			{
				X->gora->kolor = 'B';
				Y->kolor = 'B';
				X->gora->gora->kolor = 'R';
				X = X->gora->gora;
				continue;
			}

			if (X == X->gora->lewy) // Przypadek 2
			{
				X = X->gora;
				Rotacja_R(X);
			}

			X->gora->kolor = 'B'; //else
			X->gora->gora->kolor = 'R';
			Rotacja_L(X->gora->gora);
			break;
		}
	}
	korzen->kolor = 'B';
}

void DrzewoCzCz::Usun(Wezel *X)
{
	Wezel *W, *Y, *Z;

	if ((X->lewy == &straznik) || (X->prawy == &straznik)) Y = X;
	else                                    Y = Nastepnik(X);

	if (Y->lewy != &straznik) Z = Y->lewy;
	else Z = Y->prawy;

	Z->gora = Y->gora;

	if (Y->gora == &straznik) korzen = Z;
	else if (Y == Y->gora->lewy) Y->gora->lewy = Z;
	else Y->gora->prawy = Z;

	if (Y != X) X->wartosc = Y->wartosc;

	if (Y->kolor == 'B')   // Naprawa struktury drzewa czerwono-czarnego
		while ((Z != korzen) && (Z->kolor == 'B'))
			if (Z == Z->gora->lewy)
			{
		W = Z->gora->prawy;

		if (W->kolor == 'R')
		{              // Przypadek 1
			W->kolor = 'B';
			Z->gora->kolor = 'R';
			Rotacja_L(Z->gora);
			W = Z->gora->prawy;
		}

		if ((W->lewy->kolor == 'B') && (W->prawy->kolor == 'B'))
		{              // Przypadek 2
			W->kolor = 'R';
			Z = Z->gora;
			continue;
		}

		if (W->prawy->kolor == 'B')
		{              // Przypadek 3
			W->lewy->kolor = 'B';
			W->kolor = 'R';
			Rotacja_R(W);
			W = Z->gora->prawy;
		}

		W->kolor = Z->gora->kolor; // Przypadek 4
		Z->gora->kolor = 'B';
		W->prawy->kolor = 'B';
		Rotacja_L(Z->gora);
		Z = korzen;         // To spowoduje zakoñczenie pêtli
			}
			else
			{                //B Przypadki lustrzane
				W = Z->gora->lewy;

				if (W->kolor == 'R')
				{              // Przypadek 1
					W->kolor = 'B';
					Z->gora->kolor = 'R';
					Rotacja_R(Z->gora);
					W = Z->gora->lewy;
				}

				if ((W->lewy->kolor == 'B') && (W->prawy->kolor == 'B'))
				{              // Przypadek 2
					W->kolor = 'R';
					Z = Z->gora;
					continue;
				}

				if (W->lewy->kolor == 'B')
				{              // Przypadek 3
					W->prawy->kolor = 'B';
					W->kolor = 'R';
					Rotacja_L(W);
					W = Z->gora->lewy;
				}

				W->kolor = Z->gora->kolor;  // Przypadek 4
				Z->gora->kolor = 'B';
				W->lewy->kolor = 'B';
				Rotacja_R(Z->gora);
				Z = korzen;         // To spowoduje zakoñczenie pêtli
			}

	Z->kolor = 'B';

	delete Y;
}