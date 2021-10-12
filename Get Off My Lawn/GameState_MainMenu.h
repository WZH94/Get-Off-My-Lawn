/* Start Header **************************************************************/
/*!
\game		Get Off My Lawn!
\file		GameState_MainMenu.h
\author		Tan Zhi Quan, zhiquan.tan, (100%)
\par        zhiquan.tan\@digipen.edu
\date       13/04/18
\brief

This file contains the implementation for functions used in the Main Menu
gamestate.
Functions include:
GameStateMainMenuLoad
GameStateMainMenuInit
GameStateMainMenuUpdate
GameStateMainMenuDraw
GameStateMainMenuFree
GameStateMainMenuUnload

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
All content © 2018 DigiPen (SINGAPORE) Corporation, all rights reserved.
*/
/* End Header ****************************************************************/

#ifndef GAMESTATE_MAINMENU_H
#define GAMESTATE_MAINMENU_H

#include "main.h"

/******************************************************************************/
/*!
"Load" function of this state
*/
/******************************************************************************/
void GameStateMainMenuLoad(void);

/******************************************************************************/
/*!
"Initialize" function of this state
*/
/******************************************************************************/
void GameStateMainMenuInit(void);

/******************************************************************************/
/*!
"Update" function of this state
*/
/******************************************************************************/
void GameStateMainMenuUpdate(void);

/******************************************************************************/
/*!
"Draw" function of this state
*/
/******************************************************************************/
void GameStateMainMenuDraw(void);

/******************************************************************************/
/*!
"Free" function of this state
*/
/******************************************************************************/
void GameStateMainMenuFree(void);

/******************************************************************************/
/*!
"Unload" function of this state
*/
/******************************************************************************/
void GameStateMainMenuUnload(void);

#endif GAMESTATE_MAINMENU_H

