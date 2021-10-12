/* Start Header **************************************************************/
/*!
\game		Get Off My Lawn!
\file		GameState_LevelSelect.h
\author		Tan Zhi Quan, zhiquan.tan, (100%)
\par        zhiquan.tan\@digipen.edu
\date       13/04/18
\brief

This file contains the implementation for functions used in the Level Select
gamestate.
Functions include:
GameStateLevelSelectLoad
GameStateLevelSelectInit
GameStateLevelSelectUpdate
GameStateLevelSelectDraw
GameStateLevelSelectFree
GameStateLevelSelectUnload

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
All content © 2018 DigiPen (SINGAPORE) Corporation, all rights reserved.
*/
/* End Header ****************************************************************/

#ifndef GAMESTATE_LEVELSELECT_H
#define GAMESTATE_LEVELSELECT_H

/******************************************************************************/
/*!
"Load" function of this state
*/
/******************************************************************************/
void GameStateLevelSelectLoad(void);

/******************************************************************************/
/*!
"Initialize" function of this state
*/
/******************************************************************************/
void GameStateLevelSelectInit(void);

/******************************************************************************/
/*!
"Update" function of this state
*/
/******************************************************************************/
void GameStateLevelSelectUpdate(void);

/******************************************************************************/
/*!
"Draw" function of this state
*/
/******************************************************************************/
void GameStateLevelSelectDraw(void);

/******************************************************************************/
/*!
"Free" function of this state
*/
/******************************************************************************/
void GameStateLevelSelectFree(void);

/******************************************************************************/
/*!
"Unload" function of this state
*/
/******************************************************************************/
void GameStateLevelSelectUnload(void);

#endif GAMESTATE_LEVELSELECT_H