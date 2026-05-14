// Up to 64 variables.
// In nnets.h: N(neurons)+N(inputs), e.g. (7+5+1)+(4)+tag(3)
// Such restrictions are introduced because each var occupies 8 bit,
//   and var_mask[8] (unsigned long long[8]) contains 64*8=512 bits.
#ifndef __SYMBOLIC_H__
#define __SYMBOLIC_H__

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <math.h>
#include <float.h>

#include <atomic>
#include <chrono>
#include <algorithm>
#include <numeric>
#include <random>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <chrono>

#ifdef _OPENMP
#include <omp.h>
#else
typedef int omp_lock_t;
void omp_init_lock(omp_lock_t *) { }
void omp_set_lock(omp_lock_t *) { }
void omp_unset_lock(omp_lock_t *) { }
void omp_destroy_lock(omp_lock_t *) { }
int omp_get_thread_num() { return 0; }
int omp_get_num_procs() { return 1; }
double omp_get_wtime() { return std::chrono::duration<double>(std::chrono::system_clock::now().time_since_epoch()).count(); }
#endif

static int NPROCS = 1;

static double TASK_PART = 3.0/4.0;

#ifdef _MSC_VER

#define ONE64 1ui64
#define FULL64 0xFFui64
#define ZERO64 0x0ui64
#define MINUS64 0x80ui64
#define THROW_EXCEPTION(msg) throw exception(msg)

#define _strcat(Dest, N, Src) strcat_s(Dest, N, Src)
#define _strcpy(Dest, N, Src) strcpy_s(Dest, N, Src)
#define _sprintf1(Buf, N, Fmt, Arg0) sprintf_s(Buf, N, Fmt, Arg0)
#define _sprintf2(Buf, N, Fmt, Arg0, Arg1) sprintf_s(Buf, N, Fmt, Arg0, Arg1)
#define _sprintf3(Buf, N, Fmt, Arg0, Arg1, Arg2) sprintf_s(Buf, N, Fmt, Arg0, Arg1, Arg2)

#define _fopen(F, Name, Mode) fopen_s(&F, Name, Mode)

#define _fscanf(F, Fmt, Arg) fscanf_s(F, Fmt, Arg)

#else

#define ONE64 1ULL
#define FULL64 0xFFULL
#define ZERO64 0x0ULL
#define MINUS64 0x80ULL
#define THROW_EXCEPTION(msg) { printf(msg); printf("\n"); throw exception(); }

#define _strcat(Dest, N, Src) strcat(Dest, Src)
#define _strcpy(Dest, N, Src) strcpy(Dest, Src)

#define _sprintf1(Buf, N, Fmt, Arg0) sprintf(Buf, Fmt, Arg0)
#define _sprintf2(Buf, N, Fmt, Arg0, Arg1) sprintf(Buf, Fmt, Arg0, Arg1)
#define _sprintf3(Buf, N, Fmt, Arg0, Arg1, Arg2) sprintf(Buf, Fmt, Arg0, Arg1, Arg2)

#define _fopen(F, Name, Mode) F = fopen(Name, Mode)

#define _fscanf(F, Fmt, Arg) fscanf(F, Fmt, Arg)

#endif

#ifdef _OPENMP
#if defined(__linux__) || _OPENMP >= 200800
#define TASKED
#endif
#endif

using namespace std;

struct VarMask {
private:
	unsigned long long var_mask[8] = { 0 };
	bool d = false;
public:
	inline bool operator > (const VarMask op2) const {
		if (d && !op2.d)
			return true;
		else if (!d && op2.d)
			return false;
		else if (d && op2.d)
			return d > op2.d;
		for (int i = 0; i < 8; i++)
			if (var_mask[i] > op2.var_mask[i])
				return true;
			else if (var_mask[i] < op2.var_mask[i])
				return false;
		return false;
	};

	inline bool operator < (const VarMask op2) const {
		if (d && !op2.d)
			return false;
		else if (!d && op2.d)
			return true;
		else if (d && op2.d)
			return d < op2.d;
		for (int i = 0; i < 8; i++)
			if (var_mask[i] < op2.var_mask[i])
				return true;
			else if (var_mask[i] > op2.var_mask[i])
				return false;
		return false;
	};

	inline bool operator == (VarMask op2) {
		if (d && !op2.d)
			return false;
		else if (!d && op2.d)
			return false;
		else if (d && op2.d)
			return d == op2.d;
		for (int i = 0; i < 8; i++)
			if (var_mask[i] != op2.var_mask[i])
				return false;
		return true;
	};

	inline bool operator == (const VarMask op2) const {
		if (d && !op2.d)
			return false;
		else if (!d && op2.d)
			return false;
		else if (d && op2.d)
			return d == op2.d;
		for (int i = 0; i < 8; i++)
			if (var_mask[i] != op2.var_mask[i])
				return false;
		return true;
	};

	inline bool operator != (VarMask op2) {
		if (d && !op2.d)
			return true;
		else if (!d && op2.d)
			return true;
		else if (d && op2.d)
			return d != op2.d;
		for (int i = 0; i < 8; i++)
			if (var_mask[i] != op2.var_mask[i])
				return true;
		return false;
	};

	inline bool operator != (const VarMask op2) const {
		if (d && !op2.d)
			return true;
		else if (!d && op2.d)
			return true;
		else if (d && op2.d)
			return d != op2.d;
		for (int i = 0; i < 8; i++)
			if (var_mask[i] != op2.var_mask[i])
				return true;
		return false;
	};

	inline void clear() {
		for (int i = 0; i < 8; i++)
			var_mask[i] = 0;
	};

	inline void setDIV() {
		this->d = true;
	};

	inline void set_mask(long double pow, int var) {
		long long p = (long long)(pow >= 0.0 ? 0.5+pow : -(0.5-pow));
		unsigned long long sign = p < 0 ? MINUS64 : ZERO64;
		unsigned long long mask = ((abs(p) | sign)<<(8*(var%8)));
		var_mask[var/8] |= mask;
	};

	inline unsigned long long is_mask(int var) {
		return var_mask[var/8] & (FULL64<<(8*(var%8)));
	};

	inline void clear(int var) {
		var_mask[var/8] &= ~(FULL64<<(8*(var%8)));
	};

	inline bool isDIV() const {
		return d;
	};
};

class ITEM {
public:
	virtual ~ITEM() {
	};

	virtual ITEM * clone() = 0;
	
	virtual bool IsZero() = 0;
	virtual bool IsOne() = 0;

	virtual ITEM* Neg() = 0;
	virtual ITEM* Add(ITEM* op) = 0;
	virtual ITEM* Sub(ITEM* op) = 0;
	virtual ITEM* Mul(ITEM* op) = 0;
	virtual ITEM* Div(ITEM* op) = 0;
	virtual ITEM* Pow(ITEM* op) = 0;

	virtual void sprint(char ** Vars, int * maxPows, string * Buf, bool insert_pow_op = false) = 0;

	virtual void CHECK_VARS(unsigned long long &used_mask, int first_sqrt_var, char ** Vars, map<string, ITEM *> &SUBSTS) = 0;
};

class MUL;
class DIV;

class SUMMAND: public ITEM {
public:
	VarMask var_mask;

	virtual ~SUMMAND() {
	};

	virtual void Mul(MUL * &S, bool free = true) = 0;
	virtual void Mul(DIV * &D, bool free = true) = 0;
	virtual bool TryAdd(SUMMAND * &S, bool free = true) = 0;
	virtual bool IsEqual(bool UseK, SUMMAND * S) = 0;

	virtual VarMask* get_mask() {
		return &var_mask;
	}
};

class SUM: public ITEM {
public:
	map<VarMask, SUMMAND *> summands;

	SUM();
	SUM(long double k);
	SUM(MUL * &S);
	SUM(DIV * &S);
	SUM(int var_idx, int n, long double * KF, long double kpow = 1.0);
	SUM(int var_idx, int sqrt_idx, int n, long double * KF, long double kpow = 1.0);

	virtual ~SUM();

	virtual ITEM * clone();

	void SETPOLY(SUM * &ARG, int n, long double * KF, const bool reversed = false);
	void SETPOLYSQR(SUM * &ARG, int sqrt_var, int n, long double * KF, const bool reversed);

	void Add(SUMMAND * &Item, bool account_similars = true);
	void Add(SUM * &S, bool account_similars = true);

	void Mul(SUMMAND * &S, bool free = true);
	void Mul(SUM * &S, bool free = true);
	void Mul(long double k);

	virtual ITEM* Neg();
	virtual ITEM* Add(ITEM* op);
	virtual ITEM* Sub(ITEM* op);
	virtual ITEM* Mul(ITEM* op);
	virtual ITEM* Div(ITEM* op);
	virtual ITEM* Pow(ITEM* op);

	void AccountSimilars();

	bool IsEqual(bool UseK, SUM * S);
	virtual bool IsZero();
	virtual bool IsOne();

	virtual void sprint(char ** Vars, int * maxPows, string * Buf, bool insert_pow_op = false);

	virtual void CHECK_VARS(unsigned long long &used_mask, int first_sqrt_var, char ** Vars, map<string, ITEM *> &SUBSTS) {
		map<VarMask, SUMMAND *>::iterator it;
		for (it = summands.begin(); it != summands.end(); it++)
			it->second->CHECK_VARS(used_mask, first_sqrt_var, Vars, SUBSTS);
	}
};

class MUL: public SUMMAND {
public:
	vector<int> vars;
	vector<long double> pows;

	MUL(long double k);

	virtual ~MUL() {
		vars.clear();
		pows.clear();
	};

	virtual ITEM * clone();

	virtual double card();

	virtual void Mul(MUL * &S, bool free = true);
	virtual void Mul(DIV * &D, bool free = true);
	virtual void Mul(long double k);
	virtual void Mul(int var_idx, long double pow);

	virtual ITEM* Neg();
	virtual ITEM* Add(ITEM* op);
	virtual ITEM* Sub(ITEM* op);
	virtual ITEM* Mul(ITEM* op);
	virtual ITEM* Div(ITEM* op);
	virtual ITEM* Pow(ITEM* op);

	virtual MUL * CheckDiv(MUL * S);

	virtual bool TryAdd(SUMMAND * &S, bool free = true);

	virtual bool IsEqual(bool UseK, SUMMAND * S);
	virtual bool IsZero();
	virtual bool IsOne();

	virtual void sprint(char ** Vars, int * maxPows, string * Buf, bool insert_pow_op = false);

	virtual void CHECK_VARS(unsigned long long &used_mask, int first_sqrt_var, char ** Vars, map<string, ITEM *> &SUBSTS) {
		for (unsigned int i = 1; i < vars.size(); i++) {
			used_mask |= (ONE64<<vars[i]);
			if (vars[i] >= first_sqrt_var)
				SUBSTS[Vars[vars[i]]]->CHECK_VARS(used_mask, first_sqrt_var, Vars, SUBSTS);
		}
	}
};

class DIV: public SUMMAND {
public:
	SUM * dividend;
	SUM * divisor;

	DIV(long double k);
	DIV(MUL * &S);
	DIV(SUM * &div1, SUM * &div2);

	virtual ~DIV();

	virtual ITEM * clone();

	virtual void Mul(MUL * &S, bool free = true);
	virtual void Mul(DIV * &D, bool free = true);

	virtual ITEM* Neg();
	virtual ITEM* Add(ITEM* op);
	virtual ITEM* Sub(ITEM* op);
	virtual ITEM* Mul(ITEM* op);
	virtual ITEM* Div(ITEM* op);
	virtual ITEM* Pow(ITEM* op);

	SUM * Divide();

	void AddToDividend(SUMMAND * dd);
	void AddToDivisor(SUMMAND * dd);

	virtual bool TryAdd(SUMMAND * &S, bool free = true);

	virtual bool IsEqual(bool UseK, SUMMAND * S);
	virtual bool IsZero();
	virtual bool IsOne();

	virtual void sprint(char ** Vars, int * maxPows, string * Buf, bool insert_pow_op = false);

	virtual void CHECK_VARS(unsigned long long &used_mask, int first_sqrt_var, char ** Vars, map<string, ITEM *> &SUBSTS) {
		dividend->CHECK_VARS(used_mask, first_sqrt_var, Vars, SUBSTS);
		divisor->CHECK_VARS(used_mask, first_sqrt_var, Vars, SUBSTS);
	}
};

SUM::SUM() : SUM(0.0) {
};

SUM::SUM(long double k) {
	SUMMAND * S = (SUMMAND *)(new MUL(k));
	summands[S->var_mask] = S;
};

SUM::SUM(MUL * &S) {
	summands[S->var_mask] = S;
	S = NULL;
};

SUM::SUM(DIV * &S) {
	summands[S->var_mask] = S;
	S = NULL;
};

SUM::SUM(int var_idx, int n, long double * KF, long double kpow) {
	if (n < 1) {
		SUMMAND * S = (SUMMAND *)(new MUL(0.0));
		summands[S->var_mask] = S;
		return;
	}
	for (int i = 0; i < n; i++) {
		SUMMAND * item = dynamic_cast<SUMMAND *>(new MUL(KF[i]));
		if (i > 0) ((MUL *)item)->Mul(var_idx, kpow*i);
		Add(item);
	}
};

SUM::SUM(int var_idx, int sqrt_idx, int n, long double * KF, long double kpow) {
	if (n < 1) {
		SUMMAND * S = (SUMMAND *)(new MUL(0.0));
		summands[S->var_mask] = S;
		return;
	}
	for (int i = 0; i < n; i++) {
		SUMMAND * item = dynamic_cast<SUMMAND *>(new MUL(KF[i]));
		if (i > 0)
			if (sqrt_idx >= 0) {
				if (i > 1) ((MUL *)item)->Mul(var_idx, kpow*floor(i/2.0));
				if (i % 2) ((MUL *)item)->Mul(sqrt_idx, kpow*0.5);
			} else {
				((MUL *)item)->Mul(sqrt_idx, kpow*0.5*i);
			}
		Add(item);
	}
};

SUM::~SUM() {
	map<VarMask, SUMMAND *>::iterator it;
	for (it = summands.begin(); it != summands.end(); it++)
		delete it->second;
};

ITEM * SUM::clone() {
	SUM * result = new SUM(0.0);
	map<VarMask, SUMMAND *>::iterator it;
	for (it = summands.begin(); it != summands.end(); it++) {
		SUMMAND * S = dynamic_cast<SUMMAND *>(it->second->clone());
		result->Add(S, false);
	}
	return result;
};

void SUM::SETPOLY(SUM * &ARG, int n, long double * KF, const bool reversed) {
	map<VarMask, SUMMAND *>::iterator it;
	for (it = summands.begin(); it != summands.end(); it++)
		delete it->second;
	summands.clear();
	SUMMAND * S = new MUL(0.0);
	summands[S->var_mask] = S;
	if (n < 1) {
		delete ARG;
		ARG = NULL;
		return;
	}
	SUM * POWARG = new SUM(1.0);
	for (int i = 0; i < n; i++) {
		SUM * _ARG = dynamic_cast<SUM *>(POWARG->clone());
		if (reversed && i>0) {
			SUM * _ARG0 = new SUM(KF[i]);
			SUMMAND * ARG0 = new DIV(_ARG0, _ARG);
			Add(ARG0, false);
		} else {
			_ARG->Mul(KF[i]);
			Add(_ARG, false);
		}
		AccountSimilars();
		SUM * ARG1 = dynamic_cast<SUM *>(ARG->clone());
		POWARG->Mul(ARG1);
		POWARG->AccountSimilars();
	}
	delete POWARG;
	delete ARG;
	ARG = NULL;
};

void SUM::SETPOLYSQR(SUM * &ARG, int sqrt_var, int n, long double * KF, const bool reversed) {
	map<VarMask, SUMMAND *>::iterator it;
	for (it = summands.begin(); it != summands.end(); it++)
		delete it->second;
	summands.clear();
	SUMMAND * S = new MUL(0.0);
	summands[S->var_mask] = S;
	if (n < 1) {
		delete ARG;
		ARG = NULL;
		return;
	}
	SUM * POWARG = new SUM(1.0);
	for (int i = 0; i < n; i++) {
		SUM * _ARG = dynamic_cast<SUM *>(POWARG->clone());
		SUMMAND * zARG = new MUL(1.0);
		if (i % 2)
			((MUL *)zARG)->Mul(sqrt_var, (i+1)/2.0);
		_ARG->Mul(zARG);
		if (reversed && i>0) {
			SUM * _ARG0 = new SUM(KF[i]);
			SUMMAND * ARG0 = new DIV(_ARG0, _ARG);
			Add(ARG0, false);
		} else {
			_ARG->Mul(KF[i]);
			Add(_ARG, false);
		}
		AccountSimilars();
		if (i % 2) {
			SUM * ARG1 = dynamic_cast<SUM *>(ARG->clone());
			POWARG->Mul(ARG1);
			POWARG->AccountSimilars();
		}
	}
	delete POWARG;
	delete ARG;
	ARG = NULL;
};

void SUM::Add(SUMMAND * &Item, bool account_similars) {
	if (Item->IsZero()) {
		delete Item;
		Item = NULL;
		return;
	}
	if (summands.size() == 1 && summands.begin()->second->IsZero()) {
		delete summands.begin()->second;
		summands.clear();
		summands[Item->var_mask] = Item;
		Item = NULL;
		return;
	}
	map<VarMask, SUMMAND *>::iterator it = summands.find(Item->var_mask);
	if (it != summands.end()) {
		if (it->second->TryAdd(Item)) {
			if (it->second->IsZero()) {
				SUMMAND* del = it->second;
				summands.erase(it);
				delete del;
			}
			if (summands.size() == 0) {
				SUMMAND * S = new MUL(0.0);
				summands[S->var_mask] = S;
			}
			return;
		}
		else {
			THROW_EXCEPTION("SUM Add!");
		}
	}
	if (Item)
		summands[Item->var_mask] = Item;
};

void SUM::Add(SUM * &S, bool account_similars) {
	map<VarMask, SUMMAND *>::iterator it;
	for (it = S->summands.begin(); it != S->summands.end(); it++)
		Add(it->second, false);
	if (account_similars)
		AccountSimilars();
	S->summands.clear();
	delete S;
	S = NULL;
};

void SUM::Mul(SUMMAND * &S, bool free) {
	MUL * SS = dynamic_cast<MUL *>(S);
	DIV * DD = dynamic_cast<DIV *>(S);
	map<VarMask, SUMMAND *>::iterator it;
	if (SS) {
		vector<SUMMAND *> buf;
		for (it = summands.begin(); it != summands.end(); ) {
			MUL * op = dynamic_cast<MUL *>(SS->clone());
			it->second->Mul(op);
			if (it->second->IsZero())
				it = summands.erase(it);
			else {
				buf.push_back(it->second);
				it++;
			}
		}
		summands.clear();

		unsigned seed = (unsigned) std::chrono::system_clock::now().time_since_epoch().count();
		std::mt19937 gen(seed);
		std::uniform_int_distribution<int> dist(0, 1000000);
		while (buf.size() > 0) {
			unsigned int i = (unsigned int)(0.000001*(buf.size()-1)*dist(gen));
// Здесь, возможно, следует поставить проверку, что слагаемое с такой маской уже существует. Тогда сложить их.
			map<VarMask, SUMMAND*>::iterator itt = summands.find(buf[i]->var_mask);
			if (itt == summands.end())
				summands[buf[i]->var_mask] = buf[i];
			else
				itt->second->TryAdd(buf[i], true);
			buf.erase(buf.begin()+i);
		}
	} else if (DD) {
		Mul(DD->dividend, free);
		SUM * op1 = dynamic_cast<SUM *>(this->clone());
		SUM * op2 = dynamic_cast<SUM*>(DD->divisor->clone());
		DIV * op = new DIV(op1, op2);

		for (it = summands.begin(); it != summands.end(); it++) {
			delete it->second;
		}
		summands.clear();
		summands[op->var_mask] = op;
	} else
		THROW_EXCEPTION("Unknown summand type in MULTIPLY");
	if (free) {
		delete S;
		S = NULL;
	}
};

void SUM::Mul(SUM * &S, bool free) {
	int NPP = NPROCS;

	vector<SUMMAND*> A;
	vector<SUMMAND*> B;
	bool AlessB = S->summands.size() > summands.size();
	if (AlessB) {
		A.reserve(summands.size());
		std::transform(summands.begin(), summands.end(), std::back_inserter(A), [](auto& kv) { return kv.second; });
		B.reserve(S->summands.size());
		std::transform(S->summands.begin(), S->summands.end(), std::back_inserter(B), [](auto& kv) { return kv.second; });
	} else {
		B.reserve(summands.size());
		std::transform(summands.begin(), summands.end(), std::back_inserter(B), [](auto& kv) { return kv.second; });
		A.reserve(S->summands.size());
		std::transform(S->summands.begin(), S->summands.end(), std::back_inserter(A), [](auto& kv) { return kv.second; });
	}

	summands.clear();

	vector<SUMMAND*> muls;
	muls.resize(B.size());
	omp_lock_t LOCK;
	omp_init_lock(&LOCK);
	for (int _a = 0; _a < A.size(); _a++) {
		SUMMAND* a = A[_a];
		#pragma omp parallel for schedule(guided) if((B.size() > 0) && (NPP-(int)(NPP*TASK_PART) > 1)) num_threads(min(min(4,(int)B.size()),NPP-(int)(NPP*TASK_PART)))
		for (int _b = 0; _b < B.size(); _b++) {
			SUMMAND* b = B[_b];
			SUMMAND* x = dynamic_cast<SUMMAND*>(a->clone());
			MUL* mb = dynamic_cast<MUL*>(b);
			DIV* db = dynamic_cast<DIV*>(b);
			MUL* mx = dynamic_cast<MUL*>(x);
			DIV* dx = dynamic_cast<DIV*>(x);
			if (mx)
				if (mb)
					mx->Mul(mb, false);
				else {
					db = dynamic_cast<DIV*>(b->clone());
					db->Mul(mx, true);
					x = db;
				}
			else
				if (mb)
					dx->Mul(mb, false);
				else
					dx->Mul(db, false);
			if (dynamic_cast<DIV*>(x)) {
				muls[_b] = NULL;
				omp_set_lock(&LOCK);
				map<VarMask, SUMMAND*>::iterator it = summands.find(*x->get_mask());
				if (it == summands.end())
					summands[*x->get_mask()] = x;
				else {
					it->second->TryAdd(x, true);
				}
				omp_unset_lock(&LOCK);
			} else {
				if (x->IsZero())
					muls[_b] = NULL;
				else
					muls[_b] = x;
			}
		}
		for (SUMMAND * x : muls)
			if (x) {
				map<VarMask, SUMMAND*>::iterator it = summands.find(*x->get_mask());
				if (it == summands.end())
					summands[*x->get_mask()] = x;
				else {
					it->second->TryAdd(x, true);
				}
			}
	}
	if (AlessB) {
		for (SUMMAND * a : A)
			delete a;
	} else {
		for (SUMMAND * b : B)
			delete b;
	}
	omp_destroy_lock(&LOCK);
	AccountSimilars();
	if (free) {
		delete S;
		S = NULL;
	}
};

void SUM::Mul(long double k) {
	map<VarMask, SUMMAND *>::iterator it;
	if (fabs(k)<1E-9) {
		for (it = summands.begin(); it != summands.end(); it++)
			delete it->second;
		summands.clear();
		SUMMAND * S = new MUL(0.0);
		summands[S->var_mask] = S;
		return;
	}
	for (it = summands.begin(); it != summands.end(); it++) {
		MUL * SS = dynamic_cast<MUL *>(it->second);
		DIV * DD = dynamic_cast<DIV *>(it->second);
		if (SS)
			SS->Mul(k);
		else if (DD)
			DD->dividend->Mul(k);
	}
};

ITEM* SUM::Neg() {
	SUM* result = new SUM(0.0);
	for (auto& item : summands) {
		SUMMAND* S = dynamic_cast<SUMMAND*>(item.second->Neg());
		result->Add(S, true);
	}
	return result;
}

ITEM* SUM::Add(ITEM* op) {
	SUMMAND* M = dynamic_cast<SUMMAND*>(op);
	SUM* S = dynamic_cast<SUM*>(op);
	SUM* result = dynamic_cast<SUM*>(this->clone());
	if (M)
		result->Add(M, true);
	else
		result->Add(S, true);
	return result;
}

ITEM* SUM::Sub(ITEM* op) {
	ITEM* old = op;
	op = old->Neg();
	delete old;
	SUMMAND* M = dynamic_cast<SUMMAND*>(op);
	SUM* S = dynamic_cast<SUM*>(op);
	SUM* result = dynamic_cast<SUM*>(this->clone());
	if (M)
		result->Add(M, true);
	else
		result->Add(S, true);
	return result;
}

ITEM* SUM::Mul(ITEM* op) {
	SUMMAND* M = dynamic_cast<SUMMAND*>(op);
	SUM* S = dynamic_cast<SUM*>(op);
	SUM* result = dynamic_cast<SUM*>(this->clone());
	if (M)
		result->Mul(M, false);
	else
		result->Mul(S, false);
	return result;
}

ITEM* SUM::Div(ITEM* op) {
	MUL* M = dynamic_cast<MUL*>(op);
	DIV* D = dynamic_cast<DIV*>(op);
	SUM* S = dynamic_cast<SUM*>(op);
	if (M) {
		SUM* S1 = dynamic_cast<SUM*>(this->clone());
		SUM* S2 = new SUM(M);
		return new DIV(S1, S2);
	}
	else if (D) {
		SUM* S1 = dynamic_cast<SUM*>(this->clone());
		SUM* S2 = new SUM(D);
		return new DIV(S1, S2);
	}
	else {
		SUM* S1 = dynamic_cast<SUM*>(this->clone());
		SUM* S2 = dynamic_cast<SUM*>(op->clone());
		return new DIV(S1, S2);
	}
}

ITEM* SUM::Pow(ITEM* op) {
	THROW_EXCEPTION("Can't calculate power of SUM!");
}

void SUM::AccountSimilars() {
	map<VarMask, SUMMAND *>::iterator it;
	for (it = summands.begin(); it != summands.end(); ) {
		DIV * DD = dynamic_cast<DIV *>(it->second);
		if (DD) {
			DD->dividend->AccountSimilars();
			DD->divisor->AccountSimilars();
		}
		if (it->second->IsZero()) {
			delete it->second;
			it = summands.erase(it);
		} else
			it++;
	}
	if (summands.size() == 0) {
		SUMMAND * S = new MUL(0.0);
		summands[S->var_mask] = S;
	}
};

bool SUM::IsEqual(bool UseK, SUM * S) {
	if (summands.size() != S->summands.size())
		return false;
	map<VarMask, SUMMAND *>::iterator it1;
	map<VarMask, SUMMAND *>::iterator it2;
	for (it1 = summands.begin(), it2 = S->summands.begin(); it1 != summands.end(); it1++, it2++)
		if (it1->first != it2->first)
			return false;
	for (it1 = summands.begin(), it2 = S->summands.begin(); it1 != summands.end(); it1++, it2++) {
		if (!it1->second->IsEqual(UseK, it2->second)) {
			return false;
		}
	}
	return true;
};

bool SUM::IsZero() {
	return summands.size()==1 && summands.begin()->second->IsZero();
};

bool SUM::IsOne() {
	return summands.size()==1 && summands.begin()->second->IsOne();
};

void SUM::sprint(char ** Vars, int * maxPows, string * Buf, bool insert_pow_op) {
	string * _Buf = new string("");
	map<VarMask, SUMMAND *>::iterator it;
	map<VarMask, SUMMAND *>::iterator it_last = summands.end();
	if (summands.size() > 0) it_last--;
	for (it = summands.begin(); it != summands.end(); it++) {
		*_Buf = "";
		it->second->sprint(Vars, maxPows, _Buf, insert_pow_op);

		if (it != it_last) *_Buf += "+";
		// if (it != summands.begin() && (*_Buf)[0] == '-')
		//	Buf->resize(Buf->length()-1);
		*Buf += *_Buf;
	}
	delete _Buf;
};

MUL::MUL(long double k): SUMMAND() {
	vars.push_back(-1);
	pows.push_back(k);
	var_mask.clear();
};

ITEM * MUL::clone() {
	MUL * result = new MUL(0.0);
	result->vars.clear();
	result->vars.assign(vars.begin(), vars.end());
	result->pows.clear();
	result->pows.assign(pows.begin(), pows.end());
	result->var_mask = var_mask;
	return result;
};

double MUL::card() {
	double result = 0.0;
	for (int i = 1; i < pows.size(); i++)
		result += fabs(pows[i]);
	return result;
}

void MUL::Mul(MUL * &S, bool free) {
	pows[0] *= S->pows[0];
	if (fabs(pows[0])<1e-9) {
		pows.erase(pows.begin()+1, pows.end());
		vars.erase(vars.begin()+1, vars.end());
		pows[0] = 0.0;
		var_mask.clear();
		if (free) {
			delete S;
			S = NULL;
		}
		return;
	}
	for (unsigned int i = 1; i < S->vars.size(); i++) {
		int found = -1;
		for (unsigned int j = 1; found<0 && j < vars.size(); j++)
			if (S->vars[i] == vars[j])
				found = j;
		if (found >= 0) {
			pows[found] += S->pows[i];
			var_mask.clear(vars[found]);
			if (fabs(pows[found])<1e-9) {
				pows.erase(pows.begin()+found);
				vars.erase(vars.begin()+found);
			} else {
				var_mask.set_mask(pows[found], vars[found]);;
			}
		} else {
			vars.push_back(S->vars[i]);
			pows.push_back(S->pows[i]);
			var_mask.clear(S->vars[i]);
			var_mask.set_mask(S->pows[i], S->vars[i]);
		}
	}
	if (free) {
		delete S;
		S = NULL;
	}
};

void MUL::Mul(DIV * &D, bool free) {
	THROW_EXCEPTION("MUL*DIV can't be performed");
};

void MUL::Mul(long double k) {
	pows[0] *= k;
	if (fabs(pows[0])<1e-9) {
		pows[0] = 0.0;
		vars.erase(vars.begin()+1, vars.end());
		pows.erase(pows.begin()+1, pows.end());
		var_mask.clear();
	}
};

void MUL::Mul(int var_idx, long double pow) {
	if (var_idx < 0)
		Mul(pow);
	else {
		for (unsigned int i = 1; i < vars.size(); i++)
			if (vars[i] == var_idx) {
				pows[i] += pow;
				var_mask.clear(var_idx);
				if (fabs(pows[i]) < 1e-9) {
					vars.erase(vars.begin()+i);
					pows.erase(pows.begin()+i);
				} else {
					var_mask.set_mask(pows[i], var_idx);
				}
				return;
			}
		vars.push_back(var_idx);
		pows.push_back(pow);
		var_mask.clear(var_idx);
		var_mask.set_mask(pow, var_idx);
	}
};

ITEM* MUL::Neg() {
	MUL* result = dynamic_cast<MUL*>(this->clone());
	if (result->pows.size())
		result->pows[0] = -result->pows[0];
	return result;
}

ITEM* MUL::Add(ITEM* op) {
	SUMMAND* M = dynamic_cast<SUMMAND*>(op);
	SUM* S = dynamic_cast<SUM*>(op);
	MUL* _THIS = dynamic_cast<MUL*>(this->clone());
	SUM* result = new SUM(_THIS);
	if (M)
		result->Add(M, true);
	else
		result->Add(S, true);
	return result;
}

ITEM* MUL::Sub(ITEM* op) {
	ITEM* old = op;
	op = old->Neg();
	delete old;
	SUMMAND* M = dynamic_cast<SUMMAND*>(op);
	SUM* S = dynamic_cast<SUM*>(op);
	MUL* _THIS = dynamic_cast<MUL*>(this->clone());
	SUM* result = new SUM(_THIS);
	if (M)
		result->Add(M, true);
	else
		result->Add(S, true);
	return result;
}

ITEM* MUL::Mul(ITEM* op) {
	SUMMAND* M = dynamic_cast<SUMMAND*>(op);
	SUM* S = dynamic_cast<SUM*>(op);
	MUL* _THIS = dynamic_cast<MUL*>(this->clone());
	SUM* result = new SUM(_THIS);
	if (M)
		result->Mul(M, false);
	else
		result->Mul(S, false);
	return result;
}

ITEM* MUL::Div(ITEM* op) {
	MUL* M = dynamic_cast<MUL*>(op);
	DIV* D = dynamic_cast<DIV*>(op);
	SUM* S = dynamic_cast<SUM*>(op);
	MUL* _THIS = dynamic_cast<MUL*>(this->clone());
	SUM* S1 = new SUM(_THIS);
	if (M) {
		SUM* S2 = new SUM(M);
		return new DIV(S1, S2);
	}
	else if (D) {
		SUM* S2 = new SUM(D);
		return new DIV(S1, S2);
	} else {
		SUM* S2 = dynamic_cast<SUM*>(op->clone());
		return new DIV(S1, S2);
	}
}

ITEM* MUL::Pow(ITEM* op) {
	MUL* M = dynamic_cast<MUL*>(op);
	if (M) {
		if (M->pows.size() != 1) {
			THROW_EXCEPTION("Can calculate power of MUL(number) only!");
		} else {
			MUL* result = dynamic_cast<MUL*>(this->clone());
			result->pows[0] = pow(result->pows[0], M->pows[0]);
			for (int i = 1; i < result->pows.size(); i++)
				result->pows[i] *= M->pows[0];
			return result;
		}
	}
	else {
		THROW_EXCEPTION("Can calculate power of MUL only!");
	}
}

MUL * MUL::CheckDiv(MUL * S) {
	double q = pows[0] / S->pows[0];
	MUL * result = new MUL(q);
	vector<unsigned int> rest_vars;
	for (unsigned int j = 1; j < vars.size(); j++)
		rest_vars.push_back(j);
	for (unsigned int i = 1; i < S->vars.size(); i++) {
		bool found = false;
		if (var_mask.is_mask(S->vars[i])) {
			for (unsigned int j = 0; !found && j < rest_vars.size(); j++)
				if (S->vars[i] == vars[rest_vars[j]]) {
					long double rest_pow = pows[rest_vars[j]]-S->pows[i];
					result->var_mask.clear(vars[rest_vars[j]]);
					if (rest_pow > 1e-9) {
						result->vars.push_back(vars[rest_vars[j]]);
						result->pows.push_back(rest_pow);
						result->var_mask.set_mask(rest_pow, vars[rest_vars[j]]);
					}
					else if (rest_pow < -1E-9) {
						delete result;
						return NULL;
					}
					rest_vars.erase(rest_vars.begin()+j);
					found = true;
				}
		}
		if (!found) {
			delete result;
			return NULL;
		}
	}
	for (unsigned int j = 0; j < rest_vars.size(); j++) {
		result->vars.push_back(vars[rest_vars[j]]);
		result->pows.push_back(pows[rest_vars[j]]);
		result->var_mask.clear(vars[rest_vars[j]]);
		result->var_mask.set_mask(pows[rest_vars[j]], vars[rest_vars[j]]);
	}
	return result;
};

bool MUL::TryAdd(SUMMAND * &S, bool free) {
	MUL * SS = dynamic_cast<MUL *>(S);
	if (!SS)
		return false;
	if (S->IsZero()) {
		if (free) {
			delete S;
			S = NULL;
		}
		return true;
	}
	if (IsZero()) {
		vars.clear();
		pows.clear();
		vars.assign(SS->vars.begin(), SS->vars.end());
		pows.assign(SS->pows.begin(), SS->pows.end());
		var_mask = SS->var_mask;
		if (free) {
			delete S;
			S = NULL;
		}
		return true;
	}
	if (!IsEqual(false, SS))
		return false;
	pows[0] += SS->pows[0];
	if (free) {
		delete S;
		S = NULL;
	}
	return true;
};

bool MUL::IsEqual(bool UseK, SUMMAND * S) {
	MUL * SS = dynamic_cast<MUL *>(S);
	DIV * DD = dynamic_cast<DIV *>(S);
	if (SS) {
		if (vars.size() != SS->vars.size())
			return false;
		if (UseK && fabs(pows[0]-SS->pows[0])>1e-9)
			return false;
		if (var_mask != SS->var_mask)
			return false;
/*
		vector<unsigned int> not_seen;
		for (unsigned int j = 1; j < SS->vars.size(); j++)
			not_seen.push_back(j);
		for (unsigned int i = 1; i < vars.size(); i++) {
			bool found = false;
			if (SS->var_mask.is_mask(vars[i])) {
				for (unsigned int j = 0; !found && j < not_seen.size(); j++)
					if (vars[i] == SS->vars[not_seen[j]] && fabs(pows[i]-SS->pows[not_seen[j]])<1e-9) {
						not_seen.erase(not_seen.begin()+j);
						found = true;
					}
			}
			if (!found)
				return false;
		}
*/
		return true;
	}
	if (DD) {
		MUL * SS1 = dynamic_cast<MUL *>(this->clone());
		DIV * D = new DIV(SS1);
		bool result = D->IsEqual(true, DD);
		delete SS1;
		delete D;
		return result;
	}
	return false;
};

bool MUL::IsZero() {
	bool result = vars.size()>0 && vars[0]<0 && fabs(pows[0])<1e-9;
	if (result) {
		pows[0] = 0.0;
		vars.erase(vars.begin()+1, vars.end());
		pows.erase(pows.begin()+1, pows.end());
		var_mask.clear();
	}
	return result;
};

bool MUL::IsOne() {
	bool result = vars.size()>0 && vars[0]<0 && fabs(1.0-pows[0])<1e-9;
	if (result) {
		for (unsigned int i = 1; i < pows.size(); i++)
			if (fabs(pows[i]) >= 1e-9)
				return false;
		vars.erase(vars.begin()+1, vars.end());
		pows.erase(pows.begin()+1, pows.end());
		var_mask.clear();
	}
	return result;
};

void STRIP(char * _Buf) {
	size_t j = strlen(_Buf)-1;
	while (j >= 0 && _Buf[j] == '0') j--;
	if (j >= 0 && _Buf[j] == '.') j--;
	_Buf[j+1] = 0x0;
};

void ESTRIP(char * _Buf) {
	size_t e = strcspn(_Buf, "Ee");
	int j = (int)e - 1;
	while (j >= 0 && _Buf[j] == '0') j--;
	if (j >= 0 && _Buf[j] == '.') j--;
	j++;
	while (_Buf[j++] = _Buf[e++]);
};

void MUL::sprint(char ** Vars, int * maxPows, string * Buf, bool insert_pow_op) {
	char * _Buf = new char[16384*64*16];
	_Buf[0] = 0x0;
	for (unsigned int i = 0; i < vars.size(); i++) {
		bool print_star = i < vars.size()-1;

		if (vars[i] < 0) {
			if (fabs(1.0-pows[i]) > 1E-9)
				if (fabs(-1.0-pows[i]) < 1E-9) {
					*Buf += "-";
					if (vars.size() == 1)
						*Buf += "1";
					print_star = false;
				} else {
					_sprintf1(_Buf, 16384*64*16, "%15.12Le", pows[i]);
					ESTRIP(_Buf);
					*Buf += _Buf;
				}
			else {
				if (vars.size() == 1)
					*Buf += "1";
				print_star = false;
			}
		} else {
			if (fabs(1.0-pows[i]) > 1E-9) {
				*Buf += "(";
				*Buf += Vars[vars[i]];
				char Num[32] = "";
				_sprintf1(Num, 32, "%Lf", fabs(pows[i]));
				STRIP(Num);
				if (insert_pow_op)
					*Buf += "^";
				if (!strchr(Num, '.') && !strchr(Num, ','))
					if (fabs(pows[i]) - maxPows[vars[i]] > 1E-9)
						maxPows[vars[i]] = (int)(0.5 + fabs(pows[i]));
				if (pows[i] >= 0.0)
					_sprintf1(_Buf, 16384*64*16, "%s)", Num);
				else
					_sprintf1(_Buf, 16384*64*16, "1.0/(%s))", Num);
				*Buf += _Buf;
			} else
				*Buf += Vars[vars[i]];
		}
		if (print_star) *Buf += "*";
	}
	delete[] _Buf;
};

DIV::DIV(long double k): SUMMAND() {
	dividend = new SUM(k);
	divisor = new SUM(1.0);
	var_mask.setDIV();
};

DIV::DIV(MUL * &S) {
	dividend = new SUM(S);
	divisor = new SUM(1.0);
	var_mask.setDIV();
};

DIV::DIV(SUM * &div1, SUM * &div2) {
	dividend = div1; div1 = NULL;
	divisor  = div2; div2 = NULL;
	var_mask.setDIV();
}

DIV::~DIV() {
	delete dividend;
	delete divisor;
}

ITEM * DIV::clone() {
	SUM * S1 = (SUM *)dividend->clone();
	SUM * S2 = (SUM *)divisor->clone();
	return new DIV(S1, S2);
};

void DIV::Mul(MUL * &S, bool free) {
	SUMMAND * SS = dynamic_cast<SUMMAND *>(S);
	dividend->Mul(SS, free);
	S = dynamic_cast<MUL *>(SS);
};

void DIV::Mul(DIV * &D, bool free) {
	#pragma omp parallel sections
	{
		#pragma omp section
		{
			dividend->Mul(D->dividend, free);
		}
		#pragma omp section
		{
			divisor->Mul(D->divisor, free);
		}
	}
	if (free) {
		delete D;
		D = NULL;
	}
};

ITEM* DIV::Neg() {
	DIV* result = dynamic_cast<DIV*>(this->clone());
	SUM* old = result->dividend;
	result->dividend = dynamic_cast<SUM*>(old->Neg());
	delete old;
	return result;
}

ITEM* DIV::Add(ITEM* op) {
	DIV* _THIS = dynamic_cast<DIV*>(this->clone());
	SUM* result = new SUM(_THIS);
	result->Add(op);
	return result;
}

ITEM* DIV::Sub(ITEM* op) {
	DIV* _THIS = dynamic_cast<DIV*>(this->clone());
	SUM* result = new SUM(_THIS);
	ITEM* old = op;
	op = old->Neg();
	delete old;
	result->Add(op);
	return result;
}

ITEM* DIV::Mul(ITEM* op) {
	DIV* _THIS = dynamic_cast<DIV*>(this->clone());
	SUM* result = new SUM(_THIS);
	result->Mul(op);
	return result;
}

ITEM* DIV::Div(ITEM* op) {
	DIV* _THIS = dynamic_cast<DIV*>(this->clone());
	MUL* M = dynamic_cast<MUL*>(op);
	DIV* D = dynamic_cast<DIV*>(op);
	SUM* S = dynamic_cast<SUM*>(op);
	SUM* S1 = new SUM(_THIS);
	if (M) {
		SUM* S2 = new SUM(M);
		return new DIV(S1, S2);
	}
	else if (D) {
		SUM* S2 = new SUM(D);
		return new DIV(S1, S2);
	}
	else {
		SUM* S2 = dynamic_cast<SUM*>(op->clone());
		return new DIV(S1, S2);
	}
}

ITEM* DIV::Pow(ITEM* op) {
	THROW_EXCEPTION("Can calculate power of MUL only!");
}

SUM * DIV::Divide() {
	SUM * result = new SUM(0.0);
	dividend->AccountSimilars();
	divisor->AccountSimilars();

	do {
		if (dividend->IsZero()) {
			delete this;
			return result;
		}

		map<VarMask, SUMMAND *>::iterator it_divisor;
		MUL* _dividend = NULL;
		MUL* _divisor = NULL;

		vector<const VarMask*> dividend_keys(dividend->summands.size());
		vector<SUMMAND*> dividend_vals(dividend->summands.size());
		map<VarMask, SUMMAND*>::iterator it_dividend;

		int k = 0;
		for (it_dividend = dividend->summands.begin(); it_dividend != dividend->summands.end(); it_dividend++, k++) {
			dividend_keys[k] = &it_dividend->first;
			dividend_vals[k] = it_dividend->second;
		}

		double best_card = 1E300;
		long long limit = 500000000LL / divisor->summands.size();
		for (it_divisor = divisor->summands.begin(); it_divisor != divisor->summands.end(); it_divisor++) {
			const int nThreads = 3;
			long long _best_dividend[256] = { 0 };
			double candidate_card = 0.0;
			double _minimal_card[256];
			for (int i = 0; i < nThreads; i++)
				_minimal_card[i] = 1E300;
			vector<const VarMask*>::iterator first = lower_bound(dividend_keys.begin(), dividend_keys.end(), &it_divisor->first,
				[&](const VarMask* a, const VarMask* b)->bool {
					return *a < *b;
				}
			);
			if (first != dividend_keys.end()) {
				auto clock = []()->long long {
					auto duration = std::chrono::system_clock().now().time_since_epoch();
					return std::chrono::duration_cast<std::chrono::nanoseconds>(duration).count();
				};
				atomic<bool> stop = false;
				long long start = clock();
				#pragma omp parallel for num_threads(nThreads) reduction(+:candidate_card) if(dividend_keys.end()-first > 50)
				for (long long j = first - dividend_keys.begin(); j < (long long)dividend_keys.size(); j++) {
					if (!stop.load() && dividend_vals[j]) {
						MUL* quot = dynamic_cast<MUL*>(dividend_vals[j])->CheckDiv(dynamic_cast<MUL*>(it_divisor->second));
						if (quot) {
							int id = omp_get_thread_num();
							double c = quot->card();
							candidate_card += dynamic_cast<MUL*>(dividend_vals[j])->card() - c;
							if (c < _minimal_card[id]) {
								_minimal_card[id] = c;
								_best_dividend[id] = j;
							}
							delete quot;
							if (clock() - start > limit)
								stop.store(true);
						}
					}
				}
			}
			int best = 0;
			for (int i = 1; i < nThreads; i++)
				if (_minimal_card[i] < _minimal_card[best])
					best = i;
			if (_minimal_card[best] == 1E300) {
				SUMMAND* div = dynamic_cast<SUMMAND*>(this->clone());
				result->Add(div);
				delete this;
				return result;
			}
			if (candidate_card < best_card) {
				_dividend = dynamic_cast<MUL*>(dividend_vals[_best_dividend[best]]);
				_divisor = dynamic_cast<MUL*>(it_divisor->second);
				best_card = candidate_card;
			}
			dividend_vals[_best_dividend[best]] = NULL;
		}
		if (_dividend == NULL || _divisor == NULL) {
			SUMMAND* div = dynamic_cast<SUMMAND*>(this->clone());
			result->Add(div);
			delete this;
			return result;
		}

		MUL* _quotient = _dividend->CheckDiv(_divisor);
		SUM * _rest = dynamic_cast<SUM *>(dividend->clone());
		map<VarMask, SUMMAND *>::iterator it_k;
		for (it_k = divisor->summands.begin(); it_k != divisor->summands.end(); it_k++) {
			MUL * item1 = dynamic_cast<MUL *>(_quotient->clone());
			MUL * item2 = dynamic_cast<MUL *>(it_k->second->clone());
			if (!item2)
				THROW_EXCEPTION("DIVIDE POLY/POLY: divisor contains DIV");
			item1->Mul(item2);
			item1->Mul(-1.0);
			SUMMAND * _item1 = dynamic_cast<SUMMAND *>(item1);
			_rest->Add(_item1);
		}
		_rest->AccountSimilars();
		if (_rest->summands.size() > dividend->summands.size()) {
			delete _rest;
			SUMMAND* div = dynamic_cast<SUMMAND*>(this->clone());
			result->Add(div);
			delete this;
			return result;
		}
		delete dividend;
		dividend = _rest;
		SUMMAND * _quot = dynamic_cast<SUMMAND *>(_quotient);
		result->Add(_quot);
	} while (true);
};

void DIV::AddToDividend(SUMMAND * dd) {
	dividend->Add(dd);
};

void DIV::AddToDivisor(SUMMAND * dd) {
	divisor->Add(dd);
};

bool DIV::TryAdd(SUMMAND * &S, bool free) {
	// add to dividend/divisor
	DIV * DD = dynamic_cast<DIV *>(S);
	MUL * SS = dynamic_cast<MUL *>(S);
	bool result = false;
	if (SS) {
		SUMMAND * _DD = dynamic_cast<SUMMAND *>(new DIV(SS));
		S = SS;
		result = TryAdd(_DD);
		if (result && free) {
			delete S;
			S = NULL;
		}
		return result;
	}
	if (!DD)
		return false;
	if (divisor->IsEqual(true, DD->divisor)) {
		dividend->Add(DD->dividend);
		result = true;
	} else {
		SUM * _divisor1 = dynamic_cast<SUM *>(DD->divisor->clone());
		SUM * __divisor1 = dynamic_cast<SUM *>(DD->divisor->clone());
		SUM * _divisor2 = dynamic_cast<SUM *>(divisor->clone());
//		SUM * __divisor2 = dynamic_cast<SUM *>(divisor->clone());
		#pragma omp parallel sections
		{
			#pragma omp section
			{
				dividend->Mul(_divisor1);
			}
			#pragma omp section
			{
				divisor->Mul(__divisor1);
			}
			#pragma omp section
			{
				DD->dividend->Mul(_divisor2);
			}
		}
//		DD->divisor->Mul(__divisor2);
		dividend->Add(DD->dividend);
		result = true;
	}
	if (result && free) {
		delete S;
		S = NULL;
	}
	return result;
};

bool DIV::IsEqual(bool UseK, SUMMAND * S) {
	MUL * SS = dynamic_cast<MUL *>(S);
	DIV * DD = dynamic_cast<DIV *>(S);
	if (DD) {
		return dividend->IsEqual(UseK, DD->dividend) && divisor->IsEqual(UseK, DD->divisor);
	} else if (SS) {
		DIV * D = new DIV(SS);
		bool result = IsEqual(UseK, D);
		delete D;
		return result;
	}
	return false;
};

bool DIV::IsZero() {
	return dividend->IsZero();
};

bool DIV::IsOne() {
	return dividend->IsOne() && divisor->IsOne();
};

void DIV::sprint(char ** Vars, int * maxPows, string * Buf, bool insert_pow_op) {
	*Buf += "(";
	dividend->sprint(Vars, maxPows, Buf, insert_pow_op);
	*Buf += ")/(";
	divisor->sprint(Vars, maxPows, Buf, insert_pow_op);
	*Buf += ")";
};

ITEM * REGULARIZE(ITEM * &SRC) {
	MUL * SS = dynamic_cast<MUL *>(SRC);
	DIV * DD = dynamic_cast<DIV *>(SRC);
	SUM * PP = dynamic_cast<SUM *>(SRC);
	if (SS) return SS;
	if (PP) {
		// simplify members and find dividend/divider
		map<VarMask, SUMMAND *>::iterator it;
		vector<SUMMAND*> additions;
		DIV* DDD = NULL;
		for (it = PP->summands.begin(); it != PP->summands.end(); ) {
			ITEM * SMND = dynamic_cast<ITEM *>(it->second);
			SMND = REGULARIZE(SMND);
			SUMMAND* _SMND = dynamic_cast<SUMMAND*>(SMND);
			if (SMND)
				if (_SMND) {
					if (*it->second->get_mask() == *_SMND->get_mask()) {
						if (_SMND->get_mask()->isDIV())
							DDD = dynamic_cast<DIV*>(_SMND);
						it->second = _SMND;
						it++;
					}
					else {
						it = PP->summands.erase(it);
						additions.push_back(_SMND);
					}
				} else {
					THROW_EXCEPTION("Can't REGULARIZE");
				}
		}
		if (DDD) {
			DD = new DIV(0.0);
			for (it = PP->summands.begin(); it != PP->summands.end(); it++) {
				if (!DD->TryAdd(it->second))
					THROW_EXCEPTION("Can't REGULARIZE : DIV_1");
			}
			for (SUMMAND* a : additions)
				if (!DD->TryAdd(a))
					THROW_EXCEPTION("Can't REGULARIZE : DIV_2");
			delete SRC;
			SRC = NULL;
			return new SUM(DD);
		}
		// add others summands to dividend/divider
		for (SUMMAND* a : additions)
			PP->Add(a);
		// account similar members
		PP->AccountSimilars();
		return PP;
	}
	if (DD) {
		ITEM * dd = dynamic_cast<ITEM *>(DD->dividend);
		DD->dividend = (SUM *)REGULARIZE(dd);
		ITEM * dr = dynamic_cast<ITEM *>(DD->divisor);
		DD->divisor = (SUM *)REGULARIZE(dr);
		if (DD->dividend->summands.size()==1 && DD->divisor->summands.size()>0 ||
			DD->divisor->summands.size()==1 && DD->dividend->summands.size()>0) {
			DIV * dop1 = DD->dividend->summands.size()==1 ? dynamic_cast<DIV *>(DD->dividend->summands.begin()->second) : NULL;
			DIV * dop2 = DD->divisor->summands.size()==1 ? dynamic_cast<DIV *>(DD->divisor->summands.begin()->second) : NULL;
			if (!dop1 && dop2) {
				// sum/[dividend/divisor]
				DD->dividend->Mul(dop2->divisor);
				SUM * oldDivisor = DD->divisor;
				DD->divisor = dop2->dividend;
				dop2->dividend = NULL;
				delete oldDivisor;
			}
			if (dop1 && !dop2) {
				// [dividend/divisor]/sum
				dop1->divisor->Mul(DD->divisor);
				DD->divisor = dop1->divisor;
				dop1->divisor = NULL;
				SUM * oldDividend = DD->dividend;
				DD->dividend = dop1->dividend;
				dop1->dividend = NULL;
				delete oldDividend;
			}
			if (dop1 && dop2) {
				// [dividend/divisor]/[dividend/divisor]
				dop1->dividend->Mul(dop2->divisor);
				dop1->divisor->Mul(dop2->dividend);
				delete DD->divisor;
				DD->divisor = dop1->divisor;
				dop1->divisor = NULL;
				SUM * oldDividend = DD->dividend;
				DD->dividend = dop1->dividend;
				dop1->dividend = NULL;
				delete oldDividend;
			}
		}
		return DD;
	}
	return NULL;
}

ITEM * SIMPLIFY(ITEM * &SRC) {
	ITEM * S = REGULARIZE(SRC);
	ITEM * _S = S;
	DIV * D = dynamic_cast<DIV *>(S);
	if (D)
		_S = D->Divide();
	else {
		SUM * SS = dynamic_cast<SUM *>(S);
		if (SS && SS->summands.size() == 1 && SS->summands.begin()->first.isDIV()) {
			D = dynamic_cast<DIV *>(SS->summands.begin()->second);
			SS->summands.clear();
			delete SS;
			S = NULL;
			_S = D->Divide();
		}
	}
	return _S;
}

ITEM * SUBSTITUTE_SQRS(ITEM * &SRC, int first_sqrt_var, char ** Vars, map<string, ITEM *> &SUBSTS) {
	MUL * SS = dynamic_cast<MUL *>(SRC);
	DIV * DD = dynamic_cast<DIV *>(SRC);
	SUM * PP = dynamic_cast<SUM *>(SRC);
	if (SS) {
		for (unsigned int i = 1; i < SS->vars.size(); i++) {
			if (SS->vars[i] >= first_sqrt_var &&
				fabs(1.0-SS->pows[i]) > 1E-9 && fabs(-1.0-SS->pows[i]) > 1E-9) {
				SUM * Z2 = dynamic_cast<SUM *>(SUBSTS[Vars[SS->vars[i]]]->clone());
				SUM * mult = dynamic_cast<SUM *>(Z2->clone());
				MUL * NEW = dynamic_cast<MUL *>(SRC->clone());
				NEW->var_mask.clear(SS->vars[i]);
				int p = (int)(SS->pows[i] >= 0.0 ? 0.5+SS->pows[i] : -(0.5-SS->pows[i]));
				if (abs(p)%2) {
					NEW->var_mask.set_mask(1.0, SS->vars[i]);
					NEW->pows[i] = p > 0 ? 1.0 : -1.0;
				} else {
					NEW->vars.erase(NEW->vars.begin()+i);
					NEW->pows.erase(NEW->pows.begin()+i);
				}
				p /= 2;
				int _p = abs(p);
				while (--_p) {
					SUM * _mult = dynamic_cast<SUM *>(mult->clone());
					Z2->Mul(_mult);
				}
				delete mult;
				SUMMAND * __NEW = dynamic_cast<SUMMAND *>(NEW);
				if (p < 0) {
					DIV * D = new DIV(1.0);
					delete D->divisor;
					Z2->AccountSimilars();
					D->divisor = Z2;
					D->Mul(NEW);
					Z2 = new SUM(0.0);
					SUMMAND * _D = dynamic_cast<SUMMAND *>(D);
					Z2->Add(_D, true);
				} else {
					Z2->Mul(__NEW);
					Z2->AccountSimilars();
				}

				delete SRC;
				SRC = NULL;
				ITEM * _Z2 = dynamic_cast<ITEM *>(Z2);
				return SUBSTITUTE_SQRS(_Z2, first_sqrt_var, Vars, SUBSTS);
			}
		}
		ITEM * result = SRC;
		SRC = NULL;
		return result;
	} else if (PP) {
		map<VarMask, SUMMAND *>::iterator it;
		vector<ITEM *> modified;
		vector<ITEM *>::iterator it_modified;
		for (it = PP->summands.begin(); it != PP->summands.end(); ) {
			ITEM * ARG = dynamic_cast<ITEM *>(it->second);
			ITEM * item = SUBSTITUTE_SQRS(ARG, first_sqrt_var, Vars, SUBSTS);
			if (item != it->second) {
				modified.push_back(item);
				it = PP->summands.erase(it);
			} else {
				it++;
			}
		}
		for (it_modified = modified.begin(); it_modified != modified.end(); it_modified++) {
			SUMMAND * _SS = dynamic_cast<SUMMAND *>(*it_modified);
			SUM * _PP = dynamic_cast<SUM *>(*it_modified);
			if (_SS)
				PP->Add(_SS);
			else if (_PP)
				PP->Add(_PP, false);
		}
		PP->AccountSimilars();
		SRC = NULL;
		return PP;
	} else if (DD) {
		ITEM * _dividend = dynamic_cast<ITEM *>(DD->dividend);
		DD->dividend = (SUM *) SUBSTITUTE_SQRS(_dividend, first_sqrt_var, Vars, SUBSTS);
		ITEM * _divisor = dynamic_cast<ITEM *>(DD->divisor);
		DD->divisor = (SUM *) SUBSTITUTE_SQRS(_divisor, first_sqrt_var, Vars, SUBSTS);
		SRC = NULL;
		return DD;
	}
	return NULL;
}

bool PRESENT_SQRS(ITEM * SRC, int first_sqrt_var) {
	MUL * SS = dynamic_cast<MUL *>(SRC);
	DIV * DD = dynamic_cast<DIV *>(SRC);
	SUM * PP = dynamic_cast<SUM *>(SRC);
	if (SS) {
		for (unsigned int i = 1; i < SS->vars.size(); i++) {
			if (SS->vars[i] >= first_sqrt_var &&
				fabs(1.0-SS->pows[i]) > 1E-9 && fabs(-1.0-SS->pows[i]) > 1E-9) {
				return true;
			}
		}
		return false;
	} else if (PP) {
		map<VarMask, SUMMAND *>::iterator it;
		for (it = PP->summands.begin(); it != PP->summands.end(); it++) {
			ITEM * ARG = dynamic_cast<ITEM *>(it->second);
			if (PRESENT_SQRS(ARG, first_sqrt_var))
				return true;
		}
		return false;
	} else if (DD) {
		bool result1 = false;
		bool result2 = false;
		#pragma omp parallel sections
		{
			#pragma omp section
			{
				ITEM * _dividend = dynamic_cast<ITEM *>(DD->dividend);
				if (PRESENT_SQRS(_dividend, first_sqrt_var))
					result1 = true;
			}
			#pragma omp section
			{
				ITEM * _divisor = dynamic_cast<ITEM *>(DD->divisor);
				if (PRESENT_SQRS(_divisor, first_sqrt_var))
					result2 = true;
			}
		}
		return result1 || result2;
	}
	return false;
}

#endif
