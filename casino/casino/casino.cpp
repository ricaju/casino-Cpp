// casino.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <ctime>
#include <cstdlib>
using namespace std;


void BrojKiC(int &kune, int &chipovi);  //treba ime za spremanje!
void Uplata(int &kune, int &chipovi);
void Isplata(int &kune, int &chipovi);
void Menu();
void IgreMenu();
void JednorukiJack(int &kune, int &chipovi);
void BacanjeKockica(int &kune, int &chipovi);
string karta(int n);

string ime;
void BrojKiC(int &kune, int &chipovi) {
	cout << "Trenutno imate: " << kune << "kuna"<< " i " << chipovi << " chipova" << endl;
}
void Uplata(int &kune, int &chipovi) {
	system("cls");
	int kolicinaK, ostatak;
	cout << "Koliko kuna zelite zamijeniti za chipove? 5kn = 1 chip" << endl;
	BrojKiC(kune, chipovi);
	cin >> kolicinaK;
	if (kolicinaK <= kune && kolicinaK % 5 == 0) {
		kune = kune - kolicinaK;
		chipovi = kolicinaK / 5;
		system("cls");
		Menu();
	}
	else if (kolicinaK <= kune && kolicinaK % 5 != 0) {
		ostatak = kolicinaK % 5;
		chipovi = kolicinaK / 5;
		kune = (kune - kolicinaK) - ostatak;
		system("cls");
		Menu();
	}
	else {
		cout << "Nemate dovoljno kuna za toliko chipova!";
		system("cls");
		Menu();
	}
}
void Isplata(int &kune, int &chipovi) {
	int isplata, dane;
	string za_spremanje;
	cout << "Jeste li sigurni da zelite zamijeniti chipove za kune? 1-da, 0-ne"<<endl;
	BrojKiC(kune, chipovi);
	cin >> dane;
	if (dane == 0) {
		system("cls");
		Menu();  
	}
	else {
		cout << "Unesite broj chipova koje zelite zamijeniti za kune (1chip = 5kn)";
		cin >> isplata;
		if (isplata <= chipovi) {
			chipovi = chipovi - isplata;
			kune = isplata * 5;
			za_spremanje = "\n" + to_string(isplata * 5);
			BrojKiC(kune, chipovi);
			ofstream output;
			output.open("Isplate.txt", ios::out | ios::app);
			output << za_spremanje;
			output.close();
		}
		else {
			cout << "Nemate toliki broj chipova za isplatu!";
			BrojKiC(kune, chipovi);
		}
	}
}
void Menu() {
	cout << "\t\t\t 1. Uplata chipova \t\t\t" << endl;
	cout << "\t\t\t 2. Isplata chipova \t\t\t" << endl;
	cout << "\t\t\t 3. Igre \t\t\t" << endl;   
	cout << "\t\t\t 4. Rezultati \t\t\t" << endl;
	cout << "\t\t\t 5. Izlaz \t\t\t" << endl;
	cout << endl;
}
void IgreMenu() {
	cout << "\t\t\t PONUDA IGARA: \t\t\t" << endl;
	cout << "\t\t\t 1. Jednoruki Jack \t\t\t" << endl;
	cout << "\t\t\t 2. Bacanje kockica \t\t\t" << endl;
	cout << "\t\t\t 3. Duplo ili nista \t\t\t" << endl;
	cout << "\t\t\t 4. Povratak u glavni menu \t\t\t" << endl;

}
void JednorukiJack(int &kune, int &chipovi) {
	int x, y, z, b = 1, a, unos;
	char c, d, e;
	string za_spremanje;
	srand(time(NULL));
	cout << "Unesite broj chipova koje zelite uloziti." << endl;
	cin >> unos;
	cout << "***** Za ostvareni dobitak, ulog se mnozi za 10 *****" << endl;
	cout << "-----> Imate pravo na 3 povlacenja rucki <-----"<<endl;
	if (unos > chipovi) {
		cout << "Nemate dovoljno chipova. Unesite ponovo: " << endl;
		cin >> unos;
		chipovi = chipovi - unos;
	}
	else {
		chipovi = chipovi - unos;
	}
	BrojKiC(kune, chipovi);
	for(int i = 0; i < 3; i++) {
		x = rand() % 4 + 1;
		y = rand() % 4 + 1;
		z = rand() % 4 + 1;
		if (x == 1) {
			c = '+';
		}
		else if (x == 2) {
			c = 'X';
		}
		else if (x == 3) {
			c = 'O';
		}
		else {
			c = '*';
		}
		if (y == 1) {
			d = '+';
		}
		else if (y == 2) {
			d = 'X';
		}
		else if (y == 3) {
			d = 'O';
		}
		else {
			d = '*';
		}
		if (z == 1) {
			e = '+';
		}
		else if (z == 2) {
			e = 'X';
		}
		else if (z == 3) {
			e = 'O';
		}
		else {
			e = '*';
		}
		cout << "Unesite broj 1 da zavrtite slot machine!" << endl;
		cin >> b;
		if (x == y && y == z) {
			cout << c << "\t" << d << "\t" << e << endl;
			cout << "Ostvarili ste DOBITAK!!!" << endl;
			chipovi = chipovi + unos * 10;
			za_spremanje = "\n" + to_string(unos * 10);
			BrojKiC(kune, chipovi);
			ofstream output;
			output.open("JednorukiJack.txt", ios::out | ios::app);
			output << za_spremanje;
			output.close();
			b = 0;
		}
		else {
			cout << c << "\t" << d << "\t" << e << endl;
			cout << "osvojili ste GUBITAK :( :( :(" << endl;
		}
	}
}
void BacanjeKockica(int &kune, int &chipovi) {
	string za_spremanje;
	srand(time(NULL));
	int a, b, c, d, bac;
	int unos;
	cout << "***Bacate kockice dva puta, ukoliko bacite više ulog se množi s dva" << endl;
	cout << "Unesite broj chipova koje zelite uloziti" << endl;
	cin >> unos;
	if (unos <= chipovi) {
		chipovi = chipovi - unos;
	}
	else {
		cout << "Nemate dovoljno chipova za igru" << endl;
	}
	BrojKiC(kune, chipovi);
	
	cout << "Pritisnite 1 za bacanje kockica" << endl;
	cin.ignore();
	cin >> bac;
	a = rand() % 6 + 1;
	b = rand() % 6 + 1;
	cout << "Vas prvi broj je: " << a << " dok je kompjuter bacio: " << b<<endl;  
	c = rand() % 6 + 1;
	d = rand() % 6 + 1;
	cout << "Vas drugi broj je: " << c << " dok je kompjuter bacio: " << d<<endl;

	if (a + c > b + d) {    //treba vidjeti koji broj je veci od dva bacanja!!!
		cout << "**DOBITAK**" << endl;
		cout << "Ukopno ste bacili: " << a + c << " kompjuter je ukupno bacio: " << b + d;
		chipovi = chipovi + unos * 2;
		za_spremanje = "\n" + to_string(unos * 2);
		ofstream output;
		output.open("BacanjeKockica.txt", ios::out | ios::app);
		output << za_spremanje;
		output.close();
	}
	else if (a + c < b + d) {
		cout << " **GUBITAK**" << endl;
		cout << "Ukopno ste bacili: " << a + c << " kompjuter je ukupno bacio: " << b + d;
		chipovi = chipovi - unos;
	}
	else {
		cout << "**IZJEDNACENO**" << endl;
		cout << "ulog vam se vraca" << endl;
		cout << "Ukopno ste bacili: " << a + c << "kompjuter je ukupno bacio: " << b + d;
		chipovi = chipovi + unos;
	}
	

}
void DuploiliNista(int &kune, int &chipovi) {
	string za_spremanje;
	srand(time(NULL));
	int ulog;
	int brojac = 52;
	char unos = 'x';
	int karta_igrac, karta_kompjuter;
	vector<int> karte;
	karte.push_back(0);
	for (int i = 1; i <= 52; i++) {
		karte.push_back(i);
	}
	
	cout << "Kartu vucete vi i racunalo" << endl;
	cout << "Pobjednik je onaj koji dobi vecu kartu" << endl;
	cout << "nakon podijele karata, mozete igrati duplo ili nista" << endl;
	BrojKiC(kune, chipovi);
	cout << "unesite svoj ulog:" << endl;
	cin >> ulog;
	do {
		if (ulog > chipovi) {
			cout << "Nemate dovoljno chipova" << endl;
			cout << "unesite ponovno ulog:" << endl;
			cin >> ulog;
		}
		else {
			chipovi = chipovi - ulog;
			while (karte.size() != 1 && unos == 'x') {
				cout << "unesite x za izvlacenje karte!";
				cin >> unos;
				int karta_i, karta_k;
				karta_igrac = (rand() % brojac) + 1;
				cout << "Vasa karta: " << karta(karte[karta_igrac]) << endl;
				karta_i = karte[karta_igrac];
				karte.erase(karte.begin() + karta_igrac);
				brojac--;
				karta_kompjuter = (rand() % brojac) + 1;
				cout << "Karta racunala: " << karta(karte[karta_kompjuter]) << endl;
				karta_k = karte[karta_kompjuter];
				karte.erase(karte.begin() + karta_kompjuter);
				brojac--;
				if ((karta_i % 13) + 1 > (karta_k % 13) + 1) {
					cout << "Pobijedili ste\n\n";
					chipovi += ulog * 2;
				}
				else if ((karta_i % 13) + 1 == (karta_k % 13) + 1) {
					cout << "Karte iste jacine!\n\n";
					chipovi += ulog;
				}
				else {
					cout << "Izgubili ste!\n\n";
					chipovi -= ulog;
				}
				if (chipovi >= (ulog * 2)) {
					char izbor;
					cout << "Zelite li duplo ili nista? D/N: ";
					cin >> izbor;
					if (izbor == 'D' || izbor == 'd') {
						ulog *= 2;
						continue;
					}
					else {
						unos = 'k';
						break;
					}
				}
				else {
					cout << "Nemate dovoljno chipova!\n";
					break;
				}
			}
		}
		} while (unos == 'x' && ulog != 0);
	} 
void ZaSpremanje(int chipovi, string file) {
	ofstream output;
	string za_krcati;
	output.open(file, ios::app);
	za_krcati = ime + " " + to_string(chipovi) + "\n";
	output << za_krcati;
	output.close();
}  //koristit funkciju za spremanje

void HighScore(){} // napraviti highscore


string karta(int n) {
	string boja, znak;
	if (n > 0 && n <= 13) {
		boja = 'pik';
	}
	else if (n > 13 && n <= 26) {
		boja = 'tref';
	}
	else if (n > 26 && n <= 39) {
		boja = 'srce';
	}
	else {
		boja = 'karo';
	}

	switch(n % 13){
		case 1: 
			znak = '2';
			break;
		case 2:
			znak = '3';
			break;
		case 3:
			znak = '4';
			break;
		case 4:
			znak = '5';
			break;
		case 5:
			znak = '6';
			break;
		case 6:
			znak = '7';
			break;
		case 7:
			znak = '8';
			break;
		case 8:
			znak = '9';
			break;
		case 9:
			znak = '10';
			break;
		case 10:
			znak = 'J';
			break;
		case 11:
			znak = 'D';
			break;
		case 12:
			znak = 'K';
			break;
		case 13:
			znak = 'AS';
			break;

	}
	return boja + " " + znak;
	
}


int main()
{	
	int kune = 0;
	int chipovi = 0;
	string ime;
	int odabir = 6;
	int odabirI = 5;
	cout << "\t\t\t DOBRODOSLI U CASINO \t\t\t " << endl;
	cout << "Unesite vase ime:" << endl;
	cin >> ime;
	cout << "S koliko kuna dolazite u Casino?" << endl;
	cin >> kune;
	system("cls");
	Menu();
	cout << endl;
	
	do {
		system("cls");
		Menu();
		cout << "Unesite broj uz zeljeni odabir" << endl;
		cin >> odabir;
		switch (odabir) {
			case 1:
				system("cls");
				Uplata(kune, chipovi);
				system("pause");
				break;
			case 2:
				system("cls");
				Isplata(kune, chipovi);
				system("pause");
				break;
			case 3:
			
					system("cls");
					IgreMenu();
					cout << "Odaberite broj uz igru koju zelite!";
					cin >> odabirI;
					do {
					switch (odabirI) {
					case 1:
						system("cls");
						JednorukiJack(kune, chipovi);
						system("pause");
						break;
					case 2:
						system("cls");
						BacanjeKockica(kune, chipovi);
						system("pause");
						break;
					case 3:
						system("cls");
						DuploiliNista(kune, chipovi);
						system("pause");
						break;
					}
				} while (odabirI != 4);
				system("pause");
				break;
			case 4:
				system("cls");
				//HighScore();
				//system("pause");
				//break;
			case 5:
				odabir = 5;

		}
	} while (odabir != 5);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
