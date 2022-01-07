#ifndef __SUN_H__
#define __SUN_H__

#preproc_passes(2)

#add_scan(topoSun)

#include <functional>
#include <iostream>
#include <list>
#include <stdio.h>

using namespace std;

#def_module() __sun_defs() {
@goal:-brackets_off.
@make_sun_def(ID, NP, BODY):-
  write('typedef struct { funnel(in, char) * recv; funnel(out, char) * send; } sun_link_'), write(ID), write(';'), nl,
  write('typedef std::function<sun_link_'), write(ID), write(' * (int Processor, int RequestId, int * Error)> sun_connector_'), write(ID), write(';'), nl,
  write('typedef std::function<RootData_t * (void)> sun_rooter_'), write(ID), write(';'), nl,
  write('typedef std::function<void(sun_rooter_'), write(ID), write(' GET_ROOT, sun_connector_'), write(ID), write(' ConnectLink)> sun_function_'), write(ID), write(';'), nl,
  write('chain sun_'), write(ID), write('(sun_function_'), write(ID), write(' worker) {'), nl,
  write('    list<sun_link_'), write(ID), write(' *> __Links;'), nl,
  write('    RootData_t RootData;'), nl,
  write('    RootProc_t RootProc;'), nl,
  write('    RootData.ProcRoot = &RootProc;'), nl,
  write('    RootProc.nProcs = throw_num_stages();'), nl,
  write('    RootProc.MyProcId = throw_stage();'), nl,
  write('    RootProc.DimX = throw_num_stages();'), nl,
  write('    RootProc.DimY = 1;'), nl,
  write('    RootProc.DimZ = 1;'), nl,
  write('    RootProc.MyX = throw_stage();'), nl,
  write('    RootProc.MyY = 0;'), nl,
  write('    RootProc.MyZ = 0;'), nl,
  write('    sun_rooter_'), write(ID), write(' GET_ROOT = [&] (void)->RootData_t * {'), nl,
  write('      return &RootData;'), nl,
  write('    };'), nl,
  write('    sun_connector_'), write(ID), write(' ConnectLink = [&] (int Processor, int RequestId, int * Error)->sun_link_'), write(ID), write(' * {'), nl,
  write('      char buf[120];'), nl,
  write('      sun_link_'), write(ID), write(' * L = new sun_link_'), write(ID), write(';'), nl,
  write('      if (Processor > throw_stage()) {'), nl,
  write('         sprintf(buf, "1+%i+%i+%i", RequestId, throw_stage(), Processor);'), nl,
  write('         L->recv = new funnel(in, char)(buf);'), nl,
  write('         sprintf(buf, "2+%i+%i+%i", RequestId, throw_stage(), Processor);'), nl,
  write('         L->send = new funnel(out, char)(buf);'), nl,
  write('      } else {'), nl,
  write('         sprintf(buf, "1+%i+%i+%i", RequestId, Processor, throw_stage());'), nl,
  write('         L->send = new funnel(out, char)(buf);'), nl,
  write('         sprintf(buf, "2+%i+%i+%i", RequestId, Processor, throw_stage());'), nl,
  write('         L->recv = new funnel(in, char)(buf);'), nl,
  write('      }'), nl,
  write('      __Links.push_back(L);'), nl,
  write('      *Error = 0;'), nl,
  write('      return L;'), nl,
  write('    };'), nl,
  write('    worker(GET_ROOT, ConnectLink);'), nl,
  write('    for (auto L : __Links) {'), nl,
  write('        delete L->recv;'), nl,
  write('        delete L->send;'), nl,
  write('        delete L;'), nl,
  write('    }'), nl,
  write('}'), nl.
@insert_sun_defs:-
  sun_def(ID, NP, BODY),
  make_sun_def(ID, NP, BODY),
  fail.
@insert_sun_defs:-!.
@goal:-
  write('typedef unsigned char byte;'), nl,
  write('#define MyProcID MyProcId'), nl,
  write('typedef struct ProcInfo_s {'), nl,
  write('        int     nProcs;   /* Число виртуальных процессоров */'), nl,
  write('        int     MyProcId; /* Идентификатор собственного процессора */'), nl,
  write('        int     DimX;     /* Размер процессорной кладки */'), nl,
  write('        int     DimY;'), nl,
  write('        int     DimZ;'), nl,
  write('        int     MyX;      /* Позиция в процессорной кладке */'), nl,
  write('        int     MyY;'), nl,
  write('        int     MyZ;'), nl,
  write('} ProcInfo_t;'), nl,
  write('#define RootProc_t ProcInfo_t'), nl,
  write('typedef struct RootData_s {'), nl,
  write('    RootProc_t * ProcRoot;'), nl,
  write('    int        * DummyRoot;'), nl,
  write('} RootData_t;'), nl,
  insert_sun_defs.
};

__sun_defs()

#def_pattern topoSun => __make_sun (gid(), /root/NP/@Value, /root/BODY/@Value) {
  (((^)|(\;)+|\}|\{|\)|\\n|(\\n|\\t|\b)else\b|(\\n|\\t|\b)do\b|\:)((\s|\\t)*\\n)*)(\s|\\t)*
  @begin
    sun
    (\s|\\t)*
    \(
    (\s|\\t)*
    (\w+)->{NP}
    (\s|\\t)*
    \)
    (\s|\\t)*
    \{
     ((.{1,8192})->{BODY}\})?=>{Predicates.BAL($,'}')}
    (\s|\\t)*
  @end
};

#def_module() __make_sun(ID, NP, BODY) {
@goal:-brackets_off.
@goal:-assertz(sun_def(ID, NP, BODY)).
@make_sun_body:-
    write('sun_function_'), write(ID), write(' worker_'), write(ID), write(' = [&] (sun_rooter_'), write(ID), write(' GET_ROOT, sun_connector_'), write(ID), write(' ConnectLink) {'), nl,
    write('typedef sun_link_'), write(ID), write(' LinkCB_t;'), nl,
    write('typedef sun_link_'), write(ID), write(' * Option_t;'), nl,
    write('auto SendLink = [&] (sun_link_'), write(ID), write(' * Link, byte * data, long Size) {'), nl,
    write('  Link->send->put(data, Size);'), nl,
    write('  while (!Link->send->empty()) _Yield();'), nl,
    write('};'), nl,
    write('auto RecvLink = [&] (sun_link_'), write(ID), write(' * Link, byte * data, long Size) {'), nl,
    write('  Link->recv->get(data, Size);'), nl,
    write('};'), nl,
    write('auto ReceiveOption = [&] (LinkCB_t * L)->Option_t { return L; };'), nl,
    write('auto SelectList = [&] (int n, Option_t * Options)->int {'), nl,
    write('  while(1) {'), nl,
    write('    for (int i = 0; i < n; i++)'), nl,
    write('        if (!Options[i]->recv->empty()) return i;'), nl,
    write('  }'), nl,
    write('};'), nl,
    write(BODY), nl,
    write('};'), nl.
@make_sun_call:-
    write('plan_parallel_chain(1, '), write(NP), write(', sun_'), write(ID), write('(worker_'), write(ID), write('));'), nl.
@goal:-make_sun_body, make_sun_call, !.
};

#endif
