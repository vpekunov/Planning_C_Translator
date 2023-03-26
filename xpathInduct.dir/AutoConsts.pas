unit AutoConsts;

{$IFDEF FPC}
{$MODE Delphi}
{$ENDIF}

interface

Uses SysUtils, Classes;

Const BoolVals:Array[Boolean] Of PChar = ('False','True');

Const CR = #$0D;
      LF = #$0A;
      CRLF = #$0D#$0A;

{$IF DEFINED(UNIX) OR DEFINED(LINUX)}
Const SuperSlash = '/';
{$ELSE}
Const SuperSlash = '\';
{$ENDIF}

Const cnidAny    = '$*any';

      flChecked             = $01;
      flClassesGenerated    = $02;
      flCallsGenerated      = $04;
      flPredicatesGenerated = $40;
      flAllTemporary        = flChecked Or flClassesGenerated Or flCallsGenerated or flPredicatesGenerated;
      flShowClass           = $08;
      flShowName            = $10;
      flShowImage           = $20;
      flAllShow             = flShowClass Or flShowName Or flShowImage;

      idfunGenerate    = 'Generate';
      idfunPushCortege = 'cortege_push';
      idfunNextEvent   = 'NextEvent';

      TasksDir         = 'Tasks';

      idlibAutoUtils = 'autoutil.php3';
      idlibUserVars  = '_vars.php3';
      idproAutoUtils = 'autoutil';
      idlibXPath     = 'XPath.class.php';
      idParamsFile   = 'params.cfg';
      idParamsOut    = 'params.out';
      {$IF DEFINED(UNIX) OR DEFINED(LINUX)}
      idParamsExe    = './lparams';
      {$ELSE}
      idParamsExe    = 'params.exe';
      {$ENDIF}

      idprmStage     = 'Stage';

      idvarStage     = 'Stage';
      idvarEvents    = 'Events';
      idvarNumEvents = 'NumEvents';
      idvarTape      = 'Tape';

      idconstResource = 'stResource';
      idconstInit     = 'stInit';
      idconstCall     = 'stCall';
      idconstDone     = 'stDone';

      idfieldClassID = 'ClassID';
      idfieldID      = 'ID';

      tagPHPOpen  = '<?php';
      tagPHPClose = '?>';

      errPHP  = '<#GENERROR>';
      errMAIN = '!Error:';

      ScriptPrepend  = tagPHPOpen+CRLF+
         'include("'+idlibAutoUtils+'");'+CRLF+
         'include("'+idlibXPath+'");'+CRLF+
         'if (file_exists("'+idlibUserVars+'"))'+CRLF+
         '   include("'+idlibUserVars+'");'+CRLF+
         CRLF+
         'global $XML;'+CRLF+
         '$xmlOptions = array(XML_OPTION_CASE_FOLDING => FALSE, XML_OPTION_SKIP_WHITE => TRUE);'+CRLF+
         '$XML = new XPathEngine($xmlOptions);'+CRLF+
         '$XML->importFromFile("_.xml");'+CRLF;

      ScriptPost     = 'CloseAsserta();'+CRLF+
                       'fclose($MappedOutput);'+CRLF+
                       'ChangeOutput(''stdout'',true);'+CRLF+
                       tagPHPClose;

      PrologPrepend  = ':-include('+idproAutoUtils+').'+CRLF;

      xmlExt     = 'xml';
      proExt     = 'pro';
      plExt      = 'pl';
      DefaultExt = xmlExt;

      xmlSystem     = 'System';
      xmlElements   = 'Elements';
      xmlElement    = 'Element';
      xmlParameters = 'Parameters';
      xmlParameter  = 'Parameter';
      xmlIInputs    = 'InternalInputs';
      xmlIOutputs   = 'InternalOutputs';
      xmlIContact   = 'iContact';
      xmlPInputs    = 'PublishedInputs';
      xmlPOutputs   = 'PublishedOutputs';
      xmlPContact   = 'pContact';
      xmlILinks     = 'InputLinks';
      xmlOLinks     = 'OutputLinks';
      xmlLink       = 'Link';
      xmlContact    = 'Contact';
      xmlShow       = 'Show';
      xmlPosition   = 'Position';
      xmlPoints     = 'Points';

      xmlHeader     =
'<?xml version="1.0" encoding="utf-8"?>'+CRLF+
'<!DOCTYPE System ['+CRLF+
'<!ELEMENT System (Elements)>'+CRLF+
'<!ATTLIST System'+CRLF+
'Lang CDATA #REQUIRED'+CRLF+
'>'+CRLF+
'<!ELEMENT Elements (Element*)>'+CRLF+
'<!ATTLIST Elements'+CRLF+
'NumItems CDATA #REQUIRED'+CRLF+
'>'+CRLF+
'<!ELEMENT Element (Show,Position,Parameters,InternalInputs,InternalOutputs,PublishedInputs,PublishedOutputs,InputLinks,OutputLinks)>'+CRLF+
'<!ATTLIST Element'+CRLF+
'ClassID CDATA #REQUIRED'+CRLF+
'ParentID CDATA #REQUIRED'+CRLF+
'ID ID #REQUIRED'+CRLF+
'Permanent (True | False) #REQUIRED'+CRLF+
'>'+CRLF+
'<!ELEMENT Show EMPTY>'+CRLF+
'<!ATTLIST Show'+CRLF+
'Class (True | False) #REQUIRED'+CRLF+
'Name (True | False) #REQUIRED'+CRLF+
'Image (True | False) #REQUIRED'+CRLF+
'>'+CRLF+
'<!ELEMENT Position EMPTY>'+CRLF+
'<!ATTLIST Position'+CRLF+
'Left CDATA #REQUIRED'+CRLF+
'Top CDATA #REQUIRED'+CRLF+
'>'+CRLF+
'<!ELEMENT Parameters (Parameter*)>'+CRLF+
'<!ATTLIST Parameters'+CRLF+
'NumItems CDATA #REQUIRED'+CRLF+
'>'+CRLF+
'<!ELEMENT Parameter (#PCDATA | EMPTY)*>'+CRLF+
'<!ATTLIST Parameter'+CRLF+
'ID CDATA #REQUIRED'+CRLF+
'Indent CDATA #IMPLIED'+CRLF+
'>'+CRLF+
'<!ELEMENT InternalInputs (iContact*)>'+CRLF+
'<!ATTLIST InternalInputs'+CRLF+
'NumItems CDATA #REQUIRED'+CRLF+
'>'+CRLF+
'<!ELEMENT InternalOutputs (iContact*)>'+CRLF+
'<!ATTLIST InternalOutputs'+CRLF+
'NumItems CDATA #REQUIRED'+CRLF+
'>'+CRLF+
'<!ELEMENT iContact EMPTY>'+CRLF+
'<!ATTLIST iContact'+CRLF+
'ID CDATA #REQUIRED'+CRLF+
'ElementID IDREF #REQUIRED'+CRLF+
'ContID CDATA #REQUIRED'+CRLF+
'>'+CRLF+
'<!ELEMENT PublishedInputs (pContact*)>'+CRLF+
'<!ATTLIST PublishedInputs'+CRLF+
'NumItems CDATA #REQUIRED'+CRLF+
'>'+CRLF+
'<!ELEMENT PublishedOutputs (pContact*)>'+CRLF+
'<!ATTLIST PublishedOutputs'+CRLF+
'NumItems CDATA #REQUIRED'+CRLF+
'>'+CRLF+
'<!ELEMENT pContact EMPTY>'+CRLF+
'<!ATTLIST pContact'+CRLF+
'ID CDATA #REQUIRED'+CRLF+
'PublicID CDATA #REQUIRED'+CRLF+
'PublicName CDATA #REQUIRED'+CRLF+
'>'+CRLF+
'<!ELEMENT InputLinks (Contact*)>'+CRLF+
'<!ELEMENT OutputLinks (Contact*)>'+CRLF+
'<!ELEMENT Contact (Link*)>'+CRLF+
'<!ATTLIST Contact'+CRLF+
'ID CDATA #REQUIRED'+CRLF+
'>'+CRLF+
'<!ELEMENT Link (Points?)>'+CRLF+
'<!ATTLIST Link'+CRLF+
'ElementID IDREF #REQUIRED'+CRLF+
'ContID CDATA #REQUIRED'+CRLF+
'Color CDATA #IMPLIED'+CRLF+
'Informational (True | False) #REQUIRED'+CRLF+
'>'+CRLF+
'<!ELEMENT Points (#PCDATA | EMPTY)*>'+CRLF+
'<!ATTLIST Points'+CRLF+
'NumItems CDATA #REQUIRED'+CRLF+
'>'+CRLF+
']>';

      proHeader     = 'create_model:-';

      proSystem     = 'pgen_system';
      proElements   = 'elements';
      proElement    = 'element';
      proParameters = 'parameters';
      proParameter  = 'parameter';
      proIInputs    = 'internal_inputs';
      proIOutputs   = 'internal_outputs';
      proIIContact  = 'ii_contact';
      proIOContact  = 'io_contact';
      proPInputs    = 'published_inputs';
      proPOutputs   = 'published_outputs';
      proPIContact  = 'pi_contact';
      proPOContact  = 'po_contact';
      proILink      = 'i_link';
      proOLink      = 'o_link';
      proIContact   = 'i_contact';
      proOContact   = 'o_contact';
      proShow       = 'show';
      proPosition   = 'position';

      ConnectPort    = 42101;
      ConnectMask    = '224.42.10.1';
      ControlPort    = 42102;
      RegisterMaster = 'Register as Master';
      RegisterSlave  = 'Ha-ha-ha, you are Slave';
      Unregister     = 'Unregister';
      ThisIsNode     = 'I have what you want, my dear...';
      RequestNode    = 'I want node';
      FreeNode       = 'I am free';
      BusyNode       = 'I am busy';
      YouAreBusy     = 'It''s time to work... The great buiseness wait for us';
      CanIWork       = 'Can I work?';
      YouAreLocked   = 'You are locked';
      YouAreFree     = 'You are free';

      ControlMutexName = 'ControlPGEN';
      WorkMutexName    = 'WorkPGEN';

      tsModelFile  = 0;
      tsInputFile  = 1;
      tsOutputFile = 2;
      tsReportFile = 3;
      tsKindMask   = $7F;
      tsMoveFlag   = $80;
      tsReqFlag    = $100;

      dirVersions  = 'versions';

Type  efType = (efFree,efSelf,efNode);

function EscapeText(Const S:String; Var Indent:Integer):String;
function GetCommaText(Const S:TStrings):String;

implementation

function EscapeText(Const S:String; Var Indent:Integer):String;

Const NumMetaChars = 5;
      MetaChars: Array[1..NumMetaChars] Of Char = '&<>''"';
      MetaSubsts: Array[1..NumMetaChars] Of PChar = ('amp','lt','gt','apos','quot');

Var F:Integer;
begin
     Result:=S;
     For F:=Low(MetaChars) To High(MetaChars) Do
         Result:=StringReplace(Result,MetaChars[F],'&'+MetaSubsts[F]+';',[rfReplaceAll]);
     Indent:=0;
     If Length(Result)>0 Then
        If Result[1]=' ' Then
           Begin
             Indent:=Length(Result);
             Result:=TrimLeft(Result);
             Dec(Indent,Length(Result))
           End
end;

Function GetCommaText(Const S: TStrings): String;

Var F:Integer;
begin
     Result:='';
     With S Do
       For F:=0 To Count-1 Do
         Begin
           If F>0 Then Result:=Result+',';
           Result:=Result+AnsiQuotedStr(Strings[F],'"')
         End
end;

end.
