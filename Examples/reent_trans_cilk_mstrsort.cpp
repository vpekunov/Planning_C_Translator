// ������, ��������� ���� ������� �� ������� ��� ������������ ������

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#include <string>
#include <algorithm>

#include "transacted.h"

using namespace std;

const int n = 2048; // ������ ������� (������� ������!)
const int max_length = 300; // ������������ ����� ������
const int min_chunk_size = n/4; // ����������� ������ ������������������� �����

string from; // ������� ������ ��� ���������� ������� �����������
int chunk_size = n; // ������������ ������ ��������������������� �����

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

class Msort {
protected:
  TArray<string> * M;
public:
  Msort(int nthreads) {
	M = new TArray<string>(n);
  }
  ~Msort() {
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

class Runner : public TQueuedObj<Msort> {
public:
  Runner(int nthreads) : TQueuedObj<Msort>(nthreads) { }

  void merge(int i1, int i2, int j1, int j2) {
	string M1[n];
	int k = 0; // ������� ��������� ������������� ���������
	int n = (i2-i1+1) + (j2-j1+1); // ������� ����� ������ ���������
	int start = i1; // ������ ������ ����� � ������� M
	while (i1 <= i2 || j1 <= j2)
		if (j1 > j2 || i1 <= i2 && Levenstein(from,(*M)[i1]) < Levenstein(from,(*M)[j1])) { // ���� � ����� [j1..j2] ��������� �������� ��� M[i1] < M[j1]
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
	if (r - l < chunk_size) {
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

string randomstr() {
	int n = rand() % max_length;
	string result;
	result.resize(n);
	for (int i = 0; i < n; i++)
		result[i] = 'a' + rand() % ('z' - 'a' + 1);
	return result;
}

int main() {
	string * M; // ������
	int i; // �������
	// �������� ������
	M = new string[n];
	srand((unsigned int) time(NULL));
	// ��������� ������� �������
	from = randomstr();
	printf("Parallelize (0/1)?");
	scanf("%i", &i);
	chunk_size = i ? min_chunk_size : n;
	// ��������� ������
	for (i = 0; i < n; i++)
		M[i] = randomstr();
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
	delete[] M;
	return 0;
}