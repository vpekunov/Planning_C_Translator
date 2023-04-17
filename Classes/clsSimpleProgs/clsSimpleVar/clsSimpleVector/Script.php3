<?php
// @global_unique(DECL,infinity):-
// (\s*double\s+(\w+)->{ID}\[(\d+)->{N}\]\;\\n)->{LINE}.
// @goal:-
// xpath('DECL','//ID/text()',[IDText]),xpath('DECL','//N/text()',[NText]),global_id(GID),assertz(simple_vector(GID,IDText,NText)),save([simple_scalar,simple_vector,simple_act,simple_program]).
// @done:-
// saveLF.
?>
<?php
   cortege_push($Handle["Size"], $this->Size);

   if ($Stage == stResource) {
      PutMail("Decls", "  double " . $this->ID . "[" . $this->Size . "];");
   }
?>