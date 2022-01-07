// ���������� ������� ������ �������� ����������� � ���������������" �������� � ������� ����������, � ��������� ��������
// ���� ����������� ����������� ������ ����� ��� �������� ��������� � �������� ������������

// [3 layered: 5, h, 3, h + lin] : 1168.88 [1144.57 sec]
// [no predictor] : 1168.89 [10163 sec]

#include "memoization.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <omp.h>

using namespace std;

const double tol = 1E-2; // ���������� ����������� ������� �����������

const double a2 = 0.143E-6; // ����������� ���������������������� [�2/�]
const double U = 3.0; // �������� �������� ���� �� ����� [�/�]
const double c = 4183; // ������������ ���� [��/��/�]
const double ro = 1000; // ��������� ���� [��/�3]
const double L = 1000; // ����� ����� [�]

const double Tenv = 273.15 + 5.0; // ����������� ����� [�]
const double Tin = 273.15 + 70.0; // ����������� �� ����� [�]
const double Taim = 273.15 + 60.0; // ����������� �� ������ [�]

#pragma memoization(i,o) feed_forward(0.001, 0.05, 2000, 5, h, 3, h) controlled(7,2)
void get_t(double alpha, double & t1) {
	const int N = 1000; // ����� �����
	const double h = L/(N-1); // ��� �����
	const double tau = 0.01; // ��� �� �������

	double T[N] = { Tin }; // ��������� ������� ������� ���� �����
	double T1[N] = { Tin };

	// �������������� �� ������������ -- ������ ��������� �������� ����� ����� ������ ������
	bool stable = false;
	while (!stable) {
		stable = true;
		for (int i = 1; i < N-1; i++) {
			double delta = tau*(-U*(T[i]-T[i-1])/h + a2*(T[i-1]-2.0*T[i]+T[i+1])/h/h + alpha*(Tenv-T[i])/c/ro/h);
			T1[i] = T[i] + delta;
			if (fabs(delta) > tol) stable = false;
		}
		for (int i = 1; i < N-1; i++)
			T[i] = T1[i];
		T[N-1] = T[N-2]; // ��������� ������� ������� ���� ������
	}
	t1 = T[N-1];
}

// ������� �������������� ������� (������� ������ �������� ����������� �� ������)
double F(double alpha) {
	double d, t1;
	get_t(alpha, t1);
	d = Taim - t1;
	return d*d;
}

double g(double alpha) {
	const double hg = 0.005; // ��� ��� ���������� ���������
	return (F(alpha+hg)-F(alpha))/hg;
}

int main() {
	srand((unsigned int) time(NULL));

	double alpha;

	// �������� �����
	double time0 = omp_get_wtime();

	// ����� ������� ����������� ����������� �������
	double err = 1E100; // ������� ������
	alpha = 600; // ��������� �����������
	while (err > tol) {
		double grad = g(alpha); // ��������

		double F0 = F(alpha);
		cout << "Error^2(" << alpha << ") = " << F0 << endl;

		double h = 10;
		do {
			double aa = alpha - h*grad;
			double Ft = F(aa);
			if (Ft < F0) {
				F0 = Ft;
				alpha = aa;
				cout << "Error^2(" << aa << ") = " << F0 << endl;
			} else
				h /= 2;
		} while (h > 0.001);
		err = F0;
	} 

	cout << "a2 = " << alpha << " " << "F = " << F(alpha) << endl;

	double time1 = omp_get_wtime(); // ������ ������� �������
	cout << "Elapsed time (predictor) = " << (time1-time0) << " sec." << endl;

	return 0;
}