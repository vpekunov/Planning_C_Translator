// ���������� ������� ������ �������� ����������� � ���������������" �������� � ������� ����������, � ��������� ��������
// ���� ����������� �� ����� �����

// [ no controlled = 334.73 [206.04 sec]
// [ 2-layered (5 exp + 1 lin) = 334.81 [117 sec]
// [1 layered [1 lin] = 334.71 [49.7 sec]

#include "memoization.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <omp.h>

using namespace std;

const double tol = 1E-4; // ���������� ����������� ������� �����������

const double a2 = 0.143E-6; // ����������� ���������������������� [�2/�]
const double U = 3.0; // �������� �������� ���� �� ����� [�/�]
const double alpha = 350.0; // ����������� ����������� ����� [��/�2/�]
const double c = 4183; // ������������ ���� [��/��/�]
const double ro = 1000; // ��������� ���� [��/�3]
const double L = 1000; // ����� ����� [�]

const double Tenv = 273.15 + 5.0; // ����������� ����� [�]
const double Taim = 273.15 + 60.0; // ������� ����������� �� ������ [�]

#pragma memoization(i,o) feed_forward(0.1, 0.05, 2000) controlled(7,2)
void get_t(double t0, double & t1) {
	const int N = 1000; // ����� �����
	const double h = L/(N-1); // ��� �����
	const double tau = 0.01; // ��� �� �������

	double T[N] = { t0 }; // ��������� ������� ������� ���� �����
	double T1[N] = { t0 };

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
double F(double t0) {
	double d, t1;
	get_t(t0, t1);
	d = Taim - t1;
	return d*d;
}

double g(double t0) {
	const double hg = 0.05; // ��� ��� ���������� ���������
	return (F(t0+hg)-F(t0))/hg;
}

int main() {
	srand((unsigned int) time(NULL));

	double t0;

	// �������� �����
	double time0 = omp_get_wtime();

	// ����� ������� ����������� ����������� �������
	double err = 1E100; // ������� ������
	t0 = 273.15 + 90.0; // ��������� �����������
	while (err > tol) {
		double grad = g(t0); // ��������

		double F0 = F(t0);
		cout << "Error^2(" << t0 << ") = " << F0 << endl;

		double h = 0.1;
		do {
			double tt = t0 - h*grad;
			double Ft = F(tt);
			if (Ft < F0) {
				F0 = Ft;
				t0 = tt;
				cout << "Error^2(" << t0 << ") = " << F0 << endl;
			} else
				h /= 2;
		} while (h > 0.001);
		err = F0;
	} 

	cout << "T = " << t0 << " " << "F = " << F(t0) << endl;

	double time1 = omp_get_wtime(); // ������ ������� �������
	cout << "Elapsed time (predictor) = " << (time1-time0) << " sec." << endl;

	return 0;
}