#include "power_sim.h"
#include "checkpoint.h"
#include <stdio.h>
#include "cmsis_os2.h"
#include "task.h"   // for taskYIELD

extern void UART_Printf(const char *format, ...);

volatile uint8_t voltage_percent = 100;
volatile uint8_t power_mode = POWER_MODE_STABLE;
volatile uint8_t power_recovered = 0;

static uint32_t phase_timer = 0;
static uint8_t cycle_complete = 0;

const char* PowerSim_GetModeString(void) {
    switch(power_mode) {
        case POWER_MODE_CHARGING:    return "CHARGING";
        case POWER_MODE_STABLE:      return "STABLE";
        case POWER_MODE_DISCHARGING: return "DISCHARGING";
        case POWER_MODE_FAILING:     return "FAILING";
        case POWER_MODE_OFF:         return "OFF";
        default:                     return "UNKNOWN";
    }
}

void PowerSim_Init(void) {
    voltage_percent = 100;
    power_mode = POWER_MODE_STABLE;
    phase_timer = 0;
    cycle_complete = 0;
    power_failing = 0;
    power_recovered = 0;
    UART_Printf("[POWER] Simulation started (100%%)\n");
}

void PowerSim_Update(void) {
    if (cycle_complete) return;

    static uint32_t counter = 0;
    counter++;
    if (counter % 10 != 0) return; // 10ms granularity

    phase_timer += 10;

    switch(power_mode) {
        case POWER_MODE_STABLE:
            voltage_percent = 100;
            if (phase_timer >= PHASE_DURATION_MS) {
                power_mode = POWER_MODE_DISCHARGING;
                phase_timer = 0;
                UART_Printf("[POWER] Discharging...\n");
            }
            break;

        case POWER_MODE_DISCHARGING: {
            uint32_t step = phase_timer / 1000;
            if (step > 4) step = 4;
            uint8_t target[] = {70, 50, 20, 0};
            voltage_percent = target[step];

            if (step == 2 && !power_failing) {
                power_failing = 1;
                power_mode = POWER_MODE_FAILING;
                UART_Printf("[POWER] BELOW THRESHOLD (20%%) - saving checkpoint\n");
            }

            if (phase_timer % 1000 < 20) {
                UART_Printf("[POWER] Voltage: %d%%\n", voltage_percent);
            }

            if (phase_timer >= 5000) {
                power_mode = POWER_MODE_OFF;
                phase_timer = 0;
                voltage_percent = 0;
                UART_Printf("[POWER] System OFF\n");
            }
            break;
        }

        case POWER_MODE_FAILING:
            if (has_checkpoint) {
                UART_Printf("[POWER] Checkpoint saved, powering off\n");
                power_mode = POWER_MODE_OFF;
                phase_timer = 0;
                power_failing = 0;
                voltage_percent = 0;
            } else if (phase_timer > 500) {
                UART_Printf("[POWER] Checkpoint timeout, forcing off\n");
                power_mode = POWER_MODE_OFF;
                phase_timer = 0;
                power_failing = 0;
                voltage_percent = 0;
            }
            break;

        case POWER_MODE_OFF:
            if (phase_timer >= PHASE_DURATION_MS) {
                power_mode = POWER_MODE_CHARGING;
                phase_timer = 0;
                voltage_percent = 10;
                power_recovered = 1;
                UART_Printf("[POWER] RECOVERED! Voltage: 10%%\n");
                taskYIELD();   // force context switch to restore checkpoint
            }
            break;

        case POWER_MODE_CHARGING: {
            uint32_t step = phase_timer / 1000;
            if (step == 0) voltage_percent = 10;
            else if (step == 1) voltage_percent = 20;
            else if (step == 2) voltage_percent = 40;
            else if (step >= 3) voltage_percent = 100;

            if (phase_timer % 1000 < 20 && step < 3) {
                UART_Printf("[POWER] Charging: %d%%\n", voltage_percent);
            }

            if (phase_timer >= 4000) {
                voltage_percent = 100;
                power_mode = POWER_MODE_STABLE;
                phase_timer = 0;
                cycle_complete = 1;
                UART_Printf("[POWER] Fully charged!\n");
            }
            break;
        }

        default: break;
    }
}

uint8_t PowerSim_GetVoltagePercent(void) {
    return voltage_percent;
}
