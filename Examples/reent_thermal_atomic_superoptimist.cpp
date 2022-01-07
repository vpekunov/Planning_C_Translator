#include <iostream>

#include <string>

#include <stdlib.h>

#include <time.h>
#include <sys/timeb.h>

using namespace std;

#define __THOROW__

const int MAX_PROCS = 255;

const double tau = 0.025;
const double D   = 0.01;
const double h   = 0.1;
const double hh  = h*h;

const double LeftT  = 300.0;
const double RightT = 350.0;
const double InitT  = 273.0;

#ifdef __THOROW__
const int N = 4*9000+2;
#else
const int N = 4*12+2;
#endif

const double EndTime = tau*10000;

double time() {
#ifdef _MSC_VER
  struct _timeb timebuf;
  _ftime(&timebuf);
#else
  struct timeb timebuf;
  ftime(&timebuf);
#endif
  return (double) timebuf.time + (double) timebuf.millitm/1000;
}

double * Therm = NULL;
double * _L[MAX_PROCS] = {NULL};
double * _M[MAX_PROCS] = {NULL};

int FirstIdx[MAX_PROCS];
int LastIdx[MAX_PROCS];

char * itoa(int n, char * buf, int radix) {
 sprintf(buf, "%i", n);
 return buf;
}

TIn<double> * getLEFTS[MAX_PROCS] = { NULL };
TOut<double> * putLEFTS[MAX_PROCS] = { NULL };
TIn<double> * getRIGHTS[MAX_PROCS] = { NULL };
TOut<double> * putRIGHTS[MAX_PROCS] = { NULL };

reenterable IntegrateThermal(int NProcs, int state)
{
 int stage = plan_processor_id();

 static double Q1 = tau*D/hh;

 int NN = (N-2)/NProcs+2;

 double * L = _L[stage];
 double * M = _M[stage];

 double LM[2];

 char buf[20];
 int i,j;

 if (state == 0) {
    Therm = new double[N];
    for (i=0; i<N; i++)
        Therm[i] = InitT;
    FirstIdx[0] = 0;
    LastIdx[0]  = NN-1;
    for (i=0; i<NProcs; i++) {
        _L[i] = new double[NN];
        _M[i] = new double[NN];
    }
    for (i=1; i<NProcs; i++)
        LastIdx[i] = (FirstIdx[i] = LastIdx[i-1]-1)+NN-1;
    double T1 = time();

    double Time = 0.0;

    while (Time < EndTime) {
      for (i = 0; i < NProcs; i++)
          plan_last(NProcs, 1);
      plan_group_soft_atomize;

      for (i = 0; i < NProcs; i++)
          plan_last(NProcs, 2);
      plan_group_soft_atomize;

      Time+=tau;
    }

    for (i = 0; i < NProcs; i++) {
        delete putLEFTS[i];
        delete getLEFTS[i];
        delete putRIGHTS[i];
        delete getRIGHTS[i];
    }

    cout<<(int)NProcs<<" procs. Time = "<<time()-T1<<" sec\n";
    for (i=0; i<NProcs; i++) {
        delete[] _L[i];
        delete[] _M[i];
    }
    for (i=0; i<N; i++)
        cout<<Therm[i]<<" ";
    cout<<"\n";
    delete[] Therm;
 } else if (state == 1) {
    int NN = LastIdx[stage]-FirstIdx[stage]+1;

    if (putLEFTS[stage] == NULL && stage > 0) {
       string pLEFT = itoa(stage, buf, 10);
       pLEFT += itoa(stage-1, buf, 10);
       putLEFTS[stage]  = new TOut<double>(pLEFT.c_str(), 1, 3, 1E-10);
    }
    if (getLEFTS[stage] == NULL && stage > 0) {
       string gLEFT = itoa(stage-1, buf, 10);
       gLEFT += itoa(stage, buf, 10);
       getLEFTS[stage]  = new TIn<double>(gLEFT.c_str(), 2, 3, 1E-10);
    }
    if (putRIGHTS[stage] == NULL && stage < NProcs - 1) {
       string pRIGHT = itoa(stage, buf, 10);
       pRIGHT += itoa(stage+1, buf, 10);
       putRIGHTS[stage] = new TOut<double>(pRIGHT.c_str(), 2, 3, 1E-10);
    }
    if (getRIGHTS[stage] == NULL && stage < NProcs - 1) {
       string gRIGHT = itoa(stage+1, buf, 10);
       gRIGHT += itoa(stage, buf, 10);
       getRIGHTS[stage] = new TIn<double>(gRIGHT.c_str(), 1, 3, 1E-10);
    }

    if (stage>0) {
       getLEFTS[stage]->get(LM, 0.0);
       L[0] = LM[0];
       M[0] = LM[1];
    } else {
       L[0] = 0;
       M[0] = LeftT;
    }

    for (i=1, j=FirstIdx[stage]+1; i<NN-1; i++, j++) {
      double Z1 = Q1;
      double Z2 = Q1;
      double Z3 = 1+2*Q1;
      double V  = Z3-Z1*L[i-1];

      L[i] = Z2/V;
      M[i] = (Therm[j]+Z1*M[i-1])/V;
    }

    if (stage < NProcs-1) {
       double LM[2] = { L[NN-2], M[NN-2] };

       putRIGHTS[stage]->put(LM);
    }
 } else if (state == 2) {
    int NN = LastIdx[stage]-FirstIdx[stage]+1;

    if (stage < NProcs-1) {
       getRIGHTS[stage]->get(&Therm[LastIdx[stage]], 0.0);
    } else
       Therm[LastIdx[stage]] = RightT;

    for (i=NN-1, j=LastIdx[stage]; i>=1; i--, j--)
        {
         Therm[j-1] = Therm[j]*L[i-1]+M[i-1];
        }
    if (stage > 0) putLEFTS[stage]->put(&Therm[FirstIdx[stage]+1]);
 }
}

void SingleIntegrateThermal()
{
 static double Q1 = tau*D/hh;
 double * L = new double[N];
 double * M = new double[N];
 double Time;
 double T1;
 int i,j;

 Therm = new double[N];
 for (i=0; i<N; i++)
     Therm[i] = InitT;
 T1 = time();
 for (Time=0.0; Time<EndTime; Time+=tau) {
     L[0] = 0;
     M[0] = LeftT;

     for (i=1; i<N-1; i++) {
       double Z1 = Q1;
       double Z2 = Q1;
       double Z3 = 1+2*Q1;
       double V  = Z3-Z1*L[i-1];

       L[i] = Z2/V;
       M[i] = (Therm[i]+Z1*M[i-1])/V;
     }
     Therm[N-1] = RightT;

     for (i=N-1; i>=1; i--)
         Therm[i-1] = Therm[i]*L[i-1]+M[i-1];
 }
 cout<<"1 proc. Time = "<<time()-T1<<" sec\n";
 for (i=0; i<N; i++)
     cout<<Therm[i]<<" ";
 cout<<"\n";
 delete[] Therm;
}

int main() {
 IntegrateThermal(omp_get_num_procs(), 0);

 SingleIntegrateThermal();

 return 0;
}
