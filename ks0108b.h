#ifndef KS0108B_H_
#define KS0108B_H_

#include <inttypes.h>

#include <avr/io.h>

#include <stdbool.h>

#include "config.h"

/*************** Definitions ****************/

#define LCD_LEFT_DISPLAY 0
#define LCD_RIGHT_DISPLAY 1

/*************** User functions ****************/

void ks0108b_initialize(void);

bool ks0108b_is_reset(void);

bool ks0108b_is_on(void);

void ks0108b_clear_screen(void);

void ks0108b_fill_screen(void);

/*************** Primitive functions  ***************/


void ks0108b_reset(void);

/* Controls display on/off. RAM data and internal status are not affected. */
void ks0108b_display_on_off(uint8_t on, uint8_t display); /* on = {0,1} */

/* Specifies the RAM line displayed at the top of the screen. */
void ks0108b_display_start_line(uint8_t line, uint8_t display); /* line = [0-63] */

/* Sets the page (X address) of RAM at the page (X address) register. */
void ks0108b_set_page(uint8_t page, uint8_t display); /* page = [0-7] */

/* Sets the Y address in the Y address in the counter. (sic)*/
void ks0108b_set_y_address(uint8_t yaddr, uint8_t display); /* yaddr = [0-63] */

/* Reads the status. */
void ks0108b_status_read(uint8_t *busy, uint8_t *on, uint8_t *reset, uint8_t display); /* returns {0,1} */

/* Writes data DB0 (LSB) to DB7 (MSB) on the data bus into display
 * RAM. Has access to the address of the display RAM specified in
 * advance. After the access, Y address is increased by 1. */
void ks0108b_write_display_data(uint8_t data, uint8_t display); /* data = [0-256] */

/* Reads data DB0 (LSB) to DB7 (MSB) from the display RAM to the data
 * bus. Has access to the address of the display RAM specified in
 * advance. After the access, Y address is increased by 1. */
void ks0108b_read_display_data(uint8_t *data, uint8_t display); /* returns *data = [0-256] */

void ks0108b_output_data(uint8_t data, uint8_t di, uint8_t display);

void ks0108b_recv_data(uint8_t *data, uint8_t di, uint8_t display);

void ks0108b_wait_on_busy(void);

#endif
