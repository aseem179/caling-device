int enablePin = 10; 
void setup() 
{
  Serial.begin(9600);                   // initialize serial at baudrate 9600:
  pinMode(enablePin, OUTPUT);
  digitalWrite(enablePin, LOW); 
}
void loop() 
{                                                  
  while (Serial.available())                   //While have data at Serial port this loop executes
     {                
        int pwmval = Serial.parseInt();            //Receive INTEGER value from Master throught RS-485
        Serial.print("I got value");
        Serial.println(pwmval);
        if(pwmval == 14)
        {
          Serial.println("realay on");
          }     
    }
 } 
