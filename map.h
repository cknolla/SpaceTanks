#ifndef _MAP_H               // Prevent multiple definitions if this 
#define _MAP_H               // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "wall.h"
#include <vector>
#include <time.h>

class Map;

class Map : public Entity {
private:
   TextureManager wallTexture;
   // walls are stored by x first, then y.
   std::vector<Wall*> horizontalWalls;
   // walls are stored by x first, then y.
   std::vector<Wall*> verticalWalls;
//   Wall* firstWall;
   int size;
public:
   Map();
   ~Map();

   bool initialize(Game* gamePtr);

//   Wall* getFirstWall() { return firstWall; }
   std::vector<Wall*>& getHorizontalWalls() { return horizontalWalls; }
   std::vector<Wall*>& getVerticalWalls() { return verticalWalls; }

	void setSize(int newSize) { size = newSize; }
	int getSize() { return size; }

   void generatePath(GridVector startingPoint);

	void onLostDevice();
	void onResetDevice();

};


#endif