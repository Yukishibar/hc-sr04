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
  unsigned long t1 = micros();

  while(digitalRead(Echo_Pin)){
    }
  unsigned long t2 = micros();
  
  unsigned long t = t2 - t1;
  Serial.print(double(V * t /20000));
  Serial.println("cm");
  delay(200);  // 距離計算の頻度
}
