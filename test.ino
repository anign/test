#define pinStep 9
#define pinDir 10
#define pinEnable 11

#define pinPot A1 // потенциометр

#define pinBtnDown 2 // кнопка "меньше"
#define pinBtnUp 3 // кнопка "больше"
#define btnTimer 1000 // таймаут удержания кнопки

#define steps 200 // Кол-во шагов на оборот двигателя  
#define rampStep 0.1 // шаг изменения рампы
#define minRamp 0.1 // 0.1 секунда
#define maxRamp 2// 2 секунуды
#define rampSteps 10

uint16_t delayMinSpeed = 1000 / (steps * 0.1); // 0.1 rpm
uint16_t delayMaxSpeed = 1000 / (steps * 2); // 2 rpm


uint32_t timer;
uint32_t tmr;

float currentRamp = minRamp;

void setup(){   
 
  Serial.begin(9600);
  pinMode(pinStep, OUTPUT);                    
  pinMode(pinDir, OUTPUT);  
  pinMode(pinEnable, OUTPUT);    
  pinMode(pinPot, INPUT);   
  pinMode(pinBtnDown, INPUT_PULLUP);
  pinMode(pinBtnUp, INPUT_PULLUP);
}

uint16_t pause = 1000 * ramp() / rampSteps;
uint16_t k = potentio() * rampSteps;

void loop() { 
  
  mainFunc();

}

void mainFunc(){

  info(potentio(), ramp());
  motor(potentio(), ramp());
}

float ramp(){
  /* Функция изменения рампы */

  bool btnDown = !digitalRead(pinBtnDown); // меньше
  bool btnUp = !digitalRead(pinBtnUp); // больше

  if (btnDown && millis() - timer > btnTimer) {
    timer = millis();

    if (currentRamp <= minRamp){
      Serial.println("Рампа минимальна!");   
    }
    else if (currentRamp >= (minRamp + 0.1) && currentRamp < (maxRamp + 0.1)){
      currentRamp -= rampStep;
      Serial.print("Текущая рампа - ");
      Serial.println(currentRamp);
    }
  }


  if (btnUp && millis() - timer > btnTimer) {
    timer = millis();
    if (currentRamp >= 2){
       Serial.println("Максимальная рампа!");    
    }
    else if(currentRamp >= minRamp && currentRamp < 2){
      currentRamp += rampStep;
      Serial.print("Текущая рампа - ");
      Serial.println(currentRamp);
    }
  }
  return currentRamp;
}


uint16_t potentio(){
  /*Функция чтения и обработки сигнала с потенциометра */ 

  uint16_t resistor = analogRead(pinPot);
  uint16_t motorSpeed = map(resistor, 0, 1023, delayMinSpeed, delayMaxSpeed);
  return motorSpeed;
}


void motor(float val, float ramp){
    /*Функция управления мотором*/

  if (val < 0){ 
    digitalWrite(pinEnable, HIGH); // запрещаем работу по ТЗ
  }

  digitalWrite(pinEnable, LOW);
  digitalWrite(pinDir, 1);
  digitalWrite(pinStep, HIGH);

  if (millis() - timer >= val){
    timer = millis();
    digitalWrite(pinStep, LOW);
  } 
}

void info(float val, float ramp){
  /* Вывод информации в последовательный порт*/
  
  if (millis() - tmr > 3000){
    tmr = millis();
    Serial.print("Текущая скорость - ");
    Serial.print(60/(val/1000)/steps); // 60 секунд
    Serial.println(" об/мин");
    Serial.print("Текущая рампа - ");
    Serial.println(ramp);  
  } 
}
