<html>
<head>
<title>BeagleBone LED Changer</title>
<style type="text/css">
	p { display: table-cell; }
	button { width: 75px; margin: 2px auto; }
</style>
<?php
	if (isset($_GET['led']) && isset($_GET['onOff']))
	{
		$led = $_GET['led'];
		$onOff = $_GET['onOff'];
		
		echo "on off change";
		exec( "/usr/lib/cgi-bin/ledcontrol $led $onOff" );
	}
?>
</head>
<body>
<div style="width: 200px; margin: 0px auto;">
	<div style="width: 100px; float: left;">
		<p>LED #2:</p>
		<button type="button" onclick="location.href='ledctl.php?led=2&onOff=1'">ON</button>
		<button type="button" onclick="location.href='ledctl.php?led=2&onOff=0'">OFF</button>
	</div>
	<div sytle="width: 100px; margin-left: 100px;">
		<p>LED #3:</p>
		<button type="button" onclick="location.href='ledctl.php?led=3&onOff=1'">ON</button>
		<button type="button" onclick="location.href='ledctl.php?led=3&onOff=0'">OFF</button>
	</div>
</div>
