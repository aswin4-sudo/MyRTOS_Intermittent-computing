#ifndef CHECKPOINT_H
#define CHECKPOINT_H

#include <stdint.h>
#include "task.h"

typedef struct {
    uint32_t magic;
    TaskHandle_t task_handle;
    uint32_t saved_progress;
    uint32_t saved_step;
    uint32_t timestamp;
    uint8_t valid;
} Checkpoint_t;

#define CHECKPOINT_MAGIC 0xDEADBEEF
#define MAX_CHECKPOINTS 5

extern volatile uint8_t power_failing;
extern volatile uint8_t has_checkpoint;
extern volatile uint32_t checkpoint_counter;

void Checkpoint_Init(void);
void Checkpoint_Save(TaskHandle_t task);
TaskHandle_t Checkpoint_Restore(void);   // ← Returns TaskHandle_t
void Checkpoint_PowerMonitor(void);

#endif
