// ex06 双通道反相PWM警车交替渐变灯
#define LED_A 2
#define LED_B 4

int brightnessA = 0;
int fadeStep = 1;

void setup() {
  pinMode(LED_A, OUTPUT);
  pinMode(LED_B, OUTPUT);
}

void loop() {
  // A灯亮度递增
  brightnessA += fadeStep;
  // 到达边界反转
  if (brightnessA <= 0 || brightnessA >= 255) {
    fadeStep = -fadeStep;
  }
  // B灯与A完全反相
  int brightnessB = 255 - brightnessA;

  analogWrite(LED_A, brightnessA);
  analogWrite(LED_B, brightnessB);
  delay(8);
}