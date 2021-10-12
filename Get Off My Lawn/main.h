/******************************************************************************/
/*!
\game	Get Off My Lawn!
\file   main.h
\author Ngm Hui Min, Lois (100%)
\par    email: lois.ngm\@digipen.edu
\par    DigiPen login: lois.ngm
\par    Course: GAM150
\date	13/04/18
\brief
This file contains the includes and global variables of main.cpp

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
All content © 2018 DigiPen (SINGAPORE) Corporation, all rights reserved.
*/
/******************************************************************************/
#ifndef MAIN_H
#define MAIN_H
//------------------------------------
// Globals

//extern float	g_dt;

// Width and height of the game screen
const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 600;

// Half, since game coordinates are cut in half
const int HALF_SCREEN_WIDTH = SCREEN_WIDTH / 2;
const int HALF_SCREEN_HEIGHT = SCREEN_HEIGHT / 2;

// Sets the game to be full screen or not
static bool full_screen = true;

static unsigned int 	gAEGameStateLevel = 0;           //!< Current Game Level

// ---------------------------------------------------------------------------
// includes

#include "AEEngine.h"			// Alpha Engine
#include "System.h"				// System function declarations
#include "GameStateManager.h"	// Game state manager functions declarations
#include <iostream>				// File I/O

#endif MAIN_H