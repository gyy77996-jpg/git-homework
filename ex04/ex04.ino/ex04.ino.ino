// ex05 多档位触摸调速呼吸灯
#define TOUCH_PIN T0
#define LED_PIN 2

// 触摸自锁变量
bool lastTouch = false;
unsigned long debounceTime = 50;
unsigned long lastDebounce = 0;

// 呼吸档位：1/2/3档，对应步进速度
int speedLevel = 1;
int step;    // PWM递增步长
int brightness = 0;
int fadeDir = 1; // 1变亮，-1变暗

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(115200);
  analogWrite(LED_PIN, brightness);
}

void loop() {
  unsigned long now = millis();
  int touchVal = touchRead(TOUCH_PIN);
  bool curTouch = (touchVal < 30);

  // 触摸切换档位逻辑
  if (now - lastDebounce > debounceTime) {
    if (curTouch == true && lastTouch == false) {
      speedLevel++;
      if (speedLevel > 3) speedLevel = 1; // 循环1-3档
      lastDebounce = now;
    }
  }
  lastTouch = curTouch;

  // 根据档位设置呼吸步长
  switch(speedLevel){
    case 1: step = 1; break; // 慢
    case 2: step = 3; break; // 中
    case 3: step = 6; break; // 快
  }

  // PWM呼吸渐变
  brightness += fadeDir * step;
  if (brightness <= 0 || brightness >= 255) {
    fadeDir = -fadeDir;
  }
  analogWrite(LED_PIN, brightness);
  delay(10);
}