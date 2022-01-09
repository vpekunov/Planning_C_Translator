// Мемоизация функции поиска конечной температуры с автоматическими" разгоном и вызовом предиктора, с контролем точности
// Ищем температуру на входе трубы

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

const double tol = 1E-4; // Допустимая погрешность расчета температуры

const double a2 = 0.143E-6; // Коэффициент температуропроводности [м2/с]
const double U = 3.0; // Скорость движения воды по трубе [м/с]
const double alpha = 350.0; // Коэффициент теплоотдачи трубы [Вт/м2/К]
const double c = 4183; // Теплоемкость воды [Дж/кг/К]
const double ro = 1000; // Плотность воды [кг/м3]
const double L = 1000; // Длина трубы [м]

const double Tenv = 273.15 + 5.0; // Температура среды [К]
const double Taim = 273.15 + 60.0; // Целевая температура на выходе [К]

#pragma memoization(i,o) feed_forward(0.1, 0.05, 2000) controlled(7,2)
void get_t(double t0, double & t1) {
	const int N = 1000; // Число узлов
	const double h = L/(N-1); // Шаг сетки
	const double tau = 0.01; // Шаг по времени

	double T[N] = { t0 }; // Граничное условие первого рода слева
	double T1[N] = { t0 };

	// Интегрирование до установления -- решаем уравнение переноса тепла явной схемой Эйлера
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
		T[N-1] = T[N-2]; // Граничное условие второго рода справа
	}
	t1 = T[N-1];
}

// Целевая минимизируемая функция (квадрат ошибки значения температуры на выходе)
double F(double t0) {
	double d, t1;
	get_t(t0, t1);
	d = Taim - t1;
	return d*d;
}

double g(double t0) {
	const double hg = 0.05; // Шаг для вычисления градиента
	return (F(t0+hg)-F(t0))/hg;
}

int main() {
	srand((unsigned int) time(NULL));

	double t0;

	// Засекаем время
	double time0 = omp_get_wtime();

	// Поиск входной температуры градиентным методом
	double err = 1E100; // Квадрат ошибки
	t0 = 273.15 + 90.0; // Начальное приближение
	while (err > tol) {
		double grad = g(t0); // Градиент

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

	double time1 = omp_get_wtime(); // Вторая засечка времени
	cout << "Elapsed time (predictor) = " << (time1-time0) << " sec." << endl;

	return 0;
}