// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// SpaceTanksClass.cpp v1.0
// This class is the core of the game

#include "spaceTanks.h"
#include <sstream>

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
    mapComplete = false;
    newMap();

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

void SpaceTanks::newMap()
{
   SAFE_DELETE(currentMap);
   currentMap = new Map;
   currentMap->initialize(this);
   playerTank.getGridPos().setPos(MAX_COLS/2, MAX_ROWS/2, &playerTank);
}

//=============================================================================
// Update all game items
//=============================================================================
void SpaceTanks::update()
{
   if(mapComplete) {
      newMap();
      mapComplete = false;
   }
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
      newMap();
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
//   if(newX >= 0 && newY >= 0 && newX < MAX_COLS+1 && newY < MAX_ROWS+1 && playerTank.getMoved() != 'n') {
   if(playerTank.getMoved() != 'n') {
      char str[200];
      sprintf_s(str, "newX = %d, newY = %d", newX, newY);
      message = str;
      if(newX == -1 || newX == MAX_COLS || newY == -1 || newY == MAX_ROWS) {
         mapComplete = true;
      } else {
         try {
            if(!walls->at(GridVector::get1dPos(wallX, wallY))->getSolid()) {
               playerTank.getGridPos().setPos(newX, newY, &playerTank);
            }
         } catch(std::out_of_range e) {
            throw(GameError(gameErrorNS::FATAL_ERROR, str));
         }
      }
   }

}

//=============================================================================
// Render game items
//=============================================================================
void SpaceTanks::render()
{
   
    graphics->spriteBegin();                // begin drawing sprites
	
    playerTank.draw();
    renderWalls(&currentMap->getHorizontalWalls());
    renderWalls(&currentMap->getVerticalWalls());
    
    dxFont->setFontColor(graphicsNS::ORANGE);
    dxFont->print(message,20,(int)messageY);
	
    graphics->spriteEnd();                  // end drawing sprites
}

void SpaceTanks::renderWalls(std::vector<Wall*>* walls)
{
   int playerX = playerTank.getGridPos().getX();
   int playerY = playerTank.getGridPos().getY();
   Wall* curWall = NULL;
   std::vector<int> visibleWalls;
   if(currentMap->getLightMode()) {
      for(int lightX = 0; lightX < currentMap->getLightRadius(); lightX++) {
         for(int lightY = 0; lightY < currentMap->getLightRadius(); lightY++) {
            if(playerX - lightX >= 0) {
               if(playerY - lightY >= 0) {
                  visibleWalls.push_back(GridVector::get1dPos(playerX - lightX, playerY - lightY));
               }
               if(playerY + lightY <= MAX_ROWS) {
                  visibleWalls.push_back(GridVector::get1dPos(playerX - lightX, playerY + lightY));
               }
            }
            if(playerX + lightX <= MAX_COLS) {
               if(playerY - lightY >= 0) {
                  visibleWalls.push_back(GridVector::get1dPos(playerX + lightX, playerY - lightY));
               }
               if(playerY + lightY <= MAX_ROWS) {
                  visibleWalls.push_back(GridVector::get1dPos(playerX + lightX, playerY + lightY));
               }
            }
         }
      }
   }
   for(int pos = 0;  pos < walls->size(); pos++) {
      Wall* curWall = walls->at(pos);
      bool visibility = true;
      if(!curWall->getSolid()) {
         visibility = false;
      } else {
         if(currentMap->getLightMode()) {
            visibility = false;
            for(int visiblePos : visibleWalls) {
               if(pos == visiblePos) {
                  visibility = true;
                  break;
               }
            }
         }
      }
      curWall->setVisible(visibility);
      curWall->draw();
   }
}

//=============================================================================
// Process console commands
//=============================================================================
void SpaceTanks::consoleCommand()
{
   command = console->getCommand();    // get command from console
   if(command == "")                   // if no command
      return;

   if(command == "help")              // if "help" command
   {
      console->print("Console Commands:");
      console->print("fps - toggle display of frames per second");
      return;
   }

   if(command == "fps") {
      fpsOn = !fpsOn;                 // toggle display of fps
      if(fpsOn)
         console->print("fps On");
      else
         console->print("fps Off");
   }
   
   if(command == "lightMode") {
      if(currentMap) {
         currentMap->setLightMode(!currentMap->getLightMode());
         if(currentMap->getLightMode())
            console->print("lightMode On");
         else
            console->print("lightMode Off");
      }
   }
   std::string commandStr = "";
   int arg1 = 0;
   if(std::stringstream(command) >> commandStr >> arg1) {
      if(commandStr == "lightRadius") {

         if(currentMap) {
            currentMap->setLightRadius(arg1);
            std::string consoleStr = "light radius set to " + arg1;
            console->print(consoleStr);
         }
      }
   }
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
