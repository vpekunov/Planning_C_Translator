<?php
   if ($Stage == stInit) {
      $argumentID = $Arg["ID"][0];
      if ($Arg["_ClassID"][0] == "clsSimpleVector") {
         $argumentSize = $Arg["Size"][0];
?>
  for (i = 0; i < <?php echo $argumentSize; ?>; i++)
<?php
         echo "    $argumentID" . "[i] = 1.0*rand()/RAND_MAX;\n";
      } else
         echo "    $argumentID = 1.0*rand()/RAND_MAX;\n";
   }
?>