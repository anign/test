#define pinStep 9
#define pinDir 10
#define pinEna 11

#define pinPotentio A1 // потенциометр

#define pinBtnDown 2 // кнопка "меньше"
#define pinBtnUp 3 // кнопка "больше"
#define btnTimer 2000 // таймаут удержания кнопки

#define steps 1000 // Кол-во шагов двигателя  
#define rampStep 0,1 // шаг изменения рампы

  // Флаги состояния кнопок

void setup(){   
  pinMode(13, OUTPUT); // для отладки
  
  Serial.begin(9600);
  pinMode(pinStep, OUTPUT);                    
  pinMode(pinDir, OUTPUT);  
  pinMode(pinEna, OUTPUT);    
  pinMode(pinPotentio, INPUT);   

  /* Использую НЗ контакты кнопок */
  pinMode(pinBtnDown, INPUT_PULLUP);
  pinMode(pinBtnUp, INPUT_PULLUP);
  
}   

void loop() { 
   /*Функция обработки нажатий. Подтяжка внутренним резистором к +5В.*/
  bool btnDownHold = false;
  bool btnUpHold = false;

  uint16_t timeLongClick; // время удержания кнопки
  uint16_t timePressBtnDown;    // момент нажатия кнопки "меньше"
  uint16_t timePressBtnUp;    // момент нажатия кнопки "меньше"
  
  bool btnDown = !digitalRead(pinBtnDown); // кнопка "меньше"
  bool btnUp = !digitalRead(pinBtnUp); // кнопка "больше"
  

  if (btnDown && !btnDownHold &&  millis() - timePressBtnDown > btnTimer){ 
    btnDownHold = true;
    timePressBtnDown = millis(); 
    digitalWrite(13, 1);
    Serial.print("btnDown LONGCLICK! "); Serial.println(timePressBtnDown);
  }


  
  if (btnUp && !btnUpHold &&  millis() - timePressBtnUp > btnTimer){ 
    btnUpHold = true;
    timePressBtnUp = millis(); 
    digitalWrite(13, 0);
    Serial.print("btnUp LONGCLICK! "); Serial.println(timePressBtnUp);
  }


}
