#ifndef I2C_H
#define I2C_H

#include <Wire.h>

class I2C
{
  public:
    /* Write functions */
    static void writeByte( uint8_t devID, uint8_t reg_addr, uint8_t val );
    static void writeBit ( uint8_t devID, uint8_t reg_addr, uint8_t bitNumber, bool val );
	
    /* Read functions */
    static bool readBytes( uint8_t devID, uint8_t reg_addr, uint8_t bytesToRead, uint8_t *buf );
    static void readByte ( uint8_t devID, uint8_t reg_addr, uint8_t *ptr );
    static bool readBit  ( uint8_t devID, uint8_t reg_addr, uint8_t bitNumber );
};

#endif
