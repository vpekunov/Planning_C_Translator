<?php
// @context(ASSGN,infinity):-
// (\s*(\w+)->{RESULT}\s*\=\s*([0-9+\-Ee.]+)->{INIT};\\n)->{LINE}.
// @global_unique(PROCESS,1):-
// \s*for\s*\(i\s*\=\s*0\;\s*i\s*\<\s*(\d+)->{N}\;\s*i\+\+\)\\n((\s*if\s*\((\w+)->{VECTOR}\[i\]\s*([<>])->{OPER}\s*(\w+)==>{ASSGN.RESULT}\)\\n\s*(\w+)==>{ASSGN.RESULT}\s*\=\s*(\w+)==>{VECTOR}\[i\];\\n)|(\s*(\w+)==>{ASSGN.RESULT}\s*\+\=\s*(\w+)->{VECTOR}\[i\];\\n)).
// handle:-xpath('PROCESS','//OPER[text()=''>'']',[_]),
//   xpath('ASSGN','//RESULT/text()',[RText]),
//   xpath('PROCESS','//VECTOR/text()',[VText]),
//   xpath('PROCESS','//N/text()',[NText]),
//   simple_scalar(_,RText),simple_vector(_,VText,NText),
//   global_id(GID),assertz(simple_act(GID,'Max',VText,RText)),!.
// handle:-xpath('PROCESS','//OPER[text()=''<'']',[_]),
//   xpath('ASSGN','//RESULT/text()',[RText]),
//   xpath('PROCESS','//VECTOR/text()',[VText]),
//   xpath('PROCESS','//N/text()',[NText]),
//   simple_scalar(_,RText),simple_vector(_,VText,NText),
//   global_id(GID),assertz(simple_act(GID,'Min',VText,RText)),!.
// handle:-
//   xpath('ASSGN','//RESULT/text()',[RText]),
//   xpath('PROCESS','//VECTOR/text()',[VText]),
//   xpath('PROCESS','//N/text()',[NText]),
//   simple_scalar(_,RText),simple_vector(_,VText,NText),
//   global_id(GID),assertz(simple_act(GID,'Avr',VText,RText)),!.
// @goal:-
// handle,save([simple_scalar,simple_vector,simple_act,simple_program]).
// @done:-
// saveLF.
?>
<?php
   // @clsSimpleMat[@ID=concat("min",local.Arg) or @ID=concat("max",local.Arg) or @ID=concat("avr",local.Arg)]/OContacts/Next?=>@clsSimpleBlock/IContacts/Prev
   // @clsSimpleBlock/OContacts/Next?=>@clsSimpleMat[@ID=concat("min",local.Arg) or @ID=concat("max",local.Arg) or @ID=concat("avr",local.Arg)]/IContacts/Prev
   // @clsSimpleMat[@Op="Min" and local.Oper="<" and @ID=concat("min",local.Arg)]
   // @clsSimpleMat[@Op="Max" and local.Oper=">" and @ID=concat("max",local.Arg)]
   // @clsSimpleMat[@Op="Avr" and local.Oper="+=" and local.Div="/=" and @ID=concat("avr",local.Arg)]
   // @clsSimpleVector[@ID=local.Arg and @Size=local.N]
   // @clsSimpleScalar[@ID=local.Result]
   // @clsSimpleVector[@ID=local.Arg and @Size=local.N]/@clsSimpleMat[local.Oper="<" and @ID=concat("min",local.Arg)]
   // @clsSimpleVector[@ID=local.Arg and @Size=local.N]/@clsSimpleMat[local.Oper=">" and @ID=concat("max",local.Arg)]
   // @clsSimpleVector[@ID=local.Arg and @Size=local.N]/@clsSimpleMat[local.Oper="+=" and local.Div="/=" and @ID=concat("avr",local.Arg)]
   // @clsSimpleMat[local.Oper="<" and @ID=concat("min",local.Arg)]/@clsSimpleScalar[@ID=local.Result]
   // @clsSimpleMat[local.Oper=">" and @ID=concat("max",local.Arg)]/@clsSimpleScalar[@ID=local.Result]
   // @clsSimpleMat[local.Oper="+=" and local.Div="/=" and @ID=concat("avr",local.Arg)]/@clsSimpleScalar[@ID=local.Result]
   if ($Stage == stInit) {
      $argumentID = $Arg["ID"][0];
      $argumentSize = $Arg["Size"][0];
      $resultID = GetNextMail("result" . $this->ID);
      if ($this->Op == "Min") {
         echo "  " . $resultID . " = 1E300;\n";
      } else if ($this->Op == "Max") {
         echo "  " . $resultID . " = -1E300;\n";
      } elseif ($this->Op == "Avr") {
         echo "  " . $resultID . " = 0.0;\n";
      }
      // [
?>
  for (i = 0; i < <?php /* ]+ */ /* +[\s*([^;]+)->{local.N}\s*]+ */ echo $argumentSize; /* +[ */ ?>; i++)
<?php // ]+
   // +[(\s*if\s*\((\w+)->{local.Arg}\[i\]\s*\([<>])->{local.Oper}\s*(\w+)->{local.Result}\s*\))|
   // (\s*(\w+)->{local.Result}\s*(\+\=)->{local.Oper}\s*(\w+)->{local.Arg}\[i\];)]
      if ($this->Op == "Min") {
?>
    if (<?php echo $argumentID . "[i] < " . $resultID; ?>)
       <?php echo $resultID . " = " . $argumentID . "[i];\n";
      } else if ($this->Op == "Max") {
?>
    if (<?php echo $argumentID . "[i] > " . $resultID; ?>)
       <?php echo $resultID . " = " . $argumentID . "[i];\n";
      } elseif ($this->Op == "Avr") {
         echo "    " . $resultID . " += " . $argumentID . "[i];\n";
      }

   // [\s*(\w+)->{local.Result}\s*(\/\=)->{local.Div}\s*(\w+)->{local.Arg};]
      if ($this->Op == "Avr") {
         echo "  " . $resultID . " /= " . $argumentSize . ";\n";
      }
   }
?>