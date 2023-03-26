#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <iostream>
#include <vector>
#include <string>

using namespace std;

#include "../prolog_micro_brain/prolog_micro_brain.h"

#pragma comment(linker, "/STACK:100000000")

static FILE * F = NULL;
static int saved_out;
static int saved_err;

interpreter * _prolog = NULL;

extern "C" {
	__declspec(dllexport) int __cdecl init_gprolog7(char * gprolog_console_out) {
		static int argc = 1;
		static char * argv[] = { ".\\Automodeling.exe" };

		F = fopen(gprolog_console_out, "wt");
		saved_out = _dup(1);
		saved_err = _dup(2);
		_dup2(_fileno(F), 1);
		_dup2(_fileno(F), 2);

	#ifdef __linux__
		struct rlimit rl = { RLIM_INFINITY, RLIM_INFINITY };
		int result = setrlimit(RLIMIT_STACK, &rl);
		if (result != 0) {
			std::cout << "setrlimit returned result = " << result << endl;
			exit(1000);
		}
	#endif

		setlocale(LC_ALL, "en_US.UTF-8");

		fast_memory_manager = getTotalSystemMemory() > (long long)8 * (long long)1024 * (long long)1024 * (long long)1024;

		_prolog = new interpreter("", "");
		std::cout << "Prolog MicroBrain by V.V.Pekunov V0.21beta" << endl;

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
			_prolog->parse_clause(renew, f, body, p);
			bypass_spaces(body, p);
		}
		_prolog->bind();

		delete f;

		fflush(stderr);
		fflush(stdout);
		fclose(F);

		_dup2(saved_out, 1);
		_dup2(saved_err, 2);

		return 0;
	}

	__declspec(dllexport) int __cdecl done_gprolog7(char * gprolog_console_out) {
		F = fopen(gprolog_console_out, "at");
		saved_out = _dup(1);
		saved_err = _dup(2);
		_dup2(_fileno(F), 1);
		_dup2(_fileno(F), 2);

		delete _prolog;

		fflush(stderr);
		fflush(stdout);
		fclose(F);

		_dup2(saved_out, 1);
		_dup2(saved_err, 2);

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
			goals[i] = (char *) malloc(1024);

		sprintf(goals[0], "change_directory('%s').", Dir);
		sprintf(goals[1], "(consult('%s')->true;rename_file('%s','_erroneous.pl')).", ConsultScript, ConsultScript);
		sprintf(goals[2], "asserta(global_id(%s)).", GID);
		sprintf(goals[3], "tell('%s').", OutFName);
		sprintf(goals[4], "%s.", MainGoal);
		sprintf(goals[5], "told.");
		sprintf(goals[6], "%s.", DoneGoal);
		sprintf(goals[7], "end_of_file.");

		F = fopen(gprolog_console_out, "at");
		saved_out = _dup(1);
		saved_err = _dup(2);
		_dup2(_fileno(F), 1);
		_dup2(_fileno(F), 2);

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

			renew.push_back("internal_goal");

			body.append("internal_goal:-");
			body.append(line);
			body.append("\n");
			bypass_spaces(body, p);
			while (p < body.length()) {
				_prolog->parse_clause(renew, f, body, p);
				bypass_spaces(body, p);
			}
			_prolog->bind();

			vector<value *> * args = new vector<value *>();
			generated_vars * variants = new generated_vars();
			variants->push_back(f);
			predicate_item_user * pi = new predicate_item_user(false, false, false, 0, NULL, _prolog, "internal_goal");
			pi->bind();
			bool ret = pi->processing(false, 0, variants, &args, f);

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
			std::cout << (ret ? "true" : "false") << endl;

			delete pi;
			delete f;
		}

		for (i = 0; i < 8; i++)
			free(goals[i]);

		fflush(stderr);
		fflush(stdout);
		fclose(F);

		_dup2(saved_out, 1);
		_dup2(saved_err, 2);

		return result;
	}
	/**/
	__declspec(dllexport) int __cdecl run_gprolog7(char * Dir, char * ConsultScript,
			char * OutFName, char * MainGoal, char * gprolog_console_out,
			char * DoneGoal, char * GID
		) {
		return process(Dir, ConsultScript, OutFName, MainGoal, gprolog_console_out, DoneGoal, GID);
	}
}
