#include <WiFi.h>
#include <HTTPClient.h>
#include <Arduino_JSON.h>
#include "DHT.h"
//======================================== 

//======================================== DHT sensor settings (DHT11).
DHT dht1(25, DHT22);
DHT dht2(26, DHT22);
DHT dht3(27, DHT22);
DHT dht4(33, DHT22);
//========================================

// // Defines the Digital Pin of the "On Board LED".
// #define ON_Board_LED 2 

// // Defines GPIO 13 as LED_1.
// #define LED_01 13 

// // Defines GPIO 12 as LED_2.
// #define LED_02 12 

//======================================== SSID and Password of your WiFi router.
const char* ssid = "password";
const char* password = "LunaSnow";
//======================================== 

//======================================== Variables for HTTP POST request data.
String postData = ""; //--> Variables sent for HTTP POST request data.
String payload = "";  //--> Variable for receiving response from HTTP POST.
//======================================== 

//======================================== Variables for DHT11 sensor data.
float send_Temp1;
int send_Humd1;
float send_Temp2;
int send_Humd2;
float send_Temp3;
int send_Humd3;
float send_Temp4;
int send_Humd4;
String send_Status_Read_DHT1 = "";
String send_Status_Read_DHT2 = "";
String send_Status_Read_DHT3 = "";
String send_Status_Read_DHT4 = "";
//======================================== 

//________________________________________________________________________________ Subroutine to control LEDs after successfully fetching data from database.
// void control_LEDs() {
//   Serial.println();
//   Serial.println("---------------control_LEDs()");
//   JSONVar myObject = JSON.parse(payload);

//   // JSON.typeof(jsonVar) can be used to get the type of the var
//   if (JSON.typeof(myObject) == "undefined") {
//     Serial.println("Parsing input failed!");
//     Serial.println("---------------");
//     return;
//   }

//   if (myObject.hasOwnProperty("LED_01")) {
//     Serial.print("myObject[\"LED_01\"] = ");
//     Serial.println(myObject["LED_01"]);
//   }

//   if (myObject.hasOwnProperty("LED_02")) {
//     Serial.print("myObject[\"LED_02\"] = ");
//     Serial.println(myObject["LED_02"]);
//   }

//   if(strcmp(myObject["LED_01"], "ON") == 0)   {digitalWrite(LED_01, HIGH);  Serial.println("LED 01 ON"); }
//   if(strcmp(myObject["LED_01"], "OFF") == 0)  {digitalWrite(LED_01, LOW);   Serial.println("LED 01 OFF");}
//   if(strcmp(myObject["LED_02"], "ON") == 0)   {digitalWrite(LED_02, HIGH);  Serial.println("LED 02 ON"); }
//   if(strcmp(myObject["LED_02"], "OFF") == 0)  {digitalWrite(LED_02, LOW);   Serial.println("LED 02 OFF");}

//   Serial.println("---------------");
// }
//________________________________________________________________________________ 

// ________________________________________________________________________________ Subroutine to read and get data from the DHT11 sensor.
void get_DHT11_sensor_data() {
  Serial.println();
  Serial.println("-------------get_DHT11_sensor_data()");
  
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  
  // Read temperature as Celsius (the default)
  send_Temp1 = dht1.readTemperature();
  send_Temp2 = dht2.readTemperature();
  send_Temp3 = dht3.readTemperature();
  send_Temp4 = dht4.readTemperature();
  
  // Read Humidity
  send_Humd1 = dht1.readHumidity();
  send_Humd2 = dht2.readHumidity();
  send_Humd3 = dht3.readHumidity();
  send_Humd4 = dht4.readHumidity();
  
  // Read temperature as Fahrenheit (isFahrenheit = true)
  // float ft = dht11_sensor.readTemperature(true);

  // Check if any reads failed.
  if (isnan(send_Temp1) || isnan(send_Humd1)) {
    Serial.println("Failed to read from DHT1 sensor!");
    send_Temp1 = 0.00;
    send_Humd1 = 0;
    send_Status_Read_DHT1 = "FAILED";
  } else {
    send_Status_Read_DHT1 = "SUCCEED";
  }
  if (isnan(send_Temp2) || isnan(send_Humd2)) {
    Serial.println("Failed to read from DHT2 sensor!");
    send_Temp2 = 0.00;
    send_Humd2 = 0;
    send_Status_Read_DHT2 = "FAILED";
  } else {
    send_Status_Read_DHT2 = "SUCCEED";
  }
  if (isnan(send_Temp3) || isnan(send_Humd3)) {
    Serial.println("Failed to read from DHT3 sensor!");
    send_Temp3 = 0.00;
    send_Humd3 = 0;
    send_Status_Read_DHT3 = "FAILED";
  } else {
    send_Status_Read_DHT3 = "SUCCEED";
  }
  if (isnan(send_Temp4) || isnan(send_Humd4)) {
    Serial.println("Failed to read from DHT4 sensor!");
    send_Temp4 = 0.00;
    send_Humd4 = 0;
    send_Status_Read_DHT4 = "FAILED";
  } else {
    send_Status_Read_DHT4 = "SUCCEED";
  }
  
  Serial.printf("Temperature1 : %.2f °C\n", send_Temp1);
  Serial.printf("Humidity1 : %d %%\n", send_Humd1);
  Serial.printf("Status Read DHT1 Sensor : %s\n", send_Status_Read_DHT1);
  Serial.printf("Temperature2 : %.2f °C\n", send_Temp2);
  Serial.printf("Humidity2 : %d %%\n", send_Humd2);
  Serial.printf("Status Read DHT2 Sensor : %s\n", send_Status_Read_DHT2);
  Serial.printf("Temperature3 : %.2f °C\n", send_Temp3);
  Serial.printf("Humidity3 : %d %%\n", send_Humd3);
  Serial.printf("Status Read DHT3 Sensor : %s\n", send_Status_Read_DHT3);
  Serial.printf("Temperature4 : %.2f °C\n", send_Temp4);
  Serial.printf("Humidity4 : %d %%\n", send_Humd4);
  Serial.printf("Status Read DHT4 Sensor : %s\n", send_Status_Read_DHT4);
  Serial.println("-------------");
}
// ________________________________________________________________________________

//________________________________________________________________________________ VOID SETUP()
void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(115200); //--> Initialize serial communications with the PC.

  // pinMode(ON_Board_LED,OUTPUT); //--> On Board LED port Direction output.
  // pinMode(LED_01,OUTPUT); //--> LED_01 port Direction output.
  // pinMode(LED_02,OUTPUT); //--> LED_02 port Direction output.
  
  // digitalWrite(ON_Board_LED, HIGH); //--> Turn on Led On Board.
  // digitalWrite(LED_01, HIGH); //--> Turn on LED_01.
  // digitalWrite(LED_02, HIGH); //--> Turn on LED_02.

  // delay(2000);

  // digitalWrite(ON_Board_LED, LOW); //--> Turn off Led On Board.
  // digitalWrite(LED_01, LOW); //--> Turn off Led LED_01.
  // digitalWrite(LED_02, LOW); //--> Turn off Led LED_02.

  //---------------------------------------- Make WiFi on ESP32 in "STA/Station" mode and start connecting to WiFi Router/Hotspot.
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  //---------------------------------------- 
  
  Serial.println();
  Serial.println("-------------");
  Serial.print("Connecting");

  //---------------------------------------- The process of connecting the WiFi on the ESP32 to the WiFi Router/Hotspot.
  // The process timeout of connecting ESP32 with WiFi Hotspot / WiFi Router is 20 seconds.
  // If within 20 seconds the ESP32 has not been successfully connected to WiFi, the ESP32 will restart.
  // I made this condition because on my ESP32, there are times when it seems like it can't connect to WiFi, so it needs to be restarted to be able to connect to WiFi.

  int connecting_process_timed_out = 20; //--> 20 = 20 seconds.
  connecting_process_timed_out = connecting_process_timed_out * 2;
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(2000);
    //........................................ Make the On Board Flashing LED on the process of connecting to the wifi router.
    // digitalWrite(ON_Board_LED, HIGH);
    // delay(250);
    // digitalWrite(ON_Board_LED, LOW);
    // delay(250);
    //........................................ 

    //........................................ Countdown "connecting_process_timed_out".
    // if(connecting_process_timed_out > 0) connecting_process_timed_out--;
    // if(connecting_process_timed_out == 0) {
    //   delay(1000);
    //   ESP.restart();
    // }
    //........................................ 
  }
  //---------------------------------------- 
  
  // digitalWrite(ON_Board_LED, LOW); //--> Turn off the On Board LED when it is connected to the wifi router.
  
  //---------------------------------------- If successfully connected to the wifi router, the IP Address that will be visited is displayed in the serial monitor
  Serial.println();
  Serial.print("Successfully connected to : ");
  Serial.println(ssid);
  //Serial.print("IP address: ");
  //Serial.println(WiFi.localIP());
  Serial.println("-------------");
  //---------------------------------------- 

  // Setting up the DHT sensor (DHT11).
  dht1.begin();
  dht2.begin();
  dht3.begin();
  dht4.begin();


  delay(2000);
}
//________________________________________________________________________________ 

//________________________________________________________________________________ VOID LOOP()
void loop() {
  // put your main code here, to run repeatedly

  //---------------------------------------- Check WiFi connection status.
  if(WiFi.status()== WL_CONNECTED) {
    HTTPClient http;  //--> Declare object of class HTTPClient.
    int httpCode;     //--> Variables for HTTP return code.
    
    //........................................ Process to get LEDs data from database to control LEDs.
    postData = "id=esp32_01";
    payload = "";
  
    // digitalWrite(ON_Board_LED, HIGH);
    Serial.println();
    Serial.println("---------------getdata.php");
    // In this project I use local server or localhost with XAMPP application.
    // So make sure all PHP files are "placed" or "saved" or "run" in the "htdocs" folder.
    // I suggest that you create a new folder for this project in the "htdocs" folder.
    // The "htdocs" folder is in the "xampp" installation folder.
    // The order of the folders I recommend:
    // xampp\htdocs\your_project_folder_name\phpfile.php
    //
    // ESP32 accesses the data bases at this line of code: 
    // http.begin("http://REPLACE_WITH_YOUR_COMPUTER_IP_ADDRESS/REPLACE_WITH_PROJECT_FOLDER_NAME_IN_htdocs_FOLDER/getdata.php");
    // REPLACE_WITH_YOUR_COMPUTER_IP_ADDRESS = there are many ways to see the IP address, you can google it. 
    //                                         But make sure that the IP address used is "IPv4 address".
    // Example : http.begin("http://192.168.0.0/ESP32_MySQL_Database/Final/getdata.php");
    http.begin("http://192.168.100.33/ESP32_MySQL_Database/Final/getdata.php");  //--> Specify request destination
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");        //--> Specify content-type header
   
    httpCode = http.POST(postData); //--> Send the request
    payload = http.getString();     //--> Get the response payload
  
    Serial.print("httpCode : ");
    Serial.println(httpCode); //--> Print HTTP return code
    Serial.print("payload  : ");
    Serial.println(payload);  //--> Print request response payload
    
    http.end();  //--> Close connection
    Serial.println("---------------");
    // digitalWrite(ON_Board_LED, LOW);
    //........................................ 

    // Calls the control_LEDs() subroutine.
    // control_LEDs();
    
    delay(1000);

    // Calls the get_DHT11_sensor_data() subroutine.
    get_DHT11_sensor_data();
  
    //........................................ The process of sending the DHT11 sensor data and the state of the LEDs to the database.
    // String LED_01_State = "";
    // String LED_02_State = "";

    // if (digitalRead(LED_01) == 1) LED_01_State = "ON";
    // if (digitalRead(LED_01) == 0) LED_01_State = "OFF";
    // if (digitalRead(LED_02) == 1) LED_02_State = "ON";
    // if (digitalRead(LED_02) == 0) LED_02_State = "OFF";
    
    postData = "id=esp32_01";
    postData += "&temperature1=" + String(send_Temp1);
    postData += "&humidity1=" + String(send_Humd1);
    postData += "&status_read_sensor_dht1=" + send_Status_Read_DHT1;
    postData += "&temperature2=" + String(send_Temp2);
    postData += "&humidity2=" + String(send_Humd2);
    postData += "&status_read_sensor_dht2=" + send_Status_Read_DHT2;
    postData += "&temperature3=" + String(send_Temp3);
    postData += "&humidity3=" + String(send_Humd3);
    postData += "&status_read_sensor_dht3=" + send_Status_Read_DHT3;
    postData += "&temperature4=" + String(send_Temp4);
    postData += "&humidity4=" + String(send_Humd4);
    postData += "&status_read_sensor_dht4=" + send_Status_Read_DHT4;
    // postData += "&led_01=" + LED_01_State;
    // postData += "&led_02=" + LED_02_State;
    payload = "";
  
    // digitalWrite(ON_Board_LED, HIGH);
    Serial.println();
    Serial.println("---------------updateDHT11data_and_recordtable.php");
    // Example : http.begin("http://192.168.0.0/ESP32_MySQL_Database/Final/updateDHT11data_and_recordtable.php");
    http.begin("http://192.168.100.33/ESP32_MySQL_Database/Final/updateDHT11data_and_recordtable.php");  //--> Specify request destination
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");  //--> Specify content-type header
   
    httpCode = http.POST(postData); //--> Send the request
    payload = http.getString();  //--> Get the response payload
  
    Serial.print("httpCode : ");
    Serial.println(httpCode); //--> Print HTTP return code
    Serial.print("payload  : ");
    Serial.println(payload);  //--> Print request response payload
    
    http.end();  //Close connection
    Serial.println("---------------");
    // digitalWrite(ON_Board_LED, LOW);
    //........................................ 
    
    delay(60000);
  }
  //---------------------------------------- 
}