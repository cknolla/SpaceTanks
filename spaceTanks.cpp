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
    messageY = 0;
}

//=============================================================================
// Destructor
//=============================================================================
SpaceTanks::~SpaceTanks()
{
    releaseAll();           // call onLostDevice() for every graphics item
    SAFE_DELETE(dxFont);
}

//=============================================================================
// Initializes the game
// Throws GameError on error
//=============================================================================
void SpaceTanks::initialize(HWND hwnd)
{
    Game::initialize(hwnd); // throws GameError

    // menu texture
    if (!menuTexture.initialize(graphics,MENU_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menu texture"));

    // menu image
    if (!menu.initialize(graphics,0,0,0,&menuTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menu"));

    // initialize DirectX font
    // 18 pixel high Arial
    if(dxFont->initialize(graphics, 18, true, false, "Arial") == false)
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing DirectX font"));

    menu.setDegrees(300);
    menu.setScale(0.002861f);

    message = "\n\n\nUtilizes Object Oriented C++ and DirectX\n\n";
    message += "Sprites with Transparency\n\n";
    message += "Three types of Collision Detection:\n";
    message += "     - Circular (Distance)\n";
    message += "     - Oriented Box\n";
    message += "     - Rotated Box\n\n";
    message += "XACT Audio\n\n";
    message += "Sprite and DirectX Text\n\n";
    message += "Tile Based Graphics\n\n";
    message += "TCP/IP and UDP/IP Network Support\n\n";
    messageY = GAME_HEIGHT;

    return;
}

//=============================================================================
// Update all game items
//=============================================================================
void SpaceTanks::update()
{
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
{}

//=============================================================================
// Render game items
//=============================================================================
void SpaceTanks::render()
{
    graphics->spriteBegin();                // begin drawing sprites
	/*
    menu.draw();
    dxFont->setFontColor(graphicsNS::ORANGE);
    dxFont->print(message,20,(int)messageY);
	*/
    graphics->spriteEnd();                  // end drawing sprites
}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void SpaceTanks::releaseAll()
{
    dxFont->onLostDevice();
    menuTexture.onLostDevice();
    Game::releaseAll();
    return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces.
//=============================================================================
void SpaceTanks::resetAll()
{
    menuTexture.onResetDevice();
    dxFont->onResetDevice();
    Game::resetAll();
    return;
}