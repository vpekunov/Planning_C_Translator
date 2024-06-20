library xpathInduct;

{$mode delphi}{$H+}

{$IF DEFINED(UNIX) OR DEFINED(LINUX)}
{$linklib c}
//{$linklib stdc++}
{$ENDIF}

Uses (* LazUTF8, *) {$IF (DEFINED(UNIX)) OR (DEFINED(LINUX))}cmem, CThreads,{$ENDIF}
  dynlibs, StrUtils, SysUtils, Classes, usemaphore,
  Consts, AutoConsts, Common, Lexique, regexpr, xpath, xpathing;

exports
   XPathing.XPathInduct, CompileXPathing,
   SetInterval, ClearRestrictions,
   ClearRuler, SetDeduceLogFile,
   CreateDOMContact, GetMSG;

begin
  // library initialization code
  DefaultTextLineBreakStyle := tlbsCRLF;
  SetMultiByteConversionCodePage(CP_UTF8);
  SetMultiByteRTLFileSystemCodePage(CP_UTF8);
end.
