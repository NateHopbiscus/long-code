#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Encoder.h>
#include <Keypad.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64
#define SCREEN_ADDRESS 0x3D
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define MOTORSELECT 0
#define DIRECTION 1
#define HUNDREDS 2
#define TENS 3
#define ONES 4
#define VERIFY 5
#define EXECUTE 6
#define BREAK 7
#define EDIT 8

#define BASE 10
#define LOWERARM 11
#define UPPERARM 12
#define WRISTONE 13
#define WRISTTWO 14
#define HAND 15

#define JOYSTICK 20
#define KEYPAD 21

#define MOTORSELECTEDIT 25
#define DIRECTIONSELECTEDIT 26
#define VALUESELECTEDIT 27
#define RESTART 28

#define HUNDREDSEDIT 30
#define TENSEDIT 31
#define ONESEDIT 32

int motor = 10;
int state = 0;
int control = 20;
int edit;
int editvalue;

int editMessage = 1;
int valMessage = 1;

int motorvar1 = 0;
int motorvar2 = 0;

int currentCount = 0;
int previousCount = 0;

int dVal;
int hVal;
int tVal;
int oVal;

int playedMessage = 0;

int selection = 0;

const byte ROWS = 4;
const byte COLS = 4;

int x;
int g;

char hexaKeys[COLS][ROWS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'0', 'F', 'E', 'D'}
};

byte colPins[COLS] = {37, 36, 35, 34};
byte rowPins[ROWS] = {33, 32, 31, 30};

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);


int BaseA = 14;
int BaseB = 15;
int LowerA = 4;
int LowerB = 5;
int UpperA = 6;
int UpperB = 7;
int Wrist1a = 22;
int Wrist1b = 23;
int Wrist2a = 24;
int Wrist2b = 25;
int HandA = 26;
int HandB = 27;

int ControlJoystick = 16;
int ControlKeypad = 17;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
  display.clearDisplay();

  pinMode(BaseA, OUTPUT);
  pinMode(BaseB, OUTPUT);
  pinMode(LowerA, OUTPUT);
  pinMode(LowerB, OUTPUT);
  pinMode(UpperA, OUTPUT);
  pinMode(UpperB, OUTPUT);
  pinMode(Wrist1a, OUTPUT);
  pinMode(Wrist1b, OUTPUT);
  pinMode(Wrist2a, OUTPUT);
  pinMode(Wrist2b, OUTPUT);
  pinMode(HandA, OUTPUT);
  pinMode(HandB, OUTPUT);

  pinMode(ControlJoystick, INPUT);
  pinMode(ControlKeypad, INPUT);

}

void loop() {

  int y = analogRead(2);

  int cValJ = digitalRead(16);
  int cValK = digitalRead(17);

  char customKey = customKeypad.getKey();
  g = customKey;
  int key = map(g, 48, 70, 0, 22);

  if (cValK == HIGH) {
    control = 21;
  }
  if (cValJ == HIGH) {
    control = 20;
  }

  

  switch (control) {
    case JOYSTICK:
      {
        if (key == 17) {
          motor = BASE;
        } if (key == 18) {
          motor = LOWERARM;
        } if (key == 19) {
          motor = UPPERARM;
        } if (key == 20) {
          motor = WRISTONE;
        } if (key == 21) {
          motor = WRISTTWO;
        } if (key == 22) {
          motor = HAND;
        }

        switch (motor) {
          case BASE:
            if (0 <= y && y <= 262) {
              digitalWrite(BaseA, HIGH);
              digitalWrite(BaseB, LOW);
            } else if (762 <= y && y <= 1023 ) {
              digitalWrite(BaseA, LOW);
              digitalWrite(BaseB, HIGH);

            } else if (262 <= y && y <= 762) {
              digitalWrite(BaseA, LOW);
              digitalWrite(BaseB, LOW);
            }
            display.clearDisplay();
            display.setTextSize(1);
            display.setTextColor(WHITE);
            display.setCursor(1, 0);
            display.print("Control Type: JStick.");
            display.setCursor(1, 2);
            display.print("_____________________");
            display.setCursor(1, 10);
            display.print("Motor: Base.");
            display.setCursor(1, 12);
            display.print("____________");
            display.display();
            break;
          case LOWERARM:
            if (0 <= y && y <= 262) {
              digitalWrite(LowerA, HIGH);
              digitalWrite(LowerB, LOW);
            } else if (762 <= y && y <= 1023 ) {
              digitalWrite(LowerA, LOW);
              digitalWrite(LowerB, HIGH);

            } else if (262 <= y && y <= 762) {
              digitalWrite(LowerA, LOW);
              digitalWrite(LowerB, LOW);
            }
            display.clearDisplay();
            display.setTextSize(1);
            display.setTextColor(WHITE);
            display.setCursor(1, 0);
            display.print("Control Type: JStick.");
            display.setCursor(1, 2);
            display.print("_____________________");
            display.setCursor(1, 10);
            display.print("Motor: Lower Arm.");
            display.setCursor(1, 12);
            display.print("_________________");
            display.display();
            break;
          case UPPERARM:
            if (0 <= y && y <= 262) {
              digitalWrite(UpperA, HIGH);
              digitalWrite(UpperB, LOW);
            } else if (762 <= y && y <= 1023 ) {
              digitalWrite(UpperA, LOW);
              digitalWrite(UpperB, HIGH);

            } else if (262 <= y && y <= 762) {
              digitalWrite(UpperA, LOW);
              digitalWrite(UpperB, LOW);
            }
            display.clearDisplay();
            display.setTextSize(1);
            display.setTextColor(WHITE);
            display.setCursor(1, 0);
            display.print("Control Type: JStick.");
            display.setCursor(1, 2);
            display.print("_____________________");
            display.setCursor(1, 10);
            display.print("Motor: Upper Arm.");
            display.setCursor(1, 12);
            display.print("_________________");
            display.display();
            break;
          case WRISTONE:
            if (0 <= y && y <= 262) {
              digitalWrite(Wrist1a, HIGH);
              digitalWrite(Wrist1b, LOW);
            } else if (762 <= y && y <= 1023 ) {
              digitalWrite(Wrist1a, LOW);
              digitalWrite(Wrist1b, HIGH);

            } else if (262 <= y && y <= 762) {
              digitalWrite(Wrist1a, LOW);
              digitalWrite(Wrist1b, LOW);
            }
            display.clearDisplay();
            display.setTextSize(1);
            display.setTextColor(WHITE);
            display.setCursor(1, 0);
            display.print("Control Type: JStick.");
            display.setCursor(1, 2);
            display.print("_____________________");
            display.setCursor(1, 10);
            display.print("Motor: Wrist One.");
            display.setCursor(1, 12);
            display.print("_________________");
            display.display();
            break;
          case WRISTTWO:
            if (0 <= y && y <= 262) {
              digitalWrite(Wrist2a, HIGH);
              digitalWrite(Wrist2b, LOW);
            } else if (762 <= y && y <= 1023 ) {
              digitalWrite(Wrist2a, LOW);
              digitalWrite(Wrist2b, HIGH);

            } else if (262 <= y && y <= 762) {
              digitalWrite(Wrist2a, LOW);
              digitalWrite(Wrist2b, LOW);
            }
            display.clearDisplay();
            display.setTextSize(1);
            display.setTextColor(WHITE);
            display.setCursor(1, 0);
            display.print("Control Type: JStick.");
            display.setCursor(1, 2);
            display.print("_____________________");
            display.setCursor(1, 10);
            display.print("Motor: Wrist Two.");
            display.setCursor(1, 12);
            display.print("_________________");
            display.display();
            break;
          case HAND:
            if (0 <= y && y <= 262) {
              digitalWrite(HandA, HIGH);
              digitalWrite(HandB, LOW);
            } else if (762 <= y && y <= 1023 ) {
              digitalWrite(HandA, LOW);
              digitalWrite(HandB, HIGH);

            } else if (262 <= y && y <= 762) {
              digitalWrite(HandA, LOW);
              digitalWrite(HandB, LOW);
            }
            display.clearDisplay();
            display.setTextSize(1);
            display.setTextColor(WHITE);
            display.setCursor(1, 0);
            display.print("Control Type: JStick");
            display.setCursor(1, 2);
            display.print("____________________");
            display.setCursor(1, 10);
            display.print("Motor: Hand.");
            display.setCursor(1, 12);
            display.print("____________________");
            display.display();
        }
      } break;
    case KEYPAD:
      {
        display.clearDisplay();
        display.setTextSize(1);
        display.setTextColor(WHITE);
        display.setCursor(1, 0);
        display.print("Control Type: Keypad.");
        display.setCursor(1, 2);
        display.print("_____________________");
        switch (state) {
          case MOTORSELECT:
            edit = -1;
            display.clearDisplay();
            display.setTextSize(1);
            display.setTextColor(WHITE);
            display.setCursor(1, 0);
            display.print("Control Type: Keypad.");
            display.setCursor(1, 2);
            display.print("_____________________");
            display.setCursor(1, 10);
            display.print("Select Motor.");
            display.setCursor(1, 12);
            display.print("_____________________");
            display.display();
            if (key == 17) {
              motor = BASE;
              motorvar1 = 14;
              motorvar2 = 15;
              state = 1;
            }
            if (key == 18) {
              motor = LOWERARM;
              motorvar1 = 4;
              motorvar2 = 5;
              state = 1;
            }
            if (key == 19) {
              motor = UPPERARM;
              motorvar1 = 6;
              motorvar2 = 7;
              state = 1;

            }
            if (key == 20) {
              motor = WRISTONE;
              motorvar1 = 8;
              motorvar2 = 9;
              state = 1;
            }
            if (key == 21) {
              motor = WRISTTWO;
              motorvar1 = 10;
              motorvar2 = 11;
              state = 1;
            }
            if (key == 22) {
              motor = HAND;
              motorvar1 = 12;
              motorvar2 = 13;
              state = 1;
            }
            break;
          case DIRECTION:
            display.clearDisplay();
            display.setTextSize(1);
            display.setTextColor(WHITE);
            display.setCursor(1, 0);
            display.print("Control Type: Keypad.");
            display.setCursor(1, 2);
            display.print("_____________________");
            display.setCursor(1, 10);
            display.print("Motor: ");
            {
              if (motor == BASE) {
                display.print("BASE.");
              } if (motor == LOWERARM) {
                display.print("LOWER ARM.");
              } if (motor == UPPERARM) {
                display.print("UPPER ARM.");
              } if (motor == WRISTONE) {
                display.print("WRIST ONE.");
              } if (motor == WRISTTWO) {
                display.print("WRIST TWO.");
              } if (motor == HAND) {
                display.print("HAND.");
              }
            }
            display.setCursor(1, 12);
            display.print("_____________________");
            display.setCursor(1, 20);
            display.print("Select Direction. 1  or 0.");
            display.setCursor(1, 22);
            display.print("_________________________");
            display.display();
            if (key == 0) {
              dVal = 1;
              state = 2;
            }
            if (key == 1) {
              dVal = -1;
              state = 2;
            }
            break;
          case HUNDREDS:
            display.clearDisplay();
            display.setTextSize(1);
            display.setTextColor(WHITE);
            display.setCursor(1, 0);
            display.print("Control Type: Keypad.");
            display.setCursor(1, 2);
            display.print("_____________________");
            display.setCursor(1, 10);
            display.print("Motor: ");
            {
              if (motor == BASE) {
                display.print("BASE.");
              } if (motor == LOWERARM) {
                display.print("LOWER ARM.");
              } if (motor == UPPERARM) {
                display.print("UPPER ARM.");
              } if (motor == WRISTONE) {
                display.print("WRIST ONE.");
              } if (motor == WRISTTWO) {
                display.print("WRIST TWO.");
              } if (motor == HAND) {
                display.print("HAND.");
              }
            }
            display.setCursor(1, 12);
            display.print("_____________________");
            display.setCursor(1, 20);
            display.print("Direction: ");
            if (dVal == 1) {
              display.print("Forward.");
            }
            if (dVal == -1) {
              display.print("Reverse.");
            }
            display.setCursor(1, 22);
            display.print("_____________________");

            display.setCursor(1, 30);
            display.print("Hundreds Value: X__");
            display.display();
            if (key == 0) {
              hVal = 0;
              state = 3;
            }
            if (key == 1) {
              hVal = 1;
              state = 3;
            }
            if (key == 2) {
              hVal = 2;
              state = 3;
            }
            if (key == 3) {
              hVal = 3;
              state = 3;
            }
            if (key == 4) {
              hVal = 4;
              state = 3;
            }
            if (key == 5) {
              hVal = 5;
              state = 3;
            }
            if (key == 6) {
              hVal = 6;
              state = 3;
            }
            if (key == 7) {
              hVal = 7;
              state = 3;
            }
            if (key == 8) {
              hVal = 8;
              state = 3;
            }
            if (key == 9) {
              hVal = 9;
              state = 3;
            }



            break;
          case TENS:
            display.clearDisplay();
            display.setTextSize(1);
            display.setTextColor(WHITE);
            display.setCursor(1, 0);
            display.print("Control Type: Keypad.");
            display.setCursor(1, 2);
            display.print("_____________________");
            display.setCursor(1, 10);
            display.print("Motor: ");
            {
              if (motor == BASE) {
                display.print("BASE.");
              } if (motor == LOWERARM) {
                display.print("LOWER ARM.");
              } if (motor == UPPERARM) {
                display.print("UPPER ARM.");
              } if (motor == WRISTONE) {
                display.print("WRIST ONE.");
              } if (motor == WRISTTWO) {
                display.print("WRIST TWO.");
              } if (motor == HAND) {
                display.print("HAND.");
              }
            }
            display.setCursor(1, 12);
            display.print("_____________________");
            display.setCursor(1, 20);
            display.print("Direction: ");
            if (dVal == 1) {
              display.print("Forward.");
            }
            if (dVal == -1) {
              display.print("Reverse.");
            }
            display.setCursor(1, 22);
            display.print("_____________________");

            display.setCursor(1, 30);
            display.print("Tens Value: ");
            display.print(hVal);
            display.print("X_");
            display.display();
            if (key == 0) {
              tVal = 0;
              state = 4;
            }
            if (key == 1) {
              tVal = 1;
              state = 4;
            }
            if (key == 2) {
              tVal = 2;
              state = 4;
            }
            if (key == 3) {
              tVal = 3;
              state = 4;
            }
            if (key == 4) {
              tVal = 4;
              state = 4;
            }
            if (key == 5) {
              tVal = 5;
              state = 4;
            }
            if (key == 6) {
              tVal = 6;
              state = 4;
            }
            if (key == 7) {
              tVal = 7;
              state = 4;
            }
            if (key == 8) {
              tVal = 8;
              state = 4;
            }
            if (key == 9) {
              tVal = 9;
              state = 4;
            }
            break;
          case ONES:
            display.clearDisplay();
            display.setTextSize(1);
            display.setTextColor(WHITE);
            display.setCursor(1, 0);
            display.print("Control Type: Keypad.");
            display.setCursor(1, 2);
            display.print("_____________________");
            display.setCursor(1, 10);
            display.print("Motor: ");
            {
              if (motor == BASE) {
                display.print("BASE.");
              } if (motor == LOWERARM) {
                display.print("LOWER ARM.");
              } if (motor == UPPERARM) {
                display.print("UPPER ARM.");
              } if (motor == WRISTONE) {
                display.print("WRIST ONE.");
              } if (motor == WRISTTWO) {
                display.print("WRIST TWO.");
              } if (motor == HAND) {
                display.print("HAND.");
              }
            }
            display.setCursor(1, 12);
            display.print("_____________________");
            display.setCursor(1, 20);
            display.print("Direction: ");
            if (dVal == 1) {
              display.print("Forward.");
            }
            if (dVal == -1) {
              display.print("Reverse.");
            }
            display.setCursor(1, 22);
            display.print("_____________________");

            display.setCursor(1, 30);
            display.print("Ones Value: ");
            display.print(hVal);
            display.print(tVal);
            display.print("X");
            display.display();
            if (key == 0) {
              oVal = 0;
              state = 5;
            }
            if (key == 1) {
              oVal = 1;
              state = 5;
            }
            if (key == 2) {
              oVal = 2;
              state = 5;
            }
            if (key == 3) {
              oVal = 3;
              state = 5;
            }
            if (key == 4) {
              oVal = 4;
              state = 5;
            }
            if (key == 5) {
              oVal = 5;
              state = 5;
            }
            if (key == 6) {
              oVal = 6;
              state = 5;
            }
            if (key == 7) {
              oVal = 7;
              state = 5;
            }
            if (key == 8) {
              oVal = 8;
              state = 5;
            }
            if (key == 9) {
              oVal = 9;
              state = 5;
            }
            break;
          case VERIFY:
            edit = -1;
            display.clearDisplay();
            display.setTextSize(1);
            display.setTextColor(WHITE);
            display.setCursor(1, 0);
            display.print("Is this correct?");
            display.setTextSize(1);
            display.setCursor(1, 20);
            display.print("The ");
            {
              if (motor == BASE) {
                display.print("BASE");
              } if (motor == LOWERARM) {
                display.print("LOWER ARM");
              } if (motor == UPPERARM) {
                display.print("UPPER ARM");
              } if (motor == WRISTONE) {
                display.print("WRIST ONE");
              } if (motor == WRISTTWO) {
                display.print("WRIST TWO");
              } if (motor == HAND) {
                display.print("HAND");
              }
              display.print(" will move ");
              display.print(hVal);
              display.print(tVal);
              display.print(oVal);
              display.print(" steps");
              if (dVal == 1) {
                display.print(" forward.");
              } if (dVal == -1) {
                display.print(" in reverse.");
              }
              display.setCursor(1, 55);
              display.print("1/Confirm | 0/Deny");
              display.display();
              if (key == 0) {
                state = 8;
                editMessage = 1;
              } else if (key == 1) {
                state = 6;
              }
              break;
            case EXECUTE:
              display.clearDisplay();
              display.setTextSize(2);
              display.setTextColor(WHITE);
              display.setCursor(1, 0);
              display.print("EXECUTING COMMAND.");
              display.display();

              previousCount = currentCount;
              currentCount = currentCount + ((hVal*100) + (tVal*10) + oVal) * dVal;
              if (currentCount > 0);
              for (previousCount; previousCount < currentCount; previousCount = previousCount + 9.5 ) {
                Serial.print("Current Value: ");
                Serial.println(currentCount);
                Serial.print("Previous Value: ");
                Serial.println(previousCount);
                digitalWrite(motorvar1, HIGH);
                digitalWrite(motorvar2, LOW);
              }
              if (currentCount < 0);
              for (previousCount; previousCount > currentCount; previousCount = previousCount - 9.5 ) {
                Serial.print("Current Value: ");
                Serial.println(currentCount);
                Serial.print("Previous Value: ");
                Serial.println(previousCount);
                digitalWrite(motorvar1, LOW);
                digitalWrite(motorvar2, HIGH);
              }
              previousCount = currentCount - (hVal + tVal + oVal) * dVal;
              digitalWrite(motorvar1, LOW);
              digitalWrite(motorvar2, LOW);
              state = 7;
              break;
            case BREAK:
              display.clearDisplay();
              display.setTextSize(1);
              display.setTextColor(WHITE);
              display.setCursor(1, 0);
              display.print("Command executed.");
              display.setCursor(1, 30);
              display.print("Restarting...");
              display.display();
              delay(10000);
              state = 0;

              break;
            case EDIT:
              {
                if (editMessage == 1) {
                  display.clearDisplay();
                  display.setTextSize(1);
                  display.setTextColor(WHITE);
                  display.setCursor(1, 0);
                  display.print("Select part to edit.");
                  display.setCursor(1, 10);
                  display.print("1. Motor");
                  display.print(" (");
                  {
                    if (motor == BASE) {
                      display.print("BASE.");
                    } if (motor == LOWERARM) {
                      display.print("LOWER ARM.");
                    } if (motor == UPPERARM) {
                      display.print("UPPER ARM.");
                    } if (motor == WRISTONE) {
                      display.print("WRIST ONE.");
                    } if (motor == WRISTTWO) {
                      display.print("WRIST TWO.");
                    } if (motor == HAND) {
                      display.print("HAND.");
                    }
                  }
                  display.print(")");
                  display.setCursor(1, 20);
                  display.print("2. Direction");
                  display.print("(");
                  if (dVal == 1) {
                    display.print("Forward");
                  } if (dVal == -1) {
                    display.print("Reverse");
                  }
                  display.print(")");
                  display.setCursor(1, 30);
                  display.print("3. Step Value");
                  display.print(" (");
                  display.print(hVal);
                  display.print(tVal);
                  display.print(oVal);
                  display.print(")");
                  display.setCursor(1, 40);
                  display.print("4. Restart");
                  display.display();
                  editMessage = 0;
                }

                if (key == 1) {
                  edit = 25;
                }
                if (key == 2) {
                  edit = 26;
                }
                if (key == 3) {
                  edit = 27;
                  valMessage = 1;
                }
                if (key == 4) {
                  edit = 28;
                }
                switch (edit) {
                  case MOTORSELECTEDIT:
                    display.clearDisplay();
                    display.setTextSize(1);
                    display.setTextColor(WHITE);
                    display.setCursor(1, 0);
                    display.print("Select new Motor.");
                    display.setCursor(1, 10);
                    display.print("A. Base");
                    display.setCursor(1, 20);
                    display.print("B. Lower Arm");
                    display.setCursor(1, 30);
                    display.print("C. Upper Arm");
                    display.setCursor(1, 40);
                    display.print("D. Wrist One");
                    display.setCursor(1, 50);
                    display.print("E. Wrist Two");
                    display.setCursor(50, 10);
                    display.print("|");
                    display.setCursor(60, 10);
                    display.print("F. Hand");
                    display.display();

                    if (key == 17) {
                      motor = BASE;
                      motorvar1 = 14;
                      motorvar2 = 15;
                      state = 5;
                    }
                    if (key == 18) {
                      motor = LOWERARM;
                      motorvar1 = 4;
                      motorvar2 = 5;
                      state = 5;
                    }
                    if (key == 19) {
                      motor = UPPERARM;
                      motorvar1 = 6;
                      motorvar2 = 7;
                      state = 5;

                    }
                    if (key == 20) {
                      motor = WRISTONE;
                      motorvar1 = 8;
                      motorvar2 = 9;
                      state = 5;
                    }
                    if (key == 21) {
                      motor = WRISTTWO;
                      motorvar1 = 10;
                      motorvar2 = 11;
                      state = 5;
                    }
                    if (key == 22) {
                      motor = HAND;
                      motorvar1 = 12;
                      motorvar2 = 13;
                      state = 5;
                    }
                    break;

                  case DIRECTIONSELECTEDIT:
                    display.clearDisplay();
                    display.setTextSize(1);
                    display.setTextColor(WHITE);
                    display.setCursor(1, 0);
                    display.print("Select new Direction.");
                    display.setCursor(1, 10);
                    display.print("0. Forward");
                    display.setCursor(1, 20);
                    display.print("1. Reverse");
                    display.display();
                    if (key == 0) {
                      dVal = 1;
                      state = 5;
                    }
                    if (key == 1) {
                      dVal = -1;
                      state = 5;
                    }
                    break;

                  case VALUESELECTEDIT:
                    if (valMessage == 1) {
                      display.clearDisplay();
                      display.setTextSize(1);
                      display.setTextColor(WHITE);
                      display.setCursor(1, 0);
                      display.print("Select Value Place to edit.");
                      display.setCursor(1, 15);
                      display.print("A. Hundreds");
                      display.print(" (");
                      display.print(hVal * 100);
                      display.print(")");
                      display.setCursor(1, 25);
                      display.print("B. Tens");
                      display.print(" (");
                      display.print(tVal * 10);
                      display.print(")");
                      display.setCursor(1, 35);
                      display.print("C. Ones");
                      display.print(" (");
                      display.print(oVal);
                      display.print(")");
                      display.display();
                      valMessage = 0;
                    }
                    if (key == 17) {
                      editvalue = 30;
                    }
                    if (key == 18) {
                      editvalue = 31;
                    }
                    if (key == 19) {
                      editvalue = 32;
                    }

                    switch (editvalue) {
                      case HUNDREDSEDIT:
                        display.clearDisplay();
                        display.setTextSize(1);
                        display.setTextColor(WHITE);
                        display.setCursor(1, 0);
                        display.print("Select New Hundreds Value.");
                        display.display();
                        if (key == 0) {
                          hVal = 0;
                          state = 5;
                        }
                        if (key == 1) {
                          hVal = 0;
                          state = 5;
                        }
                        if (key == 2) {
                          hVal = 2;
                          state = 5;
                        }
                        if (key == 3) {
                          hVal = 3;
                          state = 5;
                        }
                        if (key == 4) {
                          hVal = 4;
                          state = 5;
                        }
                        if (key == 5) {
                          hVal = 5;
                          state = 5;
                        }
                        if (key == 6) {
                          hVal = 6;
                          state = 5;
                        }
                        if (key == 7) {
                          hVal = 7;
                          state = 5;
                        }
                        if (key == 8) {
                          hVal = 8;
                          state = 5;
                        }
                        if (key == 9) {
                          hVal = 9;
                          state = 5;
                        }

                        break;

                      case TENSEDIT:
                        display.clearDisplay();
                        display.setTextSize(1);
                        display.setTextColor(WHITE);
                        display.setCursor(1, 0);
                        display.print("Select New Tens Value.");
                        display.display();
                        if (key == 0) {
                          tVal = 0;
                          state = 5;
                        }
                        if (key == 1) {
                          tVal = 0;
                          state = 5;
                        }
                        if (key == 2) {
                          tVal = 2;
                          state = 5;
                        }
                        if (key == 3) {
                          tVal = 3;
                          state = 5;
                        }
                        if (key == 4) {
                          tVal = 4;
                          state = 5;
                        }
                        if (key == 5) {
                          tVal = 5;
                          state = 5;
                        }
                        if (key == 6) {
                          tVal = 6;
                          state = 5;
                        }
                        if (key == 7) {
                          tVal = 7;
                          state = 5;
                        }
                        if (key == 8) {
                          tVal = 8;
                          state = 5;
                        }
                        if (key == 9) {
                          tVal = 9;
                          state = 5;
                        }
                        break;



                      case ONESEDIT:
                        display.clearDisplay();
                        display.setTextSize(1);
                        display.setTextColor(WHITE);
                        display.setCursor(1, 0);
                        display.print("Select New Ones Value.");
                        display.display();
                        if (key == 0) {
                          oVal = 0;
                          state = 5;
                        }
                        if (key == 1) {
                          oVal = 0;
                          state = 5;
                        }
                        if (key == 2) {
                          oVal = 2;
                          state = 5;
                        }
                        if (key == 3) {
                          oVal = 3;
                          state = 5;
                        }
                        if (key == 4) {
                          oVal = 4;
                          state = 5;
                        }
                        if (key == 5) {
                          oVal = 5;
                          state = 5;
                        }
                        if (key == 6) {
                          oVal = 6;
                          state = 5;
                        }
                        if (key == 7) {
                          oVal = 7;
                          state = 5;
                        }
                        if (key == 8) {
                          oVal = 8;
                          state = 5;
                        }
                        if (key == 9) {
                          oVal = 9;
                          state = 5;
                        }
                        break;

                    }
                    break;

                  case RESTART:
                    display.clearDisplay();
                    display.setTextSize(1);
                    display.setTextColor(WHITE);
                    display.setCursor(1, 0);
                    display.print("RESTART.");
                    display.setCursor(1, 20);
                    display.print("Restarting will move you all the way back to Motor Select.");
                    display.setCursor(1, 50);
                    display.print("1/Confirm | 0/Deny");
                    display.display();

                    if (key == 0) {
                      state = 8;
                      editMessage = 1;
                      edit = -1;
                    } else if (key == 1) {
                      state = 0;
                    }

                    break;

                }
              }
              break;

            } break;
        }
      }
  }
}


/*
  display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(1, 10);
      display.print("Space");
      display.display();
*/