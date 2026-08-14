#include "checkpoint.h"
#include <string.h>
#include <stdio.h>

extern void UART_Printf(const char *format, ...);

volatile uint8_t power_failing = 0;
volatile uint8_t has_checkpoint = 0;
volatile uint32_t checkpoint_counter = 0;

static Checkpoint_t checkpoints[MAX_CHECKPOINTS];

void Checkpoint_Init(void) {
    memset(checkpoints, 0, sizeof(checkpoints));
    has_checkpoint = 0;
    power_failing = 0;
    checkpoint_counter = 0;
    UART_Printf("[CHECKPOINT] Init\n");
}

void Checkpoint_Save(TaskHandle_t task) {
    if (task == NULL) {
        UART_Printf("[CHECKPOINT] Save: NULL task\n");
        return;
    }

    int slot = -1;
    for (int i = 0; i < MAX_CHECKPOINTS; i++) {
        if (!checkpoints[i].valid) { slot = i; break; }
    }
    if (slot == -1) {
        UART_Printf("[CHECKPOINT] Save: No free slots\n");
        return;
    }

    Checkpoint_t *cp = &checkpoints[slot];
    cp->magic = CHECKPOINT_MAGIC;
    cp->task_handle = task;
    cp->timestamp = xTaskGetTickCount();
    cp->saved_progress = 0;
    cp->valid = 1;

    has_checkpoint = 1;
    checkpoint_counter++;

    UART_Printf("[CHECKPOINT] SAVED (slot %d, task %p)\n", slot, (void*)task);
}

TaskHandle_t Checkpoint_Restore(void) {
    if (!has_checkpoint) {
        UART_Printf("[CHECKPOINT] Restore: No checkpoint\n");
        return NULL;
    }

    int best_slot = -1;
    uint32_t latest_time = 0;
    for (int i = 0; i < MAX_CHECKPOINTS; i++) {
        if (checkpoints[i].valid && checkpoints[i].timestamp > latest_time) {
            latest_time = checkpoints[i].timestamp;
            best_slot = i;
        }
    }
    if (best_slot == -1) {
        has_checkpoint = 0;
        UART_Printf("[CHECKPOINT] Restore: No valid checkpoint\n");
        return NULL;
    }

    Checkpoint_t *cp = &checkpoints[best_slot];
    TaskHandle_t task = cp->task_handle;

    UART_Printf("[CHECKPOINT] RESTORED (slot %d, task %p)\n", best_slot, (void*)task);

    cp->valid = 0;
    has_checkpoint = 0;

    return task;
}

void Checkpoint_PowerMonitor(void) {
    // Called from SysTick – checks power status
}
