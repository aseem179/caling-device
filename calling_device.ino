#include <EEPROM.h>
String textMessage;
#define pin1 11
#define pin2 12
#define pin3 10
int hooter;
unsigned long long curren_time;
unsigned long int val;
#include <RCSwitch.h>
RCSwitch mySwitch = RCSwitch();
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  mySwitch.enableReceive(0);  // Receiver on interrupt 0 => that is pin #2
  //delay(20000);
  digitalWrite(pin3, HIGH);
  pinMode(pin1, INPUT_PULLUP);
  delay(5000);
  Serial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);
  Serial.println("AT+CNMI=2,2,0,0,0"); // AT Command to receive a live SMS
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  Serial.println("AT+CMGS=\"+917597540000\"\r"); // Replace x with mobile number
  delay(1000);
  Serial.println("security sytem power on");// The SMS text you want to send
  delay(100);
  Serial.println((char)26);// ASCII code of CTRL+Z
  curren_time = millis();
}
void loop() {
  hooter;
  if (mySwitch.available()) {
    val = mySwitch.getReceivedValue();
    switch (val)
    {
      case 5030156 : Serial.println("arming");
        Serial.println("AT+CMGS=\"+917597540000\"\r"); // Replace x with mobile number
        delay(1000);
        Serial.println("armed by remote");// The SMS text you want to send
        delay(100);
        Serial.println((char)26);// ASCII code of CTRL+Z
        EEPROM.write(1, 1);
        break;
      case 5030147 : Serial.println("disarming");
        EEPROM.write(1, 0);
        Serial.println("AT+CMGS=\"+917597540000\"\r"); // Replace x with mobile number
        delay(1000);
        Serial.println("diarmed by remote");// The SMS text you want to send
        delay(100);
        Serial.println((char)26);// ASCII code of CTRL+Z
        break;
      case 5030336 : Serial.println("hooter");
        if (hooter == 0)
        {
          digitalWrite(pin2, HIGH);
          Serial.println("AT+CMGS=\"+917597540000\"\r"); // Replace x with mobile number
          delay(1000);
          Serial.println("hooter on by remote");// The SMS text you want to send
          delay(100);
          Serial.println((char)26);// ASCII code of CTRL+Z
          hooter = 1;
        }
        else
        {
          hooter = 0;
          digitalWrite(pin2, LOW);
          Serial.println("AT+CMGS=\"+917597540000\"\r"); // Replace x with mobile number
          delay(1000);
          Serial.println("hooter off by remote");// The SMS text you want to send
          delay(100);
          Serial.println((char)26);// ASCII code of CTRL+Z
        }
        break;
    }

    mySwitch.resetAvailable();
  }
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0)
  {

    //Serial.write(Serial.read());
    textMessage = Serial.readString();
    textMessage.toUpperCase();
  }
  int pin1val = digitalRead(pin1);
  int eepread;
  EEPROM.get(1, eepread);
  //Serial.println(EEPROM.read(1));
  if (pin1val == 0 && EEPROM.read(1) == 1)
  {
    digitalWrite(pin2, HIGH);
    Serial.println("AT+CMGS=\"+917597540000\"\r"); // Replace x with mobile number
    delay(1000);
    Serial.println("security alarm rice mill");// The SMS text you want to send
    delay(100);
    Serial.println((char)26);// ASCII code of CTRL+Z
    delay(6000);
    Serial.println("AT");
    delay(1000);
    Serial.println("calling");
    Serial.println("ATD+917597540000;");
    delay(18000);
    Serial.println("ATH");
  }
  if (textMessage.indexOf("ALARM5069") >= 0) {
    Serial.println("text matched");
    hooter = 1;
    digitalWrite(pin2, HIGH);
    Serial.println("AT+CMGS=\"+917597540000\"\r"); // Replace x with mobile number
    delay(1000);
    Serial.println("security alarm oN");// The SMS text you want to send
    delay(100);
    Serial.println((char)26);// ASCII code of CTRL+Z
    textMessage = "";
  }
  if (textMessage.indexOf("ALARM OFF 5069") >= 0) {
    hooter = 0;
    Serial.println("ALRAM OFF");
    digitalWrite(pin2, LOW);
    Serial.println("AT+CMGS=\"+917597540000\"\r"); // Replace x with mobile number
    delay(1000);
    Serial.println("security alarm off");// The SMS text you want to send
    delay(100);
    Serial.println((char)26);// ASCII code of CTRL+Z
    textMessage = "";
  }
  if (textMessage.indexOf("MACHINE OFF 5069") >= 0) {
    Serial.println("MACHINE OFF");
    digitalWrite(pin3, LOW);
    Serial.println("AT+CMGS=\"+917597540000\"\r"); // Replace x with mobile number
    delay(1000);
    Serial.println("current off");// The SMS text you want to send
    delay(100);
    Serial.println((char)26);// ASCII code of CTRL+Z
    textMessage = "";
  }
  if (textMessage.indexOf("MACHINE ON 5069") >= 0) {
    Serial.println("MACHINE ON");
    digitalWrite(pin3, HIGH);
    Serial.println("AT+CMGS=\"+917597540000\"\r"); // Replace x with mobile number
    delay(1000);
    Serial.println("current on");// The SMS text you want to send
    delay(100);
    Serial.println((char)26);// ASCII code of CTRL+Z
    textMessage = "";
  }
  if (textMessage.indexOf("DISARM 5069") >= 0) {
    Serial.println("DISARM");
    EEPROM.write(1, 0);
    Serial.println("AT+CMGS=\"+917597540000\"\r"); // Replace x with mobile number
    delay(1000);
    Serial.println("disarmed");// The SMS text you want to send
    delay(100);
    Serial.println((char)26);// ASCII code of CTRL+Z
    textMessage = "";
  }
  if (textMessage.indexOf("ARMING 5069") >= 0) {
    Serial.println("MACHINE ON");
    EEPROM.write(1, 1);
    Serial.println("AT+CMGS=\"+917597540000\"\r"); // Replace x with mobile number
    delay(1000);
    Serial.println("armed");// The SMS text you want to send
    delay(100);
    Serial.println((char)26);// ASCII code of CTRL+Z
    textMessage = "";
  }
  if (textMessage.indexOf("STATUS 5069") >= 0) {
    if (EEPROM.read(1) == 1)
    {
      Serial.println("AT+CMGS=\"+917597540000\"\r"); // Replace x with mobile number
      delay(1000);
      Serial.println("armed");// The SMS text you want to send
      delay(100);
      Serial.println((char)26);// ASCII code of CTRL+Z
      textMessage = "";
    }
    else
    {
      Serial.println("AT+CMGS=\"+917597540000\"\r"); // Replace x with mobile number
      delay(1000);
      Serial.println("disarmed");// The SMS text you want to send
      delay(100);
      Serial.println((char)26);// ASCII code of CTRL+Z
      textMessage = "";
      }
  }
  if ((millis() - curren_time) > 14400000)
  {
    curren_time = millis();
    Serial.println("AT+CMGS=\"+917597540000\"\r"); // Replace x with mobile number
    delay(1000);
    Serial.println("stay worryless your property is  under supervision");// The SMS text you want to send
    delay(100);
    Serial.println((char)26);// ASCII code of CTRL+Z
  }
}
