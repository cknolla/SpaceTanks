#include "gridVector.h"

void GridVector::setPos(int newX, int newY, Image* image)
{
   x = newX;
   y = newY;
   image->setX(x*GRID_SIZE);
   image->setY(y*GRID_SIZE);
}

int GridVector::get1dPos(int x, int y)
{
   int pos = x*(MAX_ROWS + 1) + y;
   return pos;
}