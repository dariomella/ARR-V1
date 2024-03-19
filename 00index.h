/*********************************************************
 * this definition sets up the skeleton for the index.html page
 */
const char index_html[] PROGMEM = R"rawliteral(

<!DOCTYPE html>
<html lang="en">
<head>
    <style>
table.table1 {
  font: 12px Arial, sans-serif;
  border-collapse: collapse;
}

table.table1 td, th {
  border: 1px solid #dddddd;
  text-align: right;
  padding-left: 3px;
  padding-right: 3px;
  margin: 0;
}

table.table2 {
  font: 13px Arial, sans-serif;
  border-collapse: collapse;
}
table.table2 td, th {
 
  text-align: right;
  padding-left: 3px;
  padding-right: 3px;
  margin: 0;
}

.container {
  width: 50px;
  background-color: #ddd;
}

.wifistrenght {
   padding: 0; 
   margin: 0;
   height:10px;
 }

.good {background-color: #00AA00;}
.avg { background-color: #ffAA00;}
.poor { background-color: red;}

</style>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<title>ARR (Automatic Router Rebooter) input parms</title>
</head>
<body>
<form action="/get" class="box" id="my-form">
<h1>ARR (Automatic Router Rebooter)</h1>
<h3>(c) Dario Mella </h3>


<h2>WIFI networks available</h2>
<table class="table1">
  <tr>
    <th>SSID</th>
    <th>Channel</th>
    <th>RSSI</th>
    <th colspan=2 style="text-align: center">Strength</th>
    <th>security</th>
  </tr>
  %wifiNetworksAvailable%
  <tr>
    <td colspan="99" style="text-align:left">
      %tableRowsWarning%
      <b>Warning:</b>the network listed are those detected during the startup;
      <br>refreshing the page has no effect
    
    </td>
  </tr>
</table>


<h3>Please fill the following fields for the WIFI connection to be monitored
<br>and then press the Save button at the end of the page</h3>


<table class="table2">
  <tbody>
	<tr>
    <td>%inputfield1%:</td>
    <td><input name="%inputfield1%" value="%currentValue1%" type="text" required></td>
     <td style="text-align:left">(WIFI connection to be monitored)</td>
  </tr>
  <tr>
    <td>%inputfield2%:</td>
    <td><input name="%inputfield2%" value="%currentValue2%" type="text" required></td>
    <td style="text-align:left">(WIFI connection to be monitored)</td>
  </tr>
</tbody></table>

<br>
<h4>The following are optional parameters. You can modify them or leave them to their default values</h4>
<table class="table2">
  <tbody>
  <tr>
        Internet connectivity is fine if at least one of the following hosts responds to a PING command
  </tr>
  <tr>
      <td>%inputfield5%:</td>
      <td><input name="%inputfield5%" value="%currentValue5%" type="text" required></td>
  </tr>
  <tr>
      <td>%inputfield6%:</td>
      <td><input name="%inputfield6%" value="%currentValue6%" type="text" required></td>
  </tr>
  <tr>
      <td>%inputfield7%:</td>
      <td><input name="%inputfield7%" value="%currentValue7%" type="text" required></td>
  </tr>
  <tr>
      <td>%inputfield8%:</td>
      <td><input name="%inputfield8%" value="%currentValue8%" type="text" required></td>
  </tr>
  </tbody>
</table> 

<br>
<table class="table2">
  <tbody>
  <tr>
    WIFI network id and password for the parameters setup (this page)
  </tr>
  <tr>
    <td>%inputfield3%:</td>
    <td><input name="%inputfield3%" value="%currentValue3%" type="text" required></td>
  </tr>
  <tr>
    <td>%inputfield4%:</td>
    <td><input name="%inputfield4%" value="%currentValue4%" type="text" required></td>
  </tr>
  </tbody>
</table> 

<br>
<table class="table2">
  <tbody>
  <tr>
    Other miscellaneous parameters
  </tr>
  <tr>
    <td>%inputfield9%:</td>
    <td><input name="%inputfield9%" value="%currentValue9%" type="text" required></td>
    <td style="text-align:left">(seconds)</td>
  </tr>
  <tr>
    <td>%inputfield11%:</td>
    <td><input name="%inputfield11%" value="%currentValue11%" type="text" required></td>
    <td style="text-align:left">(seconds)</td>
  </tr>
  <tr>
    <td>%inputfield10%:</td>
    <td><input name="%inputfield10%" value="%currentValue10%" type="text" required></td>
    <td style="text-align:left">(seconds)</td>
  </tr>
  </tbody>
</table>

<br>
<input type="submit" value="Save" style="height:40px; width:70px; font-size:140%;">

</form></body></html>

)rawliteral";

const char notfound_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
    <head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">
      <link rel=\"icon\" href=\"data:,\">
      <title>404 - Page not found</title>
    </head>
    <body>
      <h1>404 - Page not found!</h1>
      <h3><a href = "\">Click here to go back home </a> </h3>
    </body>
 </html>
)rawliteral";
