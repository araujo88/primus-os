#include "../include/datetime.h"
#include "../include/string.h"
#include "../include/io.h"

#include "stdint.h"

#define CURRENT_YEAR 2022

#define RTCaddress 0x0070
#define RTCdata 0x0071

// PORT_CMOS_INDEX nmi disable bit
#define NMI_DISABLE_BIT 0x80

// Standard BIOS RTC chip entries
#define CMOS_RTC_SECONDS 0x00
#define CMOS_RTC_SECONDS_ALARM 0x01
#define CMOS_RTC_MINUTES 0x02
#define CMOS_RTC_MINUTES_ALARM 0x03
#define CMOS_RTC_HOURS 0x04
#define CMOS_RTC_HOURS_ALARM 0x05
#define CMOS_RTC_DAY_WEEK 0x06
#define CMOS_RTC_DAY_MONTH 0x07
#define CMOS_RTC_MONTH 0x08
#define CMOS_RTC_YEAR 0x09
#define CMOS_STATUS_A 0x0a
#define CMOS_STATUS_B 0x0b
#define CMOS_STATUS_C 0x0c
#define CMOS_STATUS_D 0x0d
#define CMOS_RESET_CODE 0x0f

uint8_t get_update_in_progress_flag()
{
    output_bytes(RTCaddress, 0x0A);
    return (input_bytes(RTCdata) & 0x80);
}

uint32_t get_RTC_register(uint8_t reg)
{
    output_bytes(RTCaddress, reg);
    return input_bytes(RTCdata);
}

void datetime()
{
    uint32_t seconds;
    uint32_t minutes;
    uint32_t hours;
    uint32_t day;
    uint32_t month;
    uint32_t year;
    char current_time[22] = "";
    uint32_t registerB;

    memset(current_time, 0, strlen(current_time));

start:
    while (get_update_in_progress_flag())
    {
    }

    seconds = CMOS_RTC_SECONDS;
    output_bytes(RTCaddress, seconds);
    seconds = input_bytes(RTCdata);

    minutes = CMOS_RTC_MINUTES;
    output_bytes(RTCaddress, minutes);
    minutes = input_bytes(RTCdata);

    hours = CMOS_RTC_HOURS;
    output_bytes(RTCaddress, hours);
    hours = input_bytes(RTCdata);

    day = CMOS_RTC_DAY_MONTH;
    output_bytes(RTCaddress, day);
    day = input_bytes(RTCdata);

    month = CMOS_RTC_MONTH;
    output_bytes(RTCaddress, month);
    month = input_bytes(RTCdata);

    year = CMOS_RTC_YEAR;
    output_bytes(RTCaddress, year);
    year = input_bytes(RTCdata);

    registerB = get_RTC_register(0x80);

    // Convert BCD to binary values if necessary

    if (!(registerB & 0x04))
    {
        seconds = (seconds & 0x0F) + ((seconds / 16) * 10);
        minutes = (minutes & 0x0F) + ((minutes / 16) * 10);
        hours = ((hours & 0x0F) + (((hours & 0x70) / 16) * 10)) | (hours & 0x80);
        day = (day & 0x0F) + ((day / 16) * 10);
        month = (month & 0x0F) + ((month / 16) * 10);
        year = (year & 0x0F) + ((year / 16) * 10);
    }

    // Convert 12 hour clock to 24 hour clock if necessary

    if (!(registerB & 0x02) && (hours & 0x80))
    {
        hours = ((hours & 0x7F) + 12) % 24;
    }

    // Calculate the full (4-digit) year
    year += (CURRENT_YEAR / 100) * 100;
    if (year < CURRENT_YEAR)
        year += 100;

    if (year != CURRENT_YEAR)
    {
        goto start;
    }

    sprintf(current_time, "%u:%u:%u - %u/%u/%u", hours, minutes, seconds, day, month, year);
    printf("%s\n", current_time);
}