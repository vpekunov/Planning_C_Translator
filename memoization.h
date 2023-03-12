#ifndef __MEMOIZATION_H__
#define __MEMOIZATION_H__

#pragma syntax nocheck

#scan(memoFun)

#include <vector>
#include <map>
#include <set>

#include <math.h>
#include <stdlib.h>

using namespace std;

int __max_history_size = 100;

void set_memoization_max_history(int v) {
	__max_history_size = v;
}


template<class T>
bool is_less(T * A, T * B, int n) {
	for (int i = 0; i < n; i++)
		if (A[i] < B[i])
			return true;
		else if (A[i] == B[i])
			continue;
		else
			return false;
	return false;
}

template<class T>
bool is_equal(T * A, T * B, int n) {
	for (int i = 0; i < n; i++)
		if (A[i] == B[i])
			continue;
		else
			return false;
	return true;
}

template<class T>
void fill_into(vector<double> * V, T * A, int n) {
	for (int i = 0; i < n; i++)
		V->push_back(A[i]);
}

template<class T>
void fill_out(vector<double> * V, int & ptr, T * A, int n) {
	for (int i = 0; i < n; i++)
		A[i] = (*V)[ptr++];
}

template<class T>
double diff(T * A, T * B, int n) {
	double result = 0.0;
	for (int i = 0; i < n; i++)
		result += fabs(A[i] - B[i]);
	return result;
}

class __Predictor {
protected:

   vector< vector<double> * > XX;
   vector< vector<double> * > YY;

public:

   __Predictor() {
      XX.reserve(1000);
      YY.reserve(1000);
   }

   virtual ~__Predictor() {
      clear();
   }

   virtual void clear() {
      for (auto & X : XX) {
          delete X;
      }
      XX.clear();
      XX.reserve(1000);

      for (auto & Y : YY) {
          delete Y;
      }
      YY.clear();
      YY.reserve(1000);
   }

   virtual void addPointX(vector<double> * X) {
      if (XX.size() == XX.capacity()) XX.reserve(XX.size() + 200);
      XX.push_back(X);
   }
   virtual void addPointY(vector<double> * Y) {
      if (YY.size() == YY.capacity()) YY.reserve(YY.size() + 200);
      YY.push_back(Y);
   }

   virtual void calculate_sample(vector<double> X, vector<double> & Y) = 0;
   virtual void train() = 0;
};

class __FeedForwardNet : public __Predictor {
private:

   double tol;
   double nu;
   int MAX_EPOCHS;

   vector< double > MMAX, MMIN, YMAX, YMIN;

   vector<char> funs;

   vector< vector<double> > B;
   vector< vector< vector<double> > > K;
   vector< vector<double> > X1, Y1;

   inline double S(char mode, double s) {
	if (mode == 'e')
		return 1.0 / (1.0 + exp(-s));
	else if (mode == 'h')
		return tanh(s);
	else if (mode == 'l')
		return s;
	else if (mode == 'r')
		return s < 0.0 ? 0.0 : s;
	else
		throw runtime_error("Unknown activation function");
   }

   inline double D(char mode, double s, double f_s) {
	if (mode == 'e')
		return f_s*(1.0 - f_s);
	else if (mode == 'h')
		return 1.0 - f_s*f_s;
	else if (mode == 'l')
		return 1.0;
	else if (mode == 'r')
		return s < 0.0 ? 0.0 : 1.0;
	else
		throw runtime_error("Unknown activation function");
   }
public:

   __FeedForwardNet(double tol, double nu, int max_epochs, int nx, int ny, const vector<int> & layers, const vector<char> & funs) : __Predictor() {
      this->tol = tol;
      this->nu = nu;
      MAX_EPOCHS = max_epochs;

      this->funs = funs;

      B.resize(layers.size()+1);
      K.resize(layers.size()+1);
      X1.resize(layers.size()+1);
      Y1.resize(layers.size()+1);

      for (int i = 0; i <= layers.size(); i++) {
          int nw = i == 0 ? nx : layers[i-1];
          int nn = i < layers.size() ? layers[i] : ny;
          B[i].resize(nn);
          X1[i].resize(nn);
          Y1[i].resize(nn);
          K[i].resize(nn);
          for (int j = 0; j < nn; j++) {
              B[i][j] = 1.0*rand()/RAND_MAX;
              K[i][j].resize(nw);
              for (int k = 0; k < nw; k++)
                  K[i][j][k] = 1.0*rand()/RAND_MAX;
          }
      }
   }

   void calculate_model(vector<double> * X) {
	if (X1.size() != B.size()) X1.resize(B.size());
	if (Y1.size() != B.size()) Y1.resize(B.size());
        for (int i = 0; i < B.size(); i++) {
		if (X1[i].size() != B[i].size()) X1[i].resize(B[i].size());
		if (Y1[i].size() != B[i].size()) Y1[i].resize(B[i].size());
		for (int j = 0; j < B[i].size(); j++) {
			double y = B[i][j];
			if (i == 0)
				for (int k = 0; k < X->size(); k++)
					y += K[i][j][k]*(*X)[k];
			else
				for (int k = 0; k < B[i-1].size(); k++)
					y += K[i][j][k]*Y1[i-1][k];
			X1[i][j] = y;
			Y1[i][j] = i == B.size()-1 ? y : S(funs[i], y);
		}
	}
   }
   virtual void calculate_sample(vector<double> X, vector<double> & Y) {
	for (int p = 0; p < X.size(); p++) {
		double d = MMAX[p]==MMIN[p] ? 1.0 : 2.0/(MMAX[p]-MMIN[p]);
		X[p] = -1.0 + (X[p]-MMIN[p])*d;
	}

	calculate_model(&X);
	Y.resize(B[B.size()-1].size());

	for (int p = 0; p < Y.size(); p++) {
		double d = YMAX[p]==YMIN[p] ? 1.0 : 2.0/(YMAX[p]-YMIN[p]);
		Y[p] = YMIN[p] + (Y1[B.size()-1][p]+1.0)/d;
	}
   }
   virtual void train() {
	  int L = XX.size();
	  int M = B.size();

	  if (L == 0) return;

	  MMAX.resize(XX[0]->size());
	  MMIN.resize(XX[0]->size());
	  for (int p = 0; p < XX[0]->size(); p++) {
		MMAX[p] = -1E100;
		MMIN[p] = 1E100;
		for (int i = 0; i < L; i++) {
			if ((*XX[i])[p] > MMAX[p]) MMAX[p] = (*XX[i])[p];
			if ((*XX[i])[p] < MMIN[p]) MMIN[p] = (*XX[i])[p];
		}
	  }

	  YMAX.resize(YY[0]->size());
	  YMIN.resize(YY[0]->size());
	  for (int p = 0; p < YY[0]->size(); p++) {
		YMAX[p] = -1E100;
		YMIN[p] = 1E100;
		for (int i = 0; i < L; i++) {
			if ((*YY[i])[p] > YMAX[p]) YMAX[p] = (*YY[i])[p];
			if ((*YY[i])[p] < YMIN[p]) YMIN[p] = (*YY[i])[p];
		}
	  }

	  for (int p = 0; p < XX[0]->size(); p++) {
		double d = MMAX[p]==MMIN[p] ? 1.0 : 2.0/(MMAX[p]-MMIN[p]);
		for (int i = 0; i < L; i++)
			(*XX[i])[p] = -1.0 + ((*XX[i])[p]-MMIN[p])*d;
	  }

	  for (int p = 0; p < YY[0]->size(); p++) {
	  	double yd = YMAX[p]==YMIN[p] ? 1.0 : 2.0/(YMAX[p]-YMIN[p]);
		for (int i = 0; i < L; i++)
			(*YY[i])[p] = -1.0 + ((*YY[i])[p]-YMIN[p])*yd;
	  }

	  vector< vector<double> > DB(M);
	  vector< vector< vector<double> > > DK(M);

	  const double alpha = 0.2;

	  int epochs = 0;

	  double err;

	  for (int i = 0; i < M; i++) {
		DB[i].resize(B[i].size());
		DK[i].resize(B[i].size());
		for (int j = 0; j < B[i].size(); j++)
			DK[i][j].resize(i == 0 ? XX[0]->size() : B[i-1].size());
	  }

	  vector<int> nums(L);
	  for (int i = 0; i < L; i++)
		nums[i] = i;
	  vector<int> idxs(L);
	  for (int i = 0; i < L; i++) {
		int idx = (int)(1.0*(nums.size()-1)*rand()/RAND_MAX);
		idxs[i] = nums[idx];
		nums.erase(nums.begin()+idx);
	  }

	  do {
		err = 0.0;
		for (int ii = 0; ii < L; ii++) {
			int i = idxs[ii];

			calculate_model(XX[i]);

			for (int yy = 0; yy < B[M-1].size(); yy++) {
				double YS = Y1[M-1][yy];
				double Y = (*YY[i])[yy];

				double delta = YS-Y;
				err += fabs(delta);

				DB[M-1][yy] = alpha*DB[M-1][yy] + (1-alpha)*(-nu*delta);
				B[M-1][yy] += DB[M-1][yy];

				if (M == 1) {
					for (int j = 0; j < XX[0]->size(); j++)
						for (int k = 0; k < B[0].size(); k++) {
							DK[0][k][j] = alpha*DK[0][k][j] + (1-alpha)*(-nu*delta*(*XX[i])[j]);
							K[0][k][j] += DK[0][k][j];
						}
				} else {
					for (int k = 0; k < DK[M-1][yy].size(); k++) {
						DK[M-1][yy][k] = alpha*DK[M-1][yy][k] + (1-alpha)*(-nu*delta*Y1[M-2][k]);
						K[M-1][yy][k] += DK[M-1][yy][k];
					}

					static double * deltas = new double[65536*4];
					memset(deltas, 0, 65536*4*sizeof(double));

					for (int k = 0; k < DK[M-1][yy].size(); k++) {
						deltas[k] = D(funs[M-2], X1[M-2][k], Y1[M-2][k])*delta*K[M-1][yy][k];
					}

					for (int lr = M-2; lr > 0; lr--) {
						for (int j = 0; j < B[lr-1].size(); j++)
							for (int k = 0; k < B[lr].size(); k++) {
								DK[lr][k][j] = alpha*DK[lr][k][j] + (1 - alpha)*(-nu*deltas[k] * Y1[lr-1][j]);
								K[lr][k][j] += DK[lr][k][j];
							}
						for (int k = 0; k < B[lr].size(); k++) {
							DB[lr][k] = alpha*DB[lr][k] + (1 - alpha)*(-nu*deltas[k]);
							B[lr][k] += DB[lr][k];
						}

						static double * deltas1 = new double[65536*4];
						memset(deltas1, 0, 65536*4*sizeof(double));

						for (int j = 0; j < B[lr-1].size(); j++)
							for (int k = 0; k < B[lr].size(); k++) {
								deltas1[j] += D(funs[lr-1], X1[lr-1][j], Y1[lr-1][j])*deltas[k] * K[lr][k][j];
							}
						for (int j = 0; j < B[lr-1].size(); j++)
							deltas[j] = deltas1[j];
					}

					for (int j = 0; j < XX[0]->size(); j++)
						for (int k = 0; k < B[0].size(); k++) {
							DK[0][k][j] = alpha*DK[0][k][j] + (1-alpha)*(-nu*deltas[k]*(*XX[i])[j]);
							K[0][k][j] += DK[0][k][j];
						}
					for (int k = 0; k < B[0].size(); k++) {
						DB[0][k] = alpha*DB[0][k] + (1-alpha)*(-nu*deltas[k]);
						B[0][k] += DB[0][k];
					}
				}
			}
		}
		// err /= L;
		err /= B[M-1].size();

	  } while (err > 0.05*tol && epochs++ < MAX_EPOCHS);
   }
};

#ifndef max
#define max(A,B) ((A) > (B) ? (A) : (B))
#endif

#ifndef min
#define min(A,B) ((A) < (B) ? (A) : (B))
#endif

#if _POSIX_C_SOURCE >= 200112L
#define _isnan isnan
#endif

namespace solve {
   /* LU - разложение  с выбором максимального элемента по диагонали */
   bool _GetLU(int NN, int * iRow, long double * A, long double * LU)
   {
    int i,j,k;
    try {
      memmove(LU,A,NN*NN*sizeof(long double));
      for (i=0;i<NN;i++)
          iRow[i]=i;
      for (i=0;i<NN-1;i++)
        {
         long double Big  = fabs(LU[iRow[i]*NN+i]);
         int iBig = i;

         long double Kf;

         for (j=i+1;j<NN;j++)
             {
              long double size = fabs(LU[iRow[j]*NN+i]);

              if (size>Big)
                 {
                  Big  = size;
                  iBig = j;
                 }
             }
         if (iBig!=i)
            {
             int V = iRow[i];
             iRow[i] = iRow[iBig];
             iRow[iBig] = V;
            }
         Kf = 1.0/LU[iRow[i]*NN+i];

         LU[iRow[i]*NN+i] = Kf;
         for (j=i+1;j<NN;j++)
             {
              long double Fact = Kf*LU[iRow[j]*NN+i];

              LU[iRow[j]*NN+i] = Fact;
              for (k=i+1;k<NN;k++)
                  LU[iRow[j]*NN+k] -= Fact*LU[iRow[i]*NN+k];
             }
        }
      LU[(iRow[NN-1]+1)*NN-1] = 1.0/LU[(iRow[NN-1]+1)*NN-1];
    }
    catch (...) {
      return false;
    }
    return true;
   }

   /* Метод LU - разложения */
   bool _SolveLU(int NN, int * iRow, long double * LU, long double * Y, long double * X)
   {
    int i,j,k;
    try {
      X[0] = Y[iRow[0]];
      for (i=1;i<NN;i++)
          {
           long double V  = Y[iRow[i]];

           for (j=0;j<i;j++)
               V -= LU[iRow[i]*NN+j]*X[j];
           X[i] = V;
          }

      X[NN-1]*=LU[(iRow[NN-1]+1)*NN-1];

      for (i=1,j=NN-2;i<NN;i++,j--)
          {
           long double V = X[j];

           for (k=j+1;k<NN;k++)
               V -= LU[iRow[j]*NN+k]*X[k];
           X[j] = V*LU[iRow[j]*NN+j];
          }
    }
    catch (...) {
      return false;
    }
    return true;
   }

}

// Расчет параметров функции Y = f(X1,X2) = g+a*X1+b*X2+c*X1*X2+d*X1^2+e*X2^2. Метод наименьших квадратов
// Вычисляет также YY -- значения выходов, вычисленные по f(X1,X2). Возвращает вектор (g, a, b, c, d, e)
long double * MNK_of_X1X2(const std::vector<double> X1, const std::vector<double> X2,
                     const std::vector<double> Y, double &err,
                     std::vector<double> & YY) {
 const int N = 6;
 int x1mask[N] = {0,1,0,1,2,0};
 int x2mask[N] = {0,0,1,1,0,2};
 int Z = X1.size();
 std::vector<std::vector<long double>> XP1(5,std::vector<long double>(Z,1.0));
 std::vector<std::vector<long double>> XP2(5,std::vector<long double>(Z,1.0));
 long double * A   = new long double[N*N];
 long double * LU  = new long double[N*N];
 long double * B   = new long double[N];
 long double * XX  = new long double[N];
 int *    iLU = new int[N];
 int i,j,k, ptr;
 long double Q;

 YY.resize(Z,0.0);
 for (i=1; i<5; i++)
   for (j=0; j<Z; j++) {
     XP1[i][j] = XP1[i-1][j]*X1[j];
     XP2[i][j] = XP2[i-1][j]*X2[j];
   }
 for (i=0, ptr=0; i<N; i++) {
   for (j=0; j<N; j++, ptr++) {
     Q = 0.0;
     for (k=0; k<Z; k++)
       Q += XP1[x1mask[j]][k]*XP2[x2mask[j]][k]*XP1[x1mask[i]][k]*XP2[x2mask[i]][k];
     A[ptr] = Q;
   }
   Q = 0.0;
   for (k=0; k<Z; k++)
     Q += Y[k]*XP1[x1mask[i]][k]*XP2[x2mask[i]][k];
   B[i] = Q;
 }
 if (!(solve::_GetLU(N, iLU, A, LU) && solve::_SolveLU(N, iLU, LU, B, XX))) {
    memset(XX,0,N*sizeof(long double));
    err = 1E300;
 } else {
   for (k=0; k<N; k++)
     if (_isnan(XX[k])) {
        memset(XX,0,N*sizeof(long double));
        err = 1E300;
        return XX;
     }
   err = 0.0;
   for (j=0; j<Z; j++) {
     long double R = 0.0;
     for (k=N-1; k>=0; k--)
       R += XP1[x1mask[k]][j]*XP2[x2mask[k]][j]*XX[k];
     YY[j] = R;
     double cur_err = (R-Y[j])*(R-Y[j]);
     err += cur_err;
   }
 }
 delete[] A;
 delete[] LU;
 delete[] B;
 delete[] iLU;
 
 return XX;
}

// Вычисление коэффициента корреляции векторов X и Y. Попутно считает среднеквадратичные отклонения SX, SY
double correlation(const std::vector<double> X, const std::vector<double> Y, double & SX, double & SY) {
  double corr = 0.0;
  double avrX = 0.0;
  double avrY = 0.0;
  int N = X.size();
  for (int i=0; i<N; i++) {
    avrX += X[i];
    avrY += Y[i];
  }
  avrX /= N;
  avrY /= N;
  SX = SY = 0.0;
  for (int i=0; i<N; i++) {
    double vx = X[i]-avrX;
    double vy = Y[i]-avrY;
    SX += vx*vx;
    SY += vy*vy;
    corr += vx*vy;
  }
  SX = sqrt(SX/(N-1));
  SY = sqrt(SY/(N-1));
  
  return corr/(N-1);
}

class MGUA_X1X2;

class MGUA_X1X2 {
  public:
    long double MGUAkoeffs[6];
    int    refcount;
    bool   FirstLayer;
    union {
      struct {
        MGUA_X1X2 * X1;
        MGUA_X1X2 * X2;
      };
      struct {
        double * NX1; double Min1, Max1;
        double * NX2; double Min2, Max2;
      };
    };
    MGUA_X1X2(long double * Kf, MGUA_X1X2 * _X1, MGUA_X1X2 * _X2):
       X1(_X1), X2(_X2) {
       FirstLayer = false; refcount = 0;
       memmove(MGUAkoeffs,Kf,sizeof(MGUAkoeffs));
       X1->refcount++;
       X2->refcount++;
       delete[] Kf;
    };
    MGUA_X1X2(long double * Kf, double * _X1, double * _X2, double min1, double max1, double min2, double max2):
       NX1(_X1), NX2(_X2), Min1(min1), Max1(max1), Min2(min2), Max2(max2) {
       FirstLayer = true; refcount = 0;
       memmove(MGUAkoeffs,Kf,sizeof(MGUAkoeffs));
       delete[] Kf;
    };
    virtual double getValue(const bool restrict = false) {
	  double _X1, _X2;
	  if (FirstLayer) {
		 double _NX1 = restrict ? (min(max(Min1, *NX1),Max1)) : *NX1;
		 double _NX2 = restrict ? (min(max(Min2, *NX2),Max2)) : *NX2;
		 _X1 = fabs(Max1-Min1)>1E-5 ? (_NX1-Min1)/(Max1-Min1) : _NX1;
		 _X2 = fabs(Max2-Min2)>1E-5 ? (_NX2-Min2)/(Max2-Min2) : _NX2;
	  } else {
		 _X1 = X1->getValue(restrict);
		 _X2 = X2->getValue(restrict);
	  }
	  return MGUAkoeffs[0]+MGUAkoeffs[1]*_X1+MGUAkoeffs[2]*_X2+
             MGUAkoeffs[3]*_X1*_X2+MGUAkoeffs[4]*_X1*_X1+MGUAkoeffs[5]*_X2*_X2;
	}
    ~MGUA_X1X2() {
      if (!FirstLayer) {
         if ((--(X1->refcount))==0) delete X1;
         if ((--(X2->refcount))==0) delete X2;
      }
    }
};

class TModelMGUA {
  private:
    MGUA_X1X2 * STRUCT;
    double denorm_value;
  public:
	TModelMGUA(double EPS, double * X, const std::vector<std::vector<double>> &XX, const std::vector<double> &YY, double &err);
    TModelMGUA(MGUA_X1X2 * out) {
      STRUCT = out;
      STRUCT->refcount++;
    };
    virtual double getValue(const bool restrict = false) {
		return STRUCT ? STRUCT->getValue(restrict) : denorm_value;
	};
    virtual ~TModelMGUA() {
      if (STRUCT && (--(STRUCT->refcount))==0)
         delete STRUCT;
    }
};

typedef struct {
  std::vector<double> YY;
  MGUA_X1X2 * ref;
} variantMGUA;

// Поиск интерполятора с помощью МГУА. XX[Z][N] -- объекты, N -- кол-во, Z -- число координат.
// YY[N] -- отклики. _X[Z] -- входы.
TModelMGUA::TModelMGUA(double EPS,
                       double * _X,
					   const std::vector< std::vector<double> > & XX,
					   const std::vector<double> & YY,
					   double &err) {
  STRUCT = NULL;

  int N = YY.size();
  int Z = XX.size();
  std::vector<double> mins(Z), maxs(Z);
  std::map<double,int> correlations;
  double SY;
  for (int i=0; i<Z; i++) {
    double SX;
    double corr = correlation(XX[i],YY,SX,SY);
    if (fabs(SY)<EPS)
       correlations[0.0] = -1;
    else if (fabs(SX*SY)>EPS) {
       double CORR = fabs(corr/(SX*SY));
       std::map<double,int>::iterator itc = correlations.find(CORR);
       if (itc==correlations.end()) correlations[CORR] = i;
       else if (++itc==correlations.end()) correlations[CORR+0.000001] = i;
       else correlations[(CORR+itc->first)*0.5] = i;
    }
    double xMin = 1E300;
    double xMax = -1E300;
    for (int j=0; j<N; j++) {
      if (XX[i][j]<xMin) xMin = XX[i][j];
      if (XX[i][j]>xMax) xMax = XX[i][j];
    }
    mins[i] = xMin;
    maxs[i] = xMax;
  }
  err = 1E300;
  if (correlations.size()>0) {
     std::map<double,int>::iterator itc0, itc = correlations.end();
     int BestV = (--itc)->second;
     if (BestV>=0) {
        std::map<double,variantMGUA> MGUA;
// ATTENTION! In Metalayer there is another formala
        int NPolies = max(1,(int)(0.8*(correlations.size()-1)*correlations.size()));
// END
        double LastCriterion = 1E300;
        int i;

		for (itc = correlations.begin(), i = 0; itc!=correlations.end() && i<NPolies; itc++, i++) {
			int V1 = itc->second;
			std::vector<double> VV(N);
			variantMGUA var;
			for (int j=0; j<N; j++)
				if (maxs[V1]-mins[V1]>EPS)
					VV[j] = (XX[V1][j]-mins[V1])/(maxs[V1]-mins[V1]);
				else
					VV[j] = XX[V1][j];
			var.YY = VV;
			var.ref = reinterpret_cast<MGUA_X1X2 *>(V1);
			MGUA[100.0-itc->first] = var; // Чтобы переменные с большей корреляцией с выходами попали в начало популяции.
		}
		while (MGUA.size()>1) {
			std::map<double,variantMGUA>::iterator i0,i1;
			std::map<double,variantMGUA> _MGUA;
			variantMGUA var;
			for (i0 = MGUA.begin(); i0!=MGUA.end(); i0++)
				for (i1 = i0, i1++; i1!=MGUA.end(); i1++) {
					if (reinterpret_cast<long long>(i0->second.ref) < Z) // В MGUA -- фиктивный первый слой (входные переменные)
						var.ref = new MGUA_X1X2(MNK_of_X1X2(i0->second.YY,i1->second.YY,YY,err,var.YY),
						                    _X+reinterpret_cast<long long>(i0->second.ref),_X+reinterpret_cast<long long>(i1->second.ref),
											mins[reinterpret_cast<long long>(i0->second.ref)],maxs[reinterpret_cast<long long>(i0->second.ref)],
											mins[reinterpret_cast<long long>(i1->second.ref)],maxs[reinterpret_cast<long long>(i1->second.ref)]);
					else // В MGUA -- настоящий слой
						var.ref = new MGUA_X1X2(MNK_of_X1X2(i0->second.YY,i1->second.YY,YY,err,var.YY),i0->second.ref,i1->second.ref);
					if (err<1E300) _MGUA[err] = var;
					else delete var.ref;
				}
			MGUA.clear();
			i0 = _MGUA.begin();
			if (i0!=_MGUA.end()) {
				int newNPolies = max(1,(double)min(NPolies,(int)_MGUA.size())*0.9);
				err = i0->first;
				if (LastCriterion-err<=1E-2 || newNPolies<2) {
					MGUA[err] = i0->second;
					if (!STRUCT) {
						STRUCT = i0->second.ref;
						STRUCT->refcount++;
					}
					i0++;
					while (i0!=_MGUA.end())
						delete (i0++)->second.ref;
					break;
				} else {
					i1 = _MGUA.begin();
					for (int k=0; k<NPolies && i1!=_MGUA.end(); k++) i1++;
					MGUA.insert(_MGUA.begin(),i1);
					while (i1!=_MGUA.end())
						delete (i1++)->second.ref;
				}
				NPolies = newNPolies;
				LastCriterion = err;
			}
		}
	 }
  }
  if (err == 1E300) {
     denorm_value = 0.0;
     for (double d : YY)
         denorm_value += d;
     if (YY.size() > 0) denorm_value /= YY.size();
     err = 0.0;
     for (double d : YY)
         err += (d-denorm_value)*(d-denorm_value);
  }
}

class __MGUA : public __Predictor {
private:
   vector<TModelMGUA *> predictors;
   int NX, NY;
   double * _X;

   double EPS;

public:

   __MGUA(double tol, int nx, int ny) : __Predictor() {
      _X = new double[nx];
      NX = nx;
      NY = ny;

      EPS = tol;
   }

   virtual void clear() {
      __Predictor::clear();
      for (TModelMGUA * &p : predictors)
          delete p;
      predictors.clear();
   }

   ~__MGUA() {
      delete[] _X;
   }

   virtual void calculate_sample(vector<double> X, vector<double> & Y) {
	for (int x = 0; x < NX; x++)
		_X[x] = X[x];
	Y.resize(NY);
	for (int y = 0; y < NY; y++)
		Y[y] = predictors[y]->getValue();
   }

   virtual void train() {
	int N = XX.size();

	for (TModelMGUA * &p : predictors)
		delete p;
	predictors.clear();

	int Z = NX;
	int K = NY;

	// _XX[Z][N] -- объекты, N -- кол-во, Z -- число координат.
	// _YY[N] -- отклики. _X[Z] -- входы.
	vector< vector<double> > _XX(Z);
	vector<double> _YY(N);

	for (int z = 0; z < Z; z++) {
		_XX[z].resize(N);
		for (int n = 0; n < N; n++)
			_XX[z][n] = XX[n]->at(z);
	}

	predictors.resize(K);
	double err;
	for (int k = 0; k < K; k++) {
		for (int n = 0; n < N; n++)
			_YY[n] = YY[n]->at(k);
		predictors[k] = new TModelMGUA(EPS, _X, _XX, _YY, err);
	}
   }
};

class __LIN_EXTRAPOLATOR : public __Predictor {
private:
   int NY;
   int P;

   double EPS;

   int * WP;
   double ** K;
   long double * A;
   long double * LU;
   long double * Y;
   long double * X;
public:

   __LIN_EXTRAPOLATOR(double tol, int p, int ny) : __Predictor() {
      P = p;
      NY = ny;

      WP = new int[NY];
      K = new double * [NY];
      for (int i = 0; i < NY; i++)
          K[i] = new double[P];

      A = new long double[P*P];
      LU = new long double[P*P];
      Y = new long double[P];
      X = new long double[P];

      EPS = tol;
   }

   ~__LIN_EXTRAPOLATOR() {
      delete[] WP;

      for (int i = 0; i < NY; i++)
          delete[] K[i];
      delete[] K;
      delete[] A;
      delete[] LU;
      delete[] Y;
      delete[] X;
   }

   virtual void addPointX(vector<double> * X) {
      if (XX.size() > 5*P) {
         delete *XX.begin();
         XX.erase(XX.begin());
      }
      XX.push_back(X);
   }
   virtual void addPointY(vector<double> * Y) {
      if (YY.size() > 5*P) {
         delete *YY.begin();
         YY.erase(YY.begin());
      }
      YY.push_back(Y);
   }

   virtual void calculate_sample(vector<double> X, vector<double> & Y) {
        map<double, int> timeline;

        int * IDX = new int[XX.size()];

        for (int i = 0; i < XX.size(); i++)
            timeline[XX[i]->at(0)] = i;

        map<double, int>::iterator it = timeline.begin();
        for (int c = 0; it != timeline.end(); it++, c++) {
        	IDX[c] = it->second;
        }

	Y.resize(NY);

	for (int y = 0; y < NY; y++) {
	   double val = K[y][0];
	   for (int j = 1; j < WP[y]; j++)
	   	val += K[y][j] * YY[IDX[XX.size() - WP[y] + j]]->at(y);
	   Y[y] = val;
	}

	delete[] IDX;
   }

   virtual void train() {
        map<double, int> timeline;

        long double * VV = new long double[XX.size()];

        for (int i = 0; i < XX.size(); i++)
            timeline[XX[i]->at(0)] = i;

        int iRow[1024];

        for (int p = 0; p < NY; p++) {
        	map<double, int>::iterator it = timeline.begin();
        	for (int c = 0; it != timeline.end(); it++, c++) {
            		VV[c] = YY[it->second]->at(p);
        	}

		double max_err = 1E300;
		WP[p] = -1;
		for (int pp = P; pp >= 1; pp--) {
			   memset(A, 0, P*P*sizeof(long double));
			   memset(Y, 0, P*sizeof(long double));

			   int L = XX.size();
			   for (int i = max(0, L - 1.5*P); i < L - pp + 1; i++) {
				   for (int j = 0, ptr = 0; j < pp; j++) {
					   long double XXV = j == 0 ? 1.0 : (long double) VV[i + j - 1];
					   for (int k = 0; k < pp; k++, ptr++) {
						   A[ptr] += (k == 0 ? 1.0 : (long double) VV[i + k - 1])*XXV;
					   }
					   Y[j] += XXV*(long double) VV[i + pp - 1];
				   }
			   }
			   bool result = _SolveGaussZeidel(pp, iRow, A, LU, Y, X) || _GetLU(pp, iRow, A, LU) && _SolveLU(pp, iRow, LU, Y, X);
			   if (result) {
				   for (int i = 0, ptr = 0; result && i < pp; i++) {
					   double val = 0.0;
					   for (int j = 0; result && j < pp; j++, ptr++) {
						   if (X[j] != X[j]) result = false;
						   val += A[ptr] * X[j];
					   }
					   double r = fabs(val - Y[i]);
					   if (r != r || r > 1E-3)
						   result = false;
				   }
			   }
			   double cur_err = 1E300;
			   if (result) {
				   int n = 0;
				   cur_err = 0.0;
				   for (int i = max(0, L - 1.5*P); i < L - pp + 1; i++, n++) {
				   	double val = X[0];
				   	for (int j = 1; j < pp; j++)
					   	val += X[j] * ((double) VV[i + j - 1]);
				   	double H = VV[i + pp - 1];
				   	if (H != 0) {
					   	cur_err += fabs(1.0*(H - val) / H);
				   	} else if (val != 0)
						cur_err += fabs(1.0*(H - val) / val);
				   }
				   if (n > 0) cur_err /= n;
			   }
			   if (result) {
				   if (cur_err <= max_err) {
					   WP[p] = pp;
					   for (int i = 0; i < pp; i++)
						K[p][i] = (double)X[i];
					   max_err = cur_err;
				   }
			   }
		}
	}

	delete[] VV;
   }
};

#def_pattern memoFun => make_memoization(gid(), //FIRST_MEMO/@Value, //OTHER_MEMOS/@Value, //MODE/@Value, //FIRST_DESC/@Value, //OTHER_DESCS/@Value, //FIRST_REF/@Value, //FIRST_TYPE/@Value, //FIRST/@Value, //FIRST_IDXS/@Value, //OTHER_REF/@Value, //OTHER_TYPE/@Value, //OTHER/@Value, //OTHER_IDXS/@Value, //THREEP/@Value, /root/ARGS/@Value, /root/RETTYPE/@Value, /root/ID/@Value, //CONTROLLED/@Value, //C1/@Value, //C2/@Value) {
  (((^)|(\;)+|\}|\\n)((\s|\\t)*\\n)*)(\s|\\t)*
  @begin
    \#pragma(\s|\\t)+memoization(\s|\\t)*
    \((\s|\\t)*((\*)*[giot])->{FIRST_MEMO}((\s|\\t)*\,(\s|\\t)*((\*)*[giot])->{OTHER_MEMOS})*\)
    (
     (\s|\\t)*
     ([A-Za-z0-9_]+)->{MODE}
     (\s|\\t)*
     \((\s|\\t)*([A-Za-z0-9_\*\.\+\-]+)->{FIRST_DESC}((\s|\\t)*\,(\s|\\t)*([A-Za-z0-9_\*\.\+\-]+)->{OTHER_DESCS})*\)
     (
      (
       (\s|\\t)*
       (controlled)->{CONTROLLED}
       (\s|\\t)*
       \((\s|\\t)*([A-Za-z0-9_]+)->{C1}(\s|\\t)*\,(\s|\\t)*([A-Za-z0-9_]+)->{C2}(\s|\\t)*\)
      )|
      (
       (\s|\\t)*
       (conditions)->{CONTROLLED}
       (\s|\\t)*
       \((\s|\\t)*((.{1,255})->{C1}\,)?=>{Predicates.BAL($,',')}
         (\s|\\t)*((.{1,255})->{C2}\))?=>{Predicates.BAL($,')')}(\s|\\t)*
      )
     )?
    )?
    (\s|\\t)*\\n
    (\s|\\t)*
    ((([A-Za-z0-9_\[\]\*]+((\\n|\s|\\t)*\*(\\n|\s|\\t)*|(\\n|\s|\\t)+))+)->{RETTYPE}(\w+(\\n|\s|\\t)*)->{ID}\(
         (
          ((((\\n|\s|\\t)*[A-Za-z0-9_\[\]]+)+)->{FIRST_TYPE}
            (
             ((\\n|\s|\\t)*(\&|(\*)+)->{FIRST_REF}
             )|
             (\\n|\s|\\t)+()->{FIRST_REF}
            )
            (\\n|\s|\\t)*(\w+)->{FIRST}(((\\n|\s|\\t)*\[(\\n|\s|\\t)*\w+(\\n|\s|\\t)*\])*)->{FIRST_IDXS}
            ((\\n|\s|\\t)*\,(((\\n|\s|\\t)*[A-Za-z0-9_\[\]]+)+)->{OTHER_TYPE}
             (
              ((\\n|\s|\\t)*(\&|(\*)+)->{OTHER_REF}
              )|
              (\\n|\s|\\t)+()->{OTHER_REF}
             )
             (\\n|\s|\\t)*(\w+)->{OTHER}(((\\n|\s|\\t)*\[(\\n|\s|\\t)*\w+(\\n|\s|\\t)*\])*)->{OTHER_IDXS}(\\n|\s|\\t)*
            )->{TAIL}*
            (
             (\\n|\s|\\t)*\,(\\n|\s|\\t)*(\.\.\.)->{THREEP}(\\n|\s|\\t)*
            )?
          )|
          ((\\n|\s|\\t)*(\.\.\.)->{THREEP}(\\n|\s|\\t)*)|
          (((\\n|\s|\\t)*void(\\n|\s|\\t)*)|((\\n|\s|\\t)*)->{EMPTY})
         )->{ARGS}\)(\s|\\t|\\n)*)
  @end
  (\s|\\t|\\n)*
  \{
};

#def_module() make_memoization(GID, FIRST_MEMO, OTHER_MEMOS, MODE, FIRST_DESC, OTHER_DESCS, FIRST_REF, FIRST_TYPE, FIRST, FIRST_IDXS, OTHER_REFS, OTHER_TYPES, OTHERS, OTHER_IDXS, THREEP, ARGS, RETTYPE, ID, CONTROLLED, C1, C2) {
@goal:-brackets_off.
@remove_spaces_r(L, L2):-
   append(L1,[' '], L),
   !,
   remove_spaces_r(L1, L2).
@remove_spaces_r(L, L):-!.
@trimr(S1, S2):-
   atom_chars(S1, L1),
   remove_spaces_r(L1, L2),
   atom_chars(S2, L2),
   !.
@write_str_list([],_):-!.
@write_str_list([''|T], DLM):-
   write_str_list(T, DLM),
   !.
@write_str_list([H|T], DLM):-
   write(H), write(DLM),
   write_str_list(T, DLM),
   !.
@write_delim_list2([],_):-!.
@write_delim_list2([''|T], DLM):-
   write_delim_list2(T, DLM).
@write_delim_list2([H|T], DLM):-
   write(DLM), write(H),
   write_delim_list2(T, DLM).
@write_delim_list([],_):-!.
@write_delim_list([''|T], DLM):-
   write_delim_list(T, DLM),
   !.
@write_delim_list([H|T], DLM):-
   write(H),
   write_delim_list2(T, DLM),
   !.
@get_num_items2(['['|TAG], LEXPR):-
   append(IND, [']','['|TAG2], TAG),
   !,
   append(['('|IND], [')','*'], L),
   get_num_items2(['['|TAG2], L2),
   append(L, L2, LEXPR),
   !.
@get_num_items2(['['|TAG], LEXPR):-
   append(L, [']'], TAG),
   !,
   append(['('|L], [')'], LEXPR),
   !.
@get_num_items(IDXS, EXPR):-
   atom_chars(IDXS, L),
   get_num_items2(L, LEXPR),
   atom_chars(EXPR, LEXPR),
   !.
@handle_ref(IR, M, IR2):-
   atom_chars(IR, IRL),
   delete(IRL, '&', IRL1),
   !,
   atom_chars(M, ML),
   delete(ML, 'i', ML1),
   delete(ML1, 'g', ML11),
   delete(ML11, 't', ML111),
   delete(ML111, 'o', ML2),
   !,
   subtract(IRL1, ML2, IRL2),
   !,
   atom_chars(IR2, IRL2).
@make_item(IT, IR, I, IIdx, M, H):-
   handle_ref(IR, M, IR1),
   atom_concat(IT, IR1, A1),
   atom_concat(A1, ' ', A11),
   atom_concat(A11, I, A2),
   atom_concat(A2, IIdx, H),
   !.
@make_items([], _, _, _, _, []):-!.
@make_items('', _, _, _, _, ['']):-!.
@make_items([IT|ITT], [IR|IRT], [I|IL], [IIdx|IIdxT], [M|MT], [H|T]):-
   make_item(IT, IR, I, IIdx, M, H),
   !,
   make_items(ITT, IRT, IL, IIdxT, MT, T).
@make_items(T, R, N, I, M, [H]):-
   make_item(T, R, N, I, M, H),
   !.
@make_arg(A, M, R):-
   atom_chars(M, ML),
   delete(ML, 'i', ML1),
   delete(ML1, 'g', ML11),
   delete(ML11, 't', ML111),
   delete(ML111, 'o', ML2),
   atom_chars(M2, ML2),
   atom_concat(M2, A, R),
   !.
@make_args([], _, []):-!.
@make_args('', _, ['']):-!.
@make_args([H|T], [M|MT], [H1|T1]):-
   make_arg(H, M, H1),
   make_args(T, MT, T1),
   !.
@make_args(H, M, [H1]):-
   make_arg(H, M, H1),
   !.
@make_list([], []):-!.
@make_list('', ['']):-!.
@make_list([H|T], [H|T]):-!.
@make_list(H, [H]):-!.
@sub_atom(A1,A2):-
   atom_chars(A1, L1),
   atom_chars(A2, L2),
   sublist(L2, L1).
@generate_cond_vars([], _, _, _, _):-!.
@generate_cond_vars([''], _, _, _, _):-!.
@generate_cond_vars([FirstA|OthersA], [FT|OT], [FM|OM], [FI|OI], NUM):-
   (sub_atom(FT, 'float'); sub_atom(FT, 'double')),
   !,
   write('  bool __v'), write(NUM),
   (
    (sub_atom(FM, 'i'); sub_atom(FM, 't'))->
     ( =(FI, '')->
        ( write(' = fabs(A.'), write(FirstA), write(') >= 1E-30 && (1.0 - fabs(B.'), write(FirstA), write('/A.'), write(FirstA), write(')) < 1E-13;'), nl
        );
        ( get_num_items(FI, SZ), write(' = is_equal(('), write(FT), write('*)A.'), write(FirstA), write(', ('), write(FT), write('*)B.'), write(FirstA), write(', '), write(SZ), write(');'), nl )
     );
     ( write(' = true;'), nl )
   ),
   !,
   NUM1 is NUM+1,
   generate_cond_vars(OthersA, OT, OM, OI, NUM1).
@generate_cond_vars([FirstA|OthersA], [FT|OT], [FM|OM], [FI|OI], NUM):-
   write('  bool __v'), write(NUM), 
   (
     (sub_atom(FM, 'i');sub_atom(FM,'t'))->
       (
        =(FI, '')->
         ( write(' = A.'), write(FirstA), write(' == B.'), write(FirstA), write(';'), nl );
         ( get_num_items(FI, SZ), write(' = is_equal(('), write(FT), write('*)A.'), write(FirstA), write(', ('), write(FT), write('*)B.'), write(FirstA), write(', '), write(SZ), write(');'), nl )
       );
       ( write(' = true;'), nl )
   ),
   !,
   NUM1 is NUM+1,
   generate_cond_vars(OthersA, OT, OM, OI, NUM1).
@generate_condition([''], _, _, _, _):- write('false').
@generate_condition([A], [F], [T], [FI], _):-
   (
     (sub_atom(F, 'i');sub_atom(F, 't'))->
       (
         =(FI, '')->
           ( write('A.'), write(A), write(' < B.'), write(A) );
           ( get_num_items(FI, SZ), write('is_less(('), write(T), write('*)A.'), write(A), write(', ('), write(T), write('*)B.'), write(A), write(', '), write(SZ), write(')') )
       );
       write('false')
   ),
   !.
@generate_condition([FirstA|OthersA], [FM|OM], [T|OT], [FI|OI], NUM):-
   write('('),
     generate_condition([FirstA], [FM], [T], [FI], NUM), !, write(' || (__v'), write(NUM), write(' && ('),
     NUM1 is NUM+1, generate_condition(OthersA, OM, OT, OI, NUM1), !, write('))'),
   write(')'),
   !.
@generate_diff([F], [FM], [FT], [FI]):-
   (
     sub_atom(FM, 'o')->
       (
         =(FI, '')->
           ( write('fabs(A.'), write(F), write(' - B.'), write(F), write(')') );
           ( get_num_items(FI, SZ), write('diff(('), write(FT), write('*)A.'), write(F), write(', ('), write(FT), write('*)B.'), write(F), write(', '), write(SZ), write(')') )
       );
       write('0.0')
   ),
   !.
@generate_diff([F|OO], [FM|OM], [FT|OT], [FI|OI]):-
   (
     sub_atom(FM, 'o')->
       (
         =(FI, '')->
           ( write('fabs(A.'), write(F), write(' - B.'), write(F), write(') + ') );
           ( get_num_items(FI, SZ), write('diff(('), write(FT), write('*)A.'), write(F), write(', ('), write(FT), write('*)B.'), write(F), write(', '), write(SZ), write(') + ') )
       );
       true
   ),
   !,
   generate_diff(OO, OM, OT, OI).
@back_assigns(_,[],[],[],[],[]):-!.
@back_assigns(_,[''],_,_,_,_):-!.
@back_assigns(Prefix,[FirstA|OthersA],[F|OO],[FT|OT],[FM|OM],[FI|OI]):-
   (
     sub_atom(FM, 'o')->
       (
         =(FI, '')->
          ( write('memmove(&'), write(FirstA), write(', &('), write(Prefix), write(F), write('), sizeof('), write(FirstA), write(')); ') );
          ( get_num_items(FI, SZ), write('memmove('), write(FirstA), write(', '), write(Prefix), write(F), write(', '), write(SZ), write('*sizeof('), write(FT), write(')); ') )
       );
       true
   ),
   !,
   back_assigns(Prefix,OthersA, OO, OT, OM, OI).
@forw_assigns(_,[],[],[],[],[]):-!.
@forw_assigns(_,[''],_,_,_,_):-!.
@forw_assigns(Postfix,[FirstA|OthersA],[F|OO],[FT|OT],[FM|OM],[FI|OI]):-
   atom_concat('item', Postfix, Item),
   (
     sub_atom(FM, 'o')->
       (
         =(FI, '')->
           ( write('memmove(&'), write(Item), write('.'), write(F), write(', &'), write(FirstA), write(', sizeof('), write(FirstA), write(')); ') );
           ( get_num_items(FI, SZ), write('memmove('), write(Item), write('.'), write(F), write(', '), write(FirstA), write(', '), write(SZ), write('*sizeof('), write(FT), write(')); ') )
       );
       true
   ),
   !,
   forw_assigns(Postfix, OthersA, OO, OT, OM, OI).
@determ_rule(_,[], _, _, _, '0', 'int'):-!.
@determ_rule(_,[''], _, _, _, '0', 'int'):-!.
@determ_rule(Kind, [FM|_], [F|_], [FTP|_], [FR|_], RULE, RULETYPE):-
   sub_atom(FM, Kind),
   !,
   make_arg(F, FM, RULE),
   atom_concat(FTP, FR, RULETYPE),
   !.   
@determ_rule(Kind, [_|OM], [_|OT], [_|OTP], [_|OR], RULE, RULETYPE):-
   determ_rule(Kind, OM, OT, OTP, OR, RULE, RULETYPE),
   !.
@determ_kind(_, [], _, ''):-!.
@determ_kind(_, [''], _, ''):-!.
@determ_kind(Kind, [FM|_], [F|_], F):-
   sub_atom(FM, Kind),
   !.
@determ_kind(Kind, [_|OM], [_|OO], Var):-
   determ_kind(Kind, OM, OO, Var),
   !.
@fill_items([], [], [], []):-!.
@fill_items([''], _, _, []):-!.
@fill_items([FM|OM], [FT|OT], [F|A], [FI|OI]):-
   ( sub_atom(FM, 'i'); sub_atom(FM, 'g'); sub_atom(FM, 't') ),
   !,
   (
     =(FI, '')->
       ( write('  memmove(&item.'), write(F), write(','), write('&'), write(F), write(', sizeof(item.'), write(F), write('));'), nl );
       ( get_num_items(FI, SZ), write('  memmove(item.'), write(F), write(','), write(F), write(', '), write(SZ), write('*sizeof('), write(FT), write('));'), nl )
   ),
   fill_items(OM, OT, A, OI).
@fill_items([_|OM], [_|OT], [_|A], [_|OI]):-
   fill_items(OM, OT, A, OI).
@fill_as_feed_forward([], _, _):-!.
@fill_as_feed_forward([NN, FUN| PARAMS], V1, V2):-
   write('     '), write(V1), write('.push_back('), write(NN), write(');'), nl,
   write('     '), write(V2), write('.push_back('''), write(FUN), write(''');'), nl,
   fill_as_feed_forward(PARAMS, V1, V2).
@fill_point([], _, _, _):-!.
@fill_point([''], _, _, _):-!.
@fill_point([F|OO],[FT|OT],[FI|OI],[FM|OM]):-
   sub_atom(FM, 'o'),
   !,
   (
    =(FI, '')->
     ( write('         Y->push_back(h.'), write(F), write(');'), nl);
     ( get_num_items(FI, SZ), handle_ref(FT, FM, FTT), write('         fill_into(Y, ('), write(FTT), write('*) h.'), write(F), write(', '), write(SZ), write(');'), nl)
   ),
   !,
   fill_point(OO, OT, OI, OM).
@fill_point([F|OO],[FT|OT],[FI|OI],[FM|OM]):-
   (sub_atom(FM, 'g')->(\+ =(MODE, 'lin_extrapolator')); true),
   !,
   (
    =(FI, '')->
     ( write('         X->push_back(h.'), write(F), write(');'), nl);
     ( get_num_items(FI, SZ), handle_ref(FT, FM, FTT), write('         fill_into(X, ('), write(FTT), write('*) h.'), write(F), write(', '), write(SZ), write(');'), nl)
   ),
   !,
   fill_point(OO, OT, OI, OM).
@fill_point([_|OO],[_|OT],[_|OI],[_|OM]):-
   fill_point(OO, OT, OI, OM).
@fill_x([], _, _, _):-!.
@fill_x([''], _, _, _):-!.
@fill_x([F|OO],[FT|OT],[FI|OI],[FM|OM]):-
   ( sub_atom(FM, 'i'); (\+ =(MODE, 'lin_extrapolator'), sub_atom(FM, 'g')); sub_atom(FM, 't') ),
   !,
   (
    =(FI, '')->
     ( write('         X.push_back('), write(F), write(');'), nl);
     ( get_num_items(FI, SZ), handle_ref(FT, FM, FTT), write('         fill_into(&X, ('), write(FTT), write('*) '), write(F), write(', '), write(SZ), write(');'), nl)
   ),
   !,
   fill_x(OO, OT, OI, OM).
@fill_x([_|OO],[_|OT],[_|OI],[_|OM]):-
   fill_x(OO, OT, OI, OM).
@fill_y([], _, _, _):-!.
@fill_y([''], _, _, _):-!.
@fill_y([F|OO],[FT|OT],[FI|OI],[FM|OM]):-
   sub_atom(FM, 'o'),
   !,
   (
    =(FI, '')->
     ( write('         '), write(F), write(' = Y[ptr++];'), nl);
     ( get_num_items(FI, SZ), handle_ref(FT, FM, FTT), write('         fill_out(&Y, ptr, ('), write(FTT), write('*) '), write(F), write(', '), write(SZ), write(');'), nl)
   ),
   !,
   fill_y(OO, OT, OI, OM).
@fill_y([_|OO],[_|OT],[_|OI],[_|OM]):-
   fill_y(OO, OT, OI, OM).
@prepare_params('feed_forward', [_, _, _| PARAMS]):-
   write('     vector<int> P1;'), nl,
   write('     vector<char> P2;'), nl,
   fill_as_feed_forward(PARAMS, 'P1', 'P2').
@prepare_params('mgua', _):-!.
@prepare_params('lin_extrapolator', _):-!.
@make_predictor_by_params('feed_forward', [TOL, NU, MAX_EPO| _]):-
   write('__FeedForwardNet('),
   write(TOL), write(', '),
   write(NU), write(', '),
   write(MAX_EPO), write(', X->size(), Y->size(), P1, P2);'), nl,
   !.
@make_predictor_by_params('mgua', [TOL| _]):-
   write('__MGUA('),
   write(TOL), write(', X->size(), Y->size());'), nl,
   !.
@make_predictor_by_params('lin_extrapolator', [TOL, P| _]):-
   write('__LIN_EXTRAPOLATOR('),
   write(TOL), write(', '),
   write(P), write(', Y->size());'), nl,
   !.
@get_eps('feed_forward', [TOL, _, _| _], TOL):-!.
@get_eps('mgua', [TOL| _], TOL):-!.
@get_eps('lin_extrapolator', [TOL, _| _], TOL):-!.
@goal:-
   atom_concat(ID, GID, UID),
   make_list(OTHERS, OO),
   make_list(OTHER_TYPES, OT),
   make_list(OTHER_MEMOS, OM),
   make_list(OTHER_REFS, OR),
   make_list(OTHER_IDXS, OI),
   make_list(OTHER_DESCS, ODS),
   determ_rule('g', [FIRST_MEMO|OM], [FIRST|OO], [FIRST_TYPE|OT], [FIRST_REF|OR], RULE, RULETYPE),
   determ_kind('t', [FIRST_MEMO|OM], [FIRST|OO], TIME),
   !,
   write(RETTYPE), write(' '), write('memo_'), write(ID), write('('), write(ARGS), write(');'), nl,
   write('typedef struct {'), nl,
   make_item(FIRST_TYPE, FIRST_REF, FIRST, FIRST_IDXS, FIRST_MEMO, First),
   make_items(OTHER_TYPES, OTHER_REFS, OTHERS, OTHER_IDXS, OTHER_MEMOS, Others),
   !,
   write_str_list([First|Others], ';'),
   trimr(RETTYPE, RetType),
   (
    =(RetType, 'void')->
      (write('signed char __result;'), nl);
      (write('  '), write(RetType), write(' __result;'), nl)
   ),
   !,
   (
    =(MODE, 'lin_extrapolator')->
     (write('mutable bool __used;'), nl);
     true
   ),
   !,
   write('} history_memo_'), write(UID), write(';'), nl,
   make_arg(FIRST, FIRST_MEMO, FirstA),
   make_args(OTHERS, OTHER_MEMOS, OthersA),
   write('bool operator < (const history_memo_'), write(UID), write(' & A, const history_memo_'), write(UID), write(' & B) {'), nl,
   generate_cond_vars([FIRST|OO], [FIRST_TYPE|OT], [FIRST_MEMO|OM], [FIRST_IDXS|OI], 1),
   write('  return '), generate_condition([FIRST|OO], [FIRST_MEMO|OM], [FIRST_TYPE|OT], [FIRST_IDXS|OI], 1), write(';'), nl,
   write('}'), nl,
   write('double operator - (const history_memo_'), write(UID), write(' & A, const history_memo_'), write(UID), write(' & B) {'), nl,
   write('  return '),
   (=(RetType, 'void')->true;write('abs(A.__result - B.__result) + ')), !,
   generate_diff([FIRST|OO], [FIRST_MEMO|OM], [FIRST_TYPE|OT], [FIRST_IDXS|OI]), write(';'), nl,
   write('}'), nl,
   write('map< '), write(RULETYPE), write(', set<history_memo_'), write(UID), write('> * > table_memo_'), write(UID), write(';'), nl,
   (
    =(MODE, '')->
      true;
      (
         write('map< '), write(RULETYPE), write(', __Predictor *> predictor_memo_'), write(UID), write(';'), nl,
         write(RETTYPE), write(' predict_'), write(ID), write('('), write(ARGS), write(', bool retrain = false, bool push = false) {'), nl,
         (=(MODE, 'lin_extrapolator')->(write('bool nulled = predictor_memo_'),write(UID),write('['),write(RULE),write('] == NULL;'),nl);true), !,
         (=(MODE, 'lin_extrapolator')->true;(write('  if (retrain || predictor_memo_'), write(UID), write('['), write(RULE), write('] == NULL) '))), !,
         write('{'), nl,
         (
          =(MODE, 'lin_extrapolator')->
            true;
            (
             write('     if (retrain && predictor_memo_'), write(UID),
             write('['), write(RULE), write('] != NULL) predictor_memo_'), write(UID), write('['), write(RULE), write(']->clear();'), nl
            )
         ),
         !,
         write('     map< '), write(RULETYPE), write(', set<history_memo_'), write(UID), write('> * >::iterator itt = table_memo_'), write(UID), write('.find('), write(RULE), write(');'), nl,
         write('     if (itt == table_memo_'), write(UID), write('.end()) {'), nl,
         write('        throw runtime_error("No training data");'), nl,
         write('     }'), nl,
         prepare_params(MODE, [FIRST_DESC|ODS]),
         write('     for (const history_memo_'), write(UID), write(' & h : *itt->second) '),
         (
          =(MODE, 'lin_extrapolator')->
            write('if (!h.__used) { h.__used = true;');
            write(' {')
         ),
         !,
         nl,
         write('         vector<double> * X = new vector<double>;'), nl,
         write('         vector<double> * Y = new vector<double>;'), nl,
         (
          =(RetType, 'void')->
            fill_point([FIRST|OO],[FIRST_TYPE|OT],[FIRST_IDXS|OI],[FIRST_MEMO|OM]);
            fill_point(['__result', FIRST|OO],[RetType, FIRST_TYPE|OT],['', FIRST_IDXS|OI],['o', FIRST_MEMO|OM])
         ),
         !,
         write('         if (predictor_memo_'), write(UID), write('['), write(RULE), write('] == NULL) '),
         write('predictor_memo_'), write(UID), write('['), write(RULE), write('] = new '),
         make_predictor_by_params(MODE, [FIRST_DESC|ODS]),
         write('         predictor_memo_'), write(UID), write('['), write(RULE), write(']->addPointX(X);'), nl,
         write('         predictor_memo_'), write(UID), write('['), write(RULE), write(']->addPointY(Y);'), nl,
         write('     }'), nl,
         write('     '),
         (=(MODE, 'lin_extrapolator')->write('if(retrain || nulled) '); true), !, 
         write('predictor_memo_'), write(UID), write('['), write(RULE), write(']->train();'), nl,
         write('  }'), nl,
         write('  vector<double> X, Y;'), nl,
         fill_x([FirstA|OthersA],[FIRST_TYPE|OT],[FIRST_IDXS|OI],[FIRST_MEMO|OM]),
         !,
         write('  predictor_memo_'), write(UID), write('['), write(RULE), write(']->calculate_sample(X, Y);'), nl,
         write('  int ptr = 0;'), nl,
         (
          =(RetType, 'void')->
            true;
            (
              write(RetType), write(' __result = Y[ptr++];'), nl
            )
         ),
         !,
         fill_y([FirstA|OthersA],[FIRST_TYPE|OT],[FIRST_IDXS|OI],[FIRST_MEMO|OM]),
         (
           =(MODE, 'lin_extrapolator')->
            (
              write(' if (push) {'), nl,
              write('    history_memo_'), write(UID), write(' item = { 0 };'), nl,
              fill_items([FIRST_MEMO|OM], [FIRST_TYPE|OT], [FirstA|OthersA], [FIRST_IDXS|OI]),
              write('    map< '), write(RULETYPE), write(', set<history_memo_'), write(UID), write('> * >::iterator itt = table_memo_'), write(UID), write('.find('), write(RULE), write(');'), nl,
              write('    if (itt == table_memo_'), write(UID), write('.end()) {'), nl,
              write('       table_memo_'), write(UID), write('['), write(RULE), write('] = new set<history_memo_'), write(UID), write('>;'), nl,
              write('       itt = table_memo_'), write(UID), write('.find('), write(RULE), write(');'), nl,
              write('    }'), nl,
              (=(RetType, 'void')->true;write('    item.__result = __result;')), !, nl,
              write('    '), forw_assigns('', [FirstA|OthersA], [FIRST|OO], [FIRST_TYPE|OT], [FIRST_MEMO|OM], [FIRST_IDXS|OI]), nl,
              write('    itt->second->insert(item);'), nl,
              write(' }'), nl
            );
            true
         ),
         !,
         (
          =(RetType, 'void')->
            true;
            (
              write('return __result;'), nl
            )
         ),
         !,
         write('}'), nl
      )
   ),
   write(RETTYPE), write(' '), write(ID), write('('), write(ARGS), write(') {'), nl,
   (
     =(CONTROLLED, '')->
       true;
       (
         write('  static map<'), write(RULETYPE), write(', int> __mode;'), nl,
         write('  static map<'), write(RULETYPE), write(', double> __k2;'), nl,
         write('  static map<'), write(RULETYPE), write(', int> __counter;'), nl,
         write('  if (__mode.find('), write(RULE), write(') == __mode.end()) {'), nl,
         (
          =(CONTROLLED, 'conditions')->
            ( write('     __mode['), write(RULE), write('] = -1;'), nl );
            ( write('     __mode['), write(RULE), write('] = 0; __k2['), write(RULE), write('] = '), write(C2),
              write('; __counter['), write(RULE), write('] = '), write(C1), write(';'), nl )
         ),
         !,
         write('  }'), nl,
         write('if (__mode['), write(RULE), write('] == 0) {'), nl,
         write('   if (__counter['), write(RULE), write('] == 0) {'), nl,
         write('      __mode['), write(RULE), write('] = 1;'), nl,
         write('      __counter['), write(RULE), write('] = '), write(C2), write(';'), nl,
         write('   } else {'), nl,
         write('      __counter['), write(RULE), write(']--;'), nl, 
         write('   }'), nl,
         write('}'), nl,
         write('if ('),
         (
           =(CONTROLLED, 'conditions')->
            ( write(C2), write(') {'), nl,
              write(' bool retrain = table_memo_'), write(UID), write('['), write(RULE), write(']->size() >= __max_history_size;'), nl,
              ( =(RetType,'void')->true;( write(RetType), write(' __result = ') ) ),
              write('      predict_'), write(ID), write('('), write_delim_list([FIRST|OO], ','), write(', retrain, true);'), nl,
              write('      if (retrain) table_memo_'), write(UID), write('['), write(RULE), write(']->clear();'), nl,
              write('      return'),
              ( =(RetType,'void')->true;write(' __result') ), write(';'),
              nl
            );
            ( write('__mode['), write(RULE), write('] == 1) {'), nl,
              write('   if (__counter['), write(RULE), write('] == 0) {'), nl,
              write('      __mode['), write(RULE), write('] = 2;'), nl,
              write('   } else {'), nl,
              write('      __counter['), write(RULE), write(']--;'), nl,
              ( =(RetType,'void')->true;write('      return ') ),
              write('      predict_'), write(ID), write('('), write_delim_list([FIRST|OO], ','), write(', false, true);'), nl,
              ( =(RetType,'void')->write('      return;');true ),
              nl,
              write('   }'), nl
            )
         ),
         !,
         write('}'), nl,
         write('if (__mode['), write(RULE), write('] == 2) {'), nl,
         write('  history_memo_'), write(UID), write(' itemp = { 0 };'), nl,
         write('  history_memo_'), write(UID), write(' itemb = { 0 };'), nl,
         write('  '), forw_assigns('b', [FirstA|OthersA], [FIRST|OO], [FIRST_TYPE|OT], [FIRST_MEMO|OM], [FIRST_IDXS|OI]), nl,
         (=(RetType, 'void')->true;write('itemp.__result = ')), !,
         write('predict_'), write(ID), write('('), write_delim_list([FIRST|OO], ','), write(', __counter['), write(RULE), write('] != 0);'), nl,
         write('  '), forw_assigns('p', [FirstA|OthersA], [FIRST|OO], [FIRST_TYPE|OT], [FIRST_MEMO|OM], [FIRST_IDXS|OI]), nl,
         write('  '), back_assigns('itemb.',[FirstA|OthersA], [FIRST|OO], [FIRST_TYPE|OT], [FIRST_MEMO|OM], [FIRST_IDXS|OI]), nl,
         write('  history_memo_'), write(UID), write(' item = { 0 };'), nl,
         write('__mode['), write(RULE), write('] = 0;'), nl,
         write('__counter['), write(RULE), write(']++;'), nl,
         (=(RetType, 'void')->true;write('item.__result = ')), !,
         write(ID), write('('), write_delim_list([FIRST|OO], ','), write(');'), nl,
         write('__mode['), write(RULE), write('] = 2;'), nl,
         write('  '), forw_assigns('', [FirstA|OthersA], [FIRST|OO], [FIRST_TYPE|OT], [FIRST_MEMO|OM], [FIRST_IDXS|OI]), nl,
         write('         double err = itemp - item;'), nl,
         get_eps(MODE, [FIRST_DESC|ODS], Eps),
         write('         if (err <= '), write(Eps), write(') {'), nl,
         write('            __k2['), write(RULE), write('] = __k2['), write(RULE), write(']*(0.1 + 1.2/(__counter['), write(RULE), write(']+1));'), nl,
         write('            if (__k2['), write(RULE), write('] > 0 && __k2['), write(RULE), write('] < 1) __k2['), write(RULE), write('] = 1;'), nl,
         write('            __counter['), write(RULE), write('] = (int)(0.5+__k2['), write(RULE), write(']);'), nl,
         write('            __mode['), write(RULE), write('] = 1;'), nl,
         write('         } else __counter['), write(RULE), write(']++;'), nl,
         (=(RetType, 'void')->write('return;');write('return item.__result;')), !, nl,
         write('      }'), nl
       )
   ),
   !,
   write('  history_memo_'), write(UID), write(' item = { 0 };'), nl,
   fill_items([FIRST_MEMO|OM], [FIRST_TYPE|OT], [FirstA|OthersA], [FIRST_IDXS|OI]),
   write('  map< '), write(RULETYPE), write(', set<history_memo_'), write(UID), write('> * >::iterator itt = table_memo_'), write(UID), write('.find('), write(RULE), write(');'), nl,
   write('  if (itt == table_memo_'), write(UID), write('.end()) {'), nl,
   write('     table_memo_'), write(UID), write('['), write(RULE), write('] = new set<history_memo_'), write(UID), write('>;'), nl,
   write('     itt = table_memo_'), write(UID), write('.find('), write(RULE), write(');'), nl,
   write('  }'), nl,
   write('  set<history_memo_'), write(UID), write('>::iterator it = itt->second->find(item);'), nl,
   write('  if (it != itt->second->end()) {'), nl,
   write('     '), back_assigns('it->',[FirstA|OthersA], [FIRST|OO], [FIRST_TYPE|OT], [FIRST_MEMO|OM], [FIRST_IDXS|OI]), !, (=(RetType, 'void')->write('return;');(write(' return it->__result;'))), !, nl,
   write('  }'), nl,
   write('  '),
   (=(RetType, 'void')->true;write('item.__result = ')), !,
   write('memo_'), write(ID), write('('), write_delim_list([FIRST|OO], ','), write(');'), nl,
   write('  '), forw_assigns('', [FirstA|OthersA], [FIRST|OO], [FIRST_TYPE|OT], [FIRST_MEMO|OM], [FIRST_IDXS|OI]), nl,
   write('  it = itt->second->begin();'), nl,
   write('  if (itt->second->size() > 1.2*__max_history_size)'), nl,
   write('     while (itt->second->size() > __max_history_size) {'), nl,
   (
    =(MODE, 'lin_extrapolator')->
     (
        write('       it = itt->second->begin();'), nl,
        write('       set<history_memo_'), write(UID), write('>::iterator it_min = it++;'), nl,
        write('       while (it != itt->second->end()) {'), nl,
        write('         if (it->'), write(TIME), write(' < it_min->'), write(TIME), write(')'), nl,
        write('            it_min = it;'), nl,
        write('         it++;'), nl,
        write('       }'), nl,
        write('       if (it_min != itt->second->end()) itt->second->erase(it_min);'), nl
     );
     (
        write('       int k = 1 + rand() % 4;'), nl,
        write('       while (k--)'), nl,
        write('         if (it == itt->second->end())'), nl,
        write('            it = itt->second->begin();'), nl,
        write('         else it++;'), nl,
        write('       if (it != itt->second->end()) it = itt->second->erase(it);'), nl
     )
   ),
   !,
   write('     }'), nl,
   (
     =(CONTROLLED, 'conditions')->
       ( write('  if ('), write(C1), write(') ') );
       true
   ),
   !,
   write('  itt->second->insert(item);'), nl,
   write('  '),
   (=(RetType, 'void')->write('return;');write('return item.__result;')), !, nl,
   write('}'), nl,
   write(RETTYPE), write(' '), write('memo_'), write(ID), write('('), write(ARGS), write(') ').
};

#pragma syntax check

#endif
