#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <chrono>

#ifdef __linux__
#include <unistd.h>
#include <pthread.h>
#define EXPORT __attribute__((visibility("default")))
#else
#define EXPORT __declspec(dllexport)
#endif

using namespace std;

#include "../prolog_micro_brain.dir/prolog_micro_brain.h"

#pragma comment(linker, "/STACK:500000000")

std::ofstream F;
std::streambuf * coutbuf;
std::streambuf * cerrbuf;

interpreter * _prolog = NULL;

extern "C" {
	EXPORT int init_gprolog7(char * gprolog_console_out) {
		static int argc = 1;
		static char * argv[] = { ".\\Automodeling.exe" };

		F.open(gprolog_console_out, ios::out | ios::trunc);
		std::streambuf * coutbuf = std::cout.rdbuf(); //save old buf
		std::streambuf * cerrbuf = std::cerr.rdbuf(); //save old buf
		std::cout.rdbuf(F.rdbuf()); //redirect std::cout!
		std::cerr.rdbuf(F.rdbuf()); //redirect std::cerr!

	#ifdef __linux__
		struct rlimit rl = { RLIM_INFINITY, RLIM_INFINITY };
		int result = setrlimit(RLIMIT_STACK, &rl);
		if (result != 0) {
			std::cout << "setrlimit returned result = " << result << endl;
			exit(1000);
		}
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		size_t default_stack_size;
		pthread_attr_getstacksize(&attr, &default_stack_size);

		pthread_attr_setstacksize(&attr, 16 * default_stack_size);
		pthread_setattr_default_np(&attr);
#endif

		setlocale(LC_ALL, "en_US.UTF-8");

		unsigned long long memavail = getTotalSystemMemory();
		fast_memory_manager = memavail > (long long)96 * (long long) 1024 * (long long) 1024 * (long long) 1024;
		mem_block_size = max((unsigned int)mem_block_size, (unsigned int)(4 * (memavail / 65536)));
		mem_block_size -= mem_block_size % 1024;

		_prolog = new interpreter("", "");
		std::cout << "Prolog MicroBrain by V.V.Pekunov V0.23beta" << endl;

		vector<string> renew;
		string body;
		int p = 0;

		frame_item * f = new frame_item();

		map<string, predicate *>::iterator it = _prolog->PREDICATES.begin();
		while (it != _prolog->PREDICATES.end()) {
			renew.push_back(it->first);
			it++;
		}

		_prolog->add_std_body(body);

		bypass_spaces(body, p);
		while (p < body.length()) {
			_prolog->parse_clause(_prolog->CONTEXT, renew, f, body, p);
			bypass_spaces(body, p);
		}
		_prolog->bind();

		delete f;

		F.flush();

		return 0;
	}

	EXPORT int done_gprolog7(char * gprolog_console_out) {
		delete _prolog;

		std::cout.rdbuf(coutbuf);
		std::cerr.rdbuf(cerrbuf);
		F.close();

		return 0;
	}

	static int process(char * Dir, char * ConsultScript,
		char * OutFName, char * MainGoal, char * gprolog_console_out,
		char * DoneGoal, char * GID) {
		static int result;

		static char * goals[8];
		static int i;

		result = 5;

		for (i = 0; i < 8; i++)
			goals[i] = (char *) malloc(65536*2);

		sprintf(goals[0], "change_directory('%s').", Dir);
		sprintf(goals[1], "(consult('%s')->true;rename_file('%s','_erroneous.pl')).", ConsultScript, ConsultScript);
		sprintf(goals[2], "asserta(global_id(%s)).", GID);
		sprintf(goals[3], "tell('%s').", OutFName);
		sprintf(goals[4], "%s.", MainGoal);
		sprintf(goals[5], "told.");
		sprintf(goals[6], "%s.", DoneGoal);
		sprintf(goals[7], "end_of_file.");

		_prolog->outs = &std::cout;
		_prolog->current_output = STD_OUTPUT;
		_prolog->file_num = 0;
		_prolog->current_input = STD_INPUT;
		_prolog->ins = &cin;

		_prolog->CONTEXT->CALLS.resize(0);
		_prolog->CONTEXT->FRAMES.resize(0);
		_prolog->CONTEXT->NEGS.resize(0);
		_prolog->CONTEXT->_FLAGS.resize(0);
		_prolog->CONTEXT->PARENT_CALLS.resize(0);
		_prolog->CONTEXT->PARENT_CALL_VARIANT.resize(0);
		_prolog->CONTEXT->CLAUSES.resize(0);
		// FLAGS;
		_prolog->CONTEXT->LEVELS.resize(0);
		_prolog->CONTEXT->TRACE.resize(0);
		_prolog->CONTEXT->TRACEARGS.resize(0);
		_prolog->CONTEXT->TRACERS.resize(0);
		_prolog->CONTEXT->ptrTRACE.resize(0);
		_prolog->CONTEXT->CTXS.resize(0);

		int goal = 0;
		while (goal < 8) {
			string line;
			int p = 0;

			line = goals[goal++];
			std::cout << ">" << line;

			if (line == "end_of_file" || line == "end_of_file.")
				break;

			vector<string> renew;
			frame_item * f = new frame_item();
			string body;

			map<string, predicate *>::iterator it = _prolog->PREDICATES.begin();
			while (it != _prolog->PREDICATES.end()) {
				renew.push_back(it->first);
				it++;
			}

			_prolog->add_std_body(body);

			body.append("internal_goal:-");
			body.append(line);
			body.append("\n");
			bypass_spaces(body, p);
			while (p < body.length()) {
				_prolog->parse_clause(_prolog->CONTEXT, renew, f, body, p);
				bypass_spaces(body, p);
			}
			_prolog->bind();

			auto start = std::chrono::high_resolution_clock::now(); // Засекаем время
			vector<value *> * args = new vector<value *>();
			generated_vars * variants = new generated_vars();
			variants->push_back(f);
			predicate_item_user * pi = new predicate_item_user(false, false, false, 0, NULL, _prolog, "internal_goal");
			pi->bind();
			bool ret = pi->processing(_prolog->CONTEXT, false, 0, variants, &args, f, _prolog->CONTEXT);
			auto end = std::chrono::high_resolution_clock::now(); // Засечка конечного времени
			std::chrono::duration<double, std::ratio<1, 1>> elapsed = end - start; // Вычисляем длительность исполнения

			int itv = 0;
			while (itv < f->get_size()) {
				std::cout << "  " << f->atn(itv) << " = ";
				f->at(itv)->write(&std::cout);
				std::cout << endl;
				itv++;
			}

			delete args;
			delete variants;

			std::cout << endl;
			std::cout << "Elapsed: " << elapsed.count() << " sec." << std::endl;
			std::cout << (ret ? "true" : "false") << endl;

			delete pi;
			delete f;

			_prolog->CONTEXT->clearDBJournals();
		}

		for (i = 0; i < 8; i++)
			free(goals[i]);

		while (_prolog->files.size()) {
			char buf[128];
			try {
				sprintf(buf, "#%i", _prolog->files.begin()->first);
				_prolog->close_file(string(buf));
			}
			catch (...) {
				std::cout << "main: Problems with closing '" << string(buf) << "'" << endl;
				break;
			}
		}

		return result;
	}
	/**/
	EXPORT int run_gprolog7(char * Dir, char * ConsultScript,
			char * OutFName, char * MainGoal, char * gprolog_console_out,
			char * DoneGoal, char * GID
		) {
		return process(Dir, ConsultScript, OutFName, MainGoal, gprolog_console_out, DoneGoal, GID);
	}
}
