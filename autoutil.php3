<?php

define('stResource',0);
define('stInit',1);
define('stCall',2);
define('stDone',3);

$Events     = array(stResource,stInit,stCall,stDone);
$NumEvents  = 4;
$NewEventID = 4;

$MailBox = array();

$MappedOutput = fopen("_.map", "w");

$Exporting = 0;

$Tape = "";

function AppendTapeEnd($Text) {
 global $Tape;
 $Tape .= $Text;
}

function AppendTapeBegin($Text) {
 global $Tape;
 $Tape = $Text . $Tape;
}

function ClearTape() {
 global $Tape;
 $Tape = "";
}

function GetTape() {
 global $Tape;
 return $Tape;
}

function UnrollIfNotExport($V) {
   global $Exporting;
   if (!$Exporting && strlen($V) > 3) {
      while (ereg("\?\(([A-Za-z0-9_.:\\\/]+)\)",$V,$regs)) {
         $file = file_get_contents($regs[1]);
         $array = split("(\x0D|\x0A)+", $file);
         $f = implode("\n", $array);
         $V = str_replace("?(".$regs[1].")", $f, $V);
      }
   }
   return $V;
}

function SwitchExportOn() {
   global $Exporting;
   $Exporting = 1;
}

function StoreMapped($ClassID, $Content) {
 global $MappedOutput;
 if ($Content !== "") {
    fwrite($MappedOutput, "<<<<<".$ClassID.">>>>>\n");
    fwrite($MappedOutput, $Content);
    fwrite($MappedOutput, "<<<<</".$ClassID.">>>>>\n");
 }
}

function ChangeOutput($FName, $Append)
{
 static $CurrentOutput = 'stdout';
 static $CurrentFile;

 if ($FName!=$CurrentOutput) {
    if ($CurrentOutput!='stdout') {
       fwrite($CurrentFile,ob_get_contents());
       fclose($CurrentFile);
       ob_end_clean();
    }
    $CurrentOutput = $FName;
    if ($CurrentOutput!='stdout') {
       $CurrentFile = fopen($CurrentOutput,$Append ? "a" : "w");
       ob_start();
    }
 }
}

function PlanAsserta($Pred)
{
 $Prefix = file_exists("_out.pl") ? "use_outs:-\n" : "";
 $File = fopen("_out.pl","ab");
 fwrite($File,$Prefix);
 fwrite($File,"asserta(");
 fwrite($File,$Pred);
 fwrite($File,"),\n");
 fclose($File);
}

function CloseAsserta()
{
 if (file_exists("_out.pl"))
    {
     $File = fopen("_out.pl","ab");
     fwrite($File,"true.");
     fclose($File);
    }
}

function PlanAutoStart($Lang)
{
 $File = fopen("_.start","wb");
 fwrite($File,$Lang);
 fclose($File);
}

function MakeError($Class,$Text,$Line)
{
 echo "<#GENERROR>\n<b>".$Class."</b>".$Text." in <b>Main file</b> on line <b>".$Line."</b>\n";
 exit();
}

function CreateEventBefore($Before,$Line)
{
 global $Events,$NumEvents,$NewEventID;

 $Result = -1;
 $Idx = array_search($Before,$Events);
 if ($Idx==="")
    MakeError("Event Error",": Event '".$Before."' does not exist",$Line);
 else if ($Idx==0)
    MakeError("Event Error",": Can not insert new event before current event",$Line);
 else
   {
    $Result = $NewEventID++;
    
    $Events = array_merge(array_slice($Events,0,$Idx),array($Result),array_slice($Events,$Idx));
    $NumEvents++;
   }
 return $Result;
}

function CreateEventAfter($After,$Line)
{
 global $Events,$NumEvents,$NewEventID;

 $Result = -1;
 $Idx = array_search($After,$Events);
 if ($Idx==="")
    MakeError("Event Error",": Event '".$After."' does not exist",$Line);
 else if ($Idx==$NumEvents-1)
    MakeError("Event Error",": Can not insert new event after last event",$Line);
 else
   {
    $Result = $NewEventID++;
    
    $Events = array_merge(array_slice($Events,0,$Idx+1),array($Result),array_slice($Events,$Idx+1));
    $NumEvents++;
   }
 return $Result;
}

function GetLastEvent($Ev)
{
 global $Events;

 $EvNum = count($Ev);
 if (gettype($Ev)!="array" || $EvNum==0)
    return -1;
 elseif ($EvNum==1)
    return $Ev[0];
 else
    {
     $Last = $Ev[0];
     $ValMax = array_search($Last,$Events);
     for ($i = 1; $i<$EvNum; $i++)
       {
        $Val = array_search($Ev[$i],$Events);
        if ($Val>$ValMax)
           {
            $ValMax = $Val;
            $Last = $Ev[$i];
           }
       }
     return $Last;
    }
}

function NextEvent()
{
 global $Events,$NumEvents;

 array_shift($Events);
 return --$NumEvents > 0 ? $Events[0] : -1;
}

function cortege_push(&$Cortege,$Val)
{
 if (gettype($Cortege)!="array") $Cortege = array();
 array_push($Cortege,$Val);
}

function contact_merge($Contacts)
{
 $Result = reset($Contacts);
 while ($Current = next($Contacts))
   while (list($CKey,$CVal) = each($Current))
     if (gettype($Result[$CKey])!="array")
        $Result[$CKey] = $CVal;
     else
        $Result[$CKey] = array_merge($Result[$CKey],$CVal);
 return $Result;
}

function CreateLoopVars($N, &$LoopIDs)
{
 $LoopIDs = explode(";","i;j;k");
 for ($i = 0; $i < $N; $i++) {
?>  #DEFVAR(<?php
     echo "#INT,",$LoopIDs[$i],")\n";
 }
}

function CreateForLoop($GenVars,$NumDims, $DimArr, &$LoopIDs, &$Indexes, &$Shift)
{
 if ($GenVars)
    CreateLoopVars($NumDims,$LoopIDs);
 $Indexes = "";
 for ($i = 0; $i < $NumDims; $i++)
     $Indexes.="[".$LoopIDs[$i]."]";
 for ($i = 0; $i < $NumDims; $i++) {
     echo $Shift;
?>#FOR(<?php
     echo $LoopIDs[$i],",#LOWDIM,#HIGHDIM(".$DimArr[$i]."),1)\n";
     $Shift .= "  ";
 }
}

function CloseForLoop($NumDims, &$Shift)
{
 for ($i = 0; $i < $NumDims; $i++) {
     $Shift = substr($Shift,0,-2);
     echo $Shift;
?>#ENDFOR
<?php
 }
}

function CreateSetSelector($Shift, $ByWhat, $Assign, $SymArr, $ValArr, $ElseVal)
{
 echo $Shift,"#SELECT(",$ByWhat,")\n";
 $NumItems = count($SymArr);
 for ($i = 0; $i < $NumItems; $i++) {
     echo $Shift, "  #SELECTOR('", $SymArr[$i], "')\n";
     if ($ValArr[$i]!="") echo $Shift, "    #SET(", $Assign, ",", $ValArr[$i], ")\n";
 }
 echo $Shift, "  #SELECTOR(#ELSE)\n";
 echo $Shift, "    #SET(", $Assign, ",",$ElseVal,")\n";
 echo $Shift,"#ENDSELECT\n";
}

function IfArray($NumDims)
{
 return $NumDims>0 ? "ARRAY" : "";
}

function ShiftStr($Offset,$Str)
{
 return rtrim($Offset.str_replace("\n","\n".$Offset,$Str)," ");
}

function PutMail($Name,$Val)
{
 global $MailBox;

 if (isset($MailBox[$Name]))
    array_push($MailBox[$Name],$Val);
 else
    $MailBox[$Name] = array(array(),$Val);
}

function ReadNextMail($ID,$Name)
{
 global $MailBox;

 if (isset($MailBox[$Name]))
    {
     if (($Idx = $MailBox[$Name][0][$ID])===null)
        $Idx = 1;
     if ($Idx>=count($MailBox[$Name]))
        return "";
     else
        {
         $MailBox[$Name][0][$ID] = $Idx+1;
         return $MailBox[$Name][$Idx];
        }
    }
 else
    return "";
}

function GetNextMail($Name)
{
 global $MailBox;

 if (isset($MailBox[$Name]))
    {
     if (count($MailBox[$Name])<=1)
        return "";
     array_shift($MailBox[$Name]);
     $Result = array_shift($MailBox[$Name]);
     array_unshift($MailBox[$Name],array());
     return $Result;
    }
 else
    return "";
}

?>