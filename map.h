#ifndef _MAP_H               // Prevent multiple definitions if this 
#define _MAP_H               // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "wall.h"
#include <time.h>

class Map;

class Map : public Entity
{
private:
	TextureManager wallTexture;
	Wall* firstWall;
	int size;
public:
	Map();
	~Map();

	bool initialize(Game* gamePtr);

	Wall* getFirstWall() { return firstWall; }

	void setSize(int newSize) { size = newSize; }
	int getSize() { return size; }

	void onLostDevice();
	void onResetDevice();

};


#endif