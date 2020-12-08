#ifndef OV7670_H
# define OV7670_H

#include "defines.h"
#include "driver/i2c.h"

esp_err_t OV7670_init();
esp_err_t OV7670_read();

#endif
