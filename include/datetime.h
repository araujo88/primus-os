#ifndef _DATETIME_H
#define _DATETIME_H 1

#include "stdint.h"

uint8_t get_update_in_progress_flag();
uint32_t get_RTC_register(uint8_t reg);
void datetime();

#endif