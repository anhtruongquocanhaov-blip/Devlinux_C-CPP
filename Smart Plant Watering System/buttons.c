#include "buttons.h"
#include <stdio.h>


static int pending_toggle = 0;
static int pending_manual = 0;


void buttons_init(void) {
pending_toggle = 0;
pending_manual = 0;
}


int buttons_poll_toggle_mode(void) {
if (pending_toggle) { pending_toggle = 0; return 1; }
return 0;
}


int buttons_poll_manual_water(void) {
if (pending_manual) { pending_manual = 0; return 1; }
return 0;
}


void buttons_sim_input(char cmd) {
if (cmd == 'a') pending_toggle = 1; /* toggle auto/manual */
if (cmd == 'm') pending_manual = 1; /* manual water */
}