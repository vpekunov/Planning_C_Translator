#ifndef __KINETIC__
#define __KINETIC__

#include <stdlib.h>
#include <math.h>

/* Максимальное число веществ, участвующих в реакции */
#define MaxActSubst 40
/* Максимальная длина имени вещества */
#define SubstNameLength 21

#define Adams_Rozhkov_Method 0
#define Rosenbrock_Method 1

typedef struct {
  int NumLeft;
  int NumRight;
  int Indexes[MaxActSubst];
} Reaction;

typedef struct {
 int      LossH;    /* Признак малости H */
 double   LastH;    /* Последнее H */
 double   ReachTau; /* Достигнутое значение TAU */
 float    Tmp;      /* Температура проведения реакций */
} ErrorKinetic;

typedef double Derivs[7];

typedef char   SubstName[SubstNameLength];

#ifndef M_LOG10E
#define M_LOG10E 0.434294481903251827651
#endif

double Koeffs[5][3] =
{
	{ 1.0, 2.0, 3.0 },
	{ 1.0, 4.5, 6.0 },
	{ 0.5, 7.3333333, 9.1666667 },
	{ 0.1666667, 10.4166667, 12.5 },
	{ 0.04166667, 13.7, 1.0 }
};

double AdamsTable[5][6] = {
	{ 1.0, 1.0, 0.0, 0.0, 0.0, 0.0 },
	{ 2.0, 1.0, 1.0, 0.0, 0.0, 0.0 },
	{ 12.0, 5.0, 8.0, -1.0, 0.0, 0.0 },
	{ 24.0, 9.0, 19.0, -5.0, 1.0, 0.0 },
	{ 720.0, 251.0, 646.0, -264.0, 106.0, -19.0 }
};

double RosenTable[4][4] = {
	{ -1.0, 0.0, 0.0, 0.0 },
	{ 1.0 / 8.0, 3.0 / 8.0, 1.0, 0.0 },
	{ 3.0 / 8.0, 19.0 / 24.0, -1.0 / 6.0, 0.0 },
	{ 13.0 / 6.0, 1.0 / 6.0, -2.0, 2.0 / 3.0 }
};

class Kinetic {
public:

ErrorKinetic KinErrorInfo; /* Блок информации по ошибке */

int LossPrecision;        /* Флаг потери точности при вычислениях */
int MaxIterations = 30000; /* Максимальное число итераций */

int Iters; /* Действительное число итераций */

/* Константы STIFF */
double dfltzr = 1.0E-18;
int    maxite = 3;
int    maxfai = 3;
double rmxini = 1.0E+4;
double rmxnor = 10.0;
double rmxfai = 2.0;
int    idelay = 10;
double rhcorr = 0.25;
double rherr3 = 0.1;
double thrshl = 0.0;
double rctest = 0.3;
double bias1  = 1.3;
double bias2  = 1.2;
double bias3  = 1.4;

double ZeroK = 273.0;
double R     = 1.987E-3;

double CalcEps = 1E-2; /* Относительная точность интегрирования ST1/eps */
double InitH = 1E-7;  /* Начальный шаг интегрирования h */
double MinH  = 1.0E-18;/* Минимальный шаг интегрирования ST1/hmin */

double InitTime = 0.0; /* Начальное время интегрирования */

int NReact;  /* Число реакций KINET/m */
int NSubst;  /* Число веществ KINET/n = ST1/n */
int NASubst; /* Число веществ, участвующих в реакции */

float Tk;   /* Температура в Кельвинах KINET/tk */

double EndTime; /* Конечное время интегрирования */

/* Имена веществ [NSubst] */
SubstName Names[MaxActSubst];
/* Скорости витания веществ [NSubst] */
double    Uw[MaxActSubst];
/* Карта участия веществ в реакциях */
char      Activity[MaxActSubst];
/* Индексы веществ, участвующих в химических реакциях */
int       TranMap[MaxActSubst];
/* Ei : Энергии активации KINET/ea [NReact] */
double * EA;
/* Ai : Lg( предэкспоненты констант скорости ) [NReact] */
double * A;
/* Ni : Показатели степеней в температурных множителях KINET/tn [NReact] */
double * Tn;
/* Реакции KINET/lr [NReact] */
Reaction * LR;
/* Начальная концентрация веществ [NASubst] */
float * Conc0;
/* Конечная концентрация [NASubst] */
float * Conc1;

/* Рабочие переменные [NASubst] */
Derivs * Y;
/* KINET */
int    LgAScale; /* ml = Lg(aml) */
double AScale; /* Масштабный множитель aml */
double * CC;    /* Вычисляемые константы скоростей реакций c [NReact] */
double Tem;    /* Температура в ккал/моль tem */
/* ST1 */
double Time;
double H;
int    MaxDer;
int    jStart;
/* ST2 */
double * Ymax; /* [NASubst] */
/* ST3 */
double * Err; /* [NASubst] */
/* ST4 */
double * Df; /* [NASubst][NASubst] */
/* ST5 */
double * FSave1; /* [NASubst] */
double * FSave2; /* [NASubst] */
/* STIFF */
int    * iRow; /* [NASubst] */

double El[6];
double Tq[4];
double edn;
double e;
double eup;
double bnd;

int   Nq;
int   l;
int   lmax;
int   idoub;
double rmax;
double rc;

double rh;

double trend;
double oldl0;
double hold;

int   evalja;
int   conver;

void SetTk(float Tmp)
{
 Tk = ZeroK+Tmp;
}

double amax2(double First, double Second)
{
 return First>Second ? First : Second;
}

double amax3(double First, double Second, double Third)
{
 return First>Second ? amax2(First,Third) : amax2(Second,Third);
}

double amin2(double First, double Second)
{
 return First<Second ? First : Second;
}

double amin3(double First, double Second, double Third)
{
 return First<Second ? amin2(First,Third) : amin2(Second,Third);
}

int AllocateKineticByReactions()
{
 int doubleNR = NReact*sizeof(double);

 memset(Activity,0,sizeof(Activity));
 /* Ei : Энергии активации KINET/ea [NReact] */
 EA = (double *) malloc(doubleNR);
 /* Ai : Lg( предэкспоненты констант скорости ) [NReact] */
 A  = (double *) malloc(doubleNR);
 /* Ni : Показатели степеней в температурных множителях KINET/tn [NReact] */
 Tn = (double *) malloc(doubleNR);
 /* Реакции [NReact] */
 LR = (Reaction *) malloc(NReact*sizeof(Reaction));

 CC     = (double *) malloc(doubleNR);

 return (EA && A && Tn && LR && CC);
}

/* Выводим из рассмотрения вещества, фактически не участвующие в реакциях */
void ReTranslate()
{
 char Map[MaxActSubst];
 char Delta = 0;
 int  i,j;

 NASubst = 0;
 for (i=0; i<NSubst; i++)
     if (Activity[i])
        {
         Map[i] = Delta;
         TranMap[NASubst++] = i;
        }
     else
        Delta++;
 for (i=0; i<NReact; i++)
     for (j=0; j<LR[i].NumLeft+LR[i].NumRight; j++)
         LR[i].Indexes[j] -= Map[LR[i].Indexes[j]];
}

int AllocateKineticBySubsts()
{
 int floatNS  = NASubst*sizeof(float);
 int doubleNS = NASubst*sizeof(double);

 Conc0 = (float *) malloc(floatNS);
 Conc1 = (float *) malloc(floatNS);
 Y     = (Derivs *) malloc(NASubst*sizeof(Derivs));
 Ymax  = (double *) malloc(doubleNS);
 Err   = (double *) malloc(doubleNS);
 Df    = (double *) malloc(NASubst*doubleNS);
 FSave1 = (double *) malloc(doubleNS);
 FSave2 = (double *) malloc(doubleNS);
 iRow   = (int *) malloc(NASubst*sizeof(int));

 return (Conc0 && Conc1 && Y && Ymax && Err && Df && FSave1 && FSave2 && iRow);
}

void FreeKinetic()
{
 free(EA);
 free(A);
 free(Tn);
 free(LR);

 free(Conc0);
 free(Conc1);
 free(Y);
 free(CC);
 free(Ymax);
 free(Err);
 free(Df);
 free(FSave1);
 free(FSave2);
 free(iRow);
}

int Translate(int NumEq, char * Equation)
{
 int Count = 0;

 int Long  = strlen(Equation);

 int Left  = 0;
 int All   = 0;

 if (!Long || Equation[Long-1]=='+' || Equation[Long-1]=='-' || Equation[Long-1]=='>')
    return 0;

 while (Count<Long)
   {
    int How = 0;

    int CurLong;
    int End;

    int Found = 0;
    int Index = 0;

    if (Equation[Count]>='0' && Equation[Count]<='9')
       {
        while (Equation[Count]>='0' && Equation[Count]<='9' && Count<Long)
          {
           How = How*10+Equation[Count]-'0';
           Count++;
          }
        if (!How) return 0;
       }
    else How = 1;

    if (All+How>MaxActSubst) return 0;

    End = Count;

    while (Equation[End]!='+' && Equation[End]!='-' && End<Long) End++;

    CurLong = End-Count;

    while (Index<NSubst && !Found)
       {
        if (strlen(Names[Index])==CurLong)
           {
            int CurN = 0;
            int CurE = Count;

            while (CurN<CurLong && Names[Index][CurN]==Equation[CurE])
              {
               CurN++;
               CurE++;
              }
            if (CurN>=CurLong) Found = 1;
           }

        if (!Found) Index++;
       }

    if (!Found) return 0;

    while (How--) LR[NumEq].Indexes[All++] = Index;
    Activity[Index] = 1;

    if (End<Long-1)
       if (Equation[End]=='-')
          if (Equation[++End]=='>' && !Left)
             Left = All;
          else return 0;
    Count = End+1;
   }
 LR[NumEq].NumLeft  = Left;
 LR[NumEq].NumRight = All-Left;

 return (Left);
}

/* ВЫЧИСЛЕНИЕ ЗНАЧЕНИЙ ЯКОБИАНА ИНТЕГРИРУЕМОЙ СИСТЕМЫ ОДУ ПО */
/* ЗНАЧЕНИЯМ ВРЕМЕНИ t И РЕШЕНИЙ y, СООТВЕТСТВУЮЩИХ ЭТОМУ МОМЕНТУ */
/* ВРЕМЕНИ. ЭЛЕМЕНТЫ ЯКОБИАНА ЗАСЫЛАЮТСЯ В МАССИВ Df[50,50) */
/* PEDERV */
void Jacobian() /* + */
{
 int i,j,k;

 int PtrIJ = 0;

 for (i=0;i<NASubst;i++)
     for (j=0;j<NASubst;j++,PtrIJ++)
         Df[PtrIJ]=0.0;
/* ЦИКЛ ПО ЧИСЛУ УРАВНЕНИЙ */
 for (i=0;i<NReact;i++)
     {
      int Left  = LR[i].NumLeft;
      int Right = LR[i].NumRight;

      for (j=0;j<Left;j++)
          {
           int Cur = LR[i].Indexes[j];

           double W  = CC[i];

           for (k=0;k<Left;k++)
               if (k!=j) W*=Y[LR[i].Indexes[k]][0];
           for (k=0;k<Left;k++)
               Df[NASubst*LR[i].Indexes[k]+Cur] -= W;
           for (k=0;k<Right;k++)
               Df[NASubst*LR[i].Indexes[Left+k]+Cur] += W;
          }
     }
 #if defined(__IMITATE__) && !defined(WIN32)
 Check();
 #endif
}

/* ВЫЧИСЛЯЕТ ЗНАЧЕНИЯ ПРАВЫХ ЧАСТЕЙ СИСТЕМЫ ОДУ ПО ЗНАЧЕНИЯМ */
/* ВРЕМЕНИ t И РЕШЕНИЙ y0, СООТВЕТСТВУЮЩИХ ЭТОМУ МОМЕНТУ ВРЕМЕНИ, */
/* И ЗАСЫЛАЕТ ИХ В МАССИВ f */
/* DIFFUN */
void DifFun(double * Y0,int Ystep,double * F) /* + */
{
 int i,j;

 for (i=0;i<NASubst;i++)
     {
      if (Y0[Ystep*i]<0.0) Y0[Ystep*i] = 0.0;
      F[i] = 0.0;
     }

 for (i=0;i<NReact;i++)
     {
      int Left  = LR[i].NumLeft;
      int Right = LR[i].NumRight;

      double W = CC[i];

      for (j=0;j<Left;j++)
          W*=Y0[Ystep*LR[i].Indexes[j]];
      /* Здесь W содержит значение скорости соответствующей реакции.
         Делить на AScale */
      for (j=0;j<Left;j++)
          F[LR[i].Indexes[j]] -= W;
      for (j=0;j<Right;j++)
          F[LR[i].Indexes[Left+j]] += W;
     }
 #if defined(__IMITATE__) && !defined(WIN32)
 Check();
 #endif
}

void JacobianD() /* + */
{
 int i,j,k;
 double F0[MaxActSubst];
 double F1[MaxActSubst];
 const double DX = 0.0000001;
 int PtrIJ;

 DifFun((double *) Y,7,F0);
 for (i=0;i<NASubst;i++)
     {
      Y[i][0] += DX;
      DifFun((double *) Y,7,F1);
      Y[i][0] -= DX;
      for (j=0,PtrIJ=i; j<NASubst; j++,PtrIJ+=NASubst)
          Df[PtrIJ] = (F1[j]-F0[j])/DX;
     }
 #if defined(__IMITATE__) && !defined(WIN32)
 Check();
 #endif
}

/* ПЕРЕМАСШТАБИРОВАНИЕ РЕШЕНИЙ СИСТЕМЫ И ИХ ПРОИЗВОДНЫХ */
/* ПРИ ИЗМЕНЕНИИ ШАГА ИНТЕГРИРОВАНИЯ */
/* RESCAL */
void Rescale(double * rH, double rMax, double * rC, int L, int * idoub)
{
 int i,j;

 double R1=1.0;

 (*rH) = amax2((*rH),MinH/fabs(H));
 (*rH) = amin3((*rH),EndTime/fabs(H),rMax);
 for (j=1;j<L;j++)
     {
      R1 *= (*rH);
      for (i=0;i<NASubst;i++)
          Y[i][j] *= R1;
     }
 H *= (*rH);
 (*rC) *= (*rH);
 (*idoub) = L+1;
 #if defined(__IMITATE__) && !defined(WIN32)
 Check();
 #endif
}

/* ВЫЧИСЛЕНИЕ ЗНАЧЕНИЯ ПРЕДИКТОРА */
void Predictor() /* + */
{
 int i,j,j1,j2;

 for (j1=0;j1<Nq;j1++)
     for (j2=j1;j2<Nq;j2++)
         {
          j = Nq-j2+j1-1;

          for (i=0;i<NASubst;i++)
              Y[i][j] += Y[i][j+1];
         }
 #if defined(__IMITATE__) && !defined(WIN32)
 Check();
 #endif
}

void RePredictor()
{
 int i,j,j1,j2;

 for (j1=0;j1<Nq;j1++)
     for (j2=j1;j2<Nq;j2++)
         {
          j = Nq-j2+j1-1;

          for (i=0;i<NASubst;i++)
              Y[i][j] -= Y[i][j+1];
         }
 #if defined(__IMITATE__) && !defined(WIN32)
 Check();
 #endif
}

/* ВЫЧИСЛЕНИЕ КОЭФФИЦИЕНТОВ МЕТОДА ИНТЕГРИРОВАНИЯ */
/* СООТВЕТСТВУЮЩЕГО ПОРЯДКА */
/* COSET */
void CalcKoeffs()
{
 int i;

 El[1]=1.0;
 if (MaxDer>5) MaxDer = 5;
 switch (Nq) {
   case 1: El[0] = 1.0;
           break;
   case 2: El[0] = 6.666666666667E-01;
           El[2] = 3.333333333333E-01;
           break;
   case 3: El[0] = 5.454545454546E-01;
           El[2] = 1.0;
           El[3] = 9.090909090909E-02;
           break;
   case 4: El[0] = 0.48;
           El[2] = 0.7;
           El[3] = 0.2;
           El[4] = 0.02;
           break;
   case 5: El[0] = 4.379562043796E-01;
           El[2] = 8.211678832117E-01;
           El[3] = 3.102189781022E-01;
           El[4] = 5.474452554745E-02;
           El[5] = 3.649635036496E-03;
 }
 for (i=0;i<3;i++)
     Tq[i] = Koeffs[Nq-1][i];
 Tq[3]=0.5/(Nq+2.0);
}

/* ОСУЩЕСТВЛЯЕТ LU-РАЗЛОЖЕНИЕ МАТРИЦЫ E-beta*h*A, */
/* ГДЕ A-ЯКОБИАН СИСТЕМЫ, E-ЕДИНИЧНАЯ МАТРИЦА, */
/* h-ТЕКУЩИЙ ШАГ ИНТЕГРИРОВАНИЯ, beta-КОНСТАНТА */
/* MATDEC */
void GetLU(int * iRow) /* + */
{
 int i,j,k;

 if (NASubst<=1)
    {
     Df[0] = 1.0/Df[0];
     iRow[0]  = 0;
    }
 else
   {
    for (i=0;i<NASubst;i++)
        iRow[i]=i;
    for (i=0;i<NASubst-1;i++)
      {
       double Big  = 0.0;
       int    iBig = 0;

       double Kf;
       int    ir;

       for (j=i;j<NASubst;j++)
           {
            /* По непонятным причинам компилятор Borland C++ 3.1
               отказался скомпилировать следующую строку :
            double size = fabs(Df[NASubst*iRow[j]+i]);
            */
            double * Deriv = Df;
            double size    = fabs(Deriv[NASubst*iRow[j]+i]);

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
       ir = NASubst*iRow[i];

       Kf = 1.0/Df[ir+i];

       Df[ir+i] = Kf;
       for (j=i+1;j<NASubst;j++)
           {
            int jr = NASubst*iRow[j];

            double Fact = Kf*Df[jr+i];

            Df[jr+i] = Fact;
            for (k=i+1;k<NASubst;k++)
                Df[jr+k] -= Fact*Df[ir+k];
           }
      }
    i = iRow[NASubst-1];

    Df[NASubst*(i+1)-1] = 1.0/Df[NASubst*(i+1)-1];
   }
 #if defined(__IMITATE__) && !defined(WIN32)
 Check();
 #endif
}

/* РЕШЕНИЕ СИСТЕМЫ ЛИНЕЙНЫХ УРАВНЕНИЙ */
void SolveLU(int * iRow, double * Y, double * X) /* + */
{
 int i,j,k;

 if (NASubst<=1) X[0] = Y[0]*Df[0];
 else
   {
    X[0] = Y[iRow[0]];
    for (i=1;i<NASubst;i++)
        {
         int   ir = iRow[i];
         double V  = Y[ir];

         for (j=0;j<i;j++)
             V -= Df[NASubst*ir+j]*X[j];
         X[i] = V;
        }

    X[NASubst-1]*=Df[NASubst*iRow[NASubst-1]+NASubst-1];

    for (i=1,j=NASubst-2;i<NASubst;i++,j--)
        {
         int   jr = NASubst*iRow[j];
         double V = X[j];

         for (k=j+1;k<NASubst;k++)
             V -= Df[jr+k]*X[k];
         X[j] = V*Df[jr+j];
        }
   }
 #if defined(__IMITATE__) && !defined(WIN32)
 Check();
 #endif
}

void SetNq(int NewNq)
{
 Nq = NewNq;
 l  = Nq+1;
 CalcKoeffs();

 lmax   = MaxDer+1;
 oldl0  = El[0];
 edn    = Tq[0]*CalcEps;
 edn   *= edn;
 e      = Tq[1]*CalcEps;
 e     *= e;
 eup    = Tq[2]*CalcEps;
 eup   *= eup;
 bnd    = Tq[3]*CalcEps;
 bnd   *= bnd;

 #if defined(__IMITATE__) && !defined(WIN32)
 Check();
 #endif
}

int Stiff()
{
 int   kFlag=0;
 double Told=Time;

 double pr1,pr2,pr3;
 double d;
 int newq;

 int Break590;
 int Break670;
 int ExitLoop;

 double Savel0;

 int i,j;

 if (jStart==0)
    {
     DifFun((double *) Y,7,FSave1);
     for (i=0;i<NASubst;i++)
         Y[i][1]=FSave1[i]*H;

     SetNq(1);

     idoub  = l+1;
     rmax   = rmxini;
     trend  = 1.0;
     rc     = 0.0;
     hold   = H;
     evalja = 1;
     conver = 0;
    }
 else
   if (jStart<0)
      if (H!=hold)
         {
          rh = H/hold;
          H  = hold;
          Rescale(&rh,rmax,&rc,l,&idoub);
         }

 Break590 = 0;
 Break670 = 0;
 ExitLoop = 0;
 do /* 200 */
   {
    if (fabs(rc-1.0)>rctest) evalja = 1;
    Time+=H;
    Predictor();

    do
      {
       int iter = 0;

       double d1;

       for (i=0;i<NASubst;i++)
           Err[i] = 0.0;
       DifFun((double *) Y,7,FSave2);

       if (evalja)
          {
           double rf = -El[0]*H;

           Jacobian();

           for (i=0;i<NASubst;i++)
             for (j=0;j<NASubst;j++)
                Df[NASubst*i+j]*=rf;

           for (i=0;i<NASubst;i++)
               Df[(NASubst+1)*i]+=1.0;

           evalja = 0;
           conver = 0;

           rc = 1.0;
           GetLU(iRow);
          }
       ExitLoop = 0;
       Break590 = 0;
       do
         {/* 460 */
          for (i=0;i<NASubst;i++)
              FSave2[i]=FSave2[i]*H-Y[i][1]-Err[i];
          SolveLU(iRow,FSave2,FSave1);

          d = 0.0;
          for (i=0;i<NASubst;i++)
              {
               double V = FSave1[i]/Ymax[i];

               Err[i] += FSave1[i];
               FSave1[i] = Y[i][0]+El[0]*Err[i];
               d += V*V;
              }
          if (iter!=0) trend = amax2(0.9*trend,d/d1);
          if ((d*amin2(1.0,2.0*trend))<=bnd) Break590 = 1;
          else
             {
              d1 = d;
              iter++;
              if (iter==maxite) ExitLoop = 1;
              else DifFun(FSave1,1,FSave2);
             }
         }
       while ((!ExitLoop) && (!Break590));
       ExitLoop = Break590 || (!conver);
       if (!ExitLoop) evalja=1;
      }
    while (!ExitLoop);

    if (!Break590)
       {
        Time = Told;
        rmax = rmxfai;
        RePredictor();

        if (fabs(H)<=(MinH*1.00001))
           {
            hold = H;
            jStart = Nq;

            return -2;
           }
        rh = rhcorr;
        Rescale(&rh,rmax,&rc,l,&idoub);
       }
    else
      {
       /* 590 */
       d = 0.0;
       for (i=0;i<NASubst;i++)
           {
            double V = Err[i]/Ymax[i];
            d += V*V;
           }
       conver = 1;

       if (d>e)
          {
           kFlag--;
           Time = Told;
           RePredictor();

           rmax = rmxfai;
           if (fabs(H)<=(MinH*1.00001))
              {
               hold = H;
               jStart = Nq;

               return -1;
              }
           if (kFlag<=-maxfai)
              { /* 650 */
               rh = amax2(MinH/fabs(H),rherr3);
               H *= rh;
               DifFun((double *) Y,7,FSave1);
               for (i=0;i<NASubst;i++)
                   Y[i][1]=H*FSave1[i];

               evalja = 1;
               idoub  = idelay;
               if (Nq!=1) SetNq(1);
              }
           else
             {
              pr2 = 1.0/(pow(d/e,0.5/l)*bias2+dfltzr);
              if (Nq!=1)
                 {
                  double sum = 0.0;
                  for (i=0;i<NASubst;i++)
                      {
                       double V = Y[i][l-1]/Ymax[i];
                       sum += V*V;
                      }
                  pr1 = 1.0/(pow(sum/edn,0.5/Nq)*bias1+dfltzr);
                  if (pr1>pr2)
                     { /* 640 */
                      double Savel0 = oldl0;

                      SetNq(Nq-1);
                      rh =  pr1;
                      rc *= El[0]/Savel0;
                      Rescale(&rh,rmax,&rc,l,&idoub);
                      continue; /* GOTO 200 */
                     }
                 }
              rh = pr2;
              Rescale(&rh,rmax,&rc,l,&idoub);
             }
          }
       else Break670 = 1;
      }
   }
 while (!Break670);
 /* 670 */
 for (j=0;j<l;j++)
     for (i=0;i<NASubst;i++)
       Y[i][j] += El[j]*Err[i];

 if (idoub!=1)
    {
     idoub--;
     if ((idoub<=1) && (Nq!=MaxDer))
        for (i=0;i<NASubst;i++)
            Y[i][lmax-1] = Err[i];
     hold = H;
     jStart = Nq;

     return 0;
    }
 pr3 = dfltzr;
 if (Nq!=MaxDer)
    {
     double sum = 0.0;
     for (i=0;i<NASubst;i++)
         {
          double V = (Err[i]-Y[i][lmax-1])/Ymax[i];
          sum += V*V;
         }
     pr3 = 1.0/(pow(sum/eup,0.5/(l+1))*bias3+dfltzr);
    }
 /* 720 */
 pr2 = 1.0/(pow(d/e,0.5/l)*bias2+dfltzr);
 pr1 = dfltzr;
 if (Nq!=1)
    {
     double sum = 0.0;
     for (i=0;i<NASubst;i++)
         {
          double V = Y[i][l-1]/Ymax[i];
          sum += V*V;
         }
     pr1 = 1.0/(pow(sum/edn,0.5/Nq)*bias1+dfltzr);
    }
 /* 740 */
 if ((pr3>pr1) && (pr3>pr2))
    {
     newq = l;
     rh = pr3;
     if (rh<thrshl)
        {
         idoub  = idelay;
         hold   = H;
         jStart = Nq;

         return 0;
        }
     for (i=0;i<NASubst;i++)
         Y[i][newq] = Err[i]*El[l-1]/l;
    }
 else
   if (pr1>pr2)
      {
       newq = Nq-1;
       rh = pr1;
       if (rh<thrshl)
          {
           idoub  = idelay;
           hold   = H;
           jStart = Nq;

           return 0;
          }
      }
   else
     {
      rh = pr2;
      if (rh<thrshl) idoub = idelay;
      else
        {
         Rescale(&rh,rmax,&rc,l,&idoub);
         rmax = rmxnor;
        }
      hold   = H;
      jStart = Nq;

      return 0;
     }
 /* 780 */
 Savel0 = oldl0;
 SetNq(newq);
 rc *= El[0]/Savel0;
 /* 790 */
 Rescale(&rh,rmax,&rc,l,&idoub);
 rmax = rmxnor;
 /* 840 */
 hold = H;
 jStart = Nq;

 return 0;
}

int AdamsOrder = 4;
int Fail = 0;

void Adams_Rozhkov()
{
 int    i,j,k;
 int    CurOrder;
 double Xp[MaxActSubst];

 double AdamsH = H/AdamsOrder;

 for (i=0; i<NASubst; i++)
     Xp[i] = Y[i][0];
 Fail = 0;
 for (CurOrder = 1; CurOrder<=AdamsOrder && !Fail && !LossPrecision; CurOrder++)
   {
    double F1 = AdamsH/AdamsTable[CurOrder-1][0];

    for (i=0;i<NASubst;i++)
        {
         FSave1[i] = 0;
         FSave2[i] = 0;
        }
    /* Вычисляем значения правых частей системы ОДУ, учитывая,
       что для каждого j-вещества правая часть записывается
       как FSave1[j]+Conc[j]*FSave2[j] */
    for (i=0;i<NReact;i++)
        {
         int Left  = LR[i].NumLeft;
         int Right = LR[i].NumRight;

         long Lj = 0; /* Номера веществ в левой части */
         /* Здесь W, WT содержит значение скорости реакции.
            Делить на AScale */
         int      Flags[MaxActSubst];
         double * W  = Ymax;
         double   WT = CC[i];

         for (j=0;j<Left;j++)
             {
              k    =  LR[i].Indexes[j];
              Lj   |= (1<<k);
              W[k] =  CC[i];
              WT   *= Y[k][CurOrder-1];
              Flags[k] = 0;
             }
         for (k=0;k<Left;k++)
             if (!Flags[LR[i].Indexes[k]])
                {
                 for (j=0;j<Left;j++)
                     if (j!=k)
                        W[LR[i].Indexes[k]] *= Y[LR[i].Indexes[j]][CurOrder-1];
                 Flags[LR[i].Indexes[k]] = 1;
                }

         for (j=0;j<Right;j++)
             {
              k = LR[i].Indexes[Left+j];
              if (Lj & (1<<k))
                 FSave2[k] += W[k];
              else
                 FSave1[k] += WT;
             }
         for (j=0;j<Left;j++)
             {
              k = LR[i].Indexes[j];
              FSave2[k] -= W[k];
             }
        }

    for (i=0; i<NASubst && !Fail; i++)
        {
         double HH = 1-F1*FSave2[i]*AdamsTable[CurOrder-1][1];

         if (fabs(HH)>dfltzr)
            {
             Y[i][CurOrder] = FSave1[i]*AdamsTable[CurOrder-1][1];
             for (j=2; j<=CurOrder; j++)
                 Y[i][CurOrder] += AdamsTable[CurOrder-1][j]*Y[i][CurOrder-j];
             Y[i][CurOrder] = (Y[i][CurOrder-1]+F1*Y[i][CurOrder])/HH;
             Y[i][CurOrder-1] = FSave1[i]+Y[i][CurOrder]*FSave2[i];
            }
         else
            {
             Fail = 1;
             H /= 2.0;
            }
        }
    if ((Time+H)==Time) LossPrecision = 1;
   }

 if (!LossPrecision)
    {
     if (!Fail)
        {
         for (i=0;i<NASubst;i++)
             Y[i][0] = Y[i][CurOrder-1];
         Time += H;
        }
     else
        for (i=0;i<NASubst;i++)
            Y[i][0] = Xp[i];
     if (EndTime-Time<H)
        H = EndTime-Time;
     if ((Time+H)==Time)
        Time = EndTime;
    }
 Iters+=AdamsOrder-1;
}

void Rosenbrock()
{
 int i,j,k;

 Fail = 0;

 Jacobian();
 for (i=0;i<NASubst;i++)
   for (j=0;j<NASubst;j++)
      Df[NASubst*i+j]*=-H;
 for (i=0;i<NASubst;i++)
     Df[(NASubst+1)*i]+=1.0;
 GetLU(iRow);

 for (k=1; k<=4; k++)
     {
      for (i=0;i<NASubst;i++)
          {
           Y[i][k] = Y[i][0];
           for (j=0; j<k-1; j++)
               Y[i][k] += RosenTable[k-2][j]*Y[i][j+1];
          }
          
      DifFun((double *) &Y[0][k],7,FSave2);
      for (i=0;i<NASubst;i++)
          FSave2[i]*=H;
      SolveLU(iRow,FSave2,FSave1);
      for (i=0;i<NASubst;i++)
          Y[i][k] = FSave1[i];
     }

 for (i=0;i<NASubst;i++)
     for (k=1; k<=4; k++)
         Y[i][0] += RosenTable[3][k-1]*Y[i][k];
 Time += H;
 if (EndTime-Time<H)
    H = EndTime-Time;
 if ((Time+H)==Time)
    Time = EndTime;
}

#if defined(__UNIX__) || defined(__MVS__) || defined(__MAY_BE_MICROSOFTC__)
double pow10(int Arg)
{
 double result = 1;

 if (Arg>0)
   while((Arg--)>0) result*=10;
 else if (Arg<0)
   while((Arg++)<0) result/=10;

 return result;
}
#endif

void OneTaktKinetic(int UseStiffGearMethod, int OtherMethod)
{
 int i,j;

 Tem = R*Tk;

 Iters = 0;
 if (Tem>dfltzr)
    {
     /* Автоматический выбор масштабного множителя */
     double maxY = dfltzr;

     for (i=0;i<NASubst;i++)
         if (Conc0[i]>maxY) maxY = Conc0[i];

     if (maxY>dfltzr)
        {
         LgAScale = -log10(maxY);
         AScale   = pow10(LgAScale);

         /* Вычисление коэффициентов скорости */
         for (i=0;i<NReact;i++)
             {
              double PEi = (A[i]-(LR[i].NumLeft-1)*LgAScale)/M_LOG10E;
              double Degree = PEi-EA[i]/Tem;

              if (Degree>-80.0) CC[i] = exp(Degree)*pow((double)Tk,Tn[i]);
              else CC[i] = 0.0;
             }

         if (UseStiffGearMethod)
            {
             double EpsCom = 1.0E-12/CalcEps;
             /* STIFFC */
             for (i=0;i<NASubst;i++)
                 {
                  Ymax[i]=0.0;
                  Y[i][0]=Conc0[i]*AScale;
                  for (j=1;j<6;j++)
                      Y[i][j]=0.0;
                 }

             Time = InitTime;

             if (EndTime<InitH) H=EndTime;
             else H = InitH;

             LossPrecision = (Time+H)==Time;

             MaxDer = 5;

             jStart = 0;

             for (Iters = 0;Time<=EndTime && Iters<MaxIterations && !LossPrecision;Iters++)
              {
               double ys = 0.0;

               for (i=0;i<NASubst;i++)
                   ys += fabs(Y[i][0]);
               ys *= EpsCom;
               for (i=0;i<NASubst;i++)
                   Ymax[i] = amax3(Y[i][0],ys,dfltzr);

               if (Stiff())
                  {
                   jStart=-1;
                   H/=10.0;
                  }
               if ((Time+H)==Time) LossPrecision = 1;
              }
             if (Iters==MaxIterations) LossPrecision = 1;

             if (LossPrecision)
                {
                 KinErrorInfo.LossH    = Iters!=MaxIterations;
                 KinErrorInfo.LastH    = H;
                 KinErrorInfo.ReachTau = Time;
                 KinErrorInfo.Tmp      = Tk-ZeroK;
                }
             else
                for (i=0;i<NASubst;i++)
                    {
                     double sum = 0.0;
                     for (j=0;j<=jStart;j++)
                         sum += Y[i][j]*pow((EndTime-Time)/H,j);
                     Conc1[i] = sum/AScale;
                    }
            }
         else
            {
             double Divider = 1.0;
             double Divisor = 2.0;
             double _EndTime = EndTime;
             double _H = amax2((EndTime-InitTime)/Divider,InitH);

             Iters = 0;

             for (i=0;i<NASubst;i++)
                 Y[i][0] = Conc0[i]*AScale;

             Time = InitTime;
             if (_H>InitH)
                {
                 float StFull[MaxActSubst];
                 int   EndFlag = 0;

                 for (i=0;i<NASubst;i++)
                     Y[i][6] = Y[i][0];

                 do
                   {
                    EndTime = _H;
                    H = _H;
					if (OtherMethod == 0)
						Adams_Rozhkov();
					else
						Rosenbrock();
                    Iters++;
                    for (i=0;i<NASubst;i++)
                        {
                         StFull[i] = Y[i][0];
                         Y[i][0] = Y[i][6];
                        }
                    if (Fail)
                       {
                        _H /= Divisor;
                        Divider *= Divisor;
                       }
                   }
                 while (Fail);

                 while (_H>InitH && Divisor*Divider<MaxIterations && !EndFlag)
                   {
                    float StHalf[MaxActSubst];
                    double YMAX = 0.0;

                    for (i=0;i<NASubst;i++)
                        Y[i][0] = Y[i][6];
                    Time = InitTime;
                    EndTime = _H/2.0;
                    H = EndTime;
					if (OtherMethod == 0)
						Adams_Rozhkov();
					else
						Rosenbrock();
					Iters++;
                    for (i=0;i<NASubst;i++)
                        StHalf[i] = Y[i][0];
                    Time = InitTime;
                    H = EndTime;
					if (OtherMethod == 0)
						Adams_Rozhkov();
					else
						Rosenbrock();
					Iters++;
                    for (i=0;i<NASubst;i++)
                        if (fabs(Y[i][0])>YMAX) YMAX = fabs(Y[i][0]);
                    EndFlag = 1;
                    for (i=0;i<NASubst;i++)
                        {
                         if (fabs(Y[i][0]-StFull[i])>CalcEps*YMAX) EndFlag = 0;

                         StFull[i] = StHalf[i];
                        }
                    if (!EndFlag)
                       {
                        _H /= Divisor;
                        Divider *= Divisor;
                       }
                   }
                 Time = InitTime+_H;
                }

             EndTime = _EndTime;
             H       = amax2(_H,InitH);
             LossPrecision = 0;

             for (;Time<EndTime && Iters<MaxIterations && !LossPrecision;Iters++)
				 if (OtherMethod == 0)
					 Adams_Rozhkov();
				 else
					 Rosenbrock();

             if (Iters==MaxIterations) LossPrecision = 1;

             if (LossPrecision)
                {
                 KinErrorInfo.LossH    = Iters!=MaxIterations;
                 KinErrorInfo.LastH    = H;
                 KinErrorInfo.ReachTau = Time;
                 KinErrorInfo.Tmp      = Tk-ZeroK;
                }
             else
                for (i=0;i<NASubst;i++)
                    Conc1[i] = Y[i][0]/AScale;
            }
        }
     else
        for (i=0;i<NASubst;i++)
            Conc1[i] = Conc0[i];
    }
 else
   for (i=0;i<NASubst;i++)
       Conc1[i] = Conc0[i];
}

};

#endif
