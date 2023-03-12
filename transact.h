#ifndef __TRANSACT_H__
#define __TRANSACT_H__

#pragma syntax nocheck

#define split_tune (get_nprocs())

#include <omp.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifdef _MSC_VER
  #include <windows.h>

  #define clock_val(T) T.##QuadPart

  #define get_thread_id GetCurrentThreadId
#else
  #include <unistd.h>
  #include <time.h>
  #include <pthread.h>

  #define LARGE_INTEGER struct timespec

  #define clock_val(T) (T)

  #define get_thread_id pthread_self

  int QueryPerformanceCounter(LARGE_INTEGER * v) {
     clock_gettime(CLOCK_MONOTONIC, v);

     return 1;
  }

  LARGE_INTEGER & operator += (LARGE_INTEGER & op1, const LARGE_INTEGER & op2) {
     op1.tv_sec += op2.tv_sec;
     op1.tv_nsec += op2.tv_nsec;
     if (op1.tv_nsec > 999999999) {
        op1.tv_sec++;
        op1.tv_nsec -= 1000000000;
     }

     return op1;
  }

  LARGE_INTEGER & operator -= (LARGE_INTEGER & op1, const LARGE_INTEGER & op2) {
     op1.tv_sec -= op2.tv_sec;
     if (op1.tv_nsec < op2.tv_nsec) {
        op1.tv_sec--;
        op1.tv_nsec -= op2.tv_nsec;
        op1.tv_nsec += 1000000000;
     } else
        op1.tv_nsec -= op2.tv_nsec;

     return op1;
  }

  long long operator - (const LARGE_INTEGER & op1) {
     LARGE_INTEGER result = { 0 };
     result -= op1;

     return 1000000000LL*result.tv_sec + result.tv_nsec;
  }

  bool operator != (const LARGE_INTEGER & op1, int op2) {
     return op1.tv_sec != op2 || op1.tv_nsec != 0;
  }

  bool operator == (const LARGE_INTEGER & op1, int op2) {
     return op1.tv_sec == op2 && op1.tv_nsec == 0;
  }

  bool operator < (const LARGE_INTEGER & op1, const LARGE_INTEGER & op2) {
     return op1.tv_sec < op2.tv_sec || op1.tv_sec == op2.tv_sec && op1.tv_nsec < op2.tv_nsec;
  }

  bool operator >= (const LARGE_INTEGER & op1, int op2) {
     return 1LL*op1.tv_sec + op1.tv_nsec >= op2;
  }
#endif

#ifndef __REENT__
#include "funnels_atomic.h"
#endif

#include <list>
#include <vector>
#include <map>
#include <stack>
#include <queue>
#include <string>
#include <algorithm>
#include <functional>
#include <iostream>
#include <thread>

using namespace std;

const int __max_procs__ = 256;

class TVar;

omp_lock_t __lock_atomics__;

class TOBJ_STARTER;

typedef struct {
	int preconds[5];
	volatile bool finished;
} __tobj_job;

typedef std::function<void(void)> __page_fun;

map<long long, stack<TOBJ_STARTER *> *> __tobj_this_stack;
vector<__tobj_job *> __tobj_jobs;
bool __use_jobs = false;
omp_lock_t __lock_tobjs__;

void set_jobs_mode(bool use) {
	omp_set_lock(&__lock_tobjs__);
	__use_jobs = use;
	for (auto v : __tobj_jobs) {
		while (!v->finished) {
			omp_unset_lock(&__lock_tobjs__);
			_Yield();
			omp_set_lock(&__lock_tobjs__);
		}
	}
	for (auto v : __tobj_jobs) {
		delete v;
	}
	__tobj_jobs.clear();
	__tobj_jobs.reserve(10000);
	omp_unset_lock(&__lock_tobjs__);
}

class __initializer__ {
public:
  __initializer__() {
    omp_set_nested(1);
    omp_init_lock(&__lock_atomics__);
    omp_init_lock(&__lock_tobjs__);
  }
  virtual ~__initializer__() {
    omp_destroy_lock(&__lock_atomics__);
    omp_destroy_lock(&__lock_tobjs__);
  }
};

__initializer__ __starter__;

class TChannel;

class TVar;

enum { __reader__ = -1, __writer__, __another__ };

typedef struct {
	int __transaction_counter__; // K
	map<int, LARGE_INTEGER> __transaction_timings__[__max_procs__]; // Меньше нуля!
	map<int, LARGE_INTEGER> __transaction_retimings__[__max_procs__]; // Меньше нуля!
	vector<int> __transaction_procs__;
	vector<int> __transaction_misses__;
} __opt_transaction__;

typedef struct __info_transaction__ {
	list<TVar *> __atomics__;

	map<string, pair<TChannel *, TChannel *> > __io__;

	bool working[__max_procs__];
	int job_ids[__max_procs__];
	__page_fun __funs[__max_procs__];
	struct __info_transaction__ * parents[__max_procs__];
	int parent_ids[__max_procs__];

	bool failed[__max_procs__];
	bool __in_transaction__;

	__opt_transaction__ __stat_transaction__;

	int __transaction_procs__[__max_procs__];
} __info_transaction__;

map< long long, string > __map_threads__;

map< string, __info_transaction__ * > __transactions__;

__info_transaction__ * get_transaction(const char * id) {
	map< string, __info_transaction__ * >::iterator it = __transactions__.find(id);

	if (it == __transactions__.end()) {
		__info_transaction__ * new_tr = new __info_transaction__;
		
		new_tr->__in_transaction__ = false;
		new_tr->__stat_transaction__.__transaction_counter__ = -1;
		memset(new_tr->working, 0, sizeof(new_tr->working));
		memset(new_tr->parents, 0, sizeof(new_tr->parents));
		memset(new_tr->parent_ids, 0, sizeof(new_tr->parent_ids));
		for (int i = 0; i < __max_procs__; i++)
			new_tr->__funs[i] = nullptr;
		memset(new_tr->job_ids, 0, sizeof(new_tr->job_ids));
		memset(new_tr->failed, 0, sizeof(new_tr->failed));

		__transactions__[id] = new_tr;

		return new_tr;
	}
	else
		return it->second;
}

__info_transaction__ * get_transaction_by_thread(string & returned_id, bool stop_if_unknown = true) {
	long long thread_id = get_thread_id();
	map< long long, string>::iterator it = __map_threads__.find(thread_id);
	if (it == __map_threads__.end()) {
		if (stop_if_unknown) {
			cout << "Thread " << thread_id << " is not bound to transaction!" << endl;
			exit(-100);
		} else
			return NULL;
	}
	else {
		returned_id = it->second;
		return get_transaction(it->second.c_str());
	}
}

class TOBJ_STARTER {
protected:
   char __this_id[20];
   long long __tid;
   int __nthreads;
private:
   bool check_ways(__info_transaction__ * info, int id, __info_transaction__ * till_info) {
      if (info == NULL) return false;
      if (info == till_info) return true;
      else return check_ways(info->parents[id], info->parent_ids[id], till_info);
   }
public:
   TOBJ_STARTER(int nthreads) {
     __nthreads = nthreads;
     __tid = get_thread_id();
     sprintf(__this_id, "&&%llX", (unsigned long long) this);
     // Помещаем в стек свой this-ptr
     omp_set_lock(&__lock_tobjs__);
     stack<TOBJ_STARTER *> * st = __tobj_this_stack[__tid];
     if (st == NULL)
        __tobj_this_stack[__tid] = st = new stack<TOBJ_STARTER *>();
     st->push(this);
     omp_unset_lock(&__lock_tobjs__);
   }
   // Возвращает идентификатор транзакции текущего объекта
   const char * get_transaction_id() {
     return __this_id;
   }
   virtual void sync(bool sync_children = true) = 0;
   virtual bool join(__page_fun f, int &id, int npreconds = 0, int * preconds = NULL, bool set_join_lock = true) = 0;
   // Не прерывая работу, ставит ее на пересогласование в транзакционном блоке. Если вызван с отличным
   // от NULL параметром = идентификатором базовой транзакции, то ставит на пересогласование все работы
   // от текущей до породивших ее в транзакциях более высокого уровня вплоть до базовой транзакции.
   virtual bool fail_till(const char * __till_id__ = NULL) {
   	__info_transaction__ * till_info;
   	string id;
	int tid = omp_get_thread_num();

   	omp_set_lock(&__lock_atomics__);
   	__info_transaction__ * info = get_transaction(__this_id);
   	if (__till_id__ == NULL)
   		till_info = get_transaction_by_thread(id, false);
   	else
   		till_info = get_transaction(__till_id__);
   	if (!check_ways(info, tid, till_info)) {
   		omp_unset_lock(&__lock_atomics__);
   		return false;
   	} else {
		info->failed[tid] = true;
		while (info != till_info) {
			int id = info->parent_ids[tid];
			info = info->parents[tid];
   			info->failed[id] = true;
			tid = id;
		} while (1);
   		omp_unset_lock(&__lock_atomics__);
   		return true;
   	}
   }
   virtual int  num_free() = 0;
   virtual ~TOBJ_STARTER() {
     // Уничтожаем транзакцию this+ptr -- стираем ее из списка
     omp_set_lock(&__lock_atomics__);
     map< string, __info_transaction__ * >::iterator it = __transactions__.find(__this_id);
     if (it != __transactions__.end())
        __transactions__.erase(it);
     omp_unset_lock(&__lock_atomics__);
   }
};

class TOBJ_STOPPER {
public:
   TOBJ_STOPPER(int nthreads) {
     // Извлекаем из стека свой this-ptr
     omp_set_lock(&__lock_tobjs__);
     __tobj_this_stack[get_thread_id()]->pop();
     omp_unset_lock(&__lock_tobjs__);
   }
};

class TVar {
protected:
  string id;
  int winner;
public:
  TVar(const char * __id__ = "") {
    if (*__id__ == 0) {
     long long tid = get_thread_id();
     omp_set_lock(&__lock_tobjs__);
     map< long long, stack<TOBJ_STARTER *> *>::iterator it = __tobj_this_stack.find(tid);
     if (it == __tobj_this_stack.end() || it->second->size() == 0)
        id = __id__;
     else {
        TOBJ_STARTER * parent = it->second->top();
        id = parent->get_transaction_id();
     }
     omp_unset_lock(&__lock_tobjs__);
    } else
	id = __id__;
    omp_set_lock(&__lock_atomics__);
    get_transaction(id.c_str())->__atomics__.push_back(this);
    omp_unset_lock(&__lock_atomics__);
  }
  virtual void startTransaction() = 0;
  virtual void check(signed char * state) = 0;
  virtual void commit(const vector<int> & _winners) = 0;
  virtual ~TVar() {
    omp_set_lock(&__lock_atomics__);
	get_transaction(id.c_str())->__atomics__.remove(this);
    omp_unset_lock(&__lock_atomics__);
  }
};

class TChannel: public TVar {
protected:
  int owner;
  bool input;
  bool shot;
public:
  TChannel(bool in, const char * name, int _owner = -1, const char * __id__ = ""): TVar(__id__) {
     input = in;
     if (_owner < 0) owner = omp_get_thread_num(); else owner = _owner;
     omp_set_lock(&__lock_atomics__);
	 __info_transaction__ * info = get_transaction(id.c_str());
     map<string, pair<TChannel *, TChannel *> >::iterator it = info->__io__.find(name);
     if (it == info->__io__.end()) {
        if (in)
           info->__io__[name] = pair<TChannel *, TChannel *>(this, NULL);
        else
           info->__io__[name] = pair<TChannel *, TChannel *>(NULL, this);
     } else
        if (in)
           info->__io__[name].first = this;
        else
           info->__io__[name].second = this;
     omp_unset_lock(&__lock_atomics__);
     shot = false;
  }
  int get_owner() { return owner; }
  bool get_input() { return input; }
  bool get_shot() { return shot; }
  virtual void prepareRestart() = 0;
};

#define transaction_atomic(id) for (init_transaction(id); !end_transaction(); commit_transaction()) if (get_working()[omp_get_thread_num()])

bool * get_working() {
	omp_set_lock(&__lock_atomics__);
	string id;
	__info_transaction__ * info = get_transaction_by_thread(id);
	omp_unset_lock(&__lock_atomics__);

	return info->working;
}

int get_nprocs() {
	omp_set_lock(&__lock_atomics__);
	string id;
	__info_transaction__ * info = get_transaction_by_thread(id);
	omp_unset_lock(&__lock_atomics__);

	return info->__transaction_procs__[omp_get_thread_num()];
}

bool in_transaction(const char * __id__ = NULL) {
	omp_set_lock(&__lock_atomics__);
	__info_transaction__ * info;
	if (__id__ == NULL) {
		string id;
		info = get_transaction_by_thread(id, false);
	} else
		info = get_transaction(__id__);
	omp_unset_lock(&__lock_atomics__);

	return info != NULL && info->__in_transaction__;
}

// Был ли вызван fail для текущего потока
bool is_failed() {
	__info_transaction__ * info;
	string id;

	omp_set_lock(&__lock_atomics__);
	info = get_transaction_by_thread(id, false);
	omp_unset_lock(&__lock_atomics__);

	return info != NULL && info->failed[omp_get_thread_num()];
}

// Не прерывая работу, ставит ее на пересогласование в транзакционном блоке
bool fail() {
	string id;
	omp_set_lock(&__lock_atomics__);
	__info_transaction__ * info = get_transaction_by_thread(id, false);
	omp_unset_lock(&__lock_atomics__);
	if (info == NULL)
		return false;
	else {
		info->failed[omp_get_thread_num()] = true;
		return true;
	}
}

void restart_optimizer(const string & id, int np) {
	omp_set_lock(&__lock_atomics__);
	__info_transaction__ * info = get_transaction(id.c_str());
	omp_unset_lock(&__lock_atomics__);

	if (info != NULL) {
		info->__stat_transaction__.__transaction_misses__.resize(np);
		info->__stat_transaction__.__transaction_procs__.resize(np);

		info->__stat_transaction__.__transaction_counter__ = 0; // K

		for (int i = 0; i < np; i++) {
			info->__stat_transaction__.__transaction_timings__[i].clear();
			info->__stat_transaction__.__transaction_retimings__[i].clear();
			if (i < np - 1)
				info->__stat_transaction__.__transaction_procs__[i] = 1;
			else
				info->__stat_transaction__.__transaction_procs__[i] = __max(1, omp_get_num_procs() - (np - 1));
			info->__stat_transaction__.__transaction_misses__[i] = 0;
			info->__transaction_procs__[i] = info->__stat_transaction__.__transaction_procs__[i];
		}
	}
}

void init_transaction(char * id) {
	omp_set_lock(&__lock_atomics__);
	__info_transaction__ * info = get_transaction(id);
	__map_threads__[get_thread_id()] = id;
	omp_unset_lock(&__lock_atomics__);

#pragma omp barrier
#pragma omp master
  {
	  const int epochs = 5;
	  const int interval = 500;

	  int np = omp_get_num_threads();
	  int nm = omp_get_num_procs();

	  for (int i = 0; i < np; i++) {
		  info->working[i] = true;
		  info->job_ids[i] = 0;
		  info->failed[i] = false;
	  }

	  int idn = strlen(id);

	  if (idn > 0 && (!(idn >= 2 && id[0] == '&' && id[1] == '&')) && np > 1) {
		  if (info->__stat_transaction__.__transaction_counter__ < 0 || info->__stat_transaction__.__transaction_counter__ % (interval*(np - 1)*(nm - 1)) == 0)
			  restart_optimizer(id, np);

		  if (info->__stat_transaction__.__transaction_counter__ > 0 && nm >= 2 * np && info->__stat_transaction__.__transaction_counter__ < epochs*(np - 1)*(nm - 1)) {
			  int k = info->__stat_transaction__.__transaction_counter__ / (nm - 1);
			  int s = info->__stat_transaction__.__transaction_counter__ % (nm - 1);
			  k %= (np - 1);
			  if (k == 0 && s == 0) {
				  for (int i = 0; i < np; i++) {
					  if (i < np - 1)
						  info->__stat_transaction__.__transaction_procs__[i] = 1;
					  else
						  info->__stat_transaction__.__transaction_procs__[i] = __max(1, nm - (np - 1));
				  }
			  }
			  else
				  info->__stat_transaction__.__transaction_procs__[k]++;
			  if (info->__stat_transaction__.__transaction_procs__[k] == nm) {
				  info->__stat_transaction__.__transaction_procs__[k] = 1;
				  info->__stat_transaction__.__transaction_procs__[k + 1]++;
			  }
			  int sum = 0;
			  for (int i = 0; i < np; i++)
				  if (i < np - 1) {
					  sum += info->__stat_transaction__.__transaction_procs__[i];
				  }
				  else
					  info->__stat_transaction__.__transaction_procs__[i] = __max(1, nm - sum);
		  }
		  else if (info->__stat_transaction__.__transaction_counter__ == epochs*(np - 1)*(nm - 1) && nm >= 2 * np) {
			  /*
						cout << "K = " << info->__stat_transaction__.__transaction_counter__ << endl;
						cout << "Betta = ";
						for (int i = 0; i < np; i++)
						cout << (1.0*info->__stat_transaction__.__transaction_misses__[i]/info->__stat_transaction__.__transaction_counter__) << " ";
						cout << endl;
						for (int i = 0; i < np; i++) {
						cout << "Timings[" << i << "] = ";
						map<int, LARGE_INTEGER>::iterator it;
						for (it = info->__stat_transaction__.__transaction_timings__[i].begin(); it != info->__stat_transaction__.__transaction_timings__[i].end() ; it++)
						cout << "[" << it->first << "] " << -clock_val(it->second) << " ";
						cout << endl;
						}
						for (int i = 0; i < np; i++) {
						cout << "RETimings[" << i << "] = ";
						map<int, LARGE_INTEGER>::iterator it;
						for (it = info->__stat_transaction__.__transaction_retimings__[i].begin(); it != info->__stat_transaction__.__transaction_retimings__[i].end() ; it++)
						cout << "[" << it->first << "] " << -clock_val(it->second) << " ";
						cout << endl;
						}
						*/
			  double mup[__max_procs__] = { 0.0 };
			  double sp[__max_procs__] = { 0.0 };
			  double dmp[__max_procs__] = { 0.0 };
			  for (int i = 0; i < np; i++) {
				  int irow[3];
				  long double A[3][3] = { 0.0 };
				  long double LU[9];
				  long double B[3] = { 0.0 };
				  long double X[3];

				  map<int, LARGE_INTEGER>::iterator it;
				  for (it = info->__stat_transaction__.__transaction_timings__[i].begin(); it != info->__stat_transaction__.__transaction_timings__[i].end(); it++) {
					  int nn = it->first;
					  B[0] += -clock_val(it->second);
					  B[1] += nn*(-clock_val(it->second));
					  B[2] += (-clock_val(it->second)) / nn;
					  A[0][0] += 1.0;
					  A[0][1] += nn;
					  A[0][2] += 1.0 / nn;
					  A[1][0] += nn;
					  A[1][1] += nn*nn;
					  A[1][2] += 1.0;
					  A[2][0] += 1.0 / nn;
					  A[2][1] += 1.0;
					  A[2][2] += 1.0 / nn / nn;
				  }
				  if (_GetLU(3, irow, (long double *)A, LU) && _SolveLU(3, irow, LU, B, X)) {
					  mup[i] = X[0];
					  sp[i] = X[1];
					  dmp[i] = X[2];
				  }
			  }
			  double mu[__max_procs__] = { mup[0] };
			  double s[__max_procs__] = { sp[0] };
			  double dm[__max_procs__] = { dmp[0] };
			  for (int i = 1; i < np; i++)
				  if (info->__stat_transaction__.__transaction_misses__[i]) {
					  if (info->__stat_transaction__.__transaction_retimings__[i].size() < 3) {
						  info->__stat_transaction__.__transaction_misses__[i] = 0;
						  continue;
					  }

					  int irow[3];
					  long double A[3][3] = { 0.0 };
					  long double LU[9];
					  long double B[3] = { 0.0 };
					  long double X[3];

					  map<int, LARGE_INTEGER>::iterator it;
					  for (it = info->__stat_transaction__.__transaction_retimings__[i].begin(); it != info->__stat_transaction__.__transaction_retimings__[i].end(); it++) {
						  int nn = it->first;
						  B[0] += -clock_val(it->second);
						  B[1] += nn*(-clock_val(it->second));
						  B[2] += (-clock_val(it->second)) / nn;
						  A[0][0] += 1.0;
						  A[0][1] += nn;
						  A[0][2] += 1.0 / nn;
						  A[1][0] += nn;
						  A[1][1] += nn*nn;
						  A[1][2] += 1.0;
						  A[2][0] += 1.0 / nn;
						  A[2][1] += 1.0;
						  A[2][2] += 1.0 / nn / nn;
					  }
					  if (_GetLU(3, irow, (long double *)A, LU) && _SolveLU(3, irow, LU, B, X)) {
						  mu[i] = X[0];
						  s[i] = X[1];
						  dm[i] = X[2];
					  }
				  }
			  auto F = [&](const vector<int> & N)->double {
				  double TS[__max_procs__] = { 0.0 };
				  for (int i = 0; i < np; i++) {
					  TS[i] = mup[i] + sp[i] * N[i] + dmp[i] / N[i];
				  }
				  double result = 0.0;
				  for (int i = 0; i < np; i++)
					  if (i == 0 || info->__stat_transaction__.__transaction_misses__[i]) {
						  double m = mu[i] + s[i] * N[i] + dm[i] / N[i];
						  for (int j = i + 1; j < np; j++)
							  if (TS[j] > m)
								  m = TS[j];
						  if (i == 0)
							  result += m;
						  else
							  result += 1.0*info->__stat_transaction__.__transaction_misses__[i] / info->__stat_transaction__.__transaction_counter__*m;
					  }
				  return result;
			  };
			  for (int i = 0; i < np; i++)
				  info->__stat_transaction__.__transaction_procs__[i] = 1;
			  int SumN = np;
			  int MaxN = omp_get_num_procs();
			  while (SumN < MaxN) {
				  double semi_grad[__max_procs__];
				  double F0 = F(info->__stat_transaction__.__transaction_procs__);
				  for (int i = 0; i < np; i++) {
					  info->__stat_transaction__.__transaction_procs__[i]++;
					  semi_grad[i] = F(info->__stat_transaction__.__transaction_procs__);
					  info->__stat_transaction__.__transaction_procs__[i]--;
				  }
				  int k = 0;
				  for (int i = 1; i < np; i++)
					  if (semi_grad[i] < semi_grad[k])
						  k = i;
				  if (semi_grad[k] > F0) break;
				  info->__stat_transaction__.__transaction_procs__[k]++;
				  SumN++;
			  }
			  /**/
			  cout << "NN = ";
			  for (int i = 0; i < np; i++)
				  cout << info->__stat_transaction__.__transaction_procs__[i] << " ";
			  cout << endl;
			  /**/
		  }

		  LARGE_INTEGER c = { 0 };
		  QueryPerformanceCounter(&c);
		  for (int i = 0; i < np; i++) {
			  if (info->__stat_transaction__.__transaction_timings__[i].find(info->__stat_transaction__.__transaction_procs__[i]) == info->__stat_transaction__.__transaction_timings__[i].end())
				  info->__stat_transaction__.__transaction_timings__[i][info->__stat_transaction__.__transaction_procs__[i]] = c;
			  else
				  clock_val(info->__stat_transaction__.__transaction_timings__[i][info->__stat_transaction__.__transaction_procs__[i]]) += clock_val(c);
		  }
		  for (int i = 0; i < np; i++)
			  info->__transaction_procs__[i] = info->__stat_transaction__.__transaction_procs__[i];
	  }
	  else
		  for (int i = 0; i < np; i++)
			  info->__transaction_procs__[i] = __max(1, nm / np);

	  omp_set_lock(&__lock_atomics__);
	  for (auto v : info->__atomics__) {
		  v->startTransaction();
	  }
	  info->__in_transaction__ = true;
	  omp_unset_lock(&__lock_atomics__);
  }
#pragma omp barrier
}

bool end_transaction() {
	omp_set_lock(&__lock_atomics__);
	string id;
	__info_transaction__ * info = get_transaction_by_thread(id);
	omp_unset_lock(&__lock_atomics__);
#pragma omp barrier
	int np = omp_get_num_threads();
	for (int i = 0; i < np; i++)
		if (info->working[i])
			return false;
#pragma omp master
	{
		info->__in_transaction__ = false;
		if (id.length() > 0) {
			info->__stat_transaction__.__transaction_counter__++;
		}
	}
#pragma omp barrier
	return true;
}

void commit_transaction() {
	omp_set_lock(&__lock_atomics__);
	string sid;
	__info_transaction__ * info = get_transaction_by_thread(sid);
	omp_unset_lock(&__lock_atomics__);

	vector<int> winners;

	LARGE_INTEGER c = { 0 };
	QueryPerformanceCounter(&c);

	int np = omp_get_num_threads();

#pragma omp barrier
#pragma omp master
	{
		omp_set_lock(&__lock_atomics__);

		bool sendrecvs[__max_procs__] = { false };

		signed char state[__max_procs__];
		for (int i = 0; i < np; i++)
			state[i] = __reader__;
		for (auto v : info->__atomics__) {
			TChannel * ch = dynamic_cast<TChannel *>(v);
			if (ch == NULL)
				v->check(state);
			else
				sendrecvs[ch->get_owner()] |= ch->get_shot();
		}

		bool solved = false;
		do {
			signed char old_state[__max_procs__];
			for (int i = 0; i < np; i++)
				old_state[i] = state[i];
			for (auto v : info->__atomics__) {
				TChannel * ch = dynamic_cast<TChannel *>(v);
				if (ch != NULL && !ch->get_input())
					v->check(state);
			}
			for (auto v : info->__atomics__) {
				TChannel * ch = dynamic_cast<TChannel *>(v);
				if (ch != NULL && ch->get_input())
					v->check(state);
			}

			for (auto v : info->__atomics__) {
				TChannel * ch = dynamic_cast<TChannel *>(v);
				if (ch != NULL) {
					int own = ch->get_owner();
					if (state[own] == __another__ && state[own] != old_state[own])
						ch->prepareRestart();
				}
			}

			solved = true;
			for (int i = 0; solved && i < np; i++)
				if (old_state[i] != state[i])
					solved = false;
		} while (!solved);

		winners.reserve(256);
		for (int i = 0; i < np; i++)
			if (!info->failed[i] && info->working[i] && state[i] != __another__) {
				winners.push_back(i);
				info->working[i] = false;
				info->__funs[i] = nullptr;
				if (info->job_ids[i]) {
					omp_set_lock(&__lock_tobjs__);
					__tobj_job * jinfo = __tobj_jobs[info->job_ids[i]-1];
					jinfo->finished = true;
					omp_unset_lock(&__lock_tobjs__);
				}
			}
		if (winners.size() == 0) {
			for (int i = 0; i < np; i++)
				if (!info->failed[i] && info->working[i] && !sendrecvs[i]) {
					winners.push_back(i);
					info->working[i] = false;
					info->__funs[i] = nullptr;
					if (info->job_ids[i]) {
						omp_set_lock(&__lock_tobjs__);
						__tobj_job * jinfo = __tobj_jobs[info->job_ids[i]-1];
						jinfo->finished = true;
						omp_unset_lock(&__lock_tobjs__);
					}
					break;
				}
		}
		for (auto v : info->__atomics__) {
			v->commit(winners);
		}
		for (auto v : info->__atomics__) {
			TChannel * ch = dynamic_cast<TChannel *>(v);
			if (ch == NULL) v->startTransaction();
		}
		for (auto v : info->__atomics__) {
			TChannel * ch = dynamic_cast<TChannel *>(v);
			if (ch != NULL && info->working[ch->get_owner()]) v->startTransaction();
		}
		for (int i = 0; i < np; i++)
			info->failed[i] = false;

		omp_unset_lock(&__lock_atomics__);
	}
#pragma omp barrier

#pragma omp critical(commit_transaction)
  {
	  int id = omp_get_thread_num();

	  if (sid.length() > 0 && (!(sid.substr(0, 2) == "&&")) && np > 1) {
		  omp_set_lock(&__lock_atomics__);

		  int nn = info->__stat_transaction__.__transaction_procs__[id];
		  if (clock_val(info->__stat_transaction__.__transaction_timings__[id][nn]) >= 0) { // Первый счет
			  if (info->working[id]) {
				  LARGE_INTEGER c1 = { 0 };
				  QueryPerformanceCounter(&c1);
				  if (info->__stat_transaction__.__transaction_retimings__[id].find(nn) == info->__stat_transaction__.__transaction_retimings__[id].end())
					  info->__stat_transaction__.__transaction_retimings__[id][nn] = c1;
				  else
					  clock_val(info->__stat_transaction__.__transaction_retimings__[id][nn]) += clock_val(c1);
				  info->__stat_transaction__.__transaction_retimings__[id][-1] = c1;
				  info->__stat_transaction__.__transaction_misses__[id]++;
			  }
			  clock_val(info->__stat_transaction__.__transaction_timings__[id][nn]) -= clock_val(c);
		  }
		  else if (info->__stat_transaction__.__transaction_retimings__[id].find(nn) != info->__stat_transaction__.__transaction_retimings__[id].end() && clock_val(info->__stat_transaction__.__transaction_retimings__[id][nn]) >= 0) { // Пересчет
			  if (!info->working[id]) {
				  clock_val(info->__stat_transaction__.__transaction_retimings__[id][nn]) -= clock_val(c);
				  info->__stat_transaction__.__transaction_retimings__[id].erase(-1);
			  }
			  else {
				  LARGE_INTEGER c1 = { 0 };
				  QueryPerformanceCounter(&c1);

				  clock_val(info->__stat_transaction__.__transaction_retimings__[id][nn]) -= clock_val(info->__stat_transaction__.__transaction_retimings__[id][-1]);
				  clock_val(info->__stat_transaction__.__transaction_retimings__[id][nn]) += clock_val(c1);
				  info->__stat_transaction__.__transaction_retimings__[id][-1] = c1;
			  }
		  }

		  omp_unset_lock(&__lock_atomics__);
	  }
  }
}

template<class Type>
  class TIn: public TChannel, public funneled_predictor_in<Type> {
  protected:
    bool predicted;
    Type * __buf__;
  public:
    TIn(const char * Name, int N = 1, int P = 2, double rel_eps = 0.001, int _owner = -1, const char * __id__ = ""):
		TChannel(true, Name, _owner, __id__), funneled_predictor_in<Type>(Name, N, P, rel_eps) {
       __buf__ = new Type[N];
    }
    virtual ~TIn() {
       delete[] __buf__;
    }
    virtual void prepareRestart() {
       predicted = false;
    }
    virtual void startTransaction() {
       prepareRestart();
       shot = false;
    };
    virtual void check(signed char * state) {
       _funnel_with_history<Type> * Ref = reinterpret_cast<_funnel_with_history<Type> *>(this->getRef());

      if (Ref && shot) {
		 string sid;
		 __info_transaction__ * info = get_transaction_by_thread(sid);
         map<string, pair<TChannel *, TChannel *> >::iterator it = info->__io__.find(Ref->Name);
         bool no_send = true;
         if (it != info->__io__.end()) {
            no_send = state[it->second.second->get_owner()] != __another__;
         }
         if (predicted) {
            int SizeInBytes = Ref->getN()*sizeof(Type);
            funneled_in<Type>::get(__buf__, SizeInBytes);
            Ref->correct();
         }
         omp_set_lock(&Ref->Lock);
         if (no_send && (state[owner] == __another__ || Ref->hasPredicted() && !Ref->isCalculated())) {
            Ref->State |= tnlValue;
            state[owner] = __another__;
         }
         omp_unset_lock(&Ref->Lock);
         if (predicted) {
            Ref->unset_predict_results();
            predicted = false;
         }
      }
    };
    void get(Type * buf, double timeout) {
      if (!this->empty()) {
         _funnel_with_history<Type> * Ref = reinterpret_cast<_funnel_with_history<Type> *>(this->getRef());
         int SizeInBytes = Ref->getN()*sizeof(Type);
         funneled_in<Type>::get(buf, SizeInBytes);
         Ref->unset_predict_results();
         predicted = false;
      } else
         predicted = this->get_timed((void *) buf, timeout);
      shot = true;
    }
    virtual void commit(const vector<int> & _winners) {};
  };

template<class Type>
  class TOut: public TChannel, public funneled_predictor_out<Type> {
  protected:
  public:
    TOut(const char * Name, int N = 1, int P = 2, double rel_eps = 0.001, int _owner = -1, const char * __id__ = ""):
		TChannel(false, Name, _owner, __id__), funneled_predictor_out<Type>(Name, N, P, rel_eps) {
    }
    virtual void prepareRestart() {
       _funnel_with_history<Type> * Ref = reinterpret_cast<_funnel_with_history<Type> *>(this->getRef());

       if (Ref) {
           this->wait();
           if (Ref->State & tnlValue) {
              Ref->State &= ~tnlValue;
              Ref->pop_history(false);
           }
           omp_unset_lock(&Ref->Lock);
       }
    }
    virtual void startTransaction() {
       prepareRestart();
       shot = false;
    };
    virtual void check(signed char * state) {
       _funnel_with_history<Type> * Ref = reinterpret_cast<_funnel_with_history<Type> *>(this->getRef());

      if (Ref && state[owner] == __another__ && shot) {
		 string sid;
		 __info_transaction__ * info = get_transaction_by_thread(sid);
         map<string, pair<TChannel *, TChannel *> >::iterator it = info->__io__.find(Ref->Name);
         if (it != info->__io__.end()) {
            state[it->second.first->get_owner()] = __another__;
         }
      }
    };
    void put(Type * buf) {
      if (!shot) {
         _funnel_with_history<Type> * Ref = reinterpret_cast<_funnel_with_history<Type> *>(this->getRef());

         funneled_predictor_out<Type>::put((void *) buf, Ref->N*sizeof(Type));
         shot = true;
      }
    }
    virtual void commit(const vector<int> & _winners) {};
  };

template<class Type>
  class TScalar: public TVar {
  public:
    typedef std::function<Type(Type, Type)> reducer;
  protected:
    Type Data;
    reducer R;

    Type Buf[__max_procs__];

    LARGE_INTEGER reads[__max_procs__];
    LARGE_INTEGER writes[__max_procs__];
  public:
	TScalar(const char * __id__ = "") : TVar(__id__) { R = nullptr; }

    virtual void startTransaction() {
      for (int i = 0; i < __max_procs__; i++) {
          memset(&reads[i], 0, sizeof(LARGE_INTEGER));
          memset(&writes[i], 0, sizeof(LARGE_INTEGER));
          Buf[i] = Data;
      }
    }
    virtual void setReducer(reducer f) {
      R = f;
    }
    TScalar<Type> & operator = (const Type & val) {
      if (in_transaction(id.c_str())) {
         int id = omp_get_thread_num();
         LARGE_INTEGER c = { 0 };
         QueryPerformanceCounter(&c);
         writes[id] = c;
         Buf[id] = val;
      } else
         Data = val;
      return *this;
    }
    TScalar<Type> & operator ++ () {
      if (in_transaction(id.c_str())) {
         int id = omp_get_thread_num();
         LARGE_INTEGER c = { 0 };
         QueryPerformanceCounter(&c);
         reads[id] = c;
         writes[id] = c;
         ++Buf[id];
      } else
         ++Data;
      return *this;
    }
    TScalar<Type> & operator += (const Type v) {
      if (in_transaction(id.c_str())) {
         int id = omp_get_thread_num();
         LARGE_INTEGER c = { 0 };
         QueryPerformanceCounter(&c);
         reads[id] = c;
         writes[id] = c;
         Buf[id] += v;
      } else
         Data += v;
      return *this;
    }
    TScalar<Type> & operator -= (const Type v) {
      if (in_transaction(id.c_str())) {
         int id = omp_get_thread_num();
         LARGE_INTEGER c = { 0 };
         QueryPerformanceCounter(&c);
         reads[id] = c;
         writes[id] = c;
         Buf[id] -= v;
      } else
         Data -= v;
      return *this;
    }
    operator Type & () {
      if (in_transaction(id.c_str())) {
         int id = omp_get_thread_num();
         if (clock_val(reads[id]) == 0) {
            LARGE_INTEGER c = { 0 };
            QueryPerformanceCounter(&c);
            reads[id] = c;
         }
         return Buf[id];
      } else
         return Data;
    }
    virtual void check(signed char * state) {
      int np = omp_get_num_threads();
      if (R != nullptr) {
         for (int i = 1; i < np; i++)
             Buf[0] = R(Buf[0], Buf[i]);
      } else {
         LARGE_INTEGER min_write = { 0 };
         winner = -1;
         for (int i = 0; i < np; i++) {
             if (clock_val(writes[i]) != 0) {
                if (winner < 0 || clock_val(writes[i]) < clock_val(min_write)) {
                   winner = i;
                   min_write = writes[i];
                }
             }
         }
         if (winner >= 0)
            for (int i = 0; i < np; i++)
                if (i != winner) {
                   if (clock_val(writes[i]) != 0)
                      state[i] = __another__;
                   else
                      if (clock_val(reads[i]) != 0 && clock_val(reads[i]) < clock_val(min_write))
                         state[i] = __another__;
                } else
                   if (state[i] == __reader__)
                      state[i] = __writer__;
      }
    }
    virtual void commit(const vector<int> & _winners) {
      if (R != nullptr && _winners.size() > 0) {
         Data = Buf[0];
         return;
      }
      if (winner < 0 || _winners.size() == 0) return;
      if (find(_winners.begin(), _winners.end(), winner) != _winners.end())
         Data = Buf[winner];
    }
  };

template<class Type>
  class TArray: public TVar {
  public:
    typedef std::function<Type(Type, Type)> reducer;
  protected:
    vector<TScalar<Type> *> Data;
  public:
    TArray(int N, const char * __id__ = ""): TVar(__id__) {
       Data.resize(N);
       for (int i = 0; i < N; i++)
           Data[i] = new TScalar<Type>(id.c_str());
    }
    virtual void setReducer(reducer f) {
       for (auto d: Data)
           d->setReducer(f);
    }
    virtual ~TArray() {
       for (auto d: Data)
           delete d;
    }
    virtual void startTransaction() {
       // Все элементы стартуют самостоятельно как потомки TVar
    }
    Type * copy() {
       Type * res = new Type[Data.size()];
       int i = 0;
       for (auto d: Data) {
          res[i++] = *d;
       }
       return res;
    }
    TScalar<Type> & operator [] (const int index) {
      return *Data[index];
    }
    TArray<Type> & operator = (const Type & val) {
       for (auto d: Data) {
          *d = val;
       }
      return *this;
    }
    virtual void check(signed char * state) {
       // Все элементы проверяются самостоятельно как потомки TVar
    }
    virtual void commit(const vector<int> & _winners) {
       // Все элементы утверждаются самостоятельно как потомки TVar
    }
  };

template <class C>
class TObj : public TOBJ_STARTER, public C, public TOBJ_STOPPER {
// Часть методов наследуется от TOBJ_STARTER, см. выше
protected:
   thread * __thread__; // Дежурный поток
   volatile unsigned short __joined; // Число занятых потоков блока
   omp_lock_t __join_lock__;
   volatile bool __stopped; // Флаг, требующий завершения всех работ

   // Подкачка работ в блок
   virtual bool pump_jobs(__page_fun &f, __info_transaction__ * &parent_info, int &parent_id) {
	f = nullptr;
	parent_info = NULL;
	parent_id = 0;
	return false;
   }
private:
   // Исполняемая процедура дежурного потока
   void worker() {
        do {
			omp_set_lock(&__lock_atomics__);
			__info_transaction__ * info = get_transaction(__this_id);
			bool * working = info->working;
			omp_unset_lock(&__lock_atomics__);

			auto make_pump = [&]() {
				omp_set_lock(&__lock_atomics__);
				for (int i = __joined; i < __nthreads; i++) {
					if (pump_jobs(info->__funs[i], info->parents[i], info->parent_ids[i])) this->__joined++;
				}
				omp_unset_lock(&__lock_atomics__);
			};

           omp_set_lock(&__join_lock__);
           while (__joined == 0 && !__stopped) {
			 make_pump();
			 omp_unset_lock(&__join_lock__);
             _Yield();
             omp_set_lock(&__join_lock__);
           }
		   make_pump();
		   if (__joined != 0) {
			   int stored_joined = __joined;
			   omp_unset_lock(&__join_lock__);
			   #pragma omp parallel num_threads(stored_joined)
			   {
				   int id = omp_get_thread_num();
					transaction_atomic(__this_id) {
						omp_set_lock(&__join_lock__);
						omp_set_lock(&__lock_atomics__);
						if (info->__funs[id] != nullptr) {
							__page_fun f = info->__funs[id];
							omp_unset_lock(&__lock_atomics__);
							omp_unset_lock(&__join_lock__);
							f();
						}
						else {
							bool all_finished = true;
							for (int i = 0; i < stored_joined; i++)
								if (info->__funs[i] != nullptr && working[i])
									all_finished = false;
							omp_unset_lock(&__lock_atomics__);
							omp_unset_lock(&__join_lock__);
							if (!all_finished) fail();
						}
					}
			   }
             omp_set_lock(&__join_lock__);
			 omp_set_lock(&__lock_atomics__);
             for (int i = stored_joined; i < __nthreads; i++)
                 if (info->__funs[i] != nullptr) {
                    info->parents[i - stored_joined] = info->parents[i];
                    info->parent_ids[i - stored_joined] = info->parent_ids[i];
                    info->__funs[i - stored_joined] = info->__funs[i];
                    info->__funs[i] = nullptr;
                 }
             __joined -= stored_joined;
			 omp_unset_lock(&__lock_atomics__);
			 make_pump();
             omp_unset_lock(&__join_lock__);
           } else {
             omp_unset_lock(&__join_lock__);
             break;
           }
        } while (1);
   }
   // Создает запись о незавершенной работе с предусловиями preconds[npreconds], представляющими собой идентификаторы работ,
   // которые должны закончиться до текущей работы.
   // Возвращает идентификатор работы (больше или равен 1) или 0, если работа не создана
   // Для создания работ с уникальными идентификаторами и корректной работы режима ожидания необходим предварительный
   // вызов set_jobs_mode(true);
   int create_job(int npreconds, int * preconds) {
	int res = 0;
	omp_set_lock(&__lock_tobjs__);
	if (__use_jobs) {
		__tobj_job * job = new __tobj_job;
		job->finished = false;
		memset(job->preconds, 0, sizeof(job->preconds));
		if (preconds) {
			if (npreconds > 5) {
				cout << "Number of pre-conditions is greater than 5 !" << endl;
				exit(-800);
			}
			memmove(job->preconds, preconds, __min(5, npreconds)*sizeof(int));
		}
		if (__tobj_jobs.capacity() == __tobj_jobs.size())
			__tobj_jobs.reserve((unsigned int)(1.5*__tobj_jobs.capacity()));
		__tobj_jobs.push_back(job);
		res = __tobj_jobs.size();
        }
	omp_unset_lock(&__lock_tobjs__);
	return res;
   }
public:
   // Передается число требуемых рабочих потоков. Может равняться единице
   TObj<C>(int nthreads) : TOBJ_STARTER(nthreads), C(nthreads), TOBJ_STOPPER(nthreads) {
     // Создаем дежурный поток и ждем присоединений
     omp_init_lock(&__join_lock__);
	 __thread__ = NULL;
     reinit();
   }
   // Реинициализация
   virtual void reinit(bool sync_children = true) {
	   sync(sync_children);
	   __joined = 0;
	   __stopped = false;
	   delete __thread__;
	   __thread__ = new thread(&TObj<C>::worker, this);
   }
   virtual __page_fun handle_job(__page_fun f, int &id, int npreconds = 0, int * preconds = NULL) {
	   __info_transaction__ * tinfo = get_transaction(__this_id);
     if (__use_jobs) {
		 id = create_job(npreconds, preconds);
		 auto job = [id, npreconds, preconds, f, tinfo]() {
             omp_set_lock(&__lock_atomics__);
             tinfo->job_ids[omp_get_thread_num()] = id;
             omp_unset_lock(&__lock_atomics__);
             omp_set_lock(&__lock_tobjs__);
             __tobj_job * info = __tobj_jobs[id-1];
             if (info != NULL && preconds != NULL) {
                for (int i = 0; i < 5; i++)
                    if (info->preconds && info->preconds[i])
                       if ((unsigned int)info->preconds[i] <= __tobj_jobs.size()) {
                          volatile bool * fin = &__tobj_jobs[info->preconds[i]-1]->finished;
                          omp_unset_lock(&__lock_tobjs__);
                          if (!(*fin)) {
                             _Yield();
                             fail();
                             return;
                          }
                          omp_set_lock(&__lock_tobjs__);
                       } else {
                          cout << "Job[" << id << "] waits non-existing job[" << info->preconds[i] << "]" << endl;
                          exit(-600);
                       }
             }
             omp_unset_lock(&__lock_tobjs__);
             f();
        };
        return job;
     } else {
        id = 0;
        return f;
     }
   }
   // Помещает работу на выполнение и возвращает true. Если блок занят, то возвращает false
   virtual bool join(__page_fun f, int &id, int npreconds = 0, int * preconds = NULL, bool set_join_lock = true) {
     if (set_join_lock) omp_set_lock(&this->__join_lock__);
     if (__joined >= __nthreads) {
        omp_unset_lock(&__join_lock__);
        return false;
     }
     omp_set_lock(&__lock_atomics__);
     __info_transaction__ * tinfo = get_transaction(__this_id);
     string tr_id;
     tinfo->__funs[__joined] = this->handle_job(f, id, npreconds, preconds);
     tinfo->parents[__joined] = get_transaction_by_thread(tr_id, false);
     tinfo->parent_ids[__joined++] = omp_get_thread_num();
     omp_unset_lock(&__lock_atomics__);
     omp_unset_lock(&__join_lock__);
     return true;
   }
   // Ожидает полного завершения работ (своих, и, если sync_children, всех дочерних TObj-объектов)
   virtual void sync(bool sync_children = true) {
	 if (__thread__ == NULL) return;
     if (sync_children) {
        omp_set_lock(&__lock_atomics__);
        __info_transaction__ * info = get_transaction(__this_id);
        stack<TOBJ_STARTER *> objs;
        for (auto v : info->__atomics__) {
            TOBJ_STARTER * obj = dynamic_cast<TOBJ_STARTER *>(v);
            if (obj != NULL && obj != this)
               objs.push(obj);
        }
        omp_unset_lock(&__lock_atomics__);
        while (!objs.empty()) {
           TOBJ_STARTER * obj = objs.top();
           objs.pop();
           obj->sync(sync_children);
        }
     }
	 omp_set_lock(&__join_lock__);
	 __stopped = true;
	 omp_unset_lock(&__join_lock__);
	 // Уничтожаем дежурный поток
     if (__thread__->joinable()) __thread__->join();
   }
   // Возвращает число свободных потоков блока
   virtual int  num_free() {
     omp_set_lock(&__join_lock__);
     int res = __joined >= __nthreads ? 0 : (__nthreads - __joined);
     omp_unset_lock(&__join_lock__);
     return res;
   }
   virtual ~TObj<C>() {
     // Вызываем sync()
     sync();
     delete __thread__;
     omp_destroy_lock(&__join_lock__);
   }
};

template <class C>
class TQueuedObj : public TObj<C> {
protected:
   typedef struct {
      __page_fun f;
      __info_transaction__ * parent;
      int parent_id;
   } queue_item;
   queue<queue_item> Q;

   // Подкачка работ в блок
   virtual bool pump_jobs(__page_fun &f, __info_transaction__ * &parent_info, int &parent_id) {
	if (Q.empty()) return TObj<C>::pump_jobs(f, parent_info, parent_id);
	else {
		queue_item item = Q.front();
		Q.pop();
		f = item.f;
		parent_info = item.parent;
		parent_id = item.parent_id;
		return true;
	}
   }

public:
   // Передается число требуемых рабочих потоков. Может равняться единице
   TQueuedObj<C>(int nthreads) : TObj<C>(nthreads) {
   }
   // Реинициализация. Если блок работал, то сначала следует вызвать sync(), и только затем reinit()
   virtual void reinit(bool sync_children = true) {
     TObj<C>::reinit(sync_children);
     omp_set_lock(&this->__join_lock__);
     Q = queue<queue_item>();
     omp_unset_lock(&this->__join_lock__);
   }
   // Помещает работу в очередь или запускает, если есть свободный поток. Всегда возвращает true
   virtual bool join(__page_fun f, int &id, int npreconds = 0, int * preconds = NULL, bool set_join_lock = true) {
     if (set_join_lock) omp_set_lock(&this->__join_lock__);
	 if (Q.size() == 0) {
		 if (TObj<C>::join(f, id, npreconds, preconds, false)) return true;
		 omp_set_lock(&this->__join_lock__);
	 }
	 omp_set_lock(&__lock_atomics__);
	 __page_fun job = this->handle_job(f, id, npreconds, preconds);
     string tr_id;
     queue_item item = {
          job,
          get_transaction_by_thread(tr_id, false),
          omp_get_thread_num()
     };
     omp_unset_lock(&__lock_atomics__);
     Q.push(item);
     omp_unset_lock(&this->__join_lock__);
     return true;
   }
};

#pragma syntax check

#endif