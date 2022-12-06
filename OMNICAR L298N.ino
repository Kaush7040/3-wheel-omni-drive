#include <SoftwareSerial.h>//used to redefine Digital Pins 2,3 as Rx and Tx

SoftwareSerial HM10(2, 3); //Creates object HM10 to refer to, using which all RxDx commands to BT will be conducted

/*We redefine pins2,3 as Rx and Tx because 
the two microcontrollers on the board communicate with each other;
by using 0,1 pins we disturb that communication,
hence we use some other pins.*/

char inData;

//motor 1
#define IN1 9
#define IN2 8
#define EN1 10

//motor 2
#define IN3 7
#define IN4 6
#define EN2 5

//motor 3 (turning wheel)
#define IN5 12
#define IN6 13
#define EN3 11

void forward();
void backward();
void left();
void right();
void cw();
void anticw();
void stop();

void setup() {
  Serial.begin(9600);//sets serial port's baud rate at 9600bits/s
  HM10.begin(9600); //begins BT module's serial port communication at baud rate 9600bits/s

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(EN1, OUTPUT);

  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(EN2, OUTPUT);

  pinMode(IN5, OUTPUT);
  pinMode(IN6, OUTPUT);
  pinMode(EN3, OUTPUT);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(EN1, 0);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(EN2, 0);

  digitalWrite(IN5, LOW);
  digitalWrite(IN6, LOW);  
  analogWrite(EN3, 0);

  Serial.println("Final Code");
  
}

void loop() {
{
  //arduino receives info
  HM10.listen();  // makes sure the hm10 port is in listening mode (Rx Dx defined ports will be the only ports that will be able to receive information, info received on other pins will be discared)
  while (HM10.available() > 0) {   // waits until HM10 sends some info
    inData = HM10.read();//reads and returns incoming data
    Serial.write(inData);//The data is sent as a series of bytes to hardware of arduino
  }
  
  //arduino transmits info
  if (Serial.available()) {// Read arduino input if available.
    delay(10);
    HM10.write(Serial.read());//The data is sent as a series of bytes to HM10
    //Serial.println(inData);
  }

    switch (inData) {
      case 'f':
        forward();
        break;

      case 'b':
        backward();
        break;

      case 'l':
        left();
        break;

      case 'r':
        right();
        break;

      case 'c':
        cw();
        break;

      case 'a':
        anticw();
        break;

      case 's':
        stop();
        break;
    }
  }
}

void forward() {
  Serial.println("Forward");
  //1cw
  analogWrite(EN1, 255);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  //2acw
  analogWrite(EN2, 255);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  //3stat
  analogWrite(EN3,0);
  digitalWrite(IN5, LOW);
  digitalWrite(IN6, LOW);
}

void backward() {
  Serial.println("Backward");
  //1acw
  analogWrite(EN1, 255);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  //2cw
  analogWrite(EN2, 255);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  //3stat
  analogWrite(EN3, 0);
  digitalWrite(IN5, LOW);
  digitalWrite(IN6, LOW);
}

void left() {
  Serial.println("Left");
  //1acw
  analogWrite(EN1, 127);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  //2acw
  analogWrite(EN2, 127);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  //3cw
  analogWrite(EN3, 255);
  digitalWrite(IN5, LOW);
  digitalWrite(IN6, HIGH);
}

void right() {
  Serial.println("Right");
  //1cw
  analogWrite(EN1, 127);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  //2cw
  analogWrite(EN2, 127);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  //3acw
  analogWrite(EN3, 255);
  digitalWrite(IN5, HIGH);
  digitalWrite(IN6, LOW);
}

void cw() {
  Serial.println("clockwise");
  //1cw
  analogWrite(EN1, 200);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  //2cw
  analogWrite(EN2, 200);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  //3cw
  analogWrite(EN3, 200);
  digitalWrite(IN5, LOW);
  digitalWrite(IN6, HIGH);
}

void anticw() {
  Serial.println("anti-clockwise");
  //1acw
  analogWrite(EN1, 200);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  //2acw
  analogWrite(EN2, 200);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  //3cw
  analogWrite(EN3, 200);
  digitalWrite(IN5, HIGH);
  digitalWrite(IN6, LOW);
}

//
void stop() {
  Serial.println("Stop");
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  digitalWrite(IN5, LOW);
  digitalWrite(IN6, LOW);
}
