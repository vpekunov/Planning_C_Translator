#include <stdio.h>
#include <math.h>
#include "mpi.h"

const double maxT = 1.0; /* Максимальное время */
const double TAU  = 0.01; /* Шаг интегрирования по времени */

/* Начальные значения переменных. */
const double Y1_0 = 3.0;
const double Y2_0 = 3.0;
const double Y3_0 = 3.0;

void main(int argc, char ** argv)
{
 int nProcs; /* Количество процессоров */
 int MyProcID; /* Идентификатор текущего процессора */
 double Y[3];  /* Значения y1,y2,y3 перед очередной итерацией */
 double Yp[3]; /* Значения прогноза y1,y2,y3 */
 double F[3];  /* Значения правых частей систему ОДУ в точке прогноза */
 double Fp;
 double t = 0.0; /* Текущее время интегрирования */
 MPI_Status status;
 int i,j;
 	
 MPI_Init(&argc,&argv);
 MPI_Comm_size(MPI_COMM_WORLD,&nProcs);
 MPI_Comm_rank(MPI_COMM_WORLD,&MyProcID);

 /* Используется только три процессора. Каждый из них интегрирует */
 /* одно из уравнений системы. Процессор номер 0 -- первое уравнение */
 /* и так далее. */
 /* Схема обменов "клика" -- каждый процессор обменивается данными с каждым. */
 /* Каждый процессор передает остальным сначала прогнозируемое */
 /* значение той переменной, которую он вычисляет, а потом передает */
 /* новое (скорректированное) значение той же переменной. */
 if (nProcs>2)
    {
     if (MyProcID<3)
      { /* Начальные значения переенных */
       Y[0] = Y1_0;
       Y[1] = Y2_0;
       Y[2] = Y3_0;

       while (t<maxT)
        {
         /* Каждый процессор вычисляет прогноз по своей переменной */
         if (MyProcID==0)
            {
             F[0]  = -Y[1]+Y[0]*Y[2]/sqrt(Y[0]*Y[0]+Y[1]*Y[1]);
             Yp[0] = Y[0]+TAU*F[0];
            }
         if (MyProcID==1)
            {
             F[1]  = Y[0]-Y[0]*Y[2]/sqrt(Y[0]*Y[0]+Y[1]*Y[1]);
             Yp[1] = Y[1]+TAU*F[1];
            }
         if (MyProcID==2)
            {
             F[2]  = Y[0]/sqrt(Y[0]*Y[0]+Y[1]*Y[1]);
             Yp[2] = Y[2]+TAU*F[2];
            }
         for (i=0; i<3; i++)
           if (i==MyProcID)
              { /* Каждый процессор посылает прогнозируемое значение */
                /* своей переменной всем остальным процессорам */
               for (j=0; j<3; j++)
                 if (j!=MyProcID)
                    MPI_Send(&Yp[i],1,MPI_DOUBLE,j,1234,MPI_COMM_WORLD);
              }
           else /* Каждый процессор принимает у остальных процессоров */
                /* прогнозируемые значения их переменных */
             MPI_Recv(&Yp[i],1,MPI_DOUBLE,i,1234,MPI_COMM_WORLD,&status);
         /* Каждый процессор вычисляет скорректированное значение по своей */
         /* переменной */
         if (MyProcID==0)
            {
             Fp    = -Yp[1]+Yp[0]*Yp[2]/sqrt(Yp[0]*Yp[0]+Yp[1]*Yp[1]);
             Y[0] += TAU*(F[0]+Fp)/2.0;
            }
         if (MyProcID==1)
            {
             Fp    = Yp[0]-Yp[0]*Yp[2]/sqrt(Yp[0]*Yp[0]+Yp[1]*Yp[1]);
             Y[1] += TAU*(F[1]+Fp)/2.0;
            }
         if (MyProcID==2)
            {
             Fp    = Yp[0]/sqrt(Yp[0]*Yp[0]+Yp[1]*Yp[1]);
             Y[2] += TAU*(F[2]+Fp)/2.0;
            }
         /* Точно такой же обмен. Процессоры обмениваются уже скорректированными */
         /* значениями. */
         for (i=0; i<3; i++)
           if (i==MyProcID)
              {
               for (j=0; j<3; j++)
                 if (j!=MyProcID)
                    MPI_Send(&Y[i],1,MPI_DOUBLE,j,1234,MPI_COMM_WORLD);
              }
           else
             MPI_Recv(&Y[i],1,MPI_DOUBLE,i,1234,MPI_COMM_WORLD,&status);

         t += TAU;
        }
       /* Каждый процессор выводит на экран результат по своей переменной */
       printf("Y[%i] = %lf\n",MyProcID+1,Y[MyProcID]);
      }
    }
 else
    printf("Должно быть 3 или больше процессоров\n");

 MPI_Finalize();
}
