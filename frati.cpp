// Copyright [2018] <Cristi>

#include <fstream>
#include <iomanip>
#include <vector>
#include <algorithm>
using namespace std;

struct Object {
	int jocuri;
	int benzi;

	Object(int _jocuri, int _benzi) : jocuri(_jocuri), benzi(_benzi) {}
};

// compar concursurile in functie de suma elementelor acestora
// in caz de egalitate are prioritate concursul cu numarul de jocuri mai mare
struct comparator {
    template<class T>
    bool operator()(T const &a, T const &b) const {
    	if (a.jocuri + a.benzi > b.jocuri + b.benzi)
    		return true;
    	if (a.jocuri + a.benzi == b.jocuri + b.benzi &&
    		a.jocuri > b.jocuri)
    		return true;
    	return false;
    }
};

class Task {
 public:
	void solve() {
		read_input();
		print_output(get_result());
	}

 private:
	int n;
	vector<Object> objs;

	// citesc datele
	void read_input() {
		ifstream fin("frati.in");
		fin >> n;
		for (int i = 0, jocuri, benzi; i < n; i++) {
			fin >> jocuri >> benzi;
			objs.push_back(Object(jocuri, benzi));
		}
		fin.close();
	}

	Object get_result() {
		// sortez vectorul cu datele
		sort(objs.begin(), objs.end(), comparator());

		int jocuri = 0, benzi = 0, index = 0, j;

		// parcurg elementele vectorului
		for (int i = 0; i < n; i++) {
			j = i;
			// in cazul in care mai multe elemente au suma egala trec cu
			// indicele peste ele, avand indicele precedent memorat (j = i)
			while (i < n - 1 && objs[i].jocuri + objs[i].benzi ==
				objs[i+1].jocuri + objs[i+1].benzi)
				i++;

			// parcurg de la inceputul elementelor ce se repeta si pana la final
			// si atribui numarul de jocuri si numarul de benzi celor 2 frati
			for (int k = j; k <= i; k++) {
				if (k > i - k + j)
					break;

				// index memoreaza care dintre cei 2 frati urmeaza sa castige
				// concursul
				if (index % 2 == 0) {
					jocuri += objs[k].jocuri;
					index++;
					if (k != i-k+j) {
						benzi += objs[i-k+j].benzi;
						index++;
					}
				} else {
					benzi += objs[i-k+j].benzi;
					index++;
					if (k != i-k+j) {
						jocuri += objs[k].jocuri;
						index++;
					}
				}
			}
		}

		// returnez rezultatul
		return Object(jocuri, benzi);
	}

	// afisez rezultatul
	void print_output(Object result) {
		ofstream fout("frati.out");
		fout << result.jocuri << ' ' << result.benzi;
		fout.close();
	}
};

int main() {
	Task task;
	task.solve();
	return 0;
}
