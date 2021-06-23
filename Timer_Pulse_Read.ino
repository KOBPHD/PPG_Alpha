//Written partially by Kevin O'Brien with heavy lifting from https://github.com/khoih-prog/TimerInterrupt_Generic/tree/main/examples/NANO33BLE

//Intended for use on an nRF52-based Arduino Nano-33-BLE board
#define TIMER_INTERRRUPT_DEBUG 0
#define _TIMERINTERRUPT_LOGLEVEL_0

//Not a standard package but available in the Arduino IDE through the built-in installer.
#include "TimerInterrupt_Generic.h"

#define TIMER0_INTERVAL_MS 5 //5ms period = 200Hz sample rate
//Is toggled by timer and main loop
volatile bool reset0 = false;

static uint32_t last_millis = 0;

// Init NRF52 timer NRF_TIMER3
NRF52_MBED_Timer ITimer0(NRF_TIMER_3);

//Sets reset0 to false in the timer function to maintain consistent timing
void TimerHandler0()
{  
  reset0 = true;
}

//Pulse sensor amped sense pin on Analog Pin 7
int analogPin = A7;
//Default ADC_val is set to higher than ADC max to mark as false reading
unsigned int ADC_val = 4096;

//Start a 115.2Kbaud serial connection, then attach the timer interrupt and configure for correct period.
void setup() {
  Serial.begin(115200);
  while(!Serial);
  delay(100);
  ITimer0.attachInterruptInterval(TIMER0_INTERVAL_MS * 1000, TimerHandler0);
}

//If reset0 has been toggled by the timer function, grab millis and combine with an ADC poll
//then print as a string and toggle reset0 back to false.
void loop() {
  // put your main code here, to run repeatedly:
  if(reset0){
    ADC_val = analogRead(analogPin);
    String out_str = String(millis())+","+String(ADC_val);
    Serial.println(out_str);
    reset0 = false;
  }

}
