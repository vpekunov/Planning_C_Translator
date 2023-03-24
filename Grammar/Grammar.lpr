library Grammar;

{$mode delphi}{$H+}

{$IF DEFINED(UNIX) OR DEFINED(LINUX)}
{$linklib c}
//{$linklib stdc++}
{$ENDIF}

Uses (* LazUTF8, *) dynlibs, StrUtils, SysUtils, Classes;

Var Grammer: TLibHandle;
    GOpts: Pointer;

Var enDict: Pointer = Nil;
Var ruDict: Pointer = Nil;

Var parse_options_create: function: Pointer; cdecl;
Var parse_options_delete: function(Opts: Pointer): Integer; cdecl;

Var parse_options_set_max_parse_time: procedure(Opts: Pointer; secs: Integer); cdecl;
Var parse_options_set_linkage_limit: procedure(Opts: Pointer; limit: Integer); cdecl;
Var parse_options_set_min_null_count: procedure(Opts: Pointer; null_count: Integer); cdecl;
Var parse_options_set_max_null_count: procedure(Opts: Pointer; null_count: Integer); cdecl;
Var parse_options_set_short_length: procedure(Opts: Pointer; short_length: Integer); cdecl;
Var parse_options_set_islands_ok: procedure(Opts: Pointer; islands_ok: Boolean); cdecl;
Var parse_options_set_disjunct_cost: procedure(Opts: Pointer; cost: Double); cdecl;
Var parse_options_reset_resources: procedure(Opts: Pointer); cdecl;
Var parse_options_resources_exhausted: function(Opts: Pointer): Boolean; cdecl;

Var dictionary_create_lang: function(Const lang: PChar): Pointer; cdecl;
Var dictionary_create_default_lang: function: Pointer; cdecl;
Var dictionary_delete: procedure(dict: Pointer); cdecl;

Var sentence_create: function(Const input_string: PChar; dict: Pointer): Pointer; cdecl;
Var sentence_delete: procedure(sent: Pointer); cdecl;
Var sentence_parse: function(sent: Pointer; opts: Pointer): Integer; cdecl;
Var sentence_length: function(sent: Pointer): Integer; cdecl;
Var sentence_num_violations: function(sent: Pointer; linkage_num: Integer): Integer; cdecl;
Var sentence_num_linkages_found: function(sent: Pointer): Integer; cdecl;
Var sentence_num_valid_linkages: function(sent: Pointer): Integer; cdecl;
Var sentence_num_linkages_post_processed: function(sent: Pointer): Integer; cdecl;

Var linkage_create: function(linkage_num: Integer; sent, opts: Pointer): Pointer; cdecl;
Var linkage_delete: procedure(linkage: Pointer); cdecl;
Var linkage_get_num_words: function(const linkage: Pointer): Integer; cdecl;
Var linkage_get_num_links: function(const linkage: Pointer): Integer; cdecl;
Var linkage_get_link_lword: function(const linkage: Pointer; index: Integer): Integer; cdecl;
Var linkage_get_link_rword: function(const linkage: Pointer; index: Integer): Integer; cdecl;
Var linkage_get_link_length: function(const linkage: Pointer; index: Integer): Integer; cdecl;
Var linkage_get_link_label: function(const linkage: Pointer; index: Integer): PChar; cdecl;
Var linkage_get_link_llabel: function(const linkage: Pointer; index: Integer): PChar; cdecl;
Var linkage_get_link_rlabel: function(const linkage: Pointer; index: Integer): PChar; cdecl;
Var linkage_get_link_num_domains: function(const linkage: Pointer; index: Integer): Integer; cdecl;
Var linkage_get_link_domain_names: function(const Linkage: Pointer; index: Integer): PPChar; cdecl;
Var linkage_get_words: function(const Linkage: Pointer): PPChar; cdecl;
Var linkage_get_word: function(const linkage: Pointer; word_num: Integer): PChar; cdecl;

Function IntegerToTObject(S: Integer): TObject;

Var V64: Int64 Absolute Result;
    V32: Integer Absolute Result;
Begin
  {$WARN 6018 OFF}
  If SizeOf(Result) = 4 Then V32 := S
  Else If SizeOf(Result) = 8 Then V64 := S
  Else
    Begin
      {$IF DEFINED(LCL) OR DEFINED(VCL)}
      MessageDlg('Unknown pointer size',mtError,[mbOk],0);
      {$ELSE}
      WriteLn('Unknown pointer size');
      {$ENDIF}
      Halt(-1)
    End;
  {$WARN 6018 ON}
End;

function parse(const lang: String; dict: Pointer; Const text: WideString): PWideChar;

Function RPosW(c:char; const S : WideString):SizeInt;

var I   : SizeInt;
    p,p2: pWideChar;
Begin
 I:=Length(S);
 If I<>0 Then
   begin
     p:=@s[i];
     p2:=@s[1];
     while (p2<=p) and (p^<>c) do dec(p);
     i:=p-p2+1;
   end;
  RPosW:=i;
End;

function _parse(_text: WideString; Var _info, _type: WideString): WideString;

Var point: Integer;
    F: Integer;
begin
   point := RPosW('.', _text);
   If point > 0 Then
      begin
        _type := Copy(_text, point + 1, 255);
        _text := Copy(_text, 1, point - 1)
      end
   Else
      _type := '';
   Result := '';
   F := 1;
   While (F <= Length(_text)) And (_text[F] <> '[') Do
     Begin
       Result := Result + _text[F];
       Inc(F)
     end;
   If F > Length(_text) Then
      _info := ''
   Else
      _info := Copy(_text, F + 1, Length(_text) - F - 1)
end;

Var _text: String;
    _mode: WideChar;
    sent: Pointer;
    linkage: Pointer;
    num_linkages, num_links: Integer;
    Lbl: String;
    L, R: Integer;
    Ltext, Rtext: WideString;
    Linfo, Rinfo: WideString;
    Ltype, Rtype: WideString;
    _Tags: String;
    WTags: WideString;
    Restricts: TList;
    Good: Boolean;
    S: String;
    F, G, K: Integer;
begin
  _Tags := '';
  If (Grammer <> NilHandle) And (Length(Trim(text)) > 0) Then
     begin
        _text := '';
        Restricts := TList.Create;

        F := 1;
        While F <= Length(text) Do
           Begin
             If text[F] in ['''', '"'] then
                Begin
                  _mode := text[F];
                  Inc(F);
                  While (F <= Length(text)) And (text[F] <> _mode) Do
                     Inc(F)
                End
             Else If text[F] = '#' Then
                Begin // #must_link1;or_must_link2##must_link1;or_must_link2#...
                  Inc(F);
                  Restricts.Add(TStringList.Create);
                  While (F <= Length(text)) And (text[F] <> '#') Do
                     begin
                       S := '';
                       While (F <= Length(text)) And (text[F] <> ';') And (text[F] <> '#') Do
                          begin
                            AppendStr(S, text[F]);
                            Inc(F)
                          end;
                       TStringList(Restricts[Restricts.Count-1]).Add(S);
                       If text[F] <> '#' Then
                          Inc(F)
                     end
                End
             Else
                If Not ((text[F] in ['0'..'9']) Or
                        (lang = 'ru') And (text[F] in ['a'..'z', 'A'..'Z']) Or
                        (lang = 'en') And (((text[F] >= 'А') And (text[F] <= 'Я')) Or
                                           ((text[F] >= 'а') And (text[F] <= 'я'))
                                          )
                       ) Then
                   AppendStr(_text, text[F]);
             Inc(F)
           End;
        sent := sentence_create(PChar(_text), dict);
	parse_options_set_min_null_count(GOpts, 0);
	parse_options_set_max_null_count(GOpts, 0);
	parse_options_reset_resources(GOpts);
        num_linkages := sentence_parse(sent, GOpts);
        if num_linkages >= 0 Then
           begin
             if num_linkages = 0 then
                num_linkages := sentence_num_linkages_found(sent);
             if num_linkages = 0 then
                begin
          	   parse_options_set_min_null_count(GOpts, 1);
          	   parse_options_set_max_null_count(GOpts, sentence_length(sent));
                   num_linkages := sentence_parse(sent, GOpts)
                end;
             num_linkages := sentence_num_linkages_post_processed(sent);
             F := 0;
             While F < num_linkages Do
               Begin
                 If sentence_num_violations(sent, F) <> 0 Then
                    begin
                      Inc(F);
                      Continue
                    end;
                 linkage := linkage_create(F, sent, GOpts);

   	         If sentence_num_violations(sent, F) = 0 Then
                    begin
                      num_links := linkage_get_num_links(linkage);
                      _Tags := '';
                      For G := 0 To Restricts.Count-1 Do
                          TStringList(Restricts[G]).Objects[0] := Nil;
                      For G := 0 To num_links - 1 Do
                          Begin
                            L := linkage_get_link_lword(linkage, G);
                            R := linkage_get_link_rword(linkage, G);
                            Ltext := {UTF8Decode}(linkage_get_word(linkage, L));
                            Ltext := _parse(Ltext, Linfo, Ltype);
                            Rtext := {UTF8Decode}(linkage_get_word(linkage, R));
                            Rtext := _parse(Rtext, Rinfo, Rtype);
                            Lbl := linkage_get_link_label(linkage, G);
                            For K := 0 To Restricts.Count-1 Do
                                If TStringList(Restricts[K]).IndexOf(Lbl) >= 0 Then
                                   TStringList(Restricts[K]).Objects[0] := IntegerToTObject(256);
                            AppendStr(_Tags, Format('<Link><Name>%s</Name><Left><Value>%s</Value><Info>%s</Info><Type>%s</Type></Left><Right><Value>%s</Value><Info>%s</Info><Type>%s</Type></Right></Link>',
                              [Lbl,
                                 Ltext, Linfo, Ltype,
                                 Rtext, Rinfo, Rtype
                              ]))
                          End;
                      linkage_delete(linkage);
                      Good := True;
                      For G := 0 To Restricts.Count-1 Do
                          Good := Good And Assigned(TStringList(Restricts[G]).Objects[0]);
                      If Good Then Break
                    end
                 Else
                    linkage_delete(linkage);

                 Inc(F)
               end;
           end;
        sentence_delete(sent);
        For F := 0 To Restricts.Count-1 Do
            TStringList(Restricts[F]).Free;
        Restricts.Free
     end;
  WTags := _Tags;
  Result := WideStrAlloc(Length(WTags)+1);
  Move(WTags[1], Result^, Length(WTags)*SizeOf(WideChar));
  (Result + Length(WTags))^ := #0;
end;

function ru(Const text: PWideChar): PWideChar; cdecl;
begin
  If Not Assigned(ruDict) Then
     ruDict := dictionary_create_lang('ru');
  Result := parse('ru', ruDict, text)
end;

function en(Const text: PWideChar): PWideChar; cdecl;
begin
  If Not Assigned(enDict) Then
     enDict := dictionary_create_lang('en');
  Result := parse('en', enDict, text)
end;

exports
   en, ru;

procedure LibExit(Info: PtrInt);
begin
  If Grammer <> NilHandle Then
     Begin
       parse_options_delete(GOpts);
       If Assigned(enDict) Then
          dictionary_delete(enDict);
       If Assigned(ruDict) Then
          dictionary_delete(ruDict);
       FreeLibrary(Grammer)
     End
end;

begin
  // library initialization code
  DefaultTextLineBreakStyle := tlbsCRLF;
  SetMultiByteConversionCodePage(CP_UTF8);
  SetMultiByteRTLFileSystemCodePage(CP_UTF8);

  Grammer := LoadLibrary({$IF DEFINED(UNIX) OR DEFINED(LINUX)}'./liblink-grammar.'{$ELSE}'link-grammar-x86.'{$ENDIF} + SharedSuffix);
  If Grammer <> NilHandle Then
     Begin
       parse_options_create := GetProcedureAddress(Grammer, 'parse_options_create');
       parse_options_delete := GetProcedureAddress(Grammer, 'parse_options_delete');
       GOpts := parse_options_create();

       dictionary_create_lang          := GetProcedureAddress(Grammer, 'dictionary_create_lang');
       dictionary_create_default_lang  := GetProcedureAddress(Grammer, 'dictionary_create_default_lang');
       dictionary_delete               := GetProcedureAddress(Grammer, 'dictionary_delete');

       parse_options_set_max_parse_time  := GetProcedureAddress(Grammer, 'parse_options_set_max_parse_time');
       parse_options_set_linkage_limit   := GetProcedureAddress(Grammer, 'parse_options_set_linkage_limit');
       parse_options_set_min_null_count  := GetProcedureAddress(Grammer, 'parse_options_set_min_null_count');
       parse_options_set_max_null_count  := GetProcedureAddress(Grammer, 'parse_options_set_max_null_count');
       parse_options_set_short_length    := GetProcedureAddress(Grammer, 'parse_options_set_short_length');
       parse_options_set_islands_ok      := GetProcedureAddress(Grammer, 'parse_options_set_islands_ok');
       parse_options_set_disjunct_cost   := GetProcedureAddress(Grammer, 'parse_options_set_disjunct_cost');
       parse_options_reset_resources     := GetProcedureAddress(Grammer, 'parse_options_reset_resources');
       parse_options_resources_exhausted := GetProcedureAddress(Grammer, 'parse_options_resources_exhausted');

       parse_options_set_max_parse_time(GOpts, 30);
       parse_options_set_linkage_limit(GOpts, 1000);
       parse_options_set_min_null_count(GOpts, 0);
       parse_options_set_max_null_count(GOpts, 0);
       parse_options_set_short_length(GOpts, 16);
       parse_options_set_islands_ok(GOpts, true);
       parse_options_set_disjunct_cost(GOpts, 2.7);

       sentence_create             := GetProcedureAddress(Grammer, 'sentence_create');
       sentence_delete             := GetProcedureAddress(Grammer, 'sentence_delete');
       sentence_parse              := GetProcedureAddress(Grammer, 'sentence_parse');
       sentence_length             := GetProcedureAddress(Grammer, 'sentence_length');
       sentence_num_violations     := GetProcedureAddress(Grammer, 'sentence_num_violations');
       sentence_num_linkages_found := GetProcedureAddress(Grammer, 'sentence_num_linkages_found');
       sentence_num_valid_linkages := GetProcedureAddress(Grammer, 'sentence_num_valid_linkages');
       sentence_num_linkages_post_processed := GetProcedureAddress(Grammer, 'sentence_num_linkages_post_processed');

       linkage_create                := GetProcedureAddress(Grammer, 'linkage_create');
       linkage_delete                := GetProcedureAddress(Grammer, 'linkage_delete');
       linkage_get_num_words         := GetProcedureAddress(Grammer, 'linkage_get_num_words');
       linkage_get_num_links         := GetProcedureAddress(Grammer, 'linkage_get_num_links');
       linkage_get_link_lword        := GetProcedureAddress(Grammer, 'linkage_get_link_lword');
       linkage_get_link_rword        := GetProcedureAddress(Grammer, 'linkage_get_link_rword');
       linkage_get_link_length       := GetProcedureAddress(Grammer, 'linkage_get_link_length');
       linkage_get_link_label        := GetProcedureAddress(Grammer, 'linkage_get_link_label');
       linkage_get_link_llabel       := GetProcedureAddress(Grammer, 'linkage_get_link_llabel');
       linkage_get_link_rlabel       := GetProcedureAddress(Grammer, 'linkage_get_link_rlabel');
       linkage_get_link_num_domains  := GetProcedureAddress(Grammer, 'linkage_get_link_num_domains');
       linkage_get_link_domain_names := GetProcedureAddress(Grammer, 'linkage_get_link_domain_names');
       linkage_get_words             := GetProcedureAddress(Grammer, 'linkage_get_words');
       linkage_get_word              := GetProcedureAddress(Grammer, 'linkage_get_word');
     End;

  {$IF NOT DEFINED(UNIX) AND NOT DEFINED(LINUX)}
  DLL_Process_Detach_Hook := @LibExit;
  {$ENDIf}
end.
