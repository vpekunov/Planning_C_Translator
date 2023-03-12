#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#include "transacted.h"

const int n = 10000; // Размер массива

class Qsort {
protected:
  TArray<int> * M;
public:
  Qsort(int nthreads) {
	M = new TArray<int>(n);
  }
  ~Qsort() {
	delete M;
  }
  void put(int n, int * _M) {
	for (int i = 0; i < n; i++)
		(*M)[i] = _M[i];
  }
  void get(int n, int * _M) {
	for (int i = 0; i < n; i++)
		_M[i] = (*M)[i];
  }
};

class Runner : public TQueuedObj<Qsort> {
public:
  Runner(int nthreads) : TQueuedObj<Qsort>(nthreads) { }

  void step(int left, int right, int * pleft_i, int * pright_i) {
	*pleft_i = left, *pright_i = right; // Счетчики слева и справа
	int avr = (*M)[(left + right)/2];
	if (left == right) return; // Массив из одного элемента не сортируется
	// Переставляем элементы относительно avr
	while (*pleft_i <= *pright_i) {
		while ((*M)[*pleft_i] < avr) (*pleft_i)++; // Ищем слева больший или равный элемент
		while ((*M)[*pright_i] > avr) (*pright_i)--; // Ищем справа меньший или равный элемент
		if (*pleft_i <= *pright_i) { // Если нашли такие элементы
			// то меняем их местами
			if ((*M)[*pleft_i] > (*M)[*pright_i]) {
				int a = (*M)[*pleft_i];
				(*M)[*pleft_i] = (*M)[*pright_i];
				(*M)[*pright_i] = a;
			}
			(*pleft_i)++;
			(*pright_i)--;
		}
	}
  }

  void par_sort(int * left, int * right) {
	int l = *left;
	int r = *right;
	if (l >= r) return;
	int * pleft_i = new int;
	int * pright_i = new int;
	if (r - l < 1000) {
		step(l, r, pleft_i, pright_i);
		par_sort(left, pright_i);
		par_sort(pleft_i, right);
	} else {
		int pid = cilk_spawn step(=l, =r, =pleft_i, =pright_i);
		int n1=cilk_spawn(1,&pid) par_sort(=left, =pright_i);
		int n2=cilk_spawn(1,&pid) par_sort(=pleft_i, =right);
	}
  }
};

int main() {
	int * M; // Массив
	int i; // Счетчик
	// Выделяем память
	M = (int *) malloc(n*sizeof(int));
	srand((unsigned int) time(NULL));
	// Заполняем массив
	for (i = 0; i < n; i++)
		M[i] = rand();
	// Сортируем массив по неубыванию
	set_jobs_mode(true);
	double t0 = omp_get_wtime();
	Runner obj(omp_get_num_procs());
	obj.put(n, M);
	int l = 0;
	int r = n-1;
	obj.par_sort(&l, &r);
	obj.cilk_sync;
	obj.get(n, M);
	printf("Elapsed time = %lf\n", omp_get_wtime() - t0);
	// Выводим результат
	printf("\n");
	// Освобождаем память
	free(M);
	return 0;
}