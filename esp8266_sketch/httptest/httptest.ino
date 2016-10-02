
#include <Shifty.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

ESP8266WiFiMulti WiFiMulti;
Shifty shift; 

const char* ssid     = "Hackerspace";
const char* password = "";

// Name of the server we want to connect to
const char kHostname[] = "95.142.75.220";
// Path to download (this is the bit after the hostname in the URL
// that you want to download
const char kPath[] = "/index.php";
// Number of milliseconds to wait without receiving any data before we give up
const int kNetworkTimeout = 30*1000;
// Number of milliseconds to wait if no data is available before trying again
const int kNetworkDelay = 1000;

void writeString(uint8_t,uint8_t,const char[],uint8_t);




void setup() {
  shift.setBitCount(16);
  shift.setPins(16,5,4);
  
  
  
  //pinMode(5,OUTPUT);
  //digitalWrite(5,LOW);
  Serial.begin(9600);
  //Serial1.begin(9600);
  //dht.begin();
  delay(10);
  
  // We start by connecting to a WiFi network

  //Serial.println();
  //Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA); 
  
  WiFiMulti.addAP(ssid, password);
  
  while (WiFiMulti.run()  != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  
  delay(5000);
  //Serial1.println("D1");
  //delay(10000);
  
}
int spaceState=0;
int value = 0;
int err =0;

void loop() {
  
  HTTPClient http;
  delay(1000);
  //++value;

  Serial.print("connecting to ");
  Serial.println(kHostname);
  

  http.begin("http://hackerspacehb.appspot.com/v2/status");
  //err = http.get(kHostname, 8080, "/index.php?field=status");
  err = http.GET();
  if (err > 0)
  {
    Serial.println("started spaceRequest ok");
    Serial.print("Got status code: ");
    Serial.println(err);
    
    if (err  == HTTP_CODE_OK)
    {
      int bodyLen = http.getSize();
      Serial.print("Content length is: ");
      Serial.println(bodyLen);
      Serial.println();
      //Serial.println("Body returned follows:");
    
      // Now we've got to the body, so we can print it out
      unsigned long timeoutStart = millis();
      char c;
      std::unique_ptr<char[]> responseBuffer(new char[bodyLen]);
      String payload=http.getString();
      payload.toCharArray(responseBuffer.get(),bodyLen);
      StaticJsonBuffer<8192> jsonBuffer;
      JsonObject& json = jsonBuffer.parseObject(responseBuffer.get());
      if (!json.success()) {
        Serial.println("Failed to parse SpaceAPI JSON!");
      }else{
        if(json["open"]==true){
          writeString(1,1,"Space open!     ",16);
          writeString(1,2,json["status"],constrain(strlen(json["status"]),0,16));
        }else if(json["open"]==false){
          writeString(1,1,"Space closed!   ",16);
          writeString(1,2,json["status"],constrain(strlen(json["status"]),0,16));
        }
      }   
    }
  }
  else
  {
    Serial.print("Connect failed: ");
    Serial.println(err);
  }
  http.end();
  
  delay(10000);
  
  
  http.begin(kHostname, 8080, "/index.php?field=time");
  err = http.GET();
  if (err>0){
    Serial.println("started timeRequest ok");
    Serial.print("Got status code: ");
    Serial.println(err);
    if (err=HTTP_CODE_OK)
    {      
      int bodyLen = http.getSize();
      Serial.print("Content length is: ");
      Serial.println(bodyLen);
      Serial.println();
      String responseBuffer=http.getString();;
      writeString(1,2,responseBuffer.substring(2,18).c_str(),constrain(responseBuffer.substring(2,18).length(),0,16));
    }
  }
  else
  {
    Serial.print("Connect failed: ");
    Serial.println(err);
  }
  http.end();
  
  //Serial.println();
  //Serial.println("closing connection");
}


