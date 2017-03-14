int rwheel=0;  // link to D15, A1
int lwheel=0;  // link to D16, A2

int pwm_a = 3;   //PWM control for motor outputs 1 and 2 is on digital pin 3
int pwm_b = 11;  //PWM control for motor outputs 3 and 4 is on digital pin 11
int dir_a = 12;  //direction control for motor outputs 1 and 2 is on digital pin 12
int dir_b = 13;  //direction control for motor outputs 3 and 4 is on digital pin 13

int distance =300;

void setup()
{
  initmotors();  
  initdipswitch();
  
  //tablebot(); /// test1
  //blackboardbot();
  //birdbot();
  
  // testmotorsdipswitch();

}

void loop()
{
 // testmotors(100,1000); 
//  checkdipswitch();
}

void tablebot()
{
  while(1)
  {  if (analogRead(A0) < 30) 
    { 
      motorA(-100); motorB(-100); 
      delay(1000);
      motorA(-100); motorB(100);
      delay(500);
    }
    else 
    {
      motorA(100); motorB(100);
    }
  }
}

void testmotorsdipswitch()
{
  while(1)
  {
    
      if (digitalRead(8) == 1)
      {  motorA(100); motorB(-100); }
      else 
      if (digitalRead(7) == 1)
      {  motorA(50); motorB(-50); }
      else 
      if (digitalRead(4) == 1)
      {  motorA(20); motorB(100); }
      else 
      if (digitalRead(2) == 1)
      {  motorA(-100); motorB(-20); }
  }
}
void motorA(int speed)
{
  if (speed > 0)
  {  
    digitalWrite(dir_a, HIGH);  //Reverse motor direction, 1 high, 2 low
    analogWrite(pwm_a, speed*2.5);    //set both motors to run at (100/255 = 39)% duty cycle
  }

  else if (speed < 0)
  {  
    digitalWrite(dir_a, LOW);  //Reverse motor direction, 1 high, 2 low
    analogWrite(pwm_a, -speed*2.5);    //set both motors to run at (100/255 = 39)% duty cycle
  }

  else if (speed == 0)
  {
    digitalWrite(dir_a, LOW); //Set motor direction, 1 low, 2 high
    analogWrite(pwm_a, 0);    //0 to off motors
  }   
}

void motorB(int speed)
{
  if (speed > 0)
  {  
    digitalWrite(dir_b, HIGH);  //Reverse motor direction, 1 high, 2 low
    analogWrite(pwm_b, speed*2.5);    //set both motors to run at (100/255 = 39)% duty cycle
  }

  else if (speed < 0)
  {  
    digitalWrite(dir_b, LOW);  //Reverse motor direction, 1 high, 2 low
    analogWrite(pwm_b, -speed*2.5);    //set both motors to run at (100/255 = 39)% duty cycle
  }

  else if (speed == 0)
  {
    digitalWrite(dir_b, LOW); //Set motor direction, 1 low, 2 high
    analogWrite(pwm_b, 0);    //0 to off motors
  }   
}

void initmotors()
{
  pinMode(pwm_a, OUTPUT);  //Set control pins to be outputs
  pinMode(pwm_b, OUTPUT);
  pinMode(dir_a, OUTPUT);
  pinMode(dir_b, OUTPUT);

  analogWrite(pwm_a, 0);    //0 to off motors
  analogWrite(pwm_b, 0);    //0 to off motors
}

void testmotors(int speed, int delaytime)
{
  motorA(speed);
  delay(delaytime);
  motorA(-speed);
  delay(delaytime);
  motorA(0);
  delay(delaytime);
  
  motorB(speed);
  delay(delaytime);
  motorB(-speed);
  delay(delaytime);
  motorB(0);
  delay(delaytime);
}

// ================== sub functions or dipswitch ============================

void initdipswitch()
{
  pinMode(8, INPUT);  //Set dip switch as inputs
  pinMode(7, INPUT);  //Set dip switch as inputs
  pinMode(4, INPUT);  //Set dip switch as inputs
  pinMode(2, INPUT);  //Set dip switch as inputs
  
  pinMode(15,INPUT);
  pinMode(16,INPUT);
}

void checkdipswitch() {
  Serial.print(digitalRead(8)); Serial.print("==");
  Serial.print(digitalRead(7)); Serial.print("==");
  Serial.print(digitalRead(4)); Serial.print("==");
  Serial.println(digitalRead(2));

  delay(50);     
}


void checkenc() {
  Serial.print(digitalRead(15)); Serial.print("==");
  Serial.println(digitalRead(16));

  delay(50);     
}

void encturn(int speed, int rotation)
{
  rwheel=0;
  lwheel=0;
  
  motorA(speed);
  motorB(-speed);
  
  while(1)
  {
    if (digitalRead(15) == 0) 
      { rwheel = rwheel+1;
        while(1)
        {  if (digitalRead(15) == 1) { break; } }
      }
    if ((rwheel == rotation) || (rwheel > rotation)) {break; }
  }
  
  motorA(0);
  motorB(0);
}
  

void encmove(int speed, int rotation)
{
  rwheel=0;
  lwheel=0;
  
  motorA(-speed);
  motorB(-speed*0.98);
  
  while(1)
  {
    if (digitalRead(15) == 0) 
      { rwheel = rwheel+1;
        while(1)
        {  if (digitalRead(15) == 1) { break; } }
      }
    if ((rwheel == rotation-3) || (rwheel > rotation)) {break; }
  }
  
  motorA(0);
  motorB(0);
}


void rightwheel(int speed, int rotation)
{
  rwheel=0;
  motorA(speed);
  while(1)
  {
    if (digitalRead(15) == 0) 
      { rwheel = rwheel+1;
        while(1)
        {  if (digitalRead(15) == 1) { break; } }
      }
    if ((rwheel == rotation) || (rwheel > rotation)) {break; }
  }
  
  motorA(0);
}
  

void leftwheel(int speed, int rotation)
{
  lwheel=0;
  motorB(speed);
  while(1)
  {
    if (digitalRead(16) == 0)
      { lwheel = lwheel+1;
        while(1)
        {  if (digitalRead(16) == 1) { break; } }
      }
    if ((lwheel == rotation) || (lwheel > rotation)) {break; }
  }
  
  motorB(0);
}

    

void countclicks()
{
  while(1)
  {
    if (digitalRead(15) == 0) 
      { rwheel = rwheel+1;
        while(1)
        {  if (digitalRead(15) == 1) { break; } }
      }
     Serial.println(rwheel);
  }
}

void setup()
{
  initmotors();  
  initdipswitch();
  
  //tablebot();
  //blackboardbot();
  //birdbot();
  
  // testmotorsdipswitch();

}
