// Мемоизация функции поиска конечной температуры с "ручными" разгоном и вызовом предиктора
// Ищем температуру на входе трубы

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

const double tol = 1E-4; // Допустимая погрешность расчета температуры

const double a2 = 0.143E-6; // Коэффициент температуропроводности [м2/с]
const double U = 3.0; // Скорость движения воды по трубе [м/с]
const double alpha = 350.0; // Коэффициент теплоотдачи трубы [Вт/м2/К]
const double c = 4183; // Теплоемкость воды [Дж/кг/К]
const double ro = 1000; // Плотность воды [кг/м3]
const double L = 2000; // Длина трубы [м]

const double Tenv = 273.15 + 5.0; // Температура среды [К]
const double Taim = 273.15 + 60.0; // Целевая температура на выходе [К]

#pragma memoization(i, o) feed_forward(0.01, 0.05, 2000, 5, e)
void get_t(double t0, double & t1) {
	const int N = 2000; // Число узлов
	const double h = L/(N-1); // Шаг сетки
	const double tau = 0.01; // Шаг по времени

	double T[N] = { t0 }; // Граничное условие первого рода слева
	double T1[N] = { t0 };

	// Интегрирование до установления
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

int main() {
	srand((unsigned int) time(NULL));

	// Целевая минимизируемая функция (квадрат ошибки значения температуры на выходе)
	auto F = [&] (double t0)->double {
		double d, t1;
		predict_get_t(t0, t1);
		d = Taim - t1;
		return d*d;
	};

	double t0;

	// Сначала делаем расчет с предикцией
	// Засекаем время
	double time0 = omp_get_wtime();

	const int NN = 10; // Число "разгоночных" точек

	// Разгон предиктора
	for (int i = 0; i < NN; i++) {
		double t1;
		t0 = 273.15 + 90.0 - 30.0*i/(NN-1);
		get_t(t0, t1);
		cout << "Boost: (" << t0 << ") = " << t1 << endl;
	}

	// Поиск входной температуры градиентным методом
	double delta = 1E100; // Квадрат ошибки
	t0 = 273.15 + 90.0; // Начальное приближение
	while (delta > tol) {
		const double hg = 0.0001; // Шаг для вычисления градиента
		// Считаем градиент
		double F0 = F(t0);

		cout << "Error^2(" << t0 << ") = " << delta << endl;

		delta = F0;
		if (delta > tol) {
			double F1 = F(t0 + hg);
			double g = (F1-F0)/hg; // Градиент

			t0 += -0.1*g;
		}
	} 

	cout << "T = " << t0 << endl;

	double time1 = omp_get_wtime(); // Вторая засечка времени
	cout << "Elapsed time (predictor) = " << (time1-time0) << " sec." << endl;

	// Повторяем расчет, но без предиктора

	// Целевая минимизируемая функция (квадрат ошибки значения температуры на выходе)
	auto FF = [&] (double t0)->double {
		double d, t1;
		get_t(t0, t1);
		d = Taim - t1;
		return d*d;
	};

	// Поиск входной температуры градиентным методом
	delta = 1E100; // Квадрат ошибки
	t0 = 273.15 + 90.0; // Начальное приближение
	while (delta > tol) {
		const double hg = 0.0001; // Шаг для вычисления градиента
		// Считаем градиент
		double F0 = FF(t0);

		cout << "Error^2(" << t0 << ") = " << delta << endl;

		delta = F0;
		if (delta > tol) {
			double F1 = FF(t0 + hg);
			double g = (F1-F0)/hg; // Градиент

			t0 += -0.1*g;
		}
	} 

	cout << "T = " << t0 << endl;

	double time2 = omp_get_wtime(); // Третья засечка времени
	cout << "Elapsed time (no predictor) = " << (time2-time1) << " sec." << endl;

	return 0;
}