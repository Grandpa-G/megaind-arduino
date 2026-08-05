
/*
def checkStack(stack):
   if stack < 0 or stack > 7:
   raise ValueError('Invalid stack level!')
   return __HW_ADD_BASE + stack


   def checkChannel(ch, limit=4):
   if ch < 1 or ch > limit:
   raise ValueError('Invalid channel number!')
*/

#include "Wire.h"
#include "MegaInd.h"

#define CHECK_STACK(s)  \
	if (s < 0 || s > 7) \
	return -1
#define CHECK_CHANNEL(c) \
	if (c < 0 || c > 4)  \
	return -1

MegaInd::MegaInd(uint8_t stack)
{
	if (stack < 0)
		stack = 0;
	if (stack > 7)
		stack = 7;
	_hwAdd = SLAVE_OWN_ADDRESS_BASE + stack;
	_detected = false;
}

bool MegaInd::begin()
{
	uint8_t value = 0;
	Wire.begin();
	if (0 == readByte(I2C_MEM_REVISION_MAJOR, &value))
	{
		_detected = true;
	}

	return _detected;
}

bool MegaInd::isAlive()
{
	return _detected;
}

int8_t MegaInd::getLed(uint8_t channel)
{
	CHECK_CHANNEL(channel);

	int ret = 0;
	uint8_t val = 0;
	int mask = 1 << (channel + 3);

	ret = readByte(I2C_MEM_RELAY_VAL, &val);

	if (val & mask)
		return 1;

	return 0;
}

bool MegaInd::setLed(uint8_t channel, uint8_t val)
{
	CHECK_CHANNEL(channel);

	bool OK = false;
	byte out = (channel + 4);
	val = val << 4;

	if (val)
	{
		if (OK == writeByte(I2C_MEM_RELAY_SET, out))
			OK = true;
	}
	else
	{
		if (OK == writeByte(I2C_MEM_RELAY_CLR, out))
			OK = true;
	}
	delay(200);
	return OK;
}

bool MegaInd::setLedAll(uint8_t val)
{
	bool OK = false;

	if (val < 0 or val > 15)
		return false;

	val = val << 4;

	for (int channel = 1; channel <= 4; channel++)
	{
		byte out = channel + 4;
		if (val)
		{
			if (OK == writeByte(I2C_MEM_RELAY_SET, out))
				OK = true;
		}
		else
		{
			if (OK == writeByte(I2C_MEM_RELAY_CLR, out))
				OK = true;
		}
		delay(200);
	}
	return OK;
}

bool MegaInd::rtcGet(RTCData &rtcData)
{
	uint8_t buff[100];
	bool OK = false;

	if ((readBytes(I2C_RTC_YEAR_ADD, buff, 6) == 0))
	{
		OK = true;

		rtcData.year = buff[0] + 2000;
		rtcData.month = buff[1];
		rtcData.day = buff[2];
		rtcData.hour = buff[3];
		rtcData.minute = buff[4];
		rtcData.second = buff[5];
	}
	return OK;
}
bool MegaInd::rtcSet(RTCData rtcData)
{
	uint8_t buffer[20];
	bool OK = false;

	uint8_t buff[8];

	buff[0] = rtcData.year;
	buff[1] = rtcData.month;
	buff[2] = rtcData.day;
	buff[3] = rtcData.hour;
	buff[4] = rtcData.minute;
	buff[5] = rtcData.second;
	buff[6] = 0xaa;

	memcpy(buffer, buff, 7 * 2);

	if ((writeBytes(I2C_RTC_SET_YEAR_ADD, buff, 7) == 0))
	{
		OK = true;
	}
	return OK;
}

double MegaInd::getRTCVolt()
{
	int ret = 0;
	uint16_t val = 0;

	ret = readWord(I2C_MEM_DIAG_3V, &val);
	if (ret != 0)
		return -1;

	double volts = (double)val / VOLT_TO_MILIVOLT;
	return volts;
}


double MegaInd::getFwVer()
{
	int ret = 0;
	uint8_t major = 0;
	uint8_t minor = 0;

	ret = readByte(I2C_MEM_REVISION_MAJOR, &major);
	ret = readByte(I2C_MEM_REVISION_MINOR, &minor);
	if (ret != 0)
		return -1;

	return major + minor / 100.0;
}

double MegaInd::getRaspVolt()
{
	int ret = 0;
	uint16_t val = 0;

	ret = readWord(I2C_MEM_DIAG_5V, &val);
	if (ret != 0)
		return -1;

	double volts = (double)val / VOLT_TO_MILIVOLT;
	return volts;
}

#define I2C_MEM_BUTTON 71
bool MegaInd::readButton()
{
	int ret = 0;
	uint8_t val = 0;

	ret = readByte(I2C_MEM_BUTTON, &val);
	if (ret < 0)
		return false;
	if (val & 1)
	{
		return true;
	}
	return false;
}
/*
**********************************************************************
*/
double MegaInd::getPowerVolt()
{
	int ret = 0;
	uint16_t val = 0;

	ret = readWord(I2C_MEM_DIAG_24V, &val);
	if (ret != 0)
		return -1;

	double volts = (double)val / VOLT_TO_MILIVOLT;
	return volts;
}

int8_t MegaInd::getCpuTemp()
{
	int ret = 0;
	uint8_t val = 0;

	ret = readByte(I2C_MEM_DIAG_TEMPERATURE, &val);

	if (ret != 0)
		return -1;

	return val;
}

double MegaInd::get0_10In(uint8_t channel)
{
	int ret = 0;
	uint16_t val = 0;

	CHECK_CHANNEL(channel);

	ret = readWord(U0_10_IN_VAL1_ADD + (2 * (channel - 1)), &val);

	if (ret != 0)
		return -1;

	double volts = (double)val / VOLT_TO_MILIVOLT;
	return volts;
}

double MegaInd::getpm10In(uint8_t channel)
{
	int ret = 0;
	uint16_t val = 0;

	CHECK_CHANNEL(channel);

	ret = readWord(U0_10_IN_VAL1_ADD + (2 * (channel - 1)), &val);

	if (ret != 0)
		return -1;

	double volts = (double)val / VOLT_TO_MILIVOLT - 10;
	return volts;
}
/*
 ***************** opto functions ****************************
 **********************************************************************
 */
int8_t MegaInd::getOptoCh(uint8_t channel)
{
	int ret = 0;
	uint8_t val = 0;

	CHECK_CHANNEL(channel);

	ret = readByte(I2C_MEM_OPTO_IN_VAL, &val);

	if (ret != 0)
		return -1;

	if ((1 << (channel - 1)) & val)
		return 1;
	return 0;
}

int8_t MegaInd::getOpto()
{
	int ret = 0;
	uint8_t val = 0;

	ret = readByte(I2C_MEM_OPTO_IN_VAL, &val);

	if (ret != 0)
		return -1;

	return val;
}

int16_t MegaInd::getOptoCount(uint8_t channel)
{
	int ret = 0;
	uint16_t val = 0;

	CHECK_CHANNEL(channel);

	ret = readWord(I2C_MEM_OPTO_COUNT1 + (2 * (channel - 1)), &val);

	if (ret != 0)
		return -1;

	return val;
}

int8_t MegaInd::rstOptoCount(uint8_t channel)
{
	int ret = 0;

	CHECK_CHANNEL(channel);

	ret = writeByte(I2C_MEM_OPTO_CH_CONT_RESET, channel);

	return ret;
}

int8_t MegaInd::getOptoRisingCountEnable(uint8_t channel)
{
	int ret = 0;
	uint8_t val = 0;

	CHECK_CHANNEL(channel);

	ret = readByte(I2C_MEM_OPTO_RISING_ENABLE, &val);

	if (ret != 0)
		return -1;

	if ((1 << (channel - 1)) & val)
		return 1;
	return 0;
}

int8_t MegaInd::setOptoRisingCountEnable(uint8_t channel, uint16_t state)
{
	uint16_t val = 0;
	int ret = 0;

	CHECK_CHANNEL(channel);

	ret = readWord(I2C_MEM_OPTO_RISING_ENABLE, &val);
	if (state == 0)
		val &= ~(1 << (channel - 1)); // set to 0 - 10V
	else
		val |= 1 << (channel - 1); // set to - 10 to + 10V

	ret = writeWord(I2C_MEM_OPTO_RISING_ENABLE, val);

	if (ret != 0)
		return -1;

	return 0;
}

int8_t MegaInd::getOptoFallingCountEnable(uint8_t channel)
{
	int ret = 0;
	uint8_t val = 0;

	CHECK_CHANNEL(channel);

	ret = readByte(I2C_MEM_OPTO_FALLING_ENABLE, &val);

	if (ret != 0)
		return -1;

	if ((1 << (channel - 1)) & val)
		return 1;
	return 0;
}

int8_t MegaInd::setOptoFallingCountEnable(uint8_t channel, uint16_t state)
{
	uint16_t val = 0;
	int ret = 0;

	CHECK_CHANNEL(channel);

	ret = readWord(I2C_MEM_OPTO_FALLING_ENABLE, &val);
	if (state == 0)
		val &= ~(1 << (channel - 1)); // set to 0 - 10V
	else
		val |= 1 << (channel - 1); // set to - 10 to + 10V

	ret = writeWord(I2C_MEM_OPTO_FALLING_ENABLE, val);

	if (ret != 0)
		return -1;

	return 0;
}

int16_t MegaInd::getOptoFrequency(uint8_t channel)
{
	int ret = 0;
	uint16_t val = 0;

	CHECK_CHANNEL(channel);

	ret = readWord(I2C_MEM_OPTO_FREQ1 + (2 * (channel - 1)), &val);

	if (ret != 0)
		return -1;

	return val;
}

/*
 ***************** PWM Drain output functions ****************************
 **********************************************************************
 */

double MegaInd::getOdPWM(uint8_t channel)
{
	int ret = 0;
	uint16_t val = 0;

	CHECK_CHANNEL(channel);

	ret = readWord(I2C_MEM_OD_PWM1 + (2 * (channel - 1)), &val);

	if (ret != 0)
		return -1;

	return val / 100.0;
}

int8_t MegaInd::setOdPWM(uint8_t channel, int16_t value)
{
	int ret = 0;

	CHECK_CHANNEL(channel);

	if (value < 0 || value > 100) //  # prcent
		return -1;

	ret = writeWord(I2C_MEM_OD_PWM1 + (2 * (channel - 1)), value * 100);
	if (ret != 0)
		return -1;

	return 0;
}

int8_t MegaInd::getOd(uint8_t channel)
{
	int ret = 0;
	uint8_t val = 0;

	CHECK_CHANNEL(channel);

	int mask = 1 << (channel - 1);

	ret = readByte(I2C_MEM_RELAY_VAL, &val);

	if (val & mask)
		return 1;

	return 0;
}

int8_t MegaInd::setOd(uint8_t channel, int8_t val)
{
	int ret = 0;

	CHECK_CHANNEL(channel);

	if (val != 0)
		ret = writeByte(I2C_MEM_RELAY_SET, channel);
	else
		ret = writeByte(I2C_MEM_RELAY_CLR, channel);
	delay(100);
	if (ret != 0)
		return -1;

	return 0;
}

/*
 ***************** one wire functions ****************************
 **********************************************************************
 */

int8_t MegaInd::owbScan()
{
	int ret = 0;
	uint8_t val = 0xaa;

	ret = writeByte(I2C_MEM_1WB_START_SEARCH, val);

	if (ret != 0)
		return -1;

	return 0;
}

int8_t MegaInd::owbGetSensorNo()
{
	int ret = 0;
	uint8_t val = 0;

	ret = readByte(I2C_MEM_1WB_DEV, &val);

	if (ret != 0)
		return -1;

	return val;
}

double MegaInd::owbGetTemp(uint8_t sensor)
{
	int ret = 0;
	uint16_t val = 0;

	if (sensor < 1 || sensor > 16)
		return -1;

	ret = readWord(I2C_MEM_1WB_T1 + OWB_TEMP_SIZE_B * (sensor - 1), &val);
	if (ret != 0)
		return -1;

	double volts = (double)val / VOLT_TO_MILIVOLT;
	return val / 100.0;
}
/*		NOT IMPLEMENTED *************************
int8_t MegaInd::owbGetRomCode(uint8_t sensor, byte* buff)
{
	uint8_t buff[100];
	int ret = 0;

	ret = writeByte(I2C_MEM_1WB_ROM_CODE_IDX, sensor - 1);
	if (ret != 0)
		return -1;

	ret = readBytes(I2C_MEM_1WB_ROM_CODE, buff, 8);
	if (ret != 0)
		return -1;

	return 0;
}
*/
/*
 ***************** 0-10 voltage functions ****************************
 **********************************************************************
 */
double MegaInd::get0_10Out(uint8_t channel)
{
	int ret = 0;
	uint16_t val = 0;

	CHECK_CHANNEL(channel);

	ret = readWord(U_0_10_OUT_VAL1_ADD + (2 * (channel - 1)), &val);

	if (ret != 0)
		return -1;

	double volts = (double)val / VOLT_TO_MILIVOLT;
	return volts;
}

int8_t MegaInd::set0_10Out(uint8_t channel, int16_t voltage)
{
	CHECK_CHANNEL(channel);

	if (voltage < -10 || voltage > 10)
		return -1;

	uint16_t value = int(voltage * 1000);
	int ret = 0;
	ret = writeWord(U_0_10_OUT_VAL1_ADD + (2 * (channel - 1)), value);

	if (ret != 0)
		return -1;

	return 0;
}

int8_t MegaInd::MegaInd::getUinRange(uint8_t channel)
{
	int ret = 0;
	uint8_t val = 0;

	CHECK_CHANNEL(channel);

	ret = readByte(I2C_MEM_PM_IN_SWITCH, &val);

	if (ret != 0)
		return -1;

	if ((1 << (channel - 1)) & val)
		return 1;
	return 0;
}

int8_t MegaInd::setUinRange(uint8_t channel, uint16_t range)
{
	uint16_t val = 0;
	int ret = 0;

	CHECK_CHANNEL(channel);

	ret = readWord(I2C_MEM_PM_IN_SWITCH, &val);
	if (range == 0)
		val &= ~(1 << (channel - 1)); // set to 0 - 10V
	else
		val |= 1 << (channel - 1); // set to - 10 to + 10V

	ret = writeWord(I2C_MEM_PM_IN_SWITCH, val);

	if (ret != 0)
		return -1;

	return 0;
}

double MegaInd::get4_20In(uint8_t channel)
{
	int ret = 0;
	uint16_t val = 0;

	CHECK_CHANNEL(channel);

	ret = readWord(I4_20_IN_VAL1_ADD + (2 * (channel - 1)), &val);

	if (ret != 0)
		return -1;

	double volts = (double)val / MILLIAMP_TO_MICROAMP;
	return volts;
}

double MegaInd::get4_20Out(uint8_t channel)
{
	int ret = 0;
	uint16_t val = 0;

	CHECK_CHANNEL(channel);

	ret = readWord(I4_20_OUT_VAL1_ADD + (2 * (channel - 1)), &val);

	if (ret != 0)
		return -1;

	double volts = (double)val / MILLIAMP_TO_MICROAMP;
	return volts;
}

int8_t MegaInd::set4_20Out(uint8_t channel, int16_t voltage)
{
	if (voltage < 0 || voltage > 30)
		return -1;

	CHECK_CHANNEL(channel);

	uint16_t value = int(voltage * MILLIAMP_TO_MICROAMP);
	int ret = 0;
	ret = writeWord(I4_20_OUT_VAL1_ADD + (2 * (channel - 1)), value);

	if (ret != 0)
		return -1;

	return 0;
}

/*
 ***************** watch dog functions ****************************
 **********************************************************************
 */
int16_t MegaInd::wdtGetPeriod()
{
	int ret = 0;
	uint16_t val = 0;

	ret = readWord(I2C_MEM_WDT_INTERVAL_GET_ADD, &val);
	if (ret != 0)
		return -1;

	return val;
}

int8_t MegaInd::wdtSetPeriod(uint16_t value)
{
	if (value < 10 || value > 65000)
		return -1;

	int ret = 0;
	ret = writeWord(I2C_MEM_WDT_INTERVAL_SET_ADD, value);
	delay(100);
	if (ret != 0)
		return -1;

	return 0;
}

int8_t MegaInd::wdtReload()
{
	int ret = 0;
	ret = writeWord(I2C_MEM_WDT_RESET_ADD, RELOAD_KEY);
	delay(100);

	if (ret != 0)
		return -1;

	return 0;
}

int8_t MegaInd::wdtSetDefaultPeriod(uint16_t value)
{
	if (value < 10 || value > 64999)
		return -1;

	int ret = 0;
	ret = writeWord(I2C_MEM_WDT_INIT_INTERVAL_SET_ADD, value);
	delay(100);
	if (ret != 0)
		return -1;

	return 0;
}

int8_t MegaInd::wdtGetDefaultPeriod()
{
	int ret = 0;
	uint16_t val = 0;

	ret = readWord(I2C_MEM_WDT_INIT_INTERVAL_GET_ADD, &val);
	if (ret != 0)
		return -1;

	return val;
}

int8_t MegaInd::wdtSetOffInterval(uint32_t value)
{
	int ret = 0;

	if (value < 10 || value > WDT_MAX_POWER_OFF_INTERVAL)
		return -1;

	byte buff[] = {0, 0, 0, 0};
	buff[0] = 0xff & value;
	buff[1] = 0xff & (value >> 8);
	buff[2] = 0xff & (value >> 16);
	buff[3] = 0xff & (value >> 24);

	ret = writeBytes(I2C_MEM_WDT_POWER_OFF_INTERVAL_SET_ADD, buff, 4);
	if (ret != 0)
		return -1;

	return 0;
}

long MegaInd::wdtGetOffInterval()
{
	int ret = 0;
	uint8_t buff[8];
	uint32_t value = 0;

	ret = readBytes(I2C_MEM_WDT_POWER_OFF_INTERVAL_GET_ADD, buff, 4);

	if (ret != 0)
		return -1;

	value = buff[0] + (buff[1] << 8) + (buff[2] << 16) + (buff[3] << 24);

	return value;
}

int16_t MegaInd::wdtGetResetCount()
{
	int ret = 0;
	uint16_t val = 0;

	ret = readWord(I2C_MEM_WDT_RESET_COUNT_ADD, &val);
	if (ret != 0)
		return -1;

	return val;
}

/*
 ***************** BAS_I2C access functions ****************************
 **********************************************************************
 */
int MegaInd::writeByte(uint8_t add, uint8_t value)
{
	// Wire.begin();
	Wire.beginTransmission(_hwAdd);
	Wire.write(add);
	Wire.write(value);
	return Wire.endTransmission();
}

int MegaInd::writeWord(uint8_t add, uint16_t value)
{
	uint8_t buff[2];

	memcpy(buff, &value, 2);
	// Wire.begin();
	Wire.beginTransmission(_hwAdd);
	Wire.write(add);
	Wire.write(buff[0]);
	Wire.write(buff[1]);
	return Wire.endTransmission();
}
int MegaInd::writeDWord(uint8_t add, uint32_t value)
{
	uint8_t buff[4];
	int i = 0;

	memcpy(buff, &value, 4);
	// Wire.begin();
	Wire.beginTransmission(_hwAdd);
	Wire.write(add);
	for (i = 0; i < 4; i++)
	{
		Wire.write(buff[i]);
	}
	return Wire.endTransmission();
}
int MegaInd::readByte(uint8_t add, uint8_t *value)
{
	if (0 == value)
	{
		return -1;
	}
	// Wire.begin();
	Wire.beginTransmission(_hwAdd);
	Wire.write(add);
	if (Wire.endTransmission() != 0)
	{
		return -1;
	}
	Wire.requestFrom(_hwAdd, (uint8_t)1);
	if (1 <= Wire.available())
	{
		*value = Wire.read();
	}
	else
	{
		return -1;
	}
	return 0;
}
int MegaInd::readWord(uint8_t add, uint16_t *value)
{
	uint8_t buff[2];

	if (0 == value)
	{
		return -1;
	}
	// Wire.begin();
	Wire.beginTransmission(_hwAdd);
	Wire.write(add);
	if (Wire.endTransmission() != 0)
	{
		return -1;
	}
	Wire.requestFrom(_hwAdd, (uint8_t)2);
	if (2 <= Wire.available())
	{
		buff[0] = Wire.read();
		buff[1] = Wire.read();
	}
	else
	{
		return -1;
	}
	memcpy(value, buff, 2);
	return 0;
}

int MegaInd::readDWord(uint8_t add, uint32_t *value)
{
	uint8_t buff[4];
	int i = 0;

	if (0 == value)
	{
		return -2;
	}
	// Wire.begin();
	Wire.beginTransmission(_hwAdd);
	Wire.write(add);
	if (Wire.endTransmission() != 0)
	{
		return -4;
	}
	Wire.requestFrom(_hwAdd, (uint8_t)2);
	if (4 <= Wire.available())
	{
		for (i = 0; i < 4; i++)
		{
			buff[i] = Wire.read();
		}
	}
	else
	{
		return -3;
	}
	memcpy(value, buff, 4);
	return 0;
}

int MegaInd::readSignedDWord(uint8_t add, int32_t *value)
{
	uint8_t buff[4];
	int i = 0;

	if (0 == value)
	{
		return -1;
	}
	// Wire.begin();
	Wire.beginTransmission(_hwAdd);
	Wire.write(add);
	if (Wire.endTransmission() != 0)
	{
		return -1;
	}
	Wire.requestFrom(_hwAdd, (uint8_t)2);
	if (4 <= Wire.available())
	{
		for (i = 0; i < 4; i++)
		{
			buff[i] = Wire.read();
		}
	}
	else
	{
		return -1;
	}
	memcpy(value, buff, 4);
	return 0;
}

int MegaInd::readBytes(uint8_t add, uint8_t *value, uint16_t bytesRequested)
{
	uint8_t buff[100];
	int i = 0;

	if (0 == value)
	{
		return -1;
	}
	// Wire.begin();
	Wire.beginTransmission(_hwAdd);
	Wire.write(add);
	if (Wire.endTransmission() != 0)
	{
		return -1;
	}
	Wire.requestFrom(_hwAdd, (uint8_t)bytesRequested);

	if (bytesRequested <= Wire.available())
	{
		for (i = 0; i < bytesRequested; i++)
		{
			buff[i] = Wire.read();
		}
	}
	else
	{
		Serial.println("ERR");
		return -1;
	}
	memcpy(value, buff, bytesRequested);

	return 0;
}

int MegaInd::writeBytes(uint8_t add, const uint8_t value[], uint16_t bytesRequested)
{
	uint8_t buff[100];
	int i = 0;

	memcpy(buff, value, bytesRequested);

	// Wire.begin();
	Wire.beginTransmission(_hwAdd);
	Wire.write(add);
	for (i = 0; i < bytesRequested; i++)
		Wire.write(buff[i]);
	Wire.endTransmission();
	delay(100);
	return 0;
}
