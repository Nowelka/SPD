#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

class Zadania
{
    public:
    	Zadania(int p1, int w1, int d1, int tindeks, int rozm, int it) : p(p1), w(w1), d(d1), indeks(tindeks), rozmiar(rozm), iter(it){};
    	int p, w, d, indeks, rozmiar, iter;
};
class Wyniki {
public:
	Wyniki(int in, int sum, int t): indeksy(in), suma(sum), czasCmax(t), flaga(0), A(0), Z(0) {};	
	int indeksy;	//idenksy dla ktorych jest to obliczone
	int suma;		//suma - najkorzystniejsza oplata
	int czasCmax;	//czas - czas dla takiego polaczenia 
	int flaga;		//flaga - czy ustawiany byla suma(w wersji rozszerzonej tu powinno byc cos co przechowuje wszsystkie mozliwosci sumy)
	vector <int> kolejnosc;
	int A;
	int Z;
};
int uzupelnianieWektoraWynikow(vector <Zadania*> &, vector <Wyniki*> &, int);
int programowanieDynamiczne(vector <Zadania*> &, vector <Wyniki*> &, int);
void wyswietlanieWynikow(vector <Wyniki*> &, int);
int AZ(int, int, int, int);
void odczytZPliku(vector <Zadania*> &, string);
void zapisDoPliku(vector <Zadania*> &, string);
void bin(int val) {
	for (int i = 31; i >= 0; i--) {
		if((i+1) % 8 == 0)
			cout << " ";
		cout << ((val >> i) % 2);
	}
};

int main() {
	vector <Zadania*> wektor01;
	odczytZPliku(wektor01, "data100.txt");//"moje.txt");
	
	int rozmiar = wektor01.size() + 1;

	vector <Wyniki*> tablica;
	
	int indeks = uzupelnianieWektoraWynikow(wektor01,tablica, rozmiar);
	wyswietlanieWynikow(tablica, rozmiar);
	programowanieDynamiczne(wektor01, tablica, indeks);
	wyswietlanieWynikow(tablica, rozmiar);
	
	int tmp = 0;
	Wyniki *wyn;
	for(int i = 0; i < indeks; i++) {
		wyn = tablica[i];
		if(wyn->suma == 3229)
			cout << "JEst";
	}
	wyn = tablica[indeks-1];
	bin(wyn->indeksy);
	cout << endl << wyn->suma << endl;
	//for(int k =0; k < indeks; k++) {
	//do {
		//cout << wyn->kolejnosc.back() << " ";
		//wyn = tablica[wyn->kolejnosc.back()-1];
		//wyn->kolejnosc.pop_back();
	//} while (wyn->kolejnosc.back() > 0);

	cout << endl; system("PAUSE");
	return 0;
}

int uzupelnianieWektoraWynikow(vector <Zadania*> & wektor, vector <Wyniki*> & wyniki, int rozmiar){
	Wyniki *wyn;
	Zadania *zad;
	int sumka = 0;
	wyn = new Wyniki(0,0,0);
	wyniki.push_back(wyn);
	int indeks = 1, Cmax;
	for(int i = 1; i < rozmiar; i++) {
		zad = wektor[i-1];
		Cmax = zad->p;
		sumka = (zad->p - zad->d)*zad->w;
		for(int k = 0; k < pow((double)2, (double)(i-1)); k++) {
			if(sumka > 0)
				wyn = new Wyniki(indeks,sumka,Cmax);
			else
				wyn = new Wyniki(indeks,0,Cmax);
			wyniki.push_back(wyn);
			indeks++;
		}
	}
	int potega = 0, tmp = 0;
	for(int i = 0; i < indeks; i++) {
		Wyniki *wyni = wyniki[i];
		Wyniki *wynp = wyniki[potega];
		if(wyni->indeksy == (int)pow((double)2,(double(potega)))) {
			potega++;
		}
		else {
			int Cmax = 0;
			for(int k = 0; k < potega; k++) {
				if((wyni->indeksy & (1 << k))) {
					Zadania *ptr = wektor[k];
					Cmax += ptr->p;
				}
			}
			wyni->czasCmax = Cmax;
			wyni->suma = 0;
		}
	}
	return indeks;
}

int programowanieDynamiczne(vector <Zadania*> & wektor, vector <Wyniki*> & wyniki, int rozmiar) {
	cout << "Prog\n\n";
	vector <int> kolejnosc;
	int* tablicaKolejnosci = new int[wektor.size()+20];
	vector <int> czasow;
	int rozmiarek = wektor.size();
	int potega = 0, tmp = 0;
	for(int i = 0; i < rozmiar; i++) {
		Wyniki *wyni = wyniki[i];
		//Wyniki *wynp = wyniki[potega];
		if(wyni->indeksy == (int)pow((double)2,(double(potega)))) {
			//cout << wyni->indeksy << "\t" << wyni->suma << endl;
			potega++;
		}
		else {
			//cout << "badany: " << wyni->indeksy << "!!!!!!!!!!!!!!!!!";
			//bin(wyni->indeksy);
			//cout << endl;
			for(int j = 0; j < potega; j++) {
				if((wyni->indeksy & (1 << j))) {
					int k = 1 << j;
					//cout << "\nk - tenbit\t" << k << "\t"; bin(k);
					//cout << "\ni-k\t\t" << i-k << "\t"; bin(i-k);
					Wyniki *ptrwi = wyniki[k];
					Wyniki *ptrwt = wyniki[i - k];
					int ktory = 0, tmj = j;
					do {
						if(tmj % 2 == 0 && tmj > 0) {
							tmj = tmj / 2;
							ktory++;
						}
						else if( tmj == 0) tmj--;
						else {
							tmj -= 1;
							ktory++;
						}
					} while(tmj > 0);
					Zadania *ptr = wektor[ktory];
					//cout << "\n"<< k << "\t";
					//bin(k);
					//cout << "\n";
					//cout <<endl<< ptrwt->suma << "  " << ptrwt->czasCmax << "  " << ptrwi->czasCmax << /*"  "<< ptr->p <<*/ "  "  << ptr->d << "  " << ptr->w << endl;
					int czas = AZ(ptrwt->suma,ptrwi->czasCmax+ptrwt->czasCmax,ptr->d,ptr->w);
					//czasow.push_back(czas);
					//cout << "czas " << czas << "\n";
					if(wyni->flaga == 0) {
						wyni->suma = czas;
						wyni->flaga = 1;
						//cout << ktory << " ";
						wyni->A = i - k;
						wyni->Z = k;
						//tablicaKolejnosci[rozmiarek] = ktory + 1;
						//tmp++;
					}
					else if(wyni->flaga == 1){
						if(wyni->suma > czas) {
							wyni->suma = czas;
							//kolejnosc.push_back(i);
							//wyni->kolejnosc.push_back(i);
							
							//tablicaKolejnosci[rozmiarek] = ktory + 1;
							//tmp++;
							//rozmiarek--;
							wyni->A = i - k;
							wyni->Z = k;
							//cout << ktory << " ";
						}
					}
					
					//cout << endl;
				}
			}
			//cout << endl;
			tablicaKolejnosci[tmp] = -1;
			tmp++;
		}
		//int gowno = 0;
		//for(int y = 0; y < czasow.size(); y++) {
		//	cout << czasow[y] << " ";
		//}
		//cout << "\n\n";
		//for(int y = 0; y < czasow.size(); y++) {
		//	if(gowno < czasow.back()) {
		//		//cout<< "tak  ";
		//		gowno = czasow.back();
		//		czasow.pop_back();
		//		tablicaKolejnosci[i] = y + 1;//gowno;
		//	}
		//}
		//czasow.clear();
		//cout << "\n\n";

	}
	/*cout << endl;
	for(int k = 0; k < wektor.size()+20; k++)
		cout << tablicaKolejnosci[k] << "\t";
	cout << endl;*/
	return 0;
}

void wyswietlanieWynikow(vector <Wyniki*> & wyniki, int rozmiar){
	cout << "\n\nWYSWIETLANIE\n\n";
	Wyniki *wyn;
	int indeks = 0;
	for(int i = 0; i < rozmiar; i++) {
		for(int k = 0; k < pow((double)2, (double)(i-1)); k++) {
			wyn = wyniki[indeks];
			cout << "indeks: " << wyn->indeksy << "\tsuma: " << wyn->suma << "  czas: " << wyn->czasCmax << "\tA: " << wyn->A << " Z: " << wyn->Z << endl;
			indeks++;
		}
	}
}

int AZ(int A, int Cmax, int d, int w) {
	if((A + (Cmax - d) * w) < 0)
		return 0;
	else
		return ((A + (Cmax - d) * w));
}

void odczytZPliku(vector <Zadania*> &wektor, string nazwa) 
{
	fstream plik;
	plik.open(nazwa, ios::in);
	
	int tmpp, tmpw, tmpd;
	Zadania *ptr;

	int ilosc = 0;
	if (plik.good())
	{
		plik >> ilosc;
		int rozmiar = ilosc;
		int i = 0;
		int indeks;
		do {
			plik >> tmpp;
			plik >> tmpw;
			plik >> tmpd;
			indeks = 1 << i;
			ptr = new Zadania(tmpp, tmpw, tmpd, indeks, rozmiar, rozmiar - ilosc);
			wektor.push_back(ptr);
			ptr = NULL;
			i++;
			ilosc--;
		} while (ilosc >= 0);
		wektor.pop_back();
	}
	else
		cout << "Nie mozna bylo otworzyc plik!" << endl;
	
	plik.close();
	
}

void zapisDoPliku(vector <Zadania*> &wektor, string nazwa)
{
	fstream plik;
	plik.open(nazwa, ios::out);

	if (plik.good())
	{
		plik << "1 " << wektor.size() << endl;
		for (int i = 0; i < (int)wektor.size(); i++)
			plik << wektor[i]->indeks << " ";
		plik << endl;// << zliczanie(wektor);
	}

	
	plik.close();
}
