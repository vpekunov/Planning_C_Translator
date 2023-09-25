Unit Macros;

Interface

{$IFDEF FPC}
{$MODE ObjFPC}
{$ENDIF}
{$H+}

Uses SysUtils, Classes, Common, Consts;

Procedure WritePlanMacros(Var _Out:TStringList; Const ID, ParamNames:String; LocGlob, Names: TStringList; Const Ldecl: String);
Procedure WriteAtomicMacros(Var _Out:TStringList; ParamNames:String; ThrParamNames:String);
Procedure WriteThrowMacros(Var _Out:TStringList; Const ID,ParamNames:String);

Implementation

Procedure WritePlanMacros(Var _Out:TStringList; Const ID, ParamNames:String; LocGlob, Names: TStringList; Const Ldecl: String);

Var SI, OI, MI, IG, NP: String;
    Fun: String;
    nLocs: Integer;
    F: Integer;
Begin
  _Out.Add('#undef _plan_first');
  _Out.Add('#undef _plan_last');
  _Out.Add('#undef plan_empty');
  _Out.Add('#undef m_clear_plan');
  _Out.Add('#undef m_plan_group_first');
  _Out.Add('#undef m_plan_group_last');
  _Out.Add('#undef m_plan_group_parallelize');
  _Out.Add('#undef m_plan_group_atomize');
  _Out.Add('#undef m_plan_group_soft_atomize');
  _Out.Add('#undef m_plan_group_vectorize');
  _Out.Add('#undef m_plan_stop');
  _Out.Add('#undef plan_after_continue');
  _Out.Add('#undef plan_register');
  _Out.Add('#ifdef _OPENMP');
  _Out.Add('#define plan_register(GroupID) __plan_register('+ID+',GroupID)');
  _Out.Add('#define m_plan_group_parallelize \');
  _Out.Add('   do { \');
  _Out.Add('     int __switched = 0; \');
  _Out.Add('     __plan_locking__; \');
  _Out.Add('     if (!*__parallel_flag__) { \');
  _Out.Add('        (*__parallel_flag__) = 1; \');
  _Out.Add('        __switched = 1; \');
  _Out.Add('     } \');
  _Out.Add('     __plan_unlocking__; \');
  _Out.Add('     if (__switched && __start_lock__) omp_unset_lock(__start_lock__); \');
  _Out.Add('   } while(0)');
  _Out.Add('#define m_plan_group_atomize \');
  _Out.Add('   do { \');
  _Out.Add('     int __switched = 0; \');
  _Out.Add('     __plan_locking__; \');
  _Out.Add('     if (!*__parallel_flag__ && __parallel_atomic__) { \');
  _Out.Add('        (*__parallel_flag__) = __parallel_atomic__; \');
  _Out.Add('        __switched = 1; \');
  _Out.Add('     } \');
  _Out.Add('     __plan_unlocking__; \');
  _Out.Add('     if (__switched && __start_lock__) omp_unset_lock(__start_lock__); \');
  _Out.Add('   } while(0)');
  _Out.Add('#define m_plan_group_soft_atomize \');
  _Out.Add('   do { \');
  _Out.Add('     __plan_locking__; \');
  _Out.Add('     __plan_unlocking__; \');
  _Out.Add('   } while(0)');
  _Out.Add('#define m_plan_stop __plan_stop(__NOT_THROWING__)');
  _Out.Add('#define plan_after_continue() __AFTER_CONTINUE(__NOT_THROWING__,__continue_lock__,__continue_plan__)');
  _Out.Add('#else');
  _Out.Add('#define plan_register(GroupID) while(0)');
  _Out.Add('#define m_plan_group_parallelize \');
  _Out.Add('   while(0)');
  _Out.Add('#define m_plan_group_atomize \');
  _Out.Add('   while(0)');
  _Out.Add('#define m_plan_group_soft_atomize \');
  _Out.Add('   while(0)');
  _Out.Add('#define m_plan_stop *__continue_plan__ = 0');
  _Out.Add('#define plan_after_continue() (*__continue_plan__ == 2)');
  _Out.Add('#endif');
  _Out.Add('#define m_plan_group_first \');
  _Out.Add('   __plan_group_'+ID+'__(front)');
  _Out.Add('#define m_plan_group_last \');
  _Out.Add('   __plan_group_'+ID+'__(back)');
  _Out.Add('#define _plan_first('+ParamNames+'__mask__) \');
  _Out.Add('   __plan_'+ID+'__(front,'+ParamNames+'__mask__)');
  _Out.Add('#define _plan_last('+ParamNames+'__mask__) \');
  _Out.Add('   __plan_'+ID+'__(back,'+ParamNames+'__mask__)');
  _Out.Add('#define plan_empty \');
  _Out.Add('   (_plan_empty())');
  _Out.Add('#define m_clear_plan do { \');
  _Out.Add('   __plan_locking__; \');
  _Out.Add('   __event_list__->clear(); \');
  _Out.Add('   __plan_unlocking__; \');
  _Out.Add('   } while(0)');
  _Out.Add('#ifdef __REENT_GPU__');
  _Out.Add('#define m_plan_group_vectorize(S) \');
  _Out.Add('   do { \');
  _Out.Add('      __plan_locking__; \');
  _Out.Add('      __device & d = __open_device(S); \');
  _Out.Add('      _params_'+ID+' __planned__; \');
  _Out.Add('      const int n_args = '+IntToStr(LocGlob.Count)+'; \');
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
  _Out.Add('const int n_locs = '+IntToStr(nLocs)+'; \');
  _Out.Add('    auto loc_items = [&] (int arg)->int { \');
  _Out.Add('      switch (arg) { \');
  _Out.Add(Fun); _Out.Add(strGlue);
  _Out.Add('        default: return 0; \');
  _Out.Add('      } \');
  _Out.Add('    }; \');
  _Out.Add(SI + 'sizeof(int)}; \');
  _Out.Add(OI + '0}; \');
  _Out.Add(MI + 'CL_MEM_READ_ONLY}; \');
  _Out.Add(IG + '0}; \');
  _Out.Add(NP + '0}; \');
  _Out.Add('int n_items[n_args+1] = {0}; \');
  _Out.Add('      '+Ldecl+'<_params_'+ID+'>::iterator it; \');
  _Out.Add('      cl_kernel kernel = __compile_on_device(d, __gpu_common, gpu_'+ID+', "gpu_'+ID+'"); \');
  _Out.Add('      __run_opencl_kernel__; \');
  _Out.Add('      __plan_unlocking__; \');
  _Out.Add('   } while(0)');
  _Out.Add('#else');
  _Out.Add('#define m_plan_group_vectorize(S) m_plan_group_parallelize');
  _Out.Add('#endif');
End;

Procedure WriteAtomicMacros(Var _Out:TStringList; ParamNames:String; ThrParamNames:String);
Begin
  _Out.Add('#undef _plan_first');
  _Out.Add('#undef _plan_last');
  _Out.Add('#undef plan_empty');
  _Out.Add('#undef m_clear_plan');
  _Out.Add('#undef m_plan_group_first');
  _Out.Add('#undef m_plan_group_last');
  _Out.Add('#undef m_plan_group_parallelize');
  _Out.Add('#undef m_plan_group_atomize');
  _Out.Add('#undef m_plan_group_soft_atomize');
  _Out.Add('#undef m_plan_group_vectorize');
  _Out.Add('#undef m_plan_stop');
  _Out.Add('#undef plan_after_continue');
  _Out.Add('#undef throw_first');
  _Out.Add('#undef throw_last');
  _Out.Add('#undef throw_stage');
  _Out.Add('#undef throw_num_stages');
  _Out.Add('#undef plan_linear_num');
  _Out.Add('#undef plan_topology_num');
  _Out.Add('#undef plan_topology_quit');
  _Out.Add('#undef plan_register');
  _Out.Add('#define plan_register(GroupID) while(0)');
  _Out.Add('#define m_plan_group_parallelize \');
  _Out.Add('   while(0)');
  _Out.Add('#define m_plan_group_atomize \');
  _Out.Add('   while(0)');
  _Out.Add('#define m_plan_group_soft_atomize \');
  _Out.Add('   while(0)');
  _Out.Add('#define m_plan_group_vectorize(S) \');
  _Out.Add('   while(0)');
  _Out.Add('#define m_plan_group_first \');
  _Out.Add('   while(0)');
  _Out.Add('#define m_plan_group_last \');
  _Out.Add('   while(0)');
  If (Length(ParamNames) > 0) And (ParamNames[Length(ParamNames)] = ',') Then
     Delete(ParamNames, Length(ParamNames), 1);
  _Out.Add('#define _plan_first('+ParamNames+') \');
  _Out.Add('   while(0)');
  _Out.Add('#define _plan_last('+ParamNames+') \');
  _Out.Add('   while(0)');
  _Out.Add('#define plan_empty \');
  _Out.Add('   (1)');
  _Out.Add('#define m_clear_plan \');
  _Out.Add('   while(0)');
  _Out.Add('#define m_plan_stop \');
  _Out.Add('   while(0)');
  _Out.Add('#define plan_after_continue() \');
  _Out.Add('   (1)');
  If (Length(ThrParamNames) > 0) And (ThrParamNames[Length(ThrParamNames)] = ',') Then
     Delete(ThrParamNames, Length(ThrParamNames), 1);
  _Out.Add('#define throw_first('+ThrParamNames+') \');
  _Out.Add('   while(0)');
  _Out.Add('#define throw_last('+ThrParamNames+') \');
  _Out.Add('   while(0)');
  _Out.Add('#define throw_stage() \');
  _Out.Add('   (-1)');
  _Out.Add('#define throw_num_stages() \');
  _Out.Add('   (-1)');
  _Out.Add('#define plan_linear_num() \');
  _Out.Add('   (-1)');
  _Out.Add('#define plan_topology_num() \');
  _Out.Add('   (-1)');
  _Out.Add('#define plan_topology_quit() \');
  _Out.Add('   while(0)')
End;

Procedure WriteThrowMacros(Var _Out:TStringList; Const ID,ParamNames:String);
Begin
  _Out.Add('#undef throw_first');
  _Out.Add('#undef throw_last');
  _Out.Add('#undef throw_stage');
  _Out.Add('#undef throw_num_stages');
  _Out.Add('#undef plan_linear_num');
  _Out.Add('#undef plan_topology_num');
  _Out.Add('#undef plan_topology_quit');
  _Out.Add('#define throw_first('+ParamNames+'__mask__) \');
  _Out.Add('   __throw_'+ID+'__(front,'+ParamNames+'__mask__)');
  _Out.Add('#define throw_last('+ParamNames+'__mask__) \');
  _Out.Add('   __throw_'+ID+'__(back,'+ParamNames+'__mask__)');
  _Out.Add('#define throw_stage() \');
  _Out.Add('   __throw_stage__');
  _Out.Add('#define throw_num_stages() _throw_num_stages()');
  _Out.Add('#define plan_linear_num() __plan_linear_num()');
  _Out.Add('#define plan_topology_num() __plan_topology_num()');
  _Out.Add('#define plan_topology_quit() __plan_topology_quit()')
End;

End.
