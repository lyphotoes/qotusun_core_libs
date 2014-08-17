#ifndef RTC_H_

#define RTC_H_
//#include "typedefs.h"
//#include "devices/rtc_funcs.h"
#include "config.h"

typedef enum
{
    RTC_SQW_OFF = 0,
    RTC_SQW_ON = 1
} rtc_sqw_t;

typedef struct
{
    signed char whole;
    byte frac;
} rtc_temperature_s;
/*
#if RTC_SRC == RTC_SRC_INTERNAL
void rtc_init(void);
#define rtc_get(timeData)				EMPTY_FUNC
#define rtc_save(timeData)				EMPTY_FUNC
#else
*/
#if RTC_SRC == RTC_SRC_PCF8563
    #include "devices/pcf8563.h"
    #define RTC_I2C_ADDR PCF8563_I2C
    #define RTCFUNC(x) pcf8563_## x
#elif RTC_SRC ==RTC_SRC_DS1307
    #include "devices/ds1307.h"
    #define RTC_I2C_ADDR DS1307_I2C
    #define RTCFUNC(x) ds1307_## x
#else
    #error "Invalid RTC Source!"
#endif // RTC_SRC


#define rtc_init (RTCFUNC(init))
#define rtc_get (RTCFUNC(get))
#define rtc_getBCD (RTCFUNC(getBCD))
#define rtc_save (RTCFUNC(save))




//#endif //RTC_SRC



#endif // RTC_H_
