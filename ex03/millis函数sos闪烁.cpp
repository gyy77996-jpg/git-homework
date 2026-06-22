const int ledPin = 2;

// 时序参数和示例完全一致
const unsigned long shortOn = 200;
const unsigned long shortOffGap = 200;
const unsigned long longOn = 600;
const unsigned long letterGap = 500;
const unsigned long fullEndPause = 2000;

unsigned long lastTime = 0;
int runState = 0;
int flashCount = 0;
bool ledLightOn = false;

// 封装统一开关函数：代码写 HIGH=亮，LOW=灭，自动适配反相硬件
void setLamp(bool turnOn)
{
  if (turnOn)
  {
    digitalWrite(ledPin, LOW);  // 外接灯泡低电平亮
  }
  else
  {
    digitalWrite(ledPin, HIGH); // 外接灯泡高电平灭
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  setLamp(false); // 初始熄灭
}

void loop() {
  unsigned long now = millis();
  unsigned long timePass = now - lastTime;

  switch (runState) {
    // 第一段S：3次短闪
    case 0:
      if (!ledLightOn) {
        if (timePass >= shortOffGap) {
          ledLightOn = true;
          setLamp(true);
          lastTime = now;
        }
      } else {
        if (timePass >= shortOn) {
          ledLightOn = false;
          setLamp(false);
          flashCount++;
          lastTime = now;
          if (flashCount >= 3) {
            flashCount = 0;
            runState = 1;
            lastTime = now;
          }
        }
      }
      break;

    // S-O间隔500ms
    case 1:
      if (timePass >= letterGap) {
        runState = 2;
      }
      break;

    // O：3次长闪
    case 2:
      if (!ledLightOn) {
        if (timePass >= shortOffGap) {
          ledLightOn = true;
          setLamp(true);
          lastTime = now;
        }
      } else {
        if (timePass >= longOn) {
          ledLightOn = false;
          setLamp(false);
          flashCount++;
          lastTime = now;
          if (flashCount >= 3) {
            flashCount = 0;
            runState = 3;
            lastTime = now;
          }
        }
      }
      break;

    // O-S间隔500ms
    case 3:
      if (timePass >= letterGap) {
        runState = 4;
      }
      break;

    // 第二段S：3次短闪
    case 4:
      if (!ledLightOn) {
        if (timePass >= shortOffGap) {
          ledLightOn = true;
          setLamp(true);
          lastTime = now;
        }
      } else {
        if (timePass >= shortOn) {
          ledLightOn = false;
          setLamp(false);
          flashCount++;
          lastTime = now;
          if (flashCount >= 3) {
            flashCount = 0;
            runState = 5;
            lastTime = now;
            setLamp(false);
            ledLightOn = false;
          }
        }
      }
      break;

    // SOS结束长停顿，全程熄灭
    case 5:
      setLamp(false);
      ledLightOn = false;
      if (timePass >= fullEndPause) {
        runState = 0;
        flashCount = 0;
        lastTime = now;
      }
      break;
  }
}
