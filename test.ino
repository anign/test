#define pinStep 9
#define pinDir 10
#define pinEnable 11

#define pinPot A1 // потенциометр

#define pinBtnDown 2 // кнопка "меньше"
#define pinBtnUp 3 // кнопка "больше"
#define btnTimer 2000 // таймаут удержания кнопки

#define steps 200 // Кол-во шагов на оборот двигателя  
#define rampStep 0,1 // шаг изменения рампы

#define delayMaxSpeed 150 // Задержка между шагами для 2 об/с
#define delayMinSpeed 1250 // Задержка между шагами для 0.25 об/с

void setup(){   
  
  Serial.begin(9600);
  pinMode(pinStep, OUTPUT);                    
  pinMode(pinDir, OUTPUT);  
  pinMode(pinEnable, OUTPUT);    
  pinMode(pinPot, INPUT);   

}   

void loop() { 

  motor(potentio());

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
    delay(1000);
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
