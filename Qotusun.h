#ifndef QOTUSUN_H_
#define QOTUSUN_H_


// 2014.8.23 change the pinWrite function

#include <avr/io.h>
#include <stdbool.h>
#include <util/delay.h>

#define byte uint8_t


#define UNUSED(var) ((void)(var))
#define EMPTY_FUNC	((void)(0))

#define noinline __attribute__ ((__noinline__))

#define delay(ms) _delay_ms(ms)
#define delay_us(us) _delay_us(us)

// Quick and easy macro for a for loop
#define LOOP(count, var) for(byte var=0;var<count;var++)

// Reverse loop sometimes produces smaller/faster code
#define LOOPR(count, var) for(byte var=count;var--;)

#define CONCAT(a, b) a ## b




#define B0 0
#define B1 1
#define B2 2
#define B3 3
#define B4 4
#define B5 5
#define B6 6
#define B7 7

#define D0 8
#define D1 9
#define D2 10
#define D3 11
#define D4 12
#define D5 13
#define D6 14
#define D7 15

#define C0 16
#define C1 17
#define C2 18
#define C3 19
#define C4 20
#define C5 21
#define C6 22
#define C7 23


#define A7 24
#define A6 25
#define A5 26
#define A4 27
#define A3 28
#define A2 29
#define A1 30
#define A0 31

struct IOStruct
{
    volatile unsigned char* pinRegister;
    volatile unsigned char* portRegister;
    volatile unsigned char* ddrRegister;
    volatile unsigned char bitmask;
};

#define TOGGLE 2
#define HIGH 1
#define LOW 0


#define INPUT 0
#define OUTPUT 1
#define INPUT_PU 2


//#define PU_EN true
//#define PU_DIS false


#define BITS7(arg, bits...) ((arg>=0)? (1 << (arg)):0)
#define BITS6(arg, bits...) ((arg>=0)? (1 << (arg)):0) | \
BITS7(bits, -1)
#define BITS5(arg, bits...) ((arg>=0)? (1 << (arg)):0) | \
BITS6(bits, -1)
#define BITS4(arg, bits...) ((arg>=0)? (1 << (arg)):0) | \
BITS5(bits, -1)
#define BITS3(arg, bits...) ((arg>=0)? (1 << (arg)):0) | \
BITS4(bits, -1)
#define BITS2(arg, bits...) ((arg>=0)? (1 << (arg)):0) | \
BITS3(bits, -1)
#define BITS1(arg, bits...) ((arg>=0)? (1 << (arg)):0) | \
BITS2(bits, -1)
#define BITS0(arg, bits...) ((arg>=0)? (1 << (arg)):0) | \
BITS1(bits, -1)

#define SET_BITS(var, bits...)   var |=   BITS0(bits, -1)
#define CLEAR_BITS(var, bits...) var &= ~(BITS0(bits, -1))
#define LOAD_BITS(var, bits...)  var =    BITS0(bits, -1)


static inline void get_io_registers(struct IOStruct* io,unsigned char pin)
{
    io->ddrRegister=0;
    io->pinRegister=0;
    io->portRegister=0;
    io->bitmask=0;

    if(pin < 8)
    {

        io->pinRegister=(unsigned char*) &PINB;
        io->portRegister=(unsigned char*) &PORTB;
        io->ddrRegister=(unsigned char*) &DDRB;
        io->bitmask= 1<<pin;
    }

    else if(pin < 16)
    {
        io->pinRegister=(unsigned char*) &PIND;
        io->portRegister=(unsigned char*) &PORTD;
        io->ddrRegister=(unsigned char*) &DDRD;
        io->bitmask=1<<(pin-8);

    }

    else if(pin < 24)
    {
        io->pinRegister=(unsigned char*) &PINC;
        io->portRegister=(unsigned char*) &PORTC;
        io->ddrRegister=(unsigned char*) &DDRC;
        io->bitmask=1<<(pin-16);

    }
    else if(pin < 32)
    {
        io->pinRegister=(unsigned char*) &PINA;
        io->portRegister=(unsigned char*) &PORTA;
        io->ddrRegister=(unsigned char*) &DDRA;
        io->bitmask=1<<(31-pin);
    }
}

static inline void pinMode(unsigned char pin,unsigned char mode)
{
    struct IOStruct* _io=0;
    get_io_registers(_io,pin);

    if (mode == INPUT_PU)
        *(_io->portRegister) |= _io->bitmask;
    mode ? (*(_io->ddrRegister) |= _io->bitmask) : (*(_io->ddrRegister) &= _io->bitmask);

}

static inline unsigned char pinRead(unsigned char pin)
{
    struct IOStruct* _io=0;
    get_io_registers(_io,pin);

    return *(_io->pinRegister) & _io->bitmask ? HIGH : LOW;
}

static inline void pinWrite(unsigned char pin,unsigned char value)
{
    struct IOStruct* _io=0;
    get_io_registers(_io,pin);

    //value ? (*(_io->portRegister) |= _io->bitmask) : (*(_io->portRegister) &= ~(_io->bitmask));// add the TOGGLE action

    value ? ( (--value) ? (*(_io->pinRegister) |= _io->bitmask) : (*(_io->portRegister) |= _io->bitmask) ) : (*(_io->portRegister) &= ~(_io->bitmask));
}

#endif // QOTUSUN_H_
