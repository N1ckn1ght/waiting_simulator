#include <iostream>
#include <vector>
#include <cmath>
#include <climits>

using namespace std;

double distance(double x1, double y1, double x2, double y2) {
	return sqrt( (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)  );
}

void print(vector <int>& vec, int size) {
	for (int i = 0; i < size; i++) {
		cout << vec[i] << " ";
	}
	cout << endl;
}

bool is_solved(vector <int>& ctb, int level) {
	for (int i = 0; i < level; i++) {
		for (int j = i + 1; j < level; j++) {
			if (ctb[i] == ctb[j]) {
				return false;
			}
		}
	}
	return true;
}

void build(int n, vector <double>& x, vector <double>& y, vector <int>& ctb, double& minimal) {
	for (int i = 0; i < n; i++) {
		ctb.push_back(i);
		if (is_solved(ctb, ctb.size())) {
			if (ctb.size() == n) {
				double len = 0;
				for (int j = 0; j < n; j++) {
					len += distance(x[j], y[j], x[ctb[j] + n], y[ctb[j] + n]);
					/*cout << "znacheniya, j: " << j << ", ctb[j]: " << ctb[j] << endl;
					cout << "\tx[j]: " << x[j] << ", y[j]: " << y[j] << ", x[ctb[j] + n]: " 
						<< x[ctb[j] + n] << ", y[ctb[j] + n]: " << y[ctb[j] + n] << endl;
					cout << "DEBUG, distance = " << distance(x[j], y[j], x[ctb[j] + n], y[ctb[j] + n]);
					cout << ", length = " << len << endl;*/
				}
				if (len < minimal) {
					minimal = len;
					print(ctb, ctb.size());
				}
			}
			else {
				build(n, x, y, ctb, minimal);
			}
		}
		ctb.pop_back();
	}
}

int main() {
	cout << "Number of Red/Blue dots: " << endl;
	int n;
	cin >> n;
	vector <double> x(2 * n);
	vector <double> y(2 * n);

	cout << "Red dots (x, y): " << endl;
	for (int i = 0; i < n; i++) {
		cin >> x[i] >> y[i];
	}

	cout << "Blue dots (x, y): " << endl;
	for (int i = n; i < 2 * n; i++) {
		cin >> x[i] >> y[i];
	}

	double minimal = DBL_MAX;
	vector <int> ctb;

	build(n, x, y, ctb, minimal);
	cout << "Minimal sum is: " << minimal << endl;

}
