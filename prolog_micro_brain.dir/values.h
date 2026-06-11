#ifndef __VALUES_H__
#define __VALUES_H__

#define _CRT_SECURE_NO_WARNINGS
#define _HAS_STD_BYTE 0

#ifdef __APPLE__
#include <mlx/mlx.h>
#endif

#include "elements.h"

#include <atomic>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <functional>
#include <list>
#include <map>
#include <random>
#include <mutex>
#include <set>

#include <omp.h>

using namespace std;

class _interpreter;
class interpreter;
class frame_item;
class thread_pool;
class _predicate;
class clause;
class predicate_item;
class predicate_item_user;
class generated_vars;
class term;
class _list;
class tthread;
class pro_thread;
class context;
class tframe_item;
class journal;
class ITEM;
class SUM;

#ifndef _MSC_VER
#include <sys/resource.h>
#include <unistd.h>
#include <pthread.h>
#include <dlfcn.h>

unsigned long long getTotalSystemMemory();
unsigned int getTotalProcs();

typedef void* HMODULE;

HMODULE LoadLibrary(const wchar_t* _fname);

void* GetProcAddress(HMODULE handle, const char* fname);

void FreeLibrary(HMODULE handle);
#else
#include <Windows.h>
#endif

typedef unsigned long long clock_rdtsc;
clock_rdtsc __clock();

void reverse(char s[]);

char* __ltoa(long long n, char s[], long long radix);

#define __itoa __ltoa

template<class T> class stack_container : public vector<T> {
public:
	virtual void push_back(const T& v) {
		if (this->capacity() == this->size())
			this->reserve((int)(1.5 * this->size()));
		vector<T>::push_back(v);
	}

	virtual void push(const T& v) { this->push_back(v); }
	virtual void pop() { this->pop_back(); }
	virtual T top() { return this->back(); }
};

typedef std::mutex fastmux;

class string_atomizer {
	map<string, unsigned int> hash;
	vector<const string*> table;
	bool forking;
	fastmux locker;
public:
	string_atomizer();
	void set_forking(bool v);
	unsigned int get_atom(const string& s);
	const string get_string(unsigned int atom);
};

extern string_atomizer atomizer;

class value {
protected:
	std::atomic<int> refs;
public:
	value();

	virtual void use();
	virtual void free();

	virtual int get_refs();

	virtual value* fill(context* CTX, frame_item* vars) = 0;
	virtual value* copy(context* CTX, frame_item* f, int unwind = 0) = 0;
	virtual value* const_copy(context* CTX, frame_item* f, int unwind = 0);
	virtual bool unify(context* CTX, frame_item* ff, value* from) = 0;
	virtual bool defined() = 0;

	virtual string to_str(bool simple = false) = 0;

	virtual void escape_vars(context* CTX, frame_item* ff) = 0;

	virtual string make_str();

	virtual string export_str(bool simple = false, bool double_slashes = true);

	virtual void write(basic_ostream<char>* outs, bool simple = false);
};

typedef struct {
	unsigned long long* _name;
	value* ptr;
} mapper;

inline unsigned int get_name_code(unsigned long long name) {
	return (unsigned int)(name & 0xFFFFFFFF);
}

inline char get_first_char(unsigned long long name) {
	return (char)((name >> 32) & 0xFF);
}

inline unsigned int get_wind(unsigned long long name) {
	return (unsigned int)((name >> 40) & 0xFFFFFF);
}

inline unsigned long long construct_var_name(unsigned int wind, unsigned long long _name, char first) {
	return _name + (((unsigned long long)first) << 32) + (((unsigned long long)wind) << 40);
}

inline void escape_name(unsigned long long& name) {
	unsigned int wind = get_wind(name);
	name &= 0xFFFFFFFFFFLL;
	name += ((unsigned long long)(wind + 1)) << 40;
}

inline void unescape_name(unsigned long long& name, unsigned int n) {
	unsigned int wind = get_wind(name);
	name &= 0xFFFFFFFFFFLL;
	name += ((unsigned long long)(wind - n)) << 40;
}

class any : public value {
public:
	any();

	virtual void escape_vars(context* CTX, frame_item* ff);

	virtual value* fill(context* CTX, frame_item* vars);
	virtual value* copy(context* CTX, frame_item* f, int unwind = 0);
	virtual bool unify(context* CTX, frame_item* ff, value* from);
	virtual bool defined();;

	virtual string to_str(bool simple = false);
};

class var : public value {
	unsigned long long name;
public:
	var(unsigned int _name);

	var(unsigned long long _name, int);

	virtual void escape_vars(context* CTX, frame_item* ff);

	virtual value* fill(context* CTX, frame_item* vars);

	virtual value* copy(context* CTX, frame_item* f, int unwind = 0);

	virtual void write(basic_ostream<char>* outs, bool simple = false);

	virtual const string get_name();

	virtual const unsigned long long get_id();

	virtual bool unify(context* CTX, frame_item* ff, value* from);

	virtual bool defined();;

	virtual string to_str(bool simple = false);
};

class int_number : public value {
	friend class float_number;
private:
	long long v;
public:
	int_number(long long _v);

	virtual void escape_vars(context* CTX, frame_item* ff);

	virtual value* fill(context* CTX, frame_item* vars);
	virtual value* copy(context* CTX, frame_item* f, int unwind = 0);
	virtual bool unify(context* CTX, frame_item* ff, value* from);
	virtual bool defined();;

	virtual double get_value();

	virtual string to_str(bool simple = false);

	void inc();
	void dec();
};

class float_number : public value {
	friend class int_number;
private:
	double v;
public:
	float_number(double _v);

	virtual void escape_vars(context* CTX, frame_item* ff);

	virtual value* fill(context* CTX, frame_item* vars);
	virtual value* copy(context* CTX, frame_item* f, int unwind = 0);
	virtual bool unify(context* CTX, frame_item* ff, value* from);
	virtual bool defined();;

	virtual double get_value();

	virtual string to_str(bool simple = false);

	void inc();
	void dec();
};

class term : public value {
protected:
	unsigned int name;
	vector<value*> args;
	signed char cached_defined;
public:
	term(const string& _name, const int init_refs = 1);

	term(const term& src);

	virtual ~term();

	virtual void change_name(const string& _name);

	virtual void free();

	virtual void use();

	virtual void escape_vars(context* CTX, frame_item* ff);

	virtual const string get_name();

	virtual const unsigned int get_id();

	virtual const vector<value*>& get_args();

	virtual value* fill(context* CTX, frame_item* vars);

	virtual void add_arg(context* CTX, frame_item* f, value* v, int unwind = 0);

	virtual value* copy(context* CTX, frame_item* f, int unwind = 0);

	virtual bool unify(context* CTX, frame_item* ff, value* from);
	virtual bool defined();;

	virtual string to_hex(char SEP);

	virtual string from_hex(char SEP);

	virtual string to_str(bool simple = false);

	virtual string escape_specials(const string& src, bool double_slashes = true);

	virtual string export_str(bool simple = false, bool double_slashes = true);
};

class network {
public:
	int NInputs;
	std::string FNAME, DAT_FILE_NAME;
	int NRows = 0;
	int NCols = 0;
	int NCC[512];
	int NL;
	int NN[1024];
	long double best_err;

	int MAXPROBES = 32;

	bool probed = false;
	int nProbes = 1;
	int nCPUs = 1;

	int best_nProbes = 1;
	int best_nCPUs = 1;
	double best_time = 1E300;

	typedef long double LAYER[64][8192];

	LAYER * YN;

	long double MMIN[512];
	long double MMAX[512];
	long double mmin[512];
	long double mmax[512];

	long double NUMIN[512], numin[512];
	long double NUMAX[512], numax[512];

	long double d[512];
	long double nud[512];

	int NW = 0;
	int NB = 0;

	long double* W = NULL;
	long double* B = NULL;

	long double tempX[512];

	long double* X[512] = { NULL };
	long double* Y[512] = { NULL };
	long double* YS[512] = { NULL };
	long double* ERR[512] = { NULL };

	int coord_b[1024];
	double d_b[1024];
	int coord_w[1024];
	double d_w[1024];

	typedef struct {
		int kind;
		int N;
		long double* KF;
	} VARIANT;

	const int HOW_MANY = 5;

	const int _div = 20;

	const static int n_kinds = 5;

	typedef enum { vkPoly = 0, vkPolySqr = 1, vkPolyRev = 2, vkPolySqrRev = 3, vkLinear = 4 } variant_kinds;

	const char* kinds[n_kinds] = { "POLY", "POLYSQR", "POLYREV", "POLYSQRREV", "LIN" };

	network(const network& src);

	network(const std::string& FName, const std::string& content);

	network(network* templ, int ni, int n1, int n2, bool first, bool last, int out);

	virtual const std::string& fname();

	virtual void setX(unsigned int i, long double v);

	virtual void set_rowX(unsigned int i, long double v);

	virtual unsigned int nX();

	virtual unsigned int nY();

	virtual long double getY(int i);

	virtual void sim(long double * result);

	virtual void filter_simplification(vector<string>& result) {
		map< int, set<int> > branches;
		for (int pq = 0; pq < result.size(); pq++) {
			string cur = result[pq];
			int cur_signature = 0;
			unsigned int ptr;
			for (ptr = 0; ptr < cur.length() && isdigit(cur[ptr]); ptr++)
				cur_signature = 10 * cur_signature + (cur[ptr] - '0');
			if (branches.find(cur_signature) == branches.end())
				branches[cur_signature] = set<int>();
			branches[cur_signature].insert(pq);
			result[pq] = cur.substr(ptr + 1);
		}
		for (const auto& [signature, nums] : branches) {
			set<int>::iterator it = nums.begin();
			string first = result[*it];
			it++;
			while (it != nums.end()) {
				string cur = result[*it];
				size_t LL = min(cur.length(), first.length());
				size_t ps = 0;
				for (; ps < LL; ps++)
					if (first[ps] != cur[ps]) {
						while (ps >= 0 && cur[ps] >= ' ')
							ps--;
						break;
					}
				result[*nums.begin()] += "\n";
				result[*nums.begin()] += cur.substr(ps + 1);
				result[*it] = "";
				it++;
			}
		}
		unsigned int c = 0;
		while (c < result.size())
			if (result.at(c).length() == 0)
				result.erase(result.begin() + c);
			else
				c++;
	}

	virtual bool load_data();

	virtual void unload_data();

	inline long double S(long double s);;

	virtual void PERTURBED_NET(int i, long double* SMIN = NULL, long double* SMAX = NULL,
		vector<long double>* XX = NULL, vector<long double>* YY = NULL);

	virtual void NET(int i, long double* SMIN = NULL, long double* SMAX = NULL,
		vector<long double>* XX = NULL, vector<long double>* YY = NULL);;

	virtual bool train(int MAX_EPOCHS);

	virtual vector<std::string> simplify(bool to_chain, int maxN, int NVARIANTS, const vector<std::string> * OUT_VAR, set<std::string>& defined);

	virtual ~network();

	virtual bool equals(network* from);

	virtual const string get();

	static std::string create(::_list& nlayers, const std::string& dat_file, ::_list& inps, const vector<int> & out);

	/* LU - разложение  с выбором максимального элемента по диагонали */
	bool _GetLU(int NN, int* iRow, long double* A, long double* LU);

	/* Метод LU - разложения */
	bool _SolveLU(int NN, int* iRow, long double* LU, long double* Y, long double* X);

	long double* MNK_of_X(int N,
		const vector<long double> W,
		const vector<long double> X,
		const vector<long double> Y,
		double& err);

	typedef map<string, ITEM*> zVars;

	void* BUILD_FUNC(int NPP, int& NVARIANTS, bool Simplify,
		vector<string> * BEST,
		const vector<string> * OUT_VAR, set<std::string> * defined,
		char** Vars,
		vector<vector<VARIANT>*>_VARS,
		int layer, zVars * zvars, string* Scheme = NULL, SUM** Inputs = NULL);

	vector<string> ANALYZE(int NPP, int maxN, int& NVARIANTS, const vector<std::string> * OUT_VAR, set<std::string> * defined, bool Simplify,
		long double* SMIN, long double* SMAX, int* SFREQ,
		vector<long double> XX[], vector<long double> YY[]);
};

class block_network : public network {
protected:
	unsigned int n_networks = 0;
	network** NETWORKS = NULL;
public:
	block_network(const block_network& src);

	block_network(const std::string& FName, const std::string& content);

	virtual bool train(int MAX_EPOCHS);

	virtual void PERTURBED_NET(int i, long double* SMIN = NULL, long double* SMAX = NULL,
		vector<long double>* XX = NULL, vector<long double>* YY = NULL);;

	virtual void NET(int i, long double* SMIN = NULL, long double* SMAX = NULL,
		vector<long double>* XX = NULL, vector<long double>* YY = NULL);;

	virtual vector<std::string> simplify(bool to_chain, int maxN, int NVARIANTS, const vector<std::string> * OUT_VAR, set<std::string>& defined);

	virtual ~block_network();

	virtual bool equals(network* from);

	static std::string create(::_list& nlayers, const std::string& dat_file, ::_list& inps, int out) = delete;

};

class nnet : public term {
private:
	network* net;
public:
	nnet();

	nnet(const nnet& src);

	nnet(const std::string& fname, ifstream& in, bool block = false);

	virtual ~nnet();

	virtual value* const_copy(context* CTX, frame_item* f, int unwind = 0);

	virtual nnet* granularize();

	virtual void free();

	virtual const string get_content();

	virtual bool train(int MAX_EPOCHS);

	virtual vector<string> simplify(bool to_chain, int maxN, set<std::string>& defined);

	virtual void sim(long double * result);
	virtual unsigned int nX();
	virtual unsigned int nY();
	virtual long double getY(int i);
	virtual void setX(unsigned int i, long double v);

	virtual value* copy(context* CTX, frame_item* f, int unwind = 0);

	virtual void add_arg(context* CTX, frame_item* f, value* v, int unwind = 0);

	virtual bool unify(context* CTX, frame_item* ff, value* from);

	virtual string to_str(bool simple = false);
};

class indicator : public value {
private:
	string name;
	int arity;
public:
	indicator(const string& _name, int _arity);

	virtual void escape_vars(context* CTX, frame_item* ff);

	virtual const string& get_name();

	virtual int get_arity();

	virtual value* fill(context* CTX, frame_item* vars);

	virtual value* copy(context* CTX, frame_item* f, int unwind = 0);
	virtual bool unify(context* CTX, frame_item* ff, value* from);
	virtual bool defined();

	virtual string to_str(bool simple = false);
};

class _list : public value {
	friend class predicate_item_nth;

	stack_container<value*> val;
	bool is_of_chars;
	string chars;
	value* tag;
	signed char cached_defined;
public:
	_list(const stack_container<value*>& v, value* _tag);

	_list(const string& v, value* _tag);

	virtual ~_list();

	virtual void free();

	virtual void use();

	virtual bool of_chars();
	virtual const string& get_chars();
	virtual void convert_non_chars(context* CTX);

	virtual void escape_vars(context* CTX, frame_item* ff);

	int size();

	value* get_last(context* CTX);

	value* get_nth(int n, bool inc_ref);

	bool set_nth(int n, value* v);

	void iterate(std::function<void(value*)> check);

	void split(context* CTX, frame_item* f, int p, value*& L1, value*& L2);

	void const_split(context* CTX, frame_item* f, int p, value*& L1, value*& L2);

	_list* from(context* CTX, frame_item* f, stack_container<value*>::iterator starting);

	_list* from(context* CTX, frame_item* f, string::iterator starting);

	_list* const_from(context* CTX, frame_item* f, stack_container<value*>::iterator starting);

	_list* const_from(context* CTX, frame_item* f, string::iterator starting);

	virtual value* fill(context* CTX, frame_item* vars);

	virtual _list* append(context* CTX, frame_item* f, _list* L2);

	virtual value* copy(context* CTX, frame_item* f, int unwind = 0);

	virtual void add(context* CTX, value* v);

	virtual void set_tag(value* new_tag);

	virtual bool get(context* CTX, frame_item* f, stack_container<value*>* dest);

	virtual bool unify(context* CTX, frame_item* ff, value* from);
	virtual bool defined();

	virtual string make_str();

	virtual string to_str(bool simple = false);

	virtual string export_str(bool simple = false, bool double_slashes = true);
};

class journal_item;
class journal;

typedef enum { jInsert = 0, jDelete } jTypes;

class context {
public:
	context(bool locals_in_forked, bool transactable_facts, predicate_item* forker, int RESERVE, context* parent, tframe_item* tframe, predicate_item* starting, predicate_item* ending, interpreter* prolog);

	virtual void clearDBJournals();

	virtual ~context();

	bool forked() {
		context* C = this;
		while (C && !C->THR)
			C = C->parent;
		bool result = C && C->THR;
		return result;
	}

	virtual void set_rollback(bool val) {
		rollback = val;
	}

	context* parent;
	interpreter* prolog;
	predicate_item* forker;
	predicate_item* starting;
	predicate_item* ending;
	bool locals_in_forked;
	bool transactable_facts;
	bool rollback;

	long long pseudo_time;

	stack_container<std::function<bool(interpreter*, context*)>> cut_query;

	stack_container<frame_item*> SEQ_RESULT;
	stack_container<predicate_item*> GENERATORS;
	stack_container<predicate_item*> SEQ_START;
	stack_container<predicate_item*> SEQ_END;
	stack_container<tframe_item*> FRAMES_TO_DELETE;

	fastmux* DBLOCK;
	map< string, std::atomic<vector<term*>*>>* DB;
	map<unsigned long long, std::atomic<journal*>>* DBJournal;

	vector<context*> CONTEXTS;
	std::atomic<tframe_item*> INIT;
	std::atomic<tframe_item*> FRAME;
	tthread* THR;

	stack_container<predicate_item*> CALLS;
	stack_container<frame_item*> FRAMES;
	stack_container<context*> CTXS;
	stack_container<bool> NEGS;
	stack_container<int> _FLAGS;
	stack_container<predicate_item_user*> PARENT_CALLS;
	stack_container<int> PARENT_CALL_VARIANT;
	stack_container<clause*> CLAUSES;
	std::list<int> FLAGS;
	stack_container<int> LEVELS;
	stack_container<generated_vars*> TRACE;
	stack_container<long long> START_TIMES;
	stack_container<clause*> START_CLAUSES;
	stack_container<vector<value*>**> TRACEARGS;
	stack_container<predicate_item*> TRACERS;
	stack_container<int> ptrTRACE;

	fastmux pages_mutex;

	virtual context* add_page(bool locals_in_forked, bool transactable_facts, predicate_item* forker, tframe_item* f, predicate_item* starting, predicate_item* ending, interpreter* prolog);

	virtual void register_db_read(const unsigned long long iid);

	virtual void register_db_write(const unsigned long long iid, jTypes t, value* data, int position, journal* src = NULL);

	virtual bool join(bool sequential_mode, int K, frame_item* f, interpreter* INTRP, int& sequential, vector<frame_item*>* rest, long long& pseudo_duration, predicate_item* starred);

	virtual void apply_transactional_db_to_parent(const std::string& fact);
};

class frame_item {
protected:
	friend class tframe_item;

	unsigned long long* names;
	int names_length;
	int names_capacity;

	vector<mapper> vars;

	unsigned long long* deleted;
public:
	frame_item(unsigned int _name_capacity = 32, unsigned int _vars_capacity = 8, context* CTX = NULL, frame_item* inheriting = NULL);

	virtual ~frame_item();

	virtual bool lock();
	virtual void unlock();

	virtual void forced_import_transacted_globs(context* CTX, frame_item* inheriting);

	virtual void import_transacted_globs(context* CTX, frame_item* inheriting);

	virtual void add_local_names(bool locals_in_forked, std::set<unsigned long long>& s);

	virtual void sync(bool _locked, bool not_sync_globs, context* CTX, frame_item* other);

	virtual frame_item* copy(context* CTX);

	virtual tframe_item* tcopy(context* CTX, _interpreter* INTRP, bool import_globs);

	virtual void register_write(const std::string& name);

	int get_size();

	virtual value* at(int i);

	virtual const string atn(int i);

	int find(const unsigned long long what, bool& found);

	void escape(unsigned long long& _name);

	virtual void set(bool _locked, context* CTX, const unsigned long long name, value* v, bool set_time_zero = false);

	virtual int unset(bool _locked, context* CTX, const unsigned long long name);

	virtual value* get(bool _locked, context* CTX, unsigned long long name, int unwind = 0);

	virtual void register_facts(bool _locked, context* CTX, std::set<unsigned long long>& names);

	virtual void unregister_facts(bool _locked, context* CTX);

	virtual void register_fact_group(bool _locked, context* CTX, unsigned long long& fact, journal* J);

	virtual void unregister_fact_group(bool _locked, context* CTX, unsigned long long& fact);
};

class tframe_item : public frame_item {
	static const int nn = 6;

	friend class frame_item;
	friend class journal;

	typedef struct {
		clock_rdtsc last_reads;
		clock_rdtsc first_writes;
		clock_rdtsc last_writes;
		clock_rdtsc first_reads;
	} var_info;

	int info_capacity;
	var_info micro_info[nn] = { 0 };
	var_info* info_vars;

	clock_rdtsc creation;

	fastmux mutex;
public:
	tframe_item(unsigned int _name_capacity = 32, unsigned int _vars_capacity = 5, context* CTX = NULL, frame_item* inheriting = NULL);

	virtual ~tframe_item();

	virtual bool lock();
	virtual void unlock();

	virtual void set(bool _locked, context* CTX, const unsigned long long name, value* v, bool set_time_zero = false);

	virtual value* get(bool _locked, context* CTX, const unsigned long long name, int unwind = 0);

	virtual int unset(bool _locked, context* CTX, const unsigned long long name);

	virtual void register_write(const unsigned long long name);

	virtual clock_rdtsc first_write(const unsigned long long vname);

	virtual clock_rdtsc last_read(const unsigned long long vname);

	virtual clock_rdtsc first_read(const unsigned long long vname);

	virtual clock_rdtsc last_write(const unsigned long long vname);

	virtual void set_written_new(frame_item* src);

	virtual void statistics(const unsigned long long vname, clock_rdtsc& cr, clock_rdtsc& fw, clock_rdtsc& fr, clock_rdtsc& lw, clock_rdtsc& lr);

	virtual void register_fact_group(bool _locked, context* CTX, unsigned long long& fact, journal* J);

	virtual void unregister_fact_group(bool _locked, context* CTX, unsigned long long& fact);

	virtual void sync(bool _locked, bool not_sync_globs, context* CTX, frame_item* other);

	virtual frame_item* copy(context* CTX);

	virtual tframe_item* tcopy(context* CTX, _interpreter* INTRP);
};

class journal_item {
public:
	jTypes type;
	value* data;
	int position;

	journal_item(jTypes t, value* data, int position);

	virtual ~journal_item();
};

class journal {
public:
	clock_rdtsc creation;
	clock_rdtsc first_write, last_write, first_read, last_read;

	vector<journal_item*> log;

	journal();

	virtual ~journal();

	virtual void register_read();

	virtual void register_write(jTypes t, value* data, int position, journal* src = NULL);
};

class _interpreter {
public:
	predicate_item_user* starter;
	HMODULE xpathInductLib;
	char env[65536 * 4];
	bool xpath_compiled;
	bool xpath_loaded;

	bool forking;
public:
	typedef enum {
		id_append = 0,
		id_sublist,
		id_delete,
		id_member,
		id_last,
		id_reverse,
		id_for,
		id_length,
		id_max_list,
		id_atom_length,
		id_nth,
		id_page_id,
		id_thread_id,
		id_atom_concat,
		id_atom_chars,
		id_atom_codes,
		id_atom_hex,
		id_atom_hexs,
		id_number_atom,
		id_number,
		id_consistency,
		id_listing,
		id_current_predicate,
		id_findall,
		id_functor,
		id_predicate_property,
		id_spredicate_property_pi,
		id_eq,
		id_neq,
		id_less,
		id_greater,
		id_term_split,
		id_g_assign,
		id_g_assign_nth,
		id_g_read,
		id_fail,
		id_true,
		id_change_directory,
		id_open,
		id_close,
		id_get_char,
		id_peek_char,
		id_read_token,
		id_read_token_from_atom,
		id_mars,
		id_mars_decode,
		id_unset,
		id_write,
		id_write_to_atom,
		id_write_term,
		id_write_term_to_atom,
		id_nl,
		id_file_exists,
		id_unlink,
		id_rename_file,
		id_seeing,
		id_telling,
		id_seen,
		id_told,
		id_see,
		id_tell,
		id_set_iteration_star_packet,
		id_repeat,
		id_random,
		id_randomize,
		id_regularize,
		id_add,
		id_mul,
		id_div,
		id_to_chain,
		id_nsimplify,
		id_granularize,
		id_nnetff,
		id_char_code,
		id_nload,
		id_nsave,
		id_train,
		id_sim,
		id_get_code,
		id_at_end_of_stream,
		id_open_url,
		id_track_post,
		id_consult,
		id_assert,
		id_asserta,
		id_assertz,
		id_retract,
		id_retractall,
		id_inc,
		id_halt,
		id_load_classes,
		id_init_xpathing,
		id_induct_xpathing,
		id_import_model_after_induct,
		id_unload_classes,
		id_var,
		id_nonvar,
		id_get_icontacts,
		id_get_ocontacts,
		id_rollback,
		id_optimize_load,
		id_parallelize_level
	} ids;

	thread_pool* THREAD_POOL;
	fastmux VARLOCK;
	unsigned int ITERATION_STAR_PACKET;

	bool load_optimized = false; // true;
	long long min_parallelizing_time = -1; // 1000;

	map<string, std::set<string>*> consulted;
	map<string, long long> consulted_cs;

	map<string, ids> MAP{
		{ "append", id_append },
		{ "sublist", id_sublist },
		{ "delete", id_delete },
		{ "member", id_member },
		{ "last", id_last },
		{ "reverse", id_reverse },
		{ "for", id_for },
		{ "length", id_length },
		{ "max_list", id_max_list },
		{ "atom_length", id_atom_length },
		{ "nth", id_nth },
		{ "page_id", id_page_id },
		{ "thread_id", id_thread_id },
		{ "atom_concat", id_atom_concat },
		{ "atom_chars", id_atom_chars },
		{ "atom_codes", id_atom_codes },
		{ "atom_hex", id_atom_hex },
		{ "atom_hexs", id_atom_hexs },
		{ "number_atom", id_number_atom },
		{ "number", id_number },
		{ "consistency", id_consistency },
		{ "listing", id_listing },
		{ "current_predicate", id_current_predicate },
		{ "findall", id_findall },
		{ "functor", id_functor },
		{ "predicate_property", id_predicate_property },
		{ "$predicate_property_pi", id_spredicate_property_pi },
		{ "eq", id_eq },
		{ "=", id_eq },
		{ "==", id_eq },
		{ "neq", id_neq },
		{ "\\=", id_neq },
		{ "less", id_less },
		{ "<", id_less },
		{ "greater", id_greater },
		{ ">", id_greater },
		{ "term_split", id_term_split },
		{ "=..", id_term_split },
		{ "g_assign", id_g_assign },
		{ "g_assign_nth", id_g_assign_nth },
		{ "g_read", id_g_read },
		{ "fail", id_fail },
		{ "true", id_true },
		{ "change_directory", id_change_directory },
		{ "open", id_open },
		{ "close", id_close },
		{ "get_char", id_get_char },
		{ "peek_char", id_peek_char },
		{ "read_token", id_read_token },
		{ "read_token_from_atom", id_read_token_from_atom },
		{ "mars", id_mars },
		{ "mars_decode", id_mars_decode },
		{ "unset", id_unset },
		{ "write", id_write },
		{ "write_to_atom", id_write_to_atom },
		{ "write_term", id_write_term },
		{ "write_term_to_atom", id_write_term_to_atom },
		{ "nl", id_nl },
		{ "file_exists", id_file_exists },
		{ "unlink", id_unlink },
		{ "rename_file", id_rename_file },
		{ "seeing", id_seeing },
		{ "telling", id_telling },
		{ "seen", id_seen },
		{ "told", id_told },
		{ "see", id_see },
		{ "tell", id_tell },
		{ "set_iteration_star_packet", id_set_iteration_star_packet },
		{ "repeat", id_repeat },
		{ "random", id_random },
		{ "randomize", id_randomize },
		{ "regularize", id_regularize },
		{ "add", id_add },
		{ "mul", id_mul },
		{ "div", id_div },
		{ "to_chain", id_to_chain },
		{ "nsimplify", id_nsimplify },
		{ "granularize", id_granularize },
		{ "nnetff", id_nnetff },
		{ "char_code", id_char_code },
		{ "nload", id_nload },
		{ "nsave", id_nsave },
		{ "train", id_train },
		{ "sim", id_sim },
		{ "get_code", id_get_code },
		{ "at_end_of_stream", id_at_end_of_stream },
		{ "open_url", id_open_url },
		{ "track_post", id_track_post },
		{ "consult", id_consult },
		{ "assert", id_assert },
		{ "asserta", id_asserta },
		{ "assertz", id_assertz },
		{ "retract", id_retract },
		{ "retractall", id_retractall },
		{ "inc", id_inc },
		{ "halt", id_halt },
		{ "load_classes", id_load_classes },
		{ "init_xpathing", id_init_xpathing },
		{ "induct_xpathing", id_induct_xpathing },
		{ "import_model_after_induct", id_import_model_after_induct },
		{ "unload_classes", id_unload_classes },
		{ "var", id_var },
		{ "nonvar", id_nonvar },
		{ "get_icontacts", id_get_icontacts },
		{ "get_ocontacts", id_get_ocontacts },
		{ "rollback", id_rollback },
		{ "optimize_load", id_optimize_load },
		{ "load_optimized", id_optimize_load },
		{ "parallelize_level", id_parallelize_level }

	};

	string CLASSES_ROOT;
	string INDUCT_MODE;

	map<string, _predicate*> PREDICATES;
	fastmux GLOCK;
	map<string, value*> GVars;
	map<string, std::recursive_mutex*> STARLOCKS;
	std::recursive_mutex STARLOCK;

	map< string, set<int>*> DBIndicators;
	fastmux DBILock;

	bool std_body_added = false;

	context* CONTEXT;

	string current_output;
	string current_input;
	string out_buf;

	basic_istream<char>* ins;
	basic_ostream<char>* outs;

	int file_num;
	map<int, std::basic_fstream<char> > files;
};

#endif
