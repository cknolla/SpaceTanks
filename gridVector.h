#ifndef _GRID_VECTOR_H           
#define _GRID_VECTOR_H 
#define WIN32_LEAN_AND_MEAN

#include "constants.h"
#include "image.h"


const int GRID_SIZE = 32;
const int MAX_ROWS = GAME_HEIGHT / GRID_SIZE;
const int MAX_COLS = GAME_WIDTH / GRID_SIZE;

class GridVector {

   // this struct allows working in int grid math versus screen position floats directly
private:
   int x;
   int y;
public:
   GridVector() : x(0), y(0) {}
   GridVector(int x, int y) : x(x), y(y) {}
   void setPos(int x, int y, Image* image);
   int getX() { return x; }
   int getY() { return y; }
   // convert 2d into 1d for std::vector position
   static int get1dPos(int x, int y);


   VECTOR2 gridToScreen() { return VECTOR2((float)x*GRID_SIZE, (float)y*GRID_SIZE); }


};

#endif