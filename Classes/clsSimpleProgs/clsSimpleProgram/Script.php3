<?php
   // @clsSimpleProgram[@Name="Main"]
   // @clsSimpleProgram[@Name="Main"]/OContacts/Begin?=>@clsSimpleBlock/IContacts/Prev
   if ($Stage == stResource) {
   // [
?>
#include <stdio.h>
#include <stdlib.h>
<?php
   // ]
   } else if ($Stage == stInit) {
   // [
?>
int main() {
<?php // ]
     while (($D = GetNextMail("Decls")) !== "")
       echo $D . "\n";
     $C = array();
     while (($i = GetNextMail("Counters")) !== "")
       array_push($C, $i);
     $counters = array_unique($C);
     foreach ($counters as $c)
        echo "  int " . $c . ";\n";
   } else if ($Stage == stDone) {
   // [
     PlanAutoStart("C");
?>
  return 0;
}
<?php // ]
   }

?>