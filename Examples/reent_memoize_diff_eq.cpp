// ���������� ������� ������ �������� ����������� � "�������" �������� � ������� ����������
// ���� ����������� �� ����� �����

// Time (predictor) = 170.996 sec
// Tin = 336.476
// -------------
// Time (no predictor) = 1793.71 sec
// Tin = 336.354

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
const double L = 2000; // ����� ����� [�]

const double Tenv = 273.15 + 5.0; // ����������� ����� [�]
const double Taim = 273.15 + 60.0; // ������� ����������� �� ������ [�]

#pragma memoization(i, o) feed_forward(0.01, 0.05, 2000, 5, e)
void get_t(double t0, double & t1) {
	const int N = 2000; // ����� �����
	const double h = L/(N-1); // ��� �����
	const double tau = 0.01; // ��� �� �������

	double T[N] = { t0 }; // ��������� ������� ������� ���� �����
	double T1[N] = { t0 };

	// �������������� �� ������������
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

int main() {
	srand((unsigned int) time(NULL));

	// ������� �������������� ������� (������� ������ �������� ����������� �� ������)
	auto F = [&] (double t0)->double {
		double d, t1;
		predict_get_t(t0, t1);
		d = Taim - t1;
		return d*d;
	};

	double t0;

	// ������� ������ ������ � ����������
	// �������� �����
	double time0 = omp_get_wtime();

	const int NN = 10; // ����� "�����������" �����

	// ������ ����������
	for (int i = 0; i < NN; i++) {
		double t1;
		t0 = 273.15 + 90.0 - 30.0*i/(NN-1);
		get_t(t0, t1);
		cout << "Boost: (" << t0 << ") = " << t1 << endl;
	}

	// ����� ������� ����������� ����������� �������
	double delta = 1E100; // ������� ������
	t0 = 273.15 + 90.0; // ��������� �����������
	while (delta > tol) {
		const double hg = 0.0001; // ��� ��� ���������� ���������
		// ������� ��������
		double F0 = F(t0);

		cout << "Error^2(" << t0 << ") = " << delta << endl;

		delta = F0;
		if (delta > tol) {
			double F1 = F(t0 + hg);
			double g = (F1-F0)/hg; // ��������

			t0 += -0.1*g;
		}
	} 

	cout << "T = " << t0 << endl;

	double time1 = omp_get_wtime(); // ������ ������� �������
	cout << "Elapsed time (predictor) = " << (time1-time0) << " sec." << endl;

	// ��������� ������, �� ��� ����������

	// ������� �������������� ������� (������� ������ �������� ����������� �� ������)
	auto FF = [&] (double t0)->double {
		double d, t1;
		get_t(t0, t1);
		d = Taim - t1;
		return d*d;
	};

	// ����� ������� ����������� ����������� �������
	delta = 1E100; // ������� ������
	t0 = 273.15 + 90.0; // ��������� �����������
	while (delta > tol) {
		const double hg = 0.0001; // ��� ��� ���������� ���������
		// ������� ��������
		double F0 = FF(t0);

		cout << "Error^2(" << t0 << ") = " << delta << endl;

		delta = F0;
		if (delta > tol) {
			double F1 = FF(t0 + hg);
			double g = (F1-F0)/hg; // ��������

			t0 += -0.1*g;
		}
	} 

	cout << "T = " << t0 << endl;

	double time2 = omp_get_wtime(); // ������ ������� �������
	cout << "Elapsed time (no predictor) = " << (time2-time1) << " sec." << endl;

	return 0;
}