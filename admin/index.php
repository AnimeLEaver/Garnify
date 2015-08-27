<?php
session_start();

if(!isset($_SESSION))
{
	header('location: login.php');
}
else
{
	header('location: dashboard.php');
}

?>