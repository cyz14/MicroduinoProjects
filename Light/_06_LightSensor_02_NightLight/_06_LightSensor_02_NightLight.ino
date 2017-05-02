#include <Adafruit_NeoPixel.h>  //调用LED彩灯的库文件

#define LIGHT_VOICE   600
#define LIGHT_STATE   50

Adafruit_NeoPixel ColorLED = Adafruit_NeoPixel(1, 6, NEO_GRB + NEO_KHZ800);
//定义彩灯引脚以及数量


int state; //定义一个整数变量state
int voice; //定义一个整数变量表示声音的音量

void setup()
{
  ColorLED.begin();
  pinMode(A0, INPUT); //设置光敏传感器引脚为输入状态
  pinMode(A2, INPUT); //设置声敏传感器引脚为输入状态
  Serial.begin(9600); //设置串口波特率为9600
}
void loop()
{
  state = analogRead(A0);
  voice = analogRead(A2);
  Serial.print("state:");
  Serial.print(state);
  Serial.print("\tvoice:");
  Serial.println(voice);
  delay(100);
  if (state < LIGHT_STATE) { //当state的值小于 LIGHT_STATE 时，亮红灯
    if (voice > LIGHT_VOICE) { // 当音量的值小于阈值时
      ColorLED.setPixelColor(0, ColorLED.Color(255, 0, 0));  //设置彩灯颜色为红色
      ColorLED.show();  //显示彩灯效果  
      delay(5000);
    }
  } else { //否则，关灯
    ColorLED.setPixelColor(0, ColorLED.Color(0, 0, 0));  //设置彩灯颜色为无色
    ColorLED.show();  //显示彩灯效果
  }
}
