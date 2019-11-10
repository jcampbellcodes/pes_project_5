/*
 * @file delay.h
 * @brief Project 4
 *
 * @details This file contains prototypes for calculating a spin-wait
 *          on various platforms, used for delaying LED state changes.
 *
 * @author Jack Campbell
 * @tools  PC Compiler: GNU gcc 8.3.0
 *         PC Linker: GNU ld 2.32
 *         PC Debugger: GNU gdb 8.2.91.20190405-git
 *         ARM Compiler: GNU gcc version 8.2.1 20181213
 *         ARM Linker: GNU ld 2.31.51.20181213
 *         ARM Debugger: GNU gdb 8.2.50.20181213-git
 */
#ifndef PES_PROJECT_4_DELAY_H
#define PES_PROJECT_4_DELAY_H

#include <stdint.h>

/**
 * delay
 *
 * @brief Blocks execution for the specified time.
 * @param inDelayMs Then time in milliseconds to block.
 */
void delay(uint64_t inDelayMs);

#endif //PES_PROJECT_4_DELAY_H
