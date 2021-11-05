#include <iostream>
#include <stdio.h>

using namespace std;

class Point
{
public:
	double* x;
	double* y;
	double* b;
	double* c;
	double* h;
	double* d;
	int n;
	Point(int _n);
	void countH();
	void countC();
	void countB();
	void countD();
	void sorting();
	void inicializator();
};

Point::Point(int _n)
{
	(*this).n = _n;
	(*this).x = new double[_n];
	(*this).y = new double[_n];
	(*this).h = new double[_n];
	(*this).c = new double[_n];
	(*this).b = new double[_n];
	(*this).d = new double[_n];
}
void Point::countH()
{
	for (int i = 1; i < n; i++)
	{
		h[i] = x[i] - x[i-1];
	}
}


void Point::countC()
{
	double **mainMatrix = new double* [(*this).n-1];
	double* free = new double[(*this).n - 1];
	double y = 0;//вспомогательное число для метода прогонки
	double* progonka = new double[(*this).n - 1];//вспомогательный массив
	double* progonka1 = new double[(*this).n - 1];//вспомогательный массив
	for (int i = 0; i < n - 1; i++)
	{
		mainMatrix[i] = new double[n-1];
		for(int j = 0; j<n-1;j++)
		mainMatrix[i][j] = 0;
	}


	for (int i = 1; i < n-1; i++)
	{
		if (i == n-2)
		{
			free[i] = 3 * ((((*this).y[i + 1] - (*this).y[i]) / (*this).h[i + 1]) - (((*this).y[i] - (*this).y[i - 1]) / (*this).h[i]));
			mainMatrix[i][i - 1] = (*this).h[i];
			mainMatrix[i][i] = 2 * ((*this).h[i] + (*this).h[i + 1]);
			continue;
		}
		free[i] = 3 * ((((*this).y[i + 1] - (*this).y[i]) / (*this).h[i + 1]) - (((*this).y[i] - (*this).y[i-1]) / (*this).h[i]));
        mainMatrix[i][i-1] = (*this).h[i];
		mainMatrix[i][i] = 2*((*this).h[i]+ (*this).h[i+1]);
		mainMatrix[i][i+1] = (*this).h[i + 1];
	}

	y = mainMatrix[1][1];
	progonka[1] = -mainMatrix[1][2] / y;
	progonka1[1] = free[1] / y;
	for (int i = 2; i < n-1; i++) {
		y = mainMatrix[i][i] + mainMatrix[i][i - 1] * progonka[i - 1];
		progonka[i] = -mainMatrix[i][i + 1] / y;
		progonka1[i] = (free[i] - mainMatrix[i][i - 1] * free[i - 1]) / y;
	}
	c[n-2] = (free[n-2] - mainMatrix[n-2][n-3] * progonka1[n-3]) / (mainMatrix[n-2][n-2] + mainMatrix[n-2][n-3] * progonka[n-3]);
	for (int i = n-2; i >= 1; i--) {
		c[i] = progonka[i] * c[i + 1] + progonka1[i];
	}
}

void Point::countB() 
{
	for (int i = 1; i < n; i++)
		b[i] = (y[i + 1] - y[i]) / h[i] - (h[i] * (2 * c[i + 1] - c[i])) / 3;
}

void Point::countD()
{
	for (int i = 1; i < n; i++)
		d[i] = (c[i + 1] - c[i]) / 3 * h[i];
}

void Point::sorting()
{
	int j = 0;
	double tmp = 0.0;
	for (int i = 0; i < (*this).n; i++) {
		j = i;
		for (int k = i; k < (*this).n; k++) {
			if (x[j] > x[k]) {
				j = k;
			}
		}
		tmp = x[i];
		x[i] = x[j];
		x[j] = tmp;
		tmp = y[i];
		y[i] = y[j];
		y[j] = tmp;
	}

}

void Point::inicializator()
{
	for (int i = 0; i < (*this).n; i++) {
		(*this).h[i] = 0;
		(*this).c[i] = 0;
		(*this).b[i] = 0;
		(*this).d[i] = 0;
	}

}

int main()
{
	int _n;
	cout << "Интерполяция кубическим сплайном\n"<<"Введите количество точек: ";
	cin >> _n;
	Point p(_n);
	cout << "\nВедите значения точек\n";
	for (int i = 0; i < p.n; i++)
	{
		cout << "\nТочка " << i + 1<<"\ny = ";
		cin >> p.y[i];
		cout << "x = ";
		cin >> p.x[i];
		int s = 0;
		for (int j = 0; j < i; j++)
			if (p.x[i] == p.x[j])
				s++;
		if (s)
		{
			i--;
			cout << "Введите неповторяющиеся значения x\n";
			continue;
		}
	}
	p.sorting();
	cout << "Введенные точки:";
	for (int i = 0; i < p.n; i++)
	{
		cout << "\nx" << i << " = " <<p.x[i];
		cout << "\ny" << i << " = "<<p.y[i]<<endl;
	}
	p.inicializator();
	p.countH();
	p.countC();
	p.countB();
	p.countD();
	cout << "h\t" << "c\t" << "b\t" << "d\t";
	for (int i = 1; i < p.n; i++)
	{
		cout << "\n" << p.h[i]<<"\t";
		cout << p.c[i] << "\t";
		cout << p.b[i] << "\t";
		cout << p.d[i] << "\t";
	}
	return 0;
}



