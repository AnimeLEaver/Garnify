<?php
	include ('database.php');

	//fetch all data from arduino
	$sunval = $_GET["sunval"];
	$frameval = $_GET["frameval"];
	$tempval = $_GET["tempval"];
	$humival = $_GET["humival"];
	$soilval = $_GET["soilval"];

	echo $sql = "INSERT INTO `data` (`id`, `sunlight`, `frame`, `temperature`, `humidity`, `soil`, `date`) VALUES (NULL, '".$sunval."', '".$frameval."', '".$tempval."', '".$soilval."' ,'".$humival."', NOW());";

	$result = $conDB->query($sql);
	if($result)
	{
		echo "Success";
	}
	else
	{
		echo "madafaka";
	}

?>