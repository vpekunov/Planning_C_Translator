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
const int N = 4*5000+2;
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
chain ThermalEquation(int NProcs, double Time)
{
 int stage = throw_stage();
 int NN = LastIdx[stage]-FirstIdx[stage]+1;

 static double Q1 = tau*D/hh;
 double * L = _L[stage];
 double * M = _M[stage];

 double LM[2];

 char buf[20];
 int i,j,k;

 string pLEFT = itoa(stage, buf, 10);
 string gLEFT = itoa(stage-1, buf, 10);
 string pRIGHT = itoa(stage, buf, 10);
 string gRIGHT = itoa(stage+1, buf, 10);

 pLEFT += itoa(stage-1, buf, 10);
 gLEFT += itoa(stage, buf, 10);
 pRIGHT += itoa(stage+1, buf, 10);
 gRIGHT += itoa(stage, buf, 10);

 funneled_predictor_out<double> * putLEFT  = stage > 0 ? new funneled_predictor_out<double>(pLEFT.c_str(), 1, 3, 1E-10) : NULL;
 funneled_predictor_in<double>  * getLEFT  = stage > 0 ? new funneled_predictor_in<double>(gLEFT.c_str(), 2, 3, 1E-10) : NULL;
 funneled_predictor_out<double> * putRIGHT = stage < NProcs - 1 ? new funneled_predictor_out<double>(pRIGHT.c_str(), 2, 3, 1E-10) : NULL;
 funneled_predictor_in<double>  * getRIGHT = stage < NProcs - 1 ? new funneled_predictor_in<double>(gRIGHT.c_str(), 1, 3, 1E-10) : NULL;

 while (Time < EndTime) {
    bool lpred = false;
    bool rpred = false;

    if (stage>0) {
       // getLEFT->get(LM, 2*sizeof(double));
       lpred = getLEFT->get_timed(LM, -1.0);
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

       putRIGHT->put(LM, 2*sizeof(double));
       // getRIGHT->get(&Therm[LastIdx[stage]], sizeof(double));
       rpred = getRIGHT->get_timed(&Therm[LastIdx[stage]], -1.0);
    } else
       Therm[LastIdx[stage]] = RightT;

    for (i=NN-1, j=LastIdx[stage], k=0; i>=1; i--, j--, k++)
        {
         Therm[j-1] = Therm[j]*L[i-1]+M[i-1];
        }
    if (stage > 0) putLEFT->put(&Therm[FirstIdx[stage]+1], sizeof(double));

    if (lpred) {
       getLEFT->get_and_correct(LM);
       Therm[FirstIdx[stage]] = Therm[FirstIdx[stage]+1]*LM[0] + LM[1];
    }
    if (rpred) {
       getRIGHT->get_and_correct(&Therm[LastIdx[stage]]);
    }

    Time+=tau;
 }

 delete putLEFT;
 delete getLEFT;
 delete putRIGHT;
 delete getRIGHT;
}

void IntegrateThermal(char NProcs)
{
 int NN = (N-2)/NProcs+2;
 int i;
 
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
 plan_parallel_chain(1,NProcs,ThermalEquation(NProcs,0.0)/1);
 cout<<(int)NProcs<<" procs. Time = "<<time()-T1<<" sec\n";
 for (i=0; i<NProcs; i++) {
     delete[] _L[i];
     delete[] _M[i];
 }
 #ifndef __THOROW__
 for (i=0; i<N; i++)
     cout<<Therm[i]<<" ";
 cout<<"\n";
 #endif
 delete[] Therm;
}

chain gThermalEquation(int NProcs, double Time, funnel(in,double) * outLEFT, funnel(out,double) * inLEFT)
{
 int stage = throw_stage();
 int NN = LastIdx[stage]-FirstIdx[stage]+1;

 static double Q1 = tau*D/hh;
 double * L = _L[stage];
 double * M = _M[stage];

 double Left_1, Left_0;
 int i,j,k;
 funnel(out,double) * putLEFT  = new funnel(out,double)(outLEFT);
 funnel(in,double)  * getLEFT  = new funnel(in,double)(inLEFT);
 funnel(out,double) * putRIGHT = new funnel(out,double)();
 funnel(in,double)  * getRIGHT = new funnel(in,double)();

 Time+=tau;
 if (stage==0 && Time<EndTime) plan_last(NProcs,Time,NULL,NULL);
 if (stage<NProcs-1) throw_last(NProcs,Time,getRIGHT,putRIGHT);
 L[0]=0;
 if (stage>0) {
    double Z1 = Q1;
    double Z2 = Q1;
    double Z3 = 1+2*Q1;

    *putLEFT = Therm[FirstIdx[stage]+1];
    Left_0 = **getLEFT;
    Left_1 = **getLEFT;
    M[0] = (Left_0+Z1*Left_1+Z2*Therm[FirstIdx[stage]+1])/Z3;
 } else
    M[0] = LeftT;

 for (i=1, j=FirstIdx[stage]+1; i<NN-1; i++, j++) {
   double Z1 = Q1;
   double Z2 = Q1;
   double Z3 = 1+2*Q1;
   double V  = Z3-Z1*L[i-1];

   L[i] = Z2/V;
   M[i] = (Therm[j]+Z1*M[i-1])/V;
 }
 if (stage<NProcs-1)
    Therm[LastIdx[stage]] = **getRIGHT;
 else
    Therm[LastIdx[stage]] = RightT;

 for (i=NN-1, j=LastIdx[stage], k=0; i>=1; i--, j--, k++)
     {
      Therm[j-1] = Therm[j]*L[i-1]+M[i-1];
      if (k<2 && stage<NProcs-1) *putRIGHT = Therm[j-1];
     }

 delete putLEFT;
 delete getLEFT;
 delete putRIGHT;
 delete getRIGHT;
}

void gIntegrateThermal(char NProcs)
{
 int NN = (N-2)/NProcs+2;
 int i;
 
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
 plan_parallel_chain(0,NProcs,gThermalEquation(NProcs,0.0,NULL,NULL)/1);
 cout<<(int)NProcs<<" procs. Time = "<<time()-T1<<" sec\n";
 for (i=0; i<NProcs; i++) {
     delete[] _L[i];
     delete[] _M[i];
 }
 #ifndef __THOROW__
 for (i=0; i<N; i++)
     cout<<Therm[i]<<" ";
 cout<<"\n";
 #endif
 delete[] Therm;
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
 #ifndef __THOROW__
 for (i=0; i<N; i++)
     cout<<Therm[i]<<" ";
 cout<<"\n";
 #endif
 delete[] Therm;
}

int main() {
 IntegrateThermal(plan_processors());

 gIntegrateThermal(plan_processors());

 SingleIntegrateThermal();

 return 0;
}
