#ifndef KS0108B_CONFIG_H_
#define KS0108B_CONFIG_H_

#define LCD_CONTROL_PORT PORTC
#define LCD_CONTROL_PORT_DDR DDRC
#define LCD_RST PC5
#define LCD_RW PC3
#define LCD_DI PC4
#define LCD_CS2 PC2
#define LCD_CS1 PC1
#define LCD_E PC0

#define LCD_DATA_PORT PORTA
#define LCD_DATA_PORT_PINS PINA
#define LCD_DATA_PORT_DDR DDRA
#define LCD_DB0 PA0
#define LCD_DB1 PA1
#define LCD_DB2 PA2
#define LCD_DB3 PA3
#define LCD_DB4 PA4
#define LCD_DB5 PA5
#define LCD_DB6 PA6
#define LCD_DB7 PA7

/* Timing in µs */

/* Currently, odd values are used because of wonky(?) display hw */
#define LCD_TIMING_TC 1.2 /* > 1 */
#define LCD_TIMING_TWH 8 /* > 0.45*/
#define LCD_TIMING_TWL 1 /* > 0.45 */
#define LCD_TIMING_TASU 0.5 /* > 0.14*/
#define LCD_TIMING_TAH 0.10 /* > 0.01 */
#define LCD_TIMING_TSU 0.5 /* > 0.2 */
#define LCD_TIMING_TDHW 0.05 /* > 0.01 */
#define LCD_TIMING_TDHR 0.10 /* > 0.02 */

#endif
