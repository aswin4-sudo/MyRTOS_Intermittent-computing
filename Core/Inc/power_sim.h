#ifndef POWER_SIM_H
#define POWER_SIM_H

#include <stdint.h>

#define POWER_MODE_CHARGING    0
#define POWER_MODE_STABLE      1
#define POWER_MODE_DISCHARGING 2
#define POWER_MODE_FAILING     3
#define POWER_MODE_OFF         4

#define PHASE_DURATION_MS 1000

extern volatile uint8_t voltage_percent;
extern volatile uint8_t power_mode;
extern volatile uint8_t power_failing;
extern volatile uint8_t has_checkpoint;
extern volatile uint8_t power_recovered;

void PowerSim_Init(void);
void PowerSim_Update(void);
uint8_t PowerSim_GetVoltagePercent(void);
const char* PowerSim_GetModeString(void);

#endif
