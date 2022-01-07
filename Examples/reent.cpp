// Reenterable reent.cpp reent1.cpp
// g++ -o reent reent1.cpp -fopenmp -fgnu-tm -fpermissive -std=c++0x -lm -lpthread -lOpenCL

// Для теста на многоядерной системе, дающего реальное ускорение, необходимо
// раскомментировать следующую строчку
// #define __THOROW__

// #define __MPI__

// Post-Build + Custom Build + Dummy file in project
// Rebuild recommended.

#include <iostream>

using namespace std;

#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/timeb.h>

#include <list>
#include <map>
#include <vector>

#ifdef _OPENMP
#include <omp.h>
#endif

#include <math.h>

#ifndef __min
#define __min(a,b) ((a)<(b) ? (a) : (b))
#endif
#ifndef __max
#define __max(a,b) ((a)>(b) ? (a) : (b))
#endif

int _time(time_t * Arg) {
  return time(Arg);
}

#ifdef __MPI__
#include "mpi.h"
double time() {
  return MPI_Wtime();
}
#else
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
#endif

using namespace std;

struct DataItem {
  protected:
    double Data[2000];
  public:
    double length() {
      double Result = 0.0;
      for (int i=0; i<sizeof(Data)/sizeof(Data[0]); i++)
          Result += Data[i]*Data[i];
      return Result;
    }
    double length() const {
      double Result = 0.0;
      for (int i=0; i<sizeof(Data)/sizeof(Data[0]); i++)
          Result += Data[i]*Data[i];
      return Result;
    }
    DataItem& operator += (const DataItem V2) {
      for (int i=0; i<sizeof(Data)/sizeof(Data[0]); i++)
          Data[i] += V2.Data[i];
      return *this;
    }
    bool operator < (DataItem &V2) {
      return length()<V2.length();
    }
    bool operator < (const DataItem &V2) const {
      return length()<V2.length();
    }
    bool operator > (DataItem &V2) {
      return length()>V2.length();
    }
    DataItem& operator = (const DataItem V2) {
      memmove(Data,V2.Data,sizeof(Data));
      return *this;
    }
    double operator () () {
      return length();
    }
    void setrand() {
      for (int i=0; i<sizeof(Data)/sizeof(Data[0]); i++)
        Data[i] = 1.0*rand()/RAND_MAX;
    }
    void fill(double filler) {
      for (int i=0; i<sizeof(Data)/sizeof(Data[0]); i++)
        Data[i] = filler;
    }
};

typedef struct TreeTag {
  DataItem Data;
  struct TreeTag * Left;
  struct TreeTag * Right;
  char Work;
} TreeNode;

markupdef struct TreeTag {
  DataItem Data;
  pre_id struct TreeTag * Left;
  pre_id struct TreeTag * Right;
  state(0,1)   char Work;
} TreeNode;

typedef struct _TreeTag {
  DataItem Data;
  vector<struct _TreeTag *> Childs;
  char Work;
} _TreeNode;

typedef struct NetTag {
  int Number;
  list<struct NetTag *> Outs;
} NetNode;

#ifdef __THOROW__
#define ARR_SIZE (1<<13)
#define _ARR_SIZE (ARR_SIZE/16)
#else
#define ARR_SIZE 32
#define _ARR_SIZE ARR_SIZE
#endif

TreeNode * Root;
_TreeNode * _Root;
DataItem A[ARR_SIZE];

reenterable Out(TreeNode * Cur, int Level); /* Прототип */

int CurLevel = 1;
reenterable Out(TreeNode * Cur, int Level)
{
 if (Level!=CurLevel)
    {
     CurLevel = Level;
     cout<<"\n";
    }
 cout<<Cur->Data()<<" ";
 if (Cur->Left)
    plan_last(Cur->Left,Level+1); /* Планируем вызов (не вызываем) эту процедуру */
 if (Cur->Right)
    plan_last(Cur->Right,Level+1); /* То же самое */
}

reenterable static global ParallelOut(TreeNode * Root, TreeNode * R, bool par) {
  if (Root) {
     if (par) {
        cout<<R->Data()<<" ";
     } else {
        if (R->Left) ParallelOut(Root, R->Left, false);
        if (R->Right) ParallelOut(Root, R->Right, false);
        plan_last(Root, R, true);
        if (R == Root) plan_group_parallelize;
        else plan_stop;
     }
  }
}

void _Out(TreeNode * Cur)
{
 list<TreeNode *> Queue = list<TreeNode *>();
 int LevelNodes = 1;
 int NextLevelNodes = 0;

 Queue.push_back(Cur);

 while (!Queue.empty())
   {
    Cur = Queue.front();
    Queue.pop_front();
    cout<<Cur->Data()<<" ";
    if (Cur->Left)
       {
        Queue.push_back(Cur->Left);
        NextLevelNodes++;
       }
    if (Cur->Right)
       {
        Queue.push_back(Cur->Right);
        NextLevelNodes++;
       }
    if (--LevelNodes==0)
       {
        cout<<"\n";
        LevelNodes = NextLevelNodes;
        NextLevelNodes = 0;
       }
   }
}

// chain[ARR_SIZE] FindMinMaxTree(id(NULL) TreeNode * Cur, char FindMin) if((!id->Left || id->Left->Work)&&(!id->Right || id->Right->Work) ) set(id->Work=1) reset(id->Work=0) depends(id->Left,id->Right);
chain[ARR_SIZE] FindMinMaxTree(id(NULL) struct TreeTag * Cur, char FindMin);

chain[ARR_SIZE] GenMinMaxTree(TreeNode * Cur, char FindMin)
{
 if (Cur==Root)
    plan_group_parallelize;
 throw_first(Cur,FindMin);
 if (Cur->Left)
    plan_last(Cur->Left,!FindMin);
 if (Cur->Right)
    plan_last(Cur->Right,!FindMin);
}

chain[ARR_SIZE] FindMinMaxTree(id(NULL) struct TreeTag * Cur, char FindMin)
{
 if (Cur==NULL)
    plan_group_parallelize;
 else if (Cur->Left && Cur->Right)
   if (FindMin) Cur->Data = __min(Cur->Left->Data,Cur->Right->Data);
   else Cur->Data = __max(Cur->Left->Data,Cur->Right->Data);
 else if (Cur->Left) Cur->Data = Cur->Left->Data;
 else if (Cur->Right) Cur->Data = Cur->Right->Data;
}

chain[ARR_SIZE] _GenMinMaxTree(_TreeNode * Cur, char FindMin)
{
 if (Cur==_Root) plan_group_parallelize;
 throw_first(Cur,FindMin);
 for (int i=0; i<Cur->Childs.size(); i++)
   if (Cur->Childs[i])
      plan_last(Cur->Childs[i],!FindMin);
}

chain[ARR_SIZE] _FindMinMaxTree(id(NULL) _TreeNode * Cur, char FindMin) if( [for (int i=0; i<id->Childs.size(); i++)] (!id->Childs[i] || id->Childs[i]->Work) ) set(id->Work=1) reset(id->Work=0) depends( [for (int i=0; i<id->Childs.size(); i++)] id->Childs[i])
{
 if (Cur==NULL) plan_group_parallelize;
 else if (Cur->Childs.size()>0) {
   Cur->Data = Cur->Childs[0]->Data;
   for (int i=1; i<Cur->Childs.size(); i++)
     if (FindMin) {
        if (Cur->Data>Cur->Childs[i]->Data) Cur->Data = Cur->Childs[i]->Data;
     } else
        if (Cur->Data<Cur->Childs[i]->Data) Cur->Data = Cur->Childs[i]->Data;
 }
}

const int nHisto = 10;

int Histo[nHisto] = {0};

reenterable FindHisto(TreeNode * Cur, double Min, double Max, bool calc) {
  if (!calc) {
     if (Cur == Root) plan_group_first;
     if (Cur->Left) {
        plan_first(Cur->Left, Min, Max, false);
     }
     if (Cur->Right) {
        plan_first(Cur->Right, Min, Max, false);
     }
     plan_last(Cur, Min, Max, true);
  } else {
     plan_group_atomize;
     int n = nHisto*(Cur->Data()-Min)/(Max-Min);
     if (n == nHisto) n--;
     Histo[n]++;
  }
}

chain FindHistoStage0(TreeNode * Cur, double Min, double Max) throw(TreeNode * Cur, double Min, double Max) {
  if (Cur == Root) plan_group_parallelize;
  throw_last(Cur, Min, Max);
  if (Cur->Left) {
     plan_last(Cur->Left, Min, Max);
  }
  if (Cur->Right) {
     plan_last(Cur->Right, Min, Max);
  }
}

chain FindHistoStage1(TreeNode * Cur, double Min, double Max) {
  if (Cur == Root) plan_group_atomize;
  int n = nHisto*(Cur->Data()-Min)/(Max-Min);
  if (n == nHisto) n--;
  Histo[n]++;
}

#if _OPENMP>=200805
void _omp3_FindMinMaxTree(TreeNode * Cur, char FindMin) {
  if (Cur->Left)
     #pragma omp task untied
     _omp3_FindMinMaxTree(Cur->Left,!FindMin);
  if (Cur->Right)
     #pragma omp task untied
     _omp3_FindMinMaxTree(Cur->Right,!FindMin);
  #pragma omp taskwait
  if (Cur->Left && Cur->Right)
     if (FindMin) Cur->Data = __min(Cur->Left->Data,Cur->Right->Data);
     else Cur->Data = __max(Cur->Left->Data,Cur->Right->Data);
  else if (Cur->Left) Cur->Data = Cur->Left->Data;
  else if (Cur->Right) Cur->Data = Cur->Right->Data;
}
void omp3_FindMinMaxTree(TreeNode * Root, char FindMin) {
  #pragma omp parallel
  {
   #pragma omp single
   {
    _omp3_FindMinMaxTree(Root,FindMin);
   }
  }
}
#endif

reenterable EnumerateByFamilies(TreeNode * Cur, char Level, int &Number)
{
 Cur->Data.fill(sqrt((Number++)/2000.0));
 if (Level)
    {
     if (Cur->Left) plan_last(Cur->Left,0,Number);
     if (Cur->Right) plan_last(Cur->Right,0,Number);
    }
 else
    {
     if (Cur->Right) plan_first(Cur->Right,1,Number);
     if (Cur->Left) plan_first(Cur->Left,1,Number);
    }
}

chain RevEnumerateStage0(TreeNode * Cur) throw(TreeNode * Cur, int &Number)
{
 if (Cur->Right) plan_last(Cur->Right);
 if (Cur->Left) plan_last(Cur->Left);
 throw_first(Cur,1); // можно и plan+признак(без перепланирования)
}

chain RevEnumerateStage1(TreeNode * Cur, int &Number)
{
 Cur->Data.fill(sqrt((Number++)/2000.0));
}

NetNode * NetRoot;
map<NetTag *,int> Markers;
map<NetTag *,int> NInps;

reenterable FindSubSystem(NetNode * Cur)
{
 list<NetNode *>::iterator OutCounter = Cur->Outs.begin();

 cout<<Cur->Number<<" ";
 if (plan_empty && (Cur->Outs.size()==0 || Cur->Outs.size()==1 && NInps[Cur->Outs.front()]==1))
    cout<<"\n";
 for (int i=0; i<Cur->Outs.size(); i++,OutCounter++)
     {
      Markers[*OutCounter]--;
      if (Markers[*OutCounter]==0)
         plan_last(*OutCounter);
     }
}

reenterable static local WalkTree(TreeNode * Cur)
{
 if (Cur->Left) WalkTree(Cur->Left)/1; // recursion!!! nested parallelizing
 cout<<Cur->Data()<<".";
 if (Cur->Right) plan_first(Cur->Right);
}

enum {entryWT, yieldWT, anyWT};
reenterable static local WalkTreeGen(TreeNode * Cur, char Point, TreeNode * &Out)
{
 switch (Point) {
   case entryWT:
     if (Cur->Left)
        {
         if (Out) continue WalkTreeGen(Cur->Left,entryWT,Out)/1;
         else WalkTreeGen(Cur->Left,entryWT,Out)/1;
         if (Out)
            {
             plan_first(Cur,entryWT,Cur!);
             plan_stop;
             return;
            }
        }
     Out = Cur;
     plan_first(Cur,yieldWT,NULL!);
     plan_stop;
     return;
   case yieldWT:
     if (Cur->Right)
        {
         if (Out) continue WalkTreeGen(Cur->Right,entryWT,Out)/1;
         else WalkTreeGen(Cur->Right,entryWT,Out)/1;
         if (Out) plan_first(Cur,yieldWT,Out!);
         plan_stop;
        }
 }
}

reenterable static local WalkTreeGen1(TreeNode * Cur, char Point, TreeNode * &Out)
{
 switch (Point) {
   case entryWT:
     if (Cur->Left)
        {
         if (Out) continue WalkTreeGen1(Cur->Left,entryWT,Out)/1;
         else WalkTreeGen1(Cur->Left,entryWT,Out)/1;
         if (Out)
            {
             plan_first(Cur,entryWT,Cur!);
             plan_stop;
             return;
            }
        }
     Out = Cur;
     plan_first(Cur,yieldWT,NULL!);
     plan_stop;
     return;
   case yieldWT:
     if (Cur->Right)
         plan_first(Cur->Right,entryWT,NULL!);
 }
}

reenterable[ARR_SIZE] PutTree(TreeNode ** Cur,TreeNode * Ins)
{
 if (*Cur)
    if (Ins->Data<(*Cur)->Data)
      plan_first(&((*Cur)->Left),Ins);
    else
      plan_first(&((*Cur)->Right),Ins);
 else
    *Cur = Ins;
}

void RecursivePutTree(TreeNode ** Cur,TreeNode * Ins)
{
 if (*Cur)
    if (Ins->Data<(*Cur)->Data)
      RecursivePutTree(&((*Cur)->Left),Ins);
    else
      RecursivePutTree(&((*Cur)->Right),Ins);
 else
    *Cur = Ins;
}

reenterable static global stack(int &Item)
{
 if (!plan_after_continue()) plan_first(Item);
 plan_stop;
}

reenterable static queue(int &Item)
{
 if (!plan_after_continue()) plan_last(Item);
 plan_stop;
}

reenterable static Fib(int First, int Last, int &Item)
{
 if (plan_after_continue()) {
    Item = First+Last;
    plan_first(Last,Item,0);
 }
 else
    {
     plan_first(0,1,0);
     Item = 1;
    }
 plan_stop;
}

reenterable[ARR_SIZE] void Sum(int Start, int Incr)
{
 int Next = Start+2*Incr;
 if (Next<ARR_SIZE) plan_first(Next,Incr);
 if (Start==0)
    {
     /* Проиллюстрируем применение синтаксиса по типу OpenMP */
     #pragma omp plan parallelize
    }
 A[Start]+=A[Start+Incr];
 if (Next>=ARR_SIZE) {
    #pragma omp plan last /* Чтобы избежать суммирования дважды в одну ячейку */
    if (Incr<ARR_SIZE/2) plan_last(0,Incr*2);
 }
}

void qsort_incr(DataItem * a, int Left, int Right, int incr)
{
 DataItem p,buf;
 int i,j;
 i=Left;
 j=Right;
 p=a[(int)((Left+Right)/incr)/2*incr];
 do {
   while (a[i]<p) i+=incr;
   while (p<a[j]) j-=incr;
   if (i<=j)
      {
       buf=a[i]; a[i]=a[j]; a[j]=buf;
       i+=incr; j-=incr;
      }
 } while (i<=j);
 if (Left<j) qsort_incr(a,Left,j,incr);
 if (i<Right) qsort_incr(a,i,Right,incr);
}

#define MAX_PROCS 256

DataItem * SortedArray;
int Lefts[MAX_PROCS];
int Rights[MAX_PROCS];
chain chain_qsort_incr(int nProcs, DataItem * a, int N, int incr)
{
 int stage    = throw_stage();
 int NN       = (N-1)/incr+1;
 int PerStage = NN/nProcs;

 Lefts[stage]  = stage*PerStage*incr;
 Rights[stage] = (stage==nProcs-1) ? N-((N-1)%incr)-1 : (stage+1)*PerStage*incr-incr;
 qsort_incr(a,Lefts[stage],Rights[stage],incr);
}

int compare_items( const void *arg1, const void *arg2 ) {
 return SortedArray[Lefts[*(int *)arg1]]<SortedArray[Lefts[*(int *)arg2]] ? -1 : SortedArray[Lefts[*(int *)arg2]]<SortedArray[Lefts[*(int *)arg1]] ? +1 : 0;
}

void MergeSort(char nProcs, DataItem * Arr, int N, int incr)
{
 plan_parallel_chain(1,nProcs,chain_qsort_incr(nProcs,Arr,N,incr));
 if (nProcs>1) {
    DataItem * Buf = new DataItem[N/incr+1];
    int Idxs[MAX_PROCS];
    int actNP = nProcs;
    SortedArray = Arr;
    for (int i=0; i<nProcs; i++)
        Idxs[i] = i;
    qsort(Idxs,nProcs,sizeof(int),compare_items);
    for (int i=0, j=0; i<N; i+=incr, j++)
        {
         int Idx = Idxs[0];
         Buf[j] = Arr[Lefts[Idx]];
         if ((Lefts[Idx]+=incr)>Rights[Idx])
            memmove(&Idxs[0],&Idxs[1],--actNP*sizeof(int));
         else
            {
             DataItem buf = Arr[Lefts[Idx]];
             int j;
             for (j=1; j<actNP; j++)
                 if (Arr[Lefts[Idxs[j]]]<buf) Idxs[j-1] = Idxs[j];
                 else break;
             if (j>1) Idxs[j-1] = Idx;
            }
        }
    for (int i=0, j=0; i<N; i+=incr, j++)
        Arr[i] = Buf[j];
    delete[] Buf;
 }
}

reenterable[ARR_SIZE] _ShellSort(char UseMergeSort, char Plan, DataItem * Arr, int N, int incr)
{
 static int Incr[100] = {1};
 int i,j;

 plan_group_parallelize;
 if (Plan)
    {
     for (i=0; Incr[i]<N; Incr[i+1] = 3*Incr[i]+1, i++);
     while (--i>=UseMergeSort)
       {
        int NLists = N%Incr[i] ? N%Incr[i] : Incr[i];
        DataItem * B = Arr;
        int NB  = N;

        plan_group_last;
        for (j=0; j<NLists; j++)
            plan_last(UseMergeSort,0,B++,NB--,Incr[i]);
       }
    }
 else
    qsort_incr(Arr,0,N-((N-1)%incr)-1,incr);
}

void ShellSort(char UseMergeSort, char nProcs, DataItem * Arr, int N)
{
 _ShellSort(UseMergeSort,1,Arr,N,0)/nProcs;
 if (UseMergeSort) MergeSort(nProcs,Arr,N,1);
}

const double Eps = 0.001;

double f(int i)
{
 return exp(1.0/i)*cos(3.1415926535897932/i);
}

double g(int i)
{
 return 1.0/i;
}

double Sums[256] = {0};
reenterable int _SumF(int i)
{
 if (i==1) plan_group_parallelize;
 if (g(i)>Eps)
    {
     plan_last(i+1);
     Sums[plan_processor_id()]+=f(i);
    }
 return 1;
}
double SumF(int NP)
{
 double Result = 0.0;
 memset(Sums,0,sizeof(Sums));
 cout<<(_SumF(1)/NP ? "\nReenterable function works\n" : "Reenterable function does not work");
 for (int i=0; i<NP; i++)
     Result += Sums[i];
 return Result;
}
#if _OPENMP>=200805
double omp3_SumF(int NP)
{
 double Result = 0.0;
 memset(Sums,0,sizeof(Sums));
 #pragma omp parallel num_threads(NP)
 {
 #pragma omp single
   {
    for (int i=1; g(i)>Eps; i++)
      #pragma omp task untied
      Sums[omp_get_thread_num()]+=f(i);
    #pragma omp taskwait
   }
 }
 for (int i=0; i<NP; i++)
     Result += Sums[i];
 return Result;
}
#endif

/*
DataItem SumResult[MAX_PROCS];
reenterable[ARR_SIZE] _TreeSum(TreeNode * Cur)
{
 if (Cur==Root) plan_group_parallelize;
 if (Cur->Left) plan_last(Cur->Left);
 if (Cur->Right) plan_last(Cur->Right);
 SumResult[plan_processor_id()]+=Cur->Data;
}
DataItem * TreeSum(int NP)
{
 static DataItem Result;
 int i;
 Result.fill(0.0);
 memset(SumResult,0,sizeof(SumResult));
 _TreeSum(Root)/NP;
 for (i=0; i<NP; i++)
     Result+=SumResult[i];
 return &Result;
}
*/

reenterable[ARR_SIZE] TreeSum(TreeNode * Cur, reduction(+) DataItem & SumResult)
{
 if (Cur==Root) plan_group_parallelize;
 if (Cur->Left) plan_last(Cur->Left,SumResult);
 if (Cur->Right) plan_last(Cur->Right,SumResult);
 SumResult = Cur->Data;
}

reenterable _rTreeMax(TreeNode * Cur, reduction(__max) DataItem &Max) {
 if (Cur==Root) plan_group_parallelize;
 if (Cur->Left) plan_last(Cur->Left,Max);
 if (Cur->Right) plan_last(Cur->Right,Max);
    Max = Cur->Data;
}
double rTreeMax(TreeNode * Root) {
 DataItem R;
 R.fill(0.0);
 _rTreeMax(Root,R);
 return R();
}

#if _OPENMP>=200805
double _omp3_TreeMax(TreeNode * Cur) {
  double L = -1E300;
  double R = -1E300;
  double C = Cur->Data();
  if (Cur->Left)
     #pragma omp task shared(L) untied
     L = _omp3_TreeMax(Cur->Left);
  if (Cur->Right)
     #pragma omp task shared(R) untied
     R = _omp3_TreeMax(Cur->Right);
  #pragma omp taskwait
  return __max(C,__max(L,R));
}
double omp3_TreeMax(TreeNode * Root) {
  double Result;
  #pragma omp parallel
  {
   #pragma omp single
   Result = _omp3_TreeMax(Root);
  }
  return Result;
}
#endif

chain[ARR_SIZE] TreeMax(TreeNode * Cur, reduction(__max) DataItem & MaxResult)
{
 static DataItem DummyMin;

 throw_last(Cur,DummyMin);
 if (Cur==Root) plan_group_parallelize;
 if (Cur->Left) plan_last(Cur->Left,MaxResult);
 if (Cur->Right) plan_last(Cur->Right,MaxResult);
 MaxResult = Cur->Data;
}

chain[ARR_SIZE] TreeMin(TreeNode * Cur, reduction(__min) DataItem & MinResult)
{
 if (Cur==Root) plan_group_parallelize;
 MinResult = Cur->Data;
}

DataItem * TreeMinMax(int PerStageNP, DataItem & Min)
{
 static DataItem Max;

 Max.fill(0.0);
 Min.fill(1000.0);
 
 if (PerStageNP)
    plan_parallel_chain(0,TreeMax(Root,Max)/PerStageNP,TreeMin(Root,Min)/PerStageNP);
 else
    plan_chain(0,TreeMax(Root,Max)/1,TreeMin(Root,Min)/1);
 return &Max;
}

// фильтрация изображения, векторные операции???

#ifdef _OPENMP
const double tau = 0.1;
const double D   = 0.001;
const double h   = 0.1;
const double hh  = h*h;

const double LeftT  = 300.0;
const double RightT = 350.0;
const double InitT  = 273.0;

#ifdef __THOROW__
const int N = 4*100000+2;
#else
const int N = 4*12+2;
#endif

const double EndTime = tau*1000;

double * Therm = NULL;
double * _L[MAX_PROCS] = {NULL};
double * _M[MAX_PROCS] = {NULL};

int FirstIdx[MAX_PROCS];
int LastIdx[MAX_PROCS];
chain ThermalEquation(int NProcs, double Time, funnel(in,double) * outLEFT, funnel(out,double) * inLEFT)
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
 plan_parallel_chain(0,NProcs,ThermalEquation(NProcs,0.0,NULL,NULL)/1);
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

void SingleIntegrateThermal(char NProcs)
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
 delete[] Therm;
}
#endif

#define VEC_SIZE 2

chain Stage0(int N, double * V1, double * V2, double * V3, double * R) throw(double * V1, double MUL, double * R) {
 for (int i=0; i<N; i++, V1+=VEC_SIZE, R+=VEC_SIZE) {
    double MUL = 0.0;
    for (int j=0; j<VEC_SIZE; j++)
        MUL += (*V2++)*(*V3++);
    throw_last(V1,MUL,R);
   }
}

chain Stage1(double * V1, double MUL, double * R) {
 for (int j=0; j<VEC_SIZE; j++)
     R[j] = V1[j]+MUL;
}

chain Div(double * V1, double * V2)
{
 int N = throw_stage();

 V1[N] /= V2[N];
}

const int NL = 10; /* Размер лабиринта */
const unsigned char W = 0xFF; /* Стенка */
/* Лабиринт */
unsigned char Labirint[NL][NL] =
{
 {W,W,W,W,W,W,W,W,W,W},
 {W,0,0,0,0,0,0,0,0,W},
 {W,0,W,W,0,0,W,0,0,W},
 {W,0,0,W,0,0,W,0,0,W},
 {W,0,0,W,W,0,W,0,0,W},
 {W,0,0,0,W,W,W,0,0,W},
 {W,0,0,0,0,0,0,0,0,W},
 {W,0,0,0,0,0,0,0,0,W},
 {W,0,0,0,0,0,0,0,0,W},
 {W,W,W,W,W,W,W,W,W,W},
};
/* Приращения для сдвига относительно текущей клетки влево, вверх, вниз, вправо */
signed char OffsX[4] = {-1,0,0,+1};
signed char OffsY[4] = {0,-1,+1,0};

const char FirstX = 8; /* Точка отправления */
const char FirstY = 8;
const char LastX  = 5; /* Точка назначения */
const char LastY  = 4;

chain[NL*NL] FindLi(unsigned char X, unsigned char Y, int Num) throw(unsigned char X, unsigned char Y)
{
 char Found = 0;

 for (int i=0; !Found && i<4; i++) { /* Просматриваем клетки рядом */
   unsigned char X1 = X+OffsX[i];
   unsigned char Y1 = Y+OffsY[i];
   if (X1>=0 && X1<NL && Y1>=0 && Y1<NL && Labirint[Y1][X1]==0) {
      /* Если клетка еще не пронумерована */
      Labirint[Y1][X1] = Num; /* Нумеруем */
      if (X1==LastX && Y1==LastY) /* Если последняя */
         Found = 1; /* Сигнализируем окончание */
      else /* Если не последняя */
         plan_last(X1,Y1,Num+1); /* Помещаем в очередь */
   }
 }

 if (Found) {
    clear_plan; /* Очищаем план просмотра клеток */
    X = LastX; Y = LastY;
    throw_last(X,Y); /* Помещаем в "стек" точку назначения (последнюю) */
    while (X!=FirstX || Y!=FirstY) { /* Пока не дошли до точки отправления */
      char PointFound = 0; /* Поиск следующей клетки пути */
      for (int i=0; !PointFound && i<4; i++) {
        unsigned char X1 = X+OffsX[i];
        unsigned char Y1 = Y+OffsY[i]; /* Кандидат на следующую клетку пути */
        if (X1>=0 && X1<NL && Y1>=0 && Y1<NL && Labirint[Y1][X1] &&
            Labirint[Y1][X1]<Labirint[Y][X]) {
            /* Если клетка не пуста и имеет меньший номер */
            /* У клеток стенок самые большие номера, в рассмотрение не попадают */
           PointFound = 1;
           throw_first(X1,Y1); /* Добавляем в путь (стек) найденную клетку */
           X = X1; Y = Y1; /* На следующем шаге будем исходить из этой клетки */
        }
      }
    }
 } else if (plan_empty)
    cout<<"NO PATH\n"; /* Не дошли до места назначения */
}

chain[NL*2] OutLi(unsigned char X, unsigned char Y) {
  cout<<"("<<(int)Y<<","<<(int)X<<") ";
}

void CopyTree(TreeNode * Cur, _TreeNode * &Dest) {
  if (Cur) {
     Dest = new _TreeNode;
     Dest->Data = Cur->Data;
     Dest->Childs = vector<struct _TreeTag *>(0);
     Dest->Work = 0;
     if (Cur->Left) {
        Dest->Childs.resize(1,NULL);
        CopyTree(Cur->Left,Dest->Childs[0]);
     }
     if (Cur->Right) {
        Dest->Childs.resize(Dest->Childs.size()+1,NULL);
        CopyTree(Cur->Right,Dest->Childs[Dest->Childs.size()-1]);
     }
  }
}

int main(int argc, char ** argv)
{
 TreeNode * CurNode;
 DataItem Max, Min;
 int i,j;
 DataItem RSUM;
 DataItem * Asave;
 int Number;
 int Q;
 double T1;

 RSUM.fill(0.0);

 #ifdef __MPI__
 MPI_Init(&argc,&argv);
 #endif
 srand(_time(NULL));

 for (i=0; i<ARR_SIZE; i++)
     A[i].setrand();
 #ifndef __THOROW__
 for (i=0; i<ARR_SIZE; i++)
     cout<<A[i]()<<".";
 cout<<"\n";
 #endif

 Asave = new DataItem[ARR_SIZE];
 memmove(Asave,A,sizeof(A));
 ShellSort(0,1,A,ARR_SIZE);
 for (j=0; j<=1; j++)
   for (i=1; i<=8; i++)
       {
        memmove(A,Asave,sizeof(A));
        T1 = time();
        ShellSort(j,i,A,ARR_SIZE);
        cout<<i<<" procs, "<<(j==0 ? "no merge" : "with merge")<<". Parallel Shell Time = "<<time()-T1<<" sec\n";
       }
 #ifndef __THOROW__
 cout<<"\nSHELLSORT:\n";
 for (i=0; i<ARR_SIZE; i++)
     cout<<A[i]()<<".";
 cout<<"\n";
 #endif
 memmove(A,Asave,sizeof(A));
 MergeSort(1,A,_ARR_SIZE,1);
 for (i=1; i<=8; i++)
     {
      memmove(A,Asave,sizeof(A));
      T1 = time();
      MergeSort(i,A,_ARR_SIZE,1);
      cout<<i<<" items/stages. Chain MergeSort Time = "<<time()-T1<<" sec\n";
     }
 #ifndef __THOROW__
 cout<<"MERGESORT:\n";
 for (i=0; i<_ARR_SIZE; i++)
     cout<<A[i]()<<".";
 cout<<"\n";
 #endif
 for (i=0; i<ARR_SIZE; i++)
     {
      if (i==0)
         CurNode = Root = new TreeNode;
      else
         CurNode = new TreeNode;
      CurNode->Data  = Asave[i];
      CurNode->Work  = 0;
      CurNode->Left  = NULL;
      CurNode->Right = NULL;

      if (i>0)
      #ifdef __THOROW__
         RecursivePutTree(&Root,CurNode);
      #else
         PutTree(&Root,CurNode);
      #endif
     }
 #ifndef __THOROW__
 cout<<"SORTED:\n";
 WalkTree(Root);
 cout<<"\nSORTED GEN:\n";
 CurNode = NULL;
 WalkTreeGen(Root,entryWT,CurNode); cout<<CurNode->Data()<<".";
 do {
   continue WalkTreeGen(Root,anyWT,CurNode);
   if (CurNode) cout<<CurNode->Data()<<".";
 } while (CurNode);
 cout<<"\nSORTED GEN 1:\n";
 CurNode = NULL;
 WalkTreeGen1(Root,entryWT,CurNode); cout<<CurNode->Data()<<".";
 do {
   continue WalkTreeGen1(Root,anyWT,CurNode);
   if (CurNode) cout<<CurNode->Data()<<".";
 } while (CurNode);
 cout<<"\nOUT:\n";
 Out(Root,1);
 cout<<"\n_OUT:\n";
 _Out(Root);
 #endif
 Sum(0,1)/1;
 memmove(A,Asave,sizeof(A));
 for (i=1; i<=8; i++)
     {
      T1 = time();
      Sum(0,1)/i;
      RSUM = A[0];
      memmove(A,Asave,sizeof(A));
      cout<<i<<" procs. CascadeSum Time = "<<time()-T1<<" sec\n";
     }
 cout<<"SUM="<<RSUM()<<"\n";
 RSUM.fill(0.0);
 TreeSum(Root,RSUM)/8;
 for (i=8; i>=1; i--)
     {
      RSUM.fill(0.0);
      T1 = time();
      TreeSum(Root,RSUM)/i;
      cout<<i<<" procs. TreeWalkSum="<<RSUM()<<" Time = "<<time()-T1<<" sec\n";
     }
 cout<<"TREE SUM="<<RSUM()<<"\n";

 double _MIN = 1E300;
 double _MAX = -1E300;
 for (i=0; i<ARR_SIZE; i++)
     {
      double T = Asave[i]();
      if (T < _MIN) _MIN = T;
      if (T > _MAX) _MAX = T;
     }

 cout<<"SEQUENTIAL: TREE MIN = "<<_MIN<<" : TREE MAX = "<<_MAX<<endl<<endl;

 T1 = time();
 FindHisto(Root, _MIN, _MAX, false)/8;
 T1 = time() - T1;
 cout<<"\nHISTO PARALLEL at 8 procs (ATOMIC) = ";
 for (int i = 0; i < nHisto; i++)
     cout<<Histo[i]<<" ";
 cout<<" at the time "<<T1<<" sec"<<endl;

 memset(Histo, 0, sizeof(Histo));
 T1 = time();
 FindHisto(Root, _MIN, _MAX, false)/1;
 T1 = time() - T1;
 cout<<"\nHISTO PARALLEL at 1 procs (ATOMIC) = ";
 for (int i = 0; i < nHisto; i++)
     cout<<Histo[i]<<" ";
 cout<<" at the time "<<T1<<" sec"<<endl;

 memset(Histo, 0, sizeof(Histo));
 T1 = time();
 plan_parallel_chain(0, FindHistoStage0(Root, _MIN, _MAX)/4, FindHistoStage1(Root, _MIN, _MAX)/8);
 T1 = time() - T1;
 cout<<"\nHISTO CONVEYOR at 4+8 procs (ATOMIC) = ";
 for (int i = 0; i < nHisto; i++)
     cout<<Histo[i]<<" ";
 cout<<" at the time "<<T1<<" sec"<<endl;

 int Histo1[nHisto] = {0};
 T1 = time();
 for (i=0; i<ARR_SIZE; i++)
     {
      double T = Asave[i]();
      int n = nHisto*(T - _MIN)/(_MAX - _MIN);
      if (n == nHisto) n--;
      Histo1[n]++;
     }
 T1 = time() - T1;
 cout<<"\nHISTO SEQUENTIAL = ";
 for (int i = 0; i < nHisto; i++)
     cout<<Histo1[i]<<" ";
 cout<<" at the time "<<T1<<" sec"<<endl;

 cout<<"Max in Tree = "<<rTreeMax(Root)<<"\n";
 #if _OPENMP>=200805
 cout<<"OpenMP 3.0: Max in Tree = "<<omp3_TreeMax(Root)<<"\n";
 #endif

 Max.fill(0.0);
// TreeMax(Root,Max)/8;
// cout<<"MAX="<<Max()<<"\n";
 for (i=4; i>=0; i--)
     {
      T1 = time();
      Max = *TreeMinMax(i,Min);
      cout<<i*2+(i==0)<<" procs. Conveyer MinMax Time = "<<time()-T1<<" sec\n";
     }
 cout<<"\nCONVEYER MAX="<<Max()<<" MIN="<<Min()<<"\n";

 Number = 1;
 EnumerateByFamilies(Root,0,Number);
 CurLevel = 1;
 cout<<"\nENUM 3-FAMILIES:\n";
 #ifndef __THOROW__
 Out(Root,1);
 #endif
 Number = 1;
 plan_chain(0,RevEnumerateStage0(Root)/5,RevEnumerateStage1(Root,Number));
 cout<<"\nENUM LIN REV:";
 #ifndef __THOROW__
 Out(Root,1);
 #endif
 
 NetRoot = new NetNode;
 Markers[NetRoot] = 0;
 NetRoot->Number = 0;
 NetNode * CC1 = new NetNode;
 CC1->Number = 1;
 Markers[CC1] = 0;
 NetRoot->Outs.push_back(CC1); Markers[CC1]++;
 NetNode * CC2 = new NetNode;
 CC2->Number = 2;
 Markers[CC2] = 0;
 NetRoot->Outs.push_back(CC2); Markers[CC2]++;
 NetNode * CC3 = new NetNode;
 CC3->Number = 3;
 Markers[CC3] = 0;
 CC1->Outs.push_back(CC2); Markers[CC2]++;
 CC1->Outs.push_back(CC3); Markers[CC3]++;
 NetNode * CC4 = new NetNode;
 CC4->Number = 4;
 Markers[CC4] = 0;
 CC2->Outs.push_back(CC4); Markers[CC4]++;
 CC3->Outs.push_back(CC4); Markers[CC4]++;
 NetNode * CC5 = new NetNode;
 CC5->Number = 5;
 Markers[CC5] = 0;
 CC4->Outs.push_back(CC5); Markers[CC5]++;
 Markers[NetRoot] = 0;
 NInps = Markers;

 cout<<"\nSUBSYSTEM:\n";
 FindSubSystem(NetRoot);
 cout<<"\nSTACK:\n";
 Q=1;
 stack(Q);
 Q=2; stack(Q);
 Q=3; stack(Q);
 continue stack(Q); cout<<Q<<" ";
 continue stack(Q); cout<<Q<<" ";
 continue stack(Q); cout<<Q<<"\n";
 cout<<"\nQUEUE:\n";
 Q=1; queue(Q);
 Q=2; queue(Q);
 Q=3; queue(Q);
 continue queue(Q); cout<<Q<<" ";
 continue queue(Q); cout<<Q<<" ";
 continue queue(Q); cout<<Q<<"\n";
 cout<<"\nFIBB:\n";
 Fib(0,0,Q); cout<<Q<<" ";
 continue Fib(0,0,Q); cout<<Q<<" ";
 continue Fib(0,0,Q); cout<<Q<<" ";
 continue Fib(0,0,Q); cout<<Q<<" ";
 continue Fib(0,0,Q); cout<<Q<<" ";
 continue Fib(0,0,Q); cout<<Q<<"\n";

 double X1[5][VEC_SIZE] = {{1,2},{-1,2},{0,5},{-4,3},{2,1}};
 double X2[5][VEC_SIZE] = {{-1,7},{6,4},{1,1},{2,3},{0,0}};
 double X3[5][VEC_SIZE] = {{6,4},{0,0},{1,1},{-1,7},{2,3}};
 double R[5][VEC_SIZE];
 plan_parallel_chain(0,Stage0(5,(double *)X1,(double *)X2,(double *)X3,(double *)R),Stage1(NULL,0,NULL));
 cout<<" REENT: ";
 for (i=0; i<5; i++)
   {
    cout<<"(";
    for (int j=0; j<VEC_SIZE; j++)
      cout<<R[i][j]<<(j==VEC_SIZE-1 ? ")" : ",");
    cout<<" ";
   }
 cout<<"\n";
 #ifdef _OPENMP
 int NLOCK = 0;
 #pragma omp parallel num_threads(2) private(i) shared(NLOCK)
  switch (omp_get_thread_num()) {
    case 0:
      for (i=0; i<5; i++)
        {
         R[i][0] = 0.0;
         for (j=0; j<VEC_SIZE; j++)
             R[i][0] += X2[i][j]*X3[i][j];
         #pragma omp atomic
           NLOCK++;
         #pragma omp flush(NLOCK)
        }
      break;
    case 1:
      for (i=0; i<5; i++)
        {
         while (NLOCK<i) _Yield();
         for (j=VEC_SIZE-1; j>=0; j--)
             R[i][j] = X1[i][j]+R[i][0];
        }
  }
 cout<<" OMP: ";
 for (i=0; i<5; i++)
   {
    cout<<"(";
    for (int j=0; j<VEC_SIZE; j++)
      cout<<R[i][j]<<(j==VEC_SIZE-1 ? ")" : ",");
    cout<<" ";
   }
 #endif
 plan_parallel_chain(1,VEC_SIZE,Div((double *) &X1[0][0],(double *) &X2[0][0]));
 cout<<"\n[ ";
 for (j=0; j<VEC_SIZE; j++)
   cout<<X1[0][j]<<" ";
 cout<<"]\n\n";

 cout<<"Sum(F) = "<<SumF(8)<<"\n";
 #if _OPENMP>=200805
 cout<<"OpenMP 3.0: Sum(F) = "<<omp3_SumF(8)<<"\n";
 #endif

 cout<<"Find the path in the simple labirint (Li algorithm) :\n";
 Labirint[FirstY][FirstX] = 1;
 plan_chain(0,FindLi(FirstX,FirstY,2),OutLi(0,0));
 cout<<"\n";

 #ifdef _OPENMP
 for (i=8; i>=2; i--)
     IntegrateThermal(i);
 SingleIntegrateThermal(8);

 CopyTree(Root,_Root);

 #ifndef __THOROW__
 plan_parallel_chain(1,GenMinMaxTree(Root,0),FindMinMaxTree(NULL,0)/8);
 cout<<"Declarative markup: Result of MinMaxing = "<<Root->Data()<<"\n";
 plan_parallel_chain(1,_GenMinMaxTree(_Root,0),_FindMinMaxTree(NULL,0)/8);
 cout<<"Partially Declarative way: Result of MinMaxing = "<<_Root->Data()<<"\n";
 Out(Root,1);
 #if _OPENMP>=200805
 omp3_FindMinMaxTree(Root,0);
 cout<<"\nOpenMP 3.0: MinMaxing = "<<Root->Data()<<"\n";
 #endif
 #endif
 #endif

 cout<<"\nPARALLEL OUT\n";
 ParallelOut(Root, Root, false);

 cout<<"\nFINISH\n";

 delete[] Asave;
 #ifdef __MPI__
 MPI_Finalize();
 #endif
}
//---------------------------------------------------------------------------
