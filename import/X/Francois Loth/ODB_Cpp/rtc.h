
#ifndef TM_RTC_H
#define TM_RTC_H 120
/**
 * Library dependencies
 * - STM32F4xx
 * - STM32F4xx RCC
 * - STM32F4xx RTC
 * - STM32F4xx PWR
 * - STM32F4xx EXTI
 * - MISC
 * - defines.h
 */
/**
 * Includes
 */
#include "stm32f4xx.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_rtc.h"
#include "stm32f4xx_pwr.h"
#include "stm32f4xx_exti.h"
#include "misc.h"


/* RTC clock is: f_clk = RTCCLK(LSI or LSE) / ((RTC_SYNC_PREDIV + 1) * (RTC_ASYNC_PREDIV + 1)) */
/* Sync pre division for clock */
#ifndef RTC_SYNC_PREDIV
#define RTC_SYNC_PREDIV					0x3FF
#endif
/* Async pre division for clock */
#ifndef RTC_ASYNC_PREDIV
#define RTC_ASYNC_PREDIV				0x1F
#endif
/* NVIC global Priority set */
#ifndef RTC_PRIORITY
#define RTC_PRIORITY					0x04
#endif
/* Sub priority for wakeup trigger */
#ifndef RTC_WAKEUP_SUBPRIORITY
#define RTC_WAKEUP_SUBPRIORITY			0x00
#endif
/* Sub priority for alarm trigger */
#ifndef RTC_ALARM_SUBPRIORITY
#define RTC_ALARM_SUBPRIORITY			0x01
#endif

/* Internal status registers for RTC */
#define RTC_STATUS_REG      			RTC_BKP_DR0  // Status Register
#define RTC_STATUS_INIT_OK  			0x1234       // RTC initialised
#define RTC_STATUS_TIME_OK  			0x4321       // RTC time ok
#define	RTC_STATUS_ZERO					0x0000

/* Internal RTC defines */
#define TM_RTC_LEAP_YEAR(year) 			(((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0))
#define TM_RTC_DAYS_IN_YEAR(x)			TM_RTC_LEAP_YEAR(x) ? 366 : 365
#define TM_RTC_OFFSET_YEAR				1970
#define TM_RTC_SECONDS_PER_DAY			86400
#define TM_RTC_SECONDS_PER_HOUR			3600
#define TM_RTC_SECONDS_PER_MINUTE		60

/**
 * Struct for date/time
 *
 * Parameters:
 * 	- uint8_t seconds:
 * 		Seconds parameter, from 00 to 59
 * 	- uint16_t subseconds:
 * 		Subsecond downcounter. When it reaches zero, it's reload value is the same as
 *		RTC_SYNC_PREDIV, so in our case 0x3FF = 1023, 1024 steps in one second
 * 	- uint8_t minutes:
 * 		Minutes parameter, from 00 to 59
 * 	- uint8_t hours:
 * 		Hours parameter, 24Hour mode, 00 to 23
 * 	- uint8_t day:
 * 		Day in a week, from 1 to 7
 * 	- uint8_t date:
 * 		Date in a month, 1 to 31
 * 	- uint8_t month:
 * 		Month in a year, 1 to 12
 * 	- uint8_t year:
 * 		Year parameter, 00 to 99, 00 is 2000 and 99 is 2099
 *	- uint32_t unix:
 *		Seconds from 	01.01.1970 00:00:00
 */
typedef struct {
	uint8_t seconds;
	uint16_t subseconds;
	uint8_t minutes;
	uint8_t hours;
	uint8_t day;
	uint8_t date;
	uint8_t month;
	uint8_t year;
	uint32_t unix;
} TM_RTC_Time_t;

/**
 * Set format of date and time
 *
 * Parameters:
 * - TM_RTC_Format_BIN:
 * 		Binary format
 * - TM_RTC_Format_BCD:
 * 		BCD format
 */
typedef enum {
	TM_RTC_Format_BIN = 0x00,
	TM_RTC_Format_BCD
} TM_RTC_Format_t;

/**
 * Select RTC to wakeup MCU every X seconds
 *
 * Parameters:
 * 	- TM_RTC_Int_Disable:
 * 		Disable wakeup interrupt
 * 	- TM_RTC_Int_60s:
 * 		Interrupt every 60 seconds
 * 	- TM_RTC_Int_30s:
 * 		Interrupt every 30 seconds
 * 	- TM_RTC_Int_15s:
 * 		Interrupt every 15 seconds
 * 	- TM_RTC_Int_10s:
 * 		Interrupt every 10 seconds
 * 	- TM_RTC_Int_5s:
 * 		Interrupt every 5 seconds
 * 	- TM_RTC_Int_2s:
 * 		Interrupt every 2 seconds
 * 	- TM_RTC_Int_1s:
 * 		Interrupt every 1 seconds
 * 	- TM_RTC_Int_500ms:
 * 		Interrupt every 500 milliseconds
 * 	- TM_RTC_Int_250ms:
 * 		Interrupt every 250 milliseconds
 * 	- TM_RTC_Int_125ms:
 * 		Interrupt every 125 milliseconds
 */
typedef enum {
	TM_RTC_Int_Disable = 0x00,
	TM_RTC_Int_60s,
	TM_RTC_Int_30s,
	TM_RTC_Int_15s,
	TM_RTC_Int_10s,
	TM_RTC_Int_5s,
	TM_RTC_Int_2s,
	TM_RTC_Int_1s,
	TM_RTC_Int_500ms,
	TM_RTC_Int_250ms,
	TM_RTC_Int_125ms
} TM_RTC_Int_t;

/**
 * Use internal or external clock
 *
 * Parameters:
 * 	- TM_RTC_ClockSource_Internal:
 * 		Use internal clock for RTC, LSI oscillator
 * 	- TM_RTC_ClockSource_External
 * 		Use external, more accurate, clock for RTC, 32768Hz
 *
 * Note: Internal clock is not so accurate
 */
typedef enum {
	TM_RTC_ClockSource_Internal = 0x00,
	TM_RTC_ClockSource_External
} TM_RTC_ClockSource_t;

/**
 * Use alarm type you will use
 *
 * Parameters:
 * 	- TM_RTC_AlarmType_DayInWeek
 * 		Trigger alarm every day in a week,
 * 		days from 1 to 7 (Monday to Sunday)
 * 	- TM_RTC_AlarmType_DayInMonth
 * 		Trigger alarm every month
 */
typedef enum {
	TM_RTC_AlarmType_DayInWeek,
	TM_RTC_AlarmType_DayInMonth
} TM_RTC_AlarmType_t;

/**
 * Alarm identifier you will use
 *
 * Parameters:
 * 	- TM_RTC_Alarm_A
 * 		Work with alarm A
 * 	- TM_RTC_Alarm_B
 * 		Work with alarm B
 */
typedef enum {
	TM_RTC_Alarm_A = 0x00,
	TM_RTC_Alarm_B
} TM_RTC_Alarm_t;

/**
 * Struct for alarm time
 *
 * Parameters:
 *  - TM_RTC_AlarmType_t alarmtype:
 *		Alarm type setting. Read TM_RTC_AlarmType_t typedef comment for more info
 * 	- uint8_t seconds:
 * 		Seconds parameter, from 00 to 59
 * 	- uint8_t minutes:
 * 		Minutes parameter, from 00 to 59
 * 	- uint8_t hours:
 * 		Hours parameter, 24Hour mode, 00 to 23
 * 	- uint8_t day:
 * 		If you select trigger for alarm every week, then this parameter has value between
 * 		1 and 7, representing days in a week, Monday to Sunday
 * 		If you select trigger for alarm every month, then this parameter has value between
 * 		1 - 31, representing days in a month.
 */
typedef struct {
	TM_RTC_AlarmType_t alarmtype;
	uint8_t seconds;
	uint8_t minutes;
	uint8_t hours;
	uint8_t day;
} TM_RTC_AlarmTime_t;

/**
 * Get number of seconds from 01.01.1970 00:00:00
 *
 * Parameters:
 * 	- TM_RTC_Time_t* data:
 * 		Struct to time data
 *
 * Returns Unix seconds
 */
extern uint32_t TM_RTC_GetUnixTimeStamp(TM_RTC_Time_t* data);

/**
 * Get formatted time from seconds till 01.01.1970 00:00:00
 * It fills struct with valid data. Valid if year is greater or equal (>=) than 2000
 *
 * Parameters:
 * 	- TM_RTC_Time_t* data:
 * 		Pointer to TM_RTC_Time_t struct to store formatted data in
 * 	- uint32_t unix:
 * 		Seconds from 01.01.1970 00:00:00
 */
extern void TM_RTC_GetDateTimeFromUnix(TM_RTC_Time_t* data, uint32_t unix);

/**
 * Initialize RTC
 *
 * Parameters:
 * 	- TM_RTC_ClockSource_t source:
 * 		Select RTC clock source
 * Returns 0 if RTC was initialized first time (power up), so you know when to set date and time
 */
extern uint32_t TM_RTC_Init(TM_RTC_ClockSource_t source);

/**
 * Select RTC interrupt
 *
 * Parameters:
 * 	- TM_RTC_Int_t int_value:
 * 		Choose struct member from struct TM_RTC_Int_t
 */
extern void TM_RTC_Interrupts(TM_RTC_Int_t int_value);

/**
 * Set date and time
 *
 * Parameters:
 * 	- TM_RTC_Time_t* data:
 * 		Struct to time data
 * 	- TM_RTC_Format_t format:
 * 		Member of struct TM_RTC_Format_t
 */
extern void TM_RTC_SetDateTime(TM_RTC_Time_t* data, TM_RTC_Format_t format);

/**
 * Get date and time
 *
 * Parameters:
 * 	- TM_RTC_Time_t* data:
 * 		Struct to time data where to save data
 * 	- TM_RTC_Format_t format:
 * 		Member of struct TM_RTC_Format_t
 */
extern void TM_RTC_GetDateTime(TM_RTC_Time_t* data, TM_RTC_Format_t format);

/**
 * Enable Alarm A or Alarm B for RTC
 *
 * Parameters:
 * 	- TM_RTC_Alarm_t Alarm:
 *		Specify alarm A or B
 * 	- TM_RTC_AlarmTime_t* AlarmTime:
 *		Pointer to alarm time struct
 * 	TM_RTC_Format_t format:
 * 		Stored date and time format, can be binary or "binary coded decimal"
 */
extern void TM_RTC_SetAlarm(TM_RTC_Alarm_t Alarm, TM_RTC_AlarmTime_t* AlarmTime, TM_RTC_Format_t format);


/**
 * Disable specific alarm
 *
 * Parameters:
 * 	- TM_RTC_Alarm_t Alarm:
 * 		Select Alarm A or Alarm B to be disabled
 */
extern void TM_RTC_DisableAlarm(TM_RTC_Alarm_t Alarm);

/**
 * Custom Request handler for RTC wakeup interrupt
 *
 * Called from main handler when wakeup interrupt occured
 *
 * WIth __weak parameter to prevent link errors if not defined by user
 */
extern  void TM_RTC_RequestHandler(void);

/**
 * Custom Alarm A interrupt handler
 *
 * Called when Alarm A interrupt is triggered
 *
 * WIth __weak parameter to prevent link errors if not defined by user
 */
extern  void TM_RTC_AlarmAHandler(void);

/**
 * Custom Alarm B interrupt handler
 *
 * Called when Alarm B interrupt is triggered
 *
 * WIth __weak parameter to prevent link errors if not defined by user
 */
extern  void TM_RTC_AlarmBHandler(void);

#endif
