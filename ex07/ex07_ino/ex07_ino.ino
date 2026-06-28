#include <WiFi.h>
#include <WebServer.h>

const char* ssid     = "Pura 70 Pro Max Ultra";
const char* password = "20240611";

#define LED_PIN 2
#define TOUCH_PIN T0

WebServer server(80);
bool armState = false;   // false=撤防，true=布防
bool alarmState = false; // 是否正在报警

String htmlPage = R"HTML(
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>安防报警主机</title>
<style>
button{font-size:24px;padding:15px 40px;margin:20px;}
#arm{background:#0c0;color:white;}
#disarm{background:#c00;color:white;}
</style>
</head>
<body style="text-align:center;margin-top:100px;">
<h2>安防系统控制面板</h2>
<button id="arm" onclick="fetch('/arm')">布防 ARM</button>
<button id="disarm" onclick="fetch('/disarm')">撤防 DISARM</button>
</body>
</html>
)HTML";

void handleRoot(){
  server.send(200, "text/html", htmlPage);
}

void handleArm(){
  armState = true;
  server.send(200, "text/plain", "已布防");
}

void handleDisarm(){
  armState = false;
  alarmState = false;
  digitalWrite(LED_PIN, LOW);
  server.send(200, "text/plain", "已撤防，报警复位");
}

void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) delay(500);
  Serial.println("设备IP："+WiFi.localIP().toString());
  server.on("/", handleRoot);
  server.on("/arm", handleArm);
  server.on("/disarm", handleDisarm);
  server.begin();
}

void loop() {
  server.handleClient();
  int touchVal = touchRead(TOUCH_PIN);
  bool touchNow = (touchVal < 30);
  // 布防状态下触摸触发报警锁定
  if(armState && touchNow && !alarmState){
    alarmState = true;
  }
  // 报警状态高频闪烁
  if(alarmState){
    digitalWrite(LED_PIN, HIGH);
    delay(80);
    digitalWrite(LED_PIN, LOW);
    delay(80);
  }
}