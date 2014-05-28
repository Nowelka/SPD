#include <iostream>
#include <fstream>
#include <iomanip>
#include <queue>
#include <list>
#include <vector>

using namespace std;

int liczbaMaszyn, liczbaZadan, liczbaOperacji, kolumny = 10;
int** tablica;
vector < vector <int>> rozwiazanie;

class Wynik {
public:
	int indeks, suma;
	Wynik(int i, int s) :indeks(i), suma(s){};
};
class Porownanie2 {
public:
	bool operator() (const Wynik &k1, const Wynik &k2) {
		if(k1.suma > k2.suma) return true;
		return false;
	}
};
typedef priority_queue<Wynik,vector<Wynik>,Porownanie2> kolejka2;

int main() {
	
	fstream plik("data.txt", ios::in);
	int i, j, tmp, kolej = 1;
	//inicjalizowanie tablicy
	if(plik.good()) {
		plik >> liczbaZadan >> liczbaMaszyn >> liczbaOperacji;
		liczbaOperacji++;
		tablica = new int*[liczbaOperacji];
		tablica[0] = new int[kolumny];
		for(i = 0; i < kolumny; i++) {
			tablica[0][i] = 0;
		}
		for(i = 1; i < liczbaOperacji; i++) {
			if(i%liczbaMaszyn == 1)
				plik >> tmp;
			tablica[i] = new int[kolumny];

			tablica[i][0] = kolej;
			plik >> tablica[i][1] >> tablica[i][2];

			kolej++;

			tablica[i][5] = tablica[i][6] = tablica[i][8] = tablica[i][9] = 0;
			tablica[i][7] = 1;

			tablica[i][3] = kolej;
			if(i%liczbaMaszyn == 0) tablica[i][3] = 0;

			tablica[i][4] = kolej - 2;
			if(i%liczbaMaszyn == 1)	{
				tablica[i][4] = 0;
				tablica[i][7] = 0;
			}
		}
		tablica[liczbaOperacji] = new int[kolumny];
		for(i = 0; i < kolumny; i++) {
			tablica[liczbaOperacji][i] = 0;
		}		
	}
	

	//utworzenie kolejnosci topologicznej // ale tylko to dziala
	vector <int> topologiczna;
	topologiczna.push_back(0);
	int licznik = 0, iter = 1;
	while(licznik < liczbaOperacji - 1) {
		for(int y = 1; y < liczbaOperacji; y++) {
			if(tablica[y][7] == 0) {
				topologiczna.push_back(y);
				tablica[y][7] = -1;
				licznik++;
			}
		}
		for(int z = 1; z < (int)topologiczna.size(); z++) {
			for(int x = 1; x < liczbaOperacji; x++) {
				if(topologiczna[z] == tablica[x][4]) {
					tablica[x][7]--;
					break;
				}
			}
		}
	}
	
	///relaksacja
	for(int y = 1; y < liczbaOperacji; y++) {
		tablica[topologiczna[y]][8] = tablica[topologiczna[y]][2] + tablica[topologiczna[y]-1][8];
		tablica[topologiczna[liczbaOperacji - y]][9] = tablica[topologiczna[liczbaOperacji-y]][2] + tablica[topologiczna[liczbaOperacji-y]+1][9];
	}

	//szeregowanie procesow po P_time
	kolejka2 kolejnosc;
	for(int i = 1; i < liczbaOperacji; i++) {
		Wynik w(i,tablica[i][2]);
		kolejnosc.push(w);
	}
	vector <int> lista;
	for(i = 0; i < liczbaOperacji-1; i++) {
		lista.push_back(kolejnosc.top().indeks);
		kolejnosc.pop();
	}

	
	//inicjalizacja rozwiazania
	vector < vector <int>> rozwiazanie (liczbaMaszyn, vector<int> (0));
	for(int i = 0; i < (int)rozwiazanie.size(); i++) { // po to zeby zawsze byl pierwszy i ostatni = 0
		rozwiazanie[i].push_back(0);
		rozwiazanie[i].push_back(0);
	}
	int **tablicaT = new int*[liczbaOperacji+1];
	for(int i = 0; i < liczbaOperacji + 1; i++) {
		tablicaT[i] = new int[kolumny];
		for(int j = 0; j < kolumny; j++) {
			tablicaT[i][j] = tablica[i][j];
		}
	}
	int n = lista.size() - 1;
	while(n > -1){
		int zadanie = lista[n];
		lista.pop_back();
		n--;
		//wstawianie wtedy gdy trzeba podjac decyzje miedzy jakie procesy
		if(rozwiazanie[tablicaT[zadanie][1] - 1].size() > 2) {
			kolejka2 kolejeczka;
			int suma, lewo, prawo, poprz_tech, poprz_kolej, nast_tech, nast_kolej;
			for(int w = 0; w < (int)rozwiazanie[tablicaT[zadanie][1] - 1].size()-1;w++) {
				poprz_tech = tablicaT[tablicaT[zadanie][4]][8];
				poprz_kolej = tablicaT[rozwiazanie[tablicaT[zadanie][1] - 1][w]][8];
				lewo = (poprz_tech > poprz_kolej) ? (lewo = poprz_tech):(lewo = poprz_kolej);
				nast_kolej = tablicaT[rozwiazanie[tablicaT[zadanie][1] - 1][w+1]][9];
				nast_tech = tablicaT[tablicaT[zadanie][3]][9];
				prawo = (nast_kolej > nast_tech) ? (prawo = nast_kolej):(prawo = nast_tech);
				suma = lewo + tablicaT[zadanie][2] + prawo;
				Wynik w1(w,suma);
				kolejeczka.push(w1);
			}
			Wynik gdzie(kolejeczka.top().indeks,kolejeczka.top().suma);
			rozwiazanie[tablicaT[zadanie][1] - 1].insert(rozwiazanie[tablicaT[zadanie][1] - 1].begin()+gdzie.indeks+1,tablicaT[zadanie][0]);

			for(int i = 0; i < topologiczna.size(); i++) {
				if(kolejeczka.top().suma == topologiczna[i]) {
					int tmp = topologiczna[i];
				}
			}

			int poprzednikWstawianego, wstawiany, nastepnikWstawianego;
			poprzednikWstawianego = rozwiazanie[tablicaT[zadanie][1] - 1][gdzie.indeks];
			wstawiany = rozwiazanie[tablicaT[zadanie][1] - 1][gdzie.indeks+1];
			nastepnikWstawianego = rozwiazanie[tablicaT[zadanie][1] - 1][gdzie.indeks+2];
			tablicaT[poprzednikWstawianego][5] = wstawiany;
			tablicaT[wstawiany][6] = poprzednikWstawianego;
			tablicaT[wstawiany][5] = nastepnikWstawianego;
			tablicaT[nastepnikWstawianego][6] = wstawiany;



//brak poprawki topologicznej
			for(int y = 1; y < liczbaOperacji; y++) {
				int tmp = 0;
				if(tablicaT[y][4] != 0) tmp += 1;
				if(tablicaT[y][6] != 0) tmp += 1;
				tablicaT[y][7] = tmp;
			}

/*
			topologiczna.clear();
			topologiczna.push_back(0);
			int licznik = 0, iter = 1;
			while(licznik < liczbaOperacji - 1) {
				for(int y = 1; y < liczbaOperacji; y++) {
					if(tablicaT[y][7] == 0) {
						topologiczna.push_back(y);
						tablicaT[y][7] = -1;
						licznik++;
					}
				}
				for(int z = 1; z < (int)topologiczna.size(); z++) {
					for(int x = 1; x < liczbaOperacji; x++) {
						if(topologiczna[z] == tablicaT[x][4]) {
							tablicaT[x][7]--;
							break;
						}
					}
				}
			}
			*/
/*//jak jest to ponizej to jest insa prawie i wtedy nie trzeba tego wyzej
		for(int y = 1; y < liczbaOperacji; y++) {
			tablicaT[topologiczna[y]][8] = 0;
			tablicaT[topologiczna[y]][9] = 0;
		}*/
		for(int y = 1; y < liczbaOperacji; y++) {
			tablicaT[topologiczna[y]][8] = tablicaT[topologiczna[y]][2] + tablicaT[topologiczna[y]-1][8];
			tablicaT[topologiczna[liczbaOperacji - y]][9] = tablicaT[topologiczna[liczbaOperacji-y]][2] + tablicaT[topologiczna[liczbaOperacji-y]+1][9];
		}
		}
		//wstawienie pomiedzy pierwsze i ostatnie zero
		else rozwiazanie[tablicaT[zadanie][1] - 1].insert(rozwiazanie[tablicaT[zadanie][1] - 1].begin()+1,tablicaT[zadanie][0]);
		


		tablicaT[0][5] = tablicaT[0][6] = tablicaT[0][7] = tablicaT[0][8] = tablicaT[0][9] = 0;
	}


	cout << "Kolejnosc:\n\n";
	for(int i = 0; i < liczbaMaszyn; i++) {
		for(j = 0; j < (int)rozwiazanie[i].size(); j++)
			cout << rozwiazanie[i][j] << " ";
		cout << endl;
	} cout << "\n\n";

	int wyn = 0; // jak to sie liczy?
	for(int i = 0; i < liczbaMaszyn; i++) {
		for(j = 0; j < (int)rozwiazanie[i].size(); j++) {
			wyn += tablicaT[rozwiazanie[i][j]][2];
		}
	}

	cout << "\n\n" << wyn << endl;

	system("PAUSE");
	return 0;
}

/*
for(j = 0; j < kolumny; j++) cout << setw(3) << j << " ";
	cout << "\n\n";
	for(i = 0; i < liczbaOperacji; i++) {
		for(int j = 0; j < kolumny; j++) {
			cout << setw(3) << tablica[i][j] << " ";
		}
		if(i%liczbaMaszyn == 0) cout << endl;
		cout << endl;
	}cout << "\n\n";*/