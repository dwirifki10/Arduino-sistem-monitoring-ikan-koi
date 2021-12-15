// libraries for connection to API
#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>

// libraries for celcius sensor
#include <DallasTemperature.h>
#include <OneWire.h>

#define ONE_WIRE_BUS 4  // D1 pin of ESP8266

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire); 

// variables for ph sensor
const int ph_Pin  = A0; // pin analog
float Po = 0; 
float PH_step;
int nilai_analog_PH;
double TeganganPh;

// variables for hostspot
const char *ssid = "Controller";  // name wifi
const char *password = "dwirifki24116"; // pass wifi 


// for sensor ph calibration 
float PH4 = 3.226;
float PH7 = 2.691;

void setup()
{
  delay(1000);
  Serial.begin(115200);
  WiFi.mode(WIFI_OFF);        
  delay(1000);
  WiFi.mode(WIFI_STA); 
  
  WiFi.begin(ssid, password); 
  Serial.println("");

  Serial.print("Connecting");
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  // IP address assigned to your ESP8266

  // initialize ph sensor
  pinMode (ph_Pin, INPUT);
}

void loop()
{
  if (Serial.available()){
    int i = 0;
    while(true){
      // displaying number
      Serial.print("No : ");
      Serial.println(i + 1);
      // call method sendData
      sendData();
      i++;
      // delay for 30 seconds if i in mod 4 == 0      
      if(i % 4 == 0){
        Serial.println("Sleep for 30s, waiting for the next request");
        delay(30000);
      }
    }  
  }
}

void sendData()
{
  nilai_analog_PH = analogRead(ph_Pin);
  Serial.print("Nilai ADC Ph : ");
  Serial.println(nilai_analog_PH);
  TeganganPh = 3.3 / 1024.0 * nilai_analog_PH;
  Serial.print("Tegangan Ph : ");
  Serial.println(TeganganPh, 3);

  PH_step = (PH4 - PH7) / 3;
  Po = 7.00 + ((PH7 - TeganganPh) / PH_step);
  Serial.print("Nilai PH cairan : ");
  Serial.println(Po, 2);

  sensors.requestTemperatures();
  Serial.print("Nilai Temperature : ");
  Serial.println(sensors.getTempCByIndex(0)); 
  delay(3000);
}
