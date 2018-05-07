// Copyright [2018] <Cristi>

#include <fstream>
#include <iomanip>
#include <vector>
#include <algorithm>
using namespace std;

struct Object {
	long long unsigned L;
	long long unsigned N;
};

class Task {
 public:
	void solve() {
		read_input();
		print_output(get_result());
	}

 private:
	int p, d, b;
	vector<int> v;

	// citirea datelor
	void read_input() {
		ifstream fin("planificare.in");
		fin >> p >> d >> b;
		// indexare de la 1
		v.push_back(-1);
		for (int i = 1, e; i <= p; i++) {
			fin >> e;
			v.push_back(e);
		}
		fin.close();
	}

	// calcueaza minimul dintre suma pierderii pana la un moment cu pierderea
	// precedenta si pierderea deja existenta (daca exista)
	// mai multe detalii in README
	long long unsigned minimum(long long unsigned cub, Object x, Object y) {
		if (y.L == 0 && y.N == 0)
			return cub + x.L;
		return min(cub + x.L, y.L);
	}

	Object get_result() {
		int i, j, rest = d;
		long long unsigned cub;
		vector<Object> dp(p+1);

		// parcurgere probe
		for (i = 1; i <= p; i++) {
			// la fiecare posibil nou concurs initializez durata din care scad
			// mereu cat dureaza proba si apoi pauza
			rest = d;
			for (j = i; j <= p; j++) {
				// daca ma aflu la primul concurs calculez pierderea (notata cu
				// variabila cub) si o pun direct in vector
				// de asemenea setez si numarul concursului
				if (i == 1) {
					rest -= v[j];
					cub = rest * rest * rest;
					rest -= b;
					dp[j].L = cub;
					dp[j].N = 1;
				// daca ma aflu la ultimul concurs stiu ca pierderea este 0, asa
				// ca fac minimul intre ce am in vector deja si ce am anterior
				// in functie de acea alegere setez si numarul de concursuri
				} else if (j == p) {
					dp[j].L = minimum(0, dp[i-1], dp[j]);
					if (dp[j].L == dp[i-1].L)
						dp[j].N = dp[i-1].N + 1;
				// altfel imi calculez pierderea si verific care este cea mai
				// mica suma pe care o pot obtine
				// de asemenea, setez numarul de concursuri ca mai sus
				} else {
					rest -= v[j];
					cub = rest * rest * rest;
					rest -= b;
					dp[j].L = minimum(cub, dp[i-1], dp[j]);
					if (dp[j].L == cub + dp[i-1].L)
						dp[j].N = dp[i-1].N + 1;
				}

				// daca durata ramasa din acel concurs este mai mica decat
				// urmatoarea proba ma opresc pentru a nu face pasi in plus
				if (j < p && rest < v[j+1])
					break;
			}
		}

		// returnez rezultatul
		return dp[p];
	}

	// afisez rezultatul
	void print_output(Object result) {
		ofstream fout("planificare.out");
		fout << result.L << ' ' << result.N;
		fout.close();
	}
};

int main() {
	Task task;
	task.solve();
	return 0;
}
