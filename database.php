<?php

$host="localhost"; // Host name 
$dbusername="root"; // Mysql username 
$dbpassword=""; // Mysql password 
$db_name="mdd"; // Database name 
$tbl_name="data"; // Table name 

// Connect to server and select databse.
$conDB = new mysqli("$host", "$dbusername", "$dbpassword","$db_name");
// mysql_select_db("$db_name")or die("cannot select DB");
?>