#include <Adafruit_NeoPixel.h>  //调用LED彩灯的库文件

#include <Microduino_Key.h> //调用开关的库文件

Adafruit_NeoPixel ColorLED = Adafruit_NeoPixel(1, 6, NEO_GRB + NEO_KHZ800);  //定义彩灯引脚以及数量
Key KeyA(8, INPUT_PULLUP); //定义开关参数

int i; //定义整数变量i
int r, g, b; // 当前温度颜色
int dr = 0;
int cr[] = {0, 0, 10, 10, 0, 0, -10, -10};

int timer = 0; // 计时器
int blinkStep;
boolean pressed = false; //开关是否按下
boolean lightOn = false; //灯是否亮

#define STEP1 30000 //pressed置true时的闪烁间隔
#define STEP2 3500 //pressed置false时的闪烁间隔
#define LIGHT_HEIGHT 200 //亮度传感器判断指标

#define FREQ 100 // frequency
#define STEP 10  // milliseconds

#define BLINK_RANGE 20
#define MIN_RED     15

#define HEAT_STEP   50

void lightWithColor(int red, int green, int blue) {
  ColorLED.setPixelColor(0, ColorLED.Color(red, green, blue));
  ColorLED.show();
}

void heating() {
  r += HEAT_STEP;
  if (r > 255)
    r = 255;
  lightWithColor(r, g, b);
  Serial.print("Heating...\tred:");
  Serial.println(r);
}

void cooling() {
  r--;
  if (r < MIN_RED)
    r = MIN_RED;
  lightWithColor(r, g, b);
}

void setup() {
  ColorLED.begin();  //设置彩灯初始状态
  pinMode(8, INPUT); //设置开关引脚为输入状态
  pinMode(A0, INPUT); //设置光敏传感器引脚为输入状态
  Serial.begin(9600);

  timer = 0;
  lightOn = true;
  blinkStep = STEP1;

  r = MIN_RED;
  g = 10;
  b = 0;
  lightWithColor(r, g, b); //菜单初始颜色#FFEB3B
  Serial.println(r);
}

void loop() {
  ++timer;
  if (timer >= FREQ) {
    timer = 0;
  }

//  if (timer % 10 == 0)
    cooling();

  if (timer % 10 == 0)
    dr = cr[timer % 8];
  else
    dr = 0;
  lightWithColor(r+dr, g, b);

  
  if (pressed) {
    if (analogRead(A0) > LIGHT_HEIGHT) {
      pressed = false;
      heating();
    }
  }

  if (KeyA.read() == SHORT_PRESS) {
    pressed = true;
    Serial.println("Short press.");
  }
  
  delay(STEP);
}
