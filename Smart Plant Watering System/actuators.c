#include "actuators.h"
#include <stdio.h>
#include <stdlib.h>

static pump_state_t pump_state = PUMP_OFF;
static led_state_t led_state = LED_NORMAL;

void actuators_init(void) {
    pump_state = PUMP_OFF;
    led_state = LED_NORMAL;
    printf("[ACT] Init actuators. Pump OFF. LED NORMAL\n");
}

void turn_pump_on(void) {
    if(pump_state == PUMP_ON) return;
    pump_state = PUMP_ON;
    printf("[ACT] Pump: ON\n");
}

void turn_pump_off(void) {
    if(pump_state == PUMP_OFF) return;
    pump_state = PUMP_OFF;
    printf("[ACT] Pump: OFF\n");
}

void set_led(led_state_t state) {
    if(led_state == state) return;
    led_state = state;
    const char *name[] ={"NORMAL","WATERING","LOW_MOISTURE_ALERT","ERROR"};
    printf("[ACT] LED -> %s\n", names[state]);
}

pump_state_t get_num_state(void) {return pump_states; }
led_state_t get_led_state(void) {return led_state; }
