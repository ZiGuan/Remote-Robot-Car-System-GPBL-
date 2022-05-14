#include <WiFi.h>
#define RXD2 16
#define TXD2 17

const char *ssid = "Ash";
const char *password = "junan0805";

const IPAddress serverIP(160,16,84,67); //欲访问的地址
uint16_t serverPort = 50201;         //服务器端口号

WiFiClient client; //声明一个客户端对象，用于与服务器进行连接

void setup()
{
    
    Serial.begin(115200);
    Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2); 
    Serial.println();

    WiFi.mode(WIFI_STA);
    WiFi.setSleep(false); //关闭STA模式下wifi休眠，提高响应速度
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
  Serial.println("連線服務端");
  if(!client.connect(serverIP,serverPort)){
    Serial.println("連線失敗");
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
    Serial.print("读取到数据：");
    Serial.println(line);
    Serial2.println(line);
    }
 
    delay(5000);
}
