// ex02_millis_1hz.ino
// ESP32板载LED引脚
const int ledPin = 2;
// 定时时间戳
unsigned long lastFlashTime = 0;
// 500ms翻转一次，亮500ms、灭500ms，整体1Hz闪烁
const unsigned long flashInterval = 500;
// LED状态标记
bool ledState = LOW;

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, ledState);
}

void loop() {
  // 获取当前系统运行毫秒
  unsigned long currentTime = millis();

  // 判断是否达到翻转间隔
  if (currentTime - lastFlashTime >= flashInterval) {
    // 翻转LED状态
    ledState = !ledState;
    digitalWrite(ledPin, ledState);

    // 串口打印调试信息
    if (ledState == HIGH) {
      Serial.println("LED ON");
    } else {
      Serial.println("LED OFF");
    }

    // 更新上次执行时间
    lastFlashTime = currentTime;
  }
  // 此处可以添加其他并行任务，不会被延时阻塞
