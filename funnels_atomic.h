#ifndef __FUNNELS_H__
#define __FUNNELS_H__

#ifdef _MSC_VER
  #include <windows.h>
#else
  #include <unistd.h>
  #ifdef _POSIX_PRIORITY_SCHEDULING
    #include <sched.h>
  #endif
#endif
inline void _Yield() {
#ifdef _MSC_VER
  Sleep(0)
#elif defined(_POSIX_PRIORITY_SCHEDULING)
  sched_yield()
#endif
;}

#ifdef __REENT_MPI__
#include "mpi.h"
int __cluster_size__ = 1;
int __cluster_id__ = 0;
#endif

#ifdef _OPENMP
 #include <string.h>
 #include <stdlib.h>
 #include <math.h>
 #include <omp.h>
 #include <iostream>
 #include <string>
 #include <vector>
 #include <algorithm>
 #include <map>
 using namespace std;
 #define funnel(Dir,Type) funneled_##Dir<Type>
 const char tnlValue  = 0x01;
 const char tnlHasIn  = 0x02;
 const char tnlHasOut = 0x04;
 const int WAITING_COUNTER = 80;
 omp_lock_t __funnel_lock__;
 class __funnel;
 map<string,__funnel *> __Funnels;
 #ifndef __min
 #define __min(a,b) ((a)<(b) ? (a) : (b))
 #endif
 #ifndef __max
 #define __max(a,b) ((a)>(b) ? (a) : (b))
 #endif
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
 /* Метод Гаусса-Зейделя  с выбором максимального элемента по диагонали */
 bool _SolveGaussZeidel(int NN, int * iRow, long double * A, long double * LU, long double * Y, long double * X) {
  int np = omp_get_num_procs();
  double prev_eps, eps;
  int grow;
  int iters;
  try {
    for (int i=0;i<NN;i++)
        iRow[i]=i;
    for (int i=0;i<NN-1;i++)
      {
       long double Big  = fabs(A[iRow[i]*NN+i]);
       int iBig = i;
       for (int j=i+1;j<NN;j++)
           {
            long double size = fabs(A[iRow[j]*NN+i]);
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
      }
    for (int i=0;i<NN;i++)
        X[i]=0.5;
    eps = 1E300;
    grow = 0;
    for (iters = 0; eps > 1E-8 && iters < 2*NN; iters++) {
        prev_eps = eps;
        eps = 0.0;
        if (NN < 20 || np < 3) {
           for (int i=0;i<NN;i++) {
               long double V = Y[iRow[i]];
               double d = X[i];
               for (int j=0;j<NN;j++)
                   if (j != i)
                      V -= A[iRow[i]*NN+j]*X[j];
               X[i] = V/A[iRow[i]*NN+i];
               d -= X[i];
               eps += d*d;
           }
           eps = sqrt(eps);
        } else {
           for (int i=0;i<NN;i++) {
               long double V = Y[iRow[i]];
               double d = X[i];
               #pragma omp parallel for num_threads(np) reduction(+:V)
               for (int j=0;j<NN;j++)
                   if (j != i)
                      V -= A[iRow[i]*NN+j]*X[j];
               X[i] = V/A[iRow[i]*NN+i];
               d -= X[i];
               eps += d*d;
           }
           eps = sqrt(eps);
        }
        if (eps > prev_eps)
           grow++;
        else
           grow = 0;
    }
    return eps <= 1E-8;
  }
  catch (...) {
    return false;
  }
 }
 class __funnel {
  public:
    omp_lock_t Lock;
    volatile char State;
    volatile int Refs;
    bool useLU;
    string Name;
    __funnel(const char * Name = NULL) {
      State = 0;
      Refs = 0;
      useLU = true;
      omp_init_lock(&Lock);
      if (Name)
         this->Name = Name;
      else
         this->Name = "";
    };
    void switchLU(bool LU) {
      useLU = LU;
    }
    virtual ~__funnel() {
      if (Name.length() > 0) {
         omp_set_lock(&__funnel_lock__);
         map<string,__funnel *>::iterator itFunnels = __Funnels.find(Name);
         if (itFunnels == __Funnels.end()) {
            cout<<"Abnormal funnel termination: funnel '"<<Name<<"' is not registered"<<endl;
            exit(-1);
         } else {
            __Funnels.erase(itFunnels);
         }
         omp_unset_lock(&__funnel_lock__);
      }
      omp_destroy_lock(&Lock);
    };
 };
 template<class Type>
  class _funnel: public __funnel {
  public:
    Type * Data;
    volatile int    N;
    _funnel(int N, const char * Name = NULL): __funnel(Name) {
      this->N = N;
      Data = (Type *) malloc(N*sizeof(Type));
    };
    void check_size(int _NN) {
      if (_NN > N) {
         N = (int)(1.5*_NN);
         free((void *) Data);
         Data = (Type *) malloc(N*sizeof(Type));
      }
    };
    int getN() {
      return N;
    };
    virtual void add_refs(const vector<_funnel<Type> *> * _refs) {
    };
    virtual ~_funnel() {
      free((void *) Data);
    };
 };
 template<class Type>
  class _funnel_with_history: public _funnel<Type> {
  protected:
    Type *  Predicted;
    volatile bool    HasPredicted;
    volatile bool    Calculated;
    Type ** History;
    double rel_eps;
    volatile int     MaxDepth;
    volatile int     Depth;
    volatile int     MaxP;
    volatile int  *  P;
	volatile bool *  Mask;
  public:
    Type * getPredicted() { return this->Predicted; };
    bool hasPredicted() { return this->HasPredicted; };
    bool isCalculated() { return this->Calculated; };
    Type ** getHistory() { return History; };
    int getMaxDepth() { return this->MaxDepth; };

    _funnel_with_history(int N, double rel_eps, const char * Name): _funnel<Type>(N, Name) {
      this->P = new int[N];
      this->MaxP = 0;
      this->MaxDepth = 0;
      this->Depth = 0;
      this->Predicted = NULL;
      this->HasPredicted = false;
      this->Calculated = false;
      this->rel_eps = rel_eps;
      this->History = NULL;
	  this->Mask = NULL;
    };
    _funnel_with_history(int P, int N = 1, double rel_eps = 0.001, const char * Name = NULL): _funnel<Type>(N, Name) {
      this->P = new int[N];
      this->MaxP = P;
      this->MaxDepth = this->MaxP*2;
      this->Depth = 0;
      this->Predicted = (Type *) malloc(N*sizeof(Type));
      this->HasPredicted = false;
      this->Calculated = false;
      this->rel_eps = rel_eps;
      this->History = new Type * [MaxDepth];
      for (int i = 0; i <this->MaxDepth; i++) {
          this->History[i] = new Type[N];
      }
	  this->Mask = NULL;
	};
    void push_history(bool lock = true) {
      if (lock) omp_set_lock(&this->Lock);
      if (Depth > 0) {
         Type * Bottom = this->History[0];
         for (int i = 0; i < this->MaxDepth - 1; i++)
             this->History[i] = this->History[i + 1];
         this->History[MaxDepth - 1] = Bottom;
      }
      if (Depth <this->MaxDepth) Depth++;
      memmove((void *) this->History[MaxDepth - 1], (void *) this->Data, this->N*sizeof(Type));
      if (lock) omp_unset_lock(&this->Lock);
    }
    void pop_history(bool lock = true) {
      if (lock) omp_set_lock(&this->Lock);
      if (Depth > 0) {
         Type * Top = this->History[MaxDepth - 1];
         for (int i = this->MaxDepth - 1; i > 0; i--)
             this->History[i] = this->History[i - 1];
         this->History[0] = Top;
         Depth--;
      }
      unset_predict_results();
      if (lock) omp_unset_lock(&this->Lock);
    }
    void replace_top_history(void * Buf, bool lock = true) {
         if (lock) omp_set_lock(&this->Lock);
         memmove((void *) this->History[MaxDepth - 1], Buf, this->N*sizeof(Type));
         if (lock) omp_unset_lock(&this->Lock);
    }
	virtual void setMask(bool * Mask) {
		this->Mask = Mask;
	}
    virtual bool predict(bool use_top) = 0;
    virtual void correct() = 0;
    virtual void unset_predict_results() {
      HasPredicted = false;
    }
    virtual void set_predict_results() {
      HasPredicted = true;
    }
    virtual void LOCK() {
      omp_set_lock(&this->Lock);
    }
    virtual void UNLOCK() {
      omp_unset_lock(&this->Lock);
    }
    virtual ~_funnel_with_history() {
      free((void *) this->Predicted);
      for (int i = 0; i <this->MaxDepth; i++)
          delete[] this->History[i];
      delete[] this->History;
      delete[] P;
    };
 };
 template<class Type>
  class _funnel_predictor: public _funnel_with_history<Type> {
  private:
    double ** K;
    long double * A;
    long double * LU;
    long double * Y;
    long double * X;
    bool calc_predictor(bool use_top) {
       int corr = use_top ? 0 : 1;
       int iRow[1024];
       for (int p = 0; p < this->N; p++)
		   if (!this->Mask || this->Mask[p]) {
			   double max_err = 1E300;
			   this->P[p] = -1;
			   for (int pp = this->MaxP; pp >= 1; pp--) {
				   memset(A, 0, this->MaxP*this->MaxP*sizeof(long double));
				   memset(Y, 0, this->MaxP*sizeof(long double));
				   int L = __min(this->MaxDepth - corr, pp * 3);
				   for (int i = this->MaxDepth - corr - L; i < this->MaxDepth - corr - pp + 1; i++) {
					   for (int j = 0, ptr = 0; j < pp; j++) {
						   long double XX = j == 0 ? 1.0 : (long double) this->History[i + j - 1][p];
						   for (int k = 0; k < pp; k++, ptr++) {
							   A[ptr] += (k == 0 ? 1.0 : (long double) this->History[i + k - 1][p])*XX;
						   }
						   Y[j] += XX*(long double) this->History[i + pp - 1][p];
					   }
				   }
				   bool result = (!this->useLU && _SolveGaussZeidel(pp, iRow, A, LU, Y, X)) || _GetLU(pp, iRow, A, LU) && _SolveLU(pp, iRow, LU, Y, X);
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
					   cur_err = 0.0;
					   double val = X[0];
					   for (int j = 1; j < pp; j++)
						   val += X[j] * ((double) this->History[this->MaxDepth - corr - pp + j - 1][p]);
					   this->Predicted[p] = (Type)val;
					   Type H = (Type)this->History[this->MaxDepth - corr - 1][p];
					   if (H != 0) {
						   cur_err = fabs(1.0*(H - (Type)val) / H);
					   }
				   }
				   if (result) {
					   if (cur_err < this->rel_eps && cur_err <= max_err) {
						   this->P[p] = pp;
						   for (int i = 0; i < pp; i++)
							   K[p][i] = (double)X[i];
						   max_err = cur_err;
					   }
				   }
			   }
		   } else
			   this->P[p] = -1;
       return true;
    }
  public:
    _funnel_predictor(int P, int N = 1, double rel_eps = 0.001, const char * Name = NULL): _funnel_with_history<Type>(P, N, rel_eps, Name) {
       K = (double **) malloc(N*sizeof(double *));
       for (int i = 0; i < N; i++)
           K[i] = (double *) malloc(this->MaxP*sizeof(double));
       A = new long double[this->MaxP*this->MaxP];
       LU = new long double[this->MaxP*this->MaxP];
       Y = new long double[this->MaxP];
       X = new long double[this->MaxP];
    };
    virtual bool predict(bool use_top) {
       bool result = false;
       if (!this->Calculated && this->Depth == this->MaxDepth) {
           this->Calculated = calc_predictor(use_top);
       }
       if (this->Calculated) {
           int corr = use_top ? 0 : 1;
           for (int i = 0; i < this->N; i++)
             if (this->P[i] < 0)
                this->Predicted[i] = (Type)this->History[this->MaxDepth - corr - 1][i];
             else {
                double val = K[i][0];
                for (int j = 1; j < this->P[i]; j++)
                    val += K[i][j]*((double) this->History[this->MaxDepth - corr - this->P[i] + j][i]);
                this->Predicted[i] = (Type) val;
           }
           result = true;
       }
       if (result) this->HasPredicted = true;
       return result;
    };
    virtual void correct() {
       omp_set_lock(&this->Lock);
       if (this->Calculated && this->HasPredicted) {
           double eps = 0.0;
           int nn = 0;
           for (int i = 0; i < this->N; i++)
			   if (!this->Mask || this->Mask[i]) {
				   if (this->Data[i] != (Type) 0.0) {
					   eps += fabs(1.0*(this->Predicted[i] - this->Data[i]) / this->Data[i]);
					   nn++;
				   }
			   }
           if (nn > 0) eps /= nn;
           if (eps > this->rel_eps)
              this->Calculated = false;
       }
       omp_unset_lock(&this->Lock);
    };
    virtual ~_funnel_predictor() {
       for (int i = 0; i < this->N; i++)
           free((void *) K[i]);
       free((void *) K);
       delete[] A;
       delete[] LU;
       delete[] Y;
       delete[] X;
    };
 };
 template<class Type>
  class _funnel_perceptron: public _funnel_with_history<Type> {
  protected:
    double ** K1;
    double ** K2;
    double ** K;
    double * B;
    double * B1;
    double * B2;
    double ** C;
    double ** C1;
    double ** C2;
    int * nstart;
    int * nend;
    int * iRow;
    long double * A;
    long double * LU;
    long double * Y;
    long double * X;
    bool hasB;
    int PATTERN;
  protected:
    vector<_funnel<Type> *> refs;
    virtual bool calc_predictor(bool use_top) = 0;
    virtual void apply_predictor(bool use_top) = 0;

    virtual void analyze(int NN, double k1, double * BB1, double k2, double * BB2, double * R1, double * R2) {
       double d = k2 - k1;
       double fd = fabs(d);
       for (int i = 0; i < NN; i++)
           if (fd < 1E-8) {
              R1[i] = BB1[i];
              R2[i] = 0.0;
           } else {
              R2[i] = (BB2[i] - BB1[i]) / d;
              R1[i] = BB1[i] - k1*R2[i];
           }
    }
    virtual void use(int NN, double k, double * R, double * R1, double * R2) {
       for (int i = 0; i < NN; i++)
           R[i] = R1[i] + k*R2[i];
    }
  public:
    const vector<_funnel<Type> *> & get_refs() { return refs; };
    const bool get_hasB() { return hasB; }

    virtual void add_refs(const vector<_funnel<Type> *> * _refs) {
       if (_refs) {
          int NN = this->refs.size();
          for (unsigned int i = 0; i < _refs->size(); i++)
              if (find(refs.begin(), this->refs.end(), (*_refs)[i]) == this->refs.end())
                 this->refs.push_back((*_refs)[i]);
          if (NN < this->refs.size()) {
             this->MaxP = this->N + this->refs.size() + (this->hasB ? 1 : 0);
             for (int i = 0; i < this->N; i++)
                 C[i] = (double *) realloc(C[i], this->refs.size()*sizeof(double));
             delete[] iRow; iRow = new int[this->MaxP];
             delete[] A;    A = new long double[this->MaxP*this->MaxP];
             delete[] LU;   LU = new long double[this->MaxP*this->MaxP];
             delete[] Y;    Y = new long double[this->MaxP];
             delete[] X;    X = new long double[this->MaxP];
          }
       }
    };

    _funnel_perceptron(bool hasB, const vector<_funnel<Type> *> &refs, int N = 1, double rel_eps = 0.001, const char * Name = NULL, int PATTERN = -1): _funnel_with_history<Type>(N, rel_eps, Name) {
       this->refs = refs;
       this->MaxDepth = N + __max(40,refs.size()) + 2;
       this->PATTERN = PATTERN;
       this->Depth = 0;
       this->MaxP = N + this->refs.size() + 1;
       this->Predicted = (Type *) malloc(N*sizeof(Type));
       this->HasPredicted = false;
       this->Calculated = false;
       this->hasB = hasB;
       this->History = new Type * [this->MaxDepth];
       for (int i = 0; i < this->MaxDepth; i++) {
          this->History[i] = new Type[N];
       }
       K = (double **) malloc(N*sizeof(double *));
       for (int i = 0; i < N; i++)
           K[i] = (double *) malloc(N*sizeof(double));
       K1 = K2 = NULL;
       C = (double **) malloc(N*sizeof(double *));
       for (int i = 0; i < N; i++)
           C[i] = (double *) malloc(refs.size()*sizeof(double));
       C1 = C2 = NULL;
       nstart = (int *) malloc(N*sizeof(int));
       nend = (int *) malloc(N*sizeof(int));
       if (hasB)
          B = (double *) malloc(N*sizeof(double));
       else
          B = NULL;
       B1 = B2 = NULL;
       iRow = new int[this->MaxP];
       A = new long double[this->MaxP*this->MaxP];
       LU = new long double[this->MaxP*this->MaxP];
       Y = new long double[this->MaxP];
       X = new long double[this->MaxP];
    };
    virtual void use_parameter(double k) {
       if (this->K1 != NULL && this->K2 != NULL && this->C1 != NULL && this->C2 != NULL) {
          if (this->hasB) {
             use(this->N, k, this->B, this->B1, this->B2);
          }
          for (int i = 0; i < this->N; i++) {
              use(this->N, k, this->K[i], this->K1[i], this->K2[i]);
              use(this->refs.size(), k, this->C[i], this->C1[i], this->C2[i]);
          }
       }
    }
    virtual void parametrize(double k1, _funnel<Type> * _d2, double k2) {
       _funnel_perceptron<Type> * d2 = reinterpret_cast<_funnel_perceptron<Type> *>(_d2);
       if (this->K1 == NULL && this->K2 == NULL && this->C1 == NULL && this->C2 == NULL) {
          this->K1 = (double **) malloc(this->N*sizeof(double *));
          for (int i = 0; i < this->N; i++)
              this->K1[i] = (double *) malloc(this->N*sizeof(double));
          this->K2 = (double **) malloc(this->N*sizeof(double *));
          for (int i = 0; i < this->N; i++)
              this->K2[i] = (double *) malloc(this->N*sizeof(double));
          this->C1 = (double **) malloc(this->N*sizeof(double *));
          for (int i = 0; i < this->N; i++)
              this->C1[i] = (double *) malloc(this->refs.size()*sizeof(double));
          this->C2 = (double **) malloc(this->N*sizeof(double *));
          for (int i = 0; i < this->N; i++)
              this->C2[i] = (double *) malloc(this->refs.size()*sizeof(double));
          if (this->hasB) {
             this->B1 = (double *) malloc(this->N*sizeof(double));
             this->B2 = (double *) malloc(this->N*sizeof(double));
          }
       }
       this->Calculated = true;
       if (this->hasB) {
          analyze(this->N, k1, this->B, k2, d2->B, this->B1, this->B2);
       }
       for (int i = 0; i < this->N; i++) {
           analyze(this->N, k1, this->K[i], k2, d2->K[i], this->K1[i], this->K2[i]);
           analyze(this->refs.size(), k1, this->C[i], k2, d2->C[i], this->C1[i], this->C2[i]);
       }
    }
    virtual bool predict(bool use_top) {
       bool result = false;
       if (!this->Calculated && this->Depth == this->MaxDepth) {
           this->Calculated = calc_predictor(use_top);
       }
       if (this->Calculated) {
           apply_predictor(use_top);
           result = true;
       }
       if (result) this->HasPredicted = true;
       return result;
    };
    virtual void correct() {
       omp_set_lock(&this->Lock);
       if (this->Calculated && this->HasPredicted) {
           double eps = 0.0;
           int nn = 0;
           for (int i = 0; i < this->N; i++)
			   if (!this->Mask || this->Mask[i]) {
				   if (this->Data[i] != (Type) 0.0) {
					   eps += fabs(1.0*(this->Predicted[i] - this->Data[i]) / this->Data[i]);
					   nn++;
				   }
			   }
           if (nn > 0) eps /= nn;
           if (eps > this->rel_eps)
              this->Calculated = false;
       }
       omp_unset_lock(&this->Lock);
    };
    virtual void LOCK() {
       omp_set_lock(&this->Lock);
       for (unsigned int j = 0; j < this->refs.size(); j++) {
           _funnel_with_history<Type> * REF = reinterpret_cast<_funnel_with_history<Type> *>(this->refs[j]);
           omp_set_lock(&(REF->Lock));
       }
    }
    virtual void UNLOCK() {
       omp_unset_lock(&this->Lock);
       for (unsigned int j = 0; j < this->refs.size(); j++) {
           _funnel_with_history<Type> * REF = reinterpret_cast<_funnel_with_history<Type> *>(refs[j]);
           omp_unset_lock(&(REF->Lock));
       }
    }
    virtual ~_funnel_perceptron() {
       for (int i = 0; i < this->N; i++)
           free((void *) K[i]);
       free((void *) K);
       if (K1) {
          for (int i = 0; i < this->N; i++)
              free((void *) K1[i]);
          free((void *) K1);
       }
       if (K2) {
          for (int i = 0; i < this->N; i++)
              free((void *) K2[i]);
          free((void *) K2);
       }
       for (int i = 0; i < this->N; i++)
           free((void *) C[i]);
       free((void *) C);
       if (C1) {
          for (int i = 0; i < this->N; i++)
              free((void *) C1[i]);
          free((void *) C1);
       }
       if (C2) {
          for (int i = 0; i < this->N; i++)
              free((void *) C2[i]);
          free((void *) C2);
       }
       if (hasB) {
          free((void *) B);
          free((void *) B1);
          free((void *) B2);
       }
       free((void *) nstart);
       free((void *) nend);
       delete[] iRow;
       delete[] A;
       delete[] LU;
       delete[] Y;
       delete[] X;
    };
 };
 template<class Type>
  class _funnel_explicit_perceptron: public _funnel_perceptron<Type> {
  protected:
    virtual bool calc_predictor(bool use_top) {
       int corr = use_top ? 0 : 1;
       int P1 = this->PATTERN + 1;
       int P2 = this->N - this->PATTERN - 2;
       vector<int> Qs;
       if (this->PATTERN < 0 || 2*this->N <= this->PATTERN) {
          for (int i = 0; i < this->N; i++)
              Qs.push_back(i);
       } else {
          Qs.push_back(P1);
          Qs.push_back(P2);
          for (int i = 0; i <= this->PATTERN; i++) {
              Qs.push_back(i);
              Qs.push_back(this->N - i - 1);
          }
       }
	   for (unsigned int q = 0; q < this->N; q++) {
		   this->nstart[q] = -1;
		   this->nend[q] = -1;
	   }
       for (unsigned int qs = 0; qs < Qs.size(); qs++) {
           int q = Qs[qs];
		   if (this->Mask && !this->Mask[q])
			   continue;
           double max_err = 1E300;
           int bb = this->hasB ? 1 : 0;
           vector<int> Ps;
           vector<int> referers;
           int ND = this->MaxDepth - corr; 
           for (int j = 0; j < this->refs.size(); j++) {
               _funnel_with_history<Type> * REF = reinterpret_cast<_funnel_with_history<Type> *>(this->refs[j]);
               int _corr = (REF->State & tnlValue) ? 2 : 1;
               int D = REF->getMaxDepth();
               if (D - _corr < ND) ND = D - _corr;
           }
           double avr = 0.0;
           for (int k = 1; k < ND; k++) {
               avr +=this->History[k + (this->MaxDepth - corr) - ND - 1][q];
           }
           avr /= (ND - 1);
           double sumq = 0.0;
           for (int k = 1; k < ND; k++) {
               sumq += pow(this->History[k + (this->MaxDepth - corr) - ND - 1][q] - avr, 2);
           }
           for (int i = 0; i < this->refs.size(); i++) {
               _funnel_with_history<Type> * REF = reinterpret_cast<_funnel_with_history<Type> *>(this->refs[i]);
               int _corr = (REF->State & tnlValue) ? 2 : 1;
               Type ** H = REF->getHistory();
               int D = REF->getMaxDepth();
               double ravr = 0.0;
               for (int k = 1; k < ND; k++) {
                   ravr += H[k + D - ND - _corr][q];
               }
               ravr /= (ND - 1);
               double nominator = 0.0;
               double denominator = 0.0;
               for (int k = 1; k < ND; k++) {
                  nominator += (this->History[k + (this->MaxDepth - corr) - ND - 1][q] - avr)*(H[k + D - ND - _corr][q] - ravr);
                  denominator += pow(H[k + D - ND - _corr][q] - ravr, 2);
               }
               denominator = sqrt(sumq*denominator);
               if (fabs(nominator) > 0.01*fabs(denominator))
                  referers.push_back(i);
           }
           for (int i = (this->PATTERN < 0 ? this->N : __min(this->N, this->PATTERN)) + referers.size() + bb; i > referers.size() + 3 + bb; ) {
               Ps.push_back(i);
               if ((i - referers.size() - bb) % 2 == 0)
                  i--;
               else
                  i -= 2;
           }
           for (int i = (this->PATTERN < 0 ? 3 : this->PATTERN) + bb; i >= 1 + bb; i--)
               Ps.push_back(referers.size() + i);
           this->nstart[q] = -1;
           this->nend[q] = -1;
           for (unsigned int pp = 0; pp < Ps.size(); pp++) {
               int NN = Ps[pp] - referers.size() - bb;
               memset(this->A, 0, this->MaxP*this->MaxP*sizeof(long double));
               memset(this->Y, 0, this->MaxP*sizeof(long double));
               int start = NN == 0 ? q : (q - (NN-1)/2 < 0 ? 0 : q - (NN-1)/2);
               int end = NN == 0 ? q-1 : (q + (NN-1)/2 >= this->N ? this->N-1 : q + (NN-1)/2);
               NN = (end - start) + 1;
               int ND = this->MaxDepth - corr; 
               for (int j = 0; j < referers.size(); j++) {
                   _funnel_with_history<Type> * REF = reinterpret_cast<_funnel_with_history<Type> *>(this->refs[referers[j]]);
                   int _corr = (REF->State & tnlValue) ? 2 : 1;
                   int D = REF->getMaxDepth();
                   if (D - _corr < ND) ND = D - _corr;
               }
               int ptr = 0;
               for (int i = 0; i < NN; i++) {
                   for (int j = 0; j < NN; j++, ptr++) {
                       this->A[ptr] = 0.0;
                       for (int k = this->MaxDepth - corr - ND + 1; k < this->MaxDepth - corr; k++)
                           this->A[ptr] +=this->History[k-1][start + i]*this->History[k-1][start + j];
                   }
                   this->Y[i] = 0.0;
                   if (this->hasB) this->A[ptr] = 0.0;
                   for (int k = this->MaxDepth - corr - ND + 1; k < this->MaxDepth - corr; k++) {
                       if (this->hasB) this->A[ptr] -=this->History[k-1][start + i];
                       this->Y[i] -= this->History[k-1][start + i]*this->History[k][q];
                   }
                   if (this->hasB) ptr++;
                   for (int j = 0; j < referers.size(); j++, ptr++) {
                       _funnel_with_history<Type> * REF = reinterpret_cast<_funnel_with_history<Type> *>(this->refs[referers[j]]);
                       int _corr = (REF->State & tnlValue) ? 2 : 1;
                       Type ** H = REF->getHistory();
                       int D = REF->getMaxDepth();
                       this->A[ptr] = 0.0;
                       for (int k = 1; k < ND; k++) {
                           this->A[ptr] +=this->History[k + (this->MaxDepth - corr) - ND - 1][start + i]*H[k + D - ND - _corr][q];
                       }
                   }
               }
               if (this->hasB) {
                  for (int j = 0; j < NN; j++, ptr++) {
                      this->A[ptr] = 0.0;
                      for (int k = this->MaxDepth - corr - ND + 1; k < this->MaxDepth - corr; k++)
                          this->A[ptr] += -this->History[k-1][start + j];
                  }
                  this->A[ptr] = 0.0;
                  this->Y[NN] = 0.0;
                  for (int k = this->MaxDepth - corr - ND + 1; k < this->MaxDepth - corr; k++) {
                      this->A[ptr] -= -1;
                      this->Y[NN] +=this->History[k][q];
                  }
                  ptr++;
                  for (int j = 0; j < referers.size(); j++, ptr++) {
                      _funnel_with_history<Type> * REF = reinterpret_cast<_funnel_with_history<Type> *>(this->refs[referers[j]]);
                      int _corr = (REF->State & tnlValue) ? 2 : 1;
                      Type ** H = REF->getHistory();
                      int D = REF->getMaxDepth();
                      this->A[ptr] = 0.0;
                      for (int k = 1; k < ND; k++) {
                          this->A[ptr] += -H[k + D - ND - _corr][q];
                      }
                  }
               }
               for (int i = 0; i < referers.size(); i++) {
                   _funnel_with_history<Type> * __REF = reinterpret_cast<_funnel_with_history<Type> *>(this->refs[referers[i]]);
                   int __corr = (__REF->State & tnlValue) ? 2 : 1;
                   Type ** __H = __REF->getHistory();
                   int __D = __REF->getMaxDepth();
                   for (int j = 0; j < NN; j++, ptr++) {
                       this->A[ptr] = 0.0;
                       for (int k = this->MaxDepth - corr - ND + 1, ck = __D - ND - __corr + 1; k < this->MaxDepth - corr; k++, ck++)
                           this->A[ptr] += __H[ck][q]*this->History[k - 1][start + j];
                   }
                   if (this->hasB) this->A[ptr] = 0.0;
                   this->Y[NN+i+bb] = 0.0;
                   for (int k = 1; k < ND; k++) {
                       if (this->hasB) this->A[ptr] -= __H[k + __D - ND - __corr][q];
                       this->Y[NN+i+bb] -= __H[k + __D - ND - __corr][q]*this->History[k + (this->MaxDepth - corr) - ND][q];
                   }
                   if (this->hasB) ptr++;
                   for (int j = 0; j < referers.size(); j++, ptr++) {
                       _funnel_with_history<Type> * REF = reinterpret_cast<_funnel_with_history<Type> *>(this->refs[referers[j]]);
                       int _corr = (REF->State & tnlValue) ? 2 : 1;
                       Type ** H = REF->getHistory();
                       int D = REF->getMaxDepth();
                       this->A[ptr] = 0.0;
                       for (int k = 1, ck = __D - ND - __corr + 1; k < ND; k++, ck++) {
                           this->A[ptr] += __H[ck][q]*H[k + D - ND - _corr][q];
                       }
                   }
               }
               bool result = (!this->useLU && _SolveGaussZeidel(NN+referers.size()+bb, this->iRow, this->A, this->LU, this->Y, this->X)) || _GetLU(NN+referers.size()+bb, this->iRow, this->A, this->LU) && _SolveLU(NN+referers.size()+bb, this->iRow, this->LU, this->Y, this->X);
               if (result) {
                  for (int i = 0, ptr = 0; result && i < NN + referers.size() + bb; i++) {
                      double val = 0.0;
                      for (int j = 0; result && j < NN + referers.size() + bb; j++, ptr++) {
                          if (this->X[j] != this->X[j]) result = false;
                          val += this->A[ptr]*this->X[j];
                      }
                      double r = fabs(val - this->Y[i]);
                      if (r != r || r > 1E-7)
                         result = false;
                  }
                  double cur_err = 1E300;
                  if (result) {
                     int cur_n = 0;
                     cur_err = 0.0;
                     for (int ii = 1; result && ii < ND; ii++) {
                         int i = this->MaxDepth - ND - corr + ii;
                         double val = 0.0;
                         for (int j = 0; j < NN; j++)
                             val += this->X[j]*((double) this->History[i - 1][start + j]);
                         if (this->hasB) val -= this->X[NN];
                         for (unsigned int j = 0; j < referers.size(); j++) {
                             _funnel_with_history<Type> * REF = reinterpret_cast<_funnel_with_history<Type> *>(this->refs[referers[j]]);
                             int _corr = (REF->State & tnlValue) ? 2 : 1;
                             Type ** H = REF->getHistory();
                             int D = REF->getMaxDepth();
                             val += this->X[NN+bb+j]*((long double) H[D - ND - _corr + ii][q]);
                         }
                         Type H = - (Type)this->History[i][q];
                         if (H != 0) {
                            cur_err += fabs(1.0*(H - (Type) val)/H);
                            cur_n++;
                         }
                     }
                     if (cur_n > 0) cur_err /= cur_n;
                  }
                  if (result) {
                     if (cur_err < this->rel_eps && cur_err <= max_err) {
                         this->nstart[q] = start;
                         this->nend[q] = end;
                         int ptr = 0;
                         for (int i = 0; i < NN; i++, ptr++)
                             this->K[q][i] = (double) this->X[ptr];
                         if (this->hasB) this->B[q] = (double) this->X[ptr++];
                         memset((void *) this->C[q], 0, this->refs.size()*sizeof(double));
                         for (int i = 0; i < referers.size(); i++, ptr++)
                             this->C[q][referers[i]] = (double) this->X[ptr];
                         max_err = cur_err;
                         result = pp == Ps.size() - 1;
                     }
                  }
               }
           }
       }
       if (this->PATTERN >= 0 && 2*this->N > this->PATTERN) {
          if (this->nstart[P1] >= 0 && this->nend[P1] >= 0 && this->nstart[P2] >= 0 && this->nend[P2] >= 0 &&
              this->nend[P1]-this->nstart[P1] == this->nend[P2]-this->nstart[P2] &&
              this->nend[P2]-this->nstart[P2]+1 == this->PATTERN) {
             for (int j = this->PATTERN + 1; j < this->N - this->PATTERN - 1; j++) {
                 if (j != P1 && j != P2) {
                    this->nstart[j] = j - this->PATTERN/2;
                    this->nend[j] = j + this->PATTERN/2;
                    for (int i = 0; i < this->PATTERN; i++)
                        this->K[j][i] = 0.5*(this->K[P1][i] + this->K[P2][i]);
                    if (this->hasB) this->B[j] = 0.5*(this->B[P1] + this->B[P2]);
                    memset((void *) this->C[j], 0, this->refs.size()*sizeof(double));
                    for (int i = 0; i < this->refs.size(); i++)
                        this->C[j][i] = 0.5*(this->C[P1][i] + this->C[P2][i]);
                 }
             }
          } else
             for (int i = this->PATTERN + 1; i < this->N - this->PATTERN - 1; i++) {
                 this->nstart[i] = -1;
                 this->nend[i] = -1;
             }
       }
       return true;
    };
    virtual void apply_predictor(bool use_top) {
       int corr = use_top ? 0 : 1;
       int np = omp_get_num_procs();
       #pragma omp parallel for schedule(static,__max(1,this->N/np)) if (this->N>100) num_threads(np)
       for (int i = 0; i < this->N; i++) {
           int start = this->nstart[i];
           int end = this->nend[i];
           if (start == -1 || end == -1)
              this->Predicted[i] = (Type)this->History[this->MaxDepth - corr - 1][i];
           else {
              int NN = end - start + 1;
              int ptr = 0;
              double val = 0.0;
              for (int j = 0; j < NN; j++)
                  val += this->K[i][j]*((double) this->History[this->MaxDepth - corr - 1][start + j]);
              if (this->hasB) val -= this->B[i];
              for (unsigned int j = 0; j < this->refs.size(); j++) {
                  _funnel_with_history<Type> * REF = reinterpret_cast<_funnel_with_history<Type> *>(this->refs[j]);
                  int _corr = (REF->State & tnlValue) ? 1 : 0;
                  Type ** H = REF->getHistory();
                  int D = REF->getMaxDepth();
                  val += this->C[i][j]*((long double) H[D - _corr - 1][i]);
              }
              this->Predicted[i] = - (Type) val;
           }
       }
    };
  public:
    _funnel_explicit_perceptron(bool hasB, const vector<_funnel<Type> *> &refs, int N = 1, double rel_eps = 0.001, const char * Name = NULL, int PATTERN = -1): _funnel_perceptron<Type>(hasB, refs, N, rel_eps, Name, PATTERN) {
    };
 };
 template<class Type>
  class _funnel_implicit_perceptron: public _funnel_perceptron<Type> {
  protected:
    virtual bool calc_predictor(bool use_top) {
       int corr = use_top ? 0 : 1;
       int P1 = this->PATTERN + 1;
       int P2 = this->N - this->PATTERN - 2;
       vector<int> Qs;
       if (this->PATTERN < 0 || 2*this->N <= this->PATTERN) {
          for (int i = 0; i < this->N; i++)
              Qs.push_back(i);
       } else {
          Qs.push_back(P1);
          Qs.push_back(P2);
          for (int i = 0; i <= this->PATTERN; i++) {
              Qs.push_back(i);
              Qs.push_back(this->N - i - 1);
          }
       }
	   for (unsigned int q = 0; q < this->N; q++) {
		   this->nstart[q] = -1;
		   this->nend[q] = -1;
	   }
	   for (unsigned int qs = 0; qs < Qs.size(); qs++) {
		   int q = Qs[qs];
		   if (this->Mask && !this->Mask[q])
			   continue;
           double max_err = 1E300;
           int bb = this->hasB ? 1 : 0;
           vector<int> Ps;
           vector<int> referers;
           int ND = this->MaxDepth - corr; 
           for (int j = 0; j < this->refs.size(); j++) {
               _funnel_with_history<Type> * REF = reinterpret_cast<_funnel_with_history<Type> *>(this->refs[j]);
               int _corr = (REF->State & tnlValue) ? 2 : 1;
               int D = REF->getMaxDepth();
               if (D - _corr < ND) ND = D - _corr;
           }
           double avr = 0.0;
           for (int k = 1; k < ND; k++) {
               avr +=this->History[k + (this->MaxDepth - corr) - ND - 1][q];
           }
           avr /= (ND - 1);
           double sumq = 0.0;
           for (int k = 1; k < ND; k++) {
               sumq += pow(this->History[k + (this->MaxDepth - corr) - ND - 1][q] - avr, 2);
           }
           for (int i = 0; i < this->refs.size(); i++) {
               _funnel_with_history<Type> * REF = reinterpret_cast<_funnel_with_history<Type> *>(this->refs[i]);
               int _corr = (REF->State & tnlValue) ? 2 : 1;
               Type ** H = REF->getHistory();
               int D = REF->getMaxDepth();
               double ravr = 0.0;
               for (int k = 1; k < ND; k++) {
                   ravr += H[k + D - ND - _corr][q];
               }
               ravr /= (ND - 1);
               double nominator = 0.0;
               double denominator = 0.0;
               for (int k = 1; k < ND; k++) {
                  nominator += (this->History[k + (this->MaxDepth - corr) - ND - 1][q] - avr)*(H[k + D - ND - _corr][q] - ravr);
                  denominator += pow(H[k + D - ND - _corr][q] - ravr, 2);
               }
               denominator = sqrt(sumq*denominator);
               if (fabs(nominator) > 0.01*fabs(denominator))
                  referers.push_back(i);
           }
           for (int i = (this->PATTERN < 0 ? this->N : __min(this->N, this->PATTERN)) + referers.size() + bb; i > referers.size() + 3 + bb; ) {
               Ps.push_back(i);
               if ((i - referers.size() - bb) % 2 == 0)
                  i--;
               else
                  i -= 2;
           }
           for (int i = (this->PATTERN < 0 ? 3 : this->PATTERN) + bb; i >= 1 + bb; i--)
               Ps.push_back(referers.size() + i);
           this->nstart[q] = -1;
           this->nend[q] = -1;
           for (unsigned int pp = 0; pp < Ps.size(); pp++) {
               int NN = Ps[pp] - referers.size() - bb;
               memset(this->A, 0, this->MaxP*this->MaxP*sizeof(long double));
               memset(this->Y, 0, this->MaxP*sizeof(long double));
               int start = NN == 0 ? q : (q - (NN-1)/2 < 0 ? 0 : q - (NN-1)/2);
               int end = NN == 0 ? q-1 : (q + (NN-1)/2 >= this->N ? this->N-1 : q + (NN-1)/2);
               NN = (end - start) + 1;
               int ND = this->MaxDepth - corr; 
               for (int j = 0; j < referers.size(); j++) {
                   _funnel_with_history<Type> * REF = reinterpret_cast<_funnel_with_history<Type> *>(this->refs[referers[j]]);
                   int _corr = (REF->State & tnlValue) ? 2 : 1;
                   int D = REF->getMaxDepth();
                   if (D - _corr < ND) ND = D - _corr;
               }
               int ptr = 0;
               for (int i = 0; i < NN; i++) {
                   for (int j = 0; j < NN; j++, ptr++) {
                       this->A[ptr] = 0.0;
                       for (int k = this->MaxDepth - corr - ND + 1; k < this->MaxDepth - corr; k++)
                           this->A[ptr] += this->History[k][start + i]*this->History[k][start + j];
                   }
                   this->Y[i] = 0.0;
                   if (this->hasB) this->A[ptr] = 0.0;
                   for (int k = this->MaxDepth - corr - ND + 1; k < this->MaxDepth - corr; k++) {
                       if (this->hasB) this->A[ptr] -= this->History[k][start + i];
                       this->Y[i] -= this->History[k][start + i]*this->History[k-1][q];
                   }
                   if (this->hasB) ptr++;
                   for (int j = 0; j < referers.size(); j++, ptr++) {
                       _funnel_with_history<Type> * REF = reinterpret_cast<_funnel_with_history<Type> *>(this->refs[referers[j]]);
                       int _corr = (REF->State & tnlValue) ? 2 : 1;
                       Type ** H = REF->getHistory();
                       int D = REF->getMaxDepth();
                       this->A[ptr] = 0.0;
                       for (int k = 1; k < ND; k++) {
                           this->A[ptr] += this->History[k + (this->MaxDepth - corr) - ND][start + i]*H[k + D - ND - _corr][q];
                       }
                   }
               }
               if (this->hasB) {
                  for (int j = 0; j < NN; j++, ptr++) {
                      this->A[ptr] = 0.0;
                      for (int k = this->MaxDepth - corr - ND + 1; k < this->MaxDepth - corr; k++)
                          this->A[ptr] += - this->History[k][start + j];
                  }
                  this->A[ptr] = 0.0;
                  this->Y[NN] = 0.0;
                  for (int k = this->MaxDepth - corr - ND + 1; k < this->MaxDepth - corr; k++) {
                      this->A[ptr] -= -1;
                      this->Y[NN] += this->History[k-1][q];
                  }
                  ptr++;
                  for (int j = 0; j < referers.size(); j++, ptr++) {
                      _funnel_with_history<Type> * REF = reinterpret_cast<_funnel_with_history<Type> *>(this->refs[referers[j]]);
                      int _corr = (REF->State & tnlValue) ? 2 : 1;
                      Type ** H = REF->getHistory();
                      int D = REF->getMaxDepth();
                      this->A[ptr] = 0.0;
                      for (int k = 1; k < ND; k++) {
                          this->A[ptr] += -H[k + D - ND - _corr][q];
                      }
                  }
               }
               for (int i = 0; i < referers.size(); i++) {
                   _funnel_with_history<Type> * __REF = reinterpret_cast<_funnel_with_history<Type> *>(this->refs[referers[i]]);
                   int __corr = (__REF->State & tnlValue) ? 2 : 1;
                   Type ** __H = __REF->getHistory();
                   int __D = __REF->getMaxDepth();
                   for (int j = 0; j < NN; j++, ptr++) {
                       this->A[ptr] = 0.0;
                       for (int k = this->MaxDepth - corr - ND + 1, ck = __D - ND - __corr + 1; k < this->MaxDepth - corr; k++, ck++)
                           this->A[ptr] += __H[ck][q]*this->History[k][start + j];
                   }
                   if (this->hasB) this->A[ptr] = 0.0;
                   this->Y[NN+i+bb] = 0.0;
                   for (int k = 1; k < ND; k++) {
                       if (this->hasB) this->A[ptr] -= __H[k + __D - ND - __corr][q];
                       this->Y[NN+i+bb] -= __H[k + __D - ND - __corr][q]*this->History[k + (this->MaxDepth - corr) - ND - 1][q];
                   }
                   if (this->hasB) ptr++;
                   for (int j = 0; j < referers.size(); j++, ptr++) {
                       _funnel_with_history<Type> * REF = reinterpret_cast<_funnel_with_history<Type> *>(this->refs[referers[j]]);
                       int _corr = (REF->State & tnlValue) ? 2 : 1;
                       Type ** H = REF->getHistory();
                       int D = REF->getMaxDepth();
                       this->A[ptr] = 0.0;
                       for (int k = 1, ck = __D - ND - __corr + 1; k < ND; k++, ck++) {
                           this->A[ptr] += __H[ck][q]*H[k + D - ND - _corr][q];
                       }
                   }
               }
               bool result = (!this->useLU && _SolveGaussZeidel(NN+referers.size()+bb, this->iRow, this->A, this->LU, this->Y, this->X)) || _GetLU(NN+referers.size()+bb, this->iRow, this->A, this->LU) && _SolveLU(NN+referers.size()+bb, this->iRow, this->LU, this->Y, this->X);
               if (result) {
                  for (int i = 0, ptr = 0; result && i < NN + referers.size() + bb; i++) {
                      double val = 0.0;
                      for (int j = 0; result && j < NN + referers.size() + bb; j++, ptr++) {
                          if (this->X[j] != this->X[j]) result = false;
                          val += this->A[ptr]*this->X[j];
                      }
                      double r = fabs(val - this->Y[i]);
                      if (r != r || r > 1E-7)
                         result = false;
                  }
                  double cur_err = 1E300;
                  if (result) {
                     int cur_n = 0;
                     cur_err = 0.0;
                     for (int ii = 1; result && ii < ND; ii++) {
                         int i = this->MaxDepth - ND - corr + ii;
                         double val = 0.0;
                         for (int j = 0; j < NN; j++)
                             val += this->X[j]*((double) this->History[i][start + j]);
                         if (this->hasB) val -= this->X[NN];
                         for (unsigned int j = 0; j < referers.size(); j++) {
                             _funnel_with_history<Type> * REF = reinterpret_cast<_funnel_with_history<Type> *>(this->refs[referers[j]]);
                             int _corr = (REF->State & tnlValue) ? 2 : 1;
                             Type ** H = REF->getHistory();
                             int D = REF->getMaxDepth();
                             val += this->X[NN+bb+j]*((long double) H[D - ND - _corr + ii][q]);
                         }
                         Type H = - (Type)this->History[i - 1][q];
                         if (H != 0) {
                            cur_err += fabs(1.0*(H - (Type) val)/H);
                            cur_n++;
                         }
                     }
                     if (cur_n > 0) cur_err /= cur_n;
                  }
                  if (result) {
                     if (cur_err < this->rel_eps && cur_err <= max_err) {
                         this->nstart[q] = start;
                         this->nend[q] = end;
                         int ptr = 0;
                         for (int i = 0; i < NN; i++, ptr++)
                             this->K[q][i] = (double) this->X[ptr];
                         if (this->hasB) this->B[q] = (double) this->X[ptr++];
                         memset((void *) this->C[q], 0, this->refs.size()*sizeof(double));
                         for (int i = 0; i < referers.size(); i++, ptr++)
                             this->C[q][referers[i]] = (double) this->X[ptr];
                         max_err = cur_err;
                         result = pp == Ps.size() - 1;
                     }
                  }
               }
           }
       }
       if (this->PATTERN >= 0 && 2*this->N > this->PATTERN) {
          if (this->nstart[P1] >= 0 && this->nend[P1] >= 0 && this->nstart[P2] >= 0 && this->nend[P2] >= 0 &&
              this->nend[P1]-this->nstart[P1] == this->nend[P2]-this->nstart[P2] &&
              this->nend[P2]-this->nstart[P2]+1 == this->PATTERN) {
             for (int j = this->PATTERN + 1; j < this->N - this->PATTERN - 1; j++) {
                 if (j != P1 && j != P2) {
                    this->nstart[j] = j - this->PATTERN/2;
                    this->nend[j] = j + this->PATTERN/2;
                    for (int i = 0; i < this->PATTERN; i++)
                        this->K[j][i] = 0.5*(this->K[P1][i] + this->K[P2][i]);
                    if (this->hasB) this->B[j] = 0.5*(this->B[P1] + this->B[P2]);
                    memset((void *) this->C[j], 0, this->refs.size()*sizeof(double));
                    for (int i = 0; i < this->refs.size(); i++)
                        this->C[j][i] = 0.5*(this->C[P1][i] + this->C[P2][i]);
                 }
             }
          } else
             for (int i = this->PATTERN + 1; i < this->N - this->PATTERN - 1; i++) {
                 this->nstart[i] = -1;
                 this->nend[i] = -1;
             }
       }
       return true;
    };
    virtual void apply_predictor(bool use_top) {
       int corr = use_top ? 0 : 1;
       int np = omp_get_num_procs();
       memset(this->A, 0, this->MaxP*this->MaxP*sizeof(long double));
       memset(this->Y, 0, this->MaxP*sizeof(long double));
       #pragma omp parallel for schedule(static,__max(1,this->N/np)) num_threads(np) if (this->N>100)
       for (int p = 0; p < this->N; p++) {
           int start = this->nstart[p];
           int end = this->nend[p];
           if (start == -1 || end == -1) {
              this->A[p*this->N + p] = 1.0;
              this->Y[p] = (Type)this->History[this->MaxDepth - corr - 1][p];
           } else {
              int NN = end - start + 1;
              for (int k = 0, ptr = p*this->N + start; k < NN; k++, ptr++) {
                  this->A[ptr] = (long double) this->K[p][k];
              }
              this->Y[p] = (this->hasB ? this->B[p] : 0.0) - (long double)this->History[this->MaxDepth - corr - 1][p];
              for (unsigned int j = 0; j < this->refs.size(); j++) {
                  _funnel_with_history<Type> * REF = reinterpret_cast<_funnel_with_history<Type> *>(this->refs[j]);
                  int _corr = (REF->State & tnlValue) ? 1 : 0;
                  Type ** H = REF->getHistory();
                  int D = REF->getMaxDepth();
                  this->Y[p] -= this->C[p][j]*((long double) H[D - _corr - 1][p]);
              }
           }
       }
       bool result = (!this->useLU && _SolveGaussZeidel(this->N, this->iRow, this->A, this->LU, this->Y, this->X)) || _GetLU(this->N, this->iRow, this->A, this->LU) && _SolveLU(this->N, this->iRow, this->LU, this->Y, this->X);
       for (int i = 0; result && i < this->N; i++)
           if (this->X[i] != this->X[i])
              result = false;
       if (result) {
          for (int i = 0; i < this->N; i++) {
              this->Predicted[i] = (Type) this->X[i];
          }
       } else {
          for (int i = 0; i < this->N; i++) {
              this->Predicted[i] = (Type)this->History[this->MaxDepth - corr - 1][i];
          }
       }
    };
  public:
    _funnel_implicit_perceptron(bool hasB, const vector<_funnel<Type> *> &refs, int N = 1, double rel_eps = 0.001, const char * Name = NULL, int PATTERN = -1): _funnel_perceptron<Type>(hasB, refs, N, rel_eps, Name, PATTERN) {
    };
 };
 template<class Type>
  class funneled_base {
  private:
    _funnel<Type> * Ref;
  protected:
    virtual void init_data(__funnel * _Ref) = 0;
  public:
    virtual void wait() = 0;
    _funnel<Type> * getRef(const vector<_funnel<Type> *> * _refs = NULL) {
       if (Ref) Ref->add_refs(_refs);
       return Ref;
    };
    void setRef(_funnel<Type> * _Ref) {
      Ref = _Ref;
      if (Ref) {
         omp_set_lock(&Ref->Lock);
         Ref->Refs++;
         omp_unset_lock(&Ref->Lock);
      }
    };
    bool empty() {
      if (Ref) {
         bool result;
         omp_set_lock(&Ref->Lock);
         result = !(Ref->State & tnlValue);
         omp_unset_lock(&Ref->Lock);
         return result;
      } else
         return true;
    };
    bool ready() {
      if (Ref) {
         bool result;
         omp_set_lock(&Ref->Lock);
         result = (Ref->State & tnlHasIn) && (Ref->State & tnlHasOut);
         omp_unset_lock(&Ref->Lock);
         return result;
      } else
         return false;
    };
    void cancel(bool lock = true) {
      if (Ref) {
         if (lock) omp_set_lock(&Ref->Lock);
         Ref->State &= ~tnlValue;
         if (lock) omp_unset_lock(&Ref->Lock);
      }
    }
  };
 template<class Type>
  class funneled_out;
 template<class Type>
  class funneled_in: public funneled_base<Type> {
    friend class funneled_out<Type>;
  protected:
    virtual void init_data(__funnel * _Ref) {
       this->setRef(reinterpret_cast<_funnel<Type> *>(_Ref));
       omp_set_lock(&_Ref->Lock);
       if (_Ref->State & tnlHasIn) {
          cout<<"Funnel already has input"<<endl;
          exit(-1);
       }
       _Ref->State |= tnlHasIn;
       omp_unset_lock(&_Ref->Lock);
    };
  public:
    funneled_in(): funneled_in((void *)NULL) { };
    funneled_in(void * _Ref) {
       this->init_data(_Ref ? ((funneled_out<Type> *) _Ref)->getRef() : new _funnel<Type>(1));
    };
    funneled_in(int N) {
       this->init_data(new _funnel<Type>(N));
    }
    funneled_in(const char * Name, int N = 1) {
       omp_set_lock(&__funnel_lock__);
       map<string,__funnel *>::iterator itFunnels = __Funnels.find(Name);
       if (itFunnels == __Funnels.end()) {
          __funnel * funnel = new _funnel<Type>(N, Name);
          this->init_data(funnel);
          __Funnels[Name] = funnel;
       } else {
          this->init_data(itFunnels->second);
       }
       omp_unset_lock(&__funnel_lock__);
    }
    virtual ~funneled_in() {
       _funnel<Type> * Ref = this->getRef();
       if (Ref) {
          omp_set_lock(&Ref->Lock);
          while (Ref->State & tnlValue) {
             omp_unset_lock(&Ref->Lock);
             _Yield();
             omp_set_lock(&Ref->Lock);
          }
          Ref->State &= ~tnlHasIn;
          Ref->Refs--;
          if (Ref->Refs == 0) {
             omp_unset_lock(&Ref->Lock);
             delete Ref;
          }
          else omp_unset_lock(&Ref->Lock);
       }
    };
    virtual void wait() {
      _funnel<Type> * Ref = this->getRef();
      if (Ref) {
         omp_set_lock(&Ref->Lock);
         while (!(Ref->State & tnlHasOut)) {
           omp_unset_lock(&Ref->Lock);
           _Yield();
           omp_set_lock(&Ref->Lock);
         }
      }
    };
    virtual void get(void * Buf, int SizeInBytes) {
      _funnel<Type> * Ref = this->getRef();
      if (Ref) {
         wait();
         while (!(Ref->State & tnlValue)) {
            omp_unset_lock(&Ref->Lock);
            _Yield();
            omp_set_lock(&Ref->Lock);
         }
         memmove(Buf,(void *) Ref->Data,SizeInBytes);
         Ref->State &= ~tnlValue;
         omp_unset_lock(&Ref->Lock);
      }
    };
    Type operator * () {
      Type Result;
      get(&Result,sizeof(Result));
      return Result;
    };
 };
 template<class Type>
  class funneled_predictor_out;
 template<class Type>
  class funneled_predictor_in: public funneled_in<Type> {
    friend class funneled_predictor_out<Type>;
  protected:
  public:
    funneled_predictor_in() { };
    funneled_predictor_in(int P, void * _Ref) {
       this->init_data(_Ref ? ((funneled_predictor_out<Type> *) _Ref)->getRef() : new _funnel_predictor<Type>(P));
    };
    funneled_predictor_in(int N, int P = 5, double rel_eps = 0.001) {
       this->init_data(new _funnel_predictor<Type>(P, N, rel_eps));
    }
    funneled_predictor_in(const char * Name, int N = 1, int P = 5, double rel_eps = 0.001) {
       omp_set_lock(&__funnel_lock__);
       map<string,__funnel *>::iterator itFunnels = __Funnels.find(Name);
       if (itFunnels == __Funnels.end()) {
          __funnel * funnel = new _funnel_predictor<Type>(P, N, rel_eps, Name);
          this->init_data(funnel);
          __Funnels[Name] = funnel;
       } else {
          this->init_data(itFunnels->second);
       }
       omp_unset_lock(&__funnel_lock__);
    }
    virtual void get(void * Buf, int SizeInBytes) {
      _funnel_with_history<Type> * Ref = reinterpret_cast< _funnel_with_history<Type> *>(this->getRef());
      if (Ref) {
         Ref->unset_predict_results();
         funneled_in<Type>::get(Buf, SizeInBytes);
      }
    }
    virtual void get_and_correct(void * Buf) {
      _funnel_with_history<Type> * Ref = reinterpret_cast< _funnel_with_history<Type> *>(this->getRef());
      if (Ref) {
         int SizeInBytes = Ref->getN()*sizeof(Type);
         funneled_in<Type>::get(Buf, SizeInBytes);
         Ref->correct();
         Ref->unset_predict_results();
      }
    }
    virtual void cancel_and_push(void * Buf) {
       _funnel_with_history<Type> * Ref = reinterpret_cast<_funnel_with_history<Type> *>(this->getRef());
       if (Ref) {
          wait();
          while (!(Ref->State & tnlValue)) {
             omp_unset_lock(&Ref->Lock);
             _Yield();
             omp_set_lock(&Ref->Lock);
          }
          Ref->State &= ~tnlValue;
          Ref->replace_top_history(Buf, false);
          omp_unset_lock(&Ref->Lock);
          Ref->unset_predict_results();
       }
    };
    virtual bool get_timed(void * Buf, double timeout_ms) {
      _funnel_with_history<Type> * Ref = reinterpret_cast< _funnel_with_history<Type> *>(this->getRef());
      if (Ref) {
         double t = omp_get_wtime();
         double timeout_s = 0.001*timeout_ms;
         int SizeInBytes = Ref->getN()*sizeof(Type);
         long counter = WAITING_COUNTER;
         bool prediction = true;
         wait();
         do {
            omp_unset_lock(&Ref->Lock);
            if (counter == WAITING_COUNTER) {
                double elapsed = omp_get_wtime() - t;
                if (elapsed >= timeout_s && prediction) {
                   Ref->LOCK();
                   prediction = Ref->predict(!(Ref->State & tnlValue));
                   if (prediction) {
                       memmove(Buf,(void *) Ref->getPredicted(),SizeInBytes);
                       Ref->UNLOCK();
                       return true;
                   }
                   Ref->UNLOCK();
                }
                counter = 0;
            } else
               counter++;
            _Yield();
            omp_set_lock(&Ref->Lock);
         } while (!(Ref->State & tnlValue));
         memmove(Buf,(void *) Ref->Data,SizeInBytes);
         Ref->State &= ~tnlValue;
         omp_unset_lock(&Ref->Lock);
      }
      return false;
    };
 };
 template<class Type>
  class funneled_perceptron_out;
 template<class Type>
  class funneled_perceptron_in: public funneled_predictor_in<Type> {
    friend class funneled_perceptron_out<Type>;
  protected:
  public:
    funneled_perceptron_in() { throw Exception("Empty constructor of funnel-perceptron-in called"); };
    funneled_perceptron_in(bool _explicit, bool hasB, const vector<_funnel<Type> *> &refs, int N, void * _Ref, int PATTERN = -1) {
       if (_explicit)
          this->init_data(_Ref ? ((funneled_predictor_out<Type> *) _Ref)->getRef(&refs) : new _funnel_explicit_perceptron<Type>(hasB, refs, N, 0.001, NULL, PATTERN));
       else
          this->init_data(_Ref ? ((funneled_predictor_out<Type> *) _Ref)->getRef(&refs) : new _funnel_implicit_perceptron<Type>(hasB, refs, N, 0.001, NULL, PATTERN));
    };
    funneled_perceptron_in(bool _explicit, bool hasB, const vector<_funnel<Type> *> &refs, const char * Name, int N = 1, double rel_eps = 0.001, int PATTERN = -1) {
       omp_set_lock(&__funnel_lock__);
       map<string,__funnel *>::iterator itFunnels = __Funnels.find(Name);
       if (itFunnels == __Funnels.end()) {
          __funnel * funnel = _explicit ? (__funnel *) new _funnel_explicit_perceptron<Type>(hasB, refs, N, rel_eps, Name, PATTERN) : (__funnel *) new _funnel_implicit_perceptron<Type>(hasB, refs, N, rel_eps, Name, PATTERN);
          this->init_data(funnel);
          __Funnels[Name] = funnel;
       } else {
          reinterpret_cast< _funnel_perceptron<Type> * >(itFunnels->second)->add_refs(&refs);
          this->init_data(itFunnels->second);
       }
       omp_unset_lock(&__funnel_lock__);
    }
 };
 template<class Type>
  class funneled_out: public funneled_base<Type> {
    friend class funneled_in<Type>;
  protected:
    void init_data(__funnel * _Ref) {
       this->setRef(reinterpret_cast<_funnel<Type> *>(_Ref));
       omp_set_lock(&_Ref->Lock);
       if (_Ref->State & tnlHasOut) {
          cout<<"Funnel already has output"<<endl;
          exit(-1);
       }
       _Ref->State |= tnlHasOut;
       omp_unset_lock(&_Ref->Lock);
    };
  public:
    funneled_out(): funneled_out((void *)NULL) { };
    funneled_out(void * _Ref) {
       this->init_data(_Ref ? ((funneled_in<Type> *) _Ref)->getRef() : new _funnel<Type>(1));
    };
    funneled_out(int N) {
       this->init_data(new _funnel<Type>(N));
    }
    funneled_out(const char * Name, int N = 1) {
       omp_set_lock(&__funnel_lock__);
       map<string,__funnel *>::iterator itFunnels = __Funnels.find(Name);
       if (itFunnels == __Funnels.end()) {
          __funnel * funnel = new _funnel<Type>(N, Name);
          this->init_data(funnel);
          __Funnels[Name] = funnel;
       } else {
          this->init_data(itFunnels->second);
       }
       omp_unset_lock(&__funnel_lock__);
    }
    virtual ~funneled_out() {
       _funnel<Type> * Ref = this->getRef();
       if (Ref) {
          omp_set_lock(&Ref->Lock);
          while (Ref->State & tnlValue) {
             omp_unset_lock(&Ref->Lock);
             _Yield();
             omp_set_lock(&Ref->Lock);
          }
          Ref->State &= ~tnlHasOut;
          Ref->Refs--;
          if (Ref->Refs == 0) {
             omp_unset_lock(&Ref->Lock);
             delete Ref;
          }
          else omp_unset_lock(&Ref->Lock);
       }
    };
    virtual void wait() {
      _funnel<Type> * Ref = this->getRef();
      if (Ref) {
         omp_set_lock(&Ref->Lock);
         while (!(Ref->State & tnlHasIn)) {
           omp_unset_lock(&Ref->Lock);
           _Yield();
           omp_set_lock(&Ref->Lock);
         }
      }
    };
    virtual void put(void * Buf, int SizeInBytes) {
      _funnel<Type> * Ref = this->getRef();
      if (Ref) {
         wait();
         while (Ref->State & tnlValue) {
            omp_unset_lock(&Ref->Lock);
            _Yield();
            omp_set_lock(&Ref->Lock);
         }
         if (SizeInBytes == 0)
            Ref->check_size(1);
         else
            Ref->check_size(SizeInBytes/sizeof(Type));
         memmove((void *) Ref->Data,Buf,SizeInBytes);
         Ref->State |= tnlValue;
         omp_unset_lock(&Ref->Lock);
      }
    };
    Type operator = (Type Val) {
      put(&Val,sizeof(Val));
      return Val;
    };
 };
 template<class Type>
  class funneled_predictor_out: public funneled_out<Type> {
    friend class funneled_predictor_in<Type>;
  protected:
  public:
    funneled_predictor_out() { };
    funneled_predictor_out(int P, void * _Ref) {
       this->init_data(_Ref ? ((funneled_predictor_in<Type> *) _Ref)->getRef() : new _funnel_predictor<Type>(P));
    };
    funneled_predictor_out(int N, int P = 5, double rel_eps = 0.001) {
       this->init_data(new _funnel_predictor<Type>(P, N, rel_eps));
    }
    funneled_predictor_out(const char * Name, int N = 1, int P = 5, double rel_eps = 0.001) {
       omp_set_lock(&__funnel_lock__);
       map<string,__funnel *>::iterator itFunnels = __Funnels.find(Name);
       if (itFunnels == __Funnels.end()) {
          __funnel * funnel = new _funnel_predictor<Type>(P, N, rel_eps, Name);
          this->init_data(funnel);
          __Funnels[Name] = funnel;
       } else {
          this->init_data(itFunnels->second);
       }
       omp_unset_lock(&__funnel_lock__);
    }
    virtual void put(void * Buf, int SizeInBytes) {
       _funnel_with_history<Type> * Ref = reinterpret_cast<_funnel_with_history<Type> *>(this->getRef());

      if (Ref) {
          wait();
          while (Ref->State & tnlValue) {
             omp_unset_lock(&Ref->Lock);
             _Yield();
             omp_set_lock(&Ref->Lock);
          }
          if (SizeInBytes == 0)
             Ref->check_size(1);
          else
             Ref->check_size(SizeInBytes/sizeof(Type));
          memmove((void *) Ref->Data,Buf,SizeInBytes);
          Ref->State |= tnlValue;
          Ref->push_history(false);
          omp_unset_lock(&Ref->Lock);
       }
    };
 };
 template<class Type>
  class funneled_perceptron_out: public funneled_predictor_out<Type> {
    friend class funneled_perceptron_in<Type>;
  protected:
  public:
    funneled_perceptron_out() { throw Exception("Empty constructor of funnel-perceptron-out called"); };
    funneled_perceptron_out(bool _explicit, bool hasB, const vector<_funnel<Type> *> &refs, int N, void * _Ref, int PATTERN = -1) {
       if (_explicit)
          this->init_data(_Ref ? ((funneled_predictor_in<Type> *) _Ref)->getRef(&refs) : new _funnel_explicit_perceptron<Type>(hasB, refs, N, 0.001, NULL, PATTERN));
       else
          this->init_data(_Ref ? ((funneled_predictor_in<Type> *) _Ref)->getRef(&refs) : new _funnel_implicit_perceptron<Type>(hasB, refs, N, 0.001, NULL, PATTERN));
    };
    funneled_perceptron_out(bool _explicit, bool hasB, const vector<_funnel<Type> *> &refs, const char * Name, int N = 1, double rel_eps = 0.001, int PATTERN = -1) {
       omp_set_lock(&__funnel_lock__);
       map<string,__funnel *>::iterator itFunnels = __Funnels.find(Name);
       if (itFunnels == __Funnels.end()) {
          __funnel * funnel = _explicit ? (__funnel *) new _funnel_explicit_perceptron<Type>(hasB, refs, N, rel_eps, Name, PATTERN) : (__funnel *) new _funnel_implicit_perceptron<Type>(hasB, refs, N, rel_eps, Name, PATTERN);
          this->init_data(funnel);
          __Funnels[Name] = funnel;
       } else {
          reinterpret_cast< _funnel_perceptron<Type> * >(itFunnels->second)->add_refs(&refs);
          this->init_data(itFunnels->second);
       }
       omp_unset_lock(&__funnel_lock__);
    }
 };
#ifdef __REENT_MPI__
 #define cfunnel(Dir,Type) cfunneled_##Dir<Type>
 #define cvar(Type) common_var<Type>
 omp_lock_t __cfunnel_lock__;
 class __cfunnel;
 map<string,__cfunnel *> __cFunnels;
 class __cfunnel {
  protected:
    static const int connect_tag = 1235;
    typedef struct {
      char connect[60];
      bool in;
      bool init;
      int  tag;
    } data;
  public:
    volatile int in_id;
    volatile int out_id;
    volatile int tag;
    volatile bool stopped;
    string Name;
    __cfunnel(const char * Name) {
      in_id  = -1;
      out_id = -1;
      tag    = -1;
      stopped = false;
      if (Name)
         this->Name = Name;
      else {
         cout<<"Cluster funnel can't be anonymous (no name in constructor)."<<endl;
         exit(-1);
      }
    };
    void process() {
      int item_received;
      omp_set_lock(&__cfunnel_lock__);
	  if (!stopped) do {
         MPI_Status status;
         MPI_Iprobe(MPI_ANY_SOURCE, connect_tag, MPI_COMM_WORLD, &item_received, &status);
		 if (item_received) {
            MPI_Status status1;
            data Buf;
            MPI_Recv(&Buf, sizeof(Buf), MPI_BYTE, status.MPI_SOURCE, connect_tag, MPI_COMM_WORLD, &status1);
			map<string, __cfunnel *>::iterator itcFunnels = __cFunnels.find(Buf.connect);
            __cfunnel * cfunnel = NULL;
            if (itcFunnels == __cFunnels.end()) {
               if (Buf.init) {
                  cfunnel = new __cfunnel(Buf.connect);
                  __cFunnels[Buf.connect] = cfunnel;
			   }
            } else
              cfunnel = itcFunnels->second;
			if (cfunnel) {
               int state1 = (cfunnel->in_id >= 0) + (cfunnel->out_id >= 0);
               if (Buf.init) {
                  if (Buf.in) {
                     if (cfunnel->in_id >= 0) {
                        cout<<"Funnel '"<<Buf.connect<<"' already has in-point. Error cluster_id=="<<cfunnel->in_id<<endl;
                        exit(-1);
                     }
                     cfunnel->in_id = status.MPI_SOURCE;
                     if (Buf.tag >= 0)
                        cfunnel->tag = Buf.tag;
                  } else {
                     if (cfunnel->out_id >= 0) {
                        cout<<"Funnel '"<<Buf.connect<<"' already has out-point. Error cluster_id=="<<cfunnel->out_id<<endl;
                        exit(-1);
                     }
                     cfunnel->out_id = status.MPI_SOURCE;
                  }
               } else {
                  if (Buf.in) {
                     if (cfunnel->in_id == status.MPI_SOURCE)
                        cfunnel->in_id = -1;
                  } else {
                     if (cfunnel->out_id == status.MPI_SOURCE)
                        cfunnel->out_id = -1;
                  }
               }
			   int state2 = (cfunnel->in_id >= 0) + (cfunnel->out_id >= 0);
               if (state2 < state1) {
                  cfunnel->stopped = true;
               }
			   if (state2 < state1 && state2 == 0 && cfunnel != this) {
                  omp_unset_lock(&__cfunnel_lock__);
                  delete cfunnel;
                  omp_set_lock(&__cfunnel_lock__);
               }
            }
         }
	  } while (item_received && !stopped);
      omp_unset_lock(&__cfunnel_lock__);
	}
    void wait() {
      if (!stopped) do {
		  process();
      } while (!stopped && (in_id < 0 || out_id < 0));
    };
    void bcast(bool in, bool init, bool all) {
      data Buf;
      Buf.in   = in;
      Buf.init = init;
      memmove(Buf.connect, Name.c_str(), Name.length()+1);
      Buf.tag = tag;
	  if (all) {
		  for (int i = 0; i < __cluster_size__; i++)
			  if (i != __cluster_id__)
				  MPI_Send(&Buf, sizeof(Buf), MPI_BYTE, i, connect_tag, MPI_COMM_WORLD);
	  } else if (in_id == __cluster_id__)
		  MPI_Send(&Buf, sizeof(Buf), MPI_BYTE, out_id, connect_tag, MPI_COMM_WORLD);
	  else if (out_id == __cluster_id__)
		  MPI_Send(&Buf, sizeof(Buf), MPI_BYTE, in_id, connect_tag, MPI_COMM_WORLD);
	};
    ~__cfunnel() {
      if (Name.length() > 0) {
         omp_set_lock(&__cfunnel_lock__);
         map<string,__cfunnel *>::iterator itcFunnels = __cFunnels.find(Name);
         if (itcFunnels == __cFunnels.end()) {
            cout<<"Abnormal funnel termination: funnel '"<<Name<<"' is not registered"<<endl;
            exit(-1);
         } else {
            __cFunnels.erase(itcFunnels);
         }
         omp_unset_lock(&__cfunnel_lock__);
      }
    };
 };
 template<class Type>
  class cfunneled_base {
  private:
    __cfunnel * Ref;
  protected:
    virtual void init_data(__cfunnel * _Ref) = 0;
  public:
    virtual __cfunnel * getRef() { return Ref; };
	virtual _funnel<Type> * getPredictRef(const vector<_funnel<Type> *> * _refs = NULL) { return NULL; };
    void setRef(__cfunnel * _Ref) { Ref = _Ref; };
    virtual bool empty() = 0;
    bool ready() {
      if (!Ref->stopped) Ref->process();
      return !Ref->stopped && Ref->in_id >= 0 && Ref->out_id >= 0;
    };
  };
 template<class Type>
  class cfunneled_out;
 template<class Type>
  class cfunneled_in: public cfunneled_base<Type> {
    friend class cfunneled_out<Type>;
  protected:
    virtual void init_data(__cfunnel * _Ref) {
       this->setRef(_Ref);
       if (_Ref->in_id >= 0) {
          cout<<"Cluster Funnel already has input"<<endl;
          exit(-1);
       }
       _Ref->in_id = __cluster_id__;
       do {
         _Ref->tag = rand();
       } while (_Ref->tag >= 1232 && _Ref->tag < 1240);
    };
  public:
    cfunneled_in(const char * Name) {
       __cfunnel * cfunnel = NULL;
       omp_set_lock(&__cfunnel_lock__);
	   map<string, __cfunnel *>::iterator itcFunnels = __cFunnels.find(Name);
       if (itcFunnels == __cFunnels.end()) {
          cfunnel = new __cfunnel(Name);
		  this->init_data(cfunnel);
          __cFunnels[Name] = cfunnel;
		  cfunnel->bcast(true, true, true);
	   }
	   else {
		   cfunnel = itcFunnels->second;
		   this->init_data(cfunnel);
		   cfunnel->bcast(true, true, false);
	   }
	   omp_unset_lock(&__cfunnel_lock__);
       cfunnel->process();
	}
    ~cfunneled_in() {
       __cfunnel * Ref = this->getRef();
       if (Ref) {
          Ref->bcast(true,false,true);
          Ref->process();
          Ref->in_id = -1;
          delete Ref;
       }
    };
    virtual bool empty() {
      __cfunnel * Ref = this->getRef();
      if (Ref) {
         MPI_Status status;
         int has_data;
         Ref->process();
         if (Ref->stopped || Ref->in_id < 0 || Ref->out_id < 0)
            return true;
         else {
            MPI_Iprobe(Ref->out_id, Ref->tag, MPI_COMM_WORLD, &has_data, &status);
            return has_data == 0;
         }
      }
      return false;
    }
    void get(void * Buf, int SizeInBytes) {
      __cfunnel * Ref = this->getRef();
      if (Ref) {
         MPI_Status status;
		 Ref->wait();
		 MPI_Recv(Buf, SizeInBytes, MPI_BYTE, Ref->out_id, Ref->tag, MPI_COMM_WORLD, &status);
		 MPI_Send(NULL, 0, MPI_BYTE, Ref->out_id, Ref->tag*10, MPI_COMM_WORLD);
	  }
    };
    Type operator * () {
      Type Result;
      get(&Result,sizeof(Result));
      return Result;
    };
 };
 template<class Type>
  class cfunneled_out: public cfunneled_base<Type> {
    friend class cfunneled_in<Type>;
    volatile int send_recv;
  protected:
    void init_data(__cfunnel * _Ref) {
       this->setRef(_Ref);
       if (_Ref->out_id >= 0) {
          cout<<"Funnel already has output"<<endl;
          exit(-1);
       }
       _Ref->out_id = __cluster_id__;
    };
  public:
    cfunneled_out(const char * Name) {
       __cfunnel * cfunnel = NULL;
       omp_set_lock(&__cfunnel_lock__);
       map<string,__cfunnel *>::iterator itcFunnels = __cFunnels.find(Name);
       if (itcFunnels == __cFunnels.end()) {
          cfunnel = new __cfunnel(Name);
          this->init_data(cfunnel);
          __cFunnels[Name] = cfunnel;
          cfunnel->bcast(false,true,true);
       } else {
		   cfunnel = itcFunnels->second;
		   this->init_data(cfunnel);
		   cfunnel->bcast(false, true, false);
	   }
       omp_unset_lock(&__cfunnel_lock__);
       send_recv = 0;
       cfunnel->process();
	}
    void process_answers() {
      __cfunnel * Ref = this->getRef();
      if (Ref) {
         int received = 1;
         while (received && !Ref->stopped && send_recv) {
            MPI_Status status, status1;
            MPI_Iprobe(Ref->in_id, Ref->tag*10, MPI_COMM_WORLD, &received, &status);
            if (received) {
               MPI_Recv(NULL, 0, MPI_BYTE, Ref->in_id, Ref->tag*10, MPI_COMM_WORLD, &status1);
               send_recv--;
            }
         }
      }
    }
    ~cfunneled_out() {
       __cfunnel * Ref = this->getRef();
       if (Ref) {
          while (send_recv && !Ref->stopped)
            process_answers();
          Ref->bcast(false,false,true);
          Ref->process();
          Ref->out_id = -1;
          delete Ref;
       }
    };
    virtual bool empty() {
      __cfunnel * Ref = this->getRef();
      Ref->process();
      if (Ref->stopped || Ref->in_id < 0 || Ref->out_id < 0)
         return true;
      if (send_recv && !Ref->stopped)
         process_answers();
      return (send_recv == 0) || Ref->stopped;
    }
    void put(void * Buf, int SizeInBytes) {
      __cfunnel * Ref = this->getRef();
      if (Ref) {
		  Ref->wait();
		  MPI_Send(Buf, SizeInBytes, MPI_BYTE, Ref->in_id, Ref->tag, MPI_COMM_WORLD);
		  send_recv++;
      }
    };
    Type operator = (Type Val) {
      put(&Val,sizeof(Val));
      return Val;
    };
 };
template<class Type>
  class cfunneled_predictor_out;
template<class Type>
  class cfunneled_predictor_in : public cfunneled_in<Type> {
	  friend class cfunneled_predictor_out<Type>;
  protected:
	  funneled_predictor_in<Type> * _in;
	  funneled_predictor_out<Type> * _out;
	  Type * _Buf;
  public:
	  virtual _funnel<Type> * getPredictRef(const vector<_funnel<Type> *> * _refs = NULL) {
		  if (_in) {
			  _funnel_with_history<Type> * Ref = reinterpret_cast< _funnel_with_history<Type> *>(_in->getRef(_refs));

			  return Ref;
		  }
		  else
			  return NULL;
	  };

	  cfunneled_predictor_in(const char * Name, int N = 1, int P = 5, double rel_eps = 0.001) : cfunneled_in<Type>(Name) {
		  this->_in = new funneled_predictor_in<Type>(N, P, rel_eps);
		  this->_out = new funneled_predictor_out<Type>(P, (void *)_in);
		  this->_Buf = new Type[N];
	  }
	  ~cfunneled_predictor_in() {
		  delete[] this->_Buf;
		  delete this->_in;
		  delete this->_out;
	  }
	  void get(void * Buf, int SizeInBytes) {
		  __cfunnel * Ref = this->getRef();
		  if (Ref) {
			  cfunneled_in<Type>::get(Buf, SizeInBytes);
			  this->_out->put(Buf, SizeInBytes);
			  this->_in->get(Buf, SizeInBytes);
		  }
	  };
	  virtual void get_and_correct(void * Buf) {
		  _funnel_with_history<Type> * Ref = reinterpret_cast< _funnel_with_history<Type> *>(_in->getRef());
		  if (Ref) {
			  int SizeInBytes = Ref->getN()*sizeof(Type);
			  this->get(Buf, SizeInBytes);
			  Ref->set_predict_results();
			  Ref->correct();
			  Ref->unset_predict_results();
		  }
	  }
	  virtual void cancel_and_push(void * Buf) {
		  _funnel_with_history<Type> * Ref = reinterpret_cast<_funnel_with_history<Type> *>(_in->getRef());
		  if (Ref) {
			  int SizeInBytes = Ref->getN()*sizeof(Type);
			  cfunneled_in<Type>::get(_Buf, SizeInBytes);
			  this->_out->put(_Buf, SizeInBytes);
			  Ref->replace_top_history(Buf, false);
			  Ref->unset_predict_results();
		  }
	  };
	  virtual bool get_timed(void * Buf, double timeout_ms) {
		  _funnel_with_history<Type> * Ref = reinterpret_cast< _funnel_with_history<Type> *>(_in->getRef());
		  if (Ref) {
			  double t = omp_get_wtime();
			  double timeout_s = 0.001*timeout_ms;
			  int SizeInBytes = Ref->getN()*sizeof(Type);
			  long counter = WAITING_COUNTER;
			  bool prediction = true;
			  do {
				  if (counter == WAITING_COUNTER) {
					  double elapsed = omp_get_wtime() - t;
					  if (elapsed >= timeout_s && prediction) {
						  Ref->LOCK();
						  prediction = Ref->predict(!(Ref->State & tnlValue));
						  if (prediction) {
							  memmove(Buf, (void *)Ref->getPredicted(), SizeInBytes);
							  Ref->UNLOCK();
							  return true;
						  }
						  Ref->UNLOCK();
					  }
					  counter = 0;
				  }
				  else
					  counter++;
				  _Yield();
			  } while (this->empty());
			  this->get(Buf, SizeInBytes);
		  }
		  return false;
	  };
  };
  template<class Type>
  class cfunneled_predictor_out : public cfunneled_out<Type> {
	  friend class cfunneled_predictor_in<Type>;
  protected:
  public:
	  cfunneled_predictor_out(const char * Name, int N = 1, int P = 5, double rel_eps = 0.001) : cfunneled_out<Type>(Name) {
	  }
  };
 static constexpr MPI_Datatype MPI_TYPES[12] = { MPI_CHAR, MPI_CHAR, MPI_SHORT, MPI_INT, MPI_LONG, MPI_FLOAT, MPI_DOUBLE, MPI_UNSIGNED_SHORT, MPI_UNSIGNED, MPI_UNSIGNED_LONG, MPI_LONG_DOUBLE, MPI_LONG_LONG_INT };
 template<class T> struct MPI_Types { };
 template<> struct MPI_Types<unsigned char> { static constexpr MPI_Datatype val = MPI_TYPES[0]; };
 template<> struct MPI_Types<char> { static constexpr MPI_Datatype val = MPI_TYPES[1]; };
 template<> struct MPI_Types<short> { static constexpr MPI_Datatype val = MPI_TYPES[2]; };
 template<> struct MPI_Types<int> { static constexpr MPI_Datatype val = MPI_TYPES[3]; };
 template<> struct MPI_Types<long> { static constexpr MPI_Datatype val = MPI_TYPES[4]; };
 template<> struct MPI_Types<float> { static constexpr MPI_Datatype val = MPI_TYPES[5]; };
 template<> struct MPI_Types<double> { static constexpr MPI_Datatype val = MPI_TYPES[6]; };
 template<> struct MPI_Types<unsigned short> { static constexpr MPI_Datatype val = MPI_TYPES[7]; };
 template<> struct MPI_Types<unsigned int> { static constexpr MPI_Datatype val = MPI_TYPES[8]; };
 template<> struct MPI_Types<unsigned long> { static constexpr MPI_Datatype val = MPI_TYPES[9]; };
 template<> struct MPI_Types<long double> { static constexpr MPI_Datatype val = MPI_TYPES[10]; };
 template<> struct MPI_Types<long long> { static constexpr MPI_Datatype val = MPI_TYPES[11]; };
 template<class Type>
  class common_var {
    protected:
      int     N;
      void *  mem;
      MPI_Win win;
      int     root;

      common_var(): N(0), mem(NULL), win(MPI_WIN_NULL), root(-1) {};
    public:
      common_var(int _NN) {
        N = _NN;
        if (__cluster_id__ == 0)
           root = rand() % __cluster_size__;
        MPI_Bcast(&root, 1, MPI_INT, 0, MPI_COMM_WORLD);
        if (__cluster_id__ == root) {
           MPI_Alloc_mem(N*sizeof(Type), MPI_INFO_NULL, &mem);
           MPI_Win_create(mem, N*sizeof(Type), sizeof(Type), MPI_INFO_NULL, MPI_COMM_WORLD, &win);
        } else {
           mem = NULL;
           MPI_Win_create(NULL, 0, sizeof(Type), MPI_INFO_NULL, MPI_COMM_WORLD, &win);
        }
      };
      void put (Type * ptr, int size_in_bytes) {
        MPI_Win_lock(MPI_LOCK_EXCLUSIVE, root, 0, win);
        MPI_Put(ptr, size_in_bytes, MPI_BYTE, root, 0, size_in_bytes, MPI_BYTE, win);
        MPI_Win_unlock(root, win);
      };
      void get (Type * ptr, int size_in_bytes) {
        MPI_Win_lock(MPI_LOCK_EXCLUSIVE, root, 0, win);
        MPI_Get(ptr, size_in_bytes, MPI_BYTE, root, 0, size_in_bytes, MPI_BYTE, win);
        MPI_Win_unlock(root, win);
      };
      Type add(Type inc, bool pre) {
        Type buf;
        MPI_Win_lock(MPI_LOCK_EXCLUSIVE, root, 0, win);
        if (pre) {
           MPI_Accumulate(&inc, 1, MPI_Types<Type>::val, root, 0, 1, MPI_Types<Type>::val, MPI_SUM, win);
           MPI_Get(&buf, 1, MPI_Types<Type>::val, root, 0, 1, MPI_Types<Type>::val, win);
        } else {
           MPI_Get(&buf, 1, MPI_Types<Type>::val, root, 0, 1, MPI_Types<Type>::val, win);
           MPI_Accumulate(&inc, 1, MPI_Types<Type>::val, root, 0, 1, MPI_Types<Type>::val, MPI_SUM, win);
        }
        MPI_Win_unlock(root, win);
        return buf;
      }
      Type operator ++ () {
        return add(+1, false);
      };
      Type operator ++ (int) {
        return add(+1, true);
      };
      Type operator -- () {
        return add(-1, false);
      };
      Type operator -- (int) {
        return add(-1, true);
      };
      Type operator += (Type Val) {
        return add(Val, true);
      };
      Type operator -= (Type Val) {
        return add(-Val, true);
      };
      Type operator = (Type Val) {
        put(&Val, sizeof(Val));
        return Val;
      };
      Type operator * () {
        Type Result;
        get(&Result,sizeof(Result));
        return Result;
      };
      ~common_var() {
        MPI_Win_free(&win);
        if (mem) MPI_Free_mem(mem);
      };
  };
  class csemaphore: public common_var<int> {
    protected:
      int MAX;
    public:
      csemaphore(int C): common_var<int>(1), MAX(C) {
        if (__cluster_id__ == this->root) {
           int val = 0;
           this->put(&val, sizeof(int));
        }
        MPI_Barrier(MPI_COMM_WORLD);
      };
      void wait () {
        int v;
        do {
           v = common_var<int>::operator ++();
           if (v >= MAX) {
              common_var<int>::operator --();
              Sleep(rand()%4);
           }
        } while (v >= MAX);
      };
      void release () {
        common_var<int>::operator --();
      };
  };
 typedef csemaphore * plan_csem_t;
 #define plan_csem_init(sem, N) *sem = new csemaphore(N)
 #define plan_csem_wait(sem) (*sem)->wait()
 #define plan_csem_release(sem) (*sem)->release()
 #define plan_csem_destroy(sem) delete *sem
#endif
#endif

#ifdef _OPENMP

class __init_openmp_mpi__ {
  public:
  __init_openmp_mpi__() {
#ifdef _OPENMP
    omp_set_nested(1);
    omp_init_lock(&__funnel_lock__);
#ifdef __REENT_MPI__
    omp_init_lock(&__cfunnel_lock__);
#endif
#endif
#ifdef __REENT_MPI__
    int provided;
    MPI_Init_thread(NULL,NULL, MPI_THREAD_SERIALIZED, &provided);
    if (provided != MPI_THREAD_SERIALIZED && provided != MPI_THREAD_MULTIPLE) {
       cout<<"MPI: multithreading support is not suffucuent"<<endl;
       MPI_Abort(MPI_COMM_WORLD,-1);
    }
    MPI_Comm_size(MPI_COMM_WORLD,&__cluster_size__);
    MPI_Comm_rank(MPI_COMM_WORLD,&__cluster_id__);
#endif
  };
  ~__init_openmp_mpi__() {
#ifdef __REENT_MPI__
    MPI_Finalize();
#endif
  };
};
__init_openmp_mpi__ __ompi_initializer = __init_openmp_mpi__();

#endif

#endif