#ifndef I2C_H
#define I2C_H

#include <Wire.h>

class I2C
{
  public:
    /* Write functions */
    static void writeBit    ( uint8_t devID, uint8_t reg_addr, uint8_t bitNumber, boolean val );
    static void flipBit     ( uint8_t devID, uint8_t reg_addr, uint8_t bitNumber );
    static void write8      ( uint8_t devID, uint8_t reg_addr, int8_t val );
    static void write16     ( uint8_t devID, uint8_t reg_addr, int16_t val );
    
    /* Read functions */
    static boolean readBit  ( uint8_t devID, uint8_t reg_addr, uint8_t bitNumber );
    static int8_t  read8    ( uint8_t devID, uint8_t reg_addr );
    static int16_t read16   ( uint8_t devID, uint8_t reg_addr );
    static boolean readBytes( uint8_t devID, uint8_t reg_addr, uint8_t bytesToRead, int8_t *buf );
};

#endif
