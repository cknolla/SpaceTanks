#ifndef _TANK_H               // Prevent multiple definitions if this 
#define _TANK_H               // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "gridVector.h"

class Tank;

class Tank : public Entity
{
private:
	char moved;
   GridVector gridPos;
public:
	Tank();
	~Tank();

	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();

	char getMoved() { return moved; }
	void setMoved(char newMoved) { moved = newMoved; }
   GridVector& getGridPos() { return gridPos; }
};


#endif
