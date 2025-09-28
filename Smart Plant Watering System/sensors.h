#include "types.h"

void sensors_init(void);
void sensors_read(sensor_data_t *out);

void sensors_simulate_dry(void);
void snesors_simulate_wet(void);

#endif /* SENSORS_H*/


