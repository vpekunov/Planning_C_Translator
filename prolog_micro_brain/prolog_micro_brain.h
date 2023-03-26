#ifndef __PROLOG_MICRO_BRAIN_H__
#define __PROLOG_MICRO_BRAIN_H__

#include <vector>
#include <string>
#include <set>

using namespace std;

#include "elements.h"

extern bool fast_memory_manager;

const int once_flag = 0x1;
const int call_flag = 0x2;

unsigned long long getTotalSystemMemory();
void * __alloc(size_t size);
void __free(void * ptr);

#ifdef __linux__
#include <sys/resource.h>
#include <unistd.h>
#include <dlfcn.h>

typedef void * HMODULE;

HMODULE LoadLibrary(wchar_t * _fname) {
	return dlopen(wstring_to_utf8(_fname).c_str(), RTLD_LAZY);
}

void * GetProcAddress(HMODULE handle, char * fname) {
	return dlsym(handle, fname);
}

void FreeLibrary(HMODULE handle) {
	dlclose(handle);
}
#else
#include <Windows.h>
#endif

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

class frame_item;
class predicate;
class clause;
class predicate_item;
class predicate_item_user;
class generated_vars;
class value;
class term;

class interpreter {
private:
	predicate_item_user * starter;
	HMODULE xpathInductLib;
	char env[65536 * 4];
	bool xpath_compiled;
	bool xpath_loaded;
public:
	string CLASSES_ROOT;
	string INDUCT_MODE;

	map<string, predicate *> PREDICATES;
	map< string, vector<term *> *> DB;
	map< string, set<int> *> DBIndicators;
	map<string, value *> GVars;

	stack_container<predicate_item *> CALLS;
	stack_container<frame_item *> FRAMES;
	stack_container<bool> NEGS;
	stack_container<int> _FLAGS;
	stack_container<predicate_item_user *> PARENT_CALLS;
	stack_container<int> PARENT_CALL_VARIANT;
	stack_container<clause *> CLAUSES;
	std::list<int> FLAGS;
	stack_container<int> LEVELS;
	stack_container<generated_vars *> TRACE;
	stack_container<vector<value *> **> TRACEARGS;
	stack_container<predicate_item *> TRACERS;
	stack_container<int> ptrTRACE;

	string current_output;
	string current_input;
	string out_buf;

	basic_istream<char> * ins;
	basic_ostream<char> * outs;

	int file_num;
	map<int, std::basic_fstream<char> > files;

	interpreter(const string & fname, const string & starter_name);
	~interpreter();

	bool XPathCompiled() {
		return xpath_compiled;
	}
	bool XPathLoaded() {
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

	string open_file(const string & fname, const string & mode);
	void close_file(const string & obj);
	std::basic_fstream<char> & get_file(const string & obj, int & fn);

	void block_process(bool clear_flag, bool cut_flag, predicate_item * frontier);

	double evaluate(frame_item * ff, const string & expression, int & p);

	bool check_consistency(set<string> & dynamic_prefixes);

	void add_std_body(string & body);

	vector<value *> * accept(frame_item * ff, predicate_item * current);
	vector<value *> * accept(frame_item * ff, clause * current);
	bool retrieve(frame_item * ff, clause * current, vector<value *> * vals, bool escape_vars);
	bool retrieve(frame_item * ff, predicate_item * current, vector<value *> * vals, bool escape_vars);
	bool process(bool neg, clause * this_clause_call, predicate_item * p, frame_item * f, vector<value *> ** positional_vals);

	void consult(const string & fname, bool renew);
	void bind();
	predicate_item_user * load_program(const string & fname, const string & starter_name);

	value * parse(bool exit_on_error, bool parse_complex_terms, frame_item * ff, const string & s, int & p);
	void parse_program(vector<string> & renew, string & s);
	void parse_clause(vector<string> & renew, frame_item * ff, string & s, int & p);
	bool unify(frame_item * ff, value * from, value * to);

	void run();
	bool loaded();
};

class value {
protected:
	int refs;
public:
	value() { refs = 1; }

	virtual void use() { refs++; }
	virtual void free() { refs--; if (refs == 0) delete this; }

	virtual value * fill(frame_item * vars) = 0;
	virtual value * copy(frame_item * f) = 0;
	virtual bool unify(frame_item * ff, value * from) = 0;
	virtual bool defined() = 0;

	virtual string to_str(bool simple = false) = 0;

	virtual void escape_vars(frame_item * ff) = 0;

	virtual string make_str() {
		return to_str();
	}

	virtual void write(basic_ostream<char> * outs, bool simple = false) {
		(*outs) << to_str(simple);
	}

	void * operator new (size_t size){
		if (fast_memory_manager)
		return __alloc(size);
		else {
			void *ptr = ::operator new(size);
//			cout<<"new:"<<ptr<<endl;
			return ptr;
		}
	}

	void operator delete (void * ptr) {
//	cout << "del:" << ptr << endl;
	if (fast_memory_manager)
		__free(ptr);
	else
		::operator delete(ptr);
	}
};

class stack_values : public stack_container<value *> {
public:
	virtual void free() {
		for (int i = 0; i < this->size(); i++)
			at(i)->free();
	}
};

class frame_item {
private:
	vector<char> names;

	typedef struct {
		char * _name;
		value * ptr;
	} mapper;

	vector<mapper> vars;
public:
	frame_item() {
		names.reserve(32);
		vars.reserve(8);
	}

	~frame_item() {
		int it = 0;
		while (it < vars.size()) {
			vars[it].ptr->free();
			it++;
		}
	}

	void sync(frame_item * other) {
		int it = 0;
		while (it < other->vars.size()) {
			char * itc = other->vars[it]._name;
			set(itc, other->vars[it].ptr);
			it++;
		}
	}

	frame_item * copy() {
		frame_item * result = new frame_item();
		result->names = names;
		long long d = result->names.size() == 0 ? 0 : &result->names[0] - &names[0];
		result->vars = vars;
		for (mapper & m : result->vars) {
			m.ptr = m.ptr->copy(this);
			m._name += d;
		}
		return result;
	}

	int get_size() { return vars.size(); }

	value * at(int i) {
		return vars[i].ptr;
	}

	char * atn(int i) {
		return vars[i]._name;
	}

	int find(const char * what, bool & found) {
		found = false;

		if (vars.size() == 0)
			return 0;
		if (strcmp(what, vars[0]._name) < 0)
			return 0;
		if (strcmp(what, vars.back()._name) > 0)
			return vars.size();

		int a = 0;
		int b = vars.size() - 1;
		while (a < b) {
			int c = (a + b) / 2;
			int r = strcmp(what, vars[c]._name);
			if (r == 0) {
				found = true;
				return c;
			}
			if (r < 0)
				b = c;
			else
				a = c + 1;
		}
		if (strcmp(what, vars[b]._name) == 0)
			found = true;
		return b;
	}

	void escape(const char * name, char prepend) {
		bool found = false;
		int it = find(name, found);
		if (found) {
			char * oldp = &names[0];
			char * s = atn(it);
			names.insert(names.begin() + (s - oldp), prepend);
			char * newp = &names[0];
			char * news = newp + (s - oldp);
			for (int i = 0; i < vars.size(); i++)
				if (i != it)
					if (atn(i) > s)
						vars[i]._name += (newp - oldp) + 1;
					else
						vars[i]._name += (newp - oldp);
			value * v = vars[it].ptr;
			vars.erase(vars.begin() + it);

			found = false;
			it = find(news, found);
			if (found) {
				cout << "Internal FRAME collision : " << news << " already exists and can't be escaped?!" << endl;
				exit(4000);
			}
			else {
				mapper m = { news, v };
				vars.insert(vars.begin() + it, m);
			}
		}
	}

	void set(const char * name, value * v) {
		bool found = false;
		int it = find(name, found);
		if (found) {
			vars[it].ptr->free();
			vars[it].ptr = v->copy(this);
		}
		else {
			char * oldp = names.size() == 0 ? NULL : &names[0];
			int oldn = names.size();
			int n = strlen(name);
			names.resize(oldn + n + 1);
			char * newp = &names[0];
			for (int i = 0; i < vars.size(); i++)
				vars[i]._name += newp - oldp;
			char * _name = newp + oldn;
			strcpy(_name, name);
			mapper m = { _name, v->copy(this) };
			vars.insert(vars.begin() + it, m);
		}
	}

	value * get(const char * name) {
		bool found = false;
		int it = find(name, found);
		return found ? vars[it].ptr : NULL;
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

	virtual frame_item * get_next_variant(int i) { return at(i); }

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
public:
	clause(predicate * pp) : parent(pp) { }
	~clause();

	virtual void bind();

	predicate * get_predicate() { return parent; }

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

	virtual int num_items() { return items.size(); }
	virtual predicate_item * get_item(int i) { return items[i]; }
};

class predicate_item {
protected:
	int self_number;
	clause * parent;
	std::list<string> args;
	std::list<value *> _args;

	interpreter * prolog;

	bool neg;
	bool once;
	bool call;
public:
	predicate_item(bool _neg, bool _once, bool _call, int num, clause * c, interpreter * _prolog) : neg(_neg), once(_once), call(_call), self_number(num), parent(c), prolog(_prolog) { }
	~predicate_item() {
		for (value * v : _args)
			v->free();
	}

	virtual void bind() { }

	virtual const string get_id() = 0;

	bool is_negated() { return neg; }
	bool is_once() { return once; }
	bool is_call() { return call; }

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
			return parent->items[self_number + 1];
		}
		else
			return NULL;
	}

	virtual frame_item * get_next_variant(frame_item * f, int & internal_variant, vector<value *> * positional_vals) { return NULL; }

	const std::list<string> * get_args() {
		return &args;
	}

	clause * get_parent() { return parent; }

	bool is_first() { return self_number == 0; }
	bool is_last() { return !parent || self_number == parent->items.size() - 1; }

	virtual generated_vars * generate_variants(frame_item * f, vector<value *> * & positional_vals) = 0;

	virtual bool execute(frame_item * f) {
		return true;
	}
};

class predicate {
	friend predicate_item;
	friend clause;
private:
	string name;
	vector<clause *> clauses;
public:
	predicate(const string & _name) : name(_name) { }
	~predicate();

	void bind() {
		for (clause * c : clauses)
			c->bind();
	}

	void add_clause(clause * c) {
		clauses.push_back(c);
	}

	virtual int num_clauses() { return clauses.size(); }
	virtual clause * get_clause(int i) { return clauses[i]; }
};

class predicate_item_user : public predicate_item {
private:
	string id;
	predicate * user_p;
public:
	predicate_item_user(bool _neg, bool _once, bool _call, int num, clause * c, interpreter * _prolog, const string & _name) : predicate_item(_neg, _once, _call, num, c, _prolog), id(_name) {
		user_p = NULL;
	}

	virtual void bind() {
		if (prolog->PREDICATES.find(id) == prolog->PREDICATES.end())
			user_p = NULL;
		else
			user_p = prolog->PREDICATES[id];
	}

	bool is_dynamic() { return user_p == NULL; }

	predicate * get_user_predicate() { return user_p; }

	virtual const string get_id() { return id; }

	virtual generated_vars * generate_variants(frame_item * f, vector<value *> * & positional_vals);

	virtual bool processing(bool line_neg, int variant, generated_vars * variants, vector<value *> ** positional_vals, frame_item * up_f);
};

#endif
