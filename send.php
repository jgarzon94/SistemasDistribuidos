
<?php
    // iot.php
    // Importamos la configuración
    require("conexion.php");
    // Leemos los valores que nos llegan por GET
    $valor = mysqli_real_escape_string($con, $_GET['velocidad']);
    // Esta es la instrucción para insertar los valores
    $query = "INSERT INTO velocidades(velocidad) VALUES('".$velocidad."')";
    // Ejecutamos la instrucción
    mysqli_query($con, $query);
    mysqli_close($con);
?>