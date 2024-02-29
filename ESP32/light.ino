#define RED_A 2
#define YELLOW_A 3
#define GREEN_A 1
#define RED_B 7
#define YELLOW_B 8
#define GREEN_B 6
int incomingByte = 0; // 定义变量用于接收串口数据
void (*resetFunc)(void) = 0;

void setup()
{
  pinMode(RED_A, OUTPUT);
  pinMode(YELLOW_A, OUTPUT);
  pinMode(GREEN_A, OUTPUT);
  pinMode(RED_B, OUTPUT);
  pinMode(YELLOW_B, OUTPUT);
  pinMode(GREEN_B, OUTPUT);
  Serial.begin(9600);
}

void countdown(String colorA, int secondsA, String colorB, int secondsB)
{
  int counterA = secondsA;
  int counterB = secondsB;
  while (counterA > 0 && counterB > 0)
  {
    if (counterA < 0 || counterB < 0)
      break;
    Serial.print("通道A: ");
    Serial.print(counterA > 0 ? colorA : "红灯");
    Serial.print(", 剩余秒数: ");
    Serial.print(counterA > 0 ? counterA : 0);
    Serial.print(" | ");
    Serial.print("通道B: ");
    Serial.print(counterB > 0 ? colorB : "红灯");
    Serial.print(", 剩余秒数: ");
    Serial.println(counterB > 0 ? counterB : 0);
    delay(1000);
    if (counterA > 0)
      counterA--;
    if (counterB > 0)
      counterB--;
    if (Serial.available() > 0)
    {
      // 有可读数据，读取1字节
      incomingByte = Serial.read();
      if (incomingByte == 49)
      {
        Serial.println("A道行人按键被按下");
        // 关闭所有通道
        digitalWrite(RED_A, LOW);
        digitalWrite(RED_B, LOW);
        digitalWrite(YELLOW_A, LOW);
        digitalWrite(YELLOW_B, LOW);
        digitalWrite(GREEN_A, LOW);
        digitalWrite(GREEN_B, LOW);

        // 按钮被按下，B道黄灯亮5s后转为红灯，A道黄灯5s后转为绿灯
        digitalWrite(YELLOW_B, HIGH);
        digitalWrite(YELLOW_A, HIGH);
        Serial.println("请等待5秒黄灯...");
        delay(5000);
        digitalWrite(YELLOW_A, LOW);
        digitalWrite(YELLOW_B, LOW);
        resetFunc();
      }
      else if (incomingByte == 50)
      {
        Serial.println("紧急按钮被按下,请等待5秒黄灯...");
        // 关闭所有通道
        digitalWrite(RED_A, LOW);
        digitalWrite(RED_B, LOW);
        digitalWrite(YELLOW_A, LOW);
        digitalWrite(YELLOW_B, LOW);
        digitalWrite(GREEN_A, LOW);
        digitalWrite(GREEN_B, LOW);

        // 按钮被按下，A道黄灯亮5s后转为红灯，B道黄灯5s后转为绿灯
        digitalWrite(YELLOW_A, HIGH);
        digitalWrite(YELLOW_B, HIGH);
        delay(5000);
        digitalWrite(YELLOW_A, LOW);
        digitalWrite(YELLOW_B, LOW);
        digitalWrite(RED_A, HIGH);
        digitalWrite(RED_B, HIGH);
        Serial.println("车辆紧急通过中...请等待5秒");
        delay(5000);
        digitalWrite(RED_A, LOW);
        digitalWrite(RED_B, LOW);
        resetFunc();
      }
      else if (incomingByte == 51)
      {
        // 如果按键3被按下，那么增加AB两车道的倒计时
        Serial.println("车流量过大,延长10秒绿灯");
        counterA += 10;
        counterB += 10;
      }
    }
  }
}

void loop()
{
  // 南北通道A绿灯亮30s，东西通道B红灯亮35s
  digitalWrite(GREEN_A, HIGH);
  digitalWrite(RED_B, HIGH);
  countdown("绿灯", 30, "红灯", 35);

  // 南北通道A黄灯亮5s，东西通道B红灯亮
  digitalWrite(GREEN_A, LOW);
  digitalWrite(YELLOW_A, HIGH);
  countdown("黄灯", 5, "红灯", 5);

  // 南北通道A红灯亮，东西通道B绿灯亮15s
  digitalWrite(YELLOW_A, LOW);
  digitalWrite(RED_A, HIGH);
  digitalWrite(RED_B, LOW);
  digitalWrite(GREEN_B, HIGH);
  countdown("红灯", 20, "绿灯", 15);

  // 南北通道A红灯亮，东西通道B黄灯亮5s
  digitalWrite(GREEN_B, LOW);
  digitalWrite(YELLOW_B, HIGH);
  countdown("红灯", 5, "黄灯", 5);

  // 关闭所有通道
  digitalWrite(RED_A, LOW);
  digitalWrite(RED_B, LOW);
  digitalWrite(YELLOW_A, LOW);
  digitalWrite(YELLOW_B, LOW);
  digitalWrite(GREEN_A, LOW);
  digitalWrite(GREEN_B, LOW);
}