# Hack The Planet Camera Trap extension module firmware
This firmware runs on the extension board placed inside existing camera traps (Bushnells)

# Requirements:
 * Modified Arduino Core for STM32L0
 * vscode or similar compile tool (Arduino IDE may break things)
 * this repository
 * TheThingsNetwork or other similar LoraWAN network server solution

## Secrets
The device LoraWAN comissioning/provisioning is done with a `secrets.h` file. Put the LoRa keys in `secrets.h` file and they will automatically be picked up.

    #define RELAY_NETWORKKEY "..."
    #define RELAY_APPKEY "..."
    #define RELAY_DEVICEADDRESS "..."

## Pulse counting mode
The pulse counting and reporting mode is built to enable interfacing an external piece of electronics, for example a camera trap and detec actions as well as to control an ouput.

Pulse input does the following:
- Increment the field in status packet `pulse_count`
- When `pulse_count` is greater then `pulse_threshold`, send status packet and reset the field. Set to 1 to send data on every pulse or set to 0 to disable.
- The device trigger sending at most often on `pulse_min_interval` in seconds, maximum value 65535.

Pulse output does the following:
- Replicate the input pulse to the output
- When the sending conditions are met, the output pulse pin is turned on for `pulse_on_timeout` seconds.

Configuration variables controlling this:
* `pulse_threshold` - how many pulses must be received to send a status packet
* `pulse_on_timeout` - how long is the pulse output on after threshold reached
* `pulse_min_interval` - how often at maximum can a device send a packet on pulse event

The use-case of above implementation is somewhat universal, however tailored at monitoring SD card activity in camera traps and similar devices and turning on these SD cards if they have WiFi capability.

## Power consumption

### System functions 0x00 - all disabled - sleep only with WDT running
Measured consumption 2uA on average, excludes sending Lora messages.

### System functions 0x01 - GPS periodic enabled
Measured consumption 15uA on average, excludes sending Lora messages
