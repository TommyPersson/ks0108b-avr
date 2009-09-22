#ifndef KS0108B_GEOM_H_
#define KS0108B_GEOM_H_

#include <inttypes.h>

void ks0108b_unset_pixel(uint8_t x, uint8_t y);

void ks0108b_set_pixel(uint8_t x, uint8_t y);

void ks0108b_circle(uint8_t x, uint8_t y, uint8_t radius); 

void ks0108b_line(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);

void ks0108b_rectangle(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);

void ks0108b_triangle(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);

#endif
