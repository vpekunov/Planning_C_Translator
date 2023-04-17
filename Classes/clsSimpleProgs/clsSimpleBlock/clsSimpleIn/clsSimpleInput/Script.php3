<?php
// @global_unique(PROCESS,infinity):-
// (\s*for\s*\(i\s*\=\s*0\;\s*i\s*\<\s*(\d+)->{N}\;\s*i\+\+\)\s*\{\\n\s*printf\(\"(\w+)->{VECTOR}\[\%i\]\s*\=\s*\"\,\s*i\)\;\\n\s*scanf\(\"\%lf\"\,\s*\&(\w+)==>{VECTOR}\[i\]\)\;\\n\s*\}\\n)|(\s*printf\(\"(\w+)->{SCALAR}\s*\=\s*\"\)\;\\n\s*scanf\(\"\%lf\"\,\s*\&(\w+)==>{SCALAR}\)\;\\n).
// handle:-xpath('PROCESS','//VECTOR/text()',[VText]),
//   xpath('PROCESS','//N/text()',[NText]),
//   simple_vector(_,VText,NText),
//   global_id(GID),assertz(simple_act(GID,in,VText,'')),!.
// handle:-xpath('PROCESS','//SCALAR/text()',[SText]),
//   simple_scalar(_,SText),
//   global_id(GID),assertz(simple_act(GID,in,SText,'')),!.
// @goal:-
// handle,save([simple_scalar,simple_vector,simple_act,simple_program]).
// @done:-
// saveLF.
?>
<?php
   if ($Stage == stInit) {
      $argumentID = $Arg["ID"][0];
      if ($Arg["_ClassID"][0] == "clsSimpleVector") {
         $argumentSize = $Arg["Size"][0];
?>
  for (i = 0; i < <?php echo $argumentSize; ?>; i++) {
<?php
         echo "    printf(\"$argumentID" . "[%i] = \", i);\n";
         echo "    scanf(\"%lf\", &$argumentID" . "[i]);\n";
?>
  }
<?php
      } else {
         echo "  printf(\"$argumentID" . " = \");\n";
         echo "  scanf(\"%lf\", &$argumentID);\n";
      }
   }
?>