#ifndef __PROLOG_MICRO_BRAIN_H__
#define __PROLOG_MICRO_BRAIN_H__

#include "values.h"

#include <vector>
#include <string>
#include <set>
#include <condition_variable>
#include <mutex>
#include <functional>
#include <algorithm>
#include <atomic>

#include <stdlib.h>
#include <chrono>

using namespace std;

extern const char * STD_INPUT;
extern const char * STD_OUTPUT;

const int once_flag = 0x1;
const int call_flag = 0x2;

const int PAR_NONE = 0;
const int PAR_SEQ = 1;
const int PAR_SEQ_JOIN_AFTER = 2;

unsigned long long getTotalSystemMemory();
unsigned int getTotalProcs();

class interpreter : public _interpreter {
public:
	interpreter(const string& fname, const string& starter_name);
	~interpreter();

	virtual string export_str(bool introduce_new_parallelism, std::set<string>* exported);

	bool XPathCompiled() const {
		return xpath_compiled;
	}
	bool XPathLoaded() const {
		return xpath_loaded;
	}
	void SetXPathCompiled(bool v) {
		xpath_compiled = v;
	}
	void SetXPathLoaded(bool v) {
		xpath_loaded = v;
	}

	bool LoadXPathing() {
		bool result = false;
		if (!xpathInductLib) {
			xpathInductLib = LoadLibrary(
#ifndef _MSC_VER
				L"./libxpathInduct.so"
#else
				L"xpathInduct.dll"
#endif
			);
			if (xpathInductLib) {
				XPathInduct = (XPathInductF)GetProcAddress(xpathInductLib, "XPathInduct");
				CompileXPathing = (CompileXPathingF)GetProcAddress(xpathInductLib, "CompileXPathing");
				SetInterval = (SetIntervalF)GetProcAddress(xpathInductLib, "SetInterval");
				ClearRestrictions = (ClearRestrictionsF)GetProcAddress(xpathInductLib, "ClearRestrictions");
				ClearRuler = (ClearRulerF)GetProcAddress(xpathInductLib, "ClearRuler");
				SetDeduceLogFile = (SetDeduceLogFileF)GetProcAddress(xpathInductLib, "SetDeduceLogFile");
				CreateDOMContact = (CreateDOMContactF)GetProcAddress(xpathInductLib, "CreateDOMContact");
				GetMSG = (GetMSGF)GetProcAddress(xpathInductLib, "GetMSG");
				result = true;
			}
		}
		return result;
	}

	void UnloadXPathing() {
		if (xpathInductLib)
			FreeLibrary(xpathInductLib);
		xpathInductLib = 0;
	}

	char* ENV() {
		return env;
	}

	void writeOptimized();

	long long calculate_check_sum(ifstream& in);

	string open_file(const string& fname, const string& mode);
	void close_file(const string& obj);
	std::basic_fstream<char>& get_file(const string& obj, int& fn);

	bool block_process(context* CNT, bool clear_flag, bool cut_flag, predicate_item* frontier, bool frontier_enough = false);

	double evaluate(context* CTX, frame_item* ff, const string& expression, size_t& p);
	void* deserialize_symbolic(const string& expression, size_t& p, vector<string>& Vars);
	string serialize_symbolic(void* expression, vector<string>& Vars);

	bool check_consistency(set<string>& dynamic_prefixes);

	void add_std_body(string& body);

	vector<value*>* accept(context* CTX, frame_item* ff, predicate_item* current);
	vector<value*>* accept(context* CTX, frame_item* ff, clause* current);
	bool retrieve(context* CTX, frame_item* ff, clause* current, vector<value*>* vals, bool escape_vars);
	bool retrieve(context* CTX, frame_item* ff, predicate_item* current, vector<value*>* vals, bool escape_vars);
	bool process(context* CNT, bool neg, clause* this_clause_call, predicate_item* p, frame_item* f, vector<value*>** positional_vals);

	void consult(const string& fname, bool renew);
	void bind();
	predicate_item_user* load_program(const string& fname, const string& starter_name);

	value* parse(context* CTX, bool exit_on_error, bool parse_complex_terms, frame_item* ff, const string& s, size_t& p);
	void parse_program(vector<string>& renew, string& s, std::set<string>* loaded_predicates, bool optimized);
	string parse_clause(context* CTX, vector<string>& renew, frame_item* ff, string& s, size_t& p, bool optimized);
	bool unify(context* CTX, frame_item* ff, value* from, value* to);

	void run();
	bool loaded();
};

class stack_values : public stack_container<value *> {
public:
	virtual void free() {
		for (int i = 0; i < this->size(); i++)
			at(i)->free();
	}
};

class tthread {
	volatile std::atomic<int> _id;
	volatile std::atomic<bool> stopped;
	volatile std::atomic<bool> terminated; // If needs to be terminated
	volatile std::atomic<bool> result; // Logical result
	volatile std::atomic<bool> allow_stop;

	volatile std::atomic<context*> CONTEXT;

	std::condition_variable_any cv;
	fastmux cv_m;

	std::condition_variable_any cvs;
	fastmux cvs_m;

	std::condition_variable_any cvt;
	fastmux cvt_m;

	std::condition_variable_any cvf;
	fastmux cvf_m;

	pro_thread * runner;
public:
	tthread(int _id, context* CTX);

	void reinit(int _id, context* CTX);

	virtual ~tthread();

	void body();

	virtual std::condition_variable_any& get_stopped_var() { return cvs; }
	virtual fastmux& get_stopped_mutex() { return cvs_m; }

	virtual std::condition_variable_any& get_terminated_var() { return cvt; }
	virtual fastmux& get_terminated_mutex() { return cvt_m; }

	virtual std::condition_variable_any& get_finished_var() { return cvf; }
	virtual fastmux& get_finished_mutex() { return cvf_m; }

	virtual context* get_context() { return CONTEXT; }
	virtual void set_context(context* CTX) {
		CONTEXT.store(CTX);
	}

	virtual int get_nthread() { return _id; }
	virtual bool is_stopped() { return stopped.load(); }
	virtual void set_stopped(bool v) { stopped.store(v); }
	virtual bool is_terminated() {
		return terminated.load();
	}
	virtual void set_terminated(bool v) {
		terminated.store(v);
	}
	virtual bool get_result() {
		return result.load();
	}
	virtual void set_result(bool v) {
		result.store(v);
	}
};

#ifdef __APPLE__
#include <stdexcept>
class pro_thread {
private:
	pthread_t thread_id;
	bool joined;
public:
	pro_thread(tthread * _this) {
		pthread_attr_t attr;
		size_t stack_size;
		int err;

		pthread_attr_init(&attr);
		pthread_attr_getstacksize(&attr, &stack_size);

		pthread_attr_setstacksize(&attr, 16 * stack_size);

		joined = false;

		if ((err = pthread_create(
				&thread_id,
				&attr,
				[](void* arg) -> void* {
					((tthread *)arg)->body();
					return nullptr;
				},
				_this)) != 0) {
			throw std::runtime_error("Thread creation error: " + std::to_string(err));
		}

		pthread_attr_destroy(&attr);
	}

	virtual bool joinable() {
		return !joined;
	}

	virtual ~pro_thread() {
		if (joinable()) join();
	}

	virtual void join() {
		if (joinable()) {
			joined = true;
			pthread_join(thread_id, NULL);
		}
	}
};
#else
#include <thread>
class pro_thread : public std::thread {
public:
	pro_thread(tthread * _this) : std::thread(&tthread::body, _this) {
	}
};
#endif

class thread_pool {
private:
	std::set<tthread*> available;
	std::set<tthread*> used;
	fastmux guard;
public:
	thread_pool() { }

	tthread* get_thread(int _id, context* CTX);

	void free_thread(tthread* t);

	virtual ~thread_pool();
};

class generated_vars : public vector<frame_item *> {
public:
	generated_vars() : vector<frame_item *>() { }
	generated_vars(int n, frame_item * filler) : vector<frame_item *>(n, filler) { }

	virtual bool has_variant(int i) { return i < size(); }
	virtual bool had_variants() { return size() != 0; }

	virtual void trunc_from(int k) {
		delete_from(k);
		this->resize(k);
	}

	virtual frame_item * get_next_variant(context * CTX, int i) { return i < size() ? at(i) : NULL; }

	virtual void undo(int _i, vector<frame_item*>* list) {
		if (!list || list->size())
			at(_i) = NULL;
		if (list)
			for (int j = 0; j < list->size(); j++)
				if ((size_t)(_i + j + 1) < size())
					at((size_t)(_i + j + 1)) = list->at(j);
	}


	virtual void delete_from(int i) {
		for (int j = i; j < size(); j++)
			delete at(j);
	}
};

class clause {
	friend predicate_item;
private:
	_predicate * parent;
	std::list<string> args;
	std::list<value *> _args;
	vector<predicate_item *> items;
	fastmux mutex;
	bool forking;

	int cached_is_not_pure_result;
public:
	clause(_predicate * pp) : parent(pp), forking(false) { }
	~clause();

	void lock() { mutex.lock(); }
	void unlock() { mutex.unlock(); }

	virtual void bind(bool starring);

	virtual void add_export(string& result, bool introduce_new_parallelism);

	virtual int is_not_pure() { return cached_is_not_pure_result; }

	_predicate * get_predicate() { return parent; }

	bool is_forking() const { return forking; }
	void set_forking(bool v) {
		forking = v;
	}

	const std::list<string> * get_args() {
		return &args;
	}

	const std::list<value *> * _get_args() {
		return &_args;
	}

	void push_cashed_arg(value * v) {
		v->use();
		_args.push_back(v);
	}

	void set_args(const std::list<string> & other_args) {
		args = other_args;
	}

	void add_item(predicate_item * p) {
		items.push_back(p);
	}

	void add_arg(const string & a) {
		args.push_back(a);
	}

	virtual int num_items() { return (int)items.size(); }
	virtual predicate_item * get_item(int i) { return items[i]; }
};

class predicate_item {
protected:
	int self_number;
	int starred_end;
	bool conditional_star_mode;
	bool is_starred;
	int star_good_tries;
	int star_bad_tries;
	clause * parent;
	std::list<string> args;
	std::list<value *> _args;

	int parallelizing_status;
	bool determined;

	interpreter * prolog;

	bool neg;
	bool once;
	bool call;

	fastmux mutex;
	std::recursive_mutex* critical;
public:
	predicate_item(bool _neg, bool _once, bool _call, int num, clause * c, interpreter * _prolog) : neg(_neg), once(_once), call(_call),
		self_number(num), starred_end(-1), parent(c), critical(NULL), prolog(_prolog),
		conditional_star_mode(false), is_starred(false), parallelizing_status(PAR_NONE),
		star_good_tries(0), star_bad_tries(0) {
		determined = true;
	}

	virtual ~predicate_item() {
		for (value * v : _args)
			v->free();
	}

	virtual bool get_determined() { return determined; }
	virtual void check_determinancy() {
		// Empty
	}

	virtual void add_export(std::set<int>& end_points, bool skip_brackets, string& result, string& offset, bool introduce_new_parallelism);
	virtual void contextual_export(std::set<int>& end_points, string& result, string& offset, bool introduce_new_parallelism);
	virtual void simple_export(const string& name, string& result, string& offset, bool introduce_new_parallelism);

	virtual int get_parallelizing_status() { return parallelizing_status; }
	virtual void include_parallelizing_status(int flag) { parallelizing_status |= flag; }
	virtual void clear_parallelizing_status() { parallelizing_status = PAR_NONE; }

	virtual void set_good_tries(int v) { star_good_tries = v; }
	virtual int get_good_tries() { return star_good_tries; }
	virtual void set_bad_tries(int v) { star_bad_tries = v; }
	virtual int get_bad_tries() { return star_bad_tries; }

	virtual void set_starred_end(int end) {
		this->starred_end = end;
	}

	virtual void set_conditional_star_mode(bool v, int goods, int bads) {
		conditional_star_mode = v;
		star_good_tries = goods;
		star_bad_tries = bads;
	}

	virtual bool get_conditional_star_mode() {
		return conditional_star_mode;
	}

	virtual void set_starred(bool v) {
		is_starred = v;
		if (this->starred_end >= 0)
			parent->get_item(this->starred_end)->set_starred(v);
	}

	virtual bool get_starred() { return is_starred; }

	virtual int get_strict_starred_end() { return this->starred_end; }

	virtual int get_starred_end() {
		if (conditional_star_mode)
			return is_starred ? this->starred_end : -1;
		else
			return this->starred_end;
	}

	virtual predicate_item* get_last(int variant) {
		return this->get_starred_end() < 0 ? NULL : parent->get_item(this->get_starred_end() - 1);
	}

	void set_critical(std::recursive_mutex* critical) {
		this->critical = critical;
	}

	void enter_critical() {
		if (this->critical)
			this->critical->lock();
	}

	void leave_critical() {
		if (this->critical)
			this->critical->unlock();
	}

	void lock() { mutex.lock(); }
	void unlock() { mutex.unlock(); }

	virtual int is_not_pure(std::set<string> * work_set) {
		work_set->insert(get_id());
		return 0;
	}

	virtual void bind(bool starring) {
		if (starring && conditional_star_mode) {
			std::set<string> work_set;
			for (int i = self_number; i < starred_end; i++)
				if (parent->get_item(i)->is_not_pure(&work_set)) {
					set_starred(false);
					return;
				}
			if (star_bad_tries + star_good_tries < 5 || star_bad_tries < star_good_tries) set_starred(true);
		}
	}

	virtual const string get_id() = 0;

	bool is_negated() const { return neg; }
	bool is_once() const { return once; }
	bool is_call() const { return call; }

	void make_once() { once = true; }
	void clear_negated() { neg = false; }

	const std::list<value *> * _get_args() {
		return &_args;
	}

	void push_cashed_arg(value * v) {
		v->use();
		_args.push_back(v);
	}

	void add_arg(const string & a) {
		args.push_back(a);
	}

	virtual predicate_item * get_next(int variant) {
		if (!is_last()) {
			if (get_starred_end() >= 0)
				return parent->get_item(get_starred_end());
			else
				return parent->items[(size_t)(self_number + 1)];
		}
		else
			return NULL;
	}

	virtual predicate_item* get_strict_next() {
		return parent->get_item(self_number + 1);
	}

	virtual predicate_item* get_strict_prev() {
		return parent->get_item(self_number - 1);
	}

	virtual frame_item * get_next_variant(context * CTX, frame_item * f, int & internal_variant, vector<value *> * positional_vals) { return NULL; }

	const std::list<string> * get_args() {
		return &args;
	}

	clause * get_parent() { return parent; }

	bool is_first(bool skip_brackets = false) const {
		return skip_brackets ? self_number <= 1 : self_number == 0;
	}
	bool is_last(bool skip_brackets = false) const {
		return skip_brackets ? !parent || self_number >= parent->items.size() - 2 : !parent || self_number == parent->items.size() - 1;
	}

	virtual int get_self_number() { return self_number; }

	virtual generated_vars * generate_variants(context * CTX, frame_item * f, vector<value *> * & positional_vals) = 0;

	virtual bool execute(context * CTX, frame_item * &f, int i, generated_vars* variants, long long & pseudo_duration) {
		return true;
	}
};

class _predicate {
	friend predicate_item;
	friend clause;
private:
	string name;
	vector<clause *> clauses;
	bool runned;
	bool forking;
public:
	_predicate(const string & _name) : name(_name), runned(false), forking(false) { }
	~_predicate();

	const string& get_name() { return name; }

	void mark_runned() { runned = true; }
	bool is_runned() { return runned; }

	void bind(bool starring) {
		for (clause * c : clauses)
			c->bind(starring);
	}

	virtual void add_export(string& result, bool introduce_new_parallelism) {
		for (clause* c : clauses) {
			c->add_export(result, introduce_new_parallelism);
			result += "\n";
		}
	}

	void add_clause(clause * c) {
		clauses.push_back(c);
	}

	bool is_forking() const { return forking; }
	void set_forking(bool v) {
		forking = v;
	}
	bool is_forking_variant(int variant) {
		return clauses[variant]->is_forking();
	}

	virtual int num_clauses() { return (int) clauses.size(); }
	virtual clause * get_clause(int i) { return clauses[i]; }
};

class predicate_item_user : public predicate_item {
private:
	string id;
	_predicate * user_p;
	bool cached_is_not_pure;
	int cached_is_not_pure_result;
public:
	predicate_item_user(bool _neg, bool _once, bool _call, int num, clause * c, interpreter * _prolog, const string & _name) : predicate_item(_neg, _once, _call, num, c, _prolog), id(_name) {
		user_p = NULL;
		cached_is_not_pure = false;
		cached_is_not_pure_result = 0;
	}

	virtual void check_determinancy(set<predicate_item *> & passed) {
		// Ecrivez! Pour determiner 'determined'
	}

	virtual void bind(bool starring);

	bool is_dynamic() { return user_p == NULL; }

	bool is_forking_variant(int variant) { return user_p != NULL && user_p->is_forking_variant(variant); }

	_predicate * get_user_predicate() { return user_p; }

	virtual const string get_id() { return id; }

	virtual int is_not_pure(std::set<string> * work_set);

	virtual generated_vars * generate_variants(context * CTX, frame_item * f, vector<value *> * & positional_vals);

	virtual bool processing(context * CONTEXT, bool line_neg, int variant, generated_vars * variants, vector<value *> ** positional_vals,
		frame_item * up_f, context * up_c);
};

#endif
