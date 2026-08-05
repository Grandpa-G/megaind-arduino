# SMmegaind

[![megaind-rpi](res/sequent.jpg)](https://www.sequentmicrosystems.com)

![Eight Relays 4A/120V 8-Layer Stackable HAT](res/New_Industrial.jpg)

Arduino library for controlling the [Industrial Automation Stackable Card for Raspberry Pi](https://sequentmicrosystems.com/products/industrial-automation-for-raspberry-pi) from [Sequent Microsystems](https://sequentmicrosystems.com/).

## Install
### Library manager
Go to **Tools**>>**Manage Libraries..** menu and search for *MegaInd* and click install 
### Manual install
To download click <>Code > [Download ZIP](https://github.com/SequentMicrosystems/???-Library/archive/refs/heads/main.zip) button from the main [page](https://github.com/SequentMicrosystems/???-Library), rename the uncompressed folder to "MegaInd" 
and copy to the libraries subdirectory of your sketchbook directory ("This PC > Documents > Arduino > libraries" for a Windows PC
 or "Home > arduino > libraries" on Linux PC). Now launch the Arduino environment. If you open the Sketch > Include Library menu, you should see MegaInd inside. 
 The library will be compiled with sketches that use it. Open an arduino sketch, go to File > Examples > MegaInd > and chose your example to run.

## Usage

### Method 1: Using any Arduino controller
You can use this method with any Arduino card with an I2C port by connecting I2C-SDA, I2C-SCL, +5V and GND, as shown in the following table.
      
| SIGNAL | PIN# |CONN| PIN# | SIGNAL|
|---|---|---|---|---|
| | --1 | O - O | 2-- |  +5V | 
| I2C-SDA | --3| O - O | 4-- |  +5V |
| I2C-SCL |-- 5|O - O| 6--|  GND |
|  |-- 7|O - O| 8--||
| GND |-- 9|O - O|10--||
| |--11|O - O|12--||
| |--13|O - O|14--| GND|
| |--15|O - O|16--||
||--17|O - O|18--||
||--19|O - O|20--|  GND|
||--21|O - O|22--||
||--23|O - O|24--||
|GND |--25|O - O|26--||
||--27|O - O|28--||
||--29|O - O|30--|  GND|
||--31|O - O|32--||
||--33|O - O|34--|  GND|
||--35|O - O|36--||
||--37|O - O|38--||
|GND |--39|O - O|40--||
 
### Method 2: Using the SM Arduino Raspberry Pi Replacement Kit
Sequent Microsystems [Arduino Uno, Nano, Teensy, Feather or ESP32 Raspberry Pi Replacement Kit](https://sequentmicrosystems.com/products/raspberry-pi-replacement-card) is an inexpensive adapter which can be used to control any of our HATs using Uno, Nano, Teensy, Feather or ESP32. Plug the HAT into the 40 pin connector of the adapter and write your Arduino software.


## Examples

More usage examples are available in the [/tests](https://github.com/SequentMicrosystems/megaind-rpi/tree/master/arduino/tests) folder.

All tests assume that one card with no address jumpers (level = 0) is present.

# Documentation

## Function prototypes
 
###	MegaInd(uint8_t stack = 0);
Class constructor
stack - The stack level of the card, choosed with the jumpers


###	bool begin();
Check card presence
Returns true is successful

###	bool isAlive();
Return card existance status
Returns true if card is present

## Diagnose Functions

### double getFwVer()
Return firmware version


### double getRaspVolt()
Read raspberry voltage

return Raspberry PI voltage in volts


## Analog input/output Functions

### double getPowerVolt()
Read power source voltage

return voltage in volts


### int8_t getCpuTemp()
Get the cpu temperature 

return - temperature in deg Celsius


### double get0_10In(uint8_t channel)
Return the selected input 0-10V channel value in volts. 
Make sure the selection jumper is not connectd in order for this measurement to be correct.

channel - selected channel number [1..4]

return - value in volts 


### double getpm10In(uint8_t channel)
Return the selected input +/-10V channel value in volts.
Make sure the selection jumper is connectd in order for this measurement to be correct.

channel - selected channel number [1..4]

return - value in volts 

### int8_t setUinRange(uint8_t channel, uint16_t range)
Set the input range for one voltage input channel

channel - selected channel number [1..4]

range - select range 0= 0..10V; 1 = -10..10V

retrn none

### int8_t getUinRange(uint8_t channel)
Get the input range for one voltage input channel

channel - selected channel number [1..4]

return 0 for 0..10V; 1 for -10..10V

### double int8_t get0_10Out(uint8_t channel)
Get the selected output 0-10V channel value in volts  

channel - selected channel number [1..4]

return - value in volts [0..10]


### int8_t set0_10Out(uint8_t channel, uint16_t value)
Set the selected output 0-10V channel value in volts

channel - selected channel number [1..4]

value - voltage output value in V [0..10]

return - none


### double get4_20In(uint8_t channel)
Return the selected input 4 - 20mA channel value. 

channel - selected channel number [1..4]

return - value in milliamps 


### double get4_20Out(uint8_t channel)
Get the selected output 4 - 20mA channel value.  

channel - selected channel number [1..4]

return - value in milliamps [4..20]


### int8_t set4_20Out(uint8_t channel, uint16_t value)
Set the selected output 4 - 20mA channel value.

channel - selected channel number [1..4]

value - current output value in milliamps [4..20]

return - none


## Digital input/output Functions

### int8_t getOptoCh(uint8_t channel)
Get the state of the optically isolated digital input channel

channel - selected channel number [1..4]

return - value of the inputs [0/1]


### int8_t getOpto()
Get the state of the all optically isolated digital inputs

return - value of the inputs [0..15]


### int16_t getOptoCount(uint8_t channel)
Return the counter value for corresponding optically isolated input.

channel - selected channel number [1..4]

return - counter value [0..65535]


### int8_t rstOptoCount(uint8_t channel)
Reset the counter value for corresponding optically isolated input.

channel - selected channel number [1..4]

return none


### int8_t getOptoRisingCountEnable(uint8_t channel)
Get the rising edge enable counting for corresponding optically isolated input.

channel - selected channel number [1..4]

return 1 - rising edges will be counted; 0 - not


## int8_t setOptoRisingCountEnable(uint8_t channel, uint16_t state)
Set the rising edge enable counting for corresponding optically isolated input.

channel - selected channel number [1..4]

state - 1 = enable; 0 - disable

return none


### int8_t getOptoFallingCountEnable(uint8_t channel)
Get the falling edge enable counting for corresponding optically isolated input.

channel - selected channel number [1..4]

return 1 - falling edges will be counted; 0 - not


### int8_t setOptoFallingCountEnable(uint8_t channel, uint16_t state)
Set the falling edge enable counting for corresponding optically isolated input.

channel - selected channel number [1..4]

state - 1 = enable; 0 - disable

return none


### int8_t setOdPWM(uint8_t channel)
Set the filling factor for Open-Drain outputs

channel - selected channel number [1..4]

value - filling factor in precent [0..100]

return none


### double getOdPWM(uint8_t channel)
Read the filling factor for Open-Drain outputs

channel - selected channel number [1..4]

return - filling factor in precent [0..100]


### int8_t setLed(uint8_t channel, val)
Set one of the 4 LED's on the card.

channel - selected LED number [1..4]

val - 0 = OFF, 1 = ON


### int8_t setLedAll(uint8_t val)
Set all 4 LED's on the card.

val - bitmap of the 4 LED's [0..15]


### int8_t getLed(uint8_t channel)
Get the state of one of the 4 LED's om the card.

channel - selected LED number [1..4]

return 0 if the LED is OFF, 1 if is ON

### int16_t getOptoFrequency(uint8_t channel)
Get the frequency of the signal connected on one of the 4 optically isolated inputs.

channel - selected LED number [1..4]

return frequency expressed in Hz

## Watcdog Timer Functions

### int16_t wdtGetPeriod()
Return the current period of the watchdog timer in seconds


### int8_t wdtSetPeriod(uint16_t val)
Set the period of the watchdog in seconds, val = 65000 disable the watchdog

val - [10..65000]


### int8_t wdtReload()
Reload the watchdog timer with the current period.
The next reload command must occur in no more the "period" time in order to prevent watchdog to re-power the Raspberry.
This command also enables the watchdog if is disabled (power-up disabled).


### int8_t wdtSetDefaultPeriod(uint16_t val)
This function updates the period that will be loaded after Raspberry power is turned off and back on. You must set this period long enough to let Raspberry boot-up and your "watchdog maintaining" script to start.

value - [10...64999] seconds


### int8_t wdtGetDefaultPeriod()
Return the default period 

value - [10...64999] seconds


### int8_t wdtSetOffInterval(uint16_t val)
Set the time interval in seconds for keeping Raspberry power off in case of watchdog timer expire. 

val - [10...4147200] seconds 


### long wdtGetOffInterval()
Return the Off time interval in seconds

return - [10...4147200] seconds 


### int8_t wdtGetResetCount()
Return the numbers of Raspberry re-powers performed by the watchdog 

return - [0..65535]

## RTC Functions

### bool rtcGet(RTCData &rtcData)
Return the RTC date and time as a list

return success/failure

	
###  rtcSet(RTCData rtcData)
Set the RTC date and time

		struct RTCData {
  int year;		last 2 digits of year
  int month;	month 1..12
  int day;		day
int hour;		hour
int minute; 	minutes
int second;		seconds
};

###  double getRTCVolt()
Read battery source voltage

return voltage in volts

## Owire Bus Functions

### int8_t owbScan()
Start scanning for connected sensors

### owbGetSensorNo()
Get the numbers of 18B20 sensors connected on the bus

 return number of connected sensors

### double owbGetTemp(uint8_t sensor)
Read the temperature aquired by one sensor

 sensor - sensor number [1..16]

 return temperature in degree Celsius
 
 ### int8_t owbGetRomCode(uint8_t sensor)
 
 This function has not been implemented

 Read the unic ROM code of one sensor
 
  sensor - sensor number [1..16]

  return ROM code as 8 bytes array
