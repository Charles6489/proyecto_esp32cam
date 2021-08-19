<?php
$luz = $_GET["luz"];
//echo $luz;
$b = 1;
$asterisk_outgoing = "/var/spool/asterisk/outgoing/";
$asterisk_tmp = "/tmp/";
$asterisk_cid = "Sensor de Luz<202>"; // the from caller id you'd like to display.
if (1 == $luz){
    $arduinocallfile = "/$asterisk_tmp/arduino_call.txt";
    $arduinocall = fopen($arduinocallfile, 'w') or die("can't open file");
    $arduinocall_data="Channel:SIP/200\nApplication:AGI\nData:arduino.php\nCallerID:$asterisk_cid";
    fwrite($arduinocall, $arduinocall_data);
    fclose($arduinocall);
   // chmod, chown and chgrp the file to asterisk:asterisk
    chmod ("/$asterisk_tmp/arduino_call.txt", 0666);
    chown ("/$asterisk_tmp/arduino_call.txt", "asterisk");
    chgrp ("/$asterisk_tmp/arduino_call.txt", "asterisk");
    rename("/$asterisk_tmp/arduino_call.txt","/$asterisk_outgoing/arduino_call.call");
    echo $luz;
}else {

    echo("no hay llamdas recientes");
}               
?>
