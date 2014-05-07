#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <queue>

using namespace std;

class Task {
public:
int p, w, d;
	Task(int tp, int tw, int td): p(tp), w(tw), d(td) {};
};

class Optimal {
public:
	int permutation, value, p, w, d;
	Optimal(int per, int val, int tp, int tw, int td)
		: permutation(per), value(val), p(tp), w(tw), d(td){};
};

void fileIn(char*, vector <Task> *);
void result(vector <Task>);
int mini(vector <Optimal>, int);
int AZ(vector <Optimal>, int, int);

void fileIn(char* nazwa, vector <Task> *wektor) {
	fstream file;
	int noOfTasks;
	file.open(nazwa, ios::in);
	int tp, tw, td;
	if(file.good()) {
		file >> noOfTasks;
		do {
			file >> tp >> tw >> td;
			Task t(tp,tw,td);
			(*wektor).push_back(t);
			noOfTasks--;
		}while(noOfTasks > 0);
		file.close();
	} else {
		cout << "Plik nie otworzyl sie";
		 cin.get();
		exit(-1);
	}
}

void result(vector <Task> wektor) {
	vector <Optimal> optimals;
	Optimal *o;
	o = new Optimal(0,0,0,0,0);
	optimals.push_back(*o);
	int permutations = (int)pow((double)2,(int)wektor.size());
	for(int i = 1, k = 0, zm = 1; i < permutations; i++) {
		if(i == zm) {
			int tmp = ((wektor[k].p - wektor[k].d) * wektor[k].w);
			if(tmp > 0)
				o = new Optimal(i,tmp,wektor[k].p,wektor[k].w,wektor[k].d);
			else 
				o = new Optimal(i,0,wektor[k].p,wektor[k].w,wektor[k].d);
			optimals.push_back(*o);
			k++;
			zm = zm<<1;
		} else {
			o = new Optimal(i,0,0,0,0);
			for(int k = i; k > 0; k--) {
				if((i & (1 << k)) > 0) {
					int tmp = optimals[(i & (1 << k))].p + optimals[ i - (i & (1 << k))].p; // ok
					if(tmp > 0)
						o->p = tmp;
					else o->p = 0;
				}
			}
			optimals.push_back(*o);
		}
	}
	for(int i = 1, zm = 1; i < permutations; i++) {
		if(i == zm)
			zm = zm<<1;
		else
			optimals[i].value = mini(optimals,i);
	}
	cout << "\nWYNIK  " << optimals[optimals.size() - 1].value << endl;
}

int mini(vector <Optimal> optimals, int per) {
	priority_queue < int, vector<int>, greater<int> > que;
	for(int i = 0; i < per; i++)
		if((per & (1 << i)) > 0)
			que.push(AZ(optimals,per - (per & (1 << i)),(per & (1 << i))));
	return que.top();
}

int AZ(vector <Optimal> optimals, int a, int z) {
	int tmp = (optimals[a+z].p - optimals[z].d);
	if(tmp >= 0)
		return (optimals[a].value + tmp*optimals[z].w);
	else
		return optimals[a].value;
}

int main (int argc, char *argv[])
{
	vector <Task> wektor;
	fileIn("data01.txt",&wektor);

	cout << "liczba zadan " << (int)wektor.size() << endl;
	for(int i = 0; i < (int)wektor.size(); i++)
		cout << wektor[i].p << " " << wektor[i].w << " " << wektor[i].d << endl;
	result(wektor);
    cin.get();
    return 0;
}
