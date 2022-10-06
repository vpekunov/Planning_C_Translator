#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#include "transacted.h"

const int n = 8192; // ������ ������� (������� ������!)

class Msort {
protected:
  TArray<int> * M;
public:
  Msort(int nthreads) {
	M = new TArray<int>(n);
  }
  ~Msort() {
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

class Runner : public TQueuedObj<Msort> {
public:
  Runner(int nthreads) : TQueuedObj<Msort>(nthreads) { }

  void merge(int i1, int i2, int j1, int j2) {
	int M1[n];
	int k = 0; // ������� ��������� ������������� ���������
	int n = (i2-i1+1) + (j2-j1+1); // ������� ����� ������ ���������
	int start = i1; // ������ ������ ����� � ������� M
	while (i1 <= i2 || j1 <= j2)
		if (j1 > j2 || i1 <= i2 && (*M)[i1] < (*M)[j1]) { // ���� � ����� [j1..j2] ��������� �������� ��� M[i1] < M[j1]
			M1[k++] = (*M)[i1]; // �� ����� �������� �� [i1..i2]
			i1++;
		} else { // ����� ����� �������� �� [j1..j2]
			M1[k++] = (*M)[j1];
			j1++;
		}
	// �������� ������ �������� ������� � ������ M
	for (k = 0; k < n; k++)
		(*M)[start+k] = M1[k];
  }

  void par_sort(int l, int r) {
	if (l == r) return;
	int m1 = (l+r)/2;
	int m2 = m1+1;
	if (r - l < 3000) {
		par_sort(l, m1);
		par_sort(m2, r);
		merge(l, m1, m2, r);
	} else {
		int * pids = new int[2];
		pids[0] = cilk_spawn par_sort(=l, =m1);
		pids[1] = cilk_spawn par_sort(=m2, =r);
		this->cilk_spawn(2,pids) merge(=l, =m1, =m2, =r);
	}
  }
};

int main() {
	int * M; // ������
	int i; // �������
	// �������� ������
	M = (int *) malloc(n*sizeof(int));
	srand((unsigned int) time(NULL));
	// ��������� ������
	for (i = 0; i < n; i++)
		M[i] = rand();
	// ��������� ������ �� ����������
	set_jobs_mode(true);
	double t0 = omp_get_wtime();
	Runner obj(omp_get_num_procs());
	obj.put(n, M);
	obj.par_sort(0, n-1);
	obj.cilk_sync;
	obj.get(n, M);
	printf("Elapsed time = %lf\n", omp_get_wtime() - t0);
	// ������� ���������
	printf("\n");
	// ����������� ������
	free(M);
	return 0;
}