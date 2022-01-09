#ifdef WIN32
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "mpi.h"

int main(int argc, char ** argv) {
	int nProcs; // ���������� �����������
	int MyProcID; // ������������� �������� ����������
	int N; // ������ �������
	int localN; // ������ ��������� ��� ���������� ����� �������

	int * Sizes = NULL; // ������ ��������� �������� �� �����������
	int * Disps = NULL; // ������ �������� ����� ������ ��������� �������
	int * _Sizes = NULL; // ������ ��������� ��������� ������ ������� �� �����������
	int * _Disps = NULL; // ������ �������� ����� ������ �������

	float * Vector = NULL; // ������
	float * Matrix = NULL; // �������, ����������� � ���������� �� �������� � ���������� ������
	float * localMatrix = NULL; // ��������� ��� ���������� ����� �������
	float * OutVector = NULL; // ������-���������
	float * localOutVector = NULL; // ��������� ��� ���������� ����� �������-���������

	int i, j, k;

	double _time; // ����� ������

	MPI_Init(NULL, NULL); // �������������� MPI

	_time = MPI_Wtime(); // �������� ��������� �����

	MPI_Comm_size(MPI_COMM_WORLD, &nProcs); // �������� ����� �����������
	MPI_Comm_rank(MPI_COMM_WORLD, &MyProcID); // �������� ����� �������� ����������

	if (argc < 2) {
		if (MyProcID == 0)
			printf("Usage: mul_vec_mat <size of matrix>\n");
		MPI_Finalize();
		return -1;
	}

	N = atoi(argv[1]);

	if (N < 100) {
		if (MyProcID == 0)
			printf("Size of matrix must be equal to or more than 100\n");
		MPI_Finalize();
		return -2;
	}

	Vector = (float *) malloc(N*sizeof(float)); // �������� ������ ��� ������

	if (MyProcID == 0) {
		int BaseN; // ������� ������ (���������� ��������) ����� �� ����� ����������
		int RestN; // ������� �� ������� ������� �� ����� -- �������������� �� ������ ����� ������������

		Matrix = (float *) malloc(N*N*sizeof(float)); // �������� ������ ��� �������
		OutVector = (float *) malloc(N*sizeof(float)); // �������� ������ ��� �������� ������
		Sizes  = (int *) malloc(N*sizeof(int)); // �������� ������ ��� ������ ��������� ��������
		Disps = (int *) malloc(N*sizeof(int)); // �������� ������ ��� ������ �������� ������� ������ ��������� �������
		_Sizes = (int *) malloc(N*sizeof(int)); // �������� ������ ��� ������ ��������� ��������� ������ �������
		_Disps = (int *) malloc(N*sizeof(int)); // �������� ������ ��� ������ �������� ������� ������ �������
		// ��������� ������� ������ ������� ��� �����������
		BaseN = N / nProcs;
		RestN = N % nProcs;

		j = 0;
		k = 0;
		for (i = 0; i < nProcs; i++) {
			Sizes[i] = BaseN;
			if (i < RestN)
				Sizes[i]++;
			Disps[i] = k;
			k += Sizes[i];
			_Sizes[i] = Sizes[i]*N;
			_Disps[i] = j;
			j += _Sizes[i];
		}
	}
	// ��������� 0 ��������� ���� ����������� �� �������� ������� ����� �������
	// ������ Sizes ����������� �� ������ �������� � ���������� localN
	MPI_Scatter(Sizes, 1, MPI_INT, &localN, 1, MPI_INT, 0, MPI_COMM_WORLD);

	// ������� ��������� �������������� ������
	if (MyProcID == 0) {
		// �������������� ��������� ��������� ����� ��������� �������� �������
		srand((unsigned int) time(NULL));
		// �������������� ������ � �������
		for (i = 0; i < N; i++) {
			Vector[i] = 1.0f*rand()/RAND_MAX;
			for (j = 0; j < N; j++)
				Matrix[i*N + j] = 1.0f*rand()/RAND_MAX;
		}
	}

	// ������� ��������� ��������� ���� ������
	MPI_Bcast(Vector, N, MPI_FLOAT, 0, MPI_COMM_WORLD);

	localMatrix = (float *) malloc(localN*N*sizeof(float));
	localOutVector = (float *) malloc(localN*sizeof(float));

	// ������� ��������� ��������� ��������� �������
	MPI_Scatterv(Matrix, _Sizes, _Disps, MPI_FLOAT, localMatrix, localN*N, MPI_FLOAT, 0, MPI_COMM_WORLD);

	// ��������� ������� �� �������� �������
	for (i = 0; i < localN; i++) {
		localOutVector[i] = 0.0f;
		for (j = 0; j < N; j++)
			localOutVector[i] += Vector[j]*localMatrix[i*N + j];
	}

	// ������� ��������� �������� � ������ ����������� ��������� ��������� �������
	MPI_Gatherv(localOutVector, localN, MPI_FLOAT, OutVector, Sizes, Disps, MPI_FLOAT, 0, MPI_COMM_WORLD);

	// ������� ��������� � ����
	if (MyProcID == 0) {
		FILE * _OUT = fopen("output.txt", "w+t");
		if (_OUT) {
			for (i = 0; i < N; i++)
				fprintf(_OUT, "%f ", OutVector[i]);
			fprintf(_OUT, "\n");
			fclose(_OUT);
		}
	}

	// ����������� ������
	free(Sizes);
	free(Disps);
	free(_Sizes);
	free(_Disps);

	free(Vector);
	free(Matrix);
	free(localMatrix);
	free(OutVector);
	free(localOutVector);

	_time = MPI_Wtime() - _time;

	if (MyProcID == 0)
		printf("%lf seconds elapsed\n", _time);

	MPI_Finalize();

	return 0;
}