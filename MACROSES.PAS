Unit Macroses;

Interface

{$IFDEF FPC}
{$MODE ObjFPC}
{$ENDIF}
{$H+}

Uses SysUtils, Classes, Common, Consts;

Procedure WritePlanMacroses(Var Out:TextFile; Const ID, ParamNames:String; LocGlob, Names: TStringList; Const Ldecl: String);
Procedure WriteAtomicMacroses(Var Out:TextFile; ParamNames:String; ThrParamNames:String);
Procedure WriteThrowMacroses(Var Out:TextFile; Const ID,ParamNames:String);

Implementation

Procedure WritePlanMacroses(Var Out:TextFile; Const ID, ParamNames:String; LocGlob, Names: TStringList; Const Ldecl: String);

Var SI, OI, MI, IG, NP: String;
    Fun: String;
    nLocs: Integer;
    F: Integer;
Begin
  WriteLn(Out,'#undef _plan_first');
  WriteLn(Out,'#undef _plan_last');
  WriteLn(Out,'#undef plan_empty');
  WriteLn(Out,'#undef m_clear_plan');
  WriteLn(Out,'#undef m_plan_group_first');
  WriteLn(Out,'#undef m_plan_group_last');
  WriteLn(Out,'#undef m_plan_group_parallelize');
  WriteLn(Out,'#undef m_plan_group_atomize');
  WriteLn(Out,'#undef m_plan_group_soft_atomize');
  WriteLn(Out,'#undef m_plan_group_vectorize');
  WriteLn(Out,'#undef m_plan_stop');
  WriteLn(Out,'#undef plan_after_continue');
  WriteLn(Out,'#undef plan_register');
  WriteLn(Out,'#ifdef _OPENMP');
  WriteLn(Out,'#define plan_register(GroupID) __plan_register('+ID+',GroupID)');
  WriteLn(Out,'#define m_plan_group_parallelize \');
  WriteLn(Out,'   do { \');
  WriteLn(Out,'     int __switched = 0; \');
  WriteLn(Out,'     __plan_locking__; \');
  WriteLn(Out,'     if (!*__parallel_flag__) { \');
  WriteLn(Out,'        (*__parallel_flag__) = 1; \');
  WriteLn(Out,'        __switched = 1; \');
  WriteLn(Out,'     } \');
  WriteLn(Out,'     __plan_unlocking__; \');
  WriteLn(Out,'     if (__switched && __start_lock__) omp_unset_lock(__start_lock__); \');
  WriteLn(Out,'   } while(0)');
  WriteLn(Out,'#define m_plan_group_atomize \');
  WriteLn(Out,'   do { \');
  WriteLn(Out,'     int __switched = 0; \');
  WriteLn(Out,'     __plan_locking__; \');
  WriteLn(Out,'     if (!*__parallel_flag__ && __parallel_atomic__) { \');
  WriteLn(Out,'        (*__parallel_flag__) = __parallel_atomic__; \');
  WriteLn(Out,'        __switched = 1; \');
  WriteLn(Out,'     } \');
  WriteLn(Out,'     __plan_unlocking__; \');
  WriteLn(Out,'     if (__switched && __start_lock__) omp_unset_lock(__start_lock__); \');
  WriteLn(Out,'   } while(0)');
  WriteLn(Out,'#define m_plan_group_soft_atomize \');
  WriteLn(Out,'   do { \');
  WriteLn(Out,'     __plan_locking__; \');
  WriteLn(Out,'     __plan_unlocking__; \');
  WriteLn(Out,'   } while(0)');
  WriteLn(Out,'#define m_plan_stop __plan_stop(__NOT_THROWING__)');
  WriteLn(Out,'#define plan_after_continue() __AFTER_CONTINUE(__NOT_THROWING__,__continue_lock__,__continue_plan__)');
  WriteLn(Out,'#else');
  WriteLn(Out,'#define plan_register(GroupID) while(0)');
  WriteLn(Out,'#define m_plan_group_parallelize \');
  WriteLn(Out,'   while(0)');
  WriteLn(Out,'#define m_plan_group_atomize \');
  WriteLn(Out,'   while(0)');
  WriteLn(Out,'#define m_plan_group_soft_atomize \');
  WriteLn(Out,'   while(0)');
  WriteLn(Out,'#define m_plan_stop *__continue_plan__ = 0');
  WriteLn(Out,'#define plan_after_continue() (*__continue_plan__ == 2)');
  WriteLn(Out,'#endif');
  WriteLn(Out,'#define m_plan_group_first \');
  WriteLn(Out,'   __plan_group_'+ID+'__(front)');
  WriteLn(Out,'#define m_plan_group_last \');
  WriteLn(Out,'   __plan_group_'+ID+'__(back)');
  WriteLn(Out,'#define _plan_first('+ParamNames+'__mask__) \');
  WriteLn(Out,'   __plan_'+ID+'__(front,'+ParamNames+'__mask__)');
  WriteLn(Out,'#define _plan_last('+ParamNames+'__mask__) \');
  WriteLn(Out,'   __plan_'+ID+'__(back,'+ParamNames+'__mask__)');
  WriteLn(Out,'#define plan_empty \');
  WriteLn(Out,'   (_plan_empty())');
  WriteLn(Out,'#define m_clear_plan do { \');
  WriteLn(Out,'   __plan_locking__; \');
  WriteLn(Out,'   __event_list__->clear(); \');
  WriteLn(Out,'   __plan_unlocking__; \');
  WriteLn(Out,'   } while(0)');
  WriteLn(Out,'#ifdef __REENT_GPU__');
  WriteLn(Out,'#define m_plan_group_vectorize(S) \');
  WriteLn(Out,'   do { \');
  WriteLn(Out,'      __plan_locking__; \');
  WriteLn(Out,'      __device & d = __open_device(S); \');
  WriteLn(Out,'      _params_'+ID+' __planned__; \');
  WriteLn(Out,'      const int n_args = '+IntToStr(LocGlob.Count)+'; \');
  SI := '    int size_items[n_args+1] = {';
  OI := '    int offs_items[n_args+1] = {';
  MI := '    int mode_items[n_args+1] = {';
  IG := '    bool is_global[n_args+1] = {';
  NP := '    long long n_pointer[n_args+1] = {';
  nLocs := 0;
  Fun := '';
  For F := 0 To LocGlob.Count - 1 Do
    Begin
      If (Length(LocGlob.Strings[F]) > 0) Then
         SI := SI + 'sizeof(*__planned__.' + Names.Strings[F] +')'
      Else
         SI := SI + 'sizeof(__planned__.' + Names.Strings[F] +')';
      OI := OI + '(char *)&__planned__.' + Names.Strings[F] + '-(char *)&__planned__';
      If (Length(LocGlob.Strings[F]) > 0) Then
         Begin
           MI := MI + 'CL_MEM_READ_WRITE';
           Fun := Fun + '  case ' + IntToStr(F) + ': return ' + LocGlob.Strings[F] + '; \' + CRLF;
           If Not Boolean(TObjectToInteger(LocGlob.Objects[F])) Then
              Begin
                Inc(nLocs)
              End
         End
      Else
         MI := MI + 'CL_MEM_READ_ONLY';
      If Boolean(TObjectToInteger(LocGlob.Objects[F])) Then
         IG := IG + 'true'
      Else
         IG := IG + 'false';
      If Length(LocGlob.Strings[F]) > 0 Then
         If Boolean(TObjectToInteger(LocGlob.Objects[F])) Then
            NP := NP + '0' // LocGlob.Strings[F]
         Else
            NP := NP + '1'
      Else
         NP := NP + '0';
      SI := SI + ',';
      OI := OI + ',';
      MI := MI + ',';
      IG := IG + ',';
      NP := NP + ','
    End;
  WriteLn(Out,'const int n_locs = '+IntToStr(nLocs)+'; \');
  WriteLn(Out,'    auto loc_items = [&] (int arg)->int { \');
  WriteLn(Out,'      switch (arg) { \');
  Write(Out,Fun);
  WriteLn(Out,'        default: return 0; \');
  WriteLn(Out,'      } \');
  WriteLn(Out,'    }; \');
  WriteLn(Out,SI,'sizeof(int)}; \');
  WriteLn(Out,OI,'0}; \');
  WriteLn(Out,MI,'CL_MEM_READ_ONLY}; \');
  WriteLn(Out,IG,'0}; \');
  WriteLn(Out,NP,'0}; \');
  WriteLn(Out,'int n_items[n_args+1] = {0}; \');
  WriteLn(Out,'      '+Ldecl+'<_params_'+ID+'>::iterator it; \');
  WriteLn(Out,'      cl_kernel kernel = __compile_on_device(d, __gpu_common, gpu_'+ID+', "gpu_'+ID+'"); \');
  WriteLn(Out,'      __run_opencl_kernel__; \');
  WriteLn(Out,'      __plan_unlocking__; \');
  WriteLn(Out,'   } while(0)');
  WriteLn(Out,'#else');
  WriteLn(Out,'#define m_plan_group_vectorize(S) m_plan_group_parallelize');
  WriteLn(Out,'#endif');
End;

Procedure WriteAtomicMacroses(Var Out:TextFile; ParamNames:String; ThrParamNames:String);
Begin
  WriteLn(Out,'#undef _plan_first');
  WriteLn(Out,'#undef _plan_last');
  WriteLn(Out,'#undef plan_empty');
  WriteLn(Out,'#undef m_clear_plan');
  WriteLn(Out,'#undef m_plan_group_first');
  WriteLn(Out,'#undef m_plan_group_last');
  WriteLn(Out,'#undef m_plan_group_parallelize');
  WriteLn(Out,'#undef m_plan_group_atomize');
  WriteLn(Out,'#undef m_plan_group_soft_atomize');
  WriteLn(Out,'#undef m_plan_group_vectorize');
  WriteLn(Out,'#undef m_plan_stop');
  WriteLn(Out,'#undef plan_after_continue');
  WriteLn(Out,'#undef throw_first');
  WriteLn(Out,'#undef throw_last');
  WriteLn(Out,'#undef throw_stage');
  WriteLn(Out,'#undef throw_num_stages');
  WriteLn(Out,'#undef plan_linear_num');
  WriteLn(Out,'#undef plan_topology_num');
  WriteLn(Out,'#undef plan_topology_quit');
  WriteLn(Out,'#undef plan_register');
  WriteLn(Out,'#define plan_register(GroupID) while(0)');
  WriteLn(Out,'#define m_plan_group_parallelize \');
  WriteLn(Out,'   while(0)');
  WriteLn(Out,'#define m_plan_group_atomize \');
  WriteLn(Out,'   while(0)');
  WriteLn(Out,'#define m_plan_group_soft_atomize \');
  WriteLn(Out,'   while(0)');
  WriteLn(Out,'#define m_plan_group_vectorize(S) \');
  WriteLn(Out,'   while(0)');
  WriteLn(Out,'#define m_plan_group_first \');
  WriteLn(Out,'   while(0)');
  WriteLn(Out,'#define m_plan_group_last \');
  WriteLn(Out,'   while(0)');
  If (Length(ParamNames) > 0) And (ParamNames[Length(ParamNames)] = ',') Then
     Delete(ParamNames, Length(ParamNames), 1);
  WriteLn(Out,'#define _plan_first('+ParamNames+') \');
  WriteLn(Out,'   while(0)');
  WriteLn(Out,'#define _plan_last('+ParamNames+') \');
  WriteLn(Out,'   while(0)');
  WriteLn(Out,'#define plan_empty \');
  WriteLn(Out,'   (1)');
  WriteLn(Out,'#define m_clear_plan \');
  WriteLn(Out,'   while(0)');
  WriteLn(Out,'#define m_plan_stop \');
  WriteLn(Out,'   while(0)');
  WriteLn(Out,'#define plan_after_continue() \');
  WriteLn(Out,'   (1)');
  If (Length(ThrParamNames) > 0) And (ThrParamNames[Length(ThrParamNames)] = ',') Then
     Delete(ThrParamNames, Length(ThrParamNames), 1);
  WriteLn(Out,'#define throw_first('+ThrParamNames+') \');
  WriteLn(Out,'   while(0)');
  WriteLn(Out,'#define throw_last('+ThrParamNames+') \');
  WriteLn(Out,'   while(0)');
  WriteLn(Out,'#define throw_stage() \');
  WriteLn(Out,'   (-1)');
  WriteLn(Out,'#define throw_num_stages() \');
  WriteLn(Out,'   (-1)');
  WriteLn(Out,'#define plan_linear_num() \');
  WriteLn(Out,'   (-1)');
  WriteLn(Out,'#define plan_topology_num() \');
  WriteLn(Out,'   (-1)');
  WriteLn(Out,'#define plan_topology_quit() \');
  WriteLn(Out,'   while(0)')
End;

Procedure WriteThrowMacroses(Var Out:TextFile; Const ID,ParamNames:String);
Begin
  WriteLn(Out,'#undef throw_first');
  WriteLn(Out,'#undef throw_last');
  WriteLn(Out,'#undef throw_stage');
  WriteLn(Out,'#undef throw_num_stages');
  WriteLn(Out,'#undef plan_linear_num');
  WriteLn(Out,'#undef plan_topology_num');
  WriteLn(Out,'#undef plan_topology_quit');
  WriteLn(Out,'#define throw_first('+ParamNames+'__mask__) \');
  WriteLn(Out,'   __throw_'+ID+'__(front,'+ParamNames+'__mask__)');
  WriteLn(Out,'#define throw_last('+ParamNames+'__mask__) \');
  WriteLn(Out,'   __throw_'+ID+'__(back,'+ParamNames+'__mask__)');
  WriteLn(Out,'#define throw_stage() \');
  WriteLn(Out,'   __throw_stage__');
  WriteLn(Out,'#define throw_num_stages() _throw_num_stages()');
  WriteLn(Out,'#define plan_linear_num() __plan_linear_num()');
  WriteLn(Out,'#define plan_topology_num() __plan_topology_num()');
  WriteLn(Out,'#define plan_topology_quit() __plan_topology_quit()')
End;

End.
