#define pinStep 9
#define pinDir 10
#define pinEnable 11

#define pinPot A1 // потенциометр

#define pinBtnDown 2 // кнопка "меньше"
#define pinBtnUp 3 // кнопка "больше"
#define btnTimer 3000 // таймаут удержания кнопки

#define steps 200 // Кол-во шагов на оборот двигателя  
#define rampStep 0,1 // шаг изменения рампы
#define minRamp 0,1 // 0.1 секунда
#define maxRamp 2 // 2 секнуды

#define delayMaxSpeed 150 // Задержка между шагами для 2 об/с
#define delayMinSpeed 1250 // Задержка между шагами для 0.25 об/с

uint32_t timer;

void setup(){   

  Serial.begin(9600);
  pinMode(pinStep, OUTPUT);                    
  pinMode(pinDir, OUTPUT);  
  pinMode(pinEnable, OUTPUT);    
  pinMode(pinPot, INPUT);   

  pinMode(pinBtnDown, INPUT_PULLUP);
  pinMode(pinBtnUp, INPUT_PULLUP);

}   

void loop() { 


  buttons();

  // motor(potentio());
  // info(potentio());

}

void buttons(){

  static bool flag = false;

  bool btnDown = !digitalRead(pinBtnDown); // меньше
  bool btnUp = !digitalRead(pinBtnUp); // больше


  if (btnUp && !flag && millis() - timer > 3000) {
    flag = true;
    timer = millis();
    Serial.println("Longlick!");
  }
  else {
    flag = false;
    timer = millis();
  }

}

void ramp(){
}

uint16_t potentio(){
  /*Функция чтения и обработки сигнала с потенциометра */ 

  bool flag = false; // флаг работы

  int val = analogRead(pinPot);

  if (val > 0){
    val = map(val, 0, 1023, delayMinSpeed, delayMaxSpeed);
    val = constrain(val, delayMaxSpeed, delayMinSpeed);
    return val;
  }
  else {
    Serial.println("Для начала работы поверните ручку резистора!");
    delay(100);
  }
}

void motor(uint16_t val){
    /*Функция управления мотором*/

    if (val > 0 && val <= delayMinSpeed){ 
    digitalWrite(pinEnable, LOW);
    digitalWrite(pinDir, 1);
    digitalWrite(pinStep, HIGH);
    delay(val);
    digitalWrite(pinStep, LOW);
  }
  else {
    digitalWrite(pinEnable, HIGH); // запрещаем работу по ТЗ
  }
  
}

void info(uint16_t val){
  /* Вывод информации в последовательный порт*/

  if (millis() - timer > 5000){
    timer = millis();
    Serial.print("Текущая скорость - ");
    Serial.print(val/75);
    Serial.println(" об/мин");
    
  }
  
}
