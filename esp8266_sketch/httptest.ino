#include <Wire.h>






#include "DHT.h"

#define DHTPIN 4
#define DHTTYPE DHT11 
DHT dht(DHTPIN, DHTTYPE);

#include <ESP8266WiFi.h>
#include <HttpClient.h>




const char* ssid     = "Hackerspace";
const char* password = "makehackmodify";

// Name of the server we want to connect to
const char kHostname[] = "95.142.75.220";
// Path to download (this is the bit after the hostname in the URL
// that you want to download
const char kPath[] = "/index.php";
// Number of milliseconds to wait without receiving any data before we give up
const int kNetworkTimeout = 30*1000;
// Number of milliseconds to wait if no data is available before trying again
const int kNetworkDelay = 1000;
//StaticJsonBuffer<8192> jsonBuffer;
//const char *spacestatus;


void setup() {
  Wire.pins(12,13);
  Wire.begin();
  
  pinMode(5,OUTPUT);
  digitalWrite(5,HIGH);
  Serial.begin(9600);
  //Serial1.begin(9600);
  dht.begin();
  delay(10);
  
  // We start by connecting to a WiFi network

  //Serial.println();
  //Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  Serial.println();
  delay(5000);
  //Serial1.println("D1");
  //delay(10000);
  
}

int value = 0;
int err =0;
char *responseBuffer_c;
void loop() {
  WiFiClient client;
  HttpClient http(client);
  delay(10000);
  //++value;

  Serial.print("connecting to ");
  Serial.println(kHostname);
  

  
  err = http.get(kHostname, 8080, "/index.php?field=status");
  if (err == 0)
  {
    Serial.println("started spaceRequest ok");

    err = http.responseStatusCode();
    if (err  < 300&& err >=200)
    {
      Serial.print("Got status code: ");
      Serial.println(err);

      // Usually you'd check that the response code is 200 or a
      // similar "success" code (200-299) before carrying on,
      // but we'll print out whatever response we get

      err = http.skipResponseHeaders();
      if (err >= 0)
      {
        int bodyLen = http.contentLength();
        Serial.print("Content length is: ");
        Serial.println(bodyLen);
        Serial.println();
        //Serial.println("Body returned follows:");
      
        // Now we've got to the body, so we can print it out
        unsigned long timeoutStart = millis();
        char c;
        String responseBuffer="";
        char screenbuffer[16]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        // Whilst we haven't timed out & haven't reached the end of the body
        while ( (http.connected() || http.available()) &&
               ((millis() - timeoutStart) < kNetworkTimeout) )
        {
            if (http.available())
            {
                c = http.read();
                // Print out this character
                //Serial.print(c);
                responseBuffer += c;
                bodyLen--;
                // We read something, reset the timeout counter
                timeoutStart = millis();
            }
            else
            {
                // We haven't got any data, so let's pause to allow some to
                // arrive
                delay(kNetworkDelay);
            }
            
              
        }
        //Serial.println(responseBuffer);
            if(responseBuffer.charAt(0)=='1'){
              digitalWrite(5,LOW);
              
              //Wire.write("D1");
              
              
              delay(1000);
              Wire.beginTransmission(4);
              Wire.write("W\t0\t0\tSpace opened!   ");
              Wire.endTransmission();
              /*
              if (responseBuffer.length()>18){
                int pages=ceil((responseBuffer.length()-2)/16);
                for (int i = 1 ; i <= pages ; i++){
                  Serial1.print("W\t0\t1\t");
                  Serial1.println(responseBuffer.substring(2*pages,18*pages));
                  delay(5000);
                }
              }else{
              */
              if (responseBuffer.length()>2){
                Wire.beginTransmission(4);
                Wire.write("W\t0\t1\t");
                responseBuffer.substring(2,18).toCharArray(screenbuffer,16);
                Wire.write(screenbuffer);
                Wire.endTransmission();
              }
            }else if(responseBuffer.charAt(0)=='0'){
              digitalWrite(5,HIGH);
              //Serial1.println("\nD1");
              //delay(1000);
              //Serial1.println("W\t0\t0\tSpace closed!   ");
              //Serial1.println("W\t0\t1\t                ");
            }else{
              digitalWrite(5,LOW);
              delay(1000);
              Wire.beginTransmission(4);
              Wire.write("W\t0\t0\tSpaceAPI Error!!");
              Wire.endTransmission();
              delay(1);
              Wire.beginTransmission(4);
              Wire.write("W\t0\t1\tScript broken!  ");
              Wire.endTransmission();
            }       
        
      }
      else
      {
        //Serial.print("Failed to skip response headers: ");
        //Serial.println(err);
      }
    }
    else
    {    
      //Serial.print("Getting response failed: ");
      //Serial.println(err);
      Serial1.println("D1");
      delay(100);
      Wire.beginTransmission(4);
      Wire.write("W\t0\t0\tSpaceAPI Error!!");
      Wire.endTransmission();
      delay(1);
      Wire.beginTransmission(4);
      Wire.write("W\t0\t1\tHTTP error !!   ");
      Wire.endTransmission();
      //Serial1.print("W\t0\t1\tHTTP ");
      //Serial1.println(err,DEC);
    }
  }
  else
  {
    Serial.print("Connect failed: ");
    Serial.println(err);
  }
  http.stop();
  
  delay(10000);
  err = http.get(kHostname, 8080, "/index.php?field=time");
  if (err == 0)
  {
    Serial.println("started timeRequest ok");

    err = http.responseStatusCode();
    if (err  < 300&& err >=200)
    {
      Serial.print("Got status code: ");
      Serial.println(err);

      // Usually you'd check that the response code is 200 or a
      // similar "success" code (200-299) before carrying on,
      // but we'll print out whatever response we get

      err = http.skipResponseHeaders();
      if (err >= 0)
      {
        int bodyLen = http.contentLength();
        Serial.print("Content length is: ");
        Serial.println(bodyLen);
        Serial.println();
        //Serial.println("Body returned follows:");
      
        // Now we've got to the body, so we can print it out
        unsigned long timeoutStart = millis();
        char c;
        String responseBuffer="";
        char screenbuffer[16]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        // Whilst we haven't timed out & haven't reached the end of the body
        while ( (http.connected() || http.available()) &&
               ((millis() - timeoutStart) < kNetworkTimeout) )
        {
            if (http.available())
            {
                c = http.read();
                // Print out this character
                //Serial.print(c);
                responseBuffer += c;
                bodyLen--;
                // We read something, reset the timeout counter
                timeoutStart = millis();
            }
            else
            {
                // We haven't got any data, so let's pause to allow some to
                // arrive
                delay(kNetworkDelay);
            }
              
              
        }
        //Serial.println(responseBuffer);
        //Serial1.println("W\t0\t0\t                ");
        Wire.beginTransmission(4);
        Wire.write("W\t0\t0\t");
        responseBuffer.substring(2,18).toCharArray(screenbuffer,16);
        Wire.write(screenbuffer);
        Wire.endTransmission();
        //Serial1.println(responseBuffer);
        float h = dht.readHumidity();
        // Read temperature as Celsius (the default)
        float t = dht.readTemperature();
        if (isnan(h) || isnan(t)) {
          Serial.println("Failed to read from DHT sensor!");
          return;
        }

        responseBuffer=String("");
        responseBuffer+=t;
        responseBuffer+=" *C ";
        responseBuffer+=h;
        responseBuffer+=" %";
        responseBuffer.toCharArray(screenbuffer,16);
        Wire.beginTransmission(4);
        Wire.write("W\t0\t1\t");
        Wire.write(screenbuffer);
        Wire.endTransmission();
        
        
      }
      else
      {
        //Serial.print("Failed to skip response headers: ");
        //Serial.println(err);
      }
    }
    else
    {    
      //Serial.print("Getting response failed: ");
      //Serial.println(err);
      Serial1.println("D1");
      delay(100);
      Wire.beginTransmission(4);
      Wire.write("W\t0\t0\tSpaceAPI Error!!");
      Wire.endTransmission();
      delay(1);
      Wire.beginTransmission(4);
      Wire.write("W\t0\t1\tHTTP error !!   ");
      Wire.endTransmission();
    }
  }
  else
  {
    Serial.print("Connect failed: ");
    Serial.println(err);
  }
  http.stop();

  //Serial.println();
  //Serial.println("closing connection");
}

