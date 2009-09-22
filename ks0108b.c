#include "ptlcd.h"

#include <util/delay.h>


/*************** User functions ****************/

bool ks0108b_is_reset(void)
{
  
  uint8_t reset, throw_away1, throw_away2;

  ks0108b_status_read(&throw_away1, &throw_away1, &reset, 0);

  return (bool) reset;

}

bool ks0108b_is_on(void)
{
  
  uint8_t on, throw_away1, throw_away2;

  ks0108b_status_read(&throw_away1, &on, &throw_away2, 0);

  return (bool) on;

}

void ks0108b_clear_screen(void)
{
  int i,j;

  for (j = 0; j < 8; j++)
  {
    ks0108b_set_page(j,0);
    ks0108b_set_y_address(0,0);

    for (i = 0; i < 64; i++)
    {
      ks0108b_write_display_data(0x00, 0);
      ks0108b_set_y_address(i+1,0); // otherwise it will +2??
    }
    
  }
  
  for (j = 0; j < 8; j++)
  {
    ks0108b_set_page(j,1);
    ks0108b_set_y_address(0,1);

    for (i = 0; i < 64; i++)
    {
      ks0108b_write_display_data(0x00, 1);
      ks0108b_set_y_address(i+1,1); // otherwise it will +2??
    }
  }
}

void ks0108b_fill_screen(void)
{
  int i,j;

  for (j = 0; j < 8; j++)
  {
    ks0108b_set_page(j,0);
    ks0108b_set_y_address(0,0);

    for (i = 0; i < 64; i++)
    {
      ks0108b_write_display_data(0xff, 0);
      ks0108b_set_y_address(i+1,0); // otherwise it will +2??
    }
    
  }
  
  for (j = 0; j < 8; j++)
  {
    ks0108b_set_page(j,1);
    ks0108b_set_y_address(0,1);

    for (i = 0; i < 64; i++)
    {
      ks0108b_write_display_data(0xff, 1);
      ks0108b_set_y_address(i+1,1); // otherwise it will +2??
    }
  }
}


/*************** Primitive functions  ***************/

void ks0108b_initialize(void)
{
  ks0108b_reset();

  _delay_ms(10);

  ks0108b_display_on_off(1,0);
  ks0108b_display_on_off(1,1);

  _delay_ms(10);

  ks0108b_display_start_line(0,0);
  ks0108b_display_start_line(0,1);

  _delay_ms(10);

  ks0108b_set_y_address(0,0);
  ks0108b_set_y_address(0,1);

  _delay_ms(10);

  ks0108b_set_page(0,0);
  ks0108b_set_page(0,1);
}


void ks0108b_reset(void)
{
  LCD_CONTROL_PORT_DDR = 0xFF;
  LCD_DATA_PORT_DDR = 0xFF;
  LCD_CONTROL_PORT &= ~_BV(LCD_RST);
  _delay_ms(1);
  LCD_CONTROL_PORT |= _BV(LCD_RST); 
}

void ks0108b_display_on_off(uint8_t on, uint8_t display)
{

  uint8_t data = _BV(LCD_DB5) | _BV(LCD_DB4) | _BV(LCD_DB3) | 
    _BV(LCD_DB2) | _BV(LCD_DB1) | (on << LCD_DB0);

  ks0108b_output_data(data, 0, display);

}

void ks0108b_display_start_line(uint8_t line, uint8_t display)
{

  line &= 0x3F; /* 00111111 */

  uint8_t data = _BV(LCD_DB7) | _BV(LCD_DB6) | line;
  
  ks0108b_output_data(data, 0, display);

}

void ks0108b_set_page(uint8_t page, uint8_t display)
{

  page &= 0x07; /* 00000111 */

  uint8_t data = _BV(LCD_DB7) | _BV(LCD_DB5) | _BV(LCD_DB4) | 
    _BV(LCD_DB3) | page;

  ks0108b_output_data(data, 0, display);

}

void ks0108b_set_y_address(uint8_t yaddr, uint8_t display)
{

  yaddr &=  0x3F; /* 00111111 */

  uint8_t data = _BV(LCD_DB6) | yaddr;

  ks0108b_output_data(data, 0, display);

  uint8_t throw_away;

}

void ks0108b_status_read(uint8_t *busy, uint8_t *on, uint8_t *reset, uint8_t display)
{
  // FIXME: look into this later
  uint8_t data;
/* ks0108b.c:108: warning: right shift count >= width of type */
/* ks0108b.c:110: warning: right shift count >= width of type */
/* ks0108b.c:112: warning: right shift count >= width of type */

  ks0108b_recv_data(&data, 0, display);

/*   *busy = (data & _BV(LCD_DB7)) >> _BV(LCD_DB7); */

/*   *on = (data & _BV(LCD_DB5)) >> _BV(LCD_DB5); */

/*   *reset = (data & _BV(LCD_DB4)) >> _BV(LCD_DB4); */


}

void ks0108b_write_display_data(uint8_t data, uint8_t display)
{

  ks0108b_output_data(data, 1, display);

}

void ks0108b_read_display_data(uint8_t *data, uint8_t display)
{

  ks0108b_recv_data(data, 1, display);

}

void ks0108b_output_data(uint8_t data, uint8_t di, uint8_t display)
{
  ks0108b_wait_on_busy();

  LCD_DATA_PORT_DDR = 0xFF;

  LCD_CONTROL_PORT_DDR |= _BV(LCD_DI) | _BV(LCD_RW) | _BV(LCD_E) | 
    _BV(LCD_CS1) | _BV(LCD_CS2) | _BV(LCD_RST);

  /* low R/W */
  LCD_CONTROL_PORT &= ~_BV(LCD_RW);

  if (di == 1)
  {
    LCD_CONTROL_PORT |= _BV(LCD_DI);
  }
  else
  { /* 0 */
    LCD_CONTROL_PORT &= ~(_BV(LCD_DI));
  }

  if (display == LCD_RIGHT_DISPLAY) /* right display */
  {
    LCD_CONTROL_PORT |= _BV(LCD_CS1);
    LCD_CONTROL_PORT &= ~_BV(LCD_CS2);   /* chip-select is active low */
  } else /* 0, left display */
  {
    LCD_CONTROL_PORT |= _BV(LCD_CS2);
    LCD_CONTROL_PORT &= ~_BV(LCD_CS1);
  }
  
  LCD_DATA_PORT = data;

  _delay_us(LCD_TIMING_TWL);

  /* raise E */
  LCD_CONTROL_PORT |= _BV(LCD_E);

  _delay_us(LCD_TIMING_TWH);

  /* drop E */
  LCD_CONTROL_PORT &= ~(_BV(LCD_E));

  _delay_us(LCD_TIMING_TAH);

  /* raise RW */
  LCD_CONTROL_PORT |= _BV(LCD_RW);

}

void ks0108b_recv_data(uint8_t *data, uint8_t di, uint8_t display)
{

  ks0108b_wait_on_busy();

  LCD_DATA_PORT_DDR = 0x00;
  LCD_CONTROL_PORT_DDR  |= _BV(LCD_DI) | _BV(LCD_RW) | _BV(LCD_E) | 
    _BV(LCD_CS1) | _BV(LCD_CS2) | _BV(LCD_RST);

  /* raise R/W */
  LCD_CONTROL_PORT |= _BV(LCD_RW);
  
  if (di == 1)
    LCD_CONTROL_PORT |= _BV(LCD_DI);
  else /* 0 */
    LCD_CONTROL_PORT &= ~(_BV(LCD_DI));

  /* do chip-select, reset magic ??? */
  if (display == LCD_RIGHT_DISPLAY) /* right display */
  {
    LCD_CONTROL_PORT |= _BV(LCD_CS1);
    LCD_CONTROL_PORT &= ~_BV(LCD_CS2);
  } else /* 0, left display */
  {
    LCD_CONTROL_PORT |= _BV(LCD_CS2);
    LCD_CONTROL_PORT &= ~_BV(LCD_CS1);
  }

  _delay_us(LCD_TIMING_TWL);

  /* raise E */
  LCD_CONTROL_PORT |= _BV(LCD_E);
  
  _delay_us(LCD_TIMING_TWH);

  *data = LCD_DATA_PORT_PINS;

  /* drop E and RW */
  LCD_CONTROL_PORT &= ~_BV(LCD_E);  
  LCD_CONTROL_PORT &= ~_BV(LCD_RW);

}

void ks0108b_wait_on_busy(void)
{

   LCD_DATA_PORT_DDR = 0x00;    // Set DDR to input.
   LCD_CONTROL_PORT_DDR = 0xFF; 

   LCD_CONTROL_PORT |= _BV(LCD_E) | _BV(LCD_RW);
   LCD_CONTROL_PORT &= ~_BV(LCD_DI);

   _delay_us(2); // kom ihåg att vänta ....

   while((LCD_DATA_PORT_PINS & 0x80))
     ;

   LCD_CONTROL_PORT &= ~(_BV(LCD_E) | _BV(LCD_RW));

} 
