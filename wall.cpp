#include "wall.h"

Wall::Wall()
{
	nextWall = NULL;
}

Wall::~Wall()
{
}

bool Wall::initialize(Game* gamePtr, TextureManager* texture)
{
	// Tiles will be in independent texture files, so width, height, and cols can be defaulted to 0
	return(Entity::initialize(gamePtr, 0, 0, 0, texture));
}

void Wall::setCoord(int x, int y, enum ROWCOL rowOrCol)
{
	if(rowOrCol == COL) {
		setX((getHeight()-getWidth()) * (float)x);
		setY((getHeight()-getWidth()) * (float)y);
		edge.left = -spriteData.width/2 + 1;
		edge.top = -spriteData.height/2 + 1;
		edge.right = spriteData.width/2 - 1;
		edge.bottom = spriteData.height/2 - 1;
	}
	if(rowOrCol == ROW) {
		setX((getHeight()-getWidth()) * (float)x + (getHeight()-getWidth())/2); // wall is rotated around its center, so it is offset
		setY((getHeight()-getWidth()) * (float)y - (getHeight()-getWidth())/2);
		setDegrees(90.0f);
		edge.left = -spriteData.height/2 + 1;
		edge.top = -spriteData.width/2 + 1;
		edge.right = spriteData.height/2 - 1;
		edge.bottom = spriteData.width/2 - 1;
	}
}