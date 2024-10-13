Const Tunnels_Vars_Sems: PChar =
'#if __GNUC__ < 4 || (__GNUC__ == 4 && __GNUC_MINOR__ < 7)'+CRLF+
'  #define __transaction_atomic /* no transactional memory */'+CRLF+
'  #define __parallel_atomic__ (0)'+CRLF+
'#else'+CRLF+
'  #define __parallel_atomic__ (2)'+CRLF+
'#endif'+CRLF+
'#ifdef _OPENMP'+CRLF+
' #include <string.h>'+CRLF+
' #include <stdlib.h>'+CRLF+
' #include <math.h>'+CRLF+
' #include <omp.h>'+CRLF+
' #include <iostream>'+CRLF+
' #include <string>'+CRLF+
' #include <vector>'+CRLF+
' #include <algorithm>'+CRLF+
' #include <map>'+CRLF+
' using namespace std;'+CRLF+
' #define funnel(Dir,Type) funneled_##Dir<Type>'+CRLF+
' const char tnlValue  = 0x01;'+CRLF+
' const char tnlHasIn  = 0x02;'+CRLF+
' const char tnlHasOut = 0x04;'+CRLF+
' const int WAITING_COUNTER = 80;'+CRLF+
' omp_lock_t __funnel_lock__;'+CRLF+
' class __funnel;'+CRLF+
' map<string,__funnel *> __Funnels;'+CRLF+
' #ifndef __min'+CRLF+
' #define __min(a,b) ((a)<(b) ? (a) : (b))'+CRLF+
' #endif'+CRLF+
' #ifndef __max'+CRLF+
' #define __max(a,b) ((a)>(b) ? (a) : (b))'+CRLF+
' #endif'+CRLF+
' /* LU - разложение  с выбором максимального элемента по диагонали */'+CRLF+
' bool _GetLU(int NN, int * iRow, long double * A, long double * LU)'+CRLF+
' {'+CRLF+
'  int i,j,k;'+CRLF+
'  try {'+CRLF+
'    memmove(LU,A,NN*NN*sizeof(long double));'+CRLF+
'    for (i=0;i<NN;i++)'+CRLF+
'        iRow[i]=i;'+CRLF+
'    for (i=0;i<NN-1;i++)'+CRLF+
'      {'+CRLF+
'       long double Big  = fabs(LU[iRow[i]*NN+i]);'+CRLF+
'       int iBig = i;'+CRLF+
'       long double Kf;'+CRLF+
'       for (j=i+1;j<NN;j++)'+CRLF+
'           {'+CRLF+
'            long double size = fabs(LU[iRow[j]*NN+i]);'+CRLF+
'            if (size>Big)'+CRLF+
'               {'+CRLF+
'                Big  = size;'+CRLF+
'                iBig = j;'+CRLF+
'               }'+CRLF+
'           }'+CRLF+
'       if (iBig!=i)'+CRLF+
'          {'+CRLF+
'           int V = iRow[i];'+CRLF+
'           iRow[i] = iRow[iBig];'+CRLF+
'           iRow[iBig] = V;'+CRLF+
'          }'+CRLF+
'       Kf = 1.0/LU[iRow[i]*NN+i];'+CRLF+
''+CRLF+
'       LU[iRow[i]*NN+i] = Kf;'+CRLF+
'       for (j=i+1;j<NN;j++)'+CRLF+
'           {'+CRLF+
'            long double Fact = Kf*LU[iRow[j]*NN+i];'+CRLF+
'            LU[iRow[j]*NN+i] = Fact;'+CRLF+
'            for (k=i+1;k<NN;k++)'+CRLF+
'                LU[iRow[j]*NN+k] -= Fact*LU[iRow[i]*NN+k];'+CRLF+
'           }'+CRLF+
'      }'+CRLF+
'    LU[(iRow[NN-1]+1)*NN-1] = 1.0/LU[(iRow[NN-1]+1)*NN-1];'+CRLF+
'  }'+CRLF+
'  catch (...) {'+CRLF+
'    return false;'+CRLF+
'  }'+CRLF+
'  return true;'+CRLF+
' }'+CRLF+
' /* Метод LU - разложения */'+CRLF+
' bool _SolveLU(int NN, int * iRow, long double * LU, long double * Y, long double * X)'+CRLF+
' {'+CRLF+
'  int i,j,k;'+CRLF+
'  try {'+CRLF+
'    X[0] = Y[iRow[0]];'+CRLF+
'    for (i=1;i<NN;i++)'+CRLF+
'        {'+CRLF+
'         long double V  = Y[iRow[i]];'+CRLF+
'         for (j=0;j<i;j++)'+CRLF+
'             V -= LU[iRow[i]*NN+j]*X[j];'+CRLF+
'         X[i] = V;'+CRLF+
'        }'+CRLF+
'    X[NN-1]*=LU[(iRow[NN-1]+1)*NN-1];'+CRLF+
'    for (i=1,j=NN-2;i<NN;i++,j--)'+CRLF+
'        {'+CRLF+
'         long double V = X[j];'+CRLF+
'         for (k=j+1;k<NN;k++)'+CRLF+
'             V -= LU[iRow[j]*NN+k]*X[k];'+CRLF+
'         X[j] = V*LU[iRow[j]*NN+j];'+CRLF+
'        }'+CRLF+
'  }'+CRLF+
'  catch (...) {'+CRLF+
'    return false;'+CRLF+
'  }'+CRLF+
'  return true;'+CRLF+
' }'+CRLF+
' /* Метод Гаусса-Зейделя  с выбором максимального элемента по диагонали */'+CRLF+
' bool _SolveGaussZeidel(int NN, int * iRow, long double * A, long double * LU, long double * Y, long double * X) {'+CRLF+
'  int np = omp_get_num_procs();'+CRLF+
'  double prev_eps, eps;'+CRLF+
'  int grow;'+CRLF+
'  int iters;'+CRLF+
'  try {'+CRLF+
'    for (int i=0;i<NN;i++)'+CRLF+
'        iRow[i]=i;'+CRLF+
'    for (int i=0;i<NN-1;i++)'+CRLF+
'      {'+CRLF+
'       long double Big  = fabs(A[iRow[i]*NN+i]);'+CRLF+
'       int iBig = i;'+CRLF+
'       for (int j=i+1;j<NN;j++)'+CRLF+
'           {'+CRLF+
'            long double size = fabs(A[iRow[j]*NN+i]);'+CRLF+
'            if (size>Big)'+CRLF+
'               {'+CRLF+
'                Big  = size;'+CRLF+
'                iBig = j;'+CRLF+
'               }'+CRLF+
'           }'+CRLF+
'       if (iBig!=i)'+CRLF+
'          {'+CRLF+
'           int V = iRow[i];'+CRLF+
'           iRow[i] = iRow[iBig];'+CRLF+
'           iRow[iBig] = V;'+CRLF+
'          }'+CRLF+
'      }'+CRLF+
'    for (int i=0;i<NN;i++)'+CRLF+
'        X[i]=0.5;'+CRLF+
'    eps = 1E300;'+CRLF+
'    grow = 0;'+CRLF+
'    for (iters = 0; eps > 1E-8 && iters < 2*NN; iters++) {'+CRLF+
'        prev_eps = eps;'+CRLF+
'        eps = 0.0;'+CRLF+
'        if (NN < 20 || np < 3) {'+CRLF+
'           for (int i=0;i<NN;i++) {'+CRLF+
'               long double V = Y[iRow[i]];'+CRLF+
'               double d = X[i];'+CRLF+
'               for (int j=0;j<NN;j++)'+CRLF+
'                   if (j != i)'+CRLF+
'                      V -= A[iRow[i]*NN+j]*X[j];'+CRLF+
'               X[i] = V/A[iRow[i]*NN+i];'+CRLF+
'               d -= X[i];'+CRLF+
'               eps += d*d;'+CRLF+
'           }'+CRLF+
'           eps = sqrt(eps);'+CRLF+
'        } else {'+CRLF+
'           for (int i=0;i<NN;i++) {'+CRLF+
'               long double V = Y[iRow[i]];'+CRLF+
'               double d = X[i];'+CRLF+
'               #pragma omp parallel for num_threads(np) reduction(+:V)'+CRLF+
'               for (int j=0;j<NN;j++)'+CRLF+
'                   if (j != i)'+CRLF+
'                      V -= A[iRow[i]*NN+j]*X[j];'+CRLF+
'               X[i] = V/A[iRow[i]*NN+i];'+CRLF+
'               d -= X[i];'+CRLF+
'               eps += d*d;'+CRLF+
'           }'+CRLF+
'           eps = sqrt(eps);'+CRLF+
'        }'+CRLF+
'        if (eps > prev_eps)'+CRLF+
'           grow++;'+CRLF+
'        else'+CRLF+
'           grow = 0;'+CRLF+
'    }'+CRLF+
'    return eps <= 1E-8;'+CRLF+
'  }'+CRLF+
'  catch (...) {'+CRLF+
'    return false;'+CRLF+
'  }'+CRLF+
' }'+CRLF+
' class __funnel {'+CRLF+
'  public:'+CRLF+
'    omp_lock_t Lock;'+CRLF+
'    volatile char State;'+CRLF+
'    volatile int Refs;'+CRLF+
'    bool useLU;'+CRLF+
'    string Name;'+CRLF+
'    __funnel(const char * Name = NULL) {'+CRLF+
'      State = 0;'+CRLF+
'      Refs = 0;'+CRLF+
'      useLU = true;'+CRLF+
'      omp_init_lock(&Lock);'+CRLF+
'      if (Name)'+CRLF+
'         this->Name = Name;'+CRLF+
'      else'+CRLF+
'         this->Name = "";'+CRLF+
'    };'+CRLF+
'    void switchLU(bool LU) {'+CRLF+
'      useLU = LU;'+CRLF+
'    }'+CRLF+
'    virtual ~__funnel() {'+CRLF+
'      if (Name.length() > 0) {'+CRLF+
'         omp_set_lock(&__funnel_lock__);'+CRLF+
'         map<string,__funnel *>::iterator itFunnels = __Funnels.find(Name);'+CRLF+
'         if (itFunnels == __Funnels.end()) {'+CRLF+
'            cout<<"Abnormal funnel termination: funnel ''"<<Name<<"'' is not registered"<<endl;'+CRLF+
'            exit(-1);'+CRLF+
'         } else {'+CRLF+
'            __Funnels.erase(itFunnels);'+CRLF+
'         }'+CRLF+
'         omp_unset_lock(&__funnel_lock__);'+CRLF+
'      }'+CRLF+
'      omp_destroy_lock(&Lock);'+CRLF+
'    };'+CRLF+
' };'+CRLF+
' template<class Type>'+CRLF+
'  class _funnel: public __funnel {'+CRLF+
'  public:'+CRLF+
'    Type * Data;'+CRLF+
'    volatile int    N;'+CRLF+
'    _funnel(int N, const char * Name = NULL): __funnel(Name) {'+CRLF+
'      this->N = N;'+CRLF+
'      Data = (Type *) malloc(N*sizeof(Type));'+CRLF+
'    };'+CRLF+
'    void check_size(int _NN) {'+CRLF+
'      if (_NN > N) {'+CRLF+
'         N = (int)(1.5*_NN);'+CRLF+
'         free((void *) Data);'+CRLF+
'         Data = (Type *) malloc(N*sizeof(Type));'+CRLF+
'      }'+CRLF+
'    };'+CRLF+
'    int getN() {'+CRLF+
'      return N;'+CRLF+
'    };'+CRLF+
'    virtual void add_refs(const vector<_funnel<Type> *> * _refs) {'+CRLF+
'    };'+CRLF+
'    virtual ~_funnel() {'+CRLF+
'      free((void *) Data);'+CRLF+
'    };'+CRLF+
' };'+CRLF+
' template<class Type>'+CRLF+
'  class _funnel_with_history: public _funnel<Type> {'+CRLF+
'  protected:'+CRLF+
'    Type *  Predicted;'+CRLF+
'    volatile bool    HasPredicted;'+CRLF+
'    volatile bool    Calculated;'+CRLF+
'    Type ** History;'+CRLF+
'    double rel_eps;'+CRLF+
'    volatile int     MaxDepth;'+CRLF+
'    volatile int     Depth;'+CRLF+
'    volatile int     MaxP;'+CRLF+
'    volatile int  *  P;'+CRLF+
'	volatile bool *  Mask;'+CRLF+
'  public:'+CRLF+
'    Type * getPredicted() { return this->Predicted; };'+CRLF+
'    bool hasPredicted() { return this->HasPredicted; };'+CRLF+
'    bool isCalculated() { return this->Calculated; };'+CRLF+
'    Type ** getHistory() { return History; };'+CRLF+
'    int getMaxDepth() { return this->MaxDepth; };'+CRLF+
''+CRLF+
'    _funnel_with_history(int N, double rel_eps, const char * Name): _funnel<Type>(N, Name) {'+CRLF+
'      this->P = new int[N];'+CRLF+
'      this->MaxP = 0;'+CRLF+
'      this->MaxDepth = 0;'+CRLF+
'      this->Depth = 0;'+CRLF+
'      this->Predicted = NULL;'+CRLF+
'      this->HasPredicted = false;'+CRLF+
'      this->Calculated = false;'+CRLF+
'      this->rel_eps = rel_eps;'+CRLF+
'      this->History = NULL;'+CRLF+
'	  this->Mask = NULL;'+CRLF+
'    };'+CRLF+
'    _funnel_with_history(int P, int N = 1, double rel_eps = 0.001, const char * Name = NULL): _funnel<Type>(N, Name) {'+CRLF+
'      this->P = new int[N];'+CRLF+
'      this->MaxP = P;'+CRLF+
'      this->MaxDepth = this->MaxP*2;'+CRLF+
'      this->Depth = 0;'+CRLF+
'      this->Predicted = (Type *) malloc(N*sizeof(Type));'+CRLF+
'      this->HasPredicted = false;'+CRLF+
'      this->Calculated = false;'+CRLF+
'      this->rel_eps = rel_eps;'+CRLF+
'      this->History = new Type * [MaxDepth];'+CRLF+
'      for (int i = 0; i <this->MaxDepth; i++) {'+CRLF+
'          this->History[i] = new Type[N];'+CRLF+
'      }'+CRLF+
'	  this->Mask = NULL;'+CRLF+
'	};'+CRLF+
'    void push_history(bool lock = true) {'+CRLF+
'      if (lock) omp_set_lock(&this->Lock);'+CRLF+
'      if (Depth > 0) {'+CRLF+
'         Type * Bottom = this->History[0];'+CRLF+
'         for (int i = 0; i < this->MaxDepth - 1; i++)'+CRLF+
'             this->History[i] = this->History[i + 1];'+CRLF+
'         this->History[MaxDepth - 1] = Bottom;'+CRLF+
'      }'+CRLF+
'      if (Depth <this->MaxDepth) Depth++;'+CRLF+
'      memmove((void *) this->History[MaxDepth - 1], (void *) this->Data, this->N*sizeof(Type));'+CRLF+
'      if (lock) omp_unset_lock(&this->Lock);'+CRLF+
'    }'+CRLF+
'    void pop_history(bool lock = true) {'+CRLF+
'      if (lock) omp_set_lock(&this->Lock);'+CRLF+
'      if (Depth > 0) {'+CRLF+
'         Type * Top = this->History[MaxDepth - 1];'+CRLF+
'         for (int i = this->MaxDepth - 1; i > 0; i--)'+CRLF+
'             this->History[i] = this->History[i - 1];'+CRLF+
'         this->History[0] = Top;'+CRLF+
'         Depth--;'+CRLF+
'      }'+CRLF+
'      unset_predict_results();'+CRLF+
'      if (lock) omp_unset_lock(&this->Lock);'+CRLF+
'    }'+CRLF+
'    void replace_top_history(void * Buf, bool lock = true) {'+CRLF+
'         if (lock) omp_set_lock(&this->Lock);'+CRLF+
'         memmove((void *) this->History[MaxDepth - 1], Buf, this->N*sizeof(Type));'+CRLF+
'         if (lock) omp_unset_lock(&this->Lock);'+CRLF+
'    }'+CRLF+
'	virtual void setMask(bool * Mask) {'+CRLF+
'		this->Mask = Mask;'+CRLF+
'	}'+CRLF+
'    virtual bool predict(bool use_top) = 0;'+CRLF+
'    virtual void correct() = 0;'+CRLF+
'    virtual void unset_predict_results() {'+CRLF+
'      HasPredicted = false;'+CRLF+
'    }'+CRLF+
'    virtual void set_predict_results() {'+CRLF+
'      HasPredicted = true;'+CRLF+
'    }'+CRLF+
'    virtual void LOCK() {'+CRLF+
'      omp_set_lock(&this->Lock);'+CRLF+
'    }'+CRLF+
'    virtual void UNLOCK() {'+CRLF+
'      omp_unset_lock(&this->Lock);'+CRLF+
'    }'+CRLF+
'    virtual ~_funnel_with_history() {'+CRLF+
'      free((void *) this->Predicted);'+CRLF+
'      for (int i = 0; i <this->MaxDepth; i++)'+CRLF+
'          delete[] this->History[i];'+CRLF+
'      delete[] this->History;'+CRLF+
'      delete[] P;'+CRLF+
'    };'+CRLF+
' };'+CRLF+
' template<class Type>'+CRLF+
'  class _funnel_predictor: public _funnel_with_history<Type> {'+CRLF+
'  private:'+CRLF+
'    double ** K;'+CRLF+
'    long double * A;'+CRLF+
'    long double * LU;'+CRLF+
'    long double * Y;'+CRLF+
'    long double * X;'+CRLF+
'    bool calc_predictor(bool use_top) {'+CRLF+
'       int corr = use_top ? 0 : 1;'+CRLF+
'       int iRow[1024];'+CRLF+
'       for (int p = 0; p < this->N; p++)'+CRLF+
'		   if (!this->Mask || this->Mask[p]) {'+CRLF+
'			   double max_err = 1E300;'+CRLF+
'			   this->P[p] = -1;'+CRLF+
'			   for (int pp = this->MaxP; pp >= 1; pp--) {'+CRLF+
'				   memset(A, 0, this->MaxP*this->MaxP*sizeof(long double));'+CRLF+
'				   memset(Y, 0, this->MaxP*sizeof(long double));'+CRLF+
'				   int L = __min(this->MaxDepth - corr, pp * 3);'+CRLF+
'				   for (int i = this->MaxDepth - corr - L; i < this->MaxDepth - corr - pp + 1; i++) {'+CRLF+
'					   for (int j = 0, ptr = 0; j < pp; j++) {'+CRLF+
'						   long double XX = j == 0 ? 1.0 : (long double) this->History[i + j - 1][p];'+CRLF+
'						   for (int k = 0; k < pp; k++, ptr++) {'+CRLF+
'							   A[ptr] += (k == 0 ? 1.0 : (long double) this->History[i + k - 1][p])*XX;'+CRLF+
'						   }'+CRLF+
'						   Y[j] += XX*(long double) this->History[i + pp - 1][p];'+CRLF+
'					   }'+CRLF+
'				   }'+CRLF+
'				   bool result = (!this->useLU && _SolveGaussZeidel(pp, iRow, A, LU, Y, X)) || _GetLU(pp, iRow, A, LU) && _SolveLU(pp, iRow, LU, Y, X);'+CRLF+
'				   if (result) {'+CRLF+
'					   for (int i = 0, ptr = 0; result && i < pp; i++) {'+CRLF+
'						   double val = 0.0;'+CRLF+
'						   for (int j = 0; result && j < pp; j++, ptr++) {'+CRLF+
'							   if (X[j] != X[j]) result = false;'+CRLF+
'							   val += A[ptr] * X[j];'+CRLF+
'						   }'+CRLF+
'						   double r = fabs(val - Y[i]);'+CRLF+
'						   if (r != r || r > 1E-3)'+CRLF+
'							   result = false;'+CRLF+
'					   }'+CRLF+
'				   }'+CRLF+
'				   double cur_err = 1E300;'+CRLF+
'				   if (result) {'+CRLF+
'					   cur_err = 0.0;'+CRLF+
'					   double val = X[0];'+CRLF+
'					   for (int j = 1; j < pp; j++)'+CRLF+
'						   val += X[j] * ((double) this->History[this->MaxDepth - corr - pp + j - 1][p]);'+CRLF+
'					   this->Predicted[p] = (Type)val;'+CRLF+
'					   Type H = (Type)this->History[this->MaxDepth - corr - 1][p];'+CRLF+
'					   if (H != 0) {'+CRLF+
'						   cur_err = fabs(1.0*(H - (Type)val) / H);'+CRLF+
'					   }'+CRLF+
'				   }'+CRLF+
'				   if (result) {'+CRLF+
'					   if (cur_err < this->rel_eps && cur_err <= max_err) {'+CRLF+
'						   this->P[p] = pp;'+CRLF+
'						   for (int i = 0; i < pp; i++)'+CRLF+
'							   K[p][i] = (double)X[i];'+CRLF+
'						   max_err = cur_err;'+CRLF+
'					   }'+CRLF+
'				   }'+CRLF+
'			   }'+CRLF+
'		   } else'+CRLF+
'			   this->P[p] = -1;'+CRLF+
'       return true;'+CRLF+
'    }'+CRLF+
'  public:'+CRLF+
'    _funnel_predictor(int P, int N = 1, double rel_eps = 0.001, const char * Name = NULL): _funnel_with_history<Type>(P, N, rel_eps, Name) {'+CRLF+
'       K = (double **) malloc(N*sizeof(double *));'+CRLF+
'       for (int i = 0; i < N; i++)'+CRLF+
'           K[i] = (double *) malloc(this->MaxP*sizeof(double));'+CRLF+
'       A = new long double[this->MaxP*this->MaxP];'+CRLF+
'       LU = new long double[this->MaxP*this->MaxP];'+CRLF+
'       Y = new long double[this->MaxP];'+CRLF+
'       X = new long double[this->MaxP];'+CRLF+
'    };'+CRLF+
'    virtual bool predict(bool use_top) {'+CRLF+
'       bool result = false;'+CRLF+
'       if (!this->Calculated && this->Depth == this->MaxDepth) {'+CRLF+
'           this->Calculated = calc_predictor(use_top);'+CRLF+
'       }'+CRLF+
'       if (this->Calculated) {'+CRLF+
'           int corr = use_top ? 0 : 1;'+CRLF+
'           for (int i = 0; i < this->N; i++)'+CRLF+
'             if (this->P[i] < 0)'+CRLF+
'                this->Predicted[i] = (Type)this->History[this->MaxDepth - corr - 1][i];'+CRLF+
'             else {'+CRLF+
'                double val = K[i][0];'+CRLF+
'                for (int j = 1; j < this->P[i]; j++)'+CRLF+
'                    val += K[i][j]*((double) this->History[this->MaxDepth - corr - this->P[i] + j][i]);'+CRLF+
'                this->Predicted[i] = (Type) val;'+CRLF+
'           }'+CRLF+
'           result = true;'+CRLF+
'       }'+CRLF+
'       if (result) this->HasPredicted = true;'+CRLF+
'       return result;'+CRLF+
'    };'+CRLF+
'    virtual void correct() {'+CRLF+
'       omp_set_lock(&this->Lock);'+CRLF+
'       if (this->Calculated && this->HasPredicted) {'+CRLF+
'           double eps = 0.0;'+CRLF+
'           int nn = 0;'+CRLF+
'           for (int i = 0; i < this->N; i++)'+CRLF+
'			   if (!this->Mask || this->Mask[i]) {'+CRLF+
'				   if (this->Data[i] != (Type) 0.0) {'+CRLF+
'					   eps += fabs(1.0*(this->Predicted[i] - this->Data[i]) / this->Data[i]);'+CRLF+
'					   nn++;'+CRLF+
'				   }'+CRLF+
'			   }'+CRLF+
'           if (nn > 0) eps /= nn;'+CRLF+
'           if (eps > this->rel_eps)'+CRLF+
'              this->Calculated = false;'+CRLF+
'       }'+CRLF+
'       omp_unset_lock(&this->Lock);'+CRLF+
'    };'+CRLF+
'    virtual ~_funnel_predictor() {'+CRLF+
'       for (int i = 0; i < this->N; i++)'+CRLF+
'           free((void *) K[i]);'+CRLF+
'       free((void *) K);'+CRLF+
'       delete[] A;'+CRLF+
'       delete[] LU;'+CRLF+
'       delete[] Y;'+CRLF+
'       delete[] X;'+CRLF+
'    };'+CRLF+
' };'+CRLF+
' template<class Type>'+CRLF+
'  class _funnel_perceptron: public _funnel_with_history<Type> {'+CRLF+
'  protected:'+CRLF+
'    double ** K1;'+CRLF+
'    double ** K2;'+CRLF+
'    double ** K;'+CRLF+
'    double * B;'+CRLF+
'    double * B1;'+CRLF+
'    double * B2;'+CRLF+
'    double ** C;'+CRLF+
'    double ** C1;'+CRLF+
'    double ** C2;'+CRLF+
'    int * nstart;'+CRLF+
'    int * nend;'+CRLF+
'    int * iRow;'+CRLF+
'    long double * A;'+CRLF+
'    long double * LU;'+CRLF+
'    long double * Y;'+CRLF+
'    long double * X;'+CRLF+
'    bool hasB;'+CRLF+
'    int PATTERN;'+CRLF+
'  protected:'+CRLF+
'    vector<_funnel<Type> *> refs;'+CRLF+
'    virtual bool calc_predictor(bool use_top) = 0;'+CRLF+
'    virtual void apply_predictor(bool use_top) = 0;'+CRLF+
''+CRLF+
'    virtual void analyze(int NN, double k1, double * BB1, double k2, double * BB2, double * R1, double * R2) {'+CRLF+
'       double d = k2 - k1;'+CRLF+
'       double fd = fabs(d);'+CRLF+
'       for (int i = 0; i < NN; i++)'+CRLF+
'           if (fd < 1E-8) {'+CRLF+
'              R1[i] = BB1[i];'+CRLF+
'              R2[i] = 0.0;'+CRLF+
'           } else {'+CRLF+
'              R2[i] = (BB2[i] - BB1[i]) / d;'+CRLF+
'              R1[i] = BB1[i] - k1*R2[i];'+CRLF+
'           }'+CRLF+
'    }'+CRLF+
'    virtual void use(int NN, double k, double * R, double * R1, double * R2) {'+CRLF+
'       for (int i = 0; i < NN; i++)'+CRLF+
'           R[i] = R1[i] + k*R2[i];'+CRLF+
'    }'+CRLF+
'  public:'+CRLF+
'    const vector<_funnel<Type> *> & get_refs() { return refs; };'+CRLF+
'    const bool get_hasB() { return hasB; }'+CRLF+
''+CRLF+
'    virtual void add_refs(const vector<_funnel<Type> *> * _refs) {'+CRLF+
'       if (_refs) {'+CRLF+
'          int NN = this->refs.size();'+CRLF+
'          for (unsigned int i = 0; i < _refs->size(); i++)'+CRLF+
'              if (find(refs.begin(), this->refs.end(), (*_refs)[i]) == this->refs.end())'+CRLF+
'                 this->refs.push_back((*_refs)[i]);'+CRLF+
'          if (NN < this->refs.size()) {'+CRLF+
'             this->MaxP = this->N + this->refs.size() + (this->hasB ? 1 : 0);'+CRLF+
'             for (int i = 0; i < this->N; i++)'+CRLF+
'                 C[i] = (double *) realloc(C[i], this->refs.size()*sizeof(double));'+CRLF+
'             delete[] iRow; iRow = new int[this->MaxP];'+CRLF+
'             delete[] A;    A = new long double[this->MaxP*this->MaxP];'+CRLF+
'             delete[] LU;   LU = new long double[this->MaxP*this->MaxP];'+CRLF+
'             delete[] Y;    Y = new long double[this->MaxP];'+CRLF+
'             delete[] X;    X = new long double[this->MaxP];'+CRLF+
'          }'+CRLF+
'       }'+CRLF+
'    };'+CRLF+
''+CRLF+
'    _funnel_perceptron(bool hasB, const vector<_funnel<Type> *> &refs, int N = 1, double rel_eps = 0.001, const char * Name = NULL, int PATTERN = -1): _funnel_with_history<Type>(N, rel_eps, Name) {'+CRLF+
'       this->refs = refs;'+CRLF+
'       this->MaxDepth = N + __max(40,refs.size()) + 2;'+CRLF+
'       this->PATTERN = PATTERN;'+CRLF+
'       this->Depth = 0;'+CRLF+
'       this->MaxP = N + this->refs.size() + 1;'+CRLF+
'       this->Predicted = (Type *) malloc(N*sizeof(Type));'+CRLF+
'       this->HasPredicted = false;'+CRLF+
'       this->Calculated = false;'+CRLF+
'       this->hasB = hasB;'+CRLF+
'       this->History = new Type * [this->MaxDepth];'+CRLF+
'       for (int i = 0; i < this->MaxDepth; i++) {'+CRLF+
'          this->History[i] = new Type[N];'+CRLF+
'       }'+CRLF+
'       K = (double **) malloc(N*sizeof(double *));'+CRLF+
'       for (int i = 0; i < N; i++)'+CRLF+
'           K[i] = (double *) malloc(N*sizeof(double));'+CRLF+
'       K1 = K2 = NULL;'+CRLF+
'       C = (double **) malloc(N*sizeof(double *));'+CRLF+
'       for (int i = 0; i < N; i++)'+CRLF+
'           C[i] = (double *) malloc(refs.size()*sizeof(double));'+CRLF+
'       C1 = C2 = NULL;'+CRLF+
'       nstart = (int *) malloc(N*sizeof(int));'+CRLF+
'       nend = (int *) malloc(N*sizeof(int));'+CRLF+
'       if (hasB)'+CRLF+
'          B = (double *) malloc(N*sizeof(double));'+CRLF+
'       else'+CRLF+
'          B = NULL;'+CRLF+
'       B1 = B2 = NULL;'+CRLF+
'       iRow = new int[this->MaxP];'+CRLF+
'       A = new long double[this->MaxP*this->MaxP];'+CRLF+
'       LU = new long double[this->MaxP*this->MaxP];'+CRLF+
'       Y = new long double[this->MaxP];'+CRLF+
'       X = new long double[this->MaxP];'+CRLF+
'    };'+CRLF+
'    virtual void use_parameter(double k) {'+CRLF+
'       if (this->K1 != NULL && this->K2 != NULL && this->C1 != NULL && this->C2 != NULL) {'+CRLF+
'          if (this->hasB) {'+CRLF+
'             use(this->N, k, this->B, this->B1, this->B2);'+CRLF+
'          }'+CRLF+
'          for (int i = 0; i < this->N; i++) {'+CRLF+
'              use(this->N, k, this->K[i], this->K1[i], this->K2[i]);'+CRLF+
'              use(this->refs.size(), k, this->C[i], this->C1[i], this->C2[i]);'+CRLF+
'          }'+CRLF+
'       }'+CRLF+
'    }'+CRLF+
'    virtual void parametrize(double k1, _funnel<Type> * _d2, double k2) {'+CRLF+
'       _funnel_perceptron<Type> * d2 = reinterpret_cast<_funnel_perceptron<Type> *>(_d2);'+CRLF+
'       if (this->K1 == NULL && this->K2 == NULL && this->C1 == NULL && this->C2 == NULL) {'+CRLF+
'          this->K1 = (double **) malloc(this->N*sizeof(double *));'+CRLF+
'          for (int i = 0; i < this->N; i++)'+CRLF+
'              this->K1[i] = (double *) malloc(this->N*sizeof(double));'+CRLF+
'          this->K2 = (double **) malloc(this->N*sizeof(double *));'+CRLF+
'          for (int i = 0; i < this->N; i++)'+CRLF+
'              this->K2[i] = (double *) malloc(this->N*sizeof(double));'+CRLF+
'          this->C1 = (double **) malloc(this->N*sizeof(double *));'+CRLF+
'          for (int i = 0; i < this->N; i++)'+CRLF+
'              this->C1[i] = (double *) malloc(this->refs.size()*sizeof(double));'+CRLF+
'          this->C2 = (double **) malloc(this->N*sizeof(double *));'+CRLF+
'          for (int i = 0; i < this->N; i++)'+CRLF+
'              this->C2[i] = (double *) malloc(this->refs.size()*sizeof(double));'+CRLF+
'          if (this->hasB) {'+CRLF+
'             this->B1 = (double *) malloc(this->N*sizeof(double));'+CRLF+
'             this->B2 = (double *) malloc(this->N*sizeof(double));'+CRLF+
'          }'+CRLF+
'       }'+CRLF+
'       this->Calculated = true;'+CRLF+
'       if (this->hasB) {'+CRLF+
'          analyze(this->N, k1, this->B, k2, d2->B, this->B1, this->B2);'+CRLF+
'       }'+CRLF+
'       for (int i = 0; i < this->N; i++) {'+CRLF+
'           analyze(this->N, k1, this->K[i], k2, d2->K[i], this->K1[i], this->K2[i]);'+CRLF+
'           analyze(this->refs.size(), k1, this->C[i], k2, d2->C[i], this->C1[i], this->C2[i]);'+CRLF+
'       }'+CRLF+
'    }'+CRLF+
'    virtual bool predict(bool use_top) {'+CRLF+
'       bool result = false;'+CRLF+
'       if (!this->Calculated && this->Depth == this->MaxDepth) {'+CRLF+
'           this->Calculated = calc_predictor(use_top);'+CRLF+
'       }'+CRLF+
'       if (this->Calculated) {'+CRLF+
'           apply_predictor(use_top);'+CRLF+
'           result = true;'+CRLF+
'       }'+CRLF+
'       if (result) this->HasPredicted = true;'+CRLF+
'       return result;'+CRLF+
'    };'+CRLF+
'    virtual void correct() {'+CRLF+
'       omp_set_lock(&this->Lock);'+CRLF+
'       if (this->Calculated && this->HasPredicted) {'+CRLF+
'           double eps = 0.0;'+CRLF+
'           int nn = 0;'+CRLF+
'           for (int i = 0; i < this->N; i++)'+CRLF+
'			   if (!this->Mask || this->Mask[i]) {'+CRLF+
'				   if (this->Data[i] != (Type) 0.0) {'+CRLF+
'					   eps += fabs(1.0*(this->Predicted[i] - this->Data[i]) / this->Data[i]);'+CRLF+
'					   nn++;'+CRLF+
'				   }'+CRLF+
'			   }'+CRLF+
'           if (nn > 0) eps /= nn;'+CRLF+
'           if (eps > this->rel_eps)'+CRLF+
'              this->Calculated = false;'+CRLF+
'       }'+CRLF+
'       omp_unset_lock(&this->Lock);'+CRLF+
'    };'+CRLF+
'    virtual void LOCK() {'+CRLF+
'       omp_set_lock(&this->Lock);'+CRLF+
'       for (unsigned int j = 0; j < this->refs.size(); j++) {'+CRLF+
'           _funnel_with_history<Type> * REF = reinterpret_cast<_funnel_with_history<Type> *>(this->refs[j]);'+CRLF+
'           omp_set_lock(&(REF->Lock));'+CRLF+
'       }'+CRLF+
'    }'+CRLF+
'    virtual void UNLOCK() {'+CRLF+
'       omp_unset_lock(&this->Lock);'+CRLF+
'       for (unsigned int j = 0; j < this->refs.size(); j++) {'+CRLF+
'           _funnel_with_history<Type> * REF = reinterpret_cast<_funnel_with_history<Type> *>(refs[j]);'+CRLF+
'           omp_unset_lock(&(REF->Lock));'+CRLF+
'       }'+CRLF+
'    }'+CRLF+
'    virtual ~_funnel_perceptron() {'+CRLF+
'       for (int i = 0; i < this->N; i++)'+CRLF+
'           free((void *) K[i]);'+CRLF+
'       free((void *) K);'+CRLF+
'       if (K1) {'+CRLF+
'          for (int i = 0; i < this->N; i++)'+CRLF+
'              free((void *) K1[i]);'+CRLF+
'          free((void *) K1);'+CRLF+
'       }'+CRLF+
'       if (K2) {'+CRLF+
'          for (int i = 0; i < this->N; i++)'+CRLF+
'              free((void *) K2[i]);'+CRLF+
'          free((void *) K2);'+CRLF+
'       }'+CRLF+
'       for (int i = 0; i < this->N; i++)'+CRLF+
'           free((void *) C[i]);'+CRLF+
'       free((void *) C);'+CRLF+
'       if (C1) {'+CRLF+
'          for (int i = 0; i < this->N; i++)'+CRLF+
'              free((void *) C1[i]);'+CRLF+
'          free((void *) C1);'+CRLF+
'       }'+CRLF+
'       if (C2) {'+CRLF+
'          for (int i = 0; i < this->N; i++)'+CRLF+
'              free((void *) C2[i]);'+CRLF+
'          free((void *) C2);'+CRLF+
'       }'+CRLF+
'       if (hasB) {'+CRLF+
'          free((void *) B);'+CRLF+
'          free((void *) B1);'+CRLF+
'          free((void *) B2);'+CRLF+
'       }'+CRLF+
'       free((void *) nstart);'+CRLF+
'       free((void *) nend);'+CRLF+
'       delete[] iRow;'+CRLF+
'       delete[] A;'+CRLF+
'       delete[] LU;'+CRLF+
'       delete[] Y;'+CRLF+
'       delete[] X;'+CRLF+
'    };'+CRLF+
' };'+CRLF+
' template<class Type>'+CRLF+
'  class _funnel_explicit_perceptron: public _funnel_perceptron<Type> {'+CRLF+
'  protected:'+CRLF+
'    virtual bool calc_predictor(bool use_top) {'+CRLF+
'       int corr = use_top ? 0 : 1;'+CRLF+
'       int P1 = this->PATTERN + 1;'+CRLF+
'       int P2 = this->N - this->PATTERN - 2;'+CRLF+
'       vector<int> Qs;'+CRLF+
'       if (this->PATTERN < 0 || 2*this->N <= this->PATTERN) {'+CRLF+
'          for (int i = 0; i < this->N; i++)'+CRLF+
'              Qs.push_back(i);'+CRLF+
'       } else {'+CRLF+
'          Qs.push_back(P1);'+CRLF+
'          Qs.push_back(P2);'+CRLF+
'          for (int i = 0; i <= this->PATTERN; i++) {'+CRLF+
'              Qs.push_back(i);'+CRLF+
'              Qs.push_back(this->N - i - 1);'+CRLF+
'          }'+CRLF+
'       }'+CRLF+
'	   for (unsigned int q = 0; q < this->N; q++) {'+CRLF+
'		   this->nstart[q] = -1;'+CRLF+
'		   this->nend[q] = -1;'+CRLF+
'	   }'+CRLF+
'       for (unsigned int qs = 0; qs < Qs.size(); qs++) {'+CRLF+
'           int q = Qs[qs];'+CRLF+
'		   if (this->Mask && !this->Mask[q])'+CRLF+
'			   continue;'+CRLF+
'           double max_err = 1E300;'+CRLF+
'           int bb = this->hasB ? 1 : 0;'+CRLF+
'           vector<int> Ps;'+CRLF+
'           vector<int> referers;'+CRLF+
'           int ND = this->MaxDepth - corr; '+CRLF+
'           for (int j = 0; j < this->refs.size(); j++) {'+CRLF+
'               _funnel_with_history<Type> * REF = reinterpret_cast<_funnel_with_history<Type> *>(this->refs[j]);'+CRLF+
'               int _corr = (REF->State & tnlValue) ? 2 : 1;'+CRLF+
'               int D = REF->getMaxDepth();'+CRLF+
'               if (D - _corr < ND) ND = D - _corr;'+CRLF+
'           }'+CRLF+
'           double avr = 0.0;'+CRLF+
'           for (int k = 1; k < ND; k++) {'+CRLF+
'               avr +=this->History[k + (this->MaxDepth - corr) - ND - 1][q];'+CRLF+
'           }'+CRLF+
'           avr /= (ND - 1);'+CRLF+
'           double sumq = 0.0;'+CRLF+
'           for (int k = 1; k < ND; k++) {'+CRLF+
'               sumq += pow(this->History[k + (this->MaxDepth - corr) - ND - 1][q] - avr, 2);'+CRLF+
'           }'+CRLF+
'           for (int i = 0; i < this->refs.size(); i++) {'+CRLF+
'               _funnel_with_history<Type> * REF = reinterpret_cast<_funnel_with_history<Type> *>(this->refs[i]);'+CRLF+
'               int _corr = (REF->State & tnlValue) ? 2 : 1;'+CRLF+
'               Type ** H = REF->getHistory();'+CRLF+
'               int D = REF->getMaxDepth();'+CRLF+
'               double ravr = 0.0;'+CRLF+
'               for (int k = 1; k < ND; k++) {'+CRLF+
'                   ravr += H[k + D - ND - _corr][q];'+CRLF+
'               }'+CRLF+
'               ravr /= (ND - 1);'+CRLF+
'               double nominator = 0.0;'+CRLF+
'               double denominator = 0.0;'+CRLF+
'               for (int k = 1; k < ND; k++) {'+CRLF+
'                  nominator += (this->History[k + (this->MaxDepth - corr) - ND - 1][q] - avr)*(H[k + D - ND - _corr][q] - ravr);'+CRLF+
'                  denominator += pow(H[k + D - ND - _corr][q] - ravr, 2);'+CRLF+
'               }'+CRLF+
'               denominator = sqrt(sumq*denominator);'+CRLF+
'               if (fabs(nominator) > 0.01*fabs(denominator))'+CRLF+
'                  referers.push_back(i);'+CRLF+
'           }'+CRLF+
'           for (int i = (this->PATTERN < 0 ? this->N : __min(this->N, this->PATTERN)) + referers.size() + bb; i > referers.size() + 3 + bb; ) {'+CRLF+
'               Ps.push_back(i);'+CRLF+
'               if ((i - referers.size() - bb) % 2 == 0)'+CRLF+
'                  i--;'+CRLF+
'               else'+CRLF+
'                  i -= 2;'+CRLF+
'           }'+CRLF+
'           for (int i = (this->PATTERN < 0 ? 3 : this->PATTERN) + bb; i >= 1 + bb; i--)'+CRLF+
'               Ps.push_back(referers.size() + i);'+CRLF+
'           this->nstart[q] = -1;'+CRLF+
'           this->nend[q] = -1;'+CRLF+
'           for (unsigned int pp = 0; pp < Ps.size(); pp++) {'+CRLF+
'               int NN = Ps[pp] - referers.size() - bb;'+CRLF+
'               memset(this->A, 0, this->MaxP*this->MaxP*sizeof(long double));'+CRLF+
'               memset(this->Y, 0, this->MaxP*sizeof(long double));'+CRLF+
'               int start = NN == 0 ? q : (q - (NN-1)/2 < 0 ? 0 : q - (NN-1)/2);'+CRLF+
'               int end = NN == 0 ? q-1 : (q + (NN-1)/2 >= this->N ? this->N-1 : q + (NN-1)/2);'+CRLF+
'               NN = (end - start) + 1;'+CRLF+
'               int ND = this->MaxDepth - corr; '+CRLF+
'               for (int j = 0; j < referers.size(); j++) {'+CRLF+
'                   _funnel_with_history<Type> * REF = reinterpret_cast<_funnel_with_history<Type> *>(this->refs[referers[j]]);'+CRLF+
'                   int _corr = (REF->State & tnlValue) ? 2 : 1;'+CRLF+
'                   int D = REF->getMaxDepth();'+CRLF+
'                   if (D - _corr < ND) ND = D - _corr;'+CRLF+
'               }'+CRLF+
'               int ptr = 0;'+CRLF+
'               for (int i = 0; i < NN; i++) {'+CRLF+
'                   for (int j = 0; j < NN; j++, ptr++) {'+CRLF+
'                       this->A[ptr] = 0.0;'+CRLF+
'                       for (int k = this->MaxDepth - corr - ND + 1; k < this->MaxDepth - corr; k++)'+CRLF+
'                           this->A[ptr] +=this->History[k-1][start + i]*this->History[k-1][start + j];'+CRLF+
'                   }'+CRLF+
'                   this->Y[i] = 0.0;'+CRLF+
'                   if (this->hasB) this->A[ptr] = 0.0;'+CRLF+
'                   for (int k = this->MaxDepth - corr - ND + 1; k < this->MaxDepth - corr; k++) {'+CRLF+
'                       if (this->hasB) this->A[ptr] -=this->History[k-1][start + i];'+CRLF+
'                       this->Y[i] -= this->History[k-1][start + i]*this->History[k][q];'+CRLF+
'                   }'+CRLF+
'                   if (this->hasB) ptr++;'+CRLF+
'                   for (int j = 0; j < referers.size(); j++, ptr++) {'+CRLF+
'                       _funnel_with_history<Type> * REF = reinterpret_cast<_funnel_with_history<Type> *>(this->refs[referers[j]]);'+CRLF+
'                       int _corr = (REF->State & tnlValue) ? 2 : 1;'+CRLF+
'                       Type ** H = REF->getHistory();'+CRLF+
'                       int D = REF->getMaxDepth();'+CRLF+
'                       this->A[ptr] = 0.0;'+CRLF+
'                       for (int k = 1; k < ND; k++) {'+CRLF+
'                           this->A[ptr] +=this->History[k + (this->MaxDepth - corr) - ND - 1][start + i]*H[k + D - ND - _corr][q];'+CRLF+
'                       }'+CRLF+
'                   }'+CRLF+
'               }'+CRLF+
'               if (this->hasB) {'+CRLF+
'                  for (int j = 0; j < NN; j++, ptr++) {'+CRLF+
'                      this->A[ptr] = 0.0;'+CRLF+
'                      for (int k = this->MaxDepth - corr - ND + 1; k < this->MaxDepth - corr; k++)'+CRLF+
'                          this->A[ptr] += -this->History[k-1][start + j];'+CRLF+
'                  }'+CRLF+
'                  this->A[ptr] = 0.0;'+CRLF+
'                  this->Y[NN] = 0.0;'+CRLF+
'                  for (int k = this->MaxDepth - corr - ND + 1; k < this->MaxDepth - corr; k++) {'+CRLF+
'                      this->A[ptr] -= -1;'+CRLF+
'                      this->Y[NN] +=this->History[k][q];'+CRLF+
'                  }'+CRLF+
'                  ptr++;'+CRLF+
'                  for (int j = 0; j < referers.size(); j++, ptr++) {'+CRLF+
'                      _funnel_with_history<Type> * REF = reinterpret_cast<_funnel_with_history<Type> *>(this->refs[referers[j]]);'+CRLF+
'                      int _corr = (REF->State & tnlValue) ? 2 : 1;'+CRLF+
'                      Type ** H = REF->getHistory();'+CRLF+
'                      int D = REF->getMaxDepth();'+CRLF+
'                      this->A[ptr] = 0.0;'+CRLF+
'                      for (int k = 1; k < ND; k++) {'+CRLF+
'                          this->A[ptr] += -H[k + D - ND - _corr][q];'+CRLF+
'                      }'+CRLF+
'                  }'+CRLF+
'               }'+CRLF+
'               for (int i = 0; i < referers.size(); i++) {'+CRLF+
'                   _funnel_with_history<Type> * __REF = reinterpret_cast<_funnel_with_history<Type> *>(this->refs[referers[i]]);'+CRLF+
'                   int __corr = (__REF->State & tnlValue) ? 2 : 1;'+CRLF+
'                   Type ** __H = __REF->getHistory();'+CRLF+
'                   int __D = __REF->getMaxDepth();'+CRLF+
'                   for (int j = 0; j < NN; j++, ptr++) {'+CRLF+
'                       this->A[ptr] = 0.0;'+CRLF+
'                       for (int k = this->MaxDepth - corr - ND + 1, ck = __D - ND - __corr + 1; k < this->MaxDepth - corr; k++, ck++)'+CRLF+
'                           this->A[ptr] += __H[ck][q]*this->History[k - 1][start + j];'+CRLF+
'                   }'+CRLF+
'                   if (this->hasB) this->A[ptr] = 0.0;'+CRLF+
'                   this->Y[NN+i+bb] = 0.0;'+CRLF+
'                   for (int k = 1; k < ND; k++) {'+CRLF+
'                       if (this->hasB) this->A[ptr] -= __H[k + __D - ND - __corr][q];'+CRLF+
'                       this->Y[NN+i+bb] -= __H[k + __D - ND - __corr][q]*this->History[k + (this->MaxDepth - corr) - ND][q];'+CRLF+
'                   }'+CRLF+
'                   if (this->hasB) ptr++;'+CRLF+
'                   for (int j = 0; j < referers.size(); j++, ptr++) {'+CRLF+
'                       _funnel_with_history<Type> * REF = reinterpret_cast<_funnel_with_history<Type> *>(this->refs[referers[j]]);'+CRLF+
'                       int _corr = (REF->State & tnlValue) ? 2 : 1;'+CRLF+
'                       Type ** H = REF->getHistory();'+CRLF+
'                       int D = REF->getMaxDepth();'+CRLF+
'                       this->A[ptr] = 0.0;'+CRLF+
'                       for (int k = 1, ck = __D - ND - __corr + 1; k < ND; k++, ck++) {'+CRLF+
'                           this->A[ptr] += __H[ck][q]*H[k + D - ND - _corr][q];'+CRLF+
'                       }'+CRLF+
'                   }'+CRLF+
'               }'+CRLF+
'               bool result = (!this->useLU && _SolveGaussZeidel(NN+referers.size()+bb, this->iRow, this->A, this->LU, this->Y, this->X)) || _GetLU(NN+referers.size()+bb, this->iRow, this->A, this->LU) && _SolveLU(NN+referers.size()+bb, this->iRow, this->LU, this->Y, this->X);'+CRLF+
'               if (result) {'+CRLF+
'                  for (int i = 0, ptr = 0; result && i < NN + referers.size() + bb; i++) {'+CRLF+
'                      double val = 0.0;'+CRLF+
'                      for (int j = 0; result && j < NN + referers.size() + bb; j++, ptr++) {'+CRLF+
'                          if (this->X[j] != this->X[j]) result = false;'+CRLF+
'                          val += this->A[ptr]*this->X[j];'+CRLF+
'                      }'+CRLF+
'                      double r = fabs(val - this->Y[i]);'+CRLF+
'                      if (r != r || r > 1E-7)'+CRLF+
'                         result = false;'+CRLF+
'                  }'+CRLF+
'                  double cur_err = 1E300;'+CRLF+
'                  if (result) {'+CRLF+
'                     int cur_n = 0;'+CRLF+
'                     cur_err = 0.0;'+CRLF+
'                     for (int ii = 1; result && ii < ND; ii++) {'+CRLF+
'                         int i = this->MaxDepth - ND - corr + ii;'+CRLF+
'                         double val = 0.0;'+CRLF+
'                         for (int j = 0; j < NN; j++)'+CRLF+
'                             val += this->X[j]*((double) this->History[i - 1][start + j]);'+CRLF+
'                         if (this->hasB) val -= this->X[NN];'+CRLF+
'                         for (unsigned int j = 0; j < referers.size(); j++) {'+CRLF+
'                             _funnel_with_history<Type> * REF = reinterpret_cast<_funnel_with_history<Type> *>(this->refs[referers[j]]);'+CRLF+
'                             int _corr = (REF->State & tnlValue) ? 2 : 1;'+CRLF+
'                             Type ** H = REF->getHistory();'+CRLF+
'                             int D = REF->getMaxDepth();'+CRLF+
'                             val += this->X[NN+bb+j]*((long double) H[D - ND - _corr + ii][q]);'+CRLF+
'                         }'+CRLF+
'                         Type H = - (Type)this->History[i][q];'+CRLF+
'                         if (H != 0) {'+CRLF+
'                            cur_err += fabs(1.0*(H - (Type) val)/H);'+CRLF+
'                            cur_n++;'+CRLF+
'                         }'+CRLF+
'                     }'+CRLF+
'                     if (cur_n > 0) cur_err /= cur_n;'+CRLF+
'                  }'+CRLF+
'                  if (result) {'+CRLF+
'                     if (cur_err < this->rel_eps && cur_err <= max_err) {'+CRLF+
'                         this->nstart[q] = start;'+CRLF+
'                         this->nend[q] = end;'+CRLF+
'                         int ptr = 0;'+CRLF+
'                         for (int i = 0; i < NN; i++, ptr++)'+CRLF+
'                             this->K[q][i] = (double) this->X[ptr];'+CRLF+
'                         if (this->hasB) this->B[q] = (double) this->X[ptr++];'+CRLF+
'                         memset((void *) this->C[q], 0, this->refs.size()*sizeof(double));'+CRLF+
'                         for (int i = 0; i < referers.size(); i++, ptr++)'+CRLF+
'                             this->C[q][referers[i]] = (double) this->X[ptr];'+CRLF+
'                         max_err = cur_err;'+CRLF+
'                         result = pp == Ps.size() - 1;'+CRLF+
'                     }'+CRLF+
'                  }'+CRLF+
'               }'+CRLF+
'           }'+CRLF+
'       }'+CRLF+
'       if (this->PATTERN >= 0 && 2*this->N > this->PATTERN) {'+CRLF+
'          if (this->nstart[P1] >= 0 && this->nend[P1] >= 0 && this->nstart[P2] >= 0 && this->nend[P2] >= 0 &&'+CRLF+
'              this->nend[P1]-this->nstart[P1] == this->nend[P2]-this->nstart[P2] &&'+CRLF+
'              this->nend[P2]-this->nstart[P2]+1 == this->PATTERN) {'+CRLF+
'             for (int j = this->PATTERN + 1; j < this->N - this->PATTERN - 1; j++) {'+CRLF+
'                 if (j != P1 && j != P2) {'+CRLF+
'                    this->nstart[j] = j - this->PATTERN/2;'+CRLF+
'                    this->nend[j] = j + this->PATTERN/2;'+CRLF+
'                    for (int i = 0; i < this->PATTERN; i++)'+CRLF+
'                        this->K[j][i] = 0.5*(this->K[P1][i] + this->K[P2][i]);'+CRLF+
'                    if (this->hasB) this->B[j] = 0.5*(this->B[P1] + this->B[P2]);'+CRLF+
'                    memset((void *) this->C[j], 0, this->refs.size()*sizeof(double));'+CRLF+
'                    for (int i = 0; i < this->refs.size(); i++)'+CRLF+
'                        this->C[j][i] = 0.5*(this->C[P1][i] + this->C[P2][i]);'+CRLF+
'                 }'+CRLF+
'             }'+CRLF+
'          } else'+CRLF+
'             for (int i = this->PATTERN + 1; i < this->N - this->PATTERN - 1; i++) {'+CRLF+
'                 this->nstart[i] = -1;'+CRLF+
'                 this->nend[i] = -1;'+CRLF+
'             }'+CRLF+
'       }'+CRLF+
'       return true;'+CRLF+
'    };'+CRLF+
'    virtual void apply_predictor(bool use_top) {'+CRLF+
'       int corr = use_top ? 0 : 1;'+CRLF+
'       int np = omp_get_num_procs();'+CRLF+
'       #pragma omp parallel for schedule(static,__max(1,this->N/np)) if (this->N>100) num_threads(np)'+CRLF+
'       for (int i = 0; i < this->N; i++) {'+CRLF+
'           int start = this->nstart[i];'+CRLF+
'           int end = this->nend[i];'+CRLF+
'           if (start == -1 || end == -1)'+CRLF+
'              this->Predicted[i] = (Type)this->History[this->MaxDepth - corr - 1][i];'+CRLF+
'           else {'+CRLF+
'              int NN = end - start + 1;'+CRLF+
'              int ptr = 0;'+CRLF+
'              double val = 0.0;'+CRLF+
'              for (int j = 0; j < NN; j++)'+CRLF+
'                  val += this->K[i][j]*((double) this->History[this->MaxDepth - corr - 1][start + j]);'+CRLF+
'              if (this->hasB) val -= this->B[i];'+CRLF+
'              for (unsigned int j = 0; j < this->refs.size(); j++) {'+CRLF+
'                  _funnel_with_history<Type> * REF = reinterpret_cast<_funnel_with_history<Type> *>(this->refs[j]);'+CRLF+
'                  int _corr = (REF->State & tnlValue) ? 1 : 0;'+CRLF+
'                  Type ** H = REF->getHistory();'+CRLF+
'                  int D = REF->getMaxDepth();'+CRLF+
'                  val += this->C[i][j]*((long double) H[D - _corr - 1][i]);'+CRLF+
'              }'+CRLF+
'              this->Predicted[i] = - (Type) val;'+CRLF+
'           }'+CRLF+
'       }'+CRLF+
'    };'+CRLF+
'  public:'+CRLF+
'    _funnel_explicit_perceptron(bool hasB, const vector<_funnel<Type> *> &refs, int N = 1, double rel_eps = 0.001, const char * Name = NULL, int PATTERN = -1): _funnel_perceptron<Type>(hasB, refs, N, rel_eps, Name, PATTERN) {'+CRLF+
'    };'+CRLF+
' };'+CRLF+
' template<class Type>'+CRLF+
'  class _funnel_implicit_perceptron: public _funnel_perceptron<Type> {'+CRLF+
'  protected:'+CRLF+
'    virtual bool calc_predictor(bool use_top) {'+CRLF+
'       int corr = use_top ? 0 : 1;'+CRLF+
'       int P1 = this->PATTERN + 1;'+CRLF+
'       int P2 = this->N - this->PATTERN - 2;'+CRLF+
'       vector<int> Qs;'+CRLF+
'       if (this->PATTERN < 0 || 2*this->N <= this->PATTERN) {'+CRLF+
'          for (int i = 0; i < this->N; i++)'+CRLF+
'              Qs.push_back(i);'+CRLF+
'       } else {'+CRLF+
'          Qs.push_back(P1);'+CRLF+
'          Qs.push_back(P2);'+CRLF+
'          for (int i = 0; i <= this->PATTERN; i++) {'+CRLF+
'              Qs.push_back(i);'+CRLF+
'              Qs.push_back(this->N - i - 1);'+CRLF+
'          }'+CRLF+
'       }'+CRLF+
'	   for (unsigned int q = 0; q < this->N; q++) {'+CRLF+
'		   this->nstart[q] = -1;'+CRLF+
'		   this->nend[q] = -1;'+CRLF+
'	   }'+CRLF+
'	   for (unsigned int qs = 0; qs < Qs.size(); qs++) {'+CRLF+
'		   int q = Qs[qs];'+CRLF+
'		   if (this->Mask && !this->Mask[q])'+CRLF+
'			   continue;'+CRLF+
'           double max_err = 1E300;'+CRLF+
'           int bb = this->hasB ? 1 : 0;'+CRLF+
'           vector<int> Ps;'+CRLF+
'           vector<int> referers;'+CRLF+
'           int ND = this->MaxDepth - corr; '+CRLF+
'           for (int j = 0; j < this->refs.size(); j++) {'+CRLF+
'               _funnel_with_history<Type> * REF = reinterpret_cast<_funnel_with_history<Type> *>(this->refs[j]);'+CRLF+
'               int _corr = (REF->State & tnlValue) ? 2 : 1;'+CRLF+
'               int D = REF->getMaxDepth();'+CRLF+
'               if (D - _corr < ND) ND = D - _corr;'+CRLF+
'           }'+CRLF+
'           double avr = 0.0;'+CRLF+
'           for (int k = 1; k < ND; k++) {'+CRLF+
'               avr +=this->History[k + (this->MaxDepth - corr) - ND - 1][q];'+CRLF+
'           }'+CRLF+
'           avr /= (ND - 1);'+CRLF+
'           double sumq = 0.0;'+CRLF+
'           for (int k = 1; k < ND; k++) {'+CRLF+
'               sumq += pow(this->History[k + (this->MaxDepth - corr) - ND - 1][q] - avr, 2);'+CRLF+
'           }'+CRLF+
'           for (int i = 0; i < this->refs.size(); i++) {'+CRLF+
'               _funnel_with_history<Type> * REF = reinterpret_cast<_funnel_with_history<Type> *>(this->refs[i]);'+CRLF+
'               int _corr = (REF->State & tnlValue) ? 2 : 1;'+CRLF+
'               Type ** H = REF->getHistory();'+CRLF+
'               int D = REF->getMaxDepth();'+CRLF+
'               double ravr = 0.0;'+CRLF+
'               for (int k = 1; k < ND; k++) {'+CRLF+
'                   ravr += H[k + D - ND - _corr][q];'+CRLF+
'               }'+CRLF+
'               ravr /= (ND - 1);'+CRLF+
'               double nominator = 0.0;'+CRLF+
'               double denominator = 0.0;'+CRLF+
'               for (int k = 1; k < ND; k++) {'+CRLF+
'                  nominator += (this->History[k + (this->MaxDepth - corr) - ND - 1][q] - avr)*(H[k + D - ND - _corr][q] - ravr);'+CRLF+
'                  denominator += pow(H[k + D - ND - _corr][q] - ravr, 2);'+CRLF+
'               }'+CRLF+
'               denominator = sqrt(sumq*denominator);'+CRLF+
'               if (fabs(nominator) > 0.01*fabs(denominator))'+CRLF+
'                  referers.push_back(i);'+CRLF+
'           }'+CRLF+
'           for (int i = (this->PATTERN < 0 ? this->N : __min(this->N, this->PATTERN)) + referers.size() + bb; i > referers.size() + 3 + bb; ) {'+CRLF+
'               Ps.push_back(i);'+CRLF+
'               if ((i - referers.size() - bb) % 2 == 0)'+CRLF+
'                  i--;'+CRLF+
'               else'+CRLF+
'                  i -= 2;'+CRLF+
'           }'+CRLF+
'           for (int i = (this->PATTERN < 0 ? 3 : this->PATTERN) + bb; i >= 1 + bb; i--)'+CRLF+
'               Ps.push_back(referers.size() + i);'+CRLF+
'           this->nstart[q] = -1;'+CRLF+
'           this->nend[q] = -1;'+CRLF+
'           for (unsigned int pp = 0; pp < Ps.size(); pp++) {'+CRLF+
'               int NN = Ps[pp] - referers.size() - bb;'+CRLF+
'               memset(this->A, 0, this->MaxP*this->MaxP*sizeof(long double));'+CRLF+
'               memset(this->Y, 0, this->MaxP*sizeof(long double));'+CRLF+
'               int start = NN == 0 ? q : (q - (NN-1)/2 < 0 ? 0 : q - (NN-1)/2);'+CRLF+
'               int end = NN == 0 ? q-1 : (q + (NN-1)/2 >= this->N ? this->N-1 : q + (NN-1)/2);'+CRLF+
'               NN = (end - start) + 1;'+CRLF+
'               int ND = this->MaxDepth - corr; '+CRLF+
'               for (int j = 0; j < referers.size(); j++) {'+CRLF+
'                   _funnel_with_history<Type> * REF = reinterpret_cast<_funnel_with_history<Type> *>(this->refs[referers[j]]);'+CRLF+
'                   int _corr = (REF->State & tnlValue) ? 2 : 1;'+CRLF+
'                   int D = REF->getMaxDepth();'+CRLF+
'                   if (D - _corr < ND) ND = D - _corr;'+CRLF+
'               }'+CRLF+
'               int ptr = 0;'+CRLF+
'               for (int i = 0; i < NN; i++) {'+CRLF+
'                   for (int j = 0; j < NN; j++, ptr++) {'+CRLF+
'                       this->A[ptr] = 0.0;'+CRLF+
'                       for (int k = this->MaxDepth - corr - ND + 1; k < this->MaxDepth - corr; k++)'+CRLF+
'                           this->A[ptr] += this->History[k][start + i]*this->History[k][start + j];'+CRLF+
'                   }'+CRLF+
'                   this->Y[i] = 0.0;'+CRLF+
'                   if (this->hasB) this->A[ptr] = 0.0;'+CRLF+
'                   for (int k = this->MaxDepth - corr - ND + 1; k < this->MaxDepth - corr; k++) {'+CRLF+
'                       if (this->hasB) this->A[ptr] -= this->History[k][start + i];'+CRLF+
'                       this->Y[i] -= this->History[k][start + i]*this->History[k-1][q];'+CRLF+
'                   }'+CRLF+
'                   if (this->hasB) ptr++;'+CRLF+
'                   for (int j = 0; j < referers.size(); j++, ptr++) {'+CRLF+
'                       _funnel_with_history<Type> * REF = reinterpret_cast<_funnel_with_history<Type> *>(this->refs[referers[j]]);'+CRLF+
'                       int _corr = (REF->State & tnlValue) ? 2 : 1;'+CRLF+
'                       Type ** H = REF->getHistory();'+CRLF+
'                       int D = REF->getMaxDepth();'+CRLF+
'                       this->A[ptr] = 0.0;'+CRLF+
'                       for (int k = 1; k < ND; k++) {'+CRLF+
'                           this->A[ptr] += this->History[k + (this->MaxDepth - corr) - ND][start + i]*H[k + D - ND - _corr][q];'+CRLF+
'                       }'+CRLF+
'                   }'+CRLF+
'               }'+CRLF+
'               if (this->hasB) {'+CRLF+
'                  for (int j = 0; j < NN; j++, ptr++) {'+CRLF+
'                      this->A[ptr] = 0.0;'+CRLF+
'                      for (int k = this->MaxDepth - corr - ND + 1; k < this->MaxDepth - corr; k++)'+CRLF+
'                          this->A[ptr] += - this->History[k][start + j];'+CRLF+
'                  }'+CRLF+
'                  this->A[ptr] = 0.0;'+CRLF+
'                  this->Y[NN] = 0.0;'+CRLF+
'                  for (int k = this->MaxDepth - corr - ND + 1; k < this->MaxDepth - corr; k++) {'+CRLF+
'                      this->A[ptr] -= -1;'+CRLF+
'                      this->Y[NN] += this->History[k-1][q];'+CRLF+
'                  }'+CRLF+
'                  ptr++;'+CRLF+
'                  for (int j = 0; j < referers.size(); j++, ptr++) {'+CRLF+
'                      _funnel_with_history<Type> * REF = reinterpret_cast<_funnel_with_history<Type> *>(this->refs[referers[j]]);'+CRLF+
'                      int _corr = (REF->State & tnlValue) ? 2 : 1;'+CRLF+
'                      Type ** H = REF->getHistory();'+CRLF+
'                      int D = REF->getMaxDepth();'+CRLF+
'                      this->A[ptr] = 0.0;'+CRLF+
'                      for (int k = 1; k < ND; k++) {'+CRLF+
'                          this->A[ptr] += -H[k + D - ND - _corr][q];'+CRLF+
'                      }'+CRLF+
'                  }'+CRLF+
'               }'+CRLF+
'               for (int i = 0; i < referers.size(); i++) {'+CRLF+
'                   _funnel_with_history<Type> * __REF = reinterpret_cast<_funnel_with_history<Type> *>(this->refs[referers[i]]);'+CRLF+
'                   int __corr = (__REF->State & tnlValue) ? 2 : 1;'+CRLF+
'                   Type ** __H = __REF->getHistory();'+CRLF+
'                   int __D = __REF->getMaxDepth();'+CRLF+
'                   for (int j = 0; j < NN; j++, ptr++) {'+CRLF+
'                       this->A[ptr] = 0.0;'+CRLF+
'                       for (int k = this->MaxDepth - corr - ND + 1, ck = __D - ND - __corr + 1; k < this->MaxDepth - corr; k++, ck++)'+CRLF+
'                           this->A[ptr] += __H[ck][q]*this->History[k][start + j];'+CRLF+
'                   }'+CRLF+
'                   if (this->hasB) this->A[ptr] = 0.0;'+CRLF+
'                   this->Y[NN+i+bb] = 0.0;'+CRLF+
'                   for (int k = 1; k < ND; k++) {'+CRLF+
'                       if (this->hasB) this->A[ptr] -= __H[k + __D - ND - __corr][q];'+CRLF+
'                       this->Y[NN+i+bb] -= __H[k + __D - ND - __corr][q]*this->History[k + (this->MaxDepth - corr) - ND - 1][q];'+CRLF+
'                   }'+CRLF+
'                   if (this->hasB) ptr++;'+CRLF+
'                   for (int j = 0; j < referers.size(); j++, ptr++) {'+CRLF+
'                       _funnel_with_history<Type> * REF = reinterpret_cast<_funnel_with_history<Type> *>(this->refs[referers[j]]);'+CRLF+
'                       int _corr = (REF->State & tnlValue) ? 2 : 1;'+CRLF+
'                       Type ** H = REF->getHistory();'+CRLF+
'                       int D = REF->getMaxDepth();'+CRLF+
'                       this->A[ptr] = 0.0;'+CRLF+
'                       for (int k = 1, ck = __D - ND - __corr + 1; k < ND; k++, ck++) {'+CRLF+
'                           this->A[ptr] += __H[ck][q]*H[k + D - ND - _corr][q];'+CRLF+
'                       }'+CRLF+
'                   }'+CRLF+
'               }'+CRLF+
'               bool result = (!this->useLU && _SolveGaussZeidel(NN+referers.size()+bb, this->iRow, this->A, this->LU, this->Y, this->X)) || _GetLU(NN+referers.size()+bb, this->iRow, this->A, this->LU) && _SolveLU(NN+referers.size()+bb, this->iRow, this->LU, this->Y, this->X);'+CRLF+
'               if (result) {'+CRLF+
'                  for (int i = 0, ptr = 0; result && i < NN + referers.size() + bb; i++) {'+CRLF+
'                      double val = 0.0;'+CRLF+
'                      for (int j = 0; result && j < NN + referers.size() + bb; j++, ptr++) {'+CRLF+
'                          if (this->X[j] != this->X[j]) result = false;'+CRLF+
'                          val += this->A[ptr]*this->X[j];'+CRLF+
'                      }'+CRLF+
'                      double r = fabs(val - this->Y[i]);'+CRLF+
'                      if (r != r || r > 1E-7)'+CRLF+
'                         result = false;'+CRLF+
'                  }'+CRLF+
'                  double cur_err = 1E300;'+CRLF+
'                  if (result) {'+CRLF+
'                     int cur_n = 0;'+CRLF+
'                     cur_err = 0.0;'+CRLF+
'                     for (int ii = 1; result && ii < ND; ii++) {'+CRLF+
'                         int i = this->MaxDepth - ND - corr + ii;'+CRLF+
'                         double val = 0.0;'+CRLF+
'                         for (int j = 0; j < NN; j++)'+CRLF+
'                             val += this->X[j]*((double) this->History[i][start + j]);'+CRLF+
'                         if (this->hasB) val -= this->X[NN];'+CRLF+
'                         for (unsigned int j = 0; j < referers.size(); j++) {'+CRLF+
'                             _funnel_with_history<Type> * REF = reinterpret_cast<_funnel_with_history<Type> *>(this->refs[referers[j]]);'+CRLF+
'                             int _corr = (REF->State & tnlValue) ? 2 : 1;'+CRLF+
'                             Type ** H = REF->getHistory();'+CRLF+
'                             int D = REF->getMaxDepth();'+CRLF+
'                             val += this->X[NN+bb+j]*((long double) H[D - ND - _corr + ii][q]);'+CRLF+
'                         }'+CRLF+
'                         Type H = - (Type)this->History[i - 1][q];'+CRLF+
'                         if (H != 0) {'+CRLF+
'                            cur_err += fabs(1.0*(H - (Type) val)/H);'+CRLF+
'                            cur_n++;'+CRLF+
'                         }'+CRLF+
'                     }'+CRLF+
'                     if (cur_n > 0) cur_err /= cur_n;'+CRLF+
'                  }'+CRLF+
'                  if (result) {'+CRLF+
'                     if (cur_err < this->rel_eps && cur_err <= max_err) {'+CRLF+
'                         this->nstart[q] = start;'+CRLF+
'                         this->nend[q] = end;'+CRLF+
'                         int ptr = 0;'+CRLF+
'                         for (int i = 0; i < NN; i++, ptr++)'+CRLF+
'                             this->K[q][i] = (double) this->X[ptr];'+CRLF+
'                         if (this->hasB) this->B[q] = (double) this->X[ptr++];'+CRLF+
'                         memset((void *) this->C[q], 0, this->refs.size()*sizeof(double));'+CRLF+
'                         for (int i = 0; i < referers.size(); i++, ptr++)'+CRLF+
'                             this->C[q][referers[i]] = (double) this->X[ptr];'+CRLF+
'                         max_err = cur_err;'+CRLF+
'                         result = pp == Ps.size() - 1;'+CRLF+
'                     }'+CRLF+
'                  }'+CRLF+
'               }'+CRLF+
'           }'+CRLF+
'       }'+CRLF+
'       if (this->PATTERN >= 0 && 2*this->N > this->PATTERN) {'+CRLF+
'          if (this->nstart[P1] >= 0 && this->nend[P1] >= 0 && this->nstart[P2] >= 0 && this->nend[P2] >= 0 &&'+CRLF+
'              this->nend[P1]-this->nstart[P1] == this->nend[P2]-this->nstart[P2] &&'+CRLF+
'              this->nend[P2]-this->nstart[P2]+1 == this->PATTERN) {'+CRLF+
'             for (int j = this->PATTERN + 1; j < this->N - this->PATTERN - 1; j++) {'+CRLF+
'                 if (j != P1 && j != P2) {'+CRLF+
'                    this->nstart[j] = j - this->PATTERN/2;'+CRLF+
'                    this->nend[j] = j + this->PATTERN/2;'+CRLF+
'                    for (int i = 0; i < this->PATTERN; i++)'+CRLF+
'                        this->K[j][i] = 0.5*(this->K[P1][i] + this->K[P2][i]);'+CRLF+
'                    if (this->hasB) this->B[j] = 0.5*(this->B[P1] + this->B[P2]);'+CRLF+
'                    memset((void *) this->C[j], 0, this->refs.size()*sizeof(double));'+CRLF+
'                    for (int i = 0; i < this->refs.size(); i++)'+CRLF+
'                        this->C[j][i] = 0.5*(this->C[P1][i] + this->C[P2][i]);'+CRLF+
'                 }'+CRLF+
'             }'+CRLF+
'          } else'+CRLF+
'             for (int i = this->PATTERN + 1; i < this->N - this->PATTERN - 1; i++) {'+CRLF+
'                 this->nstart[i] = -1;'+CRLF+
'                 this->nend[i] = -1;'+CRLF+
'             }'+CRLF+
'       }'+CRLF+
'       return true;'+CRLF+
'    };'+CRLF+
'    virtual void apply_predictor(bool use_top) {'+CRLF+
'       int corr = use_top ? 0 : 1;'+CRLF+
'       int np = omp_get_num_procs();'+CRLF+
'       memset(this->A, 0, this->MaxP*this->MaxP*sizeof(long double));'+CRLF+
'       memset(this->Y, 0, this->MaxP*sizeof(long double));'+CRLF+
'       #pragma omp parallel for schedule(static,__max(1,this->N/np)) num_threads(np) if (this->N>100)'+CRLF+
'       for (int p = 0; p < this->N; p++) {'+CRLF+
'           int start = this->nstart[p];'+CRLF+
'           int end = this->nend[p];'+CRLF+
'           if (start == -1 || end == -1) {'+CRLF+
'              this->A[p*this->N + p] = 1.0;'+CRLF+
'              this->Y[p] = (Type)this->History[this->MaxDepth - corr - 1][p];'+CRLF+
'           } else {'+CRLF+
'              int NN = end - start + 1;'+CRLF+
'              for (int k = 0, ptr = p*this->N + start; k < NN; k++, ptr++) {'+CRLF+
'                  this->A[ptr] = (long double) this->K[p][k];'+CRLF+
'              }'+CRLF+
'              this->Y[p] = (this->hasB ? this->B[p] : 0.0) - (long double)this->History[this->MaxDepth - corr - 1][p];'+CRLF+
'              for (unsigned int j = 0; j < this->refs.size(); j++) {'+CRLF+
'                  _funnel_with_history<Type> * REF = reinterpret_cast<_funnel_with_history<Type> *>(this->refs[j]);'+CRLF+
'                  int _corr = (REF->State & tnlValue) ? 1 : 0;'+CRLF+
'                  Type ** H = REF->getHistory();'+CRLF+
'                  int D = REF->getMaxDepth();'+CRLF+
'                  this->Y[p] -= this->C[p][j]*((long double) H[D - _corr - 1][p]);'+CRLF+
'              }'+CRLF+
'           }'+CRLF+
'       }'+CRLF+
'       bool result = (!this->useLU && _SolveGaussZeidel(this->N, this->iRow, this->A, this->LU, this->Y, this->X)) || _GetLU(this->N, this->iRow, this->A, this->LU) && _SolveLU(this->N, this->iRow, this->LU, this->Y, this->X);'+CRLF+
'       for (int i = 0; result && i < this->N; i++)'+CRLF+
'           if (this->X[i] != this->X[i])'+CRLF+
'              result = false;'+CRLF+
'       if (result) {'+CRLF+
'          for (int i = 0; i < this->N; i++) {'+CRLF+
'              this->Predicted[i] = (Type) this->X[i];'+CRLF+
'          }'+CRLF+
'       } else {'+CRLF+
'          for (int i = 0; i < this->N; i++) {'+CRLF+
'              this->Predicted[i] = (Type)this->History[this->MaxDepth - corr - 1][i];'+CRLF+
'          }'+CRLF+
'       }'+CRLF+
'    };'+CRLF+
'  public:'+CRLF+
'    _funnel_implicit_perceptron(bool hasB, const vector<_funnel<Type> *> &refs, int N = 1, double rel_eps = 0.001, const char * Name = NULL, int PATTERN = -1): _funnel_perceptron<Type>(hasB, refs, N, rel_eps, Name, PATTERN) {'+CRLF+
'    };'+CRLF+
' };'+CRLF+
' template<class Type>'+CRLF+
'  class funneled_base {'+CRLF+
'  private:'+CRLF+
'    _funnel<Type> * Ref;'+CRLF+
'  protected:'+CRLF+
'    virtual void init_data(__funnel * _Ref) = 0;'+CRLF+
'  public:'+CRLF+
'    virtual void wait() = 0;'+CRLF+
'    _funnel<Type> * getRef(const vector<_funnel<Type> *> * _refs = NULL) {'+CRLF+
'       if (Ref) Ref->add_refs(_refs);'+CRLF+
'       return Ref;'+CRLF+
'    };'+CRLF+
'    void setRef(_funnel<Type> * _Ref) {'+CRLF+
'      Ref = _Ref;'+CRLF+
'      if (Ref) {'+CRLF+
'         omp_set_lock(&Ref->Lock);'+CRLF+
'         Ref->Refs++;'+CRLF+
'         omp_unset_lock(&Ref->Lock);'+CRLF+
'      }'+CRLF+
'    };'+CRLF+
'    bool empty() {'+CRLF+
'      if (Ref) {'+CRLF+
'         bool result;'+CRLF+
'         omp_set_lock(&Ref->Lock);'+CRLF+
'         result = !(Ref->State & tnlValue);'+CRLF+
'         omp_unset_lock(&Ref->Lock);'+CRLF+
'         return result;'+CRLF+
'      } else'+CRLF+
'         return true;'+CRLF+
'    };'+CRLF+
'    bool ready() {'+CRLF+
'      if (Ref) {'+CRLF+
'         bool result;'+CRLF+
'         omp_set_lock(&Ref->Lock);'+CRLF+
'         result = (Ref->State & tnlHasIn) && (Ref->State & tnlHasOut);'+CRLF+
'         omp_unset_lock(&Ref->Lock);'+CRLF+
'         return result;'+CRLF+
'      } else'+CRLF+
'         return false;'+CRLF+
'    };'+CRLF+
'    void cancel(bool lock = true) {'+CRLF+
'      if (Ref) {'+CRLF+
'         if (lock) omp_set_lock(&Ref->Lock);'+CRLF+
'         Ref->State &= ~tnlValue;'+CRLF+
'         if (lock) omp_unset_lock(&Ref->Lock);'+CRLF+
'      }'+CRLF+
'    }'+CRLF+
'  };'+CRLF+
' template<class Type>'+CRLF+
'  class funneled_out;'+CRLF+
' template<class Type>'+CRLF+
'  class funneled_in: public funneled_base<Type> {'+CRLF+
'    friend class funneled_out<Type>;'+CRLF+
'  protected:'+CRLF+
'    virtual void init_data(__funnel * _Ref) {'+CRLF+
'       this->setRef(reinterpret_cast<_funnel<Type> *>(_Ref));'+CRLF+
'       omp_set_lock(&_Ref->Lock);'+CRLF+
'       if (_Ref->State & tnlHasIn) {'+CRLF+
'          cout<<"Funnel already has input"<<endl;'+CRLF+
'          exit(-1);'+CRLF+
'       }'+CRLF+
'       _Ref->State |= tnlHasIn;'+CRLF+
'       omp_unset_lock(&_Ref->Lock);'+CRLF+
'    };'+CRLF+
'  public:'+CRLF+
'    funneled_in(): funneled_in((void *)NULL) { };'+CRLF+
'    funneled_in(void * _Ref) {'+CRLF+
'       this->init_data(_Ref ? ((funneled_out<Type> *) _Ref)->getRef() : new _funnel<Type>(1));'+CRLF+
'    };'+CRLF+
'    funneled_in(int N) {'+CRLF+
'       this->init_data(new _funnel<Type>(N));'+CRLF+
'    }'+CRLF+
'    funneled_in(const char * Name, int N = 1) {'+CRLF+
'       omp_set_lock(&__funnel_lock__);'+CRLF+
'       map<string,__funnel *>::iterator itFunnels = __Funnels.find(Name);'+CRLF+
'       if (itFunnels == __Funnels.end()) {'+CRLF+
'          __funnel * funnel = new _funnel<Type>(N, Name);'+CRLF+
'          this->init_data(funnel);'+CRLF+
'          __Funnels[Name] = funnel;'+CRLF+
'       } else {'+CRLF+
'          this->init_data(itFunnels->second);'+CRLF+
'       }'+CRLF+
'       omp_unset_lock(&__funnel_lock__);'+CRLF+
'    }'+CRLF+
'    virtual ~funneled_in() {'+CRLF+
'       _funnel<Type> * Ref = this->getRef();'+CRLF+
'       if (Ref) {'+CRLF+
'          omp_set_lock(&Ref->Lock);'+CRLF+
'          while (Ref->State & tnlValue) {'+CRLF+
'             omp_unset_lock(&Ref->Lock);'+CRLF+
'             _Yield();'+CRLF+
'             omp_set_lock(&Ref->Lock);'+CRLF+
'          }'+CRLF+
'          Ref->State &= ~tnlHasIn;'+CRLF+
'          Ref->Refs--;'+CRLF+
'          if (Ref->Refs == 0) {'+CRLF+
'             omp_unset_lock(&Ref->Lock);'+CRLF+
'             delete Ref;'+CRLF+
'          }'+CRLF+
'          else omp_unset_lock(&Ref->Lock);'+CRLF+
'       }'+CRLF+
'    };'+CRLF+
'    virtual void wait() {'+CRLF+
'      _funnel<Type> * Ref = this->getRef();'+CRLF+
'      if (Ref) {'+CRLF+
'         omp_set_lock(&Ref->Lock);'+CRLF+
'         while (!(Ref->State & tnlHasOut)) {'+CRLF+
'           omp_unset_lock(&Ref->Lock);'+CRLF+
'           _Yield();'+CRLF+
'           omp_set_lock(&Ref->Lock);'+CRLF+
'         }'+CRLF+
'      }'+CRLF+
'    };'+CRLF+
'    virtual void get(void * Buf, int SizeInBytes) {'+CRLF+
'      _funnel<Type> * Ref = this->getRef();'+CRLF+
'      if (Ref) {'+CRLF+
'         wait();'+CRLF+
'         while (!(Ref->State & tnlValue)) {'+CRLF+
'            omp_unset_lock(&Ref->Lock);'+CRLF+
'            _Yield();'+CRLF+
'            omp_set_lock(&Ref->Lock);'+CRLF+
'         }'+CRLF+
'         memmove(Buf,(void *) Ref->Data,SizeInBytes);'+CRLF+
'         Ref->State &= ~tnlValue;'+CRLF+
'         omp_unset_lock(&Ref->Lock);'+CRLF+
'      }'+CRLF+
'    };'+CRLF+
'    Type operator * () {'+CRLF+
'      Type Result;'+CRLF+
'      get(&Result,sizeof(Result));'+CRLF+
'      return Result;'+CRLF+
'    };'+CRLF+
' };'+CRLF+
' template<class Type>'+CRLF+
'  class funneled_predictor_out;'+CRLF+
' template<class Type>'+CRLF+
'  class funneled_predictor_in: public funneled_in<Type> {'+CRLF+
'    friend class funneled_predictor_out<Type>;'+CRLF+
'  protected:'+CRLF+
'  public:'+CRLF+
'    funneled_predictor_in() { };'+CRLF+
'    funneled_predictor_in(int P, void * _Ref) {'+CRLF+
'       this->init_data(_Ref ? ((funneled_predictor_out<Type> *) _Ref)->getRef() : new _funnel_predictor<Type>(P));'+CRLF+
'    };'+CRLF+
'    funneled_predictor_in(int N, int P = 5, double rel_eps = 0.001) {'+CRLF+
'       this->init_data(new _funnel_predictor<Type>(P, N, rel_eps));'+CRLF+
'    }'+CRLF+
'    funneled_predictor_in(const char * Name, int N = 1, int P = 5, double rel_eps = 0.001) {'+CRLF+
'       omp_set_lock(&__funnel_lock__);'+CRLF+
'       map<string,__funnel *>::iterator itFunnels = __Funnels.find(Name);'+CRLF+
'       if (itFunnels == __Funnels.end()) {'+CRLF+
'          __funnel * funnel = new _funnel_predictor<Type>(P, N, rel_eps, Name);'+CRLF+
'          this->init_data(funnel);'+CRLF+
'          __Funnels[Name] = funnel;'+CRLF+
'       } else {'+CRLF+
'          this->init_data(itFunnels->second);'+CRLF+
'       }'+CRLF+
'       omp_unset_lock(&__funnel_lock__);'+CRLF+
'    }'+CRLF+
'    virtual void get(void * Buf, int SizeInBytes) {'+CRLF+
'      _funnel_with_history<Type> * Ref = reinterpret_cast< _funnel_with_history<Type> *>(this->getRef());'+CRLF+
'      if (Ref) {'+CRLF+
'         Ref->unset_predict_results();'+CRLF+
'         funneled_in<Type>::get(Buf, SizeInBytes);'+CRLF+
'      }'+CRLF+
'    }'+CRLF+
'    virtual void get_and_correct(void * Buf) {'+CRLF+
'      _funnel_with_history<Type> * Ref = reinterpret_cast< _funnel_with_history<Type> *>(this->getRef());'+CRLF+
'      if (Ref) {'+CRLF+
'         int SizeInBytes = Ref->getN()*sizeof(Type);'+CRLF+
'         funneled_in<Type>::get(Buf, SizeInBytes);'+CRLF+
'         Ref->correct();'+CRLF+
'         Ref->unset_predict_results();'+CRLF+
'      }'+CRLF+
'    }'+CRLF+
'    virtual void cancel_and_push(void * Buf) {'+CRLF+
'       _funnel_with_history<Type> * Ref = reinterpret_cast<_funnel_with_history<Type> *>(this->getRef());'+CRLF+
'       if (Ref) {'+CRLF+
'          wait();'+CRLF+
'          while (!(Ref->State & tnlValue)) {'+CRLF+
'             omp_unset_lock(&Ref->Lock);'+CRLF+
'             _Yield();'+CRLF+
'             omp_set_lock(&Ref->Lock);'+CRLF+
'          }'+CRLF+
'          Ref->State &= ~tnlValue;'+CRLF+
'          Ref->replace_top_history(Buf, false);'+CRLF+
'          omp_unset_lock(&Ref->Lock);'+CRLF+
'          Ref->unset_predict_results();'+CRLF+
'       }'+CRLF+
'    };'+CRLF+
'    virtual bool get_timed(void * Buf, double timeout_ms) {'+CRLF+
'      _funnel_with_history<Type> * Ref = reinterpret_cast< _funnel_with_history<Type> *>(this->getRef());'+CRLF+
'      if (Ref) {'+CRLF+
'         double t = omp_get_wtime();'+CRLF+
'         double timeout_s = 0.001*timeout_ms;'+CRLF+
'         int SizeInBytes = Ref->getN()*sizeof(Type);'+CRLF+
'         long counter = WAITING_COUNTER;'+CRLF+
'         bool prediction = true;'+CRLF+
'         wait();'+CRLF+
'         do {'+CRLF+
'            omp_unset_lock(&Ref->Lock);'+CRLF+
'            if (counter == WAITING_COUNTER) {'+CRLF+
'                double elapsed = omp_get_wtime() - t;'+CRLF+
'                if (elapsed >= timeout_s && prediction) {'+CRLF+
'                   Ref->LOCK();'+CRLF+
'                   prediction = Ref->predict(!(Ref->State & tnlValue));'+CRLF+
'                   if (prediction) {'+CRLF+
'                       memmove(Buf,(void *) Ref->getPredicted(),SizeInBytes);'+CRLF+
'                       Ref->UNLOCK();'+CRLF+
'                       return true;'+CRLF+
'                   }'+CRLF+
'                   Ref->UNLOCK();'+CRLF+
'                }'+CRLF+
'                counter = 0;'+CRLF+
'            } else'+CRLF+
'               counter++;'+CRLF+
'            _Yield();'+CRLF+
'            omp_set_lock(&Ref->Lock);'+CRLF+
'         } while (!(Ref->State & tnlValue));'+CRLF+
'         memmove(Buf,(void *) Ref->Data,SizeInBytes);'+CRLF+
'         Ref->State &= ~tnlValue;'+CRLF+
'         omp_unset_lock(&Ref->Lock);'+CRLF+
'      }'+CRLF+
'      return false;'+CRLF+
'    };'+CRLF+
' };'+CRLF+
' template<class Type>'+CRLF+
'  class funneled_perceptron_out;'+CRLF+
' template<class Type>'+CRLF+
'  class funneled_perceptron_in: public funneled_predictor_in<Type> {'+CRLF+
'    friend class funneled_perceptron_out<Type>;'+CRLF+
'  protected:'+CRLF+
'  public:'+CRLF+
'    funneled_perceptron_in() { throw Exception("Empty constructor of funnel-perceptron-in called"); };'+CRLF+
'    funneled_perceptron_in(bool _explicit, bool hasB, const vector<_funnel<Type> *> &refs, int N, void * _Ref, int PATTERN = -1) {'+CRLF+
'       if (_explicit)'+CRLF+
'          this->init_data(_Ref ? ((funneled_predictor_out<Type> *) _Ref)->getRef(&refs) : new _funnel_explicit_perceptron<Type>(hasB, refs, N, 0.001, NULL, PATTERN));'+CRLF+
'       else'+CRLF+
'          this->init_data(_Ref ? ((funneled_predictor_out<Type> *) _Ref)->getRef(&refs) : new _funnel_implicit_perceptron<Type>(hasB, refs, N, 0.001, NULL, PATTERN));'+CRLF+
'    };'+CRLF+
'    funneled_perceptron_in(bool _explicit, bool hasB, const vector<_funnel<Type> *> &refs, const char * Name, int N = 1, double rel_eps = 0.001, int PATTERN = -1) {'+CRLF+
'       omp_set_lock(&__funnel_lock__);'+CRLF+
'       map<string,__funnel *>::iterator itFunnels = __Funnels.find(Name);'+CRLF+
'       if (itFunnels == __Funnels.end()) {'+CRLF+
'          __funnel * funnel = _explicit ? (__funnel *) new _funnel_explicit_perceptron<Type>(hasB, refs, N, rel_eps, Name, PATTERN) : (__funnel *) new _funnel_implicit_perceptron<Type>(hasB, refs, N, rel_eps, Name, PATTERN);'+CRLF+
'          this->init_data(funnel);'+CRLF+
'          __Funnels[Name] = funnel;'+CRLF+
'       } else {'+CRLF+
'          reinterpret_cast< _funnel_perceptron<Type> * >(itFunnels->second)->add_refs(&refs);'+CRLF+
'          this->init_data(itFunnels->second);'+CRLF+
'       }'+CRLF+
'       omp_unset_lock(&__funnel_lock__);'+CRLF+
'    }'+CRLF+
' };'+CRLF+
' template<class Type>'+CRLF+
'  class funneled_out: public funneled_base<Type> {'+CRLF+
'    friend class funneled_in<Type>;'+CRLF+
'  protected:'+CRLF+
'    void init_data(__funnel * _Ref) {'+CRLF+
'       this->setRef(reinterpret_cast<_funnel<Type> *>(_Ref));'+CRLF+
'       omp_set_lock(&_Ref->Lock);'+CRLF+
'       if (_Ref->State & tnlHasOut) {'+CRLF+
'          cout<<"Funnel already has output"<<endl;'+CRLF+
'          exit(-1);'+CRLF+
'       }'+CRLF+
'       _Ref->State |= tnlHasOut;'+CRLF+
'       omp_unset_lock(&_Ref->Lock);'+CRLF+
'    };'+CRLF+
'  public:'+CRLF+
'    funneled_out(): funneled_out((void *)NULL) { };'+CRLF+
'    funneled_out(void * _Ref) {'+CRLF+
'       this->init_data(_Ref ? ((funneled_in<Type> *) _Ref)->getRef() : new _funnel<Type>(1));'+CRLF+
'    };'+CRLF+
'    funneled_out(int N) {'+CRLF+
'       this->init_data(new _funnel<Type>(N));'+CRLF+
'    }'+CRLF+
'    funneled_out(const char * Name, int N = 1) {'+CRLF+
'       omp_set_lock(&__funnel_lock__);'+CRLF+
'       map<string,__funnel *>::iterator itFunnels = __Funnels.find(Name);'+CRLF+
'       if (itFunnels == __Funnels.end()) {'+CRLF+
'          __funnel * funnel = new _funnel<Type>(N, Name);'+CRLF+
'          this->init_data(funnel);'+CRLF+
'          __Funnels[Name] = funnel;'+CRLF+
'       } else {'+CRLF+
'          this->init_data(itFunnels->second);'+CRLF+
'       }'+CRLF+
'       omp_unset_lock(&__funnel_lock__);'+CRLF+
'    }'+CRLF+
'    virtual ~funneled_out() {'+CRLF+
'       _funnel<Type> * Ref = this->getRef();'+CRLF+
'       if (Ref) {'+CRLF+
'          omp_set_lock(&Ref->Lock);'+CRLF+
'          while (Ref->State & tnlValue) {'+CRLF+
'             omp_unset_lock(&Ref->Lock);'+CRLF+
'             _Yield();'+CRLF+
'             omp_set_lock(&Ref->Lock);'+CRLF+
'          }'+CRLF+
'          Ref->State &= ~tnlHasOut;'+CRLF+
'          Ref->Refs--;'+CRLF+
'          if (Ref->Refs == 0) {'+CRLF+
'             omp_unset_lock(&Ref->Lock);'+CRLF+
'             delete Ref;'+CRLF+
'          }'+CRLF+
'          else omp_unset_lock(&Ref->Lock);'+CRLF+
'       }'+CRLF+
'    };'+CRLF+
'    virtual void wait() {'+CRLF+
'      _funnel<Type> * Ref = this->getRef();'+CRLF+
'      if (Ref) {'+CRLF+
'         omp_set_lock(&Ref->Lock);'+CRLF+
'         while (!(Ref->State & tnlHasIn)) {'+CRLF+
'           omp_unset_lock(&Ref->Lock);'+CRLF+
'           _Yield();'+CRLF+
'           omp_set_lock(&Ref->Lock);'+CRLF+
'         }'+CRLF+
'      }'+CRLF+
'    };'+CRLF+
'    virtual void put(void * Buf, int SizeInBytes) {'+CRLF+
'      _funnel<Type> * Ref = this->getRef();'+CRLF+
'      if (Ref) {'+CRLF+
'         wait();'+CRLF+
'         while (Ref->State & tnlValue) {'+CRLF+
'            omp_unset_lock(&Ref->Lock);'+CRLF+
'            _Yield();'+CRLF+
'            omp_set_lock(&Ref->Lock);'+CRLF+
'         }'+CRLF+
'         if (SizeInBytes == 0)'+CRLF+
'            Ref->check_size(1);'+CRLF+
'         else'+CRLF+
'            Ref->check_size(SizeInBytes/sizeof(Type));'+CRLF+
'         memmove((void *) Ref->Data,Buf,SizeInBytes);'+CRLF+
'         Ref->State |= tnlValue;'+CRLF+
'         omp_unset_lock(&Ref->Lock);'+CRLF+
'      }'+CRLF+
'    };'+CRLF+
'    Type operator = (Type Val) {'+CRLF+
'      put(&Val,sizeof(Val));'+CRLF+
'      return Val;'+CRLF+
'    };'+CRLF+
' };'+CRLF+
' template<class Type>'+CRLF+
'  class funneled_predictor_out: public funneled_out<Type> {'+CRLF+
'    friend class funneled_predictor_in<Type>;'+CRLF+
'  protected:'+CRLF+
'  public:'+CRLF+
'    funneled_predictor_out() { };'+CRLF+
'    funneled_predictor_out(int P, void * _Ref) {'+CRLF+
'       this->init_data(_Ref ? ((funneled_predictor_in<Type> *) _Ref)->getRef() : new _funnel_predictor<Type>(P));'+CRLF+
'    };'+CRLF+
'    funneled_predictor_out(int N, int P = 5, double rel_eps = 0.001) {'+CRLF+
'       this->init_data(new _funnel_predictor<Type>(P, N, rel_eps));'+CRLF+
'    }'+CRLF+
'    funneled_predictor_out(const char * Name, int N = 1, int P = 5, double rel_eps = 0.001) {'+CRLF+
'       omp_set_lock(&__funnel_lock__);'+CRLF+
'       map<string,__funnel *>::iterator itFunnels = __Funnels.find(Name);'+CRLF+
'       if (itFunnels == __Funnels.end()) {'+CRLF+
'          __funnel * funnel = new _funnel_predictor<Type>(P, N, rel_eps, Name);'+CRLF+
'          this->init_data(funnel);'+CRLF+
'          __Funnels[Name] = funnel;'+CRLF+
'       } else {'+CRLF+
'          this->init_data(itFunnels->second);'+CRLF+
'       }'+CRLF+
'       omp_unset_lock(&__funnel_lock__);'+CRLF+
'    }'+CRLF+
'    virtual void put(void * Buf, int SizeInBytes) {'+CRLF+
'       _funnel_with_history<Type> * Ref = reinterpret_cast<_funnel_with_history<Type> *>(this->getRef());'+CRLF+
''+CRLF+
'      if (Ref) {'+CRLF+
'          wait();'+CRLF+
'          while (Ref->State & tnlValue) {'+CRLF+
'             omp_unset_lock(&Ref->Lock);'+CRLF+
'             _Yield();'+CRLF+
'             omp_set_lock(&Ref->Lock);'+CRLF+
'          }'+CRLF+
'          if (SizeInBytes == 0)'+CRLF+
'             Ref->check_size(1);'+CRLF+
'          else'+CRLF+
'             Ref->check_size(SizeInBytes/sizeof(Type));'+CRLF+
'          memmove((void *) Ref->Data,Buf,SizeInBytes);'+CRLF+
'          Ref->State |= tnlValue;'+CRLF+
'          Ref->push_history(false);'+CRLF+
'          omp_unset_lock(&Ref->Lock);'+CRLF+
'       }'+CRLF+
'    };'+CRLF+
' };'+CRLF+
' template<class Type>'+CRLF+
'  class funneled_perceptron_out: public funneled_predictor_out<Type> {'+CRLF+
'    friend class funneled_perceptron_in<Type>;'+CRLF+
'  protected:'+CRLF+
'  public:'+CRLF+
'    funneled_perceptron_out() { throw Exception("Empty constructor of funnel-perceptron-out called"); };'+CRLF+
'    funneled_perceptron_out(bool _explicit, bool hasB, const vector<_funnel<Type> *> &refs, int N, void * _Ref, int PATTERN = -1) {'+CRLF+
'       if (_explicit)'+CRLF+
'          this->init_data(_Ref ? ((funneled_predictor_in<Type> *) _Ref)->getRef(&refs) : new _funnel_explicit_perceptron<Type>(hasB, refs, N, 0.001, NULL, PATTERN));'+CRLF+
'       else'+CRLF+
'          this->init_data(_Ref ? ((funneled_predictor_in<Type> *) _Ref)->getRef(&refs) : new _funnel_implicit_perceptron<Type>(hasB, refs, N, 0.001, NULL, PATTERN));'+CRLF+
'    };'+CRLF+
'    funneled_perceptron_out(bool _explicit, bool hasB, const vector<_funnel<Type> *> &refs, const char * Name, int N = 1, double rel_eps = 0.001, int PATTERN = -1) {'+CRLF+
'       omp_set_lock(&__funnel_lock__);'+CRLF+
'       map<string,__funnel *>::iterator itFunnels = __Funnels.find(Name);'+CRLF+
'       if (itFunnels == __Funnels.end()) {'+CRLF+
'          __funnel * funnel = _explicit ? (__funnel *) new _funnel_explicit_perceptron<Type>(hasB, refs, N, rel_eps, Name, PATTERN) : (__funnel *) new _funnel_implicit_perceptron<Type>(hasB, refs, N, rel_eps, Name, PATTERN);'+CRLF+
'          this->init_data(funnel);'+CRLF+
'          __Funnels[Name] = funnel;'+CRLF+
'       } else {'+CRLF+
'          reinterpret_cast< _funnel_perceptron<Type> * >(itFunnels->second)->add_refs(&refs);'+CRLF+
'          this->init_data(itFunnels->second);'+CRLF+
'       }'+CRLF+
'       omp_unset_lock(&__funnel_lock__);'+CRLF+
'    }'+CRLF+
' };'+CRLF+
'#ifdef __REENT_MPI__'+CRLF+
' #define cfunnel(Dir,Type) cfunneled_##Dir<Type>'+CRLF+
' #define cvar(Type) common_var<Type>'+CRLF+
' omp_lock_t __cfunnel_lock__;'+CRLF+
' class __cfunnel;'+CRLF+
' map<string,__cfunnel *> __cFunnels;'+CRLF+
' class __cfunnel {'+CRLF+
'  protected:'+CRLF+
'    static const int connect_tag = 1235;'+CRLF+
'    typedef struct {'+CRLF+
'      char connect[60];'+CRLF+
'      bool in;'+CRLF+
'      bool init;'+CRLF+
'      int  tag;'+CRLF+
'    } data;'+CRLF+
'  public:'+CRLF+
'    volatile int in_id;'+CRLF+
'    volatile int out_id;'+CRLF+
'    volatile int tag;'+CRLF+
'    volatile bool stopped;'+CRLF+
'    string Name;'+CRLF+
'    __cfunnel(const char * Name) {'+CRLF+
'      in_id  = -1;'+CRLF+
'      out_id = -1;'+CRLF+
'      tag    = -1;'+CRLF+
'      stopped = false;'+CRLF+
'      if (Name)'+CRLF+
'         this->Name = Name;'+CRLF+
'      else {'+CRLF+
'         cout<<"Cluster funnel can''t be anonymous (no name in constructor)."<<endl;'+CRLF+
'         exit(-1);'+CRLF+
'      }'+CRLF+
'    };'+CRLF+
'    void process() {'+CRLF+
'      int item_received;'+CRLF+
'      omp_set_lock(&__cfunnel_lock__);'+CRLF+
'	  if (!stopped) do {'+CRLF+
'         MPI_Status status;'+CRLF+
'         MPI_Iprobe(MPI_ANY_SOURCE, connect_tag, MPI_COMM_WORLD, &item_received, &status);'+CRLF+
'		 if (item_received) {'+CRLF+
'            MPI_Status status1;'+CRLF+
'            data Buf;'+CRLF+
'            MPI_Recv(&Buf, sizeof(Buf), MPI_BYTE, status.MPI_SOURCE, connect_tag, MPI_COMM_WORLD, &status1);'+CRLF+
'			map<string, __cfunnel *>::iterator itcFunnels = __cFunnels.find(Buf.connect);'+CRLF+
'            __cfunnel * cfunnel = NULL;'+CRLF+
'            if (itcFunnels == __cFunnels.end()) {'+CRLF+
'               if (Buf.init) {'+CRLF+
'                  cfunnel = new __cfunnel(Buf.connect);'+CRLF+
'                  __cFunnels[Buf.connect] = cfunnel;'+CRLF+
'			   }'+CRLF+
'            } else'+CRLF+
'              cfunnel = itcFunnels->second;'+CRLF+
'			if (cfunnel) {'+CRLF+
'               int state1 = (cfunnel->in_id >= 0) + (cfunnel->out_id >= 0);'+CRLF+
'               if (Buf.init) {'+CRLF+
'                  if (Buf.in) {'+CRLF+
'                     if (cfunnel->in_id >= 0) {'+CRLF+
'                        cout<<"Funnel ''"<<Buf.connect<<"'' already has in-point. Error cluster_id=="<<cfunnel->in_id<<endl;'+CRLF+
'                        exit(-1);'+CRLF+
'                     }'+CRLF+
'                     cfunnel->in_id = status.MPI_SOURCE;'+CRLF+
'                     if (Buf.tag >= 0)'+CRLF+
'                        cfunnel->tag = Buf.tag;'+CRLF+
'                  } else {'+CRLF+
'                     if (cfunnel->out_id >= 0) {'+CRLF+
'                        cout<<"Funnel ''"<<Buf.connect<<"'' already has out-point. Error cluster_id=="<<cfunnel->out_id<<endl;'+CRLF+
'                        exit(-1);'+CRLF+
'                     }'+CRLF+
'                     cfunnel->out_id = status.MPI_SOURCE;'+CRLF+
'                  }'+CRLF+
'               } else {'+CRLF+
'                  if (Buf.in) {'+CRLF+
'                     if (cfunnel->in_id == status.MPI_SOURCE)'+CRLF+
'                        cfunnel->in_id = -1;'+CRLF+
'                  } else {'+CRLF+
'                     if (cfunnel->out_id == status.MPI_SOURCE)'+CRLF+
'                        cfunnel->out_id = -1;'+CRLF+
'                  }'+CRLF+
'               }'+CRLF+
'			   int state2 = (cfunnel->in_id >= 0) + (cfunnel->out_id >= 0);'+CRLF+
'               if (state2 < state1) {'+CRLF+
'                  cfunnel->stopped = true;'+CRLF+
'               }'+CRLF+
'			   if (state2 < state1 && state2 == 0 && cfunnel != this) {'+CRLF+
'                  omp_unset_lock(&__cfunnel_lock__);'+CRLF+
'                  delete cfunnel;'+CRLF+
'                  omp_set_lock(&__cfunnel_lock__);'+CRLF+
'               }'+CRLF+
'            }'+CRLF+
'         }'+CRLF+
'	  } while (item_received && !stopped);'+CRLF+
'      omp_unset_lock(&__cfunnel_lock__);'+CRLF+
'	}'+CRLF+
'    void wait() {'+CRLF+
'      if (!stopped) do {'+CRLF+
'		  process();'+CRLF+
'      } while (!stopped && (in_id < 0 || out_id < 0));'+CRLF+
'    };'+CRLF+
'    void bcast(bool in, bool init, bool all) {'+CRLF+
'      data Buf;'+CRLF+
'      Buf.in   = in;'+CRLF+
'      Buf.init = init;'+CRLF+
'      memmove(Buf.connect, Name.c_str(), Name.length()+1);'+CRLF+
'      Buf.tag = tag;'+CRLF+
'	  if (all) {'+CRLF+
'		  for (int i = 0; i < __cluster_topo_size__; i++)'+CRLF+
'			  if (__cluster_topo_ids__[i] != __cluster_id__)'+CRLF+
'				  MPI_Send(&Buf, sizeof(Buf), MPI_BYTE, __cluster_topo_ids__[i], connect_tag, MPI_COMM_WORLD);'+CRLF+
'	  } else if (in_id == __cluster_id__)'+CRLF+
'		  MPI_Send(&Buf, sizeof(Buf), MPI_BYTE, out_id, connect_tag, MPI_COMM_WORLD);'+CRLF+
'	  else if (out_id == __cluster_id__)'+CRLF+
'		  MPI_Send(&Buf, sizeof(Buf), MPI_BYTE, in_id, connect_tag, MPI_COMM_WORLD);'+CRLF+
'	};'+CRLF+
'    ~__cfunnel() {'+CRLF+
'      if (Name.length() > 0) {'+CRLF+
'         omp_set_lock(&__cfunnel_lock__);'+CRLF+
'         map<string,__cfunnel *>::iterator itcFunnels = __cFunnels.find(Name);'+CRLF+
'         if (itcFunnels == __cFunnels.end()) {'+CRLF+
'            cout<<"Abnormal funnel termination: funnel ''"<<Name<<"'' is not registered"<<endl;'+CRLF+
'            exit(-1);'+CRLF+
'         } else {'+CRLF+
'            __cFunnels.erase(itcFunnels);'+CRLF+
'         }'+CRLF+
'         omp_unset_lock(&__cfunnel_lock__);'+CRLF+
'      }'+CRLF+
'    };'+CRLF+
' };'+CRLF+
' template<class Type>'+CRLF+
'  class cfunneled_base {'+CRLF+
'  private:'+CRLF+
'    __cfunnel * Ref;'+CRLF+
'  protected:'+CRLF+
'    virtual void init_data(__cfunnel * _Ref) = 0;'+CRLF+
'  public:'+CRLF+
'    virtual __cfunnel * getRef() { return Ref; };'+CRLF+
'	virtual _funnel<Type> * getPredictRef(const vector<_funnel<Type> *> * _refs = NULL) { return NULL; };'+CRLF+
'    void setRef(__cfunnel * _Ref) { Ref = _Ref; };'+CRLF+
'    virtual bool empty() = 0;'+CRLF+
'    bool ready() {'+CRLF+
'      if (!Ref->stopped) Ref->process();'+CRLF+
'      return !Ref->stopped && Ref->in_id >= 0 && Ref->out_id >= 0;'+CRLF+
'    };'+CRLF+
'  };'+CRLF+
' template<class Type>'+CRLF+
'  class cfunneled_out;'+CRLF+
' template<class Type>'+CRLF+
'  class cfunneled_in: public cfunneled_base<Type> {'+CRLF+
'    friend class cfunneled_out<Type>;'+CRLF+
'  protected:'+CRLF+
'    virtual void init_data(__cfunnel * _Ref) {'+CRLF+
'       this->setRef(_Ref);'+CRLF+
'       if (_Ref->in_id >= 0) {'+CRLF+
'          cout<<"Cluster Funnel already has input"<<endl;'+CRLF+
'          exit(-1);'+CRLF+
'       }'+CRLF+
'       _Ref->in_id = __cluster_id__;'+CRLF+
'       do {'+CRLF+
'         _Ref->tag = rand() % (RAND_MAX / 20);'+CRLF+
'       } while (_Ref->tag >= 1232 && _Ref->tag < 1240);'+CRLF+
'    };'+CRLF+
'  public:'+CRLF+
'    cfunneled_in(const char * Name) {'+CRLF+
'       __cfunnel * cfunnel = NULL;'+CRLF+
'       omp_set_lock(&__cfunnel_lock__);'+CRLF+
'	   map<string, __cfunnel *>::iterator itcFunnels = __cFunnels.find(Name);'+CRLF+
'       if (itcFunnels == __cFunnels.end()) {'+CRLF+
'          cfunnel = new __cfunnel(Name);'+CRLF+
'		  this->init_data(cfunnel);'+CRLF+
'          __cFunnels[Name] = cfunnel;'+CRLF+
'		  cfunnel->bcast(true, true, true);'+CRLF+
'	   }'+CRLF+
'	   else {'+CRLF+
'		   cfunnel = itcFunnels->second;'+CRLF+
'		   this->init_data(cfunnel);'+CRLF+
'		   cfunnel->bcast(true, true, false);'+CRLF+
'	   }'+CRLF+
'	   omp_unset_lock(&__cfunnel_lock__);'+CRLF+
'       cfunnel->process();'+CRLF+
'	}'+CRLF+
'    ~cfunneled_in() {'+CRLF+
'       __cfunnel * Ref = this->getRef();'+CRLF+
'       if (Ref) {'+CRLF+
'          Ref->bcast(true,false,true);'+CRLF+
'          Ref->process();'+CRLF+
'          Ref->in_id = -1;'+CRLF+
'          delete Ref;'+CRLF+
'       }'+CRLF+
'    };'+CRLF+
'    virtual bool empty() {'+CRLF+
'      __cfunnel * Ref = this->getRef();'+CRLF+
'      if (Ref) {'+CRLF+
'         MPI_Status status;'+CRLF+
'         int has_data;'+CRLF+
'         Ref->process();'+CRLF+
'         if (Ref->stopped || Ref->in_id < 0 || Ref->out_id < 0)'+CRLF+
'            return true;'+CRLF+
'         else {'+CRLF+
'            MPI_Iprobe(Ref->out_id, Ref->tag, MPI_COMM_WORLD, &has_data, &status);'+CRLF+
'            return has_data == 0;'+CRLF+
'         }'+CRLF+
'      }'+CRLF+
'      return false;'+CRLF+
'    }'+CRLF+
'    void get(void * Buf, int SizeInBytes) {'+CRLF+
'      __cfunnel * Ref = this->getRef();'+CRLF+
'      if (Ref) {'+CRLF+
'         MPI_Status status;'+CRLF+
'		 Ref->wait();'+CRLF+
'		 MPI_Recv(Buf, SizeInBytes, MPI_BYTE, Ref->out_id, Ref->tag, MPI_COMM_WORLD, &status);'+CRLF+
'		 MPI_Send(NULL, 0, MPI_BYTE, Ref->out_id, Ref->tag*10, MPI_COMM_WORLD);'+CRLF+
'	  }'+CRLF+
'    };'+CRLF+
'    Type operator * () {'+CRLF+
'      Type Result;'+CRLF+
'      get(&Result,sizeof(Result));'+CRLF+
'      return Result;'+CRLF+
'    };'+CRLF+
' };'+CRLF+
' template<class Type>'+CRLF+
'  class cfunneled_out: public cfunneled_base<Type> {'+CRLF+
'    friend class cfunneled_in<Type>;'+CRLF+
'    volatile int send_recv;'+CRLF+
'  protected:'+CRLF+
'    void init_data(__cfunnel * _Ref) {'+CRLF+
'       this->setRef(_Ref);'+CRLF+
'       if (_Ref->out_id >= 0) {'+CRLF+
'          cout<<"Funnel already has output"<<endl;'+CRLF+
'          exit(-1);'+CRLF+
'       }'+CRLF+
'       _Ref->out_id = __cluster_id__;'+CRLF+
'    };'+CRLF+
'  public:'+CRLF+
'    cfunneled_out(const char * Name) {'+CRLF+
'       __cfunnel * cfunnel = NULL;'+CRLF+
'       omp_set_lock(&__cfunnel_lock__);'+CRLF+
'       map<string,__cfunnel *>::iterator itcFunnels = __cFunnels.find(Name);'+CRLF+
'       if (itcFunnels == __cFunnels.end()) {'+CRLF+
'          cfunnel = new __cfunnel(Name);'+CRLF+
'          this->init_data(cfunnel);'+CRLF+
'          __cFunnels[Name] = cfunnel;'+CRLF+
'          cfunnel->bcast(false,true,true);'+CRLF+
'       } else {'+CRLF+
'		   cfunnel = itcFunnels->second;'+CRLF+
'		   this->init_data(cfunnel);'+CRLF+
'		   cfunnel->bcast(false, true, false);'+CRLF+
'	   }'+CRLF+
'       omp_unset_lock(&__cfunnel_lock__);'+CRLF+
'       send_recv = 0;'+CRLF+
'       cfunnel->process();'+CRLF+
'	}'+CRLF+
'    void process_answers() {'+CRLF+
'      __cfunnel * Ref = this->getRef();'+CRLF+
'      if (Ref) {'+CRLF+
'         int received = 1;'+CRLF+
'         while (received && !Ref->stopped && send_recv) {'+CRLF+
'            MPI_Status status, status1;'+CRLF+
'            MPI_Iprobe(Ref->in_id, Ref->tag*10, MPI_COMM_WORLD, &received, &status);'+CRLF+
'            if (received) {'+CRLF+
'               MPI_Recv(NULL, 0, MPI_BYTE, Ref->in_id, Ref->tag*10, MPI_COMM_WORLD, &status1);'+CRLF+
'               send_recv--;'+CRLF+
'            }'+CRLF+
'         }'+CRLF+
'      }'+CRLF+
'    }'+CRLF+
'    ~cfunneled_out() {'+CRLF+
'       __cfunnel * Ref = this->getRef();'+CRLF+
'       if (Ref) {'+CRLF+
'          while (send_recv && !Ref->stopped)'+CRLF+
'            process_answers();'+CRLF+
'          Ref->bcast(false,false,true);'+CRLF+
'          Ref->process();'+CRLF+
'          Ref->out_id = -1;'+CRLF+
'          delete Ref;'+CRLF+
'       }'+CRLF+
'    };'+CRLF+
'    virtual bool empty() {'+CRLF+
'      __cfunnel * Ref = this->getRef();'+CRLF+
'      Ref->process();'+CRLF+
'      if (Ref->stopped || Ref->in_id < 0 || Ref->out_id < 0)'+CRLF+
'         return true;'+CRLF+
'      if (send_recv && !Ref->stopped)'+CRLF+
'         process_answers();'+CRLF+
'      return (send_recv == 0) || Ref->stopped;'+CRLF+
'    }'+CRLF+
'    void put(void * Buf, int SizeInBytes) {'+CRLF+
'      __cfunnel * Ref = this->getRef();'+CRLF+
'      if (Ref) {'+CRLF+
'		  Ref->wait();'+CRLF+
'		  MPI_Send(Buf, SizeInBytes, MPI_BYTE, Ref->in_id, Ref->tag, MPI_COMM_WORLD);'+CRLF+
'		  send_recv++;'+CRLF+
'      }'+CRLF+
'    };'+CRLF+
'    Type operator = (Type Val) {'+CRLF+
'      put(&Val,sizeof(Val));'+CRLF+
'      return Val;'+CRLF+
'    };'+CRLF+
' };'+CRLF+
'template<class Type>'+CRLF+
'  class cfunneled_predictor_out;'+CRLF+
'template<class Type>'+CRLF+
'  class cfunneled_predictor_in : public cfunneled_in<Type> {'+CRLF+
'	  friend class cfunneled_predictor_out<Type>;'+CRLF+
'  protected:'+CRLF+
'	  funneled_predictor_in<Type> * _in;'+CRLF+
'	  funneled_predictor_out<Type> * _out;'+CRLF+
'	  Type * _Buf;'+CRLF+
'  public:'+CRLF+
'	  virtual _funnel<Type> * getPredictRef(const vector<_funnel<Type> *> * _refs = NULL) {'+CRLF+
'		  if (_in) {'+CRLF+
'			  _funnel_with_history<Type> * Ref = reinterpret_cast< _funnel_with_history<Type> *>(_in->getRef(_refs));'+CRLF+
''+CRLF+
'			  return Ref;'+CRLF+
'		  }'+CRLF+
'		  else'+CRLF+
'			  return NULL;'+CRLF+
'	  };'+CRLF+
''+CRLF+
'	  cfunneled_predictor_in(const char * Name, int N = 1, int P = 5, double rel_eps = 0.001) : cfunneled_in<Type>(Name) {'+CRLF+
'		  this->_in = new funneled_predictor_in<Type>(N, P, rel_eps);'+CRLF+
'		  this->_out = new funneled_predictor_out<Type>(P, (void *)_in);'+CRLF+
'		  this->_Buf = new Type[N];'+CRLF+
'	  }'+CRLF+
'	  ~cfunneled_predictor_in() {'+CRLF+
'		  delete[] this->_Buf;'+CRLF+
'		  delete this->_in;'+CRLF+
'		  delete this->_out;'+CRLF+
'	  }'+CRLF+
'	  void get(void * Buf, int SizeInBytes) {'+CRLF+
'		  __cfunnel * Ref = this->getRef();'+CRLF+
'		  if (Ref) {'+CRLF+
'			  cfunneled_in<Type>::get(Buf, SizeInBytes);'+CRLF+
'			  this->_out->put(Buf, SizeInBytes);'+CRLF+
'			  this->_in->get(Buf, SizeInBytes);'+CRLF+
'		  }'+CRLF+
'	  };'+CRLF+
'	  virtual void get_and_correct(void * Buf) {'+CRLF+
'		  _funnel_with_history<Type> * Ref = reinterpret_cast< _funnel_with_history<Type> *>(_in->getRef());'+CRLF+
'		  if (Ref) {'+CRLF+
'			  int SizeInBytes = Ref->getN()*sizeof(Type);'+CRLF+
'			  this->get(Buf, SizeInBytes);'+CRLF+
'			  Ref->set_predict_results();'+CRLF+
'			  Ref->correct();'+CRLF+
'			  Ref->unset_predict_results();'+CRLF+
'		  }'+CRLF+
'	  }'+CRLF+
'	  virtual void cancel_and_push(void * Buf) {'+CRLF+
'		  _funnel_with_history<Type> * Ref = reinterpret_cast<_funnel_with_history<Type> *>(_in->getRef());'+CRLF+
'		  if (Ref) {'+CRLF+
'			  int SizeInBytes = Ref->getN()*sizeof(Type);'+CRLF+
'			  cfunneled_in<Type>::get(_Buf, SizeInBytes);'+CRLF+
'			  this->_out->put(_Buf, SizeInBytes);'+CRLF+
'			  Ref->replace_top_history(Buf, false);'+CRLF+
'			  Ref->unset_predict_results();'+CRLF+
'		  }'+CRLF+
'	  };'+CRLF+
'	  virtual bool get_timed(void * Buf, double timeout_ms) {'+CRLF+
'		  _funnel_with_history<Type> * Ref = reinterpret_cast< _funnel_with_history<Type> *>(_in->getRef());'+CRLF+
'		  if (Ref) {'+CRLF+
'			  double t = omp_get_wtime();'+CRLF+
'			  double timeout_s = 0.001*timeout_ms;'+CRLF+
'			  int SizeInBytes = Ref->getN()*sizeof(Type);'+CRLF+
'			  long counter = WAITING_COUNTER;'+CRLF+
'			  bool prediction = true;'+CRLF+
'			  do {'+CRLF+
'				  if (counter == WAITING_COUNTER) {'+CRLF+
'					  double elapsed = omp_get_wtime() - t;'+CRLF+
'					  if (elapsed >= timeout_s && prediction) {'+CRLF+
'						  Ref->LOCK();'+CRLF+
'						  prediction = Ref->predict(!(Ref->State & tnlValue));'+CRLF+
'						  if (prediction) {'+CRLF+
'							  memmove(Buf, (void *)Ref->getPredicted(), SizeInBytes);'+CRLF+
'							  Ref->UNLOCK();'+CRLF+
'							  return true;'+CRLF+
'						  }'+CRLF+
'						  Ref->UNLOCK();'+CRLF+
'					  }'+CRLF+
'					  counter = 0;'+CRLF+
'				  }'+CRLF+
'				  else'+CRLF+
'					  counter++;'+CRLF+
'				  _Yield();'+CRLF+
'			  } while (this->empty());'+CRLF+
'			  this->get(Buf, SizeInBytes);'+CRLF+
'		  }'+CRLF+
'		  return false;'+CRLF+
'	  };'+CRLF+
'  };'+CRLF+
'  template<class Type>'+CRLF+
'  class cfunneled_predictor_out : public cfunneled_out<Type> {'+CRLF+
'	  friend class cfunneled_predictor_in<Type>;'+CRLF+
'  protected:'+CRLF+
'  public:'+CRLF+
'	  cfunneled_predictor_out(const char * Name, int N = 1, int P = 5, double rel_eps = 0.001) : cfunneled_out<Type>(Name) {'+CRLF+
'	  }'+CRLF+
'  };'+CRLF+
' static constexpr MPI_Datatype MPI_TYPES[12] = { MPI_CHAR, MPI_CHAR, MPI_SHORT, MPI_INT, MPI_LONG, MPI_FLOAT, MPI_DOUBLE, MPI_UNSIGNED_SHORT, MPI_UNSIGNED, MPI_UNSIGNED_LONG, MPI_LONG_DOUBLE, MPI_LONG_LONG_INT };'+CRLF+
' template<class T> struct MPI_Types { };'+CRLF+
' template<> struct MPI_Types<unsigned char> { static constexpr MPI_Datatype val = MPI_TYPES[0]; };'+CRLF+
' template<> struct MPI_Types<char> { static constexpr MPI_Datatype val = MPI_TYPES[1]; };'+CRLF+
' template<> struct MPI_Types<short> { static constexpr MPI_Datatype val = MPI_TYPES[2]; };'+CRLF+
' template<> struct MPI_Types<int> { static constexpr MPI_Datatype val = MPI_TYPES[3]; };'+CRLF+
' template<> struct MPI_Types<long> { static constexpr MPI_Datatype val = MPI_TYPES[4]; };'+CRLF+
' template<> struct MPI_Types<float> { static constexpr MPI_Datatype val = MPI_TYPES[5]; };'+CRLF+
' template<> struct MPI_Types<double> { static constexpr MPI_Datatype val = MPI_TYPES[6]; };'+CRLF+
' template<> struct MPI_Types<unsigned short> { static constexpr MPI_Datatype val = MPI_TYPES[7]; };'+CRLF+
' template<> struct MPI_Types<unsigned int> { static constexpr MPI_Datatype val = MPI_TYPES[8]; };'+CRLF+
' template<> struct MPI_Types<unsigned long> { static constexpr MPI_Datatype val = MPI_TYPES[9]; };'+CRLF+
' template<> struct MPI_Types<long double> { static constexpr MPI_Datatype val = MPI_TYPES[10]; };'+CRLF+
' template<> struct MPI_Types<long long> { static constexpr MPI_Datatype val = MPI_TYPES[11]; };'+CRLF+
' template<class Type>'+CRLF+
'  class common_var {'+CRLF+
'    protected:'+CRLF+
'      int     N;'+CRLF+
'      void *  mem;'+CRLF+
'      MPI_Win win;'+CRLF+
'      int     root;'+CRLF+
''+CRLF+
'      common_var(): N(0), mem(NULL), win(MPI_WIN_NULL), root(-1) {};'+CRLF+
'    public:'+CRLF+
'      common_var(int _NN) {'+CRLF+
'        N = _NN;'+CRLF+
'        if (__cluster_id__ == 0)'+CRLF+
'           root = rand() % __cluster_size__;'+CRLF+
'        MPI_Bcast(&root, 1, MPI_INT, 0, MPI_COMM_WORLD);'+CRLF+
'        if (__cluster_id__ == root) {'+CRLF+
'           MPI_Alloc_mem(N*sizeof(Type), MPI_INFO_NULL, &mem);'+CRLF+
'           MPI_Win_create(mem, N*sizeof(Type), sizeof(Type), MPI_INFO_NULL, MPI_COMM_WORLD, &win);'+CRLF+
'        } else {'+CRLF+
'           mem = NULL;'+CRLF+
'           MPI_Win_create(NULL, 0, sizeof(Type), MPI_INFO_NULL, MPI_COMM_WORLD, &win);'+CRLF+
'        }'+CRLF+
'      };'+CRLF+
'      void put (Type * ptr, int size_in_bytes) {'+CRLF+
'        MPI_Win_lock(MPI_LOCK_EXCLUSIVE, root, 0, win);'+CRLF+
'        MPI_Put(ptr, size_in_bytes, MPI_BYTE, root, 0, size_in_bytes, MPI_BYTE, win);'+CRLF+
'        MPI_Win_unlock(root, win);'+CRLF+
'      };'+CRLF+
'      void get (Type * ptr, int size_in_bytes) {'+CRLF+
'        MPI_Win_lock(MPI_LOCK_EXCLUSIVE, root, 0, win);'+CRLF+
'        MPI_Get(ptr, size_in_bytes, MPI_BYTE, root, 0, size_in_bytes, MPI_BYTE, win);'+CRLF+
'        MPI_Win_unlock(root, win);'+CRLF+
'      };'+CRLF+
'      Type add(Type inc, bool pre) {'+CRLF+
'        Type buf;'+CRLF+
'        MPI_Win_lock(MPI_LOCK_EXCLUSIVE, root, 0, win);'+CRLF+
'        MPI_Get_accumulate(&inc, 1, MPI_Types<Type>::val, &buf, 1, MPI_Types<Type>::val, root, 0, 1, MPI_Types<Type>::val, MPI_SUM, win);'+CRLF+
'        MPI_Win_unlock(root, win);'+CRLF+
'        if (pre) {'+CRLF+
'           buf += inc;'+CRLF+
'        }'+CRLF+
'        return buf;'+CRLF+
'      }'+CRLF+
'      Type operator ++ (int) {'+CRLF+
'        return add(+1, false);'+CRLF+
'      };'+CRLF+
'      Type operator ++ () {'+CRLF+
'        return add(+1, true);'+CRLF+
'      };'+CRLF+
'      Type operator -- (int) {'+CRLF+
'        return add(-1, false);'+CRLF+
'      };'+CRLF+
'      Type operator -- () {'+CRLF+
'        return add(-1, true);'+CRLF+
'      };'+CRLF+
'      Type operator += (Type Val) {'+CRLF+
'        return add(Val, true);'+CRLF+
'      };'+CRLF+
'      Type operator -= (Type Val) {'+CRLF+
'        return add(-Val, true);'+CRLF+
'      };'+CRLF+
'      Type operator = (Type Val) {'+CRLF+
'        put(&Val, sizeof(Val));'+CRLF+
'        return Val;'+CRLF+
'      };'+CRLF+
'      Type operator * () {'+CRLF+
'        Type Result;'+CRLF+
'        get(&Result,sizeof(Result));'+CRLF+
'        return Result;'+CRLF+
'      };'+CRLF+
'      ~common_var() {'+CRLF+
'        MPI_Win_free(&win);'+CRLF+
'        if (mem) MPI_Free_mem(mem);'+CRLF+
'      };'+CRLF+
'  };'+CRLF+
'  class csemaphore: public common_var<int> {'+CRLF+
'    protected:'+CRLF+
'      int MAX;'+CRLF+
'    public:'+CRLF+
'      csemaphore(int C): common_var<int>(1), MAX(C) {'+CRLF+
'        if (__cluster_id__ == this->root) {'+CRLF+
'           int val = 0;'+CRLF+
'           this->put(&val, sizeof(int));'+CRLF+
'        }'+CRLF+
'        MPI_Barrier(MPI_COMM_WORLD);'+CRLF+
'      };'+CRLF+
'      void wait () {'+CRLF+
'        int v;'+CRLF+
'        do {'+CRLF+
'           v = common_var<int>::operator ++();'+CRLF+
'           if (v > MAX) {'+CRLF+
'              common_var<int>::operator --();'+CRLF+
'              Sleep(rand()%4);'+CRLF+
'           }'+CRLF+
'        } while (v > MAX);'+CRLF+
'      };'+CRLF+
'      void release () {'+CRLF+
'        common_var<int>::operator --();'+CRLF+
'      };'+CRLF+
'  };'+CRLF+
' typedef csemaphore * plan_csem_t;'+CRLF+
' #define plan_csem_init(sem, N) *sem = new csemaphore(N)'+CRLF+
' #define plan_csem_wait(sem) (*sem)->wait()'+CRLF+
' #define plan_csem_release(sem) (*sem)->release()'+CRLF+
' #define plan_csem_destroy(sem) delete *sem'+CRLF+
'#endif'+CRLF+
'#endif'+CRLF;

Const Signals: PChar =
'#include <string.h>'+CRLF+
'#ifdef _MSC_VER'+CRLF+
'  #include <windows.h>'+CRLF+
'#else'+CRLF+
'  #include <unistd.h>'+CRLF+
'  #ifdef _POSIX_PRIORITY_SCHEDULING'+CRLF+
'    #include <sched.h>'+CRLF+
'  #endif'+CRLF+
'#endif'+CRLF+
'inline void _Yield() {'+CRLF+
'#ifdef _MSC_VER'+CRLF+
'  Sleep(0)'+CRLF+
'#elif defined(_POSIX_PRIORITY_SCHEDULING)'+CRLF+
'  sched_yield()'+CRLF+
'#endif'+CRLF+
';}'+CRLF+
'#define EVENT_TIMEOUT 10'+CRLF+
'#ifdef _MSC_VER'+CRLF+
'  #include <windows.h>'+CRLF+
'  typedef DWORD plan_thread_t;'+CRLF+
'  inline plan_thread_t GetTID() {'+CRLF+
'    return GetCurrentThreadId();'+CRLF+
'  }'+CRLF+
'  inline bool CompareTID(plan_thread_t TID1, plan_thread_t TID2) {'+CRLF+
'    return TID1 == TID2;'+CRLF+
'  }'+CRLF+
'#elif defined(_POSIX_THREADS)'+CRLF+
'  #include <pthread.h>'+CRLF+
'  typedef pthread_t plan_thread_t;'+CRLF+
'  inline plan_thread_t GetTID() {'+CRLF+
'    return pthread_self();'+CRLF+
'  }'+CRLF+
'  inline bool CompareTID(plan_thread_t TID1, plan_thread_t TID2) {'+CRLF+
'    return pthread_equal(TID1, TID2) != 0;'+CRLF+
'  }'+CRLF+
'#endif'+CRLF+
'#ifdef _OPENMP'+CRLF+
'#ifdef _MSC_VER'+CRLF+
'typedef HANDLE plan_sem_t;'+CRLF+
'void plan_sem_init(plan_sem_t * sem, int N) {'+CRLF+
'  *sem = CreateSemaphore(NULL, N, N, NULL);'+CRLF+
'}'+CRLF+
'void plan_sem_wait(plan_sem_t * sem) {'+CRLF+
'  WaitForSingleObject(*sem, INFINITE);'+CRLF+
'}'+CRLF+
'void plan_sem_release(plan_sem_t * sem) {'+CRLF+
'  ReleaseSemaphore(*sem, 1, NULL);'+CRLF+
'}'+CRLF+
'void plan_sem_destroy(plan_sem_t * sem) {'+CRLF+
'  CloseHandle(*sem);'+CRLF+
'}'+CRLF+
'typedef omp_lock_t plan_lock_t;'+CRLF+
'#define plan_set_lock omp_set_lock'+CRLF+
'#define plan_unset_lock omp_unset_lock'+CRLF+
'#define plan_init_lock omp_init_lock'+CRLF+
'#define plan_destroy_lock omp_destroy_lock'+CRLF+
'typedef HANDLE __reent_event;'+CRLF+
'inline void __init_reent_event(__reent_event * event) {'+CRLF+
'  *event = CreateEvent(NULL,0,0,NULL);'+CRLF+
'}'+CRLF+
'inline void __destroy_reent_event(__reent_event * event) {'+CRLF+
'  CloseHandle(*event);'+CRLF+
'}'+CRLF+
'inline void __wait_reent_event(__reent_event * event, plan_lock_t * mutex) {'+CRLF+
'  plan_unset_lock(mutex);'+CRLF+
'  if (WaitForSingleObject(*event,EVENT_TIMEOUT) != WAIT_TIMEOUT)'+CRLF+
'     ResetEvent(*event);'+CRLF+
'}'+CRLF+
'inline void __signal_reent_event(__reent_event * event) {'+CRLF+
'  SetEvent(*event);'+CRLF+
'}'+CRLF+
'inline void __instead_signal_yield() {'+CRLF+
'}'+CRLF+
'#elif defined(_POSIX_SEMAPHORES)'+CRLF+
'#include <semaphore.h>'+CRLF+
'typedef sem_t plan_sem_t;'+CRLF+
'void plan_sem_init(plan_sem_t * sem, int N) {'+CRLF+
'  sem_init(sem, 0, N);'+CRLF+
'}'+CRLF+
'void plan_sem_wait(plan_sem_t * sem) {'+CRLF+
'  sem_wait(sem);'+CRLF+
'}'+CRLF+
'void plan_sem_release(plan_sem_t * sem) {'+CRLF+
'  sem_post(sem);'+CRLF+
'}'+CRLF+
'void plan_sem_destroy(plan_sem_t * sem) {'+CRLF+
'  sem_destroy(sem);'+CRLF+
'}'+CRLF+
'typedef pthread_mutex_t plan_lock_t;'+CRLF+
'#define plan_set_lock pthread_mutex_lock'+CRLF+
'#define plan_unset_lock pthread_mutex_unlock'+CRLF+
'#define plan_init_lock(L) pthread_mutex_init(L,NULL)'+CRLF+
'#define plan_destroy_lock pthread_mutex_destroy'+CRLF+
'typedef pthread_cond_t __reent_event;'+CRLF+
'inline void __init_reent_event(__reent_event * event) {'+CRLF+
'  pthread_cond_init(event,NULL);'+CRLF+
'}'+CRLF+
'inline void __destroy_reent_event(__reent_event * event) {'+CRLF+
'  pthread_cond_destroy(event);'+CRLF+
'}'+CRLF+
'inline void __wait_reent_event(__reent_event * event, plan_lock_t * mutex) {'+CRLF+
'  struct timespec t;'+CRLF+
'  t.tv_sec = 0;'+CRLF+
'  t.tv_nsec = EVENT_TIMEOUT*1000000;'+CRLF+
'  pthread_cond_timedwait(event,mutex,&t);'+CRLF+
'  plan_unset_lock(mutex);'+CRLF+
'}'+CRLF+
'inline void __signal_reent_event(__reent_event * event) {'+CRLF+
'  pthread_cond_signal(event);'+CRLF+
'}'+CRLF+
'inline void __instead_signal_yield() {'+CRLF+
'}'+CRLF+
'inline void Sleep(int milliseconds) {'+CRLF+
'  struct timespec req = {milliseconds/1000, (milliseconds % 1000)*1000000};'+CRLF+
'  nanosleep(&req, NULL);'+CRLF+
'}'+CRLF+
'#else'+CRLF+
'typedef struct {'+CRLF+
'  omp_lock_t Lock;'+CRLF+
'  volatile int Counter;'+CRLF+
'} plan_sem_t;'+CRLF+
'void plan_sem_init(plan_sem_t * sem, int N) {'+CRLF+
'  omp_init_lock(&sem->Lock);'+CRLF+
'  sem->Counter = N;'+CRLF+
'}'+CRLF+
'void plan_sem_wait(plan_sem_t * sem) {'+CRLF+
'  omp_set_lock(&sem->Lock);'+CRLF+
'  while (!sem->Counter) {'+CRLF+
'    omp_unset_lock(&sem->Lock);'+CRLF+
'    _Yield();'+CRLF+
'    omp_set_lock(&sem->Lock);'+CRLF+
'  }'+CRLF+
'  sem->Counter--;'+CRLF+
'  omp_unset_lock(&sem->Lock);'+CRLF+
'}'+CRLF+
'void plan_sem_release(plan_sem_t * sem) {'+CRLF+
'  omp_set_lock(&sem->Lock);'+CRLF+
'  sem->Counter++;'+CRLF+
'  omp_unset_lock(&sem->Lock);'+CRLF+
'}'+CRLF+
'void plan_sem_destroy(plan_sem_t * sem) {'+CRLF+
'  omp_destroy_lock(&sem->Lock);'+CRLF+
'}'+CRLF+
'typedef omp_lock_t plan_lock_t;'+CRLF+
'#define plan_set_lock omp_set_lock'+CRLF+
'#define plan_unset_lock omp_unset_lock'+CRLF+
'#define plan_init_lock omp_init_lock'+CRLF+
'#define plan_destroy_lock omp_destroy_lock'+CRLF+
'typedef int __reent_event;'+CRLF+
'inline void __init_reent_event(__reent_event * event) {'+CRLF+
'}'+CRLF+
'inline void __destroy_reent_event(__reent_event * event) {'+CRLF+
'}'+CRLF+
'inline void __wait_reent_event(__reent_event * event, plan_lock_t * mutex) {'+CRLF+
'  plan_unset_lock(mutex);'+CRLF+
'}'+CRLF+
'inline void __signal_reent_event(__reent_event * event) {'+CRLF+
'}'+CRLF+
'inline void __instead_signal_yield() {'+CRLF+
'  _Yield();'+CRLF+
'}'+CRLF+
'inline void Sleep(int milliseconds) {'+CRLF+
'}'+CRLF+
'#endif'+CRLF+
'#endif'+CRLF;

Const Transact: PChar =
'#ifndef __TRANSACT_H__'+CRLF+
'#define __TRANSACT_H__'+CRLF+
''+CRLF+
'#define split_tune (get_nprocs())'+CRLF+
''+CRLF+
'#include <omp.h>'+CRLF+
'#include <stdlib.h>'+CRLF+
'#include <stdio.h>'+CRLF+
'#include <string.h>'+CRLF+
''+CRLF+
'#ifdef _MSC_VER'+CRLF+
'  #include <windows.h>'+CRLF+
''+CRLF+
'  #define clock_val(T) T.##QuadPart'+CRLF+
''+CRLF+
'  #define get_thread_id GetCurrentThreadId'+CRLF+
'#else'+CRLF+
'  #include <unistd.h>'+CRLF+
'  #include <time.h>'+CRLF+
'  #include <pthread.h>'+CRLF+
''+CRLF+
'  #define LARGE_INTEGER struct timespec'+CRLF+
''+CRLF+
'  #define clock_val(T) (T)'+CRLF+
''+CRLF+
'  #define get_thread_id pthread_self'+CRLF+
''+CRLF+
'  int QueryPerformanceCounter(LARGE_INTEGER * v) {'+CRLF+
'     clock_gettime(CLOCK_MONOTONIC, v);'+CRLF+
''+CRLF+
'     return 1;'+CRLF+
'  }'+CRLF+
''+CRLF+
'  LARGE_INTEGER & operator += (LARGE_INTEGER & op1, const LARGE_INTEGER & op2) {'+CRLF+
'     op1.tv_sec += op2.tv_sec;'+CRLF+
'     op1.tv_nsec += op2.tv_nsec;'+CRLF+
'     if (op1.tv_nsec > 999999999) {'+CRLF+
'        op1.tv_sec++;'+CRLF+
'        op1.tv_nsec -= 1000000000;'+CRLF+
'     }'+CRLF+
''+CRLF+
'     return op1;'+CRLF+
'  }'+CRLF+
''+CRLF+
'  LARGE_INTEGER & operator -= (LARGE_INTEGER & op1, const LARGE_INTEGER & op2) {'+CRLF+
'     op1.tv_sec -= op2.tv_sec;'+CRLF+
'     if (op1.tv_nsec < op2.tv_nsec) {'+CRLF+
'        op1.tv_sec--;'+CRLF+
'        op1.tv_nsec -= op2.tv_nsec;'+CRLF+
'        op1.tv_nsec += 1000000000;'+CRLF+
'     } else'+CRLF+
'        op1.tv_nsec -= op2.tv_nsec;'+CRLF+
''+CRLF+
'     return op1;'+CRLF+
'  }'+CRLF+
''+CRLF+
'  long long operator - (const LARGE_INTEGER & op1) {'+CRLF+
'     LARGE_INTEGER result = { 0 };'+CRLF+
'     result -= op1;'+CRLF+
''+CRLF+
'     return 1000000000LL*result.tv_sec + result.tv_nsec;'+CRLF+
'  }'+CRLF+
''+CRLF+
'  bool operator != (const LARGE_INTEGER & op1, int op2) {'+CRLF+
'     return op1.tv_sec != op2 || op1.tv_nsec != 0;'+CRLF+
'  }'+CRLF+
''+CRLF+
'  bool operator == (const LARGE_INTEGER & op1, int op2) {'+CRLF+
'     return op1.tv_sec == op2 && op1.tv_nsec == 0;'+CRLF+
'  }'+CRLF+
''+CRLF+
'  bool operator < (const LARGE_INTEGER & op1, const LARGE_INTEGER & op2) {'+CRLF+
'     return op1.tv_sec < op2.tv_sec || op1.tv_sec == op2.tv_sec && op1.tv_nsec < op2.tv_nsec;'+CRLF+
'  }'+CRLF+
''+CRLF+
'  bool operator >= (const LARGE_INTEGER & op1, int op2) {'+CRLF+
'     return 1LL*op1.tv_sec + op1.tv_nsec >= op2;'+CRLF+
'  }'+CRLF+
'#endif'+CRLF+
''+CRLF+
'#ifndef __REENT__'+CRLF+
'#include "funnels_atomic.h"'+CRLF+
'#endif'+CRLF+
''+CRLF+
'#include <list>'+CRLF+
'#include <vector>'+CRLF+
'#include <map>'+CRLF+
'#include <stack>'+CRLF+
'#include <queue>'+CRLF+
'#include <string>'+CRLF+
'#include <algorithm>'+CRLF+
'#include <functional>'+CRLF+
'#include <iostream>'+CRLF+
'#include <thread>'+CRLF+
''+CRLF+
'using namespace std;'+CRLF+
''+CRLF+
'const int __max_procs__ = 256;'+CRLF+
''+CRLF+
'class TVar;'+CRLF+
''+CRLF+
'omp_lock_t __lock_atomics__;'+CRLF+
''+CRLF+
'class TOBJ_STARTER;'+CRLF+
''+CRLF+
'typedef struct {'+CRLF+
'	int preconds[5];'+CRLF+
'	volatile bool finished;'+CRLF+
'} __tobj_job;'+CRLF+
''+CRLF+
'typedef std::function<void(void)> __page_fun;'+CRLF+
''+CRLF+
'map<long long, stack<TOBJ_STARTER *> *> __tobj_this_stack;'+CRLF+
'vector<__tobj_job *> __tobj_jobs;'+CRLF+
'bool __use_jobs = false;'+CRLF+
'omp_lock_t __lock_tobjs__;'+CRLF+
''+CRLF+
'void set_jobs_mode(bool use) {'+CRLF+
'	omp_set_lock(&__lock_tobjs__);'+CRLF+
'	__use_jobs = use;'+CRLF+
'	for (auto v : __tobj_jobs) {'+CRLF+
'		while (!v->finished) {'+CRLF+
'			omp_unset_lock(&__lock_tobjs__);'+CRLF+
'			_Yield();'+CRLF+
'			omp_set_lock(&__lock_tobjs__);'+CRLF+
'		}'+CRLF+
'	}'+CRLF+
'	for (auto v : __tobj_jobs) {'+CRLF+
'		delete v;'+CRLF+
'	}'+CRLF+
'	__tobj_jobs.clear();'+CRLF+
'	__tobj_jobs.reserve(10000);'+CRLF+
'	omp_unset_lock(&__lock_tobjs__);'+CRLF+
'}'+CRLF+
''+CRLF+
'class __initializer__ {'+CRLF+
'public:'+CRLF+
'  __initializer__() {'+CRLF+
'    omp_set_nested(1);'+CRLF+
'    omp_init_lock(&__lock_atomics__);'+CRLF+
'    omp_init_lock(&__lock_tobjs__);'+CRLF+
'  }'+CRLF+
'  virtual ~__initializer__() {'+CRLF+
'    omp_destroy_lock(&__lock_atomics__);'+CRLF+
'    omp_destroy_lock(&__lock_tobjs__);'+CRLF+
'  }'+CRLF+
'};'+CRLF+
''+CRLF+
'__initializer__ __starter__;'+CRLF+
''+CRLF+
'class TChannel;'+CRLF+
''+CRLF+
'class TVar;'+CRLF+
''+CRLF+
'enum { __reader__ = -1, __writer__, __another__ };'+CRLF+
''+CRLF+
'typedef struct {'+CRLF+
'	int __transaction_counter__; // K'+CRLF+
'	map<int, LARGE_INTEGER> __transaction_timings__[__max_procs__]; // Меньше нуля!'+CRLF+
'	map<int, LARGE_INTEGER> __transaction_retimings__[__max_procs__]; // Меньше нуля!'+CRLF+
'	vector<int> __transaction_procs__;'+CRLF+
'	vector<int> __transaction_misses__;'+CRLF+
'} __opt_transaction__;'+CRLF+
''+CRLF+
'typedef struct __info_transaction__ {'+CRLF+
'	list<TVar *> __atomics__;'+CRLF+
''+CRLF+
'	map<string, pair<TChannel *, TChannel *> > __io__;'+CRLF+
''+CRLF+
'	bool working[__max_procs__];'+CRLF+
'	int job_ids[__max_procs__];'+CRLF+
'	__page_fun __funs[__max_procs__];'+CRLF+
'	struct __info_transaction__ * parents[__max_procs__];'+CRLF+
'	int parent_ids[__max_procs__];'+CRLF+
''+CRLF+
'	bool failed[__max_procs__];'+CRLF+
'	bool __in_transaction__;'+CRLF+
''+CRLF+
'	__opt_transaction__ __stat_transaction__;'+CRLF+
''+CRLF+
'	int __transaction_procs__[__max_procs__];'+CRLF+
'} __info_transaction__;'+CRLF+
''+CRLF+
'map< long long, string > __map_threads__;'+CRLF+
''+CRLF+
'map< string, __info_transaction__ * > __transactions__;'+CRLF+
''+CRLF+
'__info_transaction__ * get_transaction(const char * id) {'+CRLF+
'	map< string, __info_transaction__ * >::iterator it = __transactions__.find(id);'+CRLF+
''+CRLF+
'	if (it == __transactions__.end()) {'+CRLF+
'		__info_transaction__ * new_tr = new __info_transaction__;'+CRLF+
'		'+CRLF+
'		new_tr->__in_transaction__ = false;'+CRLF+
'		new_tr->__stat_transaction__.__transaction_counter__ = -1;'+CRLF+
'		memset(new_tr->working, 0, sizeof(new_tr->working));'+CRLF+
'		memset(new_tr->parents, 0, sizeof(new_tr->parents));'+CRLF+
'		memset(new_tr->parent_ids, 0, sizeof(new_tr->parent_ids));'+CRLF+
'		for (int i = 0; i < __max_procs__; i++)'+CRLF+
'			new_tr->__funs[i] = nullptr;'+CRLF+
'		memset(new_tr->job_ids, 0, sizeof(new_tr->job_ids));'+CRLF+
'		memset(new_tr->failed, 0, sizeof(new_tr->failed));'+CRLF+
''+CRLF+
'		__transactions__[id] = new_tr;'+CRLF+
''+CRLF+
'		return new_tr;'+CRLF+
'	}'+CRLF+
'	else'+CRLF+
'		return it->second;'+CRLF+
'}'+CRLF+
''+CRLF+
'__info_transaction__ * get_transaction_by_thread(string & returned_id, bool stop_if_unknown = true) {'+CRLF+
'	long long thread_id = get_thread_id();'+CRLF+
'	map< long long, string>::iterator it = __map_threads__.find(thread_id);'+CRLF+
'	if (it == __map_threads__.end()) {'+CRLF+
'		if (stop_if_unknown) {'+CRLF+
'			cout << "Thread " << thread_id << " is not bound to transaction!" << endl;'+CRLF+
'			exit(-100);'+CRLF+
'		} else'+CRLF+
'			return NULL;'+CRLF+
'	}'+CRLF+
'	else {'+CRLF+
'		returned_id = it->second;'+CRLF+
'		return get_transaction(it->second.c_str());'+CRLF+
'	}'+CRLF+
'}'+CRLF+
''+CRLF+
'class TOBJ_STARTER {'+CRLF+
'protected:'+CRLF+
'   char __this_id[20];'+CRLF+
'   long long __tid;'+CRLF+
'   int __nthreads;'+CRLF+
'private:'+CRLF+
'   bool check_ways(__info_transaction__ * info, int id, __info_transaction__ * till_info) {'+CRLF+
'      if (info == NULL) return false;'+CRLF+
'      if (info == till_info) return true;'+CRLF+
'      else return check_ways(info->parents[id], info->parent_ids[id], till_info);'+CRLF+
'   }'+CRLF+
'public:'+CRLF+
'   TOBJ_STARTER(int nthreads) {'+CRLF+
'     __nthreads = nthreads;'+CRLF+
'     __tid = get_thread_id();'+CRLF+
'     sprintf(__this_id, "&&%llX", (unsigned long long) this);'+CRLF+
'     // Помещаем в стек свой this-ptr'+CRLF+
'     omp_set_lock(&__lock_tobjs__);'+CRLF+
'     stack<TOBJ_STARTER *> * st = __tobj_this_stack[__tid];'+CRLF+
'     if (st == NULL)'+CRLF+
'        __tobj_this_stack[__tid] = st = new stack<TOBJ_STARTER *>();'+CRLF+
'     st->push(this);'+CRLF+
'     omp_unset_lock(&__lock_tobjs__);'+CRLF+
'   }'+CRLF+
'   // Возвращает идентификатор транзакции текущего объекта'+CRLF+
'   const char * get_transaction_id() {'+CRLF+
'     return __this_id;'+CRLF+
'   }'+CRLF+
'   virtual void sync(bool sync_children = true) = 0;'+CRLF+
'   virtual bool join(__page_fun f, int &id, int npreconds = 0, int * preconds = NULL, bool set_join_lock = true) = 0;'+CRLF+
'   // Не прерывая работу, ставит ее на пересогласование в транзакционном блоке. Если вызван с отличным'+CRLF+
'   // от NULL параметром = идентификатором базовой транзакции, то ставит на пересогласование все работы'+CRLF+
'   // от текущей до породивших ее в транзакциях более высокого уровня вплоть до базовой транзакции.'+CRLF+
'   virtual bool fail_till(const char * __till_id__ = NULL) {'+CRLF+
'   	__info_transaction__ * till_info;'+CRLF+
'   	string id;'+CRLF+
'	int tid = omp_get_thread_num();'+CRLF+
''+CRLF+
'   	omp_set_lock(&__lock_atomics__);'+CRLF+
'   	__info_transaction__ * info = get_transaction(__this_id);'+CRLF+
'   	if (__till_id__ == NULL)'+CRLF+
'   		till_info = get_transaction_by_thread(id, false);'+CRLF+
'   	else'+CRLF+
'   		till_info = get_transaction(__till_id__);'+CRLF+
'   	if (!check_ways(info, tid, till_info)) {'+CRLF+
'   		omp_unset_lock(&__lock_atomics__);'+CRLF+
'   		return false;'+CRLF+
'   	} else {'+CRLF+
'		info->failed[tid] = true;'+CRLF+
'		while (info != till_info) {'+CRLF+
'			int id = info->parent_ids[tid];'+CRLF+
'			info = info->parents[tid];'+CRLF+
'   			info->failed[id] = true;'+CRLF+
'			tid = id;'+CRLF+
'		} while (1);'+CRLF+
'   		omp_unset_lock(&__lock_atomics__);'+CRLF+
'   		return true;'+CRLF+
'   	}'+CRLF+
'   }'+CRLF+
'   virtual int  num_free() = 0;'+CRLF+
'   virtual ~TOBJ_STARTER() {'+CRLF+
'     // Уничтожаем транзакцию this+ptr -- стираем ее из списка'+CRLF+
'     omp_set_lock(&__lock_atomics__);'+CRLF+
'     map< string, __info_transaction__ * >::iterator it = __transactions__.find(__this_id);'+CRLF+
'     if (it != __transactions__.end())'+CRLF+
'        __transactions__.erase(it);'+CRLF+
'     omp_unset_lock(&__lock_atomics__);'+CRLF+
'   }'+CRLF+
'};'+CRLF+
''+CRLF+
'class TOBJ_STOPPER {'+CRLF+
'public:'+CRLF+
'   TOBJ_STOPPER(int nthreads) {'+CRLF+
'     // Извлекаем из стека свой this-ptr'+CRLF+
'     omp_set_lock(&__lock_tobjs__);'+CRLF+
'     __tobj_this_stack[get_thread_id()]->pop();'+CRLF+
'     omp_unset_lock(&__lock_tobjs__);'+CRLF+
'   }'+CRLF+
'};'+CRLF+
''+CRLF+
'class TVar {'+CRLF+
'protected:'+CRLF+
'  string id;'+CRLF+
'  int winner;'+CRLF+
'public:'+CRLF+
'  TVar(const char * __id__ = "") {'+CRLF+
'    if (*__id__ == 0) {'+CRLF+
'     long long tid = get_thread_id();'+CRLF+
'     omp_set_lock(&__lock_tobjs__);'+CRLF+
'     map< long long, stack<TOBJ_STARTER *> *>::iterator it = __tobj_this_stack.find(tid);'+CRLF+
'     if (it == __tobj_this_stack.end() || it->second->size() == 0)'+CRLF+
'        id = __id__;'+CRLF+
'     else {'+CRLF+
'        TOBJ_STARTER * parent = it->second->top();'+CRLF+
'        id = parent->get_transaction_id();'+CRLF+
'     }'+CRLF+
'     omp_unset_lock(&__lock_tobjs__);'+CRLF+
'    } else'+CRLF+
'	id = __id__;'+CRLF+
'    omp_set_lock(&__lock_atomics__);'+CRLF+
'    get_transaction(id.c_str())->__atomics__.push_back(this);'+CRLF+
'    omp_unset_lock(&__lock_atomics__);'+CRLF+
'  }'+CRLF+
'  virtual void startTransaction() = 0;'+CRLF+
'  virtual void check(signed char * state) = 0;'+CRLF+
'  virtual void commit(const vector<int> & _winners) = 0;'+CRLF+
'  virtual ~TVar() {'+CRLF+
'    omp_set_lock(&__lock_atomics__);'+CRLF+
'	get_transaction(id.c_str())->__atomics__.remove(this);'+CRLF+
'    omp_unset_lock(&__lock_atomics__);'+CRLF+
'  }'+CRLF+
'};'+CRLF+
''+CRLF+
'class TChannel: public TVar {'+CRLF+
'protected:'+CRLF+
'  int owner;'+CRLF+
'  bool input;'+CRLF+
'  bool shot;'+CRLF+
'public:'+CRLF+
'  TChannel(bool in, const char * name, int _owner = -1, const char * __id__ = ""): TVar(__id__) {'+CRLF+
'     input = in;'+CRLF+
'     if (_owner < 0) owner = omp_get_thread_num(); else owner = _owner;'+CRLF+
'     omp_set_lock(&__lock_atomics__);'+CRLF+
'	 __info_transaction__ * info = get_transaction(id.c_str());'+CRLF+
'     map<string, pair<TChannel *, TChannel *> >::iterator it = info->__io__.find(name);'+CRLF+
'     if (it == info->__io__.end()) {'+CRLF+
'        if (in)'+CRLF+
'           info->__io__[name] = pair<TChannel *, TChannel *>(this, NULL);'+CRLF+
'        else'+CRLF+
'           info->__io__[name] = pair<TChannel *, TChannel *>(NULL, this);'+CRLF+
'     } else'+CRLF+
'        if (in)'+CRLF+
'           info->__io__[name].first = this;'+CRLF+
'        else'+CRLF+
'           info->__io__[name].second = this;'+CRLF+
'     omp_unset_lock(&__lock_atomics__);'+CRLF+
'     shot = false;'+CRLF+
'  }'+CRLF+
'  int get_owner() { return owner; }'+CRLF+
'  bool get_input() { return input; }'+CRLF+
'  bool get_shot() { return shot; }'+CRLF+
'  virtual void prepareRestart() = 0;'+CRLF+
'};'+CRLF+
''+CRLF+
'#define transaction_atomic(id) for (init_transaction(id); !end_transaction(); commit_transaction()) if (get_working()[omp_get_thread_num()])'+CRLF+
''+CRLF+
'bool * get_working() {'+CRLF+
'	omp_set_lock(&__lock_atomics__);'+CRLF+
'	string id;'+CRLF+
'	__info_transaction__ * info = get_transaction_by_thread(id);'+CRLF+
'	omp_unset_lock(&__lock_atomics__);'+CRLF+
''+CRLF+
'	return info->working;'+CRLF+
'}'+CRLF+
''+CRLF+
'int get_nprocs() {'+CRLF+
'	omp_set_lock(&__lock_atomics__);'+CRLF+
'	string id;'+CRLF+
'	__info_transaction__ * info = get_transaction_by_thread(id);'+CRLF+
'	omp_unset_lock(&__lock_atomics__);'+CRLF+
''+CRLF+
'	return info->__transaction_procs__[omp_get_thread_num()];'+CRLF+
'}'+CRLF+
''+CRLF+
'bool in_transaction(const char * __id__ = NULL) {'+CRLF+
'	omp_set_lock(&__lock_atomics__);'+CRLF+
'	__info_transaction__ * info;'+CRLF+
'	if (__id__ == NULL) {'+CRLF+
'		string id;'+CRLF+
'		info = get_transaction_by_thread(id, false);'+CRLF+
'	} else'+CRLF+
'		info = get_transaction(__id__);'+CRLF+
'	omp_unset_lock(&__lock_atomics__);'+CRLF+
''+CRLF+
'	return info != NULL && info->__in_transaction__;'+CRLF+
'}'+CRLF+
''+CRLF+
'// Был ли вызван fail для текущего потока'+CRLF+
'bool is_failed() {'+CRLF+
'	__info_transaction__ * info;'+CRLF+
'	string id;'+CRLF+
''+CRLF+
'	omp_set_lock(&__lock_atomics__);'+CRLF+
'	info = get_transaction_by_thread(id, false);'+CRLF+
'	omp_unset_lock(&__lock_atomics__);'+CRLF+
''+CRLF+
'	return info != NULL && info->failed[omp_get_thread_num()];'+CRLF+
'}'+CRLF+
''+CRLF+
'// Не прерывая работу, ставит ее на пересогласование в транзакционном блоке'+CRLF+
'bool fail() {'+CRLF+
'	string id;'+CRLF+
'	omp_set_lock(&__lock_atomics__);'+CRLF+
'	__info_transaction__ * info = get_transaction_by_thread(id, false);'+CRLF+
'	omp_unset_lock(&__lock_atomics__);'+CRLF+
'	if (info == NULL)'+CRLF+
'		return false;'+CRLF+
'	else {'+CRLF+
'		info->failed[omp_get_thread_num()] = true;'+CRLF+
'		return true;'+CRLF+
'	}'+CRLF+
'}'+CRLF+
''+CRLF+
'void restart_optimizer(const string & id, int np) {'+CRLF+
'	omp_set_lock(&__lock_atomics__);'+CRLF+
'	__info_transaction__ * info = get_transaction(id.c_str());'+CRLF+
'	omp_unset_lock(&__lock_atomics__);'+CRLF+
''+CRLF+
'	if (info != NULL) {'+CRLF+
'		info->__stat_transaction__.__transaction_misses__.resize(np);'+CRLF+
'		info->__stat_transaction__.__transaction_procs__.resize(np);'+CRLF+
''+CRLF+
'		info->__stat_transaction__.__transaction_counter__ = 0; // K'+CRLF+
''+CRLF+
'		for (int i = 0; i < np; i++) {'+CRLF+
'			info->__stat_transaction__.__transaction_timings__[i].clear();'+CRLF+
'			info->__stat_transaction__.__transaction_retimings__[i].clear();'+CRLF+
'			if (i < np - 1)'+CRLF+
'				info->__stat_transaction__.__transaction_procs__[i] = 1;'+CRLF+
'			else'+CRLF+
'				info->__stat_transaction__.__transaction_procs__[i] = __max(1, omp_get_num_procs() - (np - 1));'+CRLF+
'			info->__stat_transaction__.__transaction_misses__[i] = 0;'+CRLF+
'			info->__transaction_procs__[i] = info->__stat_transaction__.__transaction_procs__[i];'+CRLF+
'		}'+CRLF+
'	}'+CRLF+
'}'+CRLF+
''+CRLF+
'void init_transaction(char * id) {'+CRLF+
'	omp_set_lock(&__lock_atomics__);'+CRLF+
'	__info_transaction__ * info = get_transaction(id);'+CRLF+
'	__map_threads__[get_thread_id()] = id;'+CRLF+
'	omp_unset_lock(&__lock_atomics__);'+CRLF+
''+CRLF+
'#pragma omp barrier'+CRLF+
'#pragma omp master'+CRLF+
'  {'+CRLF+
'	  const int epochs = 5;'+CRLF+
'	  const int interval = 500;'+CRLF+
''+CRLF+
'	  int np = omp_get_num_threads();'+CRLF+
'	  int nm = omp_get_num_procs();'+CRLF+
''+CRLF+
'	  for (int i = 0; i < np; i++) {'+CRLF+
'		  info->working[i] = true;'+CRLF+
'		  info->job_ids[i] = 0;'+CRLF+
'		  info->failed[i] = false;'+CRLF+
'	  }'+CRLF+
''+CRLF+
'	  int idn = strlen(id);'+CRLF+
''+CRLF+
'	  if (idn > 0 && (!(idn >= 2 && id[0] == ''&'' && id[1] == ''&'')) && np > 1) {'+CRLF+
'		  if (info->__stat_transaction__.__transaction_counter__ < 0 || info->__stat_transaction__.__transaction_counter__ % (interval*(np - 1)*(nm - 1)) == 0)'+CRLF+
'			  restart_optimizer(id, np);'+CRLF+
''+CRLF+
'		  if (info->__stat_transaction__.__transaction_counter__ > 0 && nm >= 2 * np && info->__stat_transaction__.__transaction_counter__ < epochs*(np - 1)*(nm - 1)) {'+CRLF+
'			  int k = info->__stat_transaction__.__transaction_counter__ / (nm - 1);'+CRLF+
'			  int s = info->__stat_transaction__.__transaction_counter__ % (nm - 1);'+CRLF+
'			  k %= (np - 1);'+CRLF+
'			  if (k == 0 && s == 0) {'+CRLF+
'				  for (int i = 0; i < np; i++) {'+CRLF+
'					  if (i < np - 1)'+CRLF+
'						  info->__stat_transaction__.__transaction_procs__[i] = 1;'+CRLF+
'					  else'+CRLF+
'						  info->__stat_transaction__.__transaction_procs__[i] = __max(1, nm - (np - 1));'+CRLF+
'				  }'+CRLF+
'			  }'+CRLF+
'			  else'+CRLF+
'				  info->__stat_transaction__.__transaction_procs__[k]++;'+CRLF+
'			  if (info->__stat_transaction__.__transaction_procs__[k] == nm) {'+CRLF+
'				  info->__stat_transaction__.__transaction_procs__[k] = 1;'+CRLF+
'				  info->__stat_transaction__.__transaction_procs__[k + 1]++;'+CRLF+
'			  }'+CRLF+
'			  int sum = 0;'+CRLF+
'			  for (int i = 0; i < np; i++)'+CRLF+
'				  if (i < np - 1) {'+CRLF+
'					  sum += info->__stat_transaction__.__transaction_procs__[i];'+CRLF+
'				  }'+CRLF+
'				  else'+CRLF+
'					  info->__stat_transaction__.__transaction_procs__[i] = __max(1, nm - sum);'+CRLF+
'		  }'+CRLF+
'		  else if (info->__stat_transaction__.__transaction_counter__ == epochs*(np - 1)*(nm - 1) && nm >= 2 * np) {'+CRLF+
'			  /*'+CRLF+
'						cout << "K = " << info->__stat_transaction__.__transaction_counter__ << endl;'+CRLF+
'						cout << "Betta = ";'+CRLF+
'						for (int i = 0; i < np; i++)'+CRLF+
'						cout << (1.0*info->__stat_transaction__.__transaction_misses__[i]/info->__stat_transaction__.__transaction_counter__) << " ";'+CRLF+
'						cout << endl;'+CRLF+
'						for (int i = 0; i < np; i++) {'+CRLF+
'						cout << "Timings[" << i << "] = ";'+CRLF+
'						map<int, LARGE_INTEGER>::iterator it;'+CRLF+
'						for (it = info->__stat_transaction__.__transaction_timings__[i].begin(); it != info->__stat_transaction__.__transaction_timings__[i].end() ; it++)'+CRLF+
'						cout << "[" << it->first << "] " << -clock_val(it->second) << " ";'+CRLF+
'						cout << endl;'+CRLF+
'						}'+CRLF+
'						for (int i = 0; i < np; i++) {'+CRLF+
'						cout << "RETimings[" << i << "] = ";'+CRLF+
'						map<int, LARGE_INTEGER>::iterator it;'+CRLF+
'						for (it = info->__stat_transaction__.__transaction_retimings__[i].begin(); it != info->__stat_transaction__.__transaction_retimings__[i].end() ; it++)'+CRLF+
'						cout << "[" << it->first << "] " << -clock_val(it->second) << " ";'+CRLF+
'						cout << endl;'+CRLF+
'						}'+CRLF+
'						*/'+CRLF+
'			  double mup[__max_procs__] = { 0.0 };'+CRLF+
'			  double sp[__max_procs__] = { 0.0 };'+CRLF+
'			  double dmp[__max_procs__] = { 0.0 };'+CRLF+
'			  for (int i = 0; i < np; i++) {'+CRLF+
'				  int irow[3];'+CRLF+
'				  long double A[3][3] = { 0.0 };'+CRLF+
'				  long double LU[9];'+CRLF+
'				  long double B[3] = { 0.0 };'+CRLF+
'				  long double X[3];'+CRLF+
''+CRLF+
'				  map<int, LARGE_INTEGER>::iterator it;'+CRLF+
'				  for (it = info->__stat_transaction__.__transaction_timings__[i].begin(); it != info->__stat_transaction__.__transaction_timings__[i].end(); it++) {'+CRLF+
'					  int nn = it->first;'+CRLF+
'					  B[0] += -clock_val(it->second);'+CRLF+
'					  B[1] += nn*(-clock_val(it->second));'+CRLF+
'					  B[2] += (-clock_val(it->second)) / nn;'+CRLF+
'					  A[0][0] += 1.0;'+CRLF+
'					  A[0][1] += nn;'+CRLF+
'					  A[0][2] += 1.0 / nn;'+CRLF+
'					  A[1][0] += nn;'+CRLF+
'					  A[1][1] += nn*nn;'+CRLF+
'					  A[1][2] += 1.0;'+CRLF+
'					  A[2][0] += 1.0 / nn;'+CRLF+
'					  A[2][1] += 1.0;'+CRLF+
'					  A[2][2] += 1.0 / nn / nn;'+CRLF+
'				  }'+CRLF+
'				  if (_GetLU(3, irow, (long double *)A, LU) && _SolveLU(3, irow, LU, B, X)) {'+CRLF+
'					  mup[i] = X[0];'+CRLF+
'					  sp[i] = X[1];'+CRLF+
'					  dmp[i] = X[2];'+CRLF+
'				  }'+CRLF+
'			  }'+CRLF+
'			  double mu[__max_procs__] = { mup[0] };'+CRLF+
'			  double s[__max_procs__] = { sp[0] };'+CRLF+
'			  double dm[__max_procs__] = { dmp[0] };'+CRLF+
'			  for (int i = 1; i < np; i++)'+CRLF+
'				  if (info->__stat_transaction__.__transaction_misses__[i]) {'+CRLF+
'					  if (info->__stat_transaction__.__transaction_retimings__[i].size() < 3) {'+CRLF+
'						  info->__stat_transaction__.__transaction_misses__[i] = 0;'+CRLF+
'						  continue;'+CRLF+
'					  }'+CRLF+
''+CRLF+
'					  int irow[3];'+CRLF+
'					  long double A[3][3] = { 0.0 };'+CRLF+
'					  long double LU[9];'+CRLF+
'					  long double B[3] = { 0.0 };'+CRLF+
'					  long double X[3];'+CRLF+
''+CRLF+
'					  map<int, LARGE_INTEGER>::iterator it;'+CRLF+
'					  for (it = info->__stat_transaction__.__transaction_retimings__[i].begin(); it != info->__stat_transaction__.__transaction_retimings__[i].end(); it++) {'+CRLF+
'						  int nn = it->first;'+CRLF+
'						  B[0] += -clock_val(it->second);'+CRLF+
'						  B[1] += nn*(-clock_val(it->second));'+CRLF+
'						  B[2] += (-clock_val(it->second)) / nn;'+CRLF+
'						  A[0][0] += 1.0;'+CRLF+
'						  A[0][1] += nn;'+CRLF+
'						  A[0][2] += 1.0 / nn;'+CRLF+
'						  A[1][0] += nn;'+CRLF+
'						  A[1][1] += nn*nn;'+CRLF+
'						  A[1][2] += 1.0;'+CRLF+
'						  A[2][0] += 1.0 / nn;'+CRLF+
'						  A[2][1] += 1.0;'+CRLF+
'						  A[2][2] += 1.0 / nn / nn;'+CRLF+
'					  }'+CRLF+
'					  if (_GetLU(3, irow, (long double *)A, LU) && _SolveLU(3, irow, LU, B, X)) {'+CRLF+
'						  mu[i] = X[0];'+CRLF+
'						  s[i] = X[1];'+CRLF+
'						  dm[i] = X[2];'+CRLF+
'					  }'+CRLF+
'				  }'+CRLF+
'			  auto F = [&](const vector<int> & N)->double {'+CRLF+
'				  double TS[__max_procs__] = { 0.0 };'+CRLF+
'				  for (int i = 0; i < np; i++) {'+CRLF+
'					  TS[i] = mup[i] + sp[i] * N[i] + dmp[i] / N[i];'+CRLF+
'				  }'+CRLF+
'				  double result = 0.0;'+CRLF+
'				  for (int i = 0; i < np; i++)'+CRLF+
'					  if (i == 0 || info->__stat_transaction__.__transaction_misses__[i]) {'+CRLF+
'						  double m = mu[i] + s[i] * N[i] + dm[i] / N[i];'+CRLF+
'						  for (int j = i + 1; j < np; j++)'+CRLF+
'							  if (TS[j] > m)'+CRLF+
'								  m = TS[j];'+CRLF+
'						  if (i == 0)'+CRLF+
'							  result += m;'+CRLF+
'						  else'+CRLF+
'							  result += 1.0*info->__stat_transaction__.__transaction_misses__[i] / info->__stat_transaction__.__transaction_counter__*m;'+CRLF+
'					  }'+CRLF+
'				  return result;'+CRLF+
'			  };'+CRLF+
'			  for (int i = 0; i < np; i++)'+CRLF+
'				  info->__stat_transaction__.__transaction_procs__[i] = 1;'+CRLF+
'			  int SumN = np;'+CRLF+
'			  int MaxN = omp_get_num_procs();'+CRLF+
'			  while (SumN < MaxN) {'+CRLF+
'				  double semi_grad[__max_procs__];'+CRLF+
'				  double F0 = F(info->__stat_transaction__.__transaction_procs__);'+CRLF+
'				  for (int i = 0; i < np; i++) {'+CRLF+
'					  info->__stat_transaction__.__transaction_procs__[i]++;'+CRLF+
'					  semi_grad[i] = F(info->__stat_transaction__.__transaction_procs__);'+CRLF+
'					  info->__stat_transaction__.__transaction_procs__[i]--;'+CRLF+
'				  }'+CRLF+
'				  int k = 0;'+CRLF+
'				  for (int i = 1; i < np; i++)'+CRLF+
'					  if (semi_grad[i] < semi_grad[k])'+CRLF+
'						  k = i;'+CRLF+
'				  if (semi_grad[k] > F0) break;'+CRLF+
'				  info->__stat_transaction__.__transaction_procs__[k]++;'+CRLF+
'				  SumN++;'+CRLF+
'			  }'+CRLF+
'			  /**/'+CRLF+
'			  cout << "NN = ";'+CRLF+
'			  for (int i = 0; i < np; i++)'+CRLF+
'				  cout << info->__stat_transaction__.__transaction_procs__[i] << " ";'+CRLF+
'			  cout << endl;'+CRLF+
'			  /**/'+CRLF+
'		  }'+CRLF+
''+CRLF+
'		  LARGE_INTEGER c = { 0 };'+CRLF+
'		  QueryPerformanceCounter(&c);'+CRLF+
'		  for (int i = 0; i < np; i++) {'+CRLF+
'			  if (info->__stat_transaction__.__transaction_timings__[i].find(info->__stat_transaction__.__transaction_procs__[i]) == info->__stat_transaction__.__transaction_timings__[i].end())'+CRLF+
'				  info->__stat_transaction__.__transaction_timings__[i][info->__stat_transaction__.__transaction_procs__[i]] = c;'+CRLF+
'			  else'+CRLF+
'				  clock_val(info->__stat_transaction__.__transaction_timings__[i][info->__stat_transaction__.__transaction_procs__[i]]) += clock_val(c);'+CRLF+
'		  }'+CRLF+
'		  for (int i = 0; i < np; i++)'+CRLF+
'			  info->__transaction_procs__[i] = info->__stat_transaction__.__transaction_procs__[i];'+CRLF+
'	  }'+CRLF+
'	  else'+CRLF+
'		  for (int i = 0; i < np; i++)'+CRLF+
'			  info->__transaction_procs__[i] = __max(1, nm / np);'+CRLF+
''+CRLF+
'	  omp_set_lock(&__lock_atomics__);'+CRLF+
'	  for (auto v : info->__atomics__) {'+CRLF+
'		  v->startTransaction();'+CRLF+
'	  }'+CRLF+
'	  info->__in_transaction__ = true;'+CRLF+
'	  omp_unset_lock(&__lock_atomics__);'+CRLF+
'  }'+CRLF+
'#pragma omp barrier'+CRLF+
'}'+CRLF+
''+CRLF+
'bool end_transaction() {'+CRLF+
'	omp_set_lock(&__lock_atomics__);'+CRLF+
'	string id;'+CRLF+
'	__info_transaction__ * info = get_transaction_by_thread(id);'+CRLF+
'	omp_unset_lock(&__lock_atomics__);'+CRLF+
'#pragma omp barrier'+CRLF+
'	int np = omp_get_num_threads();'+CRLF+
'	for (int i = 0; i < np; i++)'+CRLF+
'		if (info->working[i])'+CRLF+
'			return false;'+CRLF+
'#pragma omp master'+CRLF+
'	{'+CRLF+
'		info->__in_transaction__ = false;'+CRLF+
'		if (id.length() > 0) {'+CRLF+
'			info->__stat_transaction__.__transaction_counter__++;'+CRLF+
'		}'+CRLF+
'	}'+CRLF+
'#pragma omp barrier'+CRLF+
'	return true;'+CRLF+
'}'+CRLF+
''+CRLF+
'void commit_transaction() {'+CRLF+
'	omp_set_lock(&__lock_atomics__);'+CRLF+
'	string sid;'+CRLF+
'	__info_transaction__ * info = get_transaction_by_thread(sid);'+CRLF+
'	omp_unset_lock(&__lock_atomics__);'+CRLF+
''+CRLF+
'	vector<int> winners;'+CRLF+
''+CRLF+
'	LARGE_INTEGER c = { 0 };'+CRLF+
'	QueryPerformanceCounter(&c);'+CRLF+
''+CRLF+
'	int np = omp_get_num_threads();'+CRLF+
''+CRLF+
'#pragma omp barrier'+CRLF+
'#pragma omp master'+CRLF+
'	{'+CRLF+
'		omp_set_lock(&__lock_atomics__);'+CRLF+
''+CRLF+
'		bool sendrecvs[__max_procs__] = { false };'+CRLF+
''+CRLF+
'		signed char state[__max_procs__];'+CRLF+
'		for (int i = 0; i < np; i++)'+CRLF+
'			state[i] = __reader__;'+CRLF+
'		for (auto v : info->__atomics__) {'+CRLF+
'			TChannel * ch = dynamic_cast<TChannel *>(v);'+CRLF+
'			if (ch == NULL)'+CRLF+
'				v->check(state);'+CRLF+
'			else'+CRLF+
'				sendrecvs[ch->get_owner()] |= ch->get_shot();'+CRLF+
'		}'+CRLF+
''+CRLF+
'		bool solved = false;'+CRLF+
'		do {'+CRLF+
'			signed char old_state[__max_procs__];'+CRLF+
'			for (int i = 0; i < np; i++)'+CRLF+
'				old_state[i] = state[i];'+CRLF+
'			for (auto v : info->__atomics__) {'+CRLF+
'				TChannel * ch = dynamic_cast<TChannel *>(v);'+CRLF+
'				if (ch != NULL && !ch->get_input())'+CRLF+
'					v->check(state);'+CRLF+
'			}'+CRLF+
'			for (auto v : info->__atomics__) {'+CRLF+
'				TChannel * ch = dynamic_cast<TChannel *>(v);'+CRLF+
'				if (ch != NULL && ch->get_input())'+CRLF+
'					v->check(state);'+CRLF+
'			}'+CRLF+
''+CRLF+
'			for (auto v : info->__atomics__) {'+CRLF+
'				TChannel * ch = dynamic_cast<TChannel *>(v);'+CRLF+
'				if (ch != NULL) {'+CRLF+
'					int own = ch->get_owner();'+CRLF+
'					if (state[own] == __another__ && state[own] != old_state[own])'+CRLF+
'						ch->prepareRestart();'+CRLF+
'				}'+CRLF+
'			}'+CRLF+
''+CRLF+
'			solved = true;'+CRLF+
'			for (int i = 0; solved && i < np; i++)'+CRLF+
'				if (old_state[i] != state[i])'+CRLF+
'					solved = false;'+CRLF+
'		} while (!solved);'+CRLF+
''+CRLF+
'		winners.reserve(256);'+CRLF+
'		for (int i = 0; i < np; i++)'+CRLF+
'			if (!info->failed[i] && info->working[i] && state[i] != __another__) {'+CRLF+
'				winners.push_back(i);'+CRLF+
'				info->working[i] = false;'+CRLF+
'				info->__funs[i] = nullptr;'+CRLF+
'				if (info->job_ids[i]) {'+CRLF+
'					omp_set_lock(&__lock_tobjs__);'+CRLF+
'					__tobj_job * jinfo = __tobj_jobs[info->job_ids[i]-1];'+CRLF+
'					jinfo->finished = true;'+CRLF+
'					omp_unset_lock(&__lock_tobjs__);'+CRLF+
'				}'+CRLF+
'			}'+CRLF+
'		if (winners.size() == 0) {'+CRLF+
'			for (int i = 0; i < np; i++)'+CRLF+
'				if (!info->failed[i] && info->working[i] && !sendrecvs[i]) {'+CRLF+
'					winners.push_back(i);'+CRLF+
'					info->working[i] = false;'+CRLF+
'					info->__funs[i] = nullptr;'+CRLF+
'					if (info->job_ids[i]) {'+CRLF+
'						omp_set_lock(&__lock_tobjs__);'+CRLF+
'						__tobj_job * jinfo = __tobj_jobs[info->job_ids[i]-1];'+CRLF+
'						jinfo->finished = true;'+CRLF+
'						omp_unset_lock(&__lock_tobjs__);'+CRLF+
'					}'+CRLF+
'					break;'+CRLF+
'				}'+CRLF+
'		}'+CRLF+
'		for (auto v : info->__atomics__) {'+CRLF+
'			v->commit(winners);'+CRLF+
'		}'+CRLF+
'		for (auto v : info->__atomics__) {'+CRLF+
'			TChannel * ch = dynamic_cast<TChannel *>(v);'+CRLF+
'			if (ch == NULL) v->startTransaction();'+CRLF+
'		}'+CRLF+
'		for (auto v : info->__atomics__) {'+CRLF+
'			TChannel * ch = dynamic_cast<TChannel *>(v);'+CRLF+
'			if (ch != NULL && info->working[ch->get_owner()]) v->startTransaction();'+CRLF+
'		}'+CRLF+
'		for (int i = 0; i < np; i++)'+CRLF+
'			info->failed[i] = false;'+CRLF+
''+CRLF+
'		omp_unset_lock(&__lock_atomics__);'+CRLF+
'	}'+CRLF+
'#pragma omp barrier'+CRLF+
''+CRLF+
'#pragma omp critical(commit_transaction)'+CRLF+
'  {'+CRLF+
'	  int id = omp_get_thread_num();'+CRLF+
''+CRLF+
'	  if (sid.length() > 0 && (!(sid.substr(0, 2) == "&&")) && np > 1) {'+CRLF+
'		  omp_set_lock(&__lock_atomics__);'+CRLF+
''+CRLF+
'		  int nn = info->__stat_transaction__.__transaction_procs__[id];'+CRLF+
'		  if (clock_val(info->__stat_transaction__.__transaction_timings__[id][nn]) >= 0) { // Первый счет'+CRLF+
'			  if (info->working[id]) {'+CRLF+
'				  LARGE_INTEGER c1 = { 0 };'+CRLF+
'				  QueryPerformanceCounter(&c1);'+CRLF+
'				  if (info->__stat_transaction__.__transaction_retimings__[id].find(nn) == info->__stat_transaction__.__transaction_retimings__[id].end())'+CRLF+
'					  info->__stat_transaction__.__transaction_retimings__[id][nn] = c1;'+CRLF+
'				  else'+CRLF+
'					  clock_val(info->__stat_transaction__.__transaction_retimings__[id][nn]) += clock_val(c1);'+CRLF+
'				  info->__stat_transaction__.__transaction_retimings__[id][-1] = c1;'+CRLF+
'				  info->__stat_transaction__.__transaction_misses__[id]++;'+CRLF+
'			  }'+CRLF+
'			  clock_val(info->__stat_transaction__.__transaction_timings__[id][nn]) -= clock_val(c);'+CRLF+
'		  }'+CRLF+
'		  else if (info->__stat_transaction__.__transaction_retimings__[id].find(nn) != info->__stat_transaction__.__transaction_retimings__[id].end() && clock_val(info->__stat_transaction__.__transaction_retimings__[id][nn]) >= 0) { // Пересчет'+CRLF+
'			  if (!info->working[id]) {'+CRLF+
'				  clock_val(info->__stat_transaction__.__transaction_retimings__[id][nn]) -= clock_val(c);'+CRLF+
'				  info->__stat_transaction__.__transaction_retimings__[id].erase(-1);'+CRLF+
'			  }'+CRLF+
'			  else {'+CRLF+
'				  LARGE_INTEGER c1 = { 0 };'+CRLF+
'				  QueryPerformanceCounter(&c1);'+CRLF+
''+CRLF+
'				  clock_val(info->__stat_transaction__.__transaction_retimings__[id][nn]) -= clock_val(info->__stat_transaction__.__transaction_retimings__[id][-1]);'+CRLF+
'				  clock_val(info->__stat_transaction__.__transaction_retimings__[id][nn]) += clock_val(c1);'+CRLF+
'				  info->__stat_transaction__.__transaction_retimings__[id][-1] = c1;'+CRLF+
'			  }'+CRLF+
'		  }'+CRLF+
''+CRLF+
'		  omp_unset_lock(&__lock_atomics__);'+CRLF+
'	  }'+CRLF+
'  }'+CRLF+
'}'+CRLF+
''+CRLF+
'template<class Type>'+CRLF+
'  class TIn: public TChannel, public funneled_predictor_in<Type> {'+CRLF+
'  protected:'+CRLF+
'    bool predicted;'+CRLF+
'    Type * __buf__;'+CRLF+
'  public:'+CRLF+
'    TIn(const char * Name, int N = 1, int P = 2, double rel_eps = 0.001, int _owner = -1, const char * __id__ = ""):'+CRLF+
'		TChannel(true, Name, _owner, __id__), funneled_predictor_in<Type>(Name, N, P, rel_eps) {'+CRLF+
'       __buf__ = new Type[N];'+CRLF+
'    }'+CRLF+
'    virtual ~TIn() {'+CRLF+
'       delete[] __buf__;'+CRLF+
'    }'+CRLF+
'    virtual void prepareRestart() {'+CRLF+
'       predicted = false;'+CRLF+
'    }'+CRLF+
'    virtual void startTransaction() {'+CRLF+
'       prepareRestart();'+CRLF+
'       shot = false;'+CRLF+
'    };'+CRLF+
'    virtual void check(signed char * state) {'+CRLF+
'       _funnel_with_history<Type> * Ref = reinterpret_cast<_funnel_with_history<Type> *>(this->getRef());'+CRLF+
''+CRLF+
'      if (Ref && shot) {'+CRLF+
'		 string sid;'+CRLF+
'		 __info_transaction__ * info = get_transaction_by_thread(sid);'+CRLF+
'         map<string, pair<TChannel *, TChannel *> >::iterator it = info->__io__.find(Ref->Name);'+CRLF+
'         bool no_send = true;'+CRLF+
'         if (it != info->__io__.end()) {'+CRLF+
'            no_send = state[it->second.second->get_owner()] != __another__;'+CRLF+
'         }'+CRLF+
'         if (predicted) {'+CRLF+
'            int SizeInBytes = Ref->getN()*sizeof(Type);'+CRLF+
'            funneled_in<Type>::get(__buf__, SizeInBytes);'+CRLF+
'            Ref->correct();'+CRLF+
'         }'+CRLF+
'         omp_set_lock(&Ref->Lock);'+CRLF+
'         if (no_send && (state[owner] == __another__ || Ref->hasPredicted() && !Ref->isCalculated())) {'+CRLF+
'            Ref->State |= tnlValue;'+CRLF+
'            state[owner] = __another__;'+CRLF+
'         }'+CRLF+
'         omp_unset_lock(&Ref->Lock);'+CRLF+
'         if (predicted) {'+CRLF+
'            Ref->unset_predict_results();'+CRLF+
'            predicted = false;'+CRLF+
'         }'+CRLF+
'      }'+CRLF+
'    };'+CRLF+
'    void get(Type * buf, double timeout) {'+CRLF+
'      if (!this->empty()) {'+CRLF+
'         _funnel_with_history<Type> * Ref = reinterpret_cast<_funnel_with_history<Type> *>(this->getRef());'+CRLF+
'         int SizeInBytes = Ref->getN()*sizeof(Type);'+CRLF+
'         funneled_in<Type>::get(buf, SizeInBytes);'+CRLF+
'         Ref->unset_predict_results();'+CRLF+
'         predicted = false;'+CRLF+
'      } else'+CRLF+
'         predicted = this->get_timed((void *) buf, timeout);'+CRLF+
'      shot = true;'+CRLF+
'    }'+CRLF+
'    virtual void commit(const vector<int> & _winners) {};'+CRLF+
'  };'+CRLF+
''+CRLF+
'template<class Type>'+CRLF+
'  class TOut: public TChannel, public funneled_predictor_out<Type> {'+CRLF+
'  protected:'+CRLF+
'  public:'+CRLF+
'    TOut(const char * Name, int N = 1, int P = 2, double rel_eps = 0.001, int _owner = -1, const char * __id__ = ""):'+CRLF+
'		TChannel(false, Name, _owner, __id__), funneled_predictor_out<Type>(Name, N, P, rel_eps) {'+CRLF+
'    }'+CRLF+
'    virtual void prepareRestart() {'+CRLF+
'       _funnel_with_history<Type> * Ref = reinterpret_cast<_funnel_with_history<Type> *>(this->getRef());'+CRLF+
''+CRLF+
'       if (Ref) {'+CRLF+
'           this->wait();'+CRLF+
'           if (Ref->State & tnlValue) {'+CRLF+
'              Ref->State &= ~tnlValue;'+CRLF+
'              Ref->pop_history(false);'+CRLF+
'           }'+CRLF+
'           omp_unset_lock(&Ref->Lock);'+CRLF+
'       }'+CRLF+
'    }'+CRLF+
'    virtual void startTransaction() {'+CRLF+
'       prepareRestart();'+CRLF+
'       shot = false;'+CRLF+
'    };'+CRLF+
'    virtual void check(signed char * state) {'+CRLF+
'       _funnel_with_history<Type> * Ref = reinterpret_cast<_funnel_with_history<Type> *>(this->getRef());'+CRLF+
''+CRLF+
'      if (Ref && state[owner] == __another__ && shot) {'+CRLF+
'		 string sid;'+CRLF+
'		 __info_transaction__ * info = get_transaction_by_thread(sid);'+CRLF+
'         map<string, pair<TChannel *, TChannel *> >::iterator it = info->__io__.find(Ref->Name);'+CRLF+
'         if (it != info->__io__.end()) {'+CRLF+
'            state[it->second.first->get_owner()] = __another__;'+CRLF+
'         }'+CRLF+
'      }'+CRLF+
'    };'+CRLF+
'    void put(Type * buf) {'+CRLF+
'      if (!shot) {'+CRLF+
'         _funnel_with_history<Type> * Ref = reinterpret_cast<_funnel_with_history<Type> *>(this->getRef());'+CRLF+
''+CRLF+
'         funneled_predictor_out<Type>::put((void *) buf, Ref->N*sizeof(Type));'+CRLF+
'         shot = true;'+CRLF+
'      }'+CRLF+
'    }'+CRLF+
'    virtual void commit(const vector<int> & _winners) {};'+CRLF+
'  };'+CRLF+
''+CRLF+
'template<class Type>'+CRLF+
'  class TScalar: public TVar {'+CRLF+
'  public:'+CRLF+
'    typedef std::function<Type(Type, Type)> reducer;'+CRLF+
'  protected:'+CRLF+
'    Type Data;'+CRLF+
'    reducer R;'+CRLF+
''+CRLF+
'    Type Buf[__max_procs__];'+CRLF+
''+CRLF+
'    LARGE_INTEGER reads[__max_procs__];'+CRLF+
'    LARGE_INTEGER writes[__max_procs__];'+CRLF+
'  public:'+CRLF+
'	TScalar(const char * __id__ = "") : TVar(__id__) { R = nullptr; }'+CRLF+
''+CRLF+
'    virtual void startTransaction() {'+CRLF+
'      for (int i = 0; i < __max_procs__; i++) {'+CRLF+
'          memset(&reads[i], 0, sizeof(LARGE_INTEGER));'+CRLF+
'          memset(&writes[i], 0, sizeof(LARGE_INTEGER));'+CRLF+
'          Buf[i] = Data;'+CRLF+
'      }'+CRLF+
'    }'+CRLF+
'    virtual void setReducer(reducer f) {'+CRLF+
'      R = f;'+CRLF+
'    }'+CRLF+
'    TScalar<Type> & operator = (const Type & val) {'+CRLF+
'      if (in_transaction(id.c_str())) {'+CRLF+
'         int id = omp_get_thread_num();'+CRLF+
'         LARGE_INTEGER c = { 0 };'+CRLF+
'         QueryPerformanceCounter(&c);'+CRLF+
'         writes[id] = c;'+CRLF+
'         Buf[id] = val;'+CRLF+
'      } else'+CRLF+
'         Data = val;'+CRLF+
'      return *this;'+CRLF+
'    }'+CRLF+
'    TScalar<Type> & operator ++ () {'+CRLF+
'      if (in_transaction(id.c_str())) {'+CRLF+
'         int id = omp_get_thread_num();'+CRLF+
'         LARGE_INTEGER c = { 0 };'+CRLF+
'         QueryPerformanceCounter(&c);'+CRLF+
'         reads[id] = c;'+CRLF+
'         writes[id] = c;'+CRLF+
'         ++Buf[id];'+CRLF+
'      } else'+CRLF+
'         ++Data;'+CRLF+
'      return *this;'+CRLF+
'    }'+CRLF+
'    TScalar<Type> & operator += (const Type v) {'+CRLF+
'      if (in_transaction(id.c_str())) {'+CRLF+
'         int id = omp_get_thread_num();'+CRLF+
'         LARGE_INTEGER c = { 0 };'+CRLF+
'         QueryPerformanceCounter(&c);'+CRLF+
'         reads[id] = c;'+CRLF+
'         writes[id] = c;'+CRLF+
'         Buf[id] += v;'+CRLF+
'      } else'+CRLF+
'         Data += v;'+CRLF+
'      return *this;'+CRLF+
'    }'+CRLF+
'    TScalar<Type> & operator -= (const Type v) {'+CRLF+
'      if (in_transaction(id.c_str())) {'+CRLF+
'         int id = omp_get_thread_num();'+CRLF+
'         LARGE_INTEGER c = { 0 };'+CRLF+
'         QueryPerformanceCounter(&c);'+CRLF+
'         reads[id] = c;'+CRLF+
'         writes[id] = c;'+CRLF+
'         Buf[id] -= v;'+CRLF+
'      } else'+CRLF+
'         Data -= v;'+CRLF+
'      return *this;'+CRLF+
'    }'+CRLF+
'    operator Type & () {'+CRLF+
'      if (in_transaction(id.c_str())) {'+CRLF+
'         int id = omp_get_thread_num();'+CRLF+
'         if (clock_val(reads[id]) == 0) {'+CRLF+
'            LARGE_INTEGER c = { 0 };'+CRLF+
'            QueryPerformanceCounter(&c);'+CRLF+
'            reads[id] = c;'+CRLF+
'         }'+CRLF+
'         return Buf[id];'+CRLF+
'      } else'+CRLF+
'         return Data;'+CRLF+
'    }'+CRLF+
'    virtual void check(signed char * state) {'+CRLF+
'      int np = omp_get_num_threads();'+CRLF+
'      if (R != nullptr) {'+CRLF+
'         for (int i = 1; i < np; i++)'+CRLF+
'             Buf[0] = R(Buf[0], Buf[i]);'+CRLF+
'      } else {'+CRLF+
'         LARGE_INTEGER min_write = { 0 };'+CRLF+
'         winner = -1;'+CRLF+
'         for (int i = 0; i < np; i++) {'+CRLF+
'             if (clock_val(writes[i]) != 0) {'+CRLF+
'                if (winner < 0 || clock_val(writes[i]) < clock_val(min_write)) {'+CRLF+
'                   winner = i;'+CRLF+
'                   min_write = writes[i];'+CRLF+
'                }'+CRLF+
'             }'+CRLF+
'         }'+CRLF+
'         if (winner >= 0)'+CRLF+
'            for (int i = 0; i < np; i++)'+CRLF+
'                if (i != winner) {'+CRLF+
'                   if (clock_val(writes[i]) != 0)'+CRLF+
'                      state[i] = __another__;'+CRLF+
'                   else'+CRLF+
'                      if (clock_val(reads[i]) != 0 && clock_val(reads[i]) < clock_val(min_write))'+CRLF+
'                         state[i] = __another__;'+CRLF+
'                } else'+CRLF+
'                   if (state[i] == __reader__)'+CRLF+
'                      state[i] = __writer__;'+CRLF+
'      }'+CRLF+
'    }'+CRLF+
'    virtual void commit(const vector<int> & _winners) {'+CRLF+
'      if (R != nullptr && _winners.size() > 0) {'+CRLF+
'         Data = Buf[0];'+CRLF+
'         return;'+CRLF+
'      }'+CRLF+
'      if (winner < 0 || _winners.size() == 0) return;'+CRLF+
'      if (find(_winners.begin(), _winners.end(), winner) != _winners.end())'+CRLF+
'         Data = Buf[winner];'+CRLF+
'    }'+CRLF+
'  };'+CRLF+
''+CRLF+
'template<class Type>'+CRLF+
'  class TArray: public TVar {'+CRLF+
'  public:'+CRLF+
'    typedef std::function<Type(Type, Type)> reducer;'+CRLF+
'  protected:'+CRLF+
'    vector<TScalar<Type> *> Data;'+CRLF+
'  public:'+CRLF+
'    TArray(int N, const char * __id__ = ""): TVar(__id__) {'+CRLF+
'       Data.resize(N);'+CRLF+
'       for (int i = 0; i < N; i++)'+CRLF+
'           Data[i] = new TScalar<Type>(id.c_str());'+CRLF+
'    }'+CRLF+
'    virtual void setReducer(reducer f) {'+CRLF+
'       for (auto d: Data)'+CRLF+
'           d->setReducer(f);'+CRLF+
'    }'+CRLF+
'    virtual ~TArray() {'+CRLF+
'       for (auto d: Data)'+CRLF+
'           delete d;'+CRLF+
'    }'+CRLF+
'    virtual void startTransaction() {'+CRLF+
'       // Все элементы стартуют самостоятельно как потомки TVar'+CRLF+
'    }'+CRLF+
'    Type * copy() {'+CRLF+
'       Type * res = new Type[Data.size()];'+CRLF+
'       int i = 0;'+CRLF+
'       for (auto d: Data) {'+CRLF+
'          res[i++] = *d;'+CRLF+
'       }'+CRLF+
'       return res;'+CRLF+
'    }'+CRLF+
'    TScalar<Type> & operator [] (const int index) {'+CRLF+
'      return *Data[index];'+CRLF+
'    }'+CRLF+
'    TArray<Type> & operator = (const Type & val) {'+CRLF+
'       for (auto d: Data) {'+CRLF+
'          *d = val;'+CRLF+
'       }'+CRLF+
'      return *this;'+CRLF+
'    }'+CRLF+
'    virtual void check(signed char * state) {'+CRLF+
'       // Все элементы проверяются самостоятельно как потомки TVar'+CRLF+
'    }'+CRLF+
'    virtual void commit(const vector<int> & _winners) {'+CRLF+
'       // Все элементы утверждаются самостоятельно как потомки TVar'+CRLF+
'    }'+CRLF+
'  };'+CRLF+
''+CRLF+
'template <class C>'+CRLF+
'class TObj : public TOBJ_STARTER, public C, public TOBJ_STOPPER {'+CRLF+
'// Часть методов наследуется от TOBJ_STARTER, см. выше'+CRLF+
'protected:'+CRLF+
'   thread * __thread__; // Дежурный поток'+CRLF+
'   volatile unsigned short __joined; // Число занятых потоков блока'+CRLF+
'   omp_lock_t __join_lock__;'+CRLF+
'   volatile bool __stopped; // Флаг, требующий завершения всех работ'+CRLF+
''+CRLF+
'   // Подкачка работ в блок'+CRLF+
'   virtual bool pump_jobs(__page_fun &f, __info_transaction__ * &parent_info, int &parent_id) {'+CRLF+
'	f = nullptr;'+CRLF+
'	parent_info = NULL;'+CRLF+
'	parent_id = 0;'+CRLF+
'	return false;'+CRLF+
'   }'+CRLF+
'private:'+CRLF+
'   // Исполняемая процедура дежурного потока'+CRLF+
'   void worker() {'+CRLF+
'        do {'+CRLF+
'			omp_set_lock(&__lock_atomics__);'+CRLF+
'			__info_transaction__ * info = get_transaction(__this_id);'+CRLF+
'			bool * working = info->working;'+CRLF+
'			omp_unset_lock(&__lock_atomics__);'+CRLF+
''+CRLF+
'			auto make_pump = [&]() {'+CRLF+
'				omp_set_lock(&__lock_atomics__);'+CRLF+
'				for (int i = __joined; i < __nthreads; i++) {'+CRLF+
'					if (pump_jobs(info->__funs[i], info->parents[i], info->parent_ids[i])) this->__joined++;'+CRLF+
'				}'+CRLF+
'				omp_unset_lock(&__lock_atomics__);'+CRLF+
'			};'+CRLF+
''+CRLF+
'           omp_set_lock(&__join_lock__);'+CRLF+
'           while (__joined == 0 && !__stopped) {'+CRLF+
'			 make_pump();'+CRLF+
'			 omp_unset_lock(&__join_lock__);'+CRLF+
'             _Yield();'+CRLF+
'             omp_set_lock(&__join_lock__);'+CRLF+
'           }'+CRLF+
'		   make_pump();'+CRLF+
'		   if (__joined != 0) {'+CRLF+
'			   int stored_joined = __joined;'+CRLF+
'			   omp_unset_lock(&__join_lock__);'+CRLF+
'			   #pragma omp parallel num_threads(stored_joined)'+CRLF+
'			   {'+CRLF+
'				   int id = omp_get_thread_num();'+CRLF+
'					transaction_atomic(__this_id) {'+CRLF+
'						omp_set_lock(&__join_lock__);'+CRLF+
'						omp_set_lock(&__lock_atomics__);'+CRLF+
'						if (info->__funs[id] != nullptr) {'+CRLF+
'							__page_fun f = info->__funs[id];'+CRLF+
'							omp_unset_lock(&__lock_atomics__);'+CRLF+
'							omp_unset_lock(&__join_lock__);'+CRLF+
'							f();'+CRLF+
'						}'+CRLF+
'						else {'+CRLF+
'							bool all_finished = true;'+CRLF+
'							for (int i = 0; i < stored_joined; i++)'+CRLF+
'								if (info->__funs[i] != nullptr && working[i])'+CRLF+
'									all_finished = false;'+CRLF+
'							omp_unset_lock(&__lock_atomics__);'+CRLF+
'							omp_unset_lock(&__join_lock__);'+CRLF+
'							if (!all_finished) fail();'+CRLF+
'						}'+CRLF+
'					}'+CRLF+
'			   }'+CRLF+
'             omp_set_lock(&__join_lock__);'+CRLF+
'			 omp_set_lock(&__lock_atomics__);'+CRLF+
'             for (int i = stored_joined; i < __nthreads; i++)'+CRLF+
'                 if (info->__funs[i] != nullptr) {'+CRLF+
'                    info->parents[i - stored_joined] = info->parents[i];'+CRLF+
'                    info->parent_ids[i - stored_joined] = info->parent_ids[i];'+CRLF+
'                    info->__funs[i - stored_joined] = info->__funs[i];'+CRLF+
'                    info->__funs[i] = nullptr;'+CRLF+
'                 }'+CRLF+
'             __joined -= stored_joined;'+CRLF+
'			 omp_unset_lock(&__lock_atomics__);'+CRLF+
'			 make_pump();'+CRLF+
'             omp_unset_lock(&__join_lock__);'+CRLF+
'           } else {'+CRLF+
'             omp_unset_lock(&__join_lock__);'+CRLF+
'             break;'+CRLF+
'           }'+CRLF+
'        } while (1);'+CRLF+
'   }'+CRLF+
'   // Создает запись о незавершенной работе с предусловиями preconds[npreconds], представляющими собой идентификаторы работ,'+CRLF+
'   // которые должны закончиться до текущей работы.'+CRLF+
'   // Возвращает идентификатор работы (больше или равен 1) или 0, если работа не создана'+CRLF+
'   // Для создания работ с уникальными идентификаторами и корректной работы режима ожидания необходим предварительный'+CRLF+
'   // вызов set_jobs_mode(true);'+CRLF+
'   int create_job(int npreconds, int * preconds) {'+CRLF+
'	int res = 0;'+CRLF+
'	omp_set_lock(&__lock_tobjs__);'+CRLF+
'	if (__use_jobs) {'+CRLF+
'		__tobj_job * job = new __tobj_job;'+CRLF+
'		job->finished = false;'+CRLF+
'		memset(job->preconds, 0, sizeof(job->preconds));'+CRLF+
'		if (preconds) {'+CRLF+
'			if (npreconds > 5) {'+CRLF+
'				cout << "Number of pre-conditions is greater than 5 !" << endl;'+CRLF+
'				exit(-800);'+CRLF+
'			}'+CRLF+
'			memmove(job->preconds, preconds, __min(5, npreconds)*sizeof(int));'+CRLF+
'		}'+CRLF+
'		if (__tobj_jobs.capacity() == __tobj_jobs.size())'+CRLF+
'			__tobj_jobs.reserve((unsigned int)(1.5*__tobj_jobs.capacity()));'+CRLF+
'		__tobj_jobs.push_back(job);'+CRLF+
'		res = __tobj_jobs.size();'+CRLF+
'        }'+CRLF+
'	omp_unset_lock(&__lock_tobjs__);'+CRLF+
'	return res;'+CRLF+
'   }'+CRLF+
'public:'+CRLF+
'   // Передается число требуемых рабочих потоков. Может равняться единице'+CRLF+
'   TObj<C>(int nthreads) : TOBJ_STARTER(nthreads), C(nthreads), TOBJ_STOPPER(nthreads) {'+CRLF+
'     // Создаем дежурный поток и ждем присоединений'+CRLF+
'     omp_init_lock(&__join_lock__);'+CRLF+
'	 __thread__ = NULL;'+CRLF+
'     reinit();'+CRLF+
'   }'+CRLF+
'   // Реинициализация'+CRLF+
'   virtual void reinit(bool sync_children = true) {'+CRLF+
'	   sync(sync_children);'+CRLF+
'	   __joined = 0;'+CRLF+
'	   __stopped = false;'+CRLF+
'	   delete __thread__;'+CRLF+
'	   __thread__ = new thread(&TObj<C>::worker, this);'+CRLF+
'   }'+CRLF+
'   virtual __page_fun handle_job(__page_fun f, int &id, int npreconds = 0, int * preconds = NULL) {'+CRLF+
'	   __info_transaction__ * tinfo = get_transaction(__this_id);'+CRLF+
'     if (__use_jobs) {'+CRLF+
'		 id = create_job(npreconds, preconds);'+CRLF+
'		 auto job = [id, npreconds, preconds, f, tinfo]() {'+CRLF+
'             omp_set_lock(&__lock_atomics__);'+CRLF+
'             tinfo->job_ids[omp_get_thread_num()] = id;'+CRLF+
'             omp_unset_lock(&__lock_atomics__);'+CRLF+
'             omp_set_lock(&__lock_tobjs__);'+CRLF+
'             __tobj_job * info = __tobj_jobs[id-1];'+CRLF+
'             if (info != NULL && preconds != NULL) {'+CRLF+
'                for (int i = 0; i < 5; i++)'+CRLF+
'                    if (info->preconds && info->preconds[i])'+CRLF+
'                       if ((unsigned int)info->preconds[i] <= __tobj_jobs.size()) {'+CRLF+
'                          volatile bool * fin = &__tobj_jobs[info->preconds[i]-1]->finished;'+CRLF+
'                          omp_unset_lock(&__lock_tobjs__);'+CRLF+
'                          if (!(*fin)) {'+CRLF+
'                             _Yield();'+CRLF+
'                             fail();'+CRLF+
'                             return;'+CRLF+
'                          }'+CRLF+
'                          omp_set_lock(&__lock_tobjs__);'+CRLF+
'                       } else {'+CRLF+
'                          cout << "Job[" << id << "] waits non-existing job[" << info->preconds[i] << "]" << endl;'+CRLF+
'                          exit(-600);'+CRLF+
'                       }'+CRLF+
'             }'+CRLF+
'             omp_unset_lock(&__lock_tobjs__);'+CRLF+
'             f();'+CRLF+
'        };'+CRLF+
'        return job;'+CRLF+
'     } else {'+CRLF+
'        id = 0;'+CRLF+
'        return f;'+CRLF+
'     }'+CRLF+
'   }'+CRLF+
'   // Помещает работу на выполнение и возвращает true. Если блок занят, то возвращает false'+CRLF+
'   virtual bool join(__page_fun f, int &id, int npreconds = 0, int * preconds = NULL, bool set_join_lock = true) {'+CRLF+
'     if (set_join_lock) omp_set_lock(&this->__join_lock__);'+CRLF+
'     if (__joined >= __nthreads) {'+CRLF+
'        omp_unset_lock(&__join_lock__);'+CRLF+
'        return false;'+CRLF+
'     }'+CRLF+
'     omp_set_lock(&__lock_atomics__);'+CRLF+
'     __info_transaction__ * tinfo = get_transaction(__this_id);'+CRLF+
'     string tr_id;'+CRLF+
'     tinfo->__funs[__joined] = this->handle_job(f, id, npreconds, preconds);'+CRLF+
'     tinfo->parents[__joined] = get_transaction_by_thread(tr_id, false);'+CRLF+
'     tinfo->parent_ids[__joined++] = omp_get_thread_num();'+CRLF+
'     omp_unset_lock(&__lock_atomics__);'+CRLF+
'     omp_unset_lock(&__join_lock__);'+CRLF+
'     return true;'+CRLF+
'   }'+CRLF+
'   // Ожидает полного завершения работ (своих, и, если sync_children, всех дочерних TObj-объектов)'+CRLF+
'   virtual void sync(bool sync_children = true) {'+CRLF+
'	 if (__thread__ == NULL) return;'+CRLF+
'     if (sync_children) {'+CRLF+
'        omp_set_lock(&__lock_atomics__);'+CRLF+
'        __info_transaction__ * info = get_transaction(__this_id);'+CRLF+
'        stack<TOBJ_STARTER *> objs;'+CRLF+
'        for (auto v : info->__atomics__) {'+CRLF+
'            TOBJ_STARTER * obj = dynamic_cast<TOBJ_STARTER *>(v);'+CRLF+
'            if (obj != NULL && obj != this)'+CRLF+
'               objs.push(obj);'+CRLF+
'        }'+CRLF+
'        omp_unset_lock(&__lock_atomics__);'+CRLF+
'        while (!objs.empty()) {'+CRLF+
'           TOBJ_STARTER * obj = objs.top();'+CRLF+
'           objs.pop();'+CRLF+
'           obj->sync(sync_children);'+CRLF+
'        }'+CRLF+
'     }'+CRLF+
'	 omp_set_lock(&__join_lock__);'+CRLF+
'	 __stopped = true;'+CRLF+
'	 omp_unset_lock(&__join_lock__);'+CRLF+
'	 // Уничтожаем дежурный поток'+CRLF+
'     if (__thread__->joinable()) __thread__->join();'+CRLF+
'   }'+CRLF+
'   // Возвращает число свободных потоков блока'+CRLF+
'   virtual int  num_free() {'+CRLF+
'     omp_set_lock(&__join_lock__);'+CRLF+
'     int res = __joined >= __nthreads ? 0 : (__nthreads - __joined);'+CRLF+
'     omp_unset_lock(&__join_lock__);'+CRLF+
'     return res;'+CRLF+
'   }'+CRLF+
'   virtual ~TObj<C>() {'+CRLF+
'     // Вызываем sync()'+CRLF+
'     sync();'+CRLF+
'     delete __thread__;'+CRLF+
'     omp_destroy_lock(&__join_lock__);'+CRLF+
'   }'+CRLF+
'};'+CRLF+
''+CRLF+
'template <class C>'+CRLF+
'class TQueuedObj : public TObj<C> {'+CRLF+
'protected:'+CRLF+
'   typedef struct {'+CRLF+
'      __page_fun f;'+CRLF+
'      __info_transaction__ * parent;'+CRLF+
'      int parent_id;'+CRLF+
'   } queue_item;'+CRLF+
'   queue<queue_item> Q;'+CRLF+
''+CRLF+
'   // Подкачка работ в блок'+CRLF+
'   virtual bool pump_jobs(__page_fun &f, __info_transaction__ * &parent_info, int &parent_id) {'+CRLF+
'	if (Q.empty()) return TObj<C>::pump_jobs(f, parent_info, parent_id);'+CRLF+
'	else {'+CRLF+
'		queue_item item = Q.front();'+CRLF+
'		Q.pop();'+CRLF+
'		f = item.f;'+CRLF+
'		parent_info = item.parent;'+CRLF+
'		parent_id = item.parent_id;'+CRLF+
'		return true;'+CRLF+
'	}'+CRLF+
'   }'+CRLF+
''+CRLF+
'public:'+CRLF+
'   // Передается число требуемых рабочих потоков. Может равняться единице'+CRLF+
'   TQueuedObj<C>(int nthreads) : TObj<C>(nthreads) {'+CRLF+
'   }'+CRLF+
'   // Реинициализация. Если блок работал, то сначала следует вызвать sync(), и только затем reinit()'+CRLF+
'   virtual void reinit(bool sync_children = true) {'+CRLF+
'     TObj<C>::reinit(sync_children);'+CRLF+
'     omp_set_lock(&this->__join_lock__);'+CRLF+
'     Q = queue<queue_item>();'+CRLF+
'     omp_unset_lock(&this->__join_lock__);'+CRLF+
'   }'+CRLF+
'   // Помещает работу в очередь или запускает, если есть свободный поток. Всегда возвращает true'+CRLF+
'   virtual bool join(__page_fun f, int &id, int npreconds = 0, int * preconds = NULL, bool set_join_lock = true) {'+CRLF+
'     if (set_join_lock) omp_set_lock(&this->__join_lock__);'+CRLF+
'	 if (Q.size() == 0) {'+CRLF+
'		 if (TObj<C>::join(f, id, npreconds, preconds, false)) return true;'+CRLF+
'		 omp_set_lock(&this->__join_lock__);'+CRLF+
'	 }'+CRLF+
'	 omp_set_lock(&__lock_atomics__);'+CRLF+
'	 __page_fun job = this->handle_job(f, id, npreconds, preconds);'+CRLF+
'     string tr_id;'+CRLF+
'     queue_item item = {'+CRLF+
'          job,'+CRLF+
'          get_transaction_by_thread(tr_id, false),'+CRLF+
'          omp_get_thread_num()'+CRLF+
'     };'+CRLF+
'     omp_unset_lock(&__lock_atomics__);'+CRLF+
'     Q.push(item);'+CRLF+
'     omp_unset_lock(&this->__join_lock__);'+CRLF+
'     return true;'+CRLF+
'   }'+CRLF+
'};'+CRLF+
''+CRLF+
'#endif'+CRLF;
