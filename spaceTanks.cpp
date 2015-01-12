// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// SpaceTanksClass.cpp v1.0
// This class is the core of the game

#include "spaceTanks.h"

//=============================================================================
// Constructor
//=============================================================================
SpaceTanks::SpaceTanks()
{
    dxFont = new TextDX();  // DirectX font
    messageY = GAME_HEIGHT-20.0f;
}

//=============================================================================
// Destructor
//=============================================================================
SpaceTanks::~SpaceTanks()
{
    releaseAll();           // call onLostDevice() for every graphics item
	 SAFE_DELETE(currentMap);
    SAFE_DELETE(dxFont);
}

//=============================================================================
// Initializes the game
// Throws GameError on error
//=============================================================================
void SpaceTanks::initialize(HWND hwnd)
{
    Game::initialize(hwnd); // throws GameError
	currentMap = new Map;

	currentMap->initialize(this);

    // textures
    if (!tankTexture.initialize(graphics,"pictures\\testSet000.png"))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing tank texture"));


    // images
    if (!playerTank.initialize(this,0,0,0,&tankTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing player tank"));


    // initialize DirectX font
    // 18 pixel high Arial
    if(dxFont->initialize(graphics, 18, true, false, "Arial") == false)
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing DirectX font"));

//	playerTank.setX(0.0f);
//	playerTank.setY(0.0f);


    return;
}

//=============================================================================
// Update all game items
//=============================================================================
void SpaceTanks::update()
{
	char str[200];
	sprintf_s(str, "X = %.3f, Y = %.3f", playerTank.getX(), playerTank.getY());
//	message = str;
	
	if(input->wasKeyPressed(ESC_KEY)) { // Quit if ESC pressed
		PostQuitMessage(0);
	}

	if(input->wasKeyPressed('A')) {
		playerTank.moveLeft();
	} else if(input->wasKeyPressed('D')) {
		playerTank.moveRight();
	} else if(input->wasKeyPressed('W')) {
		playerTank.moveUp();
	} else if(input->wasKeyPressed('S')) {
		playerTank.moveDown();
	} else if (input->wasKeyPressed('1')) {
		delete currentMap;
		currentMap = new Map;
		currentMap->setSize(100);
		currentMap->initialize(this);
	} else
		playerTank.setMoved('n');
	/*
    if(menu.getDegrees() > 0)
    {
        menu.setDegrees(menu.getDegrees() - frameTime * 120);
        menu.setScale(menu.getScale() + frameTime * 0.4f);
    }
    else if(messageY > -400)
    {
        menu.setDegrees(0);
        menu.setY(menu.getY() - frameTime * 50);
        messageY -= frameTime * 50;
    }
    else    // start over
    {
        menu.setDegrees(300);
        menu.setScale(0.002861f);
        menu.setY(0);
        messageY = GAME_HEIGHT;
    }
	*/
}

//=============================================================================
// Artificial Intelligence
//=============================================================================
void SpaceTanks::ai()
{}

//=============================================================================
// Handle collisions
//=============================================================================
void SpaceTanks::collisions()
{
   int newX = playerTank.getGridPos().getX();
   int newY = playerTank.getGridPos().getY();
   int wallX = newX;
   int wallY = newY;
   std::vector<Wall*>* walls = &(currentMap->getVerticalWalls());
   if(playerTank.getMoved() == 'l') {
      newX -= 1;   
   } else if(playerTank.getMoved() == 'r') {
      newX += 1;
      wallX += 1;
   } else if(playerTank.getMoved() == 'u') {
      newY -= 1;
      walls = &(currentMap->getHorizontalWalls());
   } else if(playerTank.getMoved() == 'd') {
      newY += 1;
      wallY += 1;
      walls = &(currentMap->getHorizontalWalls());
   }
   if(newX >= 0 && newY >= 0 && newX < MAX_COLS+1 && newY < MAX_ROWS+1 && playerTank.getMoved() != 'n') {
      char str[200];
      sprintf_s(str, "newX = %d, newY = %d, size = %d", newX, newY, walls->size());
      message = str;
      try {
         if(!walls->at(wallX*(MAX_ROWS+1) + wallY)->getVisible()) {
            playerTank.getGridPos().setPos(newX, newY, &playerTank);
         }
      } catch(std::out_of_range e) {
         throw(GameError(gameErrorNS::FATAL_ERROR, str));
      }
   }
   /*
	VECTOR2 collisionVector;
//	Wall* curWall = currentMap->getFirstWall();
	float shiftAmount = 8.0f;

	if(playerTank.getMoved() == 'l') {
		playerTank.setX(playerTank.getX()+shiftAmount);
		for(auto curWall : currentMap->getWalls()) {
			if(playerTank.collidesWith((*curWall), collisionVector)) {
				playerTank.setX(playerTank.getX()+GRID_SIZE);
				message = "Collision";
				break; // prevent a chain reaction shifting you all the way left off the screen
			}
//			curWall = curWall->getNextWall();
		}
		playerTank.setX(playerTank.getX()-shiftAmount);
	}
	else if(playerTank.getMoved() == 'r') {
		playerTank.setX(playerTank.getX()-shiftAmount);
		for(auto curWall : currentMap->getWalls()) {
			if(playerTank.collidesWith((*curWall), collisionVector)) {
				playerTank.setX(playerTank.getX()-GRID_SIZE);
				message = "Collision";
				break;
			}
//			curWall = curWall->getNextWall();
		}
		playerTank.setX(playerTank.getX()+shiftAmount);
	}
	else if(playerTank.getMoved() == 'u') {
		playerTank.setY(playerTank.getY()+shiftAmount);
      for(auto curWall : currentMap->getWalls()) {
			if(playerTank.collidesWith((*curWall), collisionVector)) {
				playerTank.setY(playerTank.getY()+GRID_SIZE);
				message = "Collision";
				break;
			}
//			curWall = curWall->getNextWall();
		}
		playerTank.setY(playerTank.getY()-shiftAmount);
	}
	else if(playerTank.getMoved() == 'd') {
		playerTank.setY(playerTank.getY()-shiftAmount);
      for(auto curWall : currentMap->getWalls()) {
			if(playerTank.collidesWith((*curWall), collisionVector)) {
				playerTank.setY(playerTank.getY()-GRID_SIZE);
				message = "Collision";
				break;
			}
//			curWall = curWall->getNextWall();
		}
		playerTank.setY(playerTank.getY()+shiftAmount);
	}
   */
}

//=============================================================================
// Render game items
//=============================================================================
void SpaceTanks::render()
{
//	Wall* curWall = currentMap->getFirstWall();
    graphics->spriteBegin();                // begin drawing sprites
	
    playerTank.draw();
    for(auto curWall : currentMap->getHorizontalWalls()) {
		curWall->draw();
	}
    for(auto curWall : currentMap->getVerticalWalls()) {
       curWall->draw();
    }
    dxFont->setFontColor(graphicsNS::ORANGE);
    dxFont->print(message,20,(int)messageY);
	
    graphics->spriteEnd();                  // end drawing sprites
}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void SpaceTanks::releaseAll()
{
    dxFont->onLostDevice();
    tankTexture.onLostDevice();
	currentMap->onLostDevice();
    Game::releaseAll();
    return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces.
//=============================================================================
void SpaceTanks::resetAll()
{
    tankTexture.onResetDevice();
    dxFont->onResetDevice();
	currentMap->onResetDevice();
    Game::resetAll();
    return;
}
