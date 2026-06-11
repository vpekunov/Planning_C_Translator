#include "values.h"

string_atomizer atomizer;

#ifndef _MSC_VER
bool _isnan(double x) {
	return std::isnan(x);
}
#endif

#ifndef _MSC_VER
unsigned long long getTotalSystemMemory()
{
	long pages = sysconf(_SC_PHYS_PAGES);
	long page_size = sysconf(_SC_PAGE_SIZE);
	return (long long)pages * page_size;
}
unsigned int getTotalProcs()
{
	return sysconf(_SC_NPROCESSORS_ONLN);
}
#else
unsigned long long getTotalSystemMemory()
{
	MEMORYSTATUSEX status = { 0 };
	status.dwLength = sizeof(status);
	GlobalMemoryStatusEx(&status);
	return status.ullTotalPhys;
}
unsigned int getTotalProcs()
{
	SYSTEM_INFO sysinfo = { 0 };
	GetSystemInfo(&sysinfo);
	return sysinfo.dwNumberOfProcessors;
}
#endif

clock_rdtsc __clock() {
	auto duration = std::chrono::system_clock().now().time_since_epoch();
	return std::chrono::duration_cast<std::chrono::nanoseconds>(duration).count();
}

void reverse(char s[])
{
	int i, j;
	char c;

	for (i = 0, j = (int)strlen(s) - 1; i < j; i++, j--) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}

char* __ltoa(long long n, char s[], long long radix)
{
	long long i, sign;

	if ((sign = n) < 0)  /* record sign */
		n = -n;          /* make n positive */
	i = 0;
	do {       /* generate digits in reverse order */
		s[i++] = (char)(n % radix) + '0';   /* get next digit */
	} while ((n /= radix) > 0);     /* delete it */
	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';
	reverse(s);

	return s;
}

inline value::value() { refs = 1; }

inline void value::use() { refs++; }

inline void value::free() {
	refs--;
	if (refs == 0) {
		delete(this);
	}
}

inline int value::get_refs() { return refs; }

value* value::const_copy(context* CTX, frame_item* f, int unwind) {
	if (this->defined()) {
		this->use();
		return this;
	}
	else
		return copy(CTX, f, unwind);
}

string value::make_str() {
	return to_str();
}

string value::export_str(bool simple, bool double_slashes) {
	return to_str();
}

void value::write(basic_ostream<char>* outs, bool simple) {
	(*outs) << to_str(simple);
}

any::any() : value() {}

void any::escape_vars(context* CTX, frame_item* ff) {}

value* any::fill(context* CTX, frame_item* vars) { return this; }

value* any::copy(context* CTX, frame_item* f, int unwind) { return new any(); }

bool any::unify(context* CTX, frame_item* ff, value* from) {
	return true;
}

bool any::defined() {
	return false;
}

string any::to_str(bool simple) { return "_"; }

var::var(unsigned int _name) : value() {
	string content = atomizer.get_string(_name);
	if (content.size())
		name = construct_var_name(0, _name, content[0]);
	else
		name = construct_var_name(0, _name, (char)0);
}

var::var(unsigned long long _name, int) : value() {
	name = _name;
}

void var::escape_vars(context* CTX, frame_item* ff) {
	value* v = ff->get(false, CTX, name);
	if (v) {
		v->escape_vars(CTX, ff);
	}
	ff->escape(name);
}

value* var::fill(context* CTX, frame_item* vars) {
	value* v = vars->get(false, CTX, name);
	if (v)
		return v->const_copy(CTX, vars);
	else {
		return this;
	}
}

value* var::copy(context* CTX, frame_item* f, int unwind) {
	value* v = f->get(false, CTX, name, unwind);
	if (v)
		return v->const_copy(CTX, f);
	else
		return new var(name, 0);
}

void var::write(basic_ostream<char>* outs, bool simple) {
	(*outs) << atomizer.get_string(get_name_code(name));
}

const string var::get_name() { return atomizer.get_string(get_name_code(name)); }

const unsigned long long var::get_id() {
	return name;
}

bool var::unify(context* CTX, frame_item* ff, value* from) {
	if (dynamic_cast<var*>(from) || dynamic_cast<any*>(from))
		return true;
	value* v = ff->get(false, CTX, name);
	if (v)
		return v->unify(CTX, ff, from);
	else
		ff->set(false, CTX, name, from);
	return true;
}

bool var::defined() {
	return false;
}

string var::to_str(bool simple) { return /* "__VAR__" + */ get_name(); }

int_number::int_number(long long _v) : value(), v(_v) {}

void int_number::escape_vars(context* CTX, frame_item* ff) {}

value* int_number::fill(context* CTX, frame_item* vars) { return this; }

value* int_number::copy(context* CTX, frame_item* f, int unwind) { return new int_number(v); }

bool int_number::unify(context* CTX, frame_item* ff, value* from) {
	if (dynamic_cast<any*>(from)) return true;
	if (dynamic_cast<var*>(from)) { ff->set(false, CTX, ((var*)from)->get_id(), this); return true; }
	if (dynamic_cast<int_number*>(from))
		return v == ((int_number*)from)->v;
	else if (dynamic_cast<float_number*>(from))
		return v == ((float_number*)from)->v;
	else
		return false;
}

bool int_number::defined() {
	return true;
}

double int_number::get_value() { use(); return 1.0 * v; }

string int_number::to_str(bool simple) {
	char buf[65] = { 0 };

	return string(__ltoa(v, buf, 10));
}

void int_number::inc() { v++; }

void int_number::dec() { v--; }

float_number::float_number(double _v) : value(), v(_v) {}

void float_number::escape_vars(context* CTX, frame_item* ff) {}

value* float_number::fill(context* CTX, frame_item* vars) { return this; }

value* float_number::copy(context* CTX, frame_item* f, int unwind) { return new float_number(v); }

bool float_number::unify(context* CTX, frame_item* ff, value* from) {
	if (dynamic_cast<any*>(from)) return true;
	if (dynamic_cast<var*>(from)) { ff->set(false, CTX, ((var*)from)->get_id(), this); return true; }
	if (dynamic_cast<float_number*>(from))
		return v == ((float_number*)from)->v;
	else if (dynamic_cast<int_number*>(from))
		return v == ((int_number*)from)->v;
	else
		return false;
}

bool float_number::defined() {
	return true;
}

double float_number::get_value() { use();  return v; }

string float_number::to_str(bool simple) {
	char buf[65];

	sprintf(buf, "%lf", v);
	return string(buf);
}

void float_number::inc() { v++; }

void float_number::dec() { v--; }

term::term(const string& _name, const int init_refs) : value() {
	this->refs = init_refs;
	name = atomizer.get_atom(_name);
	cached_defined = 1;
}

term::term(const term& src) {
	this->refs = 1;
	this->name = src.name;
	this->args = vector<value*>();
	cached_defined = 1;
}

term::~term() {}

void term::change_name(const string& _name) {
	name = atomizer.get_atom(_name);
}

void term::free() {
	refs--;
	for (int i = 0; i < args.size(); i++)
		if (args[i]->get_refs() >= refs)
			args[i]->free();
	if (refs == 0)
		delete this;
}

void term::use() {
	refs++;
	for (int i = 0; i < args.size(); i++)
		args[i]->use();
}

void term::escape_vars(context* CTX, frame_item* ff) {
	for (int i = 0; i < args.size(); i++)
		args[i]->escape_vars(CTX, ff);
}

const string term::get_name() { return atomizer.get_string(name); }

const unsigned int term::get_id() {
	return name;
}

const vector<value*>& term::get_args() { return args; }

value* term::fill(context* CTX, frame_item* vars) {
	cached_defined = 1;
	for (int i = 0; i < args.size(); i++) {
		value* old = args[i];
		args[i] = args[i]->fill(CTX, vars);
		if (args[i] != old) old->free();
		if (cached_defined && args[i] && !args[i]->defined())
			cached_defined = 0;
	}
	return this;
}

void term::add_arg(context* CTX, frame_item* f, value* v, int unwind) {
	args.push_back(v->const_copy(CTX, f, unwind));
	if (cached_defined && !args[args.size() - 1]->defined())
		cached_defined = 0;
}

value* term::copy(context* CTX, frame_item* f, int unwind) {
	term* result = new term(*this);
	for (int i = 0; i < args.size(); i++)
		result->add_arg(CTX, f, args[i], unwind);
	return result;
}

bool term::unify(context* CTX, frame_item* ff, value* from) {
	cached_defined = -1;
	if (dynamic_cast<any*>(from)) return true;
	if (dynamic_cast<var*>(from)) { ff->set(false, CTX, ((var*)from)->get_id(), this); return true; }
	if (dynamic_cast<term*>(from)) {
		term* v2 = ((term*)from);
		if (name != v2->name || args.size() != v2->args.size())
			return false;
		for (int i = 0; i < args.size(); i++)
			if (!args[i]->unify(CTX, ff, v2->args[i]))
				return false;
		return true;
	}
	else
		return false;
}

bool term::defined() {
	if (cached_defined >= 0)
		return cached_defined == 1;
	cached_defined = 1;
	for (int i = 0; i < args.size(); i++)
		if (!args[i]->defined()) {
			cached_defined = 0;
			return false;
		}
	return true;
}

string term::to_hex(char SEP) {
	string NAME = atomizer.get_string(name);
	string result;
	for (unsigned char C : NAME) {
		if (C == (unsigned char)SEP)
			result += SEP;
		else {
			int h = C >> 4;
			int l = C & 0x0F;
			if (h > 9) result += (char)('A' + h - 10);
			else result += (char)('0' + h);
			if (l > 9) result += (char)('A' + l - 10);
			else result += (char)('0' + l);
		}
	}
	return result;
}

string term::from_hex(char SEP) {
	string NAME = atomizer.get_string(name);
	string result;

	auto HexDigit = [](char H)->unsigned int {
		if (H >= '0' && H <= '9')
			return H - '0';
		else if (H >= 'A' && H <= 'F')
			return H - 'A' + 10;
		else if (H >= 'a' && H <= 'f')
			return H - 'a' + 10;
		else
			return 0;
		};

	for (size_t i = 0; i < NAME.length(); i++) {
		if (NAME[i] == SEP)
			result += SEP;
		else if (i + 1 < NAME.length()) {
			result += (char)(HexDigit(NAME[i]) * 16 + HexDigit(NAME[i + 1]));
			i++;
		}
		else {
			cout << "from_hex ERROR : '" + NAME + "' can't parse!" << endl;
			exit(1343);
		}
	}
	return result;
}

string term::to_str(bool simple) {
	string result = atomizer.get_string(name);
	if (args.size() > 0) {
		result += "(";
		for (int i = 0; i < args.size() - 1; i++) {
			result += args[i]->to_str(simple);
			result += ",";
		}
		result += args[args.size() - 1]->to_str(simple);
		result += ")";
	}
	return result;
}

string term::escape_specials(const string& src, bool double_slashes) {
	string result;

	int i = 0;
	if (double_slashes)
		while (i < src.length()) {
			switch (src[i]) {
			case '\r': result += "\\\\r"; break;
			case '\n': result += "\\\\n"; break;
			case '\t': result += "\\\\t"; break;
			case '\0': result += "\\\\0"; break;
			default: result += src[i];
			}
			i++;
		}
	else
		while (i < src.length()) {
			switch (src[i]) {
			case '\r': result += "\\r"; break;
			case '\n': result += "\\n"; break;
			case '\t': result += "\\t"; break;
			case '\0': result += "\\0"; break;
			default: result += src[i];
			}
			i++;
		}

	return result;
}

string term::export_str(bool simple, bool double_slashes) {
	string result = escape_specials(atomizer.get_string(name), double_slashes);
	if (result.length() == 0)
		result = "''";
	else {
		bool valid_atom = islower(result[0]);
		for (int i = 1; valid_atom && i < result.length(); i++)
			if (!isalnum(result[i]) && result[i] != '_')
				valid_atom = false;
		if (!valid_atom) {
			char buf[16384];
			sprintf(buf, "'%s'", result.c_str());
			result = buf;
		}
	}
	if (args.size() > 0) {
		result += "(";
		for (int i = 0; i < args.size() - 1; i++) {
			result += args[i]->export_str(simple, double_slashes);
			result += ",";
		}
		result += args[args.size() - 1]->export_str(simple, double_slashes);
		result += ")";
	}
	return result;
}

network::network(const network& src) {
	MAXPROBES = max(2, (int)(getTotalSystemMemory() / ((long long)1024 * 1024 * 1024)));
	YN = new LAYER[MAXPROBES];
	NInputs = src.NInputs;
	FNAME = src.FNAME;
	DAT_FILE_NAME = src.DAT_FILE_NAME;
	NRows = src.NRows;
	NCols = src.NCols;
	NL = src.NL;
	for (int i = 0; i < NL; i++)
		NN[i] = src.NN[i];
	for (int i = 0; i < NInputs + NN[NL-1]; i++)
		NCC[i] = src.NCC[i];
	best_err = src.best_err;

	memmove(YN, src.YN, sizeof(YN));

	memmove(MMIN, src.MMIN, sizeof(MMIN));
	memmove(MMAX, src.MMAX, sizeof(MMAX));
	memmove(mmin, src.mmin, sizeof(mmin));
	memmove(mmax, src.mmax, sizeof(mmax));

	memmove(NUMIN, src.NUMIN, sizeof(NUMIN));
	memmove(NUMAX, src.NUMAX, sizeof(NUMAX));
	memmove(numin, src.numin, sizeof(numin));
	memmove(numax, src.numax, sizeof(numax));

	memmove(d, src.d, sizeof(d));
	memmove(nud, src.nud, sizeof(nud));

	NW = src.NW;
	NB = src.NB;

	if (src.W) {
		W = new long double[NW];
		memmove(W, src.W, NW * sizeof(long double));
	}
	else
		W = NULL;
	if (src.B) {
		B = new long double[NB];
		memmove(B, src.B, NB * sizeof(long double));
	}
	else
		B = NULL;

	memmove(tempX, src.tempX, sizeof(tempX));

	for (int i = 0; i < src.NInputs; i++)
		if (src.X[i]) {
			X[i] = new long double[src.NRows];
			memmove(X[i], src.X[i], src.NRows * sizeof(long double));
		}
		else
			X[i] = NULL;
	for (int i = 0; i < NN[NL - 1]; i++) {
		if (src.Y[i]) {
			Y[i] = new long double[src.NRows];
			memmove(Y[i], src.Y[i], src.NRows * sizeof(long double));
		}
		else
			Y[i] = NULL;
		if (src.YS[i]) {
			YS[i] = new long double[src.NRows];
			memmove(YS[i], src.YS[i], src.NRows * sizeof(long double));
		}
		else
			YS[i] = NULL;
		if (src.ERR[i]) {
			ERR[i] = new long double[src.NRows];
			memmove(ERR[i], src.ERR[i], src.NRows * sizeof(long double));
		}
		else
			ERR[i] = NULL;
	}
}

network::network(const std::string& FName, const std::string& content) {
	MAXPROBES = max(2, (int)(getTotalSystemMemory() / ((long long)1024 * 1024 * 1024)));
	YN = new LAYER[MAXPROBES];
	FNAME = FName;
	istringstream NET(content);
	std::string Buf;
	while (!NET.eof() && (Buf.size() < 3 || Buf[0] != '-' || Buf[1] != '-' || Buf[2] != '-'))
		std::getline(NET, Buf);

	if (NET.eof()) {
		printf("No NET data in the NET FILE\n");
		exit(-11);
	}

	NET >> NInputs;
	size_t cpos1 = FNAME.rfind('\\');
	size_t cpos2 = FNAME.rfind('/');
	do {
		std::getline(NET, DAT_FILE_NAME);
		if (DAT_FILE_NAME.length()) {
			if (DAT_FILE_NAME[DAT_FILE_NAME.length() - 1] == '\n')
				DAT_FILE_NAME.resize(DAT_FILE_NAME.length() - 1);
			if (cpos1 != string::npos || cpos2 != string::npos) {
				size_t pos1 = DAT_FILE_NAME.rfind('\\');
				size_t pos2 = DAT_FILE_NAME.rfind('/');
				if (pos1 == string::npos && pos2 == string::npos) {
					size_t pos = cpos1 == string::npos ? cpos2 : (cpos2 == string::npos ? cpos1 : max(cpos1, cpos2));
					DAT_FILE_NAME = FNAME.substr(0, pos + 1) + DAT_FILE_NAME;
				}
			}
		}
	} while (!NET.eof() && DAT_FILE_NAME.length() == 0);
	if (NET.eof()) {
		printf("No DATA FILE NAME in the NET FILE\n");
		exit(-12);
	}

	NET >> NRows;
	NET >> NCols;

	auto read_array = [&](long double* ARR)->unsigned int {
		string LINE;
		do {
			std::getline(NET, LINE);
			LINE.erase(LINE.begin(), std::find_if(LINE.begin(), LINE.end(), [](unsigned char c) { return !std::isspace(c); }));
		} while (LINE.size() == 0);
		istringstream GET(LINE);
		unsigned int ptr = 0;
		while (GET >> ARR[ptr])
			ptr++;
		return ptr;
	};

	auto read_int_array = [&](int* ARR)->unsigned int {
		string LINE;
		do {
			std::getline(NET, LINE);
			LINE.erase(LINE.begin(), std::find_if(LINE.begin(), LINE.end(), [](unsigned char c) { return !std::isspace(c); }));
		} while (LINE.size() == 0);
		istringstream GET(LINE);
		unsigned int ptr = 0;
		while (GET >> ARR[ptr])
			ptr++;
		return ptr;
	};

	int NCN = read_int_array(NCC);
	if (NCN < NInputs + 1) {
		printf("COLS array is too small?\n");
		exit(-12);
	}

	string BUF;
	do {
		std::getline(NET, BUF);
		BUF.erase(BUF.begin(), std::find_if(BUF.begin(), BUF.end(), [](unsigned char c) { return !std::isspace(c); }));
	} while (BUF.size() == 0);
	istringstream SZ(BUF);
	int number;
	NL = 0;
	while (SZ >> number) {
		NN[NL++] = number;
	}

	if (NL == 0) {
		printf("EMPTY NET detected!!!\n");
		exit(-13);
	}

	for (int i = 0; i < NL; i++) {
		int NP = i == 0 ? NInputs : NN[i - 1];
		NW += NP * NN[i];
		NB += NN[i];
	}

	W = new long double[NW];
	B = new long double[NB];

	for (int i = 0; i < NN[NL - 1]; i++) {
		YS[i] = new long double[NRows];
		ERR[i] = new long double[NRows];
	}

	NET >> best_err;

	for (int i = 0; i < NInputs; i++)
		NET >> MMIN[i];
	for (int i = 0; i < NInputs; i++)
		NET >> MMAX[i];
	for (int i = 0; i < NInputs; i++)
		NET >> mmin[i];
	for (int i = 0; i < NInputs; i++)
		NET >> mmax[i];

	int N1 = read_array(NUMIN);
	int N2 = read_array(NUMAX);
	int N3 = read_array(numin);
	int N4 = read_array(numax);

	if (N1 != N2 || N1 != N3 || N1 != N4 || N1 != NN[NL-1]) {
		printf("NUMIN/NUMAX/numin/numax : incorrect number of outputs?\n");
		exit(-14);
	}

	for (int p = 0; p < NInputs; p++) {
		d[p] = MMAX[p] == MMIN[p] ? 1.0 : (mmax[p] - mmin[p]) / (MMAX[p] - MMIN[p]);
	}

	for (int p = 0; p < NN[NL-1]; p++)
		nud[p] = NUMAX[p] == NUMIN[p] ? 1.0 : (numax[p] - numin[p]) / (NUMAX[p] - NUMIN[p]);

	auto read_val = [&](istringstream& NET, long double& W) {
		string token;
		NET >> token;
		if (token == "inf" || token == "infinity")
			W = INFINITY;
		else
			W = stold(token);
		};

	int ptr = 0;
	for (int layer = 0; layer < NL; layer++) {
		int NP = layer == 0 ? NInputs : NN[layer - 1];
		for (int i = 0; i < NP; i++)
			for (int j = 0; j < NN[layer]; j++, ptr++)
				read_val(NET, W[ptr]);
	}
	ptr = 0;
	for (int layer = 0; layer < NL; layer++)
		for (int j = 0; j < NN[layer]; j++, ptr++)
			NET >> B[ptr];
}

network::network(network* templ, int ni, int n1, int n2, bool first, bool last, int out) {
	MAXPROBES = max(2, (int)(getTotalSystemMemory() / ((long long)1024 * 1024 * 1024)));
	YN = new LAYER[MAXPROBES];
	FNAME = templ->FNAME;

	NInputs = ni;
	DAT_FILE_NAME = templ->DAT_FILE_NAME;

	NRows = templ->NRows;
	NCols = templ->NCols;

	for (int i = 0; i < ni; i++)
		NCC[i] = templ->NCC[i];
	NCC[ni] = templ->NCC[ni + out];

	NL = 3;

	NN[0] = n1;
	NN[1] = n2;
	NN[2] = 1;

	for (int i = 0; i < NL; i++) {
		int NP = i == 0 ? NInputs : NN[i - 1];
		NW += NP * NN[i];
		NB += NN[i];
	}

	W = new long double[NW];
	B = new long double[NB];

	for (int i = 0; i < NN[NL - 1]; i++) {
		YS[i] = new long double[NRows];
		ERR[i] = new long double[NRows];
	}

	best_err = templ->best_err;

	for (int i = 0; i < NInputs; i++)
		MMIN[i] = first ? templ->MMIN[i] : 0.0;
	for (int i = 0; i < NInputs; i++)
		MMAX[i] = first ? templ->MMAX[i] : 1.0;
	for (int i = 0; i < NInputs; i++)
		mmin[i] = first ? templ->mmin[i] : 0.0;
	for (int i = 0; i < NInputs; i++)
		mmax[i] = first ? templ->mmax[i] : 1.0;
	for (int i = 0; i < NN[NL-1]; i++)
		NUMIN[i] = last ? templ->NUMIN[i] : 0.0;
	for (int i = 0; i < NN[NL - 1]; i++)
		NUMAX[i] = last ? templ->NUMAX[i] : 1.0;
	for (int i = 0; i < NN[NL - 1]; i++)
		numin[i] = last ? templ->numin[i] : 0.0;
	for (int i = 0; i < NN[NL - 1]; i++)
		numax[i] = last ? templ->numax[i] : 1.0;

	for (int p = 0; p < NInputs; p++) {
		d[p] = MMAX[p] == MMIN[p] ? 1.0 : (mmax[p] - mmin[p]) / (MMAX[p] - MMIN[p]);
	}

	for (int p = 0; p < NN[NL - 1]; p++)
		nud[p] = NUMAX[p] == NUMIN[p] ? 1.0 : (numax[p] - numin[p]) / (NUMAX[p] - NUMIN[p]);

	int ptr = 0;
	for (int layer = 0; layer < NL; layer++) {
		int NP = layer == 0 ? NInputs : NN[layer - 1];
		for (int i = 0; i < NP; i++)
			for (int j = 0; j < NN[layer]; j++, ptr++)
				W[ptr] = 0.5;
	}
	ptr = 0;
	for (int layer = 0; layer < NL; layer++)
		for (int j = 0; j < NN[layer]; j++, ptr++)
			B[ptr] = 0.5;

	for (int s = 0; s < NInputs; s++)
		X[s] = new long double[NRows];

	for (int s = 0; s < NN[NL-1]; s++)
		Y[s] = new long double[NRows];
}

const std::string& network::fname() { return FNAME; }

void network::setX(unsigned int i, long double v) {
	if (v < MMIN[i]) v = MMIN[i];
	if (v > MMAX[i]) v = MMAX[i];
	tempX[i] = mmin[i] + (v - MMIN[i]) * d[i];
}

void network::set_rowX(unsigned int i, long double v) {
	tempX[i] = v;
}

unsigned int network::nX() { return NInputs; }

unsigned int network::nY() {
	return NN[NL - 1];
}

long double network::getY(int i) {
	return YN[0][NL - 1][i];
}

void network::sim(long double * result) {
	NET(-1);
	for (int i = 0; i < NN[NL-1]; i++)
		result[i] = NUMIN[i] + (YN[0][NL-1][i] - numin[i]) / nud[i];
}

bool network::load_data() {
	for (int i = 0; i < NInputs; i++)
		X[i] = new long double[NRows];

	for (int i = 0; i < NN[NL-1]; i++)
		Y[i] = new long double[NRows];

	ifstream DAT(DAT_FILE_NAME);
	if (DAT) {
		for (int i = 0; i < NRows; i++) {
			long double VALS[1024 * 32];
			for (int j = 0; j < NCols; j++)
				DAT >> VALS[j];
			for (int j = 0; j < NInputs; j++)
				X[j][i] = mmin[j] + (VALS[NCC[j]] - MMIN[j]) * d[j];
			for (int j = 0; j < NN[NL-1]; j++)
				Y[j][i] = numin[j] + (VALS[NCC[NInputs + j]] - NUMIN[j]) * nud[j];
		}
		DAT.close();
	}
	else {
		printf("DAT file '%s' not found!\n", DAT_FILE_NAME.c_str());
		exit(-17);
	}

	return NRows * NCols > 50000;
}

void network::unload_data() {
	for (int i = 0; i < NN[NL - 1]; i++) {
		delete[] Y[i];
		Y[i] = NULL;
	}

	for (int i = 0; i < NInputs; i++) {
		delete[] X[i];
		X[i] = NULL;
	}
}

long double network::S(long double s) {
	return 1.0 / (1.0 + exp(-s));
}

void network::PERTURBED_NET(int i, long double* SMIN, long double* SMAX, vector<long double>* XX, vector<long double>* YY) {
	int id = omp_get_thread_num();

	long double* _W = new long double[NW];
	long double* _B = new long double[NB];
	memmove(_W, this->W, NW * sizeof(long double));
	memmove(_B, this->B, NB * sizeof(long double));

	_W[coord_w[id]] += d_w[id];
	_B[coord_b[id]] += d_b[id];

	for (int i = 0; i < NL; i++)
		memset(&YN[id][i], 0, NN[i] * sizeof(long double));
	int ptr = 0;
	if (i >= 0)
		for (int j = 0; j < NInputs; j++)
			for (int k = 0; k < NN[0]; k++, ptr++)
				YN[id][0][k] += _W[ptr] * X[j][i];
	else
		for (int j = 0; j < NInputs; j++)
			for (int k = 0; k < NN[0]; k++, ptr++)
				YN[id][0][k] += _W[ptr] * tempX[j];
	int ptr1 = 0;
	for (int k = 0; k < NN[0]; k++, ptr1++) {
		YN[id][0][k] += _B[ptr1];
		if (SMIN && SMAX) {
			if (YN[id][0][k] < SMIN[k]) SMIN[k] = YN[id][0][k];
			if (YN[id][0][k] > SMAX[k]) SMAX[k] = YN[id][0][k];
		}
		if (XX) XX[k].push_back(YN[id][0][k]);
		YN[id][0][k] = S(YN[id][0][k]);
		if (YY) YY[k].push_back(YN[id][0][k]);
	}

	for (int layer = 1; layer < NL - 1; layer++) {
		for (int j = 0; j < NN[layer - 1]; j++)
			for (int k = 0; k < NN[layer]; k++, ptr++)
				YN[id][layer][k] += _W[ptr] * YN[id][layer - 1][j];
		for (int k = 0; k < NN[layer]; k++, ptr1++) {
			YN[id][layer][k] += _B[ptr1];
			if (SMIN && SMAX) {
				if (YN[id][layer][k] < SMIN[ptr1]) SMIN[ptr1] = YN[id][layer][k];
				if (YN[id][layer][k] > SMAX[ptr1]) SMAX[ptr1] = YN[id][layer][k];
			}
			if (XX) XX[ptr1].push_back(YN[id][layer][k]);
			YN[id][layer][k] = S(YN[id][layer][k]);
			if (YY) YY[ptr1].push_back(YN[id][layer][k]);
		}
	}

	int idx = 0;
	for (int i = 0; i < NL - 1; i++)
		idx += NN[i];

	for (int q = 0; q < NN[NL - 1]; q++, ptr1++) {
		long double res = _B[ptr1];
		for (int k = 0; k < NN[NL - 2]; k++, ptr++) {
			res += YN[id][NL - 2][k] * _W[ptr];
		}
		if (XX) XX[ptr1].push_back(res);
		if (YY) YY[ptr1].push_back(res);

		if (SMIN && SMAX) {
			if (res < SMIN[idx]) SMIN[idx] = res;
			if (res > SMAX[idx]) SMAX[idx] = res;
			idx++;
		}
		YN[id][NL - 1][q] = res;
	}

	delete[] _B;
	delete[] _W;
}

void network::NET(int i, long double* SMIN, long double* SMAX, vector<long double>* XX, vector<long double>* YY) {
	int id = omp_get_thread_num();
	for (int i = 0; i < NL; i++)
		memset(&YN[id][i], 0, NN[i] * sizeof(long double));
	int ptr = 0;
	int ptr1 = 0;
#ifdef __APPLE__
	vector<float> _X(NInputs);
	vector<float> _W(NW);
	vector<float> _B(NB);
	if (id >= nCPUs) {
		if (i >= 0)
			for (int j = 0; j < NInputs; j++)
				_X[j] = X[j][i];
		else
			for (int j = 0; j < NInputs; j++)
				_X[j] = tempX[j];
		for (int j = 0; j < NW; j++)
			_W[j] = W[j];
		for (int j = 0; j < NB; j++)
			_B[j] = B[j];

		auto __X = mlx::core::array(_X.data(), { NInputs }, mlx::core::float32);

		auto __W0 = mlx::core::array(_W.data(), { NInputs, NN[0] }, mlx::core::float32);
		auto __B0 = mlx::core::array(_B.data(), { NN[0] }, mlx::core::float32);
		auto __Y0 = mlx::core::matmul(__X, __W0) + __B0;
		mlx::core::eval(__Y0);
		const float* y0 = __Y0.data<float>();
		for (int k = 0; k < NN[0]; k++)
			YN[id][0][k] = y0[k];
		ptr += NInputs * NN[0];
		ptr1 = 0;
		for (int k = 0; k < NN[0]; k++, ptr1++) {
			if (SMIN && SMAX) {
				if (YN[id][0][k] < SMIN[k]) SMIN[k] = YN[id][0][k];
				if (YN[id][0][k] > SMAX[k]) SMAX[k] = YN[id][0][k];
			}
			if (XX) XX[k].push_back(YN[id][0][k]);
			YN[id][0][k] = S(YN[id][0][k]);
			if (YY) YY[k].push_back(YN[id][0][k]);
		}
		__Y0 = mlx::core::sigmoid(__Y0);
		for (int layer = 1; layer < NL - 1; layer++) {
			auto __W1 = mlx::core::array(_W.data() + ptr, { NN[layer - 1], NN[layer] }, mlx::core::float32);
			auto __B1 = mlx::core::array(_B.data() + ptr1, { NN[layer] }, mlx::core::float32);
			__Y0 = mlx::core::matmul(__Y0, __W1) + __B1;
			ptr += NN[layer - 1] * NN[layer];
			mlx::core::eval(__Y0);
			const float* y0 = __Y0.data<float>();
			for (int k = 0; k < NN[layer]; k++)
				YN[id][layer][k] = y0[k];
			for (int k = 0; k < NN[layer]; k++, ptr1++) {
				if (SMIN && SMAX) {
					if (YN[id][layer][k] < SMIN[ptr1]) SMIN[ptr1] = YN[id][layer][k];
					if (YN[id][layer][k] > SMAX[ptr1]) SMAX[ptr1] = YN[id][layer][k];
				}
				if (XX) XX[ptr1].push_back(YN[id][layer][k]);
				YN[id][layer][k] = S(YN[id][layer][k]);
				if (YY) YY[ptr1].push_back(YN[id][layer][k]);
			}
			__Y0 = mlx::core::sigmoid(__Y0);
		}
		auto __W2 = mlx::core::array(_W.data() + ptr, { NN[NL - 2], NN[NL-1] }, mlx::core::float32);
		auto __B2 = mlx::core::array(_B.data() + ptr1, { NN[NL-1] }, mlx::core::float32);
		__Y0 = mlx::core::matmul(__Y0, __W2) + __B2;
		ptr += NN[NL - 2] * NN[NL - 1];
		mlx::core::eval(__Y0);
		const float* y1 = __Y0.data<float>();
		for (int k = 0; k < NN[NL-1]; k++)
			YN[id][NL-1][k] = y1[k];
	}
#endif
	if (id < nCPUs) {
		ptr = 0;
		if (i >= 0) {
			for (int j = 0; j < NInputs; j++)
				for (int k = 0; k < NN[0]; k++, ptr++)
					YN[id][0][k] += W[ptr] * X[j][i];
		}
		else {
			for (int j = 0; j < NInputs; j++)
				for (int k = 0; k < NN[0]; k++, ptr++)
					YN[id][0][k] += W[ptr] * tempX[j];
		}
		ptr1 = 0;
		for (int k = 0; k < NN[0]; k++, ptr1++) {
			YN[id][0][k] += B[ptr1];
			if (SMIN && SMAX) {
				if (YN[id][0][k] < SMIN[k]) SMIN[k] = YN[id][0][k];
				if (YN[id][0][k] > SMAX[k]) SMAX[k] = YN[id][0][k];
			}
			if (XX) XX[k].push_back(YN[id][0][k]);
			YN[id][0][k] = S(YN[id][0][k]);
			if (YY) YY[k].push_back(YN[id][0][k]);
		}

		for (int layer = 1; layer < NL - 1; layer++) {
			for (int j = 0; j < NN[layer - 1]; j++)
				for (int k = 0; k < NN[layer]; k++, ptr++)
					YN[id][layer][k] += W[ptr] * YN[id][layer - 1][j];
			for (int k = 0; k < NN[layer]; k++, ptr1++) {
				YN[id][layer][k] += B[ptr1];
				if (SMIN && SMAX) {
					if (YN[id][layer][k] < SMIN[ptr1]) SMIN[ptr1] = YN[id][layer][k];
					if (YN[id][layer][k] > SMAX[ptr1]) SMAX[ptr1] = YN[id][layer][k];
				}
				if (XX) XX[ptr1].push_back(YN[id][layer][k]);
				YN[id][layer][k] = S(YN[id][layer][k]);
				if (YY) YY[ptr1].push_back(YN[id][layer][k]);
			}
		}
		for (int q = 0; q < NN[NL - 1]; q++) {
			long double res = B[ptr1 + q];
			for (int k = 0; k < NN[NL - 2]; k++, ptr++) {
				res += YN[id][NL - 2][k] * W[ptr];
			}
			YN[id][NL - 1][q] = res;
		}
	}

	int idx = 0;
	for (int i = 0; i < NL - 1; i++)
		idx += NN[i];

	for (int q = 0; q < NN[NL - 1]; q++, ptr1++) {
		long double res = YN[id][NL - 1][q];

		if (XX) XX[ptr1].push_back(res);
		if (YY) YY[ptr1].push_back(res);

		if (SMIN && SMAX) {
			if (res < SMIN[idx]) SMIN[idx] = res;
			if (res > SMAX[idx]) SMAX[idx] = res;
			idx++;
		}
	}
}

bool network::train(int MAX_EPOCHS) {
	bool non_compact = false;
	if (!Y[0]) non_compact = load_data();

	const double nu = 0.01;
	const double alpha = 0.2;
	const double tol = 1E-5;

	double err = 1E300;

	int epochs = 0;

	long double* DW = new long double[NW];
	memset(DW, 0, NW * sizeof(long double));

	long double* DB = new long double[NB];
	memset(DB, 0, NB * sizeof(long double));

	double real_err = best_err;

	vector<int> idxs(NRows);
	for (int i = 0; i < NRows; i++)
		idxs[i] = i;
	auto rd = std::random_device{};
	auto rng = std::default_random_engine{ rd() };
	std::shuffle(idxs.begin(), idxs.end(), rng);

	long double YYS = 1E300;
	long double DD[1024];
	int* rands[1024];
	for (int i = 0; i < MAXPROBES; i++)
		rands[i] = new int[NRows * 300];

	do {
		err = 0.0;
		for (int i = 0; i < MAXPROBES; i++)
			for (int j = 0; j < NRows * 300; j++)
				rands[i][j] = rand();
#pragma omp parallel for num_threads(nProbes) schedule(static, 1)
		for (int probe = 0; probe < nProbes; probe++) {
			int id = omp_get_thread_num();
			int rc = 0;
			DD[id] = 1E300;
			int w = 0, b = 0;
			long double ww = 0.0, bb = 0.0;
			for (int tries = 0; tries < 3; tries++) {
				long double dd = 0.0;
				for (int ii = 0; ii < NRows; ii++) {
					int i = idxs[ii];

					do {
						coord_b[id] = rands[id][rc++] % NB;
						if (!isinf(B[coord_b[id]])) {
							d_b[id] = 0.15 - 0.3 * rands[id][rc++] / RAND_MAX;
							break;
						}
					} while (true);
					do {
						coord_w[id] = rands[id][rc++] % NW;
						if (!isinf(W[coord_w[id]])) {
							d_w[id] = 0.15 - 0.3 * rands[id][rc++] / RAND_MAX;
							break;
						}
					} while (true);
					PERTURBED_NET(i);
					for (int q = 0; q < NN[NL - 1]; q++) {
						long double delta = YN[id][NL-1][q] - Y[q][i];
						dd += delta * delta;
					}
				}
				if (dd < DD[id]) {
					w = coord_w[id];
					b = coord_b[id];
					ww = d_w[id];
					bb = d_b[id];
					DD[id] = dd;
				}
			}
			coord_w[id] = w;
			coord_b[id] = b;
			d_w[id] = ww;
			d_b[id] = bb;
		}
		int best = 0;
		for (int probe = 1; probe < nProbes; probe++)
			if (DD[probe] < DD[best]) {
				best = probe;
			}
		if (DD[best] < YYS) {
			B[coord_b[best]] += d_b[best];
			W[coord_w[best]] += d_w[best];
		}
		long double YYS0 = YYS;
		YYS = 0.0;
		double start = !probed ? omp_get_wtime() : 0.0;
		for (int ii = 0; ii < NRows; ii++) {
			int i = idxs[ii];

			NET(i);
			long double delta;
			int NLAST = NN[NL - 1];
			for (int q = 0; q < NLAST; q++) {
				YS[q][i] = YN[0][NL - 1][q];
				delta = YS[q][i] - Y[q][i];

				YYS += delta * delta;

				ERR[q][i] = fabs(delta);
				err += ERR[q][i];

				DB[NB - NLAST + q] = isinf(B[NB - NLAST + q]) ? 0.0 : alpha * DB[NB - NLAST + q] + (1 - alpha) * (-nu * delta);
				B[NB - NLAST + q] += DB[NB - NLAST + q];

				int ptr = NW - (NLAST - q) * NN[NL - 2];
				for (int k = 0; k < NN[NL - 2]; k++, ptr++) {
					DW[ptr] = isinf(W[ptr]) ? 0.0 : alpha * DW[ptr] + (1 - alpha) * (-nu * delta * YN[0][NL - 2][k]);
					W[ptr] += DW[ptr];
				}

				long double deltas[8192] = { 0.0 };

				ptr = NW - (NLAST - q) * NN[NL - 2];
				for (int k = 0; k < NN[NL - 2]; k++, ptr++) {
					deltas[k] = YN[0][NL - 2][k] * (1.0 - YN[0][NL - 2][k]) * delta * W[ptr];
				}

				int ptrw = NW - NLAST * NN[NL - 2] - 1;
				int ptrb = NB - NLAST - 1;
				for (int layer = NL - 2; layer > 0; layer--) {
					ptr = ptrw;
					for (int j = NN[layer - 1] - 1; j >= 0; j--)
						for (int k = NN[layer] - 1; k >= 0; k--, ptrw--) {
							DW[ptrw] = isinf(W[ptrw]) ? 0.0 : alpha * DW[ptrw] + (1 - alpha) * (-nu * deltas[k] * YN[0][layer - 1][j]);
							W[ptrw] += DW[ptrw];
						}
					for (int k = NN[layer] - 1; k >= 0; k--, ptrb--) {
						DB[ptrb] = isinf(B[ptrb]) ? 0.0 : alpha * DB[ptrb] + (1 - alpha) * (-nu * deltas[k]);
						B[ptrb] += DB[ptrb];
					}

					long double deltas1[8192] = { 0.0 };

					for (int j = NN[layer - 1] - 1; j >= 0; j--)
						for (int k = NN[layer] - 1; k >= 0; k--, ptr--) {
							deltas1[j] += YN[0][layer - 1][j] * (1.0 - YN[0][layer - 1][j]) * deltas[k] * W[ptr];
						}
					for (int j = 0; j < NN[layer - 1]; j++)
						deltas[j] = deltas1[j];
				}
				ptr = 0;
				for (int j = 0; j < NInputs; j++)
					for (int k = 0; k < NN[0]; k++, ptr++) {
						DW[ptr] = isinf(W[ptr]) ? 0.0 : alpha * DW[ptr] + (1 - alpha) * (-nu * deltas[k] * X[j][i]);
						W[ptr] += DW[ptr];
					}
				for (int k = 0; k < NN[0]; k++) {
					DB[k] = isinf(B[k]) ? 0.0 : alpha * DB[k] + (1 - alpha) * (-nu * deltas[k]);
					B[k] += DB[k];
				}
			}
		}
		err /= NRows * NN[NL - 1];
		double stop = !probed ? omp_get_wtime() : 0.0;
		if (!probed) {
			double time = stop - start;
			if (time < 1.05 * best_time) {
				best_time = time;
				best_nProbes = nProbes;
				best_nCPUs = nCPUs;
			}
#ifdef __APPLE__
			if (nCPUs == 1) {
#endif
				if (best_nProbes < nProbes || nProbes == MAXPROBES) {
					probed = true;
					nProbes = best_nProbes;
					nCPUs = best_nCPUs;
					cout << "NPROBES = " << nProbes << " [CPU: " << nCPUs << " | MLX: " << (nProbes - nCPUs) << "]\n";
				}
				else {
					nProbes++;
					nCPUs = nProbes;
				}
#ifdef __APPLE__
		}
			else
				nCPUs--;
#else
#endif
		}
		if (epochs % 100 == 0) {
			real_err = 0.0;
			for (int ii = 0; ii < NRows; ii++) {
				int i = idxs[ii];
				NET(i);
				for (int q = 0; q < NN[NL - 1]; q++) {
					YS[q][i] = YN[0][NL - 1][q];
					long double delta = YS[q][i] - Y[q][i];
					real_err += fabs(delta);
				}
			}
			printf("%i epochs reached, err = [%lf (really = %lf) / %i] = %lf (really = %lf)\n", epochs, (double)(err * NRows * NN[NL-1]), real_err, NRows, (double)err, (double)(real_err / (NRows * NN[NL-1])));
			fflush(stdout);
		}
		if (YYS > YYS0)
			std::shuffle(idxs.begin(), idxs.end(), rng);
	} while (err > tol && epochs++ < MAX_EPOCHS);

	for (int i = 0; i < nProbes; i++)
		delete[] rands[i];

	bool result = real_err < best_err;

	best_err = real_err;

	delete[] DW;
	delete[] DB;

	if (non_compact) unload_data();

	return result;
}

vector<std::string> network::simplify(bool to_chain, int maxN, int NVARIANTS, const vector<std::string> * OUT_VAR, set<std::string>& defined) {
	bool non_compact = false;
	if (!Y[0]) non_compact = load_data();

	long double err = 0.0;
	for (int i = 0; i < NRows; i++) {
		NET(i);
		for (int q = 0; q < NN[NL - 1]; q++) {
			YS[q][i] = YN[0][NL - 1][q];
			long double delta = YS[q][i] - Y[q][i];
			ERR[q][i] = fabs(delta);
			err += ERR[q][i];
		}
	}
	err /= NRows * NN[NL-1];

	long double err1 = err * NRows * NN[NL-1];

	long double tol_err = err1 * 1.05;

	bool enhanced = true;
	do {
		long double min_delta = 1E300;
		int min_n_w = -1;
		for (int j = 0; j < NW; j++)
			if (fabs(W[j]) >= 1e-14) {
				long double save = W[j];
				W[j] = 0.0;
				long double err2 = 0.0;
				for (int i = 0; i < NRows; i++) {
					NET(i);
					for (int q = 0; q < NN[NL-1]; q++)
						err2 += fabs(Y[q][i] - YN[0][NL-1][q]);
				}
				if (err2 >= err1 && err2 - err1 < min_delta) {
					min_delta = err2 - err1;
					min_n_w = j;
				}
				W[j] = save;
			}

		if (min_n_w >= 0 && err1 + min_delta < tol_err) {
			W[min_n_w] = 0.0;
			int k = min_n_w;
			int layer = 1;
			while (layer <= NL) {
				int NP = layer == 1 ? NInputs : NN[layer - 2];
				if (k < NP * NN[layer - 1])
					break;
				k -= NP * NN[layer - 1];
				layer++;
			}
			printf("AT ERROR(%lf to %lf) WEIGHT in %i layer (%i-%i) is excluded\n",
				(double)err1, (double)(err1 + min_delta),
				layer,
				k / NN[layer - 1],
				k % NN[layer - 1]
			);
			fflush(stdout);
		}
		else
			enhanced = false;
	} while (enhanced);

	long double* SMIN = new long double[NB];
	long double* SMAX = new long double[NB];
	int* SFREQ = new int[NB * _div];
	memset(SFREQ, 0, NB * _div * sizeof(int));
	for (int j = 0; j < NB; j++) {
		SMIN[j] = 1E300;
		SMAX[j] = -1E300;
	}

	vector<long double>* XX = new vector<long double>[NB];
	vector<long double>* YY = new vector<long double>[NB];
	for (int i = 0; i < NRows; i++)
		NET(i, SMIN, SMAX, XX, YY);

	vector<std::string> result = ANALYZE(omp_get_num_procs(), maxN, NVARIANTS, OUT_VAR, &defined, to_chain, SMIN, SMAX, SFREQ, XX, YY);

	delete[] XX;
	delete[] YY;

	delete[] SMIN;
	delete[] SMAX;

	if (non_compact) unload_data();

	filter_simplification(result);
	return result;
}

network::~network() {
	delete[] W;
	delete[] B;
	for (int i = 0; i < NN[NL - 1]; i++) {
		delete[] Y[i];
		delete[] YS[i];
		delete[] ERR[i];
	}

	for (int i = 0; i < NInputs; i++)
		delete[] X[i];

	delete[] YN;
}

bool network::equals(network* from) {
	if (NInputs != from->NInputs) return false;
	if (DAT_FILE_NAME != from->DAT_FILE_NAME) return false;
	if (NRows != from->NRows) return false;
	if (NCols != from->NCols) return false;
	for (int i = 0; i < NCols; i++)
		if (NCC[i] != from->NCC[i])
			return false;
	if (NL != from->NL) return false;
	for (int i = 0; i < NL; i++)
		if (NN[i] != from->NN[i])
			return false;
	if (best_err != from->best_err) return false;
	for (int i = 0; i < NInputs; i++) {
		if (MMIN[i] != from->MMIN[i]) return false;
		if (MMAX[i] != from->MMAX[i]) return false;
		if (mmin[i] != from->mmin[i]) return false;
		if (mmax[i] != from->mmax[i]) return false;
	}

	for (int i = 0; i < NN[NL-1]; i++)
		if (NUMIN[i] != from->NUMIN[i] || numin[i] != from->numin[i] ||
			NUMAX[i] != from->NUMAX[i] || numax[i] != from->numax[i]) return false;

	if (NW != from->NW || NB != from->NB) return false;
	for (int i = 0; i < NW; i++)
		if (W[i] != from->W[i])
			return false;
	for (int i = 0; i < NB; i++)
		if (B[i] != from->B[i])
			return false;

	return true;
}

const string network::get() {
	ostringstream NET;

	NET << "Net file after additional training by the nnets_simplify\n";
	NET << "-------------------------------------------------------\n";

	NET << NInputs << "\n\n";
	NET << DAT_FILE_NAME << "\n\n";

	NET << NRows << " " << NCols << "\n\n";

	for (int i = 0; i < NInputs + NN[NL-1]; i++)
		NET << NCC[i] << " ";
	NET << "\n\n";

	for (int i = 0; i < NL; i++)
		NET << NN[i] << " ";
	NET << "\n\n";

	NET << setprecision(15) << best_err << "\n\n";
	for (int i = 0; i < NInputs; i++)
		NET << setprecision(15) << MMIN[i] << " ";
	NET << "\n";
	for (int i = 0; i < NInputs; i++)
		NET << setprecision(15) << MMAX[i] << " ";
	NET << "\n\n";
	for (int i = 0; i < NInputs; i++)
		NET << setprecision(15) << mmin[i] << " ";
	NET << "\n";
	for (int i = 0; i < NInputs; i++)
		NET << setprecision(15) << mmax[i] << " ";
	NET << "\n\n";
	for (int i = 0; i < NN[NL-1]; i++)
		NET << setprecision(15) << NUMIN[i] << " ";
	NET << "\n";
	for (int i = 0; i < NN[NL-1]; i++)
		NET << setprecision(15) << NUMAX[i] << " ";
	NET << "\n\n";
	for (int i = 0; i < NN[NL-1]; i++)
		NET << setprecision(15) << numin[i] << " ";
	NET << "\n";
	for (int i = 0; i < NN[NL-1]; i++)
		NET << setprecision(15) << numax[i] << " ";
	NET << "\n\n";
	int ptr = 0;
	for (int layer = 0; layer < NL; layer++) {
		int NP = layer == 0 ? NInputs : NN[layer - 1];
		for (int i = 0; i < NP; i++) {
			for (int j = 0; j < NN[layer]; j++, ptr++)
				NET << setprecision(15) << W[ptr] << " ";
			NET << "\n";
		}
		NET << "\n";
	}
	ptr = 0;
	for (int layer = 0; layer < NL; layer++) {
		for (int j = 0; j < NN[layer]; j++, ptr++)
			NET << setprecision(15) << B[ptr] << " ";
		NET << "\n\n";
	}

	return NET.str();
}

std::string network::create(::_list& nlayers, const std::string& dat_file, ::_list& inps, const vector<int> & out) {
	ostringstream NET;

	NET << "Net file after additional training by the nnets_simplify\n";
	NET << "-------------------------------------------------------\n";

	NET << inps.size() << "\n\n";
	NET << dat_file << "\n\n";

	ifstream dat(dat_file);

	if (!dat) return "";

	int _NCC[1024];

	for (int i = 1; i <= inps.size(); i++) {
		int_number* v = dynamic_cast<int_number*>(inps.get_nth(i, false));
		if (!v)
			return "";
		_NCC[i - 1] = ((int)(0.5 + v->get_value()));
	}
	if (nlayers.size() == 0)
		return "";
	int_number* _NLAST = dynamic_cast<int_number*>(nlayers.get_nth(nlayers.size(), false));
	if (!_NLAST)
		return "";
	int NLAST = ((int)(0.5 + _NLAST->get_value()));

	if (NLAST != out.size())
		return "";

	std::string line;
	long double VALS[1024];
	long double _MMIN[1024];
	long double _MMAX[1024];
	long double _NUMIN[1024];
	long double _NUMAX[1024];
	for (int i = 0; i < inps.size(); i++) {
		_MMIN[i] = 1E300;
		_MMAX[i] = -1E300;
	}
	for (int i = 0; i < NLAST; i++) {
		_NUMIN[i] = 1E300;
		_NUMAX[i] = -1E300;
	}
	size_t NR = 0;
	size_t NC = 0;
	while (getline(dat, line)) {
		if (line.length()) {
			istringstream LINE(line);
			size_t locNC = 0;
			while (LINE >> VALS[locNC])
				locNC++;
			if (locNC > NC)
				NC = locNC;
			for (int j = 0; j < inps.size(); j++) {
				long double v = VALS[_NCC[j]];
				if (v < _MMIN[j])
					_MMIN[j] = v;
				if (v > _MMAX[j])
					_MMAX[j] = v;
			}
			for (int q = 0; q < NLAST; q++) {
				long double ov = VALS[out[q]];
				if (ov < _NUMIN[q])
					_NUMIN[q] = ov;
				if (ov > _NUMAX[q])
					_NUMAX[q] = ov;
			}
			NR++;
		}
	}

	dat.close();

	if (NC > inps.size() + NLAST)
		return "";

	NET << NR << " " << NC << "\n\n";

	for (int i = 1; i <= inps.size(); i++) {
		if (_NCC[i - 1] >= NC)
			return "";
		NET << _NCC[i - 1] << " ";
	}
	for (int q = 0; q < NLAST; q++) {
		if (out[q] >= NC)
			return "";
		NET << out[q];
		if (q < NLAST - 1)
			NET << " ";
	}
	NET << "\n\n";

	for (int i = 1; i <= nlayers.size(); i++) {
		int_number* v = dynamic_cast<int_number*>(nlayers.get_nth(i, false));
		if (!v)
			return "";
		NET << ((int)(0.5 + v->get_value())) << " ";
	}
	NET << "\n\n";

	NET << setprecision(15) << 1E300 << "\n\n";
	for (int i = 0; i < inps.size(); i++)
		NET << setprecision(15) << _MMIN[i] << " ";
	NET << "\n";
	for (int i = 0; i < inps.size(); i++)
		NET << setprecision(15) << _MMAX[i] << " ";
	NET << "\n\n";
	for (int i = 0; i < inps.size(); i++)
		NET << setprecision(15) << -1 << " ";
	NET << "\n";
	for (int i = 0; i < inps.size(); i++)
		NET << setprecision(15) << +1 << " ";
	NET << "\n\n";
	for (int i = 0; i < NLAST; i++)
		NET << setprecision(15) << _NUMIN[i] << " ";
	NET << "\n";
	for (int i = 0; i < NLAST; i++)
		NET << setprecision(15) << _NUMAX[i] << " ";
	NET << "\n\n";
	for (int i = 0; i < NLAST; i++)
		NET << setprecision(15) << -1 << " ";
	NET << "\n";
	for (int i = 0; i < NLAST; i++)
		NET << setprecision(15) << +1 << " ";
	NET << "\n\n";

	auto rd = std::random_device{};
	auto rng = std::default_random_engine{ rd() };
	std::uniform_real_distribution<double> distribution(-1.0, 1.0);

	int ptr = 0;
	for (int layer = 0; layer < nlayers.size(); layer++) {
		int NP;
		if (layer == 0)
			NP = inps.size();
		else {
			int_number* v = dynamic_cast<int_number*>(nlayers.get_nth(layer, false));
			if (!v)
				return "";
			NP = ((int)(0.5 + v->get_value()));
		}
		for (int i = 0; i < NP; i++) {
			int_number* v = dynamic_cast<int_number*>(nlayers.get_nth(layer + 1, false));
			if (!v)
				return "";
			int _NN = ((int)(0.5 + v->get_value()));
			for (int j = 0; j < _NN; j++, ptr++)
				NET << setprecision(15) << distribution(rng) << " ";
			NET << "\n";
		}
		NET << "\n";
	}
	ptr = 0;
	for (int layer = 0; layer < nlayers.size(); layer++) {
		int_number* v = dynamic_cast<int_number*>(nlayers.get_nth(layer + 1, false));
		if (!v)
			return "";
		int _NN = ((int)(0.5 + v->get_value()));
		for (int j = 0; j < _NN; j++, ptr++)
			NET << setprecision(15) << distribution(rng) << " ";
		NET << "\n\n";
	}

	return NET.str();
}

/* LU - разложение  с выбором максимального элемента по диагонали */
bool network::_GetLU(int NN, int* iRow, long double* A, long double* LU)
{
	int i, j, k;
	try {
		memmove(LU, A, NN * NN * sizeof(long double));
		for (i = 0; i < NN; i++)
			iRow[i] = i;
		for (i = 0; i < NN - 1; i++)
		{
			long double Big = fabs(LU[iRow[i] * NN + i]);
			int iBig = i;

			long double Kf;

			for (j = i + 1; j < NN; j++)
			{
				long double size = fabs(LU[iRow[j] * NN + i]);

				if (size > Big)
				{
					Big = size;
					iBig = j;
				}
			}
			if (iBig != i)
			{
				int V = iRow[i];
				iRow[i] = iRow[iBig];
				iRow[iBig] = V;
			}
			Kf = 1.0 / LU[iRow[i] * NN + i];

			LU[iRow[i] * NN + i] = Kf;
			for (j = i + 1; j < NN; j++)
			{
				long double Fact = Kf * LU[iRow[j] * NN + i];

				LU[iRow[j] * NN + i] = Fact;
				for (k = i + 1; k < NN; k++)
					LU[iRow[j] * NN + k] -= Fact * LU[iRow[i] * NN + k];
			}
		}
		LU[(iRow[NN - 1] + 1) * NN - 1] = 1.0 / LU[(iRow[NN - 1] + 1) * NN - 1];
	}
	catch (...) {
		return false;
	}
	return true;
}

/* Метод LU - разложения */
bool network::_SolveLU(int NN, int* iRow, long double* LU, long double* Y, long double* X)
{
	int i, j, k;
	try {
		X[0] = Y[iRow[0]];
		for (i = 1; i < NN; i++)
		{
			long double V = Y[iRow[i]];

			for (j = 0; j < i; j++)
				V -= LU[iRow[i] * NN + j] * X[j];
			X[i] = V;
		}

		X[NN - 1] *= LU[(iRow[NN - 1] + 1) * NN - 1];

		for (i = 1, j = NN - 2; i < NN; i++, j--)
		{
			long double V = X[j];

			for (k = j + 1; k < NN; k++)
				V -= LU[iRow[j] * NN + k] * X[k];
			X[j] = V * LU[iRow[j] * NN + j];
		}
	}
	catch (...) {
		return false;
	}
	return true;
}

long double* network::MNK_of_X(int N, const vector<long double> W, const vector<long double> X, const vector<long double> Y, double& err) {
	int Z = (int)X.size();
	vector<long double> _XP(Z, 1.0);
	long double* A = new long double[N * N];
	long double* LU = new long double[N * N];
	long double* B = new long double[N];
	long double* XX = new long double[N];
	int* iLU = new int[N];
	int i, j, k;

	for (i = 0; i < 2 * N - 1; i++) {
		long double QX = 0.0;
		long double QY = 0.0;
		for (j = 0; j < Z; j++) {
			QX += W[j] * _XP[j];
			if (i < N) QY += W[j] * _XP[j] * Y[j];
			_XP[j] *= X[j];
		}
		for (j = (i < N ? i : N - 1), k = (i < N ? 0 : i - N + 1); j >= 0 && k < N; j--, k++)
			A[k * N + j] = QX;
		if (i < N) B[i] = QY;
	}
	long double ZZ = 0.0;
	if (!(_GetLU(N, iLU, A, LU) && _SolveLU(N, iLU, LU, B, XX))) {
		memset(XX, 0, N * sizeof(long double));
		err = 1E300;
	}
	else {
		for (k = 0; k < N; k++)
			if (_isnan(XX[k])) {
				memset(XX, 0, N * sizeof(long double));
				err = 1E300;
				return XX;
			}
		err = 0.0;
		for (j = 0; j < Z; j++) {
			long double R = 0.0;
			for (k = N - 1; k >= 0; k--)
				R = R * X[j] + XX[k];
			double cur_err = fabs(R - Y[j]);
			err += W[j] * cur_err;
			ZZ += W[j];
		}
	}

	delete[] A;
	delete[] LU;
	delete[] B;
	delete[] iLU;

	if (ZZ > 0.0) err /= ZZ;

	return XX;
}

block_network::block_network(const block_network& src) : network(src) {
	n_networks = src.n_networks;
	NETWORKS = new network * [n_networks];
	for (unsigned int i = 0; i < n_networks; i++)
		NETWORKS[i] = new network(*src.NETWORKS[i]);
}

block_network::block_network(const std::string& FName, const std::string& content) : network(FName, content) {
	if (NL % 3) {
		printf("Only nets with (NLayers %% 3 == 0) can have 'block' type\n");
		exit(-19);
	}

	load_data();

	for (int layer = 2; layer < NL; layer += 3) {
		n_networks += NN[layer];
	}
	NETWORKS = new network * [n_networks];

	int WBASE = 0;
	int BBASE = 0;
	n_networks = 0;
	for (int layer = 2; layer < NL; layer += 3) {
		int n = layer == 2 ? NInputs : NN[layer - 3];
		int NOUTS = NN[layer];
		int N1 = NN[layer - 2] / NOUTS;
		int rN1 = NN[layer - 2] % NOUTS;
		int N2 = NN[layer - 1] / NOUTS;
		int rN2 = NN[layer - 1] % NOUTS;
		int BBASE2 = BBASE + NN[layer - 2];
		int BBASE3 = BBASE2 + NN[layer - 1];
		int nw[8192] = { 0 };
		int nb[8192] = { 0 };
		if (N1 == 0 || N2 == 0) {
			cout << "Can't granularize network. Reason: number of outputs is greater than number of neurons in middle layers!\n";
			exit(-153);
		}
		for (int N = 0; N < NOUTS; N++) {
			int _N1 = N1;
			if (N < rN1) _N1++;
			int _N2 = N2;
			if (N < rN2) _N2++;

			NETWORKS[n_networks + N] = new network(this, n, _N1, _N2, layer == 2, layer == NL - 1, layer < NL - 1 ? 0 : N);

			int _BBASE = BBASE + N;
			for (int i = 0; i < _N1; i++, nb[N]++) {
				for (int j = 0; j < n; j++, nw[N]++) {
					NETWORKS[n_networks + N]->W[nw[N]] = W[WBASE++];
				}
				NETWORKS[n_networks + N]->B[nb[N]] = B[_BBASE];
				_BBASE++;
			}
		}
		for (int N = 0; N < NOUTS; N++) {
			int _N1 = N1;
			if (N < rN1) _N1++;
			int _N2 = N2;
			if (N < rN2) _N2++;

			int _BBASE2 = BBASE2 + N;
			for (int j = 0; j < N * _N1; j++) {
				WBASE++;
			}
			for (int i = 0; i < _N2; i++, nb[N]++) {
				for (int j = 0; j < _N1; j++, nw[N]++) {
					NETWORKS[n_networks + N]->W[nw[N]] = W[WBASE++];
				}
				NETWORKS[n_networks + N]->B[nb[N]] = B[_BBASE2];
				_BBASE2++;
			}
			for (int j = 0; j < (NN[layer - 1] - N - _N2) * _N1; j++) {
				WBASE++;
			}
		}
		for (int N = 0; N < NOUTS; N++, n_networks++) {
			int _N1 = N1;
			if (N < rN1) _N1++;
			int _N2 = N2;
			if (N < rN2) _N2++;

			int _BBASE3 = BBASE3 + N;
			for (int j = 0; j < N * _N2; j++, nw) {
				WBASE++;
			}
			for (int j = 0; j < _N2; j++, nw[N]++) {
				NETWORKS[n_networks]->W[nw[N]] = W[WBASE++];
			}
			for (int j = 0; j < (NN[layer] - N - 1) * _N2; j++) {
				WBASE++;
			}
			NETWORKS[n_networks]->B[nb[N]] = B[_BBASE3];
			NETWORKS[n_networks]->best_err = 100.0 * best_err;
		}
		BBASE = BBASE3 + NOUTS;
	}

	for (int i = 0; i < NRows; i++) {
		network::NET(i);

		n_networks = 0;
		BBASE = 0;
		for (int layer = 2; layer < NL; layer += 3) {
			int n = layer == 2 ? NInputs : NN[layer - 3];
			int NOUTS = NN[layer];
			for (int N = 0; N < NOUTS; N++, n_networks++) {
				for (int j = 0; j < n; j++) {
					double x = layer == 2 ? X[j][i] : YN[0][layer - 3][j];
					NETWORKS[n_networks]->X[j][i] = x;
				}
				double y = YN[0][layer][N];
				NETWORKS[n_networks]->Y[0][i] = y;
			}
		}
	}

	WBASE = 0;
	BBASE = 0;
	n_networks = 0;
	for (int layer = 2; layer < NL; layer += 3) {
		int n = layer == 2 ? NInputs : NN[layer - 3];
		int NOUTS = NN[layer];
		int N1 = NN[layer - 2] / NOUTS;
		int rN1 = NN[layer - 2] % NOUTS;
		int N2 = NN[layer - 1] / NOUTS;
		int rN2 = NN[layer - 1] % NOUTS;
		int BBASE2 = BBASE + NN[layer - 2];
		int BBASE3 = BBASE2 + NN[layer - 1];
		int nw[8192] = { 0 };
		int nb[8192] = { 0 };
		for (int N = 0; N < NOUTS; N++) {
			int _N1 = N1;
			if (N < rN1) _N1++;
			int _N2 = N2;
			if (N < rN2) _N2++;

			int _BBASE = BBASE + N;
			for (int i = 0; i < _N1; i++, nb[N]++) {
				for (int j = 0; j < n; j++, nw[N]++) {
					WBASE++;
				}
				_BBASE++;
			}
		}
		for (int N = 0; N < NOUTS; N++) {
			int _N1 = N1;
			if (N < rN1) _N1++;
			int _N2 = N2;
			if (N < rN2) _N2++;

			int _BBASE2 = BBASE2 + N;
			for (int j = 0; j < N * _N1; j++) {
				W[WBASE++] = INFINITY;
			}
			for (int i = 0; i < _N2; i++, nb[N]++) {
				for (int j = 0; j < _N1; j++, nw[N]++) {
					WBASE++;
				}
				_BBASE2++;
			}
			for (int j = 0; j < (NN[layer - 1] - N - _N2) * _N1; j++) {
				W[WBASE++] = INFINITY;
			}
		}
		for (int N = 0; N < NOUTS; N++, n_networks++) {
			int _N1 = N1;
			if (N < rN1) _N1++;
			int _N2 = N2;
			if (N < rN2) _N2++;

			int _BBASE3 = BBASE3 + N;
			for (int j = 0; j < N * _N2; j++, nw) {
				W[WBASE++] = INFINITY;
			}
			for (int j = 0; j < _N2; j++, nw[N]++) {
				WBASE++;
			}
			for (int j = 0; j < (NN[layer] - N - 1) * _N2; j++) {
				W[WBASE++] = INFINITY;
			}
		}
		BBASE = BBASE3 + NOUTS;
	}

	unload_data();
}

bool block_network::train(int MAX_EPOCHS) {
	bool result = true;

	for (unsigned int i = 0; i < n_networks; i++)
		result &= NETWORKS[i]->train(MAX_EPOCHS);

	return result;
}

void block_network::PERTURBED_NET(int i, long double* SMIN, long double* SMAX, vector<long double>* XX, vector<long double>* YY) {
	int id = omp_get_thread_num();
	int BBASE = 0;
	n_networks = 0;
	long double _XX[8192];
	for (int layer = 2; layer < NL; layer += 3) {
		int n = layer == 2 ? NInputs : NN[layer - 3];
		int NOUTS = NN[layer];
		for (int N = 0; N < NOUTS; N++, n_networks++) {
			if (layer == 2)
				for (int k = 0; k < NInputs; k++)
					NETWORKS[n_networks]->set_rowX(k, X[k][i]);
			else
				for (int k = 0; k < NETWORKS[n_networks]->NInputs; k++)
					NETWORKS[n_networks]->set_rowX(k, _XX[k]);
			NETWORKS[n_networks]->PERTURBED_NET(-1);
			_XX[N] = NETWORKS[n_networks]->YN[id][NETWORKS[n_networks]->NL - 1][0];
			YN[id][layer][N] = _XX[N];
		}
	}
}

void block_network::NET(int i, long double* SMIN, long double* SMAX, vector<long double>* XX, vector<long double>* YY) {
	int id = omp_get_thread_num();
	int BBASE = 0;
	n_networks = 0;
	long double _XX[8192];
	for (int layer = 2; layer < NL; layer += 3) {
		int n = layer == 2 ? NInputs : NN[layer - 3];
		int NOUTS = NN[layer];
		for (int N = 0; N < NOUTS; N++, n_networks++) {
			if (layer == 2)
				for (int k = 0; k < NInputs; k++)
					NETWORKS[n_networks]->set_rowX(k, X[k][i]);
			else
				for (int k = 0; k < NETWORKS[n_networks]->NInputs; k++)
					NETWORKS[n_networks]->set_rowX(k, _XX[k]);
			NETWORKS[n_networks]->NET(-1);
			_XX[N] = NETWORKS[n_networks]->YN[id][NETWORKS[n_networks]->NL - 1][0];
			YN[id][layer][N] = _XX[N];
		}
	}
}

vector<std::string> block_network::simplify(bool to_chain, int maxN, int NVARIANTS, const vector<std::string> * OUT_VAR, set<std::string>& defined) {
	vector<std::string> result(1);

	n_networks = 0;
	vector<std::string> XX;
	for (int layer = 2; layer < NL; layer += 3) {
		int n = layer == 2 ? NInputs : NN[layer - 3];
		int NOUTS = NN[layer];
		for (int k = 0; k < NETWORKS[n_networks]->NInputs; k++) {
			char var[2] = { (char)('a' + k), 0 };
			if (k >= NInputs && defined.find(var) == defined.end()) {
				defined.insert(var);
			}
			if (layer > 2) {
				result[0] += var;
				result[0] += " = ";
				result[0] += XX[k];
				result[0] += ";\n";
			}
		}
		XX.clear();
		for (int N = 0; N < NOUTS; N++, n_networks++) {
			char buf[80];
			std::string OUTER = layer == NL-1 ? OUT_VAR->at(N) : (std::string("OUT") + __itoa(n_networks, buf, 10));
			vector<std::string> OUTERS(1, OUTER);
			vector<std::string> addition = NETWORKS[n_networks]->simplify(to_chain, maxN, 1, &OUTERS, defined);
			if (addition.size() == 0)
				return vector<string>(1, "ERROR!");
			result[0] += addition[0];
			result[0] += "\n";
			XX.push_back(OUTER);
		}
	}

	return result;
}

block_network::~block_network() {
	for (unsigned int i = 0; i < n_networks; i++)
		delete NETWORKS[i];
}

bool block_network::equals(network* from) {
	block_network* _from = dynamic_cast<block_network*>(from);
	if (_from == NULL)
		return false;
	if (NInputs != from->NInputs) return false;
	if (DAT_FILE_NAME != from->DAT_FILE_NAME) return false;
	if (NRows != from->NRows) return false;
	if (NCols != from->NCols) return false;
	for (int i = 0; i < NCols; i++)
		if (NCC[i] != from->NCC[i])
			return false;

	for (unsigned int i = 0; i < n_networks; i++)
		if (!NETWORKS[i]->equals(_from->NETWORKS[i]))
			return false;

	return true;
}

nnet::nnet() : term("nnet", 1) {
	net = NULL;
}

nnet::nnet(const nnet& src) : term("nnet", 1) {
	this->args.push_back(new ::term(src.args[0]->to_str()));
	const block_network* bn = dynamic_cast<const block_network*>(src.net);
	if (bn)
		net = new block_network(*bn);
	else
		net = new network(*src.net);
}

nnet::nnet(const std::string& fname, ifstream& in, bool block) : term("nnet") {
	string content;
	in.seekg(0, std::ios::end);
	content.reserve(in.tellg());
	in.seekg(0, std::ios::beg);

	content.assign((std::istreambuf_iterator<char>(in)),
		std::istreambuf_iterator<char>());
	this->args.push_back(new ::term(content));
	if (block)
		net = new block_network(fname, content);
	else
		net = new network(fname, content);
}

nnet::~nnet() { delete net; }

value* nnet::const_copy(context* CTX, frame_item* f, int unwind) {
	return copy(CTX, f, unwind);
}

nnet* nnet::granularize() {
	ifstream _IN(net->fname());

	nnet* result = new nnet(net->fname(), _IN, true);

	if (_IN) _IN.close();

	return result;
}

void nnet::free() {
	refs--;
	if (refs == 0)
		delete this;
}

const string nnet::get_content() { return net->get(); }

bool nnet::train(int MAX_EPOCHS) { return net->train(MAX_EPOCHS); }

vector<string> nnet::simplify(bool to_chain, int maxN, set<std::string>& defined) {
	vector<std::string> OUTERS;
	for (unsigned int i = 0; i < net->nY(); i++) {
		char buf[80];
		std::string OUTER = std::string("OUT") + __itoa(i, buf, 10);
		defined.insert(OUTER);
		OUTERS.push_back(OUTER);
	}
	return net->simplify(to_chain, maxN, net->HOW_MANY, &OUTERS, defined);
}

void nnet::sim(long double * result) { return net->sim(result); }

unsigned int nnet::nX() { return net->nX(); }

unsigned int nnet::nY() {
	return net->nY();
}

long double nnet::getY(int i) {
	return net->getY(i);
}

void nnet::setX(unsigned int i, long double v) { net->setX(i, v); }

value* nnet::copy(context* CTX, frame_item* f, int unwind) {
	return new nnet(*this);;
}

void nnet::add_arg(context* CTX, frame_item* f, value* v, int unwind) {
	term::add_arg(CTX, f, v, unwind);
	term* arg = dynamic_cast<term*>(v);
	if (args.size() > 1 || !v) {
		cout << "nnet(arg) must has one term arg only!";
		exit(1001);
	}
	net = new network("", arg->get_name());
}

bool nnet::unify(context* CTX, frame_item* ff, value* from) {
	cached_defined = -1;
	if (dynamic_cast<nnet*>(from)) {
		return net->equals(dynamic_cast<nnet*>(from)->net);
	}
	else
		return term::unify(CTX, ff, from);
}

string nnet::to_str(bool simple) {
	return get_content();
}

indicator::indicator(const string& _name, int _arity) : value(), name(_name), arity(_arity) {}

void indicator::escape_vars(context* CTX, frame_item* ff) {}

const string& indicator::get_name() { return name; }

int indicator::get_arity() { return arity; }

value* indicator::fill(context* CTX, frame_item* vars) {
	return this;
}

value* indicator::copy(context* CTX, frame_item* f, int unwind) {
	return new indicator(name, arity);
}

bool indicator::unify(context* CTX, frame_item* ff, value* from) {
	if (dynamic_cast<any*>(from)) return true;
	if (dynamic_cast<var*>(from)) { ff->set(false, CTX, ((var*)from)->get_id(), this); return true; }
	if (dynamic_cast<indicator*>(from)) {
		indicator* v2 = ((indicator*)from);
		return name == v2->name && arity == v2->arity;
	}
	else
		return false;
}

bool indicator::defined() {
	return true;
}

string indicator::to_str(bool simple) {
	string result = name;

	char buf[65];
	result += "/";
	result += __itoa(arity, buf, 10);

	return result;
}

::_list::_list(const stack_container<value*>& v, value* _tag) : value(), tag(_tag) {
	is_of_chars = true;
	chars = "";
	for (int i = 0; is_of_chars && i < v.size(); i++) {
		term* t = dynamic_cast<term*>(v[i]);
		if (t && t->get_args().size() == 0) {
			string s = t->get_name();
			if (s.length() != 1) {
				is_of_chars = false;
				chars = "";
			}
			else {
				chars += s[0];
			}
		}
		else {
			is_of_chars = false;
			chars = "";
		}
	}
	cached_defined = (tag == NULL || tag->defined()) ? 1 : 0;
	if (is_of_chars) {
		for (int i = 0; i < v.size(); i++)
			v[i]->free();
	}
	else {
		val = v;
		if (cached_defined)
			for (value* vv : v)
				if (!vv->defined()) {
					cached_defined = false;
					break;
				}
	}
}

::_list::_list(const string& v, value* _tag) : value(), tag(_tag) {
	is_of_chars = true;
	cached_defined = (tag == NULL || tag->defined()) ? 1 : 0;
	chars = v;
}

::_list::~_list() {}

void ::_list::free() {
	for (value* v : val)
		v->free();
	if (tag) tag->free();
	refs--;
	if (refs == 0)
		delete this;
}

void ::_list::use() {
	refs++;
	for (value* v : val)
		v->use();
	if (tag) tag->use();
}

bool ::_list::of_chars() { return is_of_chars; }

const string& ::_list::get_chars() { return chars; }

void ::_list::convert_non_chars(context* CTX) {
	if (is_of_chars) {
		is_of_chars = false;
		for (char s : chars)
			val.push_back(new term(string(1, s), refs));
		chars = "";
	}
}

void ::_list::escape_vars(context* CTX, frame_item* ff) {
	for (value* v : val)
		v->escape_vars(CTX, ff);
	if (tag)
		tag->escape_vars(CTX, ff);
}

int ::_list::size() {
	int result = (int)(is_of_chars ? chars.size() : val.size());
	if (tag)
		if (dynamic_cast<_list*>(tag))
			result += ((_list*)tag)->size();
		else
			result++;
	return result;
}

value* ::_list::get_last(context* CTX) {
	if (tag)
		if (dynamic_cast<_list*>(tag))
			return ((_list*)tag)->get_last(CTX);
		else {
			tag->use();
			return tag;
		}
	else if (is_of_chars && chars.size() == 0 || !is_of_chars && val.size() == 0)
		return NULL;
	else if (is_of_chars) {
		return new term(string(1, chars[chars.length() - 1]), refs);
	}
	else {
		stack_container<value*>::iterator it = val.end();

		(*(--it))->use();

		return *it;
	}
}

value* ::_list::get_nth(int n, bool inc_ref) {
	if (n < 1) return NULL;

	if (is_of_chars && n <= chars.size() || !is_of_chars && n <= val.size()) {
		if (is_of_chars) {
			return new term(string(1, chars[n - 1]), refs);
		}
		else {
			stack_container<value*>::iterator it = val.begin() + (size_t)(n - 1);
			if (inc_ref) (*it)->use();
			return *it;
		}
	}
	else
		if (tag)
			if (dynamic_cast<_list*>(tag))
				return ((_list*)tag)->get_nth(
					(int)(is_of_chars ? n - chars.size() : n - val.size()),
					inc_ref);
			else {
				if (inc_ref) tag->use();
				return tag;
			}
		else
			return NULL;
}

bool ::_list::set_nth(int n, value* v) {
	if (n < 1) return false;

	if (is_of_chars && n <= chars.size() || !is_of_chars && n <= val.size()) {
		if (is_of_chars) {
			term* t = dynamic_cast<term*>(v);
			if (t && t->get_name().length() == 1) {
				chars[(size_t)(n - 1)] = t->get_name()[0];
				return true;
			}
			else
				return false;
		}
		else {
			stack_container<value*>::iterator it = val.begin() + (size_t)(n - 1);
			(*it)->free();
			(*it) = v;
			v->use();

			cached_defined = -1;
			if (v && !v->defined())
				cached_defined = 0;

			return true;
		}
	}
	else
		if (tag) {
			cached_defined = -1;
			if (v && !v->defined())
				cached_defined = 0;

			if (dynamic_cast<_list*>(tag))
				return ((_list*)tag)->set_nth((int)(is_of_chars ? n - chars.size() : n - val.size()), v);
			else {
				tag->free();
				tag = v;
				v->use();
				return true;
			}
		}
		else
			return false;
}

void ::_list::iterate(std::function<void(value*)> check) {
	if (is_of_chars) {
		term* t = new term("");
		for (char s : chars) {
			t->change_name(string(1, s));
			check(t);
		}
		t->free();
	}
	else {
		stack_container<value*>::iterator it = val.begin();
		while (it != val.end()) {

			check(*it);
			it++;
		}
	}
	if (tag)
		if (dynamic_cast<_list*>(tag))
			((_list*)tag)->iterate(check);
		else
			check(tag);
}

void ::_list::split(context* CTX, frame_item* f, int p, value*& L1, value*& L2) {
	if (is_of_chars && !tag) {
		string S1 = chars.substr(0, p);
		string S2 = chars.substr(p);
		L1 = new _list(S1, NULL);
		L2 = new _list(S2, NULL);
	}
	else {
		stack_container<value*> S, S1, S2;
		get(CTX, f, &S);

		stack_container<value*>::iterator it = S.begin();
		S1.reserve(p);
		for (int i = 0; i < p; i++)
			S1.push_back((*it++)->const_copy(CTX, f));
		S2.reserve(S.size() - p);
		for (int i = p; i < S.size(); i++)
			S2.push_back((*it++)->const_copy(CTX, f));
		L1 = new _list(S1, NULL);
		L2 = new _list(S2, NULL);
	}
}

void ::_list::const_split(context* CTX, frame_item* f, int p, value*& L1, value*& L2) {
	if (is_of_chars && !tag) {
		string S1 = chars.substr(0, p);
		string S2 = chars.substr(p);
		L1 = new _list(S1, NULL);
		L2 = new _list(S2, NULL);
	}
	else {
		if (!defined()) return split(CTX, f, p, L1, L2);
		stack_container<value*> S, S1, S2;
		get(CTX, f, &S);

		stack_container<value*>::iterator it = S.begin();
		S1.reserve(p);
		for (int i = 0; i < p; i++)
			S1.push_back((*it++)->const_copy(CTX, f));
		S2.reserve(S.size() - p);
		for (int i = p; i < S.size(); i++)
			S2.push_back((*it++)->const_copy(CTX, f));
		L1 = new _list(S1, NULL);
		L2 = new _list(S2, NULL);
	}
}

::_list* ::_list::from(context* CTX, frame_item* f, stack_container<value*>::iterator starting) {
	_list* result = new _list(stack_container<value*>(), NULL);
	while (starting != val.end())
	{
		result->add(CTX, (*starting)->const_copy(CTX, f));
		starting++;
	}
	if (tag) result->set_tag(tag->copy(CTX, f));
	return result;
}

::_list* ::_list::from(context* CTX, frame_item* f, string::iterator starting) {
	_list* result = new _list(string(starting, chars.end()), NULL);
	if (tag) result->set_tag(tag->copy(CTX, f));
	return result;
}

::_list* ::_list::const_from(context* CTX, frame_item* f, stack_container<value*>::iterator starting) {
	if (!defined()) return from(CTX, f, starting);
	_list* result = new _list(stack_container<value*>(), NULL);
	while (starting != val.end())
	{
		(*starting)->use();
		result->add(CTX, *starting);
		starting++;
	}
	if (tag) {
		tag->use();
		result->set_tag(tag);
	}
	return result;
}

::_list* ::_list::const_from(context* CTX, frame_item* f, string::iterator starting) {
	if (!defined()) return from(CTX, f, starting);
	_list* result = new _list(string(starting, chars.end()), NULL);
	if (tag) {
		tag->use();
		result->set_tag(tag);
	}
	return result;
}

value* ::_list::fill(context* CTX, frame_item* vars) {
	cached_defined = 1;
	if (!is_of_chars) {
		stack_container<value*>::iterator it = val.begin();
		for (; it != val.end(); it++) {
			value* old = *it;
			*it = (*it)->fill(CTX, vars);
			if (*it != old) old->free();
			if (cached_defined && *it && !(*it)->defined())
				cached_defined = 0;
		}
	}
	if (tag) {
		value* old = tag;
		tag = tag->fill(CTX, vars);
		if (old && old != tag) old->free();
		if (cached_defined && tag && !tag->defined())
			cached_defined = 0;
	}
	return this;
}

::_list* ::_list::append(context* CTX, frame_item* f, _list* L2) {
	::_list* result = NULL;
	if (is_of_chars && !tag && L2->of_chars()) {
		result = new ::_list(chars + L2->get_chars(), NULL);
	}
	else {
		result = ((_list*)copy(CTX, f));
		if (is_of_chars) convert_non_chars(CTX);
		if (L2->of_chars()) {
			for (char s : L2->get_chars())
				result->add(CTX, new term(string(1, s)));
		}
		else
			for (value* v : L2->val) {
				result->add(CTX, v->const_copy(CTX, f));
				if (cached_defined && !v->defined())
					cached_defined = 0;
			}
	}
	if (L2->tag) {
		if (cached_defined && !L2->tag->defined())
			cached_defined = 0;
		if (dynamic_cast<::_list*>(L2->tag))
			return result->append(CTX, f, ((_list*)L2->tag));
		else
			result->add(CTX, L2->tag->copy(CTX, f));
	}
	return result;
}

value* ::_list::copy(context* CTX, frame_item* f, int unwind) {
	if (is_of_chars)
		return new ::_list(chars, tag ? tag->copy(CTX, f) : NULL);
	else {
		stack_container<value*> new_val;
		new_val.reserve(val.size());
		for (value* v : val)
			new_val.push_back(v->const_copy(CTX, f));
		return new ::_list(new_val, tag ? tag->copy(CTX, f) : NULL);
	}
}

void ::_list::add(context* CTX, value* v) {
	if (cached_defined && v && !v->defined())
		cached_defined = 0;

	if (tag)
		if (dynamic_cast<_list*>(tag))
			((_list*)tag)->add(CTX, v);
		else {
			std::cout << "Adding to non-list tag?!" << endl;
			exit(1);
		}
	else {
		term* t = dynamic_cast<term*>(v);
		if (t && t->get_args().size() == 0) {
			if (is_of_chars) {
				string s = t->get_name();
				if (s.length() == 1)
					chars += s;
				else {
					convert_non_chars(CTX);
					val.push_back(v);
				}
			}
			else {
				val.push_back(v);
			}
		}
		else {
			convert_non_chars(CTX);
			val.push_back(v);
		}
	}
}

void ::_list::set_tag(value* new_tag) {
	if (cached_defined && new_tag && !new_tag->defined())
		cached_defined = 0;

	if (tag) tag->free();
	if (dynamic_cast<_list*>(new_tag) && ((_list*)new_tag)->size() == 0)
		new_tag = NULL;
	tag = new_tag;
	if (new_tag) new_tag->use();
}

bool ::_list::get(context* CTX, frame_item* f, stack_container<value*>* dest) {
	dest->clear();
	if (is_of_chars) {
		for (char s : chars)
			dest->push_back(new term(string(1, s)));
	}
	else
		for (value* v : val)
			dest->push_back(v->const_copy(CTX, f));
	if (tag) {
		if (dynamic_cast<_list*>(tag)) {
			stack_container<value*> ltag;
			if (((_list*)tag)->get(CTX, f, &ltag)) {
				for (value* v : ltag)
					dest->push_back(v->const_copy(CTX, f));
				return true;
			}
			else
				return false;
		}
		dest->push_back(tag->copy(CTX, f));
		return true;
	}
	else return true;
}

bool ::_list::unify(context* CTX, frame_item* ff, value* from) {
	cached_defined = -1;
	if (dynamic_cast<any*>(from)) return true;
	if (dynamic_cast<var*>(from)) {
		ff->set(false, CTX, ((var*)from)->get_id(), this);
		return true;
	}
	if (dynamic_cast<_list*>(from)) {
		value* _from = (_list*)from;
		stack_container<value*>::iterator _from_it = ((_list*)_from)->val.begin();
		string::iterator _from_it_s = ((_list*)_from)->chars.begin();
		value* _to = this;
		stack_container<value*>::iterator _to_it = ((_list*)_to)->val.begin();
		string::iterator _to_it_s = ((_list*)_to)->chars.begin();

		while (_from && _to) {
			bool advanced = false;
			if (dynamic_cast<_list*>(_from))
				while (dynamic_cast<_list*>(_from) && (
					((_list*)_from)->is_of_chars && _from_it_s == ((_list*)_from)->chars.end() ||
					!((_list*)_from)->is_of_chars && _from_it == ((_list*)_from)->val.end()
					)) {
					_from = ((_list*)_from)->tag;
					if (dynamic_cast<_list*>(_from)) {
						_from_it_s = ((_list*)_from)->chars.begin();
						_from_it = ((_list*)_from)->val.begin();
					}
					advanced = true;
				}
			if (dynamic_cast<_list*>(_to))
				while (dynamic_cast<_list*>(_to) && (
					((_list*)_to)->is_of_chars && _to_it_s == ((_list*)_to)->chars.end() ||
					!((_list*)_to)->is_of_chars && _to_it == ((_list*)_to)->val.end()
					)) {
					_to = ((_list*)_to)->tag;
					if (dynamic_cast<_list*>(_to)) {
						_to_it_s = ((_list*)_to)->chars.begin();
						_to_it = ((_list*)_to)->val.begin();
					}
					advanced = true;
				}
			if (dynamic_cast<any*>(_from) || dynamic_cast<any*>(_to))
				return true;
			if (dynamic_cast<var*>(_from))
				if (dynamic_cast<_list*>(_to))
					if (((_list*)_to)->of_chars())
						return _from->unify(CTX, ff, ((_list*)_to)->const_from(CTX, ff, _to_it_s));
					else
						return _from->unify(CTX, ff, ((_list*)_to)->const_from(CTX, ff, _to_it));
				else if (_to)
					return _from->unify(CTX, ff, _to);
				else
					return _from->unify(CTX, ff, new ::_list(stack_container<value*>(), NULL));
			if (dynamic_cast<var*>(_to))
				if (dynamic_cast<_list*>(_from))
					if (((_list*)_from)->of_chars())
						return _to->unify(CTX, ff, ((_list*)_from)->const_from(CTX, ff, _from_it_s));
					else
						return _to->unify(CTX, ff, ((_list*)_from)->const_from(CTX, ff, _from_it));
				else if (_from)
					return _to->unify(CTX, ff, _from);
				else
					return _to->unify(CTX, ff, new ::_list(stack_container<value*>(), NULL));
			if (dynamic_cast<_list*>(_from) && dynamic_cast<_list*>(_to)) {
				if (((_list*)_from)->of_chars() && ((_list*)_to)->of_chars())
					if ((*_to_it_s++) != (*_from_it_s++))
						return false;
					else
						advanced = true;
				else if (((_list*)_from)->of_chars() != ((_list*)_to)->of_chars()) {
					if (((_list*)_from)->of_chars()) {
						term* fr = new term(string(1, *_from_it_s++));
						if (!(*_to_it++)->unify(CTX, ff, fr)) {
							fr->free();
							return false;
						}
						else
							advanced = true;
						fr->free();
					}
					else {
						term* t = new term(string(1, *_to_it_s++));
						if (!(*_from_it++)->unify(CTX, ff, t)) {
							t->free();
							return false;
						}
						else
							advanced = true;
						t->free();
					}
				}
				else
					if (!(*_to_it++)->unify(CTX, ff, *_from_it++))
						return false;
					else
						advanced = true;
			}
			if (!advanced)
				return _to->unify(CTX, ff, _from);
		}

		return !_from && !_to;
	}
	else
		return false;
}

bool ::_list::defined() {
	if (cached_defined >= 0)
		return cached_defined == 1;
	cached_defined = 1;
	if (!is_of_chars)
		for (value* v : val)
			if (!v->defined()) {
				cached_defined = 0;
				return false;
			}
	if (tag) {
		bool result = tag->defined();
		cached_defined = result ? 1 : 0;
		return result;
	}
	return true;
}

string _list::make_str() {
	string result;
	if (is_of_chars) {
		result = chars;
	}
	else
		for (value* v : val)
			result += v->make_str();
	if (tag)
		result += tag->make_str();
	return result;
}

string _list::to_str(bool simple) {
	string result;

	int k = 0;

	if (!simple) result += "[";
	if (is_of_chars) {
		for (char s : chars) {
			result += s;
			k++;
			if (k < chars.size() || tag && !(dynamic_cast<_list*>(tag) && dynamic_cast<_list*>(tag)->size() == 0))
				result += ",";
		}
	}
	else
		for (value* v : val) {
			result += v->to_str(false);
			k++;
			if (k < val.size() || tag && !(dynamic_cast<_list*>(tag) && dynamic_cast<_list*>(tag)->size() == 0))
				result += ",";
		}
	if (tag) {
		result += tag->to_str(true);
	}
	if (!simple) result += "]";

	return result;
}

string _list::export_str(bool simple, bool double_slashes) {
	string result;

	int k = 0;

	if (!simple) result += "[";
	if (is_of_chars) {
		for (char s : chars) {
			result += string("'") + s + string("'");
			k++;
			if (k < chars.size() || tag && !(dynamic_cast<_list*>(tag) && dynamic_cast<_list*>(tag)->size() == 0))
				result += ",";
		}
	}
	else
		for (value* v : val) {
			result += v->export_str(false, double_slashes);
			k++;
			if (k < val.size() || tag && !(dynamic_cast<_list*>(tag) && dynamic_cast<_list*>(tag)->size() == 0))
				result += ",";
		}
	if (tag) {
		result += tag->export_str(true, double_slashes);
	}
	if (!simple) result += "]";

	return result;
}

string_atomizer::string_atomizer() { forking = false; }

void string_atomizer::set_forking(bool v) { forking = v; }

unsigned int string_atomizer::get_atom(const string& s) {
	if (s.length() == 1)
		return (unsigned char)s[0];
	else if (s.length() == 2)
		return (((unsigned char)s[1]) << 8) + (unsigned char)s[0];
	else {
		size_t L = s.length();
		if (L <= 6) {
			size_t l = 0;
			size_t u = 0;
			size_t d = 0;
			for (size_t i = 0; i < L; i++)
				if (i == u && (s[i] >= 0x40 && s[i] <= 0x5E))
					u++;
				else if (i == l && (s[i] >= 0x60 && s[i] <= 0x7E))
					l++;
				else if (i == d && (s[i] >= 0x20 && s[i] <= 0x3E))
					d++;
				else
					break;
			if (l == L) {
				unsigned int R = 0;
				for (int i = 0; i < L; i++) {
					unsigned int code = s[i] - 0x60 + 1;
					R <<= 5;
					R |= code;
				}
				return 0x80000000U + R;
			}
			else if (u == L) {
				unsigned int R = 0;
				for (int i = 0; i < L; i++) {
					unsigned int code = s[i] - 0x40 + 1;
					R <<= 5;
					R |= code;
				}
				return 0x40000000U + R;
			}
			else if (d == L) {
				unsigned int R = 0;
				for (int i = 0; i < L; i++) {
					unsigned int code = s[i] - 0x20 + 1;
					R <<= 5;
					R |= code;
				}
				return 0xC0000000U + R;
			}
		}

		if (forking) locker.lock();
		unsigned int result = 0;
		map<string, unsigned int>::iterator it = hash.find(s);
		if (it != hash.end())
			result = it->second;
		else {
			if (table.size() == table.capacity()) {
				table.reserve(table.size() + 2000);
			}
			pair<map<string, unsigned int>::iterator, bool> itt =
				hash.insert(pair<string, unsigned int>(s, 0));
			table.push_back(&itt.first->first);
			itt.first->second = (unsigned int)(65536 + table.size() - 1);
			result = itt.first->second;
		}
		if (forking) locker.unlock();
		return result;
	}
}

const string string_atomizer::get_string(unsigned int atom) {
	if (atom < 256) {
		char buf[2] = { (char)atom, 0 };
		return string(buf);
	}
	else if (atom < 65536) {
		char buf[3] = { (char)(atom & 0xFF), (char)(atom >> 8), 0 };
		return string(buf);
	}
	else if (atom >= 0x40000000U) {
		char C[7];
		char base = 0x20;
		int L = 6;
		C[L] = 0;
		if ((atom & 0xC0000000U) == 0x80000000U)
			base = 0x60;
		else if ((atom & 0xC0000000U) == 0x40000000U)
			base = 0x40;
		atom &= 0x3FFFFFFFU;
		while (atom) {
			unsigned int code = atom & 0x1F;
			C[--L] = code - 1 + base;
			atom >>= 5;
		}
		return string(&C[L]);
	}
	else {
		if (forking) locker.lock();
		string result = *table[atom - 65536];
		if (forking) locker.unlock();
		return result;
	}
}

frame_item::frame_item(unsigned int _name_capacity, unsigned int _vars_capacity, context* CTX, frame_item* inheriting) {
	names_capacity = _name_capacity;
	names = (unsigned long long*) malloc(names_capacity * sizeof(char));
	names_length = 0;
	vars.reserve(_vars_capacity);
	deleted = NULL;

	import_transacted_globs(CTX, inheriting);
}

frame_item::~frame_item() {
	int it = 0;
	while (it < vars.size()) {
		if (vars[it].ptr)
			vars[it].ptr->free();
		it++;
	}
	if (names)
		free(names);
	if (deleted)
		free(deleted);
}

bool frame_item::lock() { return false; }

void frame_item::unlock() {}

void frame_item::forced_import_transacted_globs(context* CTX, frame_item* inheriting) {
	lock();
	for (mapper& m : inheriting->vars) {
		if (get_first_char(m._name[0]) == '*')
			set(true, CTX, m._name[0], m.ptr, true);
	}
	unlock();
}

void frame_item::import_transacted_globs(context* CTX, frame_item* inheriting) {
	if (CTX && inheriting && (CTX->THR || CTX->forked())) {
		forced_import_transacted_globs(CTX, inheriting);
	}
}

void frame_item::add_local_names(bool locals_in_forked, std::set<unsigned long long>& s) {
	for (mapper& m : vars)
		if (get_wind(m._name[0]) == 0 && (!locals_in_forked || get_first_char(m._name[0]) == '*'))
			s.insert(m._name[0]);
}

void frame_item::sync(bool _locked, bool not_sync_globs, context* CTX, frame_item* other) {
	bool locked = !_locked && lock();
	int it = 0;
	while (it < other->vars.size()) {
		unsigned long long* itc = other->vars[it]._name;
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

frame_item* frame_item::copy(context* CTX) {
	frame_item* result = new frame_item(names_capacity, (unsigned int)vars.size());
	result->names_length = names_length;
	memmove(result->names, names, names_length * sizeof(char));
	long long d = &result->names[0] - &names[0];
	result->vars = vars;
	for (mapper& m : result->vars) {
		m.ptr = m.ptr ? m.ptr->const_copy(CTX, this) : NULL;
		m._name += d;
	}
	return result;
}

const string frame_item::atn(int i) {
	return atomizer.get_string(get_name_code(*vars[i]._name));
}

int frame_item::find(const unsigned long long what, bool& found) {
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

void frame_item::escape(unsigned long long& _name) {
	bool found = false;
	int it = find(_name, found);
	escape_name(_name);
	if (found) {
		unsigned long long* oldp = &names[0];
		unsigned long long* s = vars[it]._name;
		*s = _name;
		// names.insert(names.begin() + (s - oldp), prepend);
		value* v = vars[it].ptr;
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

void frame_item::set(bool _locked, context* CTX, const unsigned long long name, value* v, bool set_time_zero) {
	bool found = false;
	int it = find(name, found);
	if (found) {
		if (vars[it].ptr) vars[it].ptr->free();
		vars[it].ptr = v ? v->const_copy(CTX, this) : NULL;
	}
	else {
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
	}
}

int frame_item::unset(bool _locked, context* CTX, const unsigned long long name) {
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
		deleted = (unsigned long long*) realloc(deleted, size_deleted * sizeof(unsigned long long));
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
	}
	else
		return -1;
}

value* frame_item::get(bool _locked, context* CTX, unsigned long long name, int unwind) {
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

void frame_item::register_facts(bool _locked, context* CTX, std::set<unsigned long long>& names) {
	bool locked = !_locked && lock();
	std::unique_lock<fastmux> lock(*CTX->DBLOCK);
	map<unsigned long long, std::atomic<journal*>>::iterator it = CTX->DBJournal->begin();
	while (it != CTX->DBJournal->end()) {
		unsigned long long fact = it->first;
		register_fact_group(locked, CTX, fact, it->second);
		names.insert(fact);
		it++;
	}
	if (locked) lock.unlock();
}

void frame_item::unregister_facts(bool _locked, context* CTX) {
	bool locked = !_locked && lock();
	std::unique_lock<fastmux> lock(*CTX->DBLOCK);
	map<unsigned long long, std::atomic<journal*>>::iterator it = CTX->DBJournal->begin();
	while (it != CTX->DBJournal->end()) {
		unsigned long long fact = it->first;
		unregister_fact_group(locked, CTX, fact);
		it++;
	}
	if (locked) lock.unlock();
}

tframe_item::tframe_item(unsigned int _name_capacity, unsigned int _vars_capacity, context* CTX, frame_item* inheriting) : frame_item(_name_capacity, _vars_capacity) {
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

tframe_item::~tframe_item() {
	lock();
	if (info_vars != micro_info)
		free(info_vars);
	unlock();
}

bool tframe_item::lock() { return mutex.try_lock(); }

void tframe_item::unlock() { mutex.unlock(); }

void tframe_item::set(bool _locked, context* CTX, const unsigned long long name, value* v, bool set_time_zero) {
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
			}
			else
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

value* tframe_item::get(bool _locked, context* CTX, const unsigned long long name, int unwind) {
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

int tframe_item::unset(bool _locked, context* CTX, const unsigned long long name) {
	bool locked = !_locked && mutex.try_lock();
	int it = frame_item::unset(locked, CTX, name);
	if (it >= 0) {
		for (int i = it; i < vars.size(); i++)
			info_vars[i] = info_vars[i + 1];
	}
	if (locked) unlock();
	return it;
}

void tframe_item::register_write(const unsigned long long name) {
	bool found = false;
	int it = find(name, found);
	clock_rdtsc c = __clock();
	if (found && info_vars[it].first_writes == 0)
		info_vars[it].first_writes = c;
	if (found)
		info_vars[it].last_writes = c;
}

clock_rdtsc tframe_item::first_write(const unsigned long long vname) {
	bool found = false;
	int it = find(vname, found);
	if (found)
		return info_vars[it].first_writes;
	else
		return 0;
}

clock_rdtsc tframe_item::last_read(const unsigned long long vname) {
	bool found = false;
	int it = find(vname, found);
	if (found)
		return info_vars[it].last_reads;
	else
		return 0;
}

clock_rdtsc tframe_item::first_read(const unsigned long long vname) {
	bool found = false;
	int it = find(vname, found);
	if (found)
		return info_vars[it].first_reads;
	else
		return 0;
}

clock_rdtsc tframe_item::last_write(const unsigned long long vname) {
	bool found = false;
	int it = find(vname, found);
	if (found)
		return info_vars[it].last_writes;
	else
		return 0;
}

void tframe_item::set_written_new(frame_item* src) {
	for (mapper& m : vars)
		if (get_first_char(m._name[0]) != '*') {
			bool found;
			src->find(m._name[0], found);
			if (!found)
				register_write(m._name[0]);
		}
}

void tframe_item::statistics(const unsigned long long vname, clock_rdtsc& cr, clock_rdtsc& fw, clock_rdtsc& fr, clock_rdtsc& lw, clock_rdtsc& lr) {
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

tframe_item* frame_item::tcopy(context* CTX, _interpreter* INTRP, bool import_globs) {
	tframe_item* result = new tframe_item(names_capacity, (unsigned int)vars.size() + 5);
	result->names_length = names_length;
	memmove(result->names, names, names_length * sizeof(char));
	long long d = &result->names[0] - &names[0];
	result->vars = vars;
	for (mapper& m : result->vars) {
		m.ptr = m.ptr ? m.ptr->const_copy(CTX, this) : NULL;
		m._name += d;
	}
	memset(result->info_vars, 0, vars.size() * sizeof(tframe_item::var_info));
	if (CTX && import_globs /* && (CTX->THR || CTX->forked()) */) {
		bool locked = INTRP->GLOCK.try_lock();
		std::map<std::string, value*>::iterator it = INTRP->GVars.begin();
		while (it != INTRP->GVars.end()) {
			if (it->first.length() && it->first[0] != '&') {
				string new_name = it->first;
				new_name.insert(0, 1, '*');
				bool use_local_copy = false;
				// find(new_name.c_str(), use_local_copy);
				// if (!use_local_copy)
				result->set(true, CTX, construct_var_name(0, atomizer.get_atom(new_name), '*'), it->second);
			}
			it++;
		}
		if (locked) INTRP->GLOCK.unlock();
	}
	memset(result->info_vars, 0, vars.size() * sizeof(tframe_item::var_info));
	return result;
}

void frame_item::register_write(const std::string& name) {}

int frame_item::get_size() { return (int)vars.size(); }

value* frame_item::at(int i) {
	return vars[i].ptr;
}

void frame_item::register_fact_group(bool _locked, context* CTX, unsigned long long& fact, journal* J) {
	bool found = false;
	string _fact = atomizer.get_string(get_name_code(fact));
	_fact.insert(0, 1, '!');
	fact = construct_var_name(0, atomizer.get_atom(_fact), '!');
	int it = find(fact, found);
	if (!found) {
		set(_locked, CTX, fact, NULL);
	}
}

void frame_item::unregister_fact_group(bool _locked, context* CTX, unsigned long long& fact) {
	bool found = false;
	string _fact = atomizer.get_string(get_name_code(fact));
	_fact.insert(0, 1, '!');
	fact = construct_var_name(0, atomizer.get_atom(_fact), '!');
	int it = find(fact, found);
	if (found)
		unset(_locked, CTX, fact);
}

void tframe_item::register_fact_group(bool _locked, context* CTX, unsigned long long& fact, journal* J) {
	bool locked = !_locked && mutex.try_lock();
	bool found = false;
	string _fact = atomizer.get_string(get_name_code(fact));
	_fact.insert(0, 1, '!');
	fact = construct_var_name(0, atomizer.get_atom(_fact), '!');
	int it = find(fact, found);
	if (!found) {
		set(locked, CTX, fact, NULL);
		it = find(fact, found);
	}
	if (!info_vars[it].first_writes || info_vars[it].first_writes > J->first_write) {
		info_vars[it].first_writes = J->first_write;
		if (!info_vars[it].last_writes)
			info_vars[it].last_writes = info_vars[it].first_writes;
	}
	if (!info_vars[it].last_writes || info_vars[it].last_writes < J->last_write) {
		info_vars[it].last_writes = J->last_write;
		if (!info_vars[it].first_writes)
			info_vars[it].first_writes = info_vars[it].last_writes;
	}
	if (!info_vars[it].first_reads || info_vars[it].first_reads > J->first_read) {
		info_vars[it].first_reads = J->first_read;
		if (!info_vars[it].last_reads)
			info_vars[it].last_reads = info_vars[it].first_reads;
	}
	if (!info_vars[it].last_reads || info_vars[it].last_reads < J->last_read) {
		info_vars[it].last_reads = J->last_read;
		if (!info_vars[it].first_reads)
			info_vars[it].first_reads = info_vars[it].last_reads;
	}
	if (locked) unlock();
}

void tframe_item::unregister_fact_group(bool _locked, context* CTX, unsigned long long& fact) {
	bool locked = !_locked && mutex.try_lock();
	frame_item::unregister_fact_group(locked, CTX, fact);
	if (locked) unlock();
}

void tframe_item::sync(bool _locked, bool not_sync_globs, context* CTX, frame_item* other) {
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
		unsigned long long* itc = _other->vars[it]._name;
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

frame_item* tframe_item::copy(context* CTX) {
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

tframe_item* tframe_item::tcopy(context* CTX, _interpreter* INTRP) {
	return dynamic_cast<tframe_item*>(copy(CTX));
}

journal::journal() {
	creation = __clock();

	first_write = last_write = first_read = last_read = 0;
}

journal::~journal() {
	for (journal_item* it : log)
		delete it;
}

void journal::register_read() {
	clock_rdtsc c = __clock();
	if (!first_read)
		first_read = c;
	last_read = c;
}

void journal::register_write(jTypes t, value* data, int position, journal* src) {
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

journal_item::journal_item(jTypes t, value* data, int position) {
	this->type = t;
	this->data = data;
	this->position = position;
}

journal_item::~journal_item() {
	if (this->type == jDelete)
		this->data->free();
}
