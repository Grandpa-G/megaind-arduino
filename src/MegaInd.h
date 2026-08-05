/*!
 * @file MegaInd.h
 *
 * Designed specifically to work with the Sequent Microsysatems
 * Building Automation 8-Layer Stackable HAT for Raspberry Pi
 *
 * ----> https://sequentmicrosystems.com/products/building-automation-8-layer-stackable-hat-v4-for-raspberry-pi
 *
 *   This card use I2C to communicate.
 *
 *   Written by Alexandru Burcea for Sequent Microsystems
 *
 *   Software License Agreement (BSD License)
 *
 *  Copyright (c) 2023, Sequent Microsystems
 *
 */
#include <Arduino.h>

#include "megaTypes.h"

#ifndef __MegaInd__
#define __MegaInd__

#define ADC_RAW_VAL_SIZE 2
#define DAC_MV_VAL_SIZE 2
#define VOLT_TO_MILIVOLT 1000
#define OPTO_CH_NO 8
#define GPIO_CH_NO 4
#define COUNTER_SIZE 4
#define DRY_CONTACT_COUNT 8
#define DRY_CONTACT_CONTOR_SIZE 4

#define RETRY_TIMES 10
#define CALIBRATION_KEY 0xaa
#define RESET_CALIBRATION_KEY 0x55
#define WDT_RESET_SIGNATURE 0xCA
#define WDT_MAX_OFF_INTERVAL_S 4147200 // 48 days
#define UI_VAL_SIZE 2
#define CAN_FIFO_SIZE 10
#define OWB_SENS_CNT 16
#define OWB_TEMP_SIZE_B 2

#define OWM_ROM_CODE_SIZE_B 8

#define ERROR -1
#define NOERROR 0
#define FAIL -1
#define ARG_CNT_ERR -3
#define COMM_ERR -4

#define ON true
#define OFF false

#define CHANNEL_NR_MIN 1
#define RELAY_CH_NR_MAX 4

#define OPTO_CH_NR_MAX 4
#define OD_CH_NR_MAX 4
#define I_OUT_CH_NR_MAX 4
#define U_OUT_CH_NR_MAX 4
#define U_IN_CH_NR_MAX 4
#define I_IN_CH_NR_MAX 4
#define LED_CH_NR_MAX 4

#define OD_PWM_VAL_MAX 10000

// # watchdog functions
#define WDT_MAX_POWER_OFF_INTERVAL 4147200
#define RELOAD_KEY 202

// 4 - 20 mA in/out functions
#define I4_20_IN_VAL1_ADD 44
#define I4_20_OUT_VAL1_ADD 12
#define MILLIAMP_TO_MICROAMP 1000.0

enum
{
	I2C_MEM_RELAY_VAL = 0, // reserved 4 bits for open-drain and 4 bits for leds
	I2C_MEM_RELAY_SET,
	I2C_MEM_RELAY_CLR,
	I2C_MEM_OPTO_IN_VAL,

	I2C_MEM_U0_10_OUT_VAL1,
	I2C_MEM_U0_10_OUT_VAL2 = I2C_MEM_U0_10_OUT_VAL1 + UI_VAL_SIZE,
	I2C_MEM_U0_10_OUT_VAL3 = I2C_MEM_U0_10_OUT_VAL2 + UI_VAL_SIZE,
	I2C_MEM_U0_10_OUT_VAL4 = I2C_MEM_U0_10_OUT_VAL3 + UI_VAL_SIZE,
	I2C_MEM_I4_20_OUT_VAL1 = I2C_MEM_U0_10_OUT_VAL4 + UI_VAL_SIZE,
	I2C_MEM_I4_20_OUT_VAL2 = I2C_MEM_I4_20_OUT_VAL1 + UI_VAL_SIZE,
	I2C_MEM_I4_20_OUT_VAL3 = I2C_MEM_I4_20_OUT_VAL2 + UI_VAL_SIZE,
	I2C_MEM_I4_20_OUT_VAL4 = I2C_MEM_I4_20_OUT_VAL3 + UI_VAL_SIZE,
	I2C_MEM_OD_PWM1 = I2C_MEM_I4_20_OUT_VAL4 + UI_VAL_SIZE,
	I2C_MEM_OD_PWM2 = I2C_MEM_OD_PWM1 + UI_VAL_SIZE,
	I2C_MEM_OD_PWM3 = I2C_MEM_OD_PWM2 + UI_VAL_SIZE,
	I2C_MEM_OD_PWM4 = I2C_MEM_OD_PWM3 + UI_VAL_SIZE,

	I2C_MEM_U0_10_IN_VAL1 = I2C_MEM_OD_PWM4 + UI_VAL_SIZE,
	I2C_MEM_U0_10_IN_VAL2 = I2C_MEM_U0_10_IN_VAL1 + UI_VAL_SIZE,
	I2C_MEM_U0_10_IN_VAL3 = I2C_MEM_U0_10_IN_VAL2 + UI_VAL_SIZE,
	I2C_MEM_U0_10_IN_VAL4 = I2C_MEM_U0_10_IN_VAL3 + UI_VAL_SIZE,
	I2C_MEM_U_PM_10_IN_VAL1 = I2C_MEM_U0_10_IN_VAL4 + UI_VAL_SIZE,
	I2C_MEM_U_PM_10_IN_VAL2 = I2C_MEM_U_PM_10_IN_VAL1 + UI_VAL_SIZE,
	I2C_MEM_U_PM_10_IN_VAL3 = I2C_MEM_U_PM_10_IN_VAL2 + UI_VAL_SIZE,
	I2C_MEM_U_PM_10_IN_VAL4 = I2C_MEM_U_PM_10_IN_VAL3 + UI_VAL_SIZE,
	I2C_MEM_I4_20_IN_VAL1 = I2C_MEM_U_PM_10_IN_VAL4 + UI_VAL_SIZE,
	I2C_MEM_I4_20_IN_VAL2 = I2C_MEM_I4_20_IN_VAL1 + UI_VAL_SIZE,
	I2C_MEM_I4_20_IN_VAL3 = I2C_MEM_I4_20_IN_VAL2 + UI_VAL_SIZE,
	I2C_MEM_I4_20_IN_VAL4 = I2C_MEM_I4_20_IN_VAL3 + UI_VAL_SIZE,

	I2C_MEM_I4_20_OUT_VALID1 = I2C_MEM_I4_20_IN_VAL4 + UI_VAL_SIZE,
	I2C_MEM_I4_20_OUT_VALID2 = I2C_MEM_I4_20_OUT_VALID1 + UI_VAL_SIZE,
	I2C_MEM_I4_20_OUT_VALID3 = I2C_MEM_I4_20_OUT_VALID2 + UI_VAL_SIZE,
	I2C_MEM_I4_20_OUT_VALID4 = I2C_MEM_I4_20_OUT_VALID3 + UI_VAL_SIZE,
	I2C_MEM_CALIB_VALUE = 60,
	I2C_MEM_CALIB_CHANNEL = I2C_MEM_CALIB_VALUE + 2, // 0-10V out [1,4]; 0-10V in [5, 12]; R 1K in [13, 20]; R 10K in [21, 28]
	I2C_MEM_CALIB_KEY,								 // set calib point 0xaa; reset calibration on the channel 0x55
	I2C_MEM_CALIB_STATUS,
	I2C_MODBUS_SETINGS_ADD = 65,
	I2C_NBS1,
	I2C_MBS2,
	I2C_MBS3,
	I2C_MODBUS_ID_OFFSET_ADD,
	I2C_RTC_YEAR_ADD,
	I2C_RTC_MONTH_ADD,
	I2C_RTC_DAY_ADD,
	I2C_RTC_HOUR_ADD,
	I2C_RTC_MINUTE_ADD,
	I2C_RTC_SECOND_ADD,
	I2C_RTC_SET_YEAR_ADD,
	I2C_RTC_SET_MONTH_ADD,
	I2C_RTC_SET_DAY_ADD,
	I2C_RTC_SET_HOUR_ADD,
	I2C_RTC_SET_MINUTE_ADD,
	I2C_RTC_SET_SECOND_ADD,
	I2C_RTC_CMD_ADD,
	I2C_MEM_WDT_RESET_ADD,
	I2C_MEM_WDT_INTERVAL_SET_ADD,
	I2C_MEM_WDT_INTERVAL_GET_ADD = I2C_MEM_WDT_INTERVAL_SET_ADD + 2,
	I2C_MEM_WDT_INIT_INTERVAL_SET_ADD = I2C_MEM_WDT_INTERVAL_GET_ADD + 2,
	I2C_MEM_WDT_INIT_INTERVAL_GET_ADD = I2C_MEM_WDT_INIT_INTERVAL_SET_ADD + 2,
	I2C_MEM_WDT_RESET_COUNT_ADD = I2C_MEM_WDT_INIT_INTERVAL_GET_ADD + 2,
	I2C_MEM_WDT_CLEAR_RESET_COUNT_ADD = I2C_MEM_WDT_RESET_COUNT_ADD + 2,
	I2C_MEM_WDT_POWER_OFF_INTERVAL_SET_ADD,
	I2C_MEM_WDT_POWER_OFF_INTERVAL_GET_ADD = I2C_MEM_WDT_POWER_OFF_INTERVAL_SET_ADD + 4,
	I2C_MEM_OPTO_RISING_ENABLE = I2C_MEM_WDT_POWER_OFF_INTERVAL_GET_ADD + 4,
	I2C_MEM_OPTO_FALLING_ENABLE,
	I2C_MEM_OPTO_CH_CONT_RESET,
	I2C_MEM_OPTO_COUNT1,
	I2C_MEM_OPTO_COUNT2 = I2C_MEM_OPTO_COUNT1 + 2,
	I2C_MEM_OPTO_COUNT3 = I2C_MEM_OPTO_COUNT2 + 2,
	I2C_MEM_OPTO_COUNT4 = I2C_MEM_OPTO_COUNT3 + 2,
	I2C_MEM_DIAG_TEMPERATURE = 0x72,
	I2C_MEM_DIAG_24V,
	I2C_MEM_DIAG_24V_1,
	I2C_MEM_DIAG_5V,
	I2C_MEM_DIAG_5V_1,
	I2C_MEM_RPI_RTS_EN, // CAN_REC_MPS_MEM,

	I2C_MEM_REVISION_MAJOR = 0x78,
	I2C_MEM_REVISION_MINOR,
	I2C_MEM_PM_IN_SW,
#ifdef CAN
	I2C_MEM_CAN_TX_FIFO_LEVEL,
	I2C_MEM_CAN_TX_FIFO,
	I2C_MEM_CAN_RX_FIFO_LEVEL = I2C_MEM_CAN_TX_FIFO + CAN_FIFO_SIZE,
	I2C_MEM_CAN_RX_FIFO,
	I2C_MEM_CAN_RX_FIFO_MARK = I2C_MEM_CAN_RX_FIFO + CAN_FIFO_SIZE,
#endif
	I2C_MEM_DIAG_3V = 145,
	I2C_MEM_DIAG_3V_1,
	I2C_MEM_1WB_DEV,
	I2C_MEM_1WB_TEMP_ALL,
	I2C_MEM_1WB_ROM_CODE_IDX = I2C_MEM_1WB_TEMP_ALL + OWB_TEMP_SIZE_B,
	I2C_MEM_1WB_ROM_CODE, // rom code 64 bits
	I2C_MEM_1WB_ROM_CODE_END = I2C_MEM_1WB_ROM_CODE + 7,
	I2C_MEM_OPTO_FREQ1,
	I2C_MEM_OPTO_FREQ2 = I2C_MEM_OPTO_FREQ1 + UI_VAL_SIZE,
	I2C_MEM_OPTO_FREQ3 = I2C_MEM_OPTO_FREQ2 + UI_VAL_SIZE,
	I2C_MEM_OPTO_FREQ4 = I2C_MEM_OPTO_FREQ3 + UI_VAL_SIZE,

	I2C_MEM_CPU_RESET = 0xaa,
	I2C_MEM_HSI_LO,
	I2C_MEM_HSI_HI,
	I2C_MEM_1WB_START_SEARCH,
	I2C_MEM_1WB_T1,
	I2C_MEM_1WB_T16 = I2C_MEM_1WB_T1 + OWB_SENS_CNT * OWB_TEMP_SIZE_B,
	I2C_MEM_OD1_FREQ = I2C_MEM_1WB_T16 + UI_VAL_SIZE,
	I2C_MEM_OD2_FREQ = I2C_MEM_OD1_FREQ + UI_VAL_SIZE,
	I2C_MEM_OD3_FREQ = I2C_MEM_OD2_FREQ + UI_VAL_SIZE,
	I2C_MEM_SIZE = 255
	// SLAVE_BUFF_SIZE = 255
};

#define SLAVE_OWN_ADDRESS_BASE 0x50

// # 0 to 10 volts input and output functions
#define U0_10_IN_VAL1_ADD 28
#define U_PM_10_IN_VAL1_ADD 36
#define U_0_10_OUT_VAL1_ADD 4
#define I2C_MEM_PM_IN_SWITCH 122

/*
typedef uint8_t u8;
typedef int8_t s8;
//typedef uint16_t u16;
typedef int16_t s16;
typedef uint32_t u32;
typedef int32_t s32;
*/
/*!
 * @brief MegaInd class
 */
class MegaInd
{
public:
	/*!
	 * @brief Class constructor.
	 */
	MegaInd(uint8_t stack = 0);

	/*!
	 * @brief Check card presence
	 * @return Returns true is successful
	 */
	bool begin();

	/*!
	 * @brief Return card existance status
	 * @return Returns true if card is present
	 */
	bool isAlive();

	bool readButton();

	bool setLed(uint8_t channel, uint8_t val);

	int8_t getLed(uint8_t channel);
	bool setLedAll(uint8_t val);

	bool rtcGet(RTCData &rtcData);

	bool rtcSet(RTCData rtcData);
	double getRTCVolt();

	double getFwVer();
	double getRaspVolt();
	double getPowerVolt();
	int8_t getCpuTemp();
	double get0_10In(uint8_t channel);
	double getpm10In(uint8_t channel);

	int8_t getOptoCh(uint8_t channel);
	int8_t getOpto();
	int16_t getOptoCount(uint8_t channel);
	int8_t rstOptoCount(uint8_t channel);
	int8_t getOptoRisingCountEnable(uint8_t channel);
	int8_t setOptoRisingCountEnable(uint8_t channel, uint16_t state);
	int8_t getOptoFallingCountEnable(uint8_t channel);
	int8_t setOptoFallingCountEnable(uint8_t channel, uint16_t state);

	double getOdPWM(uint8_t channel);
	int8_t setOdPWM(uint8_t channel, int16_t value);
	int16_t getOptoFrequency(uint8_t channel);
	int8_t getOd(uint8_t channel);
	int8_t setOd(uint8_t channel, int8_t val);

	double get0_10Out(uint8_t channel);
	int8_t set0_10Out(uint8_t channel, int16_t voltage);

	int8_t getUinRange(uint8_t channel);
	int8_t setUinRange(uint8_t channel, uint16_t range);

	double get4_20In(uint8_t channel);
	double get4_20Out(uint8_t channel);
	int8_t set4_20Out(uint8_t channel, int16_t voltage);

	int8_t owbScan();
	int8_t owbGetSensorNo();
	double owbGetTemp(uint8_t sensor);
//	int8_t owbGetRomCode(uint8_t sensor);

	int16_t wdtGetPeriod();
	int8_t wdtSetPeriod(uint16_t value);
	int8_t wdtReload();
	int8_t wdtSetDefaultPeriod(uint16_t value);
	int8_t wdtGetDefaultPeriod();
	int8_t wdtSetOffInterval(uint32_t value);
	long MegaInd::wdtGetOffInterval();
	int16_t wdtGetResetCount();

private:
	uint8_t _hwAdd;
	bool _detected;
	int OK;
	int writeBuff(uint8_t add, uint8_t *buff, uint8_t size);
	int readBuff(uint8_t add, uint8_t *buff, uint8_t size);
	int writeByte(uint8_t add, uint8_t value);
	int writeWord(uint8_t add, uint16_t value);
	int writeDWord(uint8_t add, uint32_t value);
	int readByte(uint8_t add, uint8_t *value);
	int readWord(uint8_t add, uint16_t *value);
	int readDWord(uint8_t add, uint32_t *value);
	int readSignedDWord(uint8_t add, int32_t *value);
	int readBytes(uint8_t add, uint8_t *value, uint16_t bytesRequested);
	int writeBytes(uint8_t add, const uint8_t value[], uint16_t bytesRequested);

	int i2cSetup(int addr);
	int i2cMem8Read(int dev, int add, uint8_t *buff, int size);
	int i2cMem8Write(int dev, int add, uint8_t *buff, int size);
};

#endif //__MegaInd__
