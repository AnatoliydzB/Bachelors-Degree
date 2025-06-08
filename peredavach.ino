#include <SPI.h>
#include <RF24.h>

RF24 radio(7, 8);
const byte address[6] = "00105";


void setup() {
  Serial.begin(9600);

  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_LOW);
  /*
  RF24_PA_MIN Приблизний рівень: близько -18 dBm
  Використання: Найнижчий рівень потужності. Застосовується, коли потрібна мінімальна потужність для економії енергії або при дуже коротких відстанях зв'язку.

  RF24_PA_LOW Приблизний рівень: близько -12 dBm
  Використання: Нижчий рівень потужності, який забезпечує дещо більшу дальність, ніж мінімальний, при збереженні досить низького споживання енергії. Часто використовується в умовах, коли важлива енергоефективність.

  RF24_PA_HIGH Приблизний рівень: близько -6 dBm
  Використання: Високий рівень, який забезпечує покращену дальність передачі. Проте разом із збільшенням потужності може зрости і споживання енергії.

  RF24_PA_MAX Приблизний рівень: 0 dBm
  Використання: Максимальний рівень потужності для передачі даних. Використовується, коли потрібно максимальне покриття або дальність, але це також може призвести до вищого енергоспоживання та більшої ймовірності завади від інших пристроїв.
*/
  radio.stopListening();

  pinMode(2, INPUT); // нормальний
  pinMode(3, INPUT); // інвертований

  
}
int people=0;
void loop() {
  if(digitalRead(2)==LOW){
   unsigned long time = millis();
    while(digitalRead(2)==LOW ){ 
      delay(1);
      if(digitalRead(3)==HIGH){  
        if((millis()-time)>10){ //визначаємо час між спрацюваннями між датчиками
          people++;
          Serial.println("+");
          char msg[16];
          sprintf(msg, "+People:%d", people);
          radio.write(&msg, sizeof(msg));
          break;
        }
      }
    }
  }
   while(digitalRead(2)==LOW ){} //чекаємо поки датчик не вимкнеться

     if(digitalRead(3)==HIGH){
   unsigned long time = millis();
    while(digitalRead(3)==HIGH ){ 
      delay(1);
      if(digitalRead(2)==LOW){  
        if((millis()-time)>10){ //визначаємо час між спрацюваннями між датчиками
          Serial.println("-");
          people--;
          char msg[16];
          sprintf(msg, "-People:%d", people);
          radio.write(&msg, sizeof(msg));
          break;
        }
      }
    }
  }
   while(digitalRead(3)== HIGH){} //чекаємо поки датчик не вимкнеться


}

