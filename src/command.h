#ifndef COMMAND_H_
#define COMMAND_H_

#include <EEPROM.h>
#include <STM32L0.h>

#include "Arduino.h"
#include "lorawan.h"
#include "settings.h"

static uint8_t command_packet_port = 99;
uint8_t command_get_packet_port(void);
void command_receive(uint8_t command);
extern boolean settings_send_flag;

#endif