#ifndef _TIME_H
#define _TIME_H 1

#include "stdint.h"

uint8_t get_update_in_progress_flag();
uint32_t get_RTC_register(uint8_t reg);
void datetime();
void date();
void clock();
uint32_t current_seconds();
uint32_t current_minutes();
uint32_t current_hour();
uint32_t current_day();
uint32_t current_month();
uint32_t current_year();

#endif