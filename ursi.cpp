// Copyright [2018] <Cristi>

#include <fstream>
#include <iomanip>
#include <vector>
#include <algorithm>
using namespace std;

// valoarea la care impartim pentru a folosi restul ca rezultat
const int kMod = 1e9 + 7;

class Task {
 public:
	void solve() {
		read_input();
		print_output(get_result());
	}

 private:
	string sir;

	// citire date
	void read_input() {
		ifstream fin("ursi.in");
		fin >> sir;

		// indexare de la 1
		sir = " " + sir;
		fin.close();
	}

	int get_result() {
		// numarul de caractere al sirului (fara caracterul pus pentru indexare)
		int n = sir.size() - 1;

		// returneaza 0 daca numarul de caciulite este impar, daca sirul incepe
		// sau se termina cu underline sau daca are mai putin de 2 caractere
		if (count(sir.begin(), sir.end(), '^') % 2 == 1 || sir[1] == '_' ||
			sir[n] == '_' || n < 2)
			return 0;

		// eliminare caractere '_' ce se afla dupa prima caciulita sau inainte
		// de ultima
		bool stergere = true;
		while (stergere) {
			stergere = false;
			if (sir[n-1] == '_') {
				stergere = true;
				sir = sir.erase(n-1, 1);
			}
			if (sir[2] == '_') {
				stergere = true;
				sir = sir.erase(2, 1);
			}
			n = sir.size() - 1;
		}

		// declar matricea (n+2)x(n+2) pentru ca am nevoie ca aceasta sa fie
		// bordata
		vector<vector<int>> dp(n+2, vector<int>(n+2, 0));

		// prima caciulita mereu va avea valoarea 1 pentru ca are rolul doar de
		// a deschide o fata zambitoare
		// avand indexare de la 1 rezulta ca pe pozitia primei caciulite se
		// deschide caciulita (j+1), deci dp[1][2] = 1
		dp[1][2] = 1;

		// parcurg matricea si atribui valorile (detalii in README)
		for (int i = 2; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				if (sir[i] == '_')
					dp[i][j] = (1ULL * (j - 1) * dp[i-1][j]) % kMod;
				else
					dp[i][j] = (1ULL * dp[i-1][j-1] + 1ULL * j * dp[i-1][j+1]) %
						kMod;
			}
		}

		// returnez rezultatul
		return dp[n][1];
	}

	// afisez rezultatul
	void print_output(int result) {
		ofstream fout("ursi.out");
		fout << result;
		fout.close();
	}
};

int main() {
	Task task;
	task.solve();
	return 0;
}
