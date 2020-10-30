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
		// is_solved проверяет, чтобы в претендентах не было вариантов, где >1 КТ соединена с 1 СТ
		if (is_solved(ctb, ctb.size())) {
			if (ctb.size() == n) {
				double len = 0;
				for (int j = 0; j < n; j++) {
					len += distance(x[j], y[j], x[ctb[j] + n], y[ctb[j] + n]);
				}
				if (len < minimal) {
					minimal = len;
					print(ctb, ctb.size());
				}
			}
			else {
				// рекурсивный перебор
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

	// ЗАПОЛНЕНИЕ работает следующим образом:
	// Допустим, точки 2.
	// Тогда в векторе X будет идти 2 координаты x для красных точек, ЗАТЕМ две координаты x для синих!
	// e.g. красные: (2, 5), (3, 6); синие: (3, 1), (5, 9); 
	// Вектор x: [2, 3, 3, 5].
	// Вектор y: [5, 6, 1, 9].
	// Первая синия точка легко вызывается через x[n], y[n].
	
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

	// Массив хранит синие точки, с которыми соединены красные соответстующих индексов.
	// e.g. в случае выше он будет хранить [0, 0] -
	// Обе точки (индекс 0, индекс 1) вектора x соединены с одной точкой (индекс 0, индекс 0) вектора y.
	// Так как это вовсе не решение, мы будем обрабатывать дальше.
	// В этой версии вместо обработки будет полный перебор с проверкой, т.е. ...
	
	build(n, x, y, ctb, minimal);
	cout << "Minimal sum is: " << minimal << endl;

}
