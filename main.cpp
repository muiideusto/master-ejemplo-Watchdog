/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"

#define pinBT1 PA_15

const uint32_t TIMEOUT_MS = 5000;
InterruptIn bt1(pinBT1);
volatile int countdown = 9;

void trigger()
{
    Watchdog::get_instance().kick();
    countdown = 9;
}

int main()
{
    printf("\r\nIniciado.\r\n");

    Watchdog &watchdog = Watchdog::get_instance();
    watchdog.start(TIMEOUT_MS);
    bt1.rise(&trigger);

    uint32_t watchdog_timeout = watchdog.get_timeout();
    printf("Watchdog inicializado a %lu ms.\r\n", watchdog_timeout);
    printf("Pulsa al menos una vez cada %lu ms para reiniciar el "
           "watchdog y prevenir que el sistema se reinicie.\r\n", watchdog_timeout);

    while (1) {
        printf("\r%3i", countdown--);
        fflush(stdout);
        ThisThread::sleep_for(TIMEOUT_MS / 10);
    }
}