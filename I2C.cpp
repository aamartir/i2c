#include "I2C.h"

static void I2C::writeByte( uint8_t devID, uint8 reg_addr, uint8_t val ) 
{
  Wire.beginTransmission(devID);	// start transmission to device 
  Wire.write(reg_addr);				// send register address
  Wire.write(val);					// send value to write
  Wire.endTransmission();			// end transmission
}

static bool I2C::readBytes( uint8_t devID, uint8_t reg_addr, uint8_t bytesToRead, uint8_t *buf )
{
  Wire.beginTransmission(devID);	// start transmission to device 
  Wire.write(reg_addr);				// send register address
  Wire.endTransmission();

  Wire.beginTransmission(devID);
  Wire.requestFrom( devID, bytesToRead );

  uint8_t i = 0;
  while( Wire.available() )
  {
    buf[i++] = Wire.read();
  }
  
  Wire.endTransmission();

  return ( i == bytesToRead );
}

/* Results of the read are stored in ptr */
static void I2C::readByte( uint8_t devID, uint8_t reg_addr, uint8_t *ptr )
{
  readBytes( devID, reg_addr, 1, ptr );
}

/* bitNumber is from 0 to N-1, right to left. That is, bit 0 is the 
 * least significant bit. bit 1 the 2nd least significant, and so on. 
 */
static bool I2C::readBit( uint8_t devID, uint8_t reg_addr, uint8_t bitNumber )
{
  uint8_t byte_ptr;
  readByte( devID, reg_addr, &byte_ptr ); /* Populate byte_ptr with the contents of reg_addr */
  return ( (byte_ptr >> bitNumber) & 1 );
}

static void I2C::writeBit( uint8_t devID, uint8_t reg_addr, uint8_t bitNumber, bool val )
{
  uint8_t byte_ptr;

  /* First we read the contents of reg_addr */
  readByte( devID, reg_addr, &byte_ptr ); 

  /* Modify the bit in the register */
  if( val )
    byte_ptr |= (val << bitNumber);
  else
    byte_ptr &= ~(val << bitNumber);
  
  /* Write new value to reg_addr */
  writeByte( devID, reg_addr, byte_ptr );	
}
