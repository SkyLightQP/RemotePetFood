#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <Servo.h> 
 
Servo myservo; 
Servo myservo2; 
ESP8266WebServer server(80);
String url = "https://raw.githubusercontent.com/SkyLightQP/RemotePetFood/master/index.html";

void setup() {
 // put your setup code here, to run once:
  Serial.begin(115200);
  myservo.attach(4); // D2
  myservo2.attach(5); // D1
  // 연결 완료 까지 대기
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(WiFi.SSID());
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }

  //접속별 동작 설정                          
  server.on("/", [](){
    sendHtml(url);
  });
  server.on("/open1", [](){
    myservo.write(160);  
    sendHtml(url);
  });
  server.on("/close1", [](){
    myservo.write(130);  
    sendHtml(url);
  });
  server.on("/auto1", [](){
    myservo.write(160);  
    delay(600);
    myservo.write(130);  
    sendHtml(url);
  });
   server.on("/open2", [](){
    myservo2.write(160);  
    sendHtml(url);
  });
  server.on("/close2", [](){
    myservo2.write(130);  
    sendHtml(url);
  });
  server.on("/auto2", [](){
    myservo2.write(160);  
    delay(600);
    myservo2.write(130);  
    sendHtml(url);
  });
  //서버 사용을 시작합니다.
  server.begin();
  Serial.println("HTTP server started");
}

void loop(void){
  server.handleClient();//클라이언트 접속을 관리합니다.
}

void sendHtml(String url){
  String html = "";
  html += "<html><script src=\"http://www.w3schools.com/lib/w3data.js\"></script>";
  html += "<body><div w3-include-html=\"" + url + "\"></div>";
  html += "<script>w3IncludeHTML();</script></body></html>";
   server.send(200, "text/html", html);
}
