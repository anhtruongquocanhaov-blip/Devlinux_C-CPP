#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include "config.h"
#include "types.h"
#include "sensors.h"
#include "actuators.h"
#include "buttons.h"
#include "watering_logic.h"
#include "utils.h"

static system_config_t cfg;
static sensor_data_t sdata;


static void init_system(void) {
/* defaults */
cfg.moisture_low = DEFAULT_MOISTURE_LOW;
cfg.moisture_high = DEFAULT_MOISTURE_HIGH;
cfg.sensor_interval_ms = DEFAULT_SENSOR_INTERVAL_MS;
cfg.pump_manual_ms = DEFAULT_PUMP_MANUAL_MS;
cfg.pump_max_ms = DEFAULT_PUMP_MAX_MS;
cfg.mode = MODE_AUTO; /* default */


sensors_init();
actuators_init();
buttons_init();
watering_init(&cfg);


printf("[SYS] Initialized. Mode = %s\n", cfg.mode == MODE_AUTO ? "AUTO" : "MANUAL");
}


/* print a short status report */
static void report_status(void) {
printf("[STATUS] Mode=%s | Moisture=%d%% | Temp=%.1fC | Pump=%s | LED=%d\n",
cfg.mode==MODE_AUTO?"AUTO":"MANUAL",
sdata.moisture_percent, sdata.temperature_c,
get_pump_state()==PUMP_ON?"ON":"OFF",
get_led_state());
}

static void handle_command(char c) {
switch (c) {
case 'a':
buttons_sim_input('a');
break;
case 'm':
buttons_sim_input('m');
break;
case 'd':
sensors_simulate_dry();
printf("[SIM] Simulate: DRY\n");
break;
case 'w':
sensors_simulate_wet();
printf("[SIM] Simulate: WET (moisture bumped)\n");
break;
case 'q':
printf("[SYS] Quit requested\n");
exit(0);
default:
printf("[INFO] Unknown command '%c'\n", c);
}
}

int main(void) {
init_system();


unsigned long last_sensor_ms = 0;
unsigned long last_report_ms = 0;


printf("[INFO] Commands: a=toggle auto/manual, m=manual water, d=simulate dry, w=simulate wet, q=quit\n");


while (1) {
/* non-blocking check for stdin input using select with timeout */
fd_set rfds;
struct timeval tv;
FD_ZERO(&rfds);
FD_SET(0, &rfds);
tv.tv_sec = 0;
tv.tv_usec = 100000; /* 100 ms */
int sel = select(1, &rfds, NULL, NULL, &tv);
if (sel > 0 && FD_ISSET(0, &rfds)) {
int c = getchar();
if (c != EOF) handle_command((char)c);
}


/* poll buttons (simulated) */
if (buttons_poll_toggle_mode()) {
/* toggle mode */
if (cfg.mode == MODE_AUTO) {
cfg.mode = MODE_MANUAL;
turn_pump_off(); /* ensure pump off when switching to manual */
set_led(LED_NORMAL);
printf("[USER] Switched to MANUAL mode\n");
} else {
cfg.mode = MODE_AUTO;
set_led(LED_NORMAL);
printf("[USER] Switched to AUTO mode\n");
}
}


if (buttons_poll_manual_water()) {
if (cfg.mode == MODE_MANUAL) {
printf("[USER] Manual watering trigger -> pump ON for %d ms\n", cfg.pump_manual_ms);
turn_pump_on();
set_led(LED_WATERING);
/* simple blocking manual watering (for clarity). In a real system use timer/RTOS */
msleep(cfg.pump_manual_ms);
turn_pump_off();
set_led(LED_NORMAL);
} else {
printf("[USER] Manual water ignored: system not in MANUAL mode\n");
}
}
static unsigned long acc_ms = 0;
msleep(50); /* small delay to avoid busy-looping */
acc_ms += 50;
if (acc_ms >= (unsigned long)cfg.sensor_interval_ms) {
sensors_read(&sdata);
acc_ms = 0;
/* In auto mode, perform watering decision */
if (cfg.mode == MODE_AUTO) {
watering_tick(&sdata, &cfg);
}
/* LED logic: if moisture low but not watering, show alert */
if (!watering_is_watering()) {
if (sdata.moisture_percent < cfg.moisture_low) set_led(LED_LOW_MOISTURE_ALERT);
else set_led(LED_NORMAL);
}
}


/* periodic status report every ~sensor interval */
static unsigned long rpt_acc = 0;
rpt_acc += 50;
if (rpt_acc >= cfg.sensor_interval_ms) {
report_status();
rpt_acc = 0;
}
}


return 0;
}

