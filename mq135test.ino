#include <WiFi.h>
#include <HTTPClient.h>
#include <Arduino_JSON.h>
#include "DHT.h"
#include <MQ135.h>
//======================================== 

//======================================== sensor settings.
DHT dht1(25, DHT22);
DHT dht2(26, DHT22);
DHT dht3(27, DHT22);
DHT dht4(33, DHT22);
MQ135 gasSensor1 = MQ135(18);
MQ135 gasSensor2 = MQ135(19);
//========================================


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

// air quality
float co21;
String send_status_Read_MQ135_1 = "";
float co22;
String send_status_Read_MQ135_2 = "";
//======================================== 


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

  // Read air quality
  co21 = gasSensor1.getPPM();
  co22 = gasSensor2.getPPM();
  
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
  if (isnan(co21)) {
    Serial.println("Failed to read from MQ135_1 sensor!");
    co21 = 0.00;
    send_status_Read_MQ135_1 = "FAILED";
  } else {
    send_status_Read_MQ135_1 = "SUCCEED";
  }
  if (isnan(co22)) {
    Serial.println("Failed to read from MQ135_2 sensor!");
    co22 = 0.00;
    send_status_Read_MQ135_2 = "FAILED";
  } else {
    send_status_Read_MQ135_2 = "SUCCEED";
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
  Serial.printf("co21 : %.2f ppm\n", co21);
  Serial.printf("Status Read MQ135_1 Sensor : %s\n", send_status_Read_MQ135_1);
  Serial.printf("co22 : %.2f ppm\n", co22);
  Serial.printf("Status Read MQ135_2 Sensor : %s\n", send_status_Read_MQ135_2);
  Serial.println("-------------");
}
// ________________________________________________________________________________

//________________________________________________________________________________ VOID SETUP()
void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(115200); //--> Initialize serial communications with the PC.

  //---------------------------------------- Make WiFi on ESP32 in "STA/Station" mode and start connecting to WiFi Router/Hotspot.
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  //---------------------------------------- 
  
  Serial.println();
  Serial.println("-------------");
  Serial.print("Connecting");

  // connect to wifi
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(2000);
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
    postData += "&co21=" + String(co21);
    postData += "&status_read_MQ135_1=" + send_status_Read_MQ135_1;
    postData += "&co22=" + String(co22);
    postData += "&status_read_MQ135_2=" + send_status_Read_MQ135_2;

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