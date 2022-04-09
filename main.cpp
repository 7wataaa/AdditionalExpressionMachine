#include <ArduinoSTL.h>
#include <vector>
#include <string>

using namespace std;

// 真ん中4つのLED 黄色
const vector<int> A = {12, 14, 15, 16};
const int SWITCH_A = 3;
int switchAValue = 0;

// 右4つのLED 橙色
const vector<int> B = {8, 9, 10, 11};
const int SWITCH_B = 2;
int switchBValue = 0;

// 左5つのLED 白色
const vector<int> result = {17, 18, 19, 20, 21};
const int SWITCH_R = 6;
int switchRValue = 0;

void setup() {
  Serial.begin(9600);

  for (int pin : A) {
    pinMode(pin, OUTPUT);
  }
  showValue(0, A);

  for (int pin : B) {
    pinMode(pin, OUTPUT);
  }
  showValue(0, B);

  for (int pin : result) {
    pinMode(pin, OUTPUT);
  }
  showValue(0, result);

  pinMode(SWITCH_A, INPUT);
  pinMode(SWITCH_B, INPUT);
  pinMode(SWITCH_R, INPUT);
}

int aValue = 0 % 16;
int bValue = 0 % 16;
int resultValue = 0 % 32;

// valueを0~15の範囲で増加させる
void increment16(int& value) {
  value = (value + 1) % 16;
}

// valueを0~31の範囲で増加させる
void increment32(int& value) {
  value = (value + 1) % 32;
}

// pinsをすべてLOWに設定する
void clearPins(vector<int> pins) {
  for (int pin : pins) {
    digitalWrite(pin, LOW);
  }
}

// valueを2進数としてpinsに表示する
void showValue(int value, vector<int> pins) {
  clearPins(pins);

  for (int i = 0; i < (int)pins.size(); i++) {
    if (value & (1 << i)) {
      digitalWrite(pins[i], OUTPUT);
    }
  }
}

void loop() {
  bool Atrigger = switchAValue == 0 && digitalRead(SWITCH_A) == 1;
  bool Btrigger = switchBValue == 0 && digitalRead(SWITCH_B) == 1;
  bool Rtrigger = switchRValue == 0 && digitalRead(SWITCH_R) == 1;

  if(Atrigger){
    increment16(aValue);
    showValue(aValue, A);
  }

  if(Btrigger){
    increment16(bValue);
    showValue(bValue, B);
  }

  if(Rtrigger){
    showValue(aValue + bValue, result);
  }

  switchAValue = digitalRead(SWITCH_A);
  switchBValue = digitalRead(SWITCH_B);
  switchRValue = digitalRead(SWITCH_R);

  delay(1);
}

void _debugLED(){
  showValue(aValue, A);
  showValue(aValue, B);
  showValue(resultValue, result);

  increment16(aValue);
  increment16(bValue);
  increment32(resultValue);
  delay(300);
}
