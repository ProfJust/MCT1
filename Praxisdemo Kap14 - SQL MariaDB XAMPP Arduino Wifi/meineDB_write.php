<?php
// PHP Script für das Eintragen von Werten in ein MySQL-Datenbank
// Wird dieses Skript aufgerufen, trägt es hum und temp in die Db ein
// Kann mit Firefox von jedem PC im Netzwerk aufgerufen werden
// zum Testen: Aufrufzeile im Browser 
// http://192.168.1.142/myPage4SQL/meineDB_write.php?hum=0.00&temp=112.4
// .. oder per Arduino im WLAN per URL-Get Befehl
// "GET /myPage4SQL/meineDB_write.php?hum=0.00&temp=171.00 HTTP/1.1" 200 106 "-" "-"
//---------------------------------------------------------------------------------
// OJ am 18.03.2021
//--------------------------------------------------------------------------------

// Damit alle Fehler angezeigt werden
error_reporting(E_ALL);

// Zum Aufbau der Verbindung zur Datenbank 
// Die Datenbank (XAMPP) läuft auf diesen PC =>
define ( 'MYSQL_HOST',      'localhost' );
//define ( 'MYSQL_HOST',      '127.0.0.1' );

// bei XAMPP ist der MYSQL_Benutzer: root
define ( 'MYSQL_BENUTZER',  'root' );
define ( 'MYSQL_KENNWORT',  '' ); // kein Passwort =>''

// wie heist die in MySQL angelegte Datenbank
define ( 'MYSQL_DATENBANK', 'meinedb' );

// Verbindung mit MySQL erstellen
$db_link = mysqli_connect (
                     MYSQL_HOST, 
                     MYSQL_BENUTZER, 
                     MYSQL_KENNWORT, 
                     MYSQL_DATENBANK );

// Verbindung prüfen
if ( $db_link ){
    // Zeilensprung wird vom Browser nur als HTML beachtet => <br />
    // http://www.rither.de/a/informatik/php-beispiele/grundlagen/zeilenumbrueche-mit-echo/
    echo (' Verbindung mit meinedb erfolgreich! /n<br />'); 
    // debug only print_r( $db_link);
}
else{
    die('keine Verbindung möglich: ' . mysqli_error());
}

// Daten in meinDB eintragen
$my_sql_query="insert into meinedb.mytab (hum,temp)  values ('".$_GET["hum"]."', '".$_GET["temp"]."')"; 
print_r( $my_sql_query );
$db_link->query($my_sql_query); 

?>