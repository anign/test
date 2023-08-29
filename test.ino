#define pinStep 9
#define pinDir 10
#define pinEnable 11

#define pinPot A1 // потенциометр

#define pinBtnDown 2 // кнопка "меньше"
#define pinBtnUp 3 // кнопка "больше"
#define btnTimer 1000 // таймаут удержания кнопки

#define steps 200 // Кол-во шагов на оборот двигателя  
#define rampStep 0.3 // шаг изменения рампы
#define minRamp 5 // 0.1 секунда
#define maxRamp 10 // 2 секнуды
#define rampSteps 10

#define delayMaxSpeed 150 // Задержка между шагами для 2 об/с
#define delayMinSpeed 1500 // Задержка между шагами для ~0.2 об/с

uint32_t timer;

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

uint16_t multi = potentio() * rampSteps;

void loop() { 

  //Serial.println(calcCoeff(potentio(), ramp()));
  //x = calcCoeff(potentio(), ramp());

  //Serial.println(x);
  
  motor(calcCoeff(potentio(), ramp()));
  //info(potentio(), ramp());
  //motor(potentio());

  
  
}


uint16_t calcCoeff(uint16_t val, float ramp){

  for(float i = 0.1; i <= ramp; i += ramp / rampSteps){
    uint16_t pause = 1000 * ramp / rampSteps;

    if(millis() - timer >= pause){
      timer = millis(); 
      if(multi >= val){
        return multi;
      }
      else{
        break;
      }
    multi -= val;
    }
  } 
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

  int val = analogRead(pinPot);
  val = map(val, 0, 1023, delayMinSpeed, delayMaxSpeed);
  val = constrain(val, delayMaxSpeed, delayMinSpeed);
  return val;
}

void motor(uint16_t val){
    /*Функция управления мотором*/

  if (val < 0){ 
    digitalWrite(pinEnable, HIGH); // запрещаем работу по ТЗ
  }

  digitalWrite(pinEnable, LOW);
  digitalWrite(pinDir, 1);
  digitalWrite(pinStep, HIGH);
  Serial.println(val);
  delay(val);
  digitalWrite(pinStep, LOW);


}

void info(float val, float ramp){
  /* Вывод информации в последовательный порт*/

  if (millis() - timer > 5000){
    timer = millis();
    if (val >= delayMinSpeed){
      Serial.println("Для начала работы поверните ручку резистора!");
    }
    else{
      Serial.print("Текущая скорость - ");
      Serial.print(60/(val/1000)/steps);
      Serial.println(" об/мин");
      Serial.print("Текущая рампа - ");
      Serial.println(ramp);
      
    }
  } 
}
