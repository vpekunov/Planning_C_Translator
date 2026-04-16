#pragma plan vectorized

#include <iostream>

using namespace std;

#pragma plan common begin

#define EPS 1E-9

__constant float AdamsTable[5][6] = {
   {1.0f,  1.0f,  0.0f,  0.0f,   0.0f,  0.0f  },
   {2.0f,  1.0f,  1.0f,  0.0f,   0.0f,  0.0f  },
   {12.0f, 5.0f,  8.0f,  -1.0f,  0.0f,  0.0f  },
   {24.0f, 9.0f,  19.0f, -5.0f,  1.0f,  0.0f  },
   {720.0f,251.0f,646.0f,-264.0f,106.0f,-19.0f}
};

__constant float AdamsTableB[5][6] = {
   {1.0f,  1.0f,   0.0f,    0.0f,   0.0f,    0.0f  },
   {2.0f,  3.0f,   -1.0f,   0.0f,   0.0f,    0.0f  },
   {12.0f, 23.0f,  -16.0f,  5.0f,   0.0f,    0.0f  },
   {24.0f, 55.0f,  -59.0f,  37.0f,  -9.0f,   0.0f  },
   {720.0f,1901.0f,-2774.0f,2616.0f,-1274.0f,251.0f}
};

#pragma plan common end

// Должен быть дедуктивный макромодуль

// k -- максимальный порядок метода
// n -- число уравнений
// m -- число коэффициентов при членах в правой части
// T -- конечное время
// tau -- шаг интегрирования
#def_module() make_adams_rozhkov(NAME, KF_EQ, SF_EQ) {
@goal:-brackets_off.
	reenterable @goal:-write(NAME).(bool init, int k, int n, int m, float tau, float T, _local(__planned__.m) float * kf, _local(__planned__.m) float * sf, _global(n) float * y0, _global(n) float * y) {
		if (init) {
			for (int i = 0; i < n; i++) {
				plan_last(false, k, n, m, tau, T, kf, sf, y0, y);
				kf += m;
				sf += m;
			}
			plan_group_typize(NULL, n);
		} else {
 			int id = plan_vector_id();
			int order = 1; // Текущий порядок метода
			float f[7]; // Значения функции
			float t = 0.0f;
			if (id < n) y[id] = y0[id];
			barrier(0);
			if (id < n) f[0] = y[id]*(@goal:-write(KF_EQ).)+(@goal:-write(SF_EQ).);
			barrier(0);
			while (fabs(t - T) > EPS) {
				if (t + tau > T) {
					tau = T - t;
					// РК-4
					float a1 = tau*(y[id]*(@goal:-write(KF_EQ).) + (@goal:-write(SF_EQ).));
					if (id < n) y[id] = y0[id] + a1/2.0f;
					barrier(0);
					float b1 = tau*(y[id]*(@goal:-write(KF_EQ).) + (@goal:-write(SF_EQ).));
					if (id < n) y[id] = y0[id] + b1/2.0f;
					barrier(0);
					float c1 = tau*(y[id]*(@goal:-write(KF_EQ).) + (@goal:-write(SF_EQ).));
					if (id < n) y[id] = y0[id] + c1;
					barrier(0);
					float d1 = tau*(y[id]*(@goal:-write(KF_EQ).) + (@goal:-write(SF_EQ).));
					if (id < n) {
						y0[id] += (a1+2.0f*b1+2.0f*c1+d1)/6.0f;
						y[id] = y0[id];
					}
					barrier(0);
				} else {
					// Адамс_Рожков_Пекунов
					float ffp = 0.0f;
					float ff, sc;

					for (int i = 1; i <= order; i++) {
						ffp += AdamsTableB[order-1][i]*f[i-1]/AdamsTableB[order-1][0];
					}

					if (id < n) y[id] += tau*ffp;
					barrier(0);

					ff = AdamsTable[order-1][1]*(@goal:-write(KF_EQ).)/AdamsTable[order-1][0];
					sc = AdamsTable[order-1][1]*(@goal:-write(SF_EQ).)/AdamsTable[order-1][0];
					for (int i = 2; i <= order; i++) {
						sc += AdamsTable[order-1][i]*f[i-2]/AdamsTable[order-1][0];
					}

					float P = tau*ff;

					if (id < n) y[id] = (y0[id] + tau*sc) / (1.0f - tau*ff);
					barrier(0);

					for (int i = order; i > 0; i--) {
						f[i] = f[i-1];
					}
					if (id < n) {
						f[0] = y[id]*(@goal:-write(KF_EQ).)+(@goal:-write(SF_EQ).);
						y0[id] = y[id];
					}
					barrier(0);
					if (order < k) order++;
				}
				t += tau;
			}
		}
	}
};

make_adams_rozhkov('ode_van_der_pol', 'kf[0]*100.0f*(1.0f-y[0]*y[0])', 'sf[0]*y[1]+sf[1]*(-y[0])')

int main() {
	float kf[2][2] = { { 0.0f, 0.0f }, { 1.0f, 0.0f } };
	float sf[2][2] = { { 1.0f, 0.0f }, { 0.0f, 1.0f } };
	float y0[2] = { 0.0f, 1.0f };
	float y1[2] = { 0.0f, 0.0f };
	ode_van_der_pol(true, 4, 2, 2, 0.001, 17.0, (float *) kf, (float *) sf, y0, y1);
	cout << y1[0] << " " << y1[1] << endl;
}
