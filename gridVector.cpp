#include "gridVector.h"

void GridVector::setPos(int newX, int newY, Image* image)
{
   x = newX;
   y = newY;
   image->setX(x*GRID_SIZE);
   image->setY(y*GRID_SIZE);
}