#include <WiFi.h>
#include <WebServer.h>

const char* ssid     = "Pura 70 Pro Max Ultra";
const char* password = "20240611";

#define TOUCH_PIN T0
WebServer server(80);

// 网页：自动轮询接口，实时刷新触摸数值
String htmlPage = R"HTML(
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>触摸传感器实时仪表盘</title>
<style>
body{text-align:center;margin-top:120px;font-size:30px;}
#data{font-size:80px;color:#0066ff;font-weight:bold;}
</style>
</head>
<body>
<h2>触摸传感器实时数值</h2>
<div id="data">0</div>
<script>
// 每100ms拉取一次传感器数据
function getData(){
  fetch("/sensor")
  .then(res=>res.text())
  .then(num=>{
    document.getElementById("data").innerText = num;
  });
}
setInterval(getData, 100);
</script>
</body>
</html>
)HTML";

void handleRoot(){
  server.send(200, "text/html", htmlPage);
}

// 传感器数据接口，返回原始touch值
void handleSensor(){
  int val = touchRead(TOUCH_PIN);
  server.send(200, "text/plain", String(val));
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) delay(500);
  Serial.println("仪表盘IP："+WiFi.localIP().toString());
  server.on("/", handleRoot);
  server.on("/sensor", handleSensor);
  server.begin();
}

void loop() {
  server.handleClient();
}