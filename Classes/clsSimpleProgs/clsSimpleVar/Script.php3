<?php
   cortege_push($Handle["ID"], $this->ID);

   if ($Stage == stResource) {
      if (isset($Asgn["_ID"]) && is_array($Asgn["_ID"]))
         PutMail("result" . $Asgn["_ID"][0], $this->ID);
   }
?>