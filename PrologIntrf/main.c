#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "gprolog.h"
#include "fd_to_c.h"

static unsigned long _ebp;

static FILE * F = NULL;
static int saved_out;
static int saved_err;

__declspec(dllexport) int __cdecl init_gprolog7(char * gprolog_console_out) {
	static int argc = 1;
	static char * argv[] = { ".\\Automodeling.exe" };

	F = fopen(gprolog_console_out, "wt");
	saved_out = _dup(1);
	saved_err = _dup(2);
	_dup2(_fileno(F), 1);
	_dup2(_fileno(F), 2);

	_asm{
		mov _ebp, ebp
	}
	printf("Number of directives loaded : %d\n", Start_Prolog(argc, argv));

	_asm{
		xchg _ebp, ebp
	}

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

	_asm{
		xchg _ebp, ebp
	}
	Stop_Prolog();

	_asm{
		xchg _ebp, ebp
	}

	fflush(stderr);
	fflush(stdout);
	fclose(F);

	_dup2(saved_out, 1);
	_dup2(saved_err, 2);

	return 0;
}

/*
static int process(char * Dir, char * ConsultScript,
	char * OutFName, char * MainGoal, char * gprolog_console_out,
	char * DoneGoal, char * GID) {
	static PlTerm arg[10];
	static PlTerm _arg[10];

	static volatile char * _Dir;
	static volatile char * _ConsultScript;
	static volatile char * _OutFName;
	static volatile char * _MainGoal;
	static volatile char * _gprolog_console_out;
	static volatile char * _DoneGoal;
	static volatile char * _GID;

	static FILE * F = NULL;
	static int result;

	static int argc = 1;
	static char * argv[] = { ".\\Automodeling.exe" };

	result = 0;

	_Dir = Dir;
	_ConsultScript = ConsultScript;
	_OutFName = OutFName;
	_MainGoal = MainGoal;
	_gprolog_console_out = gprolog_console_out;
	_DoneGoal = DoneGoal;
	_GID = GID;

	F = fopen(gprolog_console_out, "wt");
	_dup2(_fileno(F), 1);
	_dup2(_fileno(F), 2);

	printf("Number of directives loaded : %d\n", Start_Prolog(argc, argv));

	arg[0] = Mk_String(_Dir);
	Pl_Query_Begin(PL_FALSE);

	result += Pl_Query_Call(Find_Atom("change_directory"), 1, arg);

	Pl_Query_End(PL_CUT);

	Pl_Query_Begin(PL_FALSE);

	arg[0] = Mk_String(_ConsultScript);

	result += 4 * Pl_Query_Call(Find_Atom("consult"), 1, arg);

	Pl_Query_End(PL_CUT);

	Pl_Query_Begin(PL_FALSE);

	_arg[0] = Mk_Integer(atoi(_GID));
	arg[0] = Mk_Callable(Mk_String("global_id"), 1, _arg);

	result += 16 * Pl_Query_Call(Find_Atom("asserta"), 1, arg);

	Pl_Query_End(PL_CUT);

	Pl_Query_Begin(PL_FALSE);

	arg[0] = Mk_String(_OutFName);

	result += 64 * Pl_Query_Call(Find_Atom("tell"), 1, arg);
	Pl_Query_End(PL_CUT);

	Pl_Query_Begin(PL_FALSE);

	result += 256 * Pl_Query_Call(Find_Atom(_MainGoal), 0, arg);
	
	Pl_Query_End(PL_KEEP_FOR_PROLOG);

	Pl_Query_Begin(PL_FALSE);

	result += 1024 * Pl_Query_Call(Find_Atom("told"), 0, arg);
	Pl_Query_End(PL_KEEP_FOR_PROLOG);

	Pl_Query_Begin(PL_FALSE);

	result += 4096 * Pl_Query_Call(Find_Atom(_DoneGoal), 0, arg);
	Pl_Query_End(PL_CUT);

	Stop_Prolog();

	fflush(stdout);
	fclose(F);

	return result;
}
*/
/**/
static int process(char * Dir, char * ConsultScript,
	char * OutFName, char * MainGoal, char * gprolog_console_out,
	char * DoneGoal, char * GID) {
	static int result;

	static char * goals[8];
	static PlTerm terms[8];
	static PlTerm args[10];
	static int i;

	result = 0;

	for (i = 0; i < 8; i++)
		goals[i] = (char *) malloc(1024);

	sprintf(goals[0], "change_directory('%s')", Dir);
	sprintf(goals[1], "(consult('%s')->true;rename_file('%s','_erroneous.pl'))", ConsultScript, ConsultScript);
	sprintf(goals[2], "asserta(global_id(%s))", GID);
	sprintf(goals[3], "tell('%s')", OutFName);
	sprintf(goals[4], "%s", MainGoal);
	sprintf(goals[5], "told");
	sprintf(goals[6], "%s", DoneGoal);
	sprintf(goals[7], "end_of_file");

	F = fopen(gprolog_console_out, "at");
	saved_out = _dup(1);
	saved_err = _dup(2);
	_dup2(_fileno(F), 1);
	_dup2(_fileno(F), 2);

	_asm {
		xchg _ebp, ebp
	}

	for (i = 0; i < 8; i++)
		terms[i] = Pl_Mk_String(goals[i]);

	args[0] = Tag_ATM(Pl_Create_Atom("$cmd_line_query_goal"));
	args[1] = Pl_Mk_Proper_List(8, terms);

	Pl_Query_Begin(PL_TRUE);

	result += 4 * Pl_Query_Call(Find_Atom("g_assign"), 2, args);

	Pl_Query_End(PL_KEEP_FOR_PROLOG);

	Reset_Prolog();

	result += Try_Execute_Top_Level();

	_asm {
		xchg _ebp, ebp
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
