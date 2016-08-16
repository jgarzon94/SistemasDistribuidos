<?

$link
=mysql_connect(
"localhost"
,
"admin"
,
""
);
if (!$conexion) {
    die('<strong>No pudo conectarse:</strong> ' . mysql_error());
}else{

echo 'Conectado  satisfactoriamente al servidor <br />';
}


mysql_select_db(
"sistema de control de velocidades"
,
$link
) OR DIE (
"Error: No es posible establecer la conexión"
);

?>
