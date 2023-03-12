// Пример, способный дать выигрыш по времени при параллельной работе

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#include <string>
#include <algorithm>
#include "transacted.h"

using namespace std;

const int n = 1024; // Размер массива
const int max_length = 400; // Максимальная длина строки
const int min_chunk_size = n/4; // Минимальный размер распараллеливаемого чанка

string from; // Опорная строка для вычисления метрики Левенштейна
int chunk_size = n; // Максимальный размер нераспараллеливаемого чанка

int Levenstein(const string & string1, const string & string2) {
	int diff;
	int m[max_length+1][max_length+1];
	for (int i = 0; i <= string1.length(); i++)
		m[i][0] = i;
	for (int j = 0; j <= string2.length(); j++)
		m[0][j] = j;

	for (int i = 1; i <= string1.length(); i++) {
		for (int j = 1; j <= string2.length(); j++) {
			if (string1[i-1] == string2[j-1]) diff = 0;
			else diff = 1;
			m[i][j] = min(min(m[i-1][j]+1, m[i][j-1]+1), m[i-1][j-1]+diff);
		}
	}
	return m[string1.length()][string2.length()];
}

class Qsort {
protected:
  TArray<string> * M;
public:
  Qsort(int nthreads) {
	M = new TArray<string>(n);
  }
  ~Qsort() {
	delete M;
  }
  void put(int n, string * _M) {
	for (int i = 0; i < n; i++)
		(*M)[i] = _M[i];
  }
  void get(int n, string * _M) {
	for (int i = 0; i < n; i++)
		_M[i] = (*M)[i];
  }
};

class Runner : public TQueuedObj<Qsort> {
public:
  Runner(int nthreads) : TQueuedObj<Qsort>(nthreads) { }

  void step(int left, int right, int * pleft_i, int * pright_i) {
	*pleft_i = left, *pright_i = right; // Счетчики слева и справа
	int avr = Levenstein(from, (*M)[(left + right)/2]);
	if (left == right) return; // Массив из одного элемента не сортируется
	// Переставляем элементы относительно avr
	while (*pleft_i <= *pright_i) {
		while (Levenstein(from,(*M)[*pleft_i]) < avr) (*pleft_i)++; // Ищем слева больший или равный элемент
		while (Levenstein(from,(*M)[*pright_i]) > avr) (*pright_i)--; // Ищем справа меньший или равный элемент
		if (*pleft_i <= *pright_i) { // Если нашли такие элементы
			// то меняем их местами
			if (Levenstein(from,(*M)[*pleft_i]) > Levenstein(from,(*M)[*pright_i])) {
				string a = (*M)[*pleft_i];
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
	if (r - l < chunk_size) {
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

string randomstr() {
	int n = rand() % max_length;
	string result;
	result.resize(n);
	for (int i = 0; i < n; i++)
		result[i] = 'a' + rand() % ('z' - 'a' + 1);
	return result;
}

int main(int argc, char ** argv) {
	string * M; // Массив
	int i; // Счетчик
	int np = 4;
	if (argc > 1) sscanf(argv[1], "%i", &np);
	// Выделяем память
	M = new string[n];
	srand((unsigned int) time(NULL));
	// Заполняем опорный элемент
	from = randomstr();
	printf("Parallelize (0/1)?");
	scanf("%i", &i);
	chunk_size = i ? min_chunk_size : n;
	// Заполняем массив
	for (i = 0; i < n; i++)
		M[i] = randomstr();
	// Сортируем массив по неубыванию
	set_jobs_mode(true);
	double t0 = omp_get_wtime();
	Runner obj(np);
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
	delete[] M;
	return 0;
}