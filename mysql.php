<?php
    $conexion = mysql_connect("localhost", "user", "12345");
    mysql_select_db("sistema de control de velocidades",$conexion);
                     
    mysql_query("INSERT INTO `velocidades`(`velocidad`) VALUES ('" . $_GET['valor'] . "')", $conexion);
 
?>