// Метаслой. Когнитивная обработка рабочих трасс
// с построением рабочих ОСМ-графовых моделей
// данных, логики и времени исполнения.
// 01.10.2014. Авторские и имущественные права на программный код
// переданы А.Е.Акимову-Тимьянову и Козлову А.Н. (в благодарность) как одному из основных соавторов
// со всеми вытекающими из этого правами для развития его научно-
// исследовательской работы в НИИММ при МГУ. Текущая версия
// объявляется последней, распространяемой как freeware OpenSource GNU PL.
// Дальнейшие версии неидентифицируются и не подлежат распространению
// иначе как с согласия правопреемников В.В.Пекунова, оставляюего за собой
// право на модернизацию кода в лично научных и иных некоммерческих целях,
// и правообладателя.

// Библиотека функций MetaLayer-P. V0.21b2.

// V0.1. 01.01.2009. Base release (V.V.Pekunov)
// V0.2. 12.08.2014. Majour Bugs fixed. (V.V.Pekunov, E.B.Akimov-Timyanov)
// V0.21b2. 12.08.2014. Unconditional breaks are reverted. Thanks to V.Pekunov

#ifdef _WIN32
  #undef _UNICODE
  #undef UNICODE
  #undef _MBCS
#endif

#include <math.h>
#include <float.h>
#include <map>
#include <list>
#include <set>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <windows.h>
#include <assert.h>
#include <stdarg.h>
#include <time.h>

using namespace std;

char * defaultContext = "default";

double milliseconds() {
  static LARGE_INTEGER ticks_per_second = {0};
  LARGE_INTEGER counter;
  
  QueryPerformanceCounter(&counter);
  if (!ticks_per_second.QuadPart) {
     QueryPerformanceFrequency(&ticks_per_second);
  }
  return 1000.0*counter.QuadPart/ticks_per_second.QuadPart;
}

namespace pm {

const int noValue = 0;

const int chunkVals = 200000;

const int MaxSeriesInRule = 10000;

const double EPS = 1E-29;
const double GEOM_EPS = 1E-2;

const int psbMul = 1000000;

const int max_coins = 3;

typedef enum { mvInt, mvDouble } TModelValueType;
typedef enum { mrRange, mrArithm, mrGeom, mrPossibility } TModelRuleType;

class TModelVariable;
class TModelLink;
class TModelNode;

typedef struct {
  TModelValueType Type;
  union {
    int    Int;
    double Double;
  };
} TModelValue;

class TModelRule {
 public:
  int idxVar;
  int First;
  int Last;
  TModelRuleType Type;
  int Level;
  union {
    struct {
      double gA0, lngp, gB;
    };
    struct {
      int period, c;
    };
  };
 char * Export(ostream * out, char * NodeName, set<TModelVariable *> * ContextVars);
};

bool operator == (const TModelRule A, const TModelRule B) {
  if (A.Type!=B.Type || A.idxVar!=B.idxVar)
     return false;
  else if (A.First!=B.First || A.Last!=B.Last)
     return false;
  else
     switch (A.Type) {
       case mrPossibility:
       case mrRange:  return true;
       case mrArithm: return A.period==B.period && A.c==B.c;
       case mrGeom:   return fabs(A.gA0-B.gA0)<EPS &&
                             fabs(A.lngp-B.lngp)<EPS &&
                             fabs(A.gB-B.gB)<EPS;
       default:       assert(false);
     }
  return false;
}

bool operator != (const TModelRule A, const TModelRule B) {
  return !(A==B);
}

bool operator < (const TModelRule A, const TModelRule B) {
  if (A.First<B.First) return true;
  else if (A.First==B.First)
    if (A.Last<B.Last) return true;
    else if (A.Last==B.Last)
       if (A.idxVar<B.idxVar) return true;
       else if (A.idxVar==B.idxVar)
         if (A.Type<B.Type) return true;
         else if (A.Type==B.Type)
           switch (A.Type) {
             case mrArithm: return A.c<B.c || A.c==B.c && A.period<B.period;
             case mrGeom:
               if (A.gB<B.gB) return true;
               else if (A.gB==B.gB)
                 if (A.gA0<B.gA0) return true;
                 else if (A.gA0==B.gA0)
                   return A.lngp<B.lngp;
           }
  return false;
}

inline TModelValue operator - (const TModelValue A, const TModelValue B) {
  TModelValue C;
  if (A.Type==mvDouble || B.Type==mvDouble) {
     double D0 = A.Type==mvInt ? A.Int : A.Double;
     double D1 = B.Type==mvInt ? B.Int : B.Double;
     
     C.Type   = mvDouble;
     C.Double = D0-D1;
  } else {
     int I0 = A.Type==mvInt ? A.Int : A.Double;
     int I1 = B.Type==mvInt ? B.Int : B.Double;
     
     C.Type   = mvInt;
     C.Int = I0-I1;
  }
  return C;
}

inline double operator - (const TModelValue A, const double B) {
  if (A.Type==mvDouble) return A.Double-B;
  else if (A.Type==mvInt) return A.Int-B;
  else assert(false);
  return 0.0;
}

inline bool operator == (const TModelValue A, int B) {
  if (A.Type==mvInt) return A.Int==B;
  else if (A.Type==mvDouble) return fabs(A.Double-B)<EPS;
  else assert(false);
  return false;
}

inline int operator % (const TModelValue A, int B) {
  if (A.Type==mvInt) return A.Int%B;
  else if (A.Type==mvDouble) return A.Double-((int)(A.Double/B))*B;
  else assert(false);
  return 0;
}

inline bool operator <= (const TModelValue A, int B) {
  if (A.Type==mvInt) return A.Int<=B;
  else if (A.Type==mvDouble) return fabs(A.Double-B)<EPS || A.Double<=B;
  else assert(false);
  return false;
}

inline bool operator >= (const TModelValue A, int B) {
  if (A.Type==mvInt) return A.Int>=B;
  else if (A.Type==mvDouble) return fabs(A.Double-B)<EPS || A.Double>=B;
  else assert(false);
  return false;
}

inline double operator ~ (const TModelValue A) {
  if (A.Type==mvInt) return A.Int;
  else return A.Double;
}

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

double correlation(const vector<double> X, const vector<double> Y, double & SX, double & SY) {
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

long double * MNK_of_X1X2(const vector<double> X1, const vector<double> X2,
                     const vector<double> Y, double &err,
                     vector<double> & YY) {
 const int N = 6;
 int x1mask[N] = {0,1,0,1,2,0};
 int x2mask[N] = {0,0,1,1,0,2};
 int Z = X1.size();
 vector<vector<long double>> XP1(5,vector<long double>(Z,1.0));
 vector<vector<long double>> XP2(5,vector<long double>(Z,1.0));
 long double * A   = new long double[N*N];
 long double * LU  = new long double[N*N];
 long double * B   = new long double[N];
 long double * XX  = new long double[N];
 int *    iLU = new int[N];
 int i,j,k, ptr;
 long double Q;
// double maxerr;

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
 if (!(_GetLU(N, iLU, A, LU) && _SolveLU(N, iLU, LU, B, XX))) {
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
//   maxerr = 0.0;
   for (j=0; j<Z; j++) {
     long double R = 0.0;
     for (k=N-1; k>=0; k--)
       R += XP1[x1mask[k]][j]*XP2[x2mask[k]][j]*XX[k];
     YY[j] = R;
     double cur_err = (R-Y[j])*(R-Y[j]);
     err += cur_err;
//     if (err>maxerr) maxerr = err;
   }
//   err += 0.5*maxerr;
 }
 delete[] A;
 delete[] LU;
 delete[] B;
 delete[] iLU;
 
 return XX;
}

long double * MNK_of_X(int N, const vector<double> X, const vector<double> Y, double &err) {
 int Z = X.size();
 vector<long double> XP(Z,1.0);
 long double * A   = new long double[N*N];
 long double * LU  = new long double[N*N];
 long double * B   = new long double[N];
 long double * XX  = new long double[N];
 int *    iLU = new int[N];
// double maxerr;
 int i,j,k;

 for (i=0; i<2*N-1; i++) {
   long double QX = 0.0;
   long double QY = 0.0;
   for (j=0; j<Z; j++) {
     QX += XP[j];
     if (i<N) QY += XP[j]*Y[j];
     XP[j] *= X[j];
   }
   for (j = (i<N ? i : N-1), k = (i<N ? 0 : i-N+1) ; j>=0 && k<N; j--, k++)
     A[k*N+j] = QX;
   if (i<N) B[i] = QY;
 }    
 if (!(_GetLU(N, iLU, A, LU) && _SolveLU(N, iLU, LU, B, XX))) {
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
//   maxerr = 0.0;
   for (j=0; j<Z; j++) {
     long double R = 0.0;
     for (k=N-1; k>=0; k--)
       R = R*X[j]+XX[k];
     double cur_err = (R-Y[j])*(R-Y[j]);
     err += cur_err;
//     if (cur_err>maxerr) maxerr = cur_err;
   }
//   err += 0.5*maxerr;
 }
 delete[] A;
 delete[] LU;
 delete[] B;
 delete[] iLU;
 
 return XX;
}

const int nFc1 = 18;
const int nFc2 = 33;
int Fc1[nFc1] = {1,2,3,4,5,6,7,8,9,10,12,15,20,24,30,40,60,120};
int Fc2[nFc2] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,40,60,120};
double FC[34][19] = {
{161.4,199.5,215.7,224.6,230.2,234.0,236.8,238.9,240.5,241.9,243.9,245.9,248.0,249.1,250.1,251.1,252.2,253.3,254.3},
{18.51,19.00,19.16,19.25,19.3,19.33,19.35,19.37,19.38,19.4,19.41,19.43,19.45,19.45,19.46,19.47,19.48,19.49,19.5},
{10.13,9.55,9.28,9.12,9.01,8.94,8.89,8.85,8.81,8.79,8.74,8.70,8.66,8.64,8.62,8.59,8.57,8.55,8.53},
{7.71,6.94,6.59,6.39,6.26,6.16,6.09,6.04,6.00,5.96,5.91,5.86,5.80,5.77,5.75,5.72,5.69,5.66,5.63},
{6.61,5.79,5.41,5.19,5.05,4.95,4.88,4.82,4.77,4.74,4.68,4.62,4.56,4.53,4.50,4.46,4.43,4.40,4.36},
{5.99,5.14,4.76,4.53,4.39,4.28,4.21,4.15,4.10,4.06,4.00,3.94,3.87,3.84,3.81,3.77,3.74,3.70,3.67},
{5.59,4.74,4.35,4.12,3.97,3.87,3.79,3.73,3.68,3.64,3.57,3.51,3.44,3.41,3.38,3.34,3.30,3.27,3.23},
{5.32,4.46,4.07,3.84,3.69,3.58,3.50,3.44,3.39,3.35,3.28,3.22,3.15,3.12,3.08,3.04,3.01,2.97,2.93},
{5.12,4.26,3.86,3.63,3.48,3.37,3.29,3.23,3.18,3.14,3.07,3.01,2.94,2.90,2.86,2.83,2.79,2.75,2.71},
{4.96,4.10,3.71,3.48,3.33,3.22,3.14,3.07,3.02,2.98,2.91,2.85,2.77,2.74,2.70,2.66,2.62,2.58,2.54},
{4.84,3.98,3.59,3.36,3.20,3.09,3.01,2.95,2.90,2.85,2.79,2.72,2.65,2.61,2.57,2.53,2.49,2.45,2.40},
{4.75,3.89,3.49,3.26,3.11,3.00,2.91,2.85,2.80,2.75,2.69,2.62,2.54,2.51,2.47,2.43,2.38,2.34,2.30},
{4.67,3.81,3.41,3.18,3.03,2.92,2.83,2.77,2.71,2.67,2.60,2.53,2.46,2.42,2.38,2.34,2.30,2.25,2.21},
{4.60,3.74,3.34,3.11,2.96,2.85,2.76,2.70,2.65,2.60,2.53,2.46,2.39,2.35,2.31,2.27,2.22,2.18,2.13},
{4.54,3.68,3.29,3.06,2.90,2.79,2.71,2.64,2.59,2.54,2.48,2.40,2.33,2.29,2.25,2.20,2.16,2.11,2.07},
{4.49,3.63,3.24,3.01,2.85,2.74,2.66,2.59,2.54,2.49,2.42,2.35,2.28,2.24,2.19,2.15,2.11,2.06,2.01},
{4.45,3.59,3.20,2.96,2.81,2.70,2.61,2.55,2.49,2.45,2.38,2.31,2.23,2.19,2.15,2.10,2.06,2.01,1.96},
{4.41,3.55,3.16,2.93,2.77,2.66,2.58,2.51,2.46,2.41,2.34,2.27,2.19,2.15,2.11,2.06,2.02,1.97,1.92},
{4.38,3.52,3.13,2.90,2.74,2.63,2.54,2.48,2.42,2.38,2.31,2.23,2.16,2.11,2.07,2.03,1.98,1.93,1.88},
{4.35,3.49,3.10,2.87,2.71,2.60,2.51,2.45,2.39,2.35,2.28,2.20,2.12,2.08,2.04,1.99,1.95,1.90,1.84},
{4.32,3.47,3.07,2.84,2.68,2.57,2.49,2.42,2.37,2.32,2.25,2.18,2.10,2.05,2.01,1.96,1.92,1.87,1.81},
{4.30,3.44,3.05,2.82,2.66,2.55,2.46,2.40,2.34,2.30,2.23,2.15,2.07,2.03,1.98,1.94,1.89,1.84,1.78},
{4.28,3.42,3.03,2.80,2.64,2.53,2.44,2.37,2.32,2.27,2.20,2.13,2.05,2.01,1.96,1.91,1.86,1.81,1.76},
{4.26,3.40,3.01,2.78,2.62,2.51,2.42,2.36,2.30,2.25,2.18,2.11,2.03,1.98,1.94,1.89,1.84,1.79,1.73},
{4.24,3.39,2.99,2.76,2.60,2.49,2.40,2.34,2.28,2.24,2.16,2.09,2.01,1.96,1.92,1.87,1.82,1.77,1.71},
{4.23,3.37,2.98,2.74,2.59,2.47,2.39,2.32,2.27,2.22,2.15,2.07,1.99,1.95,1.90,1.85,1.80,1.75,1.69},
{4.21,3.35,2.96,2.73,2.57,2.46,2.37,2.31,2.25,2.20,2.13,2.06,1.97,1.93,1.88,1.84,1.79,1.73,1.67},
{4.20,3.34,2.95,2.71,2.56,2.45,2.36,2.29,2.24,2.19,2.12,2.04,1.96,1.91,1.87,1.82,1.77,1.71,1.65},
{4.18,3.33,2.93,2.70,2.55,2.43,2.35,2.28,2.22,2.18,2.10,2.03,1.94,1.90,1.85,1.81,1.75,1.70,1.64},
{4.17,3.32,2.92,2.69,2.53,2.42,2.33,2.27,2.21,2.16,2.09,2.01,1.93,1.89,1.84,1.79,1.74,1.68,1.62},
{4.08,3.23,2.84,2.61,2.45,2.34,2.25,2.18,2.12,2.08,2.00,1.92,1.84,1.79,1.74,1.69,1.64,1.58,1.51},
{4.00,3.15,2.76,2.53,2.37,2.25,2.17,2.10,2.04,1.99,1.92,1.84,1.75,1.70,1.65,1.59,1.53,1.47,1.39},
{3.92,3.07,2.68,2.45,2.29,2.17,2.09,2.02,1.96,1.91,1.83,1.75,1.66,1.10,1.55,1.50,1.43,1.35,1.25},
{3.84,3.00,2.60,2.37,2.21,2.10,2.01,1.94,1.88,1.83,1.75,1.67,1.57,1.52,1.46,1.39,1.32,1.22,1.00}
};

double Fisher(int v1, int v2) {
  int _v1, _v2;
  double t1,t2;
  double p0,p1;

  for (_v1 = 0; _v1<nFc1 && v1>=Fc1[_v1]; _v1++);
  if (_v1==nFc1)
     t1 = 1.0;
  else
     t1 = 1.0*(v1-Fc1[_v1-1])/(Fc1[_v1]-Fc1[_v1-1]);
  for (_v2 = 0; _v2<nFc2 && v2>=Fc2[_v2]; _v2++);
  if (_v2==nFc2)
     t2 = 1.0;
  else
     t2 = 1.0*(v2-Fc2[_v2-1])/(Fc2[_v2]-Fc2[_v2-1]);
  p0 = FC[_v2-1][_v1-1]+(FC[_v2][_v1-1]-FC[_v2-1][_v1-1])*t2;
  p1 = FC[_v2-1][_v1]+(FC[_v2][_v1]-FC[_v2-1][_v1])*t2;
  
  return p0+t1*(p1-p0);
}

map<string,TModelVariable *> Vars;
map<TModelVariable *,string> nmVars;
list<TModelNode *> Trace;
map<string,map<string,TModelVariable *> *> Contexts;
map<string,TModelVariable *> * CurContext = &Vars;
set<TModelVariable *> ToInductVars;
list<TModelVariable *> ToInductList;

TModelNode * ModelRoot = NULL;
char ModelRootName[100];
TModelNode * LastNode  = NULL;
char LastNodeName[100];

double Timer = 0;
double Delay = 0;
double ModelTime = 0;

int nVAR = 0;

class TModelFunction {
  private:
    string Declarations;
    string Definition;
    friend class TModelConst;
    friend class TModelPolinom;
    friend class TModelMGUA;
    friend class TModelLink;
  public:
    const char * getDeclarations() {
      return Declarations.c_str();
    }
    const char * getDefinition() {
      return Definition.c_str();
    }
    virtual void MarkUsedVariables() {};
    virtual double getValue() { return 0.0; };
    virtual double RetrieveArgument(string var);
    virtual ~TModelFunction() {};
};

class TModelConst: public TModelFunction {
  private:
    double Value;
  public:
    TModelConst(double Val) {
      char Buf[1000];
      Value = Val;
      sprintf(Buf,"%lf",Val);
      Definition = Buf;
    }
    virtual double getValue() { return Value; };
};

class TModelPolinom: public TModelFunction {
  private:
    int      n;
    long double * Koeffs;
    string   var;
    double   Xmin, Xmax;
    char     V0[200];
    char     V1[200];
  public:
    TModelPolinom(int N, long double * Kfs, char * VAR, double BestXmin, double BestXmax, char * _V0, char * _V1) {
      char V[1000],Buf[10000],Buf1[10000];
      strcpy(V0,_V0); strcpy(V1,_V1);
      n = N;
      Koeffs = new long double[N];
      memmove(Koeffs,Kfs,N*sizeof(long double));
      var = VAR;
      Xmin = BestXmin;
      Xmax = BestXmax;
      Declarations = "long double ";
      sprintf(V,"POLY%i",nVAR++);
      Declarations += V;
      Declarations += " = ";
      if (BestXmax-BestXmin<EPS)
         Declarations += VAR;
      else {
         sprintf(Buf,"(%s-(%.18le))/(%.18le-(%.18le))",VAR,BestXmin,BestXmax,BestXmin);
         Declarations += Buf;
      }
      Declarations += ";\n";
      if (N==1) {
         sprintf(Buf,"%.18Le",Kfs[0]);
         Definition = Buf;
      } else {
         sprintf(Buf,"%.18Le",Kfs[N-1]);
         for (int i=N-2; i>=0; i--) {
             sprintf(Buf1,"%.18Le+%s*(%s)",Kfs[i],V,Buf);
             strcpy(Buf,Buf1);
         }
         Definition = Buf;
      }
    };
    virtual void MarkUsedVariables();
    virtual double getValue() {
      long double result = Koeffs[n-1];
      long double Arg = RetrieveArgument(var);
      for (int i=n-2; i>=0; i--)
        result = Koeffs[i] + result*Arg;
      return result;
    };
    virtual ~TModelPolinom() {
      delete[] Koeffs;
    }
};

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
        char * NX1; double Min1, Max1;
        char * NX2; double Min2, Max2;
      };
    };
    MGUA_X1X2(long double * Kf, MGUA_X1X2 * _X1, MGUA_X1X2 * _X2):
       X1(_X1), X2(_X2) {
       FirstLayer = false; refcount = 0;
       memmove(MGUAkoeffs,Kf,sizeof(MGUAkoeffs));
       X1->refcount++;
       X2->refcount++;
    };
    MGUA_X1X2(long double * Kf, char * _X1, char * _X2, double min1, double max1, double min2, double max2):
       Min1(min1), Max1(max1), Min2(min2), Max2(max2) {
       FirstLayer = true; refcount = 0;
       memmove(MGUAkoeffs,Kf,sizeof(MGUAkoeffs));
       NX1 = new char[strlen(_X1)+1]; NX2 = new char[strlen(_X2)+1];
       strcpy(NX1,_X1);               strcpy(NX2,_X2);
    };
    void Build(string & Declarations, char * NM) {
       char R1[14000] = "", R2[14000] = "";
       char Buf[28000];
       if (!FirstLayer) {
          X1->Build(Declarations,R1);
          X2->Build(Declarations,R2);
       } else {
          if (Max1-Min1<EPS)
             strcpy(R1,NX1);
          else {
             sprintf(R1,"x1%p",this);
             sprintf(Buf, "long double %s = (%s-(%.18le))/(%.18le-(%.18le));\n",R1,NX1,Min1,Max1,Min1);
             Declarations += Buf;
          }
          if (Max2-Min2<EPS)
             strcpy(R2,NX2);
          else {
             sprintf(R2,"x2%p",this);
             sprintf(Buf, "long double %s = (%s-(%.18le))/(%.18le-(%.18le));\n",R2,NX2,Min2,Max2,Min2);
             Declarations += Buf;
          }
       }
       if (!*NM) {
          sprintf(NM,"MGUA%i",nVAR++);
          Declarations += "long double ";
       }
       Declarations += NM;
       Declarations += " = ";
       sprintf(Buf,"(%.18Le)+(%.18Le)*%s+(%.18Le)*%s+(%.18Le)*%s*%s+(%.18Le)*%s*%s+(%.18Le)*%s*%s;\n",
                   MGUAkoeffs[0], MGUAkoeffs[1],R1, MGUAkoeffs[2],R2,
                   MGUAkoeffs[3],R1,R2, MGUAkoeffs[4],R1,R1, MGUAkoeffs[5],R2,R2);
       Declarations += Buf;
    };
    virtual void MarkUsedVariables();
    void MarkUsedVarsInCombination(char * Name);
    virtual double getValue();
    ~MGUA_X1X2() {
      if (FirstLayer) {
         delete[] NX1;
         delete[] NX2;
      } else {
         if ((--(X1->refcount))==0) delete X1;
         if ((--(X2->refcount))==0) delete X2;
      }
    }
};

class TModelMGUA: public TModelFunction {
  private:
    MGUA_X1X2 * STRUCT;
  public:
    TModelMGUA(MGUA_X1X2 * out) {
      STRUCT = out;
      STRUCT->refcount++;
    };
    void Build(char * VAR) {
      char Buf[20000];
      strcpy(Buf,VAR);
      STRUCT->Build(Declarations,Buf);
      Definition = Buf;
    };
    virtual double getValue() { return STRUCT->getValue(); };
    virtual void MarkUsedVariables() {
      STRUCT->MarkUsedVariables();
    }
    virtual ~TModelMGUA() {
      if ((--(STRUCT->refcount))==0)
         delete STRUCT;
    }
};

class TModelVariable {
  private:
    bool used;
  public:
    friend class TModelLink;
    friend class TModelNode;
    friend class TModelPolinom;
    friend class TModelMGUA;
    friend class MGUA_X1X2;
    friend class TModelIntVariable;
    friend class TModelDoubleVariable;
    TModelVariable(): used(false) {};
    inline bool getUsed() { return used; };
    virtual TModelValue ExportValue() = 0;
    virtual void ImportValue(int Val) = 0;
    virtual void ImportValue(double Val) = 0;
    virtual void FlushRules(char * MyName) = 0;
    virtual void MarkUsedVariables() = 0;
    virtual void ClearAfterExport() {};
    virtual void Restart() {};
    virtual ~TModelVariable() {};
};

class TModelLink {
  protected:
    list<map<TModelVariable *,TModelValue> *> Vals;
    set<TModelRule>  Rules;
    bool             InitNext;
    TModelNode     * Next;
    TModelFunction * FUN;
    map<TModelVariable *, TModelFunction *> InductVars;
    list<TModelVariable *> InductList;
  public:
    friend class TModelNode;
    TModelLink(bool init, TModelNode * To):
      InitNext(init), Next(To), FUN(NULL) {};
    TModelNode * GetOutNode() { return Next; };
    void Process();
    int  AnalyzeContext(double delay);
    void CollectVars(set<TModelVariable *> & ContextVars, set<TModelVariable *> & MyVars);
    vector<TModelValue *> * CollectVals(set<TModelVariable *> & ContextVars);
    bool FilterVals(TModelValue * cLine, TModelLink * _With);
    bool FilterByRule(TModelValue * cLine, const set<TModelRule>::iterator _iRules);
    void MarkUsedVariables(set<TModelVariable *> * ContextVars);
    char * GetActions(bool WithGoto, char * ToName);
    char * GetConditions(ostream * out, char * NodeName, set<TModelVariable *> * ContextVars);
    bool Go(set<TModelVariable *> * ContextVars, TModelValue * Line, double rnd, double & time);
    void Perform(set<TModelVariable *> * ContextVars, TModelValue * Line, double & time);
    virtual ~TModelLink() {
      list<map<TModelVariable *,TModelValue> *>::iterator iVals;
      if (FUN) {
         delete FUN;
         FUN = NULL;
      }
      for (iVals = Vals.begin(); iVals!=Vals.end(); iVals++)
        delete *iVals;
      Vals.clear();
      Rules.clear();
    }
};

class TModelIntVariable: public TModelVariable {
  protected:
    int Value;
  public:
    TModelIntVariable(int Val): Value(Val) { used = true; };
    virtual TModelValue ExportValue() {
      TModelValue result;
      result.Type = mvInt;
      result.Int = Value;
      return result;
    };
    virtual void ImportValue(int Val) {
      Value = Val;
    };
    virtual void ImportValue(double Val) {
      Value = Val;
    };
    virtual void FlushRules(char * MyName) {};
    virtual void MarkUsedVariables() {};
};

class TModelDoubleVariable: public TModelVariable {
  protected:
    double Value;
  public:
    TModelDoubleVariable(double Val): Value(Val) { used = true; };
    virtual TModelValue ExportValue() {
      TModelValue result;
      result.Type   = mvDouble;
      result.Double = Value;
      return result;
    };
    virtual void ImportValue(int Val) {
      Value = Val;
    };
    virtual void ImportValue(double Val) {
      Value = Val;
    };
    virtual void FlushRules(char * MyName) {};
    virtual void MarkUsedVariables() {};
};

class TModelNode: public TModelIntVariable {
  protected:
    bool HasTiming;
    map<char *, TModelLink *> Outs;
    map<char *, TModelLink *>::iterator unconditional;
    set<TModelVariable *> ContextVars;
    bool exported;
  public:
    friend class TModelLink;
    TModelNode(int Val, bool timing = false):
      TModelIntVariable(Val), exported(false), HasTiming(timing) { used = false; };
    TModelLink * GetOutLink(char * name) {
      map<char *, TModelLink *>::iterator i_result = Outs.find(name);
      return i_result==Outs.end() ? NULL : i_result->second;
    }
    void AddOutLink(char * OutName, TModelLink * Lnk);
    void FlushRules(char * MyName);
    void Export(ostream * out, char * MyName);
    TModelNode * Go (double & time);
    virtual void MarkUsedVariables();
    virtual void ClearAfterExport() {
      exported = false;
    };
    virtual void Restart() {
      Value = noValue;
    };
    bool IsRandomized();
    virtual ~TModelNode() {
      map<char *, TModelLink *>::iterator iOuts;
      for (iOuts = Outs.begin(); iOuts!=Outs.end(); iOuts++)
        delete (TModelLink *) iOuts->second;
      Outs.clear();
    }
};

void GetVarName(int idxVar, set<TModelVariable *> * ContextVars, char * varRule,
                int & Var0, int & Var1, char * NM1 = NULL, char * NM2 = NULL) {
  set<TModelVariable *>::iterator iVars;
  int K = ContextVars->size();
  int i;

  if (idxVar<0) {
     Var0 = -1;
     Var1 = -1;
     strcpy(varRule,"");
  } else {
     Var0 = idxVar;
     Var1 = -1;
     if (Var0>=K) {
        Var0 -= K;
        Var1 = 0;
        while (Var0>=K-Var1-1) Var0-=K-(++Var1);
        Var0+=Var1+1;
     }
     if (varRule) {
        char Nm0[100] = "";
        char Nm1[100] = "";
        int  i;
        for (iVars = ContextVars->begin(), i=0; Var0>=0 || Var1>=0; iVars++, i++) {
         if (i==Var0) { strcpy(Nm0,nmVars[*iVars].c_str()); Var0 = -1; }
         if (i==Var1) { strcpy(Nm1,nmVars[*iVars].c_str()); Var1 = -1; }
        }
        if (Nm1[0]) {
           strcpy(varRule,"(_");
           strcat(varRule,Nm1);
           strcat(varRule,"-_");
           strcat(varRule,Nm0);
           strcat(varRule,")");
           if (NM1) strcpy(NM1,Nm1);
           if (NM2) strcpy(NM2,Nm0);
        } else {
           strcpy(varRule,"_");
           strcat(varRule,Nm0);
           if (NM1) strcpy(NM1,Nm0);
           if (NM2) strcpy(NM2,"");
        }
     }
  }
}

void ExtractVars(char * Name, char * V0, char * V1) {
  char * posMinus = strchr(Name,'-');
  char First = *Name;
  if (First=='(') {
     Name++;
     Name[strlen(Name)-1] = 0x0;
  }
  if (!posMinus) {
     strcpy(V0,Name+1);
     strcpy(V1,"");
  } else {
     *posMinus = 0x0;
     strcpy(V0,Name+1);
     strcpy(V1,posMinus+2);
     *posMinus = '-';
  }
  if (First=='(')
     Name[strlen(Name)] = ')';
}

double TModelFunction::RetrieveArgument(string var) {
  char Arg[100], V0[100], V1[100];
  strcpy(Arg,var.c_str());
  ExtractVars(Arg,V0,V1);
  if (*V1) return ~(Vars[V0]->ExportValue()-Vars[V1]->ExportValue());
  else return ~(Vars[V0]->ExportValue());
};

void TModelPolinom::MarkUsedVariables() {
  if (V0[0])
     Vars[V0]->used = true;
  if (V1[0])
     Vars[V1]->used = true;
};

double MGUA_X1X2::getValue() {
  double _X1, _X2;
  if (FirstLayer) {
     char NM0[100], NM1[100];
     ExtractVars(NX1,NM0,NM1);
     _X1 = ~(Vars[NM0]->ExportValue());
     if (*NM1) _X1 -= ~(Vars[NM1]->ExportValue());
     ExtractVars(NX2,NM0,NM1);
     _X2 = ~(Vars[NM0]->ExportValue());
     if (*NM1) _X2 -= ~(Vars[NM1]->ExportValue());
  } else {
     _X1 = X1->getValue();
     _X2 = X2->getValue();
  }
  return MGUAkoeffs[0]+MGUAkoeffs[1]*_X1+MGUAkoeffs[2]*_X2+
         MGUAkoeffs[3]*_X1*_X2+MGUAkoeffs[4]*_X1*_X1+MGUAkoeffs[5]*_X2*_X2;
};

void MGUA_X1X2::MarkUsedVarsInCombination(char * Name) {
  char V0[100], V1[100];
  ExtractVars(Name,V0,V1);
  Vars[V0]->used = true;
  if (*V1) Vars[V1]->used = true;
}

void MGUA_X1X2::MarkUsedVariables() {
  if (!FirstLayer) {
     X1->MarkUsedVariables();
     X2->MarkUsedVariables();
  } else {
     if (NX1[0]) MarkUsedVarsInCombination(NX1);
     if (NX2[0]) MarkUsedVarsInCombination(NX2);
  }
};
    
char * TModelRule::Export(ostream * out, char * NodeName, set<TModelVariable *> * ContextVars) {
  static char _OUT[32000];
  char Buf[20000];
  char Var[1000];
  int Var0, Var1;
  if (Type==mrPossibility) {
    sprintf(_OUT,"(rnd%s>=%.18le && rnd%s<%.18le)",NodeName,1.0*First/psbMul,NodeName,1.0*Last/psbMul);
  } else {
    GetVarName(idxVar,ContextVars,Var,Var0,Var1);
    if (First==Last)
       sprintf(_OUT,"((int)%s==%i)",Var,First);
    else
       sprintf(_OUT,"((int)%s>=%i && (int)%s<=%i)",Var,First,Var,Last);
    switch(Type) {
      case mrArithm:
        sprintf(Buf," && (((int)%s) %% %i == %i)",Var,period,c);
        strcat(_OUT,Buf);
        break;
      case mrGeom:
        sprintf(Buf," && fabs(dummy = log((%s - %lf) / %lf) / %lf)>=0.0 && fabs(dummy - (int)(dummy + 0.5))<%lf",Var,gB,gA0,lngp,GEOM_EPS);
        strcat(_OUT,Buf);
        break;
    }
  }
  return _OUT;
}

void TModelNode::AddOutLink(char * OutName, TModelLink * Lnk) {
  TModelNode * OutNode = Lnk->GetOutNode();
  Outs[OutName] = Lnk;
}

typedef struct {
  int first, last;
  int freq;
} aPeriod;

typedef struct {
  vector<double> YY;
  MGUA_X1X2 * ref;
} variantMGUA;

TModelFunction * FindRelations(char * NameOfVar, set<int> Declined,
                   set<TModelVariable *> * ContextVars, vector<TModelValue *> * LinkVals,
                   const vector<double> Y, double Min, double Max, int Z, int N,
                   double tol) {
  vector<double> X(N),P(N);
  vector<double> mins(Z), maxs(Z);
  map<double,int> correlations;
  double MinMax, SY;
  MinMax = Max-Min;
  for (int i=0; i<Z; i++)
   if (Declined.find(i)==Declined.end()) {
    for (int j=0; j<N; j++)
        X[j] = ~(*LinkVals)[j][i];
    double SX;
    double corr = correlation(X,Y,SX,SY);
    if (fabs(SY)<EPS)
       correlations[0.0] = -1;
    else if (fabs(SX*SY)>EPS) {
       double CORR = fabs(corr/(SX*SY));
       map<double,int>::iterator itc = correlations.find(CORR);
       if (itc==correlations.end()) correlations[CORR] = i;
       else if (++itc==correlations.end()) correlations[CORR+0.000001] = i;
       else correlations[(CORR+itc->first)*0.5] = i;
    }
    double xMin = 1E300;
    double xMax = -1E300;
    for (int j=0; j<N; j++) {
      if (X[j]<xMin) xMin = X[j];
      if (X[j]>xMax) xMax = X[j];
    }
    mins[i] = xMin;
    maxs[i] = xMax;
  }
  if (correlations.size()>0) {
     map<double,int>::iterator itc0, itc = correlations.end();
     int BestV = (--itc)->second;
     double err;
     if (BestV<0)
        return new TModelConst(0.5*(Max+Min));
     else {
       int KK = min(3,correlations.size());
       double maxerr = 1E300;
       long double BestKoeffs[50];
       double BestXmin, BestXmax;
       int    BestP = -1;
       for (int k=0; k<KK; k++, itc--) {
           int Var = itc->second;
           for (int j=0; j<N; j++)
             X[j] = ~(*LinkVals)[j][Var];
           if (maxs[Var]-mins[Var]>EPS)
              for (int i=0; i<N; i++)
                X[i] = (X[i]-mins[Var])/(maxs[Var]-mins[Var]);
           for (int P=1; P<min(Y.size(),7); P++) {
             long double * Koeffs = MNK_of_X(P,X,Y,err);
             err /= (MinMax>EPS ? MinMax*MinMax : 1.0);
             if (err<maxerr && (SY<EPS || err/(Y.size()-P)/(SY*SY)<Fisher(Y.size()-P,Y.size()-1))) {
                memmove(BestKoeffs,Koeffs,P*sizeof(long double));
                maxerr = err;
                BestP  = P;
                BestXmin = mins[Var];
                BestXmax = maxs[Var];
                BestV  = Var;
             }
           }
       }
       if (maxerr<tol) {
          char var[1000];
          char S0[200],S1[200];
          int  V0,V1;
          GetVarName(BestV,ContextVars,var,V0,V1,S0,S1);
          return new TModelPolinom(BestP,BestKoeffs,var,BestXmin,BestXmax,S0,S1);
       }
       map<double,variantMGUA> MGUA;
       TModelMGUA * MG = NULL;
       int NPolies = min(20,max(1,(int)(0.8*correlations.size())));
       double LastCriterion = 1E300;
       int NK = 0;
       int i;
       if (Y.size()>=6) {
          for (itc = correlations.begin(), i = 0; itc!=correlations.end() && i<NPolies; itc++, i++) {
            int V1 = itc->second;
            vector<double> VV(N);
            variantMGUA var;
            for (int j=0; j<N; j++)
              if (maxs[V1]-mins[V1]>EPS)
                VV[j] = (~(*LinkVals)[j][V1]-mins[V1])/(maxs[V1]-mins[V1]);
              else
                VV[j] = ~(*LinkVals)[j][V1];
            var.YY = VV;
            var.ref = (MGUA_X1X2 *) V1;
            MGUA[100.0-itc->first] = var;
          }
          while (MGUA.size()>1) {
            map<double,variantMGUA>::iterator i0,i1;
            map<double,variantMGUA> _MGUA;
            variantMGUA var;
            char Buf[1000],Buf1[1000];
            int V0,V1;
            for (i0 = MGUA.begin(); i0!=MGUA.end(); i0++) {
              X = i0->second.YY;
              for (i1 = i0, i1++; i1!=MGUA.end(); i1++) {
                P = i1->second.YY;
                if ((int)i0->second.ref < Z) {
                   GetVarName((int) i0->second.ref,ContextVars,Buf,V0,V1);
                   GetVarName((int) i1->second.ref,ContextVars,Buf1,V0,V1);
                   var.ref = new MGUA_X1X2(MNK_of_X1X2(X,P,Y,err,var.YY),Buf,Buf1,
                                           mins[(int)i0->second.ref],maxs[(int)i0->second.ref],
                                           mins[(int)i1->second.ref],maxs[(int)i1->second.ref]);
                }
                else
                   var.ref = new MGUA_X1X2(MNK_of_X1X2(X,P,Y,err,var.YY),i0->second.ref,i1->second.ref);
                if (err<1E300) _MGUA[err/(MinMax>EPS ? MinMax*MinMax : 1.0)] = var;
                else delete var.ref;
              }
            }
            MGUA.clear();
            i0 = _MGUA.begin();
            if (i0!=_MGUA.end()) {
               err = i0->first;
               if (LastCriterion-err<=1E-2 || err<tol) {
                  MGUA[err] = i0->second;
                  if (!MG) MG = new TModelMGUA(i0->second.ref);
                  i0++;
                  while (i0!=_MGUA.end())
                    delete (i0++)->second.ref;
                  NK += 6;
                  break;
               } else {
                 i1 = _MGUA.begin();
                 for (int k=0; k<NPolies && i1!=_MGUA.end(); k++) i1++;
                 MGUA.insert(_MGUA.begin(),i1);
                 while (i1!=_MGUA.end())
                   delete (i1++)->second.ref;
               }
               NK += MGUA.size()*6;
               NPolies = max(1,(int)sqrt((double)MGUA.size()));
               LastCriterion = err;
            } else {
               if (!MG) {
                  delete MG;
                  MG = NULL;
               }
               NK = 0;
            }
          }
       }
       if (MG && NK && err<maxerr && (SY<EPS || err/(Y.size()-NK)/(SY*SY)<Fisher(Y.size()-NK,Y.size()-1))) {
          MG->Build(NameOfVar);
          return MG;
       } else if (BestP>=0) {
          char var[1000], S0[200], S1[200];
          int  V0,V1;
          GetVarName(BestV,ContextVars,var,V0,V1,S0,S1);
          return new TModelPolinom(BestP,BestKoeffs,var,BestXmin,BestXmax,S0,S1);
       } else {
          double AvrTime = 0.0;
          for (int j=0; j<N; j++)
              AvrTime += Y[j];
          return new TModelConst(AvrTime/N);
       }
     }
  } else
     return NULL;
}

void TModelNode::FlushRules(char * MyName) {
  map<char *, TModelLink *>::iterator iOuts, iOuts1, iOuts2, _iOuts;
  map<TModelLink *, vector<TModelValue *> *> ContextValues;
  set<TModelVariable *> * LinkVars = new set<TModelVariable *>[Outs.size()];
  for (int i=0; i<Outs.size(); i++)
      LinkVars[i] = set<TModelVariable *>();
  map<TModelLink *, vector<map<int,int> *> *> ContextSets; // Now int. In the future -- float. Or filter by int???
  int NumLink;

  for (iOuts = Outs.begin(), NumLink = 0; iOuts!=Outs.end(); iOuts++, NumLink++)
      iOuts->second->CollectVars(ContextVars,LinkVars[NumLink]);
  int K = ContextVars.size();
  int Z = K+K*(K-1)/2;
  
  map<TModelLink *, vector<bool>> UsedVars;
  for (iOuts = Outs.begin(), NumLink = 0; iOuts!=Outs.end(); iOuts++, NumLink++) {
      map<TModelLink *, vector<bool>>::iterator iUsedVars;
      set<TModelVariable *>::iterator iContextVars;
      int i, j, k;
      UsedVars[iOuts->second] = vector<bool>(Z,false);
      iUsedVars = UsedVars.find(iOuts->second);
      for (iContextVars = ContextVars.begin(), i = 0; iContextVars!=ContextVars.end(); iContextVars++, i++)
          iUsedVars->second[i] = LinkVars[NumLink].find(*iContextVars)!=LinkVars[NumLink].end();
      for (j = 0; j<K; j++)
          for (k = j+1; k<K; k++)
              iUsedVars->second[i++] = iUsedVars->second[j] && iUsedVars->second[k];
  }
  // Count tables. If only one exist -- "without condition" or "else"
  // If all tables are empty -- stop
  // Loop.
  unconditional = Outs.end();
  if (Outs.size())
	  unconditional--;
  bool calcTimings = true;
  int curLevel = 0;
  int StopFlag = 1;
  int coins = 0;
  do {
     vector<set<TModelRule>> LocalRules(Outs.size());
	 for (iOuts = Outs.begin(); iOuts != Outs.end(); iOuts++) {
		 vector<map<int, int> *> * LinkSets = new vector<map<int, int> *>(Z);
		 vector<TModelValue *> * LinkVals = iOuts->second->CollectVals(ContextVars);
		 int N = LinkVals ? LinkVals->size() : 0;
		 ContextValues[iOuts->second] = LinkVals;
		 if (calcTimings && N) {
			 if (iOuts->second->Next->HasTiming) {
				 double Min = 1E300, Max = -1E300;
				 vector<double> Y(N), Y1(N);
				 int Zeroes = 0;
				 for (int j = 0; j<N; j++)
				 if (Y[j]>Max) Max = Y[j];
				 for (int j = 0; j < N; j++)
				 if (fabs(Y[j] = ~(*LinkVals)[j][Z])<0.1)
					 Zeroes++;
				 if (1.0*Zeroes / N>0.97 && Max < 80.0)
				 for (int j = 0; j<N; j++)
					 Y[j] = 0.0;
				 else if (1.0*Zeroes / N>0.9) {
					 for (int k = 1; k < 2; k++)
					 for (int j = 1; j < N - 1; j++)
						 Y1[j] = (Y[j - 1] + Y[j] + Y[j + 1]) / 3.0;
					 Y1[0] = Y[0]; Y1[N - 1] = Y[N - 1];
					 Y = Y1;
				 }
				 Max = -1E300;
				 for (int j = 0; j < N; j++) {
					 if (Y[j]<Min) Min = Y[j];
					 if (Y[j]>Max) Max = Y[j];
				 }
				 iOuts->second->FUN = FindRelations("", set<int>(), &ContextVars, LinkVals, Y, Min, Max, Z, N, 0.1*Y.size() / (Max - Min));
			 }
			 else
				 iOuts->second->FUN = NULL;
			 map<TModelVariable *, TModelFunction *>::iterator iInductVars;
			 for (iInductVars = iOuts->second->InductVars.begin(); iInductVars != iOuts->second->InductVars.end(); iInductVars++) {
				 double Min = 1E300, Max = -1E300;
				 vector<double> Y(N);
				 list<TModelVariable *>::iterator iInductList, _iInductList;
				 set<int> Declined;
				 int VAR;
				 // InductList = list of vars in order of register. Exclude vars from current to the end
				 // (and their derivatives).
				 for (iInductList = iOuts->second->InductList.begin(); *iInductList != iInductVars->first; iInductList++);
				 for (_iInductList = iOuts->second->InductList.end(); _iInductList != iInductList;) {
					 set<TModelVariable *>::iterator iContextVars;
					 _iInductList--;
					 for (iContextVars = ContextVars.begin(), VAR = 0; *iContextVars != *_iInductList; iContextVars++, VAR++);

					 int From = K + VAR - 1;
					 Declined.insert(VAR);
					 for (int j = 0; j < VAR; j++, From += K - j - 1)
						 Declined.insert(From);
					 From++;
					 for (int j = 0; j < K - VAR - 1; j++, From++)
						 Declined.insert(From);
				 }
				 for (int j = 0; j < N; j++) {
					 Y[j] = ~(*LinkVals)[j][VAR];
					 if (Y[j]<Min) Min = Y[j];
					 if (Y[j]>Max) Max = Y[j];
				 }
				 iInductVars->second = FindRelations((char *)nmVars[iInductVars->first].c_str(),
					 Declined, &ContextVars,
					 LinkVals, Y, Min, Max, Z, N, 0.1*Y.size() / (Max - Min));
			 }
		 }
	 }
	 for (iOuts = Outs.begin(), NumLink = 0; iOuts != Outs.end(); iOuts++, NumLink++) {
       vector<map<int,int> *> * LinkSets = new vector<map<int,int> *>(Z);
       vector<TModelValue *> * LinkVals = iOuts->second->CollectVals(ContextVars);
       int N = LinkVals ? LinkVals->size() : 0;
       ContextValues[iOuts->second] = LinkVals;
       for (int i=0; i<Z; i++)
         (*LinkSets)[i] = new map<int,int>();
       for (int i=0; i<Z; i++)
        if (UsedVars[iOuts->second][i])
         for (int j=0; j<N; j++) {
           TModelValue & V = (*LinkVals)[j][i];
           map<int,int>::iterator it;
           if ((it = (*LinkSets)[i]->find((int)~V))==(*LinkSets)[i]->end())
              (*(*LinkSets)[i])[(int)~V] = 1;
           else
              (it->second)++;
         }
       ContextSets[iOuts->second] = LinkSets;
     }
     calcTimings = false;
     for (iOuts = Outs.begin(), NumLink = 0; iOuts!=Outs.end(); iOuts++, NumLink++)
         LocalRules[NumLink] = set<TModelRule>();
     for (iOuts = Outs.begin(), NumLink = 0; iOuts!=Outs.end(); iOuts++, NumLink++)
       if (ContextValues[iOuts->second] && ContextValues[iOuts->second]->size()) {
         int    BestVar = -1;
         double BestDiscr = 1E300;
         map<int,int> RestValsSet;
         cout<<iOuts->first<<" ";
         for (int i=0; i<Z; i++)
          if (UsedVars[iOuts->second][i]) {
           map<int,int> * Set = (*ContextSets[iOuts->second])[i];
           map<int,int> Set1;
           map<int,int> SetR = *Set;
           for (iOuts1 = Outs.begin(); iOuts1!=Outs.end(); iOuts1++)
             if (iOuts!=iOuts1) {
                map<int,int> * Set2 = (*ContextSets[iOuts1->second])[i];
                map<int,int>::iterator iValSet, it;
                for (iValSet = Set2->begin(); iValSet!=Set2->end(); iValSet++) {
                  if ((it = Set1.find(iValSet->first))!=Set1.end())
                     (it->second)+=iValSet->second;
                  else
                     Set1[iValSet->first] = iValSet->second;
                  if ((it = SetR.find(iValSet->first))!=SetR.end())
                     SetR.erase(it);
                }
             }
           if (!Set->empty()) {
              map<int,int>::iterator iValSet, iValSet1;
              double LocalDiscr;
              int    NumEqualItems    = 0;
              int    CountEqualItems0 = 0;
              int    CountEqualItems1 = 0;
              int    CountItems0 = 0;
              int    CountItems1 = 0;
              for (iValSet = Set->begin(); iValSet!=Set->end(); iValSet++)
                  CountItems0 += iValSet->second;
              for (iValSet = Set1.begin(); iValSet!=Set1.end(); iValSet++)
                  CountItems1 += iValSet->second;
              for (iValSet = Set->begin(); iValSet!=Set->end(); iValSet++)
                if ((iValSet1 = Set1.find(iValSet->first))!=Set1.end()) {
                   CountEqualItems0 += iValSet->second;
                   CountEqualItems1 += iValSet1->second;
                   NumEqualItems++;
                }
              LocalDiscr = SetR.size() ? 1.0*(CountEqualItems0+CountEqualItems1)+0.1*NumEqualItems : 1E300;
              cout<<LocalDiscr<<" ";
              if (LocalDiscr<BestDiscr) {
                 BestDiscr   = LocalDiscr;
                 BestVar     = i;
                 RestValsSet = SetR;
                 _iOuts      = iOuts;
              }
           }
          }
         cout<<endl;
         if (BestVar>=0) {
             map<int,int>::iterator iSet = RestValsSet.end();
             int  First = RestValsSet.begin()->first;
             int  Last  = (--iSet)->first;
             bool handled;
             if (Last-First+1==RestValsSet.size()) { // Full range
                TModelRule Rule;
                Rule.Type   = mrRange;
                Rule.idxVar = BestVar;
                Rule.First  = First;
                Rule.Last   = Last;
                Rule.Level  = curLevel;
                LocalRules[NumLink].insert(Rule);
             } else { // induct series of range with arithm/geom progression or not...
                      // Serie: [progression &&] c1<=Val && Val<=c2
                map<int,int> Set1 = RestValsSet;
                int    series;
                for (series = 1; series<=MaxSeriesInRule && Set1.size()>=1; series++) {
                    int    Item, ItemLast;
                    TModelRule Rule;
                    iSet = Set1.begin();
                    Item = iSet->first;
					iSet++;
                    ItemLast = Set1.size() > 1 ? iSet->first : Item; // dd
					if (Set1.size() > 1) iSet++;
                    Rule.Type  = mrRange;
                    Rule.First = Item;
                    Rule.Last  = ItemLast;
                    if (Set1.size()>2 && // vp
                        Item>=0 && // May be negative sequence too?
                        ItemLast-Item!=0 &&
                        fabs(Rule.lngp = (iSet->first-ItemLast)/(ItemLast-Item))>EPS &&
						fabs(Rule.lngp - 1.0)>0.5 &&
						fabs(Rule.gA0 = (iSet->first-ItemLast)/(Rule.lngp*Rule.lngp-Rule.lngp))>GEOM_EPS &&
						fabs(Rule.gB = Item-Rule.gA0)>=0.0)
                    {
					  Rule.lngp = log(Rule.lngp);
					  Rule.Type = mrGeom;
                      handled = true;
                      do {
						iSet = Set1.begin();
						double C = log((iSet->first - Rule.gB) / Rule.gA0) / Rule.lngp;
						if (fabs(C - (int)(C + 0.5))>=GEOM_EPS)
                           handled = false;
						else {
							Rule.Last = iSet->first;
							Set1.erase(Set1.begin());
						}
                      } while (handled && Set1.size());
					  iSet = Set1.begin();
					} else if (Set1.size() == 1)
					  Set1.clear();
					else {
                      map<int,aPeriod> periods;
                      map<int,aPeriod>::iterator iperiods, maxperiod;
                      aPeriod a;             
                      int    curPeriod = ItemLast-Item;
                      
                      a.freq = 2;
                      a.first = Item;
                      a.last  = ItemLast;
//                      if (iSet==Set1.end()) curPeriod = 0;
//                      else
                      if (iSet!=Set1.end())
					   do {
                         Item = ItemLast;
                         ItemLast = (iSet++)->first;
                         if (ItemLast-Item==curPeriod)
                            a.freq++;
                         else {
                            a.last    = Item;
                            iperiods  = periods.find(curPeriod);
                            if (iperiods==periods.end())
                               periods[curPeriod] = a;
                            else {
                               iperiods->second.freq+=a.freq;
                               if ((iperiods->second.last-iperiods->second.first)<(a.last-a.first)) {
                                  iperiods->second.first = a.first;
                                  iperiods->second.last  = a.last;
                               }
                            }
                            if (iSet!=Set1.end()) {
                               a.freq  = 1;
                               a.first = Item      = ItemLast;
                               a.last  = ItemLast  = (iSet++)->first;
                               curPeriod = ItemLast-Item;
                            } else curPeriod = 0;
                         }
                       } while (iSet!=Set1.end());
                      if (curPeriod!=0) {
                         a.last    = ItemLast;
                         iperiods  = periods.find(curPeriod);
                         if (iperiods==periods.end())
                            periods[curPeriod] = a;
                         else {
                            iperiods->second.freq+=a.freq;
                            if ((iperiods->second.last-iperiods->second.first)<(a.last-a.first)) {
                               iperiods->second.first = a.first;
                               iperiods->second.last  = a.last;
                            }
                         }
                      }
                      for (iperiods = maxperiod = periods.begin(); iperiods!=periods.end(); iperiods++)
                          if (iperiods->second.freq>maxperiod->second.freq)
                             maxperiod = iperiods;
                      if (maxperiod!=periods.end()) {
                         Rule.First  = maxperiod->second.first;
                         Rule.Last   = maxperiod->second.last;
                         if (maxperiod->first>1) {
                            Rule.Type   = mrArithm;
                            Rule.period = maxperiod->first;
                            Rule.c = maxperiod->second.first % maxperiod->first;
                         } else {
                            Rule.Type   = mrRange;
                            Rule.period = 1;
                         }
                      }
                      int k = Rule.Type==mrArithm ? Rule.period : 1;
                      for (int j=Rule.First; j<=Rule.Last; j+=k)
                        if (Set1.find(j)!=Set1.end())
                          Set1.erase(Set1.find(j));
                    }
                    Rule.idxVar = BestVar;
                    Rule.Level  = curLevel;
                    LocalRules[NumLink].insert(Rule);
                }
             }
         } else {
            //int card   = 0;
            //double Low = 0.0;
            //int i;
            //for (iOuts1 = Outs.begin(); iOuts1!=Outs.end(); iOuts1++)
            //  if (ContextValues[iOuts1->second])
            //     card += ContextValues[iOuts1->second]->size();
            //for (iOuts1 = Outs.begin(), i = 0; iOuts1!=Outs.end(); iOuts1++, i++)
            //  if (ContextValues[iOuts1->second]) {
            //    TModelRule Rule;

            //    Rule.Type   = mrPossibility;
            //    Rule.idxVar = -1;
            //    Rule.First  = Low*psbMul;
            //    Rule.Last   = (Low += 1.0*ContextValues[iOuts1->second]->size()/card)*psbMul;
            //    Rule.Level  = curLevel;
            //    LocalRules[i].insert(Rule);
            //}
         }
     }
     for (iOuts = Outs.begin(), NumLink = 0; iOuts!=Outs.end(); iOuts++, NumLink++)
       if (!LocalRules[NumLink].empty()) {
          set<TModelRule>::iterator iRules;
          vector<TModelValue *> * curValues = ContextValues[iOuts->second];
          vector<TModelValue *>::iterator icVals;
          list<map<TModelVariable *,TModelValue> *>::iterator iVals;
          curLevel++;
          for (iRules = LocalRules[NumLink].begin(); iRules!=LocalRules[NumLink].end(); iRules++)
            iOuts->second->Rules.insert(*iRules);
          // Here my be we must count combinations on some links -- non-separatable
          // and count possibilities or use additional vars.
          if (curValues->size()) {
             icVals = curValues->begin();
             iVals  = iOuts->second->Vals.begin();
             while (icVals!=curValues->end()) {
               bool delFlag = false;
               for (iRules = LocalRules[NumLink].begin(); !delFlag && iRules!=LocalRules[NumLink].end(); iRules++)
                 if (iOuts->second->FilterByRule(*icVals,iRules))
                    delFlag = true;
               if (delFlag) {
                 icVals = curValues->erase(icVals);
                 iVals  = iOuts->second->Vals.erase(iVals);
               } else {
                 iVals++;
                 icVals++;
               }
             }
          }
       }
	 coins++;
	 if (coins == max_coins) {
		 int card = 0;
		 double Low = 0.0;
		 int ii;
		 for (iOuts1 = Outs.begin(); iOuts1 != Outs.end(); iOuts1++)
		 if (ContextValues[iOuts1->second]->size())
			 card += ContextValues[iOuts1->second]->size();
		 for (iOuts1 = Outs.begin(), ii = 0; iOuts1 != Outs.end(); iOuts1++, ii++)
		 if (ContextValues[iOuts1->second]->size()) {
			 TModelRule Rule;
			 Rule.Type = mrPossibility;
			 Rule.idxVar = -1;
			 Rule.First = Low*psbMul;
			 Rule.Last = (Low += 1.0*ContextValues[iOuts1->second]->size() / card)*psbMul;
			 Rule.Level = curLevel;
			 LocalRules[ii].insert(Rule);
		 }
		 for (iOuts = Outs.begin(), NumLink = 0; iOuts != Outs.end(); iOuts++, NumLink++)
		 if (!LocalRules[NumLink].empty()) {
			 set<TModelRule>::iterator iRules;
			 vector<TModelValue *> * curValues = ContextValues[iOuts->second];
			 vector<TModelValue *>::iterator icVals;
			 list<map<TModelVariable *, TModelValue> *>::iterator iVals;
			 curLevel++;
			 for (iRules = LocalRules[NumLink].begin(); iRules != LocalRules[NumLink].end(); iRules++)
				 iOuts->second->Rules.insert(*iRules);
			 // Here my be we must count combinations on some links -- non-separatable
			 // and count possibilities or use additional vars.
			 if (curValues->size()) {
				 icVals = curValues->begin();
				 iVals = iOuts->second->Vals.begin();
				 while (icVals != curValues->end()) {
					 bool delFlag = false;
					 for (iRules = LocalRules[NumLink].begin(); !delFlag && iRules != LocalRules[NumLink].end(); iRules++)
					 if (iOuts->second->FilterByRule(*icVals, iRules))
						 delFlag = true;
					 if (delFlag) {
						 icVals = curValues->erase(icVals);
						 iVals = iOuts->second->Vals.erase(iVals);
					 }
					 else {
						 iVals++;
						 icVals++;
					 }
				 }
			 }
		 }
	 }
	 StopFlag = 1;
     for (iOuts = Outs.begin(), NumLink = 0; iOuts!=Outs.end(); iOuts++, NumLink++) {
         LocalRules[NumLink].clear();
         if (iOuts->second)
            if (iOuts->second->Vals.size()>0)
               StopFlag = 0;
     }
     for (iOuts = Outs.begin(); iOuts!=Outs.end(); iOuts++) {
       vector<TModelValue *> *  curValues = ContextValues[iOuts->second];
       vector<map<int,int> *> * curSet    = ContextSets[iOuts->second];
       if (curValues) {
          for (int j=0; j<curValues->size(); j++)
              delete (*curValues)[j];
          delete curValues;
       }
       for (int j=0; j<curSet->size(); j++)
           delete (*curSet)[j];
       delete curSet;
     }
     ContextValues.clear();
     ContextSets.clear();
  } while (!StopFlag && coins < max_coins);
/*
  unconditional = Outs.begin();
  for (iOuts = Outs.begin(); iOuts!=Outs.end(); iOuts++)
    if (iOuts->second->Rules.size()==0 || !iOuts->second->InitNext) {
       unconditional = iOuts;
       break;
    }
*/
  cout<<MyName<<":"<<endl;
  delete[] LinkVars;
/*  for (iOuts = Outs.begin(); iOuts!=Outs.end(); iOuts++) {
    vector<TModelValue *> * cVals = ContextValues[iOuts->second];
    int N = cVals->size();
    cout<<iOuts->first<<"=";
    for (int i=0; i<N; i++) {
      TModelValue * cLine = (*cVals)[i];
      map<char *, TModelLink *>::iterator maxLink = Outs.end();
      int maxVoices = 0;
      for (iOuts1 = Outs.begin(); iOuts1!=Outs.end(); iOuts1++) {
        int curVoices = 0;
        for (iOuts2 = Outs.begin(); iOuts2!=Outs.end(); iOuts2++)
          if (iOuts1!=iOuts2)
             if (iOuts1->second->FilterVals(cLine, iOuts2->second))
                curVoices++;
        if (curVoices>maxVoices) {
           maxVoices = curVoices;
           maxLink   = iOuts1;
        }
      }
      if (iOuts==maxLink) cout<<"1"; else cout<<"0";
    }
    cout<<endl;
  }
*/
  // ContextValues[link] -- NULL or pointer to vector of (pointers of values array).
  // (*ContextValues[link])[set_of_vals_num][i]
  // Indexes (i) in order by ContextVars
  // Do not forget free its lines...
}

void TModelNode::MarkUsedVariables() {
  map<char *, TModelLink *>::iterator iOuts;
  
  for (iOuts = Outs.begin(); iOuts!=Outs.end(); iOuts++)
    iOuts->second->MarkUsedVariables(&ContextVars);
}

bool TModelNode::IsRandomized() {
  map<char *, TModelLink *>::iterator iOuts;
  bool Randomized = false;
  for (iOuts = Outs.begin(); !Randomized && iOuts!=Outs.end(); iOuts++)
    if (iOuts!=unconditional) {
       set<TModelRule>::iterator iRules;
       for (iRules = iOuts->second->Rules.begin(); !Randomized && iRules != iOuts->second->Rules.end(); iRules++)
         if (iRules->Type==mrPossibility)
            Randomized = true;
    }
  return Randomized;
}

TModelNode * TModelNode::Go (double & time) {
  set<TModelVariable *>::iterator iContextVars, iContextVars1;
  map<char *, TModelLink *>::iterator iOuts;
  double rnd = 0.0;
  int    K = ContextVars.size();
  int    i,j,k;

  TModelValue * Line = new TModelValue[K+K*(K-1)/2+1];

  for (iContextVars = ContextVars.begin(), i=0; iContextVars!=ContextVars.end(); iContextVars++, i++)
      Line[i] = (*iContextVars)->ExportValue();
  for (iContextVars = ContextVars.begin(), j=0; iContextVars!=ContextVars.end(); iContextVars++, j++)
    for (iContextVars1 = iContextVars, iContextVars1++, k=j+1; iContextVars1!=ContextVars.end(); iContextVars1++, i++, k++)
         Line[i] = Line[j]-Line[k];
  if (IsRandomized())
     rnd = 1.0*rand()/RAND_MAX;
  if (Outs.size()!=0) {
    for (iOuts = Outs.begin(); iOuts!=Outs.end(); iOuts++)
      if (iOuts!=unconditional && iOuts->second->Go(&ContextVars, Line, rnd, time)) {
         delete[] Line;
         return iOuts->second->Next;
      }
    if (unconditional!=Outs.end()) {
       unconditional->second->Perform(&ContextVars, Line, time);
       delete[] Line;
       return unconditional->second->Next;
    }
  }
  delete[] Line;
  return NULL;
}

void TModelNode::Export(ostream * out, char * MyName) {
  map<char *, TModelLink *>::iterator iOuts;
  bool Randomized = false;
  int K;
  exported = true;
  K = ContextVars.size();
  *out<<MyName<<":"<<endl;
  for (iOuts = Outs.begin(); !Randomized && iOuts!=Outs.end(); iOuts++)
    if (iOuts!=unconditional) {
       set<TModelRule>::iterator iRules;
       for (iRules = iOuts->second->Rules.begin(); !Randomized && iRules != iOuts->second->Rules.end(); iRules++)
         if (iRules->Type==mrPossibility)
            Randomized = true;
    }
  if (Randomized)
     *out<<"double rnd"<<MyName<<" = 1.0*rand()/RAND_MAX;\n";
  if (Outs.size()==0)
     *out<<"return __result;"<<endl;
  else {
    for (iOuts = Outs.begin(); iOuts!=Outs.end(); iOuts++)
      if (iOuts!=unconditional)
         *out<<"if ("<<iOuts->second->GetConditions(out, MyName,&ContextVars)<<") "<<iOuts->second->GetActions(true,iOuts->first);
	if (unconditional != Outs.end()) {
	   *out << unconditional->second->GetActions(true, unconditional->first);
	   if (!unconditional->second->Next->exported)
		  unconditional->second->Next->Export(out, unconditional->first);
	}
    for (iOuts = Outs.begin(); iOuts!=Outs.end(); iOuts++)
      if (iOuts!=unconditional && !iOuts->second->Next->exported)
         iOuts->second->Next->Export(out, iOuts->first);
  }
};

void TModelLink::Process() {
  if (InitNext) Next->Value = noValue;
  Next->Value++;
};

int TModelLink::AnalyzeContext(double delay) {
  map<string,TModelVariable *>::iterator iVars;
  map<TModelVariable *,TModelValue> * Context = new map<TModelVariable *,TModelValue>();
  TModelValue Val;
  set<TModelVariable *>::iterator iToInductVars;
  for (iToInductVars = ToInductVars.begin(); iToInductVars!=ToInductVars.end(); iToInductVars++)
      InductVars[*iToInductVars] = NULL;
  InductList = ToInductList;
  Val.Type = mvDouble;
  Val.Double = delay;
  if (Next->HasTiming) (*Context)[NULL] = Val; // This is the time only...
  for (iVars = CurContext->begin(); iVars!=CurContext->end(); iVars++) {
    map<string,TModelVariable *>::iterator inContext = Vars.find(iVars->first);
    if (inContext!=Vars.end())
       if (!(iVars->second)) iVars->second = inContext->second;
  }
  for (iVars = CurContext->begin(); iVars!=CurContext->end(); iVars++) {
    Val = iVars->second->ExportValue();
    if (typeid(*(iVars->second))==typeid(TModelNode) ||
        typeid(*(iVars->second))==typeid(TModelIntVariable) ||
        typeid(*(iVars->second))==typeid(TModelDoubleVariable))
       (*Context)[iVars->second] = Val;
  }
  Vals.push_back(Context);
  return Vals.size()>=chunkVals;
}

void TModelLink::CollectVars(set<TModelVariable *> & ContextVars, set<TModelVariable *> & MyVars) {
  int N = Vals.size();
  if (N>0) {
     list<map<TModelVariable *,TModelValue> *>::iterator iVals;
     map<TModelVariable *,TModelValue> * Context;
     map<TModelVariable *,TModelValue>::iterator iContext;
     int i;
     
     for (iVals = Vals.begin(), i=0; i<N; iVals++, i++) {
       Context = *iVals;
       for (iContext = Context->begin(); iContext!=Context->end(); iContext++)
           if (iContext->first) {
              ContextVars.insert(iContext->first);
              MyVars.insert(iContext->first);
           }
     }
  }
}

vector<TModelValue *> * TModelLink::CollectVals(set<TModelVariable *> & ContextVars) {
  vector<TModelValue *> * ContextValues = NULL;
  int N = Vals.size();
  if (N>0) {
     list<map<TModelVariable *,TModelValue> *>::iterator iVals;
     map<TModelVariable *,TModelValue> * Context;
     map<TModelVariable *,TModelValue>::iterator iContext, iContext1;
     set<TModelVariable *>::iterator iContextVars, iContextVars1;
     int idxContextValues, i;
     
     int K = ContextVars.size();
     ContextValues = new vector<TModelValue *>(N);
     for (iVals = Vals.begin(), idxContextValues = 0; idxContextValues<N; iVals++, idxContextValues++) {
       TModelValue * Line = new TModelValue[K+K*(K-1)/2+(Next->HasTiming ? 1 : 0)];
       Context = *iVals;
       for (iContextVars = ContextVars.begin(), i=0; iContextVars!=ContextVars.end(); iContextVars++, i++) {
         if ((iContext = Context->find(*iContextVars))==Context->end()) {
            Line[i].Type = mvInt;
            Line[i].Int  = noValue;
         } else
            Line[i] = iContext->second;
       }
       for (iContextVars = ContextVars.begin(); iContextVars!=ContextVars.end(); iContextVars++) {
         iContext = Context->find(*iContextVars);
         for (iContextVars1 = iContextVars, iContextVars1++; iContextVars1!=ContextVars.end(); iContextVars1++, i++) {
           if ((iContext1 = Context->find(*iContextVars1))==Context->end() ||
               iContext==Context->end()) {
              Line[i].Type = mvInt;
              Line[i].Int  = noValue;
           } else
              Line[i] = iContext->second-iContext1->second;
         } 
       }
       if (Next->HasTiming) Line[i] = (*Context)[NULL];
       (*ContextValues)[idxContextValues] = Line;
     }
  }
 return ContextValues;
}

bool TModelLink::FilterVals(TModelValue * cLine, TModelLink * _With) {
  set<TModelRule>::iterator _iRules;
  for (_iRules = Rules.begin(); _iRules!=Rules.end(); _iRules++)
    if (FilterByRule(cLine,_iRules))
       return true;
  return false;
}

bool TModelLink::FilterByRule(TModelValue * cLine, const set<TModelRule>::iterator _iRules) {
   TModelRule curRule = *_iRules;
   if (curRule.Type==mrPossibility)
      return true;
   else {
     int VAL = (int)(~cLine[curRule.idxVar]);
     if (VAL>=curRule.First && VAL<=curRule.Last)
        switch (curRule.Type) {
           case mrArithm:
             if (VAL % curRule.period == curRule.c)
                return true;
             break;
           case mrGeom: {
             double C = log((VAL-curRule.gB)/curRule.gA0)/curRule.lngp;
             if (fabs(C-(int)(C + 0.5))<GEOM_EPS)
                return true;
             break;
           }
           default: return true;
        }
   }
   return false;
}

void TModelLink::MarkUsedVariables(set<TModelVariable *> * ContextVars) {
  set<TModelRule>::iterator iRules;
  set<TModelVariable *>::iterator iVars;
  map<TModelVariable *, TModelFunction *>::iterator iInductVars;

  if (FUN) FUN->MarkUsedVariables();
  for (iInductVars = InductVars.begin(); iInductVars!=InductVars.end(); iInductVars++)
      if (iInductVars->second) iInductVars->second->MarkUsedVariables();
  for (iRules = Rules.begin(); iRules!=Rules.end(); iRules++) {
    int Var0, Var1;
    int i;
    if (iRules->idxVar>=0) {
       GetVarName(iRules->idxVar,ContextVars,NULL,Var0,Var1);
       for (iVars = ContextVars->begin(), i=0; Var0>=0 || Var1>=0; iVars++, i++)
         if (i==Var0 || i==Var1) {
           (*iVars)->used = true;
           if (i==Var0) Var0 = -1;
           if (i==Var1) Var1 = -1;
         }
    }
  }
}

void InsertDeclarations(char * _OUT, set<string> & DECLS, const char * NewDECLS) {
   set<string>::iterator iDECLS;
   char Buf[20000];
   char * tok;
   strcpy(Buf,NewDECLS);
   tok = strtok(Buf,"\n");
   while (tok) {
     if (DECLS.find(tok)==DECLS.end()) {
        DECLS.insert(tok);
        strcat(_OUT,tok);
        strcat(_OUT,"\n");
     }
     tok = strtok(NULL,"\n");
   }
}

char * TModelLink::GetActions(bool WithGoto, char * ToName) {
   static char _OUT[20000];
   map<TModelVariable *, TModelFunction *>::iterator iInductVars;
   set<string> DECLS;
   bool WithTime = FUN && !(typeid(*FUN)==typeid(TModelConst) && ((TModelConst *)(FUN))->getValue()<1);
   strcpy(_OUT,"");
   if (Next && Next->used && WithGoto || WithTime || !InductVars.empty()) strcat(_OUT,"{ ");
   strcat(_OUT,"\n");
   for (iInductVars = InductVars.begin(); iInductVars!=InductVars.end(); iInductVars++)
     if (iInductVars->second)
        InsertDeclarations(_OUT,DECLS,iInductVars->second->Declarations.c_str());
   if (WithTime) {
      InsertDeclarations(_OUT,DECLS,FUN->Declarations.c_str());
      strcat(_OUT,"double timing = ");
      strcat(_OUT,FUN->Definition.c_str());
      strcat(_OUT,"; if (timing>=___min && timing<=___max) __result += timing;\n");
   }
   for (iInductVars = InductVars.begin(); iInductVars!=InductVars.end(); iInductVars++)
     if (iInductVars->second) {
        strcat(_OUT,"_");
        strcat(_OUT,nmVars[iInductVars->first].c_str());
        strcat(_OUT," = ");
        strcat(_OUT,iInductVars->second->Definition.c_str());
        strcat(_OUT,";\n");
     }
   if (Next && Next->used) {
      strcat(_OUT," _");
      strcat(_OUT,ToName);
      if (InitNext)
         strcat(_OUT," = 1; ");
      else
         strcat(_OUT,"++; ");
   }
   if (WithGoto) {
      strcat(_OUT,"goto ");
      strcat(_OUT,ToName);
      strcat(_OUT,";");
   }
   if (Next && Next->used && WithGoto || WithTime || !InductVars.empty()) strcat(_OUT," }");
   if (_OUT[0]) strcat(_OUT,"\n");
   return _OUT;
 }
 
struct rless : public binary_function <TModelRule *, TModelRule *, bool> 
{
  bool operator()(const TModelRule * _Left, const TModelRule * _Right ) const {
   return _Left->Level<_Right->Level;
  }
};

char * TModelLink::GetConditions(ostream * out, char * NodeName, set<TModelVariable *> * ContextVars) {
  static char _OUT[20000];
  set<TModelRule>::iterator iRules;
  list<TModelRule *>::iterator _iRules;
  list<TModelRule *> _Rules;
  strcpy(_OUT,"");
  if (Rules.size()) {
     for (iRules = Rules.begin(); iRules!=Rules.end(); iRules++)
       _Rules.push_back((pm::TModelRule *)&(*iRules));
     _Rules.sort(rless());
     for (_iRules = _Rules.begin(); _iRules!=_Rules.end(); _iRules++) {
       if (_iRules!=_Rules.begin())
          strcat(_OUT," || (");
       else
          strcat(_OUT,"(");
       strcat(_OUT,(*_iRules)->Export(out, NodeName,ContextVars));
       strcat(_OUT,")");
     }
  } else
     strcpy(_OUT,"true");
   
  return _OUT;
}

bool TModelLink::Go(set<TModelVariable *> * ContextVars, TModelValue * Line, double rnd, double & time) {
  set<TModelRule>::iterator iRules;
  bool ok = false;
  iRules = Rules.begin();
  while (!ok && iRules!=Rules.end())
    if (iRules->Type==mrPossibility) {
       ok = 1.0*iRules->First/psbMul<=rnd && rnd<1.0*iRules->Last/psbMul;
       if (!ok) iRules++;
    } else if (FilterByRule(Line,iRules))
       ok = true;
    else
       iRules++;
  if (ok) Perform(ContextVars, Line, time);
  return ok;
}

void TModelLink::Perform(set<TModelVariable *> * ContextVars, TModelValue * Line, double & time) {
  if (FUN) {
     double val = FUN->getValue();
     if (val>=0.0)
        time += val;
  }
  Process();
}

}

void MarkModelPoint(char * Name, bool Timing = false);

void FreeModel() {
  using namespace pm;
  map<string,TModelVariable *>::iterator iVars;
  for (iVars = Vars.begin(); iVars!=Vars.end(); iVars++)
      delete (TModelVariable *) iVars->second;
  map<string,map<string,TModelVariable *> *>::iterator iContext;
  for (iContext = Contexts.begin(); iContext!=Contexts.end(); iContext++)
      if (iContext->first!=defaultContext) delete iContext->second;
  Contexts.clear();
  Contexts[defaultContext] = &Vars;
  Vars.clear();
  nmVars.clear();
  Trace.clear();
  ToInductVars.clear();
  ToInductList.clear();
  CurContext = &Vars;
  ModelRoot = NULL;
  LastNode  = NULL;
}

void StartModel() {
  using namespace pm;
  if (ModelRoot) {
     map<string,TModelVariable *>::iterator iVars;
     MarkModelPoint("___exit___",false);
     for (iVars = Vars.begin(); iVars!=Vars.end(); iVars++)
         iVars->second->Restart();
  } else {
     Contexts.clear();
     Contexts[defaultContext] = &Vars;
     Vars.clear();
     nmVars.clear();
     ModelRoot = NULL;
  }
  Trace.clear();
  ToInductVars.clear();
  ToInductList.clear();
  CurContext = &Vars;
  LastNode  = NULL;
  ModelTime = 0.0;
  Timer = milliseconds();
  MarkModelPoint("___entry___",true);
}

bool ExportModelToCPP(char * funName, char * fName = NULL) {
  using namespace pm;
  if (ModelRoot) {
     map<string,TModelVariable *>::iterator iVars;
     ostream * out = &cout;

     if (fName) out = new ofstream(fName);
     for (iVars = Vars.begin(); iVars!=Vars.end(); iVars++)
         iVars->second->MarkUsedVariables(); // In the future not only int...
     *out<<"#include <windows.h>"<<endl;
     *out<<"#include <math.h>"<<endl;
     *out<<"#include <stdlib.h>"<<endl;
     *out<<"#include <time.h>"<<endl;
     *out<<"#ifdef __cplusplus"<<endl;
     *out<<"extern "<<'"'<<"C"<<'"'<<" {"<<endl;
     *out<<"#endif"<<endl;
     *out<<"__declspec(dllexport) double "<<funName<<"(double ___min, double ___max";
     for (iVars = Vars.begin(); iVars!=Vars.end(); iVars++)
         if (typeid(*(iVars->second))==typeid(TModelIntVariable))
            *out<<", int &_"<<iVars->first;
         else if (typeid(*(iVars->second))==typeid(TModelDoubleVariable))
            *out<<", double &_"<<iVars->first;
     *out<<");"<<endl;
     *out<<"#ifdef __cplusplus"<<endl;
     *out<<"}"<<endl;
     *out<<"#endif"<<endl;
     *out<<"__declspec(dllexport) double "<<funName<<"(double ___min, double ___max";
     for (iVars = Vars.begin(); iVars!=Vars.end(); iVars++)
         if (typeid(*(iVars->second))==typeid(TModelIntVariable))
            *out<<", int &_"<<iVars->first;
         else if (typeid(*(iVars->second))==typeid(TModelDoubleVariable))
            *out<<", double &_"<<iVars->first;
     *out<<") {"<<endl;
     *out<<"double __result = 0.0;"<<endl;
     for (iVars = Vars.begin(); iVars!=Vars.end(); iVars++)
       if (iVars->second->getUsed() && typeid(*(iVars->second))==typeid(TModelNode))
          *out<<"int _"<<iVars->first<<" = 0;"<<endl;
     *out<<"double dummy;"<<endl;
     ModelRoot->Export(out, ModelRootName);
     for (iVars = Vars.begin(); iVars!=Vars.end(); iVars++)
         iVars->second->ClearAfterExport();
     *out<<"}"<<endl;
     *out<<"int CALLBACK LibMain(HINSTANCE hinst, WORD wDataSeg, WORD cbHeapSize, LPSTR lpszCmdLine)"<<endl;
     *out<<"{"<<endl;
     *out<<" return 1;"<<endl;
     *out<<"}"<<endl;
     if (fName) {
        dynamic_cast<ofstream *>(out)->close();
        delete out;
     }
     return true;
  }
 return false;
}

bool ExportModelToLibrary(char * funName, char * fName, char * path, int nipaths, char ** ipaths, int nlpaths, char ** lpaths) {
  char * cmd_name = "run.bat";
  ofstream cmd(cmd_name);
  char libname[255];
  if (!ExportModelToCPP(funName,fName))
     return false;
  else {
    strcpy(libname,fName);
    char * PointPos = strrchr(libname,'.');
    if (PointPos) *PointPos = 0x0;
    cmd<<"@echo off"<<endl;
	if (path && *path) cmd << "@set PATH=" << path << ";%PATH%;" << endl;
    for (int i=0; i<nipaths; i++)
        cmd<<"@set IPATH"<<i<<"="<<ipaths[i]<<endl;
    for (int i=0; i<nlpaths; i++)
        cmd<<"@set LPATH"<<i<<"="<<lpaths[i]<<endl;
    cmd<<"@cl.exe /LD /O2 -o "<<libname<<".dll "<<fName<<" /Fa /MTd /EHsc";
    for (int i=0; i<nipaths; i++)
        cmd<<" /I %IPATH"<<i<<"%";
    cmd<<" /link";
    for (int i=0; i<nlpaths; i++)
        cmd<<" /LIBPATH:%LPATH"<<i<<"%";
    cmd<<endl;
    cmd.close();
    system(cmd_name);
    return true;
  }
}

map<string,HMODULE> Libs;

void * ImportModel(char * funName, char * libName) {
  HMODULE LIB = Libs.find(libName)!=Libs.end() ? Libs[libName] : (Libs[libName] = LoadLibrary(libName));
  if (LIB)
     return GetProcAddress(LIB,funName);
  else
     return NULL;
}

int ProcessModel() {
  const int Nexprms = 11;
  using namespace pm;
  int result = 0;
  if (ModelRoot) {
     map<string,TModelVariable *>::iterator iVars;
     double Timings[Nexprms] = {0};
     bool Randomized = false;
     for (iVars = Vars.begin(); !Randomized && iVars!=Vars.end(); iVars++)
         if (typeid(*(iVars->second))==typeid(TModelNode))
            Randomized = dynamic_cast<TModelNode *>(iVars->second)->IsRandomized();
     int N = Randomized ? Nexprms : 1;
     srand(time(NULL));
     for (int i=0; i<N; i++) {
       TModelNode * CurrentNode = ModelRoot;
       for (iVars = Vars.begin(); iVars!=Vars.end(); iVars++)
           iVars->second->Restart();
       while (CurrentNode = CurrentNode->Go(Timings[i]));
     }
     // Elementary cluster tree analysis
     if (N>1) {
        set<set<int> *> Data;
        set<set<int> *>::iterator iData, _iData;
        set<int>::iterator iCluster;
        int nClusters;
        for (int i=0; i<N; i++) {
            set<int> * Item = new set<int>();
            Item->insert(i);
            Data.insert(Item);
        }
        double Centers[Nexprms] = {0.0};
        double SKO[Nexprms] = {0.0};
        int i, j;
        while ((nClusters = Data.size())>1) {
          int mrgFirst, mrgSecond;
          double C, _SKO, mrgSKO;
          double MinDist = 1E300;
          for (iData = Data.begin(), i = 0; iData!=Data.end(); iData++, i++) {
              Centers[i] = 0.0;
              for (iCluster = (*iData)->begin(); iCluster!=(*iData)->end(); iCluster++)
                  Centers[i] += Timings[*iCluster];
              Centers[i] /= (*iData)->size();
              SKO[i] = 0.0;
              for (iCluster = (*iData)->begin(); iCluster!=(*iData)->end(); iCluster++)
                  SKO[i] += (Timings[*iCluster]-Centers[i])*(Timings[*iCluster]-Centers[i]);
              SKO[i] = sqrt(SKO[i]);
              if ((*iData)->size()>1) SKO[i] /= (*iData)->size()-1;
          }
          for (i = 0; i<nClusters-1; i++)
            for (j = i+1; j<nClusters; j++) {
              double Dist = fabs(Centers[i]-Centers[j]);
              if (Dist<MinDist) {
                 MinDist   = Dist;
                 mrgFirst  = i;
                 mrgSecond = j-i;
                 mrgSKO    = max(SKO[i],SKO[j]);
              }
            }
          for (iData = Data.begin(); mrgFirst--; iData++);
          _iData = iData;
          while (mrgSecond--) iData++;
          
          C = 0.0;
          for (iCluster = (*iData)->begin(); iCluster!=(*iData)->end(); iCluster++)
              C += Timings[*iCluster];
          for (iCluster = (*_iData)->begin(); iCluster!=(*_iData)->end(); iCluster++)
              C += Timings[*iCluster];
          C /= ((*iData)->size()+(*_iData)->size());
          _SKO = 0.0;
          for (iCluster = (*iData)->begin(); iCluster!=(*iData)->end(); iCluster++)
              _SKO += (Timings[*iCluster]-C)*(Timings[*iCluster]-C);
          for (iCluster = (*_iData)->begin(); iCluster!=(*_iData)->end(); iCluster++)
              _SKO += (Timings[*iCluster]-C)*(Timings[*iCluster]-C);
          _SKO = sqrt(_SKO);
          _SKO /= ((*iData)->size()+(*_iData)->size()-1);
          // STOP if new cluster has SKO in 50 times greater than the bigest of sources...
          if (_SKO>50*mrgSKO && mrgSKO>EPS)
             break;
          else {
			  for (iCluster = (*iData)->begin(); iCluster!=(*iData)->end(); iCluster++)
				 (*_iData)->insert(*iCluster);
              Data.erase(iData);
          }
        };
        // Get the biggest cluster, conforming to rule that the most of probes were correct, not else
        for (iData = _iData = Data.begin(), i = 0, j = 0, _iData++; _iData!=Data.end(); _iData++, j++)
            if ((*_iData)->size()>(*iData)->size() || (*_iData)->size()==(*iData)->size() && Centers[j]<Centers[i]) {
               iData = _iData;
               i = j;
            }
        result = 0;
        for (iCluster = (*iData)->begin(); iCluster!=(*iData)->end(); iCluster++)
            result += Timings[*iCluster];
        result /= (*iData)->size();
     } else
        result = Timings[0];
  }
  return result;
}

void StopModel() {
  using namespace pm;
  MarkModelPoint("___exit___",false);
  map<string,TModelVariable *>::iterator iVars;
  for (iVars = Vars.begin(); iVars!=Vars.end(); iVars++)
      iVars->second->FlushRules((char *) iVars->first.c_str());
}

void MarkModelPoint(char * Name, bool Timing) {
  using namespace pm;
  double Start = milliseconds();
  Delay = Start-Timer;
  map<string,TModelVariable *>::iterator iVars = Vars.find(Name);
  TModelNode * ThisNode;
  if (iVars==Vars.end()) {
     ThisNode = new TModelNode(noValue, Timing);
     Vars[Name] = ThisNode;
     nmVars[ThisNode] = Name;
  } else
     ThisNode = (TModelNode*) iVars->second;
  if (!LastNode) {
     ModelRoot = ThisNode;
     strcpy(ModelRootName,Name);
  } else {
     TModelLink * ThisLink = LastNode->GetOutLink(Name);
     list<TModelNode *>::iterator iTrace = Trace.end();
     bool Cycled = false;
     while (!Cycled && iTrace!=Trace.begin())
       if (*(--iTrace)==ThisNode) Cycled = true;
     if (Cycled)
        Trace.erase(++iTrace,Trace.end());
     if (!ThisLink) {
        ThisLink = new TModelLink(!Cycled,ThisNode);
        LastNode->AddOutLink(Name,ThisLink);
     }
     if (ThisLink->AnalyzeContext(Delay))
        LastNode->FlushRules(LastNodeName);
     ThisLink->Process();
  }
  ToInductVars.clear();
  ToInductList.clear();
  LastNode = ThisNode;
  strcpy(LastNodeName,Name);
  Trace.push_back(ThisNode);
  if (Timing) {
     Timer = milliseconds();
     ModelTime += Delay;
  } else Timer += milliseconds()-Start;
}

void RegisterVariable(char * Name, int Value, bool Induct = false) {
  using namespace pm;
  if (Vars.find(Name)!=Vars.end())
     Vars[Name]->ImportValue(Value);
  else {
    TModelIntVariable * Var = new TModelIntVariable(Value);
    Vars[Name] = Var;
    nmVars[Var] = Name;
  }
 if (Induct) {
    TModelVariable * V = Vars[Name];
    ToInductVars.insert(V);
    ToInductList.push_back(V);
 }
}

void RegisterVariable(char * Name, double Value, bool Induct = false) {
  using namespace pm;
  if (Vars.find(Name)!=Vars.end())
     Vars[Name]->ImportValue(Value);
  else {
    TModelDoubleVariable * Var = new TModelDoubleVariable(Value);
    Vars[Name] = Var;
    nmVars[Var] = Name;
  }
 if (Induct) {
    TModelVariable * V = Vars[Name];
    ToInductVars.insert(V);
    ToInductList.push_back(V);
 }
}

void CreateContext(char * Name, int Size, ...) {
  using namespace pm;
  va_list Args;
  map<string,map<string,TModelVariable *> *>::iterator it;
  if ((it = Contexts.find(Name))!=Contexts.end()) {
     CurContext = it->second;
     CurContext->clear();
  } else
     Contexts[Name] = CurContext = new map<string,TModelVariable *>;
  
  va_start(Args,Size);
  for (; Size>0; Size--) {
      char * Arg = va_arg(Args,char *);
      map<string,TModelVariable *>::iterator _it = Vars.find(Name);
      if (_it!=Vars.end())
         (*CurContext)[Arg] = _it->second;
      else
         (*CurContext)[Arg] = NULL;
  }
  
  va_end(Args);
}

bool SwitchContext(char * Name) {
  using namespace pm;
  map<string,map<string,TModelVariable *> *>::iterator it;
  if ((it = Contexts.find(Name))==Contexts.end())
     return false;
  else
     CurContext = it->second;
  return true;
}

