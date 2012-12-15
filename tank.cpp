
#include "tank.h"

Tank::Tank()
{
	moved = 'n';
}

Tank::~Tank()
{
}

void Tank::moveLeft()
{
	setDegrees(90.0);
	if(getX()-GRID_SIZE >= 0.0) {
		moved = 'l';
		setX(getX()-GRID_SIZE);
	} 
}

void Tank::moveRight()
{
	setDegrees(270.0);
	if(getX()+GRID_SIZE <= GAME_WIDTH) {
		moved = 'r';
		setX(getX()+GRID_SIZE);
	} 
}

void Tank::moveUp()
{
	setDegrees(180.0);
	if(getY()-GRID_SIZE >= 0.0) {
		moved = 'u';
		setY(getY()-GRID_SIZE);
	}
}

void Tank::moveDown()
{
	setDegrees(0.0);
	if(getY()+GRID_SIZE <= GAME_HEIGHT) {
		moved = 'd';
		setY(getY()+GRID_SIZE);
	} 
}
