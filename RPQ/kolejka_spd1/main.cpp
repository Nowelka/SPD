#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

class zadania{
public:
	zadania(int r1, int p1, int q1): r(r1), p(p1), q(q1) {};
	//~zadania();
	int r, p, q;
};
void sortowanieMinMaxR(vector <zadania*> &);
int zliczanie(vector <zadania*> &);
void sortowanieMaxMinQ(vector <zadania*> &, int);
void odczytZPliku(vector <zadania*> &, vector <zadania*> &, vector <zadania*> &);

//r - czas dotarcia
//p - czas obróbki
//q - czas stygniecia
int main() {
	vector <zadania*> wektor50;
	vector <zadania*> wektor100;
	vector <zadania*> wektor200;
	odczytZPliku(wektor50, wektor100, wektor200);

	int wynik50, wynik100, wynik200;

	cout << "Czas po samym wczytaniu z plikow:";
	cout << "\n50:\n";
	wynik50 = zliczanie(wektor50);
	cout << "\t" << wynik50;
	cout << "\n100:\n";
	wynik100 = zliczanie(wektor100);
	cout << "\t" << wynik100;
	cout << "\n200:\n";
	wynik200 = zliczanie(wektor200);
	cout << "\t" << wynik200;
	cout << "\nw sumie: " << wynik50+wynik100+wynik200 << "\n\n\n";

	//Ponizej same sortowanie od wartosci malejacej 
	//do rosnacej wzgledem parametru r
	sortowanieMinMaxR(wektor50);
	sortowanieMinMaxR(wektor100);
	sortowanieMinMaxR(wektor200);

	cout << "Czas po sortowaniu wzgledem wartosci r" 
		<< "\n(od najmniejszego do najwiekszego)";		//jak widac na ocene 3.0
	cout << "\n50:\n";
	wynik50 = zliczanie(wektor50);
	cout << "\t" << wynik50;
	cout << "\n100:\n";
	wynik100 = zliczanie(wektor100);
	cout << "\t" << wynik100;
	cout << "\n200:\n";
	wynik200 = zliczanie(wektor200);
	cout << "\t" << wynik200;
	cout << "\nw sumie: " << wynik50+wynik100+wynik200 << "\n\n\n";
	
	//Ponizej sortowanie od wartosci rosnacej 
	//do wartosci malejace wzgledem parametru q
	//od wybranego doswiadczalnie elementu
	//np.	sortowanie malejace wzgledem q 
	//		od elementu 22 do 49 w wektor50 <- najkorzystniejszy wynik
	sortowanieMaxMinQ(wektor50, 22);	
	sortowanieMaxMinQ(wektor100, 46);
	sortowanieMaxMinQ(wektor200, 115);
	
	cout << "Czas po sortowaniu wzgldem q"
		<< "\n(od najwiekszego do najmniejszego;"
		<< " od wybranego miejsca)";
	cout << "\n50:\n";
	wynik50 = zliczanie(wektor50);
	cout << "\t" << wynik50;
	cout << "\n100:\n";
	wynik100 = zliczanie(wektor100);
	cout << "\t" << wynik100;
	cout << "\n200:\n";
	wynik200 = zliczanie(wektor200);
	cout << "\t" << wynik200;
	cout << "\nw sumie: " << wynik50+wynik100+wynik200 << "\n\n\n";
	

	cout << "\n\n A tu pokazuje o co chodzi mi w tym sortowaniu\n"
		<< "r \tp \t q\n";
	for(int i = 0 ; i < wektor50.size(); i++) {
		zadania *ptr = wektor50[i];
		cout << ptr->r << "\t" << ptr->p << "\t" << ptr->q << endl;
		ptr = NULL;
	}
	cout << "\n\n";
	system("PAUSE");
	return 0;
}

//sortowanie babelkowe wektorow wzgledem r
//od najmniejszej wartosci do najwiekszej wartosci
void sortowanieMinMaxR(vector <zadania*> & wektor) {	
	int n = wektor.size();
	do {
		for(int i = 0; i < n - 1; i++){
			zadania *ptr0 = wektor[i];
			zadania *ptr1 = wektor[i+1];
			if((ptr0->r) > (ptr1->r)) {
				auto tmp = wektor[i];
				wektor[i] = wektor[i+1];
				wektor[i+1] = tmp;
			}
			ptr0 = NULL; ptr1 = NULL;
		}
		n--;
	}while(n>1);
}


//sortowanie babelkowe wektorow wzgledem q
//od najwiekszej wartosci do najmniejszej wartosci 
//od pewnego wybranego (najkorzystniejszego) miejsca/elementu w wektorze
//dla wektor50 -> 22
//dla wektor100 -> 46
//dla wektor200 -> 115
void sortowanieMaxMinQ(vector <zadania*> & wektor,int odKtoregoMiejsca){
	int n = wektor.size();
	do {
		for(int i = odKtoregoMiejsca; i < n - 1; i++){
			zadania *ptr0 = wektor[i];
			zadania *ptr1 = wektor[i+1];
			if((ptr0->q) < (ptr1->q)) {
				auto tmp = wektor[i];
				wektor[i] = wektor[i+1];
				wektor[i+1] = tmp;
			}
			ptr0 = NULL; ptr1 = NULL;
		}
		n--;
	}while(n>1);
}

//zliczanie czasu jaki jest potrzebny na wykonanie 
//wszystkich procesow w wektorze
int zliczanie(vector <zadania*> & wektor) {
	int tmpSumaRP = 0, tmpQ = 0;
	zadania *ptr = wektor[0];
	tmpSumaRP = ptr->r + ptr->p;
	tmpQ = tmpSumaRP + ptr->q;
	int n = wektor.size();
	for(int i = 1; i < n; i++){
		zadania *ptr0 = wektor[i];
		if(tmpSumaRP < ptr0->r) {
			tmpSumaRP = ptr0->r + ptr0->p;
		}
		else {
			tmpSumaRP = tmpSumaRP + ptr0->p;
			
		}
		if(tmpQ < tmpSumaRP + ptr0->q) {
			tmpQ = tmpSumaRP + ptr0->q;
		}
		ptr0 = NULL;
	}
	ptr = wektor[n-1];
	tmpSumaRP = tmpSumaRP + ptr->q;
	if(tmpSumaRP > tmpQ)
		return tmpSumaRP;
	else return tmpQ;
}


//dalej jest brzydko zrobiony odczyt z pliku, ale chcialam gdzies to zwinac
void odczytZPliku(vector <zadania*> &wektor50, vector <zadania*> &wektor100, vector <zadania*> &wektor200) {
	fstream plik50, plik100, plik200;
	plik50.open("in50.txt", ios::in);
	plik100.open("in100.txt", ios::in);
	plik200.open("in200.txt", ios::in);

	int tmpr, tmpp, tmpq;
	zadania *ptr;
	
	if(plik50.good()) {
		plik50 >> tmpr >> tmpr;
		do {
			plik50 >> tmpr;
			plik50 >> tmpp;
			plik50 >> tmpq;
			ptr = new zadania(tmpr, tmpp, tmpq);
			wektor50.push_back(ptr);
			ptr = NULL;
		}while(!plik50.eof());
	}
	if(plik100.good()) {
		plik100 >> tmpr >> tmpr;
		do {
			plik100 >> tmpr;
			plik100 >> tmpp;
			plik100 >> tmpq;
			ptr = new zadania(tmpr, tmpp, tmpq);
			wektor100.push_back(ptr);
			ptr = NULL;
		}while(!plik100.eof());
	}
	if(plik200.good()) {
		plik200 >> tmpr >> tmpr;
		do {
			plik200 >> tmpr;
			plik200 >> tmpp;
			plik200 >> tmpq;
			ptr = new zadania(tmpr, tmpp, tmpq);
			wektor200.push_back(ptr);
			ptr = NULL;
		}while(!plik200.eof());
	}
	
	wektor50.pop_back();
	wektor100.pop_back();
	wektor200.pop_back();
}