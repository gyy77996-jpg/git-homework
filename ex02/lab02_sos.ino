// 定义板载LED引脚 ESP32默认GPIO2
const int ledPin = 2;

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // 发送字母S：3次短闪
  for(int i=0; i<3; i++) { 
    digitalWrite(ledPin, HIGH); 
    delay(200); 
    digitalWrite(ledPin, LOW); 
    delay(200); 
  }
  delay(500); // 字母间隔

  // 发送字母O：3次长闪
  for(int i=0; i<3; i++) { 
    digitalWrite(ledPin, HIGH); 
    delay(600); 
    digitalWrite(ledPin, LOW); 
    delay(200); 
  }
  delay(500);

  // 发送字母S：3次短闪
  for(int i=0; i<3; i++) { 
    digitalWrite(ledPin, HIGH); 
    delay(200); 
    digitalWrite(ledPin, LOW); 
    delay(200); 
  }
  delay(2000); // 整套SOS结束长停顿
}
