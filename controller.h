#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include <avr/eeprom.h>
#include "timer0.h"
#include "BLMC.h"
#include "state.h"

#define CONTROL_FORWARD_ARRAY_LENGTH	250
#define CONTROL_DEFAULT_P				0
#define CONTROL_DEFAULT_I				0

struct {
	uint16_t *is, *should;
	uint8_t out;
	uint16_t RPMToPWM[CONTROL_FORWARD_ARRAY_LENGTH];
	uint16_t lastTime;
	int16_t integral;
	uint8_t P, I;
	uint16_t sampleTimer;
	uint8_t sampleCharacteristic :1;
	uint8_t samplingFinished :1;
} control;

void control_Init(uint16_t *is, uint16_t *should);

void control_Sample(void);

void control_Update(uint8_t limited);

void control_SaveSettings(void);

void control_LoadSettings(void);

inline uint16_t control_VoltageToPWM(uint16_t Vout, uint16_t batVoltage) {
	return (((uint32_t) Vout) << 8) / batVoltage;
}

inline uint16_t control_PWMToVoltage(uint8_t PWM, uint16_t batVoltage) {
	return (((uint32_t) batVoltage) * PWM) >> 8;
}

#endif
