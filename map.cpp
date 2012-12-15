#include "map.h"

Map::Map()
{
	firstWall = NULL;
	size = 800;
}

Map::~Map()
{
	Wall* curWall = firstWall;
	Wall* nextWall;

	onLostDevice();

	while(curWall) {
		nextWall = curWall->getNextWall();
		SAFE_DELETE(curWall);
		curWall = nextWall;
	}

}

bool Map::initialize(Game* gamePtr)
{
	char errorStr[200];
	int tempSize;
	int randomNum;
	Wall* curWall = NULL;
	Wall* prevWall = NULL;
	int startX = 1, startY = 1;
	int curX = startX, curY = startY;
	
	srand(time(NULL));

	if (!wallTexture.initialize(gamePtr->getGraphics(),"pictures\\wall.png"))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing wall texture"));

	// initialize walls
	for(tempSize = size; tempSize > 0; tempSize--)
	{
		curWall = new Wall;
		if(!firstWall)
			firstWall = curWall;
		if(prevWall)
			prevWall->setNextWall(curWall);
		if (!curWall->initialize(gamePtr, &wallTexture)) {
			sprintf_s(errorStr, "Error initializing wall #%d", size-tempSize);
			throw(GameError(gameErrorNS::FATAL_ERROR, errorStr));
			return false;
		}
		prevWall = curWall;
	}

	curWall = firstWall;
	for(tempSize = size/2; tempSize > 0; tempSize--) {
		curWall->setCoord(rand() % MAX_COLS, rand() % MAX_ROWS, ROW);
		curWall = curWall->getNextWall();
	}
	for(tempSize = size/2; tempSize > 0; tempSize--) {
		curWall->setCoord(rand() % MAX_COLS, rand() % MAX_ROWS, COL);
		curWall = curWall->getNextWall();
	}


/*	while(curWall) {
		curWall->setCoord(curX, curY, COL);
		curWall = curWall->getNextWall();
		curX += 1;
	}
	*/
	return true;

}

void Map::onLostDevice()
{
	wallTexture.onLostDevice();
}

void Map::onResetDevice()
{
	wallTexture.onResetDevice();
}