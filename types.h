#ifndef TYPES_H
#define TYPES_H

typedef enum {
    MODE_AUTO = 0,
    MODE_MANUAL = 1
} system_mode_t;

typedef enum {
    PUMP_OFF = 0,
    PUMP_ON = 1
} pump_state_t;

typedef enum {
    LED_NORMAL = 0,
    LED_WATERING = 1,
    LED_LOW_MOISTURE_ALERT = 2,
    LED_ERROR = 3
} led_state_t;

typedef struct {
    int moisture_percent; 
    float temparature_c;
} sensor_data_t;

typedef struct {
    int moisture_low;
    int moisture_high;
    int sensor_interval_ms;
    int pump_manual_ms;
    int pump_max_ms;
    system_mode_t mode;
} system_config_t;

#endif /* TYPES_H */

