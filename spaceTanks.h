// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// SpaceTanksClass.h

#ifndef _SPACETANKS_H           // Prevent multiple definitions if this 
#define _SPACETANKS_H           // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include <string>
#include "game.h"
#include "textureManager.h"
#include "image.h"
#include "textDX.h"
#include "tank.h"
#include "map.h"
#include "wall.h"

#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"xinput.lib")

//=============================================================================
// This class is the core of the game
//=============================================================================
class SpaceTanks : public Game
{
private:
    // game items
    TextureManager tankTexture; // textures
	Map currentMap;
    Tank playerTank;               // menu image
    TextDX  *dxFont;            // DirectX font
    std::string  message;
    float messageY;

public:
    // Constructor
    SpaceTanks();
    // Destructor
    virtual ~SpaceTanks();
    // Initialize the game
    void initialize(HWND hwnd);
    void update();      // must override pure virtual from Game
    void ai();          // "
    void collisions();  // "
    void render();      // "
    void releaseAll();
    void resetAll();
};

#endif
