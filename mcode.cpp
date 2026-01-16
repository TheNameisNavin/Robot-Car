
// Bluetooth Controlled Robot Car
// Board: Arduino UNO
// BT: HC-05 on SoftwareSerial (D2=RX, D3=TX via divider)
// Motor driver: L298N (ENA=D5, IN1=D8, IN2=D9, IN3=D10, IN4=D11, ENB=D6)

#include <SoftwareSerial.h>
SoftwareSerial BT(2, 3); // RX, TX (to HC-05)

const int ENA = 5;   // PWM left
const int IN1 = 8;
const int IN2 = 9;
const int ENB = 6;   // PWM right
const int IN3 = 10;
const int IN4 = 11;

int baseSpeed = 200; // 0..255 default speed

void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Stop motors initially
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);

  Serial.begin(9600); // for debug via USB
  BT.begin(9600);     // HC-05 default baud rate

  Serial.println("BT Car ready. Commands: F,B,L,R,S and 0..9 for speed");
}

void loop() {
  if (BT.available()) {
    char c = BT.read();
    if (c == '\r' || c == '\n') return; // ignore CR/LF
    c = toupper(c);

    switch (c) {
      case 'F': forward(baseSpeed);  Serial.println("FWD"); break;
      case 'B': backward(baseSpeed); Serial.println("BACK"); break;
      case 'L': left(baseSpeed);     Serial.println("LEFT"); break;
      case 'R': right(baseSpeed);    Serial.println("RIGHT"); break;
      case 'S': stopCar();           Serial.println("STOP"); break;
      default:
        if (c >= '0' && c <= '9') {
          baseSpeed = map(c, '0', '9', 0, 255);
          Serial.print("Speed = "); Serial.println(baseSpeed);
          BT.print("Speed="); BT.println(baseSpeed);
        }
        break;
    }
  }
}

// ---- Movement helpers ----
void forward(int spd)   { drive(spd,  spd);  }
void backward(int spd)  { drive(-spd, -spd); }
void left(int spd)      { drive(-spd, spd);  }  // pivot turn
void right(int spd)     { drive(spd, -spd);  }
void stopCar()          { drive(0, 0);       }

// drive: +speed = forward, -speed = backward, 0 = stop
void drive(int leftSpeed, int rightSpeed) {
  // Left motor
  if (leftSpeed > 0) {
    digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  } else if (leftSpeed < 0) {
    digitalWrite(IN1, LOW);  digitalWrite(IN2, HIGH);
  } else {
    digitalWrite(IN1, LOW);  digitalWrite(IN2, LOW);
  }
  // Right motor
  if (rightSpeed > 0) {
    digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
  } else if (rightSpeed < 0) {
    digitalWrite(IN3, LOW);  digitalWrite(IN4, HIGH);
  } else {
    digitalWrite(IN3, LOW);  digitalWrite(IN4, LOW);
  }

  analogWrite(ENA, constrain(abs(leftSpeed), 0, 255));
  analogWrite(ENB, constrain(abs(rightSpeed), 0, 255));
}
