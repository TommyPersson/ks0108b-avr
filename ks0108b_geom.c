#include "ks0108b_geom.h"
#include "ks0108b.h"
#include "math.h"

void ks0108b_unset_pixel(uint8_t x, uint8_t y)
{

  /*   y                  */
  /*   0                  */
  /* 0 +----------> x 127 */
  /*   |                  */
  /*   |                  */
  /*   v                  */
  /*   63                 */

 
  if ( !(x < 128 && y < 64) )
    return;

  uint8_t display, page, pixel;

  if ( x < 64 )
  {
    display = 0; // left side
  }
  else
  {
    display = 1; // right side
    x -= 64;
  }

  page = y/8;

  pixel = y%8;
  
  uint8_t data = 0;
  uint8_t old_data = 0;
  uint8_t old_data2 = 0;

  ks0108b_set_page(page, display);

  ks0108b_set_y_address(x, display);
  ks0108b_read_display_data(&old_data, display);

  ks0108b_set_y_address(x, display);
  ks0108b_read_display_data(&old_data2, display);

  data = old_data2 & (~_BV(pixel));

  ks0108b_set_y_address(x, display);
  ks0108b_write_display_data(data, display);  

}

void ks0108b_set_pixel(uint8_t x, uint8_t y)
{


  /*   y                  */
  /*   0                  */
  /* 0 +----------> x 127 */
  /*   |                  */
  /*   |                  */
  /*   v                  */
  /*   63                 */

 
  if ( !(x < 128 && y < 64) )
    return;

  uint8_t display, page, pixel;

  if ( x < 64 )
  {
    display = 0; // left side
  }
  else
  {
    display = 1; // right side
    x -= 64;
  }

  page = y/8;

  pixel = y%8;
  
  uint8_t data = 0;
  uint8_t old_data = 0;
  uint8_t old_data2 = 0;

  ks0108b_set_page(page, display);

  ks0108b_set_y_address(x, display);
  ks0108b_read_display_data(&old_data, display);
  ks0108b_set_y_address(x, display);
  ks0108b_read_display_data(&old_data2, display);

  data = old_data2 | _BV(pixel);

  ks0108b_set_y_address(x, display);
  ks0108b_write_display_data(data, display);  


}


void ks0108b_circle(uint8_t x0, uint8_t y0, uint8_t radius)
{
  

 /* signed int raster_x, raster_y; */
 /*  uint8_t r2 = radius*radius; */

 /*  for (raster_x = -radius; raster_x <= radius; raster_x++) */
 /*  { */
 /*    raster_y = (int) (sqrt(r2 - raster_x*raster_x) + 0.5); */
 /*    ks0108b_set_pixel(x+raster_x, y+raster_y); */
 /*    ks0108b_set_pixel(x+raster_x, y-raster_y); */
 /*  } */

    int f = 1 - radius;
    int ddF_x = 1;
    int ddF_y = -2 * radius;
    int x = 0;
    int y = radius;
 
    ks0108b_set_pixel(x0, y0 + radius);
    ks0108b_set_pixel(x0, y0 - radius);
    ks0108b_set_pixel(x0 + radius, y0);
    ks0108b_set_pixel(x0 - radius, y0);
 
    while(x < y)
    {
      /* assert(ddF_x == 2 * x + 1); */
      /* assert(ddF_y == -2 * y); */
      /* assert(f == x*x + y*y - radius*radius + 2*x - y + 1); */
      if(f >= 0) 
      {
        y--;
        ddF_y += 2;
        f += ddF_y;
      }
      x++;
      ddF_x += 2;
      f += ddF_x;    
      ks0108b_set_pixel(x0 + x, y0 + y);
      ks0108b_set_pixel(x0 - x, y0 + y);
      ks0108b_set_pixel(x0 + x, y0 - y);
      ks0108b_set_pixel(x0 - x, y0 - y);
      ks0108b_set_pixel(x0 + y, y0 + x);
      ks0108b_set_pixel(x0 - y, y0 + x);
      ks0108b_set_pixel(x0 + y, y0 - x);
      ks0108b_set_pixel(x0 - y, y0 - x);
    }


}

#define SWAP(x, y) (x ^= y ^= x ^= y)

void ks0108b_line(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1)
{

   int Dx = x1 - x0; 
   int Dy = y1 - y0;
   int steep = (fabs(Dy) >= fabs(Dx));
   if (steep) {
       SWAP(x0, y0);
       SWAP(x1, y1);
       // recompute Dx, Dy after swap
       Dx = x1 - x0;
       Dy = y1 - y0;
   }
   int xstep = 1;
   if (Dx < 0) {
       xstep = -1;
       Dx = -Dx;
   }
   int ystep = 1;
   if (Dy < 0) {
       ystep = -1;		
       Dy = -Dy; 
   }
   int TwoDy = 2*Dy; 
   int TwoDyTwoDx = TwoDy - 2*Dx; // 2*Dy - 2*Dx
   int E = TwoDy - Dx; //2*Dy - Dx
   int y = y0;
   int xDraw, yDraw;	
   int x;
   for (x = x0; x != x1; x += xstep) {		
       if (steep) {			
           xDraw = y;
           yDraw = x;
       } else {			
           xDraw = x;
           yDraw = y;
       }
       // plot
       ks0108b_set_pixel(xDraw, yDraw);
       // next
       if (E > 0) {
           E += TwoDyTwoDx; //E += 2*Dy - 2*Dx;
           y = y + ystep;
       } else {
           E += TwoDy; //E += 2*Dy;
       }
   }

   // above buggy? Doesn't always output end pixels
   ks0108b_set_pixel(x0, y0);
   ks0108b_set_pixel(x1, y1);

}


void ks0108b_rectangle(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1)
{
 
  ks0108b_line(x0, y0, x0, y1);
  ks0108b_line(x0, y0, x1, y0);

  ks0108b_line(x1, y1, x1, y0);
  ks0108b_line(x1, y1, x0, y1);
  
}


void ks0108b_triangle(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2)
{
 
  ks0108b_line(x0, y0, x1, y1);
  ks0108b_line(x1, y1, x2, y2);
  ks0108b_line(x2, y2, x0, y0);
  
}

