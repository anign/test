#define PIN_STEP 9
#define PIN_DIR 10
#define PIN_ENA 11

#define PIN_POTENTIO A1
#define PIN_BUTTON_DOWN 2
#define PIN_BUTTON_UP 3

#define STEPS 1000 // Кол-во шагов двигателя  

void setup(){   
  Serial.begin(9600);
  pinMode(PIN_STEP, OUTPUT);                    
  pinMode(PIN_DIR, OUTPUT);  
  pinMode(PIN_ENA, OUTPUT);    
  pinMode(PIN_POTENTIO, INPUT);   
}  

void loop() {
  digitalWrite(PIN_ENA, 0); // разрешить работу
  digitalWrite(PIN_DIR, 0); // направление вращения

  digitalWrite(PIN_ENA, 1); // запретить работу

  
  // Serial.println(SPEED, RAMP);
}
