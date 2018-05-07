// Copyright [2018] <Cristi>

#include <fstream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

class Task {
 public:
	void solve() {
		read_input();
		print_output(get_result());
	}

 private:
	int s, n, i, index = 0;
	string sol = "";

	// citirea datelor
	void read_input() {
		ifstream fin("numaratoare.in");
		fin >> s >> n >> i;
		fin.close();
	}

	void back(int elems, int sum, vector<int> &v) {
		// verific daca am exact n termeni, daca suma este exact cat trebuie si
		// daca index-ul este exact cel cerut in datele de intrare
		if (elems == n) {
			if (sum == s) {
				if (index == i) {
					// daca se respecta cele de mai sus imi formez output-ul si
					// apelez functia de afisare
					sol += to_string(s) + '=' + to_string(v[0]);
					for (int j = 1; j < n; j++)
						sol += '+' + to_string(v[j]);
					print_output(sol);
				}
				index++;
			}
			return;
		}

		// parcurg de la maximul posibil (in functie de suma deja existenta, de
		// numarul de termeni ai sumei si de cate elemente am adaugat deja) si
		// pana la 1 inclusiv
		for (int j = s-sum-n+elems+1; j > 0; j--) {
			// daca nu ma aflu la primul termen, indexul nu este cel cerut si
			// urmatorul numar pe care ar trebui sa il adaug este 1, ma opresc
			// fara a mai adauga si fara a continua solutia, insa trec la
			// urmatoarea valoare a index-ului
			if (elems != 0 && index < i && j < 2) {
				index++;
				return;
			}

			// daca nu am niciun element in lista, il adaug pe cel calculat (j)
			if (elems == 0) {
				v[elems] = j;
			// altfel aleg minimul dintre ceea ce am calculat si valoarea
			// anterioara pentru a nu avea o suma de genul "8=3+4+1"
			} else {
				v[elems] = min(j, v[elems-1]);
				j = v[elems];
			}
			// apelez recursiv functia
			back(elems + 1, sum + j, v);
			// daca am iesit din functie si j are valoarea 2 (nefiind la primul
			// termen) nu las for-ul sa continue cu valoarea 1 pentru a nu
			// genera o solutie gresita si pentru a nu pierde timp
			if (elems != 0 && j == 2)
				return;
		}
	}

	string get_result() {
		vector<int> v(n, 0);
		// apelez asa zisa functie de backtracking
		back(0, 0, v);

		// returnez solutia
		return sol;
	}

	// afisez solutia
	void print_output(string result) {
		ofstream fout("numaratoare.out");
		if (result.size() == 0)
			fout << "-";
		else
			fout << result;
		fout.close();
		exit(0);
	}
};

int main() {
	Task task;
	task.solve();
	return 0;
}
