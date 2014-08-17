#include "i2c.h"
#include "config.h"

#define TWI_FREQ	400000UL
#define TWI_BR		(((F_CPU / TWI_FREQ) - 16) / 2)

void i2c_init()
{
	TWBR = TWI_BR;
}



void i2c_start()
{




	// START
	LOAD_BITS(TWCR, TWINT, TWSTA, TWEN);

	// Wait for START
	loop_until_bit_is_set(TWCR, TWINT);
}

void i2c_stop()
{
	// STOP
	LOAD_BITS(TWCR, TWINT, TWEN, TWSTO);

	// Wait for STOP
	// WARNING: A bad I2C line can cause this loop to hang
	//loop_until_bit_is_set(TWCR, TWSTO);
	byte counter = 255; // 255 * 5us = 1.275ms timeout
	while(bit_is_clear(TWCR, TWSTO) && counter--)
		delay_us(5);

	// Disable I2C
	CLEAR_BITS(TWCR, TWEN);


}

bool i2c_stop_error()
{
	i2c_stop();
	return false;
}

bool i2c_write(byte data)
{
	// Set data
	TWDR = data;

	// Begin sending
	LOAD_BITS(TWCR, TWINT, TWEN);

	// Wait for finish
	loop_until_bit_is_set(TWCR, TWINT);

	// Check status
	byte status = TW_STATUS;
	return (status == TW_MT_SLA_ACK || status == TW_MT_DATA_ACK || status == TW_MR_SLA_ACK);
}

bool i2c_read(byte* data, bool ack)
{
	// Expects more data (ACK) or not (NACK)
	//ack ? (SET_BITS(TWCR, TWEA)) : (CLEAR_BITS(TWCR, TWEA));
	// http://graphics.stanford.edu/~seander/bithacks.html#ConditionalSetOrClearBitsWithoutBranching
	TWCR = (TWCR & ~_BV(TWEA)) | (-ack & _BV(TWEA));

	// Begin receiving
	SET_BITS(TWCR, TWINT);

	// Wait for finish
	loop_until_bit_is_set(TWCR, TWINT);

	// Check status
	byte status = TW_STATUS;
	if(status != TW_MR_DATA_ACK && status != TW_MR_DATA_NACK)
		return false;

	// Read data
	*data = TWDR;
	return true;
}
