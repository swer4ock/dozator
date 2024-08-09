#include <TFT_eSPI.h>
#include <ESP32Servo.h>

Servo myservo;  // создаем объект сервопривода

int servoPin = 1;  // Пин ESP32 для сигнала

void setup() {
  Serial.begin(115200);  // инициализация серийного соединения для вывода
  myservo.attach(servoPin);  // подключаем сервопривод к выбранному пину
  Serial.println("Сервопривод подключен");
}

void loop() {
  // Проверка сервопривода с ограничением до 90 градусов на максимальной скорости
  Serial.println("Тест до 90 градусов на максимальной скорости:");
  
  myservo.write(0);  // устанавливаем сервопривод в начальное положение
  delay(500);  // ждем полсекунды для стабилизации
  
  myservo.write(90);  // перемещаем сервопривод на 90 градусов
  delay(500);  // ждем полсекунды для стабилизации
  
  myservo.write(0);  // возвращаем сервопривод в начальное положение
  delay(500);  // ждем полсекунды для стабилизации
}






// ///начало рабочего кода

// #include <TFT_eSPI.h>
// #include <HX711.h>
// #include <ESP32Servo.h>
// #include <Arduino.h>
// #include <IRremoteESP8266.h>
// #include <IRrecv.h>
// #include <IRutils.h>
// // Add this line to define the LCD backlight pin
// #define LCDpin 15

// #define IR_RECEIVE_PIN 16
// IRrecv irrecv(IR_RECEIVE_PIN);
// decode_results results;
// bool forceUpdate = false; // Флаг принудительного обновления экрана


// const int dtPin = 43;    // Пин DT подключен к GPIO 3
// const int sckPin = 44;   // Пин SCK подключен к GPIO 2
// const int servo1Pin = 2; // Пин для первого сервопривода
// const int servo2Pin = 3; // Пин для второго сервопривода
// const int startButtonPin = 11; // Пин для кнопки открытия сервоприводов
// const int tareButtonPin = 12; // Пин для кнопки тары



// // Пины управления L298N
// const int bin1Pin = 17; //bIN1
// // const int in2Pin = 0; //
// const int pwmbPin = 21; //pwmb еще нужен stby указать
// const int stbyPin = 18;

// Servo servo1;
// Servo servo2;

// const float calibrationFactor = 0.002496; // Калибровочный коэффициент
// // const int targetWeightThreshold = 100; // Порог веса для закрытия сервоприводов
// int targetWeightThreshold = 100; // Начальное значение, допускается изменение


// bool servosOpen = false; // Флаг открытия/закрытия сервоприводов
// bool motorRunning = false; // Флаг мотора

// TFT_eSPI tft = TFT_eSPI();
// HX711 scale;

// unsigned long previousMillis = 0;
// const long interval = 100; // Интервал между измерениями в миллисекундах

// // Буфер для усреднения значений веса
// const int weightBufferLength = 10;
// float weightBuffer[weightBufferLength];
// int bufferIndex = 0;

// // Прототипы функций
// void displayWeight(float weight, int targetThreshold);
// void openServos();
// void closeServos();
// void startMotor();
// void stopMotor();
// void displayState();
// void tareWeight();
// float getSmoothedWeight(float currentWeight);


 
// void handleIRInput(unsigned long code);


// void setup() {
// irrecv.enableIRIn(); // Включение приема ИК-сигналов


//   // Настройка пинов 
//   pinMode(bin1Pin, OUTPUT);
//   // pinMode(in2Pin, OUTPUT);
//   pinMode(pwmbPin, OUTPUT);
//   pinMode(stbyPin, OUTPUT);


//   // Начальное состояние
//   digitalWrite(bin1Pin, HIGH);
//   // digitalWrite(in2Pin, HIGH);
//   digitalWrite(stbyPin, HIGH); // Выход из режима ожидания

//   // Add these lines to configure the LCD backlight pin
//   pinMode(LCDpin, OUTPUT);
//   digitalWrite(LCDpin, HIGH);


//   // Настройка PWM для управления скоростью мотора (если нужно)
//   //analogWrite(enAPin, 255); // Максимальная скорость

//   Serial.begin(115200);
//   scale.begin(dtPin, sckPin);

//   tft.init();
//   tft.setRotation(3);
//   //tft.fillScreen(TFT_GREEN);
//   tft.setTextSize(3);

//   pinMode(startButtonPin, INPUT_PULLUP);
//   pinMode(tareButtonPin, INPUT_PULLUP);

//   servo1.attach(servo1Pin);
//   servo2.attach(servo2Pin);
// }

// float previousWeight = 0.0;
// unsigned long startMillis = 0;
// //const int analogInputPin = 4; 

// void loop() {

//  float currentWeight = scale.get_units(1) * calibrationFactor; // Пример получения текущего веса
  

//   if (irrecv.decode(&results)) {
//     handleIRInput(results.value);
//     irrecv.resume(); // Готовимся к приему следующего сигнала
//   }
 
//   // displayWeight(currentWeight, targetWeightThreshold);



//   digitalWrite(LCDpin, HIGH);


//           if (currentWeight >= targetWeightThreshold && motorRunning) {
//                 Serial.println("Остановка мотора");
//                 stopMotor();
//             } else if (currentWeight < targetWeightThreshold && !servosOpen && !motorRunning) {
//                 Serial.println("Запуск мотора");
//                 startMotor();
//             }

//     // Если кнопка "старт" нажата и мотор выключен, открыть сервоприводы и включить мотор // LOW && !motorRunning
//     if (digitalRead(startButtonPin) == LOW) {
//         stopMotor();
//         delay(1000);
//         openServos();
//         delay(1500);
//         closeServos();
//         delay(1500);
//         startMotor();
        
//     }

//     // Если кнопка "тара" нажата, обнулить вес
//     if (digitalRead(tareButtonPin) == LOW) {
//         tareWeight();
//     }

//       // Вывод отладочной информации
//   Serial.print("Вес: ");
//   Serial.println(currentWeight);
//   Serial.print("Состояние мотора: ");
//   Serial.println(motorRunning ? "Включен" : "Выключен");

//   displayWeight(currentWeight, targetWeightThreshold);
// }


// void handleIRInput(unsigned long code) {
//   switch (code) {
//     case 0xFF18E7: // Код для увеличения порогового веса
//       targetWeightThreshold += 10;
//       forceUpdate = true;
//       break;
//     case 0xFF4AB5: // Код для уменьшения порогового веса
//       targetWeightThreshold = max(10, targetWeightThreshold - 10);
//       forceUpdate = true;
//       break;
//   }
// }





// void openServos() {
//     servo1.write(0);
//     servo2.write(90);
//     servosOpen = true;
//     startMillis = millis(); // Запоминаем время открытия сервопривода
//     Serial.println("OpenServos");
// }

// void closeServos() {
//     servo1.write(94);
//     servo2.write(3);
//     servosOpen = false;
//     Serial.println("CloseServos");
// }

// void startMotor() {
//     // Запуск мотора (ваш код)
//     motorRunning = true;
//     digitalWrite(stbyPin, HIGH); // Выход из режима ожидания
//     digitalWrite(bin1Pin, HIGH);
//     // digitalWrite(in2Pin, LOW);
//     analogWrite(pwmbPin, 255);
//    Serial.println("Motor start");
// }

// void stopMotor() {
//     // Остановка мотора (ваш код)
//     motorRunning = false;
//     digitalWrite(bin1Pin, LOW);
//     // digitalWrite(in2Pin, LOW);
//     analogWrite(pwmbPin, 0);
//     digitalWrite(stbyPin, LOW); // Перевод в режим ожидания
//    Serial.println("Motor stop");
// }

// // // void displayState() {
// //     // Вывод состояния работы мотора и состояния флага сервопривода на экран (ваш код)
// // }

// void tareWeight() {
//   scale.tare();
//   Serial.println("TARE GO");
// }

// // Добавьте переменную для хранения последнего отображенного значения веса
// int lastDisplayedWeight = 0;

// void displayWeight(float weight, int targetThreshold) {
//   int roundedWeight = round(weight);

//   // Проверяем, нужно ли обновить экран
//   if (abs(roundedWeight - lastDisplayedWeight) >= 1 || forceUpdate) {
//     tft.fillScreen(TFT_GREEN);
//     tft.setTextColor(TFT_BLACK);

//     // Строки состояния для сервопривода и мотора
//     String servoState = servosOpen ? "On" : "Off";
//     String motorState = motorRunning ? "On" : "Off";

//     // Отображаем вес и пороговое значение
//     String weightString = String(roundedWeight) + " g";
//     String thresholdString = "VES: " + String(targetThreshold) + " g";
//     String servoString = "Servo: " + servoState;
//     String motorString = "Motor: " + motorState;

//     // Расчет позиций для вывода текста
//     int startY = 15; // Начальная Y-позиция для текста
//     int stepY = 35; // Шаг между строками

//     tft.setCursor(0, startY);
//     tft.println(weightString);
//     tft.setCursor(0, startY + stepY);
//     tft.println(thresholdString);
//     tft.setCursor(0, startY + 2 * stepY);
//     tft.println(servoString);
//     tft.setCursor(0, startY + 3 * stepY);
//     tft.println(motorString);

//     // Обновляем последнее отображенное значение и сбрасываем флаг принудительного обновления
//     lastDisplayedWeight = roundedWeight;
//     forceUpdate = false;
//   }
// }




// float getSmoothedWeight(float currentWeight) {
//   // Усреднение значений веса
//   weightBuffer[bufferIndex] = currentWeight;
//   bufferIndex = (bufferIndex + 1) % weightBufferLength;

//   float sum = 0;
//   for (int i = 0; i < weightBufferLength; i++) {
//     sum += weightBuffer[i];
//   }

//   return sum / weightBufferLength;
// }





//////////////////конец рабочего кода


// //////IR зелененькая работает которая использует резисторы и данные считывает все норм, значит код рабочии и меняет вес ОК жмем и наверх вниз все отображается на экране 14 марта 24г. 
// #include <TFT_eSPI.h>
// #include <HX711.h>
// #include <ESP32Servo.h>
// #include <Arduino.h>
// #include <IRrecv.h>
// #include <IRremoteESP8266.h>
// #include <IRutils.h>

// #define IR_RECEIVE_PIN 16


// IRrecv irrecv(IR_RECEIVE_PIN);
// decode_results results;

// TFT_eSPI tft = TFT_eSPI();  // Создаем объект дисплея

// int weight = 100; // Начальный вес
// bool inMenu = false; // Находится ли пользователь в меню

// // Прототипы функций
// void showMenu();
// void showWeight();

// void setup() {
//   Serial.begin(115200);
//   irrecv.enableIRIn(); // Включение приема ИК-сигналов

//   tft.init();
//   tft.setRotation(1); // Поворот дисплея, если необходимо
//   tft.fillScreen(TFT_BLACK);
//   tft.setTextColor(TFT_WHITE, TFT_BLACK); // Установка цвета текста и фона
//   tft.setTextSize(2); // Размер текста
  
//   showWeight(); // Показываем начальный вес
// }

// void loop() {
//   if (irrecv.decode(&results)) {
//     if (results.value == 0xFF38C7) { // Открыть/закрыть меню
//       inMenu = !inMenu;
//       showMenu(); // Отображаем состояние меню
//     } else if (inMenu && results.value == 0xFF18E7) { // Увеличить вес
//       weight += 10;
//       showWeight();
//     } else if (inMenu && results.value == 0xFF4AB5) { // Уменьшить вес
//       weight = max(10, weight - 10); // Предотвращаем установку веса меньше 10
//       showWeight();
//     }
//     irrecv.resume();
//   }
// }

// void showMenu() {
//   tft.fillScreen(TFT_BLACK); // Очищаем экран
//   if (inMenu) {
//     tft.drawString("Меню настройки веса:", 10, 20, 2); // Указываем, что меню открыто
//   } else {
//     tft.drawString("Меню закрыто.", 10, 20, 2);
//   }
//   showWeight(); // Показываем текущий вес
// }

// void showWeight() {
//   tft.setTextDatum(MC_DATUM);
//   tft.fillScreen(TFT_BLACK); // Очищаем экран
//   tft.drawString("Вес: " + String(weight) + " г", tft.width()/2, tft.height()/2, 2);
//   tft.setTextDatum(TL_DATUM); // Возвращаем базовую точку текста обратно в левый верхний угол
// }

///////////////////////
///////////////////////
///////////////////////
///////////////////////
// FFA25D 1
// FF629D 2
// FFE21D 3
// FF22DD 4
// FF02FD 5
// FFC23D 6
// FFE01F 7
// FFA857 8
// FF906F 9
// FF9867 0
// FF6897 *
// FFB04F #
// FF18E7 вверх
// FF4AB5 вниз
// FF10EF влево
// FF5AA5 вправо
// FF38C7 кнопка OK


/////////Незнаю может и рабочии может и нет верхнии был последним загруженным который скорее всего работает 12 марта 2024
// #include <IRremote.h>
// #include <TFT_eSPI.h>

// const int RECV_PIN = 2; // Укажите ваш пин для подключения ИК-датчика

// IRrecv irrecv(RECV_PIN);
// decode_results results;

// TFT_eSPI tft = TFT_eSPI();

// void setup() {
//   Serial.begin(9600);
//   irrecv.enableIRIn(); // Инициализация ИК-датчика

//   tft.init();
//   tft.setRotation(3); // В зависимости от вашего TFT-дисплея может потребоваться другое значение
// }

// void loop() {
//   if (irrecv.decode(&results)) {
//     // Получение сырых данных
//     Serial.println("Raw Data:");
//     for (int i = 0; i < results.rawlen; i++) {
//       Serial.print(results.rawbuf[i]);
//       Serial.print(" ");
//     }
//     Serial.println();

//     // Вывод информации на экран TFT
//     tft.fillScreen(TFT_BLACK);
//     tft.setCursor(0, 0);
//     tft.setTextColor(TFT_WHITE);
//     tft.setTextSize(2);
//     tft.println("Raw Data:");
//     for (int i = 0; i < results.rawlen; i++) {
//       tft.print(results.rawbuf[i]);
//       tft.print(" ");
//     }

//     irrecv.resume(); // Продолжаем прослушивание для следующего сигнала
//   }
// }




// //// Все работает!!!!!! здесь нет ИК приемника от 14 марта 24г

// #include <TFT_eSPI.h>
// #include <HX711.h>
// #include <ESP32Servo.h>
// #include <Arduino.h>

// // Add this line to define the LCD backlight pin
// #define LCDpin 15


// const int dtPin = 43;    // Пин DT подключен к GPIO 3
// const int sckPin = 44;   // Пин SCK подключен к GPIO 2
// const int servo1Pin = 2; // Пин для первого сервопривода
// const int servo2Pin = 3; // Пин для второго сервопривода
// const int startButtonPin = 11; // Пин для кнопки открытия сервоприводов
// const int tareButtonPin = 12; // Пин для кнопки тары



// // Пины управления L298N
// const int bin1Pin = 17; //bIN1
// // const int in2Pin = 0; //
// const int pwmbPin = 21; //pwmb еще нужен stby указать
// const int stbyPin = 18;

// Servo servo1;
// Servo servo2;

// const float calibrationFactor = 0.002496; // Калибровочный коэффициент
// const int targetWeightThreshold = 100; // Порог веса для закрытия сервоприводов

// bool servosOpen = false; // Флаг открытия/закрытия сервоприводов
// bool motorRunning = false; // Флаг мотора

// TFT_eSPI tft = TFT_eSPI();
// HX711 scale;

// unsigned long previousMillis = 0;
// const long interval = 100; // Интервал между измерениями в миллисекундах

// // // Параметры для плавного старта и остановки двигателя
// // const int accelerationTime = 1000; // Время ускорения в миллисекундах
// // const int decelerationTime = 1000; // Время замедления в миллисекундах
// // unsigned long accelerationStartMillis = 0;
// // unsigned long decelerationStartMillis = 0;

// // Буфер для усреднения значений веса
// const int weightBufferLength = 10;
// float weightBuffer[weightBufferLength];
// int bufferIndex = 0;

// // Прототипы функций
// void displayWeight(float weight, int targetThreshold);
// void openServos();
// void closeServos();
// void startMotor();
// void stopMotor();
// void displayState();
// void tareWeight();
// float getSmoothedWeight(float currentWeight);

// void setup() {
//   // Настройка пинов
//   pinMode(bin1Pin, OUTPUT);
//   // pinMode(in2Pin, OUTPUT);
//   pinMode(pwmbPin, OUTPUT);
//   pinMode(stbyPin, OUTPUT);


//   // Начальное состояние
//   digitalWrite(bin1Pin, LOW);
//   // digitalWrite(in2Pin, HIGH);
//   digitalWrite(stbyPin, LOW); // Выход из режима ожидания

//   // Add these lines to configure the LCD backlight pin
//   pinMode(LCDpin, OUTPUT);
//   digitalWrite(LCDpin, LOW);


//   // Настройка PWM для управления скоростью мотора (если нужно)
//   //analogWrite(enAPin, 255); // Максимальная скорость

//   Serial.begin(115200);
//   scale.begin(dtPin, sckPin);

//   tft.init();
//   tft.setRotation(3);
//   //tft.fillScreen(TFT_GREEN);
//   tft.setTextSize(3);

//   pinMode(startButtonPin, INPUT_PULLUP);
//   pinMode(tareButtonPin, INPUT_PULLUP);

//   servo1.attach(servo1Pin);
//   servo2.attach(servo2Pin);
// }

// float previousWeight = 0.0;
// unsigned long startMillis = 0;
// //const int analogInputPin = 4; 

// void loop() {

//   // Считываем напряжение с аналогового входа
//   //int sensorValue = analogRead(analogInputPin);

//   // Преобразуем считанное значение в напряжение (в вольтах)
//   //float voltage = sensorValue * (3.3 / 4095);

//   // Выводим результат в монитор последовательного порта
//   // Serial.print("Analog Read: ");
//   // Serial.print(sensorValue);
//   // Serial.print(", Voltage: ");
//   // Serial.println(voltage);

//   // If the LCD backlight is not turning on, you can try adding the following lines
//   // to explicitly turn on the backlight after the initial setup.
//   digitalWrite(LCDpin, HIGH);


//     // Если сервоприводы закрыты и вес менее 100гр, запустить мотор
//     if (scale.is_ready()) {
//         float weight = getSmoothedWeight(scale.get_units(1) * calibrationFactor);

//             // Проверяем, изменился ли вес
//         if (weight != previousWeight) {
//             Serial.println(weight);
//             displayWeight(weight, targetWeightThreshold);
//             // Обновляем переменную предыдущего веса
//             previousWeight = weight;
//         }

//         if (weight < targetWeightThreshold && !servosOpen && !motorRunning) {
//             startMotor();
//             // Обновляем переменную предыдущего веса
//            // previousWeight = weight;
//         } else if (weight >= targetWeightThreshold && !servosOpen && motorRunning) {
//             stopMotor();
//            // displayWeight(weight, targetWeightThreshold);
//             // Обновляем переменную предыдущего веса
//            // previousWeight = weight;
//         }
//     }

//     // Если кнопка "старт" нажата и мотор выключен,а есть high это замкнута открыть сервоприводы и включить мотор // LOW && !motorRunning
//     if (digitalRead(startButtonPin) == LOW) {
//         stopMotor();
//         delay(1000);
//         openServos();
//         delay(1500);
//         closeServos();
//         delay(1500);
//     }

//     // Если кнопка "тара" нажата, обнулить вес
//     if (digitalRead(tareButtonPin) == LOW) {
//         tareWeight();
//     }
// }

// void openServos() {
//     servo1.write(0);
//     servo2.write(0);
//     servosOpen = true;
//     startMillis = millis(); // Запоминаем время открытия сервопривода
//     //Serial.println("OpenServos");
// }

// void closeServos() {
//     servo1.write(90);
//     servo2.write(90);
//     servosOpen = false;
//     //Serial.println("CloseServos");
// }

// void startMotor() {
//     // Запуск мотора (ваш код)
//     motorRunning = true;
//     digitalWrite(stbyPin, HIGH); // Выход из режима ожидания
//     digitalWrite(bin1Pin, HIGH);
//     // digitalWrite(in2Pin, LOW);
//     analogWrite(pwmbPin, 255);
//    Serial.println("Motor start");
// }

// void stopMotor() {
//     // Остановка мотора (ваш код)
//     motorRunning = false;
//     digitalWrite(bin1Pin, LOW);
//     // digitalWrite(in2Pin, LOW);
//     analogWrite(pwmbPin, 0);
//     digitalWrite(stbyPin, LOW); // Перевод в режим ожидания
//    Serial.println("Motor stop");
// }

// // // void displayState() {
// //     // Вывод состояния работы мотора и состояния флага сервопривода на экран (ваш код)
// // }

// void tareWeight() {
//   scale.tare();
// }

// // Добавьте переменную для хранения последнего отображенного значения веса
// int lastDisplayedWeight = 0;

// void displayWeight(float weight, int targetThreshold) {
//   // Округляем значение веса до 1 грамма
//   int roundedWeight = round(weight);

//   // Проверяем разницу с последним отображенным значением
//   if (abs(roundedWeight - lastDisplayedWeight) >= 1) {
//     tft.fillScreen(TFT_GREEN);
//     tft.setTextColor(TFT_BLACK);

//     String weightString = String(roundedWeight) + " g";
//     String thresholdString = String(targetThreshold) + " g";

//     int textWidth = max(tft.textWidth(weightString), tft.textWidth(thresholdString));
//     int textX = (tft.width() - textWidth) / 2;
//     int textY = (tft.height() - 160) / 2;

//     tft.setCursor(textX, textY);
//     tft.print(weightString);

//     int thresholdX = (tft.width() - textWidth) / 2;
//     int thresholdY = textY + 50;

//     tft.setCursor(thresholdX, thresholdY);
//     tft.print(thresholdString);

//     // Обновляем последнее отображенное значение
//     lastDisplayedWeight = roundedWeight;
//   }
// }



// float getSmoothedWeight(float currentWeight) {
//   // Усреднение значений веса
//   weightBuffer[bufferIndex] = currentWeight;
//   bufferIndex = (bufferIndex + 1) % weightBufferLength;

//   float sum = 0;
//   for (int i = 0; i < weightBufferLength; i++) {
//     sum += weightBuffer[i];
//   }

//   return sum / weightBufferLength;
// }





// В этом примере использована библиотека HX711, и предполагается, что кнопка калибровки нуля подключена к пину 14,
//  а кнопка калибровки с известным весом подключена к пину 15. Пожалуйста, убедитесь, что вы используете правильные пины 
//  для ваших конкретных подключений.

// Также обратите внимание, что код выполняет измерение веса с использованием scale.get_units(10), 
// где 10 - это количество средних значений. Это может помочь уменьшить шум в измерениях. 
// Вы можете настроить это значение в зависимости от ваших требований.

// #include "HX711.h"

// const int dtPin = 2;   // Пин DT подключен к GPIO 2
// const int sckPin = 3;  // Пин SCK подключен к GPIO 3

// HX711 scale;

// void setup() {
//   Serial.begin(115200);
//   scale.begin(dtPin, sckPin);
// }

// void loop() {
//   if (digitalRead(14) == LOW) {  // Проверка кнопки калибровки нуля
//     scale.tare();  // Выполнение калибровки нуля
//     Serial.println("Zero calibration completed");
//     delay(1000);  // Пауза для избежания ложных срабатываний
//   }

//   if (digitalRead(15) == LOW) {  // Проверка кнопки калибровки с известным весом
//     Serial.println("Place a known weight on the scale...");
//     delay(5000);  // Пауза для пользователя, чтобы установить вес
//     float knownWeight = scale.get_units(10);  // Измерение веса
//     scale.set_scale(knownWeight / 100.0);  // Установка коэффициента масштабирования
//     Serial.println("Known weight calibration completed");
//     delay(1000);  // Пауза для избежания ложных срабатываний
//   }

//   // Ваш основной код здесь
// }




////Внесены изменения в местах, где ранее использовалась функция delay(), чтобы избежать блокировки выполнения кода. Пожалуйста, проверьте этот вариант

// #include <TFT_eSPI.h>
// #include <HX711.h>
// #include <ESP32Servo.h>
// #include <Arduino.h>

// const int dtPin = 3;    // Пин DT подключен к GPIO 3
// const int sckPin = 2;   // Пин SCK подключен к GPIO 2
// const int servo1Pin = 43; // Пин для первого сервопривода
// const int servo2Pin = 44; // Пин для второго сервопривода
// const int startButtonPin = 18; // Пин для кнопки открытия сервоприводов
// const int tareButtonPin = 17; // Пин для кнопки тары

// // Пины управления L298N
// const int in1Pin = 12;
// const int in2Pin = 13;
// const int enAPin = 21;

// Servo servo1;
// Servo servo2;

// const float calibrationFactor = 0.002496; // Калибровочный коэффициент
// const int targetWeightThreshold = 100; // Порог веса для закрытия сервоприводов

// bool servosOpen = false; // Флаг открытия/закрытия сервоприводов

// TFT_eSPI tft = TFT_eSPI();
// HX711 scale;

// unsigned long previousMillis = 0;
// const long interval = 100; // Интервал между измерениями в миллисекундах

// // Параметры для плавного старта и остановки двигателя
// const int accelerationTime = 1000; // Время ускорения в миллисекундах
// const int decelerationTime = 1000; // Время замедления в миллисекундах
// unsigned long accelerationStartMillis = 0;
// unsigned long decelerationStartMillis = 0;

// // Буфер для усреднения значений веса
// const int weightBufferLength = 10;
// float weightBuffer[weightBufferLength];
// int bufferIndex = 0;

// // Прототипы функций
// void displayWeight(float weight, int targetThreshold);
// void openServos();
// void closeServos();
// void tareWeight();
// float getSmoothedWeight(float currentWeight);

// void setup() {
//   // Настройка пинов
//   pinMode(in1Pin, OUTPUT);
//   pinMode(in2Pin, OUTPUT);
//   pinMode(enAPin, OUTPUT);

//   // Начальное состояние
//   digitalWrite(in1Pin, LOW);
//   digitalWrite(in2Pin, LOW);

//   // Настройка PWM для управления скоростью мотора (если нужно)
//   analogWrite(enAPin, 255); // Максимальная скорость

//   Serial.begin(115200);
//   scale.begin(dtPin, sckPin);

//   tft.init();
//   tft.setRotation(3);
//   //tft.fillScreen(TFT_GREEN);
//   tft.setTextSize(3);

//   pinMode(startButtonPin, INPUT_PULLUP);
//   pinMode(tareButtonPin, INPUT_PULLUP);

//   servo1.attach(servo1Pin);
//   servo2.attach(servo2Pin);
// }

// void loop() {

//     if (scale.is_ready()) {
//         float weight = getSmoothedWeight(scale.get_units(10) * calibrationFactor);

//         displayWeight(weight, targetWeightThreshold);

//         // Если вес превышает порог, закрыть сервоприводы
//         if (weight >= targetWeightThreshold) {
//             closeServos();
//         }
//     }

//   // Debug
//   Serial.println("In the loop...");

//   // Если вес меньше 100 и сервоприводы закрыты, то двигаемся вперед
//   if (scale.is_ready()) {
//     float weight = getSmoothedWeight(scale.get_units(10) * calibrationFactor);
    
//     if (weight < targetWeightThreshold && !servosOpen) {
//       // Debug
//       Serial.println("Displaying weight...");

//        // Отображение веса
//       //tft.fillScreen(TFT_GREEN); // Очистим экран зеленым цветом
//       //tft.setTextColor(TFT_GREEN); // Установим цвет текста на черный

//       int textWidth = tft.textWidth("Weight: " + String(weight, 2) + " g");
//       int textX = (tft.width() - textWidth) / 2;
//       int textY = (tft.height() - 160) / 2;

//       tft.setCursor(textX, textY);
//       tft.print("Weight: ");
//       tft.print(weight, 2);
//       tft.print(" g");

//       int thresholdWidth = tft.textWidth("Threshold: " + String(targetWeightThreshold) + " g");
//       int thresholdX = (tft.width() - thresholdWidth) / 2;
//       int thresholdY = textY + 50;

//       tft.setCursor(thresholdX, thresholdY);
//       tft.print("Threshold: ");
//       tft.print(targetWeightThreshold);
//       tft.print(" g");
    

//       // Плавный старт
//       unsigned long currentMillis = millis();
//       if (currentMillis - accelerationStartMillis < accelerationTime) {
//         int accelerationValue = map(currentMillis - accelerationStartMillis, 0, accelerationTime, 0, 255);
//         analogWrite(enAPin, accelerationValue);
//       } else {
//         analogWrite(enAPin, 255);
//       }

//       // Движение вперед
//       digitalWrite(in1Pin, HIGH);
//       digitalWrite(in2Pin, LOW);
//     } else {
//       // Плавное замедление и остановка
//       unsigned long currentMillis = millis();
//       if (currentMillis - decelerationStartMillis < decelerationTime) {
//         int decelerationValue = map(currentMillis - decelerationStartMillis, 0, decelerationTime, 255, 0);
//         analogWrite(enAPin, decelerationValue);
//       } else {
//         digitalWrite(in1Pin, LOW);
//         digitalWrite(in2Pin, LOW);
//         analogWrite(enAPin, 0);
//       }
//     }
//   }

//   unsigned long currentMillis = millis();

// if (currentMillis - previousMillis >= interval) {
//     previousMillis = currentMillis;
// }


//   // Если кнопка "старт" нажата, открыть сервоприводы
//   if (digitalRead(startButtonPin) == LOW) {
//     openServos();
//   }

//   // Если кнопка "тара" нажата, обнулить вес
//   if (digitalRead(tareButtonPin) == LOW) {
//     tareWeight();
//   }
// }

// void displayWeight(float weight, int targetThreshold) {
//   Serial.println("Displaying weight...");
//   tft.fillScreen(TFT_WHITE); // Очистим экран белым цветом
//   tft.setTextColor(TFT_BLACK); // Установим цвет текста на черный

//   String weightString = "Weight: " + String(weight, 2) + " g";
//   String thresholdString = "Threshold: " + String(targetThreshold) + " g";

//   int textWidth = max(tft.textWidth(weightString), tft.textWidth(thresholdString));
//   int textX = (tft.width() - textWidth) / 2;
//   int textY = (tft.height() - 160) / 2;

//   tft.setCursor(textX, textY);
//   tft.print(weightString);

//   int thresholdX = (tft.width() - textWidth) / 2;
//   int thresholdY = textY + 50;

//   tft.setCursor(thresholdX, thresholdY);
//   tft.print(thresholdString);
// }





// void openServos() {
//   servo1.write(0);
//   servo2.write(0);
//   servosOpen = true;
// }

// void closeServos() {
//   servo1.write(90);
//   servo2.write(90);
//   servosOpen = false;
// }

// void tareWeight() {
//   scale.tare();
// }

// float getSmoothedWeight(float currentWeight) {
//   // Усреднение значений веса
//   weightBuffer[bufferIndex] = currentWeight;
//   bufferIndex = (bufferIndex + 1) % weightBufferLength;

//   float sum = 0;
//   for (int i = 0; i < weightBufferLength; i++) {
//     sum += weightBuffer[i];
//   }

//   return sum / weightBufferLength;
// }



/// работает тара все кнопки но медленно обновляется
// #include <TFT_eSPI.h>
// #include <HX711.h>
// #include <ESP32Servo.h>
// #include <Arduino.h>

// const int dtPin = 3;    // Пин DT подключен к GPIO 3
// const int sckPin = 2;   // Пин SCK подключен к GPIO 2
// const int servo1Pin = 43; // Пин для первого сервопривода
// const int servo2Pin = 44; // Пин для второго сервопривода
// const int startButtonPin = 18; // Пин для кнопки открытия сервоприводов
// const int tareButtonPin = 17; // Пин для кнопки тары

// // Пины управления L298N
// const int in1Pin = 12;
// const int in2Pin = 13;
// const int enAPin = 21;

// Servo servo1;
// Servo servo2;

// const float calibrationFactor = 0.002496; // Калибровочный коэффициент
// const int targetWeightThreshold = 100; // Порог веса для закрытия сервоприводов

// bool servosOpen = false; // Флаг открытия/закрытия сервоприводов

// TFT_eSPI tft = TFT_eSPI();
// HX711 scale;

// unsigned long previousMillis = 0;
// unsigned long forwardMillis = 0;
// unsigned long stopMillis = 0;
// const long interval = 1000; // Интервал между измерениями в миллисекундах

// // Прототипы функций
// void displayWeight(float weight, int targetThreshold);
// void openServos();
// void closeServos();
// void tareWeight();

// void setup() {
//   // Настройка пинов
//   pinMode(in1Pin, OUTPUT);
//   pinMode(in2Pin, OUTPUT);
//   pinMode(enAPin, OUTPUT);

//   // Начальное состояние
//   digitalWrite(in1Pin, LOW);
//   digitalWrite(in2Pin, LOW);

//   // Настройка PWM для управления скоростью мотора (если нужно)
//   analogWrite(enAPin, 255); // Максимальная скорость

//   Serial.begin(115200);
//   scale.begin(dtPin, sckPin);

//   tft.init();
//   tft.setRotation(3);
//   tft.fillScreen(TFT_WHITE);
//   tft.setTextSize(3);

//   pinMode(startButtonPin, INPUT_PULLUP);
//   pinMode(tareButtonPin, INPUT_PULLUP);

//   servo1.attach(servo1Pin);
//   servo2.attach(servo2Pin);
// }

// void loop() {
//   // Если вес меньше 100 и сервоприводы закрыты, то двигаемся вперед
//   if (scale.is_ready()) {
//     float weight = scale.get_units(10) * calibrationFactor;
    
//     if (weight < targetWeightThreshold && !servosOpen) {
//       // Движение вперед
//       digitalWrite(in1Pin, HIGH);
//       digitalWrite(in2Pin, LOW);
//       unsigned long forwardMillis = millis();
//       while (millis() - forwardMillis < 2000) {
//         // Дождемся движения вперед в течение 2 секунд
//       }
//       // Остановка
//       digitalWrite(in1Pin, LOW);
//       digitalWrite(in2Pin, LOW);
//       unsigned long stopMillis = millis();
//       while (millis() - stopMillis < 1000) {
//         // Пауза на 1 секунду
//       }
//     }
//   }

//   // Проверка времени остановки
//   if (stopMillis > 0 && millis() - stopMillis >= 1000) {
//     stopMillis = 0;  // Сбрасываем время остановки
//   }

//   // Проверка кнопки "тара"
//   if (digitalRead(tareButtonPin) == LOW) {
//     tareWeight();
//   }

//   // Обновление данных раз в секунду
//   unsigned long currentMillis = millis();
//   if (currentMillis - previousMillis >= interval) {
//     previousMillis = currentMillis;

//     if (scale.is_ready()) {
//       float weight = scale.get_units(10) * calibrationFactor;
//       displayWeight(weight, targetWeightThreshold);

//       // Если вес превышает порог, закрыть сервоприводы
//       if (weight >= targetWeightThreshold) {
//         closeServos();
//       }
//     }
//   }

//   // Если кнопка "старт" нажата, открыть сервоприводы
//   if (digitalRead(startButtonPin) == LOW) {
//     openServos();
//   }
// }

// void displayWeight(float weight, int targetThreshold) {
//   tft.fillRect(0, 0, tft.width(), tft.height(), TFT_WHITE);
//   tft.setTextColor(TFT_BLACK);

//   int textWidth = tft.textWidth("Weight: " + String(weight, 2) + " g");
//   int textX = (tft.width() - textWidth) / 2;
//   int textY = (tft.height() - 160) / 2;

//   tft.setCursor(textX, textY);
//   tft.print("Weight: ");
//   tft.print(weight, 2);
//   tft.print(" g");

//   int thresholdWidth = tft.textWidth("Threshold: " + String(targetThreshold) + " g");
//   int thresholdX = (tft.width() - thresholdWidth) / 2;
//   int thresholdY = textY + 50;

//   tft.setCursor(thresholdX, thresholdY);
//   tft.print("Threshold: ");
//   tft.print(targetThreshold);
//   tft.print(" g");
// }

// void openServos() {
//   servo1.write(0);
//   servo2.write(0);
//   servosOpen = true;
// }

// void closeServos() {
//   servo1.write(90);
//   servo2.write(90);
//   servosOpen = false;
// }

// void tareWeight() {
//   scale.tare();
// }


// #include <TFT_eSPI.h>
// #include <HX711.h>
// #include <ESP32Servo.h>
// #include <Arduino.h>


// const int dtPin = 3;    // Пин DT подключен к GPIO 3
// const int sckPin = 2;   // Пин SCK подключен к GPIO 2
// const int servo1Pin = 43; // Пин для первого сервопривода
// const int servo2Pin = 44; // Пин для второго сервопривода
// const int startButtonPin = 18; // Пин для кнопки открытия сервоприводов
// const int tareButtonPin = 17; // Пин для кнопки тары

// // Пины управления L298N
// const int in1Pin = 12;
// const int in2Pin = 13;
// const int enAPin = 21;

// Servo servo1;
// Servo servo2;

// const float calibrationFactor = 0.002496; // Калибровочный коэффициент
// const int targetWeightThreshold = 100; // Порог веса для закрытия сервоприводов

// bool servosOpen = false; // Флаг открытия/закрытия сервоприводов

// TFT_eSPI tft = TFT_eSPI();
// HX711 scale;

// unsigned long previousMillis = 0;
// const long interval = 10; // Интервал между измерениями в миллисекундах

// // Прототипы функций
// void displayWeight(float weight, int targetThreshold);
// void openServos();
// void closeServos();
// void tareWeight();



// // Проблема, возможно, связана с задержкой в вашем коде, а именно с функцией delay(1000), которая вызывается после движения вперед. При использовании delay весь микроконтроллер приостанавливается на указанное количество миллисекунд, и это может привести к задержкам в обновлении данных.

// // Вместо использования delay можно использовать механизм таймеров или функцию millis(), чтобы управлять временными задержками без блокировки выполнения кода. Вот обновленная версия вашего кода с использованием millis()
// unsigned long forwardMillis = 0;
// unsigned long stopMillis = 0;

// void setup() {
//   // Настройка пинов
//   pinMode(in1Pin, OUTPUT);
//   pinMode(in2Pin, OUTPUT);
//   pinMode(enAPin, OUTPUT);

//   // Начальное состояние
//   digitalWrite(in1Pin, LOW);
//   digitalWrite(in2Pin, LOW);

//   // Настройка PWM для управления скоростью мотора (если нужно)
//   analogWrite(enAPin, 255); // Максимальная скорость

//   Serial.begin(115200);
//   scale.begin(dtPin, sckPin);

//   tft.init();
//   tft.setRotation(3);
//   tft.fillScreen(TFT_WHITE);
//   tft.setTextSize(3);

//   pinMode(startButtonPin, INPUT_PULLUP);
//   pinMode(tareButtonPin, INPUT_PULLUP);

//   servo1.attach(servo1Pin);
//   servo2.attach(servo2Pin);
// }

// void loop() {
//   // Если вес меньше 100 и сервоприводы закрыты, то двигаемся вперед
//   if (scale.is_ready()) {
//     float weight = scale.get_units(10) * calibrationFactor;
    
//     if (weight < targetWeightThreshold && !servosOpen) {
//       // Движение вперед
//       digitalWrite(in1Pin, HIGH);
//       digitalWrite(in2Pin, LOW);
//       delay(2000); // Двигаться вперед в течение 2 секунд

//       // Остановка
//       digitalWrite(in1Pin, LOW);
//       digitalWrite(in2Pin, LOW);
//       delay(1000); // Пауза на 1 секунду
//     }
//   }

//   // Проверка кнопки "тара"
//   if (digitalRead(tareButtonPin) == LOW) {
//     tareWeight();
//   }

//   unsigned long currentMillis = millis();

//   if (currentMillis - previousMillis >= interval) {
//     previousMillis = currentMillis;

//     if (scale.is_ready()) {
//       float weight = scale.get_units(10) * calibrationFactor;

//       displayWeight(weight, targetWeightThreshold);

//       // Если вес превышает порог, закрыть сервоприводы
//       if (weight >= targetWeightThreshold) {
//         closeServos();
//       }
//     }
//   }

//   // Если кнопка "старт" нажата, открыть сервоприводы
//   if (digitalRead(startButtonPin) == LOW) {
//     openServos();
//   }
// }

// void displayWeight(float weight, int targetThreshold) {
//   tft.fillRect(0, 0, tft.width(), tft.height(), TFT_WHITE);
//   tft.setTextColor(TFT_BLACK);

//   int textWidth = tft.textWidth("Weight: " + String(weight, 2) + " g");
//   int textX = (tft.width() - textWidth) / 2;
//   int textY = (tft.height() - 160) / 2;

//   tft.setCursor(textX, textY);
//   tft.print("Weight: ");
//   tft.print(weight, 2);
//   tft.print(" g");

//   int thresholdWidth = tft.textWidth("Threshold: " + String(targetThreshold) + " g");
//   int thresholdX = (tft.width() - thresholdWidth) / 2;
//   int thresholdY = textY + 50;

//   tft.setCursor(thresholdX, thresholdY);
//   tft.print("Threshold: ");
//   tft.print(targetThreshold);
//   tft.print(" g");
// }

// void openServos() {
//   servo1.write(0);
//   servo2.write(0);
//   servosOpen = true;
// }

// void closeServos() {
//   servo1.write(90);
//   servo2.write(90);
//   servosOpen = false;
// }

// void tareWeight() {
//   // Обнуление веса
//   scale.tare();
// }









// #include <TFT_eSPI.h>
// #include <IRremote.h>

// #define IR_PIN 11  // Пин, к которому подключен ИК-приемник

// TFT_eSPI tft = TFT_eSPI();
// IRrecv irReceiver(IR_PIN);

// void setup() {
//   Serial.begin(115200);

//   tft.init();
//   tft.setRotation(3);
//   tft.fillScreen(TFT_WHITE);
//   tft.setTextSize(2);

//   irReceiver.enableIRIn();  // Инициализация ИК-приемника
// }

// void loop() {
//   decode_results results;

//   if (irReceiver.decode(&results)) {
//     // Обработка полученного кода с пульта
//     tft.fillRect(0, 0, tft.width(), tft.height(), TFT_WHITE);
//     tft.setTextColor(TFT_BLACK);
    
//     tft.setCursor(0, 0);
//     tft.print("IR Code: 0x");
//     tft.print(results.value, HEX);

//     // Включение LED на ИК-приемнике
//     digitalWrite(IR_PIN, HIGH);
//     delay(500);
//     digitalWrite(IR_PIN, LOW);

//     irReceiver.resume();  // Продолжение прослушивания ИК-сигнала
//   }
// }



///////// вибромотор драйвер кнопка рестарт весы сервопривод все подключено и работает, медленно обновляются данные на датчике hx711, так же есть условие срабатывание вибромотора и сервоприводы откр или закрыт.

// #include <TFT_eSPI.h>
// #include <HX711.h>
// #include <ESP32Servo.h>
// #include <Arduino.h>

// const int dtPin = 3;    // Пин DT подключен к GPIO 3
// const int sckPin = 2;   // Пин SCK подключен к GPIO 2
// const int servo1Pin = 43; // Пин для первого сервопривода
// const int servo2Pin = 44; // Пин для второго сервопривода
// const int startButtonPin = 18; // Пин для кнопки открытия сервоприводов

// // Пины управления L298N
// const int in1Pin = 12;
// const int in2Pin = 13;
// const int enAPin = 21;

// Servo servo1;
// Servo servo2;

// const float calibrationFactor = 0.002496; // Калибровочный коэффициент
// const int targetWeightThreshold = 100; // Порог веса для закрытия сервоприводов

// bool servosOpen = false; // Флаг открытия/закрытия сервоприводов

// TFT_eSPI tft = TFT_eSPI();
// HX711 scale;


// unsigned long previousMillis = 0;
// const long interval = 10; // Интервал между измерениями в миллисекундах

// // Прототипы функций
// void displayWeight(float weight, int targetThreshold);
// void openServos();
// void closeServos();

// void setup() {
//   // Настройка пинов
//   pinMode(in1Pin, OUTPUT);
//   pinMode(in2Pin, OUTPUT);
//   pinMode(enAPin, OUTPUT);

//   // Начальное состояние
//   digitalWrite(in1Pin, LOW);
//   digitalWrite(in2Pin, LOW);

//   // Настройка PWM для управления скоростью мотора (если нужно)
//   analogWrite(enAPin, 255); // Максимальная скорость

//   Serial.begin(115200);
//   scale.begin(dtPin, sckPin);

//   tft.init();
//   tft.setRotation(3);
//   tft.fillScreen(TFT_WHITE);
//   tft.setTextSize(3);

//   pinMode(startButtonPin, INPUT_PULLUP);

//   servo1.attach(servo1Pin);
//   servo2.attach(servo2Pin);
// }


// void loop() {
//   // Если вес меньше 100 и сервоприводы закрыты, то двигаемся вперед
//   if (scale.is_ready()) {
//     float weight = scale.get_units(10) * calibrationFactor;
    
//     if (weight < targetWeightThreshold && !servosOpen) {
//       // Движение вперед
//       digitalWrite(in1Pin, HIGH);
//       digitalWrite(in2Pin, LOW);
//       delay(2000); // Двигаться вперед в течение 2 секунд

//       // Остановка
//       digitalWrite(in1Pin, LOW);
//       digitalWrite(in2Pin, LOW);
//       delay(1000); // Пауза на 1 секунду
//     }
//   }

//   unsigned long currentMillis = millis();

//   if (currentMillis - previousMillis >= interval) {
//     previousMillis = currentMillis;

//     if (scale.is_ready()) {
//       float weight = scale.get_units(10) * calibrationFactor;

//       displayWeight(weight, targetWeightThreshold);

//       // Если вес превышает порог, закрыть сервоприводы
//       if (weight >= targetWeightThreshold) {
//         closeServos();
//       }
//     }
//   }

//   // Если кнопка "старт" нажата, открыть сервоприводы
//   if (digitalRead(startButtonPin) == LOW) {
//     openServos();
//   }
// }

// void displayWeight(float weight, int targetThreshold) {
//   tft.fillRect(0, 0, tft.width(), tft.height(), TFT_WHITE);
//   tft.setTextColor(TFT_BLACK);

//   int textWidth = tft.textWidth("Weight: " + String(weight, 2) + " g");
//   int textX = (tft.width() - textWidth) / 2;
//   int textY = (tft.height() - 160) / 2;

//   tft.setCursor(textX, textY);
//   tft.print("Weight: ");
//   tft.print(weight, 2);
//   tft.print(" g");

//   int thresholdWidth = tft.textWidth("Threshold: " + String(targetThreshold) + " g");
//   int thresholdX = (tft.width() - thresholdWidth) / 2;
//   int thresholdY = textY + 50;

//   tft.setCursor(thresholdX, thresholdY);
//   tft.print("Threshold: ");
//   tft.print(targetThreshold);
//   tft.print(" g");
// }

// void openServos() {
//   servo1.write(0);
//   servo2.write(0);
//   servosOpen = true;
// }

// void closeServos() {
//   servo1.write(90);
//   servo2.write(90);
//   servosOpen = false;
// }



// #include <TFT_eSPI.h>
// #include <HX711.h>
// #include <ESP32Servo.h>

// TFT_eSPI tft = TFT_eSPI();
// HX711 scale;

// const int dtPin = 3;    // Пин DT подключен к GPIO 3
// const int sckPin = 2;   // Пин SCK подключен к GPIO 2
// const int servo1Pin = 43; // Пин для первого сервопривода
// const int servo2Pin = 44; // Пин для второго сервопривода
// const int startButtonPin = 18; // Пин для кнопки открытия сервоприводов

// Servo servo1;
// Servo servo2;

// const float calibrationFactor = 0.002496; // Калибровочный коэффициент
// const int targetWeightThreshold = 100; // Порог веса для закрытия сервоприводов

// unsigned long previousMillis = 0;
// const long interval = 1000; // Интервал между измерениями в миллисекундах

// // Прототипы функций
// void displayWeight(float weight, int targetThreshold);
// void openServos();
// void closeServos();

// void setup() {
//   Serial.begin(115200);
//   scale.begin(dtPin, sckPin);

//   tft.init();
//   tft.setRotation(3);
//   tft.fillScreen(TFT_WHITE);
//   tft.setTextSize(3);

//   pinMode(startButtonPin, INPUT_PULLUP);

//   servo1.attach(servo1Pin);
//   servo2.attach(servo2Pin);
// }

// void loop() {
//   unsigned long currentMillis = millis();

//   if (currentMillis - previousMillis >= interval) {
//     previousMillis = currentMillis;

//     if (scale.is_ready()) {
//       float weight = scale.get_units(10) * calibrationFactor;

//       displayWeight(weight, targetWeightThreshold);

//       // Если вес превышает порог, закрыть сервоприводы
//       if (weight >= targetWeightThreshold) {
//         closeServos();
//       }
//     }
//   }

//   // Если кнопка "старт" нажата, открыть сервоприводы
//   if (digitalRead(startButtonPin) == LOW) {
//     openServos();
//   }
// }

// void displayWeight(float weight, int targetThreshold) {
//   tft.fillRect(0, 0, tft.width(), tft.height(), TFT_WHITE);
//   tft.setTextColor(TFT_BLACK);

//   int textWidth = tft.textWidth("Weight: " + String(weight, 2) + " g");
//   int textX = (tft.width() - textWidth) / 2;
//   int textY = (tft.height() - 160) / 2;

//   tft.setCursor(textX, textY);
//   tft.print("Weight: ");
//   tft.print(weight, 2);
//   tft.print(" g");

//   int thresholdWidth = tft.textWidth("Threshold: " + String(targetThreshold) + " g");
//   int thresholdX = (tft.width() - thresholdWidth) / 2;
//   int thresholdY = textY + 50;

//   tft.setCursor(thresholdX, thresholdY);
//   tft.print("Threshold: ");
//   tft.print(targetThreshold);
//   tft.print(" g");
// }

// void openServos() {
//   servo1.write(0);
//   servo2.write(0);
// }

// void closeServos() {
//   servo1.write(90);
//   servo2.write(90);
// }


///// тензодатчик без калибровки
// #include <TFT_eSPI.h>
// #include <HX711.h>

// TFT_eSPI tft = TFT_eSPI();
// HX711 scale;

// const int dtPin = 3;  // Пин DT подключен к GPIO 3
// const int sckPin = 2; // Пин SCK подключен к GPIO 2

// void setup() {
//   Serial.begin(115200);
//   scale.begin(dtPin, sckPin);

//   tft.init();
//   tft.setRotation(3);
//   tft.fillScreen(TFT_WHITE);
//   tft.setTextSize(3);
// }

// // Прототип функции
// void displayRawValue(long rawValue);

// void loop() {
//   if (scale.is_ready()) {
//     long raw = scale.read();
//     displayRawValue(raw);
//   }

//   delay(1000); // Пауза 1 секунда между измерениями
// }

// void displayRawValue(long rawValue) {
//   tft.fillRect(0, 0, tft.width(), tft.height(), TFT_WHITE); // Очистим экран перед выводом новой информации
//   tft.setTextColor(TFT_BLACK);

//   int textWidth = tft.textWidth("Raw Value: " + String(rawValue));
//   int textX = (tft.width() - textWidth) / 2;
//   int textY = (tft.height() - 160) / 2;

//   tft.setCursor(textX, textY);
//   tft.print("Raw Value: ");
//   tft.print(rawValue);
// }





///////////тензодатчик
// #include <TFT_eSPI.h>
// #include <HX711.h>

// TFT_eSPI tft = TFT_eSPI();
// HX711 scale;

// const int dtPin = 3;  // Пин DT подключен к GPIO 2
// const int sckPin = 2; // Пин SCK подключен к GPIO 4

// // Калибровочный коэффициент
// const float calibrationFactor = 0.002496;

// void setup() {
//   Serial.begin(115200);
//   scale.begin(dtPin, sckPin);

//   tft.init();
//   tft.setRotation(3);
//  // tft.fillScreen(TFT_WHITE);
//   tft.setTextSize(3);
// }

// // Прототип функции
// void displayWeight(float weight);

// void loop() {
//   if (scale.is_ready()) {
//     float weight = scale.get_units(10) * calibrationFactor; // 10 - количество отсчетов для усреднения
//     displayWeight(weight);
//   }

//   delay(1000); // Пауза 1 секунда между измерениями
// }

// void displayWeight(float weight) {
//   tft.fillRect(0, 0, tft.width(), tft.height(), TFT_WHITE); // Очистим экран перед выводом новой информации
//   tft.setTextColor(TFT_BLACK);

//   int textWidth = tft.textWidth("Weight: " + String(weight, 2) + " g");
//   int textX = (tft.width() - textWidth) / 2;
//   int textY = (tft.height() - 160) / 2;

//   tft.setCursor(textX, textY);
//   tft.print("Weight: ");
//   tft.print(weight, 2);
//   tft.print(" g");
// }



///// тензодатчик и кнопки РАБОТАЕТ ОТ 21 декабря сервоприводы не работают при достижении 100гр
// #include <TFT_eSPI.h>
// #include <HX711.h>
// #include <ESP32Servo.h>

// TFT_eSPI tft = TFT_eSPI();
// HX711 scale;
// Servo servo1;
// Servo servo2;

// const int dtPin = 3;        // Пин DT подключен к GPIO 2
// const int sckPin = 2;       // Пин SCK подключен к GPIO 4
// const int startButtonPin = 18;  // Пин для кнопки старта
// const int tareButtonPin = 17;   // Пин для кнопки тарировки

// // Переменные для управления сервоприводами
// const int servo1Pin = 43;
// const int servo2Pin = 44;
// int angle1 = 0;
// int angle2 = 180;

// // Определение порога веса для закрытия сервоприводов
// const float closingWeightThreshold = 100.0; // Пороговый вес для закрытия сервоприводов (граммы)

// // Калибровочный коэффициент
// const float calibrationFactor = 0.002496;

// // Переменная для отслеживания состояния кнопки старта
// bool startButtonPressed = false;

// // Объявление функций
// void displayWeight(float weight, float threshold);
// void moveServosToInitialPosition();
// void openServos();
// void closeServos();

// void setup() {
//   Serial.begin(115200);
//   scale.begin(dtPin, sckPin);

//   tft.init();
//   tft.setRotation(3);
//   //tft.fillScreen(TFT_WHITE);
//   tft.setTextSize(3);

//   servo1.attach(servo1Pin);
//   servo2.attach(servo2Pin);

//   pinMode(startButtonPin, INPUT_PULLUP);
//   pinMode(tareButtonPin, INPUT_PULLUP);

//   moveServosToInitialPosition();
// }

// void loop() {
//   if (scale.is_ready()) {
//     // Тарируем весы при нажатии на кнопку тарировки
//     if (digitalRead(tareButtonPin) == LOW) {
//       scale.tare();
//       delay(1000);   // Задержка для предотвращения многократного срабатывания кнопки
//     }

//     float weight = scale.get_units(10) * calibrationFactor; // 10 - количество отсчетов для усреднения
//     displayWeight(weight, closingWeightThreshold);

//     // Проверяем состояние кнопки старта
//     if (digitalRead(startButtonPin) == LOW) {
//       if (!startButtonPressed) {  // Если кнопка только что была нажата
//         startButtonPressed = true;
//         if (weight >= closingWeightThreshold) {
//           closeServos();
//         } else {
//           openServos();
//         }
//       }
//     } else {
//       startButtonPressed = false;
//     }
//   }

//   delay(1000); // Пауза 1 секунда между измерениями
// }

// void displayWeight(float weight, float threshold) {
//   tft.fillRect(0, 0, tft.width(), tft.height(), TFT_WHITE); // Очистим экран перед выводом новой информации
//   tft.setTextColor(TFT_BLACK);

//   int textWidth = tft.textWidth("Weight: " + String(weight, 2) + " g");
//   int textX = (tft.width() - textWidth) / 2;
//   int textY = (tft.height() - 160) / 2;

//   tft.setCursor(textX, textY);
//   tft.print("Weight: ");
//   tft.print(weight, 2);
//   tft.print(" g");

//   int thresholdWidth = tft.textWidth("Threshold: " + String(threshold, 2) + " g");
//   int thresholdX = (tft.width() - thresholdWidth) / 2;
//   int thresholdY = (tft.height() + 40) / 2;

//   tft.setCursor(thresholdX, thresholdY);
//   tft.print("Threshold: ");
//   tft.print(threshold, 2);
//   tft.print(" g");
// }

// void moveServosToInitialPosition() {
//   angle1 = 0;
//   angle2 = 180;
//   servo1.write(angle1);
//   servo2.write(angle2);
//   delay(500); // Добавим задержку для плавного движения
// }

// void openServos() {
//   angle1 = 55;
//   angle2 = 125;
//   servo1.write(angle1);
//   servo2.write(angle2);
// }

// void closeServos() {
//   angle1 = 0;
//   angle2 = 180;
//   servo1.write(angle1);
//   servo2.write(angle2);
//   delay(500); // Добавим задержку для плавного движения
// }


// //тензодатчик и сервоприводы срабатывают в автоматическом режиме если меньше 100гр открывает если больше закрывает
// #include <TFT_eSPI.h>
// #include <HX711.h>
// #include <ESP32Servo.h>

// TFT_eSPI tft = TFT_eSPI();
// HX711 scale;
// Servo servo1;
// Servo servo2;

// const int dtPin = 3;        // Пин DT подключен к GPIO 2
// const int sckPin = 2;       // Пин SCK подключен к GPIO 4
// const int startButtonPin = 18;  // Пин для кнопки старта
// const int tareButtonPin = 17;   // Пин для кнопки тарировки

// // Переменные для управления сервоприводами
// const int servo1Pin = 43;
// const int servo2Pin = 44;
// int angle1 = 0;
// int angle2 = 180;

// // Определение порога веса для закрытия сервоприводов
// const float closingWeightThreshold = 100.0; // Пороговый вес для закрытия сервоприводов (граммы)

// // Объявление функций
// void displayWeight(float weight);
// void moveServosToInitialPosition();
// void openServos();
// void closeServos();

// void setup() {
//   Serial.begin(115200);
//   scale.begin(dtPin, sckPin);

//   tft.init();
//   tft.setRotation(3);
//   tft.fillScreen(TFT_WHITE);
//   tft.setTextSize(3);

//   servo1.attach(servo1Pin);
//   servo2.attach(servo2Pin);

//   pinMode(startButtonPin, INPUT_PULLUP);
//   pinMode(tareButtonPin, INPUT_PULLUP);

//   moveServosToInitialPosition();
// }

// void loop() {
//   if (scale.is_ready()) {
//     // Тарируем весы при нажатии на кнопку тарировки
//     if (digitalRead(tareButtonPin) == LOW) {
//       scale.tare();
//       delay(1000);   // Задержка для предотвращения многократного срабатывания кнопки
//     }

//     float weight = scale.get_units(10); // 10 - количество отсчетов для усреднения
//     displayWeight(weight);

//     // Проверяем состояние кнопки старта
//     if (digitalRead(startButtonPin) == LOW) {
//       if (weight >= closingWeightThreshold) {
//         closeServos();
//       } else {
//         openServos();
//       }
//     }
//   }

//   delay(1000); // Пауза 1 секунда между измерениями
// }

// void displayWeight(float weight) {
//   tft.fillRect(0, 0, tft.width(), tft.height(), TFT_WHITE); // Очистим экран перед выводом новой информации
//   tft.setTextColor(TFT_BLACK);

//   int textWidth = tft.textWidth("Weight: " + String(weight, 2) + " g");
//   int textX = (tft.width() - textWidth) / 2;
//   int textY = (tft.height() - 160) / 2;

//   tft.setCursor(textX, textY);
//   tft.print("Weight: ");
//   tft.print(weight, 2);
//   tft.print(" g");
// }

// void moveServosToInitialPosition() {
//   angle1 = 0;
//   angle2 = 180;
//   servo1.write(angle1);
//   servo2.write(angle2);
//   delay(500); // Добавим задержку для плавного движения
// }

// void openServos() {
//   angle1 = 55;
//   angle2 = 125;
//   servo1.write(angle1);
//   servo2.write(angle2);
// }

// void closeServos() {
//   angle1 = 0;
//   angle2 = 180;
//   servo1.write(angle1);
//   servo2.write(angle2);
//   delay(500); // Добавим задержку для плавного движения
// }



/// Тензо датчик работает сервоприводы с кнопкой не работают

// #include <TFT_eSPI.h>
// #include <HX711.h>
// #include <ESP32Servo.h>

// TFT_eSPI tft = TFT_eSPI();
// HX711 scale;
// Servo servo1;
// Servo servo2;

// const int dtPin = 3;        // Пин DT подключен к GPIO 2
// const int sckPin = 2;       // Пин SCK подключен к GPIO 4
// const int startButtonPin = 18;  // Пин для кнопки старта
// const int tareButtonPin = 17;   // Пин для кнопки тарировки

// // Переменные для управления сервоприводами
// const int servo1Pin = 43;
// const int servo2Pin = 44;
// int angle1 = 0;
// int angle2 = 180;

// // Объявление функций
// void displayWeight(float weight);
// void moveServosToInitialPosition();

// void setup() {
//   Serial.begin(115200);
//   scale.begin(dtPin, sckPin);

//   tft.init();
//   tft.setRotation(3);
//   tft.fillScreen(TFT_WHITE);
//   tft.setTextSize(3);

//   servo1.attach(servo1Pin);
//   servo2.attach(servo2Pin);

//   pinMode(startButtonPin, INPUT_PULLUP);
//   pinMode(tareButtonPin, INPUT_PULLUP);

//   moveServosToInitialPosition();
// }

// void loop() {
//   if (scale.is_ready()) {
//     // Тарируем весы при нажатии на кнопку тарировки
//     if (digitalRead(tareButtonPin) == LOW) {
//       scale.tare();
//       delay(1000);   // Задержка для предотвращения многократного срабатывания кнопки
//     }

//     float weight = scale.get_units(10); // 10 - количество отсчетов для усреднения
//     displayWeight(weight);

//     // Проверяем состояние кнопки старта
//     if (digitalRead(startButtonPin) == LOW) {
//       moveServosToInitialPosition();
//     }
//   }

//   delay(1000); // Пауза 1 секунда между измерениями
// }

// void displayWeight(float weight) {
//   tft.fillRect(0, 0, tft.width(), tft.height(), TFT_WHITE); // Очистим экран перед выводом новой информации
//   tft.setTextColor(TFT_BLACK);

//   int textWidth = tft.textWidth("Weight: " + String(weight, 2) + " g");
//   int textX = (tft.width() - textWidth) / 2;
//   int textY = (tft.height() - 160) / 2;

//   tft.setCursor(textX, textY);
//   tft.print("Weight: ");
//   tft.print(weight, 2);
//   tft.print(" g");
// }

// void moveServosToInitialPosition() {
//   angle1 = 0;
//   angle2 = 180;
//   servo1.write(angle1);
//   servo2.write(angle2);
//   delay(500); // Добавим задержку для плавного движения
// }



// //тензодатчик и дисплей 19дек
// #include <TFT_eSPI.h>
// #include <HX711.h>

// TFT_eSPI tft = TFT_eSPI();
// HX711 scale;

// const int dtPin = 3;     // Пин DT подключен к GPIO 2
// const int sckPin = 2;    // Пин SCK подключен к GPIO 4
// const float calibrationFactor = 0.002496;  // Калибровочный коэффициент

// // Объявление функции
// void displayWeight(float weight);

// void setup() {
//   Serial.begin(115200);
//   scale.begin(dtPin, sckPin);
//   scale.set_scale(calibrationFactor);

//   tft.init();
//   tft.setRotation(3);
//   tft.fillScreen(TFT_WHITE);
//   tft.setTextSize(3);
// }

// void loop() {
//   if (scale.is_ready()) {
//     float weight = scale.get_units(10); // 10 - количество отсчетов для усреднения
//     displayWeight(weight);
//   }

//   delay(1000); // Пауза 1 секунда между измерениями
// }

// void displayWeight(float weight) {
//   tft.fillScreen(TFT_WHITE);
//   tft.setTextColor(TFT_BLACK);

//   int textWidth = tft.textWidth("Weight: " + String(weight, 2) + " g");
//   int textX = (tft.width() - textWidth) / 2;
//   int textY = (tft.height() - 160) / 2;

//   tft.setCursor(textX, textY);
//   tft.print("Weight: ");
//   tft.print(weight, 2);
//   tft.print(" g");
// }


////////РАБОЧАЯ ПОСЛЕДНЕЕ от 20 сентября 23г////////////////////////////////////////////////////////////////////////////////
// #include <TFT_eSPI.h>
// #include <ESP32Servo.h>
// #include <HX711.h>
// #include <EEPROM.h>


// TFT_eSPI tft = TFT_eSPI();

// HX711 scale;
// const int dtPin = 2;  // Пин DT подключен к GPIO 43
// const int sckPin = 3; // Пин SCK подключен к GPIO 44
// float calibrationFactor = 0.002496; // Калибровочный коэффициент

// Servo servo1;
// Servo servo2;
// const int buttonPin = 0;
// int angle1 = 0;
// int angle2 = 180;
// bool isOpen = false; // Флаг состояния (открыто/закрыто)
// float targetWeight; // Целевая масса для закрытия сервоприводов
// float closingThreshold = 0.95; // Пороговое значение в процентах для начала закрытия сервоприводов

// int buttonCount = 0; // Количество нажатий на кнопку
// int addr; // Адрес в EEPROM для сохранения значения

// bool useEEPROMValue = false; // Флаг для использования значения из EEPROM

// // Объявления функций
// void handleButtons();
// void displayTargetWeight();
// void saveTargetWeight();

// float lastDisplayedWeight = 0; // Переменная для отслеживания последнего отображенного веса


// void setup() {
//   scale.begin(dtPin, sckPin);
//   scale.set_scale();
//   scale.tare();

//   tft.init();
//   tft.setRotation(3);
//   tft.fillScreen(TFT_BLUE);
//   tft.setTextSize(5);

//   servo1.attach(1);
//   servo2.attach(2);

//   pinMode(buttonPin, INPUT_PULLUP);
//   pinMode(18, INPUT_PULLUP);
//   pinMode(17, INPUT_PULLUP);
//   pinMode(13, INPUT_PULLUP);
//   pinMode(12, INPUT_PULLUP);

//   EEPROM.begin(sizeof(targetWeight));
//   //EEPROM.get(addr + 1, targetWeight);  // Read targetWeight from EEPROM
//   targetWeight = EEPROM.read(addr);
//   displayTargetWeight();
// }




// void loop() {
//   if (scale.is_ready()) {
//     float weight = scale.get_units() * calibrationFactor;

//     // Проверяем изменение веса на 1 грамм перед обновлением экрана
//     if (abs(weight - lastDisplayedWeight) >= 1.0) {
//       lastDisplayedWeight = weight; // Обновляем последний отображенный вес

//       tft.fillScreen(TFT_WHITE);
//       tft.setTextColor(TFT_BLACK);

//       int textWidth = tft.textWidth("" + String(weight, 0) + " g");
//       int textX = (tft.width() - textWidth) / 2;

//       tft.setCursor(textX, (tft.height() - 160) / 2);
//       tft.print("");
//       tft.print(weight, 0);
//       tft.print(" g");

//     //int countWidth = tft.textWidth("Button Count: " + String(buttonCount));
//     //int countX = (tft.width() - countWidth) / 2;
//     //tft.setCursor(countX, (tft.height() + 40) / 2);
//     //tft.print("Button Count: ");
//     //tft.print(buttonCount);

//     String reachedText = String(targetWeight, 0) + " g";
//     int reachedWidth = tft.textWidth(reachedText);
//     int reachedX = (tft.width() - reachedWidth) / 2;

//     tft.setCursor(reachedX, (tft.height() + 10) / 2);
//     tft.print(reachedText);
//     }

//     if (!isOpen && weight >= targetWeight * closingThreshold) {
//       pinMode(buttonPin, INPUT_PULLUP);
//     }

//     if (isOpen) {
//       if (weight >= targetWeight * closingThreshold) {
//         angle1 = 0;
//         angle2 = 180;
//         isOpen = false;

//         int closingWidth = tft.textWidth("Closing servos");
//         int closingX = (tft.width() - closingWidth) / 2;

//         tft.setCursor(closingX, (tft.height() - 80) / 2);
//         tft.print("Closing servos");

//         buttonCount++;

//       }
//     } else {
//       if (weight >= targetWeight) {
//         angle1 = 0;
//         angle2 = 180;
//         isOpen = false;

    
//       }
//     }
    
//     //delay(1);
//   }

//   if (digitalRead(buttonPin) == LOW && isOpen == false) {
//     angle1 = 55;
//     angle2 = 125;
//     isOpen = true;
//     pinMode(buttonPin, INPUT);
//   }

//   servo1.write(angle1);
//   servo2.write(angle2);

//   handleButtons();

//   //delay(1);
// }

// void handleButtons() {
//   if (digitalRead(18) == LOW) {
//     angle1 = 55;
//     angle2 = 125;
//     isOpen = true;
//     pinMode(buttonPin, INPUT);
//   }

//   if (digitalRead(17) == LOW) {
//     esp_restart();
//   }

//   if (digitalRead(12) == LOW) {
//     targetWeight += 10;
//     displayTargetWeight();
//     saveTargetWeight();
//     delay(500);
//   }

//   if (digitalRead(13) == LOW) {
//     targetWeight -= 10;
//     displayTargetWeight();
//     saveTargetWeight();
//     delay(500);
//   }
// }

// void displayTargetWeight() {
//   tft.fillScreen(TFT_WHITE);
//   tft.setTextColor(TFT_BLACK);

//   int textWidth = tft.textWidth(": " + String(targetWeight, 0) + " g");
//   int textX = (tft.width() - textWidth) / 2;

//   tft.setCursor(textX, (tft.height() - 160) / 2);
//   tft.print("PRODUCT   ");
//   tft.print(targetWeight, 0);
//   tft.print(" g");


// }

// void saveTargetWeight() {
//   EEPROM.write(addr, targetWeight);  // Save targetWeight to EEPROM
//   EEPROM.commit();

        
//   //EEPROM.write(addr, buttonCount);
//   //EEPROM.commit();
// } 
////////////////////////////////////////////////////////////////////////////////////////






// ////////РАБОЧАЯ ПОСЛЕДНЕЕ от 20 сентября 23г////////////////////////////////////////////////////////////////////////////////
// #include <TFT_eSPI.h>
// #include <ESP32Servo.h>
// #include <HX711.h>
// #include <EEPROM.h>


// TFT_eSPI tft = TFT_eSPI();

// HX711 scale;
// const int dtPin = 44;  // Пин DT подключен к GPIO 43
// const int sckPin = 43; // Пин SCK подключен к GPIO 44
// float calibrationFactor = 0.002496; // Калибровочный коэффициент

// Servo servo1;
// Servo servo2;
// const int buttonPin = 0;
// int angle1 = 0;
// int angle2 = 180;
// bool isOpen = false; // Флаг состояния (открыто/закрыто)
// float targetWeight = 1000; // Целевая масса для закрытия сервоприводов
// float closingThreshold = 0.95; // Пороговое значение в процентах для начала закрытия сервоприводов

// int buttonCount = 0; // Количество нажатий на кнопку
// int addr = 0; // Адрес в EEPROM для сохранения значения

// void setup() {
//   scale.begin(dtPin, sckPin);
//   // Калибровка тензодатчика
//   scale.set_scale(); // Установка фактора масштабирования по умолчанию
//   scale.tare(); // Установка нулевой точки

//   EEPROM.begin(2); // Инициализация EEPROM с размером 2 байта для хранения количества нажатий

//   tft.init();
//   tft.setRotation(2);
//   tft.fillScreen(TFT_BLACK);
//   tft.setTextSize(2); // Увеличение размера шрифта в 4 раза

//   servo1.attach(1);
//   servo2.attach(2);

//   pinMode(buttonPin, INPUT_PULLUP);

//   servo1.write(angle1);
//   servo2.write(angle2);

//   // Чтение сохраненного значения из EEPROM
//   buttonCount = EEPROM.read(addr);
// }

// void loop() {
//   if (scale.is_ready()) {
//     float weight = scale.get_units() * calibrationFactor;

//     tft.fillScreen(TFT_BLACK);
//     tft.setTextColor(TFT_WHITE);

//     int textWidth = tft.textWidth("Weight: " + String(weight, 0) + " g"); // Ширина текста
//     int textX = (tft.width() - textWidth) / 2; // Расчет позиции X для центрирования

//     tft.setCursor(textX, (tft.height() - 160) / 2);
//     tft.print("Weight: ");
//     tft.print(weight, 0);
//     tft.print(" g");

//     // Вывод количества нажатий на кнопку
//     int countWidth = tft.textWidth("Button Count: " + String(buttonCount)); // Ширина текста
//     int countX = (tft.width() - countWidth) / 2; // Расчет позиции X для центрирования
//     tft.setCursor(countX, (tft.height() + 40) / 2);
//     tft.print("Button Count: ");
//     tft.print(buttonCount);

//     if (!isOpen && weight >= targetWeight * closingThreshold) {
//       // Запрет повторного нажатия кнопки
//       pinMode(buttonPin, INPUT_PULLUP);
//     }

//     if (isOpen) {
//       if (weight >= targetWeight * closingThreshold) {
//         angle1 = 0;
//         angle2 = 180;
//         isOpen = false;

//         int closingWidth = tft.textWidth("Closing servos"); // Ширина текста
//         int closingX = (tft.width() - closingWidth) / 2; // Расчет позиции X для центрирования

//         tft.setCursor(closingX, (tft.height() - 80) / 2);
//         tft.print("Closing servos");

//         // Увеличение счетчика нажатий на кнопку
//         buttonCount++;
//         // Сохранение значения в EEPROM
//         EEPROM.write(addr, buttonCount);
//         EEPROM.commit();
//       }
//     } else {
//       if (weight >= targetWeight) {
//         angle1 = 0;
//         angle2 = 180;
//         isOpen = false;

//         int reachedWidth = tft.textWidth("1000g reached"); // Ширина текста
//         int reachedX = (tft.width() - reachedWidth) / 2; // Расчет позиции X для центрирования

//         tft.setCursor(reachedX, (tft.height() - 80) / 2);
//         tft.print("1000g reached");
//       }
//     }
    
//     delay(1); // Задержка между измерениями
//   }

//   if (digitalRead(buttonPin) == LOW && isOpen == false) {
//     angle1 = 55;
//     angle2 = 125;
//     isOpen = true;
//     // Запрет повторного нажатия кнопки
//     pinMode(buttonPin, INPUT);
//   }

//   // Обновление положений сервоприводов
//   servo1.write(angle1);
//   servo2.write(angle2);

//   delay(1);
// }








// ////////////////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////
// #include <HX711.h>
// #include <TFT_eSPI.h>

// TFT_eSPI tft = TFT_eSPI();
// HX711 scale;

// const int dtPin = 44;  // Пин DT подключен к GPIO 43
// const int sckPin = 43; // Пин SCK подключен к GPIO 44

// float calibrationFactor = 0.002486; // Калибровочный коэффициент

// void setup() {
//   Serial.begin(115200);
//   tft.init();
//   tft.setRotation(2);
//   tft.fillScreen(TFT_BLACK);
//   tft.setTextSize(2);
  
//   scale.begin(dtPin, sckPin);

//   // Калибровка тензодатчика
//   scale.set_scale(); // Установка фактора масштабирования по умолчанию
//   scale.tare(); // Установка нулевой точки
  
//   tft.fillScreen(TFT_BLACK);
// }

// void loop() {
//   if (scale.is_ready()) {
//     float weight = scale.get_units() * calibrationFactor;

//     tft.fillScreen(TFT_BLACK);
//     tft.setTextColor(TFT_WHITE);
//     tft.setCursor((tft.width() - 200) / 2, (tft.height() - 60) / 2);
//     tft.print("Weight: ");
//     tft.print(weight, 2);
//     tft.print(" g");

//     delay(1000); // Задержка между измерениями
//   }
// }

// Предложенный вами код представляет программу, которая использует тензодатчик HX711 для измерения массы и выводит результат на TFT-дисплей. Вот краткое описание того, что делает программа:

// 1. Импортируются необходимые библиотеки: HX711 для работы с тензодатчиком и TFT_eSPI для работы с TFT-дисплеем.

// 2. Создаются объекты tft и scale для работы с TFT-дисплеем и тензодатчиком соответственно.

// 3. Задаются пины dtPin и sckPin для подключения тензодатчика.

// 4. Определяется переменная calibrationFactor для хранения калибровочного коэффициента.

// 5. В функции setup():
//    - Инициализируется Serial для обмена данными по сериальному порту.
//    - Инициализируется TFT-дисплей и настраиваются его параметры.
//    - Выполняется инициализация тензодатчика, установка фактора масштабирования по умолчанию и установка нулевой точки.
//    - Запрашивается ввод известной массы через сериальный порт.
//    - Вычисляется калибровочный коэффициент.

// 6. В функции loop():
//    - Проверяется, готов ли тензодатчик для измерения.
//    - Если тензодатчик готов, выполняется измерение массы и вычисление фактической массы с учетом калибровочного коэффициента.
//    - Значение массы выводится на TFT-дисплей.

// 7. В функции readFloatFromSerial():
//    - Ожидается доступность данных в сериальном порту.
//    - Считывается строка из сериального порта до символа новой строки.
//    - Строка обрабатывается, удаляются лишние пробелы и символы, и преобразуется в тип float.
//    - Значение массы выводится обратно в Serial (для проверки) и возвращается из функции.

// Вы можете сохранить этот код, создав новый коммит в вашем репозитории с описанием изменений. Это позволит вам вернуться к нему позже, если понадобится.
//////////////////////////////////////////////////////////////

///////////////////////////////

// #include <TFT_eSPI.h>
// #include <ESP32Servo.h>

// TFT_eSPI tft = TFT_eSPI();
// Servo servo1;
// Servo servo2;
// const int buttonPin = 0;
// int angle1 = 0;
// int angle2 = 180;
// bool isOpen = false; // Флаг состояния (открыто/закрыто)
// unsigned long lastButtonPressTime = 0; // Время последнего нажатия кнопки

// void setup() {
//   tft.init();
//   tft.setRotation(2);
//   tft.fillScreen(TFT_BLACK);
//   tft.setTextSize(2);

//   servo1.attach(1);
//   servo2.attach(2);

//   pinMode(buttonPin, INPUT_PULLUP);

//   servo1.write(angle1);
//   servo2.write(angle2);
// }

// void loop() {
//   if (digitalRead(buttonPin) == LOW) {
//     if (!isOpen) {
//       angle1 = 55;
//       angle2 = 125;
//       isOpen = true;
//       lastButtonPressTime = millis(); // Запоминаем время первого нажатия
//     }
//   } else if (isOpen && millis() - lastButtonPressTime > 7200) {
//     angle1 = 0;
//     angle2 = 180;
//     isOpen = false;
//   }

//   // Обновление положений сервоприводов
//   servo1.write(angle1);
//   servo2.write(angle2);

//   tft.fillScreen(TFT_BLACK);

//   if (isOpen) {
//     tft.setTextColor(TFT_WHITE);
//     tft.setCursor((tft.width() - 200) / 2, (tft.height() - 60) / 2);
//     tft.print("Elapsed time: 4 seconds");
//   } else {
//     tft.setTextColor(TFT_WHITE);
//     tft.setCursor((tft.width() - 180) / 2, (tft.height() - 60) / 2);
//     tft.print("Servo 1 angle: ");
//     tft.print(angle1);

//     tft.setCursor((tft.width() - 180) / 2, (tft.height() - 20) / 2);
//     tft.print("Servo 2 angle: ");
//     tft.print(angle2);
//   }

//   delay(100);
// }
// Этот код представляет собой пример программы, которая управляет двумя сервоприводами и выводит информацию на дисплей TFT. Вот основной функционал программы:
// * 		Инициализация дисплея и сервоприводов в функции setup().
//     * В функции loop() происходит следующее:
//     * Считывание состояния кнопки с помощью digitalRead(buttonPin).
//     * Если кнопка нажата и состояние "открыто" (isOpen) равно false, то устанавливаются новые углы для сервоприводов (angle1 и angle2), и переменная isOpen устанавливается в true. Также сохраняется время нажатия кнопки.
//     * Если кнопка не нажата, и состояние "открыто" (isOpen) равно true, и прошло более 3900 миллисекунд (4 секунды минус небольшая поправка), то устанавливаются новые углы для сервоприводов, возвращая их в исходное состояние, и переменная isOpen устанавливается в false.
//     * Обновление положений сервоприводов с помощью servo1.write(angle1) и servo2.write(angle2).
//     * Очистка экрана дисплея (tft.fillScreen(TFT_BLACK)).
//     * Если состояние "открыто" (isOpen) равно true, то выводится сообщение "Elapsed time: 4 seconds" на дисплей.
//     * Если состояние "открыто" (isOpen) равно false, то выводятся углы сервоприводов на дисплей.
// Таким образом, программа позволяет открыть сервоприводы на 55 и 125 градусов соответственно при первом нажатии кнопки, и через 4 секунды они возвращаются в исходное состояние (0 и 180 градусов). Информация о состоянии и углах сервоприводов выводится на дисплей TFT.
////////////////////////////////
///////////////////////////////




// Возможно эта была компиляция Блютуз гарнитуры ИИ #include <NimBLEDevice.h>
// #include <TFT_eSPI.h>

// static BLEAddress *pServerAddress;
// static NimBLEAdvertisedDevice* advDevice;

// TFT_eSPI tft = TFT_eSPI();
// int dots = 0;

// class MyClientCallback : public NimBLEClientCallbacks {
//   void onConnect(NimBLEClient* pclient) {
//     Serial.println("Connected");
//     tft.fillScreen(TFT_BLACK);
//     tft.setCursor((tft.width() - tft.textWidth("Connected")) / 2, tft.height() / 2);
//     tft.println("Connected");
//   }

//   void onDisconnect(NimBLEClient* pclient) {
//     Serial.println("Disconnected");
//     tft.fillScreen(TFT_BLACK);
//     tft.setCursor((tft.width() - tft.textWidth("Disconnected")) / 2, tft.height() / 2);
//     tft.println("Disconnected");
//   }
// };

// bool connectToServer(BLEAddress pAddress) {
//   NimBLEClient*  pClient  = NimBLEDevice::createClient();

//   Serial.println("Forming a connection to ");
//   pClient->setClientCallbacks(new MyClientCallback());

//   pServerAddress = new BLEAddress(pAddress);
//   // Connect to the remove BLE Server.
//   pClient->connect(*pServerAddress, true);
//   delay(2000); 

//   return true;
// }

// void setup() {
//   Serial.begin(115200);
//   tft.init();
//   tft.setRotation(2);
//   tft.fillScreen(TFT_BLACK);
//   tft.setTextSize(2);

//   // Print message before connecting
//   String message = "Attempting to connect...";
//   tft.setCursor((tft.width() - tft.textWidth(message)) / 2, tft.height() / 2);
//   tft.println(message);

//   NimBLEDevice::init("");
//   connectToServer(BLEAddress("00:00:00:00:00:00"));
// }

// void loop() {
//   delay(1000); // delay for one second
//   tft.drawCircle(10 + dots * 10, 10, 5, TFT_WHITE); // draw a white dot at position (10+dots*10, 10)
//   dots = (dots + 1) % 10; // increment dots, resetting to 0 after 10
// }


// TFT_eSPI tft = TFT_eSPI();  // Create an instance of the library
// #include "my_image.h" // Include the image data

// void setup() {
//     tft.init();  // Initialize the display
//     tft.setRotation(2);  // Set the orientation of the display
// }

// void loop() {
//     // Display the image
//     tft.pushImage(0, 0, zeekr.header.w, zeekr.header.h, (uint16_t*)zeekr.data);
//     delay(5000);  // Wait for 5 seconds before refreshing
// }

