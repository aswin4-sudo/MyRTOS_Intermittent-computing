/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os2.h"
#include "checkpoint.h"
#include "usart.h"
#include "power_sim.h"
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

// FreeRTOS includes
#include "MyRTOS.h"
#include "task.h"

// ==========================================
// GLOBAL VARIABLES
// ==========================================
volatile uint32_t current_step = 0;
volatile uint32_t current_progress = 0;

// ==========================================
// UART DEBUG FUNCTIONS
// ==========================================
void UART_Print(const char *msg) {
    HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), 100);
}

void UART_Printf(const char *format, ...) {
    char buffer[256];
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);
    UART_Print(buffer);
}

// ==========================================
// FUNCTION PROTOTYPES
// ==========================================
void SystemClock_Config(void);
void MX_GPIO_Init(void);
void MX_USART2_UART_Init(void);
void Error_Handler(void);

// ==========================================
// MONITOR TASK – Shows Power & Checkpoint Status
// ==========================================
void MonitorTask(void *argument) {
    UART_Printf("[TASK] MonitorTask started!\n");
    for(;;) {
        // Use the new function: PowerSim_GetVoltagePercent()
        UART_Printf("[MONITOR] Voltage: %d%% | Mode: %s | Checkpoint: %s\n",
                    PowerSim_GetVoltagePercent(),
                    PowerSim_GetModeString(),
                    has_checkpoint ? "ACTIVE" : "INACTIVE");
        if(power_failing) {
            UART_Printf("[MONITOR] ⚡ POWER FAILING!\n");
        }
        osDelay(1000);
    }
}

// ==========================================
// SYSTEM CLOCK CONFIGURATION (CubeMX generated)
// ==========================================
void SystemClock_Config(void) {
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
    __HAL_RCC_PWR_CLK_ENABLE();
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) { Error_Handler(); }
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                                 |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK) { Error_Handler(); }
}

// ==========================================
// GPIO INITIALIZATION (CubeMX generated)
// ==========================================
void MX_GPIO_Init(void) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    __HAL_RCC_GPIOH_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
    GPIO_InitStruct.Pin = GPIO_PIN_5;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

// ==========================================
// ERROR HANDLER
// ==========================================
void Error_Handler(void) {
    __disable_irq();
    while (1) {}
}

// ==========================================
// HAL TIM PERIOD ELAPSED CALLBACK (for HAL timebase)
// ==========================================
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
    if (htim->Instance == TIM2) { HAL_IncTick(); }
}



// Simple test task
void TestTask(void *pvParameters) {
    uint32_t counter = 0;
    UART_Printf("[TASK] Started!\n");

    while(1) {
    	// ==========================================
    	// PAUSE DURING POWER OFF
    	// ==========================================
    	while(power_mode == POWER_MODE_OFF) {
    	    UART_Printf("[TASK] ⏸️ Waiting for power...\n");
    	    vTaskDelay(pdMS_TO_TICKS(100));   // Wait 100ms
    	}
        counter++;
        UART_Printf("[TASK] Counter: %lu\n", counter);
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

int main(void) {
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_USART2_UART_Init();

    PowerSim_Init();
    Checkpoint_Init();

    UART_Printf("\n========================================\n");
    UART_Printf("     MYRTOS STARTING UP!\n");
    UART_Printf("========================================\n");

    // Create test task
    xTaskCreate(TestTask, "Test", 512, NULL, 1, NULL);

    UART_Printf("[INFO] Starting Scheduler...\n");
    vTaskStartScheduler();

    while (1) {}
}
