// 04 processors

#include <stdio.h>
#include <math.h>
#include "mpi.h"

const int    nPoints = 10; /* Число узлов сетки на каждый процессор */
const double L    = 200.0; /* Длина стержня */
const double A    = 1.5;
const double maxT = 10.0;  /* Максимальное время */
const double TAU  = 0.0001; /* Шаг интегрирования по времени */
const double a2   = 10.0;   /* Коэффициент температуропроводности */

void main(int argc, char ** argv)
{
 int nProcs; /* Число процессоров */
 int MyProcID; /* Номер текущего процессора */
 double T[nPoints]; /* Старые значения температуры в узлах сетки */
 double T1[nPoints]; /* Новые значения температуры в узлах сетки */
 double t = 0.0; /* Время */
 double h, k;
 MPI_Status status;
 int Last;
 int i;
 	
 MPI_Init(&argc,&argv);
 MPI_Comm_size(MPI_COMM_WORLD,&nProcs);
 MPI_Comm_rank(MPI_COMM_WORLD,&MyProcID);

 /* Топология типа "труба". Процессоры обмениваются данными по цепочке. */
 /* Число процессоров больше двух. Каждый процессор обрабатывает */
 /* часть всей области. Самая левая часть обрабатывается процессором */
 /* с номером 0. Самая правая -- процессором с номером nProcs-1. */
 /* Части области перекрываются на два узла, чтобы обеспечить непрерывность */
 /* интегрирования. */
 /* Для интегрирования используется явная разностная схема 1-го порядка -- */
 /* схема Эйлера. */
 if (nProcs>1)
    {
     h = L/(nProcs*(nPoints-2)+1); /* Вычисляем шаг сетки */
     k = TAU*a2/h/h; 
     for (i=0; i<nPoints; i++) /* Сначала температура везде равна нулю */
       T[i] = 0.0;
     while (t<maxT)
      {
       /* Граничное условие в точке X=0. Эта точка принадлежит процессору
          с номером 0. */
       if (MyProcID==0) T[0] = A*(1.0+sin(0.5*t));
       /* Вычисляем новые значения температуры по явной схеме. */
       for (i=1; i<nPoints-1; i++)
         T1[i] = T[i]+k*(T[i-1]-2*T[i]+T[i+1]);
       if (MyProcID<nProcs-1)
          {
           /* Все процессоры, кроме последнего, обмениваются */
           /* данными с соседом справа. */
           MPI_Send(&T1[nPoints-2],1,MPI_DOUBLE,MyProcID+1,1234,MPI_COMM_WORLD);
           MPI_Recv(&T1[nPoints-1],1,MPI_DOUBLE,MyProcID+1,1234,MPI_COMM_WORLD,&status);
          }
       else /* У последнего процессора справа -- граничное условие в точке X=L */
          T1[nPoints-1] = T[nPoints-1];
       if (MyProcID>0)
          {
           /* Все процессоры, кроме первого, обмениваются */
           /* данными с соседом слева. */
           MPI_Recv(&T1[0],1,MPI_DOUBLE,MyProcID-1,1234,MPI_COMM_WORLD,&status);
           MPI_Send(&T1[1],1,MPI_DOUBLE,MyProcID-1,1234,MPI_COMM_WORLD);
          }
       else /* У первого процессора слева -- граничное условие в точке X=0 */
          T1[0] = T[0];
       for (i=0; i<nPoints; i++)
         T[i] = T1[i];
       t += TAU;
      }
     /* Процессоры последовательно выводят данные на экран. Сначала выводит */
     /* процессор с номером 0, затем 1 и так далее. */
     if (MyProcID>0)
         MPI_Recv(&i,1,MPI_INT,MyProcID-1,1235,MPI_COMM_WORLD,&status);
     /* Все процессоры, кроме последнего, выводят температуру в своих узлах */
     /* (кроме двух последних узлов). Последний процессор выводит значения */
     /* температуры во всех своих узлах. */
     if (MyProcID<nProcs-1) Last = nPoints-3;
     else Last = nPoints-1;
     for (i=0; i<=Last; i++)
       printf("T[%i] = %lf\n",MyProcID*(nPoints-2)+i,T[i]);
     /* Как только процессор выведет свои данные на экран, он посылает */
     /* своему соседу справа разрешение на вывод данных. */
     if (MyProcID<nProcs-1)
         MPI_Ssend(&i,1,MPI_INT,MyProcID+1,1235,MPI_COMM_WORLD);
    }
 else
    printf("Должно быть 2 или больше процессоров\n");

 MPI_Finalize();
}
