# Custom RTOS with Checkpointing for Energy-Harvesting IoT Devices

## Overview

This project focuses on designing a lightweight custom Real-Time Operating System (RTOS) for ARM Cortex-M4-based embedded systems operating under intermittent power conditions. In energy-harvesting IoT devices, the available power can fluctuate or disappear unexpectedly, potentially interrupting tasks and causing the loss of computational progress. The project explores checkpointing and recovery mechanisms that preserve essential execution and application state in non-volatile memory, enabling interrupted computations to resume when power becomes available again.

The system combines embedded task management, context switching, power-failure handling, checkpoint storage, and recovery concepts to improve computational resilience in energy-constrained environments.

## Problem Statement

Energy-harvesting devices obtain power from sources such as solar energy, mechanical vibration, and thermal gradients. Unlike conventional battery-powered systems, these devices may experience intermittent energy availability. If power disappears while a task is executing, volatile memory loses its contents and the computation may need to restart from the beginning.

This can result in repeated computation, wasted energy, delayed results, and difficulty completing long-running tasks.

## Project Objectives

- Design a lightweight RTOS architecture for ARM Cortex-M4-based embedded systems.
- Explore task scheduling and context switching using Cortex-M4 mechanisms.
- Develop a checkpointing approach to preserve execution and application state.
- Investigate power-failure detection and safe checkpoint initiation.
- Design a recovery mechanism to restore valid checkpoint data after reboot.
- Explore checkpoint integrity and protection against incomplete writes.
- Evaluate the design under controlled power-interruption scenarios using Renode.
- Study trade-offs involving checkpoint latency, energy consumption, recovery time, and non-volatile memory endurance.

## System Architecture

```text
        Energy-Harvesting Source
                  |
                  v
        Power Management Circuit
                  |
                  v
         Energy Storage Element
          (Capacitor / Storage)
                  |
                  v
          ARM Cortex-M4 MCU
                  |
                  v
          Custom RTOS Kernel
          /       |        \
         v        v         v
    Scheduler  Context   Power-Failure
               Switching   Handling
                  |            |
                  v            v
             Task State   Checkpoint Manager
                               |
                               v
                      Non-Volatile Memory
                               |
                               v
                      Recovery on Reboot
                               |
                               v
                      Resume Computation
```

## Key Features

### 1. Custom RTOS Architecture

The project explores a lightweight RTOS structure for resource-constrained microcontrollers, focusing on task management, scheduling, processor-state handling, and recovery under intermittent power conditions.

### 2. ARM Cortex-M4 Context Switching

PendSV-based context switching is investigated for saving and restoring task execution context. The context may include processor registers, stack information, and other state required to resume a task, depending on the implementation.

### 3. Checkpointing Mechanism

Checkpointing preserves the information required to reconstruct a computation after a power interruption. Depending on the implementation, this can include task execution context, application variables, progress counters, and algorithm state.

### 4. Power-Failure Handling

A voltage-monitoring mechanism can detect a falling supply voltage and initiate checkpointing before the microcontroller becomes unable to execute instructions. Successful checkpointing requires sufficient remaining energy to complete the operation.

### 5. Non-Volatile State Storage

Non-volatile memory, such as internal Flash or external FRAM, can preserve checkpoint information across complete power loss. The choice depends on write endurance, latency, capacity, and energy requirements.

### 6. Recovery and State Restoration

During startup, the system can check for a valid checkpoint, verify its integrity, restore the required execution and application state, and resume computation. If no valid checkpoint exists, the application can follow its normal startup path.

### 7. Checkpoint Integrity

Checkpoint metadata, sequence numbers, checksums, and validity markers can help detect incomplete or corrupted checkpoint writes. A dual-slot strategy can preserve an older valid checkpoint while a new one is being written.

### 8. Simulation and Validation

Renode is used to investigate embedded firmware behavior in a controlled virtual environment. Simulation helps with repeatable debugging and testing, while physical hardware testing is required to validate real voltage behavior, checkpoint energy requirements, and actual recovery timing.

## Execution Workflow

1. Initialize the microcontroller and RTOS.
2. Initialize tasks and start the scheduler.
3. Execute application tasks while sufficient energy is available.
4. Monitor the supply voltage or receive a power-failure signal.
5. Initiate checkpointing when the power-failure condition is detected.
6. Preserve the required execution context and application state in non-volatile memory.
7. Enter a safe shutdown or low-power state when continued execution is no longer possible.
8. Restart when sufficient power becomes available.
9. Validate the stored checkpoint and restore the required state.
10. Resume the interrupted computation or start normally if no valid checkpoint is available.

## Example Application: Industrial Machine-Health Monitoring

An industrial monitoring node can use a vibration energy harvester to convert a portion of a machine's mechanical vibration into electrical energy. A power-management circuit stores the harvested energy in a capacitor and supplies the microcontroller.

An accelerometer collects vibration samples, and the embedded application processes the data to identify possible abnormal vibration patterns. If the available energy becomes insufficient before a long-running analysis finishes, checkpointing can preserve the processing state. When sufficient energy becomes available again, the system can restore the checkpoint and continue the analysis instead of repeating all previous computation.

The effectiveness of this approach depends on the actual harvested power, energy-storage capacity, computation requirements, and checkpoint overhead. If a task consistently finishes within one energy burst, checkpointing may not provide a meaningful benefit.

## Technologies and Tools

- **Programming Language:** C
- **Processor Architecture:** ARM Cortex-M4
- **Embedded Operating Systems:** Custom RTOS concepts
- **Processor Mechanisms:** PendSV, interrupts, context switching
- **Memory:** RAM and non-volatile memory concepts
- **Simulation:** Renode
- **Hardware Validation:** STM32 Cortex-M4 development board, voltage monitoring, controlled power switching, and oscilloscope measurements (planned or applicable depending on implementation)

## Testing and Evaluation

The design can be evaluated using controlled power interruptions at different points during task execution.

Important evaluation metrics include:

- **Checkpoint latency:** Time required to save a checkpoint.
- **Recovery time:** Time from power restoration to useful application execution.
- **Lost computational progress:** Work that must be repeated after an interruption.
- **Checkpoint overhead:** Additional execution time and energy consumed by checkpointing.
- **Checkpoint integrity:** Ability to identify incomplete or corrupted checkpoint data.
- **Task completion:** Whether long-running computation completes across multiple energy cycles.
- **Memory endurance:** Impact of repeated checkpoint writes on non-volatile memory.

Comparisons against a restart-only baseline can help determine whether checkpointing provides measurable benefits.

## Limitations and Design Considerations

- Checkpointing consumes energy and must finish before the MCU supply becomes unreliable.
- The power-management circuit and energy-storage element must provide sufficient hold-up energy for safe checkpointing.
- Arbitrary task restoration is more complex than saving a single progress counter because stack contents, processor state, pointers, and application state may need special handling.
- Non-volatile memory has limitations involving write endurance, latency, and capacity.
- Simulation results do not replace validation on physical hardware.
- Checkpointing is most useful when computation cannot reliably finish within a single available energy burst.

## Future Enhancements

- Integrate the design with a physical STM32 Cortex-M4 development board.
- Implement and measure power-failure detection using a voltage supervisor or comparator.
- Integrate an energy-storage and controlled power-interruption circuit.
- Evaluate internal Flash versus external FRAM for checkpoint storage.
- Implement robust checkpoint validation and recovery.
- Measure checkpoint latency, energy consumption, and recovery performance.
- Explore adaptive checkpoint strategies based on available energy and task progress.
- Investigate integration with energy-harvesting sensor nodes and industrial monitoring applications.

## Conclusion

This project explores the design of a lightweight RTOS that addresses computation loss in intermittently powered embedded systems. By combining task execution management, processor-context handling, checkpoint storage, and recovery concepts, the system aims to support long-running computations across multiple energy cycles. The project provides a practical learning platform for embedded firmware development, ARM Cortex-M architecture, RTOS internals, non-volatile memory management, and energy-aware computing.

## Author

**Aswin M.**

Interested in Embedded Systems, Firmware Development, RTOS, ARM Cortex-M, and Energy-Efficient IoT Systems.
