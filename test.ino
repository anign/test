#define pinStep 9
#define pinDir 10
#define pinEnable 11

#define pinPot A1 // потенциометр

#define pinBtnDown 2 // кнопка "меньше"
#define pinBtnUp 3 // кнопка "больше"
#define btnTimer 2000 // таймаут удержания кнопки

#define steps 1000 // Кол-во шагов двигателя  
#define rampStep 0,1 // шаг изменения рампы


void setup(){   
  pinMode(13, OUTPUT); // для отладки
  
  Serial.begin(9600);
  pinMode(pinStep, OUTPUT);                    
  pinMode(pinDir, OUTPUT);  
  pinMode(pinEnable, OUTPUT); 

  digitalWrite(pinEnable, HIGH); // по умолчанию запрет работы

  pinMode(pinPot, INPUT);   

  pinMode(pinBtnDown, INPUT_PULLUP);
  pinMode(pinBtnUp, INPUT_PULLUP);
  
}   

void loop() { 
  bool flag = false; //работа
  int val = analogRead(pinPot);
  val = map(val, 0, 1023, 0, 20);
  val = constrain(val, 0, 20);

  if (val >= 2){
    flag = true;    
    digitalWrite(pinEnable, LOW); // Разрешаем работу двигателя.
  }

  if (flag){
    digitalWrite(pinDir, 1); // напраление вращения
  }
}
void buttons(){

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
