Unit Consts;

Interface

{$IFDEF FPC}
{$MODE ObjFPC}
{$ENDIF}
{$H+}

Uses Lexique;

Const idReenterable          = 'REENTERABLE';
      idStatic               = 'STATIC';
      idLocal                = 'LOCAL';
      idGlobal               = 'GLOBAL';
      idContinue             = 'CONTINUE';
      idPragma               = 'PRAGMA';
      idDefine               = 'DEFINE';
      idUndef                = 'UNDEF';
      idInclude              = 'INCLUDE';
      idIf                   = 'IF';
      idIfdef                = 'IFDEF';
      idIfndef               = 'IFNDEF';
      idElse                 = 'ELSE';
      idElif                 = 'ELIF';
      idEndif                = 'ENDIF';
      iddef_module           = 'DEF_MODULE';
      idTypedef              = 'TYPEDEF';
      idStruct               = 'STRUCT';
      idUnion                = 'UNION';
      idMarkupdef            = 'MARKUPDEF';
      idOmp                  = 'OMP';
      idParallel             = 'PARALLEL';
      idPlan                 = 'PLAN';
      idFirst                = 'FIRST';
      idLast                 = 'LAST';
      idParallelize          = 'PARALLELIZE';
      idplan_first           = 'PLAN_FIRST';
      idplan_last            = 'PLAN_LAST';
      idthrow_first          = 'THROW_FIRST';
      idthrow_last           = 'THROW_LAST';
      idplan_chain           = 'PLAN_CHAIN';
      idclustered            = 'CLUSTERED';
      idvectorized           = 'VECTORIZED';
      idtypized              = 'TYPIZED';
      idgpu                  = 'GPU';
      idcommon               = 'COMMON';
      idbegin                = 'BEGIN';
      idend                  = 'END';
      id_local               = '_LOCAL';
      id_global              = '_GLOBAL';
      idplan_parallel_chain  = 'PLAN_PARALLEL_CHAIN';
      idplan_parallel_reverse= 'PLAN_PARALLEL_REVERSE';
      idplan_registered_barrier = 'PLAN_REGISTERED_BARRIER';
      idplan_register        = 'PLAN_REGISTER';
      idplan_critical        = 'PLAN_CRITICAL';
      idplan_group_atomize   = 'PLAN_GROUP_ATOMIZE';
      idplan_group_vectorize = 'PLAN_GROUP_VECTORIZE';
      idplan_group_typize    = 'PLAN_GROUP_TYPIZE';
      idChain                = 'CHAIN';
      idThrow                = 'THROW';
      idReduction            = 'REDUCTION';
      idConst                = 'CONST';
      idID                   = 'ID';
      idSet                  = 'SET';
      idReset                = 'RESET';
      idDepends              = 'DEPENDS';
      idPre_id               = 'PRE_ID';
      idState                = 'STATE';
      idInput_Proc           = 'INPUT_PROC';
      idplan_topology        = 'PLAN_TOPOLOGY';
      idgoal                 = 'GOAL';
      idnull                 = 'NULL';

      getTaskID              = Pound;

Const Plans: Array[1..4] Of PChar = (idplan_first, idplan_last, idthrow_first, idthrow_last);

Const CRLF = #$0D#$0A;

Implementation

End.