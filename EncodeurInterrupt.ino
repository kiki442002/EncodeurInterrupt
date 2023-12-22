#include "FastInterruptEncoder.h"

Encoder encDroit(PA0, PA1, SINGLE , 250 ); // - Example for STM32, check datasheet for possible Timers for Encoder mode. TIM_CHANNEL_1 and TIM_CHANNEL_2 only
Encoder encGauche(PB4, PB5, SINGLE , 250 );


void setup() {
  Serial.begin(115200);
  
  if (encDroit.init() && encGauche.init()) {
    Serial.println("Encoder Initialization OK");
  } else {
    Serial.println("Encoder Initialization Failed");
    while(1);
  }

  TIM_TypeDef *Instance = TIM4;
  HardwareTimer *MyTim = new HardwareTimer(Instance);
  MyTim->setOverflow(10, HERTZ_FORMAT); // 100 Hz
  MyTim->attachInterrupt(Update_IT_callback);
  MyTim->resume();
}

void Update_IT_callback(void)
{ 
  encDroit.loop(); 
  encGauche.loop(); 
  Serial.print("Droit: ");
  Serial.println(encDroit.getTicks());
  Serial.print("Gauche: ");
  Serial.println(encGauche.getTicks());
}

void loop() {}
