#include "I2C.h"

static void I2C::write8( uint8_t devID, uint8 reg_addr, int8_t val ) 
{
  Wire.beginTransmission( devID );	// start transmission to device 
  Wire.write( reg_addr );				    // send register address
  Wire.write( val );					      // send value to write
  Wire.endTransmission();			      // end transmission
}

static void I2C::write16( uint8_t devID, uint8_t reg_addr, int16_t val )
{
  write8( devID, reg_addr, val >> 8 );
  write8( devID, reg_addr + 1, val & 0xFF )
}

static boolean I2C::readBytes( uint8_t devID, uint8_t reg_addr, uint8_t bytesToRead, int8_t *buf )
{
  Wire.beginTransmission(devID);	// start transmission to device 
  Wire.write(reg_addr);				    // send register address
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
static int8_t I2C::read8( uint8_t devID, uint8_t reg_addr )
{
  int8_t b;
  
  Wire.beginTransmission(devID);	// start transmission to device 
  Wire.write(reg_addr);				    // send register address
  Wire.endTransmission();

  Wire.beginTransmission(devID);
  Wire.requestFrom( devID, 1 );   // Request 1 byte from device
  
  b = Wire.read();
  Wire.endTransmission();
  
  return ( b );
}

static int16_t I2C::read16( uint8_t devID, uint8_t reg_addr )
{
  int8_t b[2];
  
  /* Read 1 word (2 bytes)*/
  if( readBytes(devID, reg_addr, 2, b) )
    return ( ((uint16_t) b[0] << 8) | b[1] );
  
  return false;
}

/* bitNumber is from 0 to N-1, right to left. That is, bit 0 is the 
 * least significant bit. bit 1 the 2nd least significant, and so on. 
 */
static boolean I2C::readBit( uint8_t devID, uint8_t reg_addr, uint8_t bitNumber )
{
  int8_t b;
  
  /* Read the contents of reg_addr */
  b = read8( devID, reg_addr ); 
  return ( (b >> bitNumber) & 1 );
}

static void I2C::writeBit( uint8_t devID, uint8_t reg_addr, uint8_t bitNumber, bool val )
{
  int8_t b;

  /* Read the contents of reg_addr */
  b = read8( devID, reg_addr ); 

  /* Modify the bit in the register */
  if( val )
    b |= (val << bitNumber);
  else
    b &= ~(val << bitNumber);
  
  /* Write new value to reg_addr */
  write8( devID, reg_addr, b );	
}

static void flipBit( uint8_t devID, uint8_t reg_addr, uint8_t bitNumber )
{
  int8_t b;
  
  /* Read the contents of reg_addr */
  b = read8( devID, reg_addr ); 
  
  /* XOR operator */
  b ^= ( 1 << bitNumber );
  
  write8( devID, reg_addr, b );
}
