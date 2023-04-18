<?php
// @global_unique(PROCESS,infinity):-
// (\s*printf\(\"(\w+)->{VECTOR}\s*\=\s*\[\"\)\;\\n\s*for\s*\(i\s*\=\s*0\;\s*i\s*\<\s*(\d+)->{N}\;\s*i\+\+\)\\n\s*printf\(\"\%lf\s*\"\,\s*(\w+)==>{VECTOR}\[i\]\)\;\\n\s*printf\(\"\]\\\\n\"\)\;\\n)|(\s*printf\(\"(\w+)->{SCALAR}\s*\=\s*\%lf\\\\n\"\,\s*(\w+)==>{SCALAR}\)\;\\n).
// handle:-xpath('PROCESS','//VECTOR/text()',[VText]),
//   xpath('PROCESS','//N/text()',[NText]),
//   simple_vector(_,VText,NText),
//   global_id(GID),assertz(simple_act(GID,out,VText,'')),!.
// handle:-xpath('PROCESS','//SCALAR/text()',[SText]),
//   simple_scalar(_,SText),
//   global_id(GID),assertz(simple_act(GID,out,SText,'')),!.
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
  printf("<?php echo $argumentID; ?> = [");
  for (i = 0; i < <?php echo $argumentSize; ?>; i++)
<?php
         echo "    printf(\"%lf \", $argumentID" . "[i]);\n";
?>
  printf("]\n");
<?php
      } else
         echo "  printf(\"$argumentID = %lf\\n\", $argumentID);\n";
   }

?>