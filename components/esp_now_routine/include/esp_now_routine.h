#ifndef ESP_NOW_ROUTINE_H
# define ESP_NOW_ROUTINE_H

#include "defines.h"

esp_err_t esp_now_install();
bool esp_now_is_master_on(uint8_t *peer_addr);

#endif
