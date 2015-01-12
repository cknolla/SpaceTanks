#include "map.h"
#include <iostream>
#include <fstream>

Map::Map()
{
//	firstWall = NULL;
	size = 1000;
}

Map::~Map()
{
//	Wall* curWall = firstWall;
//	Wall* nextWall;

	onLostDevice();

   for(auto wall : horizontalWalls) {
      SAFE_DELETE(wall);
   }
   for(auto wall : verticalWalls) {
      SAFE_DELETE(wall);
   }
//	while(curWall) {
//		nextWall = curWall->getNextWall();
//		SAFE_DELETE(curWall);
//		curWall = nextWall;
//	}

}

bool Map::initialize(Game* gamePtr)
{
	char errorStr[200];

	Wall* curWall = NULL;


   if(!wallTexture.initialize(gamePtr->getGraphics(), "pictures\\wall4x36.png")) {
      throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing wall texture"));
   }

   // initialize walls and make all visible
   for(int i = 0; i < 2; i++) {
      std::vector<Wall*>* walls;
      enum ORIENTATION orientation;
      if(i == 0) {
         walls = &horizontalWalls;
         orientation = HORIZONTAL;
      } else {
         walls = &verticalWalls;
         orientation = VERTICAL;
//         visible = false;
      }
      for(int x = 0; x < MAX_COLS+1; x++) { // +1 to include top/bottom and left/right wall
         for(int y = 0; y < MAX_ROWS+1; y++) {
//            visible = !visible;
            curWall = new Wall;

            if(!curWall->initialize(gamePtr, &wallTexture)) {
               sprintf_s(errorStr, "Error initializing wall i = %d, x = %d, y = %d", i, x, y);
               throw(GameError(gameErrorNS::FATAL_ERROR, errorStr));
               return false;
            }
            curWall->setCoord(GridVector(x,y), orientation);
            walls->push_back(curWall);
         }
      }
   }
   generatePath(GridVector(0,0));
   /*
	curWall = firstWall;
	for(tempSize = size/2; tempSize > 0; tempSize--) {
		curWall->setCoord(rand() % MAX_COLS, rand() % MAX_ROWS, ROW);
		curWall = curWall->getNextWall();
	}
	for(tempSize = size/2; tempSize > 0; tempSize--) {
		curWall->setCoord(rand() % MAX_COLS, rand() % MAX_ROWS, COL);
		curWall = curWall->getNextWall();
	}
   */


/*	while(curWall) {
		curWall->setCoord(curX, curY, COL);
		curWall = curWall->getNextWall();
		curX += 1;
	}
	*/
	return true;

}

void Map::generatePath(GridVector startingPoint)
{
   int startX = startingPoint.getX();
   int startY = startingPoint.getY();
   srand(time(NULL));
   std::ofstream logfile;
   logfile.open("pathLog.txt");
   logfile << "Writing this to a file.\n";
   logfile.close();
}

void Map::onLostDevice()
{
	wallTexture.onLostDevice();
}

void Map::onResetDevice()
{
	wallTexture.onResetDevice();
}