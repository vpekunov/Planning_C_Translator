#include <stdio.h>
#include <math.h>
#include "mpi.h"

const double X0[4] = {3.0,-1.0,0.0,1.0}; /* ��砫쭠� �窠 ���᪠ */
const double h = 0.005; /* ��� ���᪠ */

const double Eps = 1E-4; /* ��筮��� ���� */

void main(int argc, char ** argv)
{
 int nProcs; /* ��᫮ �����஢ */
 int MyProcID; /* �����䨪��� ⥪�饣� ������ */
 MPI_Status status;
 double X[4]; /* ������ �窠 */
 double Gr, LGr; /* Gr -- ���祭�� ����� �� ��������� �ࠤ���� */
 double F1;
 int WorkFlag = 1; /* �ਧ��� �த������� ࠡ��� */
 int i;
 	
 MPI_Init(&argc,&argv);
 MPI_Comm_size(MPI_COMM_WORLD,&nProcs);
 MPI_Comm_rank(MPI_COMM_WORLD,&MyProcID);

 /* ��⮤ �ࠤ���⭮�� ��᪠. */
 /* �ᯮ������ �奬� ������� ⨯� "������". ������ ������ ������������ */
 /* ����묨 � ࠡ�稬� �����ࠬ�. */
 /* ������ ����� 0 -- ������. �ᯮ������� �� 4 ࠡ��� ������, */
 /* �.�. �ᥣ� �ᯮ������ 5 �����஢. */
 /* ����稥 ������� ������� ���������� ����� �ࠤ����. */
 /* ������ ����� 1 ������ dF/dX1 � ⠪ �����. */
 if (nProcs>=5)
    {
     if (MyProcID==0)
        for (i=0; i<4; i++)
          X[i] = X0[i];
     if (MyProcID<5)
       while (WorkFlag)
        if (MyProcID==0)
           {
            /* ���뫠�� ࠡ�稬 �����ࠬ ���न���� ⥪�饩 �窨 */
            for (i=1; i<5; i++)
              MPI_Send(X,4,MPI_DOUBLE,i,1234,MPI_COMM_WORLD);
            LGr = 0.0;
            /* ����砥� �� ࠡ��� �����஢ ���������� �ࠤ���� */
            for (i=1; i<5; i++)
              {
               MPI_Recv(&Gr,1,MPI_DOUBLE,i,1234,MPI_COMM_WORLD,&status);
               /* ������ 蠣 �� ����� �� ��६����� � ���ࠢ����� ��⨣ࠤ����. */
               X[i-1] -= h*Gr;
               LGr += Gr*Gr; /* � LGr ����������� ����� ����� �ࠤ���� */
              }
            /* ��⠥� ���祭�� 楫���� �㭪樨 � ����� �窥 */
            F1 = pow(X[0]+10.0*X[1],2.0)+5.0*pow(X[0]-X[3],2.0)+
                 pow(X[1]-2.0*X[2],4.0)+10.0*pow(X[0]-X[3],4.0);
            printf("F(%lf,%lf,%lf,%lf)=%lf\n",X[0],X[1],X[2],X[3],F1);
            if (sqrt(LGr)<=Eps) /* �᫨ ����� �ࠤ���� ����� �筮�� -- ����� */
               WorkFlag = 0;
            /* ����뫠�� ࠡ�稬 㪠����� �த������ ��� �������� ࠡ��� */
            for (i=1; i<5; i++)
              MPI_Send(&WorkFlag,1,MPI_INT,i,1234,MPI_COMM_WORLD);
           }
        else
           {
            /* ����稩 ������ ����砥� �� �������� ���न���� ⥪�饩 �窨 */
            MPI_Recv(X,4,MPI_DOUBLE,0,1234,MPI_COMM_WORLD,&status);
            /* ����� ࠡ�稩 ������ ᢮� ���������� �ࠤ���� */
            if (MyProcID==1) /* dF/dX1 */
               Gr = 2.0*(X[0]+10.0*X[1])+10.0*(X[0]-X[3])+40.0*pow(X[0]-X[3],3.0);
            else if (MyProcID==2) /* dF/dX2 */
               Gr = 20.0*(X[0]+10.0*X[1])+4.0*pow(X[1]-2.0*X[2],3.0);
            else if (MyProcID==3) /* dF/dX3 */
               Gr = -8.0*pow(X[1]-2.0*X[2],3.0);
            else /* dF/dX4 */
               Gr = -10.0*(X[0]-X[3])-40.0*pow(X[0]-X[3],3.0);
            /* ���뫠�� ���᫥���� ���祭�� ���������� �ࠤ���� �������� ������� */
            MPI_Send(&Gr,1,MPI_DOUBLE,0,1234,MPI_COMM_WORLD);
            /* ����砥� 㪠����� �த������ ��� �������� ࠡ��� */
            MPI_Recv(&WorkFlag,1,MPI_INT,0,1234,MPI_COMM_WORLD,&status);
           }
    }
 else
    printf("������ ���� 5 ��� ����� �����஢\n");

 MPI_Finalize();
}