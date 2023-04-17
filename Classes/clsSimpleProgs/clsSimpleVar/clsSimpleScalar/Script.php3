<?php
// @global_unique(DECL,infinity):-
// (\s*double\s+(\w+)->{ID}\;\\n)->{LINE}.
// @goal:-
// xpath('DECL','//ID/text()',[IDText]),global_id(GID),assertz(simple_scalar(GID,IDText)),save([simple_scalar,simple_vector,simple_act,simple_program]).
// @done:-
// saveLF.
?>
<?php
   if ($Stage == stResource) {
      PutMail("Decls", "  double " . $this->ID . ";");
   }
?>