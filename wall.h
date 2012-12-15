#ifndef _WALL_H               // Prevent multiple definitions if this 
#define _WALL_H               // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"

class Wall;

class Wall : public Entity
{
private:
	Wall* nextWall;
public:
	Wall();
	~Wall();

	bool initialize(Game* gamePtr, TextureManager* texture);

	void setCoord(int x, int y, enum ROWCOL rowOrCol);

	Wall* getNextWall() { return nextWall; }
	void setNextWall(Wall* nw) { nextWall = nw; }

};


#endif