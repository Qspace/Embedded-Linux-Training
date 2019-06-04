<html>

<head>

<title>BeagleBone Temperature</title>

<script type="text/javascript" src="https://www.google.com/jsapi"></script>

<script type="text/javascript">

google.load("visualization", "1", {packages:["corechart"]});

google.setOnLoadCallback(drawChart);

function drawChart() {

var data = google.visualization.arrayToDataTable([

['Time', 'Temperature'],

<?php

$con = mysqli_connect("localhost", "bone", "bone", "TempDB");

 

$query = "SELECT * FROM TempMeas";

$result = mysqli_query($con, $query);

 

mysqli_close($con);

 

while ($row = mysqli_fetch_array($result))

{

$time = $row['MeasTime'];

$temp = $row['Temp'];

echo "['$time', $temp],";

}

?>

]);

 

var options = {

title: 'BeagleBone Measured Temperature',

vAxis: { title: "Degrees Celsius" }

};

 

var chart = new google.visualization.LineChart(document.getElementById('chart_div'));

chart.draw(data, options);

}

</script>

</head>

<body>

<div id="chart_div" style="width: 900px; height: 500px;"></div>

</body>

</html>