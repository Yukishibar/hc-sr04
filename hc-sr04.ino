#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

#define Trigger_Pin 25
#define Echo_Pin 26

double T = 24.2;   // 室温
double V = 331.5 + 0.6 * T;  // 温度を考慮した音速

void setup() 
{
  Serial.begin(115200);
  pinMode(Trigger_Pin, OUTPUT);
  pinMode(Echo_Pin, INPUT);
  digitalWrite(Trigger_Pin, LOW);

  SerialBT.begin("ESP32test"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
}

// Trigger pulse
void sendTrigger()
{
  digitalWrite(Trigger_Pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trigger_Pin, LOW);
}

void loop() 
{
  sendTrigger();

  while(!digitalRead(Echo_Pin)){
    }
  unsigned long t1 = micros();  // micros:起動から現在までの時間を取得

  while(digitalRead(Echo_Pin)){
    }
  unsigned long t2 = micros();  // t1との差分を取り，音波の跳ね返り時間を算出
  
  unsigned long t = t2 - t1;
  double d = V * t /20000;
  Serial.print(d);
  Serial.println("cm");

  // 1sごとに相互通信する
  if (Serial.available()) {   // ESP32側のシリアル通信で何か入力があったらBT側に書き込む．
    SerialBT.write(Serial.read());
  }
  if (SerialBT.available()) {   // Bluetooth通信側のシリアル通信で何か入力があったらESP32側に書き込む．
    Serial.write(SerialBT.read());
  }
  delay(1000);
}
