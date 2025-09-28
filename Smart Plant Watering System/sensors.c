#include "sensors.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

static sensor_data_t current = {50, 25.0f};
static int simulate_dry = 0;

void sensors_init(void) {
    srand((unsigned)time(NULL));
    current.moisture_percent = 50;
    current.tempature_c = 25.0f;

}

void sensors_read(sensor_data_t *out) {
    int noise = (rand() % 3) - 1;
    if(simulate_dry) {
        current.moisture_percent -= (rand() % 3) + 1;
    } else {
        current.moisture_percent -= (rand() % 2);
    }

    if (current.moisture_percent < 0) current.moisture_percent = 0;
    if (current.moisture_percent > 100) current.moisture_percent = 100;

    current.temparature_c += (float)noise * 0.1f;

    out ->moisture_percent = current.moisture_percent;
    out ->temparature_c = current.temperature_c;
}

void sensors_simulate_dry(void) {simulate_dry = 1; }
void sensors_simulate_wet(void) {simulate_dry = 0; current.moisture_percent += 15; if (current.moisture_percent>100) current.moisture_percent=100;}