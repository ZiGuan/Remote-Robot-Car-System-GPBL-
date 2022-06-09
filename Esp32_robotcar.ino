#include <WiFi.h>
#define RXD2 16
#define TXD2 17

const char *ssid = "Ash";
const char *password = "junan0805";

const IPAddress serverIP(160,16,84,67); // IP Address
uint16_t serverPort = 50201;         // SIT Server port

WiFiClient client; // Build connection with server

void setup()
{
    
    Serial.begin(115200);
    Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2); 
    Serial.println();

    WiFi.mode(WIFI_STA);
    WiFi.setSleep(false); // Close STA mode to increase transmit speed
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
    
        delay(500);
        Serial.print(".");
    }
    Serial.println("Connected");
    Serial.print("IP Address:");
    Serial.println(WiFi.localIP());
    Serial.println("Please enter 'f' to run the motor FORWARD, or 'b' to run the motor BACKWARD");                  
    Serial.println("or 'r' to run the motor RIGHT, or 'l' to run the motor LEFT, or 's' to STOP all motors. ");
}

int num = 0;

void loop()
{
  // put your main code here, to run repeatedly:
  Serial.println("Connect server);
  if(!client.connect(serverIP,serverPort)){
    Serial.println("Connection Failed");
    return ;
  }

    if(num == 0) {
      client.print("phone");
      Serial.println("send phone...");
      num = 1;
      Serial.println(num);
    }
    while(client.read()){
    String line = client.readStringUntil('\n');
    Serial.print("Data Reading：");
    Serial.println(line);
    Serial2.println(line);
    }
 
    delay(5000);
}
