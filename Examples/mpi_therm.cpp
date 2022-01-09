#include <stdio.h>
#include <math.h>
#include "mpi.h"

const int    nPoints = 10; /* ��᫮ 㧫�� �⪨ �� ����� ������ */
const double L    = 200.0; /* ����� ��ভ� */
const double A    = 1.5;
const double maxT = 10.0;  /* ���ᨬ��쭮� �६� */
const double TAU  = 0.0001; /* ��� ��⥣�஢���� �� �६��� */
const double a2   = 10.0;   /* �����樥�� ⥬�����ய஢������ */

void main(int argc, char ** argv)
{
 int nProcs; /* ��᫮ �����஢ */
 int MyProcID; /* ����� ⥪�饣� ������ */
 double T[nPoints]; /* ���� ���祭�� ⥬������� � 㧫�� �⪨ */
 double T1[nPoints]; /* ���� ���祭�� ⥬������� � 㧫�� �⪨ */
 double t = 0.0; /* �६� */
 double h, k;
 MPI_Status status;
 int Last;
 int i;
 	
 MPI_Init(&argc,&argv);
 MPI_Comm_size(MPI_COMM_WORLD,&nProcs);
 MPI_Comm_rank(MPI_COMM_WORLD,&MyProcID);

 /* ��������� ⨯� "��㡠". ������� ������������ ����묨 �� 楯�窥. */
 /* ��᫮ �����஢ ����� ����. ����� ������ ��ࠡ��뢠�� */
 /* ���� �ᥩ ������. ����� ����� ���� ��ࠡ��뢠���� �����஬ */
 /* � ����஬ 0. ����� �ࠢ�� -- �����஬ � ����஬ nProcs-1. */
 /* ���� ������ ��४�뢠���� �� ��� 㧫�, �⮡� ���ᯥ��� �����뢭���� */
 /* ��⥣�஢����. */
 /* ��� ��⥣�஢���� �ᯮ������ �� ࠧ���⭠� �奬� 1-�� ���浪� -- */
 /* �奬� �����. */
 if (nProcs>1)
    {
     h = L/(nProcs*(nPoints-2)+1); /* ����塞 蠣 �⪨ */
     k = TAU*a2/h/h; 
     for (i=0; i<nPoints; i++) /* ���砫� ⥬������ ����� ࠢ�� ��� */
       T[i] = 0.0;
     while (t<maxT)
      {
       /* �࠭�筮� �᫮��� � �窥 X=0. �� �窠 �ਭ������� �������
          � ����஬ 0. */
       if (MyProcID==0) T[0] = A*(1.0+sin(0.5*t));
       /* ����塞 ���� ���祭�� ⥬������� �� �� �奬�. */
       for (i=1; i<nPoints-1; i++)
         T1[i] = T[i]+k*(T[i-1]-2*T[i]+T[i+1]);
       if (MyProcID<nProcs-1)
          {
           /* �� �������, �஬� ��᫥�����, ������������ */
           /* ����묨 � �ᥤ�� �ࠢ�. */
           MPI_Send(&T1[nPoints-2],1,MPI_DOUBLE,MyProcID+1,1234,MPI_COMM_WORLD);
           MPI_Recv(&T1[nPoints-1],1,MPI_DOUBLE,MyProcID+1,1234,MPI_COMM_WORLD,&status);
          }
       else /* � ��᫥����� ������ �ࠢ� -- �࠭�筮� �᫮��� � �窥 X=L */
          T1[nPoints-1] = T[nPoints-1];
       if (MyProcID>0)
          {
           /* �� �������, �஬� ��ࢮ��, ������������ */
           /* ����묨 � �ᥤ�� ᫥��. */
           MPI_Recv(&T1[0],1,MPI_DOUBLE,MyProcID-1,1234,MPI_COMM_WORLD,&status);
           MPI_Send(&T1[1],1,MPI_DOUBLE,MyProcID-1,1234,MPI_COMM_WORLD);
          }
       else /* � ��ࢮ�� ������ ᫥�� -- �࠭�筮� �᫮��� � �窥 X=0 */
          T1[0] = T[0];
       for (i=0; i<nPoints; i++)
         T[i] = T1[i];
       t += TAU;
      }
     /* ������� ��᫥����⥫쭮 �뢮��� ����� �� �࠭. ���砫� �뢮��� */
     /* ������ � ����஬ 0, ��⥬ 1 � ⠪ �����. */
     if (MyProcID>0)
         MPI_Recv(&i,1,MPI_INT,MyProcID-1,1235,MPI_COMM_WORLD,&status);
     /* �� �������, �஬� ��᫥�����, �뢮��� ⥬������� � ᢮�� 㧫�� */
     /* (�஬� ���� ��᫥���� 㧫��). ��᫥���� ������ �뢮��� ���祭�� */
     /* ⥬������� �� ��� ᢮�� 㧫��. */
     if (MyProcID<nProcs-1) Last = nPoints-3;
     else Last = nPoints-1;
     for (i=0; i<=Last; i++)
       printf("T[%i] = %lf\n",MyProcID*(nPoints-2)+i,T[i]);
     /* ��� ⮫쪮 ������ �뢥��� ᢮� ����� �� �࠭, �� ���뫠�� */
     /* ᢮��� �ᥤ� �ࠢ� ࠧ�襭�� �� �뢮� ������. */
     if (MyProcID<nProcs-1)
         MPI_Ssend(&i,1,MPI_INT,MyProcID+1,1235,MPI_COMM_WORLD);
    }
 else
    printf("������ ���� 2 ��� ����� �����஢\n");

 MPI_Finalize();
}
