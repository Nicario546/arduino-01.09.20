#include <Servo.h>
#include <SPI.h>
#include <MFRC522.h> // библиотека "RFID".
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);
unsigned long uidDec, uidDecTemp;  // для храниения номера метки в десятичном формате
Servo servo;
void setup() {
  Serial.begin(9600);
  SPI.begin();  //  инициализация SPI / Init SPI bus.
  mfrc522.PCD_Init();     // инициализация MFRC522 / Init MFRC522 card.
  servo.attach(6);
  servo.write(0);  // устанавливаем серву в закрытое сосотояние
}
void loop() {
  // Поиск новой метки
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }
  // Выбор метки
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }
  uidDec = 0;
  // Выдача серийного номера метки.
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    uidDecTemp = mfrc522.uid.uidByte[i];
    uidDec = uidDec * 256 + uidDecTemp;
  }
 
  if (uidDec == 2841136825) // Сравниваем Uid метки, если он равен заданому то серва открывает.
  {
    Serial.println("Сикорский Артем пришол");
    servo.write(90); // Поворациваем серву на угол 90 градусов(Отпираем какой либо механизм: задвижку, поворациваем ключ и т.д.)
    delay(3000); // пауза 3 сек и механизм запирается.
    servo.write(0);  // устанавливаем серву в закрытое сосотояние
  }

    if (uidDec == 1773590713) // Сравниваем Uid метки, если он равен заданому то серва открывает.
  {
    Serial.println("Олег Игоревич пришол");
    servo.write(90); // Поворациваем серву на угол 90 градусов(Отпираем какой либо механизм: задвижку, поворациваем ключ и т.д.)
    delay(3000); // пауза 3 сек и механизм запирается.
    servo.write(0);  // устанавливаем серву в закрытое сосотояние
  }
}
