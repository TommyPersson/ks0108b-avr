#include "ks0108b_geom.h"
#include "ks0108b.h"
#include "fonts.h"

#include <avr/pgmspace.h>
#include <avr/io.h>

#include <string.h>
#include <stdio.h>

void ks0108b_write_char5x7(char c, uint8_t x, uint8_t y)
{

  if ( !(x < 128 && y < 64) )
    return;

  uint8_t cbyte, cbit;
  uint8_t byte;

  for (cbyte = 0; cbyte < 5; cbyte++)
  {
    
    byte = pgm_read_byte( &font5x7[(c-0x20)*5 + cbyte] );

    for (cbit = 0; cbit < 8; cbit++)
    {
      if (byte & _BV(cbit))
        ks0108b_set_pixel(x+cbyte,y+cbit);
    }
   
  }
  
}

void ks0108b_write_string5x7(char *string, uint8_t x, uint8_t y)
{

  uint8_t i;

  for (i = 0; i < strlen(string); i++, x+=6)
  {
    ks0108b_write_char5x7(string[i], x, y);
  }
}


void ks0108b_write_char5x12(char c, uint8_t x, uint8_t y)
{

  if ( !(x < 128 && y < 64) )
    return;

  uint8_t cbyte, cbit;
  uint8_t byte;

  for (cbyte = 0; cbyte < 5; cbyte++)
  {
    
    byte = pgm_read_byte( &font5x12[(c-0x20)*10 + cbyte] );

    for (cbit = 0; cbit < 8; cbit++)
    {
      if (byte & _BV(cbit))
        ks0108b_set_pixel(x+cbyte,y+cbit);
    }
   
  }

  for (cbyte = 0; cbyte < 5; cbyte++)
  {
    
    byte = pgm_read_byte( &font5x12[(c-0x20)*10 + cbyte + 5] );

    for (cbit = 0; cbit < 8; cbit++)
    {
      if (byte & _BV(cbit))
        ks0108b_set_pixel(x+cbyte,y+cbit+5);
    }
   
  }
  
}

void ks0108b_write_string5x12(char *string, uint8_t x, uint8_t y)
{

  uint8_t i;

  for (i = 0; i < strlen(string); i++, x+=6)
  {
    ks0108b_write_char5x12(string[i], x, y);
  }
}

void ks0108b_write_decimal5x7(uint32_t number, uint8_t x, uint8_t y)
{
  const int MAX_DIGITS = 10;

  char asciinumber[MAX_DIGITS];
  snprintf(asciinumber, MAX_DIGITS, "%ld", number);

  ks0108b_write_string5x7(asciinumber, x, y);
}
