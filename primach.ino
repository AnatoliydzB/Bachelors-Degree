#include <SPI.h>
#include <RF24.h>

// Ініціалізація об'єкта radio із зазначенням пінів CE та CSN
RF24 radio(7,8);

// Визначення того ж каналу, що і у передавача
const byte address[6] = "00105";  

void setup() {
  Serial.begin(9600);             // Ініціалізація серійного зв’язку для відображення отриманих даних
  radio.begin();                  // Ініціалізація радіомодуля
  radio.openReadingPipe(0, address);  // Встановлення каналу приймання
  radio.setPALevel(RF24_PA_LOW);   // Встановлюємо рівень потужності
  radio.startListening();         // Перемикаємо модуль у режим приймача
}
int people=0;
void loop() {
  // Якщо доступні дані для читання, читаємо їх
  if (radio.available()) {
    char receivedText[32] = "";  // Резервуємо буфер для отриманого тексту (32 байти – стандартний розмір буфера)
    radio.read(&receivedText, sizeof(receivedText));  // Читаємо отримане повідомлення
    Serial.println(receivedText);
    if(receivedText[0]=='+') people++;
    if(receivedText[0]=='-') people--;
    Serial.println(String("****** ")+people+" ******");
  }
}
