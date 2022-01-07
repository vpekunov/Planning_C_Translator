#include <stdio.h>
#include <math.h>
#include "mpi.h"

const double maxT = 1.0; /* ���ᨬ��쭮� �६� */
const double TAU  = 0.01; /* ��� ��⥣�஢���� �� �६��� */

/* ��砫�� ���祭�� ��६�����. */
const double Y1_0 = 3.0;
const double Y2_0 = 3.0;
const double Y3_0 = 3.0;

void main(int argc, char ** argv)
{
 int nProcs; /* ������⢮ �����஢ */
 int MyProcID; /* �����䨪��� ⥪�饣� ������ */
 double Y[3];  /* ���祭�� y1,y2,y3 ��। ��।��� ���樥� */
 double Yp[3]; /* ���祭�� �ண���� y1,y2,y3 */
 double F[3];  /* ���祭�� �ࠢ�� ��⥩ ��⥬� ��� � �窥 �ண���� */
 double Fp;
 double t = 0.0; /* ����饥 �६� ��⥣�஢���� */
 MPI_Status status;
 int i,j;
 	
 MPI_Init(&argc,&argv);
 MPI_Comm_size(MPI_COMM_WORLD,&nProcs);
 MPI_Comm_rank(MPI_COMM_WORLD,&MyProcID);

 /* �ᯮ������ ⮫쪮 �� ������. ����� �� ��� ��⥣���� */
 /* ���� �� �ࠢ����� ��⥬�. ������ ����� 0 -- ��ࢮ� �ࠢ����� */
 /* � ⠪ �����. */
 /* �奬� ������� "�����" -- ����� ������ ������������ ����묨 � �����. */
 /* ����� ������ ��।��� ��⠫�� ᭠砫� �ண�����㥬�� */
 /* ���祭�� ⮩ ��६�����, ������ �� ������, � ��⮬ ��।��� */
 /* ����� (᪮�४�஢�����) ���祭�� ⮩ �� ��६�����. */
 if (nProcs>2)
    {
     if (MyProcID<3)
      { /* ��砫�� ���祭�� ��॥���� */
       Y[0] = Y1_0;
       Y[1] = Y2_0;
       Y[2] = Y3_0;

       while (t<maxT)
        {
         /* ����� ������ ������ �ண��� �� ᢮�� ��६����� */
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
              { /* ����� ������ ���뫠�� �ண�����㥬�� ���祭�� */
                /* ᢮�� ��६����� �ᥬ ��⠫�� �����ࠬ */
               for (j=0; j<3; j++)
                 if (j!=MyProcID)
                    MPI_Send(&Yp[i],1,MPI_DOUBLE,j,1234,MPI_COMM_WORLD);
              }
           else /* ����� ������ �ਭ����� � ��⠫��� �����஢ */
                /* �ண�����㥬� ���祭�� �� ��६����� */
             MPI_Recv(&Yp[i],1,MPI_DOUBLE,i,1234,MPI_COMM_WORLD,&status);
         /* ����� ������ ������ ᪮�४�஢����� ���祭�� �� ᢮�� */
         /* ��६����� */
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
         /* ��筮 ⠪�� �� �����. ������� ������������ 㦥 ᪮�४�஢���묨 */
         /* ���祭�ﬨ. */
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
       /* ����� ������ �뢮��� �� �࠭ १���� �� ᢮�� ��६����� */
       printf("Y[%i] = %lf\n",MyProcID+1,Y[MyProcID]);
      }
    }
 else
    printf("������ ���� 3 ��� ����� �����஢\n");

 MPI_Finalize();
}
