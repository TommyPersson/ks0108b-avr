#ifndef KS0108B_FONT_H_
#define KS0108B_FONT_H_

#include <inttypes.h>

void ks0108b_write_char5x7(char c, uint8_t x, uint8_t y);
void ks0108b_write_string5x7(char *string, uint8_t x, uint8_t y);
void ks0108b_write_char5x12(char c, uint8_t x, uint8_t y);
void ks0108b_write_string5x12(char *string, uint8_t x, uint8_t y);

void ks0108b_write_decimal5x7(uint32_t number, uint8_t x, uint8_t y);

#endif
