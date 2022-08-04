#include <Arduino.h>
#include <EEPROM.h>


#define FIRST_CODE_UPLOAD					1
#define DEBUG								1
#define EEPROM_START_ADDR					0
#define STORE_LAST_STATE					0

#define AERATOR_START_PIN					0 // Interrupt pin
#define AERATOR_STOP_PIN					1 // Interrupt pin
#define SSR_CONTROLL_PIN					3 // Output pin == SSR input pin


#define DEBOUNCE_TIME						500



unsigned long last_ON_interrupt_time = 0;
unsigned long last_OFF_interrupt_time = 0;

bool ssr_pin_status;

// void turnOnSSR()
// {
// 	if(millis() - last_ON_interrupt_time > DEBOUNCE_TIME)
// 	{
// 		digitalWrite(SSR_CONTROLL_PIN, HIGH);
// 		last_ON_interrupt_time = millis();
// 	}
	
// }

// void turnOffSSR()
// {
// 	if(millis() - last_OFF_interrupt_time > DEBOUNCE_TIME)
// 	{
// 		digitalWrite(SSR_CONTROLL_PIN, LOW);
// 		last_OFF_interrupt_time = millis();
// 	}
// }

void setup()
{
	digitalWrite(SSR_CONTROLL_PIN, LOW);
	pinMode(SSR_CONTROLL_PIN, OUTPUT);
	pinMode(AERATOR_START_PIN, INPUT);
	pinMode(AERATOR_STOP_PIN, INPUT);

	// attachInterrupt(digitalPinToInterrupt(AERATOR_START_PIN), turnOnSSR, RISING);
	// attachInterrupt(digitalPinToInterrupt(AERATOR_STOP_PIN), turnOffSSR, RISING);

	#ifdef FIRST_CODE_UPLOAD
		EEPROM.put(EEPROM_START_ADDR, 0); // Store 0/False when starting for the first time
	#endif // FIRST_CODE_UPLOAD
	ssr_pin_status = 0;
}

void loop()
{
	if(digitalRead(AERATOR_START_PIN) && !ssr_pin_status)
	{
		ssr_pin_status = 1;
	}

	if(digitalRead(AERATOR_STOP_PIN) && ssr_pin_status)
	{
		ssr_pin_status = 0;
	}


	digitalWrite(SSR_CONTROLL_PIN, ssr_pin_status);
}