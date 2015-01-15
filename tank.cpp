
#include "tank.h"

Tank::Tank()
{
	moved = 'n';
   gridPos.setPos(MAX_COLS/2, MAX_ROWS/2, this);
}

Tank::~Tank()
{
}

void Tank::moveLeft()
{
   flipHorizontal(false);
//	setDegrees(90.0);
//	if(gridPos.getX() > 0) {
		moved = 'l';
//		gridPos.setPos(gridPos.getX()-1,gridPos.getY(), this);
//	} 
}

void Tank::moveRight()
{
   flipHorizontal(true);
// setDegrees(270.0);
//	if(gridPos.getX() < MAX_COLS-1) {
		moved = 'r';
//      gridPos.setPos(gridPos.getX() + 1, gridPos.getY(), this);
//	} 
}

void Tank::moveUp()
{
//	setDegrees(180.0);
//	if(gridPos.getY() > 0) {
		moved = 'u';
//      gridPos.setPos(gridPos.getX(), gridPos.getY() - 1, this);
//	}
}

void Tank::moveDown()
{
//	setDegrees(0.0);
//	if(gridPos.getY() < MAX_ROWS-1) {
		moved = 'd';
//     gridPos.setPos(gridPos.getX(), gridPos.getY() + 1, this);
//	} 
}
