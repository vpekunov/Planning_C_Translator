#ifndef __PROLOG_MICRO_BRAIN_H__
#define __PROLOG_MICRO_BRAIN_H__

#define _CRT_SECURE_NO_WARNINGS

#include <vector>
#include <string>
#include <set>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <functional>
#include <algorithm>
#include <atomic>

#include <stdlib.h>
#include <chrono>

using namespace std;

#include "elements.h"

extern const char * STD_INPUT;
extern const char * STD_OUTPUT;

const int once_flag = 0x1;
const int call_flag = 0x2;

const int PAR_NONE = 0;
const int PAR_SEQ = 1;
const int PAR_SEQ_JOIN_AFTER = 2;

unsigned long long getTotalSystemMemory();
unsigned int getTotalProcs();

#ifdef __linux__
#include <sys/resource.h>
#include <unistd.h>
#include <pthread.h>
#include <dlfcn.h>

typedef void * HMODULE;

HMODULE LoadLibrary(const wchar_t * _fname) {
	return dlopen(wstring_to_utf8(_fname).c_str(), RTLD_LAZY);
}

void * GetProcAddress(HMODULE handle, const char * fname) {
	return dlsym(handle, fname);
}

void FreeLibrary(HMODULE handle) {
	dlclose(handle);
}
#else
#include <Windows.h>
#endif

typedef unsigned long long clock_rdtsc;
clock_rdtsc __clock();

typedef std::mutex fastmux;

template<class T> class stack_container : public vector<T>{
public:
	virtual void push_back(const T & v) {
		if (this->capacity() == this->size())
			this->reserve((int)(1.5*this->size()));
		vector<T>::push_back(v);
	}

	virtual void push(const T & v) { this->push_back(v); }
	virtual void pop() { this->pop_back(); }
	virtual T top() { return this->back(); }
};

class interpreter;
class frame_item;
class thread_pool;
class predicate;
class clause;
class predicate_item;
class predicate_item_user;
class generated_vars;
class term;
class tthread;
class context;
class tframe_item;

class value {
protected:
	std::atomic<int> refs;
public:
	value() { refs = 1; }

	virtual void use() { refs++; }
	virtual void free() {
		refs--;
		if (refs == 0) {
			delete(this);
		}
	}

	virtual int get_refs() { return refs; }

	virtual value* fill(context* CTX, frame_item* vars) = 0;
	virtual value* copy(context* CTX, frame_item* f, int unwind = 0) = 0;
	virtual value* const_copy(context* CTX, frame_item* f, int unwind = 0) {
		if (this->defined()) {
			this->use();
			return this;
		}
		else
			return copy(CTX, f, unwind);
	}
	virtual bool unify(context* CTX, frame_item* ff, value* from) = 0;
	virtual bool defined() = 0;

	virtual string to_str(bool simple = false) = 0;

	virtual void escape_vars(context* CTX, frame_item* ff) = 0;

	virtual string make_str() {
		return to_str();
	}

	virtual string export_str(bool simple = false, bool double_slashes = true) {
		return to_str();
	}

	virtual void write(basic_ostream<char>* outs, bool simple = false) {
		(*outs) << to_str(simple);
	}
};

typedef struct {
	unsigned long long * _name;
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
	stack_container<predicate_item *> SEQ_START;
	stack_container<predicate_item*> SEQ_END;
	stack_container<tframe_item*> FRAMES_TO_DELETE;

	fastmux * DBLOCK;
	map< string, std::atomic<vector<term*>*>> * DB;
	map<unsigned long long, std::atomic<journal*>> * DBJournal;

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
	stack_container<clause *> START_CLAUSES;
	stack_container<vector<value*>**> TRACEARGS;
	stack_container<predicate_item*> TRACERS;
	stack_container<int> ptrTRACE;

	fastmux pages_mutex;

	virtual context* add_page(bool locals_in_forked, bool transactable_facts, predicate_item * forker, tframe_item* f, predicate_item* starting, predicate_item* ending, interpreter* prolog);

	virtual void register_db_read(const unsigned long long iid);

	virtual void register_db_write(const unsigned long long iid, jTypes t, value* data, int position, journal * src = NULL);
	
	virtual bool join(bool sequential_mode, int K, frame_item* f, interpreter* INTRP, int & sequential, vector<frame_item*> * rest, long long & pseudo_duration, predicate_item * starred);

	virtual void apply_transactional_db_to_parent(const std::string & fact);
};

class interpreter {
private:
	predicate_item_user * starter;
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
		id_char_code,
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

	map<string, std::set<string> *> consulted;
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
		{ "char_code", id_char_code },
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

	map<string, predicate *> PREDICATES;
	fastmux GLOCK;
	map<string, value *> GVars;
	map<string, std::recursive_mutex *> STARLOCKS;
	std::recursive_mutex STARLOCK;

	map< string, set<int>*> DBIndicators;
	fastmux DBILock;

	bool std_body_added = false;

	context* CONTEXT;

	string current_output;
	string current_input;
	string out_buf;

	basic_istream<char> * ins;
	basic_ostream<char> * outs;

	int file_num;
	map<int, std::basic_fstream<char> > files;

	interpreter(const string & fname, const string & starter_name);
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
#ifdef __linux__
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

	char * ENV() {
		return env;
	}

	void writeOptimized();

	long long calculate_check_sum(ifstream& in);

	string open_file(const string & fname, const string & mode);
	void close_file(const string & obj);
	std::basic_fstream<char> & get_file(const string & obj, int & fn);

	bool block_process(context * CNT, bool clear_flag, bool cut_flag, predicate_item * frontier, bool frontier_enough = false);

	double evaluate(context* CTX, frame_item * ff, const string & expression, size_t & p);

	bool check_consistency(set<string> & dynamic_prefixes);

	void add_std_body(string & body);

	vector<value *> * accept(context* CTX, frame_item * ff, predicate_item * current);
	vector<value *> * accept(context* CTX, frame_item * ff, clause * current);
	bool retrieve(context* CTX, frame_item * ff, clause * current, vector<value *> * vals, bool escape_vars);
	bool retrieve(context* CTX, frame_item * ff, predicate_item * current, vector<value *> * vals, bool escape_vars);
	bool process(context* CNT, bool neg, clause * this_clause_call, predicate_item * p, frame_item * f, vector<value *> ** positional_vals);

	void consult(const string & fname, bool renew);
	void bind();
	predicate_item_user * load_program(const string & fname, const string & starter_name);

	value * parse(context* CTX, bool exit_on_error, bool parse_complex_terms, frame_item * ff, const string & s, size_t & p);
	void parse_program(vector<string> & renew, string & s, std::set<string>* loaded_predicates, bool optimized);
	string parse_clause(context* CTX, vector<string> & renew, frame_item * ff, string & s, size_t & p, bool optimized);
	bool unify(context* CTX, frame_item * ff, value * from, value * to);

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

class frame_item {
protected:
	friend class tframe_item;

	unsigned long long * names;
	int names_length;
	int names_capacity;

	vector<mapper> vars;

	unsigned long long* deleted;
public:
	frame_item(unsigned int _name_capacity = 32, unsigned int _vars_capacity = 8, context * CTX = NULL, frame_item* inheriting = NULL) {
		names_capacity = _name_capacity;
		names = (unsigned long long *) malloc(names_capacity*sizeof(char));
		names_length = 0;
		vars.reserve(_vars_capacity);
		deleted = NULL;

		import_transacted_globs(CTX, inheriting);
	}

	virtual ~frame_item();

	virtual bool lock() { return false; }
	virtual void unlock() { }

	virtual void forced_import_transacted_globs(context* CTX, frame_item* inheriting) {
		lock();
		for (mapper& m : inheriting->vars) {
			if (get_first_char(m._name[0]) == '*')
				set(true, CTX, m._name[0], m.ptr, true);
		}
		unlock();
	}

	virtual void import_transacted_globs(context* CTX, frame_item* inheriting) {
		if (CTX && inheriting && (CTX->THR || CTX->forked())) {
			forced_import_transacted_globs(CTX, inheriting);
		}
	}

	virtual void add_local_names(bool locals_in_forked, std::set<unsigned long long>& s) {
		for (mapper& m : vars)
			if (get_wind(m._name[0]) == 0 && (!locals_in_forked || get_first_char(m._name[0]) == '*'))
				s.insert(m._name[0]);
	}

	virtual void sync(bool _locked, bool not_sync_globs, context * CTX, frame_item * other) {
		bool locked = !_locked && lock();
		int it = 0;
		while (it < other->vars.size()) {
			unsigned long long * itc = other->vars[it]._name;
			if (not_sync_globs || get_first_char(*itc) == '*')
				set(locked, CTX, *itc, other->vars[it].ptr, true);
			it++;
		}
		if (not_sync_globs && other->deleted) {
			unsigned long long* cur = other->deleted;
			while (*cur) {
				unset(locked, CTX, *cur);
				cur++;
			}
		}
		if (locked) unlock();
	}

	virtual frame_item * copy(context * CTX) {
		frame_item * result = new frame_item(names_capacity, (unsigned int)vars.size());
		result->names_length = names_length;
		memmove(result->names, names, names_length*sizeof(char));
		long long d = &result->names[0] - &names[0];
		result->vars = vars;
		for (mapper & m : result->vars) {
			m.ptr = m.ptr ? m.ptr->const_copy(CTX, this) : NULL;
			m._name += d;
		}
		return result;
	}

	virtual tframe_item* tcopy(context* CTX, interpreter * INTRP, bool import_globs);

	virtual void register_write(const std::string & name) { }

	int get_size() { return (int)vars.size(); }

	virtual value * at(int i) {
		return vars[i].ptr;
	}

	virtual const string atn(int i);

	int find(const unsigned long long what, bool & found) {
		found = false;

		int sz = (int)vars.size();

		if (sz == 0)
			return 0;
		long long n0 = what - vars[0]._name[0];
		if (n0 <= 0) {
			found = n0 == 0;
			return 0;
		}
		if (sz <= 4) {
			if (sz == 1)
				return 1;
			long long nn = what - vars.back()._name[0];
			if (nn >= 0) {
				found = nn == 0;
				return found ? sz - 1 : sz;
			}
			if (sz == 2)
				return 1;
			for (int i = 1; i < sz - 1; i++) {
				long long ni = what - vars[i]._name[0];
				if (ni <= 0) {
					found = ni == 0;
					return i;
				}
			}
			return sz - 1;
		}

		if (what > vars.back()._name[0])
			return (int)vars.size();

		int a = 0;
		int b = sz - 1;
		while (a < b) {
			int c = (a + b) / 2;
			long long r = what - vars[c]._name[0];
			if (r == 0) {
				found = true;
				return c;
			}
			if (r < 0)
				b = c;
			else
				a = c + 1;
		}
		if (what == vars[b]._name[0])
			found = true;
		return b;
	}

	void escape(unsigned long long & _name) {
		bool found = false;
		int it = find(_name, found);
		escape_name(_name);
		if (found) {
			unsigned long long * oldp = &names[0];
			unsigned long long * s = vars[it]._name;
			*s = _name;
			// names.insert(names.begin() + (s - oldp), prepend);
			value * v = vars[it].ptr;
			vars.erase(vars.begin() + it);

			found = false;
			it = find(*s, found);
			if (found) {
				cout << "Internal FRAME collision : [" << _name << "] already exists and can't be escaped?!" << endl;
				exit(4000);
			}
			else {
				mapper m = { s, v };
				vars.insert(vars.begin() + it, m);
			}
		}
	}

	virtual void set(bool _locked, context * CTX, const unsigned long long name, value * v, bool set_time_zero = false) {
		bool found = false;
		int it = find(name, found);
		if (found) {
			if (vars[it].ptr) vars[it].ptr->free();
			vars[it].ptr = v ? v->const_copy(CTX, this) : NULL;
		}
		else {
			unsigned long long * oldp = &names[0];
			int n = (int)sizeof(name);
			names_length += n;
			if (names_length >= names_capacity) {
				names_capacity += 24 + n;
				unsigned long long * new_mem = (unsigned long long*)realloc(names, names_capacity * sizeof(char));
				if (!new_mem) {
					cout << "set: Insufficient memory in realloc?!" << endl;
					exit(3702);
				}
				names = new_mem;
			}
			// names.resize(oldn + n + 1);
			unsigned long long * newp = &names[0];
			for (int i = 0; i < vars.size(); i++)
				vars[i]._name += newp - oldp;
			unsigned long long * _name = newp + vars.size();
			*_name = name;
			mapper m = { _name, v ? v->const_copy(CTX, this) : NULL };
			vars.insert(vars.begin() + it, m);
		}
	}

	virtual int unset(bool _locked, context* CTX, const unsigned long long name) {
		bool found = false;
		int it = find(name, found);
		if (found) {
			int size_deleted = 1;
			if (deleted) {
				unsigned long long* ptr = deleted;
				while (*ptr++);
				size_deleted = (int)(ptr - deleted);
			}
			size_deleted++;
			deleted = (unsigned long long *) realloc(deleted, size_deleted * sizeof(unsigned long long));
			deleted[size_deleted - 2] = name;
			deleted[size_deleted - 1] = 0;

			unsigned long long* oldp = &names[0];
			unsigned long long* start = vars[it]._name;
			unsigned long long* end = start + 1;
			for (int to_move = (int)(vars.size() - (vars[it]._name - oldp) - 1); to_move > 0; to_move--)
				*start++ = *end++;
			names_length -= sizeof(unsigned long long);
			// names.erase(names.begin() + (vars[it]._name - oldp), names.begin() + (vars[it]._name - oldp) + n + 1);
			if (names_length > 0) {
				unsigned long long* newp = &names[0];
				for (int i = 0; i < vars.size(); i++)
					if (i != it)
						if (vars[i]._name < vars[it]._name)
							vars[i]._name += newp - oldp;
						else
							vars[i]._name += newp - oldp - 1;
			}
			vars.erase(vars.begin() + it);
			return it;
		} else
			return -1;
	}

	virtual value * get(bool _locked, context * CTX, unsigned long long name, int unwind = 0) {
		bool found = false;
		int it = find(name, found);
		if (found)
			return vars[it].ptr;
		else if (unwind) {
			unsigned int n = get_wind(name);
			if (n == 0)
				return NULL;
			if (unwind >= (int)n) {
				unescape_name(name, n);
				return get(_locked, CTX, name, unwind - n);
			}
			else
			{
				unescape_name(name, unwind);
				return get(_locked, CTX, name, 0);
			}
		}
		else
			return NULL;
	}

	virtual void register_facts(bool _locked, context* CTX, std::set<unsigned long long>& names);

	virtual void unregister_facts(bool _locked, context* CTX);

	virtual void register_fact_group(bool _locked, context* CTX, unsigned long long& fact, journal* J);

	virtual void unregister_fact_group(bool _locked, context* CTX, unsigned long long& fact);
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

	std::thread * runner;
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
	tframe_item(unsigned int _name_capacity = 32, unsigned int _vars_capacity = 5, context* CTX = NULL, frame_item* inheriting = NULL) : frame_item(_name_capacity, _vars_capacity) {
		creation = __clock();
		info_capacity = _vars_capacity;
		if (info_capacity <= nn) {
			info_vars = micro_info;
			info_capacity = nn;
		}
		else
			info_vars = (var_info*)malloc(info_capacity * sizeof(var_info));

		import_transacted_globs(CTX, inheriting);
	}

	virtual ~tframe_item();

	virtual bool lock() { return mutex.try_lock(); }
	virtual void unlock() { mutex.unlock(); }

	virtual void set(bool _locked, context * CTX, const unsigned long long name, value* v, bool set_time_zero = false) {
		static var_info var_info_zero = { 0 };

		bool locked = !_locked && mutex.try_lock();
		bool found = false;
		int it = find(name, found);
		if (!found) {
			unsigned long long* oldp = &names[0];
			int n = (int)sizeof(name);
			names_length += n;
			if (names_length >= names_capacity) {
				names_capacity += 24 + n;
				unsigned long long* new_mem = (unsigned long long*)realloc(names, names_capacity * sizeof(char));
				if (!new_mem) {
					cout << "set: Insufficient memory in realloc?!" << endl;
					exit(3702);
				}
				names = new_mem;
			}
			// names.resize(oldn + n + 1);
			unsigned long long* newp = &names[0];
			for (int i = 0; i < vars.size(); i++)
				vars[i]._name += newp - oldp;
			unsigned long long* _name = newp + vars.size();
			*_name = name;
			mapper m = { _name, v ? v->const_copy(CTX, this) : NULL };
			vars.insert(vars.begin() + it, m);
			if (vars.size() > info_capacity) {
				int _info_capacity = info_capacity;
				info_capacity += 10;
				if (info_vars == micro_info) {
					info_vars = (var_info*)malloc(/*_info_capacity * sizeof(var_info),*/ info_capacity * sizeof(var_info));
					memmove(info_vars, micro_info, _info_capacity * sizeof(var_info));
				} else
					info_vars = (var_info*)realloc(info_vars, /*_info_capacity * sizeof(var_info),*/ info_capacity * sizeof(var_info));
			}
			for (int i = (int)vars.size() - 1; i > it; i--)
				info_vars[i] = info_vars[i - 1];
			info_vars[it] = var_info_zero;
		}
		else {
			if (vars[it].ptr)
				vars[it].ptr->free();
			vars[it].ptr = v ? v->const_copy(CTX, this) : NULL;
		}
		if (set_time_zero) {
			info_vars[it] = var_info_zero;
		}
		else {
			clock_rdtsc c = __clock();
			if (info_vars[it].first_writes == 0)
				info_vars[it].first_writes = c;
			info_vars[it].last_writes = c;
		}
		if (locked) unlock();
	}

	virtual value* get(bool _locked, context * CTX, const unsigned long long name, int unwind = 0) {
		bool locked = !_locked && mutex.try_lock();
		value* result = NULL;
		bool found = false;
		int it = find(name, found);
		if (found) {
			result = vars[it].ptr;
			clock_rdtsc c = __clock();
			if (info_vars[it].first_reads == 0)
				info_vars[it].first_reads = c;
			info_vars[it].last_reads = c;
		}
		else if (unwind && get_wind(name)) {
			result = frame_item::get(locked, CTX, name, unwind);
		}
		if (locked) unlock();
		return result;
	}

	virtual int unset(bool _locked, context* CTX, const unsigned long long name) {
		bool locked = !_locked && mutex.try_lock();
		int it = frame_item::unset(locked, CTX, name);
		if (it >= 0) {
			for (int i = it; i < vars.size(); i++)
				info_vars[i] = info_vars[i + 1];
		}
		if (locked) unlock();
		return it;
	}

	virtual void register_write(const unsigned long long name) {
		bool found = false;
		int it = find(name, found);
		clock_rdtsc c = __clock();
		if (found && info_vars[it].first_writes == 0)
			info_vars[it].first_writes = c;
		if (found)
			info_vars[it].last_writes = c;
	}

	virtual clock_rdtsc first_write(const unsigned long long vname) {
		bool found = false;
		int it = find(vname, found);
		if (found)
			return info_vars[it].first_writes;
		else
			return 0;
	}

	virtual clock_rdtsc last_read(const unsigned long long vname) {
		bool found = false;
		int it = find(vname, found);
		if (found)
			return info_vars[it].last_reads;
		else
			return 0;
	}

	virtual clock_rdtsc first_read(const unsigned long long vname) {
		bool found = false;
		int it = find(vname, found);
		if (found)
			return info_vars[it].first_reads;
		else
			return 0;
	}

	virtual clock_rdtsc last_write(const unsigned long long vname) {
		bool found = false;
		int it = find(vname, found);
		if (found)
			return info_vars[it].last_writes;
		else
			return 0;
	}

	virtual void set_written_new(frame_item* src) {
		for (mapper& m : vars)
			if (get_first_char(m._name[0]) != '*') {
				bool found;
				src->find(m._name[0], found);
				if (!found)
					register_write(m._name[0]);
			}
	}

	virtual void statistics(const unsigned long long vname, clock_rdtsc & cr, clock_rdtsc &fw, clock_rdtsc &fr, clock_rdtsc &lw, clock_rdtsc &lr) {
		bool found = false;
		int it = find(vname, found);
		if (found) {
			lw = info_vars[it].last_writes;
			lr = info_vars[it].last_reads;
			fw = info_vars[it].first_writes;
			fr = info_vars[it].first_reads;
		}
		else {
			fw = fr = lw = lr = 0;
		}
		cr = creation;
	}

	virtual void register_fact_group(bool _locked, context* CTX, unsigned long long & fact, journal* J);

	virtual void unregister_fact_group(bool _locked, context* CTX, unsigned long long & fact);

	virtual void sync(bool _locked, bool not_sync_globs, context* CTX, frame_item* other) {
		bool locked = !_locked && mutex.try_lock();
		tframe_item* _other = dynamic_cast<tframe_item*>(other);
		if (!_other) {
			frame_item::sync(locked, not_sync_globs, CTX, other);
			if (locked) unlock();
			return;
		}
		int it = 0;
		while (it < _other->vars.size()) {
			bool f;
			unsigned long long * itc = _other->vars[it]._name;
			if (not_sync_globs || get_first_char(*itc) == '*') {
				set(locked, CTX, *itc, _other->vars[it].ptr, true);
				int _it = find(*itc, f);
				if (f) {
					info_vars[_it] = _other->info_vars[it];
				}
				else {
					cout << "Internal ERROR : can't sync tframe_item : var [" << *itc << "]" << endl;
					exit(-60);
				}
			}
			it++;
		}
		if (not_sync_globs && other->deleted) {
			unsigned long long* cur = other->deleted;
			while (*cur) {
				unset(locked, CTX, *cur);
				cur++;
			}
		}
		if (locked) unlock();
	}

	virtual frame_item* copy(context* CTX) {
		frame_item* result = new tframe_item(names_capacity, info_capacity);
		result->names_length = names_length;
		memmove(result->names, names, names_length * sizeof(char));
		long long d = &result->names[0] - &names[0];
		result->vars = vars;
		for (mapper& m : result->vars) {
			m.ptr = m.ptr ? m.ptr->const_copy(CTX, this) : NULL;
			m._name += d;
		}
		memmove(((tframe_item*)result)->info_vars, info_vars, vars.size() * sizeof(var_info));
		return result;
	}

	virtual tframe_item* tcopy(context* CTX, interpreter* INTRP) {
		return dynamic_cast<tframe_item *>(copy(CTX));
	}
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
		at(_i) = NULL;
	}

	virtual void delete_from(int i) {
		for (int j = i; j < size(); j++)
			delete at(j);
	}
};

class clause {
	friend predicate_item;
private:
	predicate * parent;
	std::list<string> args;
	std::list<value *> _args;
	vector<predicate_item *> items;
	fastmux mutex;
	bool forking;

	int cached_is_not_pure_result;
public:
	clause(predicate * pp) : parent(pp), forking(false) { }
	~clause();

	void lock() { mutex.lock(); }
	void unlock() { mutex.unlock(); }

	virtual void bind(bool starring);

	virtual void add_export(string& result, bool introduce_new_parallelism);

	virtual int is_not_pure() { return cached_is_not_pure_result; }

	predicate * get_predicate() { return parent; }

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
		star_good_tries(0), star_bad_tries(0) { }

	virtual ~predicate_item() {
		for (value * v : _args)
			v->free();
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

class predicate {
	friend predicate_item;
	friend clause;
private:
	string name;
	vector<clause *> clauses;
	bool runned;
	bool forking;
public:
	predicate(const string & _name) : name(_name), runned(false), forking(false) { }
	~predicate();

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
	predicate * user_p;
	bool cached_is_not_pure;
	int cached_is_not_pure_result;
public:
	predicate_item_user(bool _neg, bool _once, bool _call, int num, clause * c, interpreter * _prolog, const string & _name) : predicate_item(_neg, _once, _call, num, c, _prolog), id(_name) {
		user_p = NULL;
		cached_is_not_pure = false;
		cached_is_not_pure_result = 0;
	}

	virtual void bind(bool starring);

	bool is_dynamic() { return user_p == NULL; }

	bool is_forking_variant(int variant) { return user_p != NULL && user_p->is_forking_variant(variant); }

	predicate * get_user_predicate() { return user_p; }

	virtual const string get_id() { return id; }

	virtual int is_not_pure(std::set<string> * work_set);

	virtual generated_vars * generate_variants(context * CTX, frame_item * f, vector<value *> * & positional_vals);

	virtual bool processing(context * CONTEXT, bool line_neg, int variant, generated_vars * variants, vector<value *> ** positional_vals,
		frame_item * up_f, context * up_c);
};

class journal_item {
public:
	jTypes type;
	value* data;
	int position;

	journal_item(jTypes t, value* data, int position) {
		this->type = t;
		this->data = data;
		this->position = position;
	}

	virtual ~journal_item() {
		if (this->type == jDelete)
			this->data->free();
	}
};

class journal {
public:
	clock_rdtsc creation;
	clock_rdtsc first_write, last_write, first_read, last_read;

	vector<journal_item*> log;

	journal() {
		creation = __clock();

		first_write = last_write = first_read = last_read = 0;
	}

	virtual ~journal() {
		for (journal_item* it : log)
			delete it;
	}

	virtual void register_read() {
		clock_rdtsc c = __clock();
		if (!first_read)
			first_read = c;
		last_read = c;
	}

	virtual void register_write(jTypes t, value* data, int position, journal * src = NULL) {
		if (src) {
			if (!first_write || src->first_write < first_write)
				first_write = src->first_write;
			if (!last_write || src->last_write > last_write)
				last_write = src->last_write;
			if (!first_read || src->first_read < first_read)
				first_read = src->first_read;
			if (!last_read || src->last_read > last_read)
				last_read = src->last_read;
		}
		else {
			clock_rdtsc c = __clock();
			if (!first_write) {
				first_write = c;
			}
			last_write = c;
		}

		log.push_back(new journal_item(t, data, position));
	}
};

#endif
