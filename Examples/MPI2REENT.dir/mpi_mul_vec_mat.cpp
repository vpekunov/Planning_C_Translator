// 08 processors

#ifdef WIN32
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "mpi.h"

int main(int argc, char ** argv) {
	int nProcs; // Количество процессоров
	int MyProcID; // Идентификатор текущего процессора
	int N; // Размер матрицы
	int localN; // Размер локальной для процессора части матрицы

	int * Sizes = NULL; // Массив количеств столбцов на процессорах
	int * Disps = NULL; // Массив смещений начал блоков выходного вектора
	int * _Sizes = NULL; // Массив количеств элементов блоков матрицы на процессорах
	int * _Disps = NULL; // Массив смещений начал блоков матрицы

	float * Vector = NULL; // Вектор
	float * Matrix = NULL; // Матрица, храняящаяся с разверткой по столбцам в одномерный массив
	float * localMatrix = NULL; // Локальная для процессора часть матрицы
	float * OutVector = NULL; // Вектор-результат
	float * localOutVector = NULL; // Локальная для процессора часть вектора-результат

	int i, j, k;

	double _time; // Время работы

	MPI_Init(NULL, NULL); // Инициализируем MPI

	_time = MPI_Wtime(); // Получаем начальное время

	MPI_Comm_size(MPI_COMM_WORLD, &nProcs); // Получаем число процессоров
	MPI_Comm_rank(MPI_COMM_WORLD, &MyProcID); // Получаем номер текущего процессора

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

	Vector = (float *) malloc(N*sizeof(float)); // Выделяем память под вектор

	if (MyProcID == 0) {
		int BaseN; // Базовый размер (количество столбцов) блока на одном процессоре
		int RestN; // Остаток от деления матрицы нв блоки -- распределяется по одному между процессорами

		Matrix = (float *) malloc(N*N*sizeof(float)); // Выделяем память под матрицу
		OutVector = (float *) malloc(N*sizeof(float)); // Выделяем память под выходной вектор
		Sizes  = (int *) malloc(N*sizeof(int)); // Выделяем память под массив количеств столбцов
		Disps = (int *) malloc(N*sizeof(int)); // Выделяем память под массив смещений началов блоков выходного вектора
		_Sizes = (int *) malloc(N*sizeof(int)); // Выделяем память под массив количеств элементов блоков матрицы
		_Disps = (int *) malloc(N*sizeof(int)); // Выделяем память под массив смещений началов блоков матрицы
		// Вычисляем размеры блоков матрицы для процессоров
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
	// Процессор 0 рассылает всем процессорам их значения размера блока матрицы
	// Массив Sizes рассылается по одному элементу в переменные localN
	MPI_Scatter(Sizes, 1, MPI_INT, &localN, 1, MPI_INT, 0, MPI_COMM_WORLD);

	// Нулевой процессор инициализирует данные
	if (MyProcID == 0) {
		// Инициализируем генератор случайных чисел значением счетчика времени
		srand((unsigned int) time(NULL));
		// Инициализируем вектор и матрицу
		for (i = 0; i < N; i++) {
			Vector[i] = 1.0f*rand()/RAND_MAX;
			for (j = 0; j < N; j++)
				Matrix[i*N + j] = 1.0f*rand()/RAND_MAX;
		}
	}

	// Нулевой процессор рассылает всем вектор
	MPI_Bcast(Vector, N, MPI_FLOAT, 0, MPI_COMM_WORLD);

	localMatrix = (float *) malloc(localN*N*sizeof(float));
	localOutVector = (float *) malloc(localN*sizeof(float));

	// Нулевой процессор рассылает фрагменты матрицы
	MPI_Scatterv(Matrix, _Sizes, _Disps, MPI_FLOAT, localMatrix, localN*N, MPI_FLOAT, 0, MPI_COMM_WORLD);

	// Умножение вектора на фрагмент матрицы
	for (i = 0; i < localN; i++) {
		localOutVector[i] = 0.0f;
		for (j = 0; j < N; j++)
			localOutVector[i] += Vector[j]*localMatrix[i*N + j];
	}

	// Нулевой процессор собирает с прочих процессоров фрагменты выходного вектора
	MPI_Gatherv(localOutVector, localN, MPI_FLOAT, OutVector, Sizes, Disps, MPI_FLOAT, 0, MPI_COMM_WORLD);

	// Выводим результат в файл
	if (MyProcID == 0) {
		FILE * _OUT = fopen("output.txt", "w+t");
		if (_OUT) {
			for (i = 0; i < N; i++)
				fprintf(_OUT, "%f ", OutVector[i]);
			fprintf(_OUT, "\n");
			fclose(_OUT);
		}
	}

	// Освобождаем память
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