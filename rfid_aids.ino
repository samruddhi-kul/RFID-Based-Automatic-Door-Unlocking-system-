/*Door lock system code
 * https://srituhobby.com
 */
 
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
Servo myservo;
#define SS_PIN 10
#define RST_PIN 9
String UID = "D3 84 88 A9";
String UID1 = "22 E5 5B 21";
byte lock = 0;
int buzzer=2;
int relay=3;
int button=4;

LiquidCrystal_I2C lcd(0x27, 16, 2);
MFRC522 rfid(SS_PIN, RST_PIN);


void setup() {
  myservo.write(0);   
  pinMode(buzzer,OUTPUT);
  pinMode(relay,OUTPUT);
  pinMode(button,INPUT_PULLUP);
  digitalWrite(relay,1);
  myservo.attach(8);
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  SPI.begin();
  rfid.PCD_Init();
  lcd.print("****Welcome****");
  lcd.setCursor(0,1);
  lcd.print("AI-DS Department");
  delay(1500);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Project Name");
  delay(1500);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("RFID Based ");
  lcd.setCursor(0,1);
  lcd.print("Door Unlocking Stm");
  delay(1500);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Guidance");
  lcd.setCursor(0,1);
  lcd.print("Prof K.K.L Sir");
  delay(1500);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Prepared By:");
  lcd.setCursor(0,1);
  lcd.print("SE AIDS");
  delay(1500);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Ms.Vaishnavi");
  lcd.setCursor(0,1);
  lcd.print("Ms.Monali");
  delay(1500);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Ms.Samruddhi");
   delay(1500);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Second Year");
  lcd.setCursor(0,1);
  lcd.print("2022-23");
  delay(1500);
  lcd.clear();
  
}

void loop() {
  int rohan=digitalRead(button);
  if(rohan==0)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Emergency S/w");
    lcd.setCursor(0, 1);
    lcd.print("Door is Open");
    digitalWrite(relay,0);
    servo();
    digitalWrite(relay,1);
    delay(1500);
    lcd.clear();
    lcd.print("Door is Closed");
     delay(1500);
    lcd.clear();
    lock = 0;
    
    }
  lcd.setCursor(4, 0);
  lcd.print("Welcome!");
  lcd.setCursor(1, 1);
  lcd.print("Put your card");
  if ( ! rfid.PICC_IsNewCardPresent())
    return;
  if ( ! rfid.PICC_ReadCardSerial())
    return;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Scanning");
  Serial.print("NUID tag is :");
  String ID = "";
  for (byte i = 0; i < rfid.uid.size; i++) {
    lcd.print(".");
    ID.concat(String(rfid.uid.uidByte[i] < 0x10 ? " 0" : " "));
    ID.concat(String(rfid.uid.uidByte[i], HEX));
    delay(300);
  }
  ID.toUpperCase();
   
    if ((ID.substring(1) == UID && lock == 0 )||(ID.substring(1) == UID1 && lock == 0 ))
  {
     digitalWrite(buzzer,1);
     delay(100);
      digitalWrite(buzzer,0);
     delay(100);
     digitalWrite(buzzer,1);
     delay(100);
     digitalWrite(buzzer,0);
     delay(100);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Valid User");
    lcd.setCursor(0, 1);
    lcd.print("Door is Open");
    digitalWrite(relay,0);
    servo();
    digitalWrite(relay,1);
    delay(1500);
    lcd.clear();
    lcd.print("Door is Closed");
     delay(1500);
    lcd.clear();
    lock = 0;
  } 
   else
  {
    digitalWrite(buzzer,1);
     delay(1000);
      digitalWrite(buzzer,0);
     delay(1000);
     digitalWrite(buzzer,1);
     delay(1000);
     digitalWrite(buzzer,0);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Wrong card!");
    lcd.setCursor(0, 1);
    lcd.print("Put Valid Card");
    delay(1500);
    lcd.clear();
    
     delay(1000);
  }
}
void servo()
{
  int pos;

  for (pos = 0; pos <= 90; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  delay(5000);
  for (pos = 90; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  
  }
