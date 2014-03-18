#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

class zadania
{
    public:
    	zadania(int r1, int p1, int q1, int tindeks) : r(r1), p(p1), q(q1), indeks(tindeks){};
    	int r, p, q, indeks;
};

int zliczanie(vector <zadania>);
void odczytZPliku(vector <zadania> &, vector <zadania> &, vector <zadania> &);
void zapisDoPliku(vector <zadania> &, vector <zadania> &, vector <zadania> &);

int main() {
	return 0;
}

int zliczanie(vector <zadania> wektor) {
	return 0;
}

void odczytZPliku(vector <zadania> &wektor50, vector <zadania> &wektor100, vector <zadania> &wektor200) 
{
	fstream plik50, plik100, plik200;
	plik50.open("in50.txt", ios::in);
	plik100.open("in100.txt", ios::in);
	plik200.open("in200.txt", ios::in);

	int tmpr, tmpp, tmpq;
	zadania *ptr;

	if (plik50.good())
	{
		plik50 >> tmpr >> tmpr;
		int i = 1;
		do {
			plik50 >> tmpr;
			plik50 >> tmpp;
			plik50 >> tmpq;
			ptr = new zadania(tmpr, tmpp, tmpq, i);
			wektor50.push_back(*ptr);
			i++;
			ptr = NULL;
		} while (!plik50.eof());
		wektor50.pop_back();
	}
	else
		cout << "Nie mozna bylo otworzyc plik50!" << endl;
	if (plik100.good()) {
		plik100 >> tmpr >> tmpr;
		int j = 1;
		do {
			plik100 >> tmpr;
			plik100 >> tmpp;
			plik100 >> tmpq;
			ptr = new zadania(tmpr, tmpp, tmpq, j);
			wektor100.push_back(*ptr);
			ptr = NULL;
			j++;
		} while (!plik100.eof());
	
		wektor100.pop_back();
	}
	else
		cout << "Nie mozna bylo otworzyc plik100!" << endl;
	if (plik200.good()) 
	{
		int k = 1;
		plik200 >> tmpr >> tmpr;
		do {
			plik200 >> tmpr;
			plik200 >> tmpp;
			plik200 >> tmpq;
			ptr = new zadania(tmpr, tmpp, tmpq, k);
			wektor200.push_back(*ptr);
			ptr = NULL;
			k++;
		} while (!plik200.eof());
		
		wektor200.pop_back();
	}
	else
		cout << "Nie mozna bylo otworzyc plik200!" << endl;

	plik50.close();
	plik100.close();
	plik200.close();
	
}

void zapisDoPliku(vector <zadania> &wektor50, vector <zadania> &wektor100, vector <zadania> &wektor200)
{
	fstream plik50, plik100, plik200;
	plik50.open("out50.txt", ios::out);
	plik100.open("out100.txt", ios::out);
	plik200.open("out200.txt", ios::out);

	if (plik50.good())
	{
		plik50 << "1 " << wektor50.size() << endl;
		for (int i = 0; i < wektor50.size(); i++)
			plik50 << wektor50[i].indeks << " ";
		plik50 << endl << zliczanie(wektor50);
	}

	if (plik100.good())
	{
		plik100 << "1 " << wektor100.size() << endl;
		for (int i = 0; i < wektor100.size(); i++)
			plik100 << wektor100[i].indeks << " ";
		plik100 << endl << zliczanie(wektor100);
	}

	if (plik100.good())
	{
		plik200 << "1 " <<  wektor200.size() << endl;
		for (int i = 0; i < wektor200.size(); i++)
			plik200 <<  wektor200[i].indeks << " ";
		plik200 << endl << zliczanie(wektor200);
	}
	plik50.close();
	plik100.close();
	plik200.close();
}
