#ifndef I2C_H_
#define I2C_H_


#include <typedefs.h>
//#include "common.h"


#define SDA			C1
#define SCL			C0



#define I2C_NACK	false
#define I2C_ACK		true
#define I2C_W		0
#define I2C_R		1

void i2c_init(void);
//void i2c_resetState(void);
void i2c_start(void);
void i2c_stop(void);
bool i2c_stop_error(void);
bool i2c_write(byte);
bool i2c_read(byte*, bool);




#endif//End of I2C_H_
