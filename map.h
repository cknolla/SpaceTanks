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
   // light mode is like carrying a flashlight. If false, the whole map is visible
   bool lightMode;
   // number of spaces away from the player where walls are visible
   int lightRadius;
public:
   Map();
   ~Map();

   bool initialize(Game* gamePtr);

//   Wall* getFirstWall() { return firstWall; }
   std::vector<Wall*>& getHorizontalWalls() { return horizontalWalls; }
   std::vector<Wall*>& getVerticalWalls() { return verticalWalls; }

   void generatePath(GridVector startingPoint);
   bool getLightMode() { return lightMode; }
   void setLightMode(bool lm) { lightMode = lm; }
   int getLightRadius() { return lightRadius; }
   void setLightRadius(int lr) { lightRadius = lr; }

	void onLostDevice();
	void onResetDevice();

};


#endif