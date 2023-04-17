<?php
  include 'database.php';
  
  //---------------------------------------- Condition to check that POST value is not empty.
  if (!empty($_POST)) {
    // keep track post values
    $id = $_POST['id'];
    
    $myObj = (object)array();
    
    //........................................ 
    $pdo = Database::connect();
    // replace_with_your_table_name, on this project I use the table name 'esp32_table_dht11_leds_update'.
    // This table is used to store DHT11 sensor data updated by ESP32. 
    // This table is also used to store the state of the LEDs, the state of the LEDs is controlled from the "home.php" page. 
    // To store data, this table is operated with the "UPDATE" command, so this table contains only one row.
    $sql = 'SELECT * FROM esp32_table_dht11_leds_update WHERE id="' . $id . '"';
    foreach ($pdo->query($sql) as $row) {
      $date = date_create($row['date']);
      $dateFormat = date_format($date,"d-m-Y");
      
      $myObj->id = $row['id'];
      $myObj->temperature1 = $row['temperature1'];
      $myObj->humidity1 = $row['humidity1'];
      $myObj->status_read_sensor_dht1 = $row['status_read_sensor_dht1'];
      $myObj->temperature2 = $row['temperature2'];
      $myObj->humidity2 = $row['humidity2'];
      $myObj->status_read_sensor_dht2 = $row['status_read_sensor_dht2'];
      $myObj->temperature3 = $row['temperature3'];
      $myObj->humidity3 = $row['humidity3'];
      $myObj->status_read_sensor_dht3 = $row['status_read_sensor_dht3'];
      $myObj->temperature4 = $row['temperature4'];
      $myObj->humidity4 = $row['humidity4'];
      $myObj->status_read_sensor_dht4 = $row['status_read_sensor_dht4'];
      $myObj->co21 = $row['co21'];
      $myObj->status_read_MQ135_1 = $row['status_read_MQ135_1'];
      $myObj->co22 = $row['co22'];
      $myObj->status_read_MQ135_2 = $row['status_read_MQ135_2'];
      $myObj->ls_time = $row['time'];
      $myObj->ls_date = $dateFormat;
      
      $myJSON = json_encode($myObj);
      
      echo $myJSON;
    }
    Database::disconnect();
    //........................................ 
  }
  //---------------------------------------- 
?>