#ifndef _WALL_H               // Prevent multiple definitions if this 
#define _WALL_H               // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "gridVector.h"

class Wall;

class Wall : public Entity
{
public:
   Wall() {}
	~Wall();

	bool initialize(Game* gamePtr, TextureManager* texture);

   // doesn't sit right on grid lines. Move walls with this function
	void setCoord(GridVector newGridPos, enum ORIENTATION orientation);

};


#endif